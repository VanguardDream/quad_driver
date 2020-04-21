#ifndef _ROS_quadnake_msgs_LegsDrive_h
#define _ROS_quadnake_msgs_LegsDrive_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "quadnake_msgs/LegCommand.h"

namespace quadnake_msgs
{

  class LegsDrive : public ros::Msg
  {
    public:
      quadnake_msgs::LegCommand legs[4];
      typedef int8_t _roll_type;
      _roll_type roll;
      typedef int8_t _yaw_type;
      _yaw_type yaw;
      typedef int8_t _pitch_type;
      _pitch_type pitch;

    LegsDrive():
      legs(),
      roll(0),
      yaw(0),
      pitch(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      offset += this->legs[i].serialize(outbuffer + offset);
      }
      union {
        int8_t real;
        uint8_t base;
      } u_roll;
      u_roll.real = this->roll;
      *(outbuffer + offset + 0) = (u_roll.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->roll);
      union {
        int8_t real;
        uint8_t base;
      } u_yaw;
      u_yaw.real = this->yaw;
      *(outbuffer + offset + 0) = (u_yaw.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->yaw);
      union {
        int8_t real;
        uint8_t base;
      } u_pitch;
      u_pitch.real = this->pitch;
      *(outbuffer + offset + 0) = (u_pitch.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pitch);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      offset += this->legs[i].deserialize(inbuffer + offset);
      }
      union {
        int8_t real;
        uint8_t base;
      } u_roll;
      u_roll.base = 0;
      u_roll.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->roll = u_roll.real;
      offset += sizeof(this->roll);
      union {
        int8_t real;
        uint8_t base;
      } u_yaw;
      u_yaw.base = 0;
      u_yaw.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->yaw = u_yaw.real;
      offset += sizeof(this->yaw);
      union {
        int8_t real;
        uint8_t base;
      } u_pitch;
      u_pitch.base = 0;
      u_pitch.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->pitch = u_pitch.real;
      offset += sizeof(this->pitch);
     return offset;
    }

    const char * getType(){ return "quadnake_msgs/LegsDrive"; };
    const char * getMD5(){ return "4d958b491cbb2c0ebde8bf0d0c69af3c"; };

  };

}
#endif
