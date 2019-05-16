#include <RGBConverter.h> 

/*
 * takes input from photoreceptor and that inversely affects brightness. Also takes in input from a slider to determine
 * the color of the RGB in the circuit. Changes the delay by 10 at 30 second marks from the start time. 
 */

//used library https://github.com/ratkins/RGBConverter

#define MAX_ANALOG_INPUT_VAL 1023
#define MIN_PHOTORECEPTOR_VAL 100
#define MAX_PHOTORECEPTOR_VAL 600

const int BLUE_PIN = 3;
const int GREEN_PIN = 5; 
const int RED_PIN = 6;

const int SLIDER_INPUT = A0;

//keep track of time
int startTime = millis();

RGBConverter converter;

void setup() {
  // sets up the output pins for led and input pins for sensing from the sensor. 
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(SLIDER_INPUT, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  // get values out of slider and photoresistor and constrain them. 
  int potValSlide = analogRead(SLIDER_INPUT);
  Serial.print("pot val slide before constrain");
  Serial.println(potValSlide); 

  //transform values into appropriate range. 

  int potVal = 100;
  int colorVal = map(potValSlide, 0, 1023, 0, 255); 
  int ledIntensityVal = map(potVal, MIN_PHOTORECEPTOR_VAL, MAX_PHOTORECEPTOR_VAL, 0, 255); //get map from regular to led value
  int inverseLedVal = 255- ledIntensityVal; //inverse brightness for photoreceptor;
  
  Serial.print(potVal);
  Serial.print(",");
  Serial.print(potValSlide);
  Serial.print(",");
  Serial.print(colorVal);
  Serial.print(",");
  Serial.println(ledIntensityVal);
   
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

  int delayTime = 1000;
  int currentTime = millis();

  //delay time is 10 timies longer at a 30 second mark. 
  if (abs(currentTime - startTime) > 30,000) {
    startTime = currentTime;
    Serial.println("its at a 30 second mark");
    delayTime = 1000 * 10;
  }
  
  delay(delayTime);

}
