#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "FD-35";
const char* password = "salasana";

//Your Domain name with URL path or IP address with path
String serverName = "http://192.168.43.99:5000";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

const int beerPin = 13;
const int boozePin = 14;
const int gambinaPin = 15;
const int modePin = 12;

bool boozeButtonPressed = false;
bool beerButtonPressed = false;
bool gambinaButtonPressed = false;

const unsigned int debounceTime = 50;
unsigned long lastDebounceTime = 0;


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

  pinMode(beerPin, INPUT);
  pinMode(boozePin, INPUT);
  pinMode(gambinaPin, INPUT);
  // Pressed == HIGH, Not pressed == LOW
  pinMode(modePin, INPUT);
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

bool isNormalMode(){
  return digitalRead(modePin) == LOW;
}

void checkBeer() {

  if(digitalRead(beerPin) == LOW && !beerButtonPressed){
      Serial.println("SENDING BEER!");
      beerButtonPressed = true;
      if(isNormalMode()){
        sendDrink("33", "5.5");
      } else {
        sendDrink("50", "5.5");
      }
    }

  if(digitalRead(beerPin) == HIGH){
    beerButtonPressed = false;
    lastDebounceTime = millis();
  }
}

void checkBooze() {

  // The booze button had it's soldering the other way around
    if(digitalRead(boozePin) == HIGH && !boozeButtonPressed){
      Serial.println("SENDING BOOZE");
      boozeButtonPressed = true;
      if(isNormalMode()){
        sendDrink("40", "20");
      } else {
        sendDrink("12", "10");
      }
    }

    if(digitalRead(boozePin) == LOW){
      boozeButtonPressed = false;
      lastDebounceTime = millis();
    }
}

void checkGambina() {
  if(digitalRead(gambinaPin) == HIGH && !gambinaButtonPressed){
    Serial.println("SENDING GAMBINA!");
      gambinaButtonPressed = true;
      if(isNormalMode()){
        sendDrink("21", "20");
      } else {
        sendDrink("15", "20");
      }
    }

    if(digitalRead(gambinaPin) == LOW){
      gambinaButtonPressed = false;
      lastDebounceTime = millis();
    }
}

void loop() {
  //Serial.println("Looping");
  //Send an HTTP POST request every 10 minutes

  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){

    if(millis() - lastDebounceTime > debounceTime){
      checkBeer();
      checkBooze();
      checkGambina();
    }
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}
