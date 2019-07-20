; Model
.model small
     
; Data
.data

; Code 
.code
    ; Main
    main proc
        ; Update > (AX, BX)
        mov ax, 10
        mov bx, 5
        
        ; Assert
        cmp ax, bx
        
        ; Update > CX
        mov cx, 0
        
        ; ... --- NOTE (Lapys) -> `jmp` operations based on the recent `cmp` evaluation.
        jcxz IF_CX_EQUAL_TO_ZERO
        je IF_AX_EQUAL_TO
        jne IF_AX_NOT_EQUAL_TO
        jmp ELSE
        
        ; [Logic]
        IF_CX_EQUAL_TO_ZERO:
            mov dl, 63 ; ?
            jmp END
        IF_AX_EQUAL_TO:
            mov dl, 61 ; =
            jmp END
        IF_AX_NOT_EQUAL_TO:
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