// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from vehicle_interfaces:msg/ControlData.idl
// generated code does not contain a copyright notice
#include "vehicle_interfaces/msg/detail/control_data__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "vehicle_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "vehicle_interfaces/msg/detail/control_data__struct.h"
#include "vehicle_interfaces/msg/detail/control_data__functions.h"
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


// forward declare type support functions


using _ControlData__ros_msg_type = vehicle_interfaces__msg__ControlData;

static bool _ControlData__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _ControlData__ros_msg_type * ros_message = static_cast<const _ControlData__ros_msg_type *>(untyped_ros_message);
  // Field name: brake
  {
    cdr << (ros_message->brake ? true : false);
  }

  // Field name: reverse
  {
    cdr << (ros_message->reverse ? true : false);
  }

  // Field name: steering_reverse
  {
    cdr << (ros_message->steering_reverse ? true : false);
  }

  // Field name: shift_up
  {
    cdr << (ros_message->shift_up ? true : false);
  }

  // Field name: power
  {
    cdr << ros_message->power;
  }

  // Field name: steering_power
  {
    cdr << ros_message->steering_power;
  }

  return true;
}

static bool _ControlData__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _ControlData__ros_msg_type * ros_message = static_cast<_ControlData__ros_msg_type *>(untyped_ros_message);
  // Field name: brake
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->brake = tmp ? true : false;
  }

  // Field name: reverse
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->reverse = tmp ? true : false;
  }

  // Field name: steering_reverse
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->steering_reverse = tmp ? true : false;
  }

  // Field name: shift_up
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->shift_up = tmp ? true : false;
  }

  // Field name: power
  {
    cdr >> ros_message->power;
  }

  // Field name: steering_power
  {
    cdr >> ros_message->steering_power;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_interfaces
size_t get_serialized_size_vehicle_interfaces__msg__ControlData(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ControlData__ros_msg_type * ros_message = static_cast<const _ControlData__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name brake
  {
    size_t item_size = sizeof(ros_message->brake);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name reverse
  {
    size_t item_size = sizeof(ros_message->reverse);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name steering_reverse
  {
    size_t item_size = sizeof(ros_message->steering_reverse);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name shift_up
  {
    size_t item_size = sizeof(ros_message->shift_up);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name power
  {
    size_t item_size = sizeof(ros_message->power);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name steering_power
  {
    size_t item_size = sizeof(ros_message->steering_power);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _ControlData__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vehicle_interfaces__msg__ControlData(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_interfaces
size_t max_serialized_size_vehicle_interfaces__msg__ControlData(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: brake
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: reverse
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: steering_reverse
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: shift_up
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: power
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: steering_power
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static size_t _ControlData__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_vehicle_interfaces__msg__ControlData(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_ControlData = {
  "vehicle_interfaces::msg",
  "ControlData",
  _ControlData__cdr_serialize,
  _ControlData__cdr_deserialize,
  _ControlData__get_serialized_size,
  _ControlData__max_serialized_size
};

static rosidl_message_type_support_t _ControlData__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ControlData,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, ControlData)() {
  return &_ControlData__type_support;
}

#if defined(__cplusplus)
}
#endif
