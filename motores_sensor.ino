const int trigPin = 2;  // Pin del trigger del sensor ultrasónico
const int echoPin = 3;  // Pin del echo del sensor ultrasónico
const int motor1Pin1 = 10;  // Pin 1 del motor 1
const int motor1Pin2 = 7;   // Pin 2 del motor 1
const int motor2Pin1 = 9;   // Pin 1 del motor 2
const int motor2Pin2 = 8;   // Pin 2 del motor 2
const int speedPin1 = 6;     // Pin de velocidad del motor 1
const int speedPin2 = 11;    // Pin de velocidad del motor 2

void setup() {
  Serial.begin(9600);  // Inicializar comunicación serial
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(speedPin1, OUTPUT);
  pinMode(speedPin2, OUTPUT);
}

void loop() {
  long duration, distance;
  bool s ;
  s = false;
  
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

  if (distance <= 20) {
    // Si la distancia es menor o igual a 20 cm, el robot retrocede
    analogWrite(speedPin1, 0);  // Velocidad máxima hacia atrás para el motor 1
    analogWrite(speedPin2, 0);
    delay(1000);
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    analogWrite(speedPin1, 125);  // Velocidad máxima hacia atrás para el motor 1
    analogWrite(speedPin2, 125);  // Velocidad máxima hacia atrás para el motor 2
    s=true;
    delay(2000);
  } else {
    
    // Si la distancia es mayor a 20 cm, el robot avanza hacia adelante
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
    analogWrite(speedPin1, 125);  // Velocidad máxima hacia adelante para el motor 1
    analogWrite(speedPin2, 125);  // Velocidad máxima hacia adelante para el motor 2
    if(s==true){
        analogWrite(speedPin1, 0);  // Velocidad máxima hacia atrás para el motor 1
        analogWrite(speedPin2, 0);
        delay(1000);      
    }
  }
}
