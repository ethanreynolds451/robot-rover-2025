// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_interfaces:msg/ToFData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__TO_F_DATA__STRUCT_H_
#define VEHICLE_INTERFACES__MSG__DETAIL__TO_F_DATA__STRUCT_H_

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
// Member 'range'
#include "sensor_msgs/msg/detail/range__struct.h"

// Struct defined in msg/ToFData in the package vehicle_interfaces.
typedef struct vehicle_interfaces__msg__ToFData
{
  std_msgs__msg__Header header;
  std_msgs__msg__Bool is_valid;
  uint32_t arduino_timestamp;
  sensor_msgs__msg__Range range;
  float intensity;
} vehicle_interfaces__msg__ToFData;

// Struct for a sequence of vehicle_interfaces__msg__ToFData.
typedef struct vehicle_interfaces__msg__ToFData__Sequence
{
  vehicle_interfaces__msg__ToFData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_interfaces__msg__ToFData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__TO_F_DATA__STRUCT_H_
