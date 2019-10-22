#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include <ArduinoJson.h>

ESP8266WebServer server;
uint8_t pin_led = LED_BUILTIN;
char* ssid = "Innovation-Science";
char* password = "Creative=Choice+1!";

//char* ssid = "KHAZANAH";
//char* password = "w1f14khazanah!!";

int leftStop = 66;
int rightStop = 71;
Servo servo_left;
Servo servo_right;
unsigned long lastConnectMillis;
unsigned long connectMillis;

void setup()
{
  servo_left.attach(D0);
  servo_right.attach(D1);
  servo_left.write(leftStop);
  servo_right.write(rightStop);
  
  pinMode(pin_led, OUTPUT);
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  Serial.println("");
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/",[](){server.send(200,"text/plain","Hello World!");});
  server.on("/toggle",toggleLED);
  server.on("/Servo",setServo);
  server.begin();
}

void loop()
{
  server.handleClient();

  lastConnectMillis = millis() - connectMillis;
  
  Serial.println(lastConnectMillis);
  if (lastConnectMillis > 1000)
  {
    servo_left.write(leftStop);
    servo_right.write(rightStop);
  }
}

void toggleLED()
{
  digitalWrite(pin_led,!digitalRead(pin_led));
  server.send(204,"");
}

void setServo()
{  
  connectMillis = millis();

  Serial.println("servo");
  
  String data_string = server.arg("plain");
  StaticJsonDocument<400> jDoc;
  DeserializationError err = deserializeJson(jDoc, data_string);
  JsonObject object = jDoc.as<JsonObject>();
  const char* left = object["left"];
  const char* right = object["right"];
  String Left = left;
  String Right = right;
  servo_left.write(Left.toInt());
  servo_right.write(Right.toInt());
  server.send(204,"");
}
