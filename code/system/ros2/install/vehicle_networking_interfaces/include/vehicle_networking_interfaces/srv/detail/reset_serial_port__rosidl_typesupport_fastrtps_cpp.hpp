// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from vehicle_networking_interfaces:srv/ResetSerialPort.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_NETWORKING_INTERFACES__SRV__DETAIL__RESET_SERIAL_PORT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define VEHICLE_NETWORKING_INTERFACES__SRV__DETAIL__RESET_SERIAL_PORT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "vehicle_networking_interfaces/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "vehicle_networking_interfaces/srv/detail/reset_serial_port__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace vehicle_networking_interfaces
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_networking_interfaces
cdr_serialize(
  const vehicle_networking_interfaces::srv::ResetSerialPort_Request & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_networking_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vehicle_networking_interfaces::srv::ResetSerialPort_Request & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_networking_interfaces
get_serialized_size(
  const vehicle_networking_interfaces::srv::ResetSerialPort_Request & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_networking_interfaces
max_serialized_size_ResetSerialPort_Request(
  bool & full_bounded,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace vehicle_networking_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_networking_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_networking_interfaces, srv, ResetSerialPort_Request)();

#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "vehicle_networking_interfaces/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
// already included above
// #include "vehicle_networking_interfaces/srv/detail/reset_serial_port__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// already included above
// #include "fastcdr/Cdr.h"

namespace vehicle_networking_interfaces
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_networking_interfaces
cdr_serialize(
  const vehicle_networking_interfaces::srv::ResetSerialPort_Response & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_networking_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vehicle_networking_interfaces::srv::ResetSerialPort_Response & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_networking_interfaces
get_serialized_size(
  const vehicle_networking_interfaces::srv::ResetSerialPort_Response & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_networking_interfaces
max_serialized_size_ResetSerialPort_Response(
  bool & full_bounded,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace vehicle_networking_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_networking_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_networking_interfaces, srv, ResetSerialPort_Response)();

#ifdef __cplusplus
}
#endif

#include "rmw/types.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "vehicle_networking_interfaces/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_networking_interfaces
const rosidl_service_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_networking_interfaces, srv, ResetSerialPort)();

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_NETWORKING_INTERFACES__SRV__DETAIL__RESET_SERIAL_PORT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
