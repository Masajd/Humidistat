/*
  Humidistat.CPP - Library for creating a Humidistat extractor fan
  Created by Sam Dicker on 10.7.2024
*/

#include "Arduino.h"
#include "Humidistat.h"
#include "DHT.h"

/**
 * Default Constructor for producing a Humidistat. The DHT module is set to Pin 1 and is assumed to be a DHT11 Type. The motor is set to Pin 2.
 * The minimum humidity is set to 20% and the maximum is set to 80% as these are the minimum and maximum values of the DHT modules.
 * The minimum temperature is set to 0c and the maximum is set to 50c for the same reason as above.
 * The fan speed is set to 255 (maximum speed) and the Humidistat is unnamed.
 */
Humidistat::Humidistat(){
  DHTPin = 1;
  DHTType = DHT11;
  MotorPin = 2;
  
  minHumidity = 20;
  maxHumidity = 80;

  minTemp = 0;
  maxTemp = 50;

  fanSpeed = 255;

  cooldownTime = 10000;
  Name = "Unnamed Humidistat";

  getHumidity();
  getTemperature();

  initDHT();
  initMotor();
}

/**
 * Constructor for producing a Humidistat from 3 arguments. The DHT module is set to to Pin DHTPin and is assumed to be a DHT11 Type.
 * The Motor is set to Pin MotorPin on the Ardiuno.
 * The minimum humidity is set to 20% and the maximum is set to 80% as these are the minimum and maximum values of the DHT modules.
 * The minimum temperature is set to 0c and the maximum is set to 50c for the same reason as above.
 * The fan speed is set to 255 (maximum speed) and the Humidistat is named Name.
** @param int DHTPin, Pin that DHT Module is assigned to on the Arduino.
** @param int MotorPin, Pin that the motor is assigned to on the Arduino. 
** @param String Name, the name of the Humidistat e.g. Basement Humidistat
**/
Humidistat::Humidistat(DHTPin,MotorPin,Name){
  this->DHTPin = DHTPin;
  DHTType = DHT11;
  this->MotorPin = MotorPin;
  
  minHumidity = 20;
  maxHumidity = 80;

  minTemp = 0;
  maxTemp = 50;

  fanSpeed = 255;

  cooldownTime = 10000;
  this->Name = Name;

  getHumidity();
  getTemperature();

  initDHT();
  initMotor();
}

/**
 * Constructor for producing a Humidistat from 4 arguments. The DHT module is set to to Pin DHTPin and is set to be a DHTType Type.
 * The Motor is set to Pin MotorPin on the Ardiuno.
 * The minimum humidity is set to 20% and the maximum is set to 80% as these are the minimum and maximum values of the DHT modules.
 * The minimum temperature is set to 0c and the maximum is set to 50c for the same reason as above.
 * The fan speed is set to 255 (maximum speed) and the Humidistat is named Name.
** @param int DHTPin, Pin that DHT Module is assigned to on the Arduino.
** @param int MotorPin, Pin that the motor is assigned to on the Arduino. 
** @param String DHTType, The type of DHT module connected to the Arduino e.g. DHT11.
** @param String Name, the name of the Humidistat e.g. Basement Humidistat.
**/
Humidistat::Humidistat(DHTPin,MotorPin,DHTType,Name){
  this->DHTPin = DHTPin;
  this->DHTType = DHTType;
  this->MotorPin = MotorPin;
  
  minHumidity = 20;
  maxHumidity = 80;

  minTemp = 0;
  maxTemp = 50;

  fanSpeed = 255;

  cooldownTime = 10000;
  this->Name = Name;

  getHumidity();
  getTemperature();

  initDHT();
  initMotor();
}

/**
 * Constructor for producing a Humidistat from 6 arguments. The DHT module is set to to Pin DHTPin and is set to be a DHTType Type.
 * The Motor is set to Pin MotorPin on the Ardiuno.
 * The minimum humidity is set to minHumidity and the maximum is set to maxHumidity. 
 * If the minHumidity or the maxHumidity exceed the DHT modules maximum or minimum humidity values then minHumidity and maxHumidity are changed to these maxiumum/minimum values.
 * The minimum temperature is set to 0c and the maximum is set to 50c as these are the minimum and maximum values of the DHT modules.
 * The fan speed is set to 255 (maximum speed) and the Humidistat is named Name.
** @param int DHTPin, Pin that DHT Module is assigned to on the Arduino.
** @param int MotorPin, Pin that the motor is assigned to on the Arduino. 
** @param String DHTType, The type of DHT module connected to the Arduino e.g. DHT11.
** @param float minHumidity, The minimum humidity reading on the DHT module.
** @param float maxHumidity, The maximum humidity reading on the DHT module.
** @param String Name, the name of the Humidistat e.g. Basement Humidistat.
**/
Humidistat::Humidistat(DHTPin,MotorPin,DHTType,minHumidity,maxHumidity,Name){
  this->DHTPin = DHTPin;
  this->DHTType = DHTType;
  this->MotorPin = MotorPin;
  
  if(minHumidity<20 || minHumidity>maxHumidity){
    minHumidity = 20;
  }
  if(maxHumidity>80||maxHumidity<minHumidity){
    maxHumidity = 80;
  }
  this->minHumidity = minHumidity;
  this->maxHumidity = maxHumidity;

  minTemp = 0;
  maxTemp = 50;
  
  fanSpeed = 255;

  cooldownTime = 10000;
  this->Name = Name;

  getHumidity();
  getTemperature();

  initDHT();
  initMotor();
}

