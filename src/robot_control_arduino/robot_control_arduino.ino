//#include <Servo.h>//ок
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include <ros.h>//ок
#include <std_msgs/Int32.h>//другой тип данных
#include <sensor_msgs/JointState.h>//
#define FREQUENCY 50
uint8_t servonum = 0;
ros::NodeHandle node_handle;//ok
Adafruit_PWMServoDriver robot_servos;
//Servo robot_servos[5];//ок-----------------------------------------------
int input;
int MIN_PULSE_WIDTH [5] ={640, 640, 525, 880, 640}; //{525, 580, 446, 500, 718}
int MAX_PULSE_WIDTH [5]={2400, 2400, 2450, 2450, 2400}; //{2597, 2597, 2551, 2597, 2409}
//int servo_pins[5] = {10, 9, 6, 5, 3}; // PWM Pins on Arduino Uno
int mid_positions[5] = {90, 90, 90, 90, 90}; //{100, 100, 100, 90, 100}
int SERVO_CURRENT_POSITIONS[5];

float TARGET_JOINT_POSITIONS[5] = {0,0,0,0,0};

// Convert the joint state values to degrees, adjust for the center and write to the servo
void writeServos() {
  for (int j = 0; j < 5; j++) {
    int target_angle;
    if (j == 2) {
      // Due to difference in mounting directions
      target_angle = - TARGET_JOINT_POSITIONS[j]*(180/3.14) + mid_positions[j];
    } else {
      target_angle = TARGET_JOINT_POSITIONS[j]*(180/3.14) + mid_positions[j];
    }

   
    robot_servos.setPWM(j, 0, pulseWidth(target_angle, j));
    SERVO_CURRENT_POSITIONS[j] = target_angle;
  }
  node_handle.spinOnce();
}

// Subscriber Callback to store the jointstate position values in the global variables
void servoControlSubscriberCallbackJointState(const sensor_msgs::JointState& msg) {
  TARGET_JOINT_POSITIONS[0] = msg.position[0];
  TARGET_JOINT_POSITIONS[1] = msg.position[1];
  TARGET_JOINT_POSITIONS[2] = msg.position[2];
  TARGET_JOINT_POSITIONS[3] = msg.position[3];
  TARGET_JOINT_POSITIONS[4] = msg.position[4];
  // Call the method to write the joint positions to the servo motors
  writeServos();//-----------------------------------------------------------------------------------------------------

}


ros::Subscriber<sensor_msgs::JointState> servo_control_subscriber_joint_state("joint_states", &servoControlSubscriberCallbackJointState);

void setup() {
 
robot_servos.begin();
robot_servos.setPWMFreq(FREQUENCY);
 
  // Initial the servo motor connections and initialize them at home position
  for (unsigned int i = 0; i < 5; i++) {
    //robot_servos[i].attach(servo_pins[i]);//----------------------------------------------------------
    //robot_servos[i].write(mid_positions[i]);//--------------------------------------------------------
    robot_servos.setPWM(i, 0, pulseWidth(mid_positions[i], i ));
    SERVO_CURRENT_POSITIONS[i] = mid_positions[i];//-------------------------------------------------
  }

  // Set the communication BaudRate and start the node
  node_handle.getHardware()->setBaud(115200);
  node_handle.initNode();
  node_handle.subscribe(servo_control_subscriber_joint_state);
}

void loop() {//ок
  // Keep calling the spinOnce() method in this infinite loop to stay tightly coupled with the ROS Serial
  node_handle.spinOnce();//ок
  delay(1);//ок
}

int pulseWidth(int angle, int input)//---------------------------------
{
  int pulse_wide, analog_value;
  //int MIN_PULSE_WIDTH [6] ={1269, 718, 500, 446, 580, 525};
 // int MAX_PULSE_WIDTH [6]={2196, 2409, 2597, 2551, 2597, 1597};
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH[input], MAX_PULSE_WIDTH[input]);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  //Serial.println(analog_value);
  return analog_value;
}
