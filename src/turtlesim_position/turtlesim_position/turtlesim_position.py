from typing import List
import rclpy           
from rclpy.context import Context
from rclpy.node import Node
from rclpy.parameter import Parameter
from std_msgs.msg import Float32
import math
from turtlesim.msg import Pose

class turtlesim_positionNode(Node):
    dicition = 0
    theta1 = 0
    def __init__(self) -> None:
        super().__init__("name")
        self.get_logger().info("我来，我发现，我记录")

        self.position = None
        self.sub_posision = self.create_subscription(Pose,"turtle1/pose",self.receive_position_callback,10)
    

    def receive_position_callback(self,msg):
        self.position = msg
        x = self.position.x
        y = self.position.y
        dicition = math.sqrt(x**2+y**2)
        theta1 = math.atan2(x,y)
        angle = math.degrees(theta1)
        self.get_logger().info("小乌龟离原点%f单位，角度是%f单位" % (dicition,angle))
    
def main(args=None):
    rclpy.init(args=args)
    node = turtlesim_positionNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()