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
#include "nav_msgs/Path.h"

//register this planner as a BaseGlobalPlanner plugin
PLUGINLIB_EXPORT_CLASS(global_planner::NomadGlobalPlanner, nav_core::BaseGlobalPlanner)

using namespace std;

//Default Constructor
namespace global_planner {

NomadGlobalPlanner::NomadGlobalPlanner (){

}

NomadGlobalPlanner::NomadGlobalPlanner(std::string name, costmap_2d::Costmap2DROS* costmap_ros){
  initialize(name, costmap_ros);
  ROS_INFO("nomad_planner init");
}


void NomadGlobalPlanner::initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros){
  // waypoints_sub = n.subscribe("nomad_dummy", 10, &NomadGlobalPlanner::waypoints_to_path, this);
  // path_pub = n.advertise<nav_msgs::Path>("nomad_path", 1);
  // goal_pub = n.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1);
  ac = new MoveBaseClient("my_client", false);
}

/* TODO< 
1. try with predefined paths as output
2. need a way for the global planner to set the plan itself

*/
void NomadGlobalPlanner::waypoints_to_path(const std_msgs::Float32MultiArray& msg){
  ROS_INFO("nomad_planner got waypoints");
  static uint32_t seq = 0;
  nav_msgs::Path path_out;
  path_out.header.frame_id = "odom";//??? TODO: make it an argument?
  path_out.header.seq = seq++; //maybe not needed
  path_out.header.stamp = ros::Time::now();
  for(int i = 0; i < msg.data.size(); i+=2){
    geometry_msgs::PoseStamped pose;
    pose.pose.position.x= msg.data[i]; 
    pose.pose.position.y= msg.data[i+1]; 
    pose.pose.orientation.w = 1; 
    // ROS_INFO("point [%f,%f]", pose.pose.position.x, pose.pose.position.y);
    path_out.poses.push_back(pose);
  }
  path_pub.publish(path_out);

  geometry_msgs::PoseStamped goal;
  goal.header.frame_id = "base_link";
  goal.header.stamp = ros::Time::now();

  // ROS_INFO("setting goal x%f y%f", msg.data[0], msg.data[1]);
  goal.pose.position.x = msg.data[0];
  goal.pose.position.y = msg.data[1];
  goal.pose.orientation.w = 1.0;

  ROS_INFO("Sending goal x%f y%f", goal.pose.position.x, goal.pose.position.y);
  // ac->sendGoal(goal);
  goal_pub.publish(goal);

  // ac->waitForResult();

  // if(ac->getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  //   ROS_INFO("Hooray, the base moved");
  // else
  //   ROS_INFO("The base failed to move");
  waypoints_sub.shutdown();

}

bool NomadGlobalPlanner::makePlan(const geometry_msgs::PoseStamped& start, const geometry_msgs::PoseStamped& goal,  std::vector<geometry_msgs::PoseStamped>& plan ){
  ROS_INFO("Making plan, goal x%f y%f", goal.pose.position.x, goal.pose.position.y);
  // waypoints_sub.shutdown();
  plan.push_back(start);
  plan.push_back(goal);
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
  // waypoints_sub = n.subscribe("nomad_dummy", 10, &NomadGlobalPlanner::waypoints_to_path, this);
  return true;
}
};