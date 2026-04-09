// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_interfaces:msg/ToFData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__TO_F_DATA__BUILDER_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__TO_F_DATA__BUILDER_HPP_

#include "vehicle_interfaces/msg/detail/to_f_data__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace vehicle_interfaces
{

namespace msg
{

namespace builder
{

class Init_ToFData_intensity
{
public:
  explicit Init_ToFData_intensity(::vehicle_interfaces::msg::ToFData & msg)
  : msg_(msg)
  {}
  ::vehicle_interfaces::msg::ToFData intensity(::vehicle_interfaces::msg::ToFData::_intensity_type arg)
  {
    msg_.intensity = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_interfaces::msg::ToFData msg_;
};

class Init_ToFData_range
{
public:
  explicit Init_ToFData_range(::vehicle_interfaces::msg::ToFData & msg)
  : msg_(msg)
  {}
  Init_ToFData_intensity range(::vehicle_interfaces::msg::ToFData::_range_type arg)
  {
    msg_.range = std::move(arg);
    return Init_ToFData_intensity(msg_);
  }

private:
  ::vehicle_interfaces::msg::ToFData msg_;
};

class Init_ToFData_is_valid
{
public:
  explicit Init_ToFData_is_valid(::vehicle_interfaces::msg::ToFData & msg)
  : msg_(msg)
  {}
  Init_ToFData_range is_valid(::vehicle_interfaces::msg::ToFData::_is_valid_type arg)
  {
    msg_.is_valid = std::move(arg);
    return Init_ToFData_range(msg_);
  }

private:
  ::vehicle_interfaces::msg::ToFData msg_;
};

class Init_ToFData_header
{
public:
  Init_ToFData_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ToFData_is_valid header(::vehicle_interfaces::msg::ToFData::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ToFData_is_valid(msg_);
  }

private:
  ::vehicle_interfaces::msg::ToFData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_interfaces::msg::ToFData>()
{
  return vehicle_interfaces::msg::builder::Init_ToFData_header();
}

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__TO_F_DATA__BUILDER_HPP_
