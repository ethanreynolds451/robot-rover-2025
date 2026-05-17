// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from vehicle_interfaces:msg/SensorData.idl
// generated code does not contain a copyright notice
#include "vehicle_interfaces/msg/detail/sensor_data__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "vehicle_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "vehicle_interfaces/msg/detail/sensor_data__struct.h"
#include "vehicle_interfaces/msg/detail/sensor_data__functions.h"
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

#include "std_msgs/msg/detail/header__functions.h"  // header
#include "vehicle_interfaces/msg/detail/encoder_data__functions.h"  // encoder
#include "vehicle_interfaces/msg/detail/gps_data__functions.h"  // gps
#include "vehicle_interfaces/msg/detail/ir_data__functions.h"  // ir_remote
#include "vehicle_interfaces/msg/detail/mpu_data__functions.h"  // mpu
#include "vehicle_interfaces/msg/detail/qmc_data__functions.h"  // qmc
#include "vehicle_interfaces/msg/detail/temperature_data__functions.h"  // temperature
#include "vehicle_interfaces/msg/detail/to_f_data__functions.h"  // tof
#include "vehicle_interfaces/msg/detail/ultrasonic_data__functions.h"  // ultrasonic

// forward declare type support functions
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vehicle_interfaces
size_t get_serialized_size_std_msgs__msg__Header(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vehicle_interfaces
size_t max_serialized_size_std_msgs__msg__Header(
  bool & full_bounded,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vehicle_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, std_msgs, msg, Header)();
size_t get_serialized_size_vehicle_interfaces__msg__EncoderData(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_vehicle_interfaces__msg__EncoderData(
  bool & full_bounded,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, EncoderData)();
size_t get_serialized_size_vehicle_interfaces__msg__GPSData(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_vehicle_interfaces__msg__GPSData(
  bool & full_bounded,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, GPSData)();
size_t get_serialized_size_vehicle_interfaces__msg__IRData(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_vehicle_interfaces__msg__IRData(
  bool & full_bounded,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, IRData)();
size_t get_serialized_size_vehicle_interfaces__msg__MPUData(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_vehicle_interfaces__msg__MPUData(
  bool & full_bounded,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, MPUData)();
size_t get_serialized_size_vehicle_interfaces__msg__QMCData(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_vehicle_interfaces__msg__QMCData(
  bool & full_bounded,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, QMCData)();
size_t get_serialized_size_vehicle_interfaces__msg__TemperatureData(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_vehicle_interfaces__msg__TemperatureData(
  bool & full_bounded,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, TemperatureData)();
size_t get_serialized_size_vehicle_interfaces__msg__ToFData(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_vehicle_interfaces__msg__ToFData(
  bool & full_bounded,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, ToFData)();
size_t get_serialized_size_vehicle_interfaces__msg__UltrasonicData(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_vehicle_interfaces__msg__UltrasonicData(
  bool & full_bounded,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, UltrasonicData)();


using _SensorData__ros_msg_type = vehicle_interfaces__msg__SensorData;

static bool _SensorData__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _SensorData__ros_msg_type * ros_message = static_cast<const _SensorData__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->header, cdr))
    {
      return false;
    }
  }

  // Field name: arduino_timestamp
  {
    cdr << ros_message->arduino_timestamp;
  }

  // Field name: mpu
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, MPUData
      )()->data);
    size_t size = ros_message->mpu.size;
    auto array_ptr = ros_message->mpu.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_serialize(
          &array_ptr[i], cdr))
      {
        return false;
      }
    }
  }

  // Field name: qmc
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, QMCData
      )()->data);
    size_t size = ros_message->qmc.size;
    auto array_ptr = ros_message->qmc.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_serialize(
          &array_ptr[i], cdr))
      {
        return false;
      }
    }
  }

  // Field name: gps
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, GPSData
      )()->data);
    size_t size = ros_message->gps.size;
    auto array_ptr = ros_message->gps.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_serialize(
          &array_ptr[i], cdr))
      {
        return false;
      }
    }
  }

  // Field name: tof
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, ToFData
      )()->data);
    size_t size = ros_message->tof.size;
    auto array_ptr = ros_message->tof.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_serialize(
          &array_ptr[i], cdr))
      {
        return false;
      }
    }
  }

  // Field name: ultrasonic
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, UltrasonicData
      )()->data);
    size_t size = ros_message->ultrasonic.size;
    auto array_ptr = ros_message->ultrasonic.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_serialize(
          &array_ptr[i], cdr))
      {
        return false;
      }
    }
  }

  // Field name: temperature
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, TemperatureData
      )()->data);
    size_t size = ros_message->temperature.size;
    auto array_ptr = ros_message->temperature.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_serialize(
          &array_ptr[i], cdr))
      {
        return false;
      }
    }
  }

  // Field name: encoder
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, EncoderData
      )()->data);
    size_t size = ros_message->encoder.size;
    auto array_ptr = ros_message->encoder.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_serialize(
          &array_ptr[i], cdr))
      {
        return false;
      }
    }
  }

  // Field name: ir_remote
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, IRData
      )()->data);
    size_t size = ros_message->ir_remote.size;
    auto array_ptr = ros_message->ir_remote.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_serialize(
          &array_ptr[i], cdr))
      {
        return false;
      }
    }
  }

  return true;
}

