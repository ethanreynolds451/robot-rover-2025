// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vehicle_interfaces:srv/GetSerialPort.idl
// generated code does not contain a copyright notice
#include "vehicle_interfaces/srv/detail/get_serial_port__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `device`
#include "rosidl_runtime_c/string_functions.h"

bool
vehicle_interfaces__srv__GetSerialPort_Request__init(vehicle_interfaces__srv__GetSerialPort_Request * msg)
{
  if (!msg) {
    return false;
  }
  // device
  if (!rosidl_runtime_c__String__init(&msg->device)) {
    vehicle_interfaces__srv__GetSerialPort_Request__fini(msg);
    return false;
  }
  return true;
}

void
vehicle_interfaces__srv__GetSerialPort_Request__fini(vehicle_interfaces__srv__GetSerialPort_Request * msg)
{
  if (!msg) {
    return;
  }
  // device
  rosidl_runtime_c__String__fini(&msg->device);
}

bool
vehicle_interfaces__srv__GetSerialPort_Request__are_equal(const vehicle_interfaces__srv__GetSerialPort_Request * lhs, const vehicle_interfaces__srv__GetSerialPort_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // device
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->device), &(rhs->device)))
  {
    return false;
  }
  return true;
}

bool
vehicle_interfaces__srv__GetSerialPort_Request__copy(
  const vehicle_interfaces__srv__GetSerialPort_Request * input,
  vehicle_interfaces__srv__GetSerialPort_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // device
  if (!rosidl_runtime_c__String__copy(
      &(input->device), &(output->device)))
  {
    return false;
  }
  return true;
}

