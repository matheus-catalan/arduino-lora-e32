/*
 * ------------------------------------- RECEIVER -------------------------------------------------
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

// ---------- Arduino pins --------------
//LoRa_E32 e32ttl(2, 3, 5, 7, 6);
LoRa_E32 e32ttl100(2, 3, 5, 6, 7); // e32 TX e32 RX

#define LOG_LEVEL 0

struct Payload {
  float sensor1;
  float sensor2;
  float sensor3;
  int count_message;
};

int size_gyro = sizeof(struct Payload);
int count = 0;
void setup() {
  Serial.begin(9600);
  delay(1000);
  
  e32ttl100.begin();
  delay(500);
  setup_lora();
}

void loop() {
  if (e32ttl100.available() > 1){
    ResponseStructContainer rsc = e32ttl100.receiveMessage(sizeof(Payload));
    
    struct Payload payload = *(Payload*) rsc.data;
    send(&payload);
    if ( LOG_LEVEL == 0 ){
      Serial.println("----------------------------------- MESSAGE -------------------------------------");
      Serial.print("Amount messages -> ");
      Serial.print(payload.count_message);
      Serial.print("\nSensor 1 -> ");
      Serial.print(payload.sensor1);
      Serial.print("\nSensor 2 -> ");
      Serial.print(payload.sensor2);
      Serial.print("\nSensor 3 -> ");
      Serial.print(payload.sensor3);
      Serial.println("\n----------------------------------- MESSAGE -------------------------------------");
    }
    free(rsc.data);
  }
}

void send (const Payload* table)
{
  Serial.write((const char*)table, size_gyro);  // 2 bytes.
}
