#include <FastLED.h>
#include <NimBLEDevice.h>

static NimBLEServer* pServer;

// Antal strips og antal LEDs per strip
#define NUM_STRIPS          12
#define NUM_LEDS_PER_STRIP  18

// Definér pins til de 12 strips (tilpas efter dine behov)
#define LED_PIN_STRIP_1   2
#define LED_PIN_STRIP_2   4
#define LED_PIN_STRIP_3   5
#define LED_PIN_STRIP_4   12
#define LED_PIN_STRIP_5   13
#define LED_PIN_STRIP_6   14
#define LED_PIN_STRIP_7   15
#define LED_PIN_STRIP_8   17
#define LED_PIN_STRIP_9   19
#define LED_PIN_STRIP_10  21
#define LED_PIN_STRIP_11  22
#define LED_PIN_STRIP_12  23

// Lysstyrke (0 - 255)
#define BRIGHTNESS 4

// Opret et todimensionelt array til dine LED-strips
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

// Et array med de farver vi vil skifte imellem
CRGB colorCycle[] = {
  CRGB::Red,
  CRGB::Green,
  CRGB::Blue
};




/**  None of these are required as they will be handled by the library with defaults. **
 **                       Remove as you see fit for your needs                        */
class ServerCallbacks : public NimBLEServerCallbacks {
    void onConnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo) override {
        Serial.printf("Client address: %s\n", connInfo.getAddress().toString().c_str());

        /**
         *  We can use the connection handle here to ask for different connection parameters.
         *  Args: connection handle, min connection interval, max connection interval
         *  latency, supervision timeout.
         *  Units; Min/Max Intervals: 1.25 millisecond increments.
         *  Latency: number of intervals allowed to skip.
         *  Timeout: 10 millisecond increments.
         */
        pServer->updateConnParams(connInfo.getConnHandle(), 24, 48, 0, 18);
    }

    void onDisconnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo, int reason) override {
        printf("Client disconnected - start advertising\n");
        NimBLEDevice::startAdvertising();
    }

    void onMTUChange(uint16_t MTU, NimBLEConnInfo& connInfo) override {
        printf("MTU updated: %u for connection ID: %u\n", MTU, connInfo.getConnHandle());
    }

} serverCallbacks;

/** Handler class for characteristic actions */
class CharacteristicCallbacks : public NimBLECharacteristicCallbacks {
    void onRead(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) override {
        printf("%s : onRead(), value: %s\n",
               pCharacteristic->getUUID().toString().c_str(),
               pCharacteristic->getValue().c_str());
    }

    void onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) override {
        printf("%s : onWrite(), value: %s\n",
               pCharacteristic->getUUID().toString().c_str(),
               pCharacteristic->getValue().c_str());
                       std::string value = pCharacteristic->getValue();
        if (pCharacteristic->getUUID().toString() == "0x8889"){
            if (value.length() > 0) {
                // Convert std::string to byte array
                const uint8_t* byteArray = reinterpret_cast<const uint8_t*>(value.data());
                size_t length = value.length();

                //strip.setLEDs(byteArray, length);
                //strip.red(byteArray[0]);
                // Log the received byte array
                /*ESP_LOGI("BLE", "Received value (byte array):");
                for (size_t i = 0; i < length; ++i) {
                    ESP_LOGI("BLE", "byteArray[%d]: %02x", i, byteArray[i]);
                }*/
            } else {
                printf("ingen data modtager");
                ESP_LOGI("BLE", "No value received");
            }
        }
        if (pCharacteristic->getUUID().toString() == "0x888a"){
            if (value.length() > 0) {
                // Convert std::string to byte array
                const uint8_t* byteArray = reinterpret_cast<const uint8_t*>(value.data());
                size_t length = value.length();

                //strip.setoneLED(byteArray, length);
                //strip.red(byteArray[0]);
                // Log the received byte array
                /*ESP_LOGI("BLE", "Received value (byte array):");
                for (size_t i = 0; i < length; ++i) {
                    ESP_LOGI("BLE", "byteArray[%d]: %02x", i, byteArray[i]);
                }*/
            } else {
                ESP_LOGI("BLE", "No value received");
            }
        }
    }

} chrCallbacks;

