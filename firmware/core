#include <WiFi.h>

// - WIFI -
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// - NETCAT-LIKE CONFIG -
#define LISTEN_PORT        2323
#define MAX_BYTES          4096
#define MAX_PACKETS        50
#define MAX_DURATION_MS    10000
#define SLOW_LORIS_BYTES   20
#define SLOW_LORIS_TIME    8000

// - FLAGS -
#define FLAG_LOG_JSON     true
#define FLAG_DETECT_SLOW  true
#define FLAG_RATE_LIMIT   true
#define FLAG_DROP_DATA    true
#define FLAG_VERBOSE      true

WiFiServer server(LISTEN_PORT);

// - LOGGING -
void log_json(
    const char* event,
    IPAddress ip,
    int bytes,
    int packets,
    unsigned long duration
) {
    if (!FLAG_LOG_JSON) return;

    Serial.printf(
        "{\"event\":\"%s\",\"src\":\"%s\",\"bytes\":%d,\"packets\":%d,\"duration_ms\":%lu}\n",
        event,
        ip.toString().c_str(),
        bytes,
        packets,
        duration
    );
}

// - SETUP -
void setup() {
    Serial.begin(115200);
    delay(1000);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    Serial.print("[*] Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\n[*] Connected");
    Serial.print("[*] IP: ");
    Serial.println(WiFi.localIP());

    server.begin();
    server.setNoDelay(true);

    log_json("listener_started", WiFi.localIP(), 0, 0, 0);
}

// - HANDLE CLIENT -
void handle_client(WiFiClient& client) {
    IPAddress ip = client.remoteIP();
    unsigned long start = millis();
    int totalBytes = 0;
    int packets = 0;

    log_json("connection_open", ip, 0, 0, 0);
    client.setTimeout(150000);

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

        // DEBUG PAYLOAD
        if (FLAG_VERBOSE) {
            Serial.print("[DATA] ");
            for (int i = 0; i < len; i++) {
                Serial.write(buf[i]);
            }
            Serial.println();
        }

        // FLAG_DROP_DATA = passive sensor
    }

    unsigned long duration = millis() - start;

    if (FLAG_DETECT_SLOW && totalBytes < SLOW_LORIS_BYTES && duration > SLOW_LORIS_TIME) {
        log_json("slow_loris_detected", ip, totalBytes, packets, duration);
    } else {
        log_json("connection_closed", ip, totalBytes, packets, duration);
    }

    client.stop();
}

// - LOOP -
void loop() {
    WiFiClient client = server.available();
    if (client) {
        handle_client(client);
    }
}

