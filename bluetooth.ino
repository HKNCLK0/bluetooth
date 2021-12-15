#include "DHT.h"
#include <SoftwareSerial.h>
#include <Wire.h>

#define DHTPIN 12

#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial bt(7, 8);

int sensorPin = A0;
int sensorValue = 0;
int percentValue = 0;
const int LDR_PIN = A1;

void setup()
{
  Serial.begin(9600);
  bt.begin(9600);
  dht.begin();
  Wire.begin();
  pinMode(LDR_PIN, INPUT);
}

void loop()
{
  if (bt.available() > 0)
  {
    int h = dht.readHumidity();
    int t = dht.readTemperature();
    int f = dht.readTemperature(true);

    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    bt.print("Humidity : %" + h);
    bt.print("Temperature : ºC" + t);
    bt.print("Temperature : ºF" + f);

    sensorValue = analogRead(sensorPin);
    percentValue = map(sensorValue, 1023, 200, 0, 100);

    bt.print("Soil Moisture : %" + percentValue);

    int LDR_STATUS = analogRead(LDR_PIN);

    if (LDR_STATUS > 400) {
      bt.print("Luminosity : Good Light");
    } else if (LDR_STATUS > 150 && LDR_STATUS < 500) {
      bt.print("Luminosity : Medium Light");
    } else {
      bt.print("Luminosity : Bad Light");
    }
  }
}
