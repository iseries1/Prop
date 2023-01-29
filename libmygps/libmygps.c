/*
 * @brief Test code for library only
 * @author Michael Burmeister
 * @date April 15, 2018
 * @version 1.0
*/

#include "simpletools.h"
#include "mygps.h"

#define Rx 0
#define Tx 27
#define Baud 9600

int rx_pin = 0;
int tx_pin = 27;
int mode_ = 0;
int Baud_rate = 9600;
int cog;

char *pRMC;
char *pGGA;

int main()                                    // Main function
{
  cog = start_gps(rx_pin, tx_pin, mode_, Baud_rate);
  print("cog %d\n",cog);
  
  pRMC = getRMC();
  pGGA = getGGA();
  
  while(1)
  {
   // getdata2();
   if (strlen(pRMC) > 0)
      print(pRMC);
   if (strlen(pGGA) > 0)
      print(pGGA);
    pause(500);  //pause half second
  }  
}




/*
void start_cog()

{
  cog=cogstart(getdata2,NULL,stack,sizeof(stack)); 
}  


void getdata2()

{
  //start gps feed
  
  {
   
  GPS = fdserial_open(rx_pin,tx_pin,mode_ ,Baud_rate);
  }   
  
  while(1)

{
  char gpsraw; 
  char GPFEED[100];  
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
   

 
}*/