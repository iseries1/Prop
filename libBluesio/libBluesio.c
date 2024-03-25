/**
 * @brief Blues IO Notecard driver
 * @date March 15, 2024
 * @version 1.0
 * 
*/
#include "JSON.h"


#include "simpletools.h"
#include "bluesio.h"
#include "fdserial.h"
#include "json.h"
#include "base64.h"

void Hex(void *);

#define BRX 14
#define BTX 15

time_t tx;
struct tm *sr;
char Buffer[128];
char Data[64];
char fmt[] = "%4.2f";

int main()
{
  int i;
  float t, h, p;
  int v, c, l;
  
  i = Bluesio_Init(BRX, BTX);

  print("Version: %d\n", i);
  
  i = Bluesio_Status();
  
  print("status: %d\n", i);
  
  tx = Bluesio_GetTime()-18000;
  sr = localtime(&tx);
  
  print("Time: %d\n", tx);
  print("Date: %d/%d/%d\n", sr->tm_mon+1, sr->tm_mday, sr->tm_year+1900);
  sprinti(Buffer, "%02d:%02d:%02d\n", sr->tm_hour, sr->tm_min, sr->tm_sec);
  print(Buffer);
  
  t = 21.16;
  h = 37.21;
  p = 28.81;
  v = 7503;
  c = 10;
  l = 470;

/*  
  Buffer[0] = 0;
  json_init(Buffer);
  sprintf(Data, fmt, t);
  json_putDec("temperature", Data);
  sprintf(Data, fmt, h);
  json_putDec("humidity", Data);
  sprintf(Data, fmt, p);
  json_putDec("pressure", Data);
  sprintf(Data, "%d", v);
  json_putDec("voltage", Data);
  sprintf(Data, "%d", c);
  json_putDec("current", Data);
  sprintf(Data, "%d", l);
  json_putDec("light", Data);
  //i = Bluesio_Add(Buffer, NULL);
*/
  
  Buffer[0] = 0;
  json_init(Buffer);
  memcpy(&Data[0], &t, 4);
  memcpy(&Data[4], &h, 4);
  memcpy(&Data[8], &p, 4);
  memcpy(&Data[12], &v, 4);
  memcpy(&Data[16], &c, 4);
  memcpy(&Data[20], &l, 4);
  memcpy(&Data[24], &tx, 4);

  Base64_Encode(Data, Buffer, 28);
  
  print("Data:%s\n", Buffer);
  
  i = Bluesio_AddPayload(Buffer);
  
  print("status: %d\n", i);
  
  //Bluesio_Sync();
  
  print("Done\n");

  while(1)
  {
    pause(1000);
    
  }  
}

void Hex(void *d)
{
    char data[10];
    char *x = d;

    sprinti(data, "%2.2x%2.2x%2.2x%2.2x", x[0], x[1], x[2], x[3]);
    for(int i=0;i<10;i++)
      if (data[i] == ' ')
        data[i] = '0';
    strcat(Buffer, data);
}
