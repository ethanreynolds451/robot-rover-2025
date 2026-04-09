// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_interfaces:srv/GetDeviceStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__SRV__DETAIL__GET_DEVICE_STATUS__TRAITS_HPP_
#define VEHICLE_INTERFACES__SRV__DETAIL__GET_DEVICE_STATUS__TRAITS_HPP_

#include "vehicle_interfaces/srv/detail/get_device_status__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vehicle_interfaces::srv::GetDeviceStatus_Request>()
{
  return "vehicle_interfaces::srv::GetDeviceStatus_Request";
}

template<>
inline const char * name<vehicle_interfaces::srv::GetDeviceStatus_Request>()
{
  return "vehicle_interfaces/srv/GetDeviceStatus_Request";
}

template<>
struct has_fixed_size<vehicle_interfaces::srv::GetDeviceStatus_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vehicle_interfaces::srv::GetDeviceStatus_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vehicle_interfaces::srv::GetDeviceStatus_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vehicle_interfaces::srv::GetDeviceStatus_Response>()
{
  return "vehicle_interfaces::srv::GetDeviceStatus_Response";
}

template<>
inline const char * name<vehicle_interfaces::srv::GetDeviceStatus_Response>()
{
  return "vehicle_interfaces/srv/GetDeviceStatus_Response";
}

template<>
struct has_fixed_size<vehicle_interfaces::srv::GetDeviceStatus_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vehicle_interfaces::srv::GetDeviceStatus_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vehicle_interfaces::srv::GetDeviceStatus_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vehicle_interfaces::srv::GetDeviceStatus>()
{
  return "vehicle_interfaces::srv::GetDeviceStatus";
}

template<>
inline const char * name<vehicle_interfaces::srv::GetDeviceStatus>()
{
  return "vehicle_interfaces/srv/GetDeviceStatus";
}

template<>
struct has_fixed_size<vehicle_interfaces::srv::GetDeviceStatus>
  : std::integral_constant<
    bool,
    has_fixed_size<vehicle_interfaces::srv::GetDeviceStatus_Request>::value &&
    has_fixed_size<vehicle_interfaces::srv::GetDeviceStatus_Response>::value
  >
{
};

template<>
struct has_bounded_size<vehicle_interfaces::srv::GetDeviceStatus>
  : std::integral_constant<
    bool,
    has_bounded_size<vehicle_interfaces::srv::GetDeviceStatus_Request>::value &&
    has_bounded_size<vehicle_interfaces::srv::GetDeviceStatus_Response>::value
  >
{
};

template<>
struct is_service<vehicle_interfaces::srv::GetDeviceStatus>
  : std::true_type
{
};

template<>
struct is_service_request<vehicle_interfaces::srv::GetDeviceStatus_Request>
  : std::true_type
{
};

template<>
struct is_service_response<vehicle_interfaces::srv::GetDeviceStatus_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_INTERFACES__SRV__DETAIL__GET_DEVICE_STATUS__TRAITS_HPP_
