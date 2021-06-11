; Compilation
;   nasm -f bin boot.asm -o boot.bin
;   qemu-system-x86_64 boot.bin
jmp $ ; ->> Repeat the same instruction at this address

times 510 - ($ - $$) db 0x00 ; ->> Execute a `NOP` instruction (`0x00`) for ~512 boot-able bytes
db 0x55, 0xAA ; ->> Execute instructions `0x55` and `0xAA`
