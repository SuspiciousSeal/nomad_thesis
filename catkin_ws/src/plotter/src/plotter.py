import numpy as np
from matplotlib import pyplot as plt
from matplotlib.patches import Rectangle
import rospy
from std_msgs.msg import Bool, Float32MultiArray
from sensor_msgs.msg import Range

box_dist = 0
def set_distance(msg: Range):
    global box_dist
    box_dist = msg.range
def plot_x(msg):
    global box_dist
    global counter, f

    if f == None:
      f = plt.figure(figsize=(10,10))
    if counter % 10 == 0:
        data = list(msg.data)
        data.insert(0, 0)
        data.insert(0, 0)
        data = np.array(data)
        print(data)
        data = data.reshape(9,2)
        print(data)
        f.clf()
        plt.plot(data[:,0], data[:,1])
        plt.xlim(0, 5)
        plt.ylim(-2.5, 2.5)
        box_center = [box_dist + 0.20, 0]
        box = [box_center[0] - 0.20, box_center[1] - 0.20]
        print("box is", box)
        f.gca().add_patch(Rectangle(box, 0.4, 0.4, color='brown'))
        f.canvas.draw()
        plt.pause(0.00000000001)

    counter += 1

if __name__ == '__main__':
    counter = 0
    f = None
    rospy.init_node("plotter")
    rospy.Subscriber("/nomad_path", Float32MultiArray, plot_x)
    rospy.Subscriber("/distance_to_obstacle/centre", Range, set_distance)
    plt.ion()
    plt.show()
    rospy.spin()