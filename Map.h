uint8_t coordsX[NUM_LEDS] = { 255, 240, 234, 216, 221, 224, 204, 204, 201, 185, 196, 214, 228, 187, 188, 178, 156, 138, 129, 124, 127, 167, 175, 161, 146, 153, 141, 124, 105, 121, 127, 106, 106, 94, 89, 80, 74, 65, 54, 44, 26, 33, 38, 59, 80, 93, 103, 112, 14, 15, 5, 0, 4, 17, 42, 66, 81, 76, 53, 33, 37, 59, 63, 47 };
uint8_t coordsY[NUM_LEDS] = { 127, 155, 121, 122, 155, 191, 209, 175, 139, 105, 82, 60, 43, 165, 193, 135, 144, 142, 110, 75, 36, 171, 225, 199, 172, 244, 211, 161, 150, 194, 244, 255, 219, 187, 237, 209, 173, 233, 192, 216, 233, 187, 155, 150, 138, 105, 74, 40, 184, 154, 124, 90, 53, 19, 0, 9, 39, 80, 96, 76, 33, 30, 63, 57 };
uint8_t angles[NUM_LEDS] = { 179, 192, 176, 175, 195, 212, 225, 210, 188, 158, 146, 141, 139, 211, 226, 187, 209, 233, 95, 85, 89, 226, 243, 244, 246, 256, 259, 274, 313, 274, 269, 278, 282, 298, 288, 299, 318, 299, 317, 312, 312, 326, 341, 340, 346, 31, 65, 79, 332, 345, 0, 15, 30, 43, 55, 61, 61, 41, 22, 27, 45, 54, 44, 40 };
uint8_t radii[NUM_LEDS] = { 206, 185, 168, 135, 150, 185, 178, 137, 107, 83, 122, 172, 213, 101, 134, 64, 32, 3, 0, 65, 137, 80, 172, 116, 59, 191, 126, 31, 28, 93, 186, 210, 144, 95, 185, 144, 99, 197, 150, 195, 241, 175, 141, 101, 57, 43, 77, 132, 204, 182, 196, 215, 236, 255, 253, 215, 153, 97, 118, 167, 210, 188, 137, 166 };

void setPixelAR(uint8_t angle, uint8_t dAngle, uint8_t radius, uint8_t dRadius, CRGB color)
{
  uint16_t amax = qadd8(angle, dAngle);
  uint8_t amin = qsub8(angle, dAngle);

  uint16_t rmax = qadd8(radius, dRadius);
  uint16_t rmin = qsub8(radius, dRadius);

  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    uint8_t o = i;

    uint8_t ao = angles[o];

    if (ao <= amax && ao >= amin) {
      uint8_t ro = radii[o];

      if (ro <= rmax && ro >= rmin) {
        leds[i] = color;
      }
    }
  }
}

void andPixelAR(uint8_t angle, uint8_t dAngle, uint8_t startRadius, uint8_t endRadius, CRGB color)
{
  uint16_t amax = qadd8(angle, dAngle);
  uint8_t amin = qsub8(angle, dAngle);

  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    uint8_t o = i;

    uint8_t ao = angles[o];

    if (ao <= amax && ao >= amin) {
      uint8_t ro = radii[o];

      if (ro <= endRadius && ro >= startRadius) {
        leds[i] += color;
      }
    }
  }
}

void antialiasPixelAR(uint8_t angle, uint8_t dAngle, uint8_t startRadius, uint8_t endRadius, CRGB color)
{
  uint16_t amax = qadd8(angle, dAngle);
  uint8_t amin = qsub8(angle, dAngle);

  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    uint8_t o = i;

    uint8_t ao = angles[o];

    uint8_t adiff = qsub8(max(ao, angle), min(ao, angle));
    uint8_t fade = qmul8(adiff, 32);
    CRGB faded = color;
    faded.fadeToBlackBy(fade);

    if (ao <= amax && ao >= amin) {
      uint8_t ro = radii[o];

      if (ro <= endRadius && ro >= startRadius) {
        leds[i] += faded;
      }
    }
  }
}

void anglePalette() {
  uint8_t hues = 1;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = angles[i];

    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - (x * hues));
  }
}

void radiusPalette() {
  uint8_t hues = 1;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t r = radii[i];
    
    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - (r * hues));
  }
}

void xPalette() {
  uint8_t hues = 1;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = coordsX[i];

    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - (x * hues));
  }
}

void yPalette() {
  uint8_t hues = 1;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t y = coordsY[i];

    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) + (y * hues));
  }
}

void xyPalette() {
  uint8_t hues = 1;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = coordsX[i];
    uint8_t y = coordsY[i];

    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - ((x + y) * hues));
  }
}

void angleGradientPalette() {
  uint8_t hues = 1;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = angles[i];

    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) - (x * hues));
  }
}

void radiusGradientPalette() {
  uint8_t hues = 1;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t r = radii[i];
    
    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) - (r * hues));
  }
}

void xGradientPalette() {
  uint8_t hues = 1;
  
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = coordsX[i];

    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) - (x * hues));
  }
}

void yGradientPalette() {
  uint8_t hues = 1;
  
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t y = coordsY[i];

    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) + (y * hues));
  }
}

void xyGradientPalette() {
  uint8_t hues = 1;
  
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = coordsX[i];
    uint8_t y = coordsY[i];

    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) - ((x + y) * hues));
  }
}

void drawAnalogClock() {
  float second = timeClient.getSeconds();
  float minute = timeClient.getMinutes() + (second / 60.0);
  float hour = timeClient.getHours() + (minute / 60.0);

  static uint8_t hourAngle = 0;
  static uint8_t minuteAngle = 0;
  static uint8_t secondAngle = 0;

  const uint8_t hourRadius = 64;
  const uint8_t minuteRadius = 96;
  const uint8_t secondRadius = 255;

  const uint8_t handWidth = 64;

  const float degreesPerSecond = 255.0 / 60.0;
  const float degreesPerMinute = 255.0 / 60.0;
  const float degreesPerHour = 255.0 / 12.0;

  EVERY_N_MILLIS(100) {
    hourAngle = 255 - hour * degreesPerHour;
    minuteAngle = 255 - minute * degreesPerMinute;
    secondAngle = 255 - second * degreesPerSecond;
  }

  fadeToBlackBy(leds, NUM_LEDS, clockBackgroundFade);

  antialiasPixelAR(secondAngle, handWidth, 0, secondRadius, CRGB::Blue);
  antialiasPixelAR(minuteAngle, handWidth, 0, minuteRadius, CRGB::Green);
  antialiasPixelAR(hourAngle, handWidth, 0, hourRadius, CRGB::Red);
  leds[0] = CRGB::Red;
}
