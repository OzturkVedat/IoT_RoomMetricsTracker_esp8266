#include "arduino_secrets.h"
#include "thingProperties.h"
#include "DHT.h"             // Library for DHT sensors
#include "Gsender.h" // Include the GmailSender library


#define dhtPin 0            // data pin (D3 port on nodeMCU esp8266)
#define dhtType DHT11        // DHT 11


const int OUT_PIN = A0;  // Analog pin on ESP8266

DHT dht(dhtPin, dhtType);    // Initialise the DHT library
const int sampleWindow = 50;              
unsigned int sample;

void setup() {
  Serial.begin(115200);                                   
  dht.begin();               // start with reading the DHT sensor
  initProperties();
  gsender = new Gsender("your_email@gmail.com", "your_email_password");


  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  humidity = dht.readHumidity();        // get the humidity from the DHT sensor
  temperature = dht.readTemperature();        // get the temperature in degrees Celsius from the DHT sensor

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Reading DHT sensor failed!");
    return;
  }
   unsigned long startMillis= millis();                   // Start of sample window
   float peakToPeak = 0;                                  // peak-to-peak level
 
   unsigned int signalMax = 0;                            //minimum value
   unsigned int signalMin = 1024;                         //maximum value
 
                                                         
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(OUT_PIN);                     //get reading from microphone
      if (sample < 1024)                                  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;                           // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;                           // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;                    // max - min = peak-peak amplitude
   noise = map(peakToPeak,20,900,49.5,90);             //calibrate for deciBels
   if (noise > 60.0) {
    sendEmail();
  }
   delay(2000);
}
void sendEmail() {
  Serial.println("Sending email...");

  String subject = "Temperature Alert!";
  String body = "Temperature has exceeded 60 degrees Celsius.";

  if (gsender->send("recipient_email@example.com", subject, body)){     // Replace "recipient_email@example.com" with the recipient's email address
    Serial.println("Email sent successfully");
  } else {
    Serial.println("Email sending failed");
  }
}
void onHumidityChange() {}
void onTemperatureChange() {}
void onNoiseChange() {}