


#include "mygps.h"

unsigned int stack[128];
void getdata2(void *);

int  cog;
unsigned int stack[128];

fdserial *GPS; 
char RMC[100];
char GGA[100];


int start_gps(int rx, int tx, int mode, int baud)
{
  GPS = fdserial_open(rx, tx, mode, baud);

  cog=cogstart(getdata2, NULL, stack, sizeof(stack)); 
}  

  //start gps feed
void getdata2(void *par)
{
  char gpsraw; 
  char GPFEED[100];  
  
  RMC[0] = 0;
  GGA[0] = 0;
  
  while(1)
  {
    //read in characters from the GPS
    int idx = 0;
    do
    {
        gpsraw = fdserial_rxChar(GPS);
        GPFEED[idx++] = gpsraw;      
    } while(gpsraw != 13 && gpsraw != 10);
    GPFEED[idx] = 0;      //null terminate
    
   if(strncmp(GPFEED,"$GPRMC",6) == 0)
      strcpy(RMC,GPFEED);  
    if(strncmp(GPFEED,"$GPGGA",6) == 0)
       strcpy(GGA,GPFEED);
       
     
   // print(RMC);
   
  }
}

char *getRMC()
{
  return RMC;
}

char *getGGA()
{
  return GGA;
}

  