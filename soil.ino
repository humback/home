
#include <ESP8266WiFi.h>

// replace with your channel’s thingspeak API key,
String apiKey = "RV05BQ88MEE3MXW6";
const char* ssid = "humback";
const char* password = "Hubert1978";
const char* server = "api.thingspeak.com";

int analogPin = A0;     
int val = 0;           // variable to store the value read



WiFiClient client;

void setup() {
Serial.begin(115200);
WiFi.begin(ssid, password);
Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

}

void loop() {

if (client.connect(server,80)) { // "184.106.153.149" or api.thingspeak.com

val = analogRead(analogPin);

String postStr = apiKey;
postStr +="&field2=";
postStr += String(val);
postStr += "\r\n\r\n";

client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);


}
client.stop();

Serial.println("Waiting…");
// thingspeak needs minimum 15 sec delay between updates
delay(20000);
}

