#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include "CarData.h"
#include "Timer/Timer.h"
#include "CarLogic/CarLogic.h"

const char *ssid = "bomba";
const char *password = "bombaBomba";

WiFiServer server(80);
int carState;
bool start;
CarData* carData;
String header;

String outputState = "off";

void init()
{
  Serial.begin(115200);
  Serial.println("starting");

<<<<<<< Updated upstream
  wifi->wifi_Innit();
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
  server.begin();
>>>>>>> Stashed changes

  ultrasoonStartup();
  carLogic_init();
  motorInnit();
  IR_Innit();
}

bool printHTML(WiFiClient &client){
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();
  // turns the GPIOs on and off
  if (header.indexOf("GET /12/on") >= 0) {
    Serial.println("GPIO 12 on");
    outputState = "on";
  } else if (header.indexOf("GET /12/off") >= 0) {
    Serial.println("GPIO 12 off");
    outputState = "off";
  }
  // Display the HTML web page
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  // CSS to style the on/off buttons
  // Feel free to change the background-color and font-size attributes to fit your preferences
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: #555555;}</style></head>");
  // Web Page Heading
  client.println("<body><h1>ESP32 Web Server</h1>");
  // Display current state, and ON/OFF buttons for GPIO 12  
  client.println("<p> ACM power: " + outputState + "</p>");
  // If the output12State is off, it displays the ON button      
  if (outputState=="on") {
    client.println("<p><a href=\"/12/off\"><button class=\"button\">ON</button></a></p>");
  } else {
    client.println("<p><a href=\"/12/on\"><button class=\"button button2\">OFF</button></a></p>");
  }
  client.println("</body></html>");
  // The HTTP response ends with another blank line
  client.println();
  // Break out of the while loop
  return 1;
}

bool printHTML(int ultrasoonSensor, bool REED, int* irArray, WiFiClient &client){
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();
  // turns the GPIOs on and off
  if (header.indexOf("GET /12/on") >= 0) {
    Serial.println("GPIO 12 on");
    outputState = "on";
  } else if (header.indexOf("GET /12/off") >= 0) {
    Serial.println("GPIO 12 off");
    outputState = "off";
  }
  // Display the HTML web page
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  // CSS to style the on/off buttons
  // Feel free to change the background-color and font-size attributes to fit your preferences
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: #555555;}</style></head>");
  // Web Page Heading
  client.println("<body><h1>ESP32 Web Server</h1>");
  // Display current state, and ON/OFF buttons for GPIO 12  
  client.println("<p> ACM power: " + outputState + "</p>");
  // If the output12State is off, it displays the ON button      
  if (outputState=="on") {
    client.println("<p><a href=\"/12/off\"><button class=\"button\">ON</button></a></p>");
  } else {
    client.println("<p><a href=\"/12/on\"><button class=\"button button2\">OFF</button></a></p>");
  }



  client.println("</body></html>");
  // The HTTP response ends with another blank line
  client.println();
  // Break out of the while loop
  return 1;
}

bool sendData(WiFiClient &client)
{
  int* irArray = carData->irArray;

  if(irArray[0] == SENTINEL_VALUE) //if irArray is empty(so start hasn't been pressed yet)
    return printHTML(client);

  return printHTML(carData->ulstrasoonData, carData->REED, irArray, client);
}

void setup() 
{
  carData = new CarData();
  carState = driveForward;
  init();

  start = false;
}


void loop(){
  if(carState == end)
    return;

  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {  // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            sendData(client);
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  if (outputState == "on"){
    printState(carState);
    carLogic(/*out*/carData, /*out*/carState);
  }
}
