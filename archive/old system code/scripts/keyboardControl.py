from serialManager import ArduinoSerial
from keyboardReader import KeysDown, KeyToCommand
from arduinoInterface import CommandArduino
import time


class keyboardControl:
    def __init__(self):
        #serial = ArduinoSerial(["/dev/ttyUSB0", "/dev/ttyUSB1"], {"sensor":"Sensor_ID", "control":"Control_ID"})

        # no sensor input for keboard control test
        # only one possible port so set manually
        self.serial = ArduinoSerial()
        self.serial.set_port("control", None, "/dev/cu.usbserial-1420", 115200)

        self.input_reader = KeysDown()

        self.command_map = {126:"reverse", 
                    125:"reverse", 
                    18:"speed", 
                    19:"speed",
                    20:"speed",
                    21:"speed",
                    23:"speed",
                    22:"speed",
                    26:"speed",
                    28:"speed",
                    25:"speed",
                    29:"speed",
                    50:"speed",
                    49:"brake",
                    123:"s_reverse",
                    124:"s_reverse",
                    48:"s_speed",
                    56:"shift_up"
                    }

        self.command_value_map = {126:0,
                            125:1,     # Move using up/down arrow keys
                            18:10,     # Set speed using number keys
                            19:20,
                            20:30,
                            21:40,
                            23:50,
                            22:60,
                            26:70,
                            28:80,
                            25:90,
                            29:100,
                            50:0,
                            49:1,       # Break using space bar
                            123:1,     # Use left/right arrow keys for steering direction
                            124:0,
                            48:50,     # Always use 50% for s_speed
                            56:1       # shift up when shift key is pressed
                            }

        # keys that toggle on/off instead of holding down
        self.sticky_keys = ["speed", "reverse"]
        # sticky_keys = [18, 19, 20, 21, 23, 22, 26, 28, 25, 29]
                            

        self.command_interface = CommandArduino()

        self.command_setter = KeyToCommand(self.command_map, self.command_value_map, self.sticky_keys, self.command_interface)

        self.loop_delay = 100

    def run(self):
        while True: 
            start = input("Press Enter to start reading keyboard input, or type 'x' to quit: ")
            if start.lower() == 'x':
                print("Exiting program.")
                break

            self.serial.open("control")
            time.sleep(2)
            self.input_reader.start()
            while True: 
                time.sleep(self.loop_delay / 1000)
                if self.input_reader.running == False:
                    break

                pressed = self.input_reader.pressed_keys

                if len(pressed) > 0:
                    print("Keys currently pressed (scan codes): ", pressed)
                else: 
                    print("No keys currently pressed.")

                self.command_setter.update(pressed)

                command_string = self.command_interface.command_string()

                print(command_string)   # testing output

                # *** uncomment when device is actually connected
                self.serial.send("control", command_string)