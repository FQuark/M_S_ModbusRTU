#include "Modbus_Master_Setup.h"
#include "Modbus_Utils.h"

uint16_t Time_out_check ;

// ควบคุมทิศทางส่ง/รับของ MAX485
void preTransmission() {
  digitalWrite(MASTER_MAX485_DE_RE, HIGH); // โหมดส่ง
}

void postTransmission() {
  digitalWrite(MASTER_MAX485_DE_RE, LOW);  // โหมดรับ
}

// เปลี่ยนสถานีปลายทาง (Slave ID)
void update_station(int stationID) {
  node.begin(stationID, Serial1);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

// อ่าน Holding Register
void readHreg(int stationID, uint16_t address, uint16_t range) {
  update_station(stationID);
  uint8_t result = node.readHoldingRegisters(address, range);

  if (result == node.ku8MBSuccess) {
    Serial.print("Read success: Address ");
    Serial.print(address);
    Serial.print(" -> ");
    for (uint16_t i = 0; i < range; i++) {
      Serial.print("Reg[");
      Serial.print(address + i);
      Serial.print("] = ");
      Serial.print(node.getResponseBuffer(i));
    }
    Serial.println();
    Time_out_check = 0 ;
  } else {
    Serial.print("Read failed (stationID ");
    Serial.print(stationID);
    Serial.println(") Time OUT");
    Time_out_check = 1 ;
  }
}

// เขียนค่าลง Holding Register
void writeHreg(int stationID, uint16_t address, uint16_t value) {
  update_station(stationID);
  uint8_t result = node.writeSingleRegister(address, value);

  if (result == node.ku8MBSuccess) {
    Serial.print("Write success: Address ");
    Serial.print(address);
    Serial.print(" = ");
    Serial.println(value);
  } else {
    Serial.print("Write failed (stationID ");
    Serial.print(stationID);
    Serial.println(")");
  }
}
