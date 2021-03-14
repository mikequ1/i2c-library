#ifndef Isqc_h
#define Isqc_h

#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>

template <typename T>
class isqc_master
{
public:
    void sendDirection(uint8_t var, isqc_slave s);
    void isqc_read(T& value, isqc_slave s);
private:
};


template <typename T>
class isqc_slave
{
public:
    isqc_slave(int addr);
    void isqc_write(T& value);

    void setAddr(int addr);
    int getAddr() const;
private:
    int m_addr;
    int m_dir;
};



#endif