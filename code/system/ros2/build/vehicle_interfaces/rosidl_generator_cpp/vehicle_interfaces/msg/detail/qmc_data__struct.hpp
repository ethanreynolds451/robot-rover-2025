// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_interfaces:msg/QMCData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__QMC_DATA__STRUCT_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__QMC_DATA__STRUCT_HPP_

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
// Member 'mag'
#include "sensor_msgs/msg/detail/magnetic_field__struct.hpp"
// Member 'temp'
#include "sensor_msgs/msg/detail/temperature__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vehicle_interfaces__msg__QMCData __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_interfaces__msg__QMCData __declspec(deprecated)
#endif

namespace vehicle_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct QMCData_
{
  using Type = QMCData_<ContainerAllocator>;

  explicit QMCData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    is_valid(_init),
    mag(_init),
    temp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = "";
      this->heading = 0.0f;
    }
  }

  explicit QMCData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    is_valid(_alloc, _init),
    id(_alloc),
    mag(_alloc, _init),
    temp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = "";
      this->heading = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _is_valid_type =
    std_msgs::msg::Bool_<ContainerAllocator>;
  _is_valid_type is_valid;
  using _id_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _id_type id;
  using _mag_type =
    sensor_msgs::msg::MagneticField_<ContainerAllocator>;
  _mag_type mag;
  using _heading_type =
    float;
  _heading_type heading;
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
  Type & set__id(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__mag(
    const sensor_msgs::msg::MagneticField_<ContainerAllocator> & _arg)
  {
    this->mag = _arg;
    return *this;
  }
  Type & set__heading(
    const float & _arg)
  {
    this->heading = _arg;
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
    vehicle_interfaces::msg::QMCData_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_interfaces::msg::QMCData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_interfaces::msg::QMCData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_interfaces::msg::QMCData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_interfaces::msg::QMCData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_interfaces::msg::QMCData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_interfaces::msg::QMCData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_interfaces::msg::QMCData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_interfaces::msg::QMCData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_interfaces::msg::QMCData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_interfaces__msg__QMCData
    std::shared_ptr<vehicle_interfaces::msg::QMCData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_interfaces__msg__QMCData
    std::shared_ptr<vehicle_interfaces::msg::QMCData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const QMCData_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->is_valid != other.is_valid) {
      return false;
    }
    if (this->id != other.id) {
      return false;
    }
    if (this->mag != other.mag) {
      return false;
    }
    if (this->heading != other.heading) {
      return false;
    }
    if (this->temp != other.temp) {
      return false;
    }
    return true;
  }
  bool operator!=(const QMCData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct QMCData_

// alias to use template instance with default allocator
using QMCData =
  vehicle_interfaces::msg::QMCData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__QMC_DATA__STRUCT_HPP_
