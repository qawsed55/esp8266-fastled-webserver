String WiFi_SSID(bool persistent) {
    struct station_config conf;
    if(persistent) wifi_station_get_config_default(&conf);
    else wifi_station_get_config(&conf);

    const size_t buffer_len = sizeof(conf.ssid)+1; //ssid can be up to 32chars, => plus null term
    char tmp[buffer_len];
    memcpy(tmp, conf.ssid, sizeof(conf.ssid));
    tmp[buffer_len-1] = 0; //nullterm in case of 32 char ssid
    return String(reinterpret_cast<char*>(tmp));
}

String getInfoJson()
{
  String json = "{";
  json += "\"millis\":" + (String)millis() + ",";
  json += "\"vcc\":" + (String)ESP.getVcc() + ",";
  json += "\"wiFiChipId\":\"" + String(WIFI_getChipId(), HEX) + "\",";
  json += "\"flashChipId\":\"" + String(ESP.getFlashChipId(), HEX) + "\",";
  json += "\"flashChipSize\":" + (String)ESP.getFlashChipSize() + ",";
  json += "\"flashChipRealSize\":" + (String)ESP.getFlashChipRealSize() + ",";
  json += "\"sdkVersion\":\"" + (String)system_get_sdk_version() + "\",";
  json += "\"coreVersion\":\"" + (String)ESP.getCoreVersion() + "\",";
  json += "\"bootVersion\":" + (String)system_get_boot_version() + ",";
  json += "\"cpuFreqMHz\":" + (String)ESP.getCpuFreqMHz() + ",";
  json += "\"freeHeap\":" + (String)ESP.getFreeHeap() + ",";
  json += "\"sketchSize\":" + (String)ESP.getSketchSize() + ",";
  json += "\"freeSketchSpace\":" + (String)ESP.getFreeSketchSpace() + ",";
  json += "\"resetReason\":\"" + (String)ESP.getResetReason() + "\",";
  json += "\"isConnected\":" + (WiFi.isConnected() ? String("true") : String("false")) + ",";
  json += "\"wiFiSsidDefault\":\"" + (String)WiFi_SSID(true) + "\",";
  json += "\"wiFiSSID\":\"" + (String)WiFi_SSID(false) + "\",";
  json += "\"localIP\":\"" + WiFi.localIP().toString() + "\",";
  json += "\"gatewayIP\":\"" + WiFi.gatewayIP().toString() + "\",";
  json += "\"subnetMask\":\"" + WiFi.subnetMask().toString() + "\",";
  json += "\"dnsIP\":\"" + WiFi.dnsIP().toString() + "\",";
  json += "\"hostname\":\"" + WiFi.hostname() + "\",";
  json += "\"macAddress\":\"" + WiFi.macAddress() + "\",";
  json += "\"autoConnect\":" + (WiFi.getAutoConnect() ? String("true") : String("false")) + ",";
  json += "\"softAPSSID\":\"" + WiFi.softAPSSID() + "\",";
  json += "\"softAPIP\":\"" + WiFi.softAPIP().toString() + "\",";
  json += "\"BSSID\":\"" + (String)WiFi.BSSIDstr() + "\",";
  json += "\"softAPmacAddress\":\"" + (String)WiFi.softAPmacAddress() + "\"";
  json += "}";

  return json;
}
