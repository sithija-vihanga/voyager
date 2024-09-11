# Voyager: Mobile robot platform for navigation research

This repo is based on building a mobile robot based on ROS2-humble with camera based navigation using SLAM toolBox for localization without use of LIDARs. Also it is developing with the purposes of conducting navigation and manipulation based research in mobile robots mainly addressing the current limitations like crowd navigation.

# Resources

/Meshes directory contains 3D printable enclosure designed for the robot providing more space and reconfigurability for new sensors and actuators which will be added as future works of this project.

# Robot features:

- Robot has autonomous and manual controls using SLAM and navigation stack.
- Odometry is setuped with sensor fusion of wheel encoders and IMU data to avoid slipping of the robot.
- For navigation it uses 4 wheel differential drive.
