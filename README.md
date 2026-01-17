# ESP32 NetProbe 🔍

<div align="center">

![ESP32](https://img.shields.io/badge/ESP32-E53529?style=for-the-badge&logo=espressif&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![WiFi](https://img.shields.io/badge/WiFi-1A73E8?style=for-the-badge&logo=wifi&logoColor=white)
![License](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-EF9421?style=for-the-badge)

**Passive Network Sensor • TCP Monitoring • No Client Responses**

</div>

## 📌 What is this?

ESP32 NetProbe is a passive network monitoring device that listens on TCP ports without responding to clients. Designed for cybersecurity education and network behavior analysis.

---

## 🎯 Two Firmware Versions

| Version | Features | Hardware Required |
|---------|----------|-------------------|
| **Core** | JSON logging, Slow Loris detection, text extraction | ESP32 only |
| **OLED** | All Core features + real-time display, encoder navigation | ESP32 + SSD1306 + KY-040 |

---

## 🚀 Quick Setup

### 1. **Prerequisites**
- Install [Arduino IDE](https://www.arduino.cc/en/software)
- Add ESP32 board support via Boards Manager
- For OLED version: Install `Adafruit SSD1306` and `Adafruit GFX` libraries

### 2. **Configure Wi-Fi**
Edit this in the `.ino` file:

```cpp
// ADD THIS AT THE TOP OF THE FILE
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

## License

This project is licensed under
[CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/)

Commercial use is strictly prohibited.
Author: Doffy
