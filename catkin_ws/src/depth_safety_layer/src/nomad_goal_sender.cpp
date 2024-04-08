#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/PoseStamped.h"

ros::Subscriber sub;
ros::Publisher pub;


void send_goal(const std_msgs::Float32MultiArray& msg){
  geometry_msgs::PoseStamped goal;
  goal.header.frame_id = "base_link";
  goal.header.stamp = ros::Time::now();

  // ROS_INFO("setting goal x%f y%f", msg.data[0], msg.data[1]);
  goal.pose.position.x = msg.data[0];
  goal.pose.position.y = msg.data[1];
  goal.pose.orientation.w = 1.0;

  ROS_INFO("Sending goal x%f y%f", goal.pose.position.x, goal.pose.position.y);
  // ac->sendGoal(goal);
  pub.publish(goal);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "wp_to_goal");
  ros::NodeHandle n;
  ros::Subscriber sub;
  sub = n.subscribe("/nomad_path", 1, send_goal);
  pub = n.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1);


  // ros::Subscriber sub2 = n.subscribe("depthscan", 10, calc_depth);
  ros::Rate loop_rate(10);
  ROS_INFO("wp_to_goal ready");


  ros::spin();
  return 0;
}
