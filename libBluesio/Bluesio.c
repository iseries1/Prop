/**
 * @brief Blues IO Notecard driver
 * @date March 15, 2024
 * @version 1.0
 * 
*/

//#define DEBUG

#include "stdlib.h"
#include "stdio.h"
#include "simpletools.h"
#include "bluesio.h"
#include "fdserial.h"
#include "json.h"


volatile int rhd;
volatile int rtl;
volatile int thd;
volatile int ttl;
volatile int Rdy;
char IBuffer[1024];
char OBuffer[1024];
char XCmd[1024];
int BRx;
int BTx;
fdserial *bio;


void Bluesio_IO(void *);
void Bluesio_Send(char *);
int Bluesio_Return(void);


int Bluesio_Init(int rx, int tx)
{
  int i;
  
  BRx = rx;
  BTx = tx;
  cog_run(&Bluesio_IO, 50);
  pause(1000);
  
  i = Bluesio_Version();
  
  return i;
}

void Bluesio_Request(char *request)
{
  int i;
  
  json_init(XCmd);
  i = json_putStr("req", request);
  Bluesio_Send(XCmd);
#ifdef DEBUG
  print("request: %s\n", request);
#endif
}

int Bluesio_Receive(char *buffer)
{
  int i;
  
  i = 0;
  while (rhd != rtl)
  {
    buffer[i++] = IBuffer[rtl++];
    rtl = rtl & 1023;
    buffer[i] = 0;
  }
  Rdy = 0;
  return i;
}

void Bluesio_Sync(void)
{
  int s;
  
  Bluesio_Request("hub.sync");
  
  s = Bluesio_Return();
}

int Bluesio_Status(void)
{
  int s;
  char *x;
  
  Bluesio_Request("hub.sync.status");
  s = Bluesio_Return();
  if (s > 0)
  {
#ifdef DEBUG
    print("Status:%s\n", XCmd);
#endif
    json_init(XCmd);
    x = json_find("completed");
    return atoi(x);
  }
  return -1;
}

int Bluesio_Version(void)
{
  int status;
  int version;
  
  version = 0;
  Bluesio_Request("card.version");
  
  status = Bluesio_Return();
#ifdef DEBUG
  print("Version: %s\n", XCmd);
#endif
  if (status > 0)
  {
    json_init(XCmd);
    version = atoi(json_find("body.ver_major"));
    version = version * 10 + atoi(json_find("body.ver_minor"));
    version = version * 10 + atoi(json_find("body.ver_patch"));
    return version;
  }
  return 0;
}

int Bluesio_Add(char *note, char *file)
{
  int i;
  char *x;
  
  json_init(XCmd);
  json_putStr("req", "note.add");
  if (file != NULL)
    json_putStr("file", file);
  i = json_putObject("body");
  XCmd[i-1] = 0;
  strcat(XCmd, note);
  strcat(XCmd, "}");
  
  Bluesio_Send(XCmd);
  
#ifdef DEBUG
  print("Add: %s\n", XCmd);
#endif

  i = Bluesio_Return();
  if (i > 0)
  {
    json_init(XCmd);
    x = json_find("total");
    if (x == NULL)
      return 0;
    return atoi(x);
  }
  return -1;
}

int Bluesio_AddPayload(char *payload)
{
  int i;
  char *x;
  
  memset(XCmd, 0, sizeof(XCmd));
  json_init(XCmd);
  json_putStr("req", "note.add");
  json_putStr("file", "data.qo");
  json_putStr("payload", payload);
  
  Bluesio_Send(XCmd);
  
//#ifdef DEBUG
  print("Add: %s\n", XCmd);
//#endif

  i = Bluesio_Return();
  if (i > 0)
  {
    json_init(XCmd);
    x = json_find("total");
    if (x == NULL)
    {
      x = json_find("err");
      if (x != NULL)
        return -2;
      return 0;
    }
    return atoi(x);
  }
  return -1;
}

int Bluesio_Check(void)
{
  int i;
  char *x;
  
  json_init(XCmd);
  json_putStr("req", "file.changes");
  json_putArray("files");
  json_putItem("data.qi");
  json_putItem(NULL);
  
  Bluesio_Send(XCmd);
#ifdef DEBUG
  print("Check: %s\n", XCmd);
#endif
  i = Bluesio_Return();
  if (i > 0)
  {
    json_init(XCmd);
    x = json_find("total");
    if (x == NULL)
      return 0;
    return atoi(x);
  }
  return i;
}

