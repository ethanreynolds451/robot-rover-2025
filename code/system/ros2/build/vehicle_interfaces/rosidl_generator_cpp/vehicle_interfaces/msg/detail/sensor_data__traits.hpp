// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_interfaces:msg/SensorData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__SENSOR_DATA__TRAITS_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__SENSOR_DATA__TRAITS_HPP_

#include "vehicle_interfaces/msg/detail/sensor_data__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vehicle_interfaces::msg::SensorData>()
{
  return "vehicle_interfaces::msg::SensorData";
}

template<>
inline const char * name<vehicle_interfaces::msg::SensorData>()
{
  return "vehicle_interfaces/msg/SensorData";
}

template<>
struct has_fixed_size<vehicle_interfaces::msg::SensorData>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vehicle_interfaces::msg::SensorData>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vehicle_interfaces::msg::SensorData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__SENSOR_DATA__TRAITS_HPP_
