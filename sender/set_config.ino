void setup_dht22(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);


  if (isnan(h) == false || isnan(t) == false || isnan(f) == false) {
    status_dht22 = true;  
  }
}

void setup_mq2() {
  status_mq2 = mq2.checkCalibration();             
}


void setup_lora() { 
  ResponseStructContainer c;
  ResponseStructContainer cMi;
  
  c = e32ttl100.getConfiguration();
  cMi = e32ttl100.getModuleInformation();
  
  Configuration configuration = *(Configuration*) c.data;
  ModuleInformation moduleInformation = *(ModuleInformation*)cMi.data;

  configuration.ADDL = 0x01;
  configuration.ADDH = 0x00;
  configuration.CHAN = 0x04;

  configuration.OPTION.fec = FEC_0_OFF;
  configuration.OPTION.fixedTransmission = FT_FIXED_TRANSMISSION;
  configuration.OPTION.ioDriveMode = IO_D_MODE_OPEN_COLLECTOR;
  configuration.OPTION.transmissionPower = POWER_20;
  configuration.OPTION.wirelessWakeupTime = WAKE_UP_250;

  configuration.SPED.airDataRate =  AIR_DATA_RATE_010_24;
  configuration.SPED.uartBaudRate = UART_BPS_9600;
  configuration.SPED.uartParity = MODE_00_8N1;

  ResponseStatus rs = e32ttl100.setConfiguration(configuration, WRITE_CFG_PWR_DWN_LOSE);
  
  if(rs.code != 1) {
    status_lora = true;
  }
  
  printConfigStatus(rs);
  printParameters(configuration);
  printModuleInformation(moduleInformation);
  ResponseStatus resetModule();

  c.close();
  cMi.close();
}
