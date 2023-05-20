#!/usr/bin/env python3


import rospy
from std_msgs.msg import Int32



def talker():
    pub = rospy.Publisher('velocidad_motores', Int32, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        velocidad =rospy.get_param()
        rospy.loginfo(velocidad)
        pub.publish(velocidad)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass