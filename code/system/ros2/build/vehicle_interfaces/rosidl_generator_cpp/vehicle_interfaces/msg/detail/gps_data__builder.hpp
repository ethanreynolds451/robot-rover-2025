// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_interfaces:msg/GPSData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__GPS_DATA__BUILDER_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__GPS_DATA__BUILDER_HPP_

#include "vehicle_interfaces/msg/detail/gps_data__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace vehicle_interfaces
{

namespace msg
{

namespace builder
{

class Init_GPSData_sats
{
public:
  explicit Init_GPSData_sats(::vehicle_interfaces::msg::GPSData & msg)
  : msg_(msg)
  {}
  ::vehicle_interfaces::msg::GPSData sats(::vehicle_interfaces::msg::GPSData::_sats_type arg)
  {
    msg_.sats = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_interfaces::msg::GPSData msg_;
};

class Init_GPSData_gps_time
{
public:
  explicit Init_GPSData_gps_time(::vehicle_interfaces::msg::GPSData & msg)
  : msg_(msg)
  {}
  Init_GPSData_sats gps_time(::vehicle_interfaces::msg::GPSData::_gps_time_type arg)
  {
    msg_.gps_time = std::move(arg);
    return Init_GPSData_sats(msg_);
  }

private:
  ::vehicle_interfaces::msg::GPSData msg_;
};

class Init_GPSData_speed_kmph
{
public:
  explicit Init_GPSData_speed_kmph(::vehicle_interfaces::msg::GPSData & msg)
  : msg_(msg)
  {}
  Init_GPSData_gps_time speed_kmph(::vehicle_interfaces::msg::GPSData::_speed_kmph_type arg)
  {
    msg_.speed_kmph = std::move(arg);
    return Init_GPSData_gps_time(msg_);
  }

private:
  ::vehicle_interfaces::msg::GPSData msg_;
};

class Init_GPSData_heading
{
public:
  explicit Init_GPSData_heading(::vehicle_interfaces::msg::GPSData & msg)
  : msg_(msg)
  {}
  Init_GPSData_speed_kmph heading(::vehicle_interfaces::msg::GPSData::_heading_type arg)
  {
    msg_.heading = std::move(arg);
    return Init_GPSData_speed_kmph(msg_);
  }

private:
  ::vehicle_interfaces::msg::GPSData msg_;
};

class Init_GPSData_position
{
public:
  explicit Init_GPSData_position(::vehicle_interfaces::msg::GPSData & msg)
  : msg_(msg)
  {}
  Init_GPSData_heading position(::vehicle_interfaces::msg::GPSData::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_GPSData_heading(msg_);
  }

private:
  ::vehicle_interfaces::msg::GPSData msg_;
};

class Init_GPSData_arduino_timestamp
{
public:
  explicit Init_GPSData_arduino_timestamp(::vehicle_interfaces::msg::GPSData & msg)
  : msg_(msg)
  {}
  Init_GPSData_position arduino_timestamp(::vehicle_interfaces::msg::GPSData::_arduino_timestamp_type arg)
  {
    msg_.arduino_timestamp = std::move(arg);
    return Init_GPSData_position(msg_);
  }

private:
  ::vehicle_interfaces::msg::GPSData msg_;
};

class Init_GPSData_is_valid
{
public:
  explicit Init_GPSData_is_valid(::vehicle_interfaces::msg::GPSData & msg)
  : msg_(msg)
  {}
  Init_GPSData_arduino_timestamp is_valid(::vehicle_interfaces::msg::GPSData::_is_valid_type arg)
  {
    msg_.is_valid = std::move(arg);
    return Init_GPSData_arduino_timestamp(msg_);
  }

private:
  ::vehicle_interfaces::msg::GPSData msg_;
};

class Init_GPSData_header
{
public:
  Init_GPSData_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GPSData_is_valid header(::vehicle_interfaces::msg::GPSData::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_GPSData_is_valid(msg_);
  }

private:
  ::vehicle_interfaces::msg::GPSData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_interfaces::msg::GPSData>()
{
  return vehicle_interfaces::msg::builder::Init_GPSData_header();
}

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__GPS_DATA__BUILDER_HPP_