/**
 * Initialises the DHT module using the DHT Library using the assigned Pin and DHT Type.
 * It then gets the temperature and humidity reading from the module.
 */
void Humidistat::initDHT(){
  DHT DHTSensor(DHTPin, DHTType);
  DHTSensor.begin();
  getTemperature();
  getHumidity();
}

/**
 * Initialises the motor controller using the assigned pin.
 * It then makes sure that the motor is turned off.
 */
void Humidistat::initMotor(){
  pinMode(MotorPin,OUTPUT);
  MotorOff();
}

// Set Variables
/**
 * Sets a new DHT module pin and then restarts the module.
 * @param int DHTPin, the new pin that the DHTmodule is on.
 */
void Humidistat::setDHTPin(DHTPin){
  this->DHTPin = DHTPin;
  initDHT();
}

/**
 * Sets a new motor controller pin and then restarts the motor controller.
 * @param int MotorPin, the new pin that the motor controller is on.
 */
void Humidistat::setMotorPin(MotorPin){
  this->MotorPin = MotorPin;
  initMotor();
}

/**
 * Sets a new DHTType and then restarts the DHT module.
 * @param String DHTType, the new DHT Type.
 */
void Humidistat::setDHTType(DHTType){
  this->DHTType = DHTType;
  initDHT();
}

/**
 * Overides the Humidity reading of the DHT module with a new value.
 * @param float Humidity, the new humidity value between 0% and 100%.
 */
void Humidistat::setHumidity(Humidity){
  if(Humidity<=100 && Humidity>0){
    this->Humidity = Humidity;
  }
  else{
    Serial.println("Value must be between 0 and 100.");
  }
}

/**
 * Sets a new minimum humidity.
 * @param float minHumidity, the new minimum humidity.
 */
void Humidistat::setMinHumidity(minHumidity){
  if(minHumidity>0 && minHumidity<=100 && minHumidity<maxHumidity){
    this->minHumidity = minHumidity;
  }
  else{
    Serial.println("Value must be between 0 and 100, and less than maxHumidity.");
  }
}

/**
 * Sets a new maximum humidity.
 * @param float maxHumidity, the new maximum humidity.
 */
void Humidistat::setMaxHumidity(maxHumidity){
  if(maxHumidity>0 && maxHumidity<=100 && maxHumidity>minHumidity){
    this->maxHumidity = maxHumidity;
  }
  else{
    Serial.println("Value must be between 0 and 100, and more than minHumidity.");
  }
}

/**
 * Overides the temperature readings from the DHT module.
 * @param float Temperature, the new temperature greater than 0.
 */
void Humidistat::setTemperature(Temperature){
  if(Temperature>-273){
    this->Temperature=Temperature;
  }
  else{
    Serial.println("Value must be greater than -273c")
  }
}

/**
 * Sets a new minimum temperature.
 * @param float minTemp, the new minimum temperature.
 */
void Humidistat::setMinTemp(minTemp){
  if(minTemp>-273 && minTemp<maxTemp){
    this->minTemp = minTemp;
  }
  else{
    Serial.println("Value must be greater than -273c and less than maxTemp.")
  }
}

/**
 * Sets a new maximum temperature.
 * @param float maxTemp, the new maximum temperature.
 */
void Humidistat::setMaxTemp(maxTemp){
  if(maxTemp>-273 && maxTemp>minTemp){
    this->maxTemp = maxTemp;
  }
  else{
    Serial.println("Value must be greater than -273 and more than minTemp.")
  }
}
/**
 * Sets a new fan speed.
 * @param int fanSpeed, the new motor speed from 0 to 255.
 */
void Humidistat::setFanSpeed(fanSpeed){
  if(fanSpeed>=0 && fanSpeed<=255){
    this->fanSpeed = fanSpeed;
  }
  else{
    Serial.println("Value must be between 0 and 255.")
  }
}

