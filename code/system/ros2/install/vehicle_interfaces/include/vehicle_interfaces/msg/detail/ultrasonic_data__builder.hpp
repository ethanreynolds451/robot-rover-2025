// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_interfaces:msg/UltrasonicData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__ULTRASONIC_DATA__BUILDER_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__ULTRASONIC_DATA__BUILDER_HPP_

#include "vehicle_interfaces/msg/detail/ultrasonic_data__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace vehicle_interfaces
{

namespace msg
{

namespace builder
{

class Init_UltrasonicData_range
{
public:
  explicit Init_UltrasonicData_range(::vehicle_interfaces::msg::UltrasonicData & msg)
  : msg_(msg)
  {}
  ::vehicle_interfaces::msg::UltrasonicData range(::vehicle_interfaces::msg::UltrasonicData::_range_type arg)
  {
    msg_.range = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_interfaces::msg::UltrasonicData msg_;
};

class Init_UltrasonicData_arduino_timestamp
{
public:
  explicit Init_UltrasonicData_arduino_timestamp(::vehicle_interfaces::msg::UltrasonicData & msg)
  : msg_(msg)
  {}
  Init_UltrasonicData_range arduino_timestamp(::vehicle_interfaces::msg::UltrasonicData::_arduino_timestamp_type arg)
  {
    msg_.arduino_timestamp = std::move(arg);
    return Init_UltrasonicData_range(msg_);
  }

private:
  ::vehicle_interfaces::msg::UltrasonicData msg_;
};

class Init_UltrasonicData_is_valid
{
public:
  explicit Init_UltrasonicData_is_valid(::vehicle_interfaces::msg::UltrasonicData & msg)
  : msg_(msg)
  {}
  Init_UltrasonicData_arduino_timestamp is_valid(::vehicle_interfaces::msg::UltrasonicData::_is_valid_type arg)
  {
    msg_.is_valid = std::move(arg);
    return Init_UltrasonicData_arduino_timestamp(msg_);
  }

private:
  ::vehicle_interfaces::msg::UltrasonicData msg_;
};

class Init_UltrasonicData_header
{
public:
  Init_UltrasonicData_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_UltrasonicData_is_valid header(::vehicle_interfaces::msg::UltrasonicData::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_UltrasonicData_is_valid(msg_);
  }

private:
  ::vehicle_interfaces::msg::UltrasonicData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_interfaces::msg::UltrasonicData>()
{
  return vehicle_interfaces::msg::builder::Init_UltrasonicData_header();
}

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__ULTRASONIC_DATA__BUILDER_HPP_
