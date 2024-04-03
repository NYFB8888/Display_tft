#include "MeterDisplay.hpp"
#include "defaultFonts.h"

/* ===== DATUM =========
TL_DATUM = 0 = Top left
TC_DATUM = 1 = Top centre
TR_DATUM = 2 = Top right
ML_DATUM = 3 = Middle left
MC_DATUM = 4 = Middle centre
MR_DATUM = 5 = Middle right
BL_DATUM = 6 = Bottom left
BC_DATUM = 7 = Bottom centre
BR_DATUM = 8 = Bottom right
*/

void MeterDisplay::Init(enum MeterDisplay::eRotation _rotation, UWORD _backGroundColor){
    DEBUG_PRINTLN("Display class init");
    rotation = _rotation;
    backGroundColor = _backGroundColor;
    tft.begin();
    tft.setRotation(rotation);
    tft.fillScreen(backGroundColor);  
    AddWindow();
    DEBUG_PRINTLN("Init done");
}

BYTE MeterDisplay::getIndex(){
   DEBUG_PRINTF("getIndex function %d \n", index);
   return index;
}

bool MeterDisplay::setIndex(BYTE _index){
  bool ret = false;
  DEBUG_PRINTLN("setIndex ..");
  if (_index >= 0 && _index <= MAX_index) {
    index = _index;
    ret = true;
    DEBUG_PRINTF("Index %d %d\n",index, MAX_index);
   } else {
    DEBUG_PRINTLN("Error index request");
   }
   return ret;
}

void MeterDisplay::AddWindow(){
  DEBUG_PRINTLN("AddWindow");
  windows.add({});
  index=MAX_index=windows.size()-1;
  DEBUG_PRINTF("Index %d %d\n",index, MAX_index);
  ListWindowSpec(index);
}

void MeterDisplay::DelateWindow(BYTE _index){
  DEBUG_PRINTLN("delateWindows");
   if (_index >= 0 && _index <= MAX_index) {
    windows.remove(_index);
    DEBUG_PRINTF("Index %d %d\n",index, MAX_index);
  } else {
    DEBUG_PRINTF("Error index delate request");
  }
}

void MeterDisplay::cleanScreen(){
  tft.fillScreen(backGroundColor);  
  DEBUG_PRINTLN("clean screen");
}

void MeterDisplay::setAlignment(BYTE style){
  windows[index].datum = style;
  DEBUG_PRINTF("setting datum %d \d",windows[index].datum);
}

void MeterDisplay::Print(String text){

  int x,y = 0;
   
  TFT_eSprite spr = TFT_eSprite(&tft);
  if (windows[index].smooth)
   spr.loadFont(windows[index].smoothFont);
  else
   spr.setTextFont(windows[index].font);
  
  if (windows[index].datum == TR_DATUM || windows[index].datum == MR_DATUM || windows[index].datum == BR_DATUM)
      x = windows[index].width;
  y=2;

  spr.createSprite(windows[index].width, windows[index].height);
  spr.fillSprite(windows[index].backGroundColor);
  spr.setTextColor(windows[index].color, windows[index].backGroundColor); // Set the font colour and the background colour
  spr.setTextDatum(windows[index].datum);
  spr.drawString(text, x, y);
  spr.pushSprite(windows[index].left, windows[index].top);  
  spr.unloadFont(); 
  spr.deleteSprite();

  DEBUG_PRINTF("printing x=%d y=%d \n", x, y);

}

WORD MeterDisplay::getScreenWidth(){
  return tft.width();
}

WORD MeterDisplay::getScreenHeight(){
  return tft.height();
}

void MeterDisplay::TestPrint(String text){
  int width, height;
  int left,top;
  int x,y;
  x=0;
  y=0;
  left=5;
  
  TFT_eSprite spr = TFT_eSprite(&tft);
  spr.loadFont(defaultFonts);
  width  = tft.width() - 2*left;
  height = spr.fontHeight();
  top =  (tft.height() - height)/2;

  spr.createSprite(width, height);
  spr.fillSprite(TFT_YELLOW);
  spr.setTextColor(TFT_RED, TFT_YELLOW); // Set the font colour and the background colour
  spr.setTextDatum(TL_DATUM);
  spr.drawString(text, x, y);
  spr.pushSprite(left, top);  
  spr.unloadFont(); 
  spr.deleteSprite();
}

