#define DEBUG
#define UART_SPEED  115200 

#include "MeterDisplay.hpp"

MeterDisplay display;

void setup() {
  int left = 5;
  int top = 5;

  Serial.begin(UART_SPEED);

  DEBUG_PRINTLN("============================== Start Init ========================");
  display.Init();

  left = 10;
  top =  120;

  display.cleanScreen();
  display.InitDisplaySmooth(left, top);
  display.setColor(TFT_RED, TFT_YELLOW);
  display.setAlignment(TR_DATUM);

  for(int i=0; i<15000; i= i+1000) {
     display.Print((long)i);
     delay(250);
  }
  

  DEBUG_PRINTLN("============================== Stop Init =========================");

}

void loop(){}