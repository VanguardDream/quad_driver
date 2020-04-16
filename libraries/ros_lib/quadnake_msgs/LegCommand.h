#ifndef _ROS_quadnake_msgs_LegCommand_h
#define _ROS_quadnake_msgs_LegCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace quadnake_msgs
{

  class LegCommand : public ros::Msg
  {
    public:
      typedef uint8_t _MODE_type;
      _MODE_type MODE;
      typedef uint8_t _TROUGHS_type;
      _TROUGHS_type TROUGHS;
      typedef float _POSTION_type;
      _POSTION_type POSTION;
      typedef float _VELOCITY_type;
      _VELOCITY_type VELOCITY;
      typedef float _AMPLITUDE_type;
      _AMPLITUDE_type AMPLITUDE;
      typedef float _DUTY_type;
      _DUTY_type DUTY;

    LegCommand():
      MODE(0),
      TROUGHS(0),
      POSTION(0),
      VELOCITY(0),
      AMPLITUDE(0),
      DUTY(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->MODE >> (8 * 0)) & 0xFF;
      offset += sizeof(this->MODE);
      *(outbuffer + offset + 0) = (this->TROUGHS >> (8 * 0)) & 0xFF;
      offset += sizeof(this->TROUGHS);
      offset += serializeAvrFloat64(outbuffer + offset, this->POSTION);
      offset += serializeAvrFloat64(outbuffer + offset, this->VELOCITY);
      offset += serializeAvrFloat64(outbuffer + offset, this->AMPLITUDE);
      offset += serializeAvrFloat64(outbuffer + offset, this->DUTY);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->MODE =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->MODE);
      this->TROUGHS =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->TROUGHS);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->POSTION));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->VELOCITY));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->AMPLITUDE));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->DUTY));
     return offset;
    }

    const char * getType(){ return "quadnake_msgs/LegCommand"; };
    const char * getMD5(){ return "06ba8ed352d31f98daaf4079b4bae0b2"; };

  };

}
#endif
