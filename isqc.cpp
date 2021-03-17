#include "isqc.h"

void isqc_master::sendDirection(uint8_t var, int s) 
{
    Wire.beginTransmission(SLAVE_ADDRESS);
    Wire.write(var);
    Wire.endTransmission();
}

//supports every primitive data type
template <typename T>
void isqc_master::isqc_read(T& value, int s)
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


//supports every primitive data type
template <typename T>
void isqc_slave::isqc_write(T& value)
{
    byte data[sizeof value];
    byte* p = (byte)&value; //changing value into an array of bytes
    for (int i = 0; i < sizeof value; i++) 
    {
        data[i] = (*p++);
    }
    Wire.write(data, sizeof value);
}


/*
Future Additions:

-test if the current program works

-isqc_write with command repeats appended to data
-isqc read that separates command and data

-implement instant READ and SEND BACK

-enumerate features to allow every instance of the 1 byte command to a user-defined instruction

-other features to be listed
*/