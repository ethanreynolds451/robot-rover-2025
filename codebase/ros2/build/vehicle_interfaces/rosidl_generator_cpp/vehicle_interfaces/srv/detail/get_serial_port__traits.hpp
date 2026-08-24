// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_interfaces:srv/GetSerialPort.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__SRV__DETAIL__GET_SERIAL_PORT__TRAITS_HPP_
#define VEHICLE_INTERFACES__SRV__DETAIL__GET_SERIAL_PORT__TRAITS_HPP_

#include "vehicle_interfaces/srv/detail/get_serial_port__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vehicle_interfaces::srv::GetSerialPort_Request>()
{
  return "vehicle_interfaces::srv::GetSerialPort_Request";
}

template<>
inline const char * name<vehicle_interfaces::srv::GetSerialPort_Request>()
{
  return "vehicle_interfaces/srv/GetSerialPort_Request";
}

template<>
struct has_fixed_size<vehicle_interfaces::srv::GetSerialPort_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vehicle_interfaces::srv::GetSerialPort_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vehicle_interfaces::srv::GetSerialPort_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vehicle_interfaces::srv::GetSerialPort_Response>()
{
  return "vehicle_interfaces::srv::GetSerialPort_Response";
}

template<>
inline const char * name<vehicle_interfaces::srv::GetSerialPort_Response>()
{
  return "vehicle_interfaces/srv/GetSerialPort_Response";
}

template<>
struct has_fixed_size<vehicle_interfaces::srv::GetSerialPort_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vehicle_interfaces::srv::GetSerialPort_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vehicle_interfaces::srv::GetSerialPort_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vehicle_interfaces::srv::GetSerialPort>()
{
  return "vehicle_interfaces::srv::GetSerialPort";
}

template<>
inline const char * name<vehicle_interfaces::srv::GetSerialPort>()
{
  return "vehicle_interfaces/srv/GetSerialPort";
}

template<>
struct has_fixed_size<vehicle_interfaces::srv::GetSerialPort>
  : std::integral_constant<
    bool,
    has_fixed_size<vehicle_interfaces::srv::GetSerialPort_Request>::value &&
    has_fixed_size<vehicle_interfaces::srv::GetSerialPort_Response>::value
  >
{
};

template<>
struct has_bounded_size<vehicle_interfaces::srv::GetSerialPort>
  : std::integral_constant<
    bool,
    has_bounded_size<vehicle_interfaces::srv::GetSerialPort_Request>::value &&
    has_bounded_size<vehicle_interfaces::srv::GetSerialPort_Response>::value
  >
{
};

template<>
struct is_service<vehicle_interfaces::srv::GetSerialPort>
  : std::true_type
{
};

template<>
struct is_service_request<vehicle_interfaces::srv::GetSerialPort_Request>
  : std::true_type
{
};

template<>
struct is_service_response<vehicle_interfaces::srv::GetSerialPort_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_INTERFACES__SRV__DETAIL__GET_SERIAL_PORT__TRAITS_HPP_
