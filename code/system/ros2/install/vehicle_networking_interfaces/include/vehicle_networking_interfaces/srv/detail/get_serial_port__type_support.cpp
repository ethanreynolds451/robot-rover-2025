// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from vehicle_networking_interfaces:srv/GetSerialPort.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "vehicle_networking_interfaces/srv/detail/get_serial_port__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace vehicle_networking_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void GetSerialPort_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) vehicle_networking_interfaces::srv::GetSerialPort_Request(_init);
}

void GetSerialPort_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<vehicle_networking_interfaces::srv::GetSerialPort_Request *>(message_memory);
  typed_message->~GetSerialPort_Request();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GetSerialPort_Request_message_member_array[1] = {
  {
    "device",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_networking_interfaces::srv::GetSerialPort_Request, device),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GetSerialPort_Request_message_members = {
  "vehicle_networking_interfaces::srv",  // message namespace
  "GetSerialPort_Request",  // message name
  1,  // number of fields
  sizeof(vehicle_networking_interfaces::srv::GetSerialPort_Request),
  GetSerialPort_Request_message_member_array,  // message members
  GetSerialPort_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  GetSerialPort_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GetSerialPort_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetSerialPort_Request_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace vehicle_networking_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vehicle_networking_interfaces::srv::GetSerialPort_Request>()
{
  return &::vehicle_networking_interfaces::srv::rosidl_typesupport_introspection_cpp::GetSerialPort_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vehicle_networking_interfaces, srv, GetSerialPort_Request)() {
  return &::vehicle_networking_interfaces::srv::rosidl_typesupport_introspection_cpp::GetSerialPort_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "vehicle_networking_interfaces/srv/detail/get_serial_port__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace vehicle_networking_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void GetSerialPort_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) vehicle_networking_interfaces::srv::GetSerialPort_Response(_init);
}

void GetSerialPort_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<vehicle_networking_interfaces::srv::GetSerialPort_Response *>(message_memory);
  typed_message->~GetSerialPort_Response();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GetSerialPort_Response_message_member_array[1] = {
  {
    "port",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_networking_interfaces::srv::GetSerialPort_Response, port),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GetSerialPort_Response_message_members = {
  "vehicle_networking_interfaces::srv",  // message namespace
  "GetSerialPort_Response",  // message name
  1,  // number of fields
  sizeof(vehicle_networking_interfaces::srv::GetSerialPort_Response),
  GetSerialPort_Response_message_member_array,  // message members
  GetSerialPort_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  GetSerialPort_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GetSerialPort_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetSerialPort_Response_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace vehicle_networking_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vehicle_networking_interfaces::srv::GetSerialPort_Response>()
{
  return &::vehicle_networking_interfaces::srv::rosidl_typesupport_introspection_cpp::GetSerialPort_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vehicle_networking_interfaces, srv, GetSerialPort_Response)() {
  return &::vehicle_networking_interfaces::srv::rosidl_typesupport_introspection_cpp::GetSerialPort_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"
// already included above
// #include "vehicle_networking_interfaces/srv/detail/get_serial_port__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace vehicle_networking_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers GetSerialPort_service_members = {
  "vehicle_networking_interfaces::srv",  // service namespace
  "GetSerialPort",  // service name
  // these two fields are initialized below on the first access
  // see get_service_type_support_handle<vehicle_networking_interfaces::srv::GetSerialPort>()
  nullptr,  // request message
  nullptr  // response message
};

static const rosidl_service_type_support_t GetSerialPort_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetSerialPort_service_members,
  get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace vehicle_networking_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<vehicle_networking_interfaces::srv::GetSerialPort>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::vehicle_networking_interfaces::srv::rosidl_typesupport_introspection_cpp::GetSerialPort_service_type_support_handle;
  // get a non-const and properly typed version of the data void *
  auto service_members = const_cast<::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
    static_cast<const ::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
      service_type_support->data));
  // make sure that both the request_members_ and the response_members_ are initialized
  // if they are not, initialize them
  if (
    service_members->request_members_ == nullptr ||
    service_members->response_members_ == nullptr)
  {
    // initialize the request_members_ with the static function from the external library
    service_members->request_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::vehicle_networking_interfaces::srv::GetSerialPort_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::vehicle_networking_interfaces::srv::GetSerialPort_Response
      >()->data
      );
  }
  // finally return the properly initialized service_type_support handle
  return service_type_support;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vehicle_networking_interfaces, srv, GetSerialPort)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<vehicle_networking_interfaces::srv::GetSerialPort>();
}

#ifdef __cplusplus
}
#endif
