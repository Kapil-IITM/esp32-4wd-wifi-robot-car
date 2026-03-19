#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Wifi-Name"; 
const char* password = "Password"; 

WebServer server(80);

// Motor Pins
int ENA = 25;
int IN1 = 26;
int IN2 = 27;
int IN3 = 14;
int IN4 = 12;
int ENB = 33;

int speedValue = 150;

// MOTOR CONTROL
void stopRobot(){
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,LOW);
}

void forward(){
 digitalWrite(IN1,HIGH);
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,LOW);
}

void backward(){
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,HIGH);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,HIGH);
}

void left(){
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,HIGH);
 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,LOW);
}

void right(){
 digitalWrite(IN1,HIGH);
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,HIGH);
}

// SIMPLE WEB PAGE
String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<title>PHOTON - STAGE 1</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body{
 text-align:center;
 font-family:Arial;
 background:#111;
 color:white;
}
button{
 width:120px;
 height:60px;
 font-size:18px;
 margin:10px;
 border-radius:10px;
}
</style>
</head>

<body>

<h1>PHOTON - STAGE 1</h1>

<button onclick="fetch('/f')">Forward</button><br>

<button onclick="fetch('/l')">Left</button>
<button onclick="fetch('/s')">Stop</button>
<button onclick="fetch('/r')">Right</button><br>

<button onclick="fetch('/b')">Backward</button>

<br><br>

<h3>Speed</h3>
<input type="range" min="0" max="255" value="150"
onchange="fetch('/speed?value='+this.value)">

<br><br>
<h3>Kapil</h3>

</body>
</html>
)rawliteral";

void handleRoot(){
 server.send(200,"text/html",page);
}

void setup(){

 Serial.begin(115200);

 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);

 // PWM (NEW ESP32 METHOD)
 ledcAttach(ENA,1000,8);
 ledcAttach(ENB,1000,8);

 ledcWrite(ENA,speedValue);
 ledcWrite(ENB,speedValue);

 // WIFI
 WiFi.begin(ssid,password);

 while(WiFi.status()!=WL_CONNECTED){
  delay(500);
  Serial.print(".");
 }

 Serial.println("");
 Serial.print("IP: ");
 Serial.println(WiFi.localIP());

 // ROUTES
 server.on("/",handleRoot);

 server.on("/f",[](){ forward(); server.send(200,"text/plain","OK"); });
 server.on("/b",[](){ backward(); server.send(200,"text/plain","OK"); });
 server.on("/l",[](){ left(); server.send(200,"text/plain","OK"); });
 server.on("/r",[](){ right(); server.send(200,"text/plain","OK"); });
 server.on("/s",[](){ stopRobot(); server.send(200,"text/plain","OK"); });

 server.on("/speed",[](){
  speedValue = server.arg("value").toInt();
  ledcWrite(ENA,speedValue);
  ledcWrite(ENB,speedValue);
  server.send(200,"text/plain","OK");
 });

 server.begin();
}

void loop(){
 server.handleClient();
}