/*
   ESP8266 + FastLED + IR Remote: https://github.com/jasoncoon/esp8266-fastled-webserver
   Copyright (C) 2016 Jason Coon

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
#include "common.h"

const String NumberFieldType = "Number";
const String BooleanFieldType = "Boolean";
const String SelectFieldType = "Select";
const String ColorFieldType = "Color";
const String SectionFieldType = "Section";
const String StringFieldType = "String";
const String LabelFieldType = "Label";
const String UtcOffsetIndexFieldType = "UtcOffsetIndex";

uint8_t power = 1;
uint8_t brightness = brightnessMap[brightnessIndex];

//String setPower(String value) {
//  power = value.toInt();
//  if(power < 0) power = 0;
//  else if (power > 1) power = 1;
//  return String(power);
//}

String getPower() {
  return String(power);
}

//String setBrightness(String value) {
//  brightness = value.toInt();
//  if(brightness < 0) brightness = 0;
//  else if (brightness > 255) brightness = 255;
//  return String(brightness);
//}

// TODO: wrapper class for EEPROM settings, to help ensure clear understanding
//       of all locations that can cause settings committed / EEPROM write.
//       Also simplifies reading prior value before writing new value (extend EEPROM life)
//       Also simplifies later extending CRC, transactional updates, bypassing "dead"
//       areas of EEPROM, etc.

String getBrightness() {
  return String(brightness);
}

String getPattern() {
  return String(currentPatternIndex);
}

String getPatterns() {
  String json = "";

  for (uint8_t i = 0; i < patternCount; i++) {
    json += "\"" + patterns[i].name + "\"";
    if (i < patternCount - 1)
      json += ",";
  }

  return json;
}

String getPalette() {
  return String(currentPaletteIndex);
}

String getPalettes() {
  String json = "";

  for (uint8_t i = 0; i < paletteCount; i++) {
    json += "\"" + paletteNames[i] + "\"";
    if (i < paletteCount - 1)
      json += ",";
  }

  return json;
}

String getAutoplay() {
  return String(autoplay);
}

String getAutoplayDuration() {
  return String(autoplayDuration);
}

String getShowClock() {
  return String(showClock);
}

String getClockBackgroundFade() {
  return String(clockBackgroundFade);
}

void setShowClock(uint8_t value)
{
  showClock = value == 0 ? 0 : 1;
  writeAndCommitSettings();
  broadcastInt("showClock", showClock);
}

void setClockBackgroundFade(uint8_t value)
{
  clockBackgroundFade = value;
  writeAndCommitSettings();
  broadcastInt("clockBackgroundFade", clockBackgroundFade);
}

String getSolidColor() {
  return String(solidColor.r) + "," + String(solidColor.g) + "," + String(solidColor.b);
}

String getCooling() {
  return String(cooling);
}

String getSparking() {
  return String(sparking);
}

String getSpeed() {
  return String(speed);
}

String getTwinkleSpeed() {
  return String(twinkleSpeed);
}

String getTwinkleDensity() {
  return String(twinkleDensity);
}

String getCoolLikeIncandescent() {
  return String(coolLikeIncandescent);
}

String getName() {
  return nameString;
}
String getUtcOffsetIndex() {
  return String(utcOffsetIndex);
}

String setUtcOffsetIndex(uint8_t value)
{
  utcOffsetIndex = value;
  if (utcOffsetIndex > 104) utcOffsetIndex = 104;
  
  const int32_t UTC_OFFSET_MINIMUM_MINUTES = ((int32_t)-12) * 60; // corresponds to index 0
  const int32_t UTC_OFFSET_INCREMENT_MINUTES = 15; // each higher index increments by this amount
  
  // minutes above the minimum
  int32_t tmp = utcOffsetIndex * UTC_OFFSET_INCREMENT_MINUTES;
  // add that to the minimum value
  tmp = UTC_OFFSET_MINIMUM_MINUTES + tmp;
  // convert to seconds
  utcOffsetInSeconds = tmp * 60;

  Serial.print(F("utcOffsetIndex: ")); Serial.println(utcOffsetIndex);
  Serial.print(F("utcOffsetInSeconds: ")); Serial.println(utcOffsetInSeconds);
  timeClient.setTimeOffset(utcOffsetInSeconds);
  writeAndCommitSettings();
  return String(utcOffsetIndex);
}

String setUtcOffsetIndexString(String value)
{
  return setUtcOffsetIndex(value.toInt());
}

// Pride Playground fields

String getSaturationBpm() {
  return String(saturationBpm);
}
String setSaturationBpm(String value)
{
  saturationBpm = value.toInt();
  return value;
}

String getSaturationMin() {
  return String(saturationMin);
}
String setSaturationMin(String value) {
  saturationMin = value.toInt();
  return value;
}

String getSaturationMax() {
  return String(saturationMax);
}
String setSaturationMax(String value) {
  saturationMax = value.toInt();
  return value;
}

String getBrightDepthBpm() {
  return String(brightDepthBpm);
}
String setBrightDepthBpm(String value) {
  brightDepthBpm = value.toInt();
  return value;
}

String getBrightDepthMin() {
  return String(brightDepthMin);
}
String setBrightDepthMin(String value) {
  brightDepthMin = value.toInt();
  return value;
}

String getBrightDepthMax() {
  return String(brightDepthMax);
}
String setBrightDepthMax(String value) {
  brightDepthMax = value.toInt();
  return value;
}

String getBrightThetaIncBpm() {
  return String(brightThetaIncBpm);
}
String setBrightThetaIncBpm(String value) {
  brightThetaIncBpm = value.toInt();
  return value;
}

String getBrightThetaIncMin() {
  return String(brightThetaIncMin);
}
String setBrightThetaIncMin(String value) {
  brightThetaIncMin = value.toInt();
  return value;
}

String getBrightThetaIncMax() {
  return String(brightThetaIncMax);
}
String setBrightThetaIncMax(String value) {
  brightThetaIncMax = value.toInt();
  return value;
}

String getMsMultiplierBpm() {
  return String(msMultiplierBpm);
}
String setMsMultiplierBpm(String value) {
  msMultiplierBpm = value.toInt();
  return value;
}

String getMsMultiplierMin() {
  return String(msMultiplierMin);
}
String setMsMultiplierMin(String value) {
  msMultiplierMin = value.toInt();
  return value;
}

String getMsMultiplierMax() {
  return String(msMultiplierMax);
}
String setMsMultiplierMax(String value) {
  msMultiplierMax = value.toInt();
  return value;
}

String getHueIncBpm() {
  return String(hueIncBpm);
}
String setHueIncBpm(String value) {
  hueIncBpm = value.toInt();
  return value;
}

String getHueIncMin() {
  return String(hueIncMin);
}
String setHueIncMin(String value) {
  hueIncMin = value.toInt();
  return value;
}

String getHueIncMax() {
  return String(hueIncMax);
}
String setHueIncMax(String value) {
  hueIncMax = value.toInt();
  return value;
}

String getSHueBpm() {
  return String(sHueBpm);
}
String setSHueBpm(String value) {
  sHueBpm = value.toInt();
  return value;
}

String getSHueMin() {
  return String(sHueMin);
}
String setSHueMin(String value) {
  sHueMin = value.toInt();
  return value;
}

String getSHueMax() {
  return String(sHueMax);
}
String setSHueMax(String value) {
  sHueMax = value.toInt();
  return value;
}


typedef String (*FieldSetter)(String);
typedef String (*FieldGetter)();
struct Field {
  String name;
  String label;
  String type;
  uint8_t min;
  uint8_t max;
  FieldGetter getValue;
  FieldGetter getOptions;
  FieldSetter setValue;
};

// passing array reference works fine, but need to make the function a template
// to capture the array size... on the positive side, no need to pass `count` parameter
template <size_t N>
Field  getField(String name, const Field (&fields)[N]) {
  for (uint8_t i = 0; i < N; i++) {
    Field field = fields[i];
    if (field.name == name) {
      return field;
    }
  }
  return Field();
}
template <size_t N>
String getFieldValue(String name, const Field (&fields)[N]) {
  Field field = getField(name, fields);
  if (field.getValue) {
    return field.getValue();
  }
  return String();
}
template <size_t N>
String setFieldValue(String name, String value, const Field (&fields)[N]) {
  Field field = getField(name, fields);
  if (field.setValue) {
    return field.setValue(value);
  }
  return String();
}
template <size_t N>
String getFieldsJson(const Field (&fields)[N]) {
  String json = "[";

  for (uint8_t i = 0; i < N; i++) {
    Field field = fields[i];

    json += "{\"name\":\"" + field.name + "\",\"label\":\"" + field.label + "\",\"type\":\"" + field.type + "\"";

    if(field.getValue) {
      if (field.type == ColorFieldType || field.type == StringFieldType || field.type == LabelFieldType) {
        json += ",\"value\":\"" + field.getValue() + "\"";
      }
      else {
        json += ",\"value\":" + field.getValue();
      }
    }

    if (field.type == NumberFieldType || field.type == UtcOffsetIndexFieldType) {
      json += ",\"min\":" + String(field.min);
      json += ",\"max\":" + String(field.max);
    }

    if (field.getOptions) {
      json += ",\"options\":[";
      json += field.getOptions();
      json += "]";
    }

    json += "}";

    if (i < N - 1)
      json += ",";
  }

  json += "]";

  return json;
}

// name, label, type, min, max, getValue, getOptions, setValue
// only items that use the 'getOptions': patterns and palettes
// only items that support 'setValue': options used for pridePlayground
const Field fields[] = {
    {"name",       "Name",       LabelFieldType,   0,            0, getName,       nullptr,     nullptr},

    {"power",      "Power",      BooleanFieldType, 0,            1, getPower,      nullptr,     nullptr},
    {"brightness", "Brightness", NumberFieldType,  1,          255, getBrightness, nullptr,     nullptr},
    {"pattern",    "Pattern",    SelectFieldType,  0, patternCount, getPattern,    getPatterns, nullptr},
    {"palette",    "Palette",    SelectFieldType,  0, paletteCount, getPalette,    getPalettes, nullptr},
    {"speed",      "Speed",      NumberFieldType,  1,          255, getSpeed,      nullptr,     nullptr},

    //--------------------------------------------------------------------------------------------------------
    {"autoplaySection",  "Autoplay",          SectionFieldType, 0,   0, nullptr,             nullptr, nullptr},
    {"autoplay",         "Autoplay",          BooleanFieldType, 0,   1, getAutoplay,         nullptr, nullptr},
    {"autoplayDuration", "Autoplay Duration", NumberFieldType,  0, 255, getAutoplayDuration, nullptr, nullptr},

    //--------------------------------------------------------------------------------------------------------
    {"clock",               "Clock",           SectionFieldType,        0,   0, nullptr,                nullptr, nullptr},	
    {"showClock",           "Show Clock",      BooleanFieldType,        0,   1, getShowClock,           nullptr, nullptr},	
    {"clockBackgroundFade", "Background Fade", NumberFieldType,         0, 255, getClockBackgroundFade, nullptr, nullptr},
    {"utcOffsetIndex",      "UTC Offset",      UtcOffsetIndexFieldType, 0, 104, getUtcOffsetIndex,      nullptr, setUtcOffsetIndexString},

    //--------------------------------------------------------------------------------------------------------
    {"solidColorSection", "Solid Color", SectionFieldType, 0,   0, nullptr,       nullptr, nullptr},
    {"solidColor",        "Color",       ColorFieldType,   0, 255, getSolidColor, nullptr, nullptr},

    //--------------------------------------------------------------------------------------------------------
    {"fireSection", "Fire & Water", SectionFieldType, 0,   0, nullptr,     nullptr, nullptr},
    {"cooling",     "Cooling",      NumberFieldType,  0, 255, getCooling,  nullptr, nullptr},
    {"sparking",    "Sparking",     NumberFieldType,  0, 255, getSparking, nullptr, nullptr},

    //--------------------------------------------------------------------------------------------------------
    {"twinklesSection",      "Twinkles",          SectionFieldType, 0, 0, nullptr,                 nullptr, nullptr},
    {"twinkleSpeed",         "Twinkle Speed",     NumberFieldType,  0, 8, getTwinkleSpeed,         nullptr, nullptr},
    {"twinkleDensity",       "Twinkle Density",   NumberFieldType,  0, 8, getTwinkleDensity,       nullptr, nullptr},
    {"coolLikeIncandescent", "Incandescent Cool", BooleanFieldType, 0, 1, getCoolLikeIncandescent, nullptr, nullptr},


    //--------------------------------------------------------------------------------------------------------
    {"prideSection",  "Pride Playground",         SectionFieldType, 0,   0, nullptr, nullptr, nullptr},

    {"saturationBpm", "Saturation BPM",           NumberFieldType,  0, 255, getSaturationBpm, nullptr, setSaturationBpm},
    {"saturationMin", "Saturation Min",           NumberFieldType,  0, 255, getSaturationMin, nullptr, setSaturationMin},
    {"saturationMax", "Saturation Max",           NumberFieldType,  0, 255, getSaturationMax, nullptr, setSaturationMax},

    {"brightDepthBpm", "Brightness Depth BPM",    NumberFieldType, 0, 255, getBrightDepthBpm, nullptr, setBrightDepthBpm},
    {"brightDepthMin", "Brightness Depth Min",    NumberFieldType, 0, 255, getBrightDepthMin, nullptr, setBrightDepthMin},
    {"brightDepthMax", "Brightness Depth Max",    NumberFieldType, 0, 255, getBrightDepthMax, nullptr, setBrightDepthMax},

    {"brightThetaIncBpm", "Bright Theta Inc BPM", NumberFieldType, 0, 255, getBrightThetaIncBpm, nullptr, setBrightThetaIncBpm},
    {"brightThetaIncMin", "Bright Theta Inc Min", NumberFieldType, 0, 255, getBrightThetaIncMin, nullptr, setBrightThetaIncMin},
    {"brightThetaIncMax", "Bright Theta Inc Max", NumberFieldType, 0, 255, getBrightThetaIncMax, nullptr, setBrightThetaIncMax},

    {"msMultiplierBpm", "Time Multiplier BPM",    NumberFieldType, 0, 255, getMsMultiplierBpm, nullptr, setMsMultiplierBpm},
    {"msMultiplierMin", "Time Multiplier Min",    NumberFieldType, 0, 255, getMsMultiplierMin, nullptr, setMsMultiplierMin},
    {"msMultiplierMax", "Time Multiplier Max",    NumberFieldType, 0, 255, getMsMultiplierMax, nullptr, setMsMultiplierMax},

    {"hueIncBpm", "Hue Inc BPM",                  NumberFieldType, 0, 255, getHueIncBpm, nullptr, setHueIncBpm},
    {"hueIncMin", "Hue Inc Min",                  NumberFieldType, 0, 255, getHueIncMin, nullptr, setHueIncMin},
    {"hueIncMax", "Hue Inc Max",                  NumberFieldType, 0, 255, getHueIncMax, nullptr, setHueIncMax},

    {"sHueBpm", "S Hue BPM",                      NumberFieldType, 0, 255, getSHueBpm, nullptr, setSHueBpm},
    {"sHueMin", "S Hue Min",                      NumberFieldType, 0, 255, getSHueMin, nullptr, setSHueMin},
    {"sHueMax", "S Hue Max",                      NumberFieldType, 0, 255, getSHueMax, nullptr, setSHueMax},
};

const uint8_t fieldCount = ARRAY_SIZE2(fields);
// TODO: consider using ArduinoJSON ... pre-allocated buffer, simpler usage, tested code

Field getField(String name) {
  return getField(name, fields);
}
String getFieldValue(String name) {
  return getFieldValue(name, fields);
}
String setFieldValue(String name, String value) {
  return setFieldValue(name, value, fields);
}
String getFieldsJson() {
  return getFieldsJson(fields);
}

