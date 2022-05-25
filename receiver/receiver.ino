/*
 * LoRa E32-TTL-100
 * Start device, reset or write to the Serial to send a message.
 * https://www.mischianti.org/2019/10/15/lora-e32-device-for-arduino-esp32-or-esp8266-specs-and-basic-usage-part-1/
 *
 * E32-TTL-100----- Arduino UNO
 * M0         ----- PIN 6
 * M1         ----- PIN 7
 * TX         ----- PIN 2 (PullUP)
 * RX         ----- PIN 3 (PullUP & Voltage divider)
 * AUX        ----- PIN 5
 * VCC        ----- 3.3v/5v
 * GND        ----- GND
 *
 */
#include "Arduino.h"
#include "LoRa_E32.h"

// ---------- Arduino pins --------------
//LoRa_E32 e32ttl(2, 3, 5, 7, 6);
LoRa_E32 e32ttl100(2, 3, 5, 7, 6); 
// -------------------------------------

struct Payload {
  float sensor1;
  float sensor2;
  float sensor3;
  int count_message;
};

int size_gyro = sizeof(struct Payload);


void setup() {
  Serial.begin(9600);
  delay(1000);

//  Serial.println("############################### STARTING RECEIVER ###############################");

  e32ttl100.begin();
  delay(500);

  ResponseStructContainer c;
  ResponseStructContainer cMi;
  
  c = e32ttl100.getConfiguration();
  cMi = e32ttl100.getModuleInformation();
  
  Configuration configuration = *(Configuration*) c.data;
  ModuleInformation moduleInformation = *(ModuleInformation*)cMi.data;

//  setup_lora(configuration);
//  printParameters(configuration);
//  printModuleInformation(moduleInformation);
  c.close();
  cMi.close();

//  Serial.println("############################### RECEIVER STARTED ################################");
}

void loop() {

//  Serial.println("teste");
//  delay(1000);
 
  if (e32ttl100.available() > 1){
    ResponseStructContainer rsc = e32ttl100.receiveMessage(sizeof(Payload));
    
    struct Payload payload = *(Payload*) rsc.data;
    send(&payload);
//    Serial.println("----------------------------------- MESSAGE -------------------------------------");
//    Serial.print("Amount messages -> ");
//    Serial.print(payload.count_message);
//    Serial.print("\nSensor 1 -> ");
//    Serial.print(payload.sensor1);
//    Serial.print("\nSensor 2 -> ");
//    Serial.print(payload.sensor2);
//    Serial.print("\nSensor 3 -> ");
//    Serial.print(payload.sensor3);
//    Serial.println("\n----------------------------------- MESSAGE -------------------------------------");
    free(rsc.data);
  }
}

void send (const Payload* table)
{
  Serial.write((const char*)table, size_gyro);  // 2 bytes.
}
