
//VARIABLES
const int trigPin = 2;  // Pin del trigger del sensor ultrasónico
const int echoPin = 3;  // Pin del echo del sensor ultrasónico
const int motor1Pin1 = 10;  // Pin 1 del motor 1
const int motor1Pin2 = 7;   // Pin 2 del motor 1
const int motor2Pin1 = 9;   // Pin 1 del motor 2
const int motor2Pin2 = 8;   // Pin 2 del motor 2
const int speedPin1 = 6;     // Pin de velocidad del motor 1
const int speedPin2 = 11;    // Pin de velocidad del motor 2

//PWM motores
const int velocidad_1 = 100;
const int velocidad_2 = 125;

//variables sensor distancia
long duration, distance;


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
  analogWrite(speedPin1, velocidad_1);
  analogWrite(speedPin2, velocidad_2);
}

void adelante() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  analogWrite(speedPin1, velocidad_1);
  analogWrite(speedPin2, velocidad_2);
}

void izquierda() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  analogWrite(speedPin1, velocidad_1);
  analogWrite(speedPin2, velocidad_2);
}

void derecha() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(speedPin1, velocidad_1);
  analogWrite(speedPin2, velocidad_2);
}

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

  medir_distancia();

  switch(direction){
    case ADELANTE:
      adelante();
    break;

    case ATRAS:
      atras();
    break;

    case IZQUIERDA:
      izquierda();
    break;

    case DERECHA:
      derecha();
    break;

    case PARAR:
      parar();
    break;
  
  }
}//loop
