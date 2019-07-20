; Model
.model small

; Data
.data

; Code
.code
    ; Main
    main proc 
        ; Update > AL
        mov al, 2
        mov bl, 5
        
        ; Update > AX
        ;     --- NOTE (Lapys) -> Multiply `AL` & `BL` and store the result in `AX`.
        ;     --- WARN (Lapys) -> The Carry Flag asserts multiplication overflow;
        ;                             If there is an overflow, the bits of the result
        ;                             will be stored in the `DX` & `AX` registers accordingly.
        mul bl
        
        ; Terminate
        hlt
    main endp
