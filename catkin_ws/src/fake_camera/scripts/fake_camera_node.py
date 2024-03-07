#!/usr/bin/env python3

import rospkg
import rospy
import cv2
import cv_bridge
from sensor_msgs.msg import Image

from os import listdir
from os.path import isfile, join

PATH = "/home/robert/visualnav-transformer/datasets/recon/jackal_2019-08-02-16-23-30_0_r00/"

def get_img_file_paths(path):
  return [f for f in listdir(path) if isfile(join(path, f)) and f[-4:] == ".jpg"]

def talker():
  pub = rospy.Publisher("/usb_cam/image_raw", Image, queue_size=1)
  rospy.init_node("fake_camera", anonymous=True)
  rate = rospy.Rate(1)
  bridge = cv_bridge.CvBridge()
  img_names = get_img_file_paths(PATH)
  img_names.sort(key=lambda f: int(''.join(filter(str.isdigit, f))))
  rospy.loginfo(f"img shape is {img_names}")
  while not rospy.is_shutdown():
    for i in img_names:
      img = cv2.imread(PATH + i, cv2.IMREAD_ANYCOLOR)
      msg = bridge.cv2_to_imgmsg(img, encoding="passthrough")
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