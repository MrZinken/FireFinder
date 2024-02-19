#include <main.h>

void setup()
{
  Serial.begin(115200);
  initLorawanModule();
}

void loop()
{
  loraLoopHandler();
}
