import keyboard

class KeysDown:

    def __init__(self):
        self.pressed_keys = set()
        self.running = False

    def track_keys_down(self, event):
        if event.event_type == keyboard.KEY_DOWN:
            if event.scan_code not in self.pressed_keys:
                self.pressed_keys.add(event.scan_code)

        elif event.event_type == keyboard.KEY_UP:
            if event.scan_code in self.pressed_keys:
                self.pressed_keys.discard(event.scan_code)

    def stop(self):
        keyboard.unhook_all()
        self.pressed_keys.clear()
        self.running = False

    def start(self):
        keyboard.hook(self.track_keys_down)
        keyboard.add_hotkey('esc', self.stop)
        self.running = True

class KeyToCommand:

    def __init__(self, key_command_map, key_value_map, sticky_keys, interface):
        self.output = interface.current_values
        self.defaults = interface.default_values
        self.key_command_map = key_command_map
        self.key_value_map = key_value_map
        self.sticky_keys = sticky_keys
    
    # code for simple testing of vehicle functionality
    def update(self, pressed_keys):
        for scan_code in pressed_keys:
            if scan_code in self.key_command_map:
                command = self.key_command_map[scan_code]
                value = self.key_value_map.get(scan_code)
                self.output[command] = value
        else:
            for command in self.output:
                if command not in [self.key_command_map[code] for code in pressed_keys if code in self.key_command_map]:
                    # Si el comando está en sticky_keys, no lo restablecemos
                    if command not in self.sticky_keys:
                        self.output[command] = self.defaults[command]

    # future code to better handle key function mapping
    def execute_keys(self, pressed_keys):
        for scan_code in pressed_keys:
            pass    
            
                
