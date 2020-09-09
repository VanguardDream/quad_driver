#ifndef _ROS_quadnake_msgs_MotorFeed_h
#define _ROS_quadnake_msgs_MotorFeed_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace quadnake_msgs
{

  class MotorFeed : public ros::Msg
  {
    public:
      typedef uint8_t _ID_type;
      _ID_type ID;
      typedef int16_t _CURRENT_type;
      _CURRENT_type CURRENT;
      typedef int32_t _POSITION_type;
      _POSITION_type POSITION;
      typedef bool _isFault_type;
      _isFault_type isFault;
      typedef uint8_t _error_code_type;
      _error_code_type error_code;

    MotorFeed():
      ID(0),
      CURRENT(0),
      POSITION(0),
      isFault(0),
      error_code(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->ID >> (8 * 0)) & 0xFF;
      offset += sizeof(this->ID);
      union {
        int16_t real;
        uint16_t base;
      } u_CURRENT;
      u_CURRENT.real = this->CURRENT;
      *(outbuffer + offset + 0) = (u_CURRENT.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_CURRENT.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->CURRENT);
      union {
        int32_t real;
        uint32_t base;
      } u_POSITION;
      u_POSITION.real = this->POSITION;
      *(outbuffer + offset + 0) = (u_POSITION.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_POSITION.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_POSITION.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_POSITION.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->POSITION);
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
      this->ID =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->ID);
      union {
        int16_t real;
        uint16_t base;
      } u_CURRENT;
      u_CURRENT.base = 0;
      u_CURRENT.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_CURRENT.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->CURRENT = u_CURRENT.real;
      offset += sizeof(this->CURRENT);
      union {
        int32_t real;
        uint32_t base;
      } u_POSITION;
      u_POSITION.base = 0;
      u_POSITION.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_POSITION.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_POSITION.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_POSITION.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->POSITION = u_POSITION.real;
      offset += sizeof(this->POSITION);
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

    const char * getType(){ return "quadnake_msgs/MotorFeed"; };
    const char * getMD5(){ return "62b35166123fe9853fe829e5111311da"; };

  };

}
#endif
