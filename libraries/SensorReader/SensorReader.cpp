#include "SensorReader.h"

SensorReader::SensorReader(/* args */)
{
}

SensorReader::~SensorReader()
{
    Serial4.end();
}

bool SensorReader::sr_init(void)
{
    Serial4.begin(57600);

    uint8_t code_error = 0x00;

    msg_batt.current = NAN;
    msg_batt.charge = NAN;
    msg_batt.capacity = NAN;
    msg_batt.design_capacity = NAN;
    msg_batt.percentage = NAN;

    Serial4.println("Initiating IMU...");
    code_error = class_imu.begin();

    if (code_error != 0x00)
    {
        Serial4.println("Failed to Init IMU... (terminate constructor function)");
    }
    else
    {
        Serial4.println("SensorReader Class is constructed done...");
    }

    return code_error;
}

void SensorReader::init_imu(void)
{
    class_imu.begin();
}

void SensorReader::update_imu(void)
{
    class_imu.update();
}

sensor_msgs::Imu SensorReader::get_imu(void)
{
    /*Angular Values*/
    msg_imu.angular_velocity.x = class_imu.SEN.gyroADC[0] * GYRO_FACTOR;
    msg_imu.angular_velocity.y = class_imu.SEN.gyroADC[1] * GYRO_FACTOR;
    msg_imu.angular_velocity.z = class_imu.SEN.gyroADC[2] * GYRO_FACTOR;

    /*Angular Convariance Values*/
    msg_imu.angular_velocity_covariance[0] = 0.02;
    msg_imu.angular_velocity_covariance[1] = 0;
    msg_imu.angular_velocity_covariance[2] = 0;
    msg_imu.angular_velocity_covariance[3] = 0;
    msg_imu.angular_velocity_covariance[4] = 0.02;
    msg_imu.angular_velocity_covariance[5] = 0;
    msg_imu.angular_velocity_covariance[6] = 0;
    msg_imu.angular_velocity_covariance[7] = 0;
    msg_imu.angular_velocity_covariance[8] = 0.02;

    /*Linear Values*/
    msg_imu.linear_acceleration.x = class_imu.SEN.accADC[0] * ACCEL_FACTOR;
    msg_imu.linear_acceleration.y = class_imu.SEN.accADC[1] * ACCEL_FACTOR;
    msg_imu.linear_acceleration.z = class_imu.SEN.accADC[2] * ACCEL_FACTOR;

    /*Linear Convariance Values*/
    msg_imu.linear_acceleration_covariance[0] = 0.04;
    msg_imu.linear_acceleration_covariance[1] = 0;
    msg_imu.linear_acceleration_covariance[2] = 0;
    msg_imu.linear_acceleration_covariance[3] = 0;
    msg_imu.linear_acceleration_covariance[4] = 0.04;
    msg_imu.linear_acceleration_covariance[5] = 0;
    msg_imu.linear_acceleration_covariance[6] = 0;
    msg_imu.linear_acceleration_covariance[7] = 0;
    msg_imu.linear_acceleration_covariance[8] = 0.04;

    /*Pose Orientation Values*/
    msg_imu.orientation.w = class_imu.quat[0];
    msg_imu.orientation.x = class_imu.quat[1];
    msg_imu.orientation.y = class_imu.quat[2];
    msg_imu.orientation.z = class_imu.quat[3];

    /*Pose Orientation Convariance Values*/
    msg_imu.orientation_covariance[0] = 0.0025;
    msg_imu.orientation_covariance[1] = 0;
    msg_imu.orientation_covariance[2] = 0;
    msg_imu.orientation_covariance[3] = 0;
    msg_imu.orientation_covariance[4] = 0.0025;
    msg_imu.orientation_covariance[5] = 0;
    msg_imu.orientation_covariance[6] = 0;
    msg_imu.orientation_covariance[7] = 0;
    msg_imu.orientation_covariance[8] = 0.0025;

    return msg_imu;
}

void SensorReader::calib_gyro(void)
{
    uint32_t pre_time;
    uint32_t now_time;

    const uint8_t ros_led = 3;

    class_imu.SEN.gyro_cali_start();

    now_time = millis();
    pre_time = millis();

    while (!class_imu.SEN.gyro_cali_get_done())
    {
        class_imu.update();

        if (millis() - pre_time > 5000)
        {
            break;
        }

        if (millis() - now_time > 100)
        {
            now_time = millis();
            setLedToggle(ros_led);
        }
    }
}

sensor_msgs::MagneticField SensorReader::get_mag(void)
{
    /*MagneticField Values*/
    msg_mag.magnetic_field.x = class_imu.SEN.magADC[0] * MAG_FACTOR;
    msg_mag.magnetic_field.y = class_imu.SEN.magADC[1] * MAG_FACTOR;
    msg_mag.magnetic_field.z = class_imu.SEN.magADC[2] * MAG_FACTOR;

    /*MagneticField Convariance Values*/
    msg_mag.magnetic_field_covariance[0] = 0.0048;
    msg_mag.magnetic_field_covariance[1] = 0;
    msg_mag.magnetic_field_covariance[2] = 0;
    msg_mag.magnetic_field_covariance[3] = 0;
    msg_mag.magnetic_field_covariance[4] = 0.0048;
    msg_mag.magnetic_field_covariance[5] = 0;
    msg_mag.magnetic_field_covariance[6] = 0;
    msg_mag.magnetic_field_covariance[7] = 0;
    msg_mag.magnetic_field_covariance[8] = 0.0048;

    return msg_mag;
}