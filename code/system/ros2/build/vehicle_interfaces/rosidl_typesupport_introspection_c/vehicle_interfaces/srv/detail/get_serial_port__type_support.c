// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vehicle_interfaces:srv/GetSerialPort.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vehicle_interfaces/srv/detail/get_serial_port__rosidl_typesupport_introspection_c.h"
#include "vehicle_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vehicle_interfaces/srv/detail/get_serial_port__functions.h"
#include "vehicle_interfaces/srv/detail/get_serial_port__struct.h"


// Include directives for member types
// Member `device`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void GetSerialPort_Request__rosidl_typesupport_introspection_c__GetSerialPort_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_interfaces__srv__GetSerialPort_Request__init(message_memory);
}

void GetSerialPort_Request__rosidl_typesupport_introspection_c__GetSerialPort_Request_fini_function(void * message_memory)
{
  vehicle_interfaces__srv__GetSerialPort_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember GetSerialPort_Request__rosidl_typesupport_introspection_c__GetSerialPort_Request_message_member_array[1] = {
  {
    "device",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__srv__GetSerialPort_Request, device),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers GetSerialPort_Request__rosidl_typesupport_introspection_c__GetSerialPort_Request_message_members = {
  "vehicle_interfaces__srv",  // message namespace
  "GetSerialPort_Request",  // message name
  1,  // number of fields
  sizeof(vehicle_interfaces__srv__GetSerialPort_Request),
  GetSerialPort_Request__rosidl_typesupport_introspection_c__GetSerialPort_Request_message_member_array,  // message members
  GetSerialPort_Request__rosidl_typesupport_introspection_c__GetSerialPort_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  GetSerialPort_Request__rosidl_typesupport_introspection_c__GetSerialPort_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t GetSerialPort_Request__rosidl_typesupport_introspection_c__GetSerialPort_Request_message_type_support_handle = {
  0,
  &GetSerialPort_Request__rosidl_typesupport_introspection_c__GetSerialPort_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, srv, GetSerialPort_Request)() {
  if (!GetSerialPort_Request__rosidl_typesupport_introspection_c__GetSerialPort_Request_message_type_support_handle.typesupport_identifier) {
    GetSerialPort_Request__rosidl_typesupport_introspection_c__GetSerialPort_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &GetSerialPort_Request__rosidl_typesupport_introspection_c__GetSerialPort_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vehicle_interfaces/srv/detail/get_serial_port__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vehicle_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vehicle_interfaces/srv/detail/get_serial_port__functions.h"
// already included above
// #include "vehicle_interfaces/srv/detail/get_serial_port__struct.h"


// Include directives for member types
// Member `port`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void GetSerialPort_Response__rosidl_typesupport_introspection_c__GetSerialPort_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_interfaces__srv__GetSerialPort_Response__init(message_memory);
}

void GetSerialPort_Response__rosidl_typesupport_introspection_c__GetSerialPort_Response_fini_function(void * message_memory)
{
  vehicle_interfaces__srv__GetSerialPort_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember GetSerialPort_Response__rosidl_typesupport_introspection_c__GetSerialPort_Response_message_member_array[1] = {
  {
    "port",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces__srv__GetSerialPort_Response, port),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers GetSerialPort_Response__rosidl_typesupport_introspection_c__GetSerialPort_Response_message_members = {
  "vehicle_interfaces__srv",  // message namespace
  "GetSerialPort_Response",  // message name
  1,  // number of fields
  sizeof(vehicle_interfaces__srv__GetSerialPort_Response),
  GetSerialPort_Response__rosidl_typesupport_introspection_c__GetSerialPort_Response_message_member_array,  // message members
  GetSerialPort_Response__rosidl_typesupport_introspection_c__GetSerialPort_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  GetSerialPort_Response__rosidl_typesupport_introspection_c__GetSerialPort_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t GetSerialPort_Response__rosidl_typesupport_introspection_c__GetSerialPort_Response_message_type_support_handle = {
  0,
  &GetSerialPort_Response__rosidl_typesupport_introspection_c__GetSerialPort_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, srv, GetSerialPort_Response)() {
  if (!GetSerialPort_Response__rosidl_typesupport_introspection_c__GetSerialPort_Response_message_type_support_handle.typesupport_identifier) {
    GetSerialPort_Response__rosidl_typesupport_introspection_c__GetSerialPort_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &GetSerialPort_Response__rosidl_typesupport_introspection_c__GetSerialPort_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "vehicle_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "vehicle_interfaces/srv/detail/get_serial_port__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers vehicle_interfaces__srv__detail__get_serial_port__rosidl_typesupport_introspection_c__GetSerialPort_service_members = {
  "vehicle_interfaces__srv",  // service namespace
  "GetSerialPort",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // vehicle_interfaces__srv__detail__get_serial_port__rosidl_typesupport_introspection_c__GetSerialPort_Request_message_type_support_handle,
  NULL  // response message
  // vehicle_interfaces__srv__detail__get_serial_port__rosidl_typesupport_introspection_c__GetSerialPort_Response_message_type_support_handle
};

static rosidl_service_type_support_t vehicle_interfaces__srv__detail__get_serial_port__rosidl_typesupport_introspection_c__GetSerialPort_service_type_support_handle = {
  0,
  &vehicle_interfaces__srv__detail__get_serial_port__rosidl_typesupport_introspection_c__GetSerialPort_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, srv, GetSerialPort_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, srv, GetSerialPort_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, srv, GetSerialPort)() {
  if (!vehicle_interfaces__srv__detail__get_serial_port__rosidl_typesupport_introspection_c__GetSerialPort_service_type_support_handle.typesupport_identifier) {
    vehicle_interfaces__srv__detail__get_serial_port__rosidl_typesupport_introspection_c__GetSerialPort_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)vehicle_interfaces__srv__detail__get_serial_port__rosidl_typesupport_introspection_c__GetSerialPort_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, srv, GetSerialPort_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interfaces, srv, GetSerialPort_Response)()->data;
  }

  return &vehicle_interfaces__srv__detail__get_serial_port__rosidl_typesupport_introspection_c__GetSerialPort_service_type_support_handle;
}
