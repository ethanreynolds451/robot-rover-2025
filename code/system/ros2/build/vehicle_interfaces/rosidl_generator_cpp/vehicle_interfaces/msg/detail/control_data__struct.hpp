// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_interfaces:msg/ControlData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__CONTROL_DATA__STRUCT_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__CONTROL_DATA__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__vehicle_interfaces__msg__ControlData __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_interfaces__msg__ControlData __declspec(deprecated)
#endif

namespace vehicle_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ControlData_
{
  using Type = ControlData_<ContainerAllocator>;

  explicit ControlData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->brake = false;
      this->reverse = false;
      this->steering_reverse = false;
      this->shift_up = false;
      this->power = 0;
      this->steering_power = 0;
    }
  }

  explicit ControlData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->brake = false;
      this->reverse = false;
      this->steering_reverse = false;
      this->shift_up = false;
      this->power = 0;
      this->steering_power = 0;
    }
  }

  // field types and members
  using _brake_type =
    bool;
  _brake_type brake;
  using _reverse_type =
    bool;
  _reverse_type reverse;
  using _steering_reverse_type =
    bool;
  _steering_reverse_type steering_reverse;
  using _shift_up_type =
    bool;
  _shift_up_type shift_up;
  using _power_type =
    uint8_t;
  _power_type power;
  using _steering_power_type =
    uint8_t;
  _steering_power_type steering_power;

  // setters for named parameter idiom
  Type & set__brake(
    const bool & _arg)
  {
    this->brake = _arg;
    return *this;
  }
  Type & set__reverse(
    const bool & _arg)
  {
    this->reverse = _arg;
    return *this;
  }
  Type & set__steering_reverse(
    const bool & _arg)
  {
    this->steering_reverse = _arg;
    return *this;
  }
  Type & set__shift_up(
    const bool & _arg)
  {
    this->shift_up = _arg;
    return *this;
  }
  Type & set__power(
    const uint8_t & _arg)
  {
    this->power = _arg;
    return *this;
  }
  Type & set__steering_power(
    const uint8_t & _arg)
  {
    this->steering_power = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_interfaces::msg::ControlData_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_interfaces::msg::ControlData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_interfaces::msg::ControlData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_interfaces::msg::ControlData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_interfaces::msg::ControlData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_interfaces::msg::ControlData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_interfaces::msg::ControlData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_interfaces::msg::ControlData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_interfaces::msg::ControlData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_interfaces::msg::ControlData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_interfaces__msg__ControlData
    std::shared_ptr<vehicle_interfaces::msg::ControlData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_interfaces__msg__ControlData
    std::shared_ptr<vehicle_interfaces::msg::ControlData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ControlData_ & other) const
  {
    if (this->brake != other.brake) {
      return false;
    }
    if (this->reverse != other.reverse) {
      return false;
    }
    if (this->steering_reverse != other.steering_reverse) {
      return false;
    }
    if (this->shift_up != other.shift_up) {
      return false;
    }
    if (this->power != other.power) {
      return false;
    }
    if (this->steering_power != other.steering_power) {
      return false;
    }
    return true;
  }
  bool operator!=(const ControlData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ControlData_

// alias to use template instance with default allocator
using ControlData =
  vehicle_interfaces::msg::ControlData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__CONTROL_DATA__STRUCT_HPP_
