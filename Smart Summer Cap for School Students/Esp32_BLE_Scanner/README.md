# ESP32 BLE Scanner for XIAO Devices

This project uses an ESP32 board to scan nearby BLE (Bluetooth Low Energy) devices and detect specific XIAO devices broadcasting a custom BLE Service UUID.

The scanner extracts:
- Student ID
- Temperature
- Activity Status
- RSSI Signal Strength

from BLE Manufacturer Data packets.

---

# 📌 Features

✅ BLE Scanning using ESP32  
✅ Detect custom BLE UUID  
✅ Read manufacturer advertisement data  
✅ Extract encoded sensor information  
✅ Display real-time data in Serial Monitor  

---

# 🧠 How This Project Works

The ESP32 continuously scans nearby BLE advertisements.

When a BLE device is found:
1. The scanner checks whether the device contains the target Service UUID.
2. If UUID matches:
   - Manufacturer data is extracted.
   - Sensor information is decoded.
   - Data is printed to Serial Monitor.

---

# 📡 BLE Data Structure

The BLE Manufacturer Data packet contains 4 bytes:

| Byte | Purpose |
|------|----------|
| 0 | Student ID |
| 1-2 | Temperature |
| 3 | Activity |

---

# 🔍 Example Decoding

Suppose manufacturer data is:

```text
[01][D2][04][02]
```

Decoded as:

| Data | Value |
|------|------|
| Student ID | 1 |
| Temperature Raw | 0x04D2 = 1234 |
| Temperature | 12.34 °C |
| Activity | 2 |

---

# 📶 RSSI

RSSI (Received Signal Strength Indicator) represents signal strength.

Higher value (closer to 0):
- Strong signal
- Device is nearby

Lower value:
- Weak signal
- Device is farther away

Example:

```text
RSSI: -45  -> Near
RSSI: -90  -> Far
```

---

# 🛠 Hardware Required

## Scanner Side
- ESP32 Dev Board

## Beacon Side
- Seeed XIAO ESP32 / BLE device

---

# 📦 Required Libraries

Install the following:

## ESP32 Board Package
Install from Arduino Board Manager:

```text
ESP32 by Espressif Systems
```

---

## BLE Library

Usually included automatically with ESP32 package.

Used headers:

```cpp
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
```

---

# ⚙️ Arduino IDE Setup

## 1. Install ESP32 Board

Go to:

```text
Tools → Board → Boards Manager
```

Search:

```text
ESP32
```

Install:

```text
ESP32 by Espressif Systems
```

---

## 2. Select Board

Example:

```text
Tools → Board → ESP32 Dev Module
```

---

## 3. Select COM Port

```text
Tools → Port → COMx
```

---

# 🚀 Uploading the Code

1. Connect ESP32 using USB.
2. Open `.ino` file.
3. Click Upload.

After uploading:

```text
Tools → Serial Monitor
```

Set baud rate:

```text
115200
```

---

# 📄 Expected Serial Output

```text
Scanning...

✅ XIAO DEVICE DETECTED

Student ID: 1
Temperature: 36.75
Activity: 2
RSSI: -52

---------------------------
```

---

# 🧩 Code Explanation

---

## 1. BLE Initialization

```cpp
BLEDevice::init("");
```

Initializes BLE functionality on ESP32.

---

## 2. Scanner Creation

```cpp
pBLEScan = BLEDevice::getScan();
```

Creates BLE scanner object.

---

## 3. Active Scanning

```cpp
pBLEScan->setActiveScan(true);
```

Enables active scan mode.

Active scanning:
- Sends scan requests
- Gets more advertisement data
- Better detection

---

## 4. Device Callback

```cpp
class MyAdvertisedDeviceCallbacks
```

Runs automatically whenever a BLE device is detected.

---

## 5. UUID Filtering

```cpp
if (devUUID.equals(targetUUID))
```

Checks whether detected device matches target BLE UUID.

Only matching devices are processed.

---

## 6. Manufacturer Data Extraction

```cpp
std::string mData = advertisedDevice.getManufacturerData();
```

Reads raw BLE advertisement payload.

---

## 7. Temperature Decoding

```cpp
int temp_int = (uint8_t)mData[1] | ((uint8_t)mData[2] << 8);
float temp = temp_int / 100.0;
```

Combines two bytes into temperature value.

Example:

```text
3675 → 36.75 °C
```

---

## 8. RSSI Reading

```cpp
advertisedDevice.getRSSI()
```

Measures signal strength.

Useful for:
- Indoor positioning
- Distance estimation
- Presence tracking

---

# ⏱ Scan Timing

```cpp
#define SCAN_TIME 5
```

Scanner scans for 5 seconds continuously.

Then:

```cpp
delay(2000);
```

Waits 2 seconds before next scan.