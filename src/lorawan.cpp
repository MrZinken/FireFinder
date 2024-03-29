#include "main.h"

/*
 * set LoraWan_RGB to Active,the RGB active in loraWan
 * RGB red means sending;
 * RGB purple means joined done;
 * RGB blue means RxWindow1;
 * RGB yellow means RxWindow2;
 * RGB green means received done;
 */

/* OTAA para 3*/
uint8_t devEui[] = {0xAA, 0xEE, 0xFF, 0x05, 0x55, 0xDD, 0xB3, 0x71};
uint8_t appEui[] = {0xED, 0x21, 0x13, 0x42, 0xEF, 0xCD, 0xAB, 0x25};
uint8_t appKey[] = {0x1F, 0xE3, 0x74, 0xF1, 0x98, 0x1F, 0x31, 0x21, 0x2C, 0xB9, 0xDE, 0xFB, 0xE8, 0x1F, 0x8A, 0x15};

/* OTAA para 4
uint8_t devEui[] = {0xAA, 0xEE, 0xFF, 0x05, 0x55, 0xDD, 0xB3, 0x70};
uint8_t appEui[] = {0xED, 0x21, 0x13, 0x42, 0xEF, 0xCD, 0xAB, 0x21};
uint8_t appKey[] = {0x1F, 0xE3, 0x74, 0xF1, 0x98, 0x1F, 0x31, 0x21, 0x2C, 0xB9, 0xDE, 0xFB, 0xE8, 0x1F, 0x8A, 0x13};

/* OTAA para 1
uint8_t devEui[] = {0xAA, 0xEE, 0xFF, 0x05, 0x55, 0xDD, 0xB3, 0x78};
uint8_t appEui[] = {0xED, 0x21, 0x13, 0x42, 0xEF, 0xCD, 0xAB, 0x24};
uint8_t appKey[] = {0x1F, 0xE3, 0x74, 0xF1, 0x98, 0x1F, 0x31, 0x21, 0x2C, 0xB9, 0xDE, 0xFB, 0xE8, 0x1F, 0x8A, 0x16};

/* OTAA para 2
uint8_t devEui[] = {0xAA, 0xEE, 0xFF, 0x05, 0x55, 0xDD, 0xB3, 0x72};
uint8_t appEui[] = {0xED, 0x21, 0x13, 0x42, 0xEF, 0xCD, 0xAB, 0x22};
uint8_t appKey[] = {0x1F, 0xE3, 0x74, 0xF1, 0x98, 0x1F, 0x31, 0x21, 0x2C, 0xB9, 0xDE, 0xFB, 0xE8, 0x1F, 0x8A, 0x14};
*/
/* ABP para*/
uint8_t nwkSKey[] = {0x15, 0xb1, 0xd0, 0xef, 0xa4, 0x63, 0xdf, 0xbe, 0x3d, 0x11, 0x18, 0x1e, 0x1e, 0xc7, 0xda, 0x85};
uint8_t appSKey[] = {0xd7, 0x2c, 0x78, 0x75, 0x8c, 0xdc, 0xca, 0xbf, 0x55, 0xee, 0x4a, 0x77, 0x8d, 0x16, 0xef, 0x67};
uint32_t devAddr = (uint32_t)0x007e6ae1;

/*LoraWan channelsmask, default channels 0-7*/
uint16_t userChannelsMask[6] = {0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};

// LoraWan region, select in arduino IDE tools
LoRaMacRegion_t loraWanRegion = LORAMAC_REGION_EU868;

// LoraWan Class, Class A and Class C are supported
DeviceClass_t loraWanClass = CLASS_A;

// the application data transmission duty cycle.  value in [ms].
uint32_t appTxDutyCycle = 1000 * 60 * 10;

// OTAA or ABP
bool overTheAirActivation = true;

// ADR enable
bool loraWanAdr = true;

// set LORAWAN_Net_Reserve ON, the node could save the network info to flash, when node reset not need to join again
bool keepNet = false;

