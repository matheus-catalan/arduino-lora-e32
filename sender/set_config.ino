void setup_lora(struct Configuration configuration) {
  Serial.println("\n##################################### Setup #####################################");
 
  configuration.ADDL = 0x0;
  configuration.ADDH = 0x1;
  configuration.CHAN = 0x17;

  configuration.OPTION.fec = FEC_0_OFF;
  configuration.OPTION.fixedTransmission = FT_TRANSPARENT_TRANSMISSION;
  configuration.OPTION.ioDriveMode = IO_D_MODE_PUSH_PULLS_PULL_UPS;
  configuration.OPTION.transmissionPower = POWER_20; //default
  configuration.OPTION.wirelessWakeupTime = WAKE_UP_250; //default

  configuration.SPED.airDataRate =  AIR_DATA_RATE_010_24; //default
  configuration.SPED.uartBaudRate = UART_BPS_9600; //default
  configuration.SPED.uartParity = MODE_00_8N1; //default

  ResponseStatus rs = e32ttl100.setConfiguration(configuration, WRITE_CFG_PWR_DWN_LOSE);
  Serial.println("Response Status: " + rs.getResponseDescription());
  Serial.print("Response code: ");
  Serial.print(rs.code);
  

  Serial.println("\n#################################################################################\n");

}
