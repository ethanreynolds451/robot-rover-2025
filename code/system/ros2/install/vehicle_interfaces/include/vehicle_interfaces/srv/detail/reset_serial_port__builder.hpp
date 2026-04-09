// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_interfaces:srv/ResetSerialPort.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__SRV__DETAIL__RESET_SERIAL_PORT__BUILDER_HPP_
#define VEHICLE_INTERFACES__SRV__DETAIL__RESET_SERIAL_PORT__BUILDER_HPP_

#include "vehicle_interfaces/srv/detail/reset_serial_port__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace vehicle_interfaces
{

namespace srv
{

namespace builder
{

class Init_ResetSerialPort_Request_device
{
public:
  Init_ResetSerialPort_Request_device()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::vehicle_interfaces::srv::ResetSerialPort_Request device(::vehicle_interfaces::srv::ResetSerialPort_Request::_device_type arg)
  {
    msg_.device = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_interfaces::srv::ResetSerialPort_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_interfaces::srv::ResetSerialPort_Request>()
{
  return vehicle_interfaces::srv::builder::Init_ResetSerialPort_Request_device();
}

}  // namespace vehicle_interfaces


namespace vehicle_interfaces
{

namespace srv
{

namespace builder
{

class Init_ResetSerialPort_Response_success
{
public:
  Init_ResetSerialPort_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::vehicle_interfaces::srv::ResetSerialPort_Response success(::vehicle_interfaces::srv::ResetSerialPort_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_interfaces::srv::ResetSerialPort_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_interfaces::srv::ResetSerialPort_Response>()
{
  return vehicle_interfaces::srv::builder::Init_ResetSerialPort_Response_success();
}

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__SRV__DETAIL__RESET_SERIAL_PORT__BUILDER_HPP_
