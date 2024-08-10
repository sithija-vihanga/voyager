#ifndef CAMERA_TF_KINEMATICS_HPP
#define CAMERA_TF_KINEMATICS_HPP

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/exceptions.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <memory>

#include "voyager_msgs/srv/get_transform.hpp"

class CameraTFKinematics : public rclcpp::Node
{
    public:
        CameraTFKinematics(const std::string& name);
    
    private:
        void timerCallback();

        bool getTransformCallback(const std::shared_ptr<voyager_msgs::srv::GetTransform::Request> req,
                                  const std::shared_ptr<voyager_msgs::srv::GetTransform::Response> res);
        
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Service<voyager_msgs::srv::GetTransform>::SharedPtr get_transform_srv_;

        std::unique_ptr<tf2_ros::TransformBroadcaster> dynamic_tf_broadcaster_;
        geometry_msgs::msg::TransformStamped dynamic_transform_stamped_;
        double last_theta_;
        double theta_incement_;
        int rotations_counter_;

        std::shared_ptr<tf2_ros::TransformListener>tf_listener_{nullptr};
        std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
        tf2::Quaternion last_orientation_;
        tf2::Quaternion orientation_increment_;


};

#endif