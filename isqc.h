#ifndef Isqc_h
#define Isqc_h

#include <Arduino.h>
#include <Wire.h>

void sendDirection(byte var) {
    Wire.beginTransmission(SLAVE_ADDRESS);
    Wire.write(var);
    Wire.endTransmission();
    mr_dir = var;
}

template <typename T>
void isqc_read(T& value)
{
    Wire.requestFrom(SLAVE_ADDRESS, sizeof value);
    byte* p = (byte*)&value;
    for (int i = 0; i < sizeof value; i++) {
        *p++ = Wire.read();
    }
    Serial.println(value);
}

template <typename T>
void isqc_write(T& value)
{
    byte data[sizeof value];
    byte p = (byte)&value; //changing value into an array of bytes
    for (int i = 0; i < sizeof value; i++) {
        data[i] = (*p++);
    }
    Wire.write(data, sizeof value);
}

#endif