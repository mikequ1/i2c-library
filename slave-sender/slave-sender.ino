#include <Wire.h>

//sample send values

int ss_sendint;
float ss_sendfloat;

float ss_float1 = 1.69;
float ss_float2 = 2.69;
int ss_int1 = 11;
int ss_int2 = 22;

byte ss_dir;

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); //receive direction on what kind of value to send back
  Wire.onRequest(requestEvent); //send back data
}

void loop() {
  Serial.begin(9600);
  delay(1000);
}

void requestEvent() {
  determineAction();
}

void receiveEvent() {
  ss_dir = Wire.read();
  Serial.print("receiving, direction is ");
  Serial.print(ss_dir);
  Serial.print(", sending value: ");
}

void determineAction(){
  switch (ss_dir) {
    case 1:
      ss_sendfloat = ss_float1;
      Serial.println(ss_sendfloat);
      isqc_write(ss_sendfloat);
      break;
    case 2:
      ss_sendfloat = ss_float2;
      Serial.println(ss_sendfloat);
      isqc_write(ss_sendfloat);
      break;
    case 3:
      ss_sendint = ss_int1;
      Serial.println(ss_sendint);
      isqc_write(ss_sendint);
      break;
    case 4:
      ss_sendint = ss_int2;
      Serial.println(ss_sendint);
      isqc_write(ss_sendint);
      break;
    default:
      break;
  }
}

template <typename T>
void isqc_write (T& value)
{
  byte data [sizeof value];
  byte p = (byte) &value; //changing value into an array of bytes
  for (int i = 0; i < sizeof value; i++){
    data[i] = (*p++);
  }
  Wire.write(data, sizeof value);
}
