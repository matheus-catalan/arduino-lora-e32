/*
 * LoRa E32-TTL-100
 * Set configuration.
 * https://www.mischianti.org/2019/10/29/lora-e32-device-for-arduino-esp32-or-esp8266-configuration-part-3/
 *
 * E32-TTL-100----- Arduino UNO
 * M0         ----- 3.3v
 * M1         ----- 3.3v
 * TX         ----- PIN 2 (PullUP)
 * RX         ----- PIN 3 (PullUP & Voltage divider)
 * AUX        ----- Not connected
 * VCC        ----- 3.3v/5v
 * GND        ----- GND
 *
 */
#include "Arduino.h"
#include "LoRa_E32.h"
//tx-rx-aux-m0-m1

LoRa_E32 e32ttl100(2, 3, 5, 6, 7);
void printParameters(struct Configuration configuration);
void printModuleInformation(struct ModuleInformation moduleInformation);

void setup() {
	Serial.begin(9600);
	delay(500);

	// Startup all pins and UART
	e32ttl100.begin();

	ResponseStructContainer c;
	c = e32ttl100.getConfiguration();
	// It's important get configuration pointer before all other operation
	Configuration configuration = *(Configuration*) c.data;
	Serial.println(c.status.getResponseDescription());
	Serial.println(c.status.code);

	printParameters(configuration);
//	configuration.ADDL = 0x0;
//	configuration.ADDH = 0x1;
//	configuration.CHAN = 0x17;
//
//	configuration.OPTION.fec = FEC_0_OFF;
//	configuration.OPTION.fixedTransmission = FT_TRANSPARENT_TRANSMISSION;
//	configuration.OPTION.ioDriveMode = IO_D_MODE_PUSH_PULLS_PULL_UPS;
//	configuration.OPTION.transmissionPower = POWER_20; //default
//	configuration.OPTION.wirelessWakeupTime = WAKE_UP_250; //default
//
//	configuration.SPED.airDataRate =  AIR_DATA_RATE_010_24; //default
//	configuration.SPED.uartBaudRate = UART_BPS_9600; //default
//	configuration.SPED.uartParity = MODE_00_8N1; //default

   configuration.ADDL = 0x01;
   configuration.ADDH = 0x00;
   configuration.CHAN = 0x04;

  configuration.OPTION.fec = FEC_0_OFF;
  configuration.OPTION.fixedTransmission = FT_FIXED_TRANSMISSION;
  configuration.OPTION.ioDriveMode = IO_D_MODE_PUSH_PULLS_PULL_UPS;
  configuration.OPTION.transmissionPower = POWER_20; //default
  configuration.OPTION.wirelessWakeupTime = WAKE_UP_250; //default

  configuration.SPED.airDataRate =  AIR_DATA_RATE_010_24; //default
  configuration.SPED.uartBaudRate = UART_BPS_9600; //default
  configuration.SPED.uartParity = MODE_00_8N1; //default


	// Set configuration changed and set to not hold the configuration
	ResponseStatus rs = e32ttl100.setConfiguration(configuration);
	Serial.println(rs.getResponseDescription());
	Serial.println(rs.code);
	printParameters(configuration);
	c.close();
}

void loop() {
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
  struct Payload payload;
  ResponseStatus rs = e32ttl100.sendFixedMessage(0, 3, 0x04, &payload, sizeof(Payload));
  Serial.println("enviou essa caralha");
}

void printParameters(struct Configuration configuration) {
	Serial.println("----------------------------------------");

	Serial.print(F("HEAD : "));  Serial.print(configuration.HEAD, BIN);Serial.print(" ");Serial.print(configuration.HEAD, DEC);Serial.print(" ");Serial.println(configuration.HEAD, HEX);
	Serial.println(F(" "));
	Serial.print(F("AddH : "));  Serial.println(configuration.ADDH, BIN);
	Serial.print(F("AddL : "));  Serial.println(configuration.ADDL, BIN);
	Serial.print(F("Chan : "));  Serial.print(configuration.CHAN, DEC); Serial.print(" -> "); Serial.println(configuration.getChannelDescription());
	Serial.println(F(" "));
	Serial.print(F("SpeedParityBit     : "));  Serial.print(configuration.SPED.uartParity, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTParityDescription());
	Serial.print(F("SpeedUARTDatte  : "));  Serial.print(configuration.SPED.uartBaudRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTBaudRate());
	Serial.print(F("SpeedAirDataRate   : "));  Serial.print(configuration.SPED.airDataRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getAirDataRate());

	Serial.print(F("OptionTrans        : "));  Serial.print(configuration.OPTION.fixedTransmission, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getFixedTransmissionDescription());
	Serial.print(F("OptionPullup       : "));  Serial.print(configuration.OPTION.ioDriveMode, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getIODroveModeDescription());
	Serial.print(F("OptionWakeup       : "));  Serial.print(configuration.OPTION.wirelessWakeupTime, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getWirelessWakeUPTimeDescription());
	Serial.print(F("OptionFEC          : "));  Serial.print(configuration.OPTION.fec, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getFECDescription());
	Serial.print(F("OptionPower        : "));  Serial.print(configuration.OPTION.transmissionPower, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getTransmissionPowerDescription());

	Serial.println("----------------------------------------");
 
  

}
