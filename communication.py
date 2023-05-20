#!/usr/bin/env python3

import rospy
import socket
from std_msgs.msg import Float32
import sys, select, termios, tty


HOST = "192.168.68.100"
PORT = 80

s = socket.socket()
print("Socket Created")
s.connect((HOST, PORT))
print("socket binded to ip %s port %s "%(HOST,PORT))

def moverRobot():
    while(True):
        key = getKey()
        print(key)
        if (key == 'w'):
            dataSend = str(1.0)
            s.sendall(dataSend.encode())
        elif (key == 'a'):
            dataSend = str(3.0)
            s.sendall(dataSend.encode())
        elif (key == 'd'):
            dataSend = str(4.0)
            s.sendall(dataSend.encode())
        elif (key == 's'):
            dataSend = str(2.0)
            s.sendall(dataSend.encode())
        elif (key == 'p'):
            dataSend = str(5.0)
            s.sendall(dataSend.encode())
        else:
            dataSend = str(5.0)
            s.sendall(dataSend.encode())

    
def getKey():
	tty.setraw(sys.stdin.fileno())
	select.select([sys.stdin], [], [], 0)
        
	key = sys.stdin.read(1)
	termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
	return key



def main():
    rospy.init_node("socket")
    rospy.Publisher("direccion",Float32, queue_size=10)
    moverRobot()
    rospy.spin()
    s.close()

if __name__ == "__main__":
    settings = termios.tcgetattr(sys.stdin)
    main()
