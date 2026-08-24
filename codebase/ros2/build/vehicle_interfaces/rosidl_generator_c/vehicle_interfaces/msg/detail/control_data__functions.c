// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vehicle_interfaces:msg/ControlData.idl
// generated code does not contain a copyright notice
#include "vehicle_interfaces/msg/detail/control_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
vehicle_interfaces__msg__ControlData__init(vehicle_interfaces__msg__ControlData * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    vehicle_interfaces__msg__ControlData__fini(msg);
    return false;
  }
  // brake
  // drive_reverse
  // steer_reverse
  // shift_up
  // drive_power
  // steer_power
  // fan_speed
  return true;
}

void
vehicle_interfaces__msg__ControlData__fini(vehicle_interfaces__msg__ControlData * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // brake
  // drive_reverse
  // steer_reverse
  // shift_up
  // drive_power
  // steer_power
  // fan_speed
}

bool
vehicle_interfaces__msg__ControlData__are_equal(const vehicle_interfaces__msg__ControlData * lhs, const vehicle_interfaces__msg__ControlData * rhs)
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
  // brake
  if (lhs->brake != rhs->brake) {
    return false;
  }
  // drive_reverse
  if (lhs->drive_reverse != rhs->drive_reverse) {
    return false;
  }
  // steer_reverse
  if (lhs->steer_reverse != rhs->steer_reverse) {
    return false;
  }
  // shift_up
  if (lhs->shift_up != rhs->shift_up) {
    return false;
  }
  // drive_power
  if (lhs->drive_power != rhs->drive_power) {
    return false;
  }
  // steer_power
  if (lhs->steer_power != rhs->steer_power) {
    return false;
  }
  // fan_speed
  if (lhs->fan_speed != rhs->fan_speed) {
    return false;
  }
  return true;
}

bool
vehicle_interfaces__msg__ControlData__copy(
  const vehicle_interfaces__msg__ControlData * input,
  vehicle_interfaces__msg__ControlData * output)
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
  // brake
  output->brake = input->brake;
  // drive_reverse
  output->drive_reverse = input->drive_reverse;
  // steer_reverse
  output->steer_reverse = input->steer_reverse;
  // shift_up
  output->shift_up = input->shift_up;
  // drive_power
  output->drive_power = input->drive_power;
  // steer_power
  output->steer_power = input->steer_power;
  // fan_speed
  output->fan_speed = input->fan_speed;
  return true;
}

vehicle_interfaces__msg__ControlData *
vehicle_interfaces__msg__ControlData__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interfaces__msg__ControlData * msg = (vehicle_interfaces__msg__ControlData *)allocator.allocate(sizeof(vehicle_interfaces__msg__ControlData), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vehicle_interfaces__msg__ControlData));
  bool success = vehicle_interfaces__msg__ControlData__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vehicle_interfaces__msg__ControlData__destroy(vehicle_interfaces__msg__ControlData * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vehicle_interfaces__msg__ControlData__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vehicle_interfaces__msg__ControlData__Sequence__init(vehicle_interfaces__msg__ControlData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interfaces__msg__ControlData * data = NULL;

  if (size) {
    data = (vehicle_interfaces__msg__ControlData *)allocator.zero_allocate(size, sizeof(vehicle_interfaces__msg__ControlData), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vehicle_interfaces__msg__ControlData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vehicle_interfaces__msg__ControlData__fini(&data[i - 1]);
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
vehicle_interfaces__msg__ControlData__Sequence__fini(vehicle_interfaces__msg__ControlData__Sequence * array)
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
      vehicle_interfaces__msg__ControlData__fini(&array->data[i]);
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

vehicle_interfaces__msg__ControlData__Sequence *
vehicle_interfaces__msg__ControlData__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interfaces__msg__ControlData__Sequence * array = (vehicle_interfaces__msg__ControlData__Sequence *)allocator.allocate(sizeof(vehicle_interfaces__msg__ControlData__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vehicle_interfaces__msg__ControlData__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vehicle_interfaces__msg__ControlData__Sequence__destroy(vehicle_interfaces__msg__ControlData__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vehicle_interfaces__msg__ControlData__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vehicle_interfaces__msg__ControlData__Sequence__are_equal(const vehicle_interfaces__msg__ControlData__Sequence * lhs, const vehicle_interfaces__msg__ControlData__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vehicle_interfaces__msg__ControlData__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vehicle_interfaces__msg__ControlData__Sequence__copy(
  const vehicle_interfaces__msg__ControlData__Sequence * input,
  vehicle_interfaces__msg__ControlData__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vehicle_interfaces__msg__ControlData);
    vehicle_interfaces__msg__ControlData * data =
      (vehicle_interfaces__msg__ControlData *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vehicle_interfaces__msg__ControlData__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          vehicle_interfaces__msg__ControlData__fini(&data[i]);
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
    if (!vehicle_interfaces__msg__ControlData__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
