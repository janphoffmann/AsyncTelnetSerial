
#include "AsyncTelnetSerial.h"

AsyncTelnetSerial Test(&Serial);

void setup() {
  WiFi.disconnect(true, true);
  delay(200);
  WiFi.mode(WIFI_STA);
  WiFi.begin("ssid","password");
  if (WiFi.waitForConnectResult() != WL_CONNECTED) return;
  WiFi.setAutoReconnect(true);

  Test.begin(); // AsyncTelnetSerial::begin(unsigned long baudrate = 115200, bool LinkTelnetToSerial = true, bool enableMDNS = false);
}

void loop() {

}
