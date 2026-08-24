// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vehicle_interfaces:msg/SensorData.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vehicle_interfaces/msg/detail/sensor_data__rosidl_typesupport_introspection_c.h"
#include "vehicle_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vehicle_interfaces/msg/detail/sensor_data__functions.h"
#include "vehicle_interfaces/msg/detail/sensor_data__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `mpu`
#include "vehicle_interfaces/msg/mpu_data.h"
// Member `mpu`
#include "vehicle_interfaces/msg/detail/mpu_data__rosidl_typesupport_introspection_c.h"
// Member `qmc`
#include "vehicle_interfaces/msg/qmc_data.h"
// Member `qmc`
#include "vehicle_interfaces/msg/detail/qmc_data__rosidl_typesupport_introspection_c.h"
// Member `gps`
#include "vehicle_interfaces/msg/gps_data.h"
// Member `gps`
#include "vehicle_interfaces/msg/detail/gps_data__rosidl_typesupport_introspection_c.h"
// Member `tof`
#include "vehicle_interfaces/msg/to_f_data.h"
// Member `tof`
#include "vehicle_interfaces/msg/detail/to_f_data__rosidl_typesupport_introspection_c.h"
// Member `ultrasonic`
#include "vehicle_interfaces/msg/ultrasonic_data.h"
// Member `ultrasonic`
#include "vehicle_interfaces/msg/detail/ultrasonic_data__rosidl_typesupport_introspection_c.h"
// Member `temperature`
#include "vehicle_interfaces/msg/temperature_data.h"
// Member `temperature`
#include "vehicle_interfaces/msg/detail/temperature_data__rosidl_typesupport_introspection_c.h"
// Member `encoder`
#include "vehicle_interfaces/msg/encoder_data.h"
// Member `encoder`
#include "vehicle_interfaces/msg/detail/encoder_data__rosidl_typesupport_introspection_c.h"
// Member `ir_remote`
#include "vehicle_interfaces/msg/ir_data.h"
// Member `ir_remote`
#include "vehicle_interfaces/msg/detail/ir_data__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void SensorData__rosidl_typesupport_introspection_c__SensorData_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_interfaces__msg__SensorData__init(message_memory);
}

void SensorData__rosidl_typesupport_introspection_c__SensorData_fini_function(void * message_memory)
{
  vehicle_interfaces__msg__SensorData__fini(message_memory);
}

size_t SensorData__rosidl_typesupport_introspection_c__size_function__MPUData__mpu(
  const void * untyped_member)
{
  const vehicle_interfaces__msg__MPUData__Sequence * member =
    (const vehicle_interfaces__msg__MPUData__Sequence *)(untyped_member);
  return member->size;
}

const void * SensorData__rosidl_typesupport_introspection_c__get_const_function__MPUData__mpu(
  const void * untyped_member, size_t index)
{
  const vehicle_interfaces__msg__MPUData__Sequence * member =
    (const vehicle_interfaces__msg__MPUData__Sequence *)(untyped_member);
  return &member->data[index];
}

void * SensorData__rosidl_typesupport_introspection_c__get_function__MPUData__mpu(
  void * untyped_member, size_t index)
{
  vehicle_interfaces__msg__MPUData__Sequence * member =
    (vehicle_interfaces__msg__MPUData__Sequence *)(untyped_member);
  return &member->data[index];
}

bool SensorData__rosidl_typesupport_introspection_c__resize_function__MPUData__mpu(
  void * untyped_member, size_t size)
{
  vehicle_interfaces__msg__MPUData__Sequence * member =
    (vehicle_interfaces__msg__MPUData__Sequence *)(untyped_member);
  vehicle_interfaces__msg__MPUData__Sequence__fini(member);
  return vehicle_interfaces__msg__MPUData__Sequence__init(member, size);
}

size_t SensorData__rosidl_typesupport_introspection_c__size_function__QMCData__qmc(
  const void * untyped_member)
{
  const vehicle_interfaces__msg__QMCData__Sequence * member =
    (const vehicle_interfaces__msg__QMCData__Sequence *)(untyped_member);
  return member->size;
}

