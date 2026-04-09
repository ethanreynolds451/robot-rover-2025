// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_interfaces:msg/ToFData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__TO_F_DATA__STRUCT_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__TO_F_DATA__STRUCT_HPP_

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
// Member 'range'
#include "sensor_msgs/msg/detail/range__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vehicle_interfaces__msg__ToFData __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_interfaces__msg__ToFData __declspec(deprecated)
#endif

namespace vehicle_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ToFData_
{
  using Type = ToFData_<ContainerAllocator>;

  explicit ToFData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    is_valid(_init),
    range(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->intensity = 0.0f;
    }
  }

  explicit ToFData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    is_valid(_alloc, _init),
    range(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->intensity = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _is_valid_type =
    std_msgs::msg::Bool_<ContainerAllocator>;
  _is_valid_type is_valid;
  using _range_type =
    sensor_msgs::msg::Range_<ContainerAllocator>;
  _range_type range;
  using _intensity_type =
    float;
  _intensity_type intensity;

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
  Type & set__range(
    const sensor_msgs::msg::Range_<ContainerAllocator> & _arg)
  {
    this->range = _arg;
    return *this;
  }
  Type & set__intensity(
    const float & _arg)
  {
    this->intensity = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_interfaces::msg::ToFData_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_interfaces::msg::ToFData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_interfaces::msg::ToFData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_interfaces::msg::ToFData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_interfaces::msg::ToFData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_interfaces::msg::ToFData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_interfaces::msg::ToFData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_interfaces::msg::ToFData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_interfaces::msg::ToFData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_interfaces::msg::ToFData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_interfaces__msg__ToFData
    std::shared_ptr<vehicle_interfaces::msg::ToFData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_interfaces__msg__ToFData
    std::shared_ptr<vehicle_interfaces::msg::ToFData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ToFData_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->is_valid != other.is_valid) {
      return false;
    }
    if (this->range != other.range) {
      return false;
    }
    if (this->intensity != other.intensity) {
      return false;
    }
    return true;
  }
  bool operator!=(const ToFData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ToFData_

// alias to use template instance with default allocator
using ToFData =
  vehicle_interfaces::msg::ToFData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__TO_F_DATA__STRUCT_HPP_
