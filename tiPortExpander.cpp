/*
  tiPortExpander.cpp - Library for interfacing with pca9563 and tca9534 (first 4 pins)  i2c port expander with RFduino
  Created by Eric O'Neill, June 9, 2015
  
*/

#include "Arduino.h" // do i need this with rfduino?
#include "Wire.h"
#include "tiPortExpander.h"

// default constructor automatically sets address to PCA9563 address
TiPortExpander::TiPortExpander(){
	_outputRegVal = 0x00;
	_inputRegVal = 0x00;
	_deviceAddress = PCA9563_ADDRESS;
}

// for configuring your own address with the tca9534
TiPortExpander::TiPortExpander(int address){
	_outputRegVal = 0x00;
	_inputRegVal = 0x00;
	_deviceAddress = address;	
}

void TiPortExpander::configurePins(int pin0, int pin1, int pin2, int pin3){
	_pinConfig[0] = pin0; _pinConfig[1] = pin1; _pinConfig[2] = pin2; _pinConfig[3] = pin3;
	Wire.beginTransmission(_deviceAddress);
	Wire.write(registers_t.EXPANDER_REGISTER_CONFIGURATION);
	byte configByte = 0x00;
	if(pin0){
		configByte |= 0x01;
	}
	if(pin1){
		configByte |= 0x02;
	}
	if(pin2){
		configByte |= 0x04;
	}
	if(pin3){
		configByte |= 0x08;
	}
	Wire.write(configByte);
	Wire.endTransmission();
}

int TiPortExpander::writePin(int pin, bool val){
	if(_pinConfig[pin] == 1){
		return -1; //pin config is set to input
	}
	Wire.beginTransmission(_deviceAddress);
	Wire.write(registers_t.EXPANDER_REGISTER_OUTPUT);
	//set bit at pin
	if(val){
		_outputRegVal |= 1 << pin;
	}
	//clear bit at pin
	else{
		_outputRegVal &= ~(1 << pin);
	}
	Wire.write(_outputRegVal);
	if(Wire.endTransmission() == 0){
		return -1;
	}
	else{
		return 1;
	}
}

int readPin(int pin){
	if(_pinConfig[pin] == 0){
		return -1;
	}
	Wire.beginTransmission(_deviceAddress);
	Wire.write(registers_t.EXPANDER_REGISTER_INPUT);

	if(Wire.endTransmission() == 0){
		_inputRegVal = Wire.requestFrom(_deviceAddress, 1);
		return (_inputRegVal >> pin) & 0x01;
	}
	else{
		return -1;
	}

}