int Bluesio_GetData(char *data, int remove)
{
  int i;

  json_init(XCmd);
  json_putStr("req", "note.get");
  json_putStr("file", "data.qi");
  if (remove != 0)
      json_putBool("delete", 1);
  Bluesio_Send(XCmd);

#ifdef DEBUG
  print("Get: %s\n", XCmd);
#endif

  i = Bluesio_Return();
  return i;
}

void Bluesio_SetAttn(int mode, int time)
{
  int i;
  char *x;
  char buf[10];

  json_init(XCmd);
  json_putStr("req", "card.attn");
  if (mode == 1)
      json_putStr("mode", "arm");
  if (mode == 2)
      json_putStr("mode", "sleep");
  if (mode == 3)
      json_putStr("mode", "disarm");
  sprinti(buf, "%d", time);
  json_putDec("seconds", buf);
  Bluesio_Send(XCmd);

#ifdef DEBUG
  print("Attn:%s\n", XCmd);
#endif

  i = Bluesio_Return();
  if (i > 0)
  {
      json_init(XCmd);
  }
}

float Bluesio_GetVoltage(void)
{
  int i;
  char *x;

  json_init(XCmd);
  json_putStr("req", "card.voltage");
  Bluesio_Send(XCmd);

#ifdef DEBUG
  print("Voltage:%s\n", XCmd);
#endif

  i = Bluesio_Return();
  if (i > 0)
  {
      json_init(XCmd);
      x = json_find("value");
      return atof(x);
  }
  return 0;
}

float Bluesio_GetTemperature(void)
{
  int i;
  char *x;

  json_init(XCmd);
  json_putStr("req", "card.temp");
  Bluesio_Send(XCmd);

#ifdef DEBUG
  print("Temp:%s\n", XCmd);
#endif

  i = Bluesio_Return();
  if (i > 0)
  {
     json_init(XCmd);
     x = json_find("value");
     return atof(x);
  }
  return 0;
}
  
int Bluesio_GetTime(void)
{
  int i;
  char *x;

  json_init(XCmd);
  json_putStr("req", "card.time");
  Bluesio_Send(XCmd);
    
#ifdef DEBUG
  print("Time:%s\n", XCmd);
#endif

  i = Bluesio_Return();
  if (i > 0)
  {
#ifdef DEBUG
     print("T:%s\n", XCmd);
#endif
     json_init(XCmd);
     x = json_find("time");
     return atoi(x);
  }
  return 0;
}



/**
 * Background serial interface tasks
 * 
 */
void Bluesio_IO(void *par)
{
  thd = 0;
  ttl = 0;
  rhd = 0;
  rtl = 0;
  Rdy = 0;
  
  bio = fdserial_open(BRx, BTx, FDSERIAL_MODE_NONE, 9600);

  while (1)
  {
    if (fdserial_rxReady(bio) != 0)
    {
      IBuffer[rhd] = fdserial_rxChar(bio);
      if (IBuffer[rhd++] == '\n')
        Rdy = 1;
      
      rhd = rhd & 1023;
    }
    
    if (thd != ttl)
    {
      fdserial_txChar(bio, OBuffer[ttl]);
      if (OBuffer[ttl++] == '\n')
        pause(5);
      ttl = ttl & 1023;
    }
    usleep(50);
  }
}

void Bluesio_Send(char *cmd)
{
  int len;
  
  len = strlen(cmd);
  for (int i=0;i<len;i++)
  {
    OBuffer[thd++] = cmd[i];
    thd = thd & 1023;
  }
  OBuffer[thd++] = '\r';
  thd = thd & 1023;
  OBuffer[thd++] = '\n';
  thd = thd & 1023;
}

/* wait 30 seconds for return data */
int Bluesio_Return()
{
    int i;

    for (i=0;i<30;i++)
    {
        if (Rdy != 0)
        {
            i = Bluesio_Receive(XCmd);
            return i;
        }
        pause(1000);
    }
    return 0;
}

