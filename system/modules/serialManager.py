import serial

class ArduinoSerial:
    def __init__(self, ports, devices):
        self.ports = ports
        self.device_info = devices
        self.devices = []
    def identify(self):
        for port in self.ports:
            pass
    def startRelay(self, input, output):
        print("Hello World")
    def stopRelay(self):
        pass


'''
pass into setup
[port_1, port_2]
{deviceID_1:deviceName_1, deviceID_2:deviceName_2}

call functions on device name
'''
    