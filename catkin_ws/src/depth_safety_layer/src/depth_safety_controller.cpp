#include "ros/ros.h"
#include "sensor_msgs/Range.h"
#include "sensor_msgs/LaserScan.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"
#include "math.h"

ros::Publisher depth_centre_pub;
ros::Publisher depth_left_pub;
ros::Publisher depth_right_pub;

float get_min_range(std::vector<float> ranges, int start, int length, float range_min, float range_max){
  float ret = range_max;
  for(int i = start; i < (start + length); i++){
    if((ranges[i] < ret) && (ranges[i] >= range_min)) ret = ranges[i];
  }
  return ret;
}

void calc_depth(const sensor_msgs::LaserScan& msg)
{
  static uint32_t seq = 0;
  // ROS_INFO("received laserscan %ld scans, anglemin %f, anglemax %f", msg.ranges.size(), msg.angle_min, msg.angle_max);
  sensor_msgs::Range range_msg_out;
  std_msgs::Header h;
  h.stamp = msg.header.stamp;
  h.seq = seq++;

  const float sector_width = M_PI / 180 * 25;
  int points_per_sector = sector_width / msg.angle_increment;
  //these get the amount of points between angle min and leftmost angle of range object
  //ceil bc otherwise it will round down and take a point that is out of the sector
  int first_left_point =  ceil(((-sector_width - (sector_width / 2) - msg.angle_min)) / msg.angle_increment);
  int first_mid_point =   ceil(((0 - (sector_width / 2)) - msg.angle_min) / msg.angle_increment);
  int first_right_point = ceil(((sector_width - (sector_width / 2)) - msg.angle_min ) / msg.angle_increment);
  // ROS_INFO("fpl %d %f, fpm %d %f, fpr %d %f", first_left_point,  (first_left_point  * msg.angle_increment + msg.angle_min) * 180/M_PI, 
  //                                             first_mid_point,   (first_mid_point   * msg.angle_increment + msg.angle_min) * 180/M_PI,
  //                                             first_right_point, (first_right_point * msg.angle_increment + msg.angle_min) * 180/M_PI);
  //left  -25 +-12.5 deg
  //mid     0 +-12.5 deg
  //right  25 +-12.5 deg

  float left_min = get_min_range(msg.ranges, first_left_point, points_per_sector, msg.range_min, msg.range_max);
  float mid_min = get_min_range(msg.ranges, first_mid_point, points_per_sector, msg.range_min, msg.range_max);
  float right_min = get_min_range(msg.ranges, first_right_point, points_per_sector, msg.range_min, msg.range_max);

  range_msg_out.range = mid_min;
  range_msg_out.field_of_view = sector_width;
  range_msg_out.max_range = msg.range_max;
  range_msg_out.min_range = msg.range_min;
  range_msg_out.radiation_type = 0;
  h.frame_id = "Range_mid";//set the transform name of the range
  range_msg_out.header = h;
  depth_centre_pub.publish(range_msg_out);
  h.frame_id = "Range_left";
  range_msg_out.range = left_min;
  range_msg_out.header = h;
  depth_left_pub.publish(range_msg_out);
  h.frame_id = "Range_right";
  range_msg_out.range = right_min;
  range_msg_out.header = h;
  depth_right_pub.publish(range_msg_out);
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "rangefinder");
  ros::NodeHandle n;
  std::string sensor_select = "lidar";
  if(n.getParam("server_source", sensor_select))
  {
    ROS_INFO("server param was %s", sensor_select.c_str());
  }
  ros::Subscriber sub;
  
  ROS_INFO("starting rangefinder");

  depth_centre_pub = n.advertise<sensor_msgs::Range>("distance_to_obstacle/centre", 1);
  depth_left_pub = n.advertise<sensor_msgs::Range>("distance_to_obstacle/left", 1);
  depth_right_pub = n.advertise<sensor_msgs::Range>("distance_to_obstacle/right", 1);
  if(sensor_select.compare("camera") == 0)
  {
    sub = n.subscribe("depthscan", 10, calc_depth);
    ROS_INFO("Subscribed to depthscan");
  } else {
    sub = n.subscribe("scan", 10, calc_depth);
    ROS_INFO("Subscribed to scan");
  }
  // ros::Subscriber sub2 = n.subscribe("depthscan", 10, calc_depth);
  ros::Rate loop_rate(10);
  ROS_INFO("rangefinder ready");
  ros::spin();
  return 0;
}
