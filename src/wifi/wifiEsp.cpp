#include "wifiEsp.h"

WiFiServer server(80);

void WifiEsp::wifi_Innit() 
{
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  server.begin();

  Serial.println("connection made");
}

bool WifiEsp::loopWifi()
{
  int returnValue = 0;
  WiFiClient client = server.available();

  if (!client) 
    return returnValue;

  
  String currentLine = "";

  while (client.connected()) 
  {
    if (client.available()) 
    {
      char c = client.read();
      Serial.write(c);
      if (c == '\n') 
      {
        if (currentLine.length() == 0) 
        {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          client.print("<head><meta http-equiv=\"refresh\" content=\"1\"></head>");
          client.print("Click <a href=\"/ON\">here</a> to turn ON the ACM.<br>");
          client.print("Click <a href=\"/STOP\">here</a> to turn OFF the ACM.<br>");
        }
        else 
        {
          currentLine = "";
        }
      }
      else if (c != '\r') 
      {
        currentLine += c;
      }
    }

    if (currentLine.endsWith("GET /ON")) 
    {
      Serial.print("ON");
      returnValue = 1;
    } 
    if (currentLine.endsWith("GET /STOP")) 
    {
      Serial.print("STOP");
      returnValue = 2;
    }
  }

  client.stop();

  return returnValue;

}

bool WifiEsp::loopWifi(int ultrasoonSensor, bool REED, int* irArray) 
{
  int returnValue = 0;
  WiFiClient client = server.available();

  if (!client) 
    return returnValue;

  Serial.println("New Client.");
  String currentLine = "";

  while (client.connected()) 
  {
    if (client.available()) 
    {
      char c = client.read();
      Serial.write(c);
      if (c == '\n') 
      {
        if (currentLine.length() == 0) 
        {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          client.print("<head><meta http-equiv=\"refresh\" content=\"1\"></head>");
          client.print("Click <a href=\"/ON\">here</a> to turn ON the ACM.<br>");
          client.print("Click <a href=\"/STOP\">here</a> to turn OFF the ACM.<br>");
          client.print(printIR_Data(irArray));
          client.print("Ultrasonische Afstands Sensor: ");
          client.print(ultrasoonSensor + "CM");
          client.print("REED Sensor: ");
          
          String reedMessage = (REED) ? "true" : "false";
          client.println(reedMessage);
          
          break;
        } 
        else 
        {
          currentLine = "";
        }
      } 
      else if (c != '\r') 
      {
        currentLine += c;
      }
    }

    if (currentLine.endsWith("GET /ON")) 
    {
      Serial.print("ON");
      returnValue = 1;
    } 
    if (currentLine.endsWith("GET /STOP")) 
    {
      Serial.print("STOP");
      returnValue = 2;
    }
  }
  client.stop();
  
  return returnValue;
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