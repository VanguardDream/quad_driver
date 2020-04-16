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
      typedef int8_t _ROLL_type;
      _ROLL_type ROLL;
      typedef int8_t _YAW_type;
      _YAW_type YAW;
      typedef int8_t _PITCH_type;
      _PITCH_type PITCH;

    LegsDrive():
      legs(),
      ROLL(0),
      YAW(0),
      PITCH(0)
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
      } u_ROLL;
      u_ROLL.real = this->ROLL;
      *(outbuffer + offset + 0) = (u_ROLL.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->ROLL);
      union {
        int8_t real;
        uint8_t base;
      } u_YAW;
      u_YAW.real = this->YAW;
      *(outbuffer + offset + 0) = (u_YAW.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->YAW);
      union {
        int8_t real;
        uint8_t base;
      } u_PITCH;
      u_PITCH.real = this->PITCH;
      *(outbuffer + offset + 0) = (u_PITCH.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->PITCH);
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
      } u_ROLL;
      u_ROLL.base = 0;
      u_ROLL.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->ROLL = u_ROLL.real;
      offset += sizeof(this->ROLL);
      union {
        int8_t real;
        uint8_t base;
      } u_YAW;
      u_YAW.base = 0;
      u_YAW.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->YAW = u_YAW.real;
      offset += sizeof(this->YAW);
      union {
        int8_t real;
        uint8_t base;
      } u_PITCH;
      u_PITCH.base = 0;
      u_PITCH.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->PITCH = u_PITCH.real;
      offset += sizeof(this->PITCH);
     return offset;
    }

    const char * getType(){ return "quadnake_msgs/LegsDrive"; };
    const char * getMD5(){ return "9556b0c957d81310a1871634d3392d75"; };

  };

}
#endif