/** Handler class for descriptor actions */
class DescriptorCallbacks : public NimBLEDescriptorCallbacks {
    void onWrite(NimBLEDescriptor* pDescriptor, NimBLEConnInfo& connInfo) override {
        std::string dscVal = pDescriptor->getValue();
        printf("Descriptor written value: %s\n", dscVal.c_str());
    }

    void onRead(NimBLEDescriptor* pDescriptor, NimBLEConnInfo& connInfo) override {
        printf("%s Descriptor read\n", pDescriptor->getUUID().toString().c_str());
    }
} dscCallbacks;


void setup() {
  Serial.begin(115200);
  // Vent gerne lidt på at porten vågner
  delay(1000);
  Serial.println("Seriemonitor startet!");
  
  // Initialiser hver enkelt strip
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_1 >(leds[0],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_2 >(leds[1],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_3 >(leds[2],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_4 >(leds[3],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_5 >(leds[4],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_6 >(leds[5],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_7 >(leds[6],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_8 >(leds[7],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_9 >(leds[8],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_10>(leds[9],  NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_11>(leds[10], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN_STRIP_12>(leds[11], NUM_LEDS_PER_STRIP);

  FastLED.setBrightness(BRIGHTNESS);

  Serial.println("Starting NimBLE Server");
  /** Initialize NimBLE and set the device name */
  NimBLEDevice::init("HyperionWall");


    NimBLEDevice::setSecurityAuth(/*BLE_SM_PAIR_AUTHREQ_BOND | BLE_SM_PAIR_AUTHREQ_MITM |*/ BLE_SM_PAIR_AUTHREQ_SC);
    pServer = NimBLEDevice::createServer();
    pServer->setCallbacks(&serverCallbacks);

    NimBLEService*        pDeadService = pServer->createService("DEAD");

    //min egen 
    NimBLECharacteristic* p8889Characteristic = pDeadService->createCharacteristic(
        "8889",
        NIMBLE_PROPERTY::READ |
        NIMBLE_PROPERTY::WRITE);
    p8889Characteristic->setValue("Many LEDs - 5 byte");
    p8889Characteristic->setCallbacks(&chrCallbacks);

    // set one led. 5 byte
    NimBLECharacteristic* p888ACharacteristic = pDeadService->createCharacteristic(
        "888A",
        NIMBLE_PROPERTY::READ |
        NIMBLE_PROPERTY::WRITE);
    p888ACharacteristic->setValue("One LED - 5 byte");
    p888ACharacteristic->setCallbacks(&chrCallbacks);

 

    /** Start the services when finished creating all Characteristics and Descriptors */
    pDeadService->start();

    /** Create an advertising instance and add the services to the advertised data */
    NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->setName("HyperionWall");
    pAdvertising->addServiceUUID(pDeadService->getUUID());

    /**
     *  If your device is battery powered you may consider setting scan response
     *  to false as it will extend battery life at the expense of less data sent.
     */
    pAdvertising->enableScanResponse(true);
    pAdvertising->start();

    printf("Advertising Started\n");  
}

void loop() {
  // Holder styr på, hvilken farve i colorCycle der skal bruges
  static uint8_t colorIndex = 0;

  // Sæt alle LEDs på alle 12 strips til den aktuelle farve
  for(int strip = 0; strip < NUM_STRIPS; strip++) {
    fill_solid(leds[strip], NUM_LEDS_PER_STRIP, colorCycle[colorIndex]);
  }

  // Send farveopdatering til alle strips
  FastLED.show();

  // Vent 1 sekund
  delay(1000);

  // Skift til næste farve (rød -> grøn -> blå -> rød ...)
  colorIndex = (colorIndex + 1) % 3;
}