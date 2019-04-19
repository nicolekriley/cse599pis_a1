#include <FastLED.h>

#define MAX_ANALOG_INPUT_VAL 1023
#define MIN_PHOTORECEPTOR_VAL 100
#define MAX_PHOTORECEPTOR_VAL 600
#define RED CRGB(0, 255, 255)
#define BLUE CRGB(255, 255, 0);
#define GREEN CRGB(255, 0, 255);
#define PURPLE CRGB(0, 255, 0);

const int BLUE_PIN = 3;
const int GREEN_PIN = 5; 
const int RED_PIN = 6;

const int PHOTO_INPUT = A1;
const int SLIDER_INPUT = A5;

/*
struct hsl {
  float luminence; // between 0 and 1
  float hue; // 0 to 360 degrees
  float saturation; // between 0 and 1
};

struct rgb {
  float red; // 0 to 255
  float green; // 0 to 255
  float blue; // 0 to 255;
};
*/

//range from 850 to 550 on slider

//static hsl rgbToHSL(rgb current);
//static rgb hslToRGB(hsl current);

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(PHOTO_INPUT, INPUT);
  pinMode(SLIDER_INPUT, INPUT);
  Serial.begin(9600);
}

//dynamic range is 100 to 400

// This came from an example of fastled code for the file AnalogOutput
void showAnalogRGB( const CRGB& rgb)
{
  /*Serial.println("r val"); 
  Serial.println(rgb.r);
  delay(500);
  Serial.println("g val");
  Serial.println(rgb.g);
  delay(500);
  Serial.println("b val");
  Serial.println(rgb.b);
  delay(500);*/
  analogWrite(RED_PIN,   rgb.r );
  analogWrite(GREEN_PIN, rgb.g );
  analogWrite(BLUE_PIN,  rgb.b );
}

void loop() {
  // put your main code here, to run repeatedly:
  int potVal = analogRead(PHOTO_INPUT);
  potVal = constrain(potVal, 100, 600);
  int potValSlide = analogRead(SLIDER_INPUT);
  potValSlide = constrain(potValSlide, 200, 600); 
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

  CRGB result;
  hsv2rgb_spectrum( CHSV(colorVal, 255, ledIntensityVal), result);
  Serial.print(result.r);
  Serial.print(",");
  Serial.print(result.g);
  Serial.print(",");
  Serial.println(result.b);

  analogWrite(RED_PIN, result.r);
  analogWrite(GREEN_PIN, result.g);
  analogWrite(BLUE_PIN, result.b);

  delay(1000);

  //showAnalogRGB(CRGB(0, 0, 0));
  //delay(1000);
}
/*

// used http://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/ as a refernece on steps.
hsl rbgToHSL(rgb current) {

  hsl result;
  
  // get them between a range from 0 to 1. 
  float r_range1 = current.red * 1.0 /255;
  float g_range1 = current.green * 1.0 / 255; 
  float b_range1 = current.blue * 1.0 / 255; 

  //get the min value
  float minVal = r_range1 < b_range1 ? r_range1 : b_range1;
  
  minVal = g_range1 < minVal ? g_range1:minVal; 
  
  int maxColorStream;

  // get the max value
  float maxVal = r_range1 > b_range1 ? r_range1 : b_range1;
  maxVal = g_range1 > maxVal ? g_range1: maxVal;
  float redValDiff = maxVal - r_range1;
  float greenValDiff = maxVal - g_range1;
  
  if(redValDiff < 0.0001) {
    maxColorStream = 0;
  } else if (greenValDiff < 0.0001) {
    maxColorStream = 1; 
  } else {
    maxColorStream = 2;
  }

  float luminence = 1.0 * (minVal + maxVal) / 2;

  float saturation; 
  float minValDiff = maxVal - minVal;
  if (minValDiff < 0.0001) {
    saturation = 0;
  } else if (luminence < 0.5) {
    saturation = (maxVal - minVal) * 1.0/ (maxVal + minVal);
  } else {
    saturation = (maxVal - minVal) * 1.0 / (2.0 - maxVal - minVal);
  }

  float hue;
  
  if (maxColorStream == 0) { //red was largest
    hue = (g_range1 - b_range1) * 1.0 / (maxVal - minVal);
  } else if (maxColorStream == 1) { //green was largest
    hue = (2.0 + b_range1 - r_range1)/(maxVal - minVal);
  } else {
    hue = (4.0 + r_range1 - g_range1)/(maxVal - minVal);  
  }

  hue *= 60; 
  result.hue = hue;
  result.saturation = saturation;
  result.luminence = luminence;
  return result;

}

rgb hslToRgb(hsl current) {
  rgb result;
  if (current.saturation == 0) { //it is a shade of gray
    result.red = current.luminence * 255; 
    result.blue = current.luminence * 255;
    result.green = current.luminence * 255; 
    return result;
  } 
  float temporary1;
  if (current.luminence < .5) {
    temporary1 = current.luminence * (1.0 + current.saturation);
  } else {
    temporary1 = current.luminence + current.saturation - current.luminence * current.saturation;
  }
  float temporary2 = 2 * current.luminence - temporary1;
  float hueAngle = current.hue * 1.0 / 360;
  float temporaryr = hueAngle + 0.333;
  if (temporaryr > 1) {
    temporaryr -= 1;
  }
  float temporaryg = hueAngle;
  float temporaryb = hueAngle - 0.333;
  if (temporaryb < 0) {
    temporaryb += 1;
  }
  float red;
  float green;
  float blue;
  result.red = red * 255;
  result.green = green * 255;
  result.blue = blue * 255;
  return result;
} 
*/
