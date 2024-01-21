#include "wifiEsp.h"

WiFiServer server(80);

void WifiEsp::wifi_Innit() 
{
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  server.begin();

  Serial.println("connection made");
}

int WifiEsp::loopWifi()
{
  WiFiClient client = server.available();
  int returnValue = IDLE;

  if (!client) 
    return IDLE;

  String currentLine = "";

  while (client.connected()) 
  {
    if (!client.available()) 
      continue;

    char c = client.read();
    Serial.write(c);
    if (c == '\n') 
    {
      if (currentLine.length() == 0) 
      {
        printBaseHtml(client);
        break;
      }

      currentLine = "";
    }
    else if (c != '\r') 
    {
      currentLine += c;
    }

    if (currentLine.endsWith("GET /ON")) 
    {
      Serial.print("ON");
      returnValue = START;
      break;
    } 

    if (currentLine.endsWith("GET /STOP")) 
    {
      Serial.print("STOP");
      returnValue = STOP;
      break;
    }
  }

  client.stop();
  return returnValue;
}

int WifiEsp::loopWifi(int ultrasoonSensor, bool REED, int* irArray) 
{
  WiFiClient client = server.available();
  int returnValue = IDLE;

  if (!client) 
    return IDLE;

  String currentLine = "";

  while (client.connected()) 
  {
    if (!client.available()) 
      continue;

    char c = client.read();
    Serial.write(c);
    if (c == '\n') 
    {
      if (currentLine.length() == 0) 
      {
        printBaseHtml(client);

        client.print(printIR_Data(irArray));

        client.print("Ultrasonische Afstands Sensor: ");
        client.print(ultrasoonSensor + "CM");

        client.print("REED Sensor: ");
        String reedMessage = (REED) ? "true" : "false";
        client.println(reedMessage);
        
        break;
      } 
      
      currentLine = "";
    } 
    else if (c != '\r') 
    {
      currentLine += c;
    }

    if (currentLine.endsWith("GET /ON")) 
    {
      Serial.print("ON");
      returnValue = START;
      break;
    } 
    if (currentLine.endsWith("GET /STOP")) 
    {
      Serial.print("STOP");
      returnValue = STOP;
      break;
    }
  }

  client.stop();
  return returnValue;
}

void WifiEsp::printBaseHtml(WiFiClient &client)
{
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  client.print("<head><meta http-equiv=\"refresh\" content=\"1\"></head>");
  client.print("Click <a href=\"/ON\">here</a> to turn ON the ACM.<br>");
  client.print("Click <a href=\"/STOP\">here</a> to turn OFF the ACM.<br>");
}

String WifiEsp::printIR_Data(int* irArray)
{
  String message = "";
  uint8_t i = 0;

  while(irArray[i] != -69)
  {
    message += "Infrarood Sensor " + String(i+1) + ": ";
    message += irArray[i];
    message += "<br>";
  
    i++;
  }

  return message;
}