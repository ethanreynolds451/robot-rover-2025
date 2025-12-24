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

    def __init__(self, key_command_map):
        self.key_command_map = key_command_map
        self.active_commands = set()
    
    def update(self, pressed_keys):
        for scan_code in pressed_keys:
            if scan_code in self.key_command_map:
                self.active_commands.add(self.key_command_map[scan_code])
