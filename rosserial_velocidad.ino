/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>

ros::NodeHandle  nh;
int IN3 = 9; 
int IN4 = 8;
int ENA = 6;
int IN1 = 10; 
int IN2 = 7;
int ENB = 11;
float  movement = 0;
float velocidad = 0;


void messageCb( const std_msgs::Float32& velocidad_msg){
  velocidad= velocidad_msg.data;

}

ros::Subscriber<std_msgs::Float32> sub("velocidad_motores", &messageCb );

void setup()
{ 

  nh.initNode();
  nh.subscribe(sub);

  pinMode (IN4, OUTPUT);    // Input4 conectada al pin 4 
  pinMode (IN3, OUTPUT);    // Input3 conectada al pin 5
  pinMode (ENA, OUTPUT);    // ENABLE 

  pinMode (IN1, OUTPUT);    // Input4 conectada al pin 4 
  pinMode (IN2, OUTPUT);    // Input3 conectada al pin 5
  pinMode (ENB, OUTPUT);    // ENABLE   
}

void loop()
{  
  nh.spinOnce();
  delay(1);

  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  // Motor gira en un sentido
  digitalWrite (IN4, HIGH);
  digitalWrite (IN3, LOW);
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
}

