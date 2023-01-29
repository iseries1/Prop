/**
 * @file mavlink.c
 * @brief Decode Mavlink Messages
 * @author Michael Burmeister
 * @date June 7, 2016
 * @version 1.0
 * 
*/

#include "mavlink.h"
#include "fdserial.h"
#include "../Mavlink/common/mavlink.h"        // Mavlink decoder/encoder

mavlink_system_t mavlink_system;

mavlink_message_t *msg;
mavlink_message_t *msg2;
mavlink_message_t *buf;
mavlink_status_t *sts;
mavlink_status_t *sts2;
mavlink_heartbeat_t *Heart;
mavlink_sys_status_t *Status;
mavlink_gps_raw_int_t *GPS;
mavlink_vfr_hud_t *Hud;
mavlink_attitude_t *Att;
mavlink_mission_current_t *Msn;
mavlink_statustext_t *stx;
mavlink_rc_channels_t *chnl;
mavlink_mission_ack_t *msnack;
mavlink_mission_request_t *msnreq;
mavlink_command_int_t *msn;
mavlink_system_time_t *systm;
mavlink_scaled_pressure_t *syspr;
mavlink_power_status_t *syspw;
mavlink_command_ack_t *cmd;
mavlink_radio_status_t *radio;

int MavlinkInit(mavdata_t *m)
{
  m->Md.Custom = 12;
  m->Seq = -1;
  m->Mission = -1;
  m->Cmd = -1;
  mavlink_system.sysid = 66;
  mavlink_system.compid = MAV_COMP_ID_IMU;
}

int MavlinkStart(mavdata_t *M, fdserial *S)
{
  
}
  
int MavDecode(mavdata_t *M, mavlink_message_t *m)
{

  switch (m->msgid)
  {
    case MAVLINK_MSG_ID_HEARTBEAT:
      Heart = (mavlink_heartbeat_t *)m->payload64;
      if (Heart->base_mode & MAV_MODE_FLAG_DECODE_POSITION_SAFETY)
        M->Armed = 1;
      else
        M->Armed = 0;
      if (Heart->base_mode & MAV_MODE_FLAG_DECODE_POSITION_CUSTOM_MODE)
      {
        M->Custom = Heart->custom_mode;
      }
      else
        M->Custom = 0;
      
      M->System = m->sysid;
      M->Component = m->compid;
      M->Type = Heart->type;
      if (Other == 0)
      {
        request_mavlink_rates();
      }      
      return 2;

    case MAVLINK_MSG_ID_SYS_STATUS:
      Status = (mavlink_sys_status_t *)m->payload64;
      M->BatteryRemaining = Status->battery_remaining;
      M->BatteryVoltage = Status->voltage_battery;
      return 2;

    case MAVLINK_MSG_ID_GPS_RAW_INT:
      GPS = (mavlink_gps_raw_int_t *)m->payload64;
      M->Latitude = GPS->lat;
      M->Longitude = GPS->lon;
      M->Altitude = GPS->alt;
      M->Satelites = GPS->satellites_visible;
      M->HDOP = GPS->eph;
      M->GPSFix = GPS->fix_type;
      return 1;

    case MAVLINK_MSG_ID_VFR_HUD:
      Hud = (mavlink_vfr_hud_t *)m->payload64;
      M->Heading = Hud->heading;
      M->RelativeAltitude = Hud->alt;
      M->Throttle = Hud->throttle;
      return 1;

    case MAVLINK_MSG_ID_ATTITUDE:
      Att = (mavlink_attitude_t *)m->payload64;
      M->Roll = Att->roll * 180/PI;
      M->Pitch = Att->pitch * 180/PI;
      M->Yaw = Att->yaw * 180/PI;
      return 1;

    case MAVLINK_MSG_ID_MISSION_CURRENT:
      Msn = (mavlink_mission_current_t *)m->payload64;
      M->WapPoint = Msn->seq;
      return 1;

    case MAVLINK_MSG_ID_RC_CHANNELS:
      chnl = (mavlink_rc_channels_t *)m->payload64;
      M->Channel9 = chnl->chan9_raw;
      return 1;

    case MAVLINK_MSG_ID_MISSION_ACK:
      msnack = (mavlink_mission_ack_t *)m->payload64;
      M->Mission = msnack->type;
      return 1;

    case MAVLINK_MSG_ID_MISSION_REQUEST:
      msnreq = (mavlink_mission_request_t *)m->payload64;
      M->Seq = msnreq->seq;
      return 1;

    case MAVLINK_MSG_ID_SYSTEM_TIME:
      systm = (mavlink_system_time_t *)m->payload64;
      M->Time = systm->time_boot_ms;
      return 1;

    case MAVLINK_MSG_ID_SCALED_PRESSURE:
      syspr = (mavlink_scaled_pressure_t *)m->payload64;
      M->Pressure = syspr->press_abs;
      return 1;

    case MAVLINK_MSG_ID_POWER_STATUS:
      syspw = (mavlink_power_status_t *)m->payload64;
      M->Power = syspw->Vcc;
      return 1;

    case MAVLINK_MSG_ID_COMMAND_ACK:
      cmd = (mavlink_command_ack_t *)m->payload64;
      M->Cmd = cmd->command;
      M->Cresults = cmd->result;
      return 1;

    case MAVLINK_MSG_ID_RC_CHANNELS_RAW:
      return 1;

    case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT:
      return 1;

    case MAVLINK_MSG_ID_RAW_IMU:
      return 1;

    case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
      return 1;

    case MAVLINK_MSG_ID_SCALED_IMU2:
      return 1;

    case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:
      return 1;

    case MAVLINK_MSG_ID_TERRAIN_REPORT:
      return 1;

    case MAVLINK_MSG_ID_RADIO_STATUS:
      radio = (mavlink_radio_status_t *)m->payload64;
      M->Txbuf = radio->txbuf;
      return 1;

    case MAVLINK_MSG_ID_STATUSTEXT:
      stx = (mavlink_statustext_t *)m->payload64;
      memcpy(StsMsg, stx->text, 50);
      StsMsg[50] = 0;
      return 2;

    default:
      NotHandled = m->msgid;
      return 0;
    }
}

void request_mavlink_rates()
{
  int i,j;
  int t;
  
  const int  maxStreams = 8;
  const uint8_t MAVStreams[] = {
        MAV_DATA_STREAM_RAW_SENSORS,
        MAV_DATA_STREAM_RAW_CONTROLLER,
        MAV_DATA_STREAM_EXTENDED_STATUS,
        MAV_DATA_STREAM_RC_CHANNELS,
        MAV_DATA_STREAM_POSITION,
        MAV_DATA_STREAM_EXTRA1, 
        MAV_DATA_STREAM_EXTRA2,
        MAV_DATA_STREAM_EXTRA3};
  const uint16_t MAVRates[] = {0x02, 0x02, 0x02, 0x05, 0x05, 0x02, 0x02, 0x02};
  for (i=0; i < maxStreams; i++)
  {
    t = mavlink_msg_request_data_stream_pack(mavlink_system.sysid, mavlink_system.compid, buf,
          Md.System, Md.Component, MAVStreams[i], MAVRates[i], 1);
    
    SndData(t);
  }
  Other = 1;
}
