; Model
.model small

; Data
.data

; Code
.code
    ; Main
    main proc
        ; Update > AL
        mov al, 5
        
        ; Update > AL --- NOTE (Lapys) -> Subtract value & Carry Flag from register.
        sbb al, 5
        
        ; Terminate
        hlt
    main endp