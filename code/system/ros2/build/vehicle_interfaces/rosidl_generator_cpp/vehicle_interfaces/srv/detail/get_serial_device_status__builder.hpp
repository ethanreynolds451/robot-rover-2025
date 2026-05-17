// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_interfaces:srv/GetSerialDeviceStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__SRV__DETAIL__GET_SERIAL_DEVICE_STATUS__BUILDER_HPP_
#define VEHICLE_INTERFACES__SRV__DETAIL__GET_SERIAL_DEVICE_STATUS__BUILDER_HPP_

#include "vehicle_interfaces/srv/detail/get_serial_device_status__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace vehicle_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetSerialDeviceStatus_Request_device
{
public:
  Init_GetSerialDeviceStatus_Request_device()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::vehicle_interfaces::srv::GetSerialDeviceStatus_Request device(::vehicle_interfaces::srv::GetSerialDeviceStatus_Request::_device_type arg)
  {
    msg_.device = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_interfaces::srv::GetSerialDeviceStatus_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_interfaces::srv::GetSerialDeviceStatus_Request>()
{
  return vehicle_interfaces::srv::builder::Init_GetSerialDeviceStatus_Request_device();
}

}  // namespace vehicle_interfaces


namespace vehicle_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetSerialDeviceStatus_Response_connected
{
public:
  explicit Init_GetSerialDeviceStatus_Response_connected(::vehicle_interfaces::srv::GetSerialDeviceStatus_Response & msg)
  : msg_(msg)
  {}
  ::vehicle_interfaces::srv::GetSerialDeviceStatus_Response connected(::vehicle_interfaces::srv::GetSerialDeviceStatus_Response::_connected_type arg)
  {
    msg_.connected = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_interfaces::srv::GetSerialDeviceStatus_Response msg_;
};

class Init_GetSerialDeviceStatus_Response_port
{
public:
  Init_GetSerialDeviceStatus_Response_port()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetSerialDeviceStatus_Response_connected port(::vehicle_interfaces::srv::GetSerialDeviceStatus_Response::_port_type arg)
  {
    msg_.port = std::move(arg);
    return Init_GetSerialDeviceStatus_Response_connected(msg_);
  }

private:
  ::vehicle_interfaces::srv::GetSerialDeviceStatus_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_interfaces::srv::GetSerialDeviceStatus_Response>()
{
  return vehicle_interfaces::srv::builder::Init_GetSerialDeviceStatus_Response_port();
}

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__SRV__DETAIL__GET_SERIAL_DEVICE_STATUS__BUILDER_HPP_
