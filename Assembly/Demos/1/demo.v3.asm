.model tiny ; COM Program. Code Data & Stack in one 64K Segment.

; Code Segment
.code
    org 100h ; Code starts at offset 100h; `h` means hexadecimal by the way...

    ; Main Process
    main proc near
        ; Routine to display string
        mov ah, 09h
        mov dx, offset message ; Offset of `message` string terminated with `$` character.
        int 21h ; DOS Interrupt

        ; Routine to terminate
        mov ah, 4ch
        mov al, 00
        int 21h ; DOS Interrupt

        ; End the program
        endp

        ; Constant > Message
        message db "Hello, World!$"
    end main
