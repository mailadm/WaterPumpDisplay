//------------------------------------------------------------------------------------------------------------
void callback(char* topic, byte* payload, unsigned int length) {
  String data_pay;
  for (int i = 0; i < length; i++) {
    data_pay += String((char)payload[i]);
  }
  //Serial.println(data_pay); 
  
  if( String(topic) == relay_topic ){
        if(data_pay == "ON" || data_pay == "1")  pumpOn();
        if(data_pay == "OFF" || data_pay == "0") pumpOff();
  }
}
//------------------------------------------------------------------------------------------------------------
void reconnect() {
  while (!client.connected()) {
    //Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266-" + WiFi.macAddress();
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password) ) {
      //Serial.println("connected");
      client.subscribe( (relay_topic + "/#").c_str() );
    } else {
      //Serial.print("failed, rc=");
      //Serial.print(client.state());
      //Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
//------------------------------------------------------------------------------------------------------------

