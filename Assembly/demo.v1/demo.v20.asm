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
        
        ; Update > AH --- NOTE (Lapys) -> NOT operation on all bits of `AH`.
        not ah
        
        ; Halt --- NOTE (Lapys) -> Halt the pfogram.
        hlt            
    ; Terminate
    main endp