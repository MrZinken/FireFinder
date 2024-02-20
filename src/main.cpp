#include <main.h>

void setup()
{
  Serial.begin(115200);
  setupBME688();
  // initLorawanModule();
}

void loop()
{
  BME688Data bme688data = readBME688();
  Serial.print("VOC: ");
  Serial.printf("%f,", bme688data.gas);
  Serial.println(" ");
  Serial.print("Humdity: ");
  Serial.printf("%f,", bme688data.humidity);
  Serial.println(" ");
  Serial.print("Temperature: ");
  Serial.printf("%f,", bme688data.temperature);
  Serial.println(" ");
  Serial.print("Battery: ");
  Serial.printf("%f,", getBatteryLevel());
  Serial.println(" ");
  delay(30000);
  // loraLoopHandler();
}
