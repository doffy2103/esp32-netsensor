# 🧠 Core Firmware

<div align="center">

![ESP32](https://img.shields.io/badge/ESP32-E53529?style=for-the-badge&logo=espressif&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![TCP](https://img.shields.io/badge/TCP-Passive%20Monitor-4CAF50?style=for-the-badge)
![JSON](https://img.shields.io/badge/Logs-JSON-000000?style=for-the-badge&logo=json&logoColor=white)

</div>

## 📋 **Overview**  
This is the core ESP32 firmware designed for **passive TCP network monitoring**.  
It listens on a configurable port, logs all activity in **JSON format**, and is capable of detecting **Slow Loris–style attacks**.

The firmware operates in **passive mode**, meaning it never responds to clients — it only observes and logs traffic.

---

## ✨ **Features**
- 🟢 TCP server listening on configurable port  
- 🟢 Passive monitoring (no responses sent)  
- 🟢 JSON-formatted connection logs  
- 🟢 Slow Loris attack detection  
- 🟢 Optional verbose debug output  
- 🟢 Rate limiting and packet tracking  

---

## 🚀 **Usage**

1. 💻 Open the `.ino` file in **Arduino IDE**
2. 🔐 Set your Wi‑Fi credentials at the top of the file:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

3. 📤 Upload the sketch to your ESP32

4. 📟 Open Serial Monitor at 115200 baud to view JSON logs

⚙️ Configuration: 
```
Network & Limits:

#define LISTEN_PORT        2323
#define MAX_BYTES          4096
#define MAX_PACKETS        50
#define MAX_DURATION_MS    10000
#define SLOW_LORIS_BYTES   20
#define SLOW_LORIS_TIME    8000


Feature Flags:

#define FLAG_LOG_JSON     true
#define FLAG_DETECT_SLOW  true
#define FLAG_RATE_LIMIT   true
#define FLAG_DROP_DATA    true
#define FLAG_VERBOSE      true

```

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

📟 Expected Output on Serial Desplay: 
```
[*] Connected
[*] IP: 10.20.67.88

#example after connection
{"event":"listener_started","src":"10.20.67.88","bytes":0,"packets":0,"duration_ms":0}
```
