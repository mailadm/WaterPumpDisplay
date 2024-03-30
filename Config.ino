//-------------------------------------------------------------------------------------------------------------------------------------------
bool loadConfig() {
  File configFile = SPIFFS.open("/config.json", "r");
  if(!configFile) {
    printErr("Load config error");
    return false;
  }
  size_t size = configFile.size();
  if(size > 256){
    printErr("Size to large");
    return false;
  }
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  StaticJsonBuffer<256> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());
  if(!json.success()){
    printErr("Parse error");
    return false; 
  }
  const char* json_ssid = json["json_ssid"];
  strncpy(wifi_ssid, json_ssid, 10);
  const char* json_paswd = json["json_paswd"];
  strncpy(wifi_password, json_paswd, 15);
  configFile.close();
  return true;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
bool saveConfig() {
  StaticJsonBuffer<256> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["json_ssid"] = wifi_ssid;  json["json_paswd"] = wifi_password;
  File configFile = SPIFFS.open("/config.json", "w");
  if(!configFile) {
    printErr("No config file");
    return false;
  }
  json.printTo(configFile);
  configFile.close();
  return true;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
