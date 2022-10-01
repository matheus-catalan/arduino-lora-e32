#include "Arduino.h"
#include "MPU6050.h"
#include <Wire.h>

MPU6050::MPU6050(int pin) {
  _pin = pin;
}

void MPU6050::begin(){
  Wire.begin();
  Wire.beginTransmission(0x68);
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true);
}

void MPU6050::update() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,14,true);
  
  
  ax = Wire.read()<<8|Wire.read();
  ay = Wire.read()<<8|Wire.read();
  az = Wire.read()<<8|Wire.read();
  tmp = Wire.read()<<8|Wire.read();
  gx = Wire.read()<<8|Wire.read();
  gy = Wire.read()<<8|Wire.read();
  gz = Wire.read()<<8|Wire.read();
}

int MPU6050::getAx(){
  return ax;
}

int MPU6050::getAy(){
  return ay;
}

int MPU6050::getAz(){
  return az;
}

int MPU6050::getGx(){
  return gx;
}

int MPU6050::getGy(){
  return gy;
}

int MPU6050::getGz(){
  return gz;
}

boolean MPU6050::checkCalibration() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,14,true);


  ax = Wire.read()<<8|Wire.read();
  ay = Wire.read()<<8|Wire.read();
  az = Wire.read()<<8|Wire.read();
  tmp = Wire.read()<<8|Wire.read();
  gx = Wire.read()<<8|Wire.read();
  gy = Wire.read()<<8|Wire.read();
  gz = Wire.read()<<8|Wire.read();

  if(ax >= 0 && ax >= 0 && ay >= 0 && az >= 0 && tmp >= 0 && gx >= 0 && gy >= 0 && gz >= 0) {
    return false;
  }

  return true;
}
