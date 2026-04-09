// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vehicle_interfaces:msg/SensorData.idl
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
#include "vehicle_interfaces/msg/detail/sensor_data__struct.h"
#include "vehicle_interfaces/msg/detail/sensor_data__functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

// Nested array functions includes
#include "vehicle_interfaces/msg/detail/encoder_data__functions.h"
#include "vehicle_interfaces/msg/detail/gps_data__functions.h"
#include "vehicle_interfaces/msg/detail/ir_data__functions.h"
#include "vehicle_interfaces/msg/detail/mpu_data__functions.h"
#include "vehicle_interfaces/msg/detail/qmc_data__functions.h"
#include "vehicle_interfaces/msg/detail/temperature_data__functions.h"
#include "vehicle_interfaces/msg/detail/to_f_data__functions.h"
#include "vehicle_interfaces/msg/detail/ultrasonic_data__functions.h"
// end nested array functions include
ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);
bool vehicle_interfaces__msg__mpu_data__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vehicle_interfaces__msg__mpu_data__convert_to_py(void * raw_ros_message);
bool vehicle_interfaces__msg__qmc_data__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vehicle_interfaces__msg__qmc_data__convert_to_py(void * raw_ros_message);
bool vehicle_interfaces__msg__gps_data__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vehicle_interfaces__msg__gps_data__convert_to_py(void * raw_ros_message);
bool vehicle_interfaces__msg__to_f_data__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vehicle_interfaces__msg__to_f_data__convert_to_py(void * raw_ros_message);
bool vehicle_interfaces__msg__ultrasonic_data__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vehicle_interfaces__msg__ultrasonic_data__convert_to_py(void * raw_ros_message);
bool vehicle_interfaces__msg__temperature_data__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vehicle_interfaces__msg__temperature_data__convert_to_py(void * raw_ros_message);
bool vehicle_interfaces__msg__encoder_data__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vehicle_interfaces__msg__encoder_data__convert_to_py(void * raw_ros_message);
bool vehicle_interfaces__msg__ir_data__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vehicle_interfaces__msg__ir_data__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool vehicle_interfaces__msg__sensor_data__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[47];
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
    assert(strncmp("vehicle_interfaces.msg._sensor_data.SensorData", full_classname_dest, 46) == 0);
  }
  vehicle_interfaces__msg__SensorData * ros_message = _ros_message;
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
  {  // arduino_timestamp
    PyObject * field = PyObject_GetAttrString(_pymsg, "arduino_timestamp");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->arduino_timestamp = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // mpu
    PyObject * field = PyObject_GetAttrString(_pymsg, "mpu");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'mpu'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!vehicle_interfaces__msg__MPUData__Sequence__init(&(ros_message->mpu), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create vehicle_interfaces__msg__MPUData__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    vehicle_interfaces__msg__MPUData * dest = ros_message->mpu.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!vehicle_interfaces__msg__mpu_data__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // qmc
    PyObject * field = PyObject_GetAttrString(_pymsg, "qmc");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'qmc'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!vehicle_interfaces__msg__QMCData__Sequence__init(&(ros_message->qmc), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create vehicle_interfaces__msg__QMCData__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    vehicle_interfaces__msg__QMCData * dest = ros_message->qmc.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!vehicle_interfaces__msg__qmc_data__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // gps
    PyObject * field = PyObject_GetAttrString(_pymsg, "gps");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'gps'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!vehicle_interfaces__msg__GPSData__Sequence__init(&(ros_message->gps), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create vehicle_interfaces__msg__GPSData__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    vehicle_interfaces__msg__GPSData * dest = ros_message->gps.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!vehicle_interfaces__msg__gps_data__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // tof
    PyObject * field = PyObject_GetAttrString(_pymsg, "tof");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'tof'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!vehicle_interfaces__msg__ToFData__Sequence__init(&(ros_message->tof), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create vehicle_interfaces__msg__ToFData__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    vehicle_interfaces__msg__ToFData * dest = ros_message->tof.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!vehicle_interfaces__msg__to_f_data__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // ultrasonic
    PyObject * field = PyObject_GetAttrString(_pymsg, "ultrasonic");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'ultrasonic'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!vehicle_interfaces__msg__UltrasonicData__Sequence__init(&(ros_message->ultrasonic), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create vehicle_interfaces__msg__UltrasonicData__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    vehicle_interfaces__msg__UltrasonicData * dest = ros_message->ultrasonic.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!vehicle_interfaces__msg__ultrasonic_data__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // temperature
    PyObject * field = PyObject_GetAttrString(_pymsg, "temperature");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'temperature'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!vehicle_interfaces__msg__TemperatureData__Sequence__init(&(ros_message->temperature), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create vehicle_interfaces__msg__TemperatureData__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    vehicle_interfaces__msg__TemperatureData * dest = ros_message->temperature.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!vehicle_interfaces__msg__temperature_data__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // encoder
    PyObject * field = PyObject_GetAttrString(_pymsg, "encoder");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'encoder'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!vehicle_interfaces__msg__EncoderData__Sequence__init(&(ros_message->encoder), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create vehicle_interfaces__msg__EncoderData__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    vehicle_interfaces__msg__EncoderData * dest = ros_message->encoder.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!vehicle_interfaces__msg__encoder_data__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // ir_remote
    PyObject * field = PyObject_GetAttrString(_pymsg, "ir_remote");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'ir_remote'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!vehicle_interfaces__msg__IRData__Sequence__init(&(ros_message->ir_remote), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create vehicle_interfaces__msg__IRData__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    vehicle_interfaces__msg__IRData * dest = ros_message->ir_remote.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!vehicle_interfaces__msg__ir_data__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vehicle_interfaces__msg__sensor_data__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of SensorData */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vehicle_interfaces.msg._sensor_data");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "SensorData");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vehicle_interfaces__msg__SensorData * ros_message = (vehicle_interfaces__msg__SensorData *)raw_ros_message;
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
  {  // arduino_timestamp
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->arduino_timestamp);
    {
      int rc = PyObject_SetAttrString(_pymessage, "arduino_timestamp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mpu
    PyObject * field = NULL;
    size_t size = ros_message->mpu.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    vehicle_interfaces__msg__MPUData * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->mpu.data[i]);
      PyObject * pyitem = vehicle_interfaces__msg__mpu_data__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "mpu", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // qmc
    PyObject * field = NULL;
    size_t size = ros_message->qmc.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    vehicle_interfaces__msg__QMCData * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->qmc.data[i]);
      PyObject * pyitem = vehicle_interfaces__msg__qmc_data__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "qmc", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gps
    PyObject * field = NULL;
    size_t size = ros_message->gps.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    vehicle_interfaces__msg__GPSData * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->gps.data[i]);
      PyObject * pyitem = vehicle_interfaces__msg__gps_data__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "gps", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // tof
    PyObject * field = NULL;
    size_t size = ros_message->tof.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    vehicle_interfaces__msg__ToFData * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->tof.data[i]);
      PyObject * pyitem = vehicle_interfaces__msg__to_f_data__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "tof", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ultrasonic
    PyObject * field = NULL;
    size_t size = ros_message->ultrasonic.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    vehicle_interfaces__msg__UltrasonicData * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->ultrasonic.data[i]);
      PyObject * pyitem = vehicle_interfaces__msg__ultrasonic_data__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "ultrasonic", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // temperature
    PyObject * field = NULL;
    size_t size = ros_message->temperature.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    vehicle_interfaces__msg__TemperatureData * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->temperature.data[i]);
      PyObject * pyitem = vehicle_interfaces__msg__temperature_data__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "temperature", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // encoder
    PyObject * field = NULL;
    size_t size = ros_message->encoder.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    vehicle_interfaces__msg__EncoderData * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->encoder.data[i]);
      PyObject * pyitem = vehicle_interfaces__msg__encoder_data__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "encoder", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ir_remote
    PyObject * field = NULL;
    size_t size = ros_message->ir_remote.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    vehicle_interfaces__msg__IRData * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->ir_remote.data[i]);
      PyObject * pyitem = vehicle_interfaces__msg__ir_data__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "ir_remote", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
