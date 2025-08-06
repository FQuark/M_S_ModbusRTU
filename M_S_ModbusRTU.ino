#include "Modbus_Master_Setup.h"
#include "Modbus_Utils.h"

#include "Modbus_Slave_Setup.h"

#include <math.h>

const uint16_t Sys_add  = 0x030C;   //780
const uint16_t SDI_add  = 0x040E;  //1038
const uint16_t SDO_add  = 0x0412;   //1042
const uint16_t WSDI_add = 0x030C;  //780
const uint16_t SP_add   = 0x0012;    //18
const uint16_t T_add    = 0x0014;  //20

// ตัวแปรเก็บค่าที่อ่านได้
uint16_t SDI_read;
uint16_t SDO_read;
uint16_t WSDI_read;
uint16_t SP_read;
uint16_t T_read;

int slave_id = 127;

const uint16_t Sys_value = 0x00ff;

unsigned long last = 0;
int h = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  setupModbusMSystem();
  delay(1000);
  setupModbusSLSystem();
  delay(1000);
  delay(5);
  writeHreg(slave_id, Sys_add, Sys_value);
  delay(5);
  RTU_SLAVE.Hreg(5, 0x0001);
  delay(5);
  writeHreg(slave_id, SDI_add, RTU_SLAVE.Hreg(5));
  delay(5);
}

void loop() {
  last = millis();

  if (Time_out_check == 1) {
    delay(5);
    readHreg(1, SDI_add, 1);
    SDI_read = node.getResponseBuffer(0);
    delay(5);
    //resetModbusSLSystem();
    //RTU_SLAVE.Hreg(6,Time_out_check);
    //RTU_SLAVE.task();
  }
  else {
    delay(5);
    readHreg(slave_id, SDI_add, 1);
    SDI_read = node.getResponseBuffer(0);
    readHreg(slave_id, SDO_add, 1);
    SDO_read = node.getResponseBuffer(0);
    readHreg(slave_id, WSDI_add, 1);
    WSDI_read = node.getResponseBuffer(0);
    readHreg(slave_id, SP_add, 1);
    SP_read = node.getResponseBuffer(0)*(0.1)/(1);
    readHreg(slave_id, T_add, 1);
    T_read = node.getResponseBuffer(0)*(0.1)/(1);
    delay(5);
    RTU_SLAVE.task();
    RTU_SLAVE.Hreg(0,SDI_read);
    RTU_SLAVE.Hreg(1,SDO_read);
    RTU_SLAVE.Hreg(2,WSDI_read);
    RTU_SLAVE.Hreg(3,SP_read);
    RTU_SLAVE.Hreg(4,T_read);
    delay(5);
    writeHreg(slave_id, SDI_add, RTU_SLAVE.Hreg(5));
    delay(5);
  }

  Serial.print("Time: "); Serial.println(millis() - last);
}


//MASTER
//ประกาศ readHreg(Station, Address, 1); เพื่ออ่าน
//เก็บค่าที่อ่านได้ใน อะไรบางอย่าง = node.getResponseBuffer(0);
//ประกาศ writeHreg(Station, Address, Value); เพื่อเขียน

//SLAVE 
//RTU_SLAVE.task(); ประกาศก่อนทำงาน
//RTU_SLAVE.Hreg(address,value); เพื่อเขียนค่าลงไป

