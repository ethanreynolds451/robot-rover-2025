# This script lists all the serial ports available on the system along with their details such as device name, description, VID, PID, manufacturer, and product information. It uses the `serial.tools.list_ports` module from the `pyserial` library to retrieve this information.

import serial.tools.list_ports

ports = serial.tools.list_ports.comports()

for port in ports:
    print("Device:", port.device)
    print("Description:", port.description)
    print("VID:", port.vid)
    print("PID:", port.pid)
    print("Manufacturer:", port.manufacturer)
    print("Product:", port.product)
    print("-" * 40)