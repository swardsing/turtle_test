#include"rclcpp/rclcpp.hpp"
#include"turtlesim/msg/pose.hpp"
#include <cmath>

using std::placeholders::_1;

class positionNode: public rclcpp::Node

{
private:
    //申明话题订阅者
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub_position ;
    //创建回调函数
    void position_call_back(const turtlesim::msg::Pose::SharedPtr msg)
    {
         x_=msg->x;
         y_=msg->y;
         double length=std::sqrt(x_*x_+y_*y_);
         double rad1=std::atan2(y_,x_);
         double angle=std::round(rad1*180/M_PI);
         RCLCPP_INFO(get_logger(),"海龟偏离了%lf单位，离原点%lf单位",angle,length);
    }

public:
 /*   void timer_callback()
            {
                
                // do something else;
            };

        rclcpp::TimerBase::SharedPtr timer;
        timer = this->create_wall_timer(1s, timer_callback);
*/
                        
    positionNode():Node("position_turtle")
    {
         sub_position = this->create_subscription<turtlesim::msg::Pose>("turtle1/pose",10,std::bind(&positionNode::position_call_back,this,_1));
                                                                        
    }
    float x_,y_;
    
};

int main(int argc,char ** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<positionNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;

}
