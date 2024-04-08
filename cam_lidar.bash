#!/bin/bash

# Create a new tmux session
session_name="vint_locobot_$(date +%s)"
tmux new-session -d -s $session_name

# Split the window into four panes
tmux selectp -t 0    # select the first (0) pane
tmux splitw -h -p 50 # split it into two halves
tmux selectp -t 0    # go back to the first pane

# Run the roslaunch command in the first pane
tmux select-pane -t 0
tmux send-keys "export ROS_IP=192.168.1.170" Enter
tmux send-keys "roslaunch realsense2_camera rs_camera.launch initial_reset:=true enable_depth:=false" Enter
tmux send-keys "roslaunch vint_jackal_remote.launch" Enter

# Run the navigate.py script with command line args in the second pane
tmux select-pane -t 1
tmux send-keys "export ROS_IP=192.168.1.170" Enter
tmux send-keys 'roslaunch sick_scan sick_tim_5xx.launch frame_id:="front_laser"' Enter

tmux select-pane -t 0
# Attach to the tmux session
tmux -2 attach-session -t $session_name
