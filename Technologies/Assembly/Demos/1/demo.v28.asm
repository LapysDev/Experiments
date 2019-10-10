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
        shl al, 1 ; NOTE (Lapys) -> Shift the bits leftward by a specified count.
                  ;     The leftmost bit is stored in the Carry Flag.
                  ;     The `sal` operation also has the same effect.
        
        ; Terminate
        hlt
    main endp
