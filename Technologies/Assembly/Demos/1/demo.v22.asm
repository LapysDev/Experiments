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
        
        ; Assert --- NOTE (Lapys) -> Performs an implied subtraction.
        ;    Combined with the `jmp` operation, control structures can be mimicked.
        ;
        ;     Destination < Source | CF = 1, ZF = 0
        ;     Destination > Source | CF = 0, ZF = 0
        ;     Destination = Source | CF = 0, ZF = 1
        cmp ah, bh
        
        ; Halt --- NOTE (Lapys) -> Halt the pfogram.
        hlt            
    ; Terminate
    main endp