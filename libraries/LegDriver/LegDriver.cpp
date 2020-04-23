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

    setTorque(0xFE, true);
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

    dxl_comm_result = dxl_pack->write4ByteTxRx(dxl_port, dxl_id, ADDR_X_GOAL_POSITION, pos_value, &dxl_error);

    if (dxl_comm_result != COMM_SUCCESS)
    {
        dxl_pack->getTxRxResult(dxl_comm_result);
    }
    else if (dxl_error != 0)
    {
        dxl_pack->getRxPacketError(dxl_error);
    }
}