#include <main.h>

// I2C
Adafruit_BME680 bme688;

bool setupBME688() {

   
    // Set up oversampling and filter initialization
    bme688.setTemperatureOversampling(BME680_OS_8X);
    bme688.setHumidityOversampling(BME680_OS_2X);
    bme688.setGasHeater(320, 150);  // 320°C for 150 ms

    return bme688.begin(0x77);
}

BME688Data readBME688() {
    // Tell BME680 to begin measurement.
    unsigned long endTime = bme688.beginReading();

    // Check if reading has ended successfully
    if (!bme688.endReading()) {
        Serial.println("[BME688] Error: Failed to complete measurement!");
    }

    // Convert measurement to struct
    BME688Data data;
    data.gas = bme688.gas_resistance / 1000.0;
    data.humidity = bme688.humidity;
    data.temperature = bme688.temperature;

    return data;
}
