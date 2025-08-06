#include "Modbus_Master_Setup.h"
ModbusMaster node;
void setupModbusMSystem() {
  pinMode(MASTER_MAX485_DE_RE, OUTPUT);   
  digitalWrite(MASTER_MAX485_DE_RE, LOW);    
  Serial1.begin(38400, SERIAL_8E1, MASTER_RX, MASTER_TX);
}
