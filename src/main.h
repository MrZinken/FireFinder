#include <Arduino.h>

float getBatteryLevel();


#include <LoRaWan_APP.h>            //LoraWan

bool initLorawanModule();
void prepareTxFrame(uint8_t port);
void loraLoopHandler();


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

struct BME688Data {
    float gas;          // Gas resistance in KOhms
    float humidity;     // Humidity in RH%
    float temperature;  // Temperature in °C
};

bool setupBME688();
BME688Data readBME688();


