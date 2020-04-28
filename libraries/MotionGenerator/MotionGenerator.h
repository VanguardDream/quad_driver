#include <quadnake_msgs/RemoteDrive.h>

class MotionGenerator
{
private:
    /* data */
    static uint16_t internal_clock;
    static quadnake_msgs::RemoteDrive remote_msg;

    struct leg
    {
        uint8_t leg_mode;
        uint8_t leg_troughs;

        double leg_amplitude;
        double leg_position;
        double leg_velocity;
        double leg_duty;

        leg() : leg_mode(0),
                leg_troughs(1), leg_position(0), leg_velocity(0), leg_amplitude(0), leg_duty(0) {}

    } static qd_legs[4];

    void clockAdder(uint16_t add);

public:
    MotionGenerator(/* args */);
    ~MotionGenerator();

    leg *getMsg(const quadnake_msgs::RemoteDrive &msg);
};
