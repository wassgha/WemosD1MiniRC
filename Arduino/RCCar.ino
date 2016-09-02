#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;
// Initialize
int PWM1   = D2; // PWM Pin Motor 1
int PoM1 = D1;   // Polarity Pin Motor 1
int PWM2   = D4; // PWM Pin Motor 2  
int PoM2 = D3;   // Polarity Pin Motor 2

int ValM1   = 200; // Initial Value for PWM Motor 1 
int ValM2   = 200; // Initial Value for PWM Motor 2

void setup()
{
  pinMode(PWM1,   OUTPUT); 
  pinMode(PoM1,   OUTPUT); 
  pinMode(PWM2, OUTPUT);   
  pinMode(PoM2, OUTPUT);   
  Serial.begin(115200);         // Used to check value 
  Serial.setDebugOutput(true);
  Serial.println();
  Serial.println();
  Serial.println();

  for(uint8_t t = 4; t > 0; t--) {
      Serial.printf("[SETUP] WAIT %d...\n", t);
      Serial.flush();
      delay(1000);
  }

  WiFiMulti.addAP("LC", "");
}

void motor1Forward() {
  digitalWrite(PoM1, HIGH) ;   // Both motor with same polarity
  analogWrite(PWM1, 20);   // Stop both motors =&gt; ValMx = 0  
}

void motor1Backwards() {
  digitalWrite(PoM1, LOW) ;   // Both motor with same polarity
  analogWrite(PWM1, -20);   // Stop both motors =&gt; ValMx = 0  
}

void motor1Stop() {
  analogWrite(PWM1, 0);   // Stop both motors =&gt; ValMx = 0  
  digitalWrite(PoM1, LOW) ;   // Both motor with same polarity
}

void motor2Forward() {
  digitalWrite(PoM2, HIGH) ;   // Both motor with same polarity
  analogWrite(PWM2, 20);   // Stop both motors =&gt; ValMx = 0  
}

void motor2Backwards() {
  digitalWrite(PoM2, LOW) ;   // Both motor with same polarity
  analogWrite(PWM2, -20);   // Stop both motors =&gt; ValMx = 0  
}

void motor2Stop() {
  analogWrite(PWM2, 0);   // Stop both motors =&gt; ValMx = 0  
  digitalWrite(PoM2, LOW) ;   // Both motor with same polarity
}
// Main program
void loop()
{
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        // configure traged server and url
        http.begin("http://SERVER.com/cmd.txt"); //HTTP

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String result = http.getString();
                Serial.print("Motor 1 : " + result.substring(0,1) + "\n");
                Serial.print("Motor 2 : " + result.substring(1,2) + "\n");
                switch (result.substring(0,1).toInt()) {
                    case 2:motor1Forward();
                             break;
                    case 1:motor1Backwards();
                             break;
                    default:motor1Stop();
                      break;
                }
                switch (result.substring(1,2).toInt()) {
                    case 2:motor2Forward();
                             break;
                    case 1:motor2Backwards();
                             break;
                    default:motor2Stop();
                      break;
                }
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
      delay(1000);
  
}
// End.
