; Model
.model small
     
; Data
.data

; Code 
.code
    ; Main
    main proc
        ; Update > AH
        mov ah, 00000001b
        
        ; Update > AH --- NOTE (Lapys) -> Assert if both operands are equal;
        ;     Does not modify the destination operand, rather it modifies the Zero Flag (`ZF`).
        test ah, 00000001b
        
        ; Halt --- NOTE (Lapys) -> Halt the pfogram.
        hlt            
    ; Terminate
    main endp