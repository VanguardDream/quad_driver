#ifndef __SENSOR_READER
#define __SENSOR_READER

#include <Arduino.h>

#include <IMU.h>

#include <sensor_msgs/Imu.h>
#include <sensor_msgs/BatteryState.h>
#include <sensor_msgs/MagneticField.h>

#include "OLLO.h"

#define ACCEL_FACTOR 0.000598550415 // (ADC_Value / Scale) * 9.80665            => Range : +- 2[g] \
                                    //                                             Scale : +- 16384
#define GYRO_FACTOR 0.0010642       // (ADC_Value/Scale) * (pi/180)             => Range : +- 2000[deg/s] \
                                    //                                             Scale : +- 16.4[deg/s]

#define MAG_FACTOR 15e-8

#define DEBUG_SERIAL SerialBT2

class SensorReader
{
private:
    /* data */
    cIMU class_imu;
    OLLO class_ollo;

    sensor_msgs::Imu msg_imu;
    sensor_msgs::MagneticField msg_mag;
    sensor_msgs::BatteryState msg_batt;

public:
    SensorReader(/* args */);
    ~SensorReader();

    /*Sensor Reading Task Initiate*/
    bool sr_init(void);

    /*IMU sensor init*/
    void init_imu(void);

    /*Update IMU value*/
    void update_imu(void);

    /*Format data to ROS IMU msg*/
    sensor_msgs::Imu get_imu(void);

    /*Calibrate gyro sensor*/
    void calib_gyro(void);

    /*Format data to ROS Magnetic msg*/
    sensor_msgs::MagneticField get_mag(void);
};

#endif