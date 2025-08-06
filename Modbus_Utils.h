#ifndef MODBUS_UTILS_H
#define MODBUS_UTILS_H
#include <Arduino.h>
#include <ModbusMaster.h>
#include "Modbus_Master_Setup.h"
#include "Modbus_Utils.h"
extern ModbusMaster node;
void readHreg(int stationID, uint16_t address, uint16_t range);
void writeHreg(int stationID, uint16_t address, uint16_t value);
void update_station(int stationID);
#endif
