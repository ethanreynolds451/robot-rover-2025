// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_interfaces:msg/IRData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__IR_DATA__BUILDER_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__IR_DATA__BUILDER_HPP_

#include "vehicle_interfaces/msg/detail/ir_data__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace vehicle_interfaces
{

namespace msg
{

namespace builder
{

class Init_IRData_data
{
public:
  explicit Init_IRData_data(::vehicle_interfaces::msg::IRData & msg)
  : msg_(msg)
  {}
  ::vehicle_interfaces::msg::IRData data(::vehicle_interfaces::msg::IRData::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_interfaces::msg::IRData msg_;
};

class Init_IRData_command
{
public:
  explicit Init_IRData_command(::vehicle_interfaces::msg::IRData & msg)
  : msg_(msg)
  {}
  Init_IRData_data command(::vehicle_interfaces::msg::IRData::_command_type arg)
  {
    msg_.command = std::move(arg);
    return Init_IRData_data(msg_);
  }

private:
  ::vehicle_interfaces::msg::IRData msg_;
};

class Init_IRData_address
{
public:
  explicit Init_IRData_address(::vehicle_interfaces::msg::IRData & msg)
  : msg_(msg)
  {}
  Init_IRData_command address(::vehicle_interfaces::msg::IRData::_address_type arg)
  {
    msg_.address = std::move(arg);
    return Init_IRData_command(msg_);
  }

private:
  ::vehicle_interfaces::msg::IRData msg_;
};

class Init_IRData_is_valid
{
public:
  explicit Init_IRData_is_valid(::vehicle_interfaces::msg::IRData & msg)
  : msg_(msg)
  {}
  Init_IRData_address is_valid(::vehicle_interfaces::msg::IRData::_is_valid_type arg)
  {
    msg_.is_valid = std::move(arg);
    return Init_IRData_address(msg_);
  }

private:
  ::vehicle_interfaces::msg::IRData msg_;
};

class Init_IRData_header
{
public:
  Init_IRData_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_IRData_is_valid header(::vehicle_interfaces::msg::IRData::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_IRData_is_valid(msg_);
  }

private:
  ::vehicle_interfaces::msg::IRData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_interfaces::msg::IRData>()
{
  return vehicle_interfaces::msg::builder::Init_IRData_header();
}

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__IR_DATA__BUILDER_HPP_
