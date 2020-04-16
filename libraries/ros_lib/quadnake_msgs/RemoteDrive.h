#ifndef _ROS_quadnake_msgs_RemoteDrive_h
#define _ROS_quadnake_msgs_RemoteDrive_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace quadnake_msgs
{

  class RemoteDrive : public ros::Msg
  {
    public:
      typedef uint8_t _MODE_type;
      _MODE_type MODE;
      typedef int8_t _FORWARD_DRIVE_type;
      _FORWARD_DRIVE_type FORWARD_DRIVE;
      typedef int8_t _SIDE_DRIVE_type;
      _SIDE_DRIVE_type SIDE_DRIVE;
      typedef int8_t _ANGULAR_DRIVE_type;
      _ANGULAR_DRIVE_type ANGULAR_DRIVE;
      typedef int8_t _ROLL_type;
      _ROLL_type ROLL;
      typedef int8_t _YAW_type;
      _YAW_type YAW;
      typedef int8_t _PITCH_type;
      _PITCH_type PITCH;

    RemoteDrive():
      MODE(0),
      FORWARD_DRIVE(0),
      SIDE_DRIVE(0),
      ANGULAR_DRIVE(0),
      ROLL(0),
      YAW(0),
      PITCH(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->MODE >> (8 * 0)) & 0xFF;
      offset += sizeof(this->MODE);
      union {
        int8_t real;
        uint8_t base;
      } u_FORWARD_DRIVE;
      u_FORWARD_DRIVE.real = this->FORWARD_DRIVE;
      *(outbuffer + offset + 0) = (u_FORWARD_DRIVE.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->FORWARD_DRIVE);
      union {
        int8_t real;
        uint8_t base;
      } u_SIDE_DRIVE;
      u_SIDE_DRIVE.real = this->SIDE_DRIVE;
      *(outbuffer + offset + 0) = (u_SIDE_DRIVE.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->SIDE_DRIVE);
      union {
        int8_t real;
        uint8_t base;
      } u_ANGULAR_DRIVE;
      u_ANGULAR_DRIVE.real = this->ANGULAR_DRIVE;
      *(outbuffer + offset + 0) = (u_ANGULAR_DRIVE.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->ANGULAR_DRIVE);
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
      this->MODE =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->MODE);
      union {
        int8_t real;
        uint8_t base;
      } u_FORWARD_DRIVE;
      u_FORWARD_DRIVE.base = 0;
      u_FORWARD_DRIVE.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->FORWARD_DRIVE = u_FORWARD_DRIVE.real;
      offset += sizeof(this->FORWARD_DRIVE);
      union {
        int8_t real;
        uint8_t base;
      } u_SIDE_DRIVE;
      u_SIDE_DRIVE.base = 0;
      u_SIDE_DRIVE.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->SIDE_DRIVE = u_SIDE_DRIVE.real;
      offset += sizeof(this->SIDE_DRIVE);
      union {
        int8_t real;
        uint8_t base;
      } u_ANGULAR_DRIVE;
      u_ANGULAR_DRIVE.base = 0;
      u_ANGULAR_DRIVE.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->ANGULAR_DRIVE = u_ANGULAR_DRIVE.real;
      offset += sizeof(this->ANGULAR_DRIVE);
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

    const char * getType(){ return "quadnake_msgs/RemoteDrive"; };
    const char * getMD5(){ return "5e737f874edc3bdccfa477b32fe176b4"; };

  };

}
#endif
