; Model
.model small
     
; Data
.data

; Code 
.code
    ; Main
    main proc
        ; Update > AH
        mov ah, 5
        
        ; Update > AH --- NOTE (Lapys) -> Sign/ unsign `AH`.
        neg ah
        
        ; Halt --- NOTE (Lapys) -> Halt the pfogram.
        hlt            
    ; Terminate
    main endp