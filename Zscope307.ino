/* Zscope307  a very very simple oscilloscope program to 
 *  acquire and display time varying signals with an 
 *  Arduino and computer.
 *  Samples an analog pin and also outputs a sqaure wave at an 
 *  integer fraction of the sample rate.
 *  Run this with the serial plotter or monitor to collect your
 *  data.
 *  
 *  Aleks Zosuls Boston University 2020
 */

bool outState = true; //the state of the digital square wave pin
float DCOffsetNull = 0; //tune this to subtract your rail splitter voltage
float gain = 1;  //software gain, useful for calibration
int z = 0;  //square wave iterator
int samplePeriodms = 2; //time delay between samples in milliseconds. Note this method
//is not very accurate. Use interrupts for legit sample timing
int squareWaveOut = 8;  // pin that outputs a square wave
int squareHalfCycSamples = 200; //number of analog samples betwen
//square wave transistions
int anaInput1 = 0;  //the analog pin that is the scope input

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  pinMode(squareWaveOut,OUTPUT);

}

void loop() {
  // this line reads the ADC and calibrates to volts
Serial.println(gain*(analogRead(anaInput1)*0.00488)-DCOffsetNull);
delay(samplePeriodms); //sample time delay. not very accurate at single 
//digit delays

//This is the square wave generator
++z;  //iterate each loop for square transition delay
if(z == squareHalfCycSamples){  //when we reach the max then change state
  digitalWrite(squareWaveOut,outState);
  outState = !outState; //toggle the state of the variable
  z = 0;    //reset half cycle counter
  }
}
