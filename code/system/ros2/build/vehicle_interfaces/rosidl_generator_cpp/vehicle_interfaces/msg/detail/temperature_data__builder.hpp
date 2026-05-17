// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_interfaces:msg/TemperatureData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__TEMPERATURE_DATA__BUILDER_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__TEMPERATURE_DATA__BUILDER_HPP_

#include "vehicle_interfaces/msg/detail/temperature_data__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace vehicle_interfaces
{

namespace msg
{

namespace builder
{

class Init_TemperatureData_temp
{
public:
  explicit Init_TemperatureData_temp(::vehicle_interfaces::msg::TemperatureData & msg)
  : msg_(msg)
  {}
  ::vehicle_interfaces::msg::TemperatureData temp(::vehicle_interfaces::msg::TemperatureData::_temp_type arg)
  {
    msg_.temp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_interfaces::msg::TemperatureData msg_;
};

class Init_TemperatureData_arduino_timestamp
{
public:
  explicit Init_TemperatureData_arduino_timestamp(::vehicle_interfaces::msg::TemperatureData & msg)
  : msg_(msg)
  {}
  Init_TemperatureData_temp arduino_timestamp(::vehicle_interfaces::msg::TemperatureData::_arduino_timestamp_type arg)
  {
    msg_.arduino_timestamp = std::move(arg);
    return Init_TemperatureData_temp(msg_);
  }

private:
  ::vehicle_interfaces::msg::TemperatureData msg_;
};

class Init_TemperatureData_is_valid
{
public:
  explicit Init_TemperatureData_is_valid(::vehicle_interfaces::msg::TemperatureData & msg)
  : msg_(msg)
  {}
  Init_TemperatureData_arduino_timestamp is_valid(::vehicle_interfaces::msg::TemperatureData::_is_valid_type arg)
  {
    msg_.is_valid = std::move(arg);
    return Init_TemperatureData_arduino_timestamp(msg_);
  }

private:
  ::vehicle_interfaces::msg::TemperatureData msg_;
};

class Init_TemperatureData_header
{
public:
  Init_TemperatureData_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TemperatureData_is_valid header(::vehicle_interfaces::msg::TemperatureData::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_TemperatureData_is_valid(msg_);
  }

private:
  ::vehicle_interfaces::msg::TemperatureData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_interfaces::msg::TemperatureData>()
{
  return vehicle_interfaces::msg::builder::Init_TemperatureData_header();
}

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__TEMPERATURE_DATA__BUILDER_HPP_
