
#include "ros/ros.h"
//#include "std_msgs/Float64.h"
#include <iostream>
#include <sensor_msgs/JointState.h>
#include "face_tracker_control_newman/centroid.h"

//Tracker parameters

int servomaxx, servomin,screenmaxx, center_offset, center_left, center_right;
float servo_step_distancex, current_pos_x;

//std_msgs::Float64 initial_pose;
//std_msgs::Float64 current_pose;
sensor_msgs::JointState joint_state;

ros::Publisher dynamixel_control;

double current_pose = 0;
double initial_pose =0;

void track_face(int x,int y)
{
	
    //Find out if the X component of the face is to the left of the middle of the screen.
    if(x < (center_left)){

	ROS_INFO("Face is at Left");

	current_pos_x += servo_step_distancex;
	current_pose = current_pos_x;
	ROS_INFO("servo controller current_position = %f",current_pos_x);

        if(current_pos_x < servomaxx and current_pos_x > servomin ){

	    joint_state.header.stamp = ros::Time::now();
        joint_state.name[0] ="waist_pan_joint";
        joint_state.position[0] = 0;
        joint_state.name[1] ="head_roll_joint";
        joint_state.position[1] = 0;
        joint_state.name[2] ="head_tilt_joint";
        joint_state.position[2] = 0;
		joint_state.name[3] ="head_pan_joint";
        joint_state.position[3] = current_pose;
        joint_state.name[4] ="jaw_joint";
        joint_state.position[4] = 0;
        dynamixel_control.publish(joint_state);
	}
	
    }

    
    //Find out if the X component of the face is to the right of the middle of the screen.
    else if(x > center_right){

	ROS_INFO("Face is at Right");

	current_pos_x -= servo_step_distancex;
	current_pose = current_pos_x;

	ROS_INFO("servo controller current_position = %f",current_pos_x);

 	 if(current_pos_x < servomaxx and current_pos_x > servomin ){

		joint_state.header.stamp = ros::Time::now();
        joint_state.name[0] ="waist_pan_joint";
        joint_state.position[0] = 0;
        joint_state.name[1] ="head_roll_joint";
        joint_state.position[1] = 0;
        joint_state.name[2] ="head_tilt_joint";
        joint_state.position[2] = 0;
		joint_state.name[3] ="head_pan_joint";
        joint_state.position[3] = current_pose;
        joint_state.name[4] ="jaw_joint";
        joint_state.position[4] = 0;
        dynamixel_control.publish(joint_state);

        	dynamixel_control.publish(joint_state);
	}


    }

   else if(x > center_left and x < center_right){

	ROS_INFO("Face is at Center");
        
	}


}
//Callback of the topic /numbers
void face_callback(const face_tracker_control_newman::centroid::ConstPtr& msg)
{
	//ROS_INFO("Recieved X = [%d], Y = [%d]",msg->x,msg->y);
	
	//Calling track face function
	track_face(msg->x,msg->y);

}

int main(int argc, char **argv)
{

	
	//Initializing ROS node with a name of demo_topic_subscriber
	ros::init(argc, argv,"face_tracker_controller");
	//Created a nodehandle object
	ros::NodeHandle node_obj;
	//Create a publisher object
	ros::Subscriber number_subscriber = node_obj.subscribe("/face_centroid",10,face_callback);
        dynamixel_control = node_obj.advertise<sensor_msgs::JointState>("joint_states", 1);



	servomaxx = 0.5;   //max degree servo horizontal (x) can turn
	servomin = -0.5;
	screenmaxx = 640;   //max screen horizontal (x)resolution
	center_offset = 100;
	servo_step_distancex = 0.005; //x servo rotation steps
	current_pos_x = 0 ;

	  try{
	  node_obj.getParam("servomaxx", servomaxx);
	  node_obj.getParam("servomin", servomin);
	  node_obj.getParam("screenmaxx", screenmaxx);
	  node_obj.getParam("center_offset", center_offset);
	  node_obj.getParam("step_distancex", servo_step_distancex);

	  ROS_INFO("Successfully Loaded tracking parameters");
	  }


	  catch(int e)
	  {
	   
	      ROS_WARN("Parameters are not properly loaded from file, loading defaults");
	
	  }
	  center_left = (screenmaxx / 2) - center_offset;
	  center_right = (screenmaxx / 2) + center_offset;


	//Sending initial pose
	initial_pose = 0;

	joint_state.header.stamp = ros::Time::now();
        joint_state.name.resize(5);
        joint_state.position.resize(5);
        joint_state.name[0] ="waist_pan_joint";
        joint_state.position[0] = 0;
        joint_state.name[1] ="head_roll_joint";
        joint_state.position[1] = 0;
        joint_state.name[2] ="head_tilt_joint";
        joint_state.position[2] = 0;
		joint_state.name[3] ="head_pan_joint";
        joint_state.position[3] = initial_pose;
        joint_state.name[4] ="jaw_joint";
        joint_state.position[4] = 0;

        dynamixel_control.publish(joint_state);
	
	//Spinning the node
	ros::spin();
	return 0;
}


