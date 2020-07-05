; Import
#include C:\LapysDev\Assets\frameworks\exception.ahk ; Exception
#include C:\LapysDev\Assets\frameworks\file-explorer.ahk ; File Explorer

; Logic > Execute
#IfWinActive ahk_class CabinetWClass
    ^!S::
#IfWinActive ahk_class ExploreWClass
    ^!S::
#IfWinActive ahk_class Progman
    ^!S::
#IfWinActive ahk_class WorkerW
    ^!S::
        ; Constant > (Current File Path, Selected File Paths, ...)
        CURRENT_FILE_PATH := GetExplorerPath()
        SELECTED_FILE_PATHS := GetExplorerSelectedFiles()
        REMOVE_FILE_PATH_FILE_EXTENSION_REGULAR_EXPRESSION := "\.[^\.]{0,}"

        ; Logic
        if SELECTED_FILE_PATHS
            ; Loop
            loop, parse, SELECTED_FILE_PATHS, `n
            {
                ; Constant > Selected File Path ...
                SELECTED_FILE_PATH := A_LoopField
                SELECTED_FILE_PATH_WITHOUT_FILE_EXTENSION := RegExReplace(SELECTED_FILE_PATH, REMOVE_FILE_PATH_FILE_EXTENSION_REGULAR_EXPRESSION, "")

                ; ...; Insertion; ...
                ChangeDirectory(CURRENT_FILE_PATH)
                FileCreateShortcut, %SELECTED_FILE_PATH%, %SELECTED_FILE_PATH_WITHOUT_FILE_EXTENSION%.lnk
                ChangeDirectory(TEMP_FILE_PATH)
            }

        else {
            ; Initialization > User Input
            UserInput :=

            ; Update > User Input; ...
            InputBox, UserInput, New Shortcut (<name>), , , 400, 100
            AssertErrorLevel("Invalid shortcut name")
            UserInput := RegExReplace(UserInput, REMOVE_FILE_PATH_FILE_EXTENSION_REGULAR_EXPRESSION)

            ; Logic > Insertion
            if UserInput
            FileCreateShortcut, %CURRENT_FILE_PATH%, %CURRENT_FILE_PATH%\%UserInput%.lnk
        }

        ; Return
        Return
#IfWinActive
