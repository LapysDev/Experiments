; Model
.model small

; Data
.data

; Code
.code
    ; Main
    main proc
        ; Update > (AH, AL) --- NOTE (Lapys) -> Yes, we have characters in Assembly.
        mov ah, 0
        mov al, '8' ; -> 56
        mov al, '2' ; -> 50
        
        ; Update > AL --- NOTE (Lapys) -> ASCII Adjust after Addtion
        ;                         Does some magic! XD
        aaa
        or ax, 3030h
        
        ; Terminate
        hlt
    main endp