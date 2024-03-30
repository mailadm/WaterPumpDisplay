//----------------------------------------------------------------------------------------------
void pumpOn(){
  printPumpON();
  digitalWrite(4, 0);
  digitalWrite(15, 1);
  digitalWrite(LED_BUILTIN, LOW);
}
//----------------------------------------------------------------------------------------------
void pumpOff(){
    printPumpOFF();
    digitalWrite(4, 1);
    digitalWrite(15, 0);
    digitalWrite(LED_BUILTIN, HIGH);
}
//----------------------------------------------------------------------------------------------
void displayInit(){
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.clearBuffer(); 
  u8g2.setFont(u8g2_font_unifont_t_cyrillic);
  //u8g2.setFont(u8g2_font_10x20_t_cyrillic);
  //u8g2.setFont(u8g2_font_cu12_t_cyrillic);
  //u8g2.setFont(u8g2_font_inr24_t_cyrillic);
  u8g2.setFontDirection(0);
}
//----------------------------------------------------------------------------------------------
void printErr(String msg){
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 10);
    u8g2.print(msg);
    } while (u8g2.nextPage()); 
}

//----------------------------------------------------------------------------------------------
void printConfig(){
  u8g2.firstPage();
  do {
      u8g2.setCursor(0, 10);
      u8g2.print("  ACCESS POINT");
      u8g2.setCursor(0, 28);
      u8g2.print("IP: "); u8g2.print(WiFi.softAPIP());
      u8g2.setCursor(0, 44);
      u8g2.print("SSID: "); u8g2.print(APSSID);
      u8g2.setCursor(0, 60);
      u8g2.print("PASS: "); u8g2.print(APPSK);
    } while (u8g2.nextPage());    
}
//----------------------------------------------------------------------------------------------
void printWebConfig(){
  u8g2.firstPage();
  do {
      u8g2.setCursor(0, 10);
      u8g2.print("   WEB SERVER");
      u8g2.setCursor(0, 28);
      u8g2.print("IP: "); u8g2.print(WiFi.localIP());
      u8g2.setCursor(0, 44);
      u8g2.print("KEY: "); u8g2.print(PUMPKEY);
      u8g2.setCursor(0, 60);
      u8g2.print("STATUS: ");
    } while (u8g2.nextPage());      
}
//----------------------------------------------------------------------------------------------
void printPumpON(){
  u8g2.firstPage();
  do {
      u8g2.setCursor(0, 10);
      u8g2.print("   WEB SERVER");
      u8g2.setCursor(0, 28);
      u8g2.print("IP: "); u8g2.print(WiFi.localIP());
      u8g2.setCursor(0, 44);
      u8g2.print("KEY: "); u8g2.print(PUMPKEY);
      u8g2.setCursor(0, 60);
      u8g2.print("STATUS: PUMP ON");
    } while (u8g2.nextPage());        
}
//----------------------------------------------------------------------------------------------
void printPumpOFF(){
  u8g2.firstPage();
  do {
      u8g2.setCursor(0, 10);
      u8g2.print("   WEB SERVER");
      u8g2.setCursor(0, 28);
      u8g2.print("IP: "); u8g2.print(WiFi.localIP());
      u8g2.setCursor(0, 44);
      u8g2.print("KEY: "); u8g2.print(PUMPKEY);
      u8g2.setCursor(0, 60);
      u8g2.print("STATUS: PUMP OFF");
    } while (u8g2.nextPage());
}
//----------------------------------------------------------------------------------------------
void scanNework(void){
  delay(100);
  int n = WiFi.scanNetworks();
  st = "";
  for (int i = 0; i < n; ++i){
    st += " => ";
    st += WiFi.SSID(i);
    st += " (";
    st += WiFi.RSSI(i);
    st += ")";
    st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
    st += "<br/>";
  }
  delay(100);
}
//----------------------------------------------------------------------------------------------
