# 🖥️ OLED Firmware

<div align="center">

![ESP32](https://img.shields.io/badge/ESP32-E53529?style=for-the-badge&logo=espressif&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![OLED](https://img.shields.io/badge/OLED-SSD1306-00FF00?style=for-the-badge&logo=display&logoColor=white)
![WiFi](https://img.shields.io/badge/WiFi-1A73E8?style=for-the-badge&logo=wifi&logoColor=white)

</div>

## 📋 **Overview**  
This firmware extends the Core firmware with a real-time display using an SSD1306 OLED screen. It also optionally supports a rotary encoder to scroll through logs.

## ✨ **Features**  
- 🟢 All Core features (JSON logging, passive monitoring, slow loris detection)  
- 🟢 Real-time log display on OLED  
- 🟢 Optional rotary encoder navigation  
- 🟢 Logs truncated to 22 characters for display  
- 🟢 Passive TCP monitoring (no responses sent to clients)  

## 🔌 **Wiring**  

### **OLED (SSD1306, I2C):** 
- 📌 VCC → 3.3V
- 📌 GND → GND
- 📌 SDA → GPIO 21
- 📌 SCL → GPIO 22
### **Optional Rotary Encoder (KY-040):**  
- 📌 CLK → GPIO 32
- 📌 DT → GPIO 33
- 📌 SW → GPIO 25

> ⚠️ **Note:** If you don't use the encoder, comment out all `ENC_*` lines and the `read_encoder()` function.

## 🚀 **Usage**  
1. 🔌 Connect OLED and optional encoder to the ESP32  
2. 💻 Open the `.cpp` file in Arduino IDE  
3. 🔐 Set Wi-Fi credentials at the top of the code:  

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

📤 Upload the sketch to your ESP32

📟 Open Serial Monitor at 115200 baud if you want to see JSON logs

👁️ Logs will appear on the OLED display automatically



💻 TCP Commands Examples: 

Windows(PowerShell):
```
$tcp = New-Object System.Net.Sockets.TcpClient("192.168.1.100", 2323)
$stream = $tcp.GetStream()
$writer = New-Object System.IO.StreamWriter($stream)
$writer.WriteLine("Hello ESP32")
$writer.Flush()
$tcp.Close()
```
Linux / macOS: 
```
echo "Hello ESP32" | nc 192.168.1.100 2323
```

Termux(Android): 
```
echo "Hello ESP32" | nc 192.168.1.100 2323
```

📟 Expected Output on OLED
After sending a message, the OLED will display:

┌─────────────────────────┐
│      TCP MONITOR        │
├─────────────────────────┤
│ CONNECT 192.168.1.50    │
│ Hello ESP32             │
│ CLOSE                   │
└─────────────────────────┘
