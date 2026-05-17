'''
This node parses string messages from the sensor board into SensorData messages for use by the rest of the system

Topics
 Subscribes to:
- /vehicle/sensor_data_str
    - String
 Publishes to:
- /vehicle/sensor_data
    - SensorData custom msg type

Parameters: 
- verbose (bool, default: false)
    - Whether to log all parsed data in the console
    - Useful for debugging but a lot of clutter / overhead for normal operation
'''

# Packages for ROS2
import rclpy
from rclpy.node import Node

# ROS2 message definitions
from vehicle_interfaces.msg import SensorData
from std_msgs.msg import String
from std_msgs.msg import Header
import importlib          # Used to dynamically resolve message classes for nested parsing

# Vehicle codes from config files
import os
from ament_index_python.packages import get_package_share_directory
import yaml


class VehicleSensorStringParser(Node):
    def __init__(self):
        super().__init__('vehicle_sensor_string_parser')
        self.get_logger().info('Starting Vehicle Sensor String Parser Node')

        # Expected execution parameters
        self.declare_parameter('verbose', False)  # Whether to log all parsed data in the console

        # Load codes, delimiters, internalh fields, and special encoding parameters once at startup
        package_share = get_package_share_directory('vehicle_string_converter')
        sensor_config_path = os.path.join(package_share, 'config', 'sensor_codes.yaml')
        delimiter_config_path = os.path.join(package_share, 'config', 'delimiters.yaml')
        encoding_config_path = os.path.join(package_share, 'config', 'sensor_encoding.yaml')
        field_config_path = os.path.join(package_share, 'config', 'sensor_fields.yaml')
        name_config_path = os.path.join(package_share, 'config', 'sensor_names.yaml')

        try:
            with open(sensor_config_path, 'r') as f:
                self.sensor_codes = yaml.safe_load(f)
            with open(delimiter_config_path, 'r') as f:
                self.delimiters = yaml.safe_load(f)
            with open(encoding_config_path, 'r') as f:
                self.encodings = yaml.safe_load(f)
            with open(field_config_path, 'r') as f:
                self.sensor_fields = yaml.safe_load(f)
            with open(name_config_path, 'r') as f:
                self.sensor_names = yaml.safe_load(f)

        except Exception as e:
            # The control system can't run without the codes, but sensors can still run
            self.get_logger().error(
                f"Error loading sensor files; system will be unable to interface with sensor board: {e}"
            )
            raise  # Re-raise so main() knows initialization failed

        self.get_logger().info("Successfully loaded sensor codes")

        # Cache for schema expansion (prevents repeated recursion work)
        self._schema_cache = {}

        # Recursively generate data type and encoding mappings for quick access during parsing
        self.fields_and_types = self.expand_schema(SensorData)

        # Store the higher level data field names for access during parsing
        self.sensor_data_fields = [f for f in self.fields_and_types.keys() if f != '__type__']

        # Build encoding mapping that matches the data types structure
        self.fields_and_encodings = self.build_encodings(
            self.fields_and_types,
            self.encodings
        )

        # Track which fields are arrays for proper assignment during parsing
        self.array_fields = self.get_array_fields(self.fields_and_types)

        # Subscriber to vehicle sensor string messages
        self.sensor_subscriber = self.create_subscription(
            String,
            '/vehicle/sensor_data_str',
            self.sensor_callback,
            10
        )

        # Publisher for sensor data formatted messages
        self.sensor_string_publisher = self.create_publisher(
            SensorData,
            '/vehicle/sensor_data',
            10
        )

        # Debug
        # self.get_logger().info(f"ir_remote schema: {self.fields_and_types.get('ir_remote')}")

    def resolve_msg_class(self, type_str):
        # Handle ROS2 sequence notation for variable-length arrays e.g. "sequence<pkg/Type>"
        if type_str.startswith("sequence<"):
            type_str = type_str[len("sequence<"):-1]  # Strip "sequence<" and ">"

        # Handle fixed-size array notation e.g. "pkg/Type[4]" or "pkg/Type[]"
        type_str = type_str.split("[")[0]

        # Handle both ROS2 Humble+ format (pkg/msg/Type) and older format (pkg/Type)
        parts = type_str.split("/")
        if len(parts) == 3:
            pkg, _, msg = parts  # Discard the middle "msg" component
        elif len(parts) == 2:
            pkg, msg = parts
        else:
            raise ValueError(f"Unexpected type string format: '{type_str}'")

        module = importlib.import_module(f"{pkg}.msg")

        return getattr(module, msg)

    def expand_schema(self, msg_class):
        msg_name = msg_class.__name__

        if msg_name in self._schema_cache:
            return self._schema_cache[msg_name]

        schema = {}

        for field, ros_type in msg_class._fields_and_field_types.items():
            if ros_type.startswith("sequence<"):
                base_type = ros_type[len("sequence<"):-1]
            else:
                base_type = ros_type.split("[")[0]

            if "/" in base_type:
                try:
                    sub_class = self.resolve_msg_class(base_type)
                    expanded = self.expand_schema(sub_class).copy()  # copy to avoid mutating the cache
                    expanded['__type__'] = base_type
                    schema[field] = expanded

                except Exception as e:
                    self.get_logger().warn(f"Failed to resolve nested type '{base_type}': {e}")
                    schema[field] = ros_type
            else:
                schema[field] = ros_type

        self._schema_cache[msg_name] = schema
        return schema

    def build_encodings(self, type_tree, override_tree):
        enc = {}

        for field, value in type_tree.items():
            if field == '__type__':
                continue

            if isinstance(value, dict):
                # Guard against encoding config having a string where a dict is expected
                sub_override = override_tree.get(field, {})
                if not isinstance(sub_override, dict):
                    sub_override = {}
                enc[field] = self.build_encodings(value, sub_override)
            else:
                enc[field] = override_tree.get(field, "int")

        return enc
    

    def get_array_fields(self, type_tree):
        array_fields = set()

        for field, ros_type in type_tree.items():
            if field == '__type__':
                continue
            # Handle both C-style "[]" notation and ROS2 "sequence<>" notation
            if isinstance(ros_type, str) and (ros_type.endswith("[]") or ros_type.startswith("sequence<")):
                array_fields.add(field)

        return array_fields


    def sensor_callback(self, msg):
        # Convert the string message to a SensorData message
        sensor_data = self.convert(msg)
        # Publish the SensorData message
        if sensor_data:  # Only publish if conversion was successful
            self.sensor_string_publisher.publish(sensor_data)
            if self.get_parameter('verbose').get_parameter_value().bool_value:
                self.get_logger().info(f"Published sensor data update: {sensor_data}")
        else:
            self.get_logger().error("Failed to convert sensor data message to SensorData format")


    def convert(self, msg):
        # Declare output type SensorData
        sensor_data = SensorData()
        # Get the string from the incoming message
        sensor_string = msg.data

        packet_timestamp = None  # Initialize packet timestamp variable

        # First, check for valid packet delimiters
        start_delimiter = self.delimiters.get('packet_start', '')
        end_delimiter = self.delimiters.get('packet_end', '')
        # Makes sure delimiters aren't empty to avoid edge case
        if start_delimiter and end_delimiter:
            if not sensor_string.startswith(start_delimiter) or not sensor_string.endswith(end_delimiter):
                self.get_logger().error(f"Invalid sensor data message received: missing start/end delimiter")
                return None
        else:
            self.get_logger().error("Packet delimiters not defined in config files; unable to validate incoming messages")
            return None

        # Verify the data start and end delimiter
        data_start_delimiter = self.delimiters.get('field_start', '')
        data_end_delimiter = self.delimiters.get('field_end', '')
        if not data_start_delimiter or not data_end_delimiter:
            self.get_logger().error("Data delimiters not defined in config files; unable to validate incoming messages")
            return None

        # After checking the packet delimiters, strip them
        # (there existence has already been validated so they can safely be removed without additional checks)
        sensor_string = sensor_string[len(start_delimiter):len(sensor_string) - len(end_delimiter)]

        # Now split the string into components based on data delimiters
        data_strings = {}
        while sensor_string:
            # The code runs up to but not including the next data start delimiter
            split_index_start = sensor_string.find(data_start_delimiter)
            if split_index_start == -1:
                break  # No more data start delimiters, exit the loop
            split_index_end = split_index_start + len(data_start_delimiter)
            end_index = sensor_string.find(data_end_delimiter, split_index_end)
            if end_index == -1:
                self.get_logger().error(f"Invalid sensor data message format: the last data in the packet was missing its end delimiter")
                break  # No more data end delimiters, exit the loop
            
            # Get the next code and data substrings and store them in the command_strings dict
            next_code = sensor_string[:split_index_start]  # Get the substring before the next data start delimiter
            next_code = next_code.strip()  # Remove any leading/trailing whitespace from the code  
            next_data = sensor_string[split_index_end:end_index]  # Get the substring after the next data start delimiter

            # Only store if a code is present
            if not next_code:
                self.get_logger().warn("Empty sensor code encountered, skipping")
            else:
                data_strings[next_code] = next_data  # Store the code and its corresponding data substring
            
            # Strip the processed part of the string for the next iteration
            sensor_string = sensor_string[end_index + len(data_end_delimiter):]
            

        # Make sure there was valid data found in the command string
        if not data_strings:
            self.get_logger().error(f"Invalid sensor data message format: no valid data strings found")
            return None
        
        # Convert each piece of data into appropriate datatype and assign it to the corresponding field in the SensorData message
        # This needs to happen recursively to handle nested message types
        data_parsed = False  # Flag to track if at least one piece of data was successfully parsed
        for next_code, next_data in data_strings.items():
            # Get the corresponding field name from the config file
            sensor_name = self.sensor_codes.get(next_code)
            # Make sure it is a valid sensor code form config file
            if not sensor_name:
                self.get_logger().warn(f"Unrecognized sensor code '{next_code}' in sensor data message; skipping this field")
                continue
            # Convert the value to the appropriate datatype based on the field type and assign it to the corresponding field in the ControlFeedback message
            try: 
                # Convert and assign to the corresponding SensorData field
                value_obj = self.construct_sensor_data_field(sensor_name, next_data, packet_timestamp) 
                # Get the field for this sensor from the SensorData message
                sensor_data_field = getattr(sensor_data, sensor_name)
                if sensor_name in self.array_fields:
                    # Appnd the individual sensor reading to its correspoding array of sensors of the same type
                    sensor_data_field.append(value_obj)
                else:
                    # Directly set the field to the value object if not array type
                    sensor_data_field = value_obj
                    # Special case to store arduino timestamp for use in calculating from offsets
                    if sensor_name == "arduino_timestamp":
                        packet_timestamp = value_obj  # Store the packet timestamp for use in parsing other fields that require it 
                        # The packet timestamp MUST come before any fields with timestamp offsets  
                data_parsed = True  # Set the flag to True if at least one piece of data was successfully parsed
            except ValueError as e:
                self.get_logger().error(f"Error parsing sensor data message for {sensor_name}: {e}")
                continue  # Skip this field but continue parsing others
            except Exception as e:
                self.get_logger().error(f"Error converting value for {sensor_name}: {e}")
                continue  # Skip this field but continue parsing others
        
        if not data_parsed:
            self.get_logger().warn("No valid data found in sensor data message")
            return None  # Return None if no valid data was parsed, otherwise return the ControlFeedback message
        
        return sensor_data


    def construct_sensor_data_field(self, sensor_name, data_str, packet_timestamp=None):
        # This handles the extraction of data and appropriate type conversion for a sensor data field
        # Input: string with the data and name of sensor to assign it to
        # Output: the appropriate data type object containing the data
        
        # First, check if the field is a nested message type that requires recursive parsing
        if isinstance(self.fields_and_types.get(sensor_name), dict):
            # If it is a nested message, recursively parse the data

            # Load and verify the intenal delimiters
            key_delimiter = self.delimiters.get('key_delimiter', '')
            value_delimiter = self.delimiters.get('value_delimiter', '')
            list_delimiter = self.delimiters.get('list_delimiter', '')
            if not key_delimiter or not value_delimiter or not list_delimiter:
                self.get_logger().error("Internal delimiters not defined in config files; unable to parse sensor data with nested fields")
                return None

            data_strings = {}
            # Parse the internal fields into a dict
            last_field = False  # Flag to track if we are parsing the last field, which may not have a trailing key delimiter
            while data_str and not last_field:
                # The code runs up to but not including the next data start delimiter
                split_index_start = data_str.find(value_delimiter)
                if split_index_start == -1:
                    break  # No more data start delimiters, exit the loop
                split_index_end = split_index_start + len(value_delimiter)
                end_index = data_str.find(key_delimiter, split_index_end)
                # There might not be a comma after the last field, so if there isn't just take the rest of the string
                if end_index == -1:
                    end_index = len(data_str)  # Set end index to the end of the string minus the length of the delimiter to avoid edge case where delimiter is missing at the end of the string
                    last_field = True

                # Get the next code and data substrings and store them in the command_strings dict
                next_code = data_str[:split_index_start]  # Get the substring before the next data start delimiter
                next_code = next_code.strip()  # Remove any leading/trailing whitespace from the code  
                next_data = data_str[split_index_end:end_index]  # Get the substring after the next data start delimiter

                # Only store if a code is present
                if not next_code:
                    self.get_logger().warn("Empty sensor code encountered, skipping")
                else:
                    # Now lok for internal list delimitors and convert to ap python list if found
                    if list_delimiter in next_data:
                        next_data_list = next_data.split(list_delimiter)
                        next_data_list = [item.strip() for item in next_data_list]  # Remove whitespace from each item
                        data_strings[next_code] = next_data_list  # Store the code and its corresponding data list
                    else: 
                        # Always make it a list even if only one item to simplify downstream processing
                        next_data_list = [next_data.strip()]  # Remove whitespace and make it a list
                        data_strings[next_code] = next_data_list  # Store the code and its corresponding data substring
                
                # Strip the processed part of the string for the next iteration

                data_str = data_str[end_index + len(key_delimiter):]

                
            # Once the data has been parsed, construct the nested message object
            return self.construct_sensor_object(sensor_name, data_strings, packet_timestamp)
        else:
            # If it is not a nested message, just convert the string to the appropriate ROS type and return it
            return self.string_to_ros_type(sensor_name, data_str)

    def construct_sensor_object(self, sensor_name, data, packet_timestamp=None):
        # Handles recursive parsing of nested message types for sensor data fields

        # First, create an instance of the nested message type

        # Primative data types should be automatically hatndled outside this function but check just in case       
        if not isinstance(self.fields_and_types.get(sensor_name), dict):
            # Return None if this function is called on a primitive type
            self.get_logger().error(f"Invalid schema for sensor '{sensor_name}': expected a nested message type but got a primitive type")
            return None
        
        # Retrieve the message type from the sensor schema mapping
        type_str = self.fields_and_types[sensor_name].get('__type__')
        
        # Make sure the type string is defined
        if not type_str:
            self.get_logger().error(f"No type string found for sensor '{sensor_name}'")
            return None
        
        # Create an instance of the messaae type
        type = self.resolve_msg_class(type_str)
        sensor_data = type()

        # Track the sensor index if applicable for frame ID assignment in the header
        # Will default to the mapping for 0 if not provided
        # Might want to handle non-indexed sensors seperately for rigerous protection against assigning the wrong sensor values
        sensor_index = None

        # Then parse the data from the nested message and assign it to appropriate fields

        for field_name, field_value in data.items():
            # Field name: the internal key, should match the ones defined in sensor_fields.yaml
            # Field value: the data asociated with that key - will always be a list of strings even if there is only one

            # Make sure the field is defined in the config file and is in the message schema
            if field_name not in self.sensor_fields[sensor_name]: 
                self.get_logger().warn(f"Unrecognized field '{field_name}' for sensor '{sensor_name}'; skipping this field")
                continue
            
            # Get the corresponding ROS field name from the config file
            ros_field_name = self.sensor_fields[sensor_name][field_name]  

            # Check for special cases beforec entering normal parsing flow
            if ros_field_name == "frame_id":
                # Special case to handle frame ID assignment
                sensor_index = field_value[0]  # Store the frame ID for use in header construction laters
                continue  # Don't try to assign this field to the message since it is only used for header construction later
            elif ros_field_name == '__type__':
                continue  # Skip internal type annotation
            elif ros_field_name not in self.fields_and_types.get(sensor_name, {}):
                self.get_logger().warn(f"Field '{ros_field_name}' for sensor '{sensor_name}' not found in message schema; skipping this field")
                continue

            try:
                # Attempt to convert the value to its corresponding ROS type
                value = self.string_to_ros_type(sensor_name, field_value, ros_field_name, packet_timestamp)
                setattr(sensor_data, ros_field_name, value)
            except ValueError as e:
                self.get_logger().error(f"Error parsing sensor data message for {sensor_name}.{ros_field_name}: {e}")
                continue  # Skip this field but continue parsing others
            except Exception as e:
                self.get_logger().error(f"Error converting value for {sensor_name}.{ros_field_name}: {e}")
                continue  # Skip this field but continue parsing others


        # Note: this assumes that every custom sensor message has a header field and is_valid flag

        # Now construct the header for the message
        setattr(sensor_data, 'header', self.construct_data_header(sensor_name, sensor_index))
        # Finally mark the sensor as valid since new data was recieved for it
        # Make sure it is a ros bool type
        bool_obj = self.resolve_msg_class('std_msgs/msg/Bool')()  # Create an instance of the Bool message
        bool_obj.data = True  # Set the data field to True
        setattr(sensor_data, 'is_valid', bool_obj)
        # Return the full sensor data object for this field
        return sensor_data


    # This function must be updated to handle each datatype possible in a message
    def string_to_ros_type(self, sensor_name, value, sensor_field = None, packet_timestamp = None):

        # Convert the value to a list if not already
        if not isinstance(value, list):
            value = [value]

        # Get the target ros type for this field from the schema mapping
        if sensor_field:
            ros_type = self.fields_and_types.get(sensor_name, {}).get(sensor_field)
        else:
            ros_type = self.fields_and_types.get(sensor_name)
        if not ros_type:
            self.get_logger().warn(f"No ROS type found for {sensor_name} (subfield: {sensor_field}), defaulting to string")
            ros_type = "string"  # Defaulting to string if no type found in schema
        
        # Get the encoding used for this field
        # Should have defaulted to specfied ros type if no oiverride avaiable in file
        if sensor_field:
            # If the sub field is specified
            encoding = self.fields_and_encodings.get(sensor_name, {}).get(sensor_field)
        else:    
            # If there is no sub field specified, just get the encoding for the main field
            encoding = self.fields_and_encodings.get(sensor_name)
        if not encoding:
            self.get_logger().warn(f"No encoding specified for {sensor_name} (subfield: {sensor_field}), defaulting to string")
            encoding = "string"  # Defaulting to string 

        # Convert the value string to the apropriate ROS type

        # First, handle conversion of any speial encodings
        if encoding != ros_type: 
            value = self.convert_encoding(value, encoding, ros_type, packet_timestamp)

        # Now cast the value to the appropriate ROS type 
        # Must be updated to handle all types used by custom sensor messages
        try:
            if ros_type.startswith('bool'):
                return value[0].lower() in ['1', 'true']
            elif ros_type.startswith('int') or ros_type.startswith('uint'):
                return int(value[0])
            elif ros_type.startswith('float'):
                return float(value[0])
            elif ros_type == 'string':
                return value[0]
            elif "/" in ros_type:
                # Handle custom message types
                obj = self.resolve_msg_class(ros_type)()  # Create an instance of the custom message
                if ros_type == 'sensor_msgs/NavSatFix':
                    # Handle NavSatFix type conversion
                    obj.latitude = float(value[0])  # Assuming the latitude is the first value in the list
                    obj.longitude = float(value[1])  # Assuming the longitude is the second value in
                    obj.altitude = float(value[2])  # Assuming the altitude is the third value in the list
                elif ros_type == 'sensor_msgs/Imu':
                    # Handle Imu type conversion
                    obj.linear_acceleration.x = float(value[0])  # Assuming the linear acceleration x is the first value in the list
                    obj.linear_acceleration.y = float(value[1])  # Assuming the linear acceleration y is
                    obj.linear_acceleration.z = float(value[2])  # Assuming the linear acceleration z is the third value in the list
                    obj.angular_velocity.x = float(value[3])  # Assuming the angular velocity x is the fourth value in the list
                    obj.angular_velocity.y = float(value[4])  # Assuming the angular velocity y is the fifth value in the list
                    obj.angular_velocity.z = float(value[5])  # Assuming the angular velocity z is the sixth value in the list
                elif ros_type == 'sensor_msgs/Temperature':
                    # Handle Temperature type conversion
                    obj.temperature = float(value[0])  # Assuming the temperature is the only value in the list
                elif ros_type == 'sensor_msgs/MagneticField':
                    # Handle MagneticField type conversion
                    obj.magnetic_field.x = float(value[0])  # Assuming the magnetic field x is the first value in the list
                    obj.magnetic_field.y = float(value[1])  # Assuming the magnetic field y
                    obj.magnetic_field.z = float(value[2])  # Assuming the magnetic field z is the third value in the list
                elif ros_type == 'sensor_msgs/Range':
                    obj.range = float(value[0])  # Assuming the range is the only value in the list
                    # Handle Range type conversion
                    pass
                else:
                    self.get_logger().warn(f"Unknown type '{ros_type}', treating as string")
                    return value[0]
                return obj
            else:
                self.get_logger().warn(f"Unknown type '{ros_type}', treating as string")
                return value[0]
            
        except Exception as e:
            self.get_logger().error(f"Failed to convert '{value}' to {ros_type}: {e}")
            return None
        
    def convert_encoding(self, values, encoding, ros_type, packet_timestamp=None):
        # This function handles the conversion of special encodings to their decoded string values based on the specified encoding type and target ROS type
        new_values = []
        # Increment through the list 
        for value in values:
            try:
                # Convert all hex encodings to base 10 numbers
                if encoding.startswith("hex"):
                    raw_value = int(value, 16)
                    if encoding.startswith("hex_float"):
                        multiplier = int(''.join(filter(str.isdigit, encoding)))  # extracts the number from the encoding, e.g. 2 from "hex_float_2"
                        new_values.append(raw_value / (10 ** multiplier))  # Convert to float by dividing by the multiplier
                    elif encoding == "hex":
                        if ros_type.startswith('uint'):
                            new_values.append(raw_value)
                        elif ros_type.startswith('int'):
                            bits = int(''.join(filter(str.isdigit, ros_type)))  # extracts 16, 32, etc.
                            sign_bit = 1 << (bits - 1)
                            mask = (1 << bits) - 1
                            raw_value = raw_value & mask  # ensure width
                            new_values.append(raw_value - (1 << bits) if (raw_value & sign_bit) else raw_value)
                        else:
                            self.get_logger().warn(f"Hex encoding specified for non-integer ROS type '{ros_type}'; treating as string")
                            new_values.append(value)  # Keep as string if target type isn't int/uint
                    elif encoding == "hex_timestamp_offset":
                        # The sensor will always have been read before the packet was constucted
                        # If this is negative, it indicates an error
                        if packet_timestamp is not None:
                            new_values.append(packet_timestamp - raw_value)
                        else:
                            self.get_logger().warn(f"Packet timestamp not available for field with 'hex_timestamp_offset' encoding; treating value as regular hex")
                            new_values.append(raw_value)  # Keep as raw hex value if timestamp isn't available
                    else:
                        self.get_logger().warn(f"Unknown hex encoding variant '{encoding}'; treating as string")
                        new_values.append(value)  # Keep as string if unknown hex encoding

                elif encoding == "unsigned_direction":
                    # -1 is reverse, 0 is stopped, 1 is forward
                    # Converted to unsiged int for transmission by adding 1
                    new_values.append(int(value) - 1)

                else:
                    self.get_logger().warn(f"Unknown encoding '{encoding}'; treating as string")
                    new_values.append(value)  # Keep as string if unknown encoding

            except Exception as e:
                self.get_logger().error(f"Failed to convert '{value}' with encoding '{encoding}': {e}")
                new_values.append(value)  # Keep the original value if conversion fails

        return new_values


    def construct_data_header(self, sensor_name, sensor_index=None):
        # This handles the construction of the field header for a given sensor data field, including any necessary indexing for array fields
        # Create a header object
        header = Header()
        # Assign the frame ID based on the sensor name and index (if applicable)
        if sensor_index is None:
            sensor_index = 0  # Default to 0 if no index provided
        # Assign the frame ID as defined in the configuration file
        try:
            header.frame_id = self.sensor_names[sensor_name][str(sensor_index)]
        except Exception as e:
            self.get_logger().warn(f"Failed to assign frame ID for sensor '{sensor_name}' with index '{sensor_index}': {e}")
            self.get_logger().warn(f"Defaulting to generic frame ID for sensor '{sensor_name}' with index '{sensor_index}'")
            header.frame_id = f"{sensor_name}_{sensor_index}"  # Default to a generic frame ID if not defined in config
        # Assign the timestamp to the current time
        header.stamp = self.get_clock().now().to_msg()
        return header


def main(args=None):
    rclpy.init(args=args)
    try:
        node = VehicleSensorStringParser()
    except Exception as e:
        print(f"Failed to initialize node: {e}")  # print since logger may not be available
        rclpy.shutdown()
        return  
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()