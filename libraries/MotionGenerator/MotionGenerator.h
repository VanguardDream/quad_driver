#include <quadnake_msgs/RemoteDrive.h>
#include <math.h>

class MotionGenerator
{
private:
    /* data */
    static uint32_t internal_ticks;

    struct leg
    {
        uint8_t leg_mode;
        uint8_t leg_troughs;

        uint16_t leg_position;
        int16_t leg_velocity;

        double leg_amplitude;
        double leg_duty;

        const uint16_t v_leg_link_length[5] = {10, 12, 12, 13, 5};
        const uint16_t v_leg_link_ratio[5] = {13107, 28180, 43254, 59630, 65536};

        uint16_t v_leg_total_length;

        double v_theta[6];
        double h_theta[3];
    };
    //static qd_legs[4];

    struct leg *qd_legs;

    uint16_t controller_clock = 0;

    void clockAdder(uint16_t add);
    void setLegsFromMsg(const quadnake_msgs::RemoteDrive &msg);
    uint32_t calTimeDiff(uint32_t t_comming);
    void setLegPosFromTimeDiff(uint32_t t_diff);
    void setThetaFromPos(void);

public:
    MotionGenerator(/* args */);
    ~MotionGenerator();
    void motionPlan(uint32_t t_init, const quadnake_msgs::RemoteDrive &msg);
    void init(void);
    int32_t returnTheta1(void);
    uint16_t returnLegDuty(void);
    uint32_t getLegsPos(uint8_t legid);
};
