/*
  Humidistat.h - Library for linking a humidity sensor and DC motor together for humidity control in a room
  Created by Sam D on 19.7.2024
*/

#ifndef Humidistat_h
#define Humidistat_h

#include "Arduino.h"
#include "DHT.h"

class Humidistat{
    private:
      uint8_t DHTPin;
      int MotorPin;
      uint8_t DHTType;
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
      DHT DHTSensor;

      void initDHT();
      void initMotor();

    public:
    // Constructors
      Humidistat(uint8_t DHTPin = 1,int MotorPin = 2,uint8_t DHTType = DHT11,float minHumidity = 20,float maxHumidity = 80,String Name = "Unnamed");

      // Set Variables
      void setDHTPin(uint8_t);
      void setMotorPin(int);
      void setDHTType(uint8_t);
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
      uint8_t getDHTPin();
      int getMotorPin();
      uint8_t getDHTType();
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