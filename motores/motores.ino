int IN3 = 9; 
int IN4 = 8;
int ENA = 6;
int IN1 = 10; 
int IN2 = 7;
int ENB = 11;

void setup()
{
  pinMode (IN4, OUTPUT);    // Input4 conectada al pin 4 
  pinMode (IN3, OUTPUT);    // Input3 conectada al pin 5
  pinMode (ENA, OUTPUT);    // ENABLE 

  pinMode (IN1, OUTPUT);    // Input4 conectada al pin 4 
  pinMode (IN2, OUTPUT);    // Input3 conectada al pin 5
  pinMode (ENB, OUTPUT);    // ENABLE   
    
  analogWrite(ENA, 80);
  analogWrite(ENB, 80);
}
void loop()
{
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  // Motor gira en un sentido
  digitalWrite (IN4, HIGH);
  digitalWrite (IN3, LOW);
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  delay(4000);
digitalWrite (IN4, HIGH);
  digitalWrite (IN3, LOW);
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  delay(4000);  
  digitalWrite (IN4, LOW);
  digitalWrite (IN3, HIGH);
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  delay(4000);
  // Motor no gira
  digitalWrite (IN4, LOW);
  digitalWrite (IN3, HIGH);
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH); 
  delay(4000);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(4000);
}