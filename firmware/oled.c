#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// - WIFI -
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// - TCP -
#define LISTEN_PORT       2323
#define MAX_BYTES         4096
#define MAX_PACKETS       50
#define MAX_DURATION_MS   15000
#define SLOW_LORIS_BYTES  20
#define SLOW_LORIS_TIME   8000

// - OLED -
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// - ENCODER (OPTIONAL) -
// Если не нужен, закомментируйте эти строки и все обращения к энкодеру
#define ENC_A 32
#define ENC_B 33
#define ENC_BTN 25

int lastEncA = HIGH;
int scrollIndex = 0;

// - LOG BUFFER -
#define LOG_LINES 10
String logs[LOG_LINES];
int logCount = 0;

// - SERVER -
WiFiServer server(LISTEN_PORT);

// - UTILS -
void push_log(String text) {
    if (logCount < LOG_LINES) {
        logs[logCount++] = text;
    } else {
        for (int i = 1; i < LOG_LINES; i++)
            logs[i - 1] = logs[i];
        logs[LOG_LINES - 1] = text;
    }
}

String extract_text(uint8_t* buf, int len) {
    String out = "";
    for (int i = 0; i < len; i++) {
        char c = buf[i];
        if (c >= 32 && c <= 126) out += c;
    }
    if (out.length() > 22) {
        out = out.substring(0, 22) + "...";
    }
    return out;
}

// - OLED DRAW -
void draw_oled() {
    display.clearDisplay();
    display.setCursor(0, 0);

    display.println("TCP MONITOR");
    display.println("----------------");

    int start = scrollIndex;
    for (int i = 0; i < 4; i++) {
        int idx = start + i;
        if (idx < logCount) {
            display.println(logs[idx]);
        }
    }

    display.display();
}

// - ENCODER READ (OPTIONAL) -
void read_encoder() {
    // If you don't need the encoder, you can remove this section.
#ifdef ENC_A
    int a = digitalRead(ENC_A);

    if (a != lastEncA) {
        if (digitalRead(ENC_B) != a) scrollIndex++;
        else scrollIndex--;

        if (scrollIndex < 0) scrollIndex = 0;
        if (scrollIndex > logCount - 1) scrollIndex = logCount - 1;

        draw_oled();
    }
    lastEncA = a;
#endif
}

// - JSON LOG -
void log_json(const char* event, IPAddress ip, int bytes, int packets, unsigned long dur) {
    Serial.printf(
        "{\"event\":\"%s\",\"src\":\"%s\",\"bytes\":%d,\"packets\":%d,\"duration_ms\":%lu}\n",
        event,
        ip.toString().c_str(),
        bytes,
        packets,
        dur
    );
}

// - HANDLE CLIENT -
void handle_client(WiFiClient& client) {
    IPAddress ip = client.remoteIP();
    unsigned long start = millis();
    int totalBytes = 0;
    int packets = 0;

    push_log("CONNECT " + ip.toString());
    draw_oled();
    log_json("connection_open", ip, 0, 0, 0);

    while (client.connected()) {
        if (!client.available()) {
            delay(10);
            if (millis() - start > MAX_DURATION_MS) break;
            continue;
        }

        uint8_t buf[256];
        int len = client.read(buf, sizeof(buf));
        if (len <= 0) break;

        totalBytes += len;
        packets++;

        String msg = extract_text(buf, len);
        if (msg.length() > 0) {
            push_log(msg);
            draw_oled();
        }
    }

    unsigned long dur = millis() - start;

    if (totalBytes < SLOW_LORIS_BYTES && dur > SLOW_LORIS_TIME) {
        push_log("SLOW LORIS DETECT");
        log_json("slow_loris_detected", ip, totalBytes, packets, dur);
    } else {
        push_log("CLOSE");
        log_json("connection_closed", ip, totalBytes, packets, dur);
    }

    draw_oled();
    client.stop();
}

// - SETUP -
void setup() {
    Serial.begin(115200);

#ifdef ENC_A
    pinMode(ENC_A, INPUT_PULLUP);
    pinMode(ENC_B, INPUT_PULLUP);
    pinMode(ENC_BTN, INPUT_PULLUP);
#endif

    Wire.begin();

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("BOOT...");
    display.display();

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) delay(300);

    server.begin();

    push_log("READY");
    push_log(WiFi.localIP().toString());
    draw_oled();
}

// - LOOP -
void loop() {
    read_encoder();

    WiFiClient client = server.available();
    if (client) handle_client(client);
}

