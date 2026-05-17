// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_interfaces:msg/ControlData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__CONTROL_DATA__BUILDER_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__CONTROL_DATA__BUILDER_HPP_

#include "vehicle_interfaces/msg/detail/control_data__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace vehicle_interfaces
{

namespace msg
{

namespace builder
{

class Init_ControlData_fan_speed
{
public:
  explicit Init_ControlData_fan_speed(::vehicle_interfaces::msg::ControlData & msg)
  : msg_(msg)
  {}
  ::vehicle_interfaces::msg::ControlData fan_speed(::vehicle_interfaces::msg::ControlData::_fan_speed_type arg)
  {
    msg_.fan_speed = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_interfaces::msg::ControlData msg_;
};

class Init_ControlData_steer_power
{
public:
  explicit Init_ControlData_steer_power(::vehicle_interfaces::msg::ControlData & msg)
  : msg_(msg)
  {}
  Init_ControlData_fan_speed steer_power(::vehicle_interfaces::msg::ControlData::_steer_power_type arg)
  {
    msg_.steer_power = std::move(arg);
    return Init_ControlData_fan_speed(msg_);
  }

private:
  ::vehicle_interfaces::msg::ControlData msg_;
};

class Init_ControlData_drive_power
{
public:
  explicit Init_ControlData_drive_power(::vehicle_interfaces::msg::ControlData & msg)
  : msg_(msg)
  {}
  Init_ControlData_steer_power drive_power(::vehicle_interfaces::msg::ControlData::_drive_power_type arg)
  {
    msg_.drive_power = std::move(arg);
    return Init_ControlData_steer_power(msg_);
  }

private:
  ::vehicle_interfaces::msg::ControlData msg_;
};

class Init_ControlData_shift_up
{
public:
  explicit Init_ControlData_shift_up(::vehicle_interfaces::msg::ControlData & msg)
  : msg_(msg)
  {}
  Init_ControlData_drive_power shift_up(::vehicle_interfaces::msg::ControlData::_shift_up_type arg)
  {
    msg_.shift_up = std::move(arg);
    return Init_ControlData_drive_power(msg_);
  }

private:
  ::vehicle_interfaces::msg::ControlData msg_;
};

class Init_ControlData_steer_reverse
{
public:
  explicit Init_ControlData_steer_reverse(::vehicle_interfaces::msg::ControlData & msg)
  : msg_(msg)
  {}
  Init_ControlData_shift_up steer_reverse(::vehicle_interfaces::msg::ControlData::_steer_reverse_type arg)
  {
    msg_.steer_reverse = std::move(arg);
    return Init_ControlData_shift_up(msg_);
  }

private:
  ::vehicle_interfaces::msg::ControlData msg_;
};

class Init_ControlData_drive_reverse
{
public:
  explicit Init_ControlData_drive_reverse(::vehicle_interfaces::msg::ControlData & msg)
  : msg_(msg)
  {}
  Init_ControlData_steer_reverse drive_reverse(::vehicle_interfaces::msg::ControlData::_drive_reverse_type arg)
  {
    msg_.drive_reverse = std::move(arg);
    return Init_ControlData_steer_reverse(msg_);
  }

private:
  ::vehicle_interfaces::msg::ControlData msg_;
};

class Init_ControlData_brake
{
public:
  explicit Init_ControlData_brake(::vehicle_interfaces::msg::ControlData & msg)
  : msg_(msg)
  {}
  Init_ControlData_drive_reverse brake(::vehicle_interfaces::msg::ControlData::_brake_type arg)
  {
    msg_.brake = std::move(arg);
    return Init_ControlData_drive_reverse(msg_);
  }

private:
  ::vehicle_interfaces::msg::ControlData msg_;
};

class Init_ControlData_header
{
public:
  Init_ControlData_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ControlData_brake header(::vehicle_interfaces::msg::ControlData::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ControlData_brake(msg_);
  }

private:
  ::vehicle_interfaces::msg::ControlData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_interfaces::msg::ControlData>()
{
  return vehicle_interfaces::msg::builder::Init_ControlData_header();
}

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__CONTROL_DATA__BUILDER_HPP_
