; Model
.model small

; Data
.data

; Code
.code
    ; Main
    main proc
        ; [Top] --- NOTE (Lapys) -> Label.
        top:
            ; Update > DL
            mov dl, 49

            ; Update > AH; Interrupt
            mov ah, 2h ; Print character from `DL` register.
            int 21h ; DOS Interrupt

        ; ... --- NOTE (Lapys) -> Implicit infinite loop.
        jmp top

        ; Terminate
        endp
    end main
