#include "voyager_firmware/voyager_interface.hpp"
#include <hardware_interface/types/hardware_interface_type_values.hpp>
#include <pluginlib/class_list_macros.hpp>


namespace voyager_firmware
{

const char* VoyagerInterface::wheel_joints[4] = { 
    "wheel_front_left_joint", 
    "wheel_front_right_joint", 
    "wheel_rear_left_joint", 
    "wheel_rear_right_joint"
};

VoyagerInterface::VoyagerInterface()
{
}

VoyagerInterface::~VoyagerInterface()
{
  if (arduino_.IsOpen())
  {
    try
    {
      arduino_.Close();
    }
    catch (...)
    {
      RCLCPP_FATAL_STREAM(rclcpp::get_logger("VoyagerInterface"),
                          "Something went wrong while closing connection with port " << port_);
    }
  }
}


CallbackReturn VoyagerInterface::on_init(const hardware_interface::HardwareInfo &hardware_info)
{
  CallbackReturn result = hardware_interface::SystemInterface::on_init(hardware_info);
  if (result != CallbackReturn::SUCCESS)
  {
    return result;
  }

  try
  {
    port_ = info_.hardware_parameters.at("port");
  }
  catch (const std::out_of_range &e)
  {
    RCLCPP_FATAL(rclcpp::get_logger("VoyagerInterface"), "No Serial Port provided! Aborting");
    return CallbackReturn::FAILURE;
  }

  position_commands_.reserve(info_.joints.size());
  velocity_commands_.reserve(info_.joints.size());
  position_states_.reserve(info_.joints.size());
  velocity_states_.reserve(info_.joints.size());
  last_run_ = rclcpp::Clock().now();

  return CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::StateInterface> VoyagerInterface::export_state_interfaces()
{
  std::vector<hardware_interface::StateInterface> state_interfaces;
 
  // Provide only a position Interafce
  for (size_t i = 0; i < 4; i++)
  {
    state_interfaces.emplace_back(hardware_interface::StateInterface(
        wheel_joints[i], hardware_interface::HW_IF_POSITION, &position_states_[i]));
    state_interfaces.emplace_back(hardware_interface::StateInterface(
        wheel_joints[i], hardware_interface::HW_IF_VELOCITY, &velocity_states_[i]));
  }
  state_interfaces.emplace_back(hardware_interface::StateInterface(
        "camera_base_joint", hardware_interface::HW_IF_POSITION, &position_states_[4]));

  state_interfaces.emplace_back(hardware_interface::StateInterface(
        "camera_base_joint", hardware_interface::HW_IF_VELOCITY, &velocity_states_[4]));


  return state_interfaces;
}


std::vector<hardware_interface::CommandInterface> VoyagerInterface::export_command_interfaces()
{
  std::vector<hardware_interface::CommandInterface> command_interfaces;

  // Provide only a velocity Interafce
  for (size_t i = 0; i < 4; i++)
  {
    command_interfaces.emplace_back(hardware_interface::CommandInterface(
        wheel_joints[i], hardware_interface::HW_IF_VELOCITY, &velocity_commands_[i]));
  }
  command_interfaces.emplace_back(hardware_interface::CommandInterface(
        "camera_base_joint", hardware_interface::HW_IF_POSITION, &position_commands_[0]));

  return command_interfaces;
}


CallbackReturn VoyagerInterface::on_activate(const rclcpp_lifecycle::State &)
{
  RCLCPP_INFO(rclcpp::get_logger("VoyagerInterface"), "Starting robot hardware ...");

  // Reset commands and states
  position_commands_    = { 0.0, 0.0, 0.0, 0.0, 0.0};
  velocity_commands_    = { 0.0, 0.0, 0.0, 0.0, 0.0};
  position_states_      = { 0.0, 0.0, 0.0, 0.0, 0.0};
  velocity_states_      = { 0.0, 0.0, 0.0, 0.0, 0.0};

  try
  {
    arduino_.Open(port_);
    arduino_.SetBaudRate(LibSerial::BaudRate::BAUD_115200);
    RCLCPP_INFO(rclcpp::get_logger("VoyagerInterface"), "Serial port opened successfully.");
  }
  catch (...)
  {
    RCLCPP_FATAL_STREAM(rclcpp::get_logger("VoyagerInterface"),
                        "Something went wrong while interacting with port " << port_);
    return CallbackReturn::FAILURE;
  }

  RCLCPP_INFO(rclcpp::get_logger("VoyagerInterface"),
              "Hardware started, ready to take commands");
  return CallbackReturn::SUCCESS;
}


CallbackReturn VoyagerInterface::on_deactivate(const rclcpp_lifecycle::State &)
{
  RCLCPP_INFO(rclcpp::get_logger("VoyagerInterface"), "Stopping robot hardware ...");

  if (arduino_.IsOpen())
  {
    try
    {
      arduino_.Close();
    }
    catch (...)
    {
      RCLCPP_FATAL_STREAM(rclcpp::get_logger("VoyagerInterface"),
                          "Something went wrong while closing connection with port " << port_);
    }
  }

  RCLCPP_INFO(rclcpp::get_logger("VoyagerInterface"), "Hardware stopped");
  return CallbackReturn::SUCCESS;
}


hardware_interface::return_type VoyagerInterface::read(const rclcpp::Time &,
                                                          const rclcpp::Duration &)
{ 
  if (arduino_.IsOpen())
  {
  RCLCPP_INFO(rclcpp::get_logger("VoyagerInterface"), "Start reading");
  // Interpret the string
  if(arduino_.IsDataAvailable())
  {
    auto dt = (rclcpp::Clock().now() - last_run_).seconds();
    std::string message;
    arduino_.ReadLine(message);
    std::stringstream ss(message);
    std::string res;
    int multiplier = 1;
    while(std::getline(ss, res, ','))
    {
      multiplier = res.at(1) == 'p' ? 1 : -1;

      if(res.at(0) == 'a') //Right Front wheel
      {
        velocity_states_.at(0) = multiplier * std::stod(res.substr(2, res.size()));
        position_states_.at(0) += velocity_states_.at(0) * dt;
      }
      else if(res.at(0) == 'b') //Left Front wheel
      {
        velocity_states_.at(1) = multiplier * std::stod(res.substr(2, res.size()));
        position_states_.at(1) += velocity_states_.at(1) * dt;
      }
      else if(res.at(0) == 'c') //Right Rear wheel
      {
        velocity_states_.at(2) = multiplier * std::stod(res.substr(2, res.size()));
        position_states_.at(2) += velocity_states_.at(2) * dt;
      }
      else if(res.at(0) == 'd') //Left Rear wheel
      {
        velocity_states_.at(3) = multiplier * std::stod(res.substr(2, res.size()));
        position_states_.at(3) += velocity_states_.at(3) * dt;
      }
    }
    last_run_ = rclcpp::Clock().now();
  }
  }
  return hardware_interface::return_type::OK;
}

hardware_interface::return_type VoyagerInterface::write(const rclcpp::Time &,
                                                          const rclcpp::Duration &)
{
  if (arduino_.IsOpen())
  {
    RCLCPP_INFO(rclcpp::get_logger("VoyagerInterface"), "Start writing");
    // Implement communication protocol with the Arduino
    std::stringstream message_stream;
    
    message_stream << std::fixed << std::setprecision(2) 
      << velocity_commands_.at(0) << "," << velocity_commands_.at(1) << "," 
      << velocity_commands_.at(3) << "," << velocity_commands_.at(2) << "," 
      << position_commands_.at(0) << ",\n";

    try
    {
      arduino_.Write(message_stream.str());
    }
    catch (...)
    {
      RCLCPP_ERROR_STREAM(rclcpp::get_logger("VoyagerInterface"),
                          "Something went wrong while sending the message "
                              << message_stream.str() << " to the port " << port_);
      return hardware_interface::return_type::ERROR;
    }
  }

  return hardware_interface::return_type::OK;
}
}  // namespace voyager_firmware

PLUGINLIB_EXPORT_CLASS(voyager_firmware::VoyagerInterface, hardware_interface::SystemInterface)