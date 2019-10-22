/*
Craig Crundwell
Oct 20, 2019
This program is run on the ESP8266 and interfaces with a python client to control the robot
*/

//Libraries
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include <ArduinoJson.h>

//Creates an server object and connets to the wifi
ESP8266WebServer server;
char* ssid = "Innovation-Science";
char* password = "Creative=Choice+1!";

//Sets centre servo values
int leftStop = 66;
int rightStop = 71;

//Creates two servo objects
Servo servo_left;
Servo servo_right;

//These values track the connection frequency
unsigned long lastConnectMillis;
unsigned long connectMillis;

void setup()
{
  //Sets pinouts for left and right servos
  servo_left.attach(D0);
  servo_right.attach(D1);

  //The servos should stay still while the wifi connects
  servo_left.write(leftStop);
  servo_right.write(rightStop);

  //Connects to the wifi
  WiFi.begin(ssid,password);

  //Starts the serial monitor and outputs the connection status
  Serial.begin(115200);
  Serial.println("");
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");

  //This IP address is needed for the python client
  Serial.println(WiFi.localIP());

  //Sends a hello world to the client
  server.on("/",[](){server.send(200,"text/plain","Hello World!");});
  
  //Creates a page to send servo commands to
  server.on("/Servo",setServo);
  server.begin();
}

void loop()
{
  //Checks for input from the client
  server.handleClient();

  //tracks time since last connection
  lastConnectMillis = millis() - connectMillis;

  //Stops motors if connection is lost for over 1 second
  if (lastConnectMillis > 1000)
  {
    servo_left.write(leftStop);
    servo_right.write(rightStop);
  }
}

void setServo()
{  
  //Updates time of last connection
  connectMillis = millis();

  //Reads data from client
  String data_string = server.arg("plain");
  StaticJsonDocument<400> jDoc;
  DeserializationError err = deserializeJson(jDoc, data_string);
  JsonObject object = jDoc.as<JsonObject>();
  const char* left = object["left"];
  const char* right = object["right"];

  //Converts data to strings
  String Left = left;
  String Right = right;

  //Sets servo values
  servo_left.write(Left.toInt());
  servo_right.write(Right.toInt());

  //Sends empty response
  server.send(204,"");
}
