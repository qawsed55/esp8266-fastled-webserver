/*
   ESP8266 FastLED WebServer: https://github.com/jasoncoon/esp8266-fastled-webserver
   Copyright (C) Jason Coon

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#if !defined(ESP8266_FASTLED_WEBSERVER_COMMON_H)
#define ESP8266_FASTLED_WEBSERVER_COMMON_H

#include "./include/simplehacks/static_eval.h"
#include "./include/simplehacks/constexpr_strlen.h"
#include "./include/simplehacks/array_size2.h"

#include "config.h" // must be included before FastLED.h

#define FASTLED_INTERNAL // no other way to suppress build warnings
#include <FastLED.h>
FASTLED_USING_NAMESPACE

extern "C" {
#include "user_interface.h"
}

#include <LittleFS.h>
#define MYFS LittleFS

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>
//#include <WebSocketsServer.h>
#include <EEPROM.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager/tree/development

#if defined(ESP32) || defined(ESP8266)
  // Optional: (LGPL) https://github.com/sinricpro/ESPTrueRandom.git#ed198f459da6d7af65dd13317a4fdc97b23991b4
  // #include "ESPTrueRandom.h"
  // Then:
  //     ESPTrueRandom.useRNG = true;
  //     int32_t r = ESPTrueRandom.memfill((void*)&r, sizeof(r));
#else
  #error "Currently only ESP32 and ESP8266 are supported"
#endif

#if defined(ENABLE_IR)
  #include <IRremoteESP8266.h>
  #include "commands.h"
#endif

// forward-declarations
// Only list those variables that are needed by the local
// project "header" files (the ones that are actually C++ files)
extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];
extern const uint8_t gGradientPaletteCount;
extern const CRGBPalette16 palettes[];
extern const uint8_t paletteCount;
extern const String paletteNames[];

extern WiFiManager wifiManager;
extern ESP8266WebServer webServer;
extern String nameString;


#if IS_FIBONACCI // actual data in map.h
  #if NUM_PIXELS > 256 // when more than 256 pixels, cannot store index in uint8_t....
    extern const uint16_t physicalToFibonacci [NUM_PIXELS];
    extern const uint16_t fibonacciToPhysical [NUM_PIXELS];
  #else
    extern const uint8_t physicalToFibonacci [NUM_PIXELS];
    extern const uint8_t fibonacciToPhysical [NUM_PIXELS];
  #endif
#elif defined(PRODUCT_KRAKEN64)
  extern const uint8_t  body    [NUM_PIXELS];
#endif

#if HAS_COORDINATE_MAP
  extern const uint8_t  coordsX [NUM_PIXELS];
  extern const uint8_t  coordsY [NUM_PIXELS];
  extern const uint8_t  angles  [NUM_PIXELS];
#endif

// Structures
typedef void (*Pattern)();
typedef Pattern PatternList[];
typedef struct {
  Pattern pattern;
  String name;
} PatternAndName;
typedef PatternAndName PatternAndNameList[];

typedef struct {
  CRGBPalette16 palette;
  String name;
} PaletteAndName;
typedef PaletteAndName PaletteAndNameList[];



// Function prototypes


// Local C++ sources that are masquerading as header files
#include "GradientPalettes.h"
#include "Info.h"
#include "Field.h"
#include "FSBrowser.h"
#include "Ping.h"




#endif // ESP8266_FASTLED_WEBSERVER_COMMON_H
