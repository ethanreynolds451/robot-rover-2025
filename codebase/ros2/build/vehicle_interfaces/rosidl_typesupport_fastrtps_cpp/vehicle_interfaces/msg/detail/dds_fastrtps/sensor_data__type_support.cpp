// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from vehicle_interfaces:msg/SensorData.idl
// generated code does not contain a copyright notice
#include "vehicle_interfaces/msg/detail/sensor_data__rosidl_typesupport_fastrtps_cpp.hpp"
#include "vehicle_interfaces/msg/detail/sensor_data__struct.hpp"

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
namespace std_msgs
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const std_msgs::msg::Header &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  std_msgs::msg::Header &);
size_t get_serialized_size(
  const std_msgs::msg::Header &,
  size_t current_alignment);
size_t
max_serialized_size_Header(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace std_msgs

namespace vehicle_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const vehicle_interfaces::msg::MPUData &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  vehicle_interfaces::msg::MPUData &);
size_t get_serialized_size(
  const vehicle_interfaces::msg::MPUData &,
  size_t current_alignment);
size_t
max_serialized_size_MPUData(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace vehicle_interfaces

namespace vehicle_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const vehicle_interfaces::msg::QMCData &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  vehicle_interfaces::msg::QMCData &);
size_t get_serialized_size(
  const vehicle_interfaces::msg::QMCData &,
  size_t current_alignment);
size_t
max_serialized_size_QMCData(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace vehicle_interfaces

namespace vehicle_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const vehicle_interfaces::msg::GPSData &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  vehicle_interfaces::msg::GPSData &);
size_t get_serialized_size(
  const vehicle_interfaces::msg::GPSData &,
  size_t current_alignment);
size_t
max_serialized_size_GPSData(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace vehicle_interfaces

namespace vehicle_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const vehicle_interfaces::msg::ToFData &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  vehicle_interfaces::msg::ToFData &);
size_t get_serialized_size(
  const vehicle_interfaces::msg::ToFData &,
  size_t current_alignment);
size_t
max_serialized_size_ToFData(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace vehicle_interfaces

namespace vehicle_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const vehicle_interfaces::msg::UltrasonicData &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  vehicle_interfaces::msg::UltrasonicData &);
size_t get_serialized_size(
  const vehicle_interfaces::msg::UltrasonicData &,
  size_t current_alignment);
size_t
max_serialized_size_UltrasonicData(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace vehicle_interfaces

namespace vehicle_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const vehicle_interfaces::msg::TemperatureData &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  vehicle_interfaces::msg::TemperatureData &);
size_t get_serialized_size(
  const vehicle_interfaces::msg::TemperatureData &,
  size_t current_alignment);
size_t
max_serialized_size_TemperatureData(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace vehicle_interfaces

namespace vehicle_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const vehicle_interfaces::msg::EncoderData &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  vehicle_interfaces::msg::EncoderData &);
size_t get_serialized_size(
  const vehicle_interfaces::msg::EncoderData &,
  size_t current_alignment);
size_t
max_serialized_size_EncoderData(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace vehicle_interfaces

namespace vehicle_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const vehicle_interfaces::msg::IRData &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  vehicle_interfaces::msg::IRData &);
size_t get_serialized_size(
  const vehicle_interfaces::msg::IRData &,
  size_t current_alignment);
