#!/bin/bash

# Create a new tmux session
session_name="simulate_$(date +%s)"
tmux new-session -d -s $session_name

# Split the window into four panes
tmux selectp -t 0    # select the first (0) pane
tmux splitw -h -p 50 # split it into two halves
tmux selectp -t 0    # select the first (0) pane
tmux splitw -v -p 50 # split it into two halves

tmux selectp -t 2    # select the new, second (2) pane
tmux splitw -v -p 50 # split it into two halves
tmux selectp -t 0    # go back to the first pane

# Run the roslaunch command in the first pane
tmux select-pane -t 0
tmux send-keys "roscore" Enter
sleep 5

# Run the navigate.py script with command line args in the second pane
tmux select-pane -t 1
# tmux send-keys "conda activate vint_deployment" Enter
# tmux send-keys "source ~/nomad_thesis/catkin_ws/devel/setup.bash" Enter
tmux send-keys "roslaunch jackal_gazebo empty_world.launch config:=front_laser" Enter
sleep 5

# Run the teleop.py script in the third pane
tmux select-pane -t 2
# tmux send-keys "conda activate vint_deployment" Enter
tmux send-keys "roslaunch jackal_viz view_robot.launch config:=navigation" Enter

# Run the pd_controller.py script in the fourth pane
tmux select-pane -t 3
# tmux send-keys "roslaunch jackal_navigation odom_navigation_demo.launch" Enter
tmux send-keys "source ~/nomad_thesis/catkin_ws/devel/setup.bash" Enter
tmux send-keys "roslaunch depth_safety_layer nomad_gp_sim.launch" Enter

# Attach to the tmux session
tmux -2 attach-session -t $session_name
