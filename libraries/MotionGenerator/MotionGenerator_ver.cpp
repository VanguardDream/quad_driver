#include "MotionGenerator_ver.h"

/*Private Funcs*/
void MotionGenerator::setLegsFromMsg(const quadnake_msgs::RemoteDrive &msg)
{

    for (int iter = 0; iter < 4; iter++)
    {
        qd_legs[iter].leg_amplitude = 3;
        qd_legs[iter].leg_troughs = 1;
        //qd_legs[iter].leg_velocity = msg.FORWARD_DRIVE + (pow(-1.0,iter)) * msg.ANGULAR_DRIVE;
        qd_legs[iter].leg_velocity = msg.FORWARD_DRIVE;
    }
}
uint32_t MotionGenerator::calTimeDiff(uint32_t t_comming)
{
    uint32_t t_tmp = MotionGenerator::internal_ticks;
    MotionGenerator::internal_ticks = t_comming;

    return (t_comming - t_tmp);
}

void MotionGenerator::setLegPosFromTimeDiff(uint32_t t_diff)
{
    int32_t posDigit[4];

    for (int iter = 0; iter < 4; iter++)
    {
        //posDigit[iter] = qd_legs[iter].leg_position + (qd_legs[iter].leg_velocity * t_diff);
        posDigit[iter] = qd_legs[iter].leg_position + (qd_legs[iter].leg_velocity * 40);
        posDigit[iter] = (uint32_t)posDigit[iter] % (uint32_t)(pow(2.0, 16.0));

        qd_legs[iter].leg_position = posDigit[iter];
        qd_legs[iter].leg_duty = qd_legs[iter].leg_position * 100.0 / (pow(2.0, 16.0));
    }
}
void MotionGenerator::setThetaFromPos(void)
{
    for (int iter = 0; iter < 4; iter++)
    {
        int gaitRes = 5958;

        if(iter == 0)
        {
            int32_t now_pos = qd_legs[iter].leg_position;
            //ratio :  {13107, 28180, 43254, 59630, 65536}
            if (now_pos < 3000) //phase 0
            {
                qd_legs[iter].v_theta[0] = 0.0f;
                qd_legs[iter].v_theta[1] = 0.0f;
                qd_legs[iter].v_theta[2] = 0.0f;
                qd_legs[iter].v_theta[3] = 0.0f;
                qd_legs[iter].v_theta[4] = 0.0f;
                qd_legs[iter].v_theta[5] = 0.0f;
                qd_legs[iter].v_theta[6] = 0.0f;
            }
            else if (now_pos < 3000 + gaitRes) //phase 1
            {
                qd_legs[iter].v_theta[0] = 0.0f;
                qd_legs[iter].v_theta[1] = 0.0f;
                qd_legs[iter].v_theta[2] = 0.0f;
                qd_legs[iter].v_theta[3] = 0.0f;
                qd_legs[iter].v_theta[4] = 0.0f;
                qd_legs[iter].v_theta[5] = 0.0f;
                qd_legs[iter].v_theta[6] = 0.0f + 0.010071f * (now_pos - 3000);
            }
            else if (now_pos < 3000 + 2 * gaitRes) //phase 2
            {
                qd_legs[iter].v_theta[0] = 0.0f;
                qd_legs[iter].v_theta[1] = 0.0f;
                qd_legs[iter].v_theta[2] = 0.0f;
                qd_legs[iter].v_theta[3] = 0.0f;
                qd_legs[iter].v_theta[4] = 0.0f;
                qd_legs[iter].v_theta[5] = 0.0f + 0.010071f * (now_pos - (3000 + gaitRes));
                qd_legs[iter].v_theta[6] = 60.0f - 0.025177f * (now_pos - (3000 + gaitRes));
            }
            else if (now_pos < 3000 + 3 * gaitRes) //phase 3
            {
                qd_legs[iter].v_theta[0] = 0.0f;
                qd_legs[iter].v_theta[1] = 0.0f;
                qd_legs[iter].v_theta[2] = 0.0f;
                qd_legs[iter].v_theta[3] = 0.0f;
                qd_legs[iter].v_theta[4] = 0.0f + 0.010071f * (now_pos - (3000 + 2 * gaitRes));
                qd_legs[iter].v_theta[5] = 60.0f - 0.025177f * (now_pos - (3000 + 2 * gaitRes));
                qd_legs[iter].v_theta[6] = -90.0f + 0.020142f * (now_pos - (3000 + 2 * gaitRes));
            }
            else if (now_pos < 3000 + 4 * gaitRes) //phase 4
            {
                qd_legs[iter].v_theta[0] = 0.0f;
                qd_legs[iter].v_theta[1] = 0.0f;
                qd_legs[iter].v_theta[2] = 0.0f;
                qd_legs[iter].v_theta[3] = 0.0f + 0.010071f * (now_pos - (3000 + 3 * gaitRes));
                qd_legs[iter].v_theta[4] = 60.0f - 0.025177f * (now_pos - (3000 + 3 * gaitRes));
                qd_legs[iter].v_theta[5] = -90.0f + 0.020142f * (now_pos - (3000 + 3 * gaitRes));
                qd_legs[iter].v_theta[6] = 30.0f - 0.005035f * (now_pos - (3000 + 3 * gaitRes));
            }
            else if (now_pos < 3000 + 5 * gaitRes) //phase 5
            {
                qd_legs[iter].v_theta[0] = 0.0f;
                qd_legs[iter].v_theta[1] = 0.0f;
                qd_legs[iter].v_theta[2] = 0.0f + 0.010071f * (now_pos - (3000 + 4 * gaitRes));
                qd_legs[iter].v_theta[3] = 60.0f - 0.025177f * (now_pos - (3000 + 4 * gaitRes));
                qd_legs[iter].v_theta[4] = -90.0f + 0.020142f * (now_pos - (3000 + 4 * gaitRes));
                qd_legs[iter].v_theta[5] = 30.0f - 0.005035f * (now_pos - (3000 + 4 * gaitRes));
                qd_legs[iter].v_theta[6] = 0.0f;
            }
            else if (now_pos < 3000 + 6 * gaitRes) //phase 6
            {
                qd_legs[iter].v_theta[0] = 0.0f;
                qd_legs[iter].v_theta[1] = 0.0f + 0.010071f * (now_pos - (3000 + 5 * gaitRes));
                qd_legs[iter].v_theta[2] = 60.0f - 0.025177f * (now_pos - (3000 + 5 * gaitRes));
                qd_legs[iter].v_theta[3] = -90.0f + 0.020142f * (now_pos - (3000 + 5 * gaitRes));
                qd_legs[iter].v_theta[4] = 30.0f - 0.005035f * (now_pos - (3000 + 5 * gaitRes));
                qd_legs[iter].v_theta[5] = 0.0f;
                qd_legs[iter].v_theta[6] = 0.0f;
            }
            else if (now_pos < 3000 + 7 * gaitRes) //phase 7
            {
                qd_legs[iter].v_theta[0] = 0.0f + 0.010071f * (now_pos - (3000 + 6 * gaitRes));
                qd_legs[iter].v_theta[1] = 60.0f - 0.025177f * (now_pos - (3000 + 6 * gaitRes));
                qd_legs[iter].v_theta[2] = -90.0f + 0.020142f * (now_pos - (3000 + 6 * gaitRes));
                qd_legs[iter].v_theta[3] = 30.0f - 0.005035f * (now_pos - (3000 + 6 * gaitRes));
                qd_legs[iter].v_theta[4] = 0.0f;
                qd_legs[iter].v_theta[5] = 0.0f;
                qd_legs[iter].v_theta[6] = 0.0f;
            }
            else if (now_pos < 3000 + 8 * gaitRes) //phase 8
            {
                qd_legs[iter].v_theta[0] = 60.0f - 0.011750f * (now_pos - (3000 + 7 * gaitRes));
                qd_legs[iter].v_theta[1] = -90.0f + 0.015106f * (now_pos - (3000 + 7 * gaitRes));
                qd_legs[iter].v_theta[2] = 30.0f - 0.005035f * (now_pos - (3000 + 7 * gaitRes));
                qd_legs[iter].v_theta[3] = 0.0f;
                qd_legs[iter].v_theta[4] = 0.0f;
                qd_legs[iter].v_theta[5] = 0.0f;
                qd_legs[iter].v_theta[6] = 0.0f;
            }
            else if (now_pos < 3000 + 9 * gaitRes) //phase 9
            {
                qd_legs[iter].v_theta[0] = -10.0f + 0.001679f * (now_pos - (3000 + 8 * gaitRes));
                qd_legs[iter].v_theta[1] = 0.0f;
                qd_legs[iter].v_theta[2] = 0.0f;
                qd_legs[iter].v_theta[3] = 0.0f;
                qd_legs[iter].v_theta[4] = 0.0f;
                qd_legs[iter].v_theta[5] = 0.0f;
                qd_legs[iter].v_theta[6] = 0.0f;
            }
            else //phase 10
            {
                qd_legs[iter].v_theta[0] = 0.0f;
                qd_legs[iter].v_theta[1] = 0.0f;
                qd_legs[iter].v_theta[2] = 0.0f;
                qd_legs[iter].v_theta[3] = 0.0f;
                qd_legs[iter].v_theta[4] = 0.0f;
                qd_legs[iter].v_theta[5] = 0.0f;
                qd_legs[iter].v_theta[6] = 0.0f;
            }
        }
        else if(iter == 1)
        {
            int32_t now_pos = qd_legs[iter].leg_position;
            //ratio :  {13107, 28180, 43254, 59630, 65536}
            if (now_pos < 3000) //phase 0
            {
                qd_legs[iter].v_theta[0] = 0.0f;
                qd_legs[iter].v_theta[1] = 0.0f;
                qd_legs[iter].v_theta[2] = 0.0f;
                qd_legs[iter].v_theta[3] = 0.0f;
                qd_legs[iter].v_theta[4] = 0.0f;
                qd_legs[iter].v_theta[5] = 0.0f;
                qd_legs[iter].v_theta[6] = 0.0f;
            }
            else if (now_pos < 3000 + gaitRes) //phase 1
            {
                qd_legs[iter].v_theta[0] = 0.0f;
                qd_legs[iter].v_theta[1] = 0.0f;
                qd_legs[iter].v_theta[2] = 0.0f;
                qd_legs[iter].v_theta[3] = 0.0f;
                qd_legs[iter].v_theta[4] = 0.0f;
                qd_legs[iter].v_theta[5] = 0.0f;
                qd_legs[iter].v_theta[6] = 0.0f - 0.010071f * (now_pos - 3000);
            }
            else if (now_pos < 3000 + 2 * gaitRes) //phase 2
            {
                qd_legs[iter].v_theta[0] = 0.0f;
                qd_legs[iter].v_theta[1] = 0.0f;
                qd_legs[iter].v_theta[2] = 0.0f;
                qd_legs[iter].v_theta[3] = 0.0f;
                qd_legs[iter].v_theta[4] = 0.0f;
                qd_legs[iter].v_theta[5] = 0.0f - 0.010071f * (now_pos - (3000 + gaitRes));
                qd_legs[iter].v_theta[6] = -60.0f + 0.025177f * (now_pos - (3000 + gaitRes));
            }
            else if (now_pos < 3000 + 3 * gaitRes) //phase 3
            {
                qd_legs[iter].v_theta[0] = 0.0f;
                qd_legs[iter].v_theta[1] = 0.0f;
                qd_legs[iter].v_theta[2] = 0.0f;
                qd_legs[iter].v_theta[3] = 0.0f;
                qd_legs[iter].v_theta[4] = 0.0f - 0.010071f * (now_pos - (3000 + 2 * gaitRes));
                qd_legs[iter].v_theta[5] = -60.0f + 0.025177f * (now_pos - (3000 + 2 * gaitRes));
                qd_legs[iter].v_theta[6] = 90.0f - 0.020142f * (now_pos - (3000 + 2 * gaitRes));
            }
            else if (now_pos < 3000 + 4 * gaitRes) //phase 4
            {
                qd_legs[iter].v_theta[0] = 0.0f;
                qd_legs[iter].v_theta[1] = 0.0f;
                qd_legs[iter].v_theta[2] = 0.0f;
                qd_legs[iter].v_theta[3] = 0.0f + 0.010071f * (now_pos - (3000 + 3 * gaitRes));
                qd_legs[iter].v_theta[4] = -60.0f + 0.025177f * (now_pos - (3000 + 3 * gaitRes));
                qd_legs[iter].v_theta[5] = 90.0f - 0.020142f * (now_pos - (3000 + 3 * gaitRes));
                qd_legs[iter].v_theta[6] = -30.0f + 0.005035f * (now_pos - (3000 + 3 * gaitRes));
            }
            else if (now_pos < 3000 + 5 * gaitRes) //phase 5
            {
                qd_legs[iter].v_theta[0] = 0.0f;
                qd_legs[iter].v_theta[1] = 0.0f;
                qd_legs[iter].v_theta[2] = 0.0f - 0.010071f * (now_pos - (3000 + 4 * gaitRes));
                qd_legs[iter].v_theta[3] = -60.0f + 0.025177f * (now_pos - (3000 + 4 * gaitRes));
                qd_legs[iter].v_theta[4] = 90.0f - 0.020142f * (now_pos - (3000 + 4 * gaitRes));
                qd_legs[iter].v_theta[5] = -30.0f + 0.005035f * (now_pos - (3000 + 4 * gaitRes));
                qd_legs[iter].v_theta[6] = 0.0f;
            }
            else if (now_pos < 3000 + 6 * gaitRes) //phase 6
            {
                qd_legs[iter].v_theta[0] = 0.0f;
                qd_legs[iter].v_theta[1] = 0.0f - 0.010071f * (now_pos - (3000 + 5 * gaitRes));
                qd_legs[iter].v_theta[2] = -60.0f + 0.025177f * (now_pos - (3000 + 5 * gaitRes));
                qd_legs[iter].v_theta[3] = 90.0f - 0.020142f * (now_pos - (3000 + 5 * gaitRes));
                qd_legs[iter].v_theta[4] = -30.0f + 0.005035f * (now_pos - (3000 + 5 * gaitRes));
                qd_legs[iter].v_theta[5] = 0.0f;
                qd_legs[iter].v_theta[6] = 0.0f;
            }
            else if (now_pos < 3000 + 7 * gaitRes) //phase 7
            {
                qd_legs[iter].v_theta[0] = 0.0f - 0.010071f * (now_pos - (3000 + 6 * gaitRes));
                qd_legs[iter].v_theta[1] = -60.0f + 0.025177f * (now_pos - (3000 + 6 * gaitRes));
                qd_legs[iter].v_theta[2] = 90.0f - 0.020142f * (now_pos - (3000 + 6 * gaitRes));
                qd_legs[iter].v_theta[3] = -30.0f + 0.005035f * (now_pos - (3000 + 6 * gaitRes));
                qd_legs[iter].v_theta[4] = 0.0f;
                qd_legs[iter].v_theta[5] = 0.0f;
                qd_legs[iter].v_theta[6] = 0.0f;
            }
            else if (now_pos < 3000 + 8 * gaitRes) //phase 8
            {
                qd_legs[iter].v_theta[0] = -60.0f + 0.011750f * (now_pos - (3000 + 7 * gaitRes));
                qd_legs[iter].v_theta[1] = 90.0f - 0.015106f * (now_pos - (3000 + 7 * gaitRes));
                qd_legs[iter].v_theta[2] = -30.0f + 0.005035f * (now_pos - (3000 + 7 * gaitRes));
                qd_legs[iter].v_theta[3] = 0.0f;
                qd_legs[iter].v_theta[4] = 0.0f;
                qd_legs[iter].v_theta[5] = 0.0f;
                qd_legs[iter].v_theta[6] = 0.0f;
            }
            else if (now_pos < 3000 + 9 * gaitRes) //phase 9
            {
                qd_legs[iter].v_theta[0] = 10.0f - 0.001679f * (now_pos - (3000 + 8 * gaitRes));
                qd_legs[iter].v_theta[1] = 0.0f;
                qd_legs[iter].v_theta[2] = 0.0f;
                qd_legs[iter].v_theta[3] = 0.0f;
                qd_legs[iter].v_theta[4] = 0.0f;
                qd_legs[iter].v_theta[5] = 0.0f;
                qd_legs[iter].v_theta[6] = 0.0f;
            }
            else //phase 10
            {
                qd_legs[iter].v_theta[0] = 0.0f;
                qd_legs[iter].v_theta[1] = 0.0f;
                qd_legs[iter].v_theta[2] = 0.0f;
                qd_legs[iter].v_theta[3] = 0.0f;
                qd_legs[iter].v_theta[4] = 0.0f;
                qd_legs[iter].v_theta[5] = 0.0f;
                qd_legs[iter].v_theta[6] = 0.0f;
            }
        }
        else if(iter == 3)
        {
            
        }
        else if(iter == 2)
        {
            
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

    qd_legs = (leg *)malloc(4 * sizeof(leg));

    for (int iter = 0; iter < 4; iter++)
    {
        qd_legs[iter].leg_mode = 0;
        qd_legs[iter].leg_troughs = 1;
        qd_legs[iter].leg_position = 0;
        qd_legs[iter].leg_velocity = 0;
        qd_legs[iter].leg_amplitude = 0.0;
        qd_legs[iter].leg_duty = 0.0;
    }
}

int32_t MotionGenerator::returnTheta1(void)
{
    return qd_legs[0].v_theta[0];
}

uint32_t MotionGenerator::getLegsPos(uint8_t legid)
{
    if (legid < 20)
    {
        return 2048 + (int32_t)(qd_legs[0].v_theta[legid - 12] / 0.088f);
    }
    else if (legid < 30)
    {
        return 2048 + (int32_t)(qd_legs[1].v_theta[legid - 22] / 0.088f);
    }
    else if (legid < 40)
    {
        return 2048 + (int32_t)(qd_legs[2].v_theta[legid - 32] / 0.088f);
    }
    else if (legid < 50)
    {
        return 2048 + (int32_t)(qd_legs[3].v_theta[legid - 42] / 0.088f);
    }
    else
    {
        return 2048;
    }
}
uint16_t MotionGenerator::returnLegDuty(void)
{
    return qd_legs[0].leg_position;
}
