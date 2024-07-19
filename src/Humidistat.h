/*
  LED.h - Library for creating and controlling LEDs
  Created by Sam Dicker on 10.7.2024
*/

#ifndef LEDs_h
#define LEDs_h

#include "Arduino.h"

class LEDs{
    private:
      int Pin;
      int Brightness;
      long ms;
      long msOld;
      int LEDState;
      long tDelay;
      String Name;

      void initLED();

      void setms(long);
      void setmsOld(long);

      long getms();
      long getmsOld();

    public:
      LEDs();
      LEDs(int);
      LEDs(int,String);
      LEDs(int,long,String);

      void setPin(int);
      void setLEDState(int);
      void settDelay(long);
      void setName(String);
      void setBrightness(int);

      int getPin();
      int getLEDState();
      long gettDelay();
      String getName();
      int getBrightness();

      void LEDOn();
      void LEDOn(int);
      void LEDOff();
      void BlinkLED();
      void BlinkLED(int);
};

#endif