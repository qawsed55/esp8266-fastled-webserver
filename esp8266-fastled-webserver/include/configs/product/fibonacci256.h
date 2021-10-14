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
#pragma once

#if !defined(ESP8266_FASTLED_WEBSERVER_PRODUCT_FIB256_H)
#define ESP8266_FASTLED_WEBSERVER_PRODUCT_FIB256_H



#define LED_TYPE                      WS2812B
#define COLOR_ORDER                   GRB
#define NUM_PIXELS                    256
#define AVAILABLE_MILLI_AMPS          1600 // IMPORTANT: set the max milli-Amps of your power supply (4A = 4000mA)
#define MAX_MILLI_AMPS_PER_PIXEL      12   // IMPORTANT: set to larger value if necessary
#define FRAMES_PER_SECOND             120
#define DEFAULT_PATTERN_INDEX         3
#define DEFAULT_COLOR_CORRECTION      TypicalSMD5050
#define NAME_PREFIX                   "Fibonacci256-"
#define PRODUCT_FRIENDLY_NAME         "Fibonacci256"

#define IS_FIBONACCI                  1

#endif // ESP8266_FASTLED_WEBSERVER_PRODUCT_FIB256_H
