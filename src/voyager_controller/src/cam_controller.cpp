#include "voyager_controller/cam_controller.hpp"

using std::placeholders::_1;

CamController::CamController(const std::string &name)
                                        :Node(name)
                                        , x_(0.0)
                                        , y_(0.0)
                                        , theta_(0.0)
{

    cam_cmd_pub_  = create_publisher<std_msgs::msg::Float64MultiArray>("/camera_position_controller/commands", 10);
    cam_vel_sub_  = create_subscription<geometry_msgs::msg::TwistStamped>("/camera_position_controller/cmd_vel", 10,
                        std::bind(&CamController::velCallback, this, _1));

}

void CamController::velCallback(const geometry_msgs::msg::TwistStamped &msg)
{
   
    std_msgs::msg::Float64MultiArray cam_speed_msgs;
    cam_speed_msgs.data.push_back(msg.twist.angular.z);

    cam_cmd_pub_ ->publish(cam_speed_msgs);
    //RCLCPP_INFO_STREAM(get_logger(), "Published z -axis velocity: " << msg.twist.angular.z);
}

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CamController>("camera_controller");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}