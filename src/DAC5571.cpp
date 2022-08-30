#include "DAC5571.h"

DAC5571::DAC5571(uint8_t deviceAdress, float supplyvoltage, TwoWire *wire)
    {
        _address = deviceAdress;
        _wire = wire;
        _supplyvoltage = supplyvoltage;
    }

bool DAC5571::begin()
{   
    _wire->begin();
    if (! isConnected()) return false;
    return true;
}
bool DAC5571::isConnected()
{
  _wire->beginTransmission(_address);
   return ( _wire->endTransmission() == 0);
}
void DAC5571::setMode(int mode)
{
    operation_mode = mode;
}
void DAC5571::setVoltage(int number)
{
    voltage = number;
}
void DAC5571::send()
{
    byte first = buildMSB(operation_mode,voltage);
    byte second = buildLSB(voltage);

    _wire->beginTransmission(_address);
    _wire->write(first);
    _wire->write(second);
    _wire->endTransmission();
}
byte DAC5571::buildMSB(int operation_mode, int volatge)
{
    byte TEMP = 0;
    bitWrite(TEMP,5,bitRead(operation_mode,1));
    bitWrite(TEMP,4,bitRead(operation_mode,0));
    bitWrite(TEMP,3,bitRead(volatge,7));
    bitWrite(TEMP,2,bitRead(volatge,6));
    bitWrite(TEMP,1,bitRead(volatge,5));
    bitWrite(TEMP,0,bitRead(volatge,4));
    return TEMP;
}
byte DAC5571::buildLSB(int voltage)
{
    byte TEMP = 0;
    bitWrite(TEMP,7,bitRead(voltage,3));
    bitWrite(TEMP,6,bitRead(voltage,2));
    bitWrite(TEMP,5,bitRead(voltage,1));
    bitWrite(TEMP,4,bitRead(voltage,0));
    bitWrite(TEMP,3,0);
    bitWrite(TEMP,2,0);
    bitWrite(TEMP,1,0);
    bitWrite(TEMP,0,0);
    return TEMP;
}
byte DAC5571::convert_volt_number(float requestetvoltage)
{
    if(requestetvoltage > 0 && requestetvoltage <= _supplyvoltage)
    {
        float conversionfactor = _supplyvoltage / 256.0;
        byte temp = requestetvoltage / conversionfactor;
        return temp;
    }
    return 0;    
}