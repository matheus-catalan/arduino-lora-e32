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
   DO ----- PIN 9
   AO  ---- AO

   -- BMP280 --
   VCC ---- VCC
   GND ---- GND
   SCL ---- A4
   SDA ---- A5

   LOG_LEVEL 0 -> DEBUG
   LOG_LEVEL 1 -> EXECUTION
*/

#include "Arduino.h"
#include "LoRa_E32.h"
#include <DHT.h>
#include "MQ2.h"
#include "MQ9.h"
#include <Adafruit_BMP280.h>
#define LOG_LEVEL 1
LoRa_E32 e32ttl100(2, 3, 5, 6, 7);
DHT dht(8, DHT22);
MQ2 mq2(A0);
MQ9 mq9(A1);
Adafruit_BMP280 bmp;


struct Payload {
  double temp = NAN;
  double hum = NAN;
  double lgp = NAN;
  double co = NAN;
  double smoke = NAN;
  double ch4 = NAN;
  double pressu = NAN;
  double alt = NAN;
};
int   count = 0;

boolean status_lora = false;
boolean status_mq2 = false;
boolean status_mq9 = false;
boolean status_dht22 = false;
boolean status_bmp = false;
struct Payload payload;

void setup() {
  Serial.begin(9600);
  delay(500);
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
  
  e32ttl100.begin();
  setup_lora();
  delay(500);

  mq2.begin();
  setup_mq2();

  mq9.begin();
  setup_mq9();

  dht.begin();
  setup_dht22();

//  setup_bmp();
//  bmp.begin();

//  delay(500);
}

void loop() {
  get_value();

  ResponseStatus rs = e32ttl100.sendFixedMessage(0, 3, 0x04, &payload, sizeof(Payload));
  
  if(rs.code != 1) {
    status_lora = false;
  } else {
    status_lora = true;
  }

  singnal_status();

  Serial.println("--------------------------------- SEND MESSAGE ----------------------------------");
  Serial.println("Response status send: " + String(rs.getResponseDescription()));
  Serial.println("Count         ->  " + String(count++));
  Serial.println("TEMPERATURA   ->  " + String(payload.temp));
  Serial.println("HUMIDADE      ->  " + String(payload.hum));
  Serial.println("GLP           ->  " + String(payload.lgp, 10));
  Serial.println("CO2           ->  " + String(payload.co, 10));
  Serial.println("FUMAÇA        ->  " + String(payload.smoke, 10));
  Serial.println("CH4           ->  " + String(payload.ch4, 10));
  Serial.println("PRESSÃO       ->  " + String(payload.pressu, 2) + " atm");
  Serial.println("ALTITUDE      ->  " + String(payload.alt, 2) + " m");

  delay(500);

}

void get_value() {
  
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

   if (status_mq9) {
    payload.ch4 = mq9.readCH4();
  } else {
    payload.ch4 = NAN;
  }
}