size_t
max_serialized_size_IRData(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace vehicle_interfaces


namespace vehicle_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_interfaces
cdr_serialize(
  const vehicle_interfaces::msg::SensorData & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.header,
    cdr);
  // Member: arduino_timestamp
  cdr << ros_message.arduino_timestamp;
  // Member: mpu
  {
    size_t size = ros_message.mpu.size();
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; i++) {
      vehicle_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.mpu[i],
        cdr);
    }
  }
  // Member: qmc
  {
    size_t size = ros_message.qmc.size();
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; i++) {
      vehicle_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.qmc[i],
        cdr);
    }
  }
  // Member: gps
  {
    size_t size = ros_message.gps.size();
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; i++) {
      vehicle_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.gps[i],
        cdr);
    }
  }
  // Member: tof
  {
    size_t size = ros_message.tof.size();
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; i++) {
      vehicle_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.tof[i],
        cdr);
    }
  }
  // Member: ultrasonic
  {
    size_t size = ros_message.ultrasonic.size();
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; i++) {
      vehicle_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.ultrasonic[i],
        cdr);
    }
  }
  // Member: temperature
  {
    size_t size = ros_message.temperature.size();
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; i++) {
      vehicle_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.temperature[i],
        cdr);
    }
  }
  // Member: encoder
  {
    size_t size = ros_message.encoder.size();
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; i++) {
      vehicle_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.encoder[i],
        cdr);
    }
  }
  // Member: ir_remote
  {
    size_t size = ros_message.ir_remote.size();
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; i++) {
      vehicle_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.ir_remote[i],
        cdr);
    }
  }
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vehicle_interfaces::msg::SensorData & ros_message)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.header);

  // Member: arduino_timestamp
  cdr >> ros_message.arduino_timestamp;

  // Member: mpu
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    ros_message.mpu.resize(size);
    for (size_t i = 0; i < size; i++) {
      vehicle_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr, ros_message.mpu[i]);
    }
  }

  // Member: qmc
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    ros_message.qmc.resize(size);
    for (size_t i = 0; i < size; i++) {
      vehicle_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr, ros_message.qmc[i]);
    }
  }

  // Member: gps
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    ros_message.gps.resize(size);
    for (size_t i = 0; i < size; i++) {
      vehicle_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr, ros_message.gps[i]);
    }
  }

  // Member: tof
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    ros_message.tof.resize(size);
    for (size_t i = 0; i < size; i++) {
      vehicle_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr, ros_message.tof[i]);
    }
  }

  // Member: ultrasonic
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    ros_message.ultrasonic.resize(size);
    for (size_t i = 0; i < size; i++) {
      vehicle_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr, ros_message.ultrasonic[i]);
    }
  }

  // Member: temperature
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    ros_message.temperature.resize(size);
    for (size_t i = 0; i < size; i++) {
      vehicle_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr, ros_message.temperature[i]);
    }
  }

  // Member: encoder
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    ros_message.encoder.resize(size);
    for (size_t i = 0; i < size; i++) {
      vehicle_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr, ros_message.encoder[i]);
    }
  }

  // Member: ir_remote
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    ros_message.ir_remote.resize(size);
    for (size_t i = 0; i < size; i++) {
      vehicle_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr, ros_message.ir_remote[i]);
    }
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_interfaces
get_serialized_size(
  const vehicle_interfaces::msg::SensorData & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: header

  current_alignment +=
    std_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.header, current_alignment);
  // Member: arduino_timestamp
  {
    size_t item_size = sizeof(ros_message.arduino_timestamp);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: mpu
  {
    size_t array_size = ros_message.mpu.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        vehicle_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.mpu[index], current_alignment);
    }
  }
  // Member: qmc
  {
    size_t array_size = ros_message.qmc.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        vehicle_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.qmc[index], current_alignment);
    }
  }
  // Member: gps
  {
    size_t array_size = ros_message.gps.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        vehicle_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.gps[index], current_alignment);
    }
  }
  // Member: tof
  {
    size_t array_size = ros_message.tof.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        vehicle_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.tof[index], current_alignment);
    }
  }
  // Member: ultrasonic
  {
    size_t array_size = ros_message.ultrasonic.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        vehicle_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.ultrasonic[index], current_alignment);
    }
  }
  // Member: temperature
  {
    size_t array_size = ros_message.temperature.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        vehicle_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.temperature[index], current_alignment);
    }
  }
  // Member: encoder
  {
    size_t array_size = ros_message.encoder.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        vehicle_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.encoder[index], current_alignment);
    }
  }
  // Member: ir_remote
  {
    size_t array_size = ros_message.ir_remote.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        vehicle_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.ir_remote[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_interfaces
max_serialized_size_SensorData(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: header
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        std_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_Header(
        full_bounded, current_alignment);
    }
  }

  // Member: arduino_timestamp
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: mpu
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        vehicle_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_MPUData(
        full_bounded, current_alignment);
    }
  }

  // Member: qmc
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        vehicle_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_QMCData(
        full_bounded, current_alignment);
    }
  }

  // Member: gps
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        vehicle_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_GPSData(
        full_bounded, current_alignment);
    }
  }

  // Member: tof
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        vehicle_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_ToFData(
        full_bounded, current_alignment);
    }
  }

  // Member: ultrasonic
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        vehicle_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_UltrasonicData(
        full_bounded, current_alignment);
    }
  }

  // Member: temperature
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        vehicle_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_TemperatureData(
        full_bounded, current_alignment);
    }
  }

  // Member: encoder
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        vehicle_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_EncoderData(
        full_bounded, current_alignment);
    }
  }

  // Member: ir_remote
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        vehicle_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_IRData(
        full_bounded, current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

static bool _SensorData__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const vehicle_interfaces::msg::SensorData *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _SensorData__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<vehicle_interfaces::msg::SensorData *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _SensorData__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const vehicle_interfaces::msg::SensorData *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _SensorData__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_SensorData(full_bounded, 0);
}

static message_type_support_callbacks_t _SensorData__callbacks = {
  "vehicle_interfaces::msg",
  "SensorData",
  _SensorData__cdr_serialize,
  _SensorData__cdr_deserialize,
  _SensorData__get_serialized_size,
  _SensorData__max_serialized_size
};

static rosidl_message_type_support_t _SensorData__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_SensorData__callbacks,
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
get_message_type_support_handle<vehicle_interfaces::msg::SensorData>()
{
  return &vehicle_interfaces::msg::typesupport_fastrtps_cpp::_SensorData__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_interfaces, msg, SensorData)() {
  return &vehicle_interfaces::msg::typesupport_fastrtps_cpp::_SensorData__handle;
}

#ifdef __cplusplus
}
#endif
