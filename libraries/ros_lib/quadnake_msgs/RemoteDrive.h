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
      typedef int8_t _roll_type;
      _roll_type roll;
      typedef int8_t _yaw_type;
      _yaw_type yaw;
      typedef int8_t _pitch_type;
      _pitch_type pitch;

    RemoteDrive():
      MODE(0),
      FORWARD_DRIVE(0),
      SIDE_DRIVE(0),
      ANGULAR_DRIVE(0),
      roll(0),
      yaw(0),
      pitch(0)
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

    const char * getType(){ return "quadnake_msgs/RemoteDrive"; };
    const char * getMD5(){ return "71cbea9129b2b3b46e69fe73e3e13e07"; };

  };

}
#endif
