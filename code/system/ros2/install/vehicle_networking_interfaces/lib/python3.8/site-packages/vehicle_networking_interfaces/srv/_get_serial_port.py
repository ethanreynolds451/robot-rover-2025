# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vehicle_networking_interfaces:srv/GetSerialPort.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GetSerialPort_Request(type):
    """Metaclass of message 'GetSerialPort_Request'."""

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
            module = import_type_support('vehicle_networking_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'vehicle_networking_interfaces.srv.GetSerialPort_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_serial_port__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_serial_port__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_serial_port__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_serial_port__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_serial_port__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetSerialPort_Request(metaclass=Metaclass_GetSerialPort_Request):
    """Message class 'GetSerialPort_Request'."""

    __slots__ = [
        '_device',
    ]

    _fields_and_field_types = {
        'device': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.device = kwargs.get('device', str())

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
        if self.device != other.device:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def device(self):
        """Message field 'device'."""
        return self._device

    @device.setter
    def device(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'device' field must be of type 'str'"
        self._device = value


# Import statements for member types

# already imported above
# import rosidl_parser.definition


class Metaclass_GetSerialPort_Response(type):
    """Metaclass of message 'GetSerialPort_Response'."""

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
            module = import_type_support('vehicle_networking_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'vehicle_networking_interfaces.srv.GetSerialPort_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_serial_port__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_serial_port__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_serial_port__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_serial_port__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_serial_port__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetSerialPort_Response(metaclass=Metaclass_GetSerialPort_Response):
    """Message class 'GetSerialPort_Response'."""

    __slots__ = [
        '_port',
    ]

    _fields_and_field_types = {
        'port': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.port = kwargs.get('port', str())

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
        if self.port != other.port:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def port(self):
        """Message field 'port'."""
        return self._port

    @port.setter
    def port(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'port' field must be of type 'str'"
        self._port = value


class Metaclass_GetSerialPort(type):
    """Metaclass of service 'GetSerialPort'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('vehicle_networking_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'vehicle_networking_interfaces.srv.GetSerialPort')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__get_serial_port

            from vehicle_networking_interfaces.srv import _get_serial_port
            if _get_serial_port.Metaclass_GetSerialPort_Request._TYPE_SUPPORT is None:
                _get_serial_port.Metaclass_GetSerialPort_Request.__import_type_support__()
            if _get_serial_port.Metaclass_GetSerialPort_Response._TYPE_SUPPORT is None:
                _get_serial_port.Metaclass_GetSerialPort_Response.__import_type_support__()


class GetSerialPort(metaclass=Metaclass_GetSerialPort):
    from vehicle_networking_interfaces.srv._get_serial_port import GetSerialPort_Request as Request
    from vehicle_networking_interfaces.srv._get_serial_port import GetSerialPort_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
