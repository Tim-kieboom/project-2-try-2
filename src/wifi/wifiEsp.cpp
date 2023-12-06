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

bool WifiEsp::loopWifi(uint8_t ir1, uint8_t ir2, int ultrasoonSensor) 
{
  int returnValue = 0;
  WiFiClient client = server.available();

  if (client) 
  {
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
            client.print("Infrarood Sensor 1: ");
            client.print(ir1);
            client.print("<br>");
            client.print("InfraRood 2: ");
            client.print(ir2);
            client.print("<br>");
            client.print("Ultrasonische Afstands Sensor: ");
            client.print(ultrasoonSensor);
            client.print("CM");
            client.println();
            
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
  }
  return returnValue;
}