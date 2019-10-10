; Model
.model small

; Data
.data
    ; Initialization > Iterator
    iterator dw 5

; Code
.code
    ; Main
    main proc  
        ; Update > (BX, CX, DS) --- NOTE (Lapys) -> Minor fix...
        mov bx, @data
        mov ds, bx
        mov bx, [iterator]
        
        mov cx, @data
        mov ds, cx
        mov cx, [iterator]
        
        ; Assert --- NOTE (Lapys) -> Set the Zero Flag (`ZF`) to `1`.
        cmp bx, cx

        ; ...
        jz ITERATION
        jmp END        
        
        ; [Loop]
        ITERATION:            
            ; Update > (DL, DS) --- NOTE (Lapys) -> Must be a better way to apply this...
            mov dx, @data
            mov ds, dx
            
            ; Update > (DX, AH); Interrupt
            mov dx, [iterator]
            add dl, 48 ; Convert to ASCII digits, not ASCII special characters.
            
            mov ah, 2h
            int 21h
            
            ; Update > Iterator --- NOTE (Lapys) -> Print a countdown this time.
            dec iterator
            
            ; ... --- WARN (Lapys) -> Keep the Zero Flag `true`.
            cmp bx, cx
            mov bx, [iterator]

            ; Loop --- NOTE (Lapys) -> Perform a `loop` operation if `CX` (or `ECX`) register is greater than zero
            ;     and the `ZF` flag is `1` (`true`).
            loope ITERATION
            
        END:
            ; Update > (DL, AH); Interrupt --- NOTE (Lapys) -> Multi-character printing, lol...
            mov dl, 46 ; -> .
            mov ah, 2h
            int 21h
            
            mov dl, 46 ; -> .
            mov ah, 2h
            int 21h
            
            mov dl, 46 ; -> .
            mov ah, 2h
            int 21h
        
        ; Terminate
        hlt
    main endp
