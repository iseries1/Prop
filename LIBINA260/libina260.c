/**
 * @brief INA260 Adafruit power driver
 * @author Michael Burmeister
 * @date June 23, 2019
 * @version 1.0
 * 
*/
#include "ina260.h"
#include "simpletools.h"

#define CLK 15
#define DTA 14

char Modes[][20] = {"Power Down", "Current Trigger", "Voltage Trigger", "Trigger Both", "Power Down",
                   "Continues Current", "Continues Voltage", "Continues Both"};

int i;

int main()
{
  i = INA260_open(CLK, DTA);

  if (i == 0x5449)
    printi("INA260 Found\n");
  else
    printi("Device Not Found\n");

  i = INA260_getMode();
  printi("Mode: %s\n", Modes[i]);
  
  i = INA260_getVoltage();
  
  printi("Volts: %d\n", i);
  
  i = INA260_getCurrent();
  
  printi("Current: %d\n", i);
  
  i = INA260_getPower();
  
  printi("Power: %d\n", i);
  
  while(1)
  {
    pause(500);
    i = INA260_getCurrent();
    printi("Current: %d ma ", i);
    i = INA260_getVoltage();
    printi("Voltage: %d mv\n", i);
  }  
}
