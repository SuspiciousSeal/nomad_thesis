#!/bin/bash

# Simple script to setup your machine env to use a remote ROS master
# example usage: use_robot.sh myrobot
# where myrobot is a resolvable hostname or an IP address

NORMAL=`tput sgr0 2> /dev/null`
GREEN=`tput setaf 2 2> /dev/null`

# get the IP of our device we'll use to conect to the host
# TARGET_IP=$1
TARGET_IP=192.168.1.170
IP=`ip route get $TARGET_IP | head -n 1 | sed "s/.*src \(\S*\) .*/\1/"`

echo -e "${GREEN}using $1 ($TARGET_IP) via $IP${NORMAL}"

source ./catkin_ws/devel/setup.bash
#export ROS_MASTER_URI=http://$TARGET_IP:11311
#export ROS_HOSTNAME=$IP
export ROS_IP=$TARGET_IP
