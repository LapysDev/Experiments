; Model
.model small

; Data
.data
    ; Constant > (Evaluation, Number (A, B) Request) Message
    evaluationMessage db "The sum of the specified numbers are: $"
    numberARequestMessage db "Enter a number: $"
    numberBRequestMessage db "Enter a second number: $"

; Code
.code
    ; Main --- NOTE (Lapys) -> Our program's runtime code. X-)
    main proc 
        ; [Request Number A]
            ; Update > (AX, DS) --- NOTE (Lapys) -> We do this because we cannot directy send the Segment Message to the `DS` register.
            mov ax, seg numberARequestMessage
            mov ds, ax
        
            ; Update > (DX, AH); Interrupt
            mov dx, offset numberARequestMessage
            mov ah, 9h ; Print string. Note that to print a character it`s `mov ah, 2h`.
            int 21h
        
            ; Update > AH; Interrupt
            mov ah, 1h ; Request character from user to be stored in `AL`.
            int 21h
        
            ; Update > BL
            mov bl, al ; Then store the character to `BL`.
            
        ; [Request Number B]
            ; Print Newline --- NOTE (Lapys) -> Interface Demarcation.
            call printNewline
            
            ; Update > (AX, DS)
            mov ax, seg numberBRequestMessage
            mov ds, ax
        
            ; Update > (DX, AH); Interrupt
            mov dx, offset numberBRequestMessage
            mov ah, 9h
            int 21h
        
            ; Update > AH; Interrupt
            mov ah, 1h
            int 21h
            
            ; Update > CL
            mov cl, bl
            
        ; [Evaluate `Number A + Number B`]
            ; Update > (BL, CL) --- WARN (Lapys) -> We assume the responses specified by the user are numeric characters.
            ;                                           If not, we simply the consequences.
            sub bl, 48 ; In ASCII, to convert from digits to integers we subtract by 48 units.
            sub cl, 48 ; In ASCII, to convert from digits to integers we subtract by 48 units.
            
            ; Update > BL --- NOTE (Lapys) -> Add the inputs and store in the `BL` register.
            add bl, cl
            add bl, 48 ; Assert that when we print `BL` as a character, it comes out as a digit.
            
        ; [Print Evaluation]
            ; Print Newline --- NOTE (Lapys) -> Interface Demarcation.
            call printNewline
            call printNewline
            
            ; Update > (AX, DS)
            mov ax, seg evaluationMessage
            mov ds, ax
        
            ; Update > (DX, AH); Interrupt
            mov dx, offset evaluationMessage
            mov ah, 9h
            int 21h
            
            ; Update > (DL, AH); Interrupt
            mov dl, bl
            mov ah, 2h
            int 21h
        
        ; Terminate
        hlt
    main endp
    
    ; Function > Print Newline
    printNewline proc
        ; Update > (DL, AH); Interrupt
        mov dl, 10 ; -> '\n'
        mov ah, 2h
        int 21h
        
        mov dl, 13 ; -> '\r'
        mov ah, 2h
        int 21h
        
        ; Return
        ret
    printNewline endp
