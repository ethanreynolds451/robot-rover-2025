import serial
import os
import time

# Class to manage communicating with arduino serial devices
class ArduinoSerial:
    # Class to create serial device objects 
    class Device:
        def __init__(self, device_name, port=None, device_id=None, baudrate=9600):
            self.device_id = device_id
            self.device_name = device_name
            self.port = port
            self.baudrate = baudrate
            self.ser = serial.Serial()

    def __init__(self, ports = None, device_info = None):
        self.ports = ports  # list of available serial ports        
        self.devices = {} # map of device names to Device objects
        self.identification_delay = 2  # seconds to wait for device response during identification

    def identify_device(self, device):
        # map device to port based on data received from device
        for port in self.ports:
            try:
                ser = serial.Serial(port, device.baudrate, timeout=1)
                ser.open()
                time.sleep(self.identification_delay)
                response = ser.readline().decode().strip()
                if response == device.device_id:
                    device.port = port
                    ser.close()
                    return device, port
            except:
                # If anything goes wrong assuming device not on port, may add better error checking later
                # This will also throw an error if the port is already open
                # May cause unexpected behaviour, need to test
                pass
        return None    
    
    def identify_all_devices(self):
        # loop through devices and identify each one
        successful_devices = {}
        for device in self.devices.values():
            successful_devices.append(self.identify_device(device))
        return successful_devices  

    def set_port(self, name,  port, ID=None, baudrate=9600):
        # directly set a device if port is known
        if name not in self.devices:
            self.devices[name] = self.Device(name, ID, port, baudrate)
        else:
            self.devices[name].port = port
        
    def get_available_ports(self): 
        # Code to scan and set self.ports to match available serial ports on device
        ports = []
        for entry in os.listdir('/dev'):
            if entry.startswith('ttyUSB') or entry.startswith('ttyACM'):
                ports.append(os.path.join('/dev', entry))
        self.ports = ports

    def open(self, device):
        # Open port on specified device
        if device.port is not None:
            try:
                device.ser = serial.Serial(device.port, device.baudrate, timeout=1)
                return True
            except serial.SerialException as e:
                print(f"Error opening port {device.port} for device {device.device_name}: {e}")
                return False
        pass

    def open_all(self):
        # Attempt to open ports on all listed devices, returns list of successfully opened devices
        successful_devices = []
        for device in self.devices:
            if self.open(device):
                successful_devices.append(device.key)
        return successful_devices

    def close(self, device):
        # Close port on specified device if open
        if device.ser.isOpen():
            device.ser.close()
        
    def close_all(self):
        # Close ports on all open devices
        for device in self.devices:
            self.close(device)

    def send(self, device_name, data): 
        if device_name in self.devices:
            device = self.devices[device_name]
            try:
                with serial.Serial(device.port, device.baudrate , timeout=1) as ser:
                    ser.write(data.encode())
                    return True
            except serial.SerialException as e:
                print(f"Error sending data to {output} on port {port}: {e}")
                return False
        else:
            print(f"Device {output} not found.")
            return False

    def read(self, device_name, size=64):
        if device_name in self.devices:
            device = self.devices[device_name]
            try:
                with serial.Serial(device.port, device.baudrate , timeout=1) as ser:
                    data = ser.read(size)
                    return data.decode()
            except serial.SerialException as e:
                print(f"Error reading data from {device_name} on port {device.port}: {e}")
                return None
        else:
            print(f"Device {device_name} not found.")
        return None


    # Code to forward data from one port to annother
    # Not needed now, but may be useful in future

    def startRelay(self, input_port, output_port):
        pass

    def stopRelay(self):
        pass


'''
pass into setup
[port_1, port_2]
{deviceID_1:deviceName_1, deviceID_2:deviceName_2}

call functions on device name
'''
    