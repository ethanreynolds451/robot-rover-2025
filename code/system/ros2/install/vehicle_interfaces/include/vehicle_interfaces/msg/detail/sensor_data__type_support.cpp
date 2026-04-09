// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from vehicle_interfaces:msg/SensorData.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "vehicle_interfaces/msg/detail/sensor_data__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace vehicle_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void SensorData_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) vehicle_interfaces::msg::SensorData(_init);
}

void SensorData_fini_function(void * message_memory)
{
  auto typed_message = static_cast<vehicle_interfaces::msg::SensorData *>(message_memory);
  typed_message->~SensorData();
}

size_t size_function__SensorData__mpu(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<vehicle_interfaces::msg::MPUData> *>(untyped_member);
  return member->size();
}

const void * get_const_function__SensorData__mpu(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<vehicle_interfaces::msg::MPUData> *>(untyped_member);
  return &member[index];
}

void * get_function__SensorData__mpu(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<vehicle_interfaces::msg::MPUData> *>(untyped_member);
  return &member[index];
}

void resize_function__SensorData__mpu(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<vehicle_interfaces::msg::MPUData> *>(untyped_member);
  member->resize(size);
}

size_t size_function__SensorData__qmc(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<vehicle_interfaces::msg::QMCData> *>(untyped_member);
  return member->size();
}

const void * get_const_function__SensorData__qmc(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<vehicle_interfaces::msg::QMCData> *>(untyped_member);
  return &member[index];
}

void * get_function__SensorData__qmc(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<vehicle_interfaces::msg::QMCData> *>(untyped_member);
  return &member[index];
}

void resize_function__SensorData__qmc(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<vehicle_interfaces::msg::QMCData> *>(untyped_member);
  member->resize(size);
}

size_t size_function__SensorData__gps(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<vehicle_interfaces::msg::GPSData> *>(untyped_member);
  return member->size();
}

const void * get_const_function__SensorData__gps(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<vehicle_interfaces::msg::GPSData> *>(untyped_member);
  return &member[index];
}

void * get_function__SensorData__gps(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<vehicle_interfaces::msg::GPSData> *>(untyped_member);
  return &member[index];
}

void resize_function__SensorData__gps(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<vehicle_interfaces::msg::GPSData> *>(untyped_member);
  member->resize(size);
}

size_t size_function__SensorData__tof(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<vehicle_interfaces::msg::ToFData> *>(untyped_member);
  return member->size();
}

const void * get_const_function__SensorData__tof(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<vehicle_interfaces::msg::ToFData> *>(untyped_member);
  return &member[index];
}

void * get_function__SensorData__tof(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<vehicle_interfaces::msg::ToFData> *>(untyped_member);
  return &member[index];
}

void resize_function__SensorData__tof(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<vehicle_interfaces::msg::ToFData> *>(untyped_member);
  member->resize(size);
}

size_t size_function__SensorData__ultrasonic(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<vehicle_interfaces::msg::UltrasonicData> *>(untyped_member);
  return member->size();
}

const void * get_const_function__SensorData__ultrasonic(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<vehicle_interfaces::msg::UltrasonicData> *>(untyped_member);
  return &member[index];
}

void * get_function__SensorData__ultrasonic(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<vehicle_interfaces::msg::UltrasonicData> *>(untyped_member);
  return &member[index];
}

void resize_function__SensorData__ultrasonic(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<vehicle_interfaces::msg::UltrasonicData> *>(untyped_member);
  member->resize(size);
}

size_t size_function__SensorData__temperature(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<vehicle_interfaces::msg::TemperatureData> *>(untyped_member);
  return member->size();
}

const void * get_const_function__SensorData__temperature(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<vehicle_interfaces::msg::TemperatureData> *>(untyped_member);
  return &member[index];
}

void * get_function__SensorData__temperature(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<vehicle_interfaces::msg::TemperatureData> *>(untyped_member);
  return &member[index];
}

void resize_function__SensorData__temperature(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<vehicle_interfaces::msg::TemperatureData> *>(untyped_member);
  member->resize(size);
}

size_t size_function__SensorData__encoder(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<vehicle_interfaces::msg::EncoderData> *>(untyped_member);
  return member->size();
}

const void * get_const_function__SensorData__encoder(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<vehicle_interfaces::msg::EncoderData> *>(untyped_member);
  return &member[index];
}

void * get_function__SensorData__encoder(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<vehicle_interfaces::msg::EncoderData> *>(untyped_member);
  return &member[index];
}

void resize_function__SensorData__encoder(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<vehicle_interfaces::msg::EncoderData> *>(untyped_member);
  member->resize(size);
}

size_t size_function__SensorData__ir_remote(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<vehicle_interfaces::msg::IRData> *>(untyped_member);
  return member->size();
}

