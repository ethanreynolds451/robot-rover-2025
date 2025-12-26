import serial

class ArduinoSerial:
    def __init__(self, ports = None, device_info = None):
        self.baud_rate = 115200 # hardcoding for now, will make configurable by device later        
        self.ports = ports
        self.device_info = device_info
        self.devices = {}

    def identify(self):
        for port in self.ports:
            pass
        # map device names to ports based on data received from device
    
    def set_port(self, device_name, port):
        self.devices[device_name] = port
        # directly set port for a device name

    def send(self, output, data): 
        if output in self.devices:
            port = self.devices[output]
            try:
                with serial.Serial(port, self.baud_rate, timeout=1) as ser:
                    ser.write(data.encode())
            except serial.SerialException as e:
                print(f"Error sending data to {output} on port {port}: {e}")
        else:
            print(f"Device {output} not found.")

    def read(self, input):
        return None

    
    def startRelay(self, input, output):
        pass
    def stopRelay(self):
        pass


'''
pass into setup
[port_1, port_2]
{deviceID_1:deviceName_1, deviceID_2:deviceName_2}

call functions on device name
'''
    