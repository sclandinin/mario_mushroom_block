/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include <CurieIMU.h>

Servo myservo;  // create servo object to control a servo

int pos_opener, pos_dumper;
const int amp_enable = 3;
const int audio = 4;

//********************************************************************************************
// setup
//********************************************************************************************
void setup() 
{
  pinMode(amp_enable, OUTPUT);
  pinMode(audio, OUTPUT);

  
  /* Initialise the IMU */
  CurieIMU.begin();
  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);
  delay(100);
}

//********************************************************************************************
// loop - do the stuff
//********************************************************************************************
void loop() 
{
  float ax, ay, az;   //scaled accelerometer values


  //read accelerometer measurements from device, scaled to the configured range
  CurieIMU.readAccelerometerScaled(ax, ay, az);

  //ay = 1 at resting, lower value indicated negative acceleration (block falling)
  if (ay < 0.5)   
  {    
    activate();
  }
}


//********************************************************************************************
// activate
//********************************************************************************************
void activate()
{   
  
  
  delay(1500);
  
  digitalWrite(amp_enable, HIGH);
  digitalWrite(audio, HIGH);
  digitalWrite(audio, LOW);
  
  //open lid
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  for (pos_opener = 0; pos_opener <= 103; pos_opener += 1) // goes from 0 degrees to 180 degrees
  { 
                                        // in steps of 1 degree
    myservo.write(pos_opener);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
   
  digitalWrite(amp_enable, LOW);


  //eject mushroom
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
  for (pos_dumper = 180; pos_dumper >= 60; pos_dumper -= 1) // goes from 0 degrees to 180 degrees
  { 
                                        // in steps of 1 degree
    myservo.write(pos_dumper);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  
  delay(100);
  
  //bring in ejector
  for (pos_dumper = 60; pos_dumper <= 180; pos_dumper += 1) // goes from 180 degrees to 0 degrees
  { 
    myservo.write(pos_dumper);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
  
  //close lid
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  for (pos_opener = 103; pos_opener >= 0; pos_opener -= 1) // goes from 180 degrees to 0 degrees
  { 
    myservo.write(pos_opener);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }

  delay(100);
  myservo.detach();  // attaches the servo on pin 9 to the servo object
}



