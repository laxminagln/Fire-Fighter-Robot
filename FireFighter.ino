//adding libraries
#include <Servo.h>

//initialising
Servo myservo;
int pos = 0;
int motor_speed = 70;  
boolean fire = false;

//defining pins
#define Front 8		// front sensor
#define Left 9		// left sensor
#define Right 10	// right sensor
#define LM1 2		// left motor
#define LM2 7		// left motor
#define RM1 4		// right motor
#define RM2 12		// right motor
#define pump 6

//setup function
void setup() {
  //defining inputs and outputs
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Front, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);
  analogWrite(3, motor_speed);
  analogWrite(5, motor_speed);
  myservo.attach(11);
  myservo.write(90);
}

//function to fight fire
void fight_fire() {
    delay (500);  
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    digitalWrite(pump, HIGH);
    delay(500);
    for (pos = 50; pos <= 130; pos += 1) {
		myservo.write(pos);
		delay(10);  
	}
	for (pos = 130; pos >= 50; pos -= 1) {
		myservo.write(pos);
		delay(10);
	}
	digitalWrite(pump,LOW);
	myservo.write(90);
	fire=false;
} 

//loop function
void loop() {
	myservo.write(90); 
    if (digitalRead(Left) ==1 && digitalRead(Right)==1 && digitalRead(Front) ==1) {   
		digitalWrite(LM1, HIGH);
		digitalWrite(LM2, HIGH);
		digitalWrite(RM1, HIGH);
		digitalWrite(RM2, HIGH);
    }  
    else if (digitalRead(Front) ==0) {
		digitalWrite(LM1, HIGH);
		digitalWrite(LM2, LOW);
		digitalWrite(RM1, HIGH);
		digitalWrite(RM2, LOW);
		fire = true;
    }   
    else if (digitalRead(Left) ==0) {
		digitalWrite(LM1, HIGH);
		digitalWrite(LM2, LOW);
		digitalWrite(RM1, HIGH);
		digitalWrite(RM2, HIGH);
    }
    else if (digitalRead(Right) ==0) {
		digitalWrite(LM1, HIGH);
		digitalWrite(LM2, HIGH);
		digitalWrite(RM1, HIGH);
		digitalWrite(RM2, LOW);
	  }
	  delay(300);  
    while (fire == true) {
		fight_fire();
    }
}
