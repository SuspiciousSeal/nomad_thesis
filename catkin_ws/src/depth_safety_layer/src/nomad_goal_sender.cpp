#include "ros/ros.h"
#include <signal.h>
#include "std_msgs/Float32MultiArray.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/PoseStamped.h"
#include "actionlib_msgs/GoalID.h"
#include <tf/transform_listener.h>

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

ros::Subscriber sub;
// tf::TransformListener listener;
ros::Publisher pub;
ros::Publisher cancel_pub;


typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
MoveBaseClient* ac;

void mySigintHandler(int sig)
{
  ac->cancelAllGoals();
  
  // All the default sigint handler does is call shutdown()
  ROS_WARN("mySigintHandler");
  ros::shutdown();
}

void send_goal(const std_msgs::Float32MultiArray& msg){
  // geometry_msgs::PoseStamped goal;
  // goal.header.frame_id = "camera_link";
  // goal.header.stamp = ros::Time::now();
  // try{
  //   // tf::StampedTransform transform;
  //   // listener.lookupTransform("/odom", "/camera_link", ros::Time(0), transform);
  //   // ROS_INFO("setting goal x%f y%f", msg.data[0], msg.data[1]);
  //   goal.pose.position.x = msg.data[0];
  //   goal.pose.position.y = msg.data[1];
  //   goal.pose.orientation.w = 1.0;

  //   ROS_INFO("Sending goal x%f y%f", goal.pose.position.x, goal.pose.position.y);
  //   // ac->sendGoal(goal);
  //   pub.publish(goal);

  // } catch(...){
  //   ROS_INFO("goal error");

  // }

  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot to move 1 meter forward
  // goal.target_pose.header.frame_id = "base_link";
  goal.target_pose.header.frame_id = "camera_link";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = msg.data[6];
  goal.target_pose.pose.position.y = msg.data[7];
  goal.target_pose.pose.orientation.w = 1.0;

  ROS_INFO("Sending goal");
  ac->sendGoal(goal);

  // ac->waitForResult(ros::Duration(10, 0));

  // if(ac->getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  //   ROS_INFO("Hooray, the base moved 0.2 meter forward");
  // else
  //   ROS_INFO("The base failed to move forward 0.2 meter for some reason");

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "wp_to_goal");
  ros::NodeHandle n;
  ros::Subscriber sub;
  sub = n.subscribe("/nomad_path", 1, send_goal);
  pub = n.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1);
  // cancel_pub = n.advertise<actionlib_msgs/GoalID>("/move_base/cancel", 1);
  ac = new MoveBaseClient("move_base", true);

  signal(SIGINT, mySigintHandler);

  // ros::Subscriber sub2 = n.subscribe("depthscan", 10, calc_depth);
  ros::Rate loop_rate(10);
  ROS_INFO("wp_to_goal ready");

   while(!ac->waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }


  ros::spin();
  return 0;
}
