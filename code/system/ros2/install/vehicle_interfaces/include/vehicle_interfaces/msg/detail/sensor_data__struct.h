// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_interfaces:msg/SensorData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACES__MSG__DETAIL__SENSOR_DATA__STRUCT_H_
#define VEHICLE_INTERFACES__MSG__DETAIL__SENSOR_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'mpu'
#include "vehicle_interfaces/msg/detail/mpu_data__struct.h"
// Member 'qmc'
#include "vehicle_interfaces/msg/detail/qmc_data__struct.h"
// Member 'gps'
#include "vehicle_interfaces/msg/detail/gps_data__struct.h"
// Member 'tof'
#include "vehicle_interfaces/msg/detail/to_f_data__struct.h"
// Member 'ultrasonic'
#include "vehicle_interfaces/msg/detail/ultrasonic_data__struct.h"
// Member 'temperature'
#include "vehicle_interfaces/msg/detail/temperature_data__struct.h"
// Member 'encoder'
#include "vehicle_interfaces/msg/detail/encoder_data__struct.h"
// Member 'ir_remote'
#include "vehicle_interfaces/msg/detail/ir_data__struct.h"

// Struct defined in msg/SensorData in the package vehicle_interfaces.
typedef struct vehicle_interfaces__msg__SensorData
{
  std_msgs__msg__Header header;
  uint32_t arduino_timestamp;
  vehicle_interfaces__msg__MPUData__Sequence mpu;
  vehicle_interfaces__msg__QMCData__Sequence qmc;
  vehicle_interfaces__msg__GPSData__Sequence gps;
  vehicle_interfaces__msg__ToFData__Sequence tof;
  vehicle_interfaces__msg__UltrasonicData__Sequence ultrasonic;
  vehicle_interfaces__msg__TemperatureData__Sequence temperature;
  vehicle_interfaces__msg__EncoderData__Sequence encoder;
  vehicle_interfaces__msg__IRData__Sequence ir_remote;
} vehicle_interfaces__msg__SensorData;

// Struct for a sequence of vehicle_interfaces__msg__SensorData.
typedef struct vehicle_interfaces__msg__SensorData__Sequence
{
  vehicle_interfaces__msg__SensorData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_interfaces__msg__SensorData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_INTERFACES__MSG__DETAIL__SENSOR_DATA__STRUCT_H_
