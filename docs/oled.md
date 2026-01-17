# OLED Firmware

- **Overview** -  
This firmware extends the Core firmware with a real-time display using an SSD1306 OLED screen. It also optionally supports a rotary encoder to scroll through logs.

- **Features** -  
- All Core features (JSON logging, passive monitoring, slow loris detection)  
- Real-time log display on OLED  
- Optional rotary encoder navigation  
- Logs truncated to 22 characters for display  
- Passive TCP monitoring (no responses sent to clients)  

- **Wiring** -  
**OLED (SSD1306, I2C):**  
- VCC → 3.3V  
- GND → GND  
- SDA → GPIO 21  
- SCL → GPIO 22  

**Optional Rotary Encoder (KY-040):**  
- CLK → GPIO 32  
- DT → GPIO 33  
- SW → GPIO 25  

> If you don't use the encoder, comment out all `ENC_*` lines and the `read_encoder()` function.

- **Usage** -  
1. Connect OLED and optional encoder to the ESP32.  
2. Open the `.cpp` file in Arduino IDE.  
3. Set Wi-Fi credentials at the top of the code:  
const char* ssid = "YOUR_WIFI_NAME";  
const char* password = "YOUR_WIFI_PASSWORD";  

4. Upload the sketch to your ESP32.  
5. Open Serial Monitor at 115200 baud if you want to see JSON logs.  
6. Logs will appear on the OLED display automatically.  

- **TCP Commands Examples** -  
You can test the device by sending simple TCP messages to the ESP32 IP on the configured port (default 2323).

💻 Windows (PowerShell):  
# Connect to ESP32 IP on port 2323  
$tcp = New-Object System.Net.Sockets.TcpClient("192.168.1.100", 2323)  
$stream = $tcp.GetStream()  
$writer = New-Object System.IO.StreamWriter($stream)  
# Send a message  
$writer.WriteLine("Hello ESP32")  
$writer.Flush()  
# Close connection  
$tcp.Close()  
# Replace "192.168.1.100" with your ESP32 IP displayed on OLED  

🐧 Linux / macOS Terminal:  
# Using netcat to send a message to ESP32  
echo "Hello ESP32" | nc 192.168.1.100 2323  
# Replace 192.168.1.100 with your ESP32 IP displayed on OLED  

🤖 Termux (Android Terminal):  
# Using netcat to send a message to ESP32  
echo "Hello ESP32" | nc 192.168.1.100 2323  
# Replace 192.168.1.100 with your ESP32 IP displayed in Serial Monitor  

- **Expected Output on OLED** -  
After sending a message, the OLED will display:  
TCP MONITOR  
----------------  
CONNECT 192.168.1.50  
Hello ESP32  
CLOSE
