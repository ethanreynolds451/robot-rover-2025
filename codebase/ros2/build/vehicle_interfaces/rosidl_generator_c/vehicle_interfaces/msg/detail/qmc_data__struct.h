// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_interfaces:msg/QMCData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__QMC_DATA__STRUCT_H_
#define VEHICLE_INTERFACES__MSG__DETAIL__QMC_DATA__STRUCT_H_

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
// Member 'mag'
#include "sensor_msgs/msg/detail/magnetic_field__struct.h"
// Member 'temp'
#include "sensor_msgs/msg/detail/temperature__struct.h"

// Struct defined in msg/QMCData in the package vehicle_interfaces.
typedef struct vehicle_interfaces__msg__QMCData
{
  std_msgs__msg__Header header;
  std_msgs__msg__Bool is_valid;
  uint32_t arduino_timestamp;
  sensor_msgs__msg__MagneticField mag;
  float heading;
  sensor_msgs__msg__Temperature temp;
} vehicle_interfaces__msg__QMCData;

// Struct for a sequence of vehicle_interfaces__msg__QMCData.
typedef struct vehicle_interfaces__msg__QMCData__Sequence
{
  vehicle_interfaces__msg__QMCData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_interfaces__msg__QMCData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__QMC_DATA__STRUCT_H_
