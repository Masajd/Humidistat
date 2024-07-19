/*
  LED.CPP - Library for creating and controlling LEDs
  Created by Sam Dicker on 10.7.2024
*/

#include "Arduino.h"
#include "LEDs.h"

/**
** Default Constructor that creates an LED on Pin 1, with a timing of 0 and an old timing of 0,
** with the LED set to OFF and a time delay between blinks of 1 second. The LED is unnamed.
**/
LEDs::LEDs(){
    Pin = 1;
    ms = 0;
    msOld = 0;
    LEDState = 0;
    Brightness = 255;
    tDelay = 1000;
    Name = "Unnamed LED";
}

/**
** Constructor that takes 1 argument. It assigns the LED to a pin, and sets a default time delay of 1000ms. The LED is unnamed.
** @param int Pin, Pin that LED is assigned to on the Arduino.
**/
LEDs::LEDs(int Pin){
    this->Pin = Pin;
    ms = 0;
    msOld = 0;
    LEDState = 0;
    Brightness = 255;
    tDelay = 1000;
    Name = "Unnamed LED";

    initLED();
    LEDOff();
}

/**
** Constructor that takes 2 arguments. It assigns the LED to a pin and gives it a name.
** @param int Pin, Pin that LED is assigned to on the Arduino.
** @param String Name, Name of the LED, usually its colour and assigned pin.
**/
LEDs::LEDs(int Pin, String Name){
    this->Pin = Pin;
    ms = 0;
    msOld = 0;
    LEDState = 0;
    Brightness = 255;
    tDelay = 1000;
    this->Name = Name;

    initLED();
    LEDOff();
}

/**
** Constructor that takes 3 arguments. It assigns the LED to a pin, the time delay between blinks, and gives it a name.
** @param int Pin, Pin that LED is assigned to on the Arduino.
** @param long tDelay, Time delay between blinks of LED states.
** @param String Name, Name of the LED, usually its colour and assigned pin.
**/
LEDs::LEDs(int Pin, long tDelay, String Name){
    this->Pin = Pin;
    ms = 0;
    msOld = 0;
    LEDState = 0;
    Brightness = 255;
    this->tDelay = tDelay;
    this->Name = Name;

    initLED();
    LEDOff();
}

/** Initialises pin that LED is assigned to OUTPUT.
**/
void LEDs::initLED(){
    pinMode(Pin,OUTPUT);
}

/** Set Pin value of Pin object.
** @param int Pin, Pin that LED is assigned to on the Arduino.
**/
void LEDs::setPin(int Pin){
    this->Pin = Pin;
}

/** Set the state of the LED to 0 or 1 to show the LED as being on or off.
**  @param int LEDState, State of the LED, 0 = OFF, 1 = ON.
**/
void LEDs::setLEDState(int LEDState){
    this->LEDState = LEDState;
}

/** Set the length between blinks of the LED object
**  @param long tDelay, Time delay between blinks of LED states.
**/
void LEDs::settDelay(long tDelay){
    this->tDelay = tDelay;
}

/** Set the Name of the LED object.
**  @param String Name, Name of the LED, usually its colour and assigned pin.
**/
void LEDs::setName(String Name){
    this->Name = Name;
}

/** Set the current clock timer to a value
**  @param int ms, the current clock timer value
**/
void LEDs::setms(long ms){
    this->ms = ms;
}

/** Set a value for the old clock timer
**  @param long msOld, the old clock timer value
**/
void LEDs::setmsOld(long msOld){
    this->msOld = msOld;
}

/**  Sets the brightness of the LED when it is turned on.
**   @param int Brightness, the brightness of the LED when turned on.
**/
void LEDs::setBrightness(int Brightness){
    if(Brightness>0 && Brightness<256){
        this->Brightness = Brightness;
    }
    else{
        Serial.println("Enter a brightness between 0 and 256");
    }
}

/** Get the LEDs Pin Number.
**  @return int Pin, the LEDs assgined Pin on the Arduino
**/
int LEDs::getPin(){
    return Pin;
}

/** Gets the LED state of the LED.
**  @return int LEDState, the LED state of the LED.
**/
int LEDs::getLEDState(){
    return LEDState;
}

/** Gets the time interval between blinks of the LED.
**  @return long tDelay, the time interval between blinks value of the LED.
**/
long LEDs::gettDelay(){
    return tDelay;
}

/** Gets the Name of the LED.
**  @return String Name, the name of the LED.
**/
String LEDs::getName(){
    return Name;
}

/** Gets the current clock timer value
**  @return long ms, the current clock timer value.
**/
long LEDs::getms(){
    return ms;
}

/** Gets the old clock timer value.
**  @return long msOld, the old clock timer value.
**/
long LEDs::getmsOld(){
    return msOld;
}

/** Get the Brightness of the LED.
**  @return int Brightness, the Brightness of the LED.
**/
int LEDs::getBrightness(){
    return Brightness;
}

/** Turn the LED on and set the LED state to 1.
**/
void LEDs::LEDOn(){
    digitalWrite(Pin,HIGH);
    setLEDState(1);
}

/** Turns the LED on with a given brightness and sets the LED State to 1.
**  @param int Brightness, the brightness of the LED.
**/
void LEDs::LEDOn(int Brightness){
    setBrightness(Brightness);
    analogWrite(Pin,Brightness);
    setLEDState(1);
}

/** Turn the LED off and set the LED state to 0.
**/
void LEDs::LEDOff(){
    digitalWrite(Pin,LOW);
    setLEDState(0);
}

/** Blinks the LED with an interval of tDelay.
**/
void LEDs::BlinkLED(){
    setms(millis());
    if((getms() - getmsOld())>gettDelay()){
    setmsOld(getms());
    if(getLEDState() == 0){
        LEDOff();
    }
    else{
        LEDOn();
    }
    }
}

/** Blinks the LED with an interval of tDelay.
**/
void LEDs::BlinkLED(int Brightness){
    setBrightness(Brightness);
    setms(millis());
    if((getms() - getmsOld())>gettDelay()){
    setmsOld(getms());
    if(getLEDState() == 0){
        LEDOff();
    }
    else{
        LEDOn(Brightness);
    }
    }
}