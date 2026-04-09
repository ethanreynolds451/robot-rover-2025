// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vehicle_interfaces:srv/ResetSerialPort.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vehicle_interfaces/srv/detail/reset_serial_port__rosidl_typesupport_introspection_c.h"
#include "vehicle_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vehicle_interfaces/srv/detail/reset_serial_port__functions.h"
#include "vehicle_interfaces/srv/detail/reset_serial_port__struct.h"


// Include directives for member types
// Member `device`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void ResetSerialPort_Request__rosidl_typesupport_introspection_c__ResetSerialPort_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_interfaces__srv__ResetSerialPort_Request__init(message_memory);
}

void ResetSerialPort_Request__rosidl_typesupport_introspection_c__ResetSerialPort_Request_fini_function(void * message_memory)
{
  vehicle_interfaces__srv__ResetSerialPort_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember ResetSerialPort_Request__rosidl_typesupport_introspection_c__ResetSerialPort_Request_message_member_array[1] = {
  {
    "device",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__srv__ResetSerialPort_Request, device),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers ResetSerialPort_Request__rosidl_typesupport_introspection_c__ResetSerialPort_Request_message_members = {
  "vehicle_interfaces__srv",  // message namespace
  "ResetSerialPort_Request",  // message name
  1,  // number of fields
  sizeof(vehicle_interfaces__srv__ResetSerialPort_Request),
  ResetSerialPort_Request__rosidl_typesupport_introspection_c__ResetSerialPort_Request_message_member_array,  // message members
  ResetSerialPort_Request__rosidl_typesupport_introspection_c__ResetSerialPort_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  ResetSerialPort_Request__rosidl_typesupport_introspection_c__ResetSerialPort_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t ResetSerialPort_Request__rosidl_typesupport_introspection_c__ResetSerialPort_Request_message_type_support_handle = {
  0,
  &ResetSerialPort_Request__rosidl_typesupport_introspection_c__ResetSerialPort_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, srv, ResetSerialPort_Request)() {
  if (!ResetSerialPort_Request__rosidl_typesupport_introspection_c__ResetSerialPort_Request_message_type_support_handle.typesupport_identifier) {
    ResetSerialPort_Request__rosidl_typesupport_introspection_c__ResetSerialPort_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &ResetSerialPort_Request__rosidl_typesupport_introspection_c__ResetSerialPort_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vehicle_interfaces/srv/detail/reset_serial_port__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vehicle_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vehicle_interfaces/srv/detail/reset_serial_port__functions.h"
// already included above
// #include "vehicle_interfaces/srv/detail/reset_serial_port__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void ResetSerialPort_Response__rosidl_typesupport_introspection_c__ResetSerialPort_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_interfaces__srv__ResetSerialPort_Response__init(message_memory);
}

void ResetSerialPort_Response__rosidl_typesupport_introspection_c__ResetSerialPort_Response_fini_function(void * message_memory)
{
  vehicle_interfaces__srv__ResetSerialPort_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember ResetSerialPort_Response__rosidl_typesupport_introspection_c__ResetSerialPort_Response_message_member_array[1] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__srv__ResetSerialPort_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers ResetSerialPort_Response__rosidl_typesupport_introspection_c__ResetSerialPort_Response_message_members = {
  "vehicle_interfaces__srv",  // message namespace
  "ResetSerialPort_Response",  // message name
  1,  // number of fields
  sizeof(vehicle_interfaces__srv__ResetSerialPort_Response),
  ResetSerialPort_Response__rosidl_typesupport_introspection_c__ResetSerialPort_Response_message_member_array,  // message members
  ResetSerialPort_Response__rosidl_typesupport_introspection_c__ResetSerialPort_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  ResetSerialPort_Response__rosidl_typesupport_introspection_c__ResetSerialPort_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t ResetSerialPort_Response__rosidl_typesupport_introspection_c__ResetSerialPort_Response_message_type_support_handle = {
  0,
  &ResetSerialPort_Response__rosidl_typesupport_introspection_c__ResetSerialPort_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, srv, ResetSerialPort_Response)() {
  if (!ResetSerialPort_Response__rosidl_typesupport_introspection_c__ResetSerialPort_Response_message_type_support_handle.typesupport_identifier) {
    ResetSerialPort_Response__rosidl_typesupport_introspection_c__ResetSerialPort_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &ResetSerialPort_Response__rosidl_typesupport_introspection_c__ResetSerialPort_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "vehicle_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "vehicle_interfaces/srv/detail/reset_serial_port__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers vehicle_interfaces__srv__detail__reset_serial_port__rosidl_typesupport_introspection_c__ResetSerialPort_service_members = {
  "vehicle_interfaces__srv",  // service namespace
  "ResetSerialPort",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // vehicle_interfaces__srv__detail__reset_serial_port__rosidl_typesupport_introspection_c__ResetSerialPort_Request_message_type_support_handle,
  NULL  // response message
  // vehicle_interfaces__srv__detail__reset_serial_port__rosidl_typesupport_introspection_c__ResetSerialPort_Response_message_type_support_handle
};

static rosidl_service_type_support_t vehicle_interfaces__srv__detail__reset_serial_port__rosidl_typesupport_introspection_c__ResetSerialPort_service_type_support_handle = {
  0,
  &vehicle_interfaces__srv__detail__reset_serial_port__rosidl_typesupport_introspection_c__ResetSerialPort_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, srv, ResetSerialPort_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, srv, ResetSerialPort_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, srv, ResetSerialPort)() {
  if (!vehicle_interfaces__srv__detail__reset_serial_port__rosidl_typesupport_introspection_c__ResetSerialPort_service_type_support_handle.typesupport_identifier) {
    vehicle_interfaces__srv__detail__reset_serial_port__rosidl_typesupport_introspection_c__ResetSerialPort_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)vehicle_interfaces__srv__detail__reset_serial_port__rosidl_typesupport_introspection_c__ResetSerialPort_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, srv, ResetSerialPort_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, srv, ResetSerialPort_Response)()->data;
  }

  return &vehicle_interfaces__srv__detail__reset_serial_port__rosidl_typesupport_introspection_c__ResetSerialPort_service_type_support_handle;
}
