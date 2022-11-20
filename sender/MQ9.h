#ifndef MQ9_h
#define MQ9_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class MQ9
{
public:
  MQ9(int pin);
  void begin();
  void close();
  float *read(bool print);
  float readCH4();
//  float CH4Curve[3] = {3.14, 0.53, -1.30};
  float CH4Curve[3] = {2.3, 0.53, -1.30};
  float Ro = -1.0;
  bool checkCalibration();
  float RL_VALUE = 5.0;
  float RO_CLEAN_AIR_FACTOR = 9.83;
  int CALIBARAION_SAMPLE_TIMES = 10;
  int CALIBRATION_SAMPLE_INTERVAL = 50;
  int READ_SAMPLE_TIMES = 5;
  int READ_SAMPLE_INTERVAL = 50;
  int READ_DELAY = 10000;

private:
  int _pin;

  float values[3];

  float MQRead();
  float MQGetPercentage(float *pcurve);
  float MQCalibration();
  float MQResistanceCalculation(int raw_adc);

  int lastReadTime = 0;
};

#endif
