#include <WiFi.h>  
   
 #define BLUE_LED  2 
   
 
 WiFiServer server(80);  
 WiFiClient client;  
   
 const char* ssid   = "ssid name";  
 const char* password = "password";     
   
   
 String HTTP;  
 String bluLed = "off";  
   
 void setup() {  
  Serial.begin(115200);  
  pinMode(BLUE_LED, OUTPUT);  
  digitalWrite(BLUE_LED, LOW);  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
   
  
  WiFi.softAP(ssid, password);  
   
  Serial.println( "" );  
  Serial.println( "IP address: " );  
  Serial.println( WiFi.softAPIP() );  
   
 
  server.begin();  
 }  
   
 void loop(){  
    
  if ( client = server.available() ) { 
   Serial.println("New Client.");  
   String clientData = "";  
   while ( client.connected() ) {    
    if ( client.available() ) {    
     char c = client.read();        
     http += c;             
     Serial.write(c);    
     if (c == '\n') {          
                        
      if (clientData.length() == 0) { 
       sendResponse();        
       updateLED();  
       updateWebpage();  
       break;  
      } else {  
       clientData = "";       
      }  
     } else if (c != '\r') {     
      clientData += c;        
     }  
    }  
   }   
   http = "";  
   client.stop();             
   Serial.println("Client disconnected.");  
   Serial.println("");  
  }  
 }  
   
 void sendResponse() {  
 
  client.println("HTTP/1.1 200 OK");  
  client.println("Content-type:text/html");  
  client.println("Connection: close");  
  client.println();   
 }  
   
 void updateWebpage() {  
   
    
    
  client.println("<!DOCTYPE html><html>");  
  client.println("<head>");  
  client.println("<title>ESP32 WiFi Station</title>");  
  client.println("</head>");  
    
  
  client.println("<body><h1>Simple ESP32 Web Server</h1>");  
   
  
  client.println("<p>1. Blue LED is " + bluLedState + "</p>");    
  if (bluLedState == "off") {  
   client.println("<p><a href=\"/BLUE_LED/on\"><button>Turn ON</button></a></p>");  
  } else {  
   client.println("<p><a href=\"/BLUE_LED/off\"><button>Turn OFF</button></a></p>");  
  }   
   
  client.print("<hr>");  
   
  client.println("</body></html>");  
  client.println();  
 }  
   
 void updateLED() {  
  
  if    (http.indexOf("GET /BLUE_LED/on") >= 0) {  
   Serial.println("Blue LED on");  
   bluLedState = "on";  
   digitalWrite(BLUE_LED, HIGH);  
  } else if (http.indexOf("GET /BLUE_LED/off") >= 0) {  
   Serial.println("Blue LED off");  
   bluLedState = "off";  
   digitalWrite(BLUE_LED, LOW);  
  }   
    
 
