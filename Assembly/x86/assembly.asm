global _start

; ...
section .data
  ; name db 'L', 'a', 'p', 'y', 's', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  name db "Lapys"
  times 100 - ($ - name) db 0

; ...
section .rodata
  characters db "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
  greeting   db "Hello, ", 34, 34, "! ()"

; ...
section .text
  jmp _start

  ; void exit(int code)
  @exit:
    mov eax, 0x1           ; EAX = &sys_exit
    mov bx, word [esp + 4] ; EBX = code
    nop                    ;
    add esp, 4             ; freea(sizeof int)
    int 0x80               ; sys_call(...)

  ; unsigned lengthof(char const string[])
  @lengthof:
    sub esp, 8                  ; alloca(sizeof size_t)
    mov dword [esp + 0], 0      ;   size_t count = 0u
    nop                         ;
    dec dword [esp + 0]         ;   --count
    dec dword [esp + 12]        ;   --string
    .@while_nul:                ;   {
      inc dword [esp + 0]       ;     ++count
      inc dword [esp + 12]      ;     ++string
      mov eax, dword [esp + 12] ;     ... = *string == '\0'
      cmp byte [eax], 0         ;
      jne .@while_nul           ;   } while (!...)
    mov eax, dword [esp + 0]    ;   return = count
    mov dword [esp + 20], eax   ;
    add esp, 8                  ; freea(sizeof size_t)
    ret                         ;

  ; void print(int descriptor, char const string[], size_t length)
  @print:
    mov eax, 0x4              ; EAX = &sys_write
    mov bx, word [esp + 4]    ; EBX = descriptor
    mov ecx, dword [esp + 8]  ; ECX = string
    mov edx, dword [esp + 16] ; EDX = length
    nop                       ;
    int 0x80                  ; sys_call(...)
    ret                       ;

  ; void scan(int descriptor, char string[], size_t length)
  @scan:
    mov eax, 0x3              ; EAX = &sys_read
    mov bx, word [esp + 4]    ; EBX = descriptor
    mov ecx, dword [esp + 8]  ; ECX = string
    mov edx, dword [esp + 16] ; EDX = length
    nop                       ;
    int 0x80                  ; sys_call(...)
    ret                       ;

  ; ...
  _start:
    sub  esp, 4 + 8 + 8        ; alloca(sizeof int + sizeof char* + sizeof size_t)
    mov  word [esp + 0], 0x0   ;   int    descriptor = stdin
    mov  dword [esp + 4], name ;   char  *string     = ::name
    mov  dword [esp + 12], 100 ;   size_t length     = sizeof name
    nop                        ;
    call @scan                 ;   scan(descriptor, string, length)
    add  esp, 4 + 8 + 8        ; freea(sizeof int + sizeof char* + sizeof size_t)

    sub  esp, 8 + 8            ; alloca(sizeof char* + sizeof size_t)
    mov  dword [esp + 0], name ;   char  *string = ::name
    mov  dword [esp + 8], 0    ;   size_t return = 0u
    nop                        ;
    call @lengthof             ;   lengthof(string)
    add  esp, 8                ; freea(sizeof char*)
    mov  edx, esp              ; EDX = &return
    add  esp, 8                ; freea(sizeof size_t)

    sub  esp, 4 + 8 + 20 + 8 + 8 + 4 + 8         ; alloca(sizeof ...)
    mov  word [esp + 0], 0x1                     ;   int           descriptor = stdout
    mov  dword [esp + 4], greeting + 0           ;   char const   *string     = ::greeting
    mov  dword [esp + 12], 8                     ;   size_t        length     = 8zu
    mov  eax, dword [edx]                        ;   unsigned long count      = *EDX
    mov  dword [esp + 20], eax                   ;
    mov  dword [esp + 28], 0                     ;   size_t        index      = 0zu
    mov  word [esp + 36], 10                     ;   unsigned      radix      = 10u
    mov  byte [esp + 40], 0                      ;   unsigned char digits[20] = {0u}
    nop                                          ;
    cmp dword [esp + 20], 0                      ;   ... = count == 0
    jne .@if_named                               ;   if ...
    jmp .@else_named                             ;
    nop                                          ;
    .@if_named:                                  ;   if {
      call @print                                ;     print(descriptor, string, length)
      mov  eax, dword [esp + 20]                 ;     length = count
      mov  dword [esp + 12], eax                 ;
      mov  dword [esp + 4], name                 ;     string = ::name
      call @print                                ;     print(descriptor, string, length)
      mov  dword [esp + 12], 4                   ;     length = 4zu
      mov  dword [esp + 4], greeting + 8         ;     string = ::greeting + 8
      call @print                                ;     print(descriptor, string, length)
      nop                                        ;
      .@while_nil:                               ;     {
        mov eax, dword [esp + 20]                ;       EAX = count
        mov edx, 0                               ;       EDX = 0u
        div word [esp + 36]                      ;       EDX = EAX % radix; EAX /= radix
        nop                                      ;
        mov dword [esp + 20], eax                ;       count = EAX
        mov eax, dword [esp + 28]                ;
        mov byte [eax + esp + 40], dl            ;       digits[index] = EDX
        inc dword [esp + 28]                     ;       ++index
        cmp dword [esp + 20], 0                  ;       ... = count == 0
        jne .@while_nil                          ;     } while (!...)
      nop                                        ;
      mov  dword [esp + 12], 1                   ;     length = 1zu
      .@while_index:                             ;     {
        dec dword [esp + 28]                     ;       --index
        mov eax, dword [esp + 28]                ;       digits[index]
        mov al, byte [eax + esp + 40]            ;
        .@switch_digit:                          ;       switch (digits[index]) {
          cmp al, 0                              ;         ... = digits[index] == 0
          je  .@case_digit_0                     ;         case ...
          cmp al, 1                              ;         ... = digits[index] == 1
          je  .@case_digit_1                     ;         case ...
          cmp al, 2                              ;         ... = digits[index] == 2
          je  .@case_digit_2                     ;         case ...
          cmp al, 3                              ;         ... = digits[index] == 3
          je  .@case_digit_3                     ;         case ...
          cmp al, 4                              ;         ... = digits[index] == 4
          je  .@case_digit_4                     ;         case ...
          cmp al, 5                              ;         ... = digits[index] == 5
          je  .@case_digit_5                     ;         case ...
          cmp al, 5                              ;         ... = digits[index] == 5
          je  .@case_digit_5                     ;         case ...
          cmp al, 6                              ;         ... = digits[index] == 6
          je  .@case_digit_6                     ;         case ...
          cmp al, 7                              ;         ... = digits[index] == 7
          je  .@case_digit_7                     ;         case ...
          cmp al, 8                              ;         ... = digits[index] == 8
          je  .@case_digit_8                     ;         case ...
          cmp al, 9                              ;         ... = digits[index] == 9
          je  .@case_digit_9                     ;         case ...
          nop                                    ;
          .@case_digit_0:                        ;         case {
            mov  dword [esp + 4], characters + 0 ;           string = ::characters + 0
            jmp  .@break_digit                   ;         }
          .@case_digit_1:                        ;         case {
            mov  dword [esp + 4], characters + 1 ;           string = ::characters + 1
            jmp  .@break_digit                   ;         }
          .@case_digit_2:                        ;         case {
            mov  dword [esp + 4], characters + 2 ;           string = ::characters + 2
            jmp  .@break_digit                   ;         }
          .@case_digit_3:                        ;         case {
            mov  dword [esp + 4], characters + 3 ;           string = ::characters + 3
            jmp  .@break_digit                   ;         }
          .@case_digit_4:                        ;         case {
            mov  dword [esp + 4], characters + 4 ;           string = ::characters + 4
            jmp  .@break_digit                   ;         }
          .@case_digit_5:                        ;         case {
            mov  dword [esp + 4], characters + 5 ;           string = ::characters + 5
            jmp  .@break_digit                   ;         }
          .@case_digit_6:                        ;         case {
            mov  dword [esp + 4], characters + 6 ;           string = ::characters + 6
            jmp  .@break_digit                   ;         }
          .@case_digit_7:                        ;         case {
            mov  dword [esp + 4], characters + 7 ;           string = ::characters + 7
            jmp  .@break_digit                   ;         }
          .@case_digit_8:                        ;         case {
            mov  dword [esp + 4], characters + 8 ;           string = ::characters + 8
            jmp  .@break_digit                   ;         }
          .@case_digit_9:                        ;         case {
            mov  dword [esp + 4], characters + 9 ;           string = ::characters + 9
            jmp  .@break_digit                   ;         }
          .@break_digit:                         ;       }
        nop                                      ;
        call @print                              ;       print(descriptor, string, length)
        cmp dword [esp + 28], 0                  ;       ... = index == 0
        jne .@while_index                        ;     } while (!...)
      nop                                        ;
      mov  dword [esp + 12], 1                   ;     length = 1zu
      mov  dword [esp + 4], greeting + 12        ;     string = ::greeting + 12
      call @print                                ;     print(descriptor, string, length)
      jmp  .@break_named                         ;   }
    nop                                          ;
    .@else_named:                                ;   else {
      mov  dword [esp + 12], 5                   ;     length = 5
      call @print                                ;     print(descriptor, string, length)
      mov  dword [esp + 12], 1                   ;     length = 5
      add  dword [esp + 4], 9                    ;     string += 9
      call @print                                ;     print(descriptor, string, length)
      jmp  .@break_named                         ;   }
    .@break_named:                               ;
    add  esp, 4 + 8 + 20 + 8 + 8 + 4 + 8         ; freea(sizeof ...)

    sub  esp, 4          ; alloca(sizeof int)
    mov  word [esp], 0x0 ;   int code = EXIT_SUCCESS
    call @exit           ;   exit(code)
