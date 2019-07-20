; Model
.model small

; Data
.data

; Code
.code
    ; Main
    main proc 
        ; Update > AL
        mov al, 00000001b
        shr al, 1 ; NOTE (Lapys) -> Shift the bits rightward by a specified count.
                  ;     The rightmost bit is stored in the Carry Flag.
                  ;     The `sar` operation also has the same effect.
        
        ; Terminate
        hlt
    main endp
