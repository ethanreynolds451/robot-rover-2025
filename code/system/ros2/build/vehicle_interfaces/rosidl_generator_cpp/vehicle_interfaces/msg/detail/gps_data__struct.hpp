// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_interfaces:msg/GPSData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__GPS_DATA__STRUCT_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__GPS_DATA__STRUCT_HPP_

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
// Member 'position'
#include "sensor_msgs/msg/detail/nav_sat_fix__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vehicle_interfaces__msg__GPSData __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_interfaces__msg__GPSData __declspec(deprecated)
#endif

namespace vehicle_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GPSData_
{
  using Type = GPSData_<ContainerAllocator>;

  explicit GPSData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    is_valid(_init),
    position(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->heading = 0.0f;
      this->speed_kmph = 0.0f;
      this->sats = 0;
    }
  }

  explicit GPSData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    is_valid(_alloc, _init),
    position(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->heading = 0.0f;
      this->speed_kmph = 0.0f;
      this->sats = 0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _is_valid_type =
    std_msgs::msg::Bool_<ContainerAllocator>;
  _is_valid_type is_valid;
  using _position_type =
    sensor_msgs::msg::NavSatFix_<ContainerAllocator>;
  _position_type position;
  using _heading_type =
    float;
  _heading_type heading;
  using _speed_kmph_type =
    float;
  _speed_kmph_type speed_kmph;
  using _sats_type =
    int8_t;
  _sats_type sats;

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
  Type & set__position(
    const sensor_msgs::msg::NavSatFix_<ContainerAllocator> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__heading(
    const float & _arg)
  {
    this->heading = _arg;
    return *this;
  }
  Type & set__speed_kmph(
    const float & _arg)
  {
    this->speed_kmph = _arg;
    return *this;
  }
  Type & set__sats(
    const int8_t & _arg)
  {
    this->sats = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_interfaces::msg::GPSData_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_interfaces::msg::GPSData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_interfaces::msg::GPSData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_interfaces::msg::GPSData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_interfaces::msg::GPSData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_interfaces::msg::GPSData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_interfaces::msg::GPSData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_interfaces::msg::GPSData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_interfaces::msg::GPSData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_interfaces::msg::GPSData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_interfaces__msg__GPSData
    std::shared_ptr<vehicle_interfaces::msg::GPSData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_interfaces__msg__GPSData
    std::shared_ptr<vehicle_interfaces::msg::GPSData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GPSData_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->is_valid != other.is_valid) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->heading != other.heading) {
      return false;
    }
    if (this->speed_kmph != other.speed_kmph) {
      return false;
    }
    if (this->sats != other.sats) {
      return false;
    }
    return true;
  }
  bool operator!=(const GPSData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GPSData_

// alias to use template instance with default allocator
using GPSData =
  vehicle_interfaces::msg::GPSData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__GPS_DATA__STRUCT_HPP_
