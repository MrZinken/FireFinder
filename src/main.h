#include <Arduino.h>

uint8_t getBatteryLevel();

//#define DEBUG // Herauskommentieren, wenn keine serielle Ausgabe erwünscht wird

#ifdef DEBUG
#define debug_print(x) Serial.print(x)
#define debug_println(x) Serial.println(x)
#define debug_begin(x) Serial.begin(x)
#else
#define debug_print(x)
#define debug_println(x)
#define debug_begin(x)
#endif

#include <LoRaWan_APP.h> //LoraWan

bool initLorawanModule();
void prepareTxFrame(uint8_t port);
void loraLoopHandler();

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

struct BME688Data
{
    uint32_t gas;        // Gas resistance in KOhms
    uint8_t humidity;    // Humidity in RH%
    uint8_t temperature; // Temperature in °C
};

bool setupBME688();
BME688Data readBME688();
