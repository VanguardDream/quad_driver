#ifndef __COMMAND_RECEIVER
#define __COMMAND_RECEIVER

#include <quadnake_msgs/RemoteDrive.h>
#include <quadnake_msgs/LegsDrive.h>
#include <std_msgs/String.h>

class CommandReceiver
{
private:
    /* data */
    quadnake_msgs::RemoteDrive remoteMsg;
    quadnake_msgs::LegsDrive legMsg;

public:
    CommandReceiver(/* args */);
    ~CommandReceiver();

    void receiveCommand(const quadnake_msgs::RemoteDrive &msg);
    void receiveCommand(const quadnake_msgs::LegsDrive &msg);

    quadnake_msgs::RemoteDrive getRemoteMsg(void);
    quadnake_msgs::LegsDrive getDriveMsg(void);
};

#endif //__COMMAND_RECEIVER