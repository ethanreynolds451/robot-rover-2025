# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vehicle_interfaces:msg/QMCData.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_QMCData(type):
    """Metaclass of message 'QMCData'."""

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
                'vehicle_interfaces.msg.QMCData')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__qmc_data
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__qmc_data
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__qmc_data
            cls._TYPE_SUPPORT = module.type_support_msg__msg__qmc_data
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__qmc_data

            from sensor_msgs.msg import MagneticField
            if MagneticField.__class__._TYPE_SUPPORT is None:
                MagneticField.__class__.__import_type_support__()

            from sensor_msgs.msg import Temperature
            if Temperature.__class__._TYPE_SUPPORT is None:
                Temperature.__class__.__import_type_support__()

            from std_msgs.msg import Bool
            if Bool.__class__._TYPE_SUPPORT is None:
                Bool.__class__.__import_type_support__()

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


class QMCData(metaclass=Metaclass_QMCData):
    """Message class 'QMCData'."""

    __slots__ = [
        '_header',
        '_is_valid',
        '_id',
        '_mag',
        '_heading',
        '_temp',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'is_valid': 'std_msgs/Bool',
        'id': 'string',
        'mag': 'sensor_msgs/MagneticField',
        'heading': 'float',
        'temp': 'sensor_msgs/Temperature',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Bool'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['sensor_msgs', 'msg'], 'MagneticField'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['sensor_msgs', 'msg'], 'Temperature'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        from std_msgs.msg import Bool
        self.is_valid = kwargs.get('is_valid', Bool())
        self.id = kwargs.get('id', str())
        from sensor_msgs.msg import MagneticField
        self.mag = kwargs.get('mag', MagneticField())
        self.heading = kwargs.get('heading', float())
        from sensor_msgs.msg import Temperature
        self.temp = kwargs.get('temp', Temperature())

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
        if self.is_valid != other.is_valid:
            return False
        if self.id != other.id:
            return False
        if self.mag != other.mag:
            return False
        if self.heading != other.heading:
            return False
        if self.temp != other.temp:
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
    def is_valid(self):
        """Message field 'is_valid'."""
        return self._is_valid

    @is_valid.setter
    def is_valid(self, value):
        if __debug__:
            from std_msgs.msg import Bool
            assert \
                isinstance(value, Bool), \
                "The 'is_valid' field must be a sub message of type 'Bool'"
        self._is_valid = value

    @property  # noqa: A003
    def id(self):  # noqa: A003
        """Message field 'id'."""
        return self._id

    @id.setter  # noqa: A003
    def id(self, value):  # noqa: A003
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'id' field must be of type 'str'"
        self._id = value

    @property
    def mag(self):
        """Message field 'mag'."""
        return self._mag

    @mag.setter
    def mag(self, value):
        if __debug__:
            from sensor_msgs.msg import MagneticField
            assert \
                isinstance(value, MagneticField), \
                "The 'mag' field must be a sub message of type 'MagneticField'"
        self._mag = value

    @property
    def heading(self):
        """Message field 'heading'."""
        return self._heading

    @heading.setter
    def heading(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'heading' field must be of type 'float'"
        self._heading = value

    @property
    def temp(self):
        """Message field 'temp'."""
        return self._temp

    @temp.setter
    def temp(self, value):
        if __debug__:
            from sensor_msgs.msg import Temperature
            assert \
                isinstance(value, Temperature), \
                "The 'temp' field must be a sub message of type 'Temperature'"
        self._temp = value
