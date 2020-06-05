; Model
.model small

; Code
.code
    mov ah, 1h ; Read character (the character is loaded to the `al` register)
    int 21h ; DOS Interrupt

    mov dl, al ; Move the value (character) from `al` to `dl` (The `dl` register`s value is read when values are printed)

    mov ah, 2h ; Write character
    int 21h ; DOS Interrupt

    ; End the program
    end
