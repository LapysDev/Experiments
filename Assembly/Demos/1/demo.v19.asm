; Model
.model small
     
; Data
.data

; Code 
.code
    ; Main
    main proc
        ; Update > (AH, BH)
        mov ah, 00000001b
        mov bh, 00000101b
        
        ; Update > AH --- NOTE (Lapys) -> XOR operation on all bits of `AH`.
        xor ah, bh
        
        ; Halt --- NOTE (Lapys) -> Halt the pfogram.
        hlt            
    ; Terminate
    main endp