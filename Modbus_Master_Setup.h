#ifndef MODBUS_MASTER_SETUP
#define MODBUS_MASTER_SETUP
#include <Arduino.h>
#include <ModbusMaster.h>
#define MASTER_MAX485_DE_RE 27
#define MASTER_RX 15
#define MASTER_TX 5
extern ModbusMaster node;
void setupModbusMSystem();
#endif
