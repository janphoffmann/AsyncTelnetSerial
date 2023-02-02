
#include "AsyncTelnetSerial.h"

AsyncTelnetSerial Test(&Serial);

void data_cb_f(const char *data, size_t len){
  Serial.write(data,len);
}
void conn_cb_f(void*, AsyncClient* c){
  Serial.print("Client connected");
}
void serial_data_cb_f(const char *response, size_t len){
  Test.write(response,len);
}

void setup() {
  WiFi.disconnect(true, true);
  delay(200);
  WiFi.mode(WIFI_STA);
  WiFi.begin("Hoffmann","7!house8");
  if (WiFi.waitForConnectResult() != WL_CONNECTED) return;
  WiFi.setAutoReconnect(true);

  Test.onConnect(conn_cb_f);
  Test.onTelnetResponse(data_cb_f);
  Test.onSerialResponse(serial_data_cb_f);
  Test.begin();

}

void loop() {

}
