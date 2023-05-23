#include "ESP8266WiFi.h"
 
const char* ssid = "iPhone";
const char* password =  "josoc2004";
 
WiFiServer wifiServer(80);


//VARIABLES
const int trigPin = 16;  // Pin del trigger del sensor ultrasónico
const int echoPin = 5;  // Pin del echo del sensor ultrasónico
const int motor1Pin1 = 13;  // Pin 1 del motor 1
const int motor1Pin2 = 12;   // Pin 2 del motor 1
const int motor2Pin1 = 0;   // Pin 1 del motor 2
const int motor2Pin2 = 3;   // Pin 2 del motor 2
const int speedPin1 = 14;     // Pin de velocidad del motor 1
const int speedPin2 = 2;    // Pin de velocidad del motor 2

//PWM motores
const int velocidad_I = 160;
const int velocidad_D = 140;

//variables sensor distancia
long duration, distance;

unsigned long tiempoInicio;


// Estados para el manejo de cada motor
typedef enum {
	ADELANTE, // moverse adelate 0
	ATRAS, // moverse atras  1
	IZQUIERDA, // giro a la izquierda 2
	DERECHA,// giro a la derecha 3
	PARAR // motores deshabilitados 4
} DIRECTION;
 DIRECTION direction = PARAR; // inicializar variable tipo: DIRECTION

//FUNCIONES
void medir_distancia() {
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  if(30 >= distance){
    parar();
    delay(500);
    atras();
    delay(500);
    direction=PARAR;
  }
}


void parar() {
  analogWrite(speedPin1, 0); 
  analogWrite(speedPin2, 0);
}

void atras() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(speedPin1, velocidad_I);
  analogWrite(speedPin2, velocidad_D);
}

void adelante() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  analogWrite(speedPin1, velocidad_I);
  analogWrite(speedPin2, velocidad_D);
}

void izquierda() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  analogWrite(speedPin1, velocidad_I);
  analogWrite(speedPin2, velocidad_D);
}

void derecha() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(speedPin1, velocidad_I);
  analogWrite(speedPin2, velocidad_D);
}

void setup() {


  Serial.begin(115200);
  delay(200);  // Inicializar comunicación serial
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(speedPin1, OUTPUT);
  pinMode(speedPin2, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output

  // Set up WiFi

  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
 
  Serial.print("Connected to WiFi. IP:");
  Serial.println(WiFi.localIP());
 
  wifiServer.begin();
}

void loop() {

  WiFiClient client = wifiServer.available();
 
  if (client) {
 
    while (client.connected()) {
     // Serial.println("Conneted");
      String messages = "";
      while (client.available()>0) {
        char c = client.read();
        //Serial.write(c);
        messages.concat(c);
      }
      
      if(messages!= "") {
        Serial.println(messages);
      }
      //Codigo MOtores 

       medir_distancia();

      if(messages == "1.0") {
        direction = ADELANTE;
      }
      if(messages == "2.0") {
        direction = ATRAS;
      }
      if(messages == "3.0") {
        direction = IZQUIERDA;
      }
      if(messages == "4.0") {
        direction = DERECHA;
      }
      if(messages == "5.0") {
        direction = PARAR;
      } 

      switch(direction){
        case ADELANTE:
          adelante();                   
          break;
        case ATRAS:
          atras();
          break;
        case IZQUIERDA:
          izquierda();
          delay(150);
          direction=ADELANTE;
          break;
        case DERECHA:
          derecha();
          delay(150);
          direction=ADELANTE;
          break;
        case PARAR:
          parar();
          break;
  
      }




      delay(10);
    }
  }
  client.stop();
 // Serial.println("Client disconnected");

 
}//loop
