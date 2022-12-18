#include<SoftwareSerial.h>
#include <SPI.h>
#include <WiFiEsp.h>
#include <ArduinoJson.h>
#include<DHT.h>
#include <Time.h>  
#include <Wire.h>  
#include <DS1307RTC.h> 


SoftwareSerial swSerial(2,3); //RX, TX (ESP-01: RX-pin3, TX-pin2)
WiFiEspClient client;
DHT dht(A1,DHT11);

float temp;
float humi;
String datetime;
char dt[15];

int status = WL_IDLE_STATUS;
const char* ssid = "WITLAB" ;//wifi ID
const char* password = "defacto8*"; //wifi PASSWORD
const char* server = "http://localhost:8000";
//const char* server = "arduino.cc";
String host = "210.102.142.20";

IPAddress hostIp(210,102,142,20);
int ServerPort = 8080;

const char* ntpServer = "kr.pool.ntp.org";
const long gmtOffset_sec = 32400;
const int daylightOffset_sec =0;

void setup() {
  Serial.begin(9600);
  swSerial.begin(9600); // initialize serial for ESP module
  
  setSyncProvider(RTC.get);  
  setTime(10,51,00,04,07,22);
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");      


   WiFi.init(&swSerial); // initialize ESP module
    
  if ( WiFi. status ( ) == WL_NO_SHIELD ) {  // check for the presence of the shield
    Serial . println ( "와이파이 쉴드가 없습니다" ) ;
    while ( true ) ;
  }
  
  while(WiFi.status() != WL_CONNECTED){ // attempt to connect to WiFi network
    delay(1000);
    Serial.println("Conneting to WIFI...");
    WiFi.begin(ssid,password);
//    timeClient.update();
  }
  
  Serial.println("Conneted to the WIFI network");// you're connected now

  printWifiStatus();

}

void loop() {

 while (client.available()) {
    char c = client.read();
    Serial.write(c);
 }

  humi = dht.readHumidity();
  temp = dht.readTemperature();
  Serial.print("humi: ");
  Serial.println(humi);
  Serial.print("temp: ");
  Serial.println(temp);
  digitalClockDisplay();  
  
  if(client.connect(hostIp, ServerPort)){
    Serial.println("Connecting");
    

  String jsondata ="";

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  
//  StaticJsonDocument<200> jsonBuffer;
//  JsonObject root = jsonBuffer.to<JsonObject>(); //json형식을 만ㄷ르어 낼 수 있는 객체 선언
//  
  root["datetime"] = datetime;
  root["temp"] = temp;
  root["humi"] = humi;

   root.printTo(jsondata); //String으로 변환/
  Serial.println(jsondata);

  client.print(F("POST /tem_hum/"));
  client.print(F(" HTTP/1.1\r\n"));
  client.print(F("Cache-Control: no-cache\r\n"));
  client.print(F("Host: 210.102.142.20:8000\r\n"));
//  client.print(F("Host: 172.30.1.58:8000\r\n"));
  client.print(F("User-Agent: Arduino\r\n"));
  client.print(F("Content-Type: application/json\r\n"));
  client.print(F("Content-Length: "));
  client.println(jsondata.length());
  client.println();
  client.println(jsondata);
  client.print(F("\r\n\r\n"));
  }
  client.flush();
  client.stop();

  delay(1000);
// Serial.println(WiFi.status());
  

}

void digitalClockDisplay(){
  Serial.print(hour());
  Serial.print(" ");
  Serial.print(timeDigits(minute()));
  Serial.print(" ");
  Serial.print(timeDigits(second()));
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
  datetime = year();
  datetime.concat("-");
  datetime.concat(month());
  datetime.concat("-");
  datetime.concat(day());
  datetime.concat(" ");
  datetime.concat(hour());
  datetime.concat(":");
  datetime.concat(timeDigits(minute()));
  datetime.concat(":");
  datetime.concat(timeDigits(second()));
  Serial.println(datetime);
  
}

String timeDigits(int digits){
  String s;
  String zero = "0";
  s = digits;
  if(digits < 10){
    zero.concat(s);
    s = zero;
  }
  return s;

}

void printWifiStatus(){

  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  
  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  
  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
