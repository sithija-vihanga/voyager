#include "voyager_controller/base_controller.hpp"
#include <Eigen/Geometry>

using std::placeholders::_1;

BaseController::BaseController(const std::string &name):Node(name)
{
    declare_parameter("wheel_radius", 0.033);
    declare_parameter("wheel_seperation", 0.15);

    wheel_radius_       = get_parameter("wheel_radius").as_double();
    wheel_seperation_   = get_parameter("wheel_seperation").as_double();

    RCLCPP_INFO_STREAM(get_logger(), "using wheel radius " <<wheel_radius_);
    RCLCPP_INFO_STREAM(get_logger(), "using wheel seperation " <<wheel_seperation_);

    wheel_cmd_pub_  = create_publisher<std_msgs::msg::Float64MultiArray>("/base_velocity_controller/commands", 10);
    vel_sub_        = create_subscription<geometry_msgs::msg::TwistStamped>("/voyager_controller/cmd_vel", 10,
                        std::bind(&BaseController::velCallback, this, _1));
    
    speed_conversion_ << wheel_radius_/2, wheel_radius_/2, wheel_radius_/wheel_seperation_, -wheel_radius_/wheel_seperation_;

    RCLCPP_INFO_STREAM(get_logger(), "The conversion matrix is \n" << speed_conversion_);

}

void BaseController::velCallback(const geometry_msgs::msg::TwistStamped &msg)
{
    Eigen::Vector2d robot_speed(msg.twist.linear.x, msg.twist.angular.z);
    Eigen::Vector2d wheel_speed = speed_conversion_.inverse() * robot_speed;

    std_msgs::msg::Float64MultiArray wheel_speed_msgs;
    wheel_speed_msgs.data.push_back(wheel_speed.coeff(1));
    wheel_speed_msgs.data.push_back(wheel_speed.coeff(0));
    wheel_speed_msgs.data.push_back(wheel_speed.coeff(1));
    wheel_speed_msgs.data.push_back(wheel_speed.coeff(0));

    wheel_cmd_pub_ ->publish(wheel_speed_msgs);
}

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<BaseController>("base_controller");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}