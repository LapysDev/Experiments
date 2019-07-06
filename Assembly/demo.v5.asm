; Model
.model small

; Code
.code
    ; Main
    main proc
        mov dl, 50 ; Set printable character to ASCII value 50 (or the `2` character)
        mov ah, 2h ; Print
        int 21h ; Execute

        ; Terminate
        endp
    end main
