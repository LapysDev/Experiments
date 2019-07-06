; Model
.model small

; Data
.data                    
    ; Constant > (Main, Nested) Loop Iterator  
    mainLoopIterator dw 5 + 1 ; Iterates `x - 1` times apparently.
    nestedLoopIterator dw 2

; Code
.code      
    ; Main
    main proc    
        ; Update > (CX, DS) --- NOTE (Lapys) -> A minor fix with assigning values.
        mov cx, @data
        mov ds, cx
                 
        ; Update > CX
        mov cx, [mainLoopIterator]
        
        ; [Main Loop]
        mainLoop:               
            ; Update > DL, AH; Interrupt --- NOTE (Lapys) -> Print the character `1`.
            mov dl, 49
            mov ah, 2h
            int 21h

            ; Update > CX; [Nested Loop]
            mov cx, [nestedLoopIterator]
            nestedLoop:
                ; Update > DL, AH; Interrupt --- NOTE (Lapys) -> Print the character `.`.
                mov dl, 46
                mov ah, 2h
                int 21h        
                
                ; dec nestedLoopIterator ; There is no need to decrement the Nested Loop Iterator since it has no child loops.

            ; Loop > Nested Loop
            loop nestedLoop     
                                  
        ; Update > (Main Loop Iterator, CX)
        dec mainLoopIterator
        mov cx, [mainLoopIterator]

        ; Loop > Main Loop --- NOTE (Lapys) -> Assembly is strict, not assertive.
        ;     The `loop` operation here will overflow the `CX` register to the value `255` (which is `0 - 1`).
        ;     Which is why the `CX` register is manually updated to avoid exceptions.
        loop mainLoop

        ; Terminate
        endp
    end main
