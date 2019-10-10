; Model
.model small

; Data
.data
    ; Constant > Variable --- NOTE (Lapys) -> Integer type of 8 bits.
    variable db 50

; Code
.code
    ; Main
    main proc
        mov dl, variable ; Set printable character to ASCII value 50 (or the `2` character)
        mov ah, 2h ; Print
        int 21h ; Execute

        ; Terminate
        endp
    end main
