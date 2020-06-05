; Section > Block Started by Symbol --- NOTE (Lapys) -> For storing variables
section .bss

; Section > Data --- NOTE (Lapys) -> For storing constants
section .data
    ; Initialization > (Message, Length)
    message db 'Hello, World!', 13, 0 ; NOTE (Lapys) -> Create a string referenced with the name `message`. The `db` stands for 'double word (32-bits)' and is data type.
    length equ $ - message ; NOTE (Lapys) -> `$` is a magic value that when subtracted from returns the length of our Message. The `equ` is also a data type.

; Section > Text --- NOTE (Lapys) -> For storing instructions
section .text
    ; Initialization > Main
    global main ; NOTE (Lapys) -> Must be declared for linker (ld). This must be what defines the bulk of our program execution.

; Register > Main
main:
    ; (...)
    mov edx, length ; NOTE (Lapys) -> Store Length in `edx` register.
    mov ecx, message ; NOTE (Lapys) -> SImilar thing here, but with `ecx`.
    mov ebx, 1 ; NOTE (Lapys) -> File descriptor (`stdout` object from C).

    mov eax, 4 ; NOTE (Lapys) -> System call number: `sys_write`.
    int 0x80 ; NOTE (Lapys) -> Call the system kernel.

    mov eax, 1 ; NOTE (Lapys) -> System call number: `sys_exit`.
    int 0x80 ; NOTE (Lapys) -> Call the system kernel.
