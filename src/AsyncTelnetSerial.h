#pragma once
#ifndef AsyncTelnetSerial_h
#define AsyncTelnetSerial_h

#include <HardwareSerial.h>
#include "AsyncTelnet.h"

typedef std::function<void(const char *response, size_t len)> SerialResponseHandler;

class AsyncTelnetSerial: public AsyncTelnet {

  public:
    AsyncTelnetSerial(HardwareSerial *serial);
    bool begin(unsigned long baudrate = 115200, bool LinkTelnetToSerial = true, bool enableMDNS = false);

    void onSerialResponse(SerialResponseHandler callbackFunc);

    SerialResponseHandler _serial_response_cb = NULL;
  private:
    HardwareSerial *_serial;

};

#endif