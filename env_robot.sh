#!/bin/bash

export ROS_MASTER_URI=http://robot-user:11311

source /opt/ros/noetic/setup.bash
source /home/ubuntu/catkin_ws/devel/setup.bash

exec "$@"
