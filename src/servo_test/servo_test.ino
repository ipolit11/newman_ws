#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define MIN_PULSE_WIDTH       0
//650
#define MAX_PULSE_WIDTH       2600
//2350
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50
// our servo # counter
uint8_t servonum = 3;
uint8_t servo = 0;
uint8_t serv=0;
void setup() {
 
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);  // Analog servos run at ~60 Hz updates
  
 
}

void loop() {
  
 // Serial.print("servonum1 "); Serial.println(servonum);//----------------------------
 // delay(1000);
 int potent =analogRead(0);
 // Serial.print("servonum2 "); Serial.println(servonum);//----------------------------
 // delay(1000);
 potent =map(potent, 0, 1024, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
 // Serial.print("servonum3 "); Serial.println(servonum);//------------------------------
 // delay(1000);
  serv=servonum;
  if (Serial.available() > 0) {
      
      servo= Serial.parseInt();
      servonum=servo;
    //  Serial.print("servo<0 "); Serial.println(servo);
   }
   if (Serial.available() == 0) {
      
      servonum=serv;
     // Serial.print("servo=0 "); Serial.println(servo);
   }
     
  
  //  Serial.print("servonum4 "); Serial.println(servonum);//--------------------------------
  //   delay(1000);
  Serial.print("Serva_№ "); Serial.println(servonum);   
  Serial.print("pulseWidth "); Serial.println(potent);
  
  pwm.setPWM(servonum, 0, pulseWidth(potent));
 // Serial.print("servonum5 "); Serial.println(servonum);//----------------------------------
  delay(1000);
 
}

int pulseWidth(int potent)
{
  int analog_value;
 // pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  
  analog_value = int(float(potent) / 1000000 * FREQUENCY * 4096);

  Serial.print("analog_value "); Serial.println(analog_value);
  
  
  return analog_value;
}
