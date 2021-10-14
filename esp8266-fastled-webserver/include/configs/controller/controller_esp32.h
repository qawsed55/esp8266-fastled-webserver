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

#if !defined(ESP8266_FASTLED_WEBSERVER_CONTROLLER_ESP32_H)
#define ESP8266_FASTLED_WEBSERVER_CONTROLLER_ESP32_H

#define DATA_PIN                      18 // d1 mini32 (same physical location as D5 on the d1 mini)

#if defined(ENABLE_IR) && !defined(IR_RECV_PIN)
   // Default pin for ESP32 is 16 (for d1 mini32, this is the same physical location as D4 on the d1 mini)
   #define IR_RECV_PIN   16  // TODO: VERIFY THIS IS CORRECT VALUE
#endif

#endif // ESP8266_FASTLED_WEBSERVER_CONTROLLER_ESP32_H