const void * get_const_function__SensorData__ir_remote(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<vehicle_interfaces::msg::IRData> *>(untyped_member);
  return &member[index];
}

void * get_function__SensorData__ir_remote(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<vehicle_interfaces::msg::IRData> *>(untyped_member);
  return &member[index];
}

void resize_function__SensorData__ir_remote(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<vehicle_interfaces::msg::IRData> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember SensorData_message_member_array[10] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces::msg::SensorData, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "arduino_timestamp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces::msg::SensorData, arduino_timestamp),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "mpu",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<vehicle_interfaces::msg::MPUData>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces::msg::SensorData, mpu),  // bytes offset in struct
    nullptr,  // default value
    size_function__SensorData__mpu,  // size() function pointer
    get_const_function__SensorData__mpu,  // get_const(index) function pointer
    get_function__SensorData__mpu,  // get(index) function pointer
    resize_function__SensorData__mpu  // resize(index) function pointer
  },
  {
    "qmc",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<vehicle_interfaces::msg::QMCData>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces::msg::SensorData, qmc),  // bytes offset in struct
    nullptr,  // default value
    size_function__SensorData__qmc,  // size() function pointer
    get_const_function__SensorData__qmc,  // get_const(index) function pointer
    get_function__SensorData__qmc,  // get(index) function pointer
    resize_function__SensorData__qmc  // resize(index) function pointer
  },
  {
    "gps",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<vehicle_interfaces::msg::GPSData>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces::msg::SensorData, gps),  // bytes offset in struct
    nullptr,  // default value
    size_function__SensorData__gps,  // size() function pointer
    get_const_function__SensorData__gps,  // get_const(index) function pointer
    get_function__SensorData__gps,  // get(index) function pointer
    resize_function__SensorData__gps  // resize(index) function pointer
  },
  {
    "tof",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<vehicle_interfaces::msg::ToFData>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces::msg::SensorData, tof),  // bytes offset in struct
    nullptr,  // default value
    size_function__SensorData__tof,  // size() function pointer
    get_const_function__SensorData__tof,  // get_const(index) function pointer
    get_function__SensorData__tof,  // get(index) function pointer
    resize_function__SensorData__tof  // resize(index) function pointer
  },
  {
    "ultrasonic",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<vehicle_interfaces::msg::UltrasonicData>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces::msg::SensorData, ultrasonic),  // bytes offset in struct
    nullptr,  // default value
    size_function__SensorData__ultrasonic,  // size() function pointer
    get_const_function__SensorData__ultrasonic,  // get_const(index) function pointer
    get_function__SensorData__ultrasonic,  // get(index) function pointer
    resize_function__SensorData__ultrasonic  // resize(index) function pointer
  },
  {
    "temperature",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<vehicle_interfaces::msg::TemperatureData>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces::msg::SensorData, temperature),  // bytes offset in struct
    nullptr,  // default value
    size_function__SensorData__temperature,  // size() function pointer
    get_const_function__SensorData__temperature,  // get_const(index) function pointer
    get_function__SensorData__temperature,  // get(index) function pointer
    resize_function__SensorData__temperature  // resize(index) function pointer
  },
  {
    "encoder",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<vehicle_interfaces::msg::EncoderData>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces::msg::SensorData, encoder),  // bytes offset in struct
    nullptr,  // default value
    size_function__SensorData__encoder,  // size() function pointer
    get_const_function__SensorData__encoder,  // get_const(index) function pointer
    get_function__SensorData__encoder,  // get(index) function pointer
    resize_function__SensorData__encoder  // resize(index) function pointer
  },
  {
    "ir_remote",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<vehicle_interfaces::msg::IRData>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interfaces::msg::SensorData, ir_remote),  // bytes offset in struct
    nullptr,  // default value
    size_function__SensorData__ir_remote,  // size() function pointer
    get_const_function__SensorData__ir_remote,  // get_const(index) function pointer
    get_function__SensorData__ir_remote,  // get(index) function pointer
    resize_function__SensorData__ir_remote  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers SensorData_message_members = {
  "vehicle_interfaces::msg",  // message namespace
  "SensorData",  // message name
  10,  // number of fields
  sizeof(vehicle_interfaces::msg::SensorData),
  SensorData_message_member_array,  // message members
  SensorData_init_function,  // function to initialize message memory (memory has to be allocated)
  SensorData_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t SensorData_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &SensorData_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace vehicle_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vehicle_interfaces::msg::SensorData>()
{
  return &::vehicle_interfaces::msg::rosidl_typesupport_introspection_cpp::SensorData_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vehicle_interfaces, msg, SensorData)() {
  return &::vehicle_interfaces::msg::rosidl_typesupport_introspection_cpp::SensorData_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
