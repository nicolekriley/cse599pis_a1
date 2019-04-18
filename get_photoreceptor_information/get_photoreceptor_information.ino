#define MAX_ANALOG_INPUT_VAL 1023

const int BLUE_PIN = 3;
const int GREEN_PIN = 5; 
const int RED_PIN = 6;

const int POT_INPUT_PIN = A1;
const int POT_INPUT_PIN2 = A5;


void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(POT_INPUT_PIN, INPUT);
  pinMode(POT_INPUT_PIN2, INPUT);
  Serial.begin(9600);
}

//dynamic range is 100 to 400

void loop() {
  // put your main code here, to run repeatedly:
  int potVal = analogRead(POT_INPUT_PIN);
  int potValSlide = analogRead(POT_INPUT_PIN2);
  int ledVal = map(potVal, 0, MAX_ANALOG_INPUT_VAL, 0, 255); //get map from regular to led value

  Serial.print(potVal);
  Serial.print(",");
  Serial.print(potValSlide);
  Serial.print(",");
  Serial.println(ledVal);

  analogWrite(RED_PIN, ledVal);
  analogWrite(GREEN_PIN, 255-ledVal);
  analogWrite(BLUE_PIN, ledVal); 

  delay(1000);
}

// used http://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/ as a refernece on steps.
void rbgToHSL(int red, int green, int blue) {
  // get them between a range from 0 to 1. 
  float r_range1 = red * 1.0 /255;
  float g_range1 = green * 1.0 / 255; 
  float b_range1 = blue * 1.0 / 255; 

  //get the min value
  float minVal = r_range1 < b_range1 ? r_range1 : b_range1;
  
  minVal = g_range1 < minVal ? g_range1:minVal; 
  
  int maxColorStream;

  // get the max value
  float maxVal = r_range1 > b_range1 ? r_range1 : b_range1;
  maxVal = g_range1 > maxVal ? g_range1: maxVal;
  if(maxVal == r_range1) {
    maxColorStream = 0;
  } else if (maxVal == g_range1) {
    maxColorStream = 1; 
  } else {
    maxColorStream = 2;
  }

  float luminence = (minVal + maxVal) / 2;

  float saturation; 
  if (minVal == maxVal) {
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

}

void hslToRgb(float hue, float saturation, float luminence) {
  if (saturation == 0) { //it is a shade of gray
    int red = luminence * 255; 
    int blue = luminence * 255;
    int green = luminence * 255; 
  } else {
    float temporary1;
    if (luminence < .5) {
      temporary1 = luminence * (1.0 + saturation);
    } else {
      temporary1 = luminence + saturation - luminence * saturation;
    }
  }
}
