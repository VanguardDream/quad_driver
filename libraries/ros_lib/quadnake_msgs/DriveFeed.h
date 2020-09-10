#ifndef _ROS_quadnake_msgs_DriveFeed_h
#define _ROS_quadnake_msgs_DriveFeed_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "quadnake_msgs/MotorFeed.h"

namespace quadnake_msgs
{

  class DriveFeed : public ros::Msg
  {
    public:
      typedef std_msgs::Header _DRIVE_FEED_HEAD_type;
      _DRIVE_FEED_HEAD_type DRIVE_FEED_HEAD;
      typedef uint8_t _MODE_type;
      _MODE_type MODE;
      typedef uint8_t _TROUGHS_type;
      _TROUGHS_type TROUGHS;
      typedef float _CONTACT_POSITION_type;
      _CONTACT_POSITION_type CONTACT_POSITION;
      typedef float _VELOCITY_type;
      _VELOCITY_type VELOCITY;
      typedef float _AMPLITUDE_type;
      _AMPLITUDE_type AMPLITUDE;
      typedef float _DUTY_type;
      _DUTY_type DUTY;
      quadnake_msgs::MotorFeed MOTORS[8];

    DriveFeed():
      DRIVE_FEED_HEAD(),
      MODE(0),
      TROUGHS(0),
      CONTACT_POSITION(0),
      VELOCITY(0),
      AMPLITUDE(0),
      DUTY(0),
      MOTORS()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->DRIVE_FEED_HEAD.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->MODE >> (8 * 0)) & 0xFF;
      offset += sizeof(this->MODE);
      *(outbuffer + offset + 0) = (this->TROUGHS >> (8 * 0)) & 0xFF;
      offset += sizeof(this->TROUGHS);
      offset += serializeAvrFloat64(outbuffer + offset, this->CONTACT_POSITION);
      offset += serializeAvrFloat64(outbuffer + offset, this->VELOCITY);
      offset += serializeAvrFloat64(outbuffer + offset, this->AMPLITUDE);
      offset += serializeAvrFloat64(outbuffer + offset, this->DUTY);
      for( uint32_t i = 0; i < 8; i++){
      offset += this->MOTORS[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->DRIVE_FEED_HEAD.deserialize(inbuffer + offset);
      this->MODE =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->MODE);
      this->TROUGHS =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->TROUGHS);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->CONTACT_POSITION));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->VELOCITY));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->AMPLITUDE));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->DUTY));
      for( uint32_t i = 0; i < 8; i++){
      offset += this->MOTORS[i].deserialize(inbuffer + offset);
      }
     return offset;
    }

    const char * getType(){ return "quadnake_msgs/DriveFeed"; };
    const char * getMD5(){ return "d8afcb08e75fceecfaa7c979d4ddd228"; };

  };

}
#endif
