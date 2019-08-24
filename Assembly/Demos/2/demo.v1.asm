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
        
        ; Update > AL --- NOTE (Lapys) -> Add value & Carry Flag to register.
        adc al, 5
        
        ; Terminate
        hlt
    main endp