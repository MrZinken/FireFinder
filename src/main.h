#include <Arduino.h>

uint8_t getBatteryLevel();


#include <LoRaWan_APP.h>            //LoraWan

bool initLorawanModule();
void prepareTxFrame(uint8_t port);

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

struct BME688Data {
    float gas;          // Gas resistance in KOhms
    float humidity;     // Humidity in RH%
    float temperature;  // Temperature in °C
};

bool setupBME688(float measuredSeaLevelPressure);
BME688Data readBME688();


