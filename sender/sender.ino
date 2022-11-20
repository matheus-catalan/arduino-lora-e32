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

#define LOG_LEVEL 1
#define LORA_TX 2
#define LORA_RX 3
#define LORA_M0 7
#define LORA_M1 6
#define LORA_AUX 5 
#define DHT_PIN 8
#define MQ_PIN A0

LoRa_E32 e32ttl100(LORA_TX, LORA_RX, LORA_AUX, LORA_M1, LORA_M0);
DHT dht(DHT_PIN, DHT22);
MQ2 mq2(MQ_PIN);




struct Payload {
  double temp = NAN;
  double hum = NAN;
  double lgp = NAN;
  double co = NAN;
  double smoke = NAN;
};

boolean status_lora = false;
boolean status_mq2 = false;
boolean status_dht22 = false;
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

  dht.begin();
  setup_dht22();

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
  Serial.println("TEMPERATURA   ->  " + String(payload.temp));
  Serial.println("HUMIDADE      ->  " + String(payload.hum));
  Serial.println("GLP           ->  " + String(payload.lgp, 10));
  Serial.println("CO2           ->  " + String(payload.co, 10));
  Serial.println("FUMAÇA        ->  " + String(payload.smoke, 10));

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

  if (status_mq2) {
    payload.lgp = mq2.readLPG();
    payload.co = mq2.readCO();
    payload.smoke = mq2.readSmoke();
  } else {
    payload.lgp = NAN;
    payload.co = NAN;
    payload.smoke = NAN;
  }
}
