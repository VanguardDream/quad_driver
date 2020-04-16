#ifndef _ROS_quadnake_msgs_DriveFeed_h
#define _ROS_quadnake_msgs_DriveFeed_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace quadnake_msgs
{

  class DriveFeed : public ros::Msg
  {
    public:
      typedef uint8_t _MODE_type;
      _MODE_type MODE;
      typedef uint8_t _TROUGHS_type;
      _TROUGHS_type TROUGHS;
      typedef float _POSITION_type;
      _POSITION_type POSITION;
      typedef float _VELOCITY_type;
      _VELOCITY_type VELOCITY;
      typedef float _AMPLITUDE_type;
      _AMPLITUDE_type AMPLITUDE;
      typedef float _DUTY_type;
      _DUTY_type DUTY;
      typedef bool _isFault_type;
      _isFault_type isFault;
      typedef uint8_t _error_code_type;
      _error_code_type error_code;

    DriveFeed():
      MODE(0),
      TROUGHS(0),
      POSITION(0),
      VELOCITY(0),
      AMPLITUDE(0),
      DUTY(0),
      isFault(0),
      error_code(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->MODE >> (8 * 0)) & 0xFF;
      offset += sizeof(this->MODE);
      *(outbuffer + offset + 0) = (this->TROUGHS >> (8 * 0)) & 0xFF;
      offset += sizeof(this->TROUGHS);
      offset += serializeAvrFloat64(outbuffer + offset, this->POSITION);
      offset += serializeAvrFloat64(outbuffer + offset, this->VELOCITY);
      offset += serializeAvrFloat64(outbuffer + offset, this->AMPLITUDE);
      offset += serializeAvrFloat64(outbuffer + offset, this->DUTY);
      union {
        bool real;
        uint8_t base;
      } u_isFault;
      u_isFault.real = this->isFault;
      *(outbuffer + offset + 0) = (u_isFault.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->isFault);
      *(outbuffer + offset + 0) = (this->error_code >> (8 * 0)) & 0xFF;
      offset += sizeof(this->error_code);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->MODE =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->MODE);
      this->TROUGHS =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->TROUGHS);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->POSITION));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->VELOCITY));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->AMPLITUDE));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->DUTY));
      union {
        bool real;
        uint8_t base;
      } u_isFault;
      u_isFault.base = 0;
      u_isFault.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->isFault = u_isFault.real;
      offset += sizeof(this->isFault);
      this->error_code =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->error_code);
     return offset;
    }

    const char * getType(){ return "quadnake_msgs/DriveFeed"; };
    const char * getMD5(){ return "2c60e965d2a7fbfb0f75ae96a9e86c5c"; };

  };

}
#endif