vehicle_interfaces__srv__GetSerialPort_Request *
vehicle_interfaces__srv__GetSerialPort_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interfaces__srv__GetSerialPort_Request * msg = (vehicle_interfaces__srv__GetSerialPort_Request *)allocator.allocate(sizeof(vehicle_interfaces__srv__GetSerialPort_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vehicle_interfaces__srv__GetSerialPort_Request));
  bool success = vehicle_interfaces__srv__GetSerialPort_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vehicle_interfaces__srv__GetSerialPort_Request__destroy(vehicle_interfaces__srv__GetSerialPort_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vehicle_interfaces__srv__GetSerialPort_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vehicle_interfaces__srv__GetSerialPort_Request__Sequence__init(vehicle_interfaces__srv__GetSerialPort_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interfaces__srv__GetSerialPort_Request * data = NULL;

  if (size) {
    data = (vehicle_interfaces__srv__GetSerialPort_Request *)allocator.zero_allocate(size, sizeof(vehicle_interfaces__srv__GetSerialPort_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vehicle_interfaces__srv__GetSerialPort_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vehicle_interfaces__srv__GetSerialPort_Request__fini(&data[i - 1]);
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
vehicle_interfaces__srv__GetSerialPort_Request__Sequence__fini(vehicle_interfaces__srv__GetSerialPort_Request__Sequence * array)
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
      vehicle_interfaces__srv__GetSerialPort_Request__fini(&array->data[i]);
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

vehicle_interfaces__srv__GetSerialPort_Request__Sequence *
vehicle_interfaces__srv__GetSerialPort_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interfaces__srv__GetSerialPort_Request__Sequence * array = (vehicle_interfaces__srv__GetSerialPort_Request__Sequence *)allocator.allocate(sizeof(vehicle_interfaces__srv__GetSerialPort_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vehicle_interfaces__srv__GetSerialPort_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vehicle_interfaces__srv__GetSerialPort_Request__Sequence__destroy(vehicle_interfaces__srv__GetSerialPort_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vehicle_interfaces__srv__GetSerialPort_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vehicle_interfaces__srv__GetSerialPort_Request__Sequence__are_equal(const vehicle_interfaces__srv__GetSerialPort_Request__Sequence * lhs, const vehicle_interfaces__srv__GetSerialPort_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vehicle_interfaces__srv__GetSerialPort_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vehicle_interfaces__srv__GetSerialPort_Request__Sequence__copy(
  const vehicle_interfaces__srv__GetSerialPort_Request__Sequence * input,
  vehicle_interfaces__srv__GetSerialPort_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vehicle_interfaces__srv__GetSerialPort_Request);
    vehicle_interfaces__srv__GetSerialPort_Request * data =
      (vehicle_interfaces__srv__GetSerialPort_Request *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vehicle_interfaces__srv__GetSerialPort_Request__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          vehicle_interfaces__srv__GetSerialPort_Request__fini(&data[i]);
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
    if (!vehicle_interfaces__srv__GetSerialPort_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `port`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
vehicle_interfaces__srv__GetSerialPort_Response__init(vehicle_interfaces__srv__GetSerialPort_Response * msg)
{
  if (!msg) {
    return false;
  }
  // port
  if (!rosidl_runtime_c__String__init(&msg->port)) {
    vehicle_interfaces__srv__GetSerialPort_Response__fini(msg);
    return false;
  }
  return true;
}

void
vehicle_interfaces__srv__GetSerialPort_Response__fini(vehicle_interfaces__srv__GetSerialPort_Response * msg)
{
  if (!msg) {
    return;
  }
  // port
  rosidl_runtime_c__String__fini(&msg->port);
}

bool
vehicle_interfaces__srv__GetSerialPort_Response__are_equal(const vehicle_interfaces__srv__GetSerialPort_Response * lhs, const vehicle_interfaces__srv__GetSerialPort_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // port
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->port), &(rhs->port)))
  {
    return false;
  }
  return true;
}

bool
vehicle_interfaces__srv__GetSerialPort_Response__copy(
  const vehicle_interfaces__srv__GetSerialPort_Response * input,
  vehicle_interfaces__srv__GetSerialPort_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // port
  if (!rosidl_runtime_c__String__copy(
      &(input->port), &(output->port)))
  {
    return false;
  }
  return true;
}

vehicle_interfaces__srv__GetSerialPort_Response *
vehicle_interfaces__srv__GetSerialPort_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interfaces__srv__GetSerialPort_Response * msg = (vehicle_interfaces__srv__GetSerialPort_Response *)allocator.allocate(sizeof(vehicle_interfaces__srv__GetSerialPort_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vehicle_interfaces__srv__GetSerialPort_Response));
  bool success = vehicle_interfaces__srv__GetSerialPort_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vehicle_interfaces__srv__GetSerialPort_Response__destroy(vehicle_interfaces__srv__GetSerialPort_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vehicle_interfaces__srv__GetSerialPort_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vehicle_interfaces__srv__GetSerialPort_Response__Sequence__init(vehicle_interfaces__srv__GetSerialPort_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interfaces__srv__GetSerialPort_Response * data = NULL;

  if (size) {
    data = (vehicle_interfaces__srv__GetSerialPort_Response *)allocator.zero_allocate(size, sizeof(vehicle_interfaces__srv__GetSerialPort_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vehicle_interfaces__srv__GetSerialPort_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vehicle_interfaces__srv__GetSerialPort_Response__fini(&data[i - 1]);
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
vehicle_interfaces__srv__GetSerialPort_Response__Sequence__fini(vehicle_interfaces__srv__GetSerialPort_Response__Sequence * array)
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
      vehicle_interfaces__srv__GetSerialPort_Response__fini(&array->data[i]);
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

vehicle_interfaces__srv__GetSerialPort_Response__Sequence *
vehicle_interfaces__srv__GetSerialPort_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interfaces__srv__GetSerialPort_Response__Sequence * array = (vehicle_interfaces__srv__GetSerialPort_Response__Sequence *)allocator.allocate(sizeof(vehicle_interfaces__srv__GetSerialPort_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vehicle_interfaces__srv__GetSerialPort_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vehicle_interfaces__srv__GetSerialPort_Response__Sequence__destroy(vehicle_interfaces__srv__GetSerialPort_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vehicle_interfaces__srv__GetSerialPort_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vehicle_interfaces__srv__GetSerialPort_Response__Sequence__are_equal(const vehicle_interfaces__srv__GetSerialPort_Response__Sequence * lhs, const vehicle_interfaces__srv__GetSerialPort_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vehicle_interfaces__srv__GetSerialPort_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vehicle_interfaces__srv__GetSerialPort_Response__Sequence__copy(
  const vehicle_interfaces__srv__GetSerialPort_Response__Sequence * input,
  vehicle_interfaces__srv__GetSerialPort_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vehicle_interfaces__srv__GetSerialPort_Response);
    vehicle_interfaces__srv__GetSerialPort_Response * data =
      (vehicle_interfaces__srv__GetSerialPort_Response *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vehicle_interfaces__srv__GetSerialPort_Response__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          vehicle_interfaces__srv__GetSerialPort_Response__fini(&data[i]);
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
    if (!vehicle_interfaces__srv__GetSerialPort_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
