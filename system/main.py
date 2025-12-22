from serialManager import ArduinoSerial

serial = ArduinoSerial(["port_1", "port_2"], {"sensor":"Sensor_ID", "control":"Control_ID"})

def run():
    serial.startRelay("sensor", "control")