from serialManager import ArduinoSerial
from keyboardReader import KeysDown, KeyToCommand
from arduinoInterface import CommandArduino
import time

#serial = ArduinoSerial(["/dev/ttyUSB0", "/dev/ttyUSB1"], {"sensor":"Sensor_ID", "control":"Control_ID"})

# no sensor input for keboard control test
# only one possible port so set manually
serial = ArduinoSerial()
serial.set_port("control", "/dev/ttyUSB0")

input_reader = KeysDown()

command_map = {126:"reverse", 
               125:"reverse", 
               49:"speed"}

command_value_map = {126:0,
                     125:1, 
                     49:50}

command_interface = CommandArduino()

command_setter = KeyToCommand(command_map, command_value_map, command_interface)

loop_delay = 100

def run():
    while True: 
        start = input("Press Enter to start reading keyboard input, or type 'x' to quit: ")
        if start.lower() == 'x':
            print("Exiting program.")
            break
        input_reader.start()
        while True: 
            time.sleep(loop_delay / 1000)
            if input_reader.running == False:
                break

            pressed = input_reader.pressed_keys

            if len(pressed) > 0:
                print("Keys currently pressed (scan codes): ", pressed)
            else: 
                print("No keys currently pressed.")

            command_setter.update(pressed)

            command_string = command_interface.command_string()

            print(command_string)   # testing output

            # *** uncomment when device is actually connected
            # serial.send("control", command_string)