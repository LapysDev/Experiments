; Model
.model small
     
; Data
.data

; Code 
.code
    ; Main
    main proc
        ; Update > AX
        mov ax, 1
        
        ; Update > [Stack]
        push ax ; Move AX to the top of the stack
        pop cx ; Move value of AX to CX and remove the last address from the SP register (Stack Pointer)
        
        ; Terminate
        endp
    end main