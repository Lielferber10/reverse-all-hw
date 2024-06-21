.intel_syntax noprefix
.global _main

_main:
        push    ebp                     # store ebp
        mov     ebp, esp

        push    0x0       		# pushing null
        push    0x41797261		# pushing A,y,r,a
        push    0x7262694c		# pushing r,b,i,L
        push    0x64616f4c		# pushing d,a,o,L
        push    esp                     # push pointer for "LoadLibraryA"

        call    FindFunction            # call FindFunction("LoadLibraryA")
        add     esp, 0x14               # clear stack

        push    0x00006c6c		# pushing null,l,l
        push    0x642e7472		# pushing d,#,t,r
        push    0x6376736d		# pushing c,v,s,m
        push    esp

        call    eax                     # call LoadLibrary("msvcrt.dll")
        add     esp, 0x0c               # clear stack (note arguments are cleared already)

        push    eax                     # store module handle for msvcrt
        push    0x00007373		# pushing null,s,s
        push    0x65726464		# pushing e,r,d,d
        push    0x41636f72		# pushing A,c,o,r
        push    0x50746547		# pushing P,t,e,G
        push    esp                     # push pointer for "GetProcAddress"

        call    FindFunction            # call FindFunction("GetProcAddress")
        add     esp, 0x14               # clear stack
        pop     ebx                     # restore module handle for msvcrt

        push    0x00006674		# pushing null,f,t
        push    0x6e697270		# pushing n,i,r,p
        push    esp                     # push pointer for "printf"
        push    ebx                     # push module handle for msvcrt

        call    eax                     # call GetProcAddress(msvcrt, "printf")
        add     esp, 0x08               # clear stack (note arguments are cleared already)

        push    eax                     # save printf
        mov     eax, ebx
        push    eax                     # store module handle for msvcrt
        push    0x00007373		# pushing null,s,s
        push    0x65726464		# pushing e,r,d,d
        push    0x41636f72		# pushing A,c,o,r
        push    0x50746547		# pushing P,t,e,G
        push    esp                     # push pointer for "GetProcAddress"

        call    FindFunction            # call FindFunction("GetProcAddress")
        add     esp, 0x14               # clear stack
        pop     ebx                     # restore module handle for msvcrt

        push    0x00000066              # pushing null,f
        push    0x6e616373              # pushing n,a,c,s
        push    esp                     # push pointer for "scanf"
        push    ebx                     # push module handle for msvcrt

        call    eax                     # call GetProcAddress(msvcrt, "scanf")
        add     esp, 0x08               # clear stack (note arguments are cleared already)
        mov     ebx, eax
        pop     esi                     # retrieve printf

        #from now on, ebx = &scanf, esi = &printf


        lea     ecx, [esp+4]
        and     esp, -16
        push    DWORD PTR [ecx-4]
        push    ebp
        mov     ebp, esp
        push    ecx
        sub     esp, 52
        mov     DWORD PTR [ebp-28], 0
        mov     DWORD PTR [ebp-24], 0
        mov     DWORD PTR [ebp-20], 0
        mov     DWORD PTR [ebp-16], 0
        mov     DWORD PTR [ebp-12], 0
.L7:
        sub     esp, 8
        lea     eax, [ebp-44]
        push    0x007325		# pushing null,s,%
        mov     edx, esp                # save %s address
        push    eax
        push    edx                     # push pointer for "%s"
        call    ebx                     # call scanf(%s, input)
        add     esp, 20                 # clear stack
        cmp     eax, -1
        setne   al
        test    al, al
        je      .L2
        movzx   eax, BYTE PTR [ebp-44]
        cmp     al, 114
        jne     .L3
        mov     eax, DWORD PTR [ebp-28]
        add     eax, 1
        mov     DWORD PTR [ebp-28], eax
        mov     eax, DWORD PTR [ebp-24]
        add     eax, 1
        mov     DWORD PTR [ebp-24], eax
        jmp     .L7
.L3:
        movzx   eax, BYTE PTR [ebp-44]
        cmp     al, 115
        jne     .L5
        mov     eax, DWORD PTR [ebp-28]
        add     eax, 1
        mov     DWORD PTR [ebp-28], eax
        mov     eax, DWORD PTR [ebp-24]
        add     eax, 1
        mov     DWORD PTR [ebp-24], eax
        mov     eax, DWORD PTR [ebp-20]
        add     eax, 1
        mov     DWORD PTR [ebp-20], eax
        mov     eax, DWORD PTR [ebp-16]
        add     eax, 1
        mov     DWORD PTR [ebp-16], eax
        jmp     .L7
