// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_interfaces:msg/MPUData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__MPU_DATA__STRUCT_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__MPU_DATA__STRUCT_HPP_

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
// Member 'is_valid'
#include "std_msgs/msg/detail/bool__struct.hpp"
// Member 'imu'
#include "sensor_msgs/msg/detail/imu__struct.hpp"
// Member 'temp'
#include "sensor_msgs/msg/detail/temperature__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vehicle_interfaces__msg__MPUData __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_interfaces__msg__MPUData __declspec(deprecated)
#endif

namespace vehicle_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MPUData_
{
  using Type = MPUData_<ContainerAllocator>;

  explicit MPUData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    is_valid(_init),
    imu(_init),
    temp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->arduino_timestamp = 0ul;
    }
  }

  explicit MPUData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    is_valid(_alloc, _init),
    imu(_alloc, _init),
    temp(_alloc, _init)
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
  using _is_valid_type =
    std_msgs::msg::Bool_<ContainerAllocator>;
  _is_valid_type is_valid;
  using _arduino_timestamp_type =
    uint32_t;
  _arduino_timestamp_type arduino_timestamp;
  using _imu_type =
    sensor_msgs::msg::Imu_<ContainerAllocator>;
  _imu_type imu;
  using _temp_type =
    sensor_msgs::msg::Temperature_<ContainerAllocator>;
  _temp_type temp;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__is_valid(
    const std_msgs::msg::Bool_<ContainerAllocator> & _arg)
  {
    this->is_valid = _arg;
    return *this;
  }
  Type & set__arduino_timestamp(
    const uint32_t & _arg)
  {
    this->arduino_timestamp = _arg;
    return *this;
  }
  Type & set__imu(
    const sensor_msgs::msg::Imu_<ContainerAllocator> & _arg)
  {
    this->imu = _arg;
    return *this;
  }
  Type & set__temp(
    const sensor_msgs::msg::Temperature_<ContainerAllocator> & _arg)
  {
    this->temp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_interfaces::msg::MPUData_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_interfaces::msg::MPUData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_interfaces::msg::MPUData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_interfaces::msg::MPUData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_interfaces::msg::MPUData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_interfaces::msg::MPUData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_interfaces::msg::MPUData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_interfaces::msg::MPUData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_interfaces::msg::MPUData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_interfaces::msg::MPUData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_interfaces__msg__MPUData
    std::shared_ptr<vehicle_interfaces::msg::MPUData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_interfaces__msg__MPUData
    std::shared_ptr<vehicle_interfaces::msg::MPUData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MPUData_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->is_valid != other.is_valid) {
      return false;
    }
    if (this->arduino_timestamp != other.arduino_timestamp) {
      return false;
    }
    if (this->imu != other.imu) {
      return false;
    }
    if (this->temp != other.temp) {
      return false;
    }
    return true;
  }
  bool operator!=(const MPUData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MPUData_

// alias to use template instance with default allocator
using MPUData =
  vehicle_interfaces::msg::MPUData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__MPU_DATA__STRUCT_HPP_
