/* CITE (Lapys)  -> http://www.howtogeek.com/howto/windows-vista/keyboard-ninja-toggle-file-extension-display-with-a-shortcut-key-in-windows/
*/
; Logic
#IfWinActive ahk_class CabinetWClass
    ; Execute
    ^!E::
        ; Initialization > Hidden File Extensions Status
        HiddenFileExtensions_Status :=

        ; Update > Hidden File Extensions Status
        RegRead, HiddenFileExtensions_Status, HKEY_CURRENT_USER, Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced, HideFileExt

        ; Logic > Update > [Registry]
        If HiddenFileExtensions_Status = 1
        RegWrite, REG_DWORD, HKEY_CURRENT_USER, Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced, HideFileExt, 0

        Else
        RegWrite, REG_DWORD, HKEY_CURRENT_USER, Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced, HideFileExt, 1

        ; ...
        Send, {F5}

        ; Return
        Return
#IfWinActive
