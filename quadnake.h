#include <ros.h>
#include <SensorReader.h>
//#include <IMU.h>

#include <CommandReceiver.h>

uint32_t static t_dead[5];

/* For ROS interfacing */

ros::NodeHandle nh;

/////////////////////////
/* For SensorReader */

SensorReader sr;

sensor_msgs::Imu msg_imu;
ros::Publisher pub_imu("imu", &msg_imu);

sensor_msgs::MagneticField msg_mag;
ros::Publisher pub_mag("magnetic_field", &msg_mag);

//Functions
/*Read sensor datas and publish on ROS.*/
uint32_t sensor_read(void);

/////////////////////////
/* For Command Receiver */

CommandReceiver cr;

//ros::Subscriber < quadnake_msgs::LegsDrive> sub_legs();

//Functions
void remoteCallback(const quadnake_msgs::RemoteDrive &msg_remote);
ros::Subscriber<quadnake_msgs::RemoteDrive> sub_remote("/message_sender/cmd_drive", remoteCallback);

/////////////////////////
