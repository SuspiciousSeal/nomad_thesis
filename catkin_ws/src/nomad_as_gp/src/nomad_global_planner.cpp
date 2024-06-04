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
  
}

bool NomadGlobalPlanner::makePlan(const geometry_msgs::PoseStamped& start, const geometry_msgs::PoseStamped& goal,  std::vector<geometry_msgs::PoseStamped>& plan ){
  ROS_INFO("Making plan, goal x%f y%f w%f, frame id:%s", goal.pose.position.x, goal.pose.position.y, goal.pose.orientation.w, goal.header.frame_id.c_str());
  plan.push_back(start);
  plan.push_back(goal);

  return true;
}
};