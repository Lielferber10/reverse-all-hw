import ctypes
import subprocess
from ctypes import wintypes
from time import sleep

command = ['python', 'attack_shell.py']

# Start the process
process = subprocess.Popen(command, stdin=subprocess.PIPE)

new_attack_config = b"Set-Content -Path config\\attack.config -Value 'Fires: False\\nRivals: False\\nKnights Infected: False\\nRobber Hunted: False'"

process.stdin.write(new_attack_config + b"\n")
process.stdin.flush()

sleep(10)


process.stdin.write(b"exit" + b"\n")
process.stdin.flush()