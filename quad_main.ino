#include "quadnake.h"

void setup()
{
    pinMode(13, OUTPUT);

    Serial4.begin(57600);

    nh.initNode();
    nh.getHardware()->setBaud(115200);

    nh.advertise(pub_imu);
    nh.advertise(pub_mag);

    nh.subscribe(sub_remote);

    sr.sr_init();
}

void loop()
{
    uint32_t t_boot = millis();

    if (((t_boot - t_dead[0]) >= 100))
    {
        uint32_t t_excution = sensor_read();

        t_dead[0] = t_boot;
    }

    nh.spinOnce();
}
void rosSerialLink(bool isConnected)
{
    static bool flag_wait = false;

    if (isConnected)
    {
        if (!flag_wait)
        {
            delay(10);

            flag_wait = true;
        }
        else
        {
            flag_wait = false;
        }
    }
}

uint32_t sensor_read(void)
{
    digitalWrite(13, HIGH - digitalRead(13));

    uint32_t tick = micros();

    sr.update_imu();

    ros::Time ros_Time = nh.now();

    msg_imu = sr.get_imu();
    msg_imu.header.stamp.sec = ros_Time.sec;
    msg_imu.header.stamp.nsec = ros_Time.nsec;
    msg_imu.header.frame_id = "imu_link";

    pub_imu.publish(&msg_imu);

    char loginfo[50];
    sprintf(loginfo, "%d", ros_Time.nsec);
    nh.loginfo(loginfo);

    // msg_mag.header.stamp = nh.now();
    // msg_mag.header.frame_id = "mag_link";
    // msg_mag = sr.get_mag();

    // pub_mag.publish(&msg_mag);

    return (micros() - tick);
}

void remoteCallback(const quadnake_msgs::RemoteDrive &msg)
{
    cr.receiveCommand(msg);
    msg_remote = cr.getRemoteMsg();

    nh.loginfo("remote drive received!...");

    char *infos;
    sprintf(infos, "%d", msg_remote.FORWARD_DRIVE);

    nh.loginfo(infos);
}
