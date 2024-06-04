#include <costmap_2d/costmap_2d_ros.h>
#include <dwa_local_planner/dwa_planner_ros.h>
#include "nav_msgs/Path.h"

#if ROS_VERSION_MINIMUM(1, 16, 0)
#define ROS_IS_NOETIC 1
#include <tf2_ros/buffer.h>
#else
#include <tf/transform_listener.h>
#endif

void execute_path(const nav_msgs::Path& msg){

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "nomad_dwa_node");
  ros::NodeHandle n;
  ros::Subscriber sub;
  sub = n.subscribe("nomad_path", 10, execute_path);


  // ros::Subscriber sub2 = n.subscribe("depthscan", 10, calc_depth);
  ros::Rate loop_rate(10);
  ROS_INFO("nomad_dwa_node ready");

  #if ROS_IS_NOETIC
  tf2_ros::Buffer tf(ros::Duration(10));
  #else
  tf::TransformListener tf(ros::Duration(10));
  #endif

  costmap_2d::Costmap2DROS costmap("my_costmap", tf);

  dwa_local_planner::DWAPlannerROS dp;
  dp.initialize("my_dwa_planner", &tf, &costmap);

  costmap.start();

  ros::spin();
  return 0;
}
