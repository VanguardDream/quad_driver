#include "quadnake.h"
//#define __DEBUG_MSG
#define __DEBUG_EXET

void setup()
{
    pinMode(13, OUTPUT); //Arduino LED.
    pinMode(22, OUTPUT); //LED USR 1.

    Serial4.begin(1000000);

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

#ifdef __DEBUG_EXET
        uint32_t tick = micros();
#endif

        uint32_t t_excution = sensor_read();

        t_dead[0] = t_boot;

#ifdef __DEBUG_EXET
        char *processtime;
        sprintf(processtime, "Sensor Reading Time : %d", micros() - tick);
        nh.loginfo(processtime);
#endif
    }

    if ((t_boot - t_dead[1]) >= 50)
    {
#ifdef __DEBUG_EXET
        uint32_t tick = micros();
#endif

        //ld.setGoalPos(0xFE, 2048 + msg_remote.SIDE_DRIVE * 10);
        legDrive();
        t_dead[1] = t_boot;

#ifdef __DEBUG_EXET
        char *processtime;
        sprintf(processtime, "motor Commanding Time : %d", micros() - tick);
        nh.loginfo(processtime);
#endif
    }

    if ((t_boot - t_dead[2] >= 500))
    {
        digitalWrite(13, HIGH - digitalRead(13));

        t_dead[2] = t_boot;
    }
    if ((t_boot - t_dead[3] >= 50))
    {
        //uint32_t tick = micros();

#ifdef __DEBUG_MSG
        char *logmsg;
        //sprintf(logmsg, "Remote msg FW value : %d MG Theta value : %d", msg_remote.FORWARD_DRIVE, mg.returnTheta1());
        sprintf(logmsg, "Theta : %d : %d", mg.returnTheta1(), mg.returnLegDuty());
        nh.loginfo(logmsg);
#endif

#ifdef __DEBUG_EXET
        uint32_t tick = micros();
#endif


        mg.motionPlan(t_boot, msg_remote);

        t_dead[3] = t_boot;

#ifdef __DEBUG_EXET
        char *processtime;
        sprintf(processtime, "motionPlan Processing Time : %d", micros() - tick);
        nh.loginfo(processtime);
#endif

#ifdef __DEBUG_MSG
        char *processtime;
        sprintf(processtime, "motionPlan Processing Time : %d", micros() - tick);
        //nh.loginfo(processtime);
#endif
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
#ifdef __DEBUG_EXET
        uint32_t tick = micros();
#endif

    cr.receiveCommand(msg);
    msg_remote = cr.getRemoteMsg();

#ifdef __DEBUG_EXET
        char *processtime;
        sprintf(processtime, "Control input Reading Time : %d", micros() - tick);
        nh.loginfo(processtime);
#endif
}

void legsDriveCallback(const quadnake_msgs::LegsDrive &msg)
{
    cr.receiveCommand(msg);
    msg_legs = cr.getDriveMsg();
}

void legDrive(void)
{
    // ld.setGoalPos(11, mg.getLegsPos(11));
    // ld.setGoalPos(12, 2048);
    // ld.setGoalPos(13, mg.getLegsPos(12));
    // ld.setGoalPos(14, 2048);
    // ld.setGoalPos(15, mg.getLegsPos(13));
    // ld.setGoalPos(16, 2048);
    // ld.setGoalPos(17, mg.getLegsPos(14));
    // ld.setGoalPos(18, mg.getLegsPos(15)); 
    
    for(int iter = 1; iter < 3 ; iter++)
    {
        ld.setGoalPos(QUAD_LEG_ID(iter,1),mg.getLegsPos(QUAD_LEG_ID(iter,1)));
        ld.setGoalPos(QUAD_LEG_ID(iter,3),mg.getLegsPos(QUAD_LEG_ID(iter,2)));
        ld.setGoalPos(QUAD_LEG_ID(iter,5),mg.getLegsPos(QUAD_LEG_ID(iter,3)));
        ld.setGoalPos(QUAD_LEG_ID(iter,7),mg.getLegsPos(QUAD_LEG_ID(iter,4)));   
        ld.setGoalPos(QUAD_LEG_ID(iter,8),mg.getLegsPos(QUAD_LEG_ID(iter,5)));   
    }
}
