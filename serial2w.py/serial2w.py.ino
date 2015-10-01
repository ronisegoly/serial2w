// Version 0.1
// Roni Segoly roni@yozma.net
// Date       : 26/9/15
//https://github.com/bblanchon/ArduinoJson/blob/master/examples/JsonGeneratorExample/JsonGeneratorExample.ino
#include <ArduinoJson.h>
#include <Servo.h>
StaticJsonBuffer<200> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
String received_message="";
float received_value =0.0;
Servo clawServo;
void setup() 
{
  Serial.begin(9600); // set the baud rate
  clawServo.attach(8);
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
    root["command"]=received_message;
    //send back
    root.printTo(Serial);
    process_message(received_message, received_value);
    //force readline on python side
    Serial.println("\n");
    
  
  }
  delay(5000);
}

void process_message(String command, float value)
{
 //do somthing
  
  
}

void parse_message(String myStr)

{
  String myString=myStr;
  int commaIndex = myString.indexOf(',');
  received_message= myString.substring(0, commaIndex);
  String valueString = myString.substring(commaIndex+1, myString.length());
  received_value = valueString.toFloat();
 
}
