// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_interfaces:msg/ControlData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__CONTROL_DATA__STRUCT_H_
#define VEHICLE_INTERFACES__MSG__DETAIL__CONTROL_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/ControlData in the package vehicle_interfaces.
typedef struct vehicle_interfaces__msg__ControlData
{
  bool brake;
  bool reverse;
  bool steering_reverse;
  bool shift_up;
  uint8_t power;
  uint8_t steering_power;
} vehicle_interfaces__msg__ControlData;

// Struct for a sequence of vehicle_interfaces__msg__ControlData.
typedef struct vehicle_interfaces__msg__ControlData__Sequence
{
  vehicle_interfaces__msg__ControlData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_interfaces__msg__ControlData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__CONTROL_DATA__STRUCT_H_