const void * SensorData__rosidl_typesupport_introspection_c__get_const_function__QMCData__qmc(
  const void * untyped_member, size_t index)
{
  const vehicle_interfaces__msg__QMCData__Sequence * member =
    (const vehicle_interfaces__msg__QMCData__Sequence *)(untyped_member);
  return &member->data[index];
}

void * SensorData__rosidl_typesupport_introspection_c__get_function__QMCData__qmc(
  void * untyped_member, size_t index)
{
  vehicle_interfaces__msg__QMCData__Sequence * member =
    (vehicle_interfaces__msg__QMCData__Sequence *)(untyped_member);
  return &member->data[index];
}

bool SensorData__rosidl_typesupport_introspection_c__resize_function__QMCData__qmc(
  void * untyped_member, size_t size)
{
  vehicle_interfaces__msg__QMCData__Sequence * member =
    (vehicle_interfaces__msg__QMCData__Sequence *)(untyped_member);
  vehicle_interfaces__msg__QMCData__Sequence__fini(member);
  return vehicle_interfaces__msg__QMCData__Sequence__init(member, size);
}

size_t SensorData__rosidl_typesupport_introspection_c__size_function__GPSData__gps(
  const void * untyped_member)
{
  const vehicle_interfaces__msg__GPSData__Sequence * member =
    (const vehicle_interfaces__msg__GPSData__Sequence *)(untyped_member);
  return member->size;
}

const void * SensorData__rosidl_typesupport_introspection_c__get_const_function__GPSData__gps(
  const void * untyped_member, size_t index)
{
  const vehicle_interfaces__msg__GPSData__Sequence * member =
    (const vehicle_interfaces__msg__GPSData__Sequence *)(untyped_member);
  return &member->data[index];
}

void * SensorData__rosidl_typesupport_introspection_c__get_function__GPSData__gps(
  void * untyped_member, size_t index)
{
  vehicle_interfaces__msg__GPSData__Sequence * member =
    (vehicle_interfaces__msg__GPSData__Sequence *)(untyped_member);
  return &member->data[index];
}

bool SensorData__rosidl_typesupport_introspection_c__resize_function__GPSData__gps(
  void * untyped_member, size_t size)
{
  vehicle_interfaces__msg__GPSData__Sequence * member =
    (vehicle_interfaces__msg__GPSData__Sequence *)(untyped_member);
  vehicle_interfaces__msg__GPSData__Sequence__fini(member);
  return vehicle_interfaces__msg__GPSData__Sequence__init(member, size);
}

size_t SensorData__rosidl_typesupport_introspection_c__size_function__ToFData__tof(
  const void * untyped_member)
{
  const vehicle_interfaces__msg__ToFData__Sequence * member =
    (const vehicle_interfaces__msg__ToFData__Sequence *)(untyped_member);
  return member->size;
}

const void * SensorData__rosidl_typesupport_introspection_c__get_const_function__ToFData__tof(
  const void * untyped_member, size_t index)
{
  const vehicle_interfaces__msg__ToFData__Sequence * member =
    (const vehicle_interfaces__msg__ToFData__Sequence *)(untyped_member);
  return &member->data[index];
}

void * SensorData__rosidl_typesupport_introspection_c__get_function__ToFData__tof(
  void * untyped_member, size_t index)
{
  vehicle_interfaces__msg__ToFData__Sequence * member =
    (vehicle_interfaces__msg__ToFData__Sequence *)(untyped_member);
  return &member->data[index];
}

bool SensorData__rosidl_typesupport_introspection_c__resize_function__ToFData__tof(
  void * untyped_member, size_t size)
{
  vehicle_interfaces__msg__ToFData__Sequence * member =
    (vehicle_interfaces__msg__ToFData__Sequence *)(untyped_member);
  vehicle_interfaces__msg__ToFData__Sequence__fini(member);
  return vehicle_interfaces__msg__ToFData__Sequence__init(member, size);
}

size_t SensorData__rosidl_typesupport_introspection_c__size_function__UltrasonicData__ultrasonic(
  const void * untyped_member)
{
  const vehicle_interfaces__msg__UltrasonicData__Sequence * member =
    (const vehicle_interfaces__msg__UltrasonicData__Sequence *)(untyped_member);
  return member->size;
}

