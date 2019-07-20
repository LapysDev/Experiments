; Model
.model small
     
; Data
.data

; Code 
.code
    ; Main
    main proc
        ; Update > AH
        mov ax, 10
        
        ; Assert --- NOTE (Lapys) -> Set the `CF` and `ZF` status flags.
        cmp ax, 5
        
        ; ... --- NOTE (Lapys) -> `jmp` operations based on `CF` and `ZF` flags.
        jc IF_AX_LESSER_THAN
        jz IF_AX_EQUAL_TO
        
        jnc IF_AX_GREATER_THAN
        jnz IF_AX_GREATER_THAN
        
        jmp ELSE
        
        ; [Logic] --- NOTE (Lapys) -> The beginnings of an `if` statement.
        IF_AX_EQUAL_TO:
            mov dl, 61 ; =
            jmp END
        IF_AX_GREATER_THAN:
            mov dl, 62 ; >
            jmp END
        IF_AX_LESSER_THAN:
            mov dl, 60 ; <
            jmp END
        ELSE:
            mov dl, 33 ; !
            jmp END
        END:
        
        mov ah, 2h
        int 21h
        
        ; Halt --- NOTE (Lapys) -> Halt the pfogram.
        hlt            
    ; Terminate
    main endp