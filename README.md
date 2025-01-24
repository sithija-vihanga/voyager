# Voyager: Mobile robot platform for navigation research

This individual project is focused on developing mobile robot platform to explore existing state of the art algorithms for navigation and mapping and to get hands-on experience on developing the robot from scratch. Robot enclosure was designed in SolidWorks and 3D printed. Metal gear motors with wheel encoders have been used for as sensor input and togather with SLAM  localization, odometry is calculated. Robot consist of raspberry pi 5 and arduino portenta h7 dual core microcontroller for running ros and for low-level sensor configurations.

## Robot assembly



https://github.com/user-attachments/assets/df637b45-a97b-4d7f-b224-7457dc5c6243


## Resources
- LIDAR - Xiaomi s1 lidar
- Processing unit - Raspberry pi 5
- Microcontroller - Arduino portenta h7  lite
- Camera - 480p webcam connected to raspberry pi
- Motors - 150 rpm metal gear motors with hall effect wheel encoders
- Battery - 4 x Li-ion 18650 batteries
- Enclosure - custom design in solidworks
- Teleop - Bluetooth joystick

## Used frameworks:
- ROS2 - humble, jazzy
- nav2 stack
- SLAM
- Joy teleop
- ROS2-zenoh bridge

## Robot features:

- Autonomous navigation with nav2 stack and SLAM toolbox.
- Mappinng and localization
- Joystick based mannual tele-operation
- Communicating with server through ROS2 zenoh for data and map visualization
