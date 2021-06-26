#include "DHTesp.h"

#define DHTpin 15    //D15 of ESP32 DevKit

DHTesp dht;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
   
  dht.setup(DHTpin, DHTesp::DHT11); 
 
}

void loop()
{
  //delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  Serial.println(temperature);
  Serial.println(humidity);
  
}
