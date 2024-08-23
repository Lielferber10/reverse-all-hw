import ctypes
import subprocess
from ctypes import wintypes
import sys

while(True):
    exe_path = "hw4_client.exe"

    # Start the process
    process = subprocess.Popen(exe_path, stdin=subprocess.PIPE, stdout=sys.stdout, text=True, encoding='utf-8')
    first_input = "archer\n56M9JNQ60KB7APLC\n"
    inp = input()
    inp2 = input()
    if inp == 'EXIT':
        exit()
    
    payload = first_input+inp+ "\n" + inp2 
    output, error = process.communicate(input = payload)
