// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_interfaces:srv/GetSerialDeviceStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__SRV__DETAIL__GET_SERIAL_DEVICE_STATUS__STRUCT_HPP_
#define VEHICLE_INTERFACES__SRV__DETAIL__GET_SERIAL_DEVICE_STATUS__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__vehicle_interfaces__srv__GetSerialDeviceStatus_Request __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_interfaces__srv__GetSerialDeviceStatus_Request __declspec(deprecated)
#endif

namespace vehicle_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetSerialDeviceStatus_Request_
{
  using Type = GetSerialDeviceStatus_Request_<ContainerAllocator>;

  explicit GetSerialDeviceStatus_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->device = "";
    }
  }

  explicit GetSerialDeviceStatus_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    vehicle_interfaces::srv::GetSerialDeviceStatus_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_interfaces::srv::GetSerialDeviceStatus_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_interfaces::srv::GetSerialDeviceStatus_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_interfaces::srv::GetSerialDeviceStatus_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_interfaces::srv::GetSerialDeviceStatus_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_interfaces::srv::GetSerialDeviceStatus_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_interfaces::srv::GetSerialDeviceStatus_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_interfaces::srv::GetSerialDeviceStatus_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_interfaces::srv::GetSerialDeviceStatus_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_interfaces::srv::GetSerialDeviceStatus_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_interfaces__srv__GetSerialDeviceStatus_Request
    std::shared_ptr<vehicle_interfaces::srv::GetSerialDeviceStatus_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_interfaces__srv__GetSerialDeviceStatus_Request
    std::shared_ptr<vehicle_interfaces::srv::GetSerialDeviceStatus_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetSerialDeviceStatus_Request_ & other) const
  {
    if (this->device != other.device) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetSerialDeviceStatus_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetSerialDeviceStatus_Request_

// alias to use template instance with default allocator
using GetSerialDeviceStatus_Request =
  vehicle_interfaces::srv::GetSerialDeviceStatus_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace vehicle_interfaces


#ifndef _WIN32
# define DEPRECATED__vehicle_interfaces__srv__GetSerialDeviceStatus_Response __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_interfaces__srv__GetSerialDeviceStatus_Response __declspec(deprecated)
#endif

namespace vehicle_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetSerialDeviceStatus_Response_
{
  using Type = GetSerialDeviceStatus_Response_<ContainerAllocator>;

  explicit GetSerialDeviceStatus_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->port = "";
      this->connected = false;
    }
  }

  explicit GetSerialDeviceStatus_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : port(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->port = "";
      this->connected = false;
    }
  }

  // field types and members
  using _port_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _port_type port;
  using _connected_type =
    bool;
  _connected_type connected;

  // setters for named parameter idiom
  Type & set__port(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->port = _arg;
    return *this;
  }
  Type & set__connected(
    const bool & _arg)
  {
    this->connected = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_interfaces::srv::GetSerialDeviceStatus_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_interfaces::srv::GetSerialDeviceStatus_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_interfaces::srv::GetSerialDeviceStatus_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_interfaces::srv::GetSerialDeviceStatus_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_interfaces::srv::GetSerialDeviceStatus_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_interfaces::srv::GetSerialDeviceStatus_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_interfaces::srv::GetSerialDeviceStatus_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_interfaces::srv::GetSerialDeviceStatus_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_interfaces::srv::GetSerialDeviceStatus_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_interfaces::srv::GetSerialDeviceStatus_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_interfaces__srv__GetSerialDeviceStatus_Response
    std::shared_ptr<vehicle_interfaces::srv::GetSerialDeviceStatus_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_interfaces__srv__GetSerialDeviceStatus_Response
    std::shared_ptr<vehicle_interfaces::srv::GetSerialDeviceStatus_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetSerialDeviceStatus_Response_ & other) const
  {
    if (this->port != other.port) {
      return false;
    }
    if (this->connected != other.connected) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetSerialDeviceStatus_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetSerialDeviceStatus_Response_

// alias to use template instance with default allocator
using GetSerialDeviceStatus_Response =
  vehicle_interfaces::srv::GetSerialDeviceStatus_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace vehicle_interfaces

namespace vehicle_interfaces
{

namespace srv
{

struct GetSerialDeviceStatus
{
  using Request = vehicle_interfaces::srv::GetSerialDeviceStatus_Request;
  using Response = vehicle_interfaces::srv::GetSerialDeviceStatus_Response;
};

}  // namespace srv

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__SRV__DETAIL__GET_SERIAL_DEVICE_STATUS__STRUCT_HPP_