/* Indicates if the node is sending confirmed or unconfirmed messages */
bool isTxConfirmed = false;

// Application port
uint8_t appPort = 2;
/*!
 * Number of trials to transmit the frame, if the LoRaMAC layer did not
 * receive an acknowledgment. The MAC performs a datarate adaptation,
 * according to the LoRaWAN Specification V1.0.2, chapter 18.4, according
 * to the following table:
 *
 * Transmission nb | Data Rate
 * ----------------|-----------
 * 1 (first)       | DR
 * 2               | DR
 * 3               | max(DR-1,0)
 * 4               | max(DR-1,0)
 * 5               | max(DR-2,0)
 * 6               | max(DR-2,0)
 * 7               | max(DR-3,0)
 * 8               | max(DR-3,0)
 *
 * Note, that if NbTrials is set to 1 or 2, the MAC will not decrease
 * the datarate, in case the LoRaMAC layer did not receive an acknowledgment
 */
uint8_t confirmedNbTrials = 4;

bool initLorawanModule()
{
    deviceState = DEVICE_STATE_INIT;
    LoRaWAN.ifskipjoin();
    return true;
    debug_println("Lorawan setup done");
}

// Prepares the payload of the frame
void prepareTxFrame(uint8_t port)
{
    /*appData size is LORAWAN_APP_DATA_MAX_SIZE which is defined in "commissioning.h".
     *appDataSize max value is LORAWAN_APP_DATA_MAX_SIZE.
     *if enabled AT, don't modify LORAWAN_APP_DATA_MAX_SIZE, it may cause system hanging or failure.
     *if disabled AT, LORAWAN_APP_DATA_MAX_SIZE can be modified, the max value is reference to lorawan region and SF.
     *for example, if use REGION_CN470,
     *the max value for different DR can be found in MaxPayloadOfDatarateCN470 refer to DataratesCN470 and BandwidthsCN470 in "RegionCN470.h".
     */
    delay(100); // Wait for voltage to stabilize
    Wire.begin();
    // Wire.setClock(400000); // Increase to fast I2C speed!

    setupBME688();
    BME688Data bme688data = readBME688();

    uint8_t battery = getBatteryLevel();
    uint8_t humidity = bme688data.humidity;
    uint8_t temperature = bme688data.temperature;
    uint32_t gas = bme688data.gas;

    debug_print("VOC: ");
    debug_println(bme688data.gas);
    debug_print("Humdity: ");
    debug_println(bme688data.humidity);
    debug_print("Temperature: ");
    debug_println(bme688data.temperature);
    debug_print("Battery: ");
    debug_println(getBatteryLevel());

    appDataSize = 4;
    appData[0] = battery;
    appData[1] = humidity;
    appData[2] = temperature;
    appData[3] = gas;
    debug_println(appData[0]);
}

void loraLoopHandler()
{
    switch (deviceState)
    {
    case DEVICE_STATE_INIT: // active after initialization
    {
        printDevParam();
        LoRaWAN.init(loraWanClass, loraWanRegion);
        deviceState = DEVICE_STATE_JOIN;
        break;
    }
    case DEVICE_STATE_JOIN: // joins with provided credentials
    {
        LoRaWAN.join();
        break;
    }
    case DEVICE_STATE_SEND: // preparesTXpayload and sends it
    {
        prepareTxFrame(appPort);
        LoRaWAN.send();
        debug_println("Package send ");
        deviceState = DEVICE_STATE_CYCLE;
        break;
    }
    case DEVICE_STATE_CYCLE:
    { // Schedule next packet transmission
        txDutyCycleTime = appTxDutyCycle + randr(0, APP_TX_DUTYCYCLE_RND);
        LoRaWAN.cycle(txDutyCycleTime);
        deviceState = DEVICE_STATE_SLEEP;
        break;
    }
    case DEVICE_STATE_SLEEP: // sleeps for time given in appTxDutyCycle
    {
        LoRaWAN.sleep();
        break;
    }
    default:
    {
        deviceState = DEVICE_STATE_INIT;
        break;
    }
    }
}
