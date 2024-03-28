#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import Image
from std_msgs.msg import Float32MultiArray

def talker():
  pub = rospy.Publisher("/nomad_dummy", Float32MultiArray, queue_size=1)
  rospy.init_node("nomad_dummy", anonymous=True)
  rate = rospy.Rate(1)
  rospy.loginfo(f"Starting nomad_dummy")
  while not rospy.is_shutdown():
    msg = Float32MultiArray()
    msg.data = [0.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    pub.publish(msg)
    rate.sleep()


if __name__ == '__main__':
  try:
    talker()
  except rospy.ROSInterruptException:
    print("ROSInterruptException")
    pass
  except Exception as e:
    print("Fake camera error", e)