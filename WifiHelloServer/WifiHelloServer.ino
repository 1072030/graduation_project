#include <ArduinoJson.h>

//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "beacon-backend-a8bf3-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "s5deCRVxfQdCAOVkjJ4T1MPBE2nsOEmFPcEyjeRk"
#define WIFI_SSID "iPhone"
#define WIFI_PASSWORD "12345678"
#define LedPin 16  
//Pin 16 = Pin D0
void setup() {
  pinMode(LedPin, OUTPUT);
  Serial.begin(9600);
  
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}
String status;
void loop() {
  status = Firebase.getString("/switch/light");
  
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }else{
    if(status.toInt() == 1){
      Serial.println(status);
      digitalWrite(LedPin, LOW);
    }else{
      Serial.println(status);
      digitalWrite(LedPin, HIGH);
    }
  }
  
  delay(500);
//  
//  // update value
//  Firebase.setFloat("number", 43.0);
//  // handle error
//  if (Firebase.failed()) {
//      Serial.print("setting /number failed:");
//      Serial.println(Firebase.error());  
//      return;
//  }
//  delay(1000);
//
//  // get value 
//  Serial.print("number: ");
//  Serial.println(Firebase.getFloat("number"));
//  delay(1000);
//
//  // remove value
//  Firebase.remove("number");
//  delay(1000);
//
//  // set string value
//  Firebase.setString("message", "hello world");
//  // handle error
//  if (Firebase.failed()) {
//      Serial.print("setting /message failed:");
//      Serial.println(Firebase.error());  
//      return;
//  }
//  delay(1000);
//  
//  // set bool value
//  Firebase.setBool("truth", false);
//  // handle error
//  if (Firebase.failed()) {
//      Serial.print("setting /truth failed:");
//      Serial.println(Firebase.error());  
//      return;
//  }
//  delay(1000);
//
//  // append a new value to /logs
//  // handle error
//  if (Firebase.failed()) {
//      Serial.print("pushing /logs failed:");
//      Serial.println(Firebase.error());  
//      return;
//  }
//  Serial.print("pushed: /logs/");
//
//  delay(1000);
}
