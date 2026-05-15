#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#define SCAN_TIME 5

BLEScan* pBLEScan;

BLEUUID targetUUID("12345678-1234-1234-1234-1234567890ab");

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {

    // ✅ Check if device has our service UUID
    if (advertisedDevice.haveServiceUUID()) {

      BLEUUID devUUID = advertisedDevice.getServiceUUID();

      if (devUUID.equals(targetUUID)) {

        Serial.println("✅ XIAO DEVICE DETECTED");

        std::string mData = advertisedDevice.getManufacturerData();

        if (mData.length() == 4) {

          uint8_t student_id = mData[0];

          int temp_int = (uint8_t)mData[1] | ((uint8_t)mData[2] << 8);
          float temp = temp_int / 100.0;

          uint8_t activity = mData[3];

          Serial.print("Student ID: ");
          Serial.println(student_id);

          Serial.print("Temperature: ");
          Serial.println(temp);

          Serial.print("Activity: ");
          Serial.println(activity);
        }

        Serial.print("RSSI: ");
        Serial.println(advertisedDevice.getRSSI());

        Serial.println("---------------------------\n");
      }
    }
  }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("");

  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());

  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
}

void loop() {
  Serial.println("Scanning...");

  BLEScanResults* results = pBLEScan->start(SCAN_TIME, false);

  Serial.print("Devices found: ");
  Serial.println(results->getCount());

  Serial.println("Scan done.\n");

  pBLEScan->clearResults();
  delay(2000);
}