# nomad_thesis

This is the repo for my master's thesis "Validation of NoMaD as a Global Planner for Mobile Robots" and used a Clearpath Jackal robot with a Sick TIM551 LiDAR and a Intel RealSense D435i camera.

## Installation
* Most software requirements are described in visualnav-transformer, which contains NoMaD.
* tmux is required to run some scripts.
1. Download this repo for both your computer and robot.
2. Initialize submodules. Visualnav-transformer is not required on your robot.
3. Follow the steps in the visualnav-transformer instructions to install software required by NoMaD on your computer with an appropriate CUDA capable GPU.


## Running
1. Connect over SSH to your robot.
  * See how to create the topological map in the visualnav-transformer repo. The topologial map is used to guide the navigation mode of NoMaD.
2. Run the script "local.bash" on the robot to start the camera and LiDAR nodes (assuming your robot has a Realsense camera and SICK TIM551 LiDAR) and the node interfacing between NoMaD and the robot.
3. Run the script "navigate_wo_c.sh --model nomad --dir <topomap_dir>" on your computer to run NoMaD without its PD controller to run the solution developed in this thesis OR run the script "navigate.sh --model nomad --dir <topomap_dir>" to run regular NoMaD.