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

bool LegDriver::getGroupPresentCurrent(uint8_t leg_id, int16_t motorCurrents[])
{
    int dxl_comm_result = COMM_TX_FAIL;
    bool dxl_addparam_result = false;
    bool dxl_getdate_result = false;

    //Set ID
    for (int idx = 1; idx < 8; idx++)
    {
        dxl_addparam_result = dxl_grp_current_reader->addParam(QUAD_LEG_ID(leg_id, idx));
        if (dxl_addparam_result != true)
            return false;
    }

    // //Send instruction Packet
    // dxl_comm_result = dxl_grp_current_reader->txRxPacket();
    // if (dxl_comm_result != COMM_SUCCESS)
    //     Serial.println(dxl_pack->getTxRxResult(dxl_comm_result));

    // //Get Date from packet
    // for (int idx = 1; idx < 8; idx++)
    // {
    //     dxl_addparam_result = dxl_grp_current_reader->isAvailable(QUAD_LEG_ID(leg_id, idx), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);
    //     if (dxl_addparam_result != true)
    //         return false;
    // }

    // //Parse Need Data
    // for (int idx = 1; idx < 8; idx++)
    // {
    //     motorCurrents[idx] = dxl_grp_current_reader->getData(QUAD_LEG_ID(leg_id, idx), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);
    // }


    //For one node debugginf
    //dxl_addparam_result = dxl_grp_current_reader->addParam(QUAD_LEG_ID(1, 1));
    dxl_comm_result = dxl_grp_current_reader->txRxPacket();
    //dxl_addparam_result = dxl_grp_current_reader->isAvailable(QUAD_LEG_ID(1, 1), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);
    motorCurrents[1] = dxl_grp_current_reader->getData(QUAD_LEG_ID(1, 1), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);
    motorCurrents[2] = dxl_grp_current_reader->getData(QUAD_LEG_ID(1, 2), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);
    motorCurrents[3] = dxl_grp_current_reader->getData(QUAD_LEG_ID(1, 3), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);
    motorCurrents[4] = dxl_grp_current_reader->getData(QUAD_LEG_ID(1, 4), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);
    motorCurrents[5] = dxl_grp_current_reader->getData(QUAD_LEG_ID(1, 5), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);
    motorCurrents[6] = dxl_grp_current_reader->getData(QUAD_LEG_ID(1, 6), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);
    motorCurrents[7] = dxl_grp_current_reader->getData(QUAD_LEG_ID(1, 7), ADDR_X_PRESENT_CURRENT, LEN_X_PRESENT_CURRENT);

    dxl_grp_current_reader->clearParam();

    return true;
}