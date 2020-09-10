#include "LegDriver.h"

LegDriver::LegDriver(/* args */)
    : baudrate(DXL_BAUDRATE), dxl_protocol_version(DXL_PROTOCOL_VERSION)
{
}

LegDriver::~LegDriver()
{
    setTorque(0xFE, false);
    dxl_port->closePort();
}
void LegDriver::legInit(void)
{
    dxl_port = dynamixel::PortHandler::getPortHandler("");
    dxl_pack = dynamixel::PacketHandler::getPacketHandler(DXL_PROTOCOL_VERSION);

    dxl_grp_current_reader = new dynamixel::GroupSyncRead(dxl_port, dxl_pack, ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);

    if (dxl_port->openPort())
    {
        SerialBT2.print("Port is opened...");
    }
    else
    {
        SerialBT2.print("Port is not opened...");
    }

    if (dxl_port->setBaudRate(DXL_BAUDRATE))
    {
        SerialBT2.print("Baudrate is set...");
    }
    else
    {
        SerialBT2.print("Baudrate is not set...");
    }
    setTorque(0xFE, false);

    setTorque(0xFE, true);

    setStatusLevel(0xFE, 1);

    setGoalPos(0xFE, 2048);
}
void LegDriver::setTorque(uint8_t dxl_id, bool onoff)
{
    uint8_t dxl_error;
    int dxl_comm_result = COMM_TX_FAIL;

    dxl_comm_result = dxl_pack->write1ByteTxRx(dxl_port, dxl_id, ADDR_X_TORQUE_ENABLE, onoff, &dxl_error);

    if (dxl_comm_result != COMM_SUCCESS)
    {
        dxl_pack->getTxRxResult(dxl_comm_result);
    }
    else if (dxl_error != 0)
    {
        dxl_pack->getRxPacketError(dxl_error);
    }
}

void LegDriver::setGoalPos(uint8_t dxl_id, uint32_t pos_value)
{
    uint8_t dxl_error;
    int dxl_comm_result = COMM_TX_FAIL;

    dxl_comm_result = dxl_pack->write4ByteTxOnly(dxl_port, dxl_id, ADDR_X_GOAL_POSITION, pos_value);

    // if (dxl_comm_result != COMM_SUCCESS)
    // {
    //     dxl_pack->getTxRxResult(dxl_comm_result);
    // }
    // else if (dxl_error != 0)
    // {
    //     dxl_pack->getRxPacketError(dxl_error);
    // }
}

void LegDriver::setStatusLevel(uint8_t dxl_id, uint8_t value)
{
    uint8_t dxl_error;
    int dxl_comm_result = COMM_TX_FAIL;

    dxl_comm_result = dxl_pack->write1ByteTxRx(dxl_port, dxl_id, ADDR_X_STATUS_RETURN_LEVEL, value, &dxl_error);

    if (dxl_comm_result != COMM_SUCCESS)
    {
        dxl_pack->getTxRxResult(dxl_comm_result);
    }
    else if (dxl_error != 0)
    {
        dxl_pack->getRxPacketError(dxl_error);
    }
}

int16_t LegDriver::getPresentCurrent(uint8_t dxl_id)
{
    //[Unit = mA]
    int dxl_comm_result;
    uint16_t received_temp_current;
    uint8_t dxl_error;

    dxl_comm_result = dxl_pack->read2ByteTxRx(dxl_port, dxl_id, ADDR_X_PRESENT_CURRENT, &received_temp_current, &dxl_error);

    if (dxl_comm_result != COMM_SUCCESS)
    {
        dxl_pack->getTxRxResult(dxl_comm_result);
    }
    else if (dxl_error != 0)
    {
        dxl_pack->getRxPacketError(dxl_error);
    }

    return received_temp_current;
}

bool LegDriver::getGroupPresentCurrent(uint8_t leg_id)
{
    int dxl_comm_result = COMM_TX_FAIL;
    bool dxl_addparam_result = false;
    bool dxl_getdate_result = false;

    //Set ID
    for (int idx = 1; idx < 9; idx++)
    {
        dxl_addparam_result = dxl_grp_current_reader->addParam(QUAD_LEG_ID(leg_id, idx));
        if (dxl_addparam_result != true)
            return false;
    }

    switch (leg_id)
    {
    case 0:
        feed.DRIVE_FEED_HEAD.frame_id = "front_left";
        break;
    case 1:
        feed.DRIVE_FEED_HEAD.frame_id = "front_right";
        break;
    case 2:
        feed.DRIVE_FEED_HEAD.frame_id = "rear_left";
        break;  
    case 3:
        feed.DRIVE_FEED_HEAD.frame_id = "rear_right";
        break;
    default:
        feed.DRIVE_FEED_HEAD.frame_id = "wrong_type_leg";
        break;
    }

    feed.MOTORS[0].ID = QUAD_LEG_ID(leg_id, 1);
    feed.MOTORS[1].ID = QUAD_LEG_ID(leg_id, 2);
    feed.MOTORS[2].ID = QUAD_LEG_ID(leg_id, 3);
    feed.MOTORS[3].ID = QUAD_LEG_ID(leg_id, 4);
    feed.MOTORS[4].ID = QUAD_LEG_ID(leg_id, 5);
    feed.MOTORS[5].ID = QUAD_LEG_ID(leg_id, 6);
    feed.MOTORS[6].ID = QUAD_LEG_ID(leg_id, 7);
    feed.MOTORS[7].ID = QUAD_LEG_ID(leg_id, 8);

    dxl_comm_result = dxl_grp_current_reader->txRxPacket();

    feed.MOTORS[0].CURRENT = (int16_t) dxl_grp_current_reader->getData(QUAD_LEG_ID(leg_id, 1), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);
    feed.MOTORS[1].CURRENT = (int16_t) dxl_grp_current_reader->getData(QUAD_LEG_ID(leg_id, 2), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);
    feed.MOTORS[2].CURRENT = (int16_t) dxl_grp_current_reader->getData(QUAD_LEG_ID(leg_id, 3), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);
    feed.MOTORS[3].CURRENT = (int16_t) dxl_grp_current_reader->getData(QUAD_LEG_ID(leg_id, 4), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);
    feed.MOTORS[4].CURRENT = (int16_t) dxl_grp_current_reader->getData(QUAD_LEG_ID(leg_id, 5), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);
    feed.MOTORS[5].CURRENT = (int16_t) dxl_grp_current_reader->getData(QUAD_LEG_ID(leg_id, 6), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);
    feed.MOTORS[6].CURRENT = (int16_t) dxl_grp_current_reader->getData(QUAD_LEG_ID(leg_id, 7), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);
    feed.MOTORS[7].CURRENT = (int16_t) dxl_grp_current_reader->getData(QUAD_LEG_ID(leg_id, 8), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);

    dxl_grp_current_reader->clearParam();

    return true;
}

quadnake_msgs::DriveFeed LegDriver::getFeedMsg(void)
{
    return feed;
}