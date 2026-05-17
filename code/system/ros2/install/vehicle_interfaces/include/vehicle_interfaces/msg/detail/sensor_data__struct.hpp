// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_interfaces:msg/SensorData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__SENSOR_DATA__STRUCT_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__SENSOR_DATA__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'mpu'
#include "vehicle_interfaces/msg/detail/mpu_data__struct.hpp"
// Member 'qmc'
#include "vehicle_interfaces/msg/detail/qmc_data__struct.hpp"
// Member 'gps'
#include "vehicle_interfaces/msg/detail/gps_data__struct.hpp"
// Member 'tof'
#include "vehicle_interfaces/msg/detail/to_f_data__struct.hpp"
// Member 'ultrasonic'
#include "vehicle_interfaces/msg/detail/ultrasonic_data__struct.hpp"
// Member 'temperature'
#include "vehicle_interfaces/msg/detail/temperature_data__struct.hpp"
// Member 'encoder'
#include "vehicle_interfaces/msg/detail/encoder_data__struct.hpp"
// Member 'ir_remote'
#include "vehicle_interfaces/msg/detail/ir_data__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vehicle_interfaces__msg__SensorData __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_interfaces__msg__SensorData __declspec(deprecated)
#endif

namespace vehicle_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SensorData_
{
  using Type = SensorData_<ContainerAllocator>;

