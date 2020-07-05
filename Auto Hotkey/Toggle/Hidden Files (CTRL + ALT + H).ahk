/* CITE (Lapys)  -> http://www.howtogeek.com/howto/keyboard-ninja/keyboard-ninja-toggle-hidden-files-with-a-shortcut-key-in-windows/
*/
; Logic
#IfWinActive ahk_class CabinetWClass
    ; Execute
    ^!H::
        ; Initialization > Hidden Files Status
        HiddenFiles_Status :=

        ; Update > Hidden Files Status
        RegRead, HiddenFiles_Status, HKEY_CURRENT_USER, Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced, Hidden

        ; Logic > Update > [Registry]
        if HiddenFiles_Status = 2
        RegWrite, REG_DWORD, HKEY_CURRENT_USER, Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced, Hidden, 1

        else
        RegWrite, REG_DWORD, HKEY_CURRENT_USER, Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced, Hidden, 2

        ; ...
        Send, {F5}

        ; Return
        return
#IfWinActive
