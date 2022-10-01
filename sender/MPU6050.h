# ifndef MPU6050_h
# define MPU6050_h
# if ARDUINO >= 100
 # include "Arduino.h"
# else
 # include "WProgram.h"
# endif

class MPU6050 {
  public: 
    MPU6050(int pin);
    void begin();
    void update();
    boolean checkCalibration();
    int getAx();
    int getAy();
    int getAz();
    int getGx();
    int getGy();
    int getGz();
  private:
    int _pin;
    int ax;
    int ay;
    int az;
    int tmp;
    int gx;
    int gy;
    int gz;
};

# endif
