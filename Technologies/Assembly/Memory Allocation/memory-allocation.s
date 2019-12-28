section .text
   global _start         ;must be declared for using gcc

_start:                  ;tell linker entry point

   mov  eax, 45      ;sys_brk
   xor  ebx, ebx
   int  80h

   add  eax, 16384   ;number of bytes to be reserved
   mov  ebx, eax
   mov  eax, 45      ;sys_brk
   int  80h

   cmp  eax, 0
   jl   exit    ;exit, if error
   mov  edi, eax     ;EDI = highest available address
   sub  edi, 4       ;pointing to the last DWORD
   mov  ecx, 4096    ;number of DWORDs allocated
   xor  eax, eax     ;clear eax
   std           ;backward
   rep  stosd            ;repeat for entire allocated area
   cld           ;put DF flag to normal state

   mov  eax, 4
   mov  ebx, 1
   mov  ecx, msg
   mov  edx, len
   int  80h      ;print a message

exit:
   mov  eax, 1
   xor  ebx, ebx
   int  80h

section .data
msg     db  "Allocated 16 KB of memory!", 10
len     equ $ - msg
