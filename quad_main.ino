#include "quadnake.h"
#define __DEBUG_MSG

void setup()
{
    pinMode(13, OUTPUT); //Arduino LED.
    pinMode(22, OUTPUT); //LED USR 1.

    Serial4.begin(57600);

    nh.initNode();
    nh.getHardware()->setBaud(115200);

    nh.advertise(pub_imu);
    nh.advertise(pub_mag);

    nh.subscribe(sub_remote);

    sr.sr_init();
    ld.legInit();
    mg.init();
}

void loop()
{
    uint32_t t_boot = millis();

    if (((t_boot - t_dead[0]) >= 100))
    {
        uint32_t t_excution = sensor_read();

        t_dead[0] = t_boot;
    }

    if ((t_boot - t_dead[1]) >= 100)
    {
        ld.setGoalPos(0xFE, 2048 + msg_remote.SIDE_DRIVE * 10);

        t_dead[1] = t_boot;
    }

    if ((t_boot - t_dead[2] >= 500))
    {
        digitalWrite(13, HIGH - digitalRead(13));

        t_dead[2] = t_boot;
    }
    if ((t_boot - t_dead[3] >= 1000))
    {

        #ifdef __DEBUG_MSG
        char *logmsg;
        sprintf(logmsg, "Remote msg FW value : %d MG Theta value : %d", msg_remote.FORWARD_DRIVE,mg.returnTheta1());
        nh.loginfo(logmsg);
        #endif

        mg.motionPlan(t_boot, msg_remote);

        t_dead[3] = t_boot;
    }

    nh.spinOnce();

    rosSerialLink(nh.connected());
}
void rosSerialLink(bool isConnected)
{
    static bool flag_wait = false;

    if (isConnected)
    {
        if (!flag_wait)
        {
            digitalWrite(22, HIGH);
            delay(10);

            flag_wait = true;
        }
        else
        {
            flag_wait = false;
        }
    }
    else
    {
        digitalWrite(22, LOW);
    }
}

uint32_t sensor_read(void)
{
    uint32_t tick = micros();

    sr.update_imu();

    msg_imu = sr.get_imu();
    msg_imu.header.stamp = nh.now();
    msg_imu.header.frame_id = "opencr_imu";

    pub_imu.publish(&msg_imu);

    msg_mag = sr.get_mag();
    msg_mag.header.stamp = nh.now();
    msg_mag.header.frame_id = "opencr_mag";

    pub_mag.publish(&msg_mag);

    return (micros() - tick);
}

void remoteCallback(const quadnake_msgs::RemoteDrive &msg)
{
    #ifdef __DEBUG_MSG
    // char* dmsg;
    // dmsg = "remoteCallback...";
    // nh.loginfo(dmsg);
    #endif

    cr.receiveCommand(msg);
    msg_remote = cr.getRemoteMsg();
}

void legsDriveCallback(const quadnake_msgs::LegsDrive &msg)
{
    cr.receiveCommand(msg);
    msg_legs = cr.getDriveMsg();
}
