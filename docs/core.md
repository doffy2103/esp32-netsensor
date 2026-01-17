# Core Firmware

- Overview -
This is the basic ESP32 firmware for passive TCP network monitoring. It listens on a port, logs connections in JSON format, and can detect slow loris attacks.

- Features -
- TCP server listening on configurable port
- JSON logging for connections
- Slow Loris attack detection
- Optional verbose debug output
- Passive mode - no responses to clients

- Usage -
1. Open the `.ino` file in Arduino IDE.
2. Set Wi-Fi credentials at the top:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

