#ifndef _ROS_quadnake_msgs_Feed_h
#define _ROS_quadnake_msgs_Feed_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "quadnake_msgs/DriveFeed.h"

namespace quadnake_msgs
{

  class Feed : public ros::Msg
  {
    public:
      quadnake_msgs::DriveFeed legs[4];

    Feed():
      legs()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      offset += this->legs[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      offset += this->legs[i].deserialize(inbuffer + offset);
      }
     return offset;
    }

    const char * getType(){ return "quadnake_msgs/Feed"; };
    const char * getMD5(){ return "a012bbbf3b5d9bbbf3bf2240e7ab623c"; };

  };

}
#endif
