#include "ros/ros.h"
#include "sensor_msgs/Range.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/Float32MultiArray.h"
#include "nav_msgs/Path.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"
#include "math.h"


ros::Publisher  path_pub;
ros::Subscriber waypoints_sub;
ros::Subscriber reached_goal_sub;

void waypoints_to_path(const std_msgs::Float32MultiArray& msg)
{
  static uint32_t seq = 0;
  nav_msgs::Path path_out;
  path_out.header.frame_id = "odom";//??? TODO: make it an argument?
  path_out.header.seq = seq++; //maybe not needed
  path_out.header.stamp = ros::Time::now();
  
  for(int i = 0; i < msg.data.size(); i+=2){
    geometry_msgs::PoseStamped pose;

    pose.pose.position.x= msg.data[i]; 
    pose.pose.position.y= msg.data[i+1]; 

    path_out.poses.push_back(pose);
  }

  path_pub.publish(path_out);
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "nomad_to_path");
  ros::NodeHandle n;
  ros::Subscriber sub;
  
  sub = n.subscribe("nomad_dummy", 10, waypoints_to_path);
  path_pub = n.advertise<nav_msgs::Path>("nomad_path", 1);
  // ros::Subscriber sub2 = n.subscribe("depthscan", 10, calc_depth);
  ros::Rate loop_rate(10);
  ROS_INFO("nomad_to_path ready");
  ros::spin();
  return 0;
}
