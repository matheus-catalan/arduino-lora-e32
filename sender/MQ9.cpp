#include "Arduino.h"
#include "MQ9.h"

MQ9::MQ9(int pin)
{
  _pin = pin;
  Ro = -1.0;
}

void MQ9::begin()
{
  Ro = MQCalibration();
}

void MQ9::close()
{
  Ro = -1.0;
  values[0] = 0.0;
}

bool MQ9::checkCalibration()
{
  if (Ro < 0.0)
  {
    return false;
  }

  return true;
}

float *MQ9::read(bool print)
{
  if (!checkCalibration())
    return NULL;

  values[0] = MQGetPercentage(CH4Curve);

  lastReadTime = millis();

  return values;
}

float MQ9::readCH4(){
  if (!checkCalibration()) return 0.0;

    if (millis() < (lastReadTime + READ_DELAY) && values[0] > 0)
        return values[0];
    else
        return MQGetPercentage(CH4Curve);
}

float MQ9::MQResistanceCalculation(int raw_adc)
{
  float flt_adc = (float)raw_adc;
  return RL_VALUE * (1023.0 - flt_adc) / flt_adc;
}

float MQ9::MQCalibration()
{
  float val = 0.0;

  for (int i = 0; i < CALIBARAION_SAMPLE_TIMES; i++)
  {
    val += MQResistanceCalculation(analogRead(_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }

  val = val / ((float)CALIBARAION_SAMPLE_TIMES);
  val = val / RO_CLEAN_AIR_FACTOR;

  return val;
}

float MQ9::MQRead()
{
  float rs = 0.0;

  for (int i = 0; i < READ_SAMPLE_TIMES; i++)
  {
    rs += MQResistanceCalculation(analogRead(_pin));
    delay(READ_SAMPLE_INTERVAL);
  }

  return rs / ((float)READ_SAMPLE_TIMES);
}

float MQ9::MQGetPercentage(float *pcurve)
{
  float rs_ro_ratio = MQRead() / Ro;
  return pow(10.0, ((log(rs_ro_ratio) - pcurve[1]) / pcurve[2]) + pcurve[0]);
}
