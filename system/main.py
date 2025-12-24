from serialManager import ArduinoSerial
from keyboardReader import KeysDown, KeyToCommand
import time

#serial = ArduinoSerial(["/dev/ttyUSB0", "/dev/ttyUSB1"], {"sensor":"Sensor_ID", "control":"Control_ID"})

# no sensor input for keboard control test
# only one possible port so set manually
serial = ArduinoSerial()
serial.set_port("control", "/dev/ttyUSB0")

input_reader = KeysDown()

command_map = {126:"forward", 
               125:"backward", 
               49:"power"}

commands = KeyToCommand(command_map)

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

            commands.update(pressed)
            for command in commands.active_commands:
                #serial.send("control", command)