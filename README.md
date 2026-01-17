# ESP32 Netsensor 🔍

<div align="center">

![ESP32](https://img.shields.io/badge/ESP32-E53529?style=for-the-badge&logo=espressif&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![WiFi](https://img.shields.io/badge/WiFi-1A73E8?style=for-the-badge&logo=wifi&logoColor=white)
![License](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-EF9421?style=for-the-badge)

**Passive Network Sensor • TCP Monitoring • No Client Responses**

</div>

## 📌 What is this?

ESP32 Netsensor is a passive network monitoring device that listens on TCP ports without responding to clients. Designed for cybersecurity education and network behavior analysis.

---

## 🎯 Firmware Versions

| Version | Features | Hardware Required | Documentation |
|---------|----------|-----------------|---------------|
| **[Core](firmware/core.ino)** | JSON logging, Slow Loris detection, text extraction | ESP32 only | [Core Docs](docs/core.md) |
| **[Oled](firmware/oled.ino)** | All Core features + real-time display, encoder navigation | ESP32 + SSD1306 + KY-040 | [OLED Docs](docs/oled.md) |

---

## 🚀 Quick Setup

For full setup instructions, see [Setup Guide](docs/setup.md)

### 1. **Prerequisites**
- Arduino IDE
- ESP32 board support
- For OLED: Adafruit SSD1306 + GFX libraries

### 2. **Configure Wi-Fi**
Edit this in your `.ino` file:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

## License This project is licensed under [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/) Commercial use is strictly prohibited. Author: Doffy
