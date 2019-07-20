; Model
.model small
     
; Data
.data

; Code 
.code
    ; Main
    main proc
        ; Update > (AX, BX, CX)
        mov ax, 1
        mov bx, 2
        mov cx, 3
        
        ; Update > [Stack] --- NOTE (Lapys) -> The registers are:
        ;     AX, CX, DX, BX, SP, BP, SI and DI
        ;     in sequence and in order.
        ;
        ;    For the 32-bit version.
        ;     the `pusha`  and `popa` instructions are suffixed with the `d` character.
        pusha ; Save the addresses of some registers to the top of the Stack
        
        ; Update > (AX, BX, CX)
        mov ax, 2
        mov bx, 4
        mov cx, 6
        
        popa ; Restore the addresses of some registers from the top of the Stack
        
        ; Terminate
        endp
    end main