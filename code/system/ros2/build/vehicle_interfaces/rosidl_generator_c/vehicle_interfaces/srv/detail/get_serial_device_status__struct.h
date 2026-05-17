// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_interfaces:srv/GetSerialDeviceStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__SRV__DETAIL__GET_SERIAL_DEVICE_STATUS__STRUCT_H_
#define VEHICLE_INTERFACES__SRV__DETAIL__GET_SERIAL_DEVICE_STATUS__STRUCT_H_

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

// Struct defined in srv/GetSerialDeviceStatus in the package vehicle_interfaces.
typedef struct vehicle_interfaces__srv__GetSerialDeviceStatus_Request
{
  rosidl_runtime_c__String device;
} vehicle_interfaces__srv__GetSerialDeviceStatus_Request;

// Struct for a sequence of vehicle_interfaces__srv__GetSerialDeviceStatus_Request.
typedef struct vehicle_interfaces__srv__GetSerialDeviceStatus_Request__Sequence
{
  vehicle_interfaces__srv__GetSerialDeviceStatus_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_interfaces__srv__GetSerialDeviceStatus_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'port'
// already included above
// #include "rosidl_runtime_c/string.h"

// Struct defined in srv/GetSerialDeviceStatus in the package vehicle_interfaces.
typedef struct vehicle_interfaces__srv__GetSerialDeviceStatus_Response
{
  rosidl_runtime_c__String port;
  bool connected;
} vehicle_interfaces__srv__GetSerialDeviceStatus_Response;

// Struct for a sequence of vehicle_interfaces__srv__GetSerialDeviceStatus_Response.
typedef struct vehicle_interfaces__srv__GetSerialDeviceStatus_Response__Sequence
{
  vehicle_interfaces__srv__GetSerialDeviceStatus_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_interfaces__srv__GetSerialDeviceStatus_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_INTERFACES__SRV__DETAIL__GET_SERIAL_DEVICE_STATUS__STRUCT_H_
