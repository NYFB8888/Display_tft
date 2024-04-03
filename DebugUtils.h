/*
#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H

#include <Arduino.h>

#ifdef DEBUG
  #define DEBUG_PRINTLN(...)  Serial.print("DEBUG >>> "); Serial.println(__VA_ARGS__)
  #define DEBUG_PRINTF(...)  Serial.printf("DEBUG >>> "); Serial.printf(__VA_ARGS__)
#else
  #define DEBUG_PRINTLN(...)
  #define DEBUG_PRINTF(...)
#endif

#endif
*/


#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H

#include <Arduino.h>

#ifdef DEBUG
#define DEBUG_PRINTLN(...)  Serial.print("DEBUG Function: ["); Serial.print(__func__); Serial.print("] Line: ("); Serial.print(__LINE__); Serial.print(") >>>> "); Serial.println(__VA_ARGS__)
#ifdef ESP32
#define DEBUG_PRINTF(...)   Serial.print("DEBUG Function: ["); Serial.print(__func__); Serial.print("] Line: ("); Serial.print(__LINE__); Serial.print(") >>>> "); Serial.printf(__VA_ARGS__)
#endif
#else
#define DEBUG_PRINTLN(...)
#define DEBUG_PRINTF(...)
#endif

#endif

