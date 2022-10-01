/*
   ---------------------------------------- SENDER ----------------------------------------
   LoRa E32-TTL-100
   E32-TTL-100----- Arduino UNO
   M0  ----- PIN 6
   M1  ----- PIN 7
   TX  ----- PIN 2 (PullUP)
   RX  ----- PIN 3 (PullUP & Voltage divider)
   AUX ----- PIN 5
   VCC ----- 3.3v/5v
   GND ----- GND


 *  * -- DHT22 --
   VCC ---- 5v
   VIN ---- PIN 8
   GND ---- GND

   -- MQ-2 --
   VCC ---- VCC
   GND ---- GND
   DO ----- 9
   AO  ---- AO

   -- MPU6050 --
   VCC ---- VCC
   GND ---- GND
   SCI ---- A5
   SDA ---- A0

   LOG_LEVEL 0 -> DEBUG
   LOG_LEVEL 1 -> EXECUTION
*/

#include "Arduino.h"
#include "LoRa_E32.h"
#include <DHT.h>
#include "MQ2.h"
#include "MPU6050.h"
#include <Adafruit_BMP280.h>
#define LOG_LEVEL 1

LoRa_E32 e32ttl100(2, 3, 5, 6, 7);
DHT dht(8, DHT22);
MQ2 mq2(A0);
MPU6050 mpu6050(0x68);
Adafruit_BMP280 bmp;

struct Payload {
  double temp = NAN;
  double hum = NAN;
  double lgp = NAN;
  double co = NAN;
  double smoke = NAN;
  double pressu = NAN;
  double alt = NAN;
  int    AcX = 0;
  int    AcY = 0;
  int    AcZ = 0;
  int    GyX = 0;
  int    GyY = 0;
  int    GyZ = 0;
};
int   count = 0;

boolean status_lora = false;
boolean status_mq2 = false;
boolean status_dht22 = false;
boolean status_mpu6050 = false;
boolean status_bmp = false;
unsigned long time = millis();
struct Payload payload;

void setup() {
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  delay(70);
  digitalWrite(12, HIGH);
  delay(70);
  digitalWrite(12, LOW);
  delay(70);
  digitalWrite(12, HIGH);
  delay(70);
  digitalWrite(12, LOW);


  Serial.begin(9600);
  delay(500);

  e32ttl100.begin();
  setup_lora();

  mq2.begin();
  setup_mq2();

  mpu6050.begin();
  setup_mpu6050();

  dht.begin();
  setup_dht22();

  setup_bmp();

  delay(500);
}

void loop() {

  Serial.println("teste");
  get_value();
  singnal_status();
  ResponseStatus rs = e32ttl100.sendFixedMessage(0, 3, 0x04, &payload, sizeof(Payload));
  
  if(rs.code != 1) {
    status_lora = false;
  } else {
    status_lora = true;
  }
  
  if (LOG_LEVEL == 0 ) {
    Serial.println("--------------------------------- SEND MESSAGE ----------------------------------");
    Serial.println("Count         ->  " + String(count++));
    Serial.println("TEMPERATURA   ->  " + String(payload.temp));
    Serial.println("HUMIDADE      ->  " + String(payload.hum));
    Serial.println("GLP           ->  " + String(payload.lgp, 10));
    Serial.println("CO2           ->  " + String(payload.co, 10));
    Serial.println("FUMAÇA        ->  " + String(payload.smoke, 10));
    Serial.println("PRESSÃO       ->  " + String(payload.pressu, 2) + " atm");
    Serial.println("ALTITUDE      ->  " + String(payload.alt, 2) + " m");
    Serial.println("ACELEROMETRO  ->  X: " + String(payload.AcX) + " Y: " + String(payload.AcY) + " Z: " + String(payload.AcZ));
    Serial.println("GIROSCOPIIO   ->  X: " + String(payload.GyX) + " Y: " + String(payload.GyY) + " Z: " + String(payload.GyZ));
  }

  digitalWrite(12, LOW);
  delay(500);

}

void get_value() {
  mpu6050.update();
  if (status_dht22) {
    payload.temp = dht.readTemperature();
    payload.hum = dht.readHumidity();
  } else {
    payload.temp = NAN;
    payload.hum = NAN;
  }

  if (status_bmp) {
    payload.pressu = bmp.readPressure();
    payload.alt = bmp.readAltitude(1013.25);
  } else {
    payload.pressu = NAN;
    payload.alt = NAN;
  }

  if (status_mq2) {
    payload.lgp = mq2.readLPG();
    payload.co = mq2.readCO();
    payload.smoke = mq2.readSmoke();
  } else {
    payload.lgp = NAN;
    payload.co = NAN;
    payload.smoke = NAN;
  }

  if (status_mpu6050) {
    payload.AcX = mpu6050.getAx();
    payload.AcY = mpu6050.getAy();
    payload.AcZ = mpu6050.getAz();
    payload.GyX = mpu6050.getGx();
    payload.GyY = mpu6050.getGy();
    payload.GyZ = mpu6050.getGz();
  } else {
    payload.AcX = 0;
    payload.AcY = 0;
    payload.AcZ = 0;
    payload.GyX = 0;
    payload.GyY = 0;
    payload.GyZ = 0;
  }
}

void singnal_status() {
  if(status_lora == false) Serial.println("Module LORA-E32 not working");
  if(status_mq2 == false) Serial.println("Module MQ2 not working");
  if(status_dht22 == false) Serial.println("Module DHT2 not working");
  if(status_mpu6050 == false) Serial.println("Module MPU6050 not working");
  if(status_bmp == false) Serial.println("Module BMP not working");
  Serial.println(status_lora);
  if ( LOG_LEVEL > 0 && status_lora == false) {
    digitalWrite(12, HIGH);
  }
}
