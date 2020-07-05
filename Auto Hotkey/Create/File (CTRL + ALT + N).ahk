/* CITE (Lapys) -> https://gist.github.com/1148174
*/

; Import
#include C:\LapysDev\Assets\frameworks\exception.ahk ; Exception
#include C:\LapysDev\Assets\frameworks\file-explorer.ahk ; File Explorer

; Logic > Execute
#IfWinActive ahk_class CabinetWClass
    ^!N::
#IfWinActive ahk_class ExploreWClass
    ^!N::
#IfWinActive ahk_class Progman
    ^!N::
#IfWinActive ahk_class WorkerW
    ^!N::
        ; Constant > Current File Path
        ; Initialization > File Path
        CURRENT_FILE_PATH := GetExplorerPath()
        filePath :=

        ; Change Directory
        ChangeDirectory(CURRENT_FILE_PATH)

        ; Update > File Path; Error
        InputBox, filePath, New File (<name>.<extension>), , , 400, 100
        AssertErrorLevel("Invalid shortcut name")

        ; Insertion
        FileAppend, , %filePath%

        ; Change Directory
        ChangeDirectory(TEMP_FILE_PATH)

        ; Return
        Return

#IfWinActive
