// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vehicle_interfaces:msg/IRData.idl
// generated code does not contain a copyright notice
#include "vehicle_interfaces/msg/detail/ir_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `is_valid`
#include "std_msgs/msg/detail/bool__functions.h"

bool
vehicle_interfaces__msg__IRData__init(vehicle_interfaces__msg__IRData * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    vehicle_interfaces__msg__IRData__fini(msg);
    return false;
  }
  // is_valid
  if (!std_msgs__msg__Bool__init(&msg->is_valid)) {
    vehicle_interfaces__msg__IRData__fini(msg);
    return false;
  }
  // address
  // command
  // data
  return true;
}

void
vehicle_interfaces__msg__IRData__fini(vehicle_interfaces__msg__IRData * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // is_valid
  std_msgs__msg__Bool__fini(&msg->is_valid);
  // address
  // command
  // data
}

bool
vehicle_interfaces__msg__IRData__are_equal(const vehicle_interfaces__msg__IRData * lhs, const vehicle_interfaces__msg__IRData * rhs)
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
  // is_valid
  if (!std_msgs__msg__Bool__are_equal(
      &(lhs->is_valid), &(rhs->is_valid)))
  {
    return false;
  }
  // address
  if (lhs->address != rhs->address) {
    return false;
  }
  // command
  if (lhs->command != rhs->command) {
    return false;
  }
  // data
  if (lhs->data != rhs->data) {
    return false;
  }
  return true;
}

bool
vehicle_interfaces__msg__IRData__copy(
  const vehicle_interfaces__msg__IRData * input,
  vehicle_interfaces__msg__IRData * output)
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
  // is_valid
  if (!std_msgs__msg__Bool__copy(
      &(input->is_valid), &(output->is_valid)))
  {
    return false;
  }
  // address
  output->address = input->address;
  // command
  output->command = input->command;
  // data
  output->data = input->data;
  return true;
}

vehicle_interfaces__msg__IRData *
vehicle_interfaces__msg__IRData__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interfaces__msg__IRData * msg = (vehicle_interfaces__msg__IRData *)allocator.allocate(sizeof(vehicle_interfaces__msg__IRData), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vehicle_interfaces__msg__IRData));
  bool success = vehicle_interfaces__msg__IRData__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vehicle_interfaces__msg__IRData__destroy(vehicle_interfaces__msg__IRData * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vehicle_interfaces__msg__IRData__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vehicle_interfaces__msg__IRData__Sequence__init(vehicle_interfaces__msg__IRData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interfaces__msg__IRData * data = NULL;

  if (size) {
    data = (vehicle_interfaces__msg__IRData *)allocator.zero_allocate(size, sizeof(vehicle_interfaces__msg__IRData), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vehicle_interfaces__msg__IRData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vehicle_interfaces__msg__IRData__fini(&data[i - 1]);
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
vehicle_interfaces__msg__IRData__Sequence__fini(vehicle_interfaces__msg__IRData__Sequence * array)
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
      vehicle_interfaces__msg__IRData__fini(&array->data[i]);
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

vehicle_interfaces__msg__IRData__Sequence *
vehicle_interfaces__msg__IRData__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interfaces__msg__IRData__Sequence * array = (vehicle_interfaces__msg__IRData__Sequence *)allocator.allocate(sizeof(vehicle_interfaces__msg__IRData__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vehicle_interfaces__msg__IRData__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vehicle_interfaces__msg__IRData__Sequence__destroy(vehicle_interfaces__msg__IRData__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vehicle_interfaces__msg__IRData__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vehicle_interfaces__msg__IRData__Sequence__are_equal(const vehicle_interfaces__msg__IRData__Sequence * lhs, const vehicle_interfaces__msg__IRData__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vehicle_interfaces__msg__IRData__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vehicle_interfaces__msg__IRData__Sequence__copy(
  const vehicle_interfaces__msg__IRData__Sequence * input,
  vehicle_interfaces__msg__IRData__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vehicle_interfaces__msg__IRData);
    vehicle_interfaces__msg__IRData * data =
      (vehicle_interfaces__msg__IRData *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vehicle_interfaces__msg__IRData__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          vehicle_interfaces__msg__IRData__fini(&data[i]);
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
    if (!vehicle_interfaces__msg__IRData__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
