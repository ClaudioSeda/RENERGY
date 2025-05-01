#ifndef RENERGY_H
#define RENERGY_H

#include <Arduino.h>

class RENERGY {
public:
    RENERGY();
    void begin();
    float getVoltage();
    float getCurrent();
    float getApparentPower();
    float getRealPower();
    float getPowerFactor();
    float getFrequency();
};

#endif // RENERGY_H
