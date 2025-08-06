#include "Modbus_Slave_Setup.h"
ModbusRTU RTU_SLAVE;
void setupModbusSLSystem() {
  pinMode(SLAVE_MAX485_DE_RE, OUTPUT);
  digitalWrite(SLAVE_MAX485_DE_RE, LOW);
  Serial2.begin(19200, SERIAL_8E1, SLAVE_RX, SLAVE_TX);
  RTU_SLAVE.begin(&Serial2, SLAVE_MAX485_DE_RE, true);
  RTU_SLAVE.slave(SLAVE_ID);
  for (uint16_t i = 0; i <= SLAVE_H_LIM; i++) {
    RTU_SLAVE.addHreg(i);
    if (i == 0) {
      RTU_SLAVE.onSetHreg(i, 0);
    }
    RTU_SLAVE.onGetHreg(i, 0);
  }
}

void resetModbusSLSystem() {
  for (uint16_t i = 0; i <= SLAVE_H_LIM; i++) {
    RTU_SLAVE.Hreg(i,0);
  }
}