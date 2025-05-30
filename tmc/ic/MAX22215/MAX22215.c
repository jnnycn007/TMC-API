/*******************************************************************************
* Copyright © 2025 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "MAX22215.h"

static int32_t readRegisterI2C(uint16_t icID, uint8_t address);
static void writeRegisterI2C(uint16_t icID, uint8_t address, int32_t value);

int32_t max22215_readRegister(uint16_t icID, uint8_t address)
{
    MAX22215BusType bus = max22215_getBusType(icID);

    if(bus == IC_BUS_I2C)
    {
        return readRegisterI2C(icID, address);
    }
    //ToDo: Error handling
    return -1;
}

void max22215_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
    MAX22215BusType bus = max22215_getBusType(icID);

    if(bus == IC_BUS_I2C)
    {
        return writeRegisterI2C(icID, address, value);
    }
}

int32_t readRegisterI2C(uint16_t icID, uint8_t address)
{
    uint8_t data[3] = { 0 };

    data[0] = max22215_getDeviceAddress(icID);
    data[1] = address;  //register address

    if(!max22215_readWriteI2C(icID, &data[0], 1,1))
        return 0;

    return (int32_t)data[2];
}

void writeRegisterI2C(uint16_t icID, uint8_t address, int32_t value)
{
    uint8_t data[3] = { 0 };

    data[0] = max22215_getDeviceAddress(icID);
    data[1] = address;  //register address
    data[2] = 0xFF & value;

    max22215_readWriteI2C(icID, &data[0], 2,0);
}
