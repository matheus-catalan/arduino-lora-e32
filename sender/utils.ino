
void printConfigStatus(struct ResponseStatus rs){
//  if(LOG_LEVEL == 0) {
    Serial.println("---------------------------------------------------------------------------------");
    Serial.println("** STATUS **");
    Serial.println("Response Status: " + rs.getResponseDescription());
    Serial.print("Response code: ");
    Serial.print(rs.code);
    Serial.println("\n---------------------------------------------------------------------------------\n");
//  }
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
//  if ( LOG_LEVEL == 0 ){
    Serial.println("---------------------------------------------------------------------------------");
    Serial.println("** MODULE INFORMATIONS **");
  
    Serial.print(F("HEAD BIN: "));  Serial.print(moduleInformation.HEAD, BIN);Serial.print(" ");Serial.print(moduleInformation.HEAD, DEC);Serial.print(" ");Serial.println(moduleInformation.HEAD, HEX);
  
    Serial.print(F("Freq.: "));  Serial.println(moduleInformation.frequency, HEX);
    Serial.print(F("Version  : "));  Serial.println(moduleInformation.version, HEX);
    Serial.print(F("Features : "));  Serial.println(moduleInformation.features, HEX);
    Serial.println("---------------------------------------------------------------------------------\n");
//  }
}

void printConfigMqStatus() {
  if(LOG_LEVEL == 0) {
//    Serial.println("---------------------------------------------------------------------------------");
//    Serial.println("** STATUS MQ-2 **");
//    status_mq2 ? Serial.println("Response Status: Success") : Serial.println("Response Status: Failed");
//    status_mq2 ? Serial.println("Response Code: 1") : Serial.println("Response Code: 0");;
//    Serial.println("---------------------------------------------------------------------------------\n");
  }
}

void printModuleInformationMq() {
//  Serial.println("---------------------------------------------------------------------------------");
//  Serial.println("** MODULE INFORMATIONS **");
//  Serial.println("Ro: " + String(mq2.Ro) + " kohm");
//  Serial.println("RL value: " + String(mq2.RL_VALUE));
//  Serial.println("RO clean air factor: " + String(mq2.RO_CLEAN_AIR_FACTOR));
//  Serial.println("Calibration sample times: " + String(mq2.CALIBARAION_SAMPLE_TIMES) + "ms");
//  Serial.println("Calibration sample interval: " + String(mq2.CALIBRATION_SAMPLE_INTERVAL));
//  Serial.println("Read sample times: " + String(mq2.READ_SAMPLE_TIMES));
//  Serial.println("Read sample interval: " + String(mq2.READ_SAMPLE_INTERVAL) + "ms");
//  
//  Serial.println("---------------------------------------------------------------------------------\n");
}

void printConfigDhtStatus() {
//  if(LOG_LEVEL == 0) {
//    Serial.println("---------------------------------------------------------------------------------");
//    Serial.println("** STATUS DHT22 **");
//    status_dht22 ? Serial.println("Response Status: Success") : Serial.println("Response Status: Failed");
//    status_dht22 ? Serial.println("Response Code: 1") : Serial.println("Response Code: 0");;
//    Serial.println("---------------------------------------------------------------------------------\n");
//  }
}


void printModuleInformationDht(float h, float t, float f, float hif, float hic) {
//  Serial.println("---------------------------------------------------------------------------------");
//  Serial.println("** MODULE INFORMATIONS **");
//  Serial.println("Humidity: " + String(h) + "%");
//  Serial.println("Temperature: " + String(t) + "°C");
//  Serial.println("Heat index: " + String(hic) + "°C " + String(hif) + "°F");
//  Serial.println("---------------------------------------------------------------------------------\n");
}
