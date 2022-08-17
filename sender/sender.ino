/*
 * ---------------------------------------- SENDER ----------------------------------------
 * LoRa E32-TTL-100
 * E32-TTL-100----- Arduino UNO
 * M0  ----- PIN 6
 * M1  ----- PIN 7
 * TX  ----- PIN 2 (PullUP)
 * RX  ----- PIN 3 (PullUP & Voltage divider)
 * AUX ----- PIN 5
 * VCC ----- 3.3v/5v
 * GND ----- GND
 * LOG_LEVEL 0 -> DEBUG
 * LOG_LEVEL 1 -> EXECUTION
 */
 
#include "Arduino.h"
#include "LoRa_E32.h"

//LoRa_E32 e32ttl(3, 2, 5, 7, 6);
//LoRa_E32 e32ttl100(2, 3, 5, 7, 6); 
LoRa_E32 e32ttl100(2, 3, 5, 6, 7); // e32 TX e32 RX

#define LOG_LEVEL 0

struct Payload {
  float sensor1;
  float sensor2;
  float sensor3;
  int count_message;
};
int count = 0;

int size_gyro = sizeof(struct Payload);

void setup() {
  Serial.begin(9600);
  delay(1000);

  

  e32ttl100.begin();
  delay(500);
  setup_lora();
}

void loop() {
  //delay(1000);


  struct Payload payload = {random(300) * 0.1, random(300) * 0.9, random(300) * 0.5, count++};

  ResponseStatus rs = e32ttl100.sendMessage(&payload, sizeof(Payload));
  Serial.println("--------------------------------- SEND MESSAGE ----------------------------------");
  Serial.print("Amount messages -> ");
  Serial.print(payload.count_message);
  Serial.print("\npayload[sensor1] ->  ");
  Serial.println(payload.sensor1);
  Serial.print("payload[sensor2] ->  ");
  Serial.println(payload.sensor2);
  Serial.print("payload[sensor3] ->  ");
  Serial.println(payload.sensor3);
  Serial.println("---------------------------------------------------------------------------------");
  
//  delay(1000);
}
