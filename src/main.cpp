#include <main.h>

void setup()
{
  debug_begin(115200);
  initLorawanModule();
}

void loop()
{
  loraLoopHandler();
}
