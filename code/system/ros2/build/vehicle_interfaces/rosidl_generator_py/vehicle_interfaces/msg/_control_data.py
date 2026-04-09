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
        '_brake',
        '_reverse',
        '_steering_reverse',
        '_shift_up',
        '_power',
        '_steering_power',
    ]

    _fields_and_field_types = {
        'brake': 'boolean',
        'reverse': 'boolean',
        'steering_reverse': 'boolean',
        'shift_up': 'boolean',
        'power': 'uint8',
        'steering_power': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.brake = kwargs.get('brake', bool())
        self.reverse = kwargs.get('reverse', bool())
        self.steering_reverse = kwargs.get('steering_reverse', bool())
        self.shift_up = kwargs.get('shift_up', bool())
        self.power = kwargs.get('power', int())
        self.steering_power = kwargs.get('steering_power', int())

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
        if self.brake != other.brake:
            return False
        if self.reverse != other.reverse:
            return False
        if self.steering_reverse != other.steering_reverse:
            return False
        if self.shift_up != other.shift_up:
            return False
        if self.power != other.power:
            return False
        if self.steering_power != other.steering_power:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

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
    def reverse(self):
        """Message field 'reverse'."""
        return self._reverse

    @reverse.setter
    def reverse(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'reverse' field must be of type 'bool'"
        self._reverse = value

    @property
    def steering_reverse(self):
        """Message field 'steering_reverse'."""
        return self._steering_reverse

    @steering_reverse.setter
    def steering_reverse(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'steering_reverse' field must be of type 'bool'"
        self._steering_reverse = value

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
    def power(self):
        """Message field 'power'."""
        return self._power

    @power.setter
    def power(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'power' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'power' field must be an unsigned integer in [0, 255]"
        self._power = value

    @property
    def steering_power(self):
        """Message field 'steering_power'."""
        return self._steering_power

    @steering_power.setter
    def steering_power(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'steering_power' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'steering_power' field must be an unsigned integer in [0, 255]"
        self._steering_power = value
