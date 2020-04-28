#include "MotionGenerator.h"

MotionGenerator::MotionGenerator(/* args */)
{
}

MotionGenerator::~MotionGenerator()
{
}

MotionGenerator::leg *MotionGenerator::getMsg(const quadnake_msgs::RemoteDrive &msg)
{
    leg tmp_leg[4];

    for (int iter = 0; iter < 4; iter++)
    {
        tmp_leg[iter].leg_amplitude = 3;
        tmp_leg[iter].leg_troughs = 1;
        tmp_leg[iter].leg_velocity = msg.FORWARD_DRIVE + ((-1) ^ iter) * msg.ANGULAR_DRIVE;
    }

    return tmp_leg;
}