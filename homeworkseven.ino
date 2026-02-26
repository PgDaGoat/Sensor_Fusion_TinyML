#include <DHT.h>
#include <Arduino_LPS22HB.h>

#define DHTPIN 11
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);

  if(!BARO.begin()){
    Serial.println("Failed to initialize pressure sensor!");
    while (1);
  
  }
  dht.begin();
}

void loop() {
  /*Barometric Reading from sensor*/
  float pressure= BARO.readPressure();

  float altitude = 44330 * (1 - pow(pressure/101.325, 1/5.255));
//end of barometric

//start of dht22
float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true);

if (isnan(h) || isnan(t) || isnan(f)) {
  Serial.println(F("Failed to read from DHT sensor!"));
  return;
}
//Computes the heat index for Fahrenheit
float hif = dht.computeHeatIndex(f, h);
//Computes the heat index for celsius
float hic = dht.computeHeatIndex(t, h, false);

Serial.print(F("Humidity: "));
Serial.print(h);
Serial.print(F("% Temperature:  "));
Serial.print(t);
Serial.print(F("C "));
Serial.print(f);
Serial.print(F("F Heat index: "))'
Serial'


}
