// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from vehicle_interfaces:msg/TemperatureData.idl
// generated code does not contain a copyright notice
#include "vehicle_interfaces/msg/detail/temperature_data__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "vehicle_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "vehicle_interfaces/msg/detail/temperature_data__struct.h"
#include "vehicle_interfaces/msg/detail/temperature_data__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "sensor_msgs/msg/detail/temperature__functions.h"  // temp
#include "std_msgs/msg/detail/bool__functions.h"  // is_valid
#include "std_msgs/msg/detail/header__functions.h"  // header

// forward declare type support functions
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vehicle_interfaces
size_t get_serialized_size_sensor_msgs__msg__Temperature(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vehicle_interfaces
size_t max_serialized_size_sensor_msgs__msg__Temperature(
  bool & full_bounded,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vehicle_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, sensor_msgs, msg, Temperature)();
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vehicle_interfaces
size_t get_serialized_size_std_msgs__msg__Bool(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vehicle_interfaces
size_t max_serialized_size_std_msgs__msg__Bool(
  bool & full_bounded,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vehicle_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, std_msgs, msg, Bool)();
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vehicle_interfaces
size_t get_serialized_size_std_msgs__msg__Header(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vehicle_interfaces
size_t max_serialized_size_std_msgs__msg__Header(
  bool & full_bounded,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vehicle_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, std_msgs, msg, Header)();


using _TemperatureData__ros_msg_type = vehicle_interfaces__msg__TemperatureData;

static bool _TemperatureData__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _TemperatureData__ros_msg_type * ros_message = static_cast<const _TemperatureData__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->header, cdr))
    {
      return false;
    }
  }

  // Field name: is_valid
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Bool
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->is_valid, cdr))
    {
      return false;
    }
  }

  // Field name: temp
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, sensor_msgs, msg, Temperature
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->temp, cdr))
    {
      return false;
    }
  }

  return true;
}

static bool _TemperatureData__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _TemperatureData__ros_msg_type * ros_message = static_cast<_TemperatureData__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->header))
    {
      return false;
    }
  }

  // Field name: is_valid
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Bool
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->is_valid))
    {
      return false;
    }
  }

  // Field name: temp
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, sensor_msgs, msg, Temperature
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->temp))
    {
      return false;
    }
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_interfaces
size_t get_serialized_size_vehicle_interfaces__msg__TemperatureData(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _TemperatureData__ros_msg_type * ros_message = static_cast<const _TemperatureData__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name header

  current_alignment += get_serialized_size_std_msgs__msg__Header(
    &(ros_message->header), current_alignment);
  // field.name is_valid

  current_alignment += get_serialized_size_std_msgs__msg__Bool(
    &(ros_message->is_valid), current_alignment);
  // field.name temp

  current_alignment += get_serialized_size_sensor_msgs__msg__Temperature(
    &(ros_message->temp), current_alignment);

  return current_alignment - initial_alignment;
}

static uint32_t _TemperatureData__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vehicle_interfaces__msg__TemperatureData(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_interfaces
size_t max_serialized_size_vehicle_interfaces__msg__TemperatureData(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: header
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_std_msgs__msg__Header(
        full_bounded, current_alignment);
    }
  }
  // member: is_valid
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_std_msgs__msg__Bool(
        full_bounded, current_alignment);
    }
  }
  // member: temp
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_sensor_msgs__msg__Temperature(
        full_bounded, current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

static size_t _TemperatureData__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_vehicle_interfaces__msg__TemperatureData(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_TemperatureData = {
  "vehicle_interfaces::msg",
  "TemperatureData",
  _TemperatureData__cdr_serialize,
  _TemperatureData__cdr_deserialize,
  _TemperatureData__get_serialized_size,
  _TemperatureData__max_serialized_size
};

static rosidl_message_type_support_t _TemperatureData__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_TemperatureData,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, TemperatureData)() {
  return &_TemperatureData__type_support;
}

#if defined(__cplusplus)
}
#endif
