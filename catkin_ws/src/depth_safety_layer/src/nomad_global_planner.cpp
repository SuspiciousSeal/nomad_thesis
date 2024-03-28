// #include "ros/ros.h"
// #include "sensor_msgs/Range.h"
// #include "sensor_msgs/LaserScan.h"
// #include "std_msgs/Float32MultiArray.h"
// #include "nav_msgs/Path.h"
// #include "tf2/LinearMath/Quaternion.h"
// #include "tf2/LinearMath/Matrix3x3.h"
// #include "math.h"


// ros::Publisher  path_pub;
// ros::Subscriber waypoints_sub;
// ros::Subscriber reached_goal_sub;

// void waypoints_to_path(const std_msgs::Float32MultiArray& msg)
// {
//   static uint32_t seq = 0;
//   nav_msgs::Path path_out;
//   path_out.header.frame_id = "odom";//??? TODO: make it an argument?
//   path_out.header.seq = seq++; //maybe not needed
//   path_out.header.stamp = ros::Time::now();
  
//   for(int i = 0; i < msg.data.size(); i+=2){
//     geometry_msgs::PoseStamped pose;

//     pose.pose.position.x= msg.data[i]; 
//     pose.pose.position.y= msg.data[i+1]; 

//     path_out.poses.push_back(pose);
//   }

//   path_pub.publish(path_out);
// }


// int main(int argc, char **argv)
// {
//   ros::init(argc, argv, "nomad_to_path");
//   ros::NodeHandle n;
//   ros::Subscriber sub;
  
//   sub = n.subscribe("nomad_dummy", 10, waypoints_to_path);
//   path_pub = n.advertise<nav_msgs::Path>("nomad_path", 1);
//   // ros::Subscriber sub2 = n.subscribe("depthscan", 10, calc_depth);
//   ros::Rate loop_rate(10);
//   ROS_INFO("nomad_to_path ready");
//   ros::spin();
//   return 0;
// }
#include <pluginlib/class_list_macros.h>
#include "nomad_global_planner/nomad_global_planner.h"

//register this planner as a BaseGlobalPlanner plugin
PLUGINLIB_EXPORT_CLASS(global_planner::NomadGlobalPlanner, nav_core::BaseGlobalPlanner)

using namespace std;

//Default Constructor
namespace global_planner {

NomadGlobalPlanner::NomadGlobalPlanner (){

}

NomadGlobalPlanner::NomadGlobalPlanner(std::string name, costmap_2d::Costmap2DROS* costmap_ros){
  initialize(name, costmap_ros);
}


void NomadGlobalPlanner::initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros){
  waypoints_sub = n.subscribe("nomad_dummy", 10, &NomadGlobalPlanner::waypoints_to_path, this);

}
void NomadGlobalPlanner::waypoints_to_path(const std_msgs::Float32MultiArray& msg){
  ROS_INFO("nomad_planner got waypoints");
}

bool NomadGlobalPlanner::makePlan(const geometry_msgs::PoseStamped& start, const geometry_msgs::PoseStamped& goal,  std::vector<geometry_msgs::PoseStamped>& plan ){

  plan.push_back(start);
  static uint32_t seq = 0;
  // nav_msgs::Path path_out;
  // path_out.header.frame_id = "odom";//??? TODO: make 
  // path_out.header.seq = seq++; //maybe not needed
  // path_out.header.stamp = ros::Time::now();
  // for(int i = 0; i < msg.data.size(); i+=2){
  //   geometry_msgs::PoseStamped pose;
  //   pose.pose.position.x= msg.data[i]; 
  //   pose.pose.position.y= msg.data[i+1]; 
  //   path_out.poses.push_back(pose);
  // }
  // path_pub.publish(path_out);
  // plan.push_back(goal);
  return true;
}
};