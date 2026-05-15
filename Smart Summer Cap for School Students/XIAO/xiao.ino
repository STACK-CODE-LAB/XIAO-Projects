#include <bluefruit.h>

#define DEVICE_NAME "SMART_CAP"
#define SERVICE_UUID "12345678-1234-1234-1234-1234567890ab"

BLEService customService(SERVICE_UUID);

uint8_t student_id = 1;   // change per device
uint8_t activity = 1;
float temp = 36.5;

void setup() {
  Serial.begin(115200);
  Bluefruit.begin();

  Bluefruit.setName(DEVICE_NAME);

  customService.begin();   // ✅ start service

  startAdvertising();
}

void loop() {
  // simulate data
  temp += 0.05;
  if (temp > 38) temp = 36.5;

  activity = random(0, 3);

  updateAdvertisingData();

  delay(5000);
}

void startAdvertising() {
  Bluefruit.Advertising.stop();
  Bluefruit.Advertising.clearData();

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);

  // ✅ KEY: advertise service UUID
  Bluefruit.Advertising.addService(customService);

  Bluefruit.Advertising.addName();

  updateAdvertisingData();

  Bluefruit.Advertising.setInterval(160, 160);
  Bluefruit.Advertising.start(0);
}

void updateAdvertisingData() {

  uint8_t data[4];

  data[0] = student_id;

  int temp_int = temp * 100;
  data[1] = temp_int & 0xFF;
  data[2] = (temp_int >> 8) & 0xFF;

  data[3] = activity;

  Bluefruit.Advertising.addManufacturerData(data, sizeof(data));
}