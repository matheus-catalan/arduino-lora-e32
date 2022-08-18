void setup_lora() { 
  ResponseStructContainer c;
  ResponseStructContainer cMi;
  
  c = e32ttl100.getConfiguration();
  cMi = e32ttl100.getModuleInformation();
  
  Configuration configuration = *(Configuration*) c.data;
  ModuleInformation moduleInformation = *(ModuleInformation*)cMi.data;

  configuration.ADDL = 0x03;
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

  ResponseStatus rs = e32ttl100.setConfiguration(configuration, WRITE_CFG_PWR_DWN_SAVE);

  
  printConfigStatus(rs);
  printParameters(configuration);
  printModuleInformation(moduleInformation);

  c.close();
  cMi.close();
  if(LOG_LEVEL == 0 ) Serial.println("############################### RECEIVER STARTED ################################");
}
