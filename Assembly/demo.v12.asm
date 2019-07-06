; Model
.model small
     
; Data
.data
    ; Definition > Flag Status --- NOTE (Lapys) -> The `?` denotes the flag/ variable is unitialized.
    FLAG_STATUS dw ?

; Code 
.code
    ; Main
    main proc
        ; Update > AX
        mov ax, 1
        
        ; Update > [Stack] --- NOTE (Lapys) -> For the 32-bit version,
        ;     the `pushf` and `popf` instructions are suffixed with the `d` character.
        ;
        ;     Of course, the size of Variable will have to be 32 bits.
        pushf ; Save state of Flags (e.g.: `CF`, `ZF`)
        pop FLAG_STATUS ; Move status of Flags to Variable
        
        push FLAG_STATUS ; Move value of Variable to top of the Stack
        popf ; Move recent value of Stack to Flags (e.g.: `CF`, `ZF`)
        
        ; Terminate
        endp
    end main