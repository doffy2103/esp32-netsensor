# ⚙️ Setup Guide

<div align="center">

![Arduino IDE](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![ESP32](https://img.shields.io/badge/ESP32-E53529?style=for-the-badge&logo=espressif&logoColor=white)
![OLED](https://img.shields.io/badge/OLED-SSD1306-00FF00?style=for-the-badge&logo=display&logoColor=white)

</div>

---

## 📝 **Prerequisites**
- 💻 **Arduino IDE** installed  
- 🛠️ **ESP32 board support** installed via **Boards Manager**  
- 📚 **Libraries** (for OLED version):
  - `Adafruit SSD1306`
  - `Adafruit GFX`

---

## 🚀 **Uploading Firmware**
1. 🔹 Open the `.ino` file in **Arduino IDE**  
2. 🔹 Select the correct **ESP32 board** in `Tools > Board`  
3. 🔹 Set the correct **COM port**  
4. 🔹 Edit **Wi-Fi credentials** at the top of the file:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```
5. 🔹 Click Upload

📟 Serial Monitoring

[*] Open Serial Monitor at 115200 baud

[*] Core firmware logs JSON events for each TCP connection

[*] OLED firmware displays logs on the screen in real time

⚠️ Notes

[*] Both Core and OLED firmware are passive sensors; they do not respond to clients

[*] OLED firmware supports an optional rotary encoder, which can be removed if not needed
