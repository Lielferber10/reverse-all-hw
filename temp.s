.intel_syntax noprefix

.LC0:
        .string "%s"
.LC1:
        .string "%02d\n"
.LC2:
        .string "Wood"
.LC3:
        .string "Brick"
.LC4:
        .string "Wool"
.LC5:
        .string "Grain"
.LC6:
        .string "Stone"
main:
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
        push    eax
        push    OFFSET FLAT:.LC0
        call    __isoc99_scanf
        add     esp, 16
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
        push    eax
        push    OFFSET FLAT:.LC1
        call    printf
        add     esp, 16
        sub     esp, 12
        push    OFFSET FLAT:.LC2
        call    puts
        add     esp, 16
        mov     eax, DWORD PTR [ebp-24]
        sub     esp, 8
        push    eax
        push    OFFSET FLAT:.LC1
        call    printf
        add     esp, 16
        sub     esp, 12
        push    OFFSET FLAT:.LC3
        call    puts
        add     esp, 16
        mov     eax, DWORD PTR [ebp-20]
        sub     esp, 8
        push    eax
        push    OFFSET FLAT:.LC1
        call    printf
        add     esp, 16
        sub     esp, 12
        push    OFFSET FLAT:.LC4
        call    puts
        add     esp, 16
        mov     eax, DWORD PTR [ebp-16]
        sub     esp, 8
        push    eax
        push    OFFSET FLAT:.LC1
        call    printf
        add     esp, 16
        sub     esp, 12
        push    OFFSET FLAT:.LC5
        call    puts
        add     esp, 16
        mov     eax, DWORD PTR [ebp-12]
        sub     esp, 8
        push    eax
        push    OFFSET FLAT:.LC1
        call    printf
        add     esp, 16
        sub     esp, 12
        push    OFFSET FLAT:.LC6
        call    puts
        add     esp, 16
        mov     eax, 0
        mov     ecx, DWORD PTR [ebp-4]
        leave
        lea     esp, [ecx-4]
        ret