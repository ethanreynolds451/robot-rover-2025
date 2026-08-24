import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/ethanreynolds/vscode/robot-rover-2025/code/system/ros2/install/vehicle_string_converter'
