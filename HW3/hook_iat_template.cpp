#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include <stdexcept>
// Add additional includes if needed
// using namespace std;

// for logging. format: log_file << ... << std::endl;
// #include <fstream> 
// using std::ofstream;
//ofstream log_file("log.txt");

// Typedef for the hooked function signature, such as:
// typedef INT(WINAPI* FUNC_PTR)(SOCKET, char*, int, int); (WINAPI is for _stdcall)
// or in the simple case:
typedef LPVOID FUNC_PTR;

// Ptr to the original function
FUNC_PTR original_func_address;

// Global variables
DWORD lpProtect = 0;
LPVOID IAT;
FUNC_PTR JumpTo;
int required_ret = 0x401917;

// Helper function to remove the hook (for the current call):
void _stdcall remove_hook() {
	VirtualProtect((char*)IAT, 0x4, PAGE_EXECUTE_READWRITE, &lpProtect);
	memcpy(IAT, &original_func_address, 0x4);
	VirtualProtect((char*)IAT, 0x4, PAGE_EXECUTE_READ, &lpProtect);
}

// Helper function to restore the hook (for the next calls)
void _stdcall restore_hook() {
	VirtualProtect((char*)IAT, 0x4, PAGE_EXECUTE_READWRITE, &lpProtect);
	memcpy(IAT, &JumpTo, 0x4);
	VirtualProtect((char*)IAT, 0x4, PAGE_EXECUTE_READ, &lpProtect);
}


//get a buffer with encrypted message and puts inside it the decrypted message
void decrypt(char* encrypted_str)
{
    int i = 0;      // Position in the encrypted string
    int j = 0;      // Position in the decrypted string
    int length = strlen(encrypted_str);
    char decrypted_str[length];
    while(i < length)
    {
        int higher_nibble = 0;
        int lower_nibble = 0;
        if(encrypted_str[i] == 10  || encrypted_str[i] == 13)
        {
            decrypted_str[j] = encrypted_str[i];
            j++;
            i++;
            continue;
        }

        if (i + 1 < length - 1 && encrypted_str[i + 1] == 43) {
            int var_1C = encrypted_str[i++] - 48;
            i++;
            higher_nibble = encrypted_str[i++] + var_1C - 48; //not accurate
        } else if (i + 1 < length - 1 && encrypted_str[i + 1] == 45) {
            higher_nibble = 0;
            i += 3;
        } else if (encrypted_str[i] == 65) {
            higher_nibble = 1;
            i++;
        } else if (encrypted_str[i] == 74) {
            higher_nibble = 10;
            i++;
        } else if (encrypted_str[i] == 81) {
            higher_nibble = 11;
            i++;
        } else if (encrypted_str[i] == 75) {
            higher_nibble = 12;
            i++;
        } else {
            higher_nibble = encrypted_str[i] - 48;
            i++;
        }


        if (i + 1 < length - 1 && encrypted_str[i + 1] == 43) {
            int var_1C = encrypted_str[i++] - 48;
            i++;
            lower_nibble = encrypted_str[i++] + var_1C - 48; //not accurate
        } else if (i + 1 < length - 1 && encrypted_str[i + 1] == 45) {
            lower_nibble = 0;
            i += 3;
        } else if (encrypted_str[i] == 65) {
            lower_nibble = 1;
            i++;
        } else if (encrypted_str[i] == 74) {
            lower_nibble = 10;
            i++;
        } else if (encrypted_str[i] == 81) {
            lower_nibble = 11;
            i++;
        } else if (encrypted_str[i] == 75) {
            lower_nibble = 12;
            i++;
        } else {
            lower_nibble = encrypted_str[i] - 48;
            i++;
        }

        decrypted_str[j] = (higher_nibble << 4) + lower_nibble;
        j++;
    }
    for(int k=0; k < j; k++)
    {
        encrypted_str[k] = decrypted_str[k];
    }
    encrypted_str[j] = '\0';
}



// Hook function. Might use helper functions in C, i.e. void _stdcall helper(int num) {}
// Might even use only a funcHook c function instead!
__declspec(naked) void funcHook() {
	// Restore overriden bytes
	// remove_hook();

	// Assembly part. Might call restore_hook somewhere inside
	__asm {
		// ...
		mov eax, [esp];
		cmp eax, required_ret
		jne not_hook

		call decrypt

		not_hook:
		mov eax, original_func_address;
		jmp eax

	}
}

void setHook() {
	HMODULE h = GetModuleHandle(L"client.exe");
	HMODULE h2 = GetModuleHandle(L"mscvrt.dll");

	if ((h == NULL) || (h2 == NULL)) { return; }

	original_func_address = (FUNC_PTR)GetProcAddress(h2, "puts");
	if (original_func_address == NULL) {
		return;
	}

	int addr_beginning_of_our_exe = 0x401000; // change!
	int addr_func_to_hook_in_IAT = 0x40A258; // change!
	IAT = h + (addr_func_to_hook_in_IAT - addr_beginning_of_our_exe) / 4; // Calc address of address to override in IAT

	JumpTo = (FUNC_PTR)((char*)&funcHook);
	restore_hook();
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		setHook();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}