// Description:
// this is a simple Arduino project which uses a DHT22 temperature/humidity
// sensor to read temperature and humidity; temperature and humidity
// are sent to the host PC via the serial connection and displayed in 
// a terminal; this is essentially the "test" example that comes with the
// library that you need to download from: 
// https://www.arduino.cc/reference/en/libraries/dht-sensor-library/

// Notes:
// remember, before verify/compile and upload, to first:
// 1) select your actual Arduino board: Tools->Board->Make-Your-Selection
// 2) check-mark the right COM port: Tools->Port->Make-Your-Selection 

// HW Connections:
// we'll use digital pin 11 of the Arduino Nano 33 BLE Sense to connect
// to pin DTA of the DHT22 sensor, like in this diagram:
//  ________________
// |                |
// |  DHT22 Sensor  | Front view (see thru) of DHT22 sensor
// |  1   2   3  4  |
// | VDD DTA NC GND |
//  ----------------
//   |   |   |   |
//   |   |   |   |
//               ^is connected to a GND pin of Arduino
//           ^is left disconnected (i.e., Not-Connected)
//       ^is connected to digital pin 11 of Nano 33 BLE Sense board
//   ^is connected to VDD of Arduino

#include <DHT.h>

#define DHTPIN 11 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22 // DHT 22

// initialize DHT sensor;
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  // create serial connection; 
  Serial.begin(115200);
  delay(1000);
  Serial.println("This is a program that reads every 2 seconds");
  Serial.println("Humidity and Temperature from a DHT22 sensor!");
  // initialize device;
  dht.begin();
}

void loop()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  // wait 2 seconds between measurements;
  delay(2000);
}
