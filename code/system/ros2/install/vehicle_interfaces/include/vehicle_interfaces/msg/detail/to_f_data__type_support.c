// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vehicle_interfaces:msg/ToFData.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vehicle_interfaces/msg/detail/to_f_data__rosidl_typesupport_introspection_c.h"
#include "vehicle_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vehicle_interfaces/msg/detail/to_f_data__functions.h"
#include "vehicle_interfaces/msg/detail/to_f_data__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `is_valid`
#include "std_msgs/msg/bool.h"
// Member `is_valid`
#include "std_msgs/msg/detail/bool__rosidl_typesupport_introspection_c.h"
// Member `range`
#include "sensor_msgs/msg/range.h"
// Member `range`
#include "sensor_msgs/msg/detail/range__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void ToFData__rosidl_typesupport_introspection_c__ToFData_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_interfaces__msg__ToFData__init(message_memory);
}

void ToFData__rosidl_typesupport_introspection_c__ToFData_fini_function(void * message_memory)
{
  vehicle_interfaces__msg__ToFData__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember ToFData__rosidl_typesupport_introspection_c__ToFData_message_member_array[5] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__ToFData, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "is_valid",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__ToFData, is_valid),  // bytes offset in struct
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
    offsetof(vehicle_interfaces__msg__ToFData, arduino_timestamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "range",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__ToFData, range),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "intensity",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__ToFData, intensity),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers ToFData__rosidl_typesupport_introspection_c__ToFData_message_members = {
  "vehicle_interfaces__msg",  // message namespace
  "ToFData",  // message name
  5,  // number of fields
  sizeof(vehicle_interfaces__msg__ToFData),
  ToFData__rosidl_typesupport_introspection_c__ToFData_message_member_array,  // message members
  ToFData__rosidl_typesupport_introspection_c__ToFData_init_function,  // function to initialize message memory (memory has to be allocated)
  ToFData__rosidl_typesupport_introspection_c__ToFData_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t ToFData__rosidl_typesupport_introspection_c__ToFData_message_type_support_handle = {
  0,
  &ToFData__rosidl_typesupport_introspection_c__ToFData_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, msg, ToFData)() {
  ToFData__rosidl_typesupport_introspection_c__ToFData_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  ToFData__rosidl_typesupport_introspection_c__ToFData_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Bool)();
  ToFData__rosidl_typesupport_introspection_c__ToFData_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sensor_msgs, msg, Range)();
  if (!ToFData__rosidl_typesupport_introspection_c__ToFData_message_type_support_handle.typesupport_identifier) {
    ToFData__rosidl_typesupport_introspection_c__ToFData_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &ToFData__rosidl_typesupport_introspection_c__ToFData_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
