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

#error #if !defined(ESP8266_FASTLED_WEBSERVER_PRODUCT_xyzzy_H)
#error #define ESP8266_FASTLED_WEBSERVER_PRODUCT_xyzzy_H

// This template documents the settings to configure a specific "product"
// for building from this repository.

// The following are MANDATORY ... they must be defined to appropriate values
// This template provides the default values as used by the prior main branch

// LED_TYPE defines the control pattern for the LEDs
// See https://github.com/FastLED/FastLED/blob/b5874b588ade1d2639925e4e9719fa7d3c9d9e94/src/FastLED.h#L92-L119
#define LED_TYPE                      WS2811

// COLOR_ORDER defines the order that each pixel expects the data to arrive in
// See https://github.com/FastLED/FastLED/blob/765d4244889a692bb453cd4087af31e01c937035/src/pixeltypes.h#L852-L859
#define COLOR_ORDER                   RGB

// NUM_PIXELS  is the number of pixels to be 
#define NUM_PIXELS                    200
#error #define AVAILABLE_MILLI_AMPS          x2000x // IMPORTANT: set the max milli-Amps of your power supply (4A = 4000mA)
#define MAX_MILLI_AMPS_PER_PIXEL      60
#define FRAMES_PER_SECOND             120
#define DEFAULT_PATTERN_INDEX         0

// DEFAULT_COLOR_CORRECTION defines which FastLED built-in color correction to apply
// Options include:
//     TypicalSMD5050     // 0xFFB0F0 == 255, 176, 240
//     TypicalLEDStrip    // 0xFFB0F0 == 255, 176, 240
//     Typical8mmPixel    // 0xFFE08C == 255, 224, 140
//     TypicalPixelString // 0xFFE08C == 255, 224, 140
//     UncorrectedColor   // 0xFFFFFF == 255, 255, 255
//
// Likely that you can encode any RGB value:
//     static_cast<LEDColorCorrection>(0xRRGGBB) 
//
// See https://github.com/FastLED/FastLED/blob/b5874b588ade1d2639925e4e9719fa7d3c9d9e94/src/color.h#L13-L32
#define DEFAULT_COLOR_CORRECTION      TypicalLEDStrip


// NAME_PREFIX defines the product-specific prefix for auto-generated hostname
#define NAME_PREFIX                   "ESP8266-"

// PRODUCT_FRIENDLY_NAME is used in HTML page's title and navigation bar
// It is modified when js/app.js loads, by parsing json data generated from device
#define PRODUCT_FRIENDLY_NAME         "ESP8266 + FastLED"

// IS_FIBONACCI is true when there are fibonacci-specific definitions for the product.
// TODO: Consider splitting to two variables:
//       1. HAS_LED_MAP
//          Indicates existence of coordsX[], coordsY[] and angles[]
//       2. IS_FIBONACCI
//          Implies HAS_LED_MAP, plus physicalToFibonacci[] and fibonacciToPhysical[]
//
// When this is true, the following must be defined in map.h:
//
// const uint16_t physicalToFibonacci[NUM_PIXELS];
// const uint16_t fibonacciToPhysical[NUM_PIXELS];
// const uint8_t coordsX[NUM_PIXELS];
// const uint8_t coordsY[NUM_PIXELS];
// const uint8_t angles[NUM_PIXELS];
#define IS_FIBONACCI                  0

// By default, no IR support is included.  Define ENABLE_IR to enable IR support.
// #define ENABLE_IR
// NOTE: When ENABLE_IR is defined, can also override controller-specific default:
// #define IR_RECV_PIN  D99

#error #endif // ESP8266_FASTLED_WEBSERVER_PRODUCT_xyzz_H
