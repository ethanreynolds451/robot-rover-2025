// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_interfaces:msg/SensorData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__SENSOR_DATA__BUILDER_HPP_
#define VEHICLE_INTERFACES__MSG__DETAIL__SENSOR_DATA__BUILDER_HPP_

#include "vehicle_interfaces/msg/detail/sensor_data__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace vehicle_interfaces
{

namespace msg
{

namespace builder
{

class Init_SensorData_ir_remote
{
public:
  explicit Init_SensorData_ir_remote(::vehicle_interfaces::msg::SensorData & msg)
  : msg_(msg)
  {}
  ::vehicle_interfaces::msg::SensorData ir_remote(::vehicle_interfaces::msg::SensorData::_ir_remote_type arg)
  {
    msg_.ir_remote = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_interfaces::msg::SensorData msg_;
};

class Init_SensorData_encoder
{
public:
  explicit Init_SensorData_encoder(::vehicle_interfaces::msg::SensorData & msg)
  : msg_(msg)
  {}
  Init_SensorData_ir_remote encoder(::vehicle_interfaces::msg::SensorData::_encoder_type arg)
  {
    msg_.encoder = std::move(arg);
    return Init_SensorData_ir_remote(msg_);
  }

private:
  ::vehicle_interfaces::msg::SensorData msg_;
};

class Init_SensorData_temperature
{
public:
  explicit Init_SensorData_temperature(::vehicle_interfaces::msg::SensorData & msg)
  : msg_(msg)
  {}
  Init_SensorData_encoder temperature(::vehicle_interfaces::msg::SensorData::_temperature_type arg)
  {
    msg_.temperature = std::move(arg);
    return Init_SensorData_encoder(msg_);
  }

private:
  ::vehicle_interfaces::msg::SensorData msg_;
};

class Init_SensorData_ultrasonic
{
public:
  explicit Init_SensorData_ultrasonic(::vehicle_interfaces::msg::SensorData & msg)
  : msg_(msg)
  {}
  Init_SensorData_temperature ultrasonic(::vehicle_interfaces::msg::SensorData::_ultrasonic_type arg)
  {
    msg_.ultrasonic = std::move(arg);
    return Init_SensorData_temperature(msg_);
  }

private:
  ::vehicle_interfaces::msg::SensorData msg_;
};

class Init_SensorData_tof
{
public:
  explicit Init_SensorData_tof(::vehicle_interfaces::msg::SensorData & msg)
  : msg_(msg)
  {}
  Init_SensorData_ultrasonic tof(::vehicle_interfaces::msg::SensorData::_tof_type arg)
  {
    msg_.tof = std::move(arg);
    return Init_SensorData_ultrasonic(msg_);
  }

private:
  ::vehicle_interfaces::msg::SensorData msg_;
};

class Init_SensorData_gps
{
public:
  explicit Init_SensorData_gps(::vehicle_interfaces::msg::SensorData & msg)
  : msg_(msg)
  {}
  Init_SensorData_tof gps(::vehicle_interfaces::msg::SensorData::_gps_type arg)
  {
    msg_.gps = std::move(arg);
    return Init_SensorData_tof(msg_);
  }

private:
  ::vehicle_interfaces::msg::SensorData msg_;
};

class Init_SensorData_qmc
{
public:
  explicit Init_SensorData_qmc(::vehicle_interfaces::msg::SensorData & msg)
  : msg_(msg)
  {}
  Init_SensorData_gps qmc(::vehicle_interfaces::msg::SensorData::_qmc_type arg)
  {
    msg_.qmc = std::move(arg);
    return Init_SensorData_gps(msg_);
  }

private:
  ::vehicle_interfaces::msg::SensorData msg_;
};

class Init_SensorData_mpu
{
public:
  explicit Init_SensorData_mpu(::vehicle_interfaces::msg::SensorData & msg)
  : msg_(msg)
  {}
  Init_SensorData_qmc mpu(::vehicle_interfaces::msg::SensorData::_mpu_type arg)
  {
    msg_.mpu = std::move(arg);
    return Init_SensorData_qmc(msg_);
  }

private:
  ::vehicle_interfaces::msg::SensorData msg_;
};

class Init_SensorData_arduino_timestamp
{
public:
  explicit Init_SensorData_arduino_timestamp(::vehicle_interfaces::msg::SensorData & msg)
  : msg_(msg)
  {}
  Init_SensorData_mpu arduino_timestamp(::vehicle_interfaces::msg::SensorData::_arduino_timestamp_type arg)
  {
    msg_.arduino_timestamp = std::move(arg);
    return Init_SensorData_mpu(msg_);
  }

private:
  ::vehicle_interfaces::msg::SensorData msg_;
};

class Init_SensorData_header
{
public:
  Init_SensorData_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SensorData_arduino_timestamp header(::vehicle_interfaces::msg::SensorData::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_SensorData_arduino_timestamp(msg_);
  }

private:
  ::vehicle_interfaces::msg::SensorData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_interfaces::msg::SensorData>()
{
  return vehicle_interfaces::msg::builder::Init_SensorData_header();
}

}  // namespace vehicle_interfaces

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__SENSOR_DATA__BUILDER_HPP_
