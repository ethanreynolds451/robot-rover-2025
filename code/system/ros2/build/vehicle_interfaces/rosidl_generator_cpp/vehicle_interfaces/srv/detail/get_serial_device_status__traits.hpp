// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_interfaces:srv/GetSerialDeviceStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__SRV__DETAIL__GET_SERIAL_DEVICE_STATUS__TRAITS_HPP_
#define VEHICLE_INTERFACES__SRV__DETAIL__GET_SERIAL_DEVICE_STATUS__TRAITS_HPP_

#include "vehicle_interfaces/srv/detail/get_serial_device_status__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vehicle_interfaces::srv::GetSerialDeviceStatus_Request>()
{
  return "vehicle_interfaces::srv::GetSerialDeviceStatus_Request";
}

template<>
inline const char * name<vehicle_interfaces::srv::GetSerialDeviceStatus_Request>()
{
  return "vehicle_interfaces/srv/GetSerialDeviceStatus_Request";
}

template<>
struct has_fixed_size<vehicle_interfaces::srv::GetSerialDeviceStatus_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vehicle_interfaces::srv::GetSerialDeviceStatus_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vehicle_interfaces::srv::GetSerialDeviceStatus_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vehicle_interfaces::srv::GetSerialDeviceStatus_Response>()
{
  return "vehicle_interfaces::srv::GetSerialDeviceStatus_Response";
}

template<>
inline const char * name<vehicle_interfaces::srv::GetSerialDeviceStatus_Response>()
{
  return "vehicle_interfaces/srv/GetSerialDeviceStatus_Response";
}

template<>
struct has_fixed_size<vehicle_interfaces::srv::GetSerialDeviceStatus_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vehicle_interfaces::srv::GetSerialDeviceStatus_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vehicle_interfaces::srv::GetSerialDeviceStatus_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vehicle_interfaces::srv::GetSerialDeviceStatus>()
{
  return "vehicle_interfaces::srv::GetSerialDeviceStatus";
}

template<>
inline const char * name<vehicle_interfaces::srv::GetSerialDeviceStatus>()
{
  return "vehicle_interfaces/srv/GetSerialDeviceStatus";
}

template<>
struct has_fixed_size<vehicle_interfaces::srv::GetSerialDeviceStatus>
  : std::integral_constant<
    bool,
    has_fixed_size<vehicle_interfaces::srv::GetSerialDeviceStatus_Request>::value &&
    has_fixed_size<vehicle_interfaces::srv::GetSerialDeviceStatus_Response>::value
  >
{
};

template<>
struct has_bounded_size<vehicle_interfaces::srv::GetSerialDeviceStatus>
  : std::integral_constant<
    bool,
    has_bounded_size<vehicle_interfaces::srv::GetSerialDeviceStatus_Request>::value &&
    has_bounded_size<vehicle_interfaces::srv::GetSerialDeviceStatus_Response>::value
  >
{
};

template<>
struct is_service<vehicle_interfaces::srv::GetSerialDeviceStatus>
  : std::true_type
{
};

template<>
struct is_service_request<vehicle_interfaces::srv::GetSerialDeviceStatus_Request>
  : std::true_type
{
};

template<>
struct is_service_response<vehicle_interfaces::srv::GetSerialDeviceStatus_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_INTERFACES__SRV__DETAIL__GET_SERIAL_DEVICE_STATUS__TRAITS_HPP_
