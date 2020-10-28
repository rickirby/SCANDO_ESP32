#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <ESPAsyncWebServer.h>
#include <ProjectHeader.hpp>

void commonSetting() {
    Serial.begin(115200);
    ProjectHeader::loadHeader();
}

void wifiSetting() {
    // Set WiFi to both mode
    // Serial.println("Configuring WiFi Mode...");
    // WiFi.mode(WIFI_AP_STA);
    // delay(100);

    // // Access Point Setup
    // Serial.println("Configuring Access Point...");
    // WiFi.softAP("SCANDO_hardware", "scandohardware");
    // IPAddress hardwareIPAddress = WiFi.softAPIP();
    // Serial.println();
    // Serial.print("Hardware IP Address: ");
    // Serial.println(hardwareIPAddress);

    // WiFi Client Setup
    WiFi.begin("Ricki", "rickibinyamin");
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println("Ricki");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

AsyncWebServer server(80);

void setup() {
    commonSetting();
    wifiSetting();
    Serial.println(WiFi.localIP());
    server.on(
        "/post",
        HTTP_POST,
        [](AsyncWebServerRequest * request){},
        NULL,
        [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
            Serial.println("GOT");
            delay(1000);
            for (size_t i = 0; i < len; i++) {
                Serial.write(data[i]);
            }
            Serial.println();
            request->send(200);
    });
    
    server.begin();
}

void loop() {
    // Serial.println("HALO");
    // delay(1000);
}
