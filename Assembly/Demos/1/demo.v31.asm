; Model
.model small

; Data
.data

; Code
.code
    ; Main
    main proc 
        ; Update > (DX, AX, BL) --- NOTE (Lapys) -> Set all associated registers.
        mov dx, 0
        mov ax, 128
        mov bx, 2
        
        ; Update > AX
        ;     --- NOTE (Lapys) -> Divide `AL`by `BL` and store the result in `AX`.
        ;                             The remainder from division is stored in `AH`.
        `.
        ;     --- WARN (Lapys) -> The Carry Flag asserts arithmetic overflow;
        ;                             If there is an overflow, the bits of the result
        ;                             will be stored in the `DX` & `AX` registers accordingly.
        div bl
        
        ; Terminate
        hlt
    main endp
