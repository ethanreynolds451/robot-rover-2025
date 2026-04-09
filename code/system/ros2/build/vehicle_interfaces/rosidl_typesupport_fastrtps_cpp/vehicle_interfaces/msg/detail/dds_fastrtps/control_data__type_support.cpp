// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from vehicle_interfaces:msg/ControlData.idl
// generated code does not contain a copyright notice
#include "vehicle_interfaces/msg/detail/control_data__rosidl_typesupport_fastrtps_cpp.hpp"
#include "vehicle_interfaces/msg/detail/control_data__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace vehicle_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_interfaces
cdr_serialize(
  const vehicle_interfaces::msg::ControlData & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: brake
  cdr << (ros_message.brake ? true : false);
  // Member: reverse
  cdr << (ros_message.reverse ? true : false);
  // Member: steering_reverse
  cdr << (ros_message.steering_reverse ? true : false);
  // Member: shift_up
  cdr << (ros_message.shift_up ? true : false);
  // Member: power
  cdr << ros_message.power;
  // Member: steering_power
  cdr << ros_message.steering_power;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vehicle_interfaces::msg::ControlData & ros_message)
{
  // Member: brake
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.brake = tmp ? true : false;
  }

  // Member: reverse
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.reverse = tmp ? true : false;
  }

  // Member: steering_reverse
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.steering_reverse = tmp ? true : false;
  }

  // Member: shift_up
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.shift_up = tmp ? true : false;
  }

  // Member: power
  cdr >> ros_message.power;

  // Member: steering_power
  cdr >> ros_message.steering_power;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_interfaces
get_serialized_size(
  const vehicle_interfaces::msg::ControlData & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: brake
  {
    size_t item_size = sizeof(ros_message.brake);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: reverse
  {
    size_t item_size = sizeof(ros_message.reverse);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: steering_reverse
  {
    size_t item_size = sizeof(ros_message.steering_reverse);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: shift_up
  {
    size_t item_size = sizeof(ros_message.shift_up);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: power
  {
    size_t item_size = sizeof(ros_message.power);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: steering_power
  {
    size_t item_size = sizeof(ros_message.steering_power);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_interfaces
max_serialized_size_ControlData(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: brake
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: reverse
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: steering_reverse
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: shift_up
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: power
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: steering_power
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static bool _ControlData__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const vehicle_interfaces::msg::ControlData *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _ControlData__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<vehicle_interfaces::msg::ControlData *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _ControlData__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const vehicle_interfaces::msg::ControlData *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _ControlData__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_ControlData(full_bounded, 0);
}

static message_type_support_callbacks_t _ControlData__callbacks = {
  "vehicle_interfaces::msg",
  "ControlData",
  _ControlData__cdr_serialize,
  _ControlData__cdr_deserialize,
  _ControlData__get_serialized_size,
  _ControlData__max_serialized_size
};

static rosidl_message_type_support_t _ControlData__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_ControlData__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace vehicle_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_vehicle_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<vehicle_interfaces::msg::ControlData>()
{
  return &vehicle_interfaces::msg::typesupport_fastrtps_cpp::_ControlData__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_interfaces, msg, ControlData)() {
  return &vehicle_interfaces::msg::typesupport_fastrtps_cpp::_ControlData__handle;
}

#ifdef __cplusplus
}
#endif
