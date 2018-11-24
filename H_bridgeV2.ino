// Actuator 1
int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA1 = 6;
int speedPinA2 = 9;                                  // Needs to be a PWM pin to be able to control motor speed

// Actuator 2
int dir1PinB = 4;
int dir2PinB = 5;
int speedPinB1 = 10;
int speedPinB2 = 11;                                // Needs to be a PWM pin to be able to control motor speed

void setup() {                                     
  Serial.begin(9600);                   
                                                   // Define L298N Dual H-Bridge Motor Controller Pins
  pinMode(dir1PinA,OUTPUT);                          
  pinMode(dir2PinA,OUTPUT);
  pinMode(speedPinA1,OUTPUT);
  pinMode(speedPinA2,OUTPUT);
  pinMode(dir1PinB,OUTPUT);
  pinMode(dir2PinB,OUTPUT);
  pinMode(speedPinB1,OUTPUT);
  pinMode(speedPinB2,OUTPUT);
}

void loop() {

  if (Serial.available() > 0) {                    // Initialization of serial communication
    int inByte = Serial.read();
    int speed;

switch (inByte) {

case '1':                                       // Motor 1 Forward
analogWrite(speedPinA1, 255);                   //Sets speed variable via PWM 
analogWrite(speedPinA2, 255);
digitalWrite(dir1PinA, LOW);                    // FORWARD = LOW on pin 1, HIGH on pin 2
digitalWrite(dir2PinA, HIGH);
analogWrite(speedPinB1, 255);
analogWrite(speedPinB2, 255);
digitalWrite(dir1PinB, LOW);                    // FORWARD = LOW on pin 1, HIGH on pin 2
digitalWrite(dir2PinB, HIGH);
Serial.println("Motor 1 Forward");
Serial.println("Motor 2 Forward");              
Serial.println("   ");                        
break;

case '2':                                       // Motor 1 Stop (Freespin)
analogWrite(speedPinA1, 0);                     //Sets speed variable via PWM 
analogWrite(speedPinA2, 0);
digitalWrite(dir1PinA, LOW);                    // STOP = LOW on both pins
digitalWrite(dir2PinA, LOW);
analogWrite(speedPinB1, 0);
analogWrite(speedPinB2, 0);
digitalWrite(dir1PinB, LOW);                    // STOP = LOW on both pins
digitalWrite(dir2PinB, LOW);
Serial.println("Motor 1 Stop");
Serial.println("Motor 2 Stop");
Serial.println("   ");
break;

case '3':                                       // Motor 1 Reverse
analogWrite(speedPinA1, 255);                   //Sets speed variable via PWM 
analogWrite(speedPinA2, 255);
digitalWrite(dir1PinA, HIGH);                   // REVERSE = HIGH on pin 1, LOW on pin 2
digitalWrite(dir2PinA, LOW);
analogWrite(speedPinB1, 255);
analogWrite(speedPinB2, 255);
digitalWrite(dir1PinB, HIGH);                   // REVERSE = HIGH on pin 1, LOW on pin 2
digitalWrite(dir2PinB, LOW);
Serial.println("Motor 1 Reverse");
Serial.println("Motor 2 Reverse");
Serial.println("   ");
break;

default:
                                              // turn all the connections off if an unmapped key is pressed:
for (int thisPin = 2; thisPin < 11; thisPin++) {
digitalWrite(thisPin, LOW);
}
  }
    }
      }
