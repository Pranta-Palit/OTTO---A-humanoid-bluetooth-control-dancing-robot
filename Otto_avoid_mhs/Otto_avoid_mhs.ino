//----------------------------------------------------------------
//-- CC BY SA (http://ottodiy.com)
//-- 16 January 2017 - Modified by MHs, Ultra Sound fixed
//-- double check your US (Ultra sound) module some have TRIG and ECHO swapped!
//-----------------------------------------------------------------
//-- Otto will avoid obstacles with this code!
//-----------------------------------------------------------------
#include <Servo.h> 
#include <Oscillator.h>
#include <US.h>
#include <Otto.h>
Otto Otto;  //This is Otto!
//---------------------------------------------------------
//-- First step: Make sure the pins for servos are in the right position
/*
         --------------- 
        |     O   O     |
        |---------------|
YR 3==> |               | <== YL 2 yaw left
         --------------- 
            ||     ||
RR 5==>   -----   ------  <== RL 4 roll left
         |-----   ------|
*/
  #define PIN_YL 2 //servo[2]
  #define PIN_YR 3 //servo[3]
  #define PIN_RL 4 //servo[4]
  #define PIN_RR 5 //servo[5]

  #define ECHOPIN 9        // Pin to receive echo pulse
  #define TRIGPIN 8        // Pin to send trigger pulse

///////////////////////////////////////////////////////////////////
//-- Global Variables -------------------------------------------//
///////////////////////////////////////////////////////////////////
//-- Movement parameters
int T=1000;              //Initial duration of movement
int moveId=0;            //Number of movement
int moveSize=15;         //Asociated with the height of some movements
//---------------------------------------------------------
bool obstacleDetected = false;
///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup(){
  Serial.begin(19200);
  //Set the servo pins
  Otto.init(PIN_YL,PIN_YR,PIN_RL,PIN_RR,true, -1, 10, 8, 9);
  Otto.sing(S_connection); //Otto wake up!
  Otto.home();
  delay(50);
  Otto.sing(S_happy); // a happy Otto :)

  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
}
///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {
  if(obstacleDetected){ 
               Otto.sing(S_surprise); 
               Otto.playGesture(OttoFretful); 
               Otto.sing(S_fart3); 
               Otto.walk(2,1300,-1); 
               Otto.turn(2,1000,-1);                
             delay(50); 
             obstacleDetector(); 
             }        
         else{ 
            Otto.walk(1,1000,1); 
            obstacleDetector(); 
        }           
  }  
//////////////////////////////////////////////////////////////////////////////////
//-- Function to read distance sensor & to actualize obstacleDetected variable //
/////////////////////////////////////////////////////////////////////////////////
void obstacleDetector(){
// Start Ranging
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
// Compute distance
  float distance = pulseIn(ECHOPIN, HIGH);
  distance= distance/58;
  Serial.print(distance);
  Serial.println("cm");
 if(distance<12){
          obstacleDetected = true;
          Serial.println ("Obstacle Detected! Avoid collision");
        }else{
          obstacleDetected = false;
          Serial.println ("No Obstacle detected! - Keep on walking");
        }
  
}