/**
 * Sets the motor state of the motor. Where true is on, and false is off.
 * @param bool MotorState, when true motor is on, when false the motor is off.
 */
void Humidistat::setMotorState(MotorState){
  this->MotorState = MotorState;
}

/**
 * Sets a new cooldownTime.
 * @param long cooldownTime, The length of time before the motor can run again.
 */
void Humidistat::setCoolDownTime(cooldownTime){
  this->cooldownTime = cooldownTime;
}

/**
 * Sets a new name for the Humidistat object.
 * @param String Nanme, the new name of the humidistat object.
 */
void Humidistat::setName(Name){
  this->Name = Name;
}

// Get Variables
/**
 * Returns the DHT module pin.
 * @return int DHTPin, the read pin of the DHT module.
 */
int Humidistat::getDHTPin(){
  return DHTPin;
}

/**
 * Returns the motor controller pin.
 * @return int MotoroPin, the pin assigned to the motorcontroller.
 */
int Humidistat::getMotorPin(){
  return MotorPin;
}

/**
 * Returns the DHT type of the DHT module.
 * @return String DHTType, the DHT type of the DHT module.
 */
String Humidistat::getDHTType(){
  return DHTType;
}

/**
 * Gets the current humidity from the DHT Sensor, then sets the new humidity.
 * @return float Humidity, the current humidity reading from the DHT sensor.
 */
float Humidistat::getHumidity(){
  Humidity = DHTSensor.readHumidity();
  setHumidity(Humidity);

  return Humidity;
}

/**
 * Returns the minimum humidity.
 * @return float minHumidity, the minimum humidity set in the humidistat object.
 */
float Humidistat::getMinHumidity(){
  return minHumidity;
}

/**
 * Returns the maximum humidity.
 * @return float maxHumidity, the maximum humidity set in the humidistat object.
 */
float Humidistat::getMaxHumidity(){
  return maxHumidity;
}

/**
 * Gets the current temperature reading from the DHT sensor, then sets a new temperature.
 * @return float Temperature, the current temperature reading from the DHT sensor.
 */
float Humidistat::getTemperature(){
  Temperature = DHTSensor.readTemperature();
  setTemperature(Temperature);

  return Temperature;
}

/** 
 * Returns the minimum temperature.
 * @return float minTemp, the minimum temperature set in the humidistat object.
 */
float Humidistat::getMinTemp(){
  return minTemp;
}

/**
 * Returns the maximum temperature.
 * @return float maxTemp, the maximum temperature set in the humidistat object.
 */
float Humidistat::getMaxTemp(){
  return maxTemp;
}

/**
 * Returns the current fan speed.
 * @return int fanSpeed, the speed of the motor if in an on state.
 */
int Humidistat::getFanSpeed(){
  return fanSpeed;
}

/**
 * Returns the motor state.
 * @return bool MotorState, The state of the motor where True is On and False is Off.
 */
bool Humidistat::getMotorState(){
  return MotorState;
}

/**
 * Returns the cooldown time.
 * @return long cooldownTime, the cooldown time before the motor can run again.
 */
long Humidistat::getCooldownTime(){
  return cooldownTime;
}

/**
 * Returns the name of the Humidistat.
 * @return String Name, the name of the Humidistat object.
 */
String Humidistat::getName(){
  return Name;
}

// Class functions
/**
 * Turns the motor using the motor pin and the assigned fan speed.
 * Sets the motor state to 1 (on).
 */
void Humidistat::MotorOn(){
  analogWrite(MotorPin,fanSpeed);
  setMotorState(1);
}

/**
 * Turns the motor off using the motor pin.
 * Sets the motor state to 0 (off).
 */
void Humidistat::MotorOff(){
  analogWrite(MotorPin,0);
  setMotorState(0);
}

/**
 * Checks the current humidity against the minimum humidity.
 * If the current humidity is greater than the minimum humidity, then the fan is switched on at fall speed.
 * Otherwise the motor is turned off.
 */
void Humidistat::RoomCheckBinary(){
  if(getHumidity()>minHumidity){
    setFanSpeed(255);
    MotorOn();
  }
  else{
    MotorOff();
  }
}

/**
 * Checks the current humidity against the minimum humidity.
 * If the current humidity is greater than the minimum humidity, then the fan is turned on at a speed related to the current humidity.
 * The speed is 40% at the minimum humidity, and 100% at the maximum humidity.
 * Otherwise the motor is turned off.
 */
void Humidistat::RoomCheckSpectrum(){
  float tempH = getHumidity();
  if(tempH>minHumidity){
    float tempFanSpeed = ((255.-100.)/(maxHumidity-minHumidity))*(tempH-maxHumidity)+255.
    setFanSpeed((int)tempFanSpeed);
    MotorOn();
  }
  else{
    MotorOff();
  }
}