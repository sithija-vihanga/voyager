from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument, GroupAction
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition, UnlessCondition

def generate_launch_description():
    
    wheel_radius_arg  = DeclareLaunchArgument(
        "wheel_radius",
        default_value= "0.33"
    )

    wheel_seperation_arg = DeclareLaunchArgument(
        "wheel_seperation",
        default_value= "0.15"
    )

    use_ros2_control_driver_arg = DeclareLaunchArgument(
        "use_ros2_control_driver" ,
        default_value= "True" 
    )

    wheel_radius        = LaunchConfiguration("wheel_radius")
    wheel_seperation    = LaunchConfiguration("wheel_seperation")
    use_ros2_control_driver = LaunchConfiguration("use_ros2_control_driver")

    joint_state_broadcaster_spawner = Node(
        package ="controller_manager",
        executable="spawner",
        arguments=[
            "joint_state_broadcaster",
            "--controller-manager",
            "/controller_manager"
        ]
    )

    diff_drive_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "diff_drive_controller",
            "--controller-manager",
            "/controller_manager"
        ],
        condition= IfCondition(use_ros2_control_driver)
    )



    base_controller = GroupAction(
        condition = UnlessCondition(use_ros2_control_driver),
        actions=[
            Node(
                package="controller_manager",
                executable="spawner",
                arguments=[
                "base_velocity_controller",
                "--controller-manager",
                "/controller_manager"
                ]),

            Node(
                package = "voyager_controller",
                executable= "base_controller",
                parameters=[{"wheel_radius": wheel_radius,
                            "wheel_seperation": wheel_seperation}
                ])
        ]
    )

    cam_controller = GroupAction(
        actions=[
            Node(
                package="controller_manager",
                executable="spawner",
                arguments=[
                    "camera_position_controller",
                    "--controller-manager",
                    "/controller_manager"
        ]),

            Node(
                package = "voyager_controller",
                executable= "cam_controller"
                )
        ]
    )

    # cam_controller = Node(
    #     package="controller_manager",
    #     executable="spawner",
    #     arguments=[
    #         "camera_velocity_controller",
    #         "--controller-manager",
    #         "/controller_manager"
    #     ]
    # )

    # position_controller = Node(
    #     package="controller_manager",
    #     executable="spawner",
    #     arguments=[
    #         "position_controller",
    #         "--controller-manager",
    #         "/controller_manager"
    #     ],
    #     condition= IfCondition(use_ros2_control_driver)
    # )

    return LaunchDescription([
        wheel_radius_arg,
        wheel_seperation_arg,
        use_ros2_control_driver_arg,
        joint_state_broadcaster_spawner,
        base_controller,
        diff_drive_controller,
        cam_controller
        #position_controller
    ])
    