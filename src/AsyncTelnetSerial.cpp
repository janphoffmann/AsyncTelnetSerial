#include "AsyncTelnetSerial.h"

AsyncTelnetSerial::AsyncTelnetSerial(HardwareSerial *serial) {
  _serial = serial;
}

bool AsyncTelnetSerial::begin(unsigned long baudrate, bool LinkTelnetToSerial, bool enableMDNS){

  if(!LinkTelnetToSerial){
    if(_serial_response_cb != NULL) _serial->onReceive([=](void) {
      while(_serial->available()){
        size_t l = _serial->available();
        uint8_t b[l];
        l = _serial->read(b, l);
        _serial_response_cb((const char *)b, l);
      }
    });
    _serial->begin(baudrate);
    AsyncTelnet::begin(true, enableMDNS);
    return true;
  }
  else{
    if(enableMDNS){
      if (WiFi.status() != WL_CONNECTED) return false;
      if (!MDNS.begin("esp32")) {
        Serial.println("Error setting up MDNS responder!");
        while(1) {
            delay(1000);
        }
      }
      MDNS.addService("http", "tcp", 80);
    }
    _serial->onReceive([=](void) {
      while(_serial->available()){
        size_t l = _serial->available();
        uint8_t b[l];
        l = _serial->read(b, l);
        AsyncTelnet::write((const char *)b, l);
      }
    });
    if (WiFi.status() != WL_CONNECTED) return false;
    server.onClient([=](void *, AsyncClient* c){
      if(c == NULL) return;
      client = c;
      // client->setRxTimeout(10);
      ip = client->remoteIP();
      if(on_connect != NULL) client->onConnect(on_connect, client); 
      c->onDisconnect([=](void *, AsyncClient* c){ 
        if(on_disconnect != NULL) on_disconnect(c); 
        c->close(true);
        c->free();
        delete c;
      }, this);
      c->onData([=](void *, AsyncClient* , void *data, size_t len){ 
        // Serial.println("data incoming");
        _serial->write((const char *)data, len); 
      }, this);      
      client->setNoDelay(true);
    }, this);
    server.setNoDelay(true);
    server.begin();
    _serial->begin(baudrate);
  }
  return true;
}

void AsyncTelnetSerial::onSerialResponse(SerialResponseHandler callbackFunc){
  _serial_response_cb = callbackFunc;
}
