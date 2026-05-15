# XIAO BLE Smart Cap Beacon

This project turns a Seeed XIAO BLE device into a BLE beacon that continuously broadcasts student and sensor information using Bluetooth Low Energy (BLE) advertisements.

The device broadcasts:
- Student ID
- Temperature
- Activity Status

using custom Manufacturer Data packets.

This beacon can be detected using an ESP32 BLE Scanner.

---

# 📌 Features

✅ BLE Beacon Broadcasting  
✅ Custom BLE Service UUID  
✅ Manufacturer Data Encoding  
✅ Real-time Sensor Simulation  
✅ Compatible with ESP32 BLE Scanner  
✅ Low-power wireless communication  

---

# 🧠 How This Project Works

The XIAO BLE device acts as a BLE advertiser.

Every few seconds:
1. Temperature and activity data are updated.
2. Data is encoded into a BLE advertisement packet.
3. The packet is broadcast wirelessly.
4. Nearby ESP32 scanners receive and decode the information.

---

# 📡 BLE Broadcast Structure

The device broadcasts:
- BLE Service UUID
- Device Name
- Manufacturer Data

---

# 🧩 Manufacturer Data Format

4 bytes are transmitted:

| Byte | Purpose |
|------|----------|
| 0 | Student ID |
| 1-2 | Temperature |
| 3 | Activity |

---

# 🔍 Example Packet

```text
[01][42][0E][02]
```

Decoded as:

| Data | Value |
|------|------|
| Student ID | 1 |
| Temperature Raw | 0x0E42 = 3650 |
| Temperature | 36.50 °C |
| Activity | 2 |

---

# 📶 BLE UUID

Custom Service UUID:

```text
12345678-1234-1234-1234-1234567890ab
```

The scanner searches specifically for this UUID.

---

# 🛠 Hardware Required

- Seeed XIAO nRF52840 Sense / XIAO BLE
- USB Cable
- Arduino IDE

---

# 📦 Required Libraries

Install:

## Adafruit nRF52 Board Package

Go to:

```text
Tools → Board → Boards Manager
```

Search:

```text
Adafruit nRF52
```

Install:

```text
Adafruit nRF52 by Adafruit
```

---

# 📚 Bluefruit Library

This project uses:

```cpp
#include <bluefruit.h>
```

Automatically included with Adafruit nRF52 package.

---

# ⚙️ Arduino IDE Setup

## 1. Install Board Package

Install:

```text
Adafruit nRF52 Boards
```

---

## 2. Select Board

Example:

```text
Tools → Board → XIAO nRF52840 Sense
```

---

## 3. Select Port

```text
Tools → Port → COMx
```

---

# 🚀 Uploading the Code

1. Connect XIAO BLE board.
2. Open `.ino` file.
3. Click Upload.

After uploading:
- Device automatically starts advertising BLE packets.

---

# 📄 Expected Behavior

The XIAO device continuously broadcasts:

```text
Student ID
Temperature
Activity
```

Nearby ESP32 scanners can detect and decode this information.

---

# 🧪 Sensor Simulation

Inside `loop()`:

```cpp
temp += 0.05;
```

Temperature gradually increases.

When temperature exceeds 38°C:

```cpp
temp = 36.5;
```

resets back to normal.

---

# 🎯 Activity Simulation

```cpp
activity = random(0, 3);
```

Random activity values:
- 0 → Idle
- 1 → Walking
- 2 → Running

---

# 🧩 Code Explanation

---

## 1. BLE Initialization

```cpp
Bluefruit.begin();
```

Starts BLE functionality.

---

## 2. Device Name

```cpp
Bluefruit.setName(DEVICE_NAME);
```

Sets BLE broadcast device name.

Example:

```text
SMART_CAP
```

---

## 3. Create BLE Service

```cpp
BLEService customService(SERVICE_UUID);
```

Defines custom BLE service.

---

## 4. Start BLE Service

```cpp
customService.begin();
```

Registers the service for advertising.

---

## 5. Start Advertising

```cpp
startAdvertising();
```

Begins BLE broadcasting.

---

## 6. Add Service UUID

```cpp
Bluefruit.Advertising.addService(customService);
```

Adds service UUID into advertisement packet.

This allows scanners to identify valid devices.

---

## 7. Add Manufacturer Data

```cpp
Bluefruit.Advertising.addManufacturerData(data, sizeof(data));
```

Embeds custom binary sensor data into BLE packet.

---

## 8. Temperature Encoding

```cpp
int temp_int = temp * 100;
```

Converts float temperature into integer format.

Example:

```text
36.50 → 3650
```

Then split into 2 bytes:

```cpp
data[1] = temp_int & 0xFF;
data[2] = (temp_int >> 8) & 0xFF;
```

---

# 📡 Advertising Interval

```cpp
Bluefruit.Advertising.setInterval(160, 160);
```

Controls BLE advertisement speed.

Lower interval:
- Faster detection
- Higher battery usage

Higher interval:
- Lower battery usage
- Slower detection

---

# 🔋 Power Efficiency

BLE advertising is very low power.

Suitable for:
- Wearables
- Smart caps
- Smart attendance
- IoT health devices

---

# 🔗 Communication Flow

```text
XIAO BLE Device
      ↓
BLE Advertisement Broadcast
      ↓
ESP32 Scanner Detects UUID
      ↓
Manufacturer Data Decoded
      ↓
Student Information Displayed
```

---

# 📄 Example libraries.txt

```text
Adafruit nRF52 Boards
Bluefruit Library
```