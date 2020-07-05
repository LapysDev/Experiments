; Logic
#IfWinActive ahk_class ConsoleWindowClass
    ; Execute
    ^V::
    ; Send Input > ...
    SendInput {Raw}%clipboard%

    ; Return
    return
#IfWinActive
