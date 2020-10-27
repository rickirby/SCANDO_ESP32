#include <WiFi.h>

const String PROJECT_VERSION = "0.0.0";

void setup() {
  commonSetting();
  loadVersion();
}

void loop() {
  
}

void commonSetting() {
  Serial.begin(115200);
}

void loadVersion() {
  Serial.println();
  Serial.println("============================");
  Serial.println("     RB_QueenMaster_Esp");
  Serial.println("       Version  " + PROJECT_VERSION);
  Serial.println(" Created by Ricki Bin Yamin");
  Serial.println("============================");
  Serial.println();
}
