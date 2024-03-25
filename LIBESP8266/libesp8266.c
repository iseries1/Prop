/**
 * @brief Connect to Parallax WX board
 * @author Michael Burmeister
 * @date April 4, 2019
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "esp8266.h"

void printb(char *, int);

#define RX 31
#define TX 30

int i;
int s;
int t;
char Request;
fdserial *fd;


int main()
{
  
  fd = esp8266_open(RX, TX); // 31 30
  
  dprinti(fd, "Starting\n");
  
  pause(1000);
  dprinti(fd, "IP: %s\n", esp8266_check("station-ipaddr"));
  
  i = esp8266_listen(HTTP, "/test");
  
  if (i < 0)
  {
    dprinti(fd, "Listen Error %d\n", i);
    while (1)
      pause(1000);
  }
  
  i = esp8266_wait(&Request);
  
  dprinti(fd, "Request: %c, Status: %d\n", Request, i);
  esp8266_reply(i, "Got That!\r\n");
  
  while(1)
  {
    Request = esp8266_poll(0);
    if (Request != 'N')
    {
      dprinti(fd, "Poll: %c\n", Request);
      i = esp8266_results();
      dprinti(fd, "Handle: %d\n", i);
      if (Request == 'G')
        esp8266_reply(i, "Also got that\r\n");
    }      
    pause(1000);

  }  
}

void printb(char *data, int size)
{
  int n;
  
  for(n = 0; n < size; n++)
  {
    if(data[n] <= 128 && data[n] >= ' ')
    {
      putChar(data[n]);
    }      
    else if(data[n] == 0)
    {
      break;
    }      
    else if(data[n] == '\n')
    {
      putChar('\n');
    }
    else
    {
      print("[%x]", data[n]);
    }      
  }  
  print("[%d]\n", n);
}

  