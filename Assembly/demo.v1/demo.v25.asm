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
        
        ; ... --- NOTE (Lapys) -> `jmp` operations based on unsigned comparisons.
        ja IF_A_GREATER_THAN_B
        jnbe IF_A_GREATER_THAN_B
        
        jae IF_A_GREATER_THAN_OR_EQUAL_TO_B
        jnb IF_A_GREATER_THAN_OR_EQUAL_TO_B
        
        jb IF_A_LESSER_THAN_B
        jnae IF_A_LESSER_THAN_B
        
        jbe IF_A_LESSER_THAN_OR_EQUAL_TO_B
        jna IF_A_LESSER_THAN_OR_EQUAL_TO_B
        
        jmp ELSE
        
        ; [Logic] > (Update > DL; ...)
        IF_A_GREATER_THAN_B:
            mov dl, 97 ; -> a
            jmp END
        IF_A_GREATER_THAN_OR_EQUAL_TO_B:
            mov dl, 65 ; -> A
            jmp END
        IF_A_LESSER_THAN_B:
            mov dl, 98 ; -> b
            jmp END
        IF_A_LESSER_THAN_OR_EQUAL_TO_B:
            mov dl, 66 ; -> B
            jmp END
        ELSE:
            mov dl, 61 ; -> =
        END:
        
        ; Update > AH; Interrupt
        mov ah, 2h
        int 21h
        
        ; Halt --- NOTE (Lapys) -> Halt the pfogram.
        hlt            
    ; Terminate
    main endp