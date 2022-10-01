# ifndef MQ2_h
# define MQ2_h
# if ARDUINO >= 100
 # include "Arduino.h"
# else
 # include "WProgram.h"
# endif

class MQ2 {
  public: 
    MQ2(int pin);
    void begin();
    void close();
    float* read(bool print);
    float readLPG();
    float readCO();
    float readSmoke();
    float LPGCurve[3] = {2.3, 0.21, -0.47}; 
    float COCurve[3] = {2.3, 0.72, -0.34};   
    float SmokeCurve[3] = {2.3, 0.53, -0.44};                                                       
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
    
    float values[3];  // array with the measured values in the order: lpg, CO and smoke
    
    float MQRead();
    float MQGetPercentage(float *pcurve);
    float MQCalibration();
    float MQResistanceCalculation(int raw_adc);
    

    int lastReadTime = 0;
};

# endif
