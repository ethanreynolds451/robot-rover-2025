// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from vehicle_networking_interfaces:srv/GetSerialPort.idl
// generated code does not contain a copyright notice
#include "vehicle_networking_interfaces/srv/detail/get_serial_port__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "vehicle_networking_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "vehicle_networking_interfaces/srv/detail/get_serial_port__struct.h"
#include "vehicle_networking_interfaces/srv/detail/get_serial_port__functions.h"
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

#include "rosidl_runtime_c/string.h"  // device
#include "rosidl_runtime_c/string_functions.h"  // device

// forward declare type support functions


using _GetSerialPort_Request__ros_msg_type = vehicle_networking_interfaces__srv__GetSerialPort_Request;

static bool _GetSerialPort_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _GetSerialPort_Request__ros_msg_type * ros_message = static_cast<const _GetSerialPort_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: device
  {
    const rosidl_runtime_c__String * str = &ros_message->device;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  return true;
}

static bool _GetSerialPort_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _GetSerialPort_Request__ros_msg_type * ros_message = static_cast<_GetSerialPort_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: device
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->device.data) {
      rosidl_runtime_c__String__init(&ros_message->device);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->device,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'device'\n");
      return false;
    }
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_networking_interfaces
size_t get_serialized_size_vehicle_networking_interfaces__srv__GetSerialPort_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _GetSerialPort_Request__ros_msg_type * ros_message = static_cast<const _GetSerialPort_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name device
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->device.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _GetSerialPort_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vehicle_networking_interfaces__srv__GetSerialPort_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_networking_interfaces
size_t max_serialized_size_vehicle_networking_interfaces__srv__GetSerialPort_Request(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: device
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  return current_alignment - initial_alignment;
}

static size_t _GetSerialPort_Request__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_vehicle_networking_interfaces__srv__GetSerialPort_Request(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_GetSerialPort_Request = {
  "vehicle_networking_interfaces::srv",
  "GetSerialPort_Request",
  _GetSerialPort_Request__cdr_serialize,
  _GetSerialPort_Request__cdr_deserialize,
  _GetSerialPort_Request__get_serialized_size,
  _GetSerialPort_Request__max_serialized_size
};

static rosidl_message_type_support_t _GetSerialPort_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_GetSerialPort_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_networking_interfaces, srv, GetSerialPort_Request)() {
  return &_GetSerialPort_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "vehicle_networking_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "vehicle_networking_interfaces/srv/detail/get_serial_port__struct.h"
// already included above
// #include "vehicle_networking_interfaces/srv/detail/get_serial_port__functions.h"
// already included above
// #include "fastcdr/Cdr.h"

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

// already included above
// #include "rosidl_runtime_c/string.h"  // port
// already included above
// #include "rosidl_runtime_c/string_functions.h"  // port

// forward declare type support functions


using _GetSerialPort_Response__ros_msg_type = vehicle_networking_interfaces__srv__GetSerialPort_Response;

static bool _GetSerialPort_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _GetSerialPort_Response__ros_msg_type * ros_message = static_cast<const _GetSerialPort_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: port
  {
    const rosidl_runtime_c__String * str = &ros_message->port;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  return true;
}

static bool _GetSerialPort_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _GetSerialPort_Response__ros_msg_type * ros_message = static_cast<_GetSerialPort_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: port
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->port.data) {
      rosidl_runtime_c__String__init(&ros_message->port);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->port,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'port'\n");
      return false;
    }
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_networking_interfaces
size_t get_serialized_size_vehicle_networking_interfaces__srv__GetSerialPort_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _GetSerialPort_Response__ros_msg_type * ros_message = static_cast<const _GetSerialPort_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name port
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->port.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _GetSerialPort_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vehicle_networking_interfaces__srv__GetSerialPort_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_networking_interfaces
size_t max_serialized_size_vehicle_networking_interfaces__srv__GetSerialPort_Response(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: port
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  return current_alignment - initial_alignment;
}

static size_t _GetSerialPort_Response__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_vehicle_networking_interfaces__srv__GetSerialPort_Response(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_GetSerialPort_Response = {
  "vehicle_networking_interfaces::srv",
  "GetSerialPort_Response",
  _GetSerialPort_Response__cdr_serialize,
  _GetSerialPort_Response__cdr_deserialize,
  _GetSerialPort_Response__get_serialized_size,
  _GetSerialPort_Response__max_serialized_size
};

static rosidl_message_type_support_t _GetSerialPort_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_GetSerialPort_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_networking_interfaces, srv, GetSerialPort_Response)() {
  return &_GetSerialPort_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "vehicle_networking_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "vehicle_networking_interfaces/srv/get_serial_port.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t GetSerialPort__callbacks = {
  "vehicle_networking_interfaces::srv",
  "GetSerialPort",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_networking_interfaces, srv, GetSerialPort_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_networking_interfaces, srv, GetSerialPort_Response)(),
};

static rosidl_service_type_support_t GetSerialPort__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &GetSerialPort__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_networking_interfaces, srv, GetSerialPort)() {
  return &GetSerialPort__handle;
}

#if defined(__cplusplus)
}
#endif
