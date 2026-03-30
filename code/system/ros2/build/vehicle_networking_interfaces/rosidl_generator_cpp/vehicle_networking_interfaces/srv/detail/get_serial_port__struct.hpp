// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_networking_interfaces:srv/GetSerialPort.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_NETWORKING_INTERFACES__SRV__DETAIL__GET_SERIAL_PORT__STRUCT_HPP_
#define VEHICLE_NETWORKING_INTERFACES__SRV__DETAIL__GET_SERIAL_PORT__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__vehicle_networking_interfaces__srv__GetSerialPort_Request __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_networking_interfaces__srv__GetSerialPort_Request __declspec(deprecated)
#endif

namespace vehicle_networking_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetSerialPort_Request_
{
  using Type = GetSerialPort_Request_<ContainerAllocator>;

  explicit GetSerialPort_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->device = "";
    }
  }

  explicit GetSerialPort_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : device(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->device = "";
    }
  }

  // field types and members
  using _device_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _device_type device;

  // setters for named parameter idiom
  Type & set__device(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->device = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_networking_interfaces::srv::GetSerialPort_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_networking_interfaces::srv::GetSerialPort_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_networking_interfaces::srv::GetSerialPort_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_networking_interfaces::srv::GetSerialPort_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_networking_interfaces::srv::GetSerialPort_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_networking_interfaces::srv::GetSerialPort_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_networking_interfaces::srv::GetSerialPort_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_networking_interfaces::srv::GetSerialPort_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_networking_interfaces::srv::GetSerialPort_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_networking_interfaces::srv::GetSerialPort_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_networking_interfaces__srv__GetSerialPort_Request
    std::shared_ptr<vehicle_networking_interfaces::srv::GetSerialPort_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_networking_interfaces__srv__GetSerialPort_Request
    std::shared_ptr<vehicle_networking_interfaces::srv::GetSerialPort_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetSerialPort_Request_ & other) const
  {
    if (this->device != other.device) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetSerialPort_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetSerialPort_Request_

// alias to use template instance with default allocator
using GetSerialPort_Request =
  vehicle_networking_interfaces::srv::GetSerialPort_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace vehicle_networking_interfaces


#ifndef _WIN32
# define DEPRECATED__vehicle_networking_interfaces__srv__GetSerialPort_Response __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_networking_interfaces__srv__GetSerialPort_Response __declspec(deprecated)
#endif

namespace vehicle_networking_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetSerialPort_Response_
{
  using Type = GetSerialPort_Response_<ContainerAllocator>;

  explicit GetSerialPort_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->port = "";
    }
  }

  explicit GetSerialPort_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : port(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->port = "";
    }
  }

  // field types and members
  using _port_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _port_type port;

  // setters for named parameter idiom
  Type & set__port(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->port = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_networking_interfaces::srv::GetSerialPort_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_networking_interfaces::srv::GetSerialPort_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_networking_interfaces::srv::GetSerialPort_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_networking_interfaces::srv::GetSerialPort_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_networking_interfaces::srv::GetSerialPort_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_networking_interfaces::srv::GetSerialPort_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_networking_interfaces::srv::GetSerialPort_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_networking_interfaces::srv::GetSerialPort_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_networking_interfaces::srv::GetSerialPort_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_networking_interfaces::srv::GetSerialPort_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_networking_interfaces__srv__GetSerialPort_Response
    std::shared_ptr<vehicle_networking_interfaces::srv::GetSerialPort_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_networking_interfaces__srv__GetSerialPort_Response
    std::shared_ptr<vehicle_networking_interfaces::srv::GetSerialPort_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetSerialPort_Response_ & other) const
  {
    if (this->port != other.port) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetSerialPort_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetSerialPort_Response_

// alias to use template instance with default allocator
using GetSerialPort_Response =
  vehicle_networking_interfaces::srv::GetSerialPort_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace vehicle_networking_interfaces

namespace vehicle_networking_interfaces
{

namespace srv
{

struct GetSerialPort
{
  using Request = vehicle_networking_interfaces::srv::GetSerialPort_Request;
  using Response = vehicle_networking_interfaces::srv::GetSerialPort_Response;
};

}  // namespace srv

}  // namespace vehicle_networking_interfaces

#endif  // VEHICLE_NETWORKING_INTERFACES__SRV__DETAIL__GET_SERIAL_PORT__STRUCT_HPP_
