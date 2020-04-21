#include "CommandReceiver.h"

CommandReceiver::CommandReceiver(/* args */)
{
}

CommandReceiver::~CommandReceiver()
{
}

void CommandReceiver::receiveCommand(const quadnake_msgs::RemoteDrive &msg)
{
    remoteMsg = msg;
}
void CommandReceiver::receiveCommand(const quadnake_msgs::LegsDrive &msg)
{
    legMsg = msg;
}

quadnake_msgs::RemoteDrive CommandReceiver::getRemoteMsg(void)
{
    return remoteMsg;
}
quadnake_msgs::LegsDrive CommandReceiver::getDriveMsg(void)
{
    return legMsg;
}