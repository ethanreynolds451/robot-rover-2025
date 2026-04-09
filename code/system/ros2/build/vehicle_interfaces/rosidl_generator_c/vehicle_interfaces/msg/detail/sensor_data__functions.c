// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vehicle_interfaces:msg/SensorData.idl
// generated code does not contain a copyright notice
#include "vehicle_interfaces/msg/detail/sensor_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `mpu`
#include "vehicle_interfaces/msg/detail/mpu_data__functions.h"
// Member `qmc`
#include "vehicle_interfaces/msg/detail/qmc_data__functions.h"
// Member `gps`
#include "vehicle_interfaces/msg/detail/gps_data__functions.h"
// Member `tof`
#include "vehicle_interfaces/msg/detail/to_f_data__functions.h"
// Member `ultrasonic`
#include "vehicle_interfaces/msg/detail/ultrasonic_data__functions.h"
// Member `temperature`
#include "vehicle_interfaces/msg/detail/temperature_data__functions.h"
// Member `encoder`
#include "vehicle_interfaces/msg/detail/encoder_data__functions.h"
// Member `ir_remote`
#include "vehicle_interfaces/msg/detail/ir_data__functions.h"

bool
vehicle_interfaces__msg__SensorData__init(vehicle_interfaces__msg__SensorData * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    vehicle_interfaces__msg__SensorData__fini(msg);
    return false;
  }
  // arduino_timestamp
  // mpu
  if (!vehicle_interfaces__msg__MPUData__Sequence__init(&msg->mpu, 0)) {
    vehicle_interfaces__msg__SensorData__fini(msg);
    return false;
  }
  // qmc
  if (!vehicle_interfaces__msg__QMCData__Sequence__init(&msg->qmc, 0)) {
    vehicle_interfaces__msg__SensorData__fini(msg);
    return false;
  }
  // gps
  if (!vehicle_interfaces__msg__GPSData__Sequence__init(&msg->gps, 0)) {
    vehicle_interfaces__msg__SensorData__fini(msg);
    return false;
  }
  // tof
  if (!vehicle_interfaces__msg__ToFData__Sequence__init(&msg->tof, 0)) {
    vehicle_interfaces__msg__SensorData__fini(msg);
    return false;
  }
  // ultrasonic
  if (!vehicle_interfaces__msg__UltrasonicData__Sequence__init(&msg->ultrasonic, 0)) {
    vehicle_interfaces__msg__SensorData__fini(msg);
    return false;
  }
  // temperature
  if (!vehicle_interfaces__msg__TemperatureData__Sequence__init(&msg->temperature, 0)) {
    vehicle_interfaces__msg__SensorData__fini(msg);
    return false;
  }
  // encoder
  if (!vehicle_interfaces__msg__EncoderData__Sequence__init(&msg->encoder, 0)) {
    vehicle_interfaces__msg__SensorData__fini(msg);
    return false;
  }
  // ir_remote
  if (!vehicle_interfaces__msg__IRData__Sequence__init(&msg->ir_remote, 0)) {
    vehicle_interfaces__msg__SensorData__fini(msg);
    return false;
  }
  return true;
}

void
vehicle_interfaces__msg__SensorData__fini(vehicle_interfaces__msg__SensorData * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // arduino_timestamp
  // mpu
  vehicle_interfaces__msg__MPUData__Sequence__fini(&msg->mpu);
  // qmc
  vehicle_interfaces__msg__QMCData__Sequence__fini(&msg->qmc);
  // gps
  vehicle_interfaces__msg__GPSData__Sequence__fini(&msg->gps);
  // tof
  vehicle_interfaces__msg__ToFData__Sequence__fini(&msg->tof);
  // ultrasonic
  vehicle_interfaces__msg__UltrasonicData__Sequence__fini(&msg->ultrasonic);
  // temperature
  vehicle_interfaces__msg__TemperatureData__Sequence__fini(&msg->temperature);
  // encoder
  vehicle_interfaces__msg__EncoderData__Sequence__fini(&msg->encoder);
  // ir_remote
  vehicle_interfaces__msg__IRData__Sequence__fini(&msg->ir_remote);
}

