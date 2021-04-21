#include <ESP8266WiFi.h>

String apiWritekey = "        "; // replace with your THINGSPEAK WRITEAPI key here
const char* ssid = "         "; // your wifi SSID name
const char* password = "      " ;// wifi pasword
 
const char* server = "api.thingspeak.com";
float resolution=3.3/1023;// 3.3 is the supply volt  & 1023 is max analog read value
WiFiClient client;
 float B=108;
 float S=96;
 int i=1;
void setup() {
  Serial.begin(9600);
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println();
  
  
}
 
void loop() {
  
if (i==1){
  B=B;
  S=S;
}

else if (i==2){
  B=B-4;
  S=S+4;
}

else if (i==3){
  B=B-4;
  S=S-8;
}


else if (i==4){
  B=B+8;
  S=S+4;
}



 
  if (client.connect(server,80))
  {  
    String tsData = apiWritekey;
           tsData +="&field1=";
           tsData += String(B);
           tsData +="&field2=";
           tsData += String(S);
           tsData += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(tsData.length());
     client.print("\n\n");  // the 2 carriage returns indicate closing of Header fields & starting of data
     client.print(tsData);
 
     Serial.print("Temperature: ");
     Serial.print(B);
     Serial.println("uploaded to Thingspeak server....");
  }
  client.stop();
 
  Serial.println("Waiting to upload next reading...");
  Serial.println();
  // thingspeak needs minimum 15 sec delay between updates
  delay(15000);
  i+=1;
}
