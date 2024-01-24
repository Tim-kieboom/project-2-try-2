#include "wifiEsp.h"

WiFiServer server1(80);

void WifiEsp::wifi_Innit() 
{
<<<<<<< Updated upstream
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  server.begin();

  Serial.println("connection made");
=======
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server1.begin();
  delay(1000);
>>>>>>> Stashed changes
}

int WifiEsp::loopWifi()
{
  WiFiClient client = server.available();
  int returnValue = IDLE;
<<<<<<< Updated upstream

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
=======
  String currentLine = "";                // make a String to hold incoming data from the client
    if (client.available()) {             // if there's bytes to read from the client,
      char c = client.read();             // read a byte, then
      Serial.write(c);                    // print it out the serial monitor
      header += c;
      if (c == '\n') {                    // if the byte is a newline character
        // if the current line is blank, you got two newline characters in a row.
        // that's the end of the client HTTP request, so send a response:
        if (currentLine.length() == 0) {
          printBaseHtml();
        } else { // if you got a newline, then clear currentLine
          currentLine = "";
        }
      } else if (c != '\r') {  // if you got anything else but a carriage return character,
        currentLine += c;      // add it to the end of the currentLine
      }
    }
>>>>>>> Stashed changes
  return returnValue;
}

int WifiEsp::loopWifi(int ultrasoonSensor, bool REED, int* irArray) 
{
  WiFiClient client = server.available();
  int returnValue = IDLE;
<<<<<<< Updated upstream

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
        client.println((REED) ? "true" : "false");
        
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
=======
  String currentLine = "";                // make a String to hold incoming data from the client
    if (client.available()) {             // if there's bytes to read from the client,
      char c = client.read();             // read a byte, then
      Serial.write(c);                    // print it out the serial monitor
      header += c;
      if (c == '\n') {                    // if the byte is a newline character
        // if the current line is blank, you got two newline characters in a row.
        // that's the end of the client HTTP request, so send a response:
        if (currentLine.length() == 0) {
          printBaseHtml();
        } else { // if you got a newline, then clear currentLine
          currentLine = "";
        }
      } else if (c != '\r') {  // if you got anything else but a carriage return character,
        currentLine += c;      // add it to the end of the currentLine
      }
    }
>>>>>>> Stashed changes
  return returnValue;
}

bool WifiEsp::isConnected(){
  client = server1.available();
  if (client && client.connected()){
    return true;
  }
  return false;
}

void WifiEsp::disconnect(){
  header = "";
  client.stop();
  Serial.println("Client disconnected.");
  Serial.println("");
}

void WifiEsp::printBaseHtml()
{
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
<<<<<<< Updated upstream
  client.println();
  client.print("<head><meta http-equiv=\"refresh\" content=\"1\"></head>");
  client.print("Click <a href=\"/ON\">here</a> to turn ON the ACM.<br>");
  client.print("Click <a href=\"/STOP\">here</a> to turn OFF the ACM.<br>");
=======
  client.println("Connection: close");
  client.println();
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: #555555;}</style></head>");
  client.println("<body><h1>ESP32 Web Server</h1>");
  client.println("<p>GPIO 12 - State " + outputState + "</p>"); 
  if (outputState=="off") {
    client.println("<p><a href=\"/12/on\"><button class=\"button\">ON</button></a></p>");
  } else {
    client.println("<p><a href=\"/12/off\"><button class=\"button button2\">OFF</button></a></p>");
  }
  client.println("</body></html>");
  client.println();
>>>>>>> Stashed changes
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