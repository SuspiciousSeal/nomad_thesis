#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import Image
from std_msgs.msg import Float32MultiArray
from geometry_msgs.msg import PoseStamped, Quaternion
import tf.transformations

def talker():
  pub = rospy.Publisher("/nomad_path", Float32MultiArray, queue_size=1)
  goal_pub = rospy.Publisher("move_base_simple/goal", PoseStamped, queue_size=1)
  rospy.init_node("nomad_dummy", anonymous=True)
  rate = rospy.Rate(1)
  rospy.loginfo(f"Starting nomad_dummy")
  while not rospy.is_shutdown():
    msg = Float32MultiArray()
    msg.data = [0.3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    print("sending data", msg.data)
    pub.publish(msg)
    # msg2 = PoseStamped()
    # msg2.header.frame_id = "base_link"
    # msg2.header.stamp = rospy.Time.now()
    # msg2.pose.position.x = 1
    # msg2.pose.position.y = 1
    # msg2.pose.orientation.w = 1
    
    # goal_pub.publish(msg2)
    rate.sleep()
    # rospy.signal_shutdown("end")
  

if __name__ == '__main__':
  try:
    talker()
  except rospy.ROSInterruptException:
    print("ROSInterruptException")
    pass
  except Exception as e:
    print("Fake camera error", e)