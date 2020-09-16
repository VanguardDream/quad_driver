#include <ros.h>
#include <ros/time.h>

#include <SensorReader.h>
#include <CommandReceiver.h>
#include <LegDriver.h>
#include <MotionGenerator_ver.h>

uint32_t static t_dead[5];

/* Quadnake Hardware Interface */

/* For ROS interfacing */

ros::NodeHandle nh;

/////////////////////////
//Functions

/* For Communication Syncronize*/
void rosSerialLink(bool isConnected);

/////////////////////////
/* For SensorReader */

SensorReader sr;

static sensor_msgs::Imu msg_imu;
ros::Publisher pub_imu("imu", &msg_imu);

sensor_msgs::MagneticField msg_mag;
ros::Publisher pub_mag("magnetic_field", &msg_mag);

//Functions
/*Read sensor datas and publish on ROS.*/
uint32_t sensor_read(void);

/////////////////////////
/* For Command Receiver */

CommandReceiver cr;

quadnake_msgs::RemoteDrive msg_remote;
quadnake_msgs::LegsDrive msg_legs;

//Functions
void remoteCallback(const quadnake_msgs::RemoteDrive &msg);
ros::Subscriber<quadnake_msgs::RemoteDrive> sub_remote("/message_sender/cmd_drive", remoteCallback);

void legsDriveCallback(const quadnake_msgs::LegsDrive &msg);
ros::Subscriber<quadnake_msgs::LegsDrive> sub_legs("", legsDriveCallback);

/////////////////////////
/* For Leg Driver */

LegDriver ld;

static quadnake_msgs::DriveFeed feed;
ros::Publisher pub_feed("leg_feed", &feed);
uint32_t seq_leg_feed = 0;

//Functions

void legDrive(void);
void legSense(void);
/////////////////////////
/* For Motion Generator */

MotionGenerator mg;
/////////////////////////