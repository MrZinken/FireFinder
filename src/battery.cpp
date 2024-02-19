#include <main.h>
  
    // 0      The end-device is connected to an external power source.
	// 1..254 The battery level, 1 being at minimum and 254 being at maximum
	// 255    The end-device was not able to measure the battery level.
/// @brief Read the battery level
/// @return Battery level from minimum 1 to 254 being the maximum
uint8_t getBatteryLevel()
{
  if (BoardGetBatteryLevel() < 255)
  {
    return BoardGetBatteryLevel();
  }
  else
  {
    return 0xff; // flag value for false reading
  }
}