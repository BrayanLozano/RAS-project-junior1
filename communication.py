#!/usr/bin/env python3

import rospy
import socket
from std_msgs.msg import Float32


HOST = "192.168.68.108"
PORT = 80

s = socket.socket()
print("Socket Created")
s.connect((HOST, PORT))
print("socket binded to ip %s port %s "%(HOST,PORT))

def moverRobot(data):
    dataSend = str(data.data)
    s.sendall(dataSend.encode())
    




def main():
    rospy.init_node("socket")
    rospy.Subscriber("direccion",Float32, moverRobot)
    rospy.spin()
    s.close()

if __name__ == "__main__":
    main()
