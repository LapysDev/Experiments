; Model
.model small

; Data
.data
    ; Constant > Variable
    variable dw 1

; Code
.code
    ; Main
    main proc
        ; Update > EAX, AX --- NOTE (Lapys) -> Transferring Variable (16 bits) to EAX register (32 bits).
        mov eax, 0
        mov ax, variable

        ; Terminate
        endp
    end main
