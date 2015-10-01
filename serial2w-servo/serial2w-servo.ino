// Version 0.1
// Roni Segoly roni@yozma.net
// Date       : 26/9/15
//https://github.com/bblanchon/ArduinoJson/blob/master/examples/JsonGeneratorExample/JsonGeneratorExample.ino
#include <ArduinoJson.h>
#include <Servo.h>
#include <Servo.h>
StaticJsonBuffer<200> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();


Servo middle,left, right,claw;  // create servo object to control a servo
String returned_message="";
String received_message="";
float received_value =0.0;
Servo clawServo;
void setup() 
{
  Serial.begin(9600); // set the baud rate
  middle.attach(9);  // attaches the servo on pin 9 to the servo object
  left.attach(10);  // attaches the servo on pin 9 to the servo object
  right.attach(11);  // attaches the servo on pin 9 to the servo object
  claw.attach(12);  // attaches the servo on pin 9 to the servo object

  Serial.println("Ready"); // print "Ready" once
}
void loop()
{
  char str1[80]="";
  //buiild json strucutre
  root["light"]=12;
  root["temp"]=256;
  root["humidity"]=23.4;
  root["v8"]="fffg";
 //check if and hoe many bytres recieved 
  byte numByte=Serial.available();
    if (numByte>0)
  { // only send data back if data has been sent
    int i;
  //read the whole string
    for (i=0;i<numByte;i++)
    {
      char inByte = Serial.read(); // read the incoming data
      str1[i]=inByte;
    }
    //put an end to the string
    str1[i]='\0';
    //add the sent command to json , just for debug
    parse_message(str1);
    process_message(received_message, received_value);
    root["command"]=returned_message;
    //send back
    root.printTo(Serial);
    //force readline on python side
    Serial.println("\n");
    
  }
  delay(5000);
}

void process_message(String command, float value)
{
 if (command=="claw")
 {
   robot_claw(value);
   return;
 }
 if (command=="right")
 {
   robot_right(value);
   return;
 }if (command=="left")
 {
   robot_left(value);
   return;
 }if (command=="middle")
 {
   robot_middle(value);
   return;
 }
 returned_message="what?????";
}

void parse_message(String myStr)

{
  String myString=myStr;
  int commaIndex = myString.indexOf(',');
  received_message= myString.substring(0, commaIndex);
  String valueString = myString.substring(commaIndex+1, myString.length());
  received_value = valueString.toFloat();
 
}

void robot_claw(int degree)
{
  Serial.println("Message revieced by robot");
  returned_message=received_message+received_value;
  claw.write(degree);
}

void robot_right(int degree)
{
Serial.println("Message revieced by robot");
  returned_message=received_message+received_value;
  right.write(degree);
}

void robot_left(int degree)
{
Serial.println("Message revieced by robot");
returned_message=received_message+received_value;
  left.write(degree);
}

void robot_middle(int degree)
{
Serial.println("Message revieced by robot");
returned_message=received_message+received_value;
  middle.write(degree);
}
