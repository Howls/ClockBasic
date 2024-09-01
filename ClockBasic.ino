#include <TFT_eSPI.h>
#include <ESP32Time.h>
#include <WiFi.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

ESP32Time rtc(0); 

//time zone  and wifi
int zone=2;
const char* ntpServer = "pool.ntp.org";          
String ssid = "MIWIFI_2G_uPpX";
String password = "JjKkmKUv";

int n=0;  // counter for seconds

void connectWifi()
{ 
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Can't connect to wifi!");
  }
}

void setTime()
{
  configTime(3600*zone, 0, ntpServer);
  struct tm timeinfo;
  if (getLocalTime(&timeinfo)){
    rtc.setTimeStruct(timeinfo); 
  }
}

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_RED);
  sprite.createSprite(240,135);

    connectWifi();
    setTime();

     //brightness
     ledcAttach(0, 10000, 8);
     //ledcAttachPin(38, 0);
     ledcWrite(0, 120);
}

void draw()
  {
    sprite.fillSprite(TFT_WHITE); 
    sprite.setTextColor(TFT_NAVY,TFT_WHITE);
    sprite.drawString(rtc.getTime(),10,40,7);
    sprite.pushSprite(0,0);
  }

void loop() {
  
  draw();
  delay(1000);

  n++;
  if(n==7200)
  {
    n=0;
    setTime();
  }
}
