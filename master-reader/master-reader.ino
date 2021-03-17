#include <Wire.h>

const int SLAVE_ADDRESS = 8;

//1 byte: byte, char, int8_t, uint8_t
//2 byte: short, int16_t, uint16_t
//4 byte: int, float, long, int32_t, uint32_t
//8 byte: double, int64_t, uint64_t

//sample receive values
volatile int mr_int;
volatile char mr_char;
volatile float mr_float;
byte mr_dir;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  sendDirection(random(1, 5));
   
  //DESIGNATE what direction corresponds to which actions
  if (mr_dir == 1 || mr_dir == 2)
    isqc_read(mr_float);
  else if (mr_dir == 3 || mr_dir == 4)
    isqc_read(mr_int);
}





////////////////////
//HELPER FUNCTIONS//
////////////////////

void sendDirection(byte var){
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(var);
  Wire.endTransmission();
  mr_dir = var;
}


template <typename T> 
void isqc_read(T& value){
  Wire.requestFrom(SLAVE_ADDRESS, sizeof value);
  byte * p = (byte*) &value;
  for (int i = 0; i < sizeof value; i++){
    *p++ = Wire.read();
  }
  Serial.println(value); 
}


template <typename T> 
T isqc_readback(){
  byte dir = Wire.read();
  T data = determineType(dir);
  byte * p = (byte*) &data;
  for (int i = 0; i < sizeof data; i++){
    *p++ = Wire.read();
  }
  Serial.println(data); 
  return data;
}


template <typename T> 
T determineCmd(byte dir){
  switch (dir){
    case 1:
    case 2:
      char b1Cmd;
      return b1Cmd;
    case 3:
    case 4:
      int b2Cmd;
      return b2Cmd;
    default:
      break;
  }
}
