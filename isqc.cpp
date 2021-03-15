#include "isqc.h"


void isqc_master::sendDirection(byte var, isqc_slave s) 
{
    Wire.beginTransmission(SLAVE_ADDRESS);
    Wire.write(var);
    Wire.endTransmission();
}


//supports every primitive data type
template <typename T>
void isqc_master::isqc_read(T& value, isqc_slave s)
{
    Wire.requestFrom(s.getAddr(), sizeof value);
    byte* p = (byte*)&value; //changing value into an array of bytes
    for (int i = 0; i < sizeof value; i++) 
    {
        *p++ = Wire.read();
    }
    Serial.println(value); //prints value, will delete later
}


isqc_slave::isqc_slave(int addr)
{
    m_addr = addr;
}


template <typename T>
void isqc_slave::isqc_write(T& value)
{
    byte data[sizeof value];
    byte p = (byte)&value; //changing value into an array of bytes
    for (int i = 0; i < sizeof value; i++) 
    {
        data[i] = (*p++);
    }
    Wire.write(data, sizeof value);
}