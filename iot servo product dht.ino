
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
#include <DHTesp.h>
//for DHT
#define DHTpin 15    
DHTesp dht;

//for servo variable
Servo myservo;
int pos = 0;
int servoPin = 13;

//start variable of product count
#define irsensor 4
int irvalue;
int irX=0;
int ircount=0;
unsigned long previousMillis = 0;
const long interval = 120; //delay for proper count
//end of product count variable

char auth[] = "ciQz99C62jj2RmExWp6RgTGP4M2mqB_3";
char ssid[] = "Tlink";
char pass[] = "98754321";

void setup()
{
  //servo PMW start
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 500, 2400);
  //Servo PWM end
  dht.setup(DHTpin, DHTesp::DHT11); 
  pinMode(irsensor,INPUT);//pin for ir / product
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

//servo funcion for inventory
BLYNK_WRITE(V1)
{
  pos = param.asInt(); // assigning incoming value from pin V1 to a variable
   myservo.write(pos);  
}
//function for Humidity and temperature 
void IOTdht(){
  int humidity = dht.getHumidity();
  int temperature = dht.getTemperature();
  Blynk.virtualWrite(1,humidity);
  Blynk.virtualWrite(2,temperature);
  
}
//function for product counting 
 void product(){
    irvalue=digitalRead(irsensor);
   unsigned long currentMillis = millis();

   if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
     if (irvalue==0){
       if(irX==0){
            ircount++;
            irX=1;
           Serial.println(ircount);
           Blynk.virtualWrite(5,ircount);
      }
    }
    else{
     irX=0;
    }
   }
 }



//Main Loop
void loop()
{
  IOTdht();
  product();
  Blynk.run();
}
