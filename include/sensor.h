#include <Arduino.h>
#include <DHT.h>
#include "d1pin.h"

#define PIN_DATA D1_PIN_4
#define DHTPIN D1_PIN_4
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);

// the setup routine runs once when you press reset:
void setup()
{
    // initialize serial communication at 9600 bits per second:
    Serial.begin(115200);
    pinMode(PIN_DATA, INPUT);
    dht.begin();
}

// the loop routine runs over and over again forever:
void loop()
{
    // read the input on analog pin 0:
    int sensorValue = analogRead(PIN_DATA);
    // print out the value you read:
    Serial.println(sensorValue);
    float h = dht.readHumidity(); // read humidity
    // Read temperature as Celsius (the default)

    float t = dht.readTemperature(); // read temperature
    // Read temperature as Fahrenheit (isFahrenheit = true)

    float f = dht.readTemperature(true);
    // Check if any reads failed and exit early (to try again).

    if (isnan(h) || isnan(t) || isnan(f))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }
    //Compute heat index in Fahrenheit(the default)

    float hif = dht.computeHeatIndex(f, h);
    // Compute heat index in Celsius(isFahreheit = false)

    float hic = dht.computeHeatIndex(t, h, false);
    // Print the measured readings on the Serial Monitor.

    Serial.print(F(" Humidity: "));
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
    delay(500); // delay in between reads for stability
}