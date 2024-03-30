String getPageHeader(){
  content = "<!DOCTYPE HTML>\r\n<html>";
  content +="<head><meta charset=\"utf-8\"><title>Управление поливом</title></head>\r\n";
  content += "<style> body{ font-family: 'Arial'; width:400px; background-color: #dddddd;  margin: 0 auto; } table {  font-size: 14px; }</style>\r\n";
  content += "<body>\r\n";
  return content;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
String getRootPageContent(){
  content = getPageHeader();
  content += "\t <table border=0>\r\n";
  content += "\t\t <tr><td colspan='2' align=\"center\"><h2>Система управления поливом</h2></td></tr>\r\n";
  content += "\t\t <tr><td colspan='2'><h3>Доступные сети</h3></td></tr'>\r\n";
  content += "\t\t <tr><td colspan='2'>\r\n\t\t";
  content += st;
  content += "\t\t </td></tr'>\r\n"; 
  content += "\t\t <tr><td colspan='2' style=\"color: red;\"><p>Для поключения устройства в вашей локальной сети введите имя точки доступа и пароль</p></td></tr>\r\n";
  content += "\t\t <tr><td><form method='get' action='setting'>Имя точки доступа</td><td><input name='ssid' type='text'></td></tr>\r\n";
  content += "\t\t <tr><td>Пароль:</td><td><input name='pass' type='text'></td></tr>\r\n";
  content +="\t\t  <tr><td colspan='2' align=\"center\">\r\n";
  content += "\t\t <input type='submit' value='Сохранить'></form>\r\n";
  content +="\t </table>\r\n";
  content +="</body>\r\n";     
  return content;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
String getSavePageContent(){
  content = getPageHeader();
  content += "\t <table border=0>\r\n";
  content += "\t\t <tr><td align=\"center\"><h2>Настройки сохранены. <br/>Устройство подключено к новой точке доступа.<br/>IP адрес Web сервера на дисплее.</h2></td></tr>\r\n";
  content +="\t </table>\r\n";
  content +="</body>\r\n";     
  return content;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
String getErrorPageContent(){
  content = getPageHeader();
  content += "\t <table border=0>\r\n";
  content += "\t\t <tr><td align=\"center\" style=\"color: red;\"><h2>Невозможно сохранить конфигурацию! Длинна пароля не может быть больше 15 символов!</h2></td></tr>\r\n";
  content +="\t </table>\r\n";
  content +="</body>\r\n";     
  return content;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
String getWebRootContent(){
  content = getPageHeader();
  content += "\t <table border=0>\r\n";
  content += "\t\t <tr><td align=\"center\" style=\"color: red;\"><h2>Привет</h2></td></tr>\r\n";

  content += "\t\t <tr><td align=\"center\" style=\"color: red;\"><a href=\"/pump?key=";
  content += PUMPKEY;
  content += "&cmd=pumpOff\">Выключить полив</a></td></tr>\r\n";

  content += "\t\t <tr><td align=\"center\" style=\"color: red;\"><a href=\"/pump?key=";
  content += PUMPKEY;
  content += "&cmd=pumpOn\">Включить полив</a></td></tr>\r\n";
  
  content +="\t </table>\r\n";
  content +="</body>\r\n";     
  return content;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
String getPumpOnContent(){
  content = getPageHeader();
  content += "\t <table border=0>\r\n";
  content += "\t\t <tr><td align=\"center\" style=\"color: red;\"><h2>Полив включен</h2></td></tr>\r\n";
  content += "\t\t <tr><td align=\"center\" style=\"color: red;\"><a href=\"/pump?key=";
  content += PUMPKEY;
  content += "&cmd=pumpOff\">Выключить полив</a></td></tr>\r\n";
  content +="\t </table>\r\n";
  content +="</body>\r\n";     
  return content;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
String getPumpOffContent(){
  content = getPageHeader();
  content += "\t <table border=0>\r\n";
  content += "\t\t <tr><td align=\"center\" style=\"color: red;\"><h2>Полив выключен</h2></td></tr>\r\n";
  content += "\t\t <tr><td align=\"center\" style=\"color: red;\"><a href=\"/pump?key=";
  content += PUMPKEY;
  content += "&cmd=pumpOn\">Включить полив</a></td></tr>\r\n";
  content +="\t </table>\r\n";
  content +="</body>\r\n";     
  return content;
}
//-------------------------------------------------------------------------------------------------------------------------------------------





