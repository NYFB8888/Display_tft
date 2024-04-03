#pragma one

#define DEBUG
#define DEPTH 16

#include <DebugUtils.h>
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h> 
#include <LinkedList.h>
#include "defaultFonts.h"

typedef uint8_t    UBYTE;
typedef uint16_t   UWORD;
typedef uint32_t   UDWORD;

typedef int8_t     BYTE;
typedef int16_t    WORD;
typedef int32_t    DWORD;

class MeterDisplay{
  public:

    enum eRotation { TOP,RIGHT,BOTTOM,LEFT};
    enum eBox {NONE, SINGLE, DOUBLE};  

    void Init(enum MeterDisplay::eRotation _rotation = MeterDisplay::eRotation::RIGHT, UWORD _backGroundColor = TFT_BLACK);
    void cleanScreen();

    bool setIndex(BYTE _index);
    BYTE getIndex();
    void AddWindow();
    void DelateWindow(BYTE _index);

    WORD getScreenWidth();
    WORD getScreenHeight();

    void setColor(UWORD color, UWORD backGroundColor);
    void setAlignment(BYTE style);
    void InitDisplaySmooth(WORD left, WORD top, WORD width = -1, WORD height = -1, const UBYTE *smoothFont = defaultFonts, UWORD backGroundColor = TFT_BLACK, UWORD color = TFT_WHITE);
    void InitDisplay(WORD left, WORD top, WORD width = -1, WORD height = -1, UBYTE font = 8, UWORD backGroundColor = TFT_BLACK, UWORD color = TFT_WHITE);

    void SetFont(UBYTE font);
    void SetFont(const UBYTE *font);
    void Origin();

    void Print(String text);
    void Print(const char *format, ...);
    void Print(float arg);
    void Print(long arg);

    void TestPrint(String text);

    private:
    void ListWindowSpec(BYTE index);
    String Format(String text);


  private:   
     class Windows{
      public:
        WORD  top    = 0;
        WORD  left   = 0;
        WORD  width  = 0;
        WORD  height = 0;
        BYTE  datum  = TL_DATUM;
        UWORD  color  = TFT_WHITE;
        UWORD  backGroundColor = TFT_BLACK;
        UBYTE  font  = 8;
        bool  smooth = true;
        const UBYTE *smoothFont = defaultFonts;
     };

    LinkedList<Windows> windows = LinkedList<Windows>();
    TFT_eSPI tft = TFT_eSPI();
    enum eRotation rotation = MeterDisplay::eRotation::RIGHT;
    UWORD  backGroundColor = TFT_BLACK;
    UWORD  color  = TFT_WHITE;
    BYTE  index = 0;
    BYTE  MAX_index = 0;

  };