bool
vehicle_interfaces__msg__SensorData__are_equal(const vehicle_interfaces__msg__SensorData * lhs, const vehicle_interfaces__msg__SensorData * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // arduino_timestamp
  if (lhs->arduino_timestamp != rhs->arduino_timestamp) {
    return false;
  }
  // mpu
  if (!vehicle_interfaces__msg__MPUData__Sequence__are_equal(
      &(lhs->mpu), &(rhs->mpu)))
  {
    return false;
  }
  // qmc
  if (!vehicle_interfaces__msg__QMCData__Sequence__are_equal(
      &(lhs->qmc), &(rhs->qmc)))
  {
    return false;
  }
  // gps
  if (!vehicle_interfaces__msg__GPSData__Sequence__are_equal(
      &(lhs->gps), &(rhs->gps)))
  {
    return false;
  }
  // tof
  if (!vehicle_interfaces__msg__ToFData__Sequence__are_equal(
      &(lhs->tof), &(rhs->tof)))
  {
    return false;
  }
  // ultrasonic
  if (!vehicle_interfaces__msg__UltrasonicData__Sequence__are_equal(
      &(lhs->ultrasonic), &(rhs->ultrasonic)))
  {
    return false;
  }
  // temperature
  if (!vehicle_interfaces__msg__TemperatureData__Sequence__are_equal(
      &(lhs->temperature), &(rhs->temperature)))
  {
    return false;
  }
  // encoder
  if (!vehicle_interfaces__msg__EncoderData__Sequence__are_equal(
      &(lhs->encoder), &(rhs->encoder)))
  {
    return false;
  }
  // ir_remote
  if (!vehicle_interfaces__msg__IRData__Sequence__are_equal(
      &(lhs->ir_remote), &(rhs->ir_remote)))
  {
    return false;
  }
  return true;
}

bool
vehicle_interfaces__msg__SensorData__copy(
  const vehicle_interfaces__msg__SensorData * input,
  vehicle_interfaces__msg__SensorData * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // arduino_timestamp
  output->arduino_timestamp = input->arduino_timestamp;
  // mpu
  if (!vehicle_interfaces__msg__MPUData__Sequence__copy(
      &(input->mpu), &(output->mpu)))
  {
    return false;
  }
  // qmc
  if (!vehicle_interfaces__msg__QMCData__Sequence__copy(
      &(input->qmc), &(output->qmc)))
  {
    return false;
  }
  // gps
  if (!vehicle_interfaces__msg__GPSData__Sequence__copy(
      &(input->gps), &(output->gps)))
  {
    return false;
  }
  // tof
  if (!vehicle_interfaces__msg__ToFData__Sequence__copy(
      &(input->tof), &(output->tof)))
  {
    return false;
  }
  // ultrasonic
  if (!vehicle_interfaces__msg__UltrasonicData__Sequence__copy(
      &(input->ultrasonic), &(output->ultrasonic)))
  {
    return false;
  }
  // temperature
  if (!vehicle_interfaces__msg__TemperatureData__Sequence__copy(
      &(input->temperature), &(output->temperature)))
  {
    return false;
  }
  // encoder
  if (!vehicle_interfaces__msg__EncoderData__Sequence__copy(
      &(input->encoder), &(output->encoder)))
  {
    return false;
  }
  // ir_remote
  if (!vehicle_interfaces__msg__IRData__Sequence__copy(
      &(input->ir_remote), &(output->ir_remote)))
  {
    return false;
  }
  return true;
}

vehicle_interfaces__msg__SensorData *
vehicle_interfaces__msg__SensorData__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interfaces__msg__SensorData * msg = (vehicle_interfaces__msg__SensorData *)allocator.allocate(sizeof(vehicle_interfaces__msg__SensorData), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vehicle_interfaces__msg__SensorData));
  bool success = vehicle_interfaces__msg__SensorData__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vehicle_interfaces__msg__SensorData__destroy(vehicle_interfaces__msg__SensorData * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vehicle_interfaces__msg__SensorData__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vehicle_interfaces__msg__SensorData__Sequence__init(vehicle_interfaces__msg__SensorData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interfaces__msg__SensorData * data = NULL;

  if (size) {
    data = (vehicle_interfaces__msg__SensorData *)allocator.zero_allocate(size, sizeof(vehicle_interfaces__msg__SensorData), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vehicle_interfaces__msg__SensorData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vehicle_interfaces__msg__SensorData__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
vehicle_interfaces__msg__SensorData__Sequence__fini(vehicle_interfaces__msg__SensorData__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      vehicle_interfaces__msg__SensorData__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

vehicle_interfaces__msg__SensorData__Sequence *
vehicle_interfaces__msg__SensorData__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interfaces__msg__SensorData__Sequence * array = (vehicle_interfaces__msg__SensorData__Sequence *)allocator.allocate(sizeof(vehicle_interfaces__msg__SensorData__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vehicle_interfaces__msg__SensorData__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vehicle_interfaces__msg__SensorData__Sequence__destroy(vehicle_interfaces__msg__SensorData__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vehicle_interfaces__msg__SensorData__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vehicle_interfaces__msg__SensorData__Sequence__are_equal(const vehicle_interfaces__msg__SensorData__Sequence * lhs, const vehicle_interfaces__msg__SensorData__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vehicle_interfaces__msg__SensorData__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vehicle_interfaces__msg__SensorData__Sequence__copy(
  const vehicle_interfaces__msg__SensorData__Sequence * input,
  vehicle_interfaces__msg__SensorData__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vehicle_interfaces__msg__SensorData);
    vehicle_interfaces__msg__SensorData * data =
      (vehicle_interfaces__msg__SensorData *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vehicle_interfaces__msg__SensorData__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          vehicle_interfaces__msg__SensorData__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vehicle_interfaces__msg__SensorData__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
