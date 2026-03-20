'''
Finds the serial port for communication with a given device
Will search through /dev for devices matching certain criteria to find the correct port
Saves found port in cach for future lookups
Must be told when to reset saved port and re-search

Services: 
 Server for: 
- /vehicle/serial_manager/get_serial_port
    - Requests the serial port to use for communication with a specific device
    - Expects a string argument specifying the device (e.g. 'control_board')
    - Returns a string with the serial port (e.g. '/dev/ttyUSB0') or none if not found
    - Uses saved cache to return port if already found
- /vehicle/serial_manager/reset_serial_port
    - Resets the cached serial port information (e.g. if device was unplugged and replugged)

Parameters: 
- Paths to search for serial devices (e.g. '/dev/ttyUSB*')
- Path to file with device identifiers (default to current directory)


'''

