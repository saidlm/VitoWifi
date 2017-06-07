/*

Copyright 2017 Bert Melis

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/
/*
VitoWifi - Library serial communication with Viessmann heating systems
using the P300 protocol.
for Arduino - ESP8266

Created by: Bert Melis, 2017
Licence: MIT

Using portions or complete code from:
Hex print: 2011, robtillaart @ Arduino.cc forum
Logger: MIT 2015, marvinroger @ Github
Blinker: MIT 2015, marvinroger @ Github

BIG thanks to openv.wikispaces.com
and many others

*/

#pragma once
#include <Arduino.h>
#include <queue>
#include "Helpers/Datatypes.h"
#include "Datapoint.h"
#include "Optolink.h"
#include "Helpers/Logger.h"
#include "Helpers/Blinker.h"


class VitoWifiClass {
  public:
    VitoWifiClass();
    ~VitoWifiClass();
    void setup(HardwareSerial& serial);
    void setup(HardwareSerial* serial);
    void loop();
    void setGlobalCallback(GlobalCallbackFunction globalCallback);
    Datapoint& addDatapoint(const char* name, const char* group, const uint16_t address, const DPType type, bool isWriteable);
    Datapoint& addDatapoint(const char* name, const char* group, const uint16_t address, const DPType type);

    void readAll();
    void readGroup(const char* group);
    void readDatapoint(const char* name);
    void writeDatapoint(const char* name, bool value);
    void writeDatapoint(const char* name, uint8_t value);
    void writeDatapoint(const char* name, float value);

    void enableLed(uint8_t pin, uint8_t on);

    void enableLogger();
    void disableLogger();
    void setLoggingPrinter(Print* printer);
    //Logger& getLogger();  //getter for Logger for use in main sketch.

  private:
    Datapoint* getDatapoint(const char* name);
    std::vector<Datapoint*> _datapoints;
    struct Action {
      Datapoint* DP;
      bool write;
      uint8_t value[4];
    };
    std::queue<Action> _queue;
    bool _isBusy;
    Optolink _optolink;
    bool _enableLed;
    Blinker _blinker;
    Logger _logger;
} extern VitoWifi;
