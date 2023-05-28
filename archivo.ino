#include <WiFi.h>
#include <ESP32Servo.h>
#include <WebServer.h>
#include <HTTPClient.h>



//------------------Servidor Web en puerto 80---------------------

WebServer server(80);

//---------------------Credenciales de WiFi-----------------------

//const char* ssid     = "ENCANTO";
//const char* password = "419183001968";
const char* ssid     = "POCO X3";
const char* password = "1010118570";
//const char* ssid     = "Shigaraki’s phone";
//const char* password = "jhojan4523";
//const char* ssid     = "Galaxy A5226D4";
//const char* password = "ccsn4230";

//const char* botToken = "5981066116:AAEHDexX7G--KbsxQWVL9DT9HkIjR7252rA";

//---------------------VARIABLES GLOBALES-------------------------
int contconexion = 0;

String header; // Variable para guardar el HTTP request

const int pirPin = 32;     // Pin del sensor PIR
const int servoPin = 33;   // Pin de control del servo
const int buzzerPin = 26; // Pin del buzzer
const int luz = 27;


//WiFiClientSecure client;
//UniversalTelegramBot bot(botToken, client);


Servo myservo;    // Objeto del servo

bool pirState = false;
bool previousPirState = false;
bool alarmActive = false;

// Configuración de Twilio esteban
String accountSid = "AC7c642bed6dc0b9d662f1cdc49b6b4aa9";
String authToken = "3c56e5cdb3e2dbf5b33e974a4f14493b";
String twilioPhoneNumber = "+13158715570";
String recipientPhoneNumber = "+573128289910";

// Configuración de Twilio jhojan
//String accountSid = "AC8909bae95315eeabb61a2badd4229b2a";
//String authToken = "02976c5e846b9a0c7a2364d207234e63";
//String twilioPhoneNumber = "+13157108405";
//String recipientPhoneNumber = "+573128289910";

//----------------------FUNCIONES-----------------------------------

void handleEncender() {
  // Código para encender el LED
  digitalWrite(luz, LOW);
  tone(buzzerPin, 3000);
  myservo.write(359);
  
  //server.sendHeader("Access-Control-Allow-Origin", "*");
  //server.sendHeader("Access-Control-Allow-Methods", "GET, POST", "OPTIONS");
  // server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  //  server.sendHeader("Access-Control-Allow-Headers", "*");
  server.send(200, "text/plain", "LED encendido");
}

void handleApagar(){
  digitalWrite(luz, HIGH);
  myservo.write(0);
  noTone(buzzerPin);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST");
  // server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
      server.sendHeader("Access-Control-Allow-Headers", "*");
  server.send(200, "text/plain", "LED apagado");
}

void handleServo(){
  myservo.write(359);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST");
  // server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
      server.sendHeader("Access-Control-Allow-Headers", "*");

  server.send(200, "text/plain", "LSERVO encendido");
}

void handleServoOff(){
  myservo.write(0);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST");
  // server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
      server.sendHeader("Access-Control-Allow-Headers", "*");

  server.send(200, "text/plain", "LSERVO encendido");
}

void handleAlarma(){
  tone(buzzerPin, 3000);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST");
  // server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
      server.sendHeader("Access-Control-Allow-Headers", "*");

  server.send(200, "text/plain", "LSERVO encendido");
}

void handleAlarmaOff(){
  noTone(buzzerPin);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST");
  // server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
      server.sendHeader("Access-Control-Allow-Headers", "*");

  server.send(200, "text/plain", "LSERVO encendido");
}

void handleLed(){
  digitalWrite(luz, LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST");
  // server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
      server.sendHeader("Access-Control-Allow-Headers", "*");

  server.send(200, "text/plain", "LSERVO encendido");
}

void handleLedOff(){
  digitalWrite(luz, HIGH);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST");
  // server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
      server.sendHeader("Access-Control-Allow-Headers", "*");

  server.send(200, "text/plain", "LSERVO encendido");
}

void sendSMS(String message) {
  String url = "https://api.twilio.com/2010-04-01/Accounts/" + accountSid + "/Messages.json";

  HTTPClient http;
  http.begin(url);
  http.setAuthorization(accountSid.c_str(), authToken.c_str());
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String body = "From=" + twilioPhoneNumber + "&To=" + recipientPhoneNumber + "&Body=" + message;

  int httpResponseCode = http.POST(body);

  if (httpResponseCode == HTTP_CODE_CREATED) {
    Serial.println("Mensaje enviado correctamente");
  } else {
    Serial.print("Error al enviar el mensaje. Código de respuesta HTTP: ");
    Serial.println(httpResponseCode);
  }

  
}

//---------------------------SETUP--------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println("");
  

  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(luz, OUTPUT);
  myservo.attach(servoPin);

  // Conexión WIFI
  WiFi.begin(ssid, password);
  // Cuenta hasta 50 si no se puede conectar lo cancela
  while (WiFi.status() != WL_CONNECTED && contconexion < 50) {
    ++contconexion;
    delay(500);
    Serial.print(".");
  }
  if (contconexion < 50) {
    Serial.println("");
    Serial.println("WiFi conectado");
    Serial.println("La direccion IP para el WebServer es:");
    Serial.println(WiFi.localIP());
    server.on("/encender", handleEncender);
    server.on("/apagar", handleApagar);
    server.on("/servo", handleServo);
    server.on("/servoOff", handleServoOff);
    server.on("/alarma", handleAlarma);
    server.on("/alarmaOff", handleAlarmaOff);
    server.on("/led", handleLed);
    server.on("/ledOff", handleLedOff);
    server.begin(); // iniciamos el servidor
    
  } else {
    Serial.println("");
    Serial.println("Error de conexion");
  }



  
}

//----------------------------LOOP----------------------------------

void loop() {
  server.handleClient();

  pirState = digitalRead(pirPin);

  // Detectar movimiento en el sensor PIR
  if (pirState != previousPirState) {
    if (pirState == HIGH) {
      Serial.println("Movement detected");

      if (!alarmActive) {
        tone(buzzerPin, 3000);
      }
      digitalWrite(luz, LOW);

      String message = "Se ha detectado movimiento en el sensor PIR, por favor ingrese al siguiente enlace para controlar los dispositivos: 'http://jncllc.com/dist/'", h;
      sendSMS(message);
   
    } else {
      Serial.println("No movement");
      if (!alarmActive) {
        noTone(buzzerPin);
      }
      digitalWrite(luz, HIGH);
    } // fin if pirState
    previousPirState = pirState;
  } // fin if pirState
} // fin loop
