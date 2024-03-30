#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include <U8g2lib.h>
#include <ArduinoJson.h>
//#include <SPI.h>
#include "FS.h"

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 12, 14, U8X8_PIN_NONE);

#ifndef APSSID
  #define APSSID "WiFiPump"
  #define APPSK "WaterPump"
  #define PUMPKEY "z5dG9r"
#endif

#ifndef MQTT_SERVER
  #define MQTT_SERVER "m9.wqtt.ru"
  #define MQTT_PORT 15794
  #define MQTT_USER "u_XLCMK6"
  #define MQTT_PASSWORD "r7Ier6j8"
  #define MQTT_TOPIC "releControl"
#endif

const char* mqtt_server = MQTT_SERVER;
const int mqtt_port = MQTT_PORT;
const char* mqtt_user = MQTT_USER;
const char* mqtt_password = MQTT_PASSWORD;
const String relay_topic = MQTT_TOPIC;

const char *ssid = APSSID;
const char *password = APPSK;
char wifi_ssid[10];
char wifi_password[15];
int statusCode;
String content;
String st;

IPAddress apIP(192, 168, 1, 1);
ESP8266WebServer server(80);
WiFiClient espClient;
PubSubClient client(espClient);

//-------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(4, OUTPUT);
  digitalWrite(4, 0);
  pinMode(15, OUTPUT);
  digitalWrite(15, 0);
  displayInit();
  
  if(!SPIFFS.begin()){
      printErr("Error moun SPIFFS");
      return;
  }

  //strncpy(wifi_ssid, ssid, 10);
  //strncpy(wifi_password, password, 15); 
  //saveConfig();
  //return;
  

  loadConfig();
  
  WiFi.mode(WIFI_STA);
  if (strcmp(wifi_ssid, ssid) == 0 && strcmp(wifi_password, password) == 0 ) {
    scanNework();
    WiFi.mode(WIFI_OFF);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssid,password);
    printConfig();
    server.on("/", handleAPRoot);
    server.on("/setting", handleAPSetting);
    server.begin();
  }else{
    WiFi.begin(wifi_ssid, wifi_password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      //tft.print(".");
    }
    
    printWebConfig();
    server.on("/", handleWebRoot);
    server.on("/pump", handlePump);
    server.begin();

    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void loop() {
  server.handleClient();
  if (!client.connected()) reconnect();
  client.loop(); 
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void handleWebRoot(){
  content = getWebRootContent();
  server.send(200, "text/html", content);  
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void handleAPRoot(){
  content = getRootPageContent();
  server.send(200, "text/html", content);  
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void handlePump(){
  String qkey = server.arg("key");       
  String qcmd = server.arg("cmd");
  int key_str_len = qkey.length() + 1;   
  int cmd_str_len = qcmd.length() + 1; 
  char webkey[key_str_len];
  char webcmd[cmd_str_len];
  qkey.toCharArray(webkey, key_str_len); 
  qcmd.toCharArray(webcmd, cmd_str_len);
  if(strcmp(webcmd, "pumpOn") == 0){ 
    pumpOn();
    content = getPumpOnContent();
    server.send(200, "text/html", content);  
  }else if(strcmp(webcmd, "pumpOff")== 0){
    pumpOff();
    content = getPumpOffContent();
    server.send(200, "text/html", content);      
  }else{
    //tft.print("Команда не распознана: "); tft.print(webcmd);
  } 
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void handleAPSetting(){
  String qsid = server.arg("ssid");
  String qpass = server.arg("pass");
  int sid_str_len = qsid.length() + 1; 
  char webssid[sid_str_len];
  qsid.toCharArray(webssid, sid_str_len);
  int pass_str_len = qpass.length() + 1; 
  char webpass[pass_str_len];
  qpass.toCharArray(webpass, pass_str_len);
  if ((qsid.length() > 0) && (qpass.length() >= 8) && (qpass.length() <=15)) {  
    strncpy(wifi_ssid, webssid, 10);
    strncpy(wifi_password, webpass, 15); 
    saveConfig();   
    content = getSavePageContent();
    statusCode = 200;
    server.send(statusCode, "text/html", content);
    delay(1000);
    WiFi.mode(WIFI_OFF);
    ESP.restart();
  } else {
    content = getErrorPageContent();
    statusCode = 404;
    server.send(statusCode, "text/html", content);
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------------



