void signal_start(int pin_buzzer = 12){
  pinMode(pin_buzzer, OUTPUT);
  digitalWrite(pin_buzzer, LOW);
  delay(70);
  digitalWrite(pin_buzzer, HIGH);
  delay(70);
  digitalWrite(pin_buzzer, LOW);
  delay(70);
  digitalWrite(pin_buzzer, HIGH);
  delay(70);
  digitalWrite(pin_buzzer, LOW);
}

void singnal_status() {
  digitalWrite(12, LOW);
  if(status_lora == false) Serial.println("Module LORA-E32 not working");
  if(status_mq2 == false) Serial.println("Module MQ2 not working");
  if(status_dht22 == false) Serial.println("Module DHT22 not working");
  if(status_bmp == false) Serial.println("Module BMP not working");
  if ( LOG_LEVEL > 0 && status_lora == false) {
    digitalWrite(12, HIGH);
    delay(500);
    digitalWrite(12, LOW);
  }
}

void printConfigStatus(struct ResponseStatus rs){
    Serial.println("---------------------------------------------------------------------------------");
    Serial.println("** STATUS **");
    Serial.println("Response Status: " + rs.getResponseDescription());
    Serial.print("Response code: ");
    Serial.print(rs.code);
    Serial.println("\n---------------------------------------------------------------------------------\n");
}

void printParameters(struct Configuration configuration) {
//  if ( LOG_LEVEL == 0 ){
    Serial.println("---------------------------------------------------------------------------------");
    Serial.println("** PARAMETERS **");
    
    Serial.print(F("HEAD BIN: "));  Serial.print(configuration.HEAD, BIN); Serial.print(" "); Serial.print(configuration.HEAD, DEC); Serial.print(" "); Serial.println(configuration.HEAD, HEX);
    Serial.println(F(" "));
    Serial.print(F("AddH BIN: "));  Serial.println(configuration.ADDH, BIN);
    Serial.print(F("AddL BIN: "));  Serial.println(configuration.ADDL, BIN);
    Serial.print(F("Chan BIN: "));  Serial.print(configuration.CHAN, DEC); Serial.print(" -> "); Serial.println(configuration.getChannelDescription());
    Serial.println(F(" "));
    Serial.print(F("SpeedParityBit BIN    : "));  Serial.print(configuration.SPED.uartParity, BIN); Serial.print(" -> "); Serial.println(configuration.SPED.getUARTParityDescription());
    Serial.print(F("SpeedUARTDataRate BIN : "));  Serial.print(configuration.SPED.uartBaudRate, BIN); Serial.print(" -> "); Serial.println(configuration.SPED.getUARTBaudRate());
    Serial.print(F("SpeedAirDataRate BIN  : "));  Serial.print(configuration.SPED.airDataRate, BIN); Serial.print(" -> "); Serial.println(configuration.SPED.getAirDataRate());
  
    Serial.print(F("OptionTrans BIN       : "));  Serial.print(configuration.OPTION.fixedTransmission, BIN); Serial.print(" -> "); Serial.println(configuration.OPTION.getFixedTransmissionDescription());
    Serial.print(F("OptionPullup BIN      : "));  Serial.print(configuration.OPTION.ioDriveMode, BIN); Serial.print(" -> "); Serial.println(configuration.OPTION.getIODroveModeDescription());
    Serial.print(F("OptionWakeup BIN      : "));  Serial.print(configuration.OPTION.wirelessWakeupTime, BIN); Serial.print(" -> "); Serial.println(configuration.OPTION.getWirelessWakeUPTimeDescription());
    Serial.print(F("OptionFEC BIN         : "));  Serial.print(configuration.OPTION.fec, BIN); Serial.print(" -> "); Serial.println(configuration.OPTION.getFECDescription());
    Serial.print(F("OptionPower BIN       : "));  Serial.print(configuration.OPTION.transmissionPower, BIN); Serial.print(" -> "); Serial.println(configuration.OPTION.getTransmissionPowerDescription());
    
    Serial.println("---------------------------------------------------------------------------------\n");
//  }
}
void printModuleInformation(struct ModuleInformation moduleInformation) {
    Serial.println("---------------------------------------------------------------------------------");
    Serial.println("** MODULE INFORMATIONS **");
  
    Serial.print(F("HEAD BIN: "));  Serial.print(moduleInformation.HEAD, BIN);Serial.print(" ");Serial.print(moduleInformation.HEAD, DEC);Serial.print(" ");Serial.println(moduleInformation.HEAD, HEX);
  
    Serial.print(F("Freq.: "));  Serial.println(moduleInformation.frequency, HEX);
    Serial.print(F("Version  : "));  Serial.println(moduleInformation.version, HEX);
    Serial.print(F("Features : "));  Serial.println(moduleInformation.features, HEX);
    Serial.println("---------------------------------------------------------------------------------\n");
}
