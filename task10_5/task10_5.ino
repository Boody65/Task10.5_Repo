#include <Wire.h>


const byte MPU_ADDR = 0x68;

const byte PWR_MGMT_1 = 0x6B;
const byte GYRO_CONFIG = 0x1B;
const byte GYRO_XOUT_H = 0x43;
const byte PWR_MGMT_1_VALUE = 0x00; 
const byte GYRO_CONFIG_VALUE = 0x08; 

void setup() {
  Wire.begin(); 


  Wire.beginTransmission(MPU_ADDR);
  Wire.write(PWR_MGMT_1);
  Wire.write(PWR_MGMT_1_VALUE);
  Wire.endTransmission();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(GYRO_CONFIG);
  Wire.write(GYRO_CONFIG_VALUE);
  Wire.endTransmission();
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(GYRO_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(uint8_t(MPU_ADDR), uint8_t(2));


  int16_t gyroX = Wire.read() << 8 | Wire.read();
  float gyroX_dps = gyroX / 131; 
  static float yaw = 0;
  yaw += gyroX_dps * 0.01; 


  Serial.print("Yaw: ");
  Serial.println(yaw);
}