from launch import LaunchDescription
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition, UnlessCondition
import os

def generate_launch_description():

    use_imu_republisher_arg = DeclareLaunchArgument(
        "use_imu_republisher",
        default_value= "False"
    )

    use_ekf_tf_publisher_arg = DeclareLaunchArgument(
        "use_ekf_tf_publisher",
        default_value= "False"
    )

    use_imu_republisher   = LaunchConfiguration("use_imu_republisher")
    use_ekf_tf_publisher  = LaunchConfiguration("use_ekf_tf_publisher")


    static_transform_publisher = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        arguments=["--x", "0", "--y", "0","--z", "0.103",
                   "--qx", "1", "--qy", "0", "--qz", "0", "--qw", "0",
                   "--frame-id", "base_footprint_ekf",
                   "--child-frame-id", "imu_link_ekf"],
        condition= IfCondition(use_ekf_tf_publisher)
    )

    robot_localization = Node(
        package="robot_localization",
        executable="ekf_node",
        name="ekf_filter_node",
        output="screen",
        parameters=[os.path.join(get_package_share_directory("voyager_localization"), "config", "ekf.yaml")],
    )


    imu_republisher = Node(
        package="voyager_localization",
        executable="imu_republisher",
        condition= IfCondition(use_imu_republisher)
    )

    return LaunchDescription([
        use_imu_republisher_arg,
        use_ekf_tf_publisher_arg,
        static_transform_publisher,
        robot_localization,
        imu_republisher  
    ])