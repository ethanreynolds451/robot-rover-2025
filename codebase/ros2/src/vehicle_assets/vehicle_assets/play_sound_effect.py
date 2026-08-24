# Simple code to play a specified sound effect in the sounds folder

import os
from ament_index_python.packages import get_package_share_directory
import pygame

def play_sound_effect(sound_name):
    # Initialize pygame mixer
    pygame.mixer.init()

    # Get the path to the sound file
    package_share = get_package_share_directory('vehicle_assets')
    sound_file = os.path.join(package_share, 'sounds', f'{sound_name}.wav')

    # Check if the sound file exists
    if not os.path.isfile(sound_file):
        print(f"Sound file '{sound_file}' not found.")
        return

    # Load and play the sound
    try:
        sound = pygame.mixer.Sound(sound_file)
        sound.play()
        print(f"Playing sound effect: {sound_name}")
    except Exception as e:
        print(f"Error playing sound effect: {e}")