.L5:
        movzx   eax, BYTE PTR [ebp-44]
        cmp     al, 99
        jne     .L6
        mov     eax, DWORD PTR [ebp-16]
        add     eax, 2
        mov     DWORD PTR [ebp-16], eax
        mov     eax, DWORD PTR [ebp-12]
        add     eax, 3
        mov     DWORD PTR [ebp-12], eax
        jmp     .L7
.L6:
        movzx   eax, BYTE PTR [ebp-44]
        cmp     al, 100
        jne     .L7
        mov     eax, DWORD PTR [ebp-20]
        add     eax, 1
        mov     DWORD PTR [ebp-20], eax
        mov     eax, DWORD PTR [ebp-16]
        add     eax, 1
        mov     DWORD PTR [ebp-16], eax
        mov     eax, DWORD PTR [ebp-12]
        add     eax, 1
        mov     DWORD PTR [ebp-12], eax
        jmp     .L7
.L2:
        mov     eax, DWORD PTR [ebp-28]
        sub     esp, 8
        push    0x0000000A              # pushing null,\n
        push    0x64323025              # pushing d,2,0,%
        mov     edx, esp
        push    eax
        push    edx                     # push pointer for "%02d\n"
        call    esi                     # call printf("%02d\n", resources[0])
        add     esp, 24                 # clear stack
        sub     esp, 12
        push    0x000A                  # pushing null,\n
        push    0x646F6F57              # pushing d,o,o,W
        push    esp                     # push pointer for "Wood\n"
        call    esi                     # call printf("Wood\n")
        add     esp, 24                 # clear stack
        mov     eax, DWORD PTR [ebp-24]
        sub     esp, 8
        push    0x0000000A              # pushing null,\n
        push    0x64323025              # pushing d,2,0,%
        mov     edx, esp
        push    eax
        push    edx                     # push pointer for "%02d\n"
        call    esi                     # call printf("%02d\n", resources[1])
        add     esp, 24                 # clear stack
        sub     esp, 12
        push    0x00000A6B              # pushing null,\n,k
        push    0x63697242              # pushing c,i,r,B
        push    esp                     # push pointer for "Brick\n"
        call    esi                     # call printf("Brick\n")
        add     esp, 24                 # clear stack
        mov     eax, DWORD PTR [ebp-20]
        sub     esp, 8

        push    0x0000000A              # pushing null,\n
        push    0x64323025              # pushing d,2,0,%
        mov     edx, esp
        push    eax
        push    edx                     # push pointer for "%02d\n"
        call    esi                     # call printf("%02d\n", resources[2])
        add     esp, 24                 # clear stack
        sub     esp, 12
        push    0x0000000A              # pushing null,\n
        push    0x6c6f6f57              # pushing l,o,o,W 
        push    esp                     # push pointer for "Wool\n"
        call    esi                     # call printf("Wool\n")
        add     esp, 24                 # clear stack
        mov     eax, DWORD PTR [ebp-16]
        sub     esp, 8
        push    0x0000000A              # pushing null,\n
        push    0x64323025              # pushing d,2,0,%
        mov     edx, esp
        push    eax
        push    edx                     # push pointer for "%02d\n"
        call    esi                     # call printf("%02d\n", resources[3])
        add     esp, 24                 # clear stack
        sub     esp, 12
        push    0x00000A6e              # pushing null,\n,n
        push    0x69617247              # pushing i,a,r,G
        push    esp                     # push pointer for "Grain\n"
        call    esi                     # call printf("Grain\n")
        add     esp, 24                 # clear stack
        mov     eax, DWORD PTR [ebp-12]
        sub     esp, 8
        push    0x0000000A              # pushing null,\n
        push    0x64323025              # pushing d,2,0,%
        mov     edx, esp
        push    eax
        push    edx                     # push pointer for "%02d\n"
        call    esi                     # call printf("%02d\n", resources[4])
        add     esp, 24                 # clear stack
        sub     esp, 12
        push    0x00000A65              # pushing null,\n,e
        push    0x6e6f7453              # pushing n,o,t,S
        push    esp                     # push pointer for "Stone\n"
        call    esi                     # call printf("Stone\n")
        add     esp, 24                 # clear stack
        mov     eax, 0
        mov     ecx, DWORD PTR [ebp-4]
        leave
        lea     esp, [ecx-4]
        ret

FindFunction:                           # placeholder for search_kernel32
