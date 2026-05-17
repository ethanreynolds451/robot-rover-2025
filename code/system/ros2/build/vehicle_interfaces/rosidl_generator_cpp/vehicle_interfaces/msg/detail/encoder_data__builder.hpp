// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_interfaces:msg/EncoderData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__ENCODER_DATA__BUILDER_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__ENCODER_DATA__BUILDER_HPP_

#include "vehicle_interfaces/msg/detail/encoder_data__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace vehicle_interfaces
{

namespace msg
{

namespace builder
{

class Init_EncoderData_direction
{
public:
  explicit Init_EncoderData_direction(::vehicle_interfaces::msg::EncoderData & msg)
  : msg_(msg)
  {}
  ::vehicle_interfaces::msg::EncoderData direction(::vehicle_interfaces::msg::EncoderData::_direction_type arg)
  {
    msg_.direction = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_interfaces::msg::EncoderData msg_;
};

class Init_EncoderData_velocity
{
public:
  explicit Init_EncoderData_velocity(::vehicle_interfaces::msg::EncoderData & msg)
  : msg_(msg)
  {}
  Init_EncoderData_direction velocity(::vehicle_interfaces::msg::EncoderData::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_EncoderData_direction(msg_);
  }

private:
  ::vehicle_interfaces::msg::EncoderData msg_;
};

class Init_EncoderData_position
{
public:
  explicit Init_EncoderData_position(::vehicle_interfaces::msg::EncoderData & msg)
  : msg_(msg)
  {}
  Init_EncoderData_velocity position(::vehicle_interfaces::msg::EncoderData::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_EncoderData_velocity(msg_);
  }

private:
  ::vehicle_interfaces::msg::EncoderData msg_;
};

class Init_EncoderData_arduino_timestamp
{
public:
  explicit Init_EncoderData_arduino_timestamp(::vehicle_interfaces::msg::EncoderData & msg)
  : msg_(msg)
  {}
  Init_EncoderData_position arduino_timestamp(::vehicle_interfaces::msg::EncoderData::_arduino_timestamp_type arg)
  {
    msg_.arduino_timestamp = std::move(arg);
    return Init_EncoderData_position(msg_);
  }

private:
  ::vehicle_interfaces::msg::EncoderData msg_;
};

class Init_EncoderData_is_valid
{
public:
  explicit Init_EncoderData_is_valid(::vehicle_interfaces::msg::EncoderData & msg)
  : msg_(msg)
  {}
  Init_EncoderData_arduino_timestamp is_valid(::vehicle_interfaces::msg::EncoderData::_is_valid_type arg)
  {
    msg_.is_valid = std::move(arg);
    return Init_EncoderData_arduino_timestamp(msg_);
  }

private:
  ::vehicle_interfaces::msg::EncoderData msg_;
};

class Init_EncoderData_header
{
public:
  Init_EncoderData_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EncoderData_is_valid header(::vehicle_interfaces::msg::EncoderData::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_EncoderData_is_valid(msg_);
  }

private:
  ::vehicle_interfaces::msg::EncoderData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_interfaces::msg::EncoderData>()
{
  return vehicle_interfaces::msg::builder::Init_EncoderData_header();
}

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__ENCODER_DATA__BUILDER_HPP_
