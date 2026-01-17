<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>OLED Firmware Documentation</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }
        
        body {
            background: linear-gradient(135deg, #0f0c29, #302b63, #24243e);
            color: #fff;
            min-height: 100vh;
            padding: 20px;
        }
        
        .container {
            max-width: 1000px;
            margin: 0 auto;
            background: rgba(20, 20, 40, 0.9);
            border-radius: 20px;
            padding: 30px;
            box-shadow: 0 15px 35px rgba(0, 0, 0, 0.5);
            border: 1px solid rgba(100, 100, 255, 0.2);
        }
        
        h1 {
            text-align: center;
            color: #4fc3f7;
            font-size: 2.8em;
            margin-bottom: 30px;
            text-shadow: 0 0 15px rgba(79, 195, 247, 0.5);
            padding-bottom: 15px;
            border-bottom: 3px solid #4fc3f7;
        }
        
        h2 {
            color: #ff9800;
            margin: 25px 0 15px;
            font-size: 1.8em;
            padding-left: 15px;
            border-left: 5px solid #ff9800;
        }
        
        h3 {
            color: #69f0ae;
            margin: 20px 0 10px;
            font-size: 1.4em;
        }
        
        .section {
            background: rgba(30, 30, 60, 0.7);
            border-radius: 12px;
            padding: 20px;
            margin: 20px 0;
            border: 1px solid rgba(100, 150, 255, 0.2);
            transition: transform 0.3s;
        }
        
        .section:hover {
            transform: translateY(-5px);
            box-shadow: 0 10px 25px rgba(0, 0, 0, 0.3);
        }
        
        .wiring-table {
            width: 100%;
            border-collapse: collapse;
            margin: 15px 0;
            background: rgba(40, 40, 80, 0.8);
            border-radius: 8px;
            overflow: hidden;
        }
        
        .wiring-table th {
            background: linear-gradient(90deg, #4fc3f7, #2196f3);
            color: #000;
            padding: 15px;
            text-align: left;
            font-weight: bold;
        }
        
        .wiring-table td {
            padding: 12px 15px;
            border-bottom: 1px solid rgba(100, 100, 200, 0.3);
        }
        
        .wiring-table tr:last-child td {
            border-bottom: none;
        }
        
        .wiring-table tr:hover {
            background: rgba(79, 195, 247, 0.15);
        }
        
        .wiring-table .pin-name {
            color: #69f0ae;
            font-weight: bold;
        }
        
        .wiring-table .pin-value {
            color: #ff9800;
        }
        
        .feature-list {
            list-style: none;
            padding-left: 20px;
        }
        
        .feature-list li {
            padding: 8px 0;
            position: relative;
        }
        
        .feature-list li:before {
            content: "✓";
            color: #69f0ae;
            font-weight: bold;
            position: absolute;
            left: -20px;
        }
        
        .code-block {
            background: #1e1e2e;
            border-radius: 10px;
            padding: 20px;
            margin: 15px 0;
            border-left: 5px solid #ff9800;
            overflow-x: auto;
            font-family: 'Courier New', monospace;
        }
        
        .code-block code {
            color: #e6db74;
            font-size: 1em;
            line-height: 1.5;
        }
        
        .command-block {
            background: rgba(40, 40, 60, 0.8);
            border-radius: 8px;
            padding: 15px;
            margin: 10px 0;
            border-left: 5px solid #4fc3f7;
        }
        
        .command-title {
            color: #4fc3f7;
            font-weight: bold;
            margin-bottom: 10px;
            display: flex;
            align-items: center;
        }
        
        .command-title:before {
            content: "▶";
            margin-right: 10px;
            color: #ff9800;
        }
        
        .warning {
            background: rgba(255, 152, 0, 0.15);
            border: 1px solid rgba(255, 152, 0, 0.5);
            border-radius: 8px;
            padding: 15px;
            margin: 15px 0;
            color: #ffcc80;
        }
        
        .warning:before {
            content: "⚠";
            color: #ff9800;
            font-weight: bold;
            margin-right: 10px;
        }
        
        .oled-output {
            background: #000;
            color: #0f0;
            font-family: 'Courier New', monospace;
            padding: 20px;
            border-radius: 8px;
            margin: 15px 0;
            border: 2px solid #444;
            line-height: 1.4;
            white-space: pre;
        }
        
        .footer {
            text-align: center;
            margin-top: 30px;
            padding-top: 20px;
            border-top: 1px solid rgba(100, 100, 255, 0.3);
            color: #aaa;
            font-size: 0.9em;
        }
        
        @media (max-width: 768px) {
            .container {
                padding: 15px;
            }
            
            h1 {
                font-size: 2em;
            }
            
            .wiring-table {
                font-size: 0.9em;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🖥️ OLED Firmware Documentation</h1>
        
        <div class="section">
            <h2>📋 Overview</h2>
            <p>This firmware extends the Core firmware with a real-time display using an SSD1306 OLED screen. It also optionally supports a rotary encoder to scroll through logs.</p>
        </div>
        
        <div class="section">
            <h2>✨ Features</h2>
            <ul class="feature-list">
                <li>All Core features (JSON logging, passive monitoring, slow loris detection)</li>
                <li>Real-time log display on OLED</li>
                <li>Optional rotary encoder navigation</li>
                <li>Logs truncated to 22 characters for display</li>
                <li>Passive TCP monitoring (no responses sent to clients)</li>
            </ul>
        </div>
        
        <div class="section">
            <h2>🔌 Wiring</h2>
            
            <h3>OLED (SSD1306, I2C):</h3>
            <table class="wiring-table">
                <thead>
                    <tr>
                        <th>OLED Pin</th>
                        <th>ESP32 Pin</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td class="pin-name">VCC</td>
                        <td class="pin-value">3.3V</td>
                    </tr>
                    <tr>
                        <td class="pin-name">GND</td>
                        <td class="pin-value">GND</td>
                    </tr>
                    <tr>
                        <td class="pin-name">SDA</td>
                        <td class="pin-value">GPIO 21</td>
                    </tr>
                    <tr>
                        <td class="pin-name">SCL</td>
                        <td class="pin-value">GPIO 22</td>
                    </tr>
                </tbody>
            </table>
            
            <h3>Optional Rotary Encoder (KY-040):</h3>
            <table class="wiring-table">
                <thead>
                    <tr>
                        <th>Encoder Pin</th>
                        <th>ESP32 Pin</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td class="pin-name">CLK</td>
                        <td class="pin-value">GPIO 32</td>
                    </tr>
                    <tr>
                        <td class="pin-name">DT</td>
                        <td class="pin-value">GPIO 33</td>
                    </tr>
                    <tr>
                        <td class="pin-name">SW</td>
                        <td class="pin-value">GPIO 25</td>
                    </tr>
                </tbody>
            </table>
            
            <div class="warning">
                If you don't use the encoder, comment out all ENC_* lines and the read_encoder() function.
            </div>
        </div>
        
        <div class="section">
            <h2>🚀 Usage</h2>
            <ol>
                <li>Connect OLED and optional encoder to the ESP32</li>
                <li>Open the .cpp file in Arduino IDE</li>
                <li>Set Wi-Fi credentials at the top of the code:</li>
            </ol>
            
            <div class="code-block">
                <code>const char* ssid = "YOUR_WIFI_NAME";<br>const char* password = "YOUR_WIFI_PASSWORD";</code>
            </div>
            
            <ol start="4">
                <li>Upload the sketch to your ESP32</li>
                <li>Open Serial Monitor at 115200 baud if you want to see JSON logs</li>
                <li>Logs will appear on the OLED display automatically</li>
            </ol>
        </div>
        
        <div class="section">
            <h2>💻 TCP Commands Examples</h2>
            
            <div class="command-block">
                <div class="command-title">Windows (PowerShell)</div>
                <div class="code-block">
                    <code># Connect to ESP32 on port 2323<br>$tcp = New-Object System.Net.Sockets.TcpClient("192.168.1.100", 2323)<br>$stream = $tcp.GetStream()<br>$writer = New-Object System.IO.StreamWriter($stream)<br># Send a message<br>$writer.WriteLine("Hello ESP32")<br>$writer.Flush()<br># Close connection<br>$tcp.Close()</code>
                </div>
            </div>
            
            <div class="command-block">
                <div class="command-title">Linux / macOS</div>
                <div class="code-block">
                    <code>echo "Hello ESP32" | nc 192.168.1.100 2323</code>
                </div>
            </div>
            
            <div class="command-block">
                <div class="command-title">Termux (Android)</div>
                <div class="code-block">
                    <code>echo "Hello ESP32" | nc 192.168.1.100 2323</code>
                </div>
            </div>
            
            <div class="warning">
                Replace 192.168.1.100 with your ESP32 IP as shown on the OLED display
            </div>
        </div>
        
        <div class="section">
            <h2>📟 Expected Output on OLED</h2>
            <p>After sending a message, the OLED will display:</p>
            <div class="oled-output">TCP MONITOR
----------------
CONNECT 192.168.1.50
Hello ESP32
CLOSE</div>
        </div>
        
        <div class="footer">
            <p>OLED Firmware Documentation | ESP32 SSD1306 Display</p>
        </div>
    </div>
</body>
</html>


