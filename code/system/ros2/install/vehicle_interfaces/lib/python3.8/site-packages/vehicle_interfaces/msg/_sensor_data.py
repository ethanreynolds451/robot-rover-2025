# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vehicle_interfaces:msg/SensorData.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SensorData(type):
    """Metaclass of message 'SensorData'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('vehicle_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'vehicle_interfaces.msg.SensorData')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__sensor_data
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__sensor_data
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__sensor_data
            cls._TYPE_SUPPORT = module.type_support_msg__msg__sensor_data
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__sensor_data

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

            from vehicle_interfaces.msg import EncoderData
            if EncoderData.__class__._TYPE_SUPPORT is None:
                EncoderData.__class__.__import_type_support__()

            from vehicle_interfaces.msg import GPSData
            if GPSData.__class__._TYPE_SUPPORT is None:
                GPSData.__class__.__import_type_support__()

            from vehicle_interfaces.msg import IRData
            if IRData.__class__._TYPE_SUPPORT is None:
                IRData.__class__.__import_type_support__()

            from vehicle_interfaces.msg import MPUData
            if MPUData.__class__._TYPE_SUPPORT is None:
                MPUData.__class__.__import_type_support__()

            from vehicle_interfaces.msg import QMCData
            if QMCData.__class__._TYPE_SUPPORT is None:
                QMCData.__class__.__import_type_support__()

            from vehicle_interfaces.msg import TemperatureData
            if TemperatureData.__class__._TYPE_SUPPORT is None:
                TemperatureData.__class__.__import_type_support__()

            from vehicle_interfaces.msg import ToFData
            if ToFData.__class__._TYPE_SUPPORT is None:
                ToFData.__class__.__import_type_support__()

            from vehicle_interfaces.msg import UltrasonicData
            if UltrasonicData.__class__._TYPE_SUPPORT is None:
                UltrasonicData.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SensorData(metaclass=Metaclass_SensorData):
    """Message class 'SensorData'."""

    __slots__ = [
        '_header',
        '_arduino_timestamp',
        '_mpu',
        '_qmc',
        '_gps',
        '_tof',
        '_ultrasonic',
        '_temperature',
        '_encoder',
        '_ir_remote',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'arduino_timestamp': 'uint32',
        'mpu': 'sequence<vehicle_interfaces/MPUData>',
        'qmc': 'sequence<vehicle_interfaces/QMCData>',
        'gps': 'sequence<vehicle_interfaces/GPSData>',
        'tof': 'sequence<vehicle_interfaces/ToFData>',
        'ultrasonic': 'sequence<vehicle_interfaces/UltrasonicData>',
        'temperature': 'sequence<vehicle_interfaces/TemperatureData>',
        'encoder': 'sequence<vehicle_interfaces/EncoderData>',
        'ir_remote': 'sequence<vehicle_interfaces/IRData>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['vehicle_interfaces', 'msg'], 'MPUData')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['vehicle_interfaces', 'msg'], 'QMCData')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['vehicle_interfaces', 'msg'], 'GPSData')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['vehicle_interfaces', 'msg'], 'ToFData')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['vehicle_interfaces', 'msg'], 'UltrasonicData')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['vehicle_interfaces', 'msg'], 'TemperatureData')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['vehicle_interfaces', 'msg'], 'EncoderData')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['vehicle_interfaces', 'msg'], 'IRData')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.arduino_timestamp = kwargs.get('arduino_timestamp', int())
        self.mpu = kwargs.get('mpu', [])
        self.qmc = kwargs.get('qmc', [])
        self.gps = kwargs.get('gps', [])
        self.tof = kwargs.get('tof', [])
        self.ultrasonic = kwargs.get('ultrasonic', [])
        self.temperature = kwargs.get('temperature', [])
        self.encoder = kwargs.get('encoder', [])
        self.ir_remote = kwargs.get('ir_remote', [])

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.arduino_timestamp != other.arduino_timestamp:
            return False
        if self.mpu != other.mpu:
            return False
        if self.qmc != other.qmc:
            return False
        if self.gps != other.gps:
            return False
        if self.tof != other.tof:
            return False
        if self.ultrasonic != other.ultrasonic:
            return False
        if self.temperature != other.temperature:
            return False
        if self.encoder != other.encoder:
            return False
        if self.ir_remote != other.ir_remote:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @property
    def arduino_timestamp(self):
        """Message field 'arduino_timestamp'."""
        return self._arduino_timestamp

    @arduino_timestamp.setter
    def arduino_timestamp(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'arduino_timestamp' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'arduino_timestamp' field must be an unsigned integer in [0, 4294967295]"
        self._arduino_timestamp = value

    @property
    def mpu(self):
        """Message field 'mpu'."""
        return self._mpu

    @mpu.setter
    def mpu(self, value):
        if __debug__:
            from vehicle_interfaces.msg import MPUData
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, MPUData) for v in value) and
                 True), \
                "The 'mpu' field must be a set or sequence and each value of type 'MPUData'"
        self._mpu = value

    @property
    def qmc(self):
        """Message field 'qmc'."""
        return self._qmc

    @qmc.setter
    def qmc(self, value):
        if __debug__:
            from vehicle_interfaces.msg import QMCData
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, QMCData) for v in value) and
                 True), \
                "The 'qmc' field must be a set or sequence and each value of type 'QMCData'"
        self._qmc = value

    @property
    def gps(self):
        """Message field 'gps'."""
        return self._gps

    @gps.setter
    def gps(self, value):
        if __debug__:
            from vehicle_interfaces.msg import GPSData
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, GPSData) for v in value) and
                 True), \
                "The 'gps' field must be a set or sequence and each value of type 'GPSData'"
        self._gps = value

    @property
    def tof(self):
        """Message field 'tof'."""
        return self._tof

    @tof.setter
    def tof(self, value):
        if __debug__:
            from vehicle_interfaces.msg import ToFData
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, ToFData) for v in value) and
                 True), \
                "The 'tof' field must be a set or sequence and each value of type 'ToFData'"
        self._tof = value

    @property
    def ultrasonic(self):
        """Message field 'ultrasonic'."""
        return self._ultrasonic

    @ultrasonic.setter
    def ultrasonic(self, value):
        if __debug__:
            from vehicle_interfaces.msg import UltrasonicData
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, UltrasonicData) for v in value) and
                 True), \
                "The 'ultrasonic' field must be a set or sequence and each value of type 'UltrasonicData'"
        self._ultrasonic = value

    @property
    def temperature(self):
        """Message field 'temperature'."""
        return self._temperature

    @temperature.setter
    def temperature(self, value):
        if __debug__:
            from vehicle_interfaces.msg import TemperatureData
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, TemperatureData) for v in value) and
                 True), \
                "The 'temperature' field must be a set or sequence and each value of type 'TemperatureData'"
        self._temperature = value

    @property
    def encoder(self):
        """Message field 'encoder'."""
        return self._encoder

    @encoder.setter
    def encoder(self, value):
        if __debug__:
            from vehicle_interfaces.msg import EncoderData
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, EncoderData) for v in value) and
                 True), \
                "The 'encoder' field must be a set or sequence and each value of type 'EncoderData'"
        self._encoder = value

    @property
    def ir_remote(self):
        """Message field 'ir_remote'."""
        return self._ir_remote

    @ir_remote.setter
    def ir_remote(self, value):
        if __debug__:
            from vehicle_interfaces.msg import IRData
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, IRData) for v in value) and
                 True), \
                "The 'ir_remote' field must be a set or sequence and each value of type 'IRData'"
        self._ir_remote = value
