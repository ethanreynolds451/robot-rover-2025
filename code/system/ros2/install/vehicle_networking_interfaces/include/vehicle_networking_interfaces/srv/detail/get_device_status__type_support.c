// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vehicle_networking_interfaces:srv/GetDeviceStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vehicle_networking_interfaces/srv/detail/get_device_status__rosidl_typesupport_introspection_c.h"
#include "vehicle_networking_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vehicle_networking_interfaces/srv/detail/get_device_status__functions.h"
#include "vehicle_networking_interfaces/srv/detail/get_device_status__struct.h"


// Include directives for member types
// Member `device`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void GetDeviceStatus_Request__rosidl_typesupport_introspection_c__GetDeviceStatus_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_networking_interfaces__srv__GetDeviceStatus_Request__init(message_memory);
}

void GetDeviceStatus_Request__rosidl_typesupport_introspection_c__GetDeviceStatus_Request_fini_function(void * message_memory)
{
  vehicle_networking_interfaces__srv__GetDeviceStatus_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember GetDeviceStatus_Request__rosidl_typesupport_introspection_c__GetDeviceStatus_Request_message_member_array[1] = {
  {
    "device",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_networking_interfaces__srv__GetDeviceStatus_Request, device),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers GetDeviceStatus_Request__rosidl_typesupport_introspection_c__GetDeviceStatus_Request_message_members = {
  "vehicle_networking_interfaces__srv",  // message namespace
  "GetDeviceStatus_Request",  // message name
  1,  // number of fields
  sizeof(vehicle_networking_interfaces__srv__GetDeviceStatus_Request),
  GetDeviceStatus_Request__rosidl_typesupport_introspection_c__GetDeviceStatus_Request_message_member_array,  // message members
  GetDeviceStatus_Request__rosidl_typesupport_introspection_c__GetDeviceStatus_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  GetDeviceStatus_Request__rosidl_typesupport_introspection_c__GetDeviceStatus_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t GetDeviceStatus_Request__rosidl_typesupport_introspection_c__GetDeviceStatus_Request_message_type_support_handle = {
  0,
  &GetDeviceStatus_Request__rosidl_typesupport_introspection_c__GetDeviceStatus_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_networking_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_networking_interfaces, srv, GetDeviceStatus_Request)() {
  if (!GetDeviceStatus_Request__rosidl_typesupport_introspection_c__GetDeviceStatus_Request_message_type_support_handle.typesupport_identifier) {
    GetDeviceStatus_Request__rosidl_typesupport_introspection_c__GetDeviceStatus_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &GetDeviceStatus_Request__rosidl_typesupport_introspection_c__GetDeviceStatus_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vehicle_networking_interfaces/srv/detail/get_device_status__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vehicle_networking_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vehicle_networking_interfaces/srv/detail/get_device_status__functions.h"
// already included above
// #include "vehicle_networking_interfaces/srv/detail/get_device_status__struct.h"


// Include directives for member types
// Member `port`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void GetDeviceStatus_Response__rosidl_typesupport_introspection_c__GetDeviceStatus_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_networking_interfaces__srv__GetDeviceStatus_Response__init(message_memory);
}

void GetDeviceStatus_Response__rosidl_typesupport_introspection_c__GetDeviceStatus_Response_fini_function(void * message_memory)
{
  vehicle_networking_interfaces__srv__GetDeviceStatus_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember GetDeviceStatus_Response__rosidl_typesupport_introspection_c__GetDeviceStatus_Response_message_member_array[2] = {
  {
    "port",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_networking_interfaces__srv__GetDeviceStatus_Response, port),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "connected",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_networking_interfaces__srv__GetDeviceStatus_Response, connected),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers GetDeviceStatus_Response__rosidl_typesupport_introspection_c__GetDeviceStatus_Response_message_members = {
  "vehicle_networking_interfaces__srv",  // message namespace
  "GetDeviceStatus_Response",  // message name
  2,  // number of fields
  sizeof(vehicle_networking_interfaces__srv__GetDeviceStatus_Response),
  GetDeviceStatus_Response__rosidl_typesupport_introspection_c__GetDeviceStatus_Response_message_member_array,  // message members
  GetDeviceStatus_Response__rosidl_typesupport_introspection_c__GetDeviceStatus_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  GetDeviceStatus_Response__rosidl_typesupport_introspection_c__GetDeviceStatus_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t GetDeviceStatus_Response__rosidl_typesupport_introspection_c__GetDeviceStatus_Response_message_type_support_handle = {
  0,
  &GetDeviceStatus_Response__rosidl_typesupport_introspection_c__GetDeviceStatus_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_networking_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_networking_interfaces, srv, GetDeviceStatus_Response)() {
  if (!GetDeviceStatus_Response__rosidl_typesupport_introspection_c__GetDeviceStatus_Response_message_type_support_handle.typesupport_identifier) {
    GetDeviceStatus_Response__rosidl_typesupport_introspection_c__GetDeviceStatus_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &GetDeviceStatus_Response__rosidl_typesupport_introspection_c__GetDeviceStatus_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "vehicle_networking_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "vehicle_networking_interfaces/srv/detail/get_device_status__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers vehicle_networking_interfaces__srv__detail__get_device_status__rosidl_typesupport_introspection_c__GetDeviceStatus_service_members = {
  "vehicle_networking_interfaces__srv",  // service namespace
  "GetDeviceStatus",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // vehicle_networking_interfaces__srv__detail__get_device_status__rosidl_typesupport_introspection_c__GetDeviceStatus_Request_message_type_support_handle,
  NULL  // response message
  // vehicle_networking_interfaces__srv__detail__get_device_status__rosidl_typesupport_introspection_c__GetDeviceStatus_Response_message_type_support_handle
};

static rosidl_service_type_support_t vehicle_networking_interfaces__srv__detail__get_device_status__rosidl_typesupport_introspection_c__GetDeviceStatus_service_type_support_handle = {
  0,
  &vehicle_networking_interfaces__srv__detail__get_device_status__rosidl_typesupport_introspection_c__GetDeviceStatus_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_networking_interfaces, srv, GetDeviceStatus_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_networking_interfaces, srv, GetDeviceStatus_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_networking_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_networking_interfaces, srv, GetDeviceStatus)() {
  if (!vehicle_networking_interfaces__srv__detail__get_device_status__rosidl_typesupport_introspection_c__GetDeviceStatus_service_type_support_handle.typesupport_identifier) {
    vehicle_networking_interfaces__srv__detail__get_device_status__rosidl_typesupport_introspection_c__GetDeviceStatus_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)vehicle_networking_interfaces__srv__detail__get_device_status__rosidl_typesupport_introspection_c__GetDeviceStatus_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_networking_interfaces, srv, GetDeviceStatus_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_networking_interfaces, srv, GetDeviceStatus_Response)()->data;
  }

  return &vehicle_networking_interfaces__srv__detail__get_device_status__rosidl_typesupport_introspection_c__GetDeviceStatus_service_type_support_handle;
}
