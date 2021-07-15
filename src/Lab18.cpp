/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/evanh/OneDrive/Desktop/CTD/InternetOfThings/Lab18/src/Lab18.ino"
void callback(char* topic, byte* payload, unsigned int length);
void toDisplay();
void setup();
void loop();
#line 1 "c:/Users/evanh/OneDrive/Desktop/CTD/InternetOfThings/Lab18/src/Lab18.ino"
SYSTEM_THREAD(ENABLED);

#include "MQTT.h"
MQTT client("lab.thewcl.com", 1883, callback);

#include "oled-wing-adafruit.h"
OledWingAdafruit display;

#include <blynk.h>

boolean isLon = true;

double valueLon = 0;
double valueLat = 0;

void callback(char* topic, byte* payload, unsigned int length) {

  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String s = p;
  double value = s.toFloat();
  Serial.printf("%s",p);
  Serial.println();
  Serial.println(value);

  if (isLon){
    valueLon = value;
    isLon = false;
  }
  else{
    valueLat = value;
    isLon = true;
  }

  toDisplay();

  Blynk.virtualWrite(V1, 1, valueLat, valueLon, "value");

}


void toDisplay(){

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Latitude: ");
  display.println(valueLat);
  display.print("Longitude: ");
  display.println(valueLon);
  display.display();
  Serial.println();
}

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.

  Blynk.begin("LvTfSIzRXUuYM9QqgaucvvzhLEAGz5X4", IPAddress(167, 172, 234, 162), 9090);

  display.setup();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  display.display();
  Serial.begin(9600);
  
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  Blynk.run();
  // The core of your code will likely live here.
  display.loop();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  if (client.isConnected()) {
    client.loop();
  } 
  else {
    client.connect(System.deviceID());
    client.subscribe("evanlee");
  }
}
