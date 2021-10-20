/*
   ESP8266 + FastLED: https://github.com/jasoncoon/esp8266-fastled-webserver
   Copyright (C) 2015-2020 Jason Coon

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

// drawNoise() function uses coordsX / coordsY
#if HAS_COORDINATE_MAP

// TODO: static assert that the values here correspond to the maximum storable value
//       used by the typeof(coordsX) and typeof(coordsY).
const uint8_t matrixWidth  = 255;
const uint8_t matrixHeight = 255;

#define MAX_DIMENSION ((matrixWidth > matrixHeight) ? matrixWidth : matrixHeight)

// The larger (16-bit) version of our coordinates
static uint16_t noisex;
static uint16_t noisey;
static uint16_t noisez;

// We're using the x/y dimensions to map to the x/y pixels on the matrix.  We'll
// use the z-axis for "time".  speed determines how fast time moves forward.  Try
// 1 for a very slow moving effect, or 60 for something that ends up looking like
// water.
static int noisespeedx = 0;
static int noisespeedy = 1;
static int noisespeedz = 0;

// Scale determines how far apart the pixels in our noise matrix are.  Try
// changing these values around to see how it affects the motion of the display.  The
// higher the value of scale, the more "zoomed out" the noise will be.  A value
// of 1 will be so zoomed in, you'll mostly see solid colors.
static uint16_t noisescale = 1; // scale is set dynamically once we've started up

static uint8_t colorLoop = 0;

static const CRGBPalette16 blackAndWhiteStripedPalette {
  CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black,
  CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black,
  CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black,
  CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black
};

static const CRGBPalette16 blackAndBlueStripedPalette {
  CRGB::Blue,  CRGB::Blue,  CRGB::Blue,  CRGB::Blue,
  CRGB::Blue,  CRGB::Blue,  CRGB::Black, CRGB::Black,
  CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black,
  CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black
};

// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.

CRGB noiseXYZ(CRGBPalette16 palette, uint8_t hueReduce, int x, int y, int z)
{
  uint8_t data = inoise8(x, y, z);
  // The range of the inoise8 function is roughly 16-238.
  // These two operations expand those values out to roughly 0..255
  // You can comment them out if you want the raw noise data.
  data = qsub8(data, 16);
  data = qadd8(data, scale8(data, 39));

  if (hueReduce > 0 && data >= hueReduce) {
    data -= hueReduce;
  }

  return ColorFromPalette(palette, data, 255, LINEARBLEND);
}

void drawNoise(CRGBPalette16 palette, uint8_t hueReduce = 0)
{
  for (uint16_t i = 0; i < NUM_PIXELS; i++) {
    uint8_t x = coordsX[i];
    uint8_t y = coordsY[i];

    int xoffset = noisescale * x;
    int yoffset = noisescale * y;

    leds[i] = noiseXYZ(palette, hueReduce, x + xoffset + noisex, y + yoffset + noisey, noisez);
  }

  noisex += noisespeedx;
  noisey += noisespeedy;
  noisez += noisespeedz;
}

#if HAS_POLAR_COORDS // change to "HAS_CONCENTRIC_RINGS" ?

// TODO: The calculations for x/y in drawPolarNoise() depend only upon constant array values.
//       Pre-calculate those, and define a proxy for noise() routine that points to this
//       pre-calculated array.  Then, the code is identical for all noise() functions, differing
//       only in the X/Y arrays and palette used.

// drawPolarNoise() uses rings[]
void drawPolarNoise(CRGBPalette16 palette, uint8_t hueReduce = 0)
{
  for (uint8_t ringIndex = 0; ringIndex < ringCount; ringIndex++) { // y == proxy for radius
    uint16_t ringStart = rings[ringIndex][0];
    uint16_t ringEnd = rings[ringIndex][1];
    
    for (uint16_t i = ringStart; i <= ringEnd; i++) { // x
      uint8_t x = (i - ringStart) * (256 / (ringEnd - ringStart)); // proxy for angle[]?
      uint8_t y = ringIndex * (128 / ringCount); // 128 / 20 == 6 ... or about half the total range ... could use (radius[] / 2)?
      
      int xoffset = noisescale * x;
      int yoffset = noisescale * y;

      leds[i] = noiseXYZ(palette, hueReduce, x + xoffset + noisex, y + yoffset + noisey, noisez);
    }
  }
  // for (uint8_t ringIndex = 1; ringIndex < ringCount; ringIndex++) {
  //   uint16_t ringStart = rings[ringIndex][0];
  //   uint16_t ringEnd = rings[ringIndex][1];
  //   // blend the first pixel in the ring into the last
  //   nblend(leds[ringStart], leds[ringEnd], 192);
  //   nblend(leds[ringStart + 1], leds[ringEnd - 1], 128);
  //   nblend(leds[ringStart + 2], leds[ringEnd - 2], 64);
  // }
  
  noisex += noisespeedx;
  noisey += noisespeedy;
  noisez += noisespeedz;
}

#endif // HAS_POLAR_COORDS

#if HAS_POLAR_COORDS //  uses drawPolarNoise(), which uses rings[]
// TODO: Check if gradientPalettePolarNoise() is equivalent to angleGradientPalette()?
void gradientPalettePolarNoise() {
  noisespeedx = 4;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 1;
  colorLoop = 0;
  drawPolarNoise(gCurrentPalette);
}
#endif
#if HAS_POLAR_COORDS // palettePolarNoise() uses drawPolarNoise(), which uses rings[]
void palettePolarNoise() {
  noisespeedx = 9;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 1;
  colorLoop = 0;
  drawPolarNoise(palettes[currentPaletteIndex]);
}
#endif

void rainbowNoise() {
  noisespeedx = 0;
  noisespeedy = -1;
  noisespeedz = 0;
  noisescale = 6;
  colorLoop = 0;
  drawNoise(RainbowColors_p);
}

#if HAS_POLAR_COORDS // rainbowPolarNoise() uses drawPolarNoise(), which uses rings[]
void rainbowPolarNoise() {
  noisespeedx = 0;
  noisespeedy = 2;
  noisespeedz = 0;
  noisescale = 0;
  colorLoop = 0;
  drawPolarNoise(RainbowColors_p);
}
#endif // HAS_POLAR_COORDS

void rainbowStripeNoise() {
  noisespeedx = 0;
  noisespeedy = -2;
  noisespeedz = 0;
  noisescale = 6;
  colorLoop = 0;
  drawNoise(RainbowStripeColors_p);
}

#if HAS_POLAR_COORDS // rainbowStripePolarNoise() uses drawPolarNoise(), which uses rings[]
void rainbowStripePolarNoise() {
  noisespeedx = 0;
  noisespeedy = 2;
  noisespeedz = 0;
  noisescale = 0;
  colorLoop = 0;
  drawPolarNoise(RainbowStripeColors_p);
}
#endif

void partyNoise() {
  noisespeedx = -9;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 8;
  colorLoop = 0;
  drawNoise(PartyColors_p);
}

#if HAS_POLAR_COORDS // partyPolarNoise() uses drawPolarNoise(), which uses rings[]
void partyPolarNoise() {
  noisespeedx = 9;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 1;
  colorLoop = 0;
  drawPolarNoise(PartyColors_p);
}
#endif

void forestNoise() {
  noisespeedx = -9;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 8;
  colorLoop = 0;
  drawNoise(ForestColors_p);
}

#if HAS_POLAR_COORDS // forestPolarNoise() uses drawPolarNoise(), which uses rings[]
void forestPolarNoise() {
  noisespeedx = 9;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 1;
  colorLoop = 0;
  drawPolarNoise(ForestColors_p);
}
#endif

void cloudNoise() {
  noisespeedx = -2;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 6;
  colorLoop = 0;
  drawNoise(CloudColors_p);
}

#if HAS_POLAR_COORDS // cloudPolarNoise() uses drawPolarNoise(), which uses rings[]
void cloudPolarNoise() {
  noisespeedx = 2;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 0;
  colorLoop = 0;
  drawPolarNoise(CloudColors_p);
}
#endif

void fireNoise() {
  noisespeedx = 0; // 24;
  noisespeedy = -32;
  noisespeedz = 0;
  noisescale = 16;
  colorLoop = 0;
  drawNoise(HeatColors_p, 60);
}

#if HAS_POLAR_COORDS // firePolarNoise() uses drawPolarNoise(), which uses rings[]
void firePolarNoise() {
//  noisespeedx = 0; // 24;
//  noisespeedy = -24;
//  noisespeedz = 0;
//  noisescale = 4;
//  colorLoop = 0;
  noisespeedx = 0; // 24;
  noisespeedy = -32;
  noisespeedz = 0;
  noisescale = 4;
  colorLoop = 0;
  drawPolarNoise(HeatColors_p, 60);
}
#endif

void fireNoise2() {
  noisespeedx = 0;
  noisespeedy = -8;
  noisespeedz = 3;
  noisescale = 8;
  colorLoop = 0;
  drawNoise(HeatColors_p);
}

#if HAS_POLAR_COORDS // firePolarNoise2() uses drawPolarNoise(), which uses rings[]
void firePolarNoise2() {
//  noisespeedx = 0;
//  noisespeedy = -8;
//  noisespeedz = 4;
//  noisescale = 1;
//  colorLoop = 0;
  noisespeedx = 0;
  noisespeedy = -4;
  noisespeedz = 4;
  noisescale = 1;
  colorLoop = 0;
  drawPolarNoise(HeatColors_p);
}
#endif

void lavaNoise() {
  noisespeedx = 0;
  noisespeedy = -1;
  noisespeedz = 1;
  noisescale = 6;
  colorLoop = 0;
  drawNoise(LavaColors_p);
}

#if HAS_POLAR_COORDS // lavaPolarNoise() uses drawPolarNoise(), which uses rings[]
void lavaPolarNoise() {
  noisespeedx = 0;
  noisespeedy = -1;
  noisespeedz = 1;
  noisescale = 1;
  colorLoop = 0;
  drawPolarNoise(LavaColors_p);
}
#endif

void oceanNoise() {
  noisespeedx = -2;
  noisespeedy = 0;
  noisespeedz = 4;
  noisescale = 6;
  colorLoop = 0;
  drawNoise(OceanColors_p);
}

#if HAS_POLAR_COORDS // oceanPolarNoise() uses drawPolarNoise(), which uses rings[]
void oceanPolarNoise() {
  noisespeedx = -1; // beatsin8(6, 0, 2) - 1;
  noisespeedy = 0;
  noisespeedz = 1;
  noisescale = 0;
  colorLoop = 0;
  drawPolarNoise(OceanColors_p);
}
#endif

void blackAndWhiteNoise() {
  noisespeedx = -12;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 6;
  colorLoop = 0;
  drawNoise(blackAndWhiteStripedPalette);
}

#if HAS_POLAR_COORDS // blackAndWhitePolarNoise() uses drawPolarNoise(), which uses rings[]
void blackAndWhitePolarNoise() {
  noisespeedx = -4; // beatsin8(8, 0, 9) - 4;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 0;
  colorLoop = 0;
  drawPolarNoise(blackAndWhiteStripedPalette);
}
#endif

void blackAndBlueNoise() {
  noisespeedx = 0;
  noisespeedy = 8;
  noisespeedz = 0;
  noisescale = 8;
  colorLoop = 0;
  drawNoise(blackAndBlueStripedPalette);
}

#if HAS_POLAR_COORDS // blackAndBluePolarNoise() uses drawPolarNoise(), which uses rings[]
void blackAndBluePolarNoise() {
  noisespeedx = 0;
  noisespeedy = -8; // beatsin8(8, 0, 16) - 8;
  noisespeedz = 0;
  noisescale = 1;
  colorLoop = 0;
  drawPolarNoise(blackAndBlueStripedPalette);
}
#endif

#endif // HAS_COORDINATE_MAP