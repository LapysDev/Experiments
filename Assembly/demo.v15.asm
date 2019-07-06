; Model
.model small
     
; Data
.data

; Code 
.code
    ; Main
    main proc
        ; Function A
        call functionA
            
    ; Terminate
    main endp
    
    ; Function > Function (A, B)
    functionA proc 
        ; Function B
        call functionB
            
        ; Return --- NOTE (Lapys) -> Instruction pointer (`IP`) may end up here.
        ;     This is because procedures are executed despite not being called.
        ret
    functionA endp
        
    functionB proc 
            ; Return
            ret
    functionB endp