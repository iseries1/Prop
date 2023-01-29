/**
 * @file mavlink.h
 * @brief Decode Mavlink Messages
 * @author Michael Burmeister
 * @date June 7, 2016
 * @version 1.0
 * 
*/

typedef struct  _MavData
{
  int System;
  int Component;
  int Type;
  int Armed;
  int Custom;
  int Mode;
  int BatteryRemaining;
  int BatteryVoltage;
  int Latitude;
  int Longitude;
  int Altitude;
  int Satelites;
  int HDOP;
  int GPSFix;
  int Heading;
  int RelativeAltitude;
  int Throttle;
  int Pitch;
  int Roll;
  int Yaw;
  int WapPoint;
  int Channel9;
  int Mission;
  int Seq;
  int Time;
  int Pressure;
  int Power;
  int Cmd;
  int Cresults;
  int Txbuf;
  }  mavdata_t;


int MavDecode(mavdata_t *, mavlink_message_t *);

void request_mavlink_rates();

