// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_interfaces:msg/MPUData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__MPU_DATA__BUILDER_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__MPU_DATA__BUILDER_HPP_

#include "vehicle_interfaces/msg/detail/mpu_data__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace vehicle_interfaces
{

namespace msg
{

namespace builder
{

class Init_MPUData_temp
{
public:
  explicit Init_MPUData_temp(::vehicle_interfaces::msg::MPUData & msg)
  : msg_(msg)
  {}
  ::vehicle_interfaces::msg::MPUData temp(::vehicle_interfaces::msg::MPUData::_temp_type arg)
  {
    msg_.temp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_interfaces::msg::MPUData msg_;
};

class Init_MPUData_imu
{
public:
  explicit Init_MPUData_imu(::vehicle_interfaces::msg::MPUData & msg)
  : msg_(msg)
  {}
  Init_MPUData_temp imu(::vehicle_interfaces::msg::MPUData::_imu_type arg)
  {
    msg_.imu = std::move(arg);
    return Init_MPUData_temp(msg_);
  }

private:
  ::vehicle_interfaces::msg::MPUData msg_;
};

class Init_MPUData_is_valid
{
public:
  explicit Init_MPUData_is_valid(::vehicle_interfaces::msg::MPUData & msg)
  : msg_(msg)
  {}
  Init_MPUData_imu is_valid(::vehicle_interfaces::msg::MPUData::_is_valid_type arg)
  {
    msg_.is_valid = std::move(arg);
    return Init_MPUData_imu(msg_);
  }

private:
  ::vehicle_interfaces::msg::MPUData msg_;
};

class Init_MPUData_header
{
public:
  Init_MPUData_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MPUData_is_valid header(::vehicle_interfaces::msg::MPUData::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_MPUData_is_valid(msg_);
  }

private:
  ::vehicle_interfaces::msg::MPUData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_interfaces::msg::MPUData>()
{
  return vehicle_interfaces::msg::builder::Init_MPUData_header();
}

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__MPU_DATA__BUILDER_HPP_
