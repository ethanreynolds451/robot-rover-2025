// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_interfaces:msg/EncoderData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__ENCODER_DATA__TRAITS_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__ENCODER_DATA__TRAITS_HPP_

#include "vehicle_interfaces/msg/detail/encoder_data__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'is_valid'
#include "std_msgs/msg/detail/bool__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vehicle_interfaces::msg::EncoderData>()
{
  return "vehicle_interfaces::msg::EncoderData";
}

template<>
inline const char * name<vehicle_interfaces::msg::EncoderData>()
{
  return "vehicle_interfaces/msg/EncoderData";
}

template<>
struct has_fixed_size<vehicle_interfaces::msg::EncoderData>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Bool>::value && has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<vehicle_interfaces::msg::EncoderData>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Bool>::value && has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<vehicle_interfaces::msg::EncoderData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__ENCODER_DATA__TRAITS_HPP_
