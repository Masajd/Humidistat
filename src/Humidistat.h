/*
  Humidistat.h - Library for linking a humidity sensor and DC motor together for humidity control in a room
  Created by Sam Dicker on 19.7.2024
*/

#ifndef Humidistat_h
#define Humidistat_h

#include "Arduino.h"
#include "DHT.h"

class Humidistat{
    private:
      int DHTPin;
      int MotorPin;
      String DHTType;
      float Humidity;
      float minHumidity;
      float maxHumidity;
      float Temperature;
      float minTemp;
      float maxTemp;
      int fanSpeed;
      bool MotorState;
      long cooldownTime;
      String Name;

      void initDHT();
      void initMotor();
      
    public:
    // Constructors
      Humidistat();
      Humidistat(int,int,String);
      Humidistat(int,int,String,String);
      Humidistat(int,int,String,float,float,String);

      // Set Variables
      void setDHTPin(int);
      void setMotorPin(int);
      void setDHTType(String);
      void setHumidity(float);
      void setMinHumidity(float);
      void setMaxHumidity(float);
      void setTemperature(float);
      void setMinTemp(float);
      void setMaxTemp(float);
      void setFanSpeed(int);
      void setMotorState(bool);
      void setCoolDownTime(long);
      void setName(String);

      // Get Variables
      int getDHTPin();
      int getMotorPin();
      String getDHTType();
      float getHumidity();
      float getMinHumidity();
      float getMaxHumidity();
      float getTemperature();
      float getMinTemp();
      float getMaxTemp();
      int getFanSpeed();
      bool getMotorState();
      long getCooldownTime();
      String getName();

      // Class functions
      void MotorOn();
      void MotorOff();
      void RoomCheckBinary();
      void RoomCheckSpectrum();
};

#endif