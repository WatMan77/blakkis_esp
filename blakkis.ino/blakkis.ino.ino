#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "aalto open";
const char* password = "";

//Your Domain name with URL path or IP address with path
String serverName = "http://10.100.36.137:5000";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void sendDrink(String amount, String percentage){
      HTTPClient http;

      String serverPath = serverName;

      String jsondata = "{\"amount\":\"" + amount + "\",\"percentage\":\"" + percentage + "\"}";

      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());

      http.addHeader("Content-Type", "application/json");

      int httpResponseCode = http.POST(jsondata);

      Serial.println("JSON sent");
      Serial.println("Status?");
      Serial.println(httpResponseCode);
      
      if (httpResponseCode>0) {
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
  
}

void loop() {
  //Serial.println("Looping");
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      
      sendDrink("33", "5.5");
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
