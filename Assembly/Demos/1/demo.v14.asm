; Model
.model small
     
; Data
.data

; Code 
.code
    ; Main
    main proc
        ; Print Character
        ; call printCharacter
        
        ; [Global Label]
        GLOBAL_LABEL::
        
        ; Terminate
        endp
    
        ; Function > Print Character --- WARN (Lapys) -> Procedures are also parsed sequentially and are executed despite not being called.
        printCharacter proc
            ; Update > (DL, AH); Interrupt
            mov dl, 65
            mov ah, 2h
            int 21h
            
            ; ... --- WARN (Lapys) -> Not recommended to jump between procedures.
            ; jmp GLOBAL_LABEL
            
            ; Return
            ret
        printCharacter endp
    end main