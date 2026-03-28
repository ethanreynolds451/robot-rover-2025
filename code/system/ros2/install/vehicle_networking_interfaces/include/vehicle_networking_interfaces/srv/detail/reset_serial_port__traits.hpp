// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_networking_interfaces:srv/ResetSerialPort.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_NETWORKING_INTERFACES__SRV__DETAIL__RESET_SERIAL_PORT__TRAITS_HPP_
#define VEHICLE_NETWORKING_INTERFACES__SRV__DETAIL__RESET_SERIAL_PORT__TRAITS_HPP_

#include "vehicle_networking_interfaces/srv/detail/reset_serial_port__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vehicle_networking_interfaces::srv::ResetSerialPort_Request>()
{
  return "vehicle_networking_interfaces::srv::ResetSerialPort_Request";
}

template<>
inline const char * name<vehicle_networking_interfaces::srv::ResetSerialPort_Request>()
{
  return "vehicle_networking_interfaces/srv/ResetSerialPort_Request";
}

template<>
struct has_fixed_size<vehicle_networking_interfaces::srv::ResetSerialPort_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vehicle_networking_interfaces::srv::ResetSerialPort_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vehicle_networking_interfaces::srv::ResetSerialPort_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vehicle_networking_interfaces::srv::ResetSerialPort_Response>()
{
  return "vehicle_networking_interfaces::srv::ResetSerialPort_Response";
}

template<>
inline const char * name<vehicle_networking_interfaces::srv::ResetSerialPort_Response>()
{
  return "vehicle_networking_interfaces/srv/ResetSerialPort_Response";
}

template<>
struct has_fixed_size<vehicle_networking_interfaces::srv::ResetSerialPort_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vehicle_networking_interfaces::srv::ResetSerialPort_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vehicle_networking_interfaces::srv::ResetSerialPort_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vehicle_networking_interfaces::srv::ResetSerialPort>()
{
  return "vehicle_networking_interfaces::srv::ResetSerialPort";
}

template<>
inline const char * name<vehicle_networking_interfaces::srv::ResetSerialPort>()
{
  return "vehicle_networking_interfaces/srv/ResetSerialPort";
}

template<>
struct has_fixed_size<vehicle_networking_interfaces::srv::ResetSerialPort>
  : std::integral_constant<
    bool,
    has_fixed_size<vehicle_networking_interfaces::srv::ResetSerialPort_Request>::value &&
    has_fixed_size<vehicle_networking_interfaces::srv::ResetSerialPort_Response>::value
  >
{
};

template<>
struct has_bounded_size<vehicle_networking_interfaces::srv::ResetSerialPort>
  : std::integral_constant<
    bool,
    has_bounded_size<vehicle_networking_interfaces::srv::ResetSerialPort_Request>::value &&
    has_bounded_size<vehicle_networking_interfaces::srv::ResetSerialPort_Response>::value
  >
{
};

template<>
struct is_service<vehicle_networking_interfaces::srv::ResetSerialPort>
  : std::true_type
{
};

template<>
struct is_service_request<vehicle_networking_interfaces::srv::ResetSerialPort_Request>
  : std::true_type
{
};

template<>
struct is_service_response<vehicle_networking_interfaces::srv::ResetSerialPort_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_NETWORKING_INTERFACES__SRV__DETAIL__RESET_SERIAL_PORT__TRAITS_HPP_
