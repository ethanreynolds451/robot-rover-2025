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

class Init_ControlData_steering_power
{
public:
  explicit Init_ControlData_steering_power(::vehicle_interfaces::msg::ControlData & msg)
  : msg_(msg)
  {}
  ::vehicle_interfaces::msg::ControlData steering_power(::vehicle_interfaces::msg::ControlData::_steering_power_type arg)
  {
    msg_.steering_power = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_interfaces::msg::ControlData msg_;
};

class Init_ControlData_power
{
public:
  explicit Init_ControlData_power(::vehicle_interfaces::msg::ControlData & msg)
  : msg_(msg)
  {}
  Init_ControlData_steering_power power(::vehicle_interfaces::msg::ControlData::_power_type arg)
  {
    msg_.power = std::move(arg);
    return Init_ControlData_steering_power(msg_);
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
  Init_ControlData_power shift_up(::vehicle_interfaces::msg::ControlData::_shift_up_type arg)
  {
    msg_.shift_up = std::move(arg);
    return Init_ControlData_power(msg_);
  }

private:
  ::vehicle_interfaces::msg::ControlData msg_;
};

class Init_ControlData_steering_reverse
{
public:
  explicit Init_ControlData_steering_reverse(::vehicle_interfaces::msg::ControlData & msg)
  : msg_(msg)
  {}
  Init_ControlData_shift_up steering_reverse(::vehicle_interfaces::msg::ControlData::_steering_reverse_type arg)
  {
    msg_.steering_reverse = std::move(arg);
    return Init_ControlData_shift_up(msg_);
  }

private:
  ::vehicle_interfaces::msg::ControlData msg_;
};

class Init_ControlData_reverse
{
public:
  explicit Init_ControlData_reverse(::vehicle_interfaces::msg::ControlData & msg)
  : msg_(msg)
  {}
  Init_ControlData_steering_reverse reverse(::vehicle_interfaces::msg::ControlData::_reverse_type arg)
  {
    msg_.reverse = std::move(arg);
    return Init_ControlData_steering_reverse(msg_);
  }

private:
  ::vehicle_interfaces::msg::ControlData msg_;
};

class Init_ControlData_brake
{
public:
  Init_ControlData_brake()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ControlData_reverse brake(::vehicle_interfaces::msg::ControlData::_brake_type arg)
  {
    msg_.brake = std::move(arg);
    return Init_ControlData_reverse(msg_);
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
  return vehicle_interfaces::msg::builder::Init_ControlData_brake();
}

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__CONTROL_DATA__BUILDER_HPP_
