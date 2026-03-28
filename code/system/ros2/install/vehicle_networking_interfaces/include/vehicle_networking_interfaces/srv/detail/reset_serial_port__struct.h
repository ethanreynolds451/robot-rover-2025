// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_networking_interfaces:srv/ResetSerialPort.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_NETWORKING_INTERFACES__SRV__DETAIL__RESET_SERIAL_PORT__STRUCT_H_
#define VEHICLE_NETWORKING_INTERFACES__SRV__DETAIL__RESET_SERIAL_PORT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'device'
#include "rosidl_runtime_c/string.h"

// Struct defined in srv/ResetSerialPort in the package vehicle_networking_interfaces.
typedef struct vehicle_networking_interfaces__srv__ResetSerialPort_Request
{
  rosidl_runtime_c__String device;
} vehicle_networking_interfaces__srv__ResetSerialPort_Request;

// Struct for a sequence of vehicle_networking_interfaces__srv__ResetSerialPort_Request.
typedef struct vehicle_networking_interfaces__srv__ResetSerialPort_Request__Sequence
{
  vehicle_networking_interfaces__srv__ResetSerialPort_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_networking_interfaces__srv__ResetSerialPort_Request__Sequence;


// Constants defined in the message

// Struct defined in srv/ResetSerialPort in the package vehicle_networking_interfaces.
typedef struct vehicle_networking_interfaces__srv__ResetSerialPort_Response
{
  bool success;
} vehicle_networking_interfaces__srv__ResetSerialPort_Response;

// Struct for a sequence of vehicle_networking_interfaces__srv__ResetSerialPort_Response.
typedef struct vehicle_networking_interfaces__srv__ResetSerialPort_Response__Sequence
{
  vehicle_networking_interfaces__srv__ResetSerialPort_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_networking_interfaces__srv__ResetSerialPort_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_NETWORKING_INTERFACES__SRV__DETAIL__RESET_SERIAL_PORT__STRUCT_H_
