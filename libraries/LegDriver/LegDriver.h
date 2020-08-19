#ifndef __MOTOR_DRIVER
#define __MOTOR_DRIVER

#include "variant.h"
#include <DynamixelSDK.h>

//msg handle
#include <quadnake_msgs/LegsDrive.h>
#include <quadnake_msgs/LegCommand.h>
#include <quadnake_msgs/Feed.h>
#include <quadnake_msgs/DriveFeed.h>
#include <quadnake_msgs/RemoteDrive.h>

// Control table address (Dynamixel X-series)
#define ADDR_X_TORQUE_ENABLE 64
#define ADDR_X_GOAL_VELOCITY 104
#define ADDR_X_GOAL_POSITION 116
#define ADDR_X_REALTIME_TICK 120
#define ADDR_X_PRESENT_CURRENT 126
#define ADDR_X_PRESENT_VELOCITY 128
#define ADDR_X_PRESENT_POSITION 132

// Data Byte Length
#define LEN_X_TORQUE_ENABLE 1
#define LEN_X_GOAL_VELOCITY 4
#define LEN_X_GOAL_POSITION 4
#define LEN_X_REALTIME_TICK 2
#define LEN_X_PRESENT_VELOCITY 4
#define LEN_X_PRESENT_POSITION 4

#define DXL_PROTOCOL_VERSION 2.0 // Dynamixel protocol version 2.0

#define DXL_BAUDRATE 1000000 // baurd rate of Dynamixel
#define DXL_DEVICENAME ""  // no need setting on OpenCR

#define DXL_TORQUE_ENABLE 1  // Value for enabling the torque
#define DXL_TORQUE_DISABLE 0 // Value for disabling the torque

#define QAUD_LEG_FL 0
#define QAUD_LEG_FR 1
#define QAUD_LEG_RL 2
#define QAUD_LEG_RR 3
#define QUAD_DXL_1_JOINT 1
#define QUAD_DXL_2_JOINT 2
#define QUAD_DXL_3_JOINT 3
#define QUAD_DXL_4_JOINT 4
#define QUAD_DXL_5_JOINT 5
#define QUAD_DXL_6_JOINT 6
#define QUAD_DXL_7_JOINT 7
#define QUAD_DXL_8_JOINT 8
#define QUAD_LEG_ID(A, B) (A * 10 + B)

class LegDriver
{
private:
    dynamixel::PortHandler *dxl_port;
    dynamixel::PacketHandler *dxl_pack;

    /* data */
    uint32_t baudrate;
    float dxl_protocol_version;

    uint8_t drive_mode;
    uint8_t trough;
    float amplitude;
    float position;
    float duty;
    float velocity;

public:
    LegDriver(/* args */);
    ~LegDriver();
    void legInit(void);
    void setTorque(uint8_t dxl_id, bool onoff);
    void setGoalPos(uint8_t dxl_id, uint32_t pos_value);
    int16_t getPresentCurrent(uint8_t dxl_id);
    
};

#endif //__MOTOR_DRIVER
