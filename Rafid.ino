#include <AFMotor.h> // Motor Library add
#define lights_green 46
#include <NewPing.h>
#define TRIGGER_PIN  44
#define ECHO_PIN     45
#define MAX_DISTANCE 200
AF_DCMotor motor(2,MOTOR12_64KHZ); //Left MOTOR-reset button of motor driver as a reference
AF_DCMotor motor2(4,MOTOR12_64KHZ); //Right MOTOR
int left_brown = 8; //Start from left sense pin
int blue = 9;
int yellow = 10;
int grey = 11;
int right_white = 12;
int value_brown, value_blue,value_yellow, value_grey, value_white;
int convalue1, convalue2,convalue3, convalue4,convalue5;
int leftOffset,rightOffset,xright,xleft,centre;
int distance;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void calibrate() {
for (int x=0; x<10; x++) { // run this 10 times to obtain average
digitalWrite(lights_green, HIGH); // lights on
//delay(100);
value_brown = analogRead(left_brown);//Name of color indicates the colors of the wires 
value_blue = analogRead(blue); 
value_yellow = analogRead(yellow); 
value_grey = analogRead(grey); 
value_white = analogRead(right_white);
leftOffset = leftOffset + value_brown;// add value of left sensor to total
xleft=xleft+value_blue;
centre = centre + value_yellow;// add value of centre sensor to total
xright=xright+value_grey;
rightOffset = rightOffset + value_white; // add value of right sensor to total
//delay(100);
digitalWrite(lights_green, LOW); // lights off
//delay(100);
}
// obtain average for each sensor
leftOffset = leftOffset / 10;
xleft=xleft/10;
centre = centre /10;
xright=xright/10;
rightOffset = rightOffset / 10;



}
void setup()
{ 
  Serial.begin(9600);
  pinMode(value_brown, INPUT);
  pinMode(value_blue, INPUT);
  pinMode(value_yellow, INPUT);
  pinMode(value_grey, INPUT);
  pinMode(value_white, INPUT);
 pinMode(lights_green, OUTPUT);
 calibrate();
//delay(3000);
digitalWrite(lights_green, HIGH); // lights on
//delay(100);

}
void loop()
{ 
  delay(500);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  distance = uS / US_ROUNDTRIP_CM;
  //Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.print(distance);
  Serial.println("cm");
  if (convalue1!=0 ||
convalue2!=0 ||
convalue3!=0 || 
convalue4!=0 ||
convalue5!=0 &&
distance>10 
)
{
  motor.setSpeed(100);
motor2.setSpeed(100);
motor.run(FORWARD);
motor2.run(FORWARD);
}

if(distance>200 || distance ==0 || distance>30)
{
  motor.setSpeed(100);
motor2.setSpeed(100);
motor.run(FORWARD);
motor2.run(FORWARD);
}

if(distance<=50 && distance >30)
{
  motor.setSpeed(50);
  motor2.setSpeed(50);
}

else if(distance<=30)
{
  motor.run(BACKWARD);
  motor2.run(BACKWARD);
  
  delay(500);
  motor.run(FORWARD);
  motor2.setSpeed(0);
  delay(150);
  
}
  
value_brown = analogRead(left_brown);
value_blue = analogRead(blue);
value_yellow = analogRead(yellow); 
value_grey = analogRead(grey); 
value_white = analogRead(right_white);
Serial.print("value_brown");
Serial.println(analogRead(value_brown));
Serial.print("value_blue");
Serial.println(analogRead(value_blue));
Serial.print("value_yellow");
Serial.println(analogRead(value_yellow));
Serial.print("value_grey");
Serial.println(analogRead(value_grey));
Serial.print("value_white");
Serial.println(analogRead(value_white));

//delay(2000);

{
{if ( value_brown >=490 && value_brown <= 1022 )
convalue1 = 0 ; //Black

else if ( value_brown >= 15 && value_brown <= 491)
convalue1 = 1 ;
} //; //White
{if ( value_blue >= 490 && value_blue <= 1022)
convalue2 = 0 ;  //Black
else if ( value_blue >=15 && value_blue <= 491)
convalue2 = 1 ;
} //White
{if ( value_yellow >= 490 && value_yellow <= 1022)
convalue3 = 0 ;  //Black
else if ( value_yellow >= 15 && value_yellow <= 491)
convalue3 = 1 ;
} //White
{if ( value_grey >= 490 && value_grey <= 1022)
convalue4 = 0 ;  //Black
else if ( value_grey >= 15 && value_grey <=491 )
convalue4 = 1 ;} //White
{if ( value_white >= 490 &&value_white <= 1022)
convalue5 = 0 ;  //Black
else if (value_white >= 15 && value_white <= 491)
convalue5 = 1 ;} //White
}


/*if (convalue1==0 &&
convalue2==0 &&
convalue3==0 && 
convalue4==0 &&
convalue5==0 ) //Stop
 {
Serial.print("Go straight new");
delay(900);
motor.setSpeed(0);
motor2.setSpeed(0);
 }*/

}
