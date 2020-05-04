#include "MotionGenerator.h"

/*Private Funcs*/
void MotionGenerator::setLegsFromMsg(const quadnake_msgs::RemoteDrive &msg)
{

    for (int iter = 0; iter < 4; iter++)
    {
        qd_legs[iter].leg_amplitude = 3;
        qd_legs[iter].leg_troughs = 1;
        qd_legs[iter].leg_velocity = msg.FORWARD_DRIVE + (pow(-1.0,iter)) * msg.ANGULAR_DRIVE;
    }
}
uint32_t MotionGenerator::calTimeDiff(uint32_t t_comming)
{
    uint32_t t_tmp = MotionGenerator::internal_ticks;
    MotionGenerator::internal_ticks = t_comming;

    return t_comming - t_tmp;
}

void MotionGenerator::setLegPosFromTimeDiff(uint32_t t_diff)
{
    int32_t posDigit[4];

    for (int iter = 0; iter < 4; iter++)
    {
        posDigit[iter] = qd_legs[iter].leg_position + (qd_legs[iter].leg_velocity * t_diff);
        posDigit[iter] = (uint32_t)posDigit[iter] % (uint32_t)(pow(2.0,16.0));

        qd_legs[iter].leg_position = posDigit[iter];
        qd_legs[iter].leg_duty = (uint32_t)posDigit[iter] / (uint32_t)(pow(2.0,16.0));
    }
}
void MotionGenerator::setThetaFromPos(void)
{
    for (int iter = 0; iter < 4; iter++)
    {
        uint16_t now_pos = qd_legs[iter].leg_position;

        if (now_pos < qd_legs[iter].v_leg_link_ratio[0])
        {
            qd_legs[iter].v_theta[0] = 17.5f + (-0.003768422860561 * (now_pos - 0));
            qd_legs[iter].v_theta[1] = 0.0f + (0.001104563377274 * (now_pos - 0));
        }
        else if (now_pos < qd_legs[iter].v_leg_link_ratio[1])
        {
            qd_legs[iter].v_theta[0] = -32.0f + (0.00327690031403 * (now_pos - 13107));
            qd_legs[iter].v_theta[1] = 14.5f + (-0.002881479238227 * (now_pos - 13107));
            qd_legs[iter].v_theta[2] = 0.0f + (0.000960493079409 * (now_pos - 13107));
        }
        else if (now_pos < qd_legs[iter].v_leg_link_ratio[2])
        {
            qd_legs[iter].v_theta[0] = 17.5f + (-0.001158126782786 * (now_pos - 28180));
            qd_legs[iter].v_theta[1] = -29.0f + (0.002881288082645 * (now_pos - 28180));
            qd_legs[iter].v_theta[2] = -14.5f + (-0.002805983028323 * (now_pos - 28180));
            qd_legs[iter].v_theta[3] = 0.0f + (0.00088512430656 * (now_pos - 28180));
        }
        else if (now_pos < qd_legs[iter].v_leg_link_ratio[3])
        {
            qd_legs[iter].v_theta[1] = 14.5f + (-0.00088363721838 * (now_pos - 43254));
            qd_legs[iter].v_theta[2] = -28.0f + (0.002581627695859 * (now_pos - 43254));
            qd_legs[iter].v_theta[3] = 13.0f + (-0.003879066481935 * (now_pos - 43254));
            qd_legs[iter].v_theta[4] = 0.0f + (0.002250359963736 * (now_pos - 43254));
        }
        else
        {
            qd_legs[iter].v_theta[0] = 0.0f + (0.002959919146104 * (now_pos - 59638));
            qd_legs[iter].v_theta[2] = 14.5f + (-0.002454647708703 * (now_pos - 59638));
            qd_legs[iter].v_theta[3] = -50.0f + (0.008513438698361 * (now_pos - 59638));
            qd_legs[iter].v_theta[4] = 39.0f + (-0.006251254263453 * (now_pos - 59638));
        }
    }
}

/*Public Funcs*/
void MotionGenerator::motionPlan(uint32_t t_init, const quadnake_msgs::RemoteDrive &msg)
{
    uint32_t t;

    t = calTimeDiff(t_init);

    setLegsFromMsg(msg);
    setLegPosFromTimeDiff(t);
    setThetaFromPos();
}
MotionGenerator::MotionGenerator(/* args */)
{
}

MotionGenerator::~MotionGenerator()
{
    free(qd_legs);
}

void MotionGenerator::init(void)
{
    internal_ticks = 0;

    qd_legs = (leg *) malloc(4*sizeof(leg));

    for(int iter = 0; iter <4 ; iter++)
    {
        qd_legs[iter].leg_mode = 0;
        qd_legs[iter].leg_troughs = 1;
        qd_legs[iter].leg_position = 300;
        qd_legs[iter].leg_velocity = 0;
        qd_legs[iter].leg_amplitude = 0;
        qd_legs[iter].leg_duty = 0;
    }
}

uint16_t MotionGenerator::returnTheta1(void)
{
    return qd_legs[0].leg_duty;
}
