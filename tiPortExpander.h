/*
  pca9563.h - Library for interfacing with pca9563 i2c port expander with RFduino
  Created by Eric O'Neill, June 9, 2015
  
*/

#ifndef tiPortExpander_h
#define tiPortExpander_h

#include "Arduino.h" // do i need this with rfduino?
#include "Wire.h"

#define PCA9563_ADDRESS 65 // 7 bit address to be used with begintransmission


typedef enum{
  EXPANDER_REGISTER_INPUT = 0x00,
  EXPANDER_REGISTER_OUTPUT = 0x01,
  EXPANDER_REGISTER_POLARITY_INVERSION = 0x02, //don't really know what this does
  EXPANDER_REGISTER_CONFIGURATION = 0x03,
} registers_t;

class TiPortExpander
{
  public:
    TiPortExpander();
    TiPortExpander(int address);
    void configurePins(int pin0, int pin1, int pin2, int pin3); // 0 for write, 1 for read
    int writePin(int pin, bool val); // return ack status from endTransmission()
    int readPin(int pin) // return data
  
  private:

    int [4] _pinConfig; // pin configurations (input/output)
    byte _outputRegVal;
    byte _inputRegVal;
    int _deviceAdress;
};

#endif