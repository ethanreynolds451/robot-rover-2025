// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vehicle_interfaces:msg/ControlData.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "vehicle_interfaces/msg/detail/control_data__struct.h"
#include "vehicle_interfaces/msg/detail/control_data__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool vehicle_interfaces__msg__control_data__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[49];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("vehicle_interfaces.msg._control_data.ControlData", full_classname_dest, 48) == 0);
  }
  vehicle_interfaces__msg__ControlData * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // brake
    PyObject * field = PyObject_GetAttrString(_pymsg, "brake");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->brake = (Py_True == field);
    Py_DECREF(field);
  }
  {  // drive_reverse
    PyObject * field = PyObject_GetAttrString(_pymsg, "drive_reverse");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->drive_reverse = (Py_True == field);
    Py_DECREF(field);
  }
  {  // steer_reverse
    PyObject * field = PyObject_GetAttrString(_pymsg, "steer_reverse");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->steer_reverse = (Py_True == field);
    Py_DECREF(field);
  }
  {  // shift_up
    PyObject * field = PyObject_GetAttrString(_pymsg, "shift_up");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->shift_up = (Py_True == field);
    Py_DECREF(field);
  }
  {  // drive_power
    PyObject * field = PyObject_GetAttrString(_pymsg, "drive_power");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->drive_power = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // steer_power
    PyObject * field = PyObject_GetAttrString(_pymsg, "steer_power");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->steer_power = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // fan_speed
    PyObject * field = PyObject_GetAttrString(_pymsg, "fan_speed");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->fan_speed = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vehicle_interfaces__msg__control_data__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of ControlData */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vehicle_interfaces.msg._control_data");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "ControlData");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vehicle_interfaces__msg__ControlData * ros_message = (vehicle_interfaces__msg__ControlData *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = std_msgs__msg__header__convert_to_py(&ros_message->header);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "header", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // brake
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->brake ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "brake", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // drive_reverse
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->drive_reverse ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "drive_reverse", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // steer_reverse
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->steer_reverse ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "steer_reverse", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // shift_up
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->shift_up ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "shift_up", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // drive_power
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->drive_power);
    {
      int rc = PyObject_SetAttrString(_pymessage, "drive_power", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // steer_power
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->steer_power);
    {
      int rc = PyObject_SetAttrString(_pymessage, "steer_power", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // fan_speed
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->fan_speed);
    {
      int rc = PyObject_SetAttrString(_pymessage, "fan_speed", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
