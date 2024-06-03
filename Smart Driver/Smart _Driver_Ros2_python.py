#!/usr/bin/env python3

import rclpy
from rclpy.node import Node 
from custom_messages.msg import MotorCommand, MotorFeedback
import struct


class MotorNode(Node):

    def __init__(self):
        super().__init__('motor_node')
        self.motor_publisher = self.create_publisher(MotorCommand, '/publish_motor', 10)
        self.encoder_subscriber = self.create_subscription(MotorFeedback, '/motor_feedback', self.encoder_feedback, 10)
        self.motor_feedback_id = 0
        self.position = 0.0
        self.speed = 0.0
        self.timer = self.create_timer(0.01, self.timer_callback)

    def timer_callback(self):
        motor_message = MotorCommand()
        motor_message.motor_id = 1 #Id of target motor
        motor_message.goal = 5.0
        motor_message.speedmode = True 
        #speed mode = True -> velocity control mode (goal = desired speed)
        #speed mode = False -> position control mode (goal = desired position)

        motor_message.voltagemode = False #Override speedmode if true
        #voltage mode = True -> voltage control mode (goal = voltage)

        self.motor_publisher.publish(motor_message)

    def encoder_feedback(self, msg):
        self.motor_feedback_id = 255 - msg.motor_id #For example, motor 1 should feedback encoder with ID 254
        self.position = msg.position
        self.speed = msg.speed

def main(args=None):
    rclpy.init(args=args)
    motor_node = MotorNode()
    rclpy.spin(motor_node)
    motor_node.destroy_node()
    rclpy.shutdown()

if __name__== '__main__':
    main()
        