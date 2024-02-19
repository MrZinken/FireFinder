#include <Arduino.h>

uint8_t getBatteryLevel();


#include <LoRaWan_APP.h>            //LoraWan

bool initLorawanModule();
void prepareTxFrame(uint8_t port);
void loraLoopHandler();


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

struct BME688Data {
    uint32_t gas;          // Gas resistance in KOhms
    uint8_t humidity;     // Humidity in RH%
    uint8_t temperature;  // Temperature in °C
};

bool setupBME688();
BME688Data readBME688();


