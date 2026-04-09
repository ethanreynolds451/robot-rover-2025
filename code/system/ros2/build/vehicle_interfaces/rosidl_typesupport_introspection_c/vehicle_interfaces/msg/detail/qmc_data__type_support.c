// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vehicle_interfaces:msg/QMCData.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vehicle_interfaces/msg/detail/qmc_data__rosidl_typesupport_introspection_c.h"
#include "vehicle_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vehicle_interfaces/msg/detail/qmc_data__functions.h"
#include "vehicle_interfaces/msg/detail/qmc_data__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `is_valid`
#include "std_msgs/msg/bool.h"
// Member `is_valid`
#include "std_msgs/msg/detail/bool__rosidl_typesupport_introspection_c.h"
// Member `id`
#include "rosidl_runtime_c/string_functions.h"
// Member `mag`
#include "sensor_msgs/msg/magnetic_field.h"
// Member `mag`
#include "sensor_msgs/msg/detail/magnetic_field__rosidl_typesupport_introspection_c.h"
// Member `temp`
#include "sensor_msgs/msg/temperature.h"
// Member `temp`
#include "sensor_msgs/msg/detail/temperature__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void QMCData__rosidl_typesupport_introspection_c__QMCData_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_interfaces__msg__QMCData__init(message_memory);
}

void QMCData__rosidl_typesupport_introspection_c__QMCData_fini_function(void * message_memory)
{
  vehicle_interfaces__msg__QMCData__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember QMCData__rosidl_typesupport_introspection_c__QMCData_message_member_array[6] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__QMCData, header),  // bytes offset in struct
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
    offsetof(vehicle_interfaces__msg__QMCData, is_valid),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__QMCData, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mag",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__QMCData, mag),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "heading",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__QMCData, heading),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "temp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__msg__QMCData, temp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers QMCData__rosidl_typesupport_introspection_c__QMCData_message_members = {
  "vehicle_interfaces__msg",  // message namespace
  "QMCData",  // message name
  6,  // number of fields
  sizeof(vehicle_interfaces__msg__QMCData),
  QMCData__rosidl_typesupport_introspection_c__QMCData_message_member_array,  // message members
  QMCData__rosidl_typesupport_introspection_c__QMCData_init_function,  // function to initialize message memory (memory has to be allocated)
  QMCData__rosidl_typesupport_introspection_c__QMCData_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t QMCData__rosidl_typesupport_introspection_c__QMCData_message_type_support_handle = {
  0,
  &QMCData__rosidl_typesupport_introspection_c__QMCData_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, msg, QMCData)() {
  QMCData__rosidl_typesupport_introspection_c__QMCData_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  QMCData__rosidl_typesupport_introspection_c__QMCData_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Bool)();
  QMCData__rosidl_typesupport_introspection_c__QMCData_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sensor_msgs, msg, MagneticField)();
  QMCData__rosidl_typesupport_introspection_c__QMCData_message_member_array[5].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sensor_msgs, msg, Temperature)();
  if (!QMCData__rosidl_typesupport_introspection_c__QMCData_message_type_support_handle.typesupport_identifier) {
    QMCData__rosidl_typesupport_introspection_c__QMCData_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &QMCData__rosidl_typesupport_introspection_c__QMCData_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