  explicit SensorData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->arduino_timestamp = 0ul;
    }
  }

  explicit SensorData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->arduino_timestamp = 0ul;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _arduino_timestamp_type =
    uint32_t;
  _arduino_timestamp_type arduino_timestamp;
  using _mpu_type =
    std::vector<vehicle_interfaces::msg::MPUData_<ContainerAllocator>, typename ContainerAllocator::template rebind<vehicle_interfaces::msg::MPUData_<ContainerAllocator>>::other>;
  _mpu_type mpu;
  using _qmc_type =
    std::vector<vehicle_interfaces::msg::QMCData_<ContainerAllocator>, typename ContainerAllocator::template rebind<vehicle_interfaces::msg::QMCData_<ContainerAllocator>>::other>;
  _qmc_type qmc;
  using _gps_type =
    std::vector<vehicle_interfaces::msg::GPSData_<ContainerAllocator>, typename ContainerAllocator::template rebind<vehicle_interfaces::msg::GPSData_<ContainerAllocator>>::other>;
  _gps_type gps;
  using _tof_type =
    std::vector<vehicle_interfaces::msg::ToFData_<ContainerAllocator>, typename ContainerAllocator::template rebind<vehicle_interfaces::msg::ToFData_<ContainerAllocator>>::other>;
  _tof_type tof;
  using _ultrasonic_type =
    std::vector<vehicle_interfaces::msg::UltrasonicData_<ContainerAllocator>, typename ContainerAllocator::template rebind<vehicle_interfaces::msg::UltrasonicData_<ContainerAllocator>>::other>;
  _ultrasonic_type ultrasonic;
  using _temperature_type =
    std::vector<vehicle_interfaces::msg::TemperatureData_<ContainerAllocator>, typename ContainerAllocator::template rebind<vehicle_interfaces::msg::TemperatureData_<ContainerAllocator>>::other>;
  _temperature_type temperature;
  using _encoder_type =
    std::vector<vehicle_interfaces::msg::EncoderData_<ContainerAllocator>, typename ContainerAllocator::template rebind<vehicle_interfaces::msg::EncoderData_<ContainerAllocator>>::other>;
  _encoder_type encoder;
  using _ir_remote_type =
    std::vector<vehicle_interfaces::msg::IRData_<ContainerAllocator>, typename ContainerAllocator::template rebind<vehicle_interfaces::msg::IRData_<ContainerAllocator>>::other>;
  _ir_remote_type ir_remote;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__arduino_timestamp(
    const uint32_t & _arg)
  {
    this->arduino_timestamp = _arg;
    return *this;
  }
  Type & set__mpu(
    const std::vector<vehicle_interfaces::msg::MPUData_<ContainerAllocator>, typename ContainerAllocator::template rebind<vehicle_interfaces::msg::MPUData_<ContainerAllocator>>::other> & _arg)
  {
    this->mpu = _arg;
    return *this;
  }
  Type & set__qmc(
    const std::vector<vehicle_interfaces::msg::QMCData_<ContainerAllocator>, typename ContainerAllocator::template rebind<vehicle_interfaces::msg::QMCData_<ContainerAllocator>>::other> & _arg)
  {
    this->qmc = _arg;
    return *this;
  }
  Type & set__gps(
    const std::vector<vehicle_interfaces::msg::GPSData_<ContainerAllocator>, typename ContainerAllocator::template rebind<vehicle_interfaces::msg::GPSData_<ContainerAllocator>>::other> & _arg)
  {
    this->gps = _arg;
    return *this;
  }
  Type & set__tof(
    const std::vector<vehicle_interfaces::msg::ToFData_<ContainerAllocator>, typename ContainerAllocator::template rebind<vehicle_interfaces::msg::ToFData_<ContainerAllocator>>::other> & _arg)
  {
    this->tof = _arg;
    return *this;
  }
  Type & set__ultrasonic(
    const std::vector<vehicle_interfaces::msg::UltrasonicData_<ContainerAllocator>, typename ContainerAllocator::template rebind<vehicle_interfaces::msg::UltrasonicData_<ContainerAllocator>>::other> & _arg)
  {
    this->ultrasonic = _arg;
    return *this;
  }
  Type & set__temperature(
    const std::vector<vehicle_interfaces::msg::TemperatureData_<ContainerAllocator>, typename ContainerAllocator::template rebind<vehicle_interfaces::msg::TemperatureData_<ContainerAllocator>>::other> & _arg)
  {
    this->temperature = _arg;
    return *this;
  }
  Type & set__encoder(
    const std::vector<vehicle_interfaces::msg::EncoderData_<ContainerAllocator>, typename ContainerAllocator::template rebind<vehicle_interfaces::msg::EncoderData_<ContainerAllocator>>::other> & _arg)
  {
    this->encoder = _arg;
    return *this;
  }
  Type & set__ir_remote(
    const std::vector<vehicle_interfaces::msg::IRData_<ContainerAllocator>, typename ContainerAllocator::template rebind<vehicle_interfaces::msg::IRData_<ContainerAllocator>>::other> & _arg)
  {
    this->ir_remote = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_interfaces::msg::SensorData_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_interfaces::msg::SensorData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_interfaces::msg::SensorData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_interfaces::msg::SensorData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_interfaces::msg::SensorData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_interfaces::msg::SensorData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_interfaces::msg::SensorData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_interfaces::msg::SensorData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_interfaces::msg::SensorData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_interfaces::msg::SensorData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_interfaces__msg__SensorData
    std::shared_ptr<vehicle_interfaces::msg::SensorData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_interfaces__msg__SensorData
    std::shared_ptr<vehicle_interfaces::msg::SensorData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SensorData_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->arduino_timestamp != other.arduino_timestamp) {
      return false;
    }
    if (this->mpu != other.mpu) {
      return false;
    }
    if (this->qmc != other.qmc) {
      return false;
    }
    if (this->gps != other.gps) {
      return false;
    }
    if (this->tof != other.tof) {
      return false;
    }
    if (this->ultrasonic != other.ultrasonic) {
      return false;
    }
    if (this->temperature != other.temperature) {
      return false;
    }
    if (this->encoder != other.encoder) {
      return false;
    }
    if (this->ir_remote != other.ir_remote) {
      return false;
    }
    return true;
  }
  bool operator!=(const SensorData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SensorData_

// alias to use template instance with default allocator
using SensorData =
  vehicle_interfaces::msg::SensorData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__SENSOR_DATA__STRUCT_HPP_
