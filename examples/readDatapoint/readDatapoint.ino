#include <ESP8266WiFi.h>
#include <VitoWifi.h>

/*

This example defines 2 datapoints of type "TEMP".
Every 30 seconds, the loop function call the updateAll-method.

For each Datapoint, the read value is returned using globalCallbackHandler

*/

const char* ssid     = "XXXX";
const char* password = "XXXX";


void globalCallbackHandler(const char* name, const char* group, const char* value) {
  Serial1.print(group);
  Serial1.print(" - ");
  Serial1.print(name);
  Serial1.print(": ");
  Serial1.println(value);
}


void setup() {
  //setup VitoWifi using a global callback handler
  VitoWifi.addDatapoint("outsidetemp", "boiler", 0x5525, TEMP);
  VitoWifi.addDatapoint("boilertemp",  "boiler", 0x0810, TEMP);
  VitoWifi.setGlobalCallback(globalCallbackHandler);
  VitoWifi.setup(&Serial);

  Serial1.begin(115200);
  Serial1.println(F("Connecting to Wifi..."));
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial1.println(F("IP address: "));
  Serial1.println(WiFi.localIP());
}

void loop() {

  static unsigned long lastMillis = 0;
  if (millis() - lastMillis > 30 * 1000UL) {  //read all values every 30 seconds
    lastMillis = millis();
    VitoWifi.readDatapoint("outsidetemp");
  }

  VitoWifi.loop();
}
