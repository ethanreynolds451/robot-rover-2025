// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_interfaces:msg/QMCData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__QMC_DATA__BUILDER_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__QMC_DATA__BUILDER_HPP_

#include "vehicle_interfaces/msg/detail/qmc_data__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace vehicle_interfaces
{

namespace msg
{

namespace builder
{

class Init_QMCData_temp
{
public:
  explicit Init_QMCData_temp(::vehicle_interfaces::msg::QMCData & msg)
  : msg_(msg)
  {}
  ::vehicle_interfaces::msg::QMCData temp(::vehicle_interfaces::msg::QMCData::_temp_type arg)
  {
    msg_.temp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_interfaces::msg::QMCData msg_;
};

class Init_QMCData_heading
{
public:
  explicit Init_QMCData_heading(::vehicle_interfaces::msg::QMCData & msg)
  : msg_(msg)
  {}
  Init_QMCData_temp heading(::vehicle_interfaces::msg::QMCData::_heading_type arg)
  {
    msg_.heading = std::move(arg);
    return Init_QMCData_temp(msg_);
  }

private:
  ::vehicle_interfaces::msg::QMCData msg_;
};

class Init_QMCData_mag
{
public:
  explicit Init_QMCData_mag(::vehicle_interfaces::msg::QMCData & msg)
  : msg_(msg)
  {}
  Init_QMCData_heading mag(::vehicle_interfaces::msg::QMCData::_mag_type arg)
  {
    msg_.mag = std::move(arg);
    return Init_QMCData_heading(msg_);
  }

private:
  ::vehicle_interfaces::msg::QMCData msg_;
};

class Init_QMCData_arduino_timestamp
{
public:
  explicit Init_QMCData_arduino_timestamp(::vehicle_interfaces::msg::QMCData & msg)
  : msg_(msg)
  {}
  Init_QMCData_mag arduino_timestamp(::vehicle_interfaces::msg::QMCData::_arduino_timestamp_type arg)
  {
    msg_.arduino_timestamp = std::move(arg);
    return Init_QMCData_mag(msg_);
  }

private:
  ::vehicle_interfaces::msg::QMCData msg_;
};

class Init_QMCData_is_valid
{
public:
  explicit Init_QMCData_is_valid(::vehicle_interfaces::msg::QMCData & msg)
  : msg_(msg)
  {}
  Init_QMCData_arduino_timestamp is_valid(::vehicle_interfaces::msg::QMCData::_is_valid_type arg)
  {
    msg_.is_valid = std::move(arg);
    return Init_QMCData_arduino_timestamp(msg_);
  }

private:
  ::vehicle_interfaces::msg::QMCData msg_;
};

class Init_QMCData_header
{
public:
  Init_QMCData_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_QMCData_is_valid header(::vehicle_interfaces::msg::QMCData::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_QMCData_is_valid(msg_);
  }

private:
  ::vehicle_interfaces::msg::QMCData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_interfaces::msg::QMCData>()
{
  return vehicle_interfaces::msg::builder::Init_QMCData_header();
}

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__QMC_DATA__BUILDER_HPP_
