#include <DHT.h>
#include <DHT_U.h>

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"


#define DHTPIN 1     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

int bitsresultados[6];
int passagem= 0;

// Variables used on this code
unsigned long time1;
unsigned long previousTime;
boolean enterFunction = true;
unsigned long time2;
unsigned long previousTime2;
boolean enterFunction2 = true;
//-----------------------

int digitoaentrar = 1;
float h;
float t;
float f;

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 3 (on the right) of the sensor to GROUND (if your sensor has 3 pins)
// Connect pin 4 (on the right) of the sensor to GROUND and leave the pin 3 EMPTY (if your sensor has 4 pins)
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  dht.begin();
  Serial.begin(9600);
}

void loop() {

  time1 = micros();
  time2 = micros();
  if (enterFunction == true) {
    previousTime = time1;
    passagem++;
    // Start your code below
    //-----------------------

    
    for (int i = 0; i < 6; i++) {

      bitsresultados[i] = bitRead(int(round(t)), i);
      
    }

    if (digitoaentrar == 1 && passagem == 1) {
      if (bitsresultados[0] == 1) {
        pinMode(2, OUTPUT);
        pinMode(3, OUTPUT);
        pinMode(4, INPUT);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
      }
      digitoaentrar = 2;
    }
    if (digitoaentrar == 2 && passagem == 2) {
      if (bitsresultados[1] == 1) {
        pinMode(2, OUTPUT);
        pinMode(3, OUTPUT);
        pinMode(4, INPUT);
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
      }
      digitoaentrar = 3;
    }
    if (digitoaentrar == 3 && passagem == 3) {
      if (bitsresultados[2] == 1) {
        pinMode(2, INPUT);
        pinMode(3, OUTPUT);
        pinMode(4, OUTPUT);
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
      }
      digitoaentrar = 4;
    }
    if (digitoaentrar == 4 && passagem == 4) {
      if (bitsresultados[3] == 1) {
        pinMode(2, INPUT);
        pinMode(3, OUTPUT);
        pinMode(4, OUTPUT);
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
      }
      digitoaentrar = 5;
    }
    if (digitoaentrar == 5 && passagem == 5) {
      if (bitsresultados[4] == 1) {
        pinMode(2, OUTPUT);
        pinMode(3, INPUT);
        pinMode(4, OUTPUT);
        digitalWrite(2, HIGH);
        digitalWrite(4, LOW);
      }
      digitoaentrar = 6;
    }
    if (digitoaentrar == 6 && passagem == 6) {
      if (bitsresultados[5] == 1) {
        pinMode(2, OUTPUT);
        pinMode(3, INPUT);
        pinMode(4, OUTPUT);
        digitalWrite(2, LOW);
        digitalWrite(4, HIGH);
      }
      digitoaentrar= 1;
      passagem= 0;
    }

    //-----------------------
    // End of your code
  }

  if (enterFunction2 == true) {
    previousTime2 = time2;

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    //h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    //f = dht.readTemperature(true);

    
   /* // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }*/

    /*// Compute heat index in Fahrenheit (the default)
    float hif = dht.computeHeatIndex(f, h);
    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);*/
    

  }


  // The DELAY time is adjusted in the constant below >>
  if (time1 - previousTime < 990) { // 1 million microsencods= 1 second delay
    /* I have actually used 0.999990 seconds, in a trial to compensate the time that
       this IF function takes to be executed. this is really a point that
       need improvement in my code */
    enterFunction = false;
  }
  else {
    enterFunction = true;
  }
  if (time2 - previousTime2 < 999990) { // 1 million microsencods= 1 second delay
    /* I have actually used 0.999990 seconds, in a trial to compensate the time that
       this IF function takes to be executed. this is really a point that
       need improvement in my code */
    enterFunction2 = false;
  }
  else {
    enterFunction2 = true;
  }

}
