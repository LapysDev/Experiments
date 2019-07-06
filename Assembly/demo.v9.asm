; Model
.model small

; Data
.data

; Code
.code
    ; Main
    main proc
        ; Update > CX
        mov cx, 5

        ; [Top] --- NOTE (Lapys) -> Label.
        top:
            ; Update > DL
            mov dl, 49

            ; Update > AH; Interrupt
            mov ah, 2h
            int 21h

        ; Loop --- NOTE (Lapys) -> Similar to the `jmp` operation;
        ;     but also decrements the `CX` register and skips the sequence to a label until the register's value reaches zero.
        loop top

        ; Terminate
        endp
    end main
