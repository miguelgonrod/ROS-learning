#!/usr/bin/env python3

import rclpy
from rclpy.node import Node

from example_interfaces.msg import Int64


class NumberCounterNode(Node):
    def __init__(self):
        super().__init__('number_counter')
        
        self.subscriber_ = self.create_subscription(Int64, "number", self.callback_number_publisher, 10)
        self.counter_ = 0
        
        self.publisher_ = self.create_publisher(Int64, "number_count", 10)
        self.timer_ =  self.create_timer(0.5, self.publishCounter)
        
        self.get_logger().info("Number Counter has been started")
        
    def callback_number_publisher(self, msg):
        self.counter_ += msg.data
        
    def publishCounter(self):
        msg = Int64()
        msg.data = self.counter_
        self.publisher_.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = NumberCounterNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == '__main__':
    main()
