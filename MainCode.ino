#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
const char* serverName = "http://yourserver.com/upload.php"; // URL SERVERU
adresu serveru
const int motionSensorPin = 2; // HC-SR501
volatile bool motionDetected = false;
unsigned long startTime = 0; // začátek stopování času
unsigned long endTime = 0; // konec stoppování času
String dogName = ""; // jméno psa
void setup() {
Serial.begin(115200);
pinMode(motionSensorPin, INPUT);
attachInterrupt(digitalPinToInterrupt(motionSensorPin), motionDetectedISR, CHANGE);
connectToWiFi();
}
void loop() {
if (motionDetected) {
startTime = millis();
Serial.println("Pohyb zaznamenán");
Serial.print("Jméno závodního psa: ");
while (Serial.available() == 0) {
// počkání na uživatelem zadáné hodnoty 
}
dogName = Serial.readStringUntil('\n');
Serial.print("Jméno psa: ");
Serial.println(dogName);
// čekání na konec pohybu
while (digitalRead(motionSensorPin) == HIGH) {
// pohyb je stále detekován
}
endTime = millis();
Serial.println("Pohyb ukončen");
// poslání dat na server
sendDataToServer();
motionDetected = false;
}
}
void motionDetectedISR() {
motionDetected = true;
}
void connectToWiFi() {
Serial.print("Connecting to WiFi");
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("WiFi připojena");
}
void sendDataToServer() {
if (WiFi.status() == WL_CONNECTED) {
HTTPClient http;
http.begin(serverName);
http.addHeader("Content-Type", "application/x-www-form-urlencoded");
String postData = "dog_name=" + dogName + "&start_time=" + String(startTime) +
"&end_time=" + String(endTime);
int httpResponseCode = http.POST(postData);
if (httpResponseCode > 0) {
Serial.print("HTTP Response code: ");
Serial.println(httpResponseCode);
String response = http.getString();
Serial.println(response);
} else {
Serial.print("Error code: ");
Serial.println(httpResponseCode);
}
http.end();
} else {
Serial.println("WiFi odpojena");
}
}
