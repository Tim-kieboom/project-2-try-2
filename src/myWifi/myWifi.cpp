#include "myWifi.h"
#include "IR_sensor/IR_sensor.h"

static const char* password = "bombaBomba";
static const char* ssid = "bomba"; 

static AsyncWebServer server(80);
static JsonDocument sensorJson = JsonDocument();
static IPAddress IP;

//if client on webbrowser presses the on button state = true;
static bool state = false;

bool getWifiState()
{
  return state;
}

void setSensorData_In_Json(String carState, int ultrasoon, int* IRs, int REED)
{

  const String IR_Low = "not detected"; 
  const String IR_High = "detected";
  const String IRnotSet = "unknown";

  sensorJson["carState"]  = carState;

  sensorJson["ultrasoon"] = String(ultrasoon);
  sensorJson["REED"]      = String(REED);

  //if IRs empty
  if(IRs[0] == SENTINEL_VALUE) 
  {
    sensorJson["IR1"] = IRnotSet;
    sensorJson["IR2"] = IRnotSet;
    sensorJson["IR3"] = IRnotSet;
    sensorJson["IR4"] = IRnotSet;
    return;
  }

  sensorJson["IR1"] = (IRs[0] == 1) ? IR_High : IR_Low;
  sensorJson["IR2"] = (IRs[1] == 1) ? IR_High : IR_Low;
  sensorJson["IR3"] = (IRs[2] == 1) ? IR_High : IR_Low;
  sensorJson["IR4"] = (IRs[3] == 1) ? IR_High : IR_Low;
}

String getJson()
{
  String jsonString = "";
  serializeJson(sensorJson, jsonString);
  return jsonString;
}

void serverController()
{
  //starts html
  server.on("/", HTTP_GET, 
    [](AsyncWebServerRequest *request)
    {
      request->send(SPIFFS, /*routingPath=*/"/test.html", /*contextType=*/String(), /*download=*/false);
    });

  //starts css
  server.on("/style.css", HTTP_GET, 
    [](AsyncWebServerRequest *request)
    {
      request->send(SPIFFS, /*routingPath=*/"/style.css", /*contextType=*/"text/css");
    });

  //if button pressed toggle "bool state" and return the current state
  server.on("/button", HTTP_GET,
    [](AsyncWebServerRequest *request)
    {
      state = !state; 
      request->send(200,/*contextType=*/"application/json" ,/*json=*/"{\"buttonState\": " + String((int)state) + "}");
    });

  //sends the sensorvalues to the webpage
  server.on("/update", HTTP_GET,
    [](AsyncWebServerRequest *request)
    {
      request->send(200,/*contextType=*/"application/json" ,/*json=*/getJson());
    });
}

void wifiInit()
{
  if(!SPIFFS.begin(true))
  {
    Serial.println("SPIFFS coundn't start");
    exit(1);
  }

  WiFi.softAP(ssid, password);
  IP = WiFi.softAPIP();

  Serial.print("ip address: ");
  Serial.println(IP);

  serverController();

  server.begin();
}

void startWifi()
{
  wifiInit();
  serverController();
}