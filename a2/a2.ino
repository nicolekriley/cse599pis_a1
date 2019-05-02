#include <RGBConverter.h> 

/*
 * takes input from photoreceptor and that inversely affects brightness. Also takes in input from a slider to determine
 * the color of the RGB in the circuit. Changes the delay by 10 at 30 second marks from the start time. 
 */

//used library https://github.com/ratkins/RGBConverter

#define MAX_ANALOG_INPUT_VAL 1023

const int BLUE_PIN = 3;
const int GREEN_PIN = 5; 
const int RED_PIN = 6;

const int POT_INPUT = A0;

RGBConverter converter;

void setup() {
  // sets up the output pins for led and input pins for sensing from the sensor. 
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(POT_INPUT, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  // get values out of slider and photoresistor and constrain them. 
  int potTwist = analogRead(POT_INPUT);
  Serial.print("pot val twist before constrain ");
  Serial.println(potTwist);


  //transform values into appropriate range. 

  if (potTwist < 250) {
    setColor(0, 255, 255);
  } else if (potTwist < 500) {
    setColor(255, 0, 255);
  } else if (potTwist < 750) {
    setColor(255, 255, 0); 
  } else {
    setColor(255, 0, 0);
  }
  //int colorVal = map(potTwist, 80, 1023, 0, 255); 

  /*

  Serial.print(potTwist);
  Serial.print(",");
  Serial.println(colorVal);

  int inverseLedVal = 0;
  byte rgb[3]; 
  double h;
  double s;
  double l;
  //calculate h, s, and l by calculating a proportion of 255. 
  h = 2.0 * colorVal / 255;
  if (h > 1) {
    h = 1.0;
  }
  s = 1.0;
  l = 1-(1.0 * inverseLedVal)/255;
  
  //hsl value result
  
  Serial.println("hsl");
  Serial.print(h);
  Serial.print(",");
  Serial.print(s);
  Serial.print(",");
  Serial.println(l);
  
  // convert hsl to rgb. 
  converter.hslToRgb(h, s, l, rgb);
  Serial.println("rgb");
  Serial.print(rgb[0]);
  Serial.print(",");
  Serial.print(rgb[1]);
  Serial.print(",");
  Serial.println(rgb[2]);
    
  //write values to rgb
  analogWrite(RED_PIN, rgb[0]);
  analogWrite(GREEN_PIN, rgb[1]);
  analogWrite(BLUE_PIN, rgb[2]);
  */
  int delayTime = 1000;
  int currentTime = millis();

  delay(delayTime);

}

void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red); 
  analogWrite(BLUE_PIN, blue);
  analogWrite(GREEN_PIN, green);
}
