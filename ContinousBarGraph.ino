#include "DHT.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
#define DHTPIN 2
#define DHTTYPE DHT11

int arrIndex=0;
int tempArray[62];
int humiArray[62];

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup(){
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  for(int i=0; i<=61; i++){tempArray[i]=0; humiArray[i]=0;}
}

void loop(){
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if(isnan(t) && isnan(h)){return;}
  if(arrIndex < 62){
    tempArray[arrIndex]=t;
    humiArray[arrIndex]=h;
    arrIndex++;
    displayDHTData(tempArray, humiArray, t, h);
    display.clearDisplay();
  }else{
    for(int j=0; j<62; j++){
      tempArray[j]=tempArray[j+1];
      humiArray[j]=humiArray[j+1];
    }
    tempArray[61]=t;
    humiArray[61]=h;
    arrIndex=63;
    displayDHTData(tempArray, humiArray, t, h);
  }
}

void displayDHTData(int dhtTemp[], int dhtHumi[], float t, float h){
  int tempValue, humiValue;
  display.clearDisplay();
  for(int k=0; k<=61; k++){
    tempValue = map(dhtTemp[k], 0, 50, 63, 31);
    humiValue = map(dhtHumi[k], 20, 80, 63, 31);
    display.drawLine(k, tempValue, k, 63, WHITE);
    display.drawLine(k+65, humiValue, k+65, 63, WHITE);
  }
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 1);
    display.println("Temp  Humi");
    display.setTextSize(1);
    display.setCursor(0, 20);
    display.print(t);
    display.print("*C");
    display.setCursor(72, 20);
    display.print(h);
    display.print("%");
    display.display();
}

