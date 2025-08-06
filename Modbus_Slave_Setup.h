#ifndef MODBUS_SLAVE_SETUP
#define MODBUS_SLAVE_SETUP
#include <ModbusRTU.h>
#define SLAVE_RX 16
#define SLAVE_TX 17
#define SLAVE_MAX485_DE_RE  4
#define SLAVE_H_LIM 7
#define SLAVE_ID 100
extern ModbusRTU RTU_SLAVE;
extern uint16_t Time_out_check;

void setupModbusSLSystem();
void resetModbusSLSystem();
#endif
