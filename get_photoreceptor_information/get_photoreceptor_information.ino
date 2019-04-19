#include <RGBConverter.h> 

#define MAX_ANALOG_INPUT_VAL 1023
#define MIN_PHOTORECEPTOR_VAL 100
#define MAX_PHOTORECEPTOR_VAL 600

const int BLUE_PIN = 3;
const int GREEN_PIN = 5; 
const int RED_PIN = 6;

const int PHOTO_INPUT = A1;
const int SLIDER_INPUT = A5;


//range from 850 to 550 on slider

//static hsl rgbToHSL(rgb current);
//static rgb hslToRGB(hsl current);

void setup() {
  // sets up the output pins for led and input pins for sensing from the sensor. 
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(PHOTO_INPUT, INPUT);
  pinMode(SLIDER_INPUT, INPUT);
  Serial.begin(9600);
}

//dynamic range is 100 to 400

void loop() {
  // get values out of slider and photoresistor and constrain them. 
  int potVal = analogRead(PHOTO_INPUT);
  potVal = constrain(potVal, 100, 600);
  int potValSlide = analogRead(SLIDER_INPUT);
  potValSlide = constrain(potValSlide, 200, 600); 

  //transform values into appropriate range. 
  int colorVal = map(potValSlide, 200, 600, 0, 255); 
  int ledIntensityVal = map(potVal, MIN_PHOTORECEPTOR_VAL, MAX_PHOTORECEPTOR_VAL, 0, 255); //get map from regular to led value
  int inverseLedVal = 255- ledIntensityVal; //inverse brightness for photoreceptor;

  Serial.print(potVal);
  Serial.print(",");
  Serial.print(potValSlide);
  Serial.print(",");
  Serial.print(colorVal);
  Serial.print(",");
  Serial.println(ledIntensityVal);

  RGBConverter current;

  byte rgb[3]; 
  double h;
  double s;
  double l;
  //calculate h, s, and l by calculating a proportion of 255. 
  h = 1- 1.0 * colorVal / 255;
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
  current.hslToRgb(h, s, l, rgb);
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

  delay(1000);

}
