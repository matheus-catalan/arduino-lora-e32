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

LoRa_E32 e32ttl100(2, 3, 5, 6, 7);


#define LOG_LEVEL 0

bool should_next = true;
struct Payload {
  double temp;
  double hum;
  double lgp;
  double co;
  double smoke;
  double pressu = NAN;
  double alt = NAN;
  int    AcX;
  int    AcY;
  int    AcZ;
  int    GyX;
  int    GyY;
  int    GyZ;
};

int size_gyro = sizeof(struct Payload);
int count = 0;
void setup() {
  Serial.begin(9600);
  delay(1000);
  
  e32ttl100.begin();
  setup_lora();
  delay(500);
}

void loop() {
  char should_read = Serial.read();
  
  
//  if(should_read  == 'y') {
//    should_next = true;
//  } else if(should_read == 'n' ) {
//    should_next = false;
//  }

  
  if (e32ttl100.available() > 1 && should_next){
    ResponseStructContainer rsc = e32ttl100.receiveMessage(sizeof(Payload));
    
    struct Payload payload = *(Payload*) rsc.data;
    
    send(&payload);
    free(rsc.data);
    delay(500);
  }
}

void send (const Payload* table) {
  digitalWrite(0, HIGH);
  String payload = String(table->temp, 4) + "/";
  payload += String(table->hum, 4) + "/";
  payload += String(table->lgp, 4) + "/";
  payload += String(table->co, 4) + "/";
  payload += String(table->smoke, 4) + "/";
  payload += String(table->pressu, 4) + "/";
  payload += String(table->alt, 4) + "/";
  payload += String(table->AcX) + "/";
  payload += String(table->AcY) + "/";
  payload += String(table->AcZ) + "/";
  payload += String(table->GyX) + "/";
  payload += String(table->GyY) + "/";
  payload += String(table->GyZ);
    Serial.println(payload);
//  Serial.write((const char*)table, size_gyro);  // 2 bytes.
}
