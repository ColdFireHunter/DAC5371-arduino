#ifndef _DAC5571_h
#define _DAC5571_h

#include <Arduino.h>
#include <Wire.h>

#define DAC5571_NORMAL 0
#define DAC5571_1K 1
#define DAC5571_100K 2
#define DAC5571_HI 3

class DAC5571{
    public:
        explicit DAC5571(uint8_t deviceAdress, float supplyvoltage, TwoWire *wire = &Wire);
        bool begin();
        void setMode(int mode);
        void setVoltage(int number);
        void send();
        byte convert_volt_number(float requestetvoltage);
    private:
        uint8_t _address;   
        TwoWire* _wire; 
        float _supplyvoltage;
        int operation_mode = 0;
        int voltage = 0;
        bool isConnected();
        byte buildMSB(int operation_mode, int volatge);
        byte buildLSB(int volatge);
};

#endif