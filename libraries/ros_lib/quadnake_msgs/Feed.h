#ifndef _ROS_quadnake_msgs_Feed_h
#define _ROS_quadnake_msgs_Feed_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "quadnake_msgs/DriveFeed.h"

namespace quadnake_msgs
{

  class Feed : public ros::Msg
  {
    public:
      typedef std_msgs::Header _Header_type;
      _Header_type Header;
      quadnake_msgs::DriveFeed legs[4];

    Feed():
      Header(),
      legs()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->Header.serialize(outbuffer + offset);
      for( uint32_t i = 0; i < 4; i++){
      offset += this->legs[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->Header.deserialize(inbuffer + offset);
      for( uint32_t i = 0; i < 4; i++){
      offset += this->legs[i].deserialize(inbuffer + offset);
      }
     return offset;
    }

    const char * getType(){ return "quadnake_msgs/Feed"; };
    const char * getMD5(){ return "c67f89c0a115c5b4c5396e60b4b60ad2"; };

  };

}
#endif
