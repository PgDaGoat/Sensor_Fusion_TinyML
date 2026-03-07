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
  float temp2 = BARO.readTemperature(); //Temp reading from arduino board
  temp2 = (temp2 * 1.8)+32; //Conversion to fahrenheit (°C × 1.8) + 32
//end of barometric
int fn =4; //This is the floor number int change when switching floors.
//start of dht22
float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true);

if (isnan(h) || isnan(t) || isnan(f)) {
  Serial.println(F("Failed to read from DHT sensor!"));
  return;
}
//Computes the heat index for Fahrenheit
//float hif = dht.computeHeatIndex(f, h);
//Computes the heat index for celsius
//float hic = dht.computeHeatIndex(t, h, false);

Serial.print(F("Pressure: "));
Serial.println(pressure);
Serial.print(F("Temp1:  "));
Serial.println(f);
Serial.print(F("Humidity%: "));
Serial.println(h);
Serial.print(F("Temp2:  "));
Serial.println(temp2);
Serial.print(F("Floor Number:  "));
Serial.println(fn);
//delay(5000);
}
