#include <SimpleTimer.h>
#include <Servo.h>
#include <Blynk.h>
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX

#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleStream.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "a37dcdda959e405b95175a733d22f250";

BLYNK_CONNECTED() { // whatever is in this will run every time Blynk connection establishes
  Blynk.syncVirtual(V4); //refresh the value of V4 which ideally is storing the motor value ex 512 at midpoint.
}

Servo esc;
int val; // app they need to be global from this thread: http://community.blynk.cc/t/how-to-return-values-from-blynk-write/2363/6 
int spd;
SimpleTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, millis() / 1000); // reading frequency occupied by VIRTUAL PIN 5
}

void setup()
{
  // Debug console
  DebugSerial.begin(9600); // CANT OPEN SERIAL MONITOR WITH BLYNK AT THE SAME TIME

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Blynk.begin(Serial, auth);

  // Setup a function to be called every second
  timer.setInterval(1000, myTimerEvent);

  // Servo stuff
  esc.attach(8);
  esc.writeMicroseconds(1500);
}

//http://docs.blynk.cc/#blynk-firmware-virtual-pins-control 
//https://github.com/blynkkk/blynk-library/blob/master/examples/More/ServerAsDataStorage/ServerAsDataStorage_SingleValue/ServerAsDataStorage_SingleValue.ino

BLYNK_WRITE(V0) { // virtual pin 0 is for setting the midpoint
  int virtualbutton = param.asInt();
  if(virtualbutton == HIGH) {
    val = 512;
   // spd = map(val, 0, 1023,1000, 2000);
   // esc.writeMicroseconds(spd); // should map it to its "zero position"
  }
}

// check if value is indeed given as 512
BLYNK_READ(V4) { // still need to check frequency of update? App says one second? 
  Blynk.virtualWrite(V4,val); // this is necessary because virtual functions cannot be nested for some reason
}

BLYNK_WRITE(V1) { // virtual pin 1 is for incrementing val
  int virtualincrement = param.asInt();
  if(virtualincrement == HIGH) {
    val = val + 20;
  } 
}
BLYNK_WRITE(V2) { // virtual pin 2 is for decrementing val
  int virtualdecrement = param.asInt();
  if(virtualdecrement == HIGH) {
    val = val - 20;
  } 
}  

BLYNK_WRITE(V3) { // virtual pin 3 is for confirming the sending of a value to the motor: sort of a safeguard
  int virtualconfirm = param.asInt();
  if(virtualconfirm == HIGH) {
    spd = map(val, 0, 1023,1000, 2000); // should trigger new speed
    esc.writeMicroseconds(spd);
  }
}

void loop()
{ 
  Blynk.run();
  timer.run();
//  BLYNK_WRITE(V0);
//  BLYNK_READ(V4);
//  BLYNK_WRITE(V1);
//  BLYNK_WRITE(V2);
//  BLYNK_WRITE(V3);
}

