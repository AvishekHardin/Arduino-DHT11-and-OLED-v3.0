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

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

//variable declarations
int x=0;
float tempValue, humiValue;

void setup(){
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  delay(2000);
}

void loop(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if(isnan(h) || isnan(t)){return;}
  humiValue = map(h, 20, 80, 63, 31);
  tempValue = map(t, 0, 50, 63, 31);
  display.drawLine(x, tempValue, x, 63, WHITE);
  display.drawLine(x+65, humiValue, x+65, 63, WHITE);
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
  x++;if(x >= 62){x=0; display.clearDisplay();}
}