static bool _SensorData__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _SensorData__ros_msg_type * ros_message = static_cast<_SensorData__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->header))
    {
      return false;
    }
  }

  // Field name: arduino_timestamp
  {
    cdr >> ros_message->arduino_timestamp;
  }

  // Field name: mpu
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, MPUData
      )()->data);
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->mpu.data) {
      vehicle_interfaces__msg__MPUData__Sequence__fini(&ros_message->mpu);
    }
    if (!vehicle_interfaces__msg__MPUData__Sequence__init(&ros_message->mpu, size)) {
      return "failed to create array for field 'mpu'";
    }
    auto array_ptr = ros_message->mpu.data;
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_deserialize(
          cdr, &array_ptr[i]))
      {
        return false;
      }
    }
  }

  // Field name: qmc
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, QMCData
      )()->data);
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->qmc.data) {
      vehicle_interfaces__msg__QMCData__Sequence__fini(&ros_message->qmc);
    }
    if (!vehicle_interfaces__msg__QMCData__Sequence__init(&ros_message->qmc, size)) {
      return "failed to create array for field 'qmc'";
    }
    auto array_ptr = ros_message->qmc.data;
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_deserialize(
          cdr, &array_ptr[i]))
      {
        return false;
      }
    }
  }

  // Field name: gps
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, GPSData
      )()->data);
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->gps.data) {
      vehicle_interfaces__msg__GPSData__Sequence__fini(&ros_message->gps);
    }
    if (!vehicle_interfaces__msg__GPSData__Sequence__init(&ros_message->gps, size)) {
      return "failed to create array for field 'gps'";
    }
    auto array_ptr = ros_message->gps.data;
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_deserialize(
          cdr, &array_ptr[i]))
      {
        return false;
      }
    }
  }

  // Field name: tof
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, ToFData
      )()->data);
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->tof.data) {
      vehicle_interfaces__msg__ToFData__Sequence__fini(&ros_message->tof);
    }
    if (!vehicle_interfaces__msg__ToFData__Sequence__init(&ros_message->tof, size)) {
      return "failed to create array for field 'tof'";
    }
    auto array_ptr = ros_message->tof.data;
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_deserialize(
          cdr, &array_ptr[i]))
      {
        return false;
      }
    }
  }

  // Field name: ultrasonic
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, UltrasonicData
      )()->data);
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->ultrasonic.data) {
      vehicle_interfaces__msg__UltrasonicData__Sequence__fini(&ros_message->ultrasonic);
    }
    if (!vehicle_interfaces__msg__UltrasonicData__Sequence__init(&ros_message->ultrasonic, size)) {
      return "failed to create array for field 'ultrasonic'";
    }
    auto array_ptr = ros_message->ultrasonic.data;
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_deserialize(
          cdr, &array_ptr[i]))
      {
        return false;
      }
    }
  }

  // Field name: temperature
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, TemperatureData
      )()->data);
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->temperature.data) {
      vehicle_interfaces__msg__TemperatureData__Sequence__fini(&ros_message->temperature);
    }
    if (!vehicle_interfaces__msg__TemperatureData__Sequence__init(&ros_message->temperature, size)) {
      return "failed to create array for field 'temperature'";
    }
    auto array_ptr = ros_message->temperature.data;
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_deserialize(
          cdr, &array_ptr[i]))
      {
        return false;
      }
    }
  }

  // Field name: encoder
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, EncoderData
      )()->data);
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->encoder.data) {
      vehicle_interfaces__msg__EncoderData__Sequence__fini(&ros_message->encoder);
    }
    if (!vehicle_interfaces__msg__EncoderData__Sequence__init(&ros_message->encoder, size)) {
      return "failed to create array for field 'encoder'";
    }
    auto array_ptr = ros_message->encoder.data;
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_deserialize(
          cdr, &array_ptr[i]))
      {
        return false;
      }
    }
  }

  // Field name: ir_remote
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, IRData
      )()->data);
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->ir_remote.data) {
      vehicle_interfaces__msg__IRData__Sequence__fini(&ros_message->ir_remote);
    }
    if (!vehicle_interfaces__msg__IRData__Sequence__init(&ros_message->ir_remote, size)) {
      return "failed to create array for field 'ir_remote'";
    }
    auto array_ptr = ros_message->ir_remote.data;
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_deserialize(
          cdr, &array_ptr[i]))
      {
        return false;
      }
    }
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_interfaces
size_t get_serialized_size_vehicle_interfaces__msg__SensorData(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SensorData__ros_msg_type * ros_message = static_cast<const _SensorData__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name header

  current_alignment += get_serialized_size_std_msgs__msg__Header(
    &(ros_message->header), current_alignment);
  // field.name arduino_timestamp
  {
    size_t item_size = sizeof(ros_message->arduino_timestamp);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name mpu
  {
    size_t array_size = ros_message->mpu.size;
    auto array_ptr = ros_message->mpu.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_vehicle_interfaces__msg__MPUData(
        &array_ptr[index], current_alignment);
    }
  }
  // field.name qmc
  {
    size_t array_size = ros_message->qmc.size;
    auto array_ptr = ros_message->qmc.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_vehicle_interfaces__msg__QMCData(
        &array_ptr[index], current_alignment);
    }
  }
  // field.name gps
  {
    size_t array_size = ros_message->gps.size;
    auto array_ptr = ros_message->gps.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_vehicle_interfaces__msg__GPSData(
        &array_ptr[index], current_alignment);
    }
  }
  // field.name tof
  {
    size_t array_size = ros_message->tof.size;
    auto array_ptr = ros_message->tof.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_vehicle_interfaces__msg__ToFData(
        &array_ptr[index], current_alignment);
    }
  }
  // field.name ultrasonic
  {
    size_t array_size = ros_message->ultrasonic.size;
    auto array_ptr = ros_message->ultrasonic.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_vehicle_interfaces__msg__UltrasonicData(
        &array_ptr[index], current_alignment);
    }
  }
  // field.name temperature
  {
    size_t array_size = ros_message->temperature.size;
    auto array_ptr = ros_message->temperature.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_vehicle_interfaces__msg__TemperatureData(
        &array_ptr[index], current_alignment);
    }
  }
  // field.name encoder
  {
    size_t array_size = ros_message->encoder.size;
    auto array_ptr = ros_message->encoder.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_vehicle_interfaces__msg__EncoderData(
        &array_ptr[index], current_alignment);
    }
  }
  // field.name ir_remote
  {
    size_t array_size = ros_message->ir_remote.size;
    auto array_ptr = ros_message->ir_remote.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_vehicle_interfaces__msg__IRData(
        &array_ptr[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

static uint32_t _SensorData__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vehicle_interfaces__msg__SensorData(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_interfaces
size_t max_serialized_size_vehicle_interfaces__msg__SensorData(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: header
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_std_msgs__msg__Header(
        full_bounded, current_alignment);
    }
  }
  // member: arduino_timestamp
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: mpu
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_vehicle_interfaces__msg__MPUData(
        full_bounded, current_alignment);
    }
  }
  // member: qmc
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_vehicle_interfaces__msg__QMCData(
        full_bounded, current_alignment);
    }
  }
  // member: gps
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_vehicle_interfaces__msg__GPSData(
        full_bounded, current_alignment);
    }
  }
  // member: tof
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_vehicle_interfaces__msg__ToFData(
        full_bounded, current_alignment);
    }
  }
  // member: ultrasonic
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_vehicle_interfaces__msg__UltrasonicData(
        full_bounded, current_alignment);
    }
  }
  // member: temperature
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_vehicle_interfaces__msg__TemperatureData(
        full_bounded, current_alignment);
    }
  }
  // member: encoder
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_vehicle_interfaces__msg__EncoderData(
        full_bounded, current_alignment);
    }
  }
  // member: ir_remote
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_vehicle_interfaces__msg__IRData(
        full_bounded, current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

static size_t _SensorData__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_vehicle_interfaces__msg__SensorData(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_SensorData = {
  "vehicle_interfaces::msg",
  "SensorData",
  _SensorData__cdr_serialize,
  _SensorData__cdr_deserialize,
  _SensorData__get_serialized_size,
  _SensorData__max_serialized_size
};

static rosidl_message_type_support_t _SensorData__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SensorData,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_interfaces, msg, SensorData)() {
  return &_SensorData__type_support;
}

#if defined(__cplusplus)
}
#endif
