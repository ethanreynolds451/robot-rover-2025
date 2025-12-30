

class CommandArduino:
    def __init__(self, device_ID=None):
        self.ID = device_ID
        self.command_codes = {
            "brake": "br",
            "reverse": "rv",
            "s_reverse": "srv",
            "shift_up": "su",
            "speed": "sp",
            "s_speed": "ssp",
        }
        self.current_values = {
            "brake": 0,   
            "reverse": 0,
            "s_reverse": 0,
            "shift_up": 0,
            "speed": 0,
            "s_speed": 0,
        }
        self.default_values = self.current_values.copy()
    
    def command_string(self):
        command_str = "{"
        for key in self.current_values:
            code = self.command_codes[key]
            value = self.current_values[key]
            command_str += f"{code}[{value}]"
        command_str += "}"
        return command_str
            

# string format: {br[0]rv[0]srv[0]su[0]sp[0]ssp[0]} 


# No implementation yet
class Sensor:
    def __init__(self):
        pass
    
