# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vehicle_interfaces:msg/ControlData.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ControlData(type):
    """Metaclass of message 'ControlData'."""

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
                'vehicle_interfaces.msg.ControlData')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__control_data
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__control_data
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__control_data
            cls._TYPE_SUPPORT = module.type_support_msg__msg__control_data
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__control_data

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ControlData(metaclass=Metaclass_ControlData):
    """Message class 'ControlData'."""

    __slots__ = [
        '_header',
        '_brake',
        '_drive_reverse',
        '_steer_reverse',
        '_shift_up',
        '_drive_power',
        '_steer_power',
        '_fan_speed',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'brake': 'boolean',
        'drive_reverse': 'boolean',
        'steer_reverse': 'boolean',
        'shift_up': 'boolean',
        'drive_power': 'uint8',
        'steer_power': 'uint8',
        'fan_speed': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.brake = kwargs.get('brake', bool())
        self.drive_reverse = kwargs.get('drive_reverse', bool())
        self.steer_reverse = kwargs.get('steer_reverse', bool())
        self.shift_up = kwargs.get('shift_up', bool())
        self.drive_power = kwargs.get('drive_power', int())
        self.steer_power = kwargs.get('steer_power', int())
        self.fan_speed = kwargs.get('fan_speed', int())

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
        if self.brake != other.brake:
            return False
        if self.drive_reverse != other.drive_reverse:
            return False
        if self.steer_reverse != other.steer_reverse:
            return False
        if self.shift_up != other.shift_up:
            return False
        if self.drive_power != other.drive_power:
            return False
        if self.steer_power != other.steer_power:
            return False
        if self.fan_speed != other.fan_speed:
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
    def brake(self):
        """Message field 'brake'."""
        return self._brake

    @brake.setter
    def brake(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'brake' field must be of type 'bool'"
        self._brake = value

    @property
    def drive_reverse(self):
        """Message field 'drive_reverse'."""
        return self._drive_reverse

    @drive_reverse.setter
    def drive_reverse(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'drive_reverse' field must be of type 'bool'"
        self._drive_reverse = value

    @property
    def steer_reverse(self):
        """Message field 'steer_reverse'."""
        return self._steer_reverse

    @steer_reverse.setter
    def steer_reverse(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'steer_reverse' field must be of type 'bool'"
        self._steer_reverse = value

    @property
    def shift_up(self):
        """Message field 'shift_up'."""
        return self._shift_up

    @shift_up.setter
    def shift_up(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'shift_up' field must be of type 'bool'"
        self._shift_up = value

    @property
    def drive_power(self):
        """Message field 'drive_power'."""
        return self._drive_power

    @drive_power.setter
    def drive_power(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'drive_power' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'drive_power' field must be an unsigned integer in [0, 255]"
        self._drive_power = value

    @property
    def steer_power(self):
        """Message field 'steer_power'."""
        return self._steer_power

    @steer_power.setter
    def steer_power(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'steer_power' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'steer_power' field must be an unsigned integer in [0, 255]"
        self._steer_power = value

    @property
    def fan_speed(self):
        """Message field 'fan_speed'."""
        return self._fan_speed

    @fan_speed.setter
    def fan_speed(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'fan_speed' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'fan_speed' field must be an unsigned integer in [0, 255]"
        self._fan_speed = value