const void * SensorData__rosidl_typesupport_introspection_c__get_const_function__UltrasonicData__ultrasonic(
  const void * untyped_member, size_t index)
{
  const vehicle_interfaces__msg__UltrasonicData__Sequence * member =
    (const vehicle_interfaces__msg__UltrasonicData__Sequence *)(untyped_member);
  return &member->data[index];
}

void * SensorData__rosidl_typesupport_introspection_c__get_function__UltrasonicData__ultrasonic(
  void * untyped_member, size_t index)
{
  vehicle_interfaces__msg__UltrasonicData__Sequence * member =
    (vehicle_interfaces__msg__UltrasonicData__Sequence *)(untyped_member);
  return &member->data[index];
}

bool SensorData__rosidl_typesupport_introspection_c__resize_function__UltrasonicData__ultrasonic(
  void * untyped_member, size_t size)
{
  vehicle_interfaces__msg__UltrasonicData__Sequence * member =
    (vehicle_interfaces__msg__UltrasonicData__Sequence *)(untyped_member);
  vehicle_interfaces__msg__UltrasonicData__Sequence__fini(member);
  return vehicle_interfaces__msg__UltrasonicData__Sequence__init(member, size);
}

size_t SensorData__rosidl_typesupport_introspection_c__size_function__TemperatureData__temperature(
  const void * untyped_member)
{
  const vehicle_interfaces__msg__TemperatureData__Sequence * member =
    (const vehicle_interfaces__msg__TemperatureData__Sequence *)(untyped_member);
  return member->size;
}

const void * SensorData__rosidl_typesupport_introspection_c__get_const_function__TemperatureData__temperature(
  const void * untyped_member, size_t index)
{
  const vehicle_interfaces__msg__TemperatureData__Sequence * member =
    (const vehicle_interfaces__msg__TemperatureData__Sequence *)(untyped_member);
  return &member->data[index];
}

void * SensorData__rosidl_typesupport_introspection_c__get_function__TemperatureData__temperature(
  void * untyped_member, size_t index)
{
  vehicle_interfaces__msg__TemperatureData__Sequence * member =
    (vehicle_interfaces__msg__TemperatureData__Sequence *)(untyped_member);
  return &member->data[index];
}

bool SensorData__rosidl_typesupport_introspection_c__resize_function__TemperatureData__temperature(
  void * untyped_member, size_t size)
{
  vehicle_interfaces__msg__TemperatureData__Sequence * member =
    (vehicle_interfaces__msg__TemperatureData__Sequence *)(untyped_member);
  vehicle_interfaces__msg__TemperatureData__Sequence__fini(member);
  return vehicle_interfaces__msg__TemperatureData__Sequence__init(member, size);
}

size_t SensorData__rosidl_typesupport_introspection_c__size_function__EncoderData__encoder(
  const void * untyped_member)
{
  const vehicle_interfaces__msg__EncoderData__Sequence * member =
    (const vehicle_interfaces__msg__EncoderData__Sequence *)(untyped_member);
  return member->size;
}

const void * SensorData__rosidl_typesupport_introspection_c__get_const_function__EncoderData__encoder(
  const void * untyped_member, size_t index)
{
  const vehicle_interfaces__msg__EncoderData__Sequence * member =
    (const vehicle_interfaces__msg__EncoderData__Sequence *)(untyped_member);
  return &member->data[index];
}

void * SensorData__rosidl_typesupport_introspection_c__get_function__EncoderData__encoder(
  void * untyped_member, size_t index)
{
  vehicle_interfaces__msg__EncoderData__Sequence * member =
    (vehicle_interfaces__msg__EncoderData__Sequence *)(untyped_member);
  return &member->data[index];
}

bool SensorData__rosidl_typesupport_introspection_c__resize_function__EncoderData__encoder(
  void * untyped_member, size_t size)
{
  vehicle_interfaces__msg__EncoderData__Sequence * member =
    (vehicle_interfaces__msg__EncoderData__Sequence *)(untyped_member);
  vehicle_interfaces__msg__EncoderData__Sequence__fini(member);
  return vehicle_interfaces__msg__EncoderData__Sequence__init(member, size);
}