void MeterDisplay::InitDisplaySmooth(WORD left, WORD top, WORD width, WORD height, const UBYTE *smoothFont, UWORD backGroundColor, UWORD color){
  windows[index].left = left;
  windows[index].top = top;
  windows[index].smoothFont = smoothFont;
  windows[index].smooth = true;
  if (width < 0)
   windows[index].width = tft.width() - 2*windows[index].left;
  if (height < 0){
    tft.loadFont(smoothFont);
    windows[index].height = tft.fontHeight();
    tft.unloadFont();
  }
  windows[index].color = color;
  windows[index].backGroundColor = backGroundColor;
  ListWindowSpec(index);
  DEBUG_PRINTF("Init smooth  left=%d top=%d width=%d height=%d \n", windows[index].left, windows[index].top, windows[index].width, windows[index].height);
}

void MeterDisplay::InitDisplay(WORD left, WORD top, WORD width, WORD height, UBYTE font, UWORD backGroundColor, UWORD color){
  windows[index].left = left;
  windows[index].top = top;
  windows[index].font = font;
  windows[index].smooth = false;
  if (width < 0)
   windows[index].width = tft.width() - 2*windows[index].left;
  if (height < 0){
    tft.setTextFont(font);
    windows[index].height = tft.fontHeight();
  }
  windows[index].color = color;
  windows[index].backGroundColor = backGroundColor;
  ListWindowSpec(index);
  DEBUG_PRINTF("Init left=%d top=%d width=%d height=%d \n", windows[index].left, windows[index].top, windows[index].width, windows[index].height);
}

void MeterDisplay::setColor(UWORD color, UWORD backGroundColor){
  windows[index].color = color;
  windows[index].backGroundColor = backGroundColor;
  DEBUG_PRINTF("setting color=%d backGroundColor=%d \n",  windows[index].color, windows[index].backGroundColor);
}

void MeterDisplay::ListWindowSpec(BYTE index){
#ifdef  DEBUG
    Serial.println("=====================================");
    Serial.printf("Index           %d\n", index);
    Serial.printf("Top             %d\n", windows[index].top);
    Serial.printf("Left            %d\n", windows[index].left);
    Serial.printf("Width           %d\n", windows[index].width);
    Serial.printf("Height          %d\n", windows[index].height);
    Serial.printf("Datum           %d\n", windows[index].datum);
    Serial.printf("Color           %d\n", windows[index].color);
    Serial.printf("backGroundColor %d\n", windows[index].backGroundColor);
    Serial.printf("Font            %d\n", windows[index].font);
    Serial.printf("Smooth          %d\n", windows[index].smooth);
    Serial.printf("SmoothFont      %d\n", windows[index].smoothFont);
    Serial.println("=====================================");
#endif
}

void MeterDisplay::Print(float arg){
  Print(Format(String(arg)));
}

void MeterDisplay::Print(long arg){
  Print(Format(String(arg)));
}

#define BUF_SIZE 128

void MeterDisplay::Print(const char *format, ...){
  char buffer[BUF_SIZE];

  va_list args;
  va_start (args, format);
  vsnprintf (buffer,BUF_SIZE,format, args);
  va_end (args);
  
  Print(String(buffer));
}

String MeterDisplay::Format(String text){
   String decEnd = text.substring(text.lastIndexOf("."));
   text = text.substring(0,text.lastIndexOf("."));
   String ret = "";
   for(int i = 0; i < text.length(); i++) {
     if (!(i%3)) ret = ","+ret;   
     ret = text.charAt(text.length()-i-1) + ret;     
   }
   ret = ret.substring(0, ret.length()-1)+decEnd;
   return ret;   
}

void MeterDisplay::SetFont(UBYTE font){
  DEBUG_PRINTLN("Set font non smooth");
  windows[index].smooth = false;
  windows[index].font = font;
  tft.setTextFont(font);
  windows[index].height = tft.fontHeight();
  DEBUG_PRINTF(" NS Font is smooth=%d  font=%d  height=%d\n",windows[index].smooth, windows[index].font, windows[index].height );
}

void MeterDisplay::SetFont(const UBYTE *font){
  DEBUG_PRINTLN("Set font smooth");
  windows[index].smooth = true;
  windows[index].smoothFont = font;
  tft.loadFont(font);
  windows[index].height = tft.fontHeight();
  DEBUG_PRINTF(" S Font is smooth=%d  font=%d  height=%d\n",windows[index].smooth, windows[index].smoothFont, windows[index].height );
}

void  MeterDisplay::Origin(){
  tft.drawFastHLine(0,0,tft.width(), TFT_WHITE);
  tft.drawFastVLine(0,0,tft.height(),TFT_WHITE);
}


