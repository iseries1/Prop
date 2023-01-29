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
void doWeather1(void);
void doWeather2(void);

int i;
int s;
int t;
char Buffer[5100];
fdserial *fd;
char url[] = "api.openweathermap.org";
// id=<your city code>&APPID=<your application ID>
char rqs2[] = "GET /data/2.5/forecast?id=<Your ID>&units=imperial";
char rqs[] = "GET /data/2.5/weather?id=<Your ID>&units=imperial";
char rqs3[] = "GET /data/2.5/onecall?lat=44.84&lon=-87.37&exclude=minutely,daily,alert&APPID=<What?>&units=imperial";

int main()
{
  //simpleterm_close();
  
  fd = esp8266_open(14, 13); // 31 30
  
  print("Starting\n");
  
  //i = esp8266_set("wifi-mode", "STA");
  //print("WiFi: %d\n", i);
  pause(1000);
  printi("IP: %s\n", esp8266_check("station-ipaddr"));
  
//  i = esp8266_set("station-ipaddr", "101.1.1.43&101.1.1.4&255.255.255.0&101.1.1.1");
//  print("StationIP: %d\n", i);

//  i = esp8266_join("WiFi?", "Password?");
//  print("Join: %d\n", i);
  pause(1000);
  //memset(Buffer, 0, sizeof(Buffer));
  //doWeather1();
  
  memset(Buffer, 0, sizeof(Buffer));
  doWeather2();
  
  while(1)
  {
    pause(1000);
//    i = esp8266_poll(0);
//    print("Poll: %d\n", i);
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

void doWeather1()
{
  i = esp8266_connect(url, 80);
  if (i >= 0)
  {
    print("Sending request\n");
    s = esp8266_http(i, rqs, 0);
    print("Request: %d \n", s);
    
    t = esp8266_recv(i, Buffer, 1024);
    print("Recv: %d \n", t);
    if (t > 0)
      printb(Buffer, sizeof(Buffer));
    esp8266_close(i);
  }
  else
  {
    print("Connect Failed: %d\n", i);
  }
}

void doWeather2()
{
  i = esp8266_connect(url, 80);
  if (i >= 0)
  {
    print("Sending request 2\n");
    s = esp8266_http(i, rqs3, 0);
    print("Request: %d \n", s);
    pause(500);

    s = 0;
    do
    {
      t = esp8266_recv(i, &Buffer[s], 1024);
      print("recv: %d\n", t);
      s += t;
      if (s > 4096)
        break;
    } while (t > 12);
    printb(Buffer, sizeof(Buffer));
    esp8266_close(i);
  }
  else
  {
    print("Connect Failed: %d\n", i);
  }
}
  