size_t SensorData__rosidl_typesupport_introspection_c__size_function__IRData__ir_remote(
  const void * untyped_member)
{
  const vehicle_interfaces__msg__IRData__Sequence * member =
    (const vehicle_interfaces__msg__IRData__Sequence *)(untyped_member);
  return member->size;
}

const void * SensorData__rosidl_typesupport_introspection_c__get_const_function__IRData__ir_remote(
  const void * untyped_member, size_t index)
{
  const vehicle_interfaces__msg__IRData__Sequence * member =
    (const vehicle_interfaces__msg__IRData__Sequence *)(untyped_member);
  return &member->data[index];
}

void * SensorData__rosidl_typesupport_introspection_c__get_function__IRData__ir_remote(
  void * untyped_member, size_t index)
{
  vehicle_interfaces__msg__IRData__Sequence * member =
    (vehicle_interfaces__msg__IRData__Sequence *)(untyped_member);
  return &member->data[index];
}

bool SensorData__rosidl_typesupport_introspection_c__resize_function__IRData__ir_remote(
  void * untyped_member, size_t size)
{
  vehicle_interfaces__msg__IRData__Sequence * member =
    (vehicle_interfaces__msg__IRData__Sequence *)(untyped_member);
  vehicle_interfaces__msg__IRData__Sequence__fini(member);
  return vehicle_interfaces__msg__IRData__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember SensorData__rosidl_typesupport_introspection_c__SensorData_message_member_array[10] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__SensorData, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "arduino_timestamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__SensorData, arduino_timestamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mpu",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__SensorData, mpu),  // bytes offset in struct
    NULL,  // default value
    SensorData__rosidl_typesupport_introspection_c__size_function__MPUData__mpu,  // size() function pointer
    SensorData__rosidl_typesupport_introspection_c__get_const_function__MPUData__mpu,  // get_const(index) function pointer
    SensorData__rosidl_typesupport_introspection_c__get_function__MPUData__mpu,  // get(index) function pointer
    SensorData__rosidl_typesupport_introspection_c__resize_function__MPUData__mpu  // resize(index) function pointer
  },
  {
    "qmc",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__SensorData, qmc),  // bytes offset in struct
    NULL,  // default value
    SensorData__rosidl_typesupport_introspection_c__size_function__QMCData__qmc,  // size() function pointer
    SensorData__rosidl_typesupport_introspection_c__get_const_function__QMCData__qmc,  // get_const(index) function pointer
    SensorData__rosidl_typesupport_introspection_c__get_function__QMCData__qmc,  // get(index) function pointer
    SensorData__rosidl_typesupport_introspection_c__resize_function__QMCData__qmc  // resize(index) function pointer
  },
  {
    "gps",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__SensorData, gps),  // bytes offset in struct
    NULL,  // default value
    SensorData__rosidl_typesupport_introspection_c__size_function__GPSData__gps,  // size() function pointer
    SensorData__rosidl_typesupport_introspection_c__get_const_function__GPSData__gps,  // get_const(index) function pointer
    SensorData__rosidl_typesupport_introspection_c__get_function__GPSData__gps,  // get(index) function pointer
    SensorData__rosidl_typesupport_introspection_c__resize_function__GPSData__gps  // resize(index) function pointer
  },
  {
    "tof",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__SensorData, tof),  // bytes offset in struct
    NULL,  // default value
    SensorData__rosidl_typesupport_introspection_c__size_function__ToFData__tof,  // size() function pointer
    SensorData__rosidl_typesupport_introspection_c__get_const_function__ToFData__tof,  // get_const(index) function pointer
    SensorData__rosidl_typesupport_introspection_c__get_function__ToFData__tof,  // get(index) function pointer
    SensorData__rosidl_typesupport_introspection_c__resize_function__ToFData__tof  // resize(index) function pointer
  },
  {
    "ultrasonic",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__SensorData, ultrasonic),  // bytes offset in struct
    NULL,  // default value
    SensorData__rosidl_typesupport_introspection_c__size_function__UltrasonicData__ultrasonic,  // size() function pointer
    SensorData__rosidl_typesupport_introspection_c__get_const_function__UltrasonicData__ultrasonic,  // get_const(index) function pointer
    SensorData__rosidl_typesupport_introspection_c__get_function__UltrasonicData__ultrasonic,  // get(index) function pointer
    SensorData__rosidl_typesupport_introspection_c__resize_function__UltrasonicData__ultrasonic  // resize(index) function pointer
  },
  {
    "temperature",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__SensorData, temperature),  // bytes offset in struct
    NULL,  // default value
    SensorData__rosidl_typesupport_introspection_c__size_function__TemperatureData__temperature,  // size() function pointer
    SensorData__rosidl_typesupport_introspection_c__get_const_function__TemperatureData__temperature,  // get_const(index) function pointer
    SensorData__rosidl_typesupport_introspection_c__get_function__TemperatureData__temperature,  // get(index) function pointer
    SensorData__rosidl_typesupport_introspection_c__resize_function__TemperatureData__temperature  // resize(index) function pointer
  },
  {
    "encoder",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__SensorData, encoder),  // bytes offset in struct
    NULL,  // default value
    SensorData__rosidl_typesupport_introspection_c__size_function__EncoderData__encoder,  // size() function pointer
    SensorData__rosidl_typesupport_introspection_c__get_const_function__EncoderData__encoder,  // get_const(index) function pointer
    SensorData__rosidl_typesupport_introspection_c__get_function__EncoderData__encoder,  // get(index) function pointer
    SensorData__rosidl_typesupport_introspection_c__resize_function__EncoderData__encoder  // resize(index) function pointer
  },
  {
    "ir_remote",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__SensorData, ir_remote),  // bytes offset in struct
    NULL,  // default value
    SensorData__rosidl_typesupport_introspection_c__size_function__IRData__ir_remote,  // size() function pointer
    SensorData__rosidl_typesupport_introspection_c__get_const_function__IRData__ir_remote,  // get_const(index) function pointer
    SensorData__rosidl_typesupport_introspection_c__get_function__IRData__ir_remote,  // get(index) function pointer
    SensorData__rosidl_typesupport_introspection_c__resize_function__IRData__ir_remote  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers SensorData__rosidl_typesupport_introspection_c__SensorData_message_members = {
  "vehicle_interfaces__msg",  // message namespace
  "SensorData",  // message name
  10,  // number of fields
  sizeof(vehicle_interfaces__msg__SensorData),
  SensorData__rosidl_typesupport_introspection_c__SensorData_message_member_array,  // message members
  SensorData__rosidl_typesupport_introspection_c__SensorData_init_function,  // function to initialize message memory (memory has to be allocated)
  SensorData__rosidl_typesupport_introspection_c__SensorData_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t SensorData__rosidl_typesupport_introspection_c__SensorData_message_type_support_handle = {
  0,
  &SensorData__rosidl_typesupport_introspection_c__SensorData_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, msg, SensorData)() {
  SensorData__rosidl_typesupport_introspection_c__SensorData_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  SensorData__rosidl_typesupport_introspection_c__SensorData_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, msg, MPUData)();
  SensorData__rosidl_typesupport_introspection_c__SensorData_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, msg, QMCData)();
  SensorData__rosidl_typesupport_introspection_c__SensorData_message_member_array[4].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, msg, GPSData)();
  SensorData__rosidl_typesupport_introspection_c__SensorData_message_member_array[5].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, msg, ToFData)();
  SensorData__rosidl_typesupport_introspection_c__SensorData_message_member_array[6].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, msg, UltrasonicData)();
  SensorData__rosidl_typesupport_introspection_c__SensorData_message_member_array[7].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, msg, TemperatureData)();
  SensorData__rosidl_typesupport_introspection_c__SensorData_message_member_array[8].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, msg, EncoderData)();
  SensorData__rosidl_typesupport_introspection_c__SensorData_message_member_array[9].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, msg, IRData)();
  if (!SensorData__rosidl_typesupport_introspection_c__SensorData_message_type_support_handle.typesupport_identifier) {
    SensorData__rosidl_typesupport_introspection_c__SensorData_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &SensorData__rosidl_typesupport_introspection_c__SensorData_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
