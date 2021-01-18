#include<Arduino.h>
#include<ESP8266WiFi.h>
#include "ThingSpeak.h"
WiFiClient client;
int val;
float mv,farh,cel;

const char* ssid="";           /* Here need give your own wifi name */
const char* password="";        /* Give your own wifi password */

unsigned long myChannelNumber = ;      /* Thingspeak Channel ID */
String APIkey = "";           /* API key of your channel */
const char* server = "api.thingspeak.com";

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting .......");
  while(WiFi.status()!= WL_CONNECTED)
  {
    delay(500);
    Serial.print("Waiting to connect to wifi\n");
  }
  Serial.print("Wifi Connected \n");
  Serial.print(WiFi.localIP());
}
void loop()
{
  val = analogRead(A0);
  mv = ( val/1024.0)*5000;
  cel = mv/10;
  farh = (cel*9)/5 + 32;
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  delay(1000);
  



  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
      {  
       String sendData = APIkey+"&field1="+String(cel)+"\r\n\r\n"; 
       
       //Serial.println(sendData);

       client.print("POST /update HTTP/1.1\n");
       client.print("Host: api.thingspeak.com\n");
       client.print("Connection: close\n");
       client.print("X-THINGSPEAKAPIKEY: "+APIkey+"\n");
       client.print("Content-Type: application/x-www-form-urlencoded\n");
       client.print("Content-Length: ");
       client.print(sendData.length());
       client.print("\n\n");
       client.print(sendData);

       Serial.print("Temperature: ");
       Serial.print(cel);
       Serial.println("deg C. Connecting to Thingspeak..");
      }
      client.stop();

      Serial.print("Sending......");

      delay(1000);
}
