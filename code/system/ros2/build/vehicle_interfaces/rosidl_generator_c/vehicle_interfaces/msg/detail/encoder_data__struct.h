// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_interfaces:msg/EncoderData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__ENCODER_DATA__STRUCT_H_
#define VEHICLE_INTERFACES__MSG__DETAIL__ENCODER_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'is_valid'
#include "std_msgs/msg/detail/bool__struct.h"

// Struct defined in msg/EncoderData in the package vehicle_interfaces.
typedef struct vehicle_interfaces__msg__EncoderData
{
  std_msgs__msg__Header header;
  std_msgs__msg__Bool is_valid;
  uint32_t arduino_timestamp;
  float position;
  float velocity;
  int8_t direction;
} vehicle_interfaces__msg__EncoderData;

// Struct for a sequence of vehicle_interfaces__msg__EncoderData.
typedef struct vehicle_interfaces__msg__EncoderData__Sequence
{
  vehicle_interfaces__msg__EncoderData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_interfaces__msg__EncoderData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__ENCODER_DATA__STRUCT_H_
