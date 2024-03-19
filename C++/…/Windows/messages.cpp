/* ... */
#define  UNICODE            // ->> Windows API
#define _UNICODE            //
#define _WIN32_WINNT 0x0501 // --> _WIN32_WINNT_WINXP

/* Import */
#include <ciso646>    // ->> C ISO 646
#include <climits>    // ->> C Limits
#include <cstddef>    // ->> C Standard Definition
#include <cstdio>     // ->> C Standard Input/ Output
#include <cstdlib>    // ->> C Standard Library
#include <inttypes.h> // ->> Integer Types
#include <stdint.h>   // ->> Standard Integers
#include <windows.h>  // ->> Windows --- (TODO) -> The other headers
# include <commctrl.h>    // ->> Common Control    --> ACM_OPENA, ACM_OPENW, ACM_PLAY, ACM_STOP
# include <ddraw.h>       // ->> Direct Draw       --> DDM_BEGIN, DDM_CLOSE, DDM_DRAW, DDM_END, DDM_SETFMT
// # include <inked.h>       // ->> Ink Edit          --> IE_DOCOMMAND, IE_GETAPPDATA, IE_GETBKGND, IE_GETCOMMAND, IE_GETCOUNT, IE_GETDRAWOPTS, IE_GETERASERTIP, IE_GETFORMAT, IE_GETGESTURE, IE_GETGRIDORIGIN, IE_GETGRIDPEN, IE_GETGRIDSIZE, IE_GETINK, IE_GETINKINPUT, IE_GETINKRECT, IE_GETMENU, IE_GETMODE, IE_GETNOTIFY, IE_GETPDEVENT, IE_GETPENTIP, IE_GETRECOG, IE_GETSECURITY, IE_GETSEL, IE_GETSELCOUNT, IE_GETSELITEMS, IE_GETSTYLE, IE_MSGFIRST, IE_SETAPPDATA, IE_SETBKGND, IE_SETDRAWOPTS, IE_SETERASERTIP, IE_SETFORMAT, IE_SETGRIDORIGIN, IE_SETGRIDPEN, IE_SETGRIDSIZE, IE_SETINK, IE_SETINKINPUT, IE_SETMODE, IE_SETNOTIFY, IE_SETPENTIP, IE_SETRECOG, IE_SETSECURITY, IE_SETSEL
# include <richedit.h>    // ->> Rich Edit         --> EM_AUTOURLDETECT, EM_CANPASTE, EM_CANREDO, EM_CANUNDO, EM_CHARFROMPOS, EM_CONVPOSITION, EM_DISPLAYBAND, EM_EMPTYUNDOBUFFER, EM_EXGETSEL, EM_EXLIMITTEXT, EM_EXLINEFROMCHAR, EM_EXSETSEL, EM_FINDTEXT, EM_FINDTEXTEX, EM_FINDTEXTEXW, EM_FINDTEXTW, EM_FINDWORDBREAK, EM_FMTLINES, EM_FORMATRANGE, EM_GETAUTOURLDETECT, EM_GETBIDIOPTIONS, EM_GETCHARFORMAT, EM_GETCTFMODEBIAS, EM_GETCTFOPENSTATUS, EM_GETEDITSTYLE, EM_GETEVENTMASK, EM_GETFIRSTVISIBLELINE, EM_GETHANDLE, EM_GETHYPHENATEINFO, EM_GETIMECOLOR, EM_GETIMECOMPMODE, EM_GETIMECOMPTEXT, EM_GETIMECOMPTEXT, EM_GETIMEMODEBIAS, EM_GETIMEOPTIONS, EM_GETIMEPROPERTY, EM_GETIMESTATUS, EM_GETLANGOPTIONS, EM_GETLIMITTEXT, EM_GETLINE, EM_GETLINECOUNT, EM_GETMARGINS, EM_GETMODIFY, EM_GETOLEINTERFACE, EM_GETOPTIONS, EM_GETPAGE, EM_GETPAGEROTATE, EM_GETPARAFORMAT, EM_GETPASSWORDCHAR, EM_GETPUNCTUATION, EM_GETQUERYRTFOBJ, EM_GETRECT, EM_GETREDONAME, EM_GETSCROLLPOS, EM_GETSEL, EM_GETSELTEXT, EM_GETTEXTEX, EM_GETTEXTLENGTHEX, EM_GETTEXTMODE, EM_GETTEXTRANGE, EM_GETTHUMB, EM_GETTYPOGRAPHYOPTIONS, EM_GETUNDONAME, EM_GETVIEWKIND, EM_GETWORDBREAKPROC, EM_GETWORDBREAKPROCEX, EM_GETWORDWRAPMODE, EM_GETZOOM, EM_HIDESELECTION, EM_ISIME, EM_LIMITTEXT, EM_LINEFROMCHAR, EM_LINEINDEX, EM_LINELENGTH, EM_LINESCROLL, EM_OUTLINE, EM_PASTESPECIAL, EM_POSFROMCHAR, EM_RECONVERSION, EM_REDO, EM_REPLACESEL, EM_REQUESTRESIZE, EM_SCROLL, EM_SCROLLCARET, EM_SELECTIONTYPE, EM_SETBIDIOPTIONS, EM_SETBKGNDCOLOR, EM_SETCHARFORMAT, EM_SETCTFMODEBIAS, EM_SETCTFOPENSTATUS, EM_SETEDITSTYLE, EM_SETEVENTMASK, EM_SETFONT, EM_SETFONTSIZE, EM_SETHANDLE, EM_SETHYPHENATEINFO, EM_SETIMECOLOR, EM_SETIMEMODEBIAS, EM_SETIMEOPTIONS, EM_SETIMESTATUS, EM_SETLANGOPTIONS, EM_SETLIMITTEXT, EM_SETMARGINS, EM_SETMODIFY, EM_SETOLECALLBACK, EM_SETOPTIONS, EM_SETPAGE, EM_SETPAGEROTATE, EM_SETPALETTE, EM_SETPARAFORMAT, EM_SETPASSWORDCHARR, EM_SETPUNCTUATION, EM_SETQUERYRTFOBJ, EM_SETREADONLY, EM_SETRECT, EM_SETRECTNP, EM_SETSCROLLPOS, EM_SETSEL, EM_SETTABSTOPS, EM_SETTARGETDEVICE, EM_SETTEXTEX, EM_SETTEXTMODE, EM_SETTYPOGRAPHYOPTIONS, EM_SETUNDOLIMIT, EM_SETVIEWKIND, EM_SETWORDBREAK, EM_SETWORDBREAKPROC, EM_SETWORDBREAKPROCEX, EM_SETWORDWRAPMODE, EM_SETZOOM, EM_SHOWSCROLLBAR, EM_STOPGROUPTYPING, EM_STREAMIN, EM_STREAMOUT, EM_UNDO
# include <shlobj.h>      // ->> Shell Objects     --> BFFM_SETSTATUSTEXTA, BFFM_SETSELECTIONW, BFFM_ENABLEOK, BFFM_SETSELECTIONA, BFFM_SETSTATUSTEXTW
# include <vfw.h>         // ->> Video for Windows --> WM_CAP_DRIVER_GET_NAMEW, WM_CAP_DRIVER_GET_VERSIONW, WM_CAP_FILE_GET_CAPTURE_FILEW, WM_CAP_FILE_SAVEASW, WM_CAP_FILE_SAVEDIBW, WM_CAP_FILE_SET_CAPTURE_FILEW, WM_CAP_GET_MCI_DEVICEW, WM_CAP_PAL_OPENW, WM_CAP_PAL_SAVEW, WM_CAP_SET_CALLBACK_ERRORW, WM_CAP_SET_CALLBACK_STATUSW, WM_CAP_SET_MCI_DEVICEW, WM_CAP_UNICODE_START
# include <winuser.h>     // ->> Windows User      --> VK_ACCEPT, VK_ADD, VK_APPS, VK_ATTN, VK_BACK, VK_BROWSER_BACK, VK_BROWSER_FAVORITES, VK_BROWSER_FORWARD, VK_BROWSER_HOME, VK_BROWSER_REFRESH, VK_BROWSER_SEARCH, VK_BROWSER_STOP, VK_CANCEL, VK_CAPITAL, VK_CLEAR, VK_CONTROL, VK_CONVERT, VK_CRSEL, VK_DECIMAL, VK_DELETE, VK_DIVIDE, VK_DOWN, VK_END, VK_EREOF, VK_ESCAPE, VK_EXECUTE, VK_EXSEL, VK_F1, VK_F10, VK_F11, VK_F12, VK_F13, VK_F14, VK_F15, VK_F16, VK_F17, VK_F18, VK_F19, VK_F2, VK_F20, VK_F21, VK_F22, VK_F23, VK_F24, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_FINAL, VK_HANGUL, VK_HANJA, VK_HELP, VK_HOME, VK_IME_OFF, VK_IME_ON, VK_INSERT, VK_JUNJA, VK_KANA, VK_KANJI, VK_LAUNCH_APP1, VK_LAUNCH_APP2, VK_LAUNCH_MAIL, VK_LAUNCH_MEDIA_SELECT, VK_LBUTTON, VK_LCONTROL, VK_LEFT, VK_LMENU, VK_LSHIFT, VK_LWIN, VK_MBUTTON, VK_MEDIA_NEXT_TRACK, VK_MEDIA_PLAY_PAUSE, VK_MEDIA_PREV_TRACK, VK_MEDIA_STOP, VK_MENU, VK_MODECHANGE, VK_MULTIPLY, VK_NEXT, VK_NONAME, VK_NONCONVERT, VK_NUMLOCK, VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9, VK_OEM_1, VK_OEM_102, VK_OEM_2, VK_OEM_3, VK_OEM_4, VK_OEM_5, VK_OEM_6, VK_OEM_7, VK_OEM_8, VK_OEM_CLEAR, VK_OEM_COMMA, VK_OEM_MINUS, VK_OEM_PERIOD, VK_OEM_PLUS, VK_PA1, VK_PACKET, VK_PAUSE, VK_PLAY, VK_PRINT, VK_PRIOR, VK_PROCESSKEY, VK_RBUTTON, VK_RCONTROL, VK_RETURN, VK_RIGHT, VK_RMENU, VK_RSHIFT, VK_RWIN, VK_SCROLL, VK_SELECT, VK_SEPARATOR, VK_SHIFT, VK_SLEEP, VK_SNAPSHOT, VK_SPACE, VK_SUBTRACT, VK_TAB, VK_UP, VK_VOLUME_DOWN, VK_VOLUME_MUTE, VK_VOLUME_UP, VK_XBUTTON1, VK_XBUTTON2, VK_ZOOM
# include <wow64apiset.h> // ->> Windows on Windows 64-Bit API Set --> ::IsWow64Process2(…)

/* Main */
int WinMain(HINSTANCE const instanceHandle, HINSTANCE const, LPSTR const, int const windowAppearance) {
  WCHAR moduleFileName[MAX_PATH] = L"\0";
  MSG   threadMessage            = {};
  struct /* final */ {
    WNDCLASSEXW classTemplate;
    HWND        handle;

    /* ... */
    inline LRESULT CALLBACK (*getProcedureByCallback(LRESULT (&callback)(HWND, HWND, UINT, WPARAM, LPARAM)) /* noexcept */)(HWND, UINT, WPARAM, LPARAM) {
      static LRESULT   (&procedureCallback)(HWND, HWND, UINT, WPARAM, LPARAM) = callback;
      static HWND const &procedureWindowHandle                                = this -> handle;

      struct procedure /* final */ {
        static LRESULT CALLBACK value(HWND const windowHandle, UINT const message, WPARAM const parameter, LPARAM const subparameter) {
          return procedureCallback(procedureWindowHandle, windowHandle, message, parameter, subparameter);
        }
      };

      // ...
      return callback == procedureCallback ? &procedure::value : NULL;
    }

    static LRESULT procedureCallback(HWND const procedureWindowHandle, HWND const windowHandle, UINT const message, WPARAM const parameter, LPARAM const subparameter) /* noexcept */ {
      struct output /* final */ {
        inline static char const* translate(UINT const message) /* noexcept */ {
          static struct /* final */ {
            std::size_t length;
            char        value[2048];

            inline bool apply(char const* messageConstant, char const* messageType, char const* messageEvent) /* noexcept */ {
              std::size_t const capacity = sizeof this -> value / sizeof(char);

              // ...
              for (char const *const messages[] = {messageConstant, messageType, messageEvent}, *const *message = messages; message != messages + (sizeof messages / sizeof(char const*)); ++message) {
                for (char *destination = this -> value + this -> length, *source = const_cast<char*>(*message); '\0' != *source; ++destination, ++source, ++(this -> length)) {
                  if (capacity == this -> length) break;
                  *destination = *source;
                }

                if (capacity == this -> length) break;
                this -> value[this -> length++] = '\0';
              }

              if (capacity == this -> length)
                return false;

              this -> value[this -> length] = '\0';
              return true;
            }
          } translation = {0u, {'\0'}};

          /* ...
            --- CITE ---
              #Lapys:
              - https://docs.microsoft.com/en-us/windows/win32/winmsg/about-messages-and-message-queues#system-defined-messages
              - https://github.com/LapysDev/Windows-API-Events
              - https://wiki.winehq.org/List_Of_Windows_Messages
          */
          translation.length = 0u;

          #ifdef ACM_OPENA
            if (not (ACM_OPENA == message ? translation.apply("ACM_OPENA", "Animation Control", "Open") : true))
            return "";
          #endif

          #ifdef ACM_OPENW
            if (not (ACM_OPENW == message ? translation.apply("ACM_OPENW", "Animation Control", "Open") : true))
            return "";
          #endif

          #ifdef ACM_PLAY
            if (not (ACM_PLAY == message ? translation.apply("ACM_PLAY", "Animation Control", "Play") : true))
            return "";
          #endif

          #ifdef ACM_STOP
            if (not (ACM_STOP == message ? translation.apply("ACM_STOP", "Animation Control", "Stop") : true))
            return "";
          #endif

          #ifdef BFFM_ENABLEOK
            if (not (BFFM_ENABLEOK == message ? translation.apply("BFFM_ENABLEOK", "Browse for Folder", "Enable OK") : true))
            return "";
          #endif

          #ifdef BFFM_SETSELECTIONA
            if (not (BFFM_SETSELECTIONA == message ? translation.apply("BFFM_SETSELECTIONA", "Browse for Folder", "Set Selection") : true))
            return "";
          #endif

          #ifdef BFFM_SETSELECTIONW
            if (not (BFFM_SETSELECTIONW == message ? translation.apply("BFFM_SETSELECTIONW", "Browse for Folder", "Set Selection") : true))
            return "";
          #endif

          #ifdef BFFM_SETSTATUSTEXTA
            if (not (BFFM_SETSTATUSTEXTA == message ? translation.apply("BFFM_SETSTATUSTEXTA", "Browse for Folder", "Set Status Text") : true))
            return "";
          #endif

          #ifdef BFFM_SETSTATUSTEXTW
            if (not (BFFM_SETSTATUSTEXTW == message ? translation.apply("BFFM_SETSTATUSTEXTW", "Browse for Folder", "Set Status Text") : true))
            return "";
          #endif

          #ifdef BM_CLICK
            if (not (BM_CLICK == message ? translation.apply("BM_CLICK", "Button", "Click") : true))
            return "";
          #endif

          #ifdef BM_GETCHECK
            if (not (BM_GETCHECK == message ? translation.apply("BM_GETCHECK", "Button", "Get Check") : true))
            return "";
          #endif

          #ifdef BM_GETIMAGE
            if (not (BM_GETIMAGE == message ? translation.apply("BM_GETIMAGE", "Button", "Get Image") : true))
            return "";
          #endif

          #ifdef BM_GETSTATE
            if (not (BM_GETSTATE == message ? translation.apply("BM_GETSTATE", "Button", "Get State") : true))
            return "";
          #endif

          #ifdef BM_SETCHECK
            if (not (BM_SETCHECK == message ? translation.apply("BM_SETCHECK", "Button", "Set Check") : true))
            return "";
          #endif

          #ifdef BM_SETDONTCLICK
            if (not (BM_SETDONTCLICK == message ? translation.apply("BM_SETDONTCLICK", "Button", "Set Don't Click") : true))
            return "";
          #endif

          #ifdef BM_SETIMAGE
            if (not (BM_SETIMAGE == message ? translation.apply("BM_SETIMAGE", "Button", "Set Image") : true))
            return "";
          #endif

          #ifdef BM_SETSTATE
            if (not (BM_SETSTATE == message ? translation.apply("BM_SETSTATE", "Button", "Set State") : true))
            return "";
          #endif

          #ifdef BM_SETSTYLE
            if (not (BM_SETSTYLE == message ? translation.apply("BM_SETSTYLE", "Button", "Set Style") : true))
            return "";
          #endif

          #ifdef CBEM_GETCOMBOCONTROL
            if (not (CBEM_GETCOMBOCONTROL == message ? translation.apply("CBEM_GETCOMBOCONTROL", "Combo Box", "Get Combo Control") : true))
            return "";
          #endif

          #ifdef CBEM_GETEDITCONTROL
            if (not (CBEM_GETEDITCONTROL == message ? translation.apply("CBEM_GETEDITCONTROL", "Combo Box", "Get Edit Control") : true))
            return "";
          #endif

          #ifdef CBEM_GETEXSTYLE
            if (not (CBEM_GETEXSTYLE == message ? translation.apply("CBEM_GETEXSTYLE", "Combo Box", "Get Extended Style") : true))
            return "";
          #endif

          #ifdef CBEM_GETEXTENDEDSTYLE
            if (not (CBEM_GETEXTENDEDSTYLE == message ? translation.apply("CBEM_GETEXTENDEDSTYLE", "Combo Box", "Get Extended Style") : true))
            return "";
          #endif

          #ifdef CBEM_GETIMAGELIST
            if (not (CBEM_GETIMAGELIST == message ? translation.apply("CBEM_GETIMAGELIST", "Combo Box", "Get Image List") : true))
            return "";
          #endif

          #ifdef CBEM_GETITEMA
            if (not (CBEM_GETITEMA == message ? translation.apply("CBEM_GETITEMA", "Combo Box", "Get Item") : true))
            return "";
          #endif

          #ifdef CBEM_GETITEMW
            if (not (CBEM_GETITEMW == message ? translation.apply("CBEM_GETITEMW", "Combo Box", "Get Item") : true))
            return "";
          #endif

          #ifdef CBEM_HASEDITCHANGED
            if (not (CBEM_HASEDITCHANGED == message ? translation.apply("CBEM_HASEDITCHANGED", "Combo Box", "Has Edit Changed") : true))
            return "";
          #endif

          #ifdef CBEM_INSERTITEMA
            if (not (CBEM_INSERTITEMA == message ? translation.apply("CBEM_INSERTITEMA", "Combo Box", "Insert Item") : true))
            return "";
          #endif

          #ifdef CBEM_INSERTITEMW
            if (not (CBEM_INSERTITEMW == message ? translation.apply("CBEM_INSERTITEMW", "Combo Box", "Insert Item") : true))
            return "";
          #endif

          #ifdef CBEM_SETEXTENDEDSTYLE
            if (not (CBEM_SETEXTENDEDSTYLE == message ? translation.apply("CBEM_SETEXTENDEDSTYLE", "Combo Box", "Set Extended Style") : true))
            return "";
          #endif

          #ifdef CBEM_SETIMAGELIST
            if (not (CBEM_SETIMAGELIST == message ? translation.apply("CBEM_SETIMAGELIST", "Combo Box", "Set Image List") : true))
            return "";
          #endif

          #ifdef CBEM_SETITEMA
            if (not (CBEM_SETITEMA == message ? translation.apply("CBEM_SETITEMA", "Combo Box", "Set Item") : true))
            return "";
          #endif

          #ifdef CBEM_SETITEMW
            if (not (CBEM_SETITEMW == message ? translation.apply("CBEM_SETITEMW", "Combo Box", "Set Item") : true))
            return "";
          #endif

          #ifdef CDM_FIRST
            if (not (CDM_FIRST == message ? translation.apply("CDM_FIRST", "Common Dialog", "1st") : true))
            return "";
          #endif

          #ifdef CDM_GETFILEPATH
            if (not (CDM_GETFILEPATH == message ? translation.apply("CDM_GETFILEPATH", "Common Dialog", "Get File Path") : true))
            return "";
          #endif

          #ifdef CDM_GETFOLDERIDLIST
            if (not (CDM_GETFOLDERIDLIST == message ? translation.apply("CDM_GETFOLDERIDLIST", "Common Dialog", "Get Folder ID List") : true))
            return "";
          #endif

          #ifdef CDM_GETFOLDERPATH
            if (not (CDM_GETFOLDERPATH == message ? translation.apply("CDM_GETFOLDERPATH", "Common Dialog", "Get Folder Path") : true))
            return "";
          #endif

          #ifdef CDM_GETSPEC
            if (not (CDM_GETSPEC == message ? translation.apply("CDM_GETSPEC", "Common Dialog", "Get Specifications") : true))
            return "";
          #endif

          #ifdef CDM_HIDECONTROL
            if (not (CDM_HIDECONTROL == message ? translation.apply("CDM_HIDECONTROL", "Common Dialog", "Hide Control") : true))
            return "";
          #endif

          #ifdef CDM_LAST
            if (not (CDM_LAST == message ? translation.apply("CDM_LAST", "Common Dialog", "nth") : true))
            return "";
          #endif

          #ifdef CDM_SETCONTROLTEXT
            if (not (CDM_SETCONTROLTEXT == message ? translation.apply("CDM_SETCONTROLTEXT", "Common Dialog", "Set Control Text") : true))
            return "";
          #endif

          #ifdef CDM_SETDEFEXT
            if (not (CDM_SETDEFEXT == message ? translation.apply("CDM_SETDEFEXT", "Common Dialog", "Set Default Text") : true))
            return "";
          #endif

          #ifdef DDM_BEGIN
            if (not (DDM_BEGIN == message ? translation.apply("DDM_BEGIN", "Direct Draw", "Begin") : true))
            return "";
          #endif

          #ifdef DDM_CLOSE
            if (not (DDM_CLOSE == message ? translation.apply("DDM_CLOSE", "Direct Draw", "Close") : true))
            return "";
          #endif

          #ifdef DDM_DRAW
            if (not (DDM_DRAW == message ? translation.apply("DDM_DRAW", "Direct Draw", "Draw") : true))
            return "";
          #endif

          #ifdef DDM_END
            if (not (DDM_END == message ? translation.apply("DDM_END", "Direct Draw", "End") : true))
            return "";
          #endif

          #ifdef DDM_SETFMT
            if (not (DDM_SETFMT == message ? translation.apply("DDM_SETFMT", "Direct Draw", "Set Format") : true))
            return "";
          #endif

          #ifdef DL_BEGINDRAG
            if (not (DL_BEGINDRAG == message ? translation.apply("DL_BEGINDRAG", "Drag List Box", "Begin Drag") : true))
            return "";
          #endif

          #ifdef DL_CANCELDRAG
            if (not (DL_CANCELDRAG == message ? translation.apply("DL_CANCELDRAG", "Drag List Box", "Cancel Drag") : true))
            return "";
          #endif

          #ifdef DL_DRAGGING
            if (not (DL_DRAGGING == message ? translation.apply("DL_DRAGGING", "Drag List Box", "Dragging") : true))
            return "";
          #endif

          #ifdef DL_DROPPED
            if (not (DL_DROPPED == message ? translation.apply("DL_DROPPED", "Drag List Box", "Dropped") : true))
            return "";
          #endif

          #ifdef DM_GETDEFID
            if (not (DM_GETDEFID == message ? translation.apply("DM_GETDEFID", "Dialog", "Get Default Identity") : true))
            return "";
          #endif

          #ifdef DM_REPOSITION
            if (not (DM_REPOSITION == message ? translation.apply("DM_REPOSITION", "Dialog", "Reposition") : true))
            return "";
          #endif

          #ifdef DM_SETDEFID
            if (not (DM_SETDEFID == message ? translation.apply("DM_SETDEFID", "Dialog", "Set Default Identity") : true))
            return "";
          #endif

          #ifdef EM_AUTOURLDETECT
            if (not (EM_AUTOURLDETECT == message ? translation.apply("EM_AUTOURLDETECT", "Rich Edit", "Automatic URL (Uniform Resource Locator) Detect") : true))
            return "";
          #endif

          #ifdef EM_CANPASTE
            if (not (EM_CANPASTE == message ? translation.apply("EM_CANPASTE", "Rich Edit", "Can Paste") : true))
            return "";
          #endif

          #ifdef EM_CANREDO
            if (not (EM_CANREDO == message ? translation.apply("EM_CANREDO", "Rich Edit", "Can Redo") : true))
            return "";
          #endif

          #ifdef EM_CANUNDO
            if (not (EM_CANUNDO == message ? translation.apply("EM_CANUNDO", "Rich Edit", "Can Undo") : true))
            return "";
          #endif

          #ifdef EM_CHARFROMPOS
            if (not (EM_CHARFROMPOS == message ? translation.apply("EM_CHARFROMPOS", "Rich Edit", "Character from Position") : true))
            return "";
          #endif

          #ifdef EM_CONVPOSITION
            if (not (EM_CONVPOSITION == message ? translation.apply("EM_CONVPOSITION", "Rich Edit", "Conv... Position") : true))
            return "";
          #endif

          #ifdef EM_DISPLAYBAND
            if (not (EM_DISPLAYBAND == message ? translation.apply("EM_DISPLAYBAND", "Rich Edit", "Display Band") : true))
            return "";
          #endif

          #ifdef EM_EMPTYUNDOBUFFER
            if (not (EM_EMPTYUNDOBUFFER == message ? translation.apply("EM_EMPTYUNDOBUFFER", "Rich Edit", "Empty Undo Buffer") : true))
            return "";
          #endif

          #ifdef EM_EXGETSEL
            if (not (EM_EXGETSEL == message ? translation.apply("EM_EXGETSEL", "Rich Edit", "Extend Get Selection") : true))
            return "";
          #endif

          #ifdef EM_EXLIMITTEXT
            if (not (EM_EXLIMITTEXT == message ? translation.apply("EM_EXLIMITTEXT", "Rich Edit", "Extend Limit Text") : true))
            return "";
          #endif

          #ifdef EM_EXLINEFROMCHAR
            if (not (EM_EXLINEFROMCHAR == message ? translation.apply("EM_EXLINEFROMCHAR", "Rich Edit", "Extend Line From Character") : true))
            return "";
          #endif

          #ifdef EM_EXSETSEL
            if (not (EM_EXSETSEL == message ? translation.apply("EM_EXSETSEL", "Rich Edit", "Extend Set Selection") : true))
            return "";
          #endif

          #ifdef EM_FINDTEXT
            if (not (EM_FINDTEXT == message ? translation.apply("EM_FINDTEXT", "Rich Edit", "Find Text") : true))
            return "";
          #endif

          #ifdef EM_FINDTEXTEX
            if (not (EM_FINDTEXTEX == message ? translation.apply("EM_FINDTEXTEX", "Rich Edit", "Find Text (Extended)") : true))
            return "";
          #endif

          #ifdef EM_FINDTEXTEXW
            if (not (EM_FINDTEXTEXW == message ? translation.apply("EM_FINDTEXTEXW", "Rich Edit", "Find Text (Extended)") : true))
            return "";
          #endif

          #ifdef EM_FINDTEXTW
            if (not (EM_FINDTEXTW == message ? translation.apply("EM_FINDTEXTW", "Rich Edit", "Find Text") : true))
            return "";
          #endif

          #ifdef EM_FINDWORDBREAK
            if (not (EM_FINDWORDBREAK == message ? translation.apply("EM_FINDWORDBREAK", "Rich Edit", "Find Word Break") : true))
            return "";
          #endif

          #ifdef EM_FMTLINES
            if (not (EM_FMTLINES == message ? translation.apply("EM_FMTLINES", "Rich Edit", "Format Lines") : true))
            return "";
          #endif

          #ifdef EM_FORMATRANGE
            if (not (EM_FORMATRANGE == message ? translation.apply("EM_FORMATRANGE", "Rich Edit", "Format Range") : true))
            return "";
          #endif

          #ifdef EM_GETAUTOURLDETECT
            if (not (EM_GETAUTOURLDETECT == message ? translation.apply("EM_GETAUTOURLDETECT", "Rich Edit", "Get Automatic URL (Uniform Resource Locator) Detect") : true))
            return "";
          #endif

          #ifdef EM_GETBIDIOPTIONS
            if (not (EM_GETBIDIOPTIONS == message ? translation.apply("EM_GETBIDIOPTIONS", "Rich Edit", "Get Bi-Directional Options") : true))
            return "";
          #endif

          #ifdef EM_GETCHARFORMAT
            if (not (EM_GETCHARFORMAT == message ? translation.apply("EM_GETCHARFORMAT", "Rich Edit", "Get Character Format") : true))
            return "";
          #endif

          #ifdef EM_GETCTFMODEBIAS
            if (not (EM_GETCTFMODEBIAS == message ? translation.apply("EM_GETCTFMODEBIAS", "Rich Edit", "Get CTF Mode Bias") : true))
            return "";
          #endif

          #ifdef EM_GETCTFOPENSTATUS
            if (not (EM_GETCTFOPENSTATUS == message ? translation.apply("EM_GETCTFOPENSTATUS", "Rich Edit", "Get CTF Open Status") : true))
            return "";
          #endif

          #ifdef EM_GETEDITSTYLE
            if (not (EM_GETEDITSTYLE == message ? translation.apply("EM_GETEDITSTYLE", "Rich Edit", "Get Edit Style") : true))
            return "";
          #endif

          #ifdef EM_GETEVENTMASK
            if (not (EM_GETEVENTMASK == message ? translation.apply("EM_GETEVENTMASK", "Rich Edit", "Get Event Mask") : true))
            return "";
          #endif

          #ifdef EM_GETFIRSTVISIBLELINE
            if (not (EM_GETFIRSTVISIBLELINE == message ? translation.apply("EM_GETFIRSTVISIBLELINE", "Rich Edit", "Get First Visible Line") : true))
            return "";
          #endif

          #ifdef EM_GETHANDLE
            if (not (EM_GETHANDLE == message ? translation.apply("EM_GETHANDLE", "Rich Edit", "Get Handle") : true))
            return "";
          #endif

          #ifdef EM_GETHYPHENATEINFO
            if (not (EM_GETHYPHENATEINFO == message ? translation.apply("EM_GETHYPHENATEINFO", "Rich Edit", "Get Hyphenate Information") : true))
            return "";
          #endif

          #ifdef EM_GETIMECOLOR
            if (not (EM_GETIMECOLOR == message ? translation.apply("EM_GETIMECOLOR", "Rich Edit", "Get IME (Input Method Encoding) Color") : true))
            return "";
          #endif

          #ifdef EM_GETIMECOMPMODE
            if (not (EM_GETIMECOMPMODE == message ? translation.apply("EM_GETIMECOMPMODE", "Rich Edit", "Get IME (Input Method Encoding) Composition Mode") : true))
            return "";
          #endif

          #ifdef EM_GETIMECOMPTEXT
            if (not (EM_GETIMECOMPTEXT == message ? translation.apply("EM_GETIMECOMPTEXT", "Rich Edit", "Get IME (Input Method Encoding) Composition Text") : true))
            return "";
          #endif

          #ifdef EM_GETIMEMODEBIAS
            if (not (EM_GETIMEMODEBIAS == message ? translation.apply("EM_GETIMEMODEBIAS", "Rich Edit", "Get IME (Input Method Encoding) Mode Bias") : true))
            return "";
          #endif

          #ifdef EM_GETIMEOPTIONS
            if (not (EM_GETIMEOPTIONS == message ? translation.apply("EM_GETIMEOPTIONS", "Rich Edit", "Get IME (Input Method Encoding) Options") : true))
            return "";
          #endif

          #ifdef EM_GETIMEPROPERTY
            if (not (EM_GETIMECOMPTEXT == message ? translation.apply("EM_GETIMEPROPERTY", "Rich Edit", "Get IME (Input Method Encoding) Property") : true))
            return "";
          #endif

          #ifdef EM_GETIMESTATUS
            if (not (EM_GETIMESTATUS == message ? translation.apply("EM_GETIMESTATUS", "Rich Edit", "Get IME (Input Method Encoding) Status") : true))
            return "";
          #endif

          #ifdef EM_GETLANGOPTIONS
            if (not (EM_GETLANGOPTIONS == message ? translation.apply("EM_GETLANGOPTIONS", "Rich Edit", "Get Language Options") : true))
            return "";
          #endif

          #ifdef EM_GETLIMITTEXT
            if (not (EM_GETLIMITTEXT == message ? translation.apply("EM_GETLIMITTEXT", "Rich Edit", "Get Limit Text") : true))
            return "";
          #endif

          #ifdef EM_GETLINE
            if (not (EM_GETLINE == message ? translation.apply("EM_GETLINE", "Rich Edit", "Get Line") : true))
            return "";
          #endif

          #ifdef EM_GETLINECOUNT
            if (not (EM_GETLINECOUNT == message ? translation.apply("EM_GETLINECOUNT", "Rich Edit", "Get Line Count") : true))
            return "";
          #endif

          #ifdef EM_GETMARGINS
            if (not (EM_GETMARGINS == message ? translation.apply("EM_GETMARGINS", "Rich Edit", "Get Margins") : true))
            return "";
          #endif

          #ifdef EM_GETMODIFY
            if (not (EM_GETMODIFY == message ? translation.apply("EM_GETMODIFY", "Rich Edit", "Get Modify") : true))
            return "";
          #endif

          #ifdef EM_GETOLEINTERFACE
            if (not (EM_GETOLEINTERFACE == message ? translation.apply("EM_GETOLEINTERFACE", "Rich Edit", "Get OLE (Object Linking & Embedding) Interface") : true))
            return "";
          #endif

          #ifdef EM_GETOPTIONS
            if (not (EM_GETOPTIONS == message ? translation.apply("EM_GETOPTIONS", "Rich Edit", "Get Options") : true))
            return "";
          #endif

          #ifdef EM_GETPAGE
            if (not (EM_GETPAGE == message ? translation.apply("EM_GETPAGE", "Rich Edit", "Get Page") : true))
            return "";
          #endif

          #ifdef EM_GETPAGEROTATE
            if (not (EM_GETPAGEROTATE == message ? translation.apply("EM_GETPAGEROTATE", "Rich Edit", "Get Page Rotate") : true))
            return "";
          #endif

          #ifdef EM_GETPARAFORMAT
            if (not (EM_GETPARAFORMAT == message ? translation.apply("EM_GETPARAFORMAT", "Rich Edit", "Get Paragraph Format") : true))
            return "";
          #endif

          #ifdef EM_GETPASSWORDCHAR
            if (not (EM_GETPASSWORDCHAR == message ? translation.apply("EM_GETPASSWORDCHAR", "Rich Edit", "Get Password Character") : true))
            return "";
          #endif

          #ifdef EM_GETPUNCTUATION
            if (not (EM_GETPUNCTUATION == message ? translation.apply("EM_GETPUNCTUATION", "Rich Edit", "Get Punctuation") : true))
            return "";
          #endif

          #ifdef EM_GETRECT
            if (not (EM_GETRECT == message ? translation.apply("EM_GETRECT", "Rich Edit", "Get Rectangle") : true))
            return "";
          #endif

          #ifdef EM_GETREDONAME
            if (not (EM_GETREDONAME == message ? translation.apply("EM_GETREDONAME", "Rich Edit", "Get Redo Name") : true))
            return "";
          #endif

          #ifdef EM_GETSCROLLPOS
            if (not (EM_GETSCROLLPOS == message ? translation.apply("EM_GETSCROLLPOS", "Rich Edit", "Get Scroll Position") : true))
            return "";
          #endif

          #ifdef EM_GETSEL
            if (not (EM_GETSEL == message ? translation.apply("EM_GETSEL", "Rich Edit", "Get Selection") : true))
            return "";
          #endif

          #ifdef EM_GETSELTEXT
            if (not (EM_GETSELTEXT == message ? translation.apply("EM_GETSELTEXT", "Rich Edit", "Get Selection Text") : true))
            return "";
          #endif

          #ifdef EM_GETTEXTEX
            if (not (EM_GETTEXTEX == message ? translation.apply("EM_GETTEXTEX", "Rich Edit", "Get Text (Extended)") : true))
            return "";
          #endif

          #ifdef EM_GETTEXTLENGTHEX
            if (not (EM_GETTEXTLENGTHEX == message ? translation.apply("EM_GETTEXTLENGTHEX", "Rich Edit", "Get Text Length (Extended)") : true))
            return "";
          #endif

          #ifdef EM_GETTEXTMODE
            if (not (EM_GETTEXTMODE == message ? translation.apply("EM_GETTEXTMODE", "Rich Edit", "Get Text Mode") : true))
            return "";
          #endif

          #ifdef EM_GETTEXTRANGE
            if (not (EM_GETTEXTRANGE == message ? translation.apply("EM_GETTEXTRANGE", "Rich Edit", "Get Text Range") : true))
            return "";
          #endif

          #ifdef EM_GETTHUMB
            if (not (EM_GETTHUMB == message ? translation.apply("EM_GETTHUMB", "Rich Edit", "Get Thumb") : true))
            return "";
          #endif

          #ifdef EM_GETTYPOGRAPHYOPTIONS
            if (not (EM_GETTYPOGRAPHYOPTIONS == message ? translation.apply("EM_GETTYPOGRAPHYOPTIONS", "Rich Edit", "Get Typography Options") : true))
            return "";
          #endif

          #ifdef EM_GETUNDONAME
            if (not (EM_GETUNDONAME == message ? translation.apply("EM_GETUNDONAME", "Rich Edit", "Get Undo Name") : true))
            return "";
          #endif

          #ifdef EM_GETVIEWKIND
            if (not (EM_GETVIEWKIND == message ? translation.apply("EM_GETVIEWKIND", "Rich Edit", "Get View Kind") : true))
            return "";
          #endif

          #ifdef EM_GETWORDBREAKPROC
            if (not (EM_GETWORDBREAKPROC == message ? translation.apply("EM_GETWORDBREAKPROC", "Rich Edit", "Get Word Break Procedure") : true))
            return "";
          #endif

          #ifdef EM_GETWORDBREAKPROCEX
            if (not (EM_GETWORDBREAKPROCEX == message ? translation.apply("EM_GETWORDBREAKPROCEX", "Rich Edit", "Get Word Break Procedure (Extended)") : true))
            return "";
          #endif

          #ifdef EM_GETWORDWRAPMODE
            if (not (EM_GETWORDWRAPMODE == message ? translation.apply("EM_GETWORDWRAPMODE", "Rich Edit", "Get Word Wrap Mode") : true))
            return "";
          #endif

          #ifdef EM_GETZOOM
            if (not (EM_GETZOOM == message ? translation.apply("EM_GETZOOM", "Rich Edit", "Get Zoom") : true))
            return "";
          #endif

          #ifdef EM_HIDESELECTION
            if (not (EM_HIDESELECTION == message ? translation.apply("EM_HIDESELECTION", "Rich Edit", "Hide Selection") : true))
            return "";
          #endif

          #ifdef EM_ISIME
            if (not (EM_ISIME == message ? translation.apply("EM_ISIME", "Rich Edit", "Is IME (Input Method Encoding)") : true))
            return "";
          #endif

          #ifdef EM_LIMITTEXT
            if (not (EM_LIMITTEXT == message ? translation.apply("EM_LIMITTEXT", "Rich Edit", "Limit Text") : true))
            return "";
          #endif

          #ifdef EM_LINEFROMCHAR
            if (not (EM_LINEFROMCHAR == message ? translation.apply("EM_LINEFROMCHAR", "Rich Edit", "Line From Character") : true))
            return "";
          #endif

          #ifdef EM_LINEINDEX
            if (not (EM_LINEINDEX == message ? translation.apply("EM_LINEINDEX", "Rich Edit", "Line Index") : true))
            return "";
          #endif

          #ifdef EM_LINELENGTH
            if (not (EM_LINELENGTH == message ? translation.apply("EM_LINELENGTH", "Rich Edit", "Line Length") : true))
            return "";
          #endif

          #ifdef EM_LINESCROLL
            if (not (EM_LINESCROLL == message ? translation.apply("EM_LINESCROLL", "Rich Edit", "Line Scroll") : true))
            return "";
          #endif

          #ifdef EM_OUTLINE
            if (not (EM_OUTLINE == message ? translation.apply("EM_OUTLINE", "Rich Edit", "Line Outline") : true))
            return "";
          #endif

          #ifdef EM_PASTESPECIAL
            if (not (EM_PASTESPECIAL == message ? translation.apply("EM_PASTESPECIAL", "Rich Edit", "Line Paste Special") : true))
            return "";
          #endif

          #ifdef EM_POSFROMCHAR
            if (not (EM_POSFROMCHAR == message ? translation.apply("EM_POSFROMCHAR", "Rich Edit", "Line Position from Character") : true))
            return "";
          #endif

          #ifdef EM_RECONVERSION
            if (not (EM_RECONVERSION == message ? translation.apply("EM_RECONVERSION", "Rich Edit", "Reconversion") : true))
            return "";
          #endif

          #ifdef EM_REDO
            if (not (EM_REDO == message ? translation.apply("EM_REDO", "Rich Edit", "Redo") : true))
            return "";
          #endif

          #ifdef EM_REPLACESEL
            if (not (EM_REPLACESEL == message ? translation.apply("EM_REPLACESEL", "Rich Edit", "Replace Selection") : true))
            return "";
          #endif

          #ifdef EM_REQUESTRESIZE
            if (not (EM_REQUESTRESIZE == message ? translation.apply("EM_REQUESTRESIZE", "Rich Edit", "Request Resize") : true))
            return "";
          #endif

          #ifdef EM_SCROLL
            if (not (EM_SCROLL == message ? translation.apply("EM_SCROLL", "Rich Edit", "Scroll") : true))
            return "";
          #endif

          #ifdef EM_SCROLLCARET
            if (not (EM_SCROLLCARET == message ? translation.apply("EM_SCROLLCARET", "Rich Edit", "Scroll Caret") : true))
            return "";
          #endif

          #ifdef EM_SELECTIONTYPE
            if (not (EM_SELECTIONTYPE == message ? translation.apply("EM_SELECTIONTYPE", "Rich Edit", "Selection Type") : true))
            return "";
          #endif

          #ifdef EM_SETBIDIOPTIONS
            if (not (EM_SETBIDIOPTIONS == message ? translation.apply("EM_SETBIDIOPTIONS", "Rich Edit", "Set Bi-Directional Options") : true))
            return "";
          #endif

          #ifdef EM_SETBKGNDCOLOR
            if (not (EM_SETBKGNDCOLOR == message ? translation.apply("EM_SETBKGNDCOLOR", "Rich Edit", "Set Background Color") : true))
            return "";
          #endif

          #ifdef EM_SETCHARFORMAT
            if (not (EM_SETCHARFORMAT == message ? translation.apply("EM_SETCHARFORMAT", "Rich Edit", "Set Character Format") : true))
            return "";
          #endif

          #ifdef EM_SETCTFMODEBIAS
            if (not (EM_SETCTFMODEBIAS == message ? translation.apply("EM_SETCTFMODEBIAS", "Rich Edit", "Set CTF Mode Bias") : true))
            return "";
          #endif

          #ifdef EM_SETCTFOPENSTATUS
            if (not (EM_SETCTFOPENSTATUS == message ? translation.apply("EM_SETCTFOPENSTATUS", "Rich Edit", "Set CTF Open Status") : true))
            return "";
          #endif

          #ifdef EM_SETEDITSTYLE
            if (not (EM_SETEDITSTYLE == message ? translation.apply("EM_SETEDITSTYLE", "Rich Edit", "Set Edit Style") : true))
            return "";
          #endif

          #ifdef EM_SETEVENTMASK
            if (not (EM_SETEVENTMASK == message ? translation.apply("EM_SETEVENTMASK", "Rich Edit", "Set Event Mask") : true))
            return "";
          #endif

          #ifdef EM_SETFONT
            if (not (EM_SETFONT == message ? translation.apply("EM_SETFONT", "Rich Edit", "Set Font") : true))
            return "";
          #endif

          #ifdef EM_SETFONTSIZE
            if (not (EM_SETFONTSIZE == message ? translation.apply("EM_SETFONTSIZE", "Rich Edit", "Set Font Size") : true))
            return "";
          #endif

          #ifdef EM_SETHANDLE
            if (not (EM_SETHANDLE == message ? translation.apply("EM_SETHANDLE", "Rich Edit", "Set Handle") : true))
            return "";
          #endif

          #ifdef EM_SETHYPHENATEINFO
            if (not (EM_SETHYPHENATEINFO == message ? translation.apply("EM_SETHYPHENATEINFO", "Rich Edit", "Set Hyphenate Information") : true))
            return "";
          #endif

          #ifdef EM_SETIMECOLOR
            if (not (EM_SETIMECOLOR == message ? translation.apply("IPM_SETFOCUS", "Internet Protocol", "Set Focus") : true))
            return "";
          #endif

          #ifdef EM_SETIMEMODEBIAS
            if (not (EM_SETIMEMODEBIAS == message ? translation.apply("EM_SETIMEMODEBIAS", "Rich Edit", "Set IME (Input Method Encoding) Mode Bias") : true))
            return "";
          #endif

          #ifdef EM_SETIMEOPTIONS
            if (not (EM_SETIMEOPTIONS == message ? translation.apply("EM_SETIMEOPTIONS", "Rich Edit", "Set IME (Input Method Encoding) Options") : true))
            return "";
          #endif

          #ifdef EM_SETIMESTATUS
            if (not (EM_SETIMESTATUS == message ? translation.apply("EM_SETIMESTATUS", "Rich Edit", "Set Time Status") : true))
            return "";
          #endif

          #ifdef EM_SETLANGOPTIONS
            if (not (EM_SETLANGOPTIONS == message ? translation.apply("EM_SETLANGOPTIONS", "Rich Edit", "Set Language Options") : true))
            return "";
          #endif

          #ifdef EM_SETLIMITTEXT
            if (not (EM_SETLIMITTEXT == message ? translation.apply("EM_SETLIMITTEXT", "Rich Edit", "Set Limit Text") : true))
            return "";
          #endif

          #ifdef EM_SETMARGINS
            if (not (EM_SETMARGINS == message ? translation.apply("EM_SETMARGINS", "Rich Edit", "Set Margins") : true))
            return "";
          #endif

          #ifdef EM_SETMODIFY
            if (not (EM_SETMODIFY == message ? translation.apply("EM_SETMODIFY", "Rich Edit", "Set Modify") : true))
            return "";
          #endif

          #ifdef EM_SETOLECALLBACK
            if (not (EM_SETOLECALLBACK == message ? translation.apply("EM_SETOLECALLBACK", "Rich Edit", "Set OLE (Object Linking & Embedding) Callback") : true))
            return "";
          #endif

          #ifdef EM_SETOPTIONS
            if (not (EM_SETOPTIONS == message ? translation.apply("EM_SETOPTIONS", "Rich Edit", "Set Options") : true))
            return "";
          #endif

          #ifdef EM_SETPAGE
            if (not (EM_SETPAGE == message ? translation.apply("EM_SETPAGE", "Rich Edit", "Set Page") : true))
            return "";
          #endif

          #ifdef EM_SETPAGEROTATE
            if (not (EM_SETPAGEROTATE == message ? translation.apply("EM_SETPAGEROTATE", "Rich Edit", "Set Page Rotate") : true))
            return "";
          #endif

          #ifdef EM_SETPALETTE
            if (not (EM_SETPALETTE == message ? translation.apply("EM_SETPALETTE", "Rich Edit", "Set Palette") : true))
            return "";
          #endif

          #ifdef EM_SETPARAFORMAT
            if (not (EM_SETPARAFORMAT == message ? translation.apply("EM_SETPARAFORMAT", "Rich Edit", "Set Paragraph Format") : true))
            return "";
          #endif

          #ifdef EM_SETPASSWORDCHAR
            if (not (EM_SETPASSWORDCHAR == message ? translation.apply("EM_SETPASSWORDCHAR", "Rich Edit", "Set Password Character") : true))
            return "";
          #endif

          #ifdef EM_SETPUNCTUATION
            if (not (EM_SETPUNCTUATION == message ? translation.apply("IPM_CLEARADDRESS", "Internet Protocol", "Clear Address") : true))
            return "";
          #endif

          #ifdef EM_SETQUERYRTFOBJ
            if (not (EM_SETQUERYRTFOBJ == message ? translation.apply("EM_SETQUERYRTFOBJ", "Rich Edit", "Set Query Rich-Text Format Object") : true))
            return "";
          #endif

          #ifdef EM_SETREADONLY
            if (not (EM_SETREADONLY == message ? translation.apply("EM_SETREADONLY", "Rich Edit", "Set Read-Only") : true))
            return "";
          #endif

          #ifdef EM_SETRECT
            if (not (EM_SETRECT == message ? translation.apply("EM_SETRECT", "Rich Edit", "Set Rectangle") : true))
            return "";
          #endif

          #ifdef EM_SETRECTNP
            if (not (EM_SETRECTNP == message ? translation.apply("EM_SETRECTNP", "Rich Edit", "Set Rectangle New Position") : true))
            return "";
          #endif

          #ifdef EM_SETSCROLLPOS
            if (not (EM_SETSCROLLPOS == message ? translation.apply("EM_SETSCROLLPOS", "Rich Edit", "Set Scroll Position") : true))
            return "";
          #endif

          #ifdef EM_SETSEL
            if (not (EM_SETSEL == message ? translation.apply("EM_SETSEL", "Rich Edit", "Set Selection") : true))
            return "";
          #endif

          #ifdef EM_SETTABSTOPS
            if (not (EM_SETTABSTOPS == message ? translation.apply("EM_SETTABSTOPS", "Rich Edit", "Set Absolute Stops") : true))
            return "";
          #endif

          #ifdef EM_SETTARGETDEVICE
            if (not (EM_SETTARGETDEVICE == message ? translation.apply("EM_SETTARGETDEVICE", "Rich Edit", "Set Target Device") : true))
            return "";
          #endif

          #ifdef EM_SETTEXTEX
            if (not (EM_SETTEXTEX == message ? translation.apply("EM_SETTEXTEX", "Rich Edit", "Set Text (Extended)") : true))
            return "";
          #endif

          #ifdef EM_SETTEXTMODE
            if (not (EM_SETTEXTMODE == message ? translation.apply("EM_SETTEXTMODE", "Rich Edit", "Set Text Mode") : true))
            return "";
          #endif

          #ifdef EM_SETTYPOGRAPHYOPTIONS
            if (not (EM_SETTYPOGRAPHYOPTIONS == message ? translation.apply("EM_SETTYPOGRAPHYOPTIONS", "Rich Edit", "Set Typography Options") : true))
            return "";
          #endif

          #ifdef EM_SETUNDOLIMIT
            if (not (EM_SETUNDOLIMIT == message ? translation.apply("EM_SETUNDOLIMIT", "Rich Edit", "Set Undo Limit") : true))
            return "";
          #endif

          #ifdef EM_SETVIEWKIND
            if (not (EM_SETVIEWKIND == message ? translation.apply("EM_SETVIEWKIND", "Rich Edit", "Set View Kind") : true))
            return "";
          #endif

          #ifdef EM_SETWORDBREAK
            if (not (EM_SETWORDBREAK == message ? translation.apply("EM_SETWORDBREAK", "Rich Edit", "Set Word Break") : true))
            return "";
          #endif

          #ifdef EM_SETWORDBREAKPROC
            if (not (EM_SETWORDBREAKPROC == message ? translation.apply("EM_SETWORDBREAKPROC", "Rich Edit", "Set Word Break Procedure") : true))
            return "";
          #endif

          #ifdef EM_SETWORDBREAKPROCEX
            if (not (EM_SETWORDBREAKPROCEX == message ? translation.apply("EM_SETWORDBREAKPROCEX", "Rich Edit", "Set Word Break Procedure (Extended)") : true))
            return "";
          #endif

          #ifdef EM_SETWORDWRAPMODE
            if (not (EM_SETWORDWRAPMODE == message ? translation.apply("EM_SETWORDWRAPMODE", "Rich Edit", "Set Word Wrap Mode") : true))
            return "";
          #endif

          #ifdef EM_SETZOOM
            if (not (EM_SETZOOM == message ? translation.apply("EM_SETZOOM", "Rich Edit", "Set Zoom") : true))
            return "";
          #endif

          #ifdef EM_SHOWSCROLLBAR
            if (not (EM_SHOWSCROLLBAR == message ? translation.apply("EM_SHOWSCROLLBAR", "Rich Edit", "Show Scrollbar") : true))
            return "";
          #endif

          #ifdef EM_STOPGROUPTYPING
            if (not (EM_STOPGROUPTYPING == message ? translation.apply("EM_STOPGROUPTYPING", "Rich Edit", "Stop Group Typing") : true))
            return "";
          #endif

          #ifdef EM_STREAMIN
            if (not (EM_STREAMIN == message ? translation.apply("EM_STREAMIN", "Rich Edit", "Stream Input") : true))
            return "";
          #endif

          #ifdef EM_STREAMOUT
            if (not (EM_STREAMOUT == message ? translation.apply("EM_STREAMOUT", "Rich Edit", "Stream Output") : true))
            return "";
          #endif

          #ifdef EM_UNDO
            if (not (EM_UNDO == message ? translation.apply("EM_UNDO", "Rich Edit", "Undo") : true))
            return "";
          #endif

          #ifdef FM_GETDRIVEINFOA
            if (not (FM_GETDRIVEINFOA == message ? translation.apply("FM_GETDRIVEINFOA", "File Manager", "Get Drive Information") : true))
            return "";
          #endif

          #ifdef FM_GETDRIVEINFOW
            if (not (FM_GETDRIVEINFOW == message ? translation.apply("FM_GETDRIVEINFOW", "File Manager", "Get Drive Information") : true))
            return "";
          #endif

          #ifdef FM_GETFILESELA
            if (not (FM_GETFILESELA == message ? translation.apply("FM_GETFILESELA", "File Manager", "Get File Selection") : true))
            return "";
          #endif

          #ifdef FM_GETFILESELLFNA
            if (not (FM_GETFILESELLFNA == message ? translation.apply("FM_GETFILESELLFNA", "File Manager", "Get File Selection Long File Name") : true))
            return "";
          #endif

          #ifdef FM_GETFILESELLFNW
            if (not (FM_GETFILESELLFNW == message ? translation.apply("FM_GETFILESELLFNW", "File Manager", "Get File Selection Long File Name") : true))
            return "";
          #endif

          #ifdef FM_GETFILESELW
            if (not (FM_GETFILESELW == message ? translation.apply("FM_GETFILESELW", "File Manager", "Get File Selection") : true))
            return "";
          #endif

          #ifdef FM_GETFOCUS
            if (not (FM_GETFOCUS == message ? translation.apply("FM_GETFOCUS", "File Manager", "Get Focus") : true))
            return "";
          #endif

          #ifdef FM_GETSELCOUNT
            if (not (FM_GETSELCOUNT == message ? translation.apply("FM_GETSELCOUNT", "File Manager", "Get Selection Count") : true))
            return "";
          #endif

          #ifdef FM_GETSELCOUNTLFN
            if (not (FM_GETSELCOUNTLFN == message ? translation.apply("FM_GETSELCOUNTLFN", "File Manager", "Get Selection Count Long File Name") : true))
            return "";
          #endif

          #ifdef FM_REFRESH_WINDOWS
            if (not (FM_REFRESH_WINDOWS == message ? translation.apply("FM_REFRESH_WINDOWS", "File Manager", "Refresh Windows") : true))
            return "";
          #endif

          #ifdef FM_RELOAD_EXTENSIONS
            if (not (FM_RELOAD_EXTENSIONS == message ? translation.apply("FM_RELOAD_EXTENSIONS", "File Manager", "Reload Extensions") : true))
            return "";
          #endif

          #ifdef HKM_GETHOTKEY
            if (not (HKM_GETHOTKEY == message ? translation.apply("HKM_GETHOTKEY", "Hotkey", "Get Hotkey") : true))
            return "";
          #endif

          #ifdef HKM_SETHOTKEY
            if (not (HKM_SETHOTKEY == message ? translation.apply("HKM_SETHOTKEY", "Hotkey", "Set Hotkey") : true))
            return "";
          #endif

          #ifdef HKM_SETRULES
            if (not (HKM_SETRULES == message ? translation.apply("HKM_SETRULES", "Hotkey", "Set Rules") : true))
            return "";
          #endif

          #ifdef IE_DOCOMMAND
            if (not (IE_DOCOMMAND == message ? translation.apply("IE_DOCOMMAND", "Ink Edit", "Do Command") : true))
            return "";
          #endif

          #ifdef IE_GETAPPDATA
            if (not (IE_GETAPPDATA == message ? translation.apply("IE_GETAPPDATA", "Ink Edit", "Get Application Data") : true))
            return "";
          #endif

          #ifdef IE_GETBKGND
            if (not (IE_GETBKGND == message ? translation.apply("IE_GETBKGND", "Ink Edit", "Get Background") : true))
            return "";
          #endif

          #ifdef IE_GETCOMMAND
            if (not (IE_GETCOMMAND == message ? translation.apply("IE_GETCOMMAND", "Ink Edit", "Get Command") : true))
            return "";
          #endif

          #ifdef IE_GETCOUNT
            if (not (IE_GETCOUNT == message ? translation.apply("IE_GETCOUNT", "Ink Edit", "Get Count") : true))
            return "";
          #endif

          #ifdef IE_GETDRAWOPTS
            if (not (IE_GETDRAWOPTS == message ? translation.apply("IE_GETDRAWOPTS", "Ink Edit", "Get Draw Options") : true))
            return "";
          #endif

          #ifdef IE_GETERASERTIP
            if (not (IE_GETERASERTIP == message ? translation.apply("IE_GETERASERTIP", "Ink Edit", "Get Eraser Tip") : true))
            return "";
          #endif

          #ifdef IE_GETFORMAT
            if (not (IE_GETFORMAT == message ? translation.apply("IE_GETFORMAT", "Ink Edit", "Get Format") : true))
            return "";
          #endif

          #ifdef IE_GETGESTURE
            if (not (IE_GETGESTURE == message ? translation.apply("IE_GETGESTURE", "Ink Edit", "Get Gesture") : true))
            return "";
          #endif

          #ifdef IE_GETGRIDORIGIN
            if (not (IE_GETGRIDORIGIN == message ? translation.apply("IE_GETGRIDORIGIN", "Ink Edit", "Get Grid Origin") : true))
            return "";
          #endif

          #ifdef IE_GETGRIDPEN
            if (not (IE_GETGRIDPEN == message ? translation.apply("IE_GETGRIDPEN", "Ink Edit", "Get Grid Pen") : true))
            return "";
          #endif

          #ifdef IE_GETGRIDSIZE
            if (not (IE_GETGRIDSIZE == message ? translation.apply("IE_GETGRIDSIZE", "Ink Edit", "Get Grid Size") : true))
            return "";
          #endif

          #ifdef IE_GETINK
            if (not (IE_GETINK == message ? translation.apply("IE_GETINK", "Ink Edit", "Get Ink") : true))
            return "";
          #endif

          #ifdef IE_GETINKINPUT
            if (not (IE_GETINKINPUT == message ? translation.apply("IE_GETINKINPUT", "Ink Edit", "Get Ink Input") : true))
            return "";
          #endif

          #ifdef IE_GETMENU
            if (not (IE_GETMENU == message ? translation.apply("IE_GETMENU", "Ink Edit", "Get Menu") : true))
            return "";
          #endif

          #ifdef IE_GETMODE
            if (not (IE_GETMODE == message ? translation.apply("IE_GETMODE", "Ink Edit", "Get Mode") : true))
            return "";
          #endif

          #ifdef IE_GETNOTIFY
            if (not (IE_GETNOTIFY == message ? translation.apply("IE_GETNOTIFY", "Ink Edit", "Get Notify") : true))
            return "";
          #endif

          #ifdef IE_GETPAINTDC
            if (not (IE_GETPAINTDC == message ? translation.apply("IE_GETPAINTDC", "Ink Edit", "Get Paint Device Context") : true))
            return "";
          #endif

          #ifdef IE_GETPDEVENT
            if (not (IE_GETPDEVENT == message ? translation.apply("IE_GETPDEVENT", "Ink Edit", "Get PD Event") : true))
            return "";
          #endif

          #ifdef IE_GETPENTIP
            if (not (IE_GETPENTIP == message ? translation.apply("IE_GETPENTIP", "Ink Edit", "Get Pen Tip") : true))
            return "";
          #endif

          #ifdef IE_GETRECOG
            if (not (IE_GETRECOG == message ? translation.apply("IE_GETRECOG", "Ink Edit", "Get Recognition") : true))
            return "";
          #endif

          #ifdef IE_GETSECURITY
            if (not (IE_GETSECURITY == message ? translation.apply("IE_GETSECURITY", "Ink Edit", "Get Security") : true))
            return "";
          #endif

          #ifdef IE_GETSEL
            if (not (IE_GETSEL == message ? translation.apply("IE_GETSEL", "Ink Edit", "Get Selection") : true))
            return "";
          #endif

          #ifdef IE_GETSELCOUNT
            if (not (IE_GETSELCOUNT == message ? translation.apply("IE_GETSELCOUNT", "Ink Edit", "Get Selection Count") : true))
            return "";
          #endif

          #ifdef IE_GETSELITEMS
            if (not (IE_GETSELITEMS == message ? translation.apply("IE_GETSELITEMS", "Ink Edit", "Get Selection Items") : true))
            return "";
          #endif

          #ifdef IE_GETSTYLE
            if (not (IE_GETSTYLE == message ? translation.apply("IE_GETSTYLE", "Ink Edit", "Get Style") : true))
            return "";
          #endif

          #ifdef IE_MSGFIRST
            if (not (IE_MSGFIRST == message ? translation.apply("IE_MSGFIRST", "Ink Edit", "Message 1st") : true))
            return "";
          #endif

          #ifdef IE_SETAPPDATA
            if (not (IE_SETAPPDATA == message ? translation.apply("IE_SETAPPDATA", "Ink Edit", "Set Application Data") : true))
            return "";
          #endif

          #ifdef IE_SETBKGND
            if (not (IE_SETBKGND == message ? translation.apply("IE_SETBKGND", "Ink Edit", "Set Background") : true))
            return "";
          #endif

          #ifdef IE_SETDRAWOPTS
            if (not (IE_SETDRAWOPTS == message ? translation.apply("IE_SETDRAWOPTS", "Ink Edit", "Set Draw Options") : true))
            return "";
          #endif

          #ifdef IE_SETERASERTIP
            if (not (IE_SETERASERTIP == message ? translation.apply("IE_SETERASERTIP", "Ink Edit", "Set Eraser Tip") : true))
            return "";
          #endif

          #ifdef IE_SETFORMAT
            if (not (IE_SETFORMAT == message ? translation.apply("IE_SETFORMAT", "Ink Edit", "Set Format") : true))
            return "";
          #endif

          #ifdef IE_SETGRIDORIGIN
            if (not (IE_SETGRIDORIGIN == message ? translation.apply("IE_SETGRIDORIGIN", "Ink Edit", "Set Grid Origin") : true))
            return "";
          #endif

          #ifdef IE_SETGRIDPEN
            if (not (IE_SETGRIDPEN == message ? translation.apply("IE_SETGRIDPEN", "Ink Edit", "Set Grid Pen") : true))
            return "";
          #endif

          #ifdef IE_SETGRIDSIZE
            if (not (IE_SETGRIDSIZE == message ? translation.apply("IE_SETGRIDSIZE", "Ink Edit", "Set Grid Size") : true))
            return "";
          #endif

          #ifdef IE_SETINK
            if (not (IE_SETINK == message ? translation.apply("IE_SETINK", "Ink Edit", "Set Ink") : true))
            return "";
          #endif

          #ifdef IE_SETINKINPUT
            if (not (IE_SETINKINPUT == message ? translation.apply("IE_SETINKINPUT", "Ink Edit", "Set Ink Input") : true))
            return "";
          #endif

          #ifdef IE_SETMODE
            if (not (IE_SETMODE == message ? translation.apply("IE_SETMODE", "Ink Edit", "Set Mode") : true))
            return "";
          #endif

          #ifdef IE_SETNOTIFY
            if (not (IE_SETNOTIFY == message ? translation.apply("IE_SETNOTIFY", "Ink Edit", "Set Notify") : true))
            return "";
          #endif

          #ifdef IE_SETPENTIP
            if (not (IE_SETPENTIP == message ? translation.apply("IE_SETPENTIP", "Ink Edit", "Set Pen Tip") : true))
            return "";
          #endif

          #ifdef IE_SETRECOG
            if (not (IE_SETRECOG == message ? translation.apply("IE_SETRECOG", "Ink Edit", "Set Recognition") : true))
            return "";
          #endif

          #ifdef IE_SETSECURITY
            if (not (IE_SETSECURITY == message ? translation.apply("IE_SETSECURITY", "Ink Edit", "Set Security") : true))
            return "";
          #endif

          #ifdef IE_SETSEL
            if (not (IE_SETSEL == message ? translation.apply("IE_SETSEL", "Ink Edit", "Set Selection") : true))
            return "";
          #endif

          #ifdef IPM_CLEARADDRESS
            if (not (IPM_CLEARADDRESS == message ? translation.apply("EM_SETPUNCTUATION", "Rich Edit", "Set Punctuation") : true))
            return "";
          #endif

          #ifdef IPM_GETADDRESS
            if (not (IPM_GETADDRESS == message ? translation.apply("IPM_GETADDRESS", "Internet Protocol", "Get Address") : true))
            return "";
          #endif

          #ifdef IPM_ISBLANK
            if (not (IPM_ISBLANK == message ? translation.apply("IPM_ISBLANK", "Internet Protocol", "Is Blank") : true))
            return "";
          #endif

          #ifdef IPM_SETADDRESS
            if (not (IPM_SETADDRESS == message ? translation.apply("IPM_SETADDRESS", "Internet Protocol", "Set Address") : true))
            return "";
          #endif

          #ifdef IPM_SETFOCUS
            if (not (IPM_SETFOCUS == message ? translation.apply("PSM_CHANGED", "Prop Sheet", "Changed") : true))
            return "";
          #endif

          #ifdef IPM_SETRANGE
            if (not (IPM_SETRANGE == message ? translation.apply("IPM_SETRANGE", "Internet Protocol", "Set Range") : true))
            return "";
          #endif

          #ifdef LVM_ARRANGE
            if (not (LVM_ARRANGE == message ? translation.apply("LVM_ARRANGE", "List View", "Arrange") : true))
            return "";
          #endif

          #ifdef LVM_CANCELEDITLABEL
            if (not (LVM_CANCELEDITLABEL == message ? translation.apply("LVM_CANCELEDITLABEL", "List View", "Cancel Edit Label") : true))
            return "";
          #endif

          #ifdef LVM_CREATEDRAGIMAGE
            if (not (LVM_CREATEDRAGIMAGE == message ? translation.apply("LVM_CREATEDRAGIMAGE", "List View", "Create Drag Image") : true))
            return "";
          #endif

          #ifdef LVM_DELETEALLITEMS
            if (not (LVM_DELETEALLITEMS == message ? translation.apply("LVM_DELETEALLITEMS", "List View", "Delete All Items") : true))
            return "";
          #endif

          #ifdef LVM_DELETECOLUMN
            if (not (LVM_DELETECOLUMN == message ? translation.apply("LVM_DELETECOLUMN", "List View", "Delete Column") : true))
            return "";
          #endif

          #ifdef LVM_DELETEITEM
            if (not (LVM_DELETEITEM == message ? translation.apply("LVM_DELETEITEM", "List View", "Delete Item") : true))
            return "";
          #endif

          #ifdef LVM_EDITLABELA
            if (not (LVM_EDITLABELA == message ? translation.apply("LVM_EDITLABELA", "List View", "Edit Label") : true))
            return "";
          #endif

          #ifdef LVM_EDITLABELW
            if (not (LVM_EDITLABELW == message ? translation.apply("LVM_EDITLABELW", "List View", "Edit Label") : true))
            return "";
          #endif

          #ifdef LVM_ENABLEGROUPVIEW
            if (not (LVM_ENABLEGROUPVIEW == message ? translation.apply("LVM_ENABLEGROUPVIEW", "List View", "Enable Group View") : true))
            return "";
          #endif

          #ifdef LVM_ENSUREVISIBLE
            if (not (LVM_ENSUREVISIBLE == message ? translation.apply("LVM_ENSUREVISIBLE", "List View", "Ensure Visible") : true))
            return "";
          #endif

          #ifdef LVM_FINDITEMA
            if (not (LVM_FINDITEMA == message ? translation.apply("LVM_FINDITEMA", "List View", "Find Item") : true))
            return "";
          #endif

          #ifdef LVM_FINDITEMW
            if (not (LVM_FINDITEMW == message ? translation.apply("LVM_FINDITEMW", "List View", "Find Item") : true))
            return "";
          #endif

          #ifdef LVM_FIRST
            if (not (LVM_FIRST == message ? translation.apply("LVM_FIRST", "List View", "1st") : true))
            return "";
          #endif

          #ifdef LVM_GETBKCOLOR
            if (not (LVM_GETBKCOLOR == message ? translation.apply("LVM_GETBKCOLOR", "List View", "Get Background Color") : true))
            return "";
          #endif

          #ifdef LVM_GETBKIMAGEA
            if (not (LVM_GETBKIMAGEA == message ? translation.apply("LVM_GETBKIMAGEA", "List View", "Get Background Image") : true))
            return "";
          #endif

          #ifdef LVM_GETBKIMAGEW
            if (not (LVM_GETBKIMAGEW == message ? translation.apply("LVM_GETBKIMAGEW", "List View", "Get Background Image") : true))
            return "";
          #endif

          #ifdef LVM_GETCALLBACKMASK
            if (not (LVM_GETCALLBACKMASK == message ? translation.apply("LVM_GETCALLBACKMASK", "List View", "Get Call Back Mask") : true))
            return "";
          #endif

          #ifdef LVM_GETCOLUMNA
            if (not (LVM_GETCOLUMNA == message ? translation.apply("LVM_GETCOLUMNA", "List View", "Get Column") : true))
            return "";
          #endif

          #ifdef LVM_GETCOLUMNORDERARRAY
            if (not (LVM_GETCOLUMNORDERARRAY == message ? translation.apply("LVM_GETCOLUMNORDERARRAY", "List View", "Get Column Order Array") : true))
            return "";
          #endif

          #ifdef LVM_GETCOLUMNW
            if (not (LVM_GETCOLUMNW == message ? translation.apply("LVM_GETCOLUMNW", "List View", "Get Column") : true))
            return "";
          #endif

          #ifdef LVM_GETCOLUMNWIDTH
            if (not (LVM_GETCOLUMNWIDTH == message ? translation.apply("LVM_GETCOLUMNWIDTH", "List View", "Get Column Width") : true))
            return "";
          #endif

          #ifdef LVM_GETCOUNTPERPAGE
            if (not (LVM_GETCOUNTPERPAGE == message ? translation.apply("LVM_GETCOUNTPERPAGE", "List View", "Get Count per Page") : true))
            return "";
          #endif

          #ifdef LVM_GETEDITCONTROL
            if (not (LVM_GETEDITCONTROL == message ? translation.apply("LVM_GETEDITCONTROL", "List View", "Get Edit Control") : true))
            return "";
          #endif

          #ifdef LVM_GETEXTENDEDLISTVIEWSTYLE
            if (not (LVM_GETEXTENDEDLISTVIEWSTYLE == message ? translation.apply("LVM_GETEXTENDEDLISTVIEWSTYLE", "List View", "Get Extended List View Style") : true))
            return "";
          #endif

          #ifdef LVM_GETGROUPINFO
            if (not (LVM_GETGROUPINFO == message ? translation.apply("LVM_GETGROUPINFO", "List View", "Get Group Information") : true))
            return "";
          #endif

          #ifdef LVM_GETGROUPMETRICS
            if (not (LVM_GETGROUPMETRICS == message ? translation.apply("LVM_GETGROUPMETRICS", "List View", "Get Group Metrics") : true))
            return "";
          #endif

          #ifdef LVM_GETHEADER
            if (not (LVM_GETHEADER == message ? translation.apply("LVM_GETHEADER", "List View", "Get Header") : true))
            return "";
          #endif

          #ifdef LVM_GETHOTCURSOR
            if (not (LVM_GETHOTCURSOR == message ? translation.apply("LVM_GETHOTCURSOR", "List View", "Get Hot Cursor") : true))
            return "";
          #endif

          #ifdef LVM_GETHOTITEM
            if (not (LVM_GETHOTITEM == message ? translation.apply("LVM_GETHOTITEM", "List View", "Get Hover Time") : true))
            return "";
          #endif

          #ifdef LVM_GETHOVERTIME
            if (not (LVM_GETHOVERTIME == message ? translation.apply("LVM_GETHOVERTIME", "List View", "Get Image List") : true))
            return "";
          #endif

          #ifdef LVM_GETIMAGELIST
            if (not (LVM_GETIMAGELIST == message ? translation.apply("LVM_GETIMAGELIST", "List View", "Get Image List") : true))
            return "";
          #endif

          #ifdef LVM_GETINSERTMARK
            if (not (LVM_GETINSERTMARK == message ? translation.apply("LVM_GETINSERTMARK", "List View", "Get Insert Mark") : true))
            return "";
          #endif

          #ifdef LVM_GETINSERTMARKCOLOR
            if (not (LVM_GETINSERTMARKCOLOR == message ? translation.apply("LVM_GETINSERTMARKCOLOR", "List View", "Get Insert Mark Color") : true))
            return "";
          #endif

          #ifdef LVM_GETINSERTMARKRECT
            if (not (LVM_GETINSERTMARKRECT == message ? translation.apply("LVM_GETINSERTMARKRECT", "List View", "Get Insert Mark Rectangle") : true))
            return "";
          #endif

          #ifdef LVM_GETISEARCHSTRINGA
            if (not (LVM_GETISEARCHSTRINGA == message ? translation.apply("LVM_GETISEARCHSTRINGA", "List View", "Get Incremental Search String") : true))
            return "";
          #endif

          #ifdef LVM_GETISEARCHSTRINGW
            if (not (LVM_GETISEARCHSTRINGW == message ? translation.apply("LVM_GETISEARCHSTRINGW", "List View", "Get Incremental Search String") : true))
            return "";
          #endif

          #ifdef LVM_GETITEMA
            if (not (LVM_GETITEMA == message ? translation.apply("LVM_GETITEMA", "List View", "Get Item") : true))
            return "";
          #endif

          #ifdef LVM_GETITEMCOUNT
            if (not (LVM_GETITEMCOUNT == message ? translation.apply("LVM_GETITEMCOUNT", "List View", "Get Item Count") : true))
            return "";
          #endif

          #ifdef LVM_GETITEMPOSITION
            if (not (LVM_GETITEMPOSITION == message ? translation.apply("LVM_GETITEMPOSITION", "List View", "Get Item Position") : true))
            return "";
          #endif

          #ifdef LVM_GETITEMRECT
            if (not (LVM_GETITEMRECT == message ? translation.apply("LVM_GETITEMRECT", "List View", "Get Item Rectangle") : true))
            return "";
          #endif

          #ifdef LVM_GETITEMSPACING
            if (not (LVM_GETITEMSPACING == message ? translation.apply("LVM_GETITEMSPACING", "List View", "Get Item Spacing") : true))
            return "";
          #endif

          #ifdef LVM_GETITEMSTATE
            if (not (LVM_GETITEMSTATE == message ? translation.apply("LVM_GETITEMSTATE", "List View", "Get Item State") : true))
            return "";
          #endif

          #ifdef LVM_GETITEMTEXTA
            if (not (LVM_GETITEMTEXTA == message ? translation.apply("LVM_GETITEMTEXTA", "List View", "Get Item Text") : true))
            return "";
          #endif

          #ifdef LVM_GETITEMTEXTW
            if (not (LVM_GETITEMTEXTW == message ? translation.apply("LVM_GETITEMTEXTW", "List View", "Get Item Text") : true))
            return "";
          #endif

          #ifdef LVM_GETITEMW
            if (not (LVM_GETITEMW == message ? translation.apply("LVM_GETITEMW", "List View", "Get Item") : true))
            return "";
          #endif

          #ifdef LVM_GETNEXTITEM
            if (not (LVM_GETNEXTITEM == message ? translation.apply("LVM_GETNEXTITEM", "List View", "Get Next Item") : true))
            return "";
          #endif

          #ifdef LVM_GETNUMBEROFWORKAREAS
            if (not (LVM_GETNUMBEROFWORKAREAS == message ? translation.apply("LVM_GETNUMBEROFWORKAREAS", "List View", "Get Number of Work Areas") : true))
            return "";
          #endif

          #ifdef LVM_GETORIGIN
            if (not (LVM_GETORIGIN == message ? translation.apply("LVM_GETORIGIN", "List View", "Get Origin") : true))
            return "";
          #endif

          #ifdef LVM_GETOUTLINECOLOR
            if (not (LVM_GETOUTLINECOLOR == message ? translation.apply("LVM_GETOUTLINECOLOR", "List View", "Get Outline Color") : true))
            return "";
          #endif

          #ifdef LVM_GETSELECTEDCOLUMN
            if (not (LVM_GETSELECTEDCOLUMN == message ? translation.apply("LVM_GETSELECTEDCOLUMN", "List View", "Get Selected Column") : true))
            return "";
          #endif

          #ifdef LVM_GETSELECTEDCOUNT
            if (not (LVM_GETSELECTEDCOUNT == message ? translation.apply("LVM_GETSELECTEDCOUNT", "List View", "Get Selected Count") : true))
            return "";
          #endif

          #ifdef LVM_GETSELECTIONMARK
            if (not (LVM_GETSELECTIONMARK == message ? translation.apply("LVM_GETSELECTIONMARK", "List View", "Get Selection Mark") : true))
            return "";
          #endif

          #ifdef LVM_GETSTRINGWIDTHA
            if (not (LVM_GETSTRINGWIDTHA == message ? translation.apply("LVM_GETSTRINGWIDTHA", "List View", "Get String Width") : true))
            return "";
          #endif

          #ifdef LVM_GETSTRINGWIDTHW
            if (not (LVM_GETSTRINGWIDTHW == message ? translation.apply("LVM_GETSTRINGWIDTHW", "List View", "Get String Width") : true))
            return "";
          #endif

          #ifdef LVM_GETSUBITEMRECT
            if (not (LVM_GETSUBITEMRECT == message ? translation.apply("LVM_GETSUBITEMRECT", "List View", "Get Sub-Item Rectangle") : true))
            return "";
          #endif

          #ifdef LVM_GETTEXTBKCOLOR
            if (not (LVM_GETTEXTBKCOLOR == message ? translation.apply("LVM_GETTEXTBKCOLOR", "List View", "Get Text Background Color") : true))
            return "";
          #endif

          #ifdef LVM_GETTEXTCOLOR
            if (not (LVM_GETTEXTCOLOR == message ? translation.apply("LVM_GETTEXTCOLOR", "List View", "Get Text Color") : true))
            return "";
          #endif

          #ifdef LVM_GETTILEINFO
            if (not (LVM_GETTILEINFO == message ? translation.apply("LVM_GETTILEINFO", "List View", "Get Tile Information") : true))
            return "";
          #endif

          #ifdef LVM_GETTILEVIEWINFO
            if (not (LVM_GETTILEVIEWINFO == message ? translation.apply("LVM_GETTILEVIEWINFO", "List View", "Get Tile View Information") : true))
            return "";
          #endif

          #ifdef LVM_GETTOOLTIPS
            if (not (LVM_GETTOOLTIPS == message ? translation.apply("LVM_GETTOOLTIPS", "List View", "Get Tooltips") : true))
            return "";
          #endif

          #ifdef LVM_GETTOPINDEX
            if (not (LVM_GETTOPINDEX == message ? translation.apply("LVM_GETTOPINDEX", "List View", "Get Top Index") : true))
            return "";
          #endif

          #ifdef LVM_GETUNICODEFORMAT
            if (not (LVM_GETUNICODEFORMAT == message ? translation.apply("LVM_GETUNICODEFORMAT", "List View", "Get Unicode Format") : true))
            return "";
          #endif

          #ifdef LVM_GETVIEW
            if (not (LVM_GETVIEW == message ? translation.apply("LVM_GETVIEW", "List View", "Get View") : true))
            return "";
          #endif

          #ifdef LVM_GETVIEWRECT
            if (not (LVM_GETVIEWRECT == message ? translation.apply("LVM_GETVIEWRECT", "List View", "Get View Rectangle") : true))
            return "";
          #endif

          #ifdef LVM_GETWORKAREAS
            if (not (LVM_GETWORKAREAS == message ? translation.apply("LVM_GETWORKAREAS", "List View", "Get Work Areas") : true))
            return "";
          #endif

          #ifdef LVM_HASGROUP
            if (not (LVM_HASGROUP == message ? translation.apply("LVM_HASGROUP", "List View", "Has Group") : true))
            return "";
          #endif

          #ifdef LVM_HITTEST
            if (not (LVM_HITTEST == message ? translation.apply("LVM_HITTEST", "List View", "Hit Test") : true))
            return "";
          #endif

          #ifdef LVM_INSERTCOLUMNA
            if (not (LVM_INSERTCOLUMNA == message ? translation.apply("LVM_INSERTCOLUMNA", "List View", "Insert Column") : true))
            return "";
          #endif

          #ifdef LVM_INSERTCOLUMNW
            if (not (LVM_INSERTCOLUMNW == message ? translation.apply("LVM_INSERTCOLUMNW", "List View", "Insert Column") : true))
            return "";
          #endif

          #ifdef LVM_INSERTGROUP
            if (not (LVM_INSERTGROUP == message ? translation.apply("LVM_INSERTGROUP", "List View", "Insert Group") : true))
            return "";
          #endif

          #ifdef LVM_INSERTGROUPSORTED
            if (not (LVM_INSERTGROUPSORTED == message ? translation.apply("LVM_INSERTGROUPSORTED", "List View", "Insert Group Sorted") : true))
            return "";
          #endif

          #ifdef LVM_INSERTITEMA
            if (not (LVM_INSERTITEMA == message ? translation.apply("LVM_INSERTITEMA", "List View", "Insert Item") : true))
            return "";
          #endif

          #ifdef LVM_INSERTITEMW
            if (not (LVM_INSERTITEMW == message ? translation.apply("LVM_INSERTITEMW", "List View", "Insert Item") : true))
            return "";
          #endif

          #ifdef LVM_INSERTMARKHITTEST
            if (not (LVM_INSERTMARKHITTEST == message ? translation.apply("LVM_INSERTMARKHITTEST", "List View", "Insert Mark Hit Test") : true))
            return "";
          #endif

          #ifdef LVM_ISGROUPVIEWENABLED
            if (not (LVM_ISGROUPVIEWENABLED == message ? translation.apply("LVM_ISGROUPVIEWENABLED", "List View", "Is Group View Enabled") : true))
            return "";
          #endif

          #ifdef LVM_ISITEMVISIBLE
            if (not (LVM_ISITEMVISIBLE == message ? translation.apply("LVM_ISITEMVISIBLE", "List View", "Is Item Visible") : true))
            return "";
          #endif

          #ifdef LVM_MAPIDTOINDEX
            if (not (LVM_MAPIDTOINDEX == message ? translation.apply("LVM_MAPIDTOINDEX", "List View", "Map Identity to Index") : true))
            return "";
          #endif

          #ifdef LVM_MAPINDEXTOID
            if (not (LVM_MAPINDEXTOID == message ? translation.apply("LVM_MAPINDEXTOID", "List View", "Map Index to Identity") : true))
            return "";
          #endif

          #ifdef LVM_MOVEGROUP
            if (not (LVM_MOVEGROUP == message ? translation.apply("LVM_MOVEGROUP", "List View", "Move Group") : true))
            return "";
          #endif

          #ifdef LVM_MOVEITEMTOGROUP
            if (not (LVM_MOVEITEMTOGROUP == message ? translation.apply("LVM_MOVEITEMTOGROUP", "List View", "Move Item to Group") : true))
            return "";
          #endif

          #ifdef LVM_REDRAWITEMS
            if (not (LVM_REDRAWITEMS == message ? translation.apply("LVM_REDRAWITEMS", "List View", "Redraw Items") : true))
            return "";
          #endif

          #ifdef LVM_REMOVEALLGROUPS
            if (not (LVM_REMOVEALLGROUPS == message ? translation.apply("LVM_REMOVEALLGROUPS", "List View", "Remove all Groups") : true))
            return "";
          #endif

          #ifdef LVM_REMOVEGROUP
            if (not (LVM_REMOVEGROUP == message ? translation.apply("LVM_REMOVEGROUP", "List View", "Remove Group") : true))
            return "";
          #endif

          #ifdef LVM_SCROLL
            if (not (LVM_SCROLL == message ? translation.apply("LVM_SCROLL", "List View", "Scroll") : true))
            return "";
          #endif

          #ifdef LVM_SETBKCOLOR
            if (not (LVM_SETBKCOLOR == message ? translation.apply("LVM_SETBKCOLOR", "List View", "Set Background Color") : true))
            return "";
          #endif

          #ifdef LVM_SETBKIMAGEA
            if (not (LVM_SETBKIMAGEA == message ? translation.apply("LVM_SETBKIMAGEA", "List View", "Set Background Image") : true))
            return "";
          #endif

          #ifdef LVM_SETCALLBACKMASK
            if (not (LVM_SETCALLBACKMASK == message ? translation.apply("LVM_SETCALLBACKMASK", "List View", "Set Callback Mask") : true))
            return "";
          #endif

          #ifdef LVM_SETCOLUMNA
            if (not (LVM_SETCOLUMNA == message ? translation.apply("LVM_SETCOLUMNA", "List View", "Set Column") : true))
            return "";
          #endif

          #ifdef LVM_SETCOLUMNORDERARRAY
            if (not (LVM_SETCOLUMNORDERARRAY == message ? translation.apply("LVM_SETCOLUMNORDERARRAY", "List View", "Set Column Order Array") : true))
            return "";
          #endif

          #ifdef LVM_SETCOLUMNW
            if (not (LVM_SETCOLUMNW == message ? translation.apply("LVM_SETCOLUMNW", "List View", "Set Column") : true))
            return "";
          #endif

          #ifdef LVM_SETCOLUMNWIDTH
            if (not (LVM_SETCOLUMNWIDTH == message ? translation.apply("LVM_SETCOLUMNWIDTH", "List View", "Set Column Width") : true))
            return "";
          #endif

          #ifdef LVM_SETEXTENDEDLISTVIEWSTYLE
            if (not (LVM_SETEXTENDEDLISTVIEWSTYLE == message ? translation.apply("LVM_SETEXTENDEDLISTVIEWSTYLE", "List View", "Set Extended List View Style") : true))
            return "";
          #endif

          #ifdef LVM_SETGROUPINFO
            if (not (LVM_SETGROUPINFO == message ? translation.apply("LVM_SETGROUPINFO", "List View", "Set Group Information") : true))
            return "";
          #endif

          #ifdef LVM_SETGROUPMETRICS
            if (not (LVM_SETGROUPMETRICS == message ? translation.apply("LVM_SETGROUPMETRICS", "List View", "Set Group Metrics") : true))
            return "";
          #endif

          #ifdef LVM_SETHOTCURSOR
            if (not (LVM_SETHOTCURSOR == message ? translation.apply("LVM_SETHOTCURSOR", "List View", "Set Hot Cursor") : true))
            return "";
          #endif

          #ifdef LVM_SETHOTITEM
            if (not (LVM_SETHOTITEM == message ? translation.apply("LVM_SETHOTITEM", "List View", "Set Hot Item") : true))
            return "";
          #endif

          #ifdef LVM_SETHOVERTIME
            if (not (LVM_SETHOVERTIME == message ? translation.apply("LVM_SETHOVERTIME", "List View", "Set Hover Time") : true))
            return "";
          #endif

          #ifdef LVM_SETICONSPACING
            if (not (LVM_SETICONSPACING == message ? translation.apply("LVM_SETICONSPACING", "List View", "Set Icon Spacing") : true))
            return "";
          #endif

          #ifdef LVM_SETIMAGELIST
            if (not (LVM_SETIMAGELIST == message ? translation.apply("LVM_SETIMAGELIST", "List View", "Set Image List") : true))
            return "";
          #endif

          #ifdef LVM_SETINFOTIP
            if (not (LVM_SETINFOTIP == message ? translation.apply("LVM_SETINFOTIP", "List View", "Set Information Tip") : true))
            return "";
          #endif

          #ifdef LVM_SETINSERTMARK
            if (not (LVM_SETINSERTMARK == message ? translation.apply("LVM_SETINSERTMARK", "List View", "Set Insert Mark") : true))
            return "";
          #endif

          #ifdef LVM_SETINSERTMARKCOLOR
            if (not (LVM_SETINSERTMARKCOLOR == message ? translation.apply("LVM_SETINSERTMARKCOLOR", "List View", "Set Insert Mark Color") : true))
            return "";
          #endif

          #ifdef LVM_SETITEMA
            if (not (LVM_SETITEMA == message ? translation.apply("LVM_SETITEMA", "List View", "Set Item") : true))
            return "";
          #endif

          #ifdef LVM_SETITEMCOUNT
            if (not (LVM_SETITEMCOUNT == message ? translation.apply("LVM_SETITEMCOUNT", "List View", "Set Item Count") : true))
            return "";
          #endif

          #ifdef LVM_SETITEMPOSITION
            if (not (LVM_SETITEMPOSITION == message ? translation.apply("LVM_SETITEMPOSITION", "List View", "Set Item Position") : true))
            return "";
          #endif

          #ifdef LVM_SETITEMPOSITION32
            if (not (LVM_SETITEMPOSITION32 == message ? translation.apply("LVM_SETITEMPOSITION32", "List View", "Set Item Position (32-Bit)") : true))
            return "";
          #endif

          #ifdef LVM_SETITEMSTATE
            if (not (LVM_SETITEMSTATE == message ? translation.apply("LVM_SETITEMSTATE", "List View", "Set Item State") : true))
            return "";
          #endif

          #ifdef LVM_SETITEMTEXTA
            if (not (LVM_SETITEMTEXTA == message ? translation.apply("LVM_SETITEMTEXTA", "List View", "Set Item Text") : true))
            return "";
          #endif

          #ifdef LVM_SETITEMTEXTW
            if (not (LVM_SETITEMTEXTW == message ? translation.apply("LVM_SETITEMTEXTW", "List View", "Set Item Text") : true))
            return "";
          #endif

          #ifdef LVM_SETITEMW
            if (not (LVM_SETITEMW == message ? translation.apply("LVM_SETITEMW", "List View", "Set Item") : true))
            return "";
          #endif

          #ifdef LVM_SETOUTLINECOLOR
            if (not (LVM_SETOUTLINECOLOR == message ? translation.apply("LVM_SETOUTLINECOLOR", "List View", "Set Outline Color") : true))
            return "";
          #endif

          #ifdef LVM_SETSELECTEDCOLUMN
            if (not (LVM_SETSELECTEDCOLUMN == message ? translation.apply("LVM_SETSELECTEDCOLUMN", "List View", "Set Selected Column") : true))
            return "";
          #endif

          #ifdef LVM_SETSELECTIONMARK
            if (not (LVM_SETSELECTIONMARK == message ? translation.apply("LVM_SETSELECTIONMARK", "List View", "Set Selection Mark") : true))
            return "";
          #endif

          #ifdef LVM_SETTEXTBKCOLOR
            if (not (LVM_SETTEXTBKCOLOR == message ? translation.apply("LVM_SETTEXTBKCOLOR", "List View", "Set Text Background Color") : true))
            return "";
          #endif

          #ifdef LVM_SETTEXTCOLOR
            if (not (LVM_SETTEXTCOLOR == message ? translation.apply("LVM_SETTEXTCOLOR", "List View", "Set Text Color") : true))
            return "";
          #endif

          #ifdef LVM_SETTILEINFO
            if (not (LVM_SETTILEINFO == message ? translation.apply("LVM_SETTILEINFO", "List View", "Set Tile Information") : true))
            return "";
          #endif

          #ifdef LVM_SETTILEVIEWINFO
            if (not (LVM_SETTILEVIEWINFO == message ? translation.apply("LVM_SETTILEVIEWINFO", "List View", "Set Tile View Information") : true))
            return "";
          #endif

          #ifdef LVM_SETTILEWIDTH
            if (not (LVM_SETTILEWIDTH == message ? translation.apply("LVM_SETTILEWIDTH", "List View", "Set Tile Width") : true))
            return "";
          #endif

          #ifdef LVM_SETTOOLTIPS
            if (not (LVM_SETTOOLTIPS == message ? translation.apply("LVM_SETTOOLTIPS", "List View", "Set Tooltips") : true))
            return "";
          #endif

          #ifdef LVM_SETUNICODEFORMAT
            if (not (LVM_SETUNICODEFORMAT == message ? translation.apply("LVM_SETUNICODEFORMAT", "List View", "Set Unicode Format") : true))
            return "";
          #endif

          #ifdef LVM_SETVIEW
            if (not (LVM_SETVIEW == message ? translation.apply("LVM_SETVIEW", "List View", "Set View") : true))
            return "";
          #endif

          #ifdef LVM_SETWORKAREAS
            if (not (LVM_SETWORKAREAS == message ? translation.apply("LVM_SETWORKAREAS", "List View", "Set WorkaAreas") : true))
            return "";
          #endif

          #ifdef LVM_SORTGROUPS
            if (not (LVM_SORTGROUPS == message ? translation.apply("LVM_SORTGROUPS", "List View", "Sort Groups") : true))
            return "";
          #endif

          #ifdef LVM_SORTITEMS
            if (not (LVM_SORTITEMS == message ? translation.apply("LVM_SORTITEMS", "List View", "Sort Items") : true))
            return "";
          #endif

          #ifdef LVM_SUBITEMHITTEST
            if (not (LVM_SUBITEMHITTEST == message ? translation.apply("LVM_SUBITEMHITTEST", "List View", "Sub-Item Hit Test") : true))
            return "";
          #endif

          #ifdef LVM_UPDATE
            if (not (LVM_UPDATE == message ? translation.apply("LVM_UPDATE", "List View", "Update") : true))
            return "";
          #endif

          #ifdef MCIWNDM_CAN_CONFIG
            if (not (MCIWNDM_CAN_CONFIG == message ? translation.apply("MCIWNDM_CAN_CONFIG", "MCI (Media Control Interface) Window", "Can Configure") : true))
            return "";
          #endif

          #ifdef MCIWNDM_CAN_EJECT
            if (not (MCIWNDM_CAN_EJECT == message ? translation.apply("MCIWNDM_CAN_EJECT", "MCI (Media Control Interface) Window", "Can Eject") : true))
            return "";
          #endif

          #ifdef MCIWNDM_CAN_PLAY
            if (not (MCIWNDM_CAN_PLAY == message ? translation.apply("MCIWNDM_CAN_PLAY", "MCI (Media Control Interface) Window", "Can Play") : true))
            return "";
          #endif

          #ifdef MCIWNDM_CAN_RECORD
            if (not (MCIWNDM_CAN_RECORD == message ? translation.apply("MCIWNDM_CAN_RECORD", "MCI (Media Control Interface) Window", "Can Record") : true))
            return "";
          #endif

          #ifdef MCIWNDM_CAN_SAVE
            if (not (MCIWNDM_CAN_SAVE == message ? translation.apply("MCIWNDM_CAN_SAVE", "MCI (Media Control Interface) Window", "Can Save") : true))
            return "";
          #endif

          #ifdef MCIWNDM_CAN_WINDOW
            if (not (MCIWNDM_CAN_WINDOW == message ? translation.apply("MCIWNDM_CAN_WINDOW", "MCI (Media Control Interface) Window", "Can Window") : true))
            return "";
          #endif

          #ifdef MCIWNDM_GET_DEST
            if (not (MCIWNDM_GET_DEST == message ? translation.apply("MCIWNDM_GET_DEST", "MCI (Media Control Interface) Window", "Get Destination") : true))
            return "";
          #endif

          #ifdef MCIWNDM_GET_SOURCE
            if (not (MCIWNDM_GET_SOURCE == message ? translation.apply("MCIWNDM_GET_SOURCE", "MCI (Media Control Interface) Window", "Get Source") : true))
            return "";
          #endif

          #ifdef MCIWNDM_GETDEVICEA
            if (not (MCIWNDM_GETDEVICEA == message ? translation.apply("MCIWNDM_GETDEVICEA", "MCI (Media Control Interface) Window", "Get Device") : true))
            return "";
          #endif

          #ifdef MCIWNDM_GETDEVICEW
            if (not (MCIWNDM_GETDEVICEW == message ? translation.apply("MCIWNDM_GETDEVICEW", "MCI (Media Control Interface) Window", "Get Device") : true))
            return "";
          #endif

          #ifdef MCIWNDM_GETERROR
            if (not (MCIWNDM_GETERROR == message ? translation.apply("MCIWNDM_GETERROR", "MCI (Media Control Interface) Window", "Get Error") : true))
            return "";
          #endif

          #ifdef MCIWNDM_GETERRORA
            if (not (MCIWNDM_GETERRORA == message ? translation.apply("MCIWNDM_GETERRORA", "MCI (Media Control Interface) Window", "Get Error") : true))
            return "";
          #endif

          #ifdef MCIWNDM_GETFILENAMEA
            if (not (MCIWNDM_GETFILENAMEA == message ? translation.apply("MCIWNDM_GETFILENAMEA", "MCI (Media Control Interface) Window", "Get File Name") : true))
            return "";
          #endif

          #ifdef MCIWNDM_GETFILENAMEW
            if (not (MCIWNDM_GETFILENAMEW == message ? translation.apply("MCIWNDM_GETFILENAMEW", "MCI (Media Control Interface) Window", "Get File Name") : true))
            return "";
          #endif

          #ifdef MCIWNDM_GETINACTIVETIMER
            if (not (MCIWNDM_GETINACTIVETIMER == message ? translation.apply("MCIWNDM_GETINACTIVETIMER", "MCI (Media Control Interface) Window", "User") : true))
            return "";
          #endif

          #ifdef MCIWNDM_GETPALETTE
            if (not (MCIWNDM_GETPALETTE == message ? translation.apply("MCIWNDM_GETPALETTE", "MCI (Media Control Interface) Window", "Get Palette") : true))
            return "";
          #endif

          #ifdef MCIWNDM_GETTIMEFORMATA
            if (not (MCIWNDM_GETTIMEFORMATA == message ? translation.apply("MCIWNDM_GETTIMEFORMATA", "MCI (Media Control Interface) Window", "Get Time Format") : true))
            return "";
          #endif

          #ifdef MCIWNDM_NOTIFYERROR
            if (not (MCIWNDM_NOTIFYERROR == message ? translation.apply("MCIWNDM_NOTIFYERROR", "MCI (Media Control Interface) Window", "Notify Error") : true))
            return "";
          #endif

          #ifdef MCIWNDM_NOTIFYMEDIA
            if (not (MCIWNDM_NOTIFYMEDIA == message ? translation.apply("MCIWNDM_NOTIFYMEDIA", "MCI (Media Control Interface) Window", "Notify Media") : true))
            return "";
          #endif

          #ifdef MCIWNDM_NOTIFYMODE
            if (not (MCIWNDM_NOTIFYMODE == message ? translation.apply("MCIWNDM_NOTIFYMODE", "MCI (Media Control Interface) Window", "Notify Mode") : true))
            return "";
          #endif

          #ifdef MCIWNDM_PALETTEKICK
            if (not (MCIWNDM_PALETTEKICK == message ? translation.apply("MCIWNDM_PALETTEKICK", "MCI (Media Control Interface) Window", "Palette Kick") : true))
            return "";
          #endif

          #ifdef MCIWNDM_PLAYTO
            if (not (MCIWNDM_PLAYTO == message ? translation.apply("MCIWNDM_PLAYTO", "MCI (Media Control Interface) Window", "Play To") : true))
            return "";
          #endif

          #ifdef MCIWNDM_PUT_DEST
            if (not (MCIWNDM_PUT_DEST == message ? translation.apply("MCIWNDM_PUT_DEST", "MCI (Media Control Interface) Window", "Put Destination") : true))
            return "";
          #endif

          #ifdef MCIWNDM_PUT_SOURCE
            if (not (MCIWNDM_PUT_SOURCE == message ? translation.apply("MCIWNDM_PUT_SOURCE", "MCI (Media Control Interface) Window", "Put Source") : true))
            return "";
          #endif

          #ifdef MCIWNDM_REALIZE
            if (not (MCIWNDM_REALIZE == message ? translation.apply("MCIWNDM_REALIZE", "MCI (Media Control Interface) Window", "Realize") : true))
            return "";
          #endif

          #ifdef MCIWNDM_SETINACTIVETIMER
            if (not (MCIWNDM_SETINACTIVETIMER == message ? translation.apply("MCIWNDM_SETINACTIVETIMER", "MCI (Media Control Interface) Window", "Set Inactive Timer") : true))
            return "";
          #endif

          #ifdef MCIWNDM_SETPALETTE
            if (not (MCIWNDM_SETPALETTE == message ? translation.apply("MCIWNDM_SETPALETTE", "MCI (Media Control Interface) Window", "Set Palette") : true))
            return "";
          #endif

          #ifdef MCIWNDM_SETTIMEFORMATA
            if (not (MCIWNDM_SETTIMEFORMATA == message ? translation.apply("MCIWNDM_SETTIMEFORMATA", "MCI (Media Control Interface) Window", "Set Time Format") : true))
            return "";
          #endif

          #ifdef MCIWNDM_SETTIMEFORMATW
            if (not (MCIWNDM_SETTIMEFORMATW == message ? translation.apply("MCIWNDM_SETTIMEFORMATW", "MCI (Media Control Interface) Window", "Set Time Format") : true))
            return "";
          #endif

          #ifdef MCIWNDM_VALIDATEMEDIA
            if (not (MCIWNDM_VALIDATEMEDIA == message ? translation.apply("MCIWNDM_VALIDATEMEDIA", "MCI (Media Control Interface) Window", "Validate Media") : true))
            return "";
          #endif

          #ifdef MSG_FTS_JUMP_QWORD
            if (not (MSG_FTS_JUMP_QWORD == message ? translation.apply("MSG_FTS_JUMP_QWORD", "Message Full-Text Search", "Jump Quad-Word") : true))
            return "";
          #endif

          #ifdef MSG_FTS_JUMP_VA
            if (not (MSG_FTS_JUMP_VA == message ? translation.apply("MSG_FTS_JUMP_VA", "Message Full-Text Search", "Jump Variably") : true))
            return "";
          #endif

          #ifdef MSG_FTS_WHERE_IS_IT
            if (not (MSG_FTS_WHERE_IS_IT == message ? translation.apply("MSG_FTS_WHERE_IS_IT", "Message Full-Text Search", "Where Is It") : true))
            return "";
          #endif

          #ifdef MSG_GET_DEFFONT
            if (not (MSG_GET_DEFFONT == message ? translation.apply("MSG_GET_DEFFONT", "Message", "Get Default Font") : true))
            return "";
          #endif

          #ifdef MSG_REINDEX_REQUEST
            if (not (MSG_REINDEX_REQUEST == message ? translation.apply("MSG_REINDEX_REQUEST", "Message", "Re-Index Request") : true))
            return "";
          #endif

          #ifdef NIN_SELECT
            if (not (NIN_SELECT == message ? translation.apply("NIN_SELECT", "Notify Icon", "Select") : true))
            return "";
          #endif

          #ifdef OCM__BASE
            if (not (OCM__BASE == message ? translation.apply("OCM__BASE", "Object Linking & Embedding Control", "Base") : true))
            return "";
          #endif

          #ifdef OCM_CHARTOITEM
            if (not (OCM_CHARTOITEM == message ? translation.apply("OCM_CHARTOITEM", "Object Linking & Embedding Control", "Character To Item") : true))
            return "";
          #endif

          #ifdef OCM_COMMAND
            if (not (OCM_COMMAND == message ? translation.apply("OCM_COMMAND", "Object Linking & Embedding Control", "Command") : true))
            return "";
          #endif

          #ifdef OCM_COMPAREITEM
            if (not (OCM_COMPAREITEM == message ? translation.apply("OCM_COMPAREITEM", "Object Linking & Embedding Control", "Compare Item") : true))
            return "";
          #endif

          #ifdef OCM_CTLCOLOR
            if (not (OCM_CTLCOLOR == message ? translation.apply("OCM_CTLCOLOR", "Object Linking & Embedding Control", "Control Color") : true))
            return "";
          #endif

          #ifdef OCM_CTLCOLORBTN
            if (not (OCM_CTLCOLORBTN == message ? translation.apply("OCM_CTLCOLORBTN", "Object Linking & Embedding Control", "Control Color Button") : true))
            return "";
          #endif

          #ifdef OCM_CTLCOLORDLG
            if (not (OCM_CTLCOLORDLG == message ? translation.apply("OCM_CTLCOLORDLG", "Object Linking & Embedding Control", "Control Color Dialog") : true))
            return "";
          #endif

          #ifdef OCM_CTLCOLOREDIT
            if (not (OCM_CTLCOLOREDIT == message ? translation.apply("OCM_CTLCOLOREDIT", "Object Linking & Embedding Control", "Control Color Edit") : true))
            return "";
          #endif

          #ifdef OCM_CTLCOLORLISTBOX
            if (not (OCM_CTLCOLORLISTBOX == message ? translation.apply("OCM_CTLCOLORLISTBOX", "Object Linking & Embedding Control", "Control Color List Box") : true))
            return "";
          #endif

          #ifdef OCM_CTLCOLORMSGBOX
            if (not (OCM_CTLCOLORMSGBOX == message ? translation.apply("OCM_CTLCOLORMSGBOX", "Object Linking & Embedding Control", "Control Color Message Box") : true))
            return "";
          #endif

          #ifdef OCM_CTLCOLORSCROLLBAR
            if (not (OCM_CTLCOLORSCROLLBAR == message ? translation.apply("OCM_CTLCOLORSCROLLBAR", "Object Linking & Embedding Control", "Control Color Scrollbar") : true))
            return "";
          #endif

          #ifdef OCM_CTLCOLORSTATIC
            if (not (OCM_CTLCOLORSTATIC == message ? translation.apply("OCM_CTLCOLORSTATIC", "Object Linking & Embedding Control", "Control Color Static") : true))
            return "";
          #endif

          #ifdef OCM_DELETEITEM
            if (not (OCM_DELETEITEM == message ? translation.apply("OCM_DELETEITEM", "Object Linking & Embedding Control", "Delete Item") : true))
            return "";
          #endif

          #ifdef OCM_DRAWITEM
            if (not (OCM_DRAWITEM == message ? translation.apply("OCM_DRAWITEM", "Object Linking & Embedding Control", "Draw Item") : true))
            return "";
          #endif

          #ifdef OCM_HSCROLL
            if (not (OCM_HSCROLL == message ? translation.apply("OCM_HSCROLL", "Object Linking & Embedding Control", "Horizontal Scroll") : true))
            return "";
          #endif

          #ifdef OCM_MEASUREITEM
            if (not (OCM_MEASUREITEM == message ? translation.apply("OCM_MEASUREITEM", "Object Linking & Embedding Control", "Measure Item") : true))
            return "";
          #endif

          #ifdef OCM_NOTIFY
            if (not (OCM_NOTIFY == message ? translation.apply("OCM_NOTIFY", "Object Linking & Embedding Control", "Notify") : true))
            return "";
          #endif

          #ifdef OCM_PARENTNOTIFY
            if (not (OCM_PARENTNOTIFY == message ? translation.apply("OCM_PARENTNOTIFY", "Object Linking & Embedding Control", "Parent Notify") : true))
            return "";
          #endif

          #ifdef OCM_VKEYTOITEM
            if (not (OCM_VKEYTOITEM == message ? translation.apply("OCM_VKEYTOITEM", "Object Linking & Embedding Control", "Virtual Key to Item") : true))
            return "";
          #endif

          #ifdef OCM_VSCROLL
            if (not (OCM_VSCROLL == message ? translation.apply("OCM_VSCROLL", "Object Linking & Embedding Control", "Vertical Scroll") : true))
            return "";
          #endif

          #ifdef PBM_DELTAPOS
            if (not (PBM_DELTAPOS == message ? translation.apply("PBM_SETBARCOLOR", "Progress Bar", "Delta Position") : true))
            return "";
          #endif

          #ifdef PBM_GETPOS
            if (not (PBM_GETPOS == message ? translation.apply("PBM_GETPOS", "Progress Bar", "Get Position") : true))
            return "";
          #endif

          #ifdef PBM_GETRANGE
            if (not (PBM_GETRANGE == message ? translation.apply("PBM_GETRANGE", "Progress Bar", "Get Range") : true))
            return "";
          #endif

          #ifdef PBM_SETBARCOLOR
            if (not (PBM_SETBARCOLOR == message ? translation.apply("PBM_SETBARCOLOR", "Progress Bar", "Set Bar Color") : true))
            return "";
          #endif

          #ifdef PBM_SETPOS
            if (not (PBM_SETPOS == message ? translation.apply("PBM_SETPOS", "Progress Bar", "Set Position") : true))
            return "";
          #endif

          #ifdef PBM_SETRANGE
            if (not (PBM_SETRANGE == message ? translation.apply("PBM_SETRANGE", "Progress Bar", "Set Range") : true))
            return "";
          #endif

          #ifdef PBM_SETRANGE32
            if (not (PBM_SETRANGE32 == message ? translation.apply("PBM_SETRANGE32", "Progress Bar", "Set Range") : true))
            return "";
          #endif

          #ifdef PBM_SETSTEP
            if (not (PBM_SETSTEP == message ? translation.apply("PBM_SETSTEP", "Progress Bar", "Set Step") : true))
            return "";
          #endif

          #ifdef PBM_STEPIT
            if (not (PBM_STEPIT == message ? translation.apply("PBM_STEPIT", "Progress Bar", "Step It") : true))
            return "";
          #endif

          #ifdef PSM_ADDPAGE
            if (not (PSM_ADDPAGE == message ? translation.apply("PSM_ADDPAGE", "Prop Sheet", "Add Page") : true))
            return "";
          #endif

          #ifdef PSM_APPLY
            if (not (PSM_APPLY == message ? translation.apply("PSM_APPLY", "Prop Sheet", "Apply") : true))
            return "";
          #endif

          #ifdef PSM_CANCELTOCLOSE
            if (not (PSM_CANCELTOCLOSE == message ? translation.apply("PSM_CANCELTOCLOSE", "Prop Sheet", "Cancel to Close") : true))
            return "";
          #endif

          #ifdef PSM_CHANGED
            if (not (PSM_CHANGED == message ? translation.apply("EM_SETIMECOLOR", "Rich Edit", "Set IME (Input Method Encoding) Color") : true))
            return "";
          #endif

          #ifdef PSM_GETCURRENTPAGEHWND
            if (not (PSM_GETCURRENTPAGEHWND == message ? translation.apply("PSM_GETCURRENTPAGEHWND", "Prop Sheet", "Get Current Page Window Handle") : true))
            return "";
          #endif

          #ifdef PSM_GETRESULT
            if (not (PSM_GETRESULT == message ? translation.apply("PSM_GETRESULT", "Prop Sheet", "Get Result") : true))
            return "";
          #endif

          #ifdef PSM_GETTABCONTROL
            if (not (PSM_GETTABCONTROL == message ? translation.apply("PSM_GETTABCONTROL", "Prop Sheet", "Get Tab Control") : true))
            return "";
          #endif

          #ifdef PSM_HWNDTOINDEX
            if (not (PSM_HWNDTOINDEX == message ? translation.apply("PSM_HWNDTOINDEX", "Prop Sheet", "Window Handle to Index") : true))
            return "";
          #endif

          #ifdef PSM_IDTOINDEX
            if (not (PSM_IDTOINDEX == message ? translation.apply("PSM_IDTOINDEX", "Prop Sheet", "ID to Index") : true))
            return "";
          #endif

          #ifdef PSM_INDEXTOHWND
            if (not (PSM_INDEXTOHWND == message ? translation.apply("PSM_INDEXTOHWND", "Prop Sheet", "Index to Window Handle") : true))
            return "";
          #endif

          #ifdef PSM_INDEXTOID
            if (not (PSM_INDEXTOID == message ? translation.apply("PSM_INDEXTOID", "Prop Sheet", "Index to ID") : true))
            return "";
          #endif

          #ifdef PSM_INDEXTOPAGE
            if (not (PSM_INDEXTOPAGE == message ? translation.apply("PSM_INDEXTOPAGE", "Prop Sheet", "Index to Page") : true))
            return "";
          #endif

          #ifdef PSM_ISDIALOGMESSAGE
            if (not (PSM_ISDIALOGMESSAGE == message ? translation.apply("PSM_ISDIALOGMESSAGE", "Prop Sheet", "Is Dialog Message") : true))
            return "";
          #endif

          #ifdef PSM_PAGETOINDEX
            if (not (PSM_PAGETOINDEX == message ? translation.apply("PSM_PAGETOINDEX", "Prop Sheet", "Insert Page") : true))
            return "";
          #endif

          #ifdef PSM_PAGETOINDEX
            if (not (PSM_PAGETOINDEX == message ? translation.apply("PSM_PAGETOINDEX", "Prop Sheet", "Page to Index") : true))
            return "";
          #endif

          #ifdef PSM_PRESSBUTTON
            if (not (PSM_PRESSBUTTON == message ? translation.apply("PSM_PRESSBUTTON", "Prop Sheet", "Press Button") : true))
            return "";
          #endif

          #ifdef PSM_QUERYSIBLINGS
            if (not (PSM_QUERYSIBLINGS == message ? translation.apply("PSM_QUERYSIBLINGS", "Prop Sheet", "Query Siblings") : true))
            return "";
          #endif

          #ifdef PSM_REBOOTSYSTEM
            if (not (PSM_REBOOTSYSTEM == message ? translation.apply("PSM_REBOOTSYSTEM", "Prop Sheet", "Reboot System") : true))
            return "";
          #endif

          #ifdef PSM_RECALCPAGESIZES
            if (not (PSM_RECALCPAGESIZES == message ? translation.apply("PSM_RECALCPAGESIZES", "Prop Sheet", "Recalculate Page Sizes") : true))
            return "";
          #endif

          #ifdef PSM_REMOVEPAGE
            if (not (PSM_REMOVEPAGE == message ? translation.apply("PSM_REMOVEPAGE", "Prop Sheet", "Remove Page") : true))
            return "";
          #endif

          #ifdef PSM_RESTARTWINDOWS
            if (not (PSM_RESTARTWINDOWS == message ? translation.apply("PSM_RESTARTWINDOWS", "Prop Sheet", "Restart Windows") : true))
            return "";
          #endif

          #ifdef PSM_SETCURSEL
            if (not (PSM_SETCURSEL == message ? translation.apply("PSM_SETCURSEL", "Prop Sheet", "Set Cursor Selection") : true))
            return "";
          #endif

          #ifdef PSM_SETCURSELID
            if (not (PSM_SETCURSELID == message ? translation.apply("PSM_SETCURSELID", "Prop Sheet", "Set Current Selection ID") : true))
            return "";
          #endif

          #ifdef PSM_SETFINISHTEXTA
            if (not (PSM_SETFINISHTEXTA == message ? translation.apply("PSM_SETFINISHTEXTA", "Prop Sheet", "Set Finish Text") : true))
            return "";
          #endif

          #ifdef PSM_SETFINISHTEXTA
            if (not (PSM_SETFINISHTEXTA == message ? translation.apply("PSM_SETFINISHTEXTA", "Prop Sheet", "Set Finish Text") : true))
            return "";
          #endif

          #ifdef PSM_SETHEADERSUBTITLEA
            if (not (PSM_SETHEADERSUBTITLEA == message ? translation.apply("PSM_SETHEADERSUBTITLEA", "Prop Sheet", "Set Header Subtitle") : true))
            return "";
          #endif

          #ifdef PSM_SETHEADERSUBTITLEW
            if (not (PSM_SETHEADERSUBTITLEW == message ? translation.apply("PSM_SETHEADERSUBTITLEW", "Prop Sheet", "Set Header Subtitle") : true))
            return "";
          #endif

          #ifdef PSM_SETHEADERTITLEA
            if (not (PSM_SETHEADERTITLEA == message ? translation.apply("PSM_SETHEADERTITLEA", "Prop Sheet", "Set Header Title") : true))
            return "";
          #endif

          #ifdef PSM_SETHEADERTITLEW
            if (not (PSM_SETHEADERTITLEW == message ? translation.apply("PSM_SETHEADERTITLEW", "Prop Sheet", "Set Header Title") : true))
            return "";
          #endif

          #ifdef PSM_SETTITLEA
            if (not (PSM_SETTITLEA == message ? translation.apply("PSM_SETTITLEA", "Prop Sheet", "Set Title") : true))
            return "";
          #endif

          #ifdef PSM_SETTITLEW
            if (not (PSM_SETTITLEW == message ? translation.apply("PSM_SETTITLEW", "Prop Sheet", "Set Title") : true))
            return "";
          #endif

          #ifdef PSM_SETWIZBUTTONS
            if (not (PSM_SETWIZBUTTONS == message ? translation.apply("PSM_SETWIZBUTTONS", "Prop Sheet", "Set Wizard Buttons") : true))
            return "";
          #endif

          #ifdef PSM_UNCHANGED
            if (not (PSM_UNCHANGED == message ? translation.apply("PSM_UNCHANGED", "Prop Sheet", "Unchanged") : true))
            return "";
          #endif

          #ifdef RB_BEGINDRAG
            if (not (RB_BEGINDRAG == message ? translation.apply("RB_BEGINDRAG", "Rebar", "Begin Drag") : true))
            return "";
          #endif

          #ifdef RB_DELETEBAND
            if (not (RB_DELETEBAND == message ? translation.apply("RB_DELETEBAND", "Rebar", "Delete Band") : true))
            return "";
          #endif

          #ifdef RB_DRAGMOVE
            if (not (RB_DRAGMOVE == message ? translation.apply("RB_DRAGMOVE", "Rebar", "Drag Move") : true))
            return "";
          #endif

          #ifdef RB_ENDDRAG
            if (not (RB_ENDDRAG == message ? translation.apply("RB_ENDDRAG", "Rebar", "End Drag") : true))
            return "";
          #endif

          #ifdef RB_GETBANDBORDERS
            if (not (RB_GETBANDBORDERS == message ? translation.apply("RB_GETBANDBORDERS", "Rebar", "Get Band Borders") : true))
            return "";
          #endif

          #ifdef RB_GETBANDCOUNT
            if (not (RB_GETBANDCOUNT == message ? translation.apply("RB_GETBANDCOUNT", "Rebar", "Get Band Count") : true))
            return "";
          #endif

          #ifdef RB_GETBANDINFOA
            if (not (RB_GETBANDINFOA == message ? translation.apply("RB_GETBANDINFOA", "Rebar", "Get Band Information") : true))
            return "";
          #endif

          #ifdef RB_GETBANDINFOW
            if (not (RB_GETBANDINFOW == message ? translation.apply("RB_GETBANDINFOW", "Rebar", "Get Band Information") : true))
            return "";
          #endif

          #ifdef RB_GETBARHEIGHT
            if (not (RB_GETBARHEIGHT == message ? translation.apply("RB_GETBARHEIGHT", "Rebar", "Get Bar Height") : true))
            return "";
          #endif

          #ifdef RB_GETBARINFO
            if (not (RB_GETBARINFO == message ? translation.apply("RB_GETBARINFO", "Rebar", "Get Bar Information") : true))
            return "";
          #endif

          #ifdef RB_GETBKCOLOR
            if (not (RB_GETBKCOLOR == message ? translation.apply("RB_GETBKCOLOR", "Rebar", "Get Background Color") : true))
            return "";
          #endif

          #ifdef RB_GETPALETTE
            if (not (RB_GETPALETTE == message ? translation.apply("RB_GETPALETTE", "Rebar", "Get Palette") : true))
            return "";
          #endif

          #ifdef RB_GETRECT
            if (not (RB_GETRECT == message ? translation.apply("RB_GETRECT", "Rebar", "Get Rectangle") : true))
            return "";
          #endif

          #ifdef RB_GETROWCOUNT
            if (not (RB_GETROWCOUNT == message ? translation.apply("RB_GETROWCOUNT", "Rebar", "Get Row Count") : true))
            return "";
          #endif

          #ifdef RB_GETROWHEIGHT
            if (not (RB_GETROWHEIGHT == message ? translation.apply("RB_GETROWHEIGHT", "Rebar", "Get Row Height") : true))
            return "";
          #endif

          #ifdef RB_GETTEXTCOLOR
            if (not (RB_GETTEXTCOLOR == message ? translation.apply("RB_GETTEXTCOLOR", "Rebar", "Get Text Color") : true))
            return "";
          #endif

          #ifdef RB_GETTOOLTIPS
            if (not (RB_GETTOOLTIPS == message ? translation.apply("RB_GETTOOLTIPS", "Rebar", "Get Tooltips") : true))
            return "";
          #endif

          #ifdef RB_HITTEST
            if (not (RB_HITTEST == message ? translation.apply("RB_HITTEST", "Rebar", "Hit Test") : true))
            return "";
          #endif

          #ifdef RB_IDTOINDEX
            if (not (RB_IDTOINDEX == message ? translation.apply("RB_IDTOINDEX", "Rebar", "ID to Index") : true))
            return "";
          #endif

          #ifdef RB_INSERTBANDA
            if (not (RB_INSERTBANDA == message ? translation.apply("RB_INSERTBANDA", "Rebar", "Insert Band") : true))
            return "";
          #endif

          #ifdef RB_INSERTBANDW
            if (not (RB_INSERTBANDW == message ? translation.apply("RB_INSERTBANDW", "Rebar", "Insert Band") : true))
            return "";
          #endif

          #ifdef RB_MAXIMIZEBAND
            if (not (RB_MAXIMIZEBAND == message ? translation.apply("RB_MAXIMIZEBAND", "Rebar", "Maximize Band") : true))
            return "";
          #endif

          #ifdef RB_MINIMIZEBAND
            if (not (RB_MINIMIZEBAND == message ? translation.apply("RB_MINIMIZEBAND", "Rebar", "Minimize Band") : true))
            return "";
          #endif

          #ifdef RB_MOVEBAND
            if (not (RB_MOVEBAND == message ? translation.apply("RB_MOVEBAND", "Rebar", "Move Band") : true))
            return "";
          #endif

          #ifdef RB_PUSHCHEVRON
            if (not (RB_PUSHCHEVRON == message ? translation.apply("RB_PUSHCHEVRON", "Rebar", "Push Chevron") : true))
            return "";
          #endif

          #ifdef RB_SETBANDINFOA
            if (not (RB_SETBANDINFOA == message ? translation.apply("RB_SETBANDINFOA", "Rebar", "Set Band Information") : true))
            return "";
          #endif

          #ifdef RB_SETBANDINFOW
            if (not (RB_SETBANDINFOW == message ? translation.apply("RB_SETBANDINFOW", "Rebar", "Set Band Information") : true))
            return "";
          #endif

          #ifdef RB_SETBARINFO
            if (not (RB_SETBARINFO == message ? translation.apply("RB_SETBARINFO", "Rebar", "Set Bar Information") : true))
            return "";
          #endif

          #ifdef RB_SETBKCOLOR
            if (not (RB_SETBKCOLOR == message ? translation.apply("RB_SETBKCOLOR", "Rebar", "Set Background Color") : true))
            return "";
          #endif

          #ifdef RB_SETPALETTE
            if (not (RB_SETPALETTE == message ? translation.apply("RB_SETPALETTE", "Rebar", "Set Palette") : true))
            return "";
          #endif

          #ifdef RB_SETPARENT
            if (not (RB_SETPARENT == message ? translation.apply("RB_SETPARENT", "Rebar", "Set Parent") : true))
            return "";
          #endif

          #ifdef RB_SETTEXTCOLOR
            if (not (RB_SETTEXTCOLOR == message ? translation.apply("RB_SETTEXTCOLOR", "Rebar", "Set Text Color") : true))
            return "";
          #endif

          #ifdef RB_SETTOOLTIPS
            if (not (RB_SETTOOLTIPS == message ? translation.apply("RB_SETTOOLTIPS", "Rebar", "Set Tooltips") : true))
            return "";
          #endif

          #ifdef RB_SHOWBAND
            if (not (RB_SHOWBAND == message ? translation.apply("RB_SHOWBAND", "Rebar", "Show Band") : true))
            return "";
          #endif

          #ifdef RB_SIZETORECT
            if (not (RB_SIZETORECT == message ? translation.apply("RB_SIZETORECT", "Rebar", "Size to Rectangle") : true))
            return "";
          #endif

          #ifdef SB_GETBORDERS
            if (not (SB_GETBORDERS == message ? translation.apply("SB_GETBORDERS", "Status Bar", "Get Borders") : true))
            return "";
          #endif

          #ifdef SB_GETPARTS
            if (not (SB_GETPARTS == message ? translation.apply("SB_GETPARTS", "Status Bar", "Get Parts") : true))
            return "";
          #endif

          #ifdef SB_GETRECT
            if (not (SB_GETRECT == message ? translation.apply("SB_GETRECT", "Status Bar", "Get Rectangle") : true))
            return "";
          #endif

          #ifdef SB_GETTEXTA
            if (not (SB_GETTEXTA == message ? translation.apply("SB_GETTEXTA", "Status Bar", "Get Text") : true))
            return "";
          #endif

          #ifdef SB_GETTEXTLENGTHA
            if (not (SB_GETTEXTLENGTHA == message ? translation.apply("SB_GETTEXTLENGTHA", "Status Bar", "Get Text Length") : true))
            return "";
          #endif

          #ifdef SB_GETTEXTLENGTHW
            if (not (SB_GETTEXTLENGTHW == message ? translation.apply("SB_GETTEXTLENGTHW", "Status Bar", "Get Text Length") : true))
            return "";
          #endif

          #ifdef SB_GETTEXTW
            if (not (SB_GETTEXTW == message ? translation.apply("SB_GETTEXTW", "Status Bar", "Get Text") : true))
            return "";
          #endif

          #ifdef SB_GETTIPTEXTA
            if (not (SB_GETTIPTEXTA == message ? translation.apply("SB_GETTIPTEXTA", "Status Bar", "Get Tip Text") : true))
            return "";
          #endif

          #ifdef SB_GETTIPTEXTW
            if (not (SB_GETTIPTEXTW == message ? translation.apply("SB_GETTIPTEXTW", "Status Bar", "Get Tip Text") : true))
            return "";
          #endif

          #ifdef SB_ISSIMPLE
            if (not (SB_ISSIMPLE == message ? translation.apply("SB_ISSIMPLE", "Status Bar", "Is Simple") : true))
            return "";
          #endif

          #ifdef SB_SETICON
            if (not (SB_SETICON == message ? translation.apply("SB_SETICON", "Status Bar", "Set Icon") : true))
            return "";
          #endif

          #ifdef SB_SETMINHEIGHT
            if (not (SB_SETMINHEIGHT == message ? translation.apply("SB_SETMINHEIGHT", "Status Bar", "Set Minimum Height") : true))
            return "";
          #endif

          #ifdef SB_SETPARTS
            if (not (SB_SETPARTS == message ? translation.apply("SB_SETPARTS", "Status Bar", "Set Parts") : true))
            return "";
          #endif

          #ifdef SB_SETTEXTW
            if (not (SB_SETTEXTW == message ? translation.apply("SB_SETTEXTW", "Status Bar", "Set Text") : true))
            return "";
          #endif

          #ifdef SB_SETTIPTEXTA
            if (not (SB_SETTIPTEXTA == message ? translation.apply("SB_SETTIPTEXTA", "Status Bar", "Set Tip Text") : true))
            return "";
          #endif

          #ifdef SB_SETTIPTEXTW
            if (not (SB_SETTIPTEXTW == message ? translation.apply("SB_SETTIPTEXTW", "Status Bar", "Set Tip Text") : true))
            return "";
          #endif

          #ifdef SB_SIMPLE
            if (not (SB_SIMPLE == message ? translation.apply("SB_SIMPLE", "Status Bar", "Simple") : true))
            return "";
          #endif

          #ifdef SBM_ENABLE_ARROWS
            if (not (SBM_ENABLE_ARROWS == message ? translation.apply("SBM_ENABLE_ARROWS", "Scrollbar", "Enable Arrows") : true))
            return "";
          #endif

          #ifdef SBM_GETPOS
            if (not (SBM_GETPOS == message ? translation.apply("SBM_GETPOS", "Scrollbar", "Get Position") : true))
            return "";
          #endif

          #ifdef SBM_GETRANGE
            if (not (SBM_GETRANGE == message ? translation.apply("SBM_GETRANGE", "Scrollbar", "Get Range") : true))
            return "";
          #endif

          #ifdef SBM_GETSCROLLINFO
            if (not (SBM_GETSCROLLINFO == message ? translation.apply("SBM_GETSCROLLINFO", "Scrollbar", "Get Scroll Information") : true))
            return "";
          #endif

          #ifdef SBM_SETPOS
            if (not (SBM_SETPOS == message ? translation.apply("SBM_SETPOS", "Scrollbar", "Set Position") : true))
            return "";
          #endif

          #ifdef SBM_SETRANGE
            if (not (SBM_SETRANGE == message ? translation.apply("SBM_SETRANGE", "Scrollbar", "Set Range") : true))
            return "";
          #endif

          #ifdef SBM_SETRANGEREDRAW
            if (not (SBM_SETRANGEREDRAW == message ? translation.apply("SBM_SETRANGEREDRAW", "Scrollbar", "Set Range Redraw") : true))
            return "";
          #endif

          #ifdef SBM_SETSCROLLINFO
            if (not (SBM_SETSCROLLINFO == message ? translation.apply("SBM_SETSCROLLINFO", "Scrollbar", "Set Scroll Information") : true))
            return "";
          #endif

          #ifdef SM_GETCURFOCUSA
            if (not (SM_GETCURFOCUSA == message ? translation.apply("SM_GETCURFOCUSA", "Storage Management", "Get Current Focus") : true))
            return "";
          #endif

          #ifdef SM_GETCURFOCUSW
            if (not (SM_GETCURFOCUSW == message ? translation.apply("SM_GETCURFOCUSW", "Storage Management", "Get Current Focus") : true))
            return "";
          #endif

          #ifdef SM_GETOPTIONS
            if (not (SM_GETOPTIONS == message ? translation.apply("SM_GETOPTIONS", "Storage Management", "Get Options") : true))
            return "";
          #endif

          #ifdef SM_GETSELCOUNT
            if (not (SM_GETSELCOUNT == message ? translation.apply("SM_GETSELCOUNT", "Storage Management", "Get Selection Count") : true))
            return "";
          #endif

          #ifdef SM_GETSERVERSELA
            if (not (SM_GETSERVERSELA == message ? translation.apply("SM_GETSERVERSELA", "Storage Management", "Get Server Selection") : true))
            return "";
          #endif

          #ifdef SM_GETSERVERSELW
            if (not (SM_GETSERVERSELW == message ? translation.apply("SM_GETSERVERSELW", "Storage Management", "Get Server Selection") : true))
            return "";
          #endif

          #ifdef TAPI_REPLY
            if (not (TAPI_REPLY == message ? translation.apply("TAPI_REPLY", "Telephony API", "Reply") : true))
            return "";
          #endif

          #ifdef TB_ADDBITMAP
            if (not (TB_ADDBITMAP == message ? translation.apply("TB_ADDBITMAP", "Toolbar", "Add Bitmap") : true))
            return "";
          #endif

          #ifdef TB_ADDBUTTONSA
            if (not (TB_ADDBUTTONSA == message ? translation.apply("TB_ADDBUTTONSA", "Toolbar", "Add Buttons") : true))
            return "";
          #endif

          #ifdef TB_ADDBUTTONSW
            if (not (TB_ADDBUTTONSW == message ? translation.apply("TB_ADDBUTTONSW", "Toolbar", "Add Buttons") : true))
            return "";
          #endif

          #ifdef TB_ADDSTRINGA
            if (not (TB_ADDSTRINGA == message ? translation.apply("TB_ADDSTRINGA", "Toolbar", "Add String") : true))
            return "";
          #endif

          #ifdef TB_ADDSTRINGW
            if (not (TB_ADDSTRINGW == message ? translation.apply("TB_ADDSTRINGW", "Toolbar", "Add String") : true))
            return "";
          #endif

          #ifdef TB_AUTOSIZE
            if (not (TB_AUTOSIZE == message ? translation.apply("TB_AUTOSIZE", "Toolbar", "Auto Size") : true))
            return "";
          #endif

          #ifdef TB_BUTTONCOUNT
            if (not (TB_BUTTONCOUNT == message ? translation.apply("TB_BUTTONCOUNT", "Toolbar", "Button Count") : true))
            return "";
          #endif

          #ifdef TB_BUTTONSTRUCTSIZE
            if (not (TB_BUTTONSTRUCTSIZE == message ? translation.apply("TB_BUTTONSTRUCTSIZE", "Toolbar", "Button Structure Size") : true))
            return "";
          #endif

          #ifdef TB_CHANGEBITMAP
            if (not (TB_CHANGEBITMAP == message ? translation.apply("TB_CHANGEBITMAP", "Toolbar", "Change Bitmap") : true))
            return "";
          #endif

          #ifdef TB_CHECKBUTTON
            if (not (TB_CHECKBUTTON == message ? translation.apply("TB_CHECKBUTTON", "Toolbar", "Check Button") : true))
            return "";
          #endif

          #ifdef TB_COMMANDTOINDEX
            if (not (TB_COMMANDTOINDEX == message ? translation.apply("TB_COMMANDTOINDEX", "Toolbar", "Command to Index") : true))
            return "";
          #endif

          #ifdef TB_CUSTOMIZE
            if (not (TB_CUSTOMIZE == message ? translation.apply("TB_CUSTOMIZE", "Toolbar", "Customize") : true))
            return "";
          #endif

          #ifdef TB_DELETEBUTTON
            if (not (TB_DELETEBUTTON == message ? translation.apply("TB_DELETEBUTTON", "Toolbar", "Delete Button") : true))
            return "";
          #endif

          #ifdef TB_ENABLEBUTTON
            if (not (TB_ENABLEBUTTON == message ? translation.apply("TB_ENABLEBUTTON", "Toolbar", "Enable Button") : true))
            return "";
          #endif

          #ifdef TB_GETANCHORHIGHLIGHT
            if (not (TB_GETANCHORHIGHLIGHT == message ? translation.apply("TB_GETANCHORHIGHLIGHT", "Toolbar", "Get Anchor Highlight") : true))
            return "";
          #endif

          #ifdef TB_GETBITMAP
            if (not (TB_GETBITMAP == message ? translation.apply("TB_GETBITMAP", "Toolbar", "Get Bitmap") : true))
            return "";
          #endif

          #ifdef TB_GETBITMAPFLAGS
            if (not (TB_GETBITMAPFLAGS == message ? translation.apply("TB_GETBITMAPFLAGS", "Toolbar", "Get Bitmap Flags") : true))
            return "";
          #endif

          #ifdef TB_GETBUTTON
            if (not (TB_GETBUTTON == message ? translation.apply("TB_GETBUTTON", "Toolbar", "Get Button") : true))
            return "";
          #endif

          #ifdef TB_GETBUTTONINFOA
            if (not (TB_GETBUTTONINFOA == message ? translation.apply("TB_GETBUTTONINFOA", "Toolbar", "Get Button Information") : true))
            return "";
          #endif

          #ifdef TB_GETBUTTONINFOW
            if (not (TB_GETBUTTONINFOW == message ? translation.apply("TB_GETBUTTONINFOW", "Toolbar", "Get Button Information") : true))
            return "";
          #endif

          #ifdef TB_GETBUTTONSIZE
            if (not (TB_GETBUTTONSIZE == message ? translation.apply("TB_GETBUTTONSIZE", "Toolbar", "Get Button Size") : true))
            return "";
          #endif

          #ifdef TB_GETBUTTONTEXTA
            if (not (TB_GETBUTTONTEXTA == message ? translation.apply("TB_GETBUTTONTEXTA", "Toolbar", "Get Button Text") : true))
            return "";
          #endif

          #ifdef TB_GETBUTTONTEXTW
            if (not (TB_GETBUTTONTEXTW == message ? translation.apply("TB_GETBUTTONTEXTW", "Toolbar", "Get Button Text") : true))
            return "";
          #endif

          #ifdef TB_GETDISABLEDIMAGELIST
            if (not (TB_GETDISABLEDIMAGELIST == message ? translation.apply("TB_GETDISABLEDIMAGELIST", "Toolbar", "Get Disabled Image List") : true))
            return "";
          #endif

          #ifdef TB_GETEXTENDEDSTYLE
            if (not (TB_GETEXTENDEDSTYLE == message ? translation.apply("TB_GETEXTENDEDSTYLE", "Toolbar", "Get Extended Style") : true))
            return "";
          #endif

          #ifdef TB_GETHOTIMAGELIST
            if (not (TB_GETHOTIMAGELIST == message ? translation.apply("TB_GETHOTIMAGELIST", "Toolbar", "Get Hot Image List") : true))
            return "";
          #endif

          #ifdef TB_GETHOTITEM
            if (not (TB_GETHOTITEM == message ? translation.apply("TB_GETHOTITEM", "Toolbar", "Get Hot Item") : true))
            return "";
          #endif

          #ifdef TB_GETIMAGELIST
            if (not (TB_GETIMAGELIST == message ? translation.apply("TB_GETIMAGELIST", "Toolbar", "Get Image List") : true))
            return "";
          #endif

          #ifdef TB_GETINSERTMARK
            if (not (TB_GETINSERTMARK == message ? translation.apply("TB_GETINSERTMARK", "Toolbar", "Get Insert Mark") : true))
            return "";
          #endif

          #ifdef TB_GETINSERTMARKCOLOR
            if (not (TB_GETINSERTMARKCOLOR == message ? translation.apply("TB_GETINSERTMARKCOLOR", "Toolbar", "Get Insert Mark Color") : true))
            return "";
          #endif

          #ifdef TB_GETITEMRECT
            if (not (TB_GETITEMRECT == message ? translation.apply("TB_GETITEMRECT", "Toolbar", "Get Item Rectangle") : true))
            return "";
          #endif

          #ifdef TB_GETMAXSIZE
            if (not (TB_GETMAXSIZE == message ? translation.apply("TB_GETMAXSIZE", "Toolbar", "Get Maximum Size") : true))
            return "";
          #endif

          #ifdef TB_GETOBJECT
            if (not (TB_GETOBJECT == message ? translation.apply("TB_GETOBJECT", "Toolbar", "Get Object") : true))
            return "";
          #endif

          #ifdef TB_GETPADDING
            if (not (TB_GETPADDING == message ? translation.apply("TB_GETPADDING", "Toolbar", "Get Padding") : true))
            return "";
          #endif

          #ifdef TB_GETRECT
            if (not (TB_GETRECT == message ? translation.apply("TB_GETRECT", "Toolbar", "Get Rectangle") : true))
            return "";
          #endif

          #ifdef TB_GETROWS
            if (not (TB_GETROWS == message ? translation.apply("TB_GETROWS", "Toolbar", "Get Rows") : true))
            return "";
          #endif

          #ifdef TB_GETSTATE
            if (not (TB_GETSTATE == message ? translation.apply("TB_GETSTATE", "Toolbar", "Get State") : true))
            return "";
          #endif

          #ifdef TB_GETSTRINGA
            if (not (TB_GETSTRINGA == message ? translation.apply("TB_GETSTRINGA", "Toolbar", "Get String") : true))
            return "";
          #endif

          #ifdef TB_GETSTRINGW
            if (not (TB_GETSTRINGW == message ? translation.apply("TB_GETSTRINGW", "Toolbar", "Get String") : true))
            return "";
          #endif

          #ifdef TB_GETSTYLE
            if (not (TB_GETSTYLE == message ? translation.apply("TB_GETSTYLE", "Toolbar", "Get Style") : true))
            return "";
          #endif

          #ifdef TB_GETTEXTROWS
            if (not (TB_GETTEXTROWS == message ? translation.apply("TB_GETTEXTROWS", "Toolbar", "Get Text Rows") : true))
            return "";
          #endif

          #ifdef TB_GETTOOLTIPS
            if (not (TB_GETTOOLTIPS == message ? translation.apply("TB_GETTOOLTIPS", "Toolbar", "Get Tooltips") : true))
            return "";
          #endif

          #ifdef TB_HIDEBUTTON
            if (not (TB_HIDEBUTTON == message ? translation.apply("TB_HIDEBUTTON", "Toolbar", "Hide Button") : true))
            return "";
          #endif

          #ifdef TB_HITTEST
            if (not (TB_HITTEST == message ? translation.apply("TB_HITTEST", "Toolbar", "Hit Test") : true))
            return "";
          #endif

          #ifdef TB_INDETERMINATE
            if (not (TB_INDETERMINATE == message ? translation.apply("TB_INDETERMINATE", "Toolbar", "Indeterminate") : true))
            return "";
          #endif

          #ifdef TB_INSERTBUTTONA
            if (not (TB_INSERTBUTTONA == message ? translation.apply("TB_INSERTBUTTONA", "Toolbar", "Insert Button") : true))
            return "";
          #endif

          #ifdef TB_INSERTBUTTONW
            if (not (TB_INSERTBUTTONW == message ? translation.apply("TB_INSERTBUTTONW", "Toolbar", "Insert Button") : true))
            return "";
          #endif

          #ifdef TB_INSERTMARKHITTEST
            if (not (TB_INSERTMARKHITTEST == message ? translation.apply("TB_INSERTMARKHITTEST", "Toolbar", "Insert Mark Hit Test") : true))
            return "";
          #endif

          #ifdef TB_ISBUTTONCHECKED
            if (not (TB_ISBUTTONCHECKED == message ? translation.apply("TB_ISBUTTONCHECKED", "Toolbar", "Is Button Checked") : true))
            return "";
          #endif

          #ifdef TB_ISBUTTONENABLED
            if (not (TB_ISBUTTONENABLED == message ? translation.apply("TB_ISBUTTONENABLED", "Toolbar", "Is Button Enabled") : true))
            return "";
          #endif

          #ifdef TB_ISBUTTONHIDDEN
            if (not (TB_ISBUTTONHIDDEN == message ? translation.apply("TB_ISBUTTONHIDDEN", "Toolbar", "Is Button Hidden") : true))
            return "";
          #endif

          #ifdef TB_ISBUTTONHIGHLIGHTED
            if (not (TB_ISBUTTONHIGHLIGHTED == message ? translation.apply("TB_ISBUTTONHIGHLIGHTED", "Toolbar", "Is Button Highlighted") : true))
            return "";
          #endif

          #ifdef TB_ISBUTTONINDETERMINATE
            if (not (TB_ISBUTTONINDETERMINATE == message ? translation.apply("TB_ISBUTTONINDETERMINATE", "Toolbar", "Is Button Indeterminate") : true))
            return "";
          #endif

          #ifdef TB_ISBUTTONPRESSED
            if (not (TB_ISBUTTONPRESSED == message ? translation.apply("TB_ISBUTTONPRESSED", "Toolbar", "Is Button Pressed") : true))
            return "";
          #endif

          #ifdef TB_LOADIMAGES
            if (not (TB_LOADIMAGES == message ? translation.apply("TB_LOADIMAGES", "Toolbar", "Load Images") : true))
            return "";
          #endif

          #ifdef TB_MAPACCELERATORA
            if (not (TB_MAPACCELERATORA == message ? translation.apply("TB_MAPACCELERATORA", "Toolbar", "Map Accelerator") : true))
            return "";
          #endif

          #ifdef TB_MAPACCELERATORW
            if (not (TB_MAPACCELERATORW == message ? translation.apply("TB_MAPACCELERATORW", "Toolbar", "Map Acceleration") : true))
            return "";
          #endif

          #ifdef TB_MARKBUTTON
            if (not (TB_MARKBUTTON == message ? translation.apply("TB_MARKBUTTON", "Toolbar", "Mark Button") : true))
            return "";
          #endif

          #ifdef TB_MOVEBUTTON
            if (not (TB_MOVEBUTTON == message ? translation.apply("TB_MOVEBUTTON", "Toolbar", "Move Button") : true))
            return "";
          #endif

          #ifdef TB_PRESSBUTTON
            if (not (TB_PRESSBUTTON == message ? translation.apply("TB_PRESSBUTTON", "Toolbar", "Press Button") : true))
            return "";
          #endif

          #ifdef TB_REPLACEBITMAP
            if (not (TB_REPLACEBITMAP == message ? translation.apply("TB_REPLACEBITMAP", "Toolbar", "Replace Bitmap") : true))
            return "";
          #endif

          #ifdef TB_SAVERESTOREA
            if (not (TB_SAVERESTOREA == message ? translation.apply("TB_SAVERESTOREA", "Toolbar", "Save Restore") : true))
            return "";
          #endif

          #ifdef TB_SAVERESTOREW
            if (not (TB_SAVERESTOREW == message ? translation.apply("TB_SAVERESTOREW", "Toolbar", "Save Restore") : true))
            return "";
          #endif

          #ifdef TB_SETANCHORHIGHLIGHT
            if (not (TB_SETANCHORHIGHLIGHT == message ? translation.apply("TB_SETANCHORHIGHLIGHT", "Toolbar", "Set Anchor Highlight") : true))
            return "";
          #endif

          #ifdef TB_SETBITMAPSIZE
            if (not (TB_SETBITMAPSIZE == message ? translation.apply("TB_SETBITMAPSIZE", "Toolbar", "Set Bitmap Size") : true))
            return "";
          #endif

          #ifdef TB_SETBUTTONINFOA
            if (not (TB_SETBUTTONINFOA == message ? translation.apply("TB_SETBUTTONINFOA", "Toolbar", "Set Button Information") : true))
            return "";
          #endif

          #ifdef TB_SETBUTTONINFOW
            if (not (TB_SETBUTTONINFOW == message ? translation.apply("TB_SETBUTTONINFOW", "Toolbar", "Set Button Information") : true))
            return "";
          #endif

          #ifdef TB_SETBUTTONSIZE
            if (not (TB_SETBUTTONSIZE == message ? translation.apply("TB_SETBUTTONSIZE", "Toolbar", "Set Button Size") : true))
            return "";
          #endif

          #ifdef TB_SETBUTTONWIDTH
            if (not (TB_SETBUTTONWIDTH == message ? translation.apply("TB_SETBUTTONWIDTH", "Toolbar", "Set Button Width") : true))
            return "";
          #endif

          #ifdef TB_SETCMDID
            if (not (TB_SETCMDID == message ? translation.apply("TB_SETCMDID", "Toolbar", "Set Command Identifier") : true))
            return "";
          #endif

          #ifdef TB_SETDISABLEDIMAGELIST
            if (not (TB_SETDISABLEDIMAGELIST == message ? translation.apply("TB_SETDISABLEDIMAGELIST", "Toolbar", "Set Disabled Image List") : true))
            return "";
          #endif

          #ifdef TB_SETDRAWTEXTFLAGS
            if (not (TB_SETDRAWTEXTFLAGS == message ? translation.apply("TB_SETDRAWTEXTFLAGS", "Toolbar", "Set Draw Text Flags") : true))
            return "";
          #endif

          #ifdef TB_SETEXTENDEDSTYLE
            if (not (TB_SETEXTENDEDSTYLE == message ? translation.apply("TB_SETEXTENDEDSTYLE", "Toolbar", "Set Extended Style") : true))
            return "";
          #endif

          #ifdef TB_SETHOTIMAGELIST
            if (not (TB_SETHOTIMAGELIST == message ? translation.apply("TB_SETHOTIMAGELIST", "Toolbar", "Set Hot Image List") : true))
            return "";
          #endif

          #ifdef TB_SETHOTITEM
            if (not (TB_SETHOTITEM == message ? translation.apply("TB_SETHOTITEM", "Toolbar", "Set Hot Item") : true))
            return "";
          #endif

          #ifdef TB_SETIMAGELIST
            if (not (TB_SETIMAGELIST == message ? translation.apply("TB_SETIMAGELIST", "Toolbar", "Set Image List") : true))
            return "";
          #endif

          #ifdef TB_SETINDENT
            if (not (TB_SETINDENT == message ? translation.apply("TB_SETINDENT", "Toolbar", "Set Indentation") : true))
            return "";
          #endif

          #ifdef TB_SETINSERTMARK
            if (not (TB_SETINSERTMARK == message ? translation.apply("TB_SETINSERTMARK", "Toolbar", "Set Insert Mark") : true))
            return "";
          #endif

          #ifdef TB_SETINSERTMARKCOLOR
            if (not (TB_SETINSERTMARKCOLOR == message ? translation.apply("TB_SETINSERTMARKCOLOR", "Toolbar", "Set Insert Mark Color") : true))
            return "";
          #endif

          #ifdef TB_SETMAXTEXTROWS
            if (not (TB_SETMAXTEXTROWS == message ? translation.apply("TB_SETMAXTEXTROWS", "Toolbar", "Set Maximum Text Rows") : true))
            return "";
          #endif

          #ifdef TB_SETPADDING
            if (not (TB_SETPADDING == message ? translation.apply("TB_SETPADDING", "Toolbar", "Set Padding") : true))
            return "";
          #endif

          #ifdef TB_SETPARENT
            if (not (TB_SETPARENT == message ? translation.apply("TB_SETPARENT", "Toolbar", "Set Parent") : true))
            return "";
          #endif

          #ifdef TB_SETROWS
            if (not (TB_SETROWS == message ? translation.apply("TB_SETROWS", "Toolbar", "Set Rows") : true))
            return "";
          #endif

          #ifdef TB_SETSTATE
            if (not (TB_SETSTATE == message ? translation.apply("TB_SETSTATE", "Toolbar", "Set State") : true))
            return "";
          #endif

          #ifdef TB_SETSTYLE
            if (not (TB_SETSTYLE == message ? translation.apply("TB_SETSTYLE", "Toolbar", "Set Style") : true))
            return "";
          #endif

          #ifdef TB_SETTOOLTIPS
            if (not (TB_SETTOOLTIPS == message ? translation.apply("TB_SETTOOLTIPS", "Toolbar", "Set Tooltips") : true))
            return "";
          #endif

          #ifdef TBM_CLEARSEL
            if (not (TBM_CLEARSEL == message ? translation.apply("TBM_CLEARSEL", "Trackbar", "Clear Selection") : true))
            return "";
          #endif

          #ifdef TBM_CLEARTICS
            if (not (TBM_CLEARTICS == message ? translation.apply("TBM_CLEARTICS", "Trackbar", "Clear Ticks") : true))
            return "";
          #endif

          #ifdef TBM_GETBUDDY
            if (not (TBM_GETBUDDY == message ? translation.apply("TBM_GETBUDDY", "Trackbar", "Get Buddy") : true))
            return "";
          #endif

          #ifdef TBM_GETCHANNELRECT
            if (not (TBM_GETCHANNELRECT == message ? translation.apply("TBM_GETCHANNELRECT", "Trackbar", "Get Channel Rectangle") : true))
            return "";
          #endif

          #ifdef TBM_GETLINESIZE
            if (not (TBM_GETLINESIZE == message ? translation.apply("TBM_GETLINESIZE", "Trackbar", "Get Line Size") : true))
            return "";
          #endif

          #ifdef TBM_GETNUMTICS
            if (not (TBM_GETNUMTICS == message ? translation.apply("TBM_GETNUMTICS", "Trackbar", "Get Number (of) Ticks") : true))
            return "";
          #endif

          #ifdef TBM_GETPAGESIZE
            if (not (TBM_GETPAGESIZE == message ? translation.apply("TBM_GETPAGESIZE", "Trackbar", "Get Page Size") : true))
            return "";
          #endif

          #ifdef TBM_GETPOS
            if (not (TBM_GETPOS == message ? translation.apply("TBM_GETPOS", "Trackbar", "Get Position") : true))
            return "";
          #endif

          #ifdef TBM_GETPTICS
            if (not (TBM_GETPTICS == message ? translation.apply("TBM_GETPTICS", "Trackbar", "Get Position (of) Ticks") : true))
            return "";
          #endif

          #ifdef TBM_GETRANGEMAX
            if (not (TBM_GETRANGEMAX == message ? translation.apply("TBM_GETRANGEMAX", "Trackbar", "Get Range Maximum") : true))
            return "";
          #endif

          #ifdef TBM_GETRANGEMIN
            if (not (TBM_GETRANGEMIN == message ? translation.apply("TBM_GETRANGEMIN", "Trackbar", "Get Range") : true))
            return "";
          #endif

          #ifdef TBM_GETSELEND
            if (not (TBM_GETSELEND == message ? translation.apply("TBM_GETSELEND", "Trackbar", "Get Selection End") : true))
            return "";
          #endif

          #ifdef TBM_GETSELSTART
            if (not (TBM_GETSELSTART == message ? translation.apply("TBM_GETSELSTART", "Trackbar", "Get Selection Start") : true))
            return "";
          #endif

          #ifdef TBM_GETTHUMBLENGTH
            if (not (TBM_GETTHUMBLENGTH == message ? translation.apply("TBM_GETTHUMBLENGTH", "Trackbar", "Get Thumb Length") : true))
            return "";
          #endif

          #ifdef TBM_GETTHUMBRECT
            if (not (TBM_GETTHUMBRECT == message ? translation.apply("TBM_GETTHUMBRECT", "Trackbar", "Get Thumb Rectangle") : true))
            return "";
          #endif

          #ifdef TBM_GETTIC
            if (not (TBM_GETTIC == message ? translation.apply("TBM_GETTIC", "Trackbar", "Get Tick") : true))
            return "";
          #endif

          #ifdef TBM_GETTICPOS
            if (not (TBM_GETTICPOS == message ? translation.apply("TBM_GETTICPOS", "Trackbar", "Get Tick (Mark) Position") : true))
            return "";
          #endif

          #ifdef TBM_GETTOOLTIPS
            if (not (TBM_GETTOOLTIPS == message ? translation.apply("TBM_GETTOOLTIPS", "Trackbar", "Get Tooltips") : true))
            return "";
          #endif

          #ifdef TBM_SETBUDDY
            if (not (TBM_SETBUDDY == message ? translation.apply("TBM_SETBUDDY", "Trackbar", "Set Buddy") : true))
            return "";
          #endif

          #ifdef TBM_SETLINESIZE
            if (not (TBM_SETLINESIZE == message ? translation.apply("TBM_SETLINESIZE", "Trackbar", "Set Line Size") : true))
            return "";
          #endif

          #ifdef TBM_SETPAGESIZE
            if (not (TBM_SETPAGESIZE == message ? translation.apply("TBM_SETPAGESIZE", "Trackbar", "Set Page Size") : true))
            return "";
          #endif

          #ifdef TBM_SETPOS
            if (not (TBM_SETPOS == message ? translation.apply("TBM_SETPOS", "Trackbar", "Set Position") : true))
            return "";
          #endif

          #ifdef TBM_SETRANGE
            if (not (TBM_SETRANGE == message ? translation.apply("TBM_SETRANGE", "Trackbar", "Set Range") : true))
            return "";
          #endif

          #ifdef TBM_SETRANGEMAX
            if (not (TBM_SETRANGEMAX == message ? translation.apply("TBM_SETRANGEMAX", "Trackbar", "Set Range Maximum") : true))
            return "";
          #endif

          #ifdef TBM_SETRANGEMIN
            if (not (TBM_SETRANGEMIN == message ? translation.apply("TTM_RELAYEVENT", "Tooltip", "Relay Event") : true))
            return "";
          #endif

          #ifdef TBM_SETSEL
            if (not (TBM_SETSEL == message ? translation.apply("TBM_SETSEL", "Trackbar", "Set Selection") : true))
            return "";
          #endif

          #ifdef TBM_SETSELEND
            if (not (TBM_SETSELEND == message ? translation.apply("TBM_SETSELEND", "Trackbar", "Set Selection End") : true))
            return "";
          #endif

          #ifdef TBM_SETSELSTART
            if (not (TBM_SETSELSTART == message ? translation.apply("TBM_SETSELSTART", "Trackbar", "Set Selection Start") : true))
            return "";
          #endif

          #ifdef TBM_SETTHUMBLENGTH
            if (not (TBM_SETTHUMBLENGTH == message ? translation.apply("TBM_SETTHUMBLENGTH", "Trackbar", "Set Thumb Length") : true))
            return "";
          #endif

          #ifdef TBM_SETTIC
            if (not (TBM_SETTIC == message ? translation.apply("TBM_SETTIC", "Trackbar", "Set Tick") : true))
            return "";
          #endif

          #ifdef TBM_SETTICFREQ
            if (not (TBM_SETTICFREQ == message ? translation.apply("TBM_SETTICFREQ", "Trackbar", "Set Tick (Mark) Frequency") : true))
            return "";
          #endif

          #ifdef TBM_SETTIPSIDE
            if (not (TBM_SETTIPSIDE == message ? translation.apply("TBM_SETTIPSIDE", "Trackbar", "Set Tip Side") : true))
            return "";
          #endif

          #ifdef TBM_SETTOOLTIPS
            if (not (TBM_SETTOOLTIPS == message ? translation.apply("TBM_SETTOOLTIPS", "Trackbar", "Set Tooltips") : true))
            return "";
          #endif

          #ifdef TTM_ACTIVATE
            if (not (TTM_ACTIVATE == message ? translation.apply("TTM_ACTIVATE", "Tooltip", "Activate") : true))
            return "";
          #endif

          #ifdef TTM_ADDTOOLA
            if (not (TTM_ADDTOOLA == message ? translation.apply("TTM_ADDTOOLA", "Tooltip", "Add Tool") : true))
            return "";
          #endif

          #ifdef TTM_ADJUSTRECT
            if (not (TTM_ADJUSTRECT == message ? translation.apply("TTM_ADJUSTRECT", "Tooltip", "Adjust Rectangle") : true))
            return "";
          #endif

          #ifdef TTM_DELTOOLA
            if (not (TTM_DELTOOLA == message ? translation.apply("TTM_DELTOOLA", "Tooltip", "Delete Tool") : true))
            return "";
          #endif

          #ifdef TTM_DELTOOLW
            if (not (TTM_DELTOOLW == message ? translation.apply("TTM_DELTOOLW", "Tooltip", "Delete Tool") : true))
            return "";
          #endif

          #ifdef TTM_ENUMTOOLSA
            if (not (TTM_ENUMTOOLSA == message ? translation.apply("TTM_ENUMTOOLSA", "Tooltip", "Enumerate Tools") : true))
            return "";
          #endif

          #ifdef TTM_ENUMTOOLSW
            if (not (TTM_ENUMTOOLSW == message ? translation.apply("TTM_ENUMTOOLSW", "Tooltip", "Enumerate Tools") : true))
            return "";
          #endif

          #ifdef TTM_GETBUBBLESIZE
            if (not (TTM_GETBUBBLESIZE == message ? translation.apply("TTM_GETBUBBLESIZE", "Tooltip", "Get Bubble Size") : true))
            return "";
          #endif

          #ifdef TTM_GETCURRENTTOOLA
            if (not (TTM_GETCURRENTTOOLA == message ? translation.apply("TTM_GETCURRENTTOOLA", "Tooltip", "Get Current Tool") : true))
            return "";
          #endif

          #ifdef TTM_GETCURRENTTOOLW
            if (not (TTM_GETCURRENTTOOLW == message ? translation.apply("TTM_GETCURRENTTOOLW", "Tooltip", "Get Current Tool") : true))
            return "";
          #endif

          #ifdef TTM_GETDELAYTIME
            if (not (TTM_GETDELAYTIME == message ? translation.apply("TTM_GETDELAYTIME", "Tooltip", "Get Delay Time") : true))
            return "";
          #endif

          #ifdef TTM_GETMARGIN
            if (not (TTM_GETMARGIN == message ? translation.apply("TTM_GETMARGIN", "Tooltip", "Get Margin") : true))
            return "";
          #endif

          #ifdef TTM_GETMAXTIPWIDTH
            if (not (TTM_GETMAXTIPWIDTH == message ? translation.apply("TTM_GETMAXTIPWIDTH", "Tooltip", "Get Maximum Tip Width") : true))
            return "";
          #endif

          #ifdef TTM_GETTEXTA
            if (not (TTM_GETTEXTA == message ? translation.apply("TTM_GETTEXTA", "Tooltip", "Get Text") : true))
            return "";
          #endif

          #ifdef TTM_GETTEXTW
            if (not (TTM_GETTEXTW == message ? translation.apply("TTM_GETTEXTW", "Tooltip", "Get Text") : true))
            return "";
          #endif

          #ifdef TTM_GETTIPBKCOLOR
            if (not (TTM_GETTIPBKCOLOR == message ? translation.apply("TTM_GETTIPBKCOLOR", "Tooltip", "Get Tip Background Color") : true))
            return "";
          #endif

          #ifdef TTM_GETTIPTEXTCOLOR
            if (not (TTM_GETTIPTEXTCOLOR == message ? translation.apply("TTM_GETTIPTEXTCOLOR", "Tooltip", "Get Tip Text Color") : true))
            return "";
          #endif

          #ifdef TTM_GETTOOLCOUNT
            if (not (TTM_GETTOOLCOUNT == message ? translation.apply("TTM_GETTOOLCOUNT", "Tooltip", "Get Tool Count") : true))
            return "";
          #endif

          #ifdef TTM_GETTOOLINFOA
            if (not (TTM_GETTOOLINFOA == message ? translation.apply("TTM_GETTOOLINFOA", "Tooltip", "Get Tool Information") : true))
            return "";
          #endif

          #ifdef TTM_GETTOOLINFOW
            if (not (TTM_GETTOOLINFOW == message ? translation.apply("TTM_GETTOOLINFOW", "Tooltip", "Get Tool Information") : true))
            return "";
          #endif

          #ifdef TTM_HITTESTA
            if (not (TTM_HITTESTA == message ? translation.apply("TTM_HITTESTA", "Tooltip", "Hit Test") : true))
            return "";
          #endif

          #ifdef TTM_HITTESTW
            if (not (TTM_HITTESTW == message ? translation.apply("TTM_HITTESTW", "Tooltip", "Hit Test") : true))
            return "";
          #endif

          #ifdef TTM_NEWTOOLRECTA
            if (not (TTM_NEWTOOLRECTA == message ? translation.apply("TTM_NEWTOOLRECTA", "Tooltip", "New Tool Rectangle") : true))
            return "";
          #endif

          #ifdef TTM_NEWTOOLRECTW
            if (not (TTM_NEWTOOLRECTW == message ? translation.apply("TTM_NEWTOOLRECTW", "Tooltip", "New Tool Rectangle") : true))
            return "";
          #endif

          #ifdef TTM_POP
            if (not (TTM_POP == message ? translation.apply("TTM_POP", "Tooltip", "Pop") : true))
            return "";
          #endif

          #ifdef TTM_RELAYEVENT
            if (not (TTM_RELAYEVENT == message ? translation.apply("TBM_SETRANGEMIN", "Trackbar", "Set Range Minimum") : true))
            return "";
          #endif

          #ifdef TTM_SETDELAYTIME
            if (not (TTM_SETDELAYTIME == message ? translation.apply("TTM_SETDELAYTIME", "Tooltip", "Set Delay Time") : true))
            return "";
          #endif

          #ifdef TTM_SETMARGIN
            if (not (TTM_SETMARGIN == message ? translation.apply("TTM_SETMARGIN", "Tooltip", "Get Channel Rectangle") : true))
            return "";
          #endif

          #ifdef TTM_SETMAXTIPWIDTH
            if (not (TTM_SETMAXTIPWIDTH == message ? translation.apply("TTM_SETMAXTIPWIDTH", "Tooltip", "Set Maximum Tip Width") : true))
            return "";
          #endif

          #ifdef TTM_SETTIPBKCOLOR
            if (not (TTM_SETTIPBKCOLOR == message ? translation.apply("TTM_SETTIPBKCOLOR", "Tooltip", "Set Tip Background Color") : true))
            return "";
          #endif

          #ifdef TTM_SETTIPTEXTCOLOR
            if (not (TTM_SETTIPTEXTCOLOR == message ? translation.apply("TTM_SETTIPTEXTCOLOR", "Tooltip", "Set Tip Text Color") : true))
            return "";
          #endif

          #ifdef TTM_SETTITLEA
            if (not (TTM_SETTITLEA == message ? translation.apply("TTM_SETTITLEA", "Tooltip", "Set Title") : true))
            return "";
          #endif

          #ifdef TTM_SETTITLEW
            if (not (TTM_SETTITLEW == message ? translation.apply("TTM_SETTITLEW", "Tooltip", "Set Title") : true))
            return "";
          #endif

          #ifdef TTM_SETTOOLINFOA
            if (not (TTM_SETTOOLINFOA == message ? translation.apply("TTM_SETTOOLINFOA", "Tooltip", "Set Tool Information") : true))
            return "";
          #endif

          #ifdef TTM_SETTOOLINFOW
            if (not (TTM_SETTOOLINFOW == message ? translation.apply("TTM_SETTOOLINFOW", "Tooltip", "Set Tool Information") : true))
            return "";
          #endif

          #ifdef TTM_TRACKACTIVATE
            if (not (TTM_TRACKACTIVATE == message ? translation.apply("TTM_TRACKACTIVATE", "Tooltip", "Track Activate") : true))
            return "";
          #endif

          #ifdef TTM_TRACKPOSITION
            if (not (TTM_TRACKPOSITION == message ? translation.apply("TTM_TRACKPOSITION", "Tooltip", "Track Position") : true))
            return "";
          #endif

          #ifdef TTM_UPDATE
            if (not (TTM_UPDATE == message ? translation.apply("TTM_UPDATE", "Tooltip", "Update") : true))
            return "";
          #endif

          #ifdef TTM_UPDATETIPTEXTA
            if (not (TTM_UPDATETIPTEXTA == message ? translation.apply("TTM_UPDATETIPTEXTA", "Tooltip", "Update Tip Text") : true))
            return "";
          #endif

          #ifdef TTM_UPDATETIPTEXTW
            if (not (TTM_UPDATETIPTEXTW == message ? translation.apply("TTM_UPDATETIPTEXTW", "Tooltip", "Update Tip Text") : true))
            return "";
          #endif

          #ifdef TTM_WINDOWFROMPOINT
            if (not (TTM_WINDOWFROMPOINT == message ? translation.apply("TTM_WINDOWFROMPOINT", "Tooltip", "Window from Point") : true))
            return "";
          #endif

          #ifdef UDM_GETACCEL
            if (not (UDM_GETACCEL == message ? translation.apply("UDM_GETACCEL", "Up-Down Control", "Get Acceleration") : true))
            return "";
          #endif

          #ifdef UDM_GETBASE
            if (not (UDM_GETBASE == message ? translation.apply("UDM_GETBASE", "Up-Down Control", "Get Base") : true))
            return "";
          #endif

          #ifdef UDM_GETBUDDY
            if (not (UDM_GETBUDDY == message ? translation.apply("UDM_GETBUDDY", "Up-Down Control", "Get Buddy") : true))
            return "";
          #endif

          #ifdef UDM_GETPOS
            if (not (UDM_GETPOS == message ? translation.apply("UDM_GETPOS", "Up-Down Control", "Get Position") : true))
            return "";
          #endif

          #ifdef UDM_GETPOS32
            if (not (UDM_GETPOS32 == message ? translation.apply("UDM_GETPOS32", "Up-Down Control", "Get Position") : true))
            return "";
          #endif

          #ifdef UDM_GETRANGE
            if (not (UDM_GETRANGE == message ? translation.apply("UDM_GETRANGE", "Up-Down Control", "Get Range") : true))
            return "";
          #endif

          #ifdef UDM_GETRANGE32
            if (not (UDM_GETRANGE32 == message ? translation.apply("UDM_GETRANGE32", "Up-Down Control", "Get Range") : true))
            return "";
          #endif

          #ifdef UDM_SETACCEL
            if (not (UDM_SETACCEL == message ? translation.apply("UDM_SETACCEL", "Up-Down Control", "Set Acceleration") : true))
            return "";
          #endif

          #ifdef UDM_SETBASE
            if (not (UDM_SETBASE == message ? translation.apply("UDM_SETBASE", "Up-Down Control", "Set Base") : true))
            return "";
          #endif

          #ifdef UDM_SETBUDDY
            if (not (UDM_SETBUDDY == message ? translation.apply("UDM_SETBUDDY", "Up-Down Control", "Set Buddy") : true))
            return "";
          #endif

          #ifdef UDM_SETPOS
            if (not (UDM_SETPOS == message ? translation.apply("UDM_SETPOS", "Up-Down Control", "Set Range") : true))
            return "";
          #endif

          #ifdef UDM_SETPOS32
            if (not (UDM_SETPOS32 == message ? translation.apply("UDM_SETPOS32", "Up-Down Control", "Set Position") : true))
            return "";
          #endif

          #ifdef UDM_SETRANGE
            if (not (UDM_SETRANGE == message ? translation.apply("UDM_SETRANGE", "Up-Down Control", "Set Range") : true))
            return "";
          #endif

          #ifdef UDM_SETRANGE32
            if (not (UDM_SETRANGE32 == message ? translation.apply("UDM_SETRANGE32", "Up-Down Control", "Set Range") : true))
            return "";
          #endif

          #ifdef UM_GETCURFOCUSA
            if (not (UM_GETCURFOCUSA == message ? translation.apply("UM_GETCURFOCUSA", "User Manager", "Get Current Focus") : true))
            return "";
          #endif

          #ifdef UM_GETCURFOCUSW
            if (not (UM_GETCURFOCUSW == message ? translation.apply("UM_GETCURFOCUSW", "User Manager", "Get Current Focus") : true))
            return "";
          #endif

          #ifdef UM_GETGROUPSELA
            if (not (UM_GETGROUPSELA == message ? translation.apply("UM_GETGROUPSELA", "User Manager", "Get Group Selection") : true))
            return "";
          #endif

          #ifdef UM_GETGROUPSELW
            if (not (UM_GETGROUPSELW == message ? translation.apply("UM_GETGROUPSELW", "User Manager", "Get Group Selection") : true))
            return "";
          #endif

          #ifdef UM_GETOPTIONS
            if (not (UM_GETOPTIONS == message ? translation.apply("UM_GETOPTIONS", "User Manager", "Get Options") : true))
            return "";
          #endif

          #ifdef UM_GETOPTIONS2
            if (not (UM_GETOPTIONS2 == message ? translation.apply("UM_GETOPTIONS2", "User Manager", "Get Options (Structure)") : true))
            return "";
          #endif

          #ifdef UM_GETSELCOUNT
            if (not (UM_GETSELCOUNT == message ? translation.apply("UM_GETSELCOUNT", "User Manager", "Get Selection Count") : true))
            return "";
          #endif

          #ifdef UM_GETUSERSELA
            if (not (UM_GETUSERSELA == message ? translation.apply("UM_GETUSERSELA", "User Manager", "Get User Selection") : true))
            return "";
          #endif

          #ifdef UM_GETUSERSELW
            if (not (UM_GETUSERSELW == message ? translation.apply("UM_GETUSERSELW", "User Manager", "Get User Selection") : true))
            return "";
          #endif

          #ifdef WIZ_NEXT
            if (not (WIZ_NEXT == message ? translation.apply("WIZ_NEXT", "Wizard", "Next") : true))
            return "";
          #endif

          #ifdef WIZ_PREV
            if (not (WIZ_PREV == message ? translation.apply("WIZ_PREV", "Wizard", "Previous") : true))
            return "";
          #endif

          #ifdef WIZ_QUERYNUMPAGES
            if (not (WIZ_QUERYNUMPAGES == message ? translation.apply("WIZ_QUERYNUMPAGES", "Wizard", "Query Number of Pages") : true))
            return "";
          #endif

          #ifdef WLX_WM_SAS
            if (not (WLX_WM_SAS == message ? translation.apply("WLX_WM_SAS", "Windows Live Sync", "Statistical Analysis Suite Message") : true))
            return "";
          #endif

          #ifdef WM_ACTIVATE
            if (not (WM_ACTIVATE == message ? translation.apply("WM_ACTIVATE", "Windows", "Activate") : true))
            return "";
          #endif

          #ifdef WM_ACTIVATEAPP
            if (not (WM_ACTIVATEAPP == message ? translation.apply("WM_ACTIVATEAPP", "Windows", "Activate Application") : true))
            return "";
          #endif

          #ifdef WM_AFXFIRST
            if (not (WM_AFXFIRST == message ? translation.apply("WM_AFXFIRST", "Windows", "Application Framework Extensions [FIRST]") : true))
            return "";
          #endif

          #ifdef WM_AFXLAST
            if (not (WM_AFXLAST == message ? translation.apply("WM_AFXLAST", "Windows", "Application Framework Extensions [LAST]") : true))
            return "";
          #endif

          #ifdef WM_APP
            if (not (WM_APP == message ? translation.apply("WM_APP", "Windows", "Application") : true))
            return "";
          #endif

          #ifdef WM_APPCOMMAND
            if (not (WM_APPCOMMAND == message ? translation.apply("WM_APPCOMMAND", "Windows", "Application Command") : true))
            return "";
          #endif

          #ifdef WM_ASKCBFORMATNAME
            if (not (WM_ASKCBFORMATNAME == message ? translation.apply("WM_ASKCBFORMATNAME", "Windows", "Ask Clipboard Format Name") : true))
            return "";
          #endif

          #ifdef WM_CANCELJOURNAL
            if (not (WM_CANCELJOURNAL == message ? translation.apply("WM_CANCELJOURNAL", "Windows", "Cancel Journal") : true))
            return "";
          #endif

          #ifdef WM_CANCELMODE
            if (not (WM_CANCELMODE == message ? translation.apply("WM_CANCELMODE", "Windows", "Cancel Mode") : true))
            return "";
          #endif

          #ifdef WM_CAP_DRIVER_GET_NAMEW
            if (not (WM_CAP_DRIVER_GET_NAMEW == message ? translation.apply("WM_CAP_DRIVER_GET_NAMEW", "Windows Capture", "Driver Get Name") : true))
            return "";
          #endif

          #ifdef WM_CAP_DRIVER_GET_VERSIONW
            if (not (WM_CAP_DRIVER_GET_VERSIONW == message ? translation.apply("WM_CAP_DRIVER_GET_VERSIONW", "Windows Capture", "Driver Get Version") : true))
            return "";
          #endif

          #ifdef WM_CAP_FILE_GET_CAPTURE_FILEW
            if (not (WM_CAP_FILE_GET_CAPTURE_FILEW == message ? translation.apply("WM_CAP_FILE_GET_CAPTURE_FILEW", "Up-Down Control", "File Get Capture") : true))
            return "";
          #endif

          #ifdef WM_CAP_FILE_SAVEASW
            if (not (WM_CAP_FILE_SAVEASW == message ? translation.apply("WM_CAP_FILE_SAVEASW", "Windows Capture", "File Save As") : true))
            return "";
          #endif

          #ifdef WM_CAP_FILE_SAVEDIBW
            if (not (WM_CAP_FILE_SAVEDIBW == message ? translation.apply("WM_CAP_FILE_SAVEDIBW", "Windows Capture", "File Save Device-Independent Bitmap") : true))
            return "";
          #endif

          #ifdef WM_CAP_FILE_SET_CAPTURE_FILEW
            if (not (WM_CAP_FILE_SET_CAPTURE_FILEW == message ? translation.apply("WM_CAP_FILE_SET_CAPTURE_FILEW", "Windows Capture", "File Set Capture File") : true))
            return "";
          #endif

          #ifdef WM_CAP_GET_MCI_DEVICEW
            if (not (WM_CAP_GET_MCI_DEVICEW == message ? translation.apply("WM_CAP_GET_MCI_DEVICEW", "Windows Capture", "Get Media Control Interface Device") : true))
            return "";
          #endif

          #ifdef WM_CAP_PAL_OPENW
            if (not (WM_CAP_PAL_OPENW == message ? translation.apply("WM_CAP_PAL_OPENW", "Windows Capture", "Palette Open") : true))
            return "";
          #endif

          #ifdef WM_CAP_PAL_SAVEW
            if (not (WM_CAP_PAL_SAVEW == message ? translation.apply("WM_CAP_PAL_SAVEW", "Windows Capture", "Palette Save") : true))
            return "";
          #endif

          #ifdef WM_CAP_SET_CALLBACK_ERRORW
            if (not (WM_CAP_SET_CALLBACK_ERRORW == message ? translation.apply("WM_CAP_SET_CALLBACK_ERRORW", "Windows Capture", "Set Callback Error") : true))
            return "";
          #endif

          #ifdef WM_CAP_SET_CALLBACK_STATUSW
            if (not (WM_CAP_SET_CALLBACK_STATUSW == message ? translation.apply("WM_CAP_SET_CALLBACK_STATUSW", "Windows Capture", "Set Callback Status") : true))
            return "";
          #endif

          #ifdef WM_CAP_SET_MCI_DEVICEW
            if (not (WM_CAP_SET_MCI_DEVICEW == message ? translation.apply("WM_CAP_SET_MCI_DEVICEW", "Windows Capture", "Set MCI (Media Control Interface) Device") : true))
            return "";
          #endif

          #ifdef WM_CAP_UNICODE_START
            if (not (WM_CAP_UNICODE_START == message ? translation.apply("WM_CAP_UNICODE_START", "Windows Capture", "Unicode Start") : true))
            return "";
          #endif

          #ifdef WM_CAPTURECHANGED
            if (not (WM_CAPTURECHANGED == message ? translation.apply("WM_CAPTURECHANGED", "Windows Capture", "Changed") : true))
            return "";
          #endif

          #ifdef WM_CHANGECBCHAIN
            if (not (WM_CHANGECBCHAIN == message ? translation.apply("WM_CHANGECBCHAIN", "Windows", "Change Control Box Chain") : true))
            return "";
          #endif

          #ifdef WM_CHANGEUISTATE
            if (not (WM_CHANGEUISTATE == message ? translation.apply("WM_CHANGEUISTATE", "Windows", "Change User-Interface State") : true))
            return "";
          #endif

          #ifdef WM_CHAR
            if (not (WM_CHAR == message ? translation.apply("WM_CHAR", "Windows", "Character") : true))
            return "";
          #endif

          #ifdef WM_CHARTOITEM
            if (not (WM_CHARTOITEM == message ? translation.apply("WM_CHARTOITEM", "Windows", "Character to Item") : true))
            return "";
          #endif

          #ifdef WM_CHILDACTIVATE
            if (not (WM_CHILDACTIVATE == message ? translation.apply("WM_CHILDACTIVATE", "Windows", "Child Activate") : true))
            return "";
          #endif

          #ifdef WM_CHOOSEFONT_GETLOGFONT
            if (not (WM_CHOOSEFONT_GETLOGFONT == message ? translation.apply("WM_CHOOSEFONT_GETLOGFONT", "Windows", "Choose Font (Get Log Font)") : true))
            return "";
          #endif

          #ifdef WM_CHOOSEFONT_SETFLAGS
            if (not (WM_CHOOSEFONT_SETFLAGS == message ? translation.apply("WM_CHOOSEFONT_SETFLAGS", "Windows", "Choose Font (Set Flags)") : true))
            return "";
          #endif

          #ifdef WM_CHOOSEFONT_SETLOGFONT
            if (not (WM_CHOOSEFONT_SETLOGFONT == message ? translation.apply("WM_CHOOSEFONT_SETLOGFONT", "Windows", "Choose Font (Set Log Font)") : true))
            return "";
          #endif

          #ifdef WM_CLEAR
            if (not (WM_CLEAR == message ? translation.apply("WM_CLEAR", "Windows", "Clear") : true))
            return "";
          #endif

          #ifdef WM_CLOSE
            if (not (WM_CLOSE == message ? translation.apply("WM_CLOSE", "Windows", "Close") : true))
            return "";
          #endif

          #ifdef WM_CLOSE
            if (not (WM_CLOSE == message ? translation.apply("WM_CLOSE", "Windows", "Close") : true))
            return "";
          #endif

          #ifdef WM_COMMAND
            if (not (WM_COMMAND == message ? translation.apply("WM_COMMAND", "Windows", "Command") : true))
            return "";
          #endif

          #ifdef WM_COMMNOTIFY
            if (not (WM_COMMNOTIFY == message ? translation.apply("WM_COMMNOTIFY", "Windows", "Command Notify") : true))
            return "";
          #endif

          #ifdef WM_COMPACTING
            if (not (WM_COMPACTING == message ? translation.apply("WM_COMPACTING", "Windows", "Compacting") : true))
            return "";
          #endif

          #ifdef WM_COMPAREITEM
            if (not (WM_COMPAREITEM == message ? translation.apply("WM_COMPAREITEM", "Windows", "Compare Item") : true))
            return "";
          #endif

          #ifdef WM_CONTEXTMENU
            if (not (WM_CONTEXTMENU == message ? translation.apply("WM_CONTEXTMENU", "Windows", "Context Menu") : true))
            return "";
          #endif

          #ifdef WM_CONVERTREQUEST
            if (not (WM_CONVERTREQUEST == message ? translation.apply("WM_CONVERTREQUEST", "Windows", "Convert Request") : true))
            return "";
          #endif

          #ifdef WM_CONVERTRESULT
            if (not (WM_CONVERTRESULT == message ? translation.apply("WM_CONVERTRESULT", "Windows", "Convert Result") : true))
            return "";
          #endif

          #ifdef WM_COPY
            if (not (WM_COPY == message ? translation.apply("WM_COPY", "Windows", "Copy") : true))
            return "";
          #endif

          #ifdef WM_COPYDATA
            if (not (WM_COPYDATA == message ? translation.apply("WM_COPYDATA", "Windows", "Copy Data") : true))
            return "";
          #endif

          #ifdef WM_COPYGLOBALDATA
            if (not (WM_COPYGLOBALDATA == message ? translation.apply("WM_COPYGLOBALDATA", "Windows", "Copy Global Data") : true))
            return "";
          #endif

          #ifdef WM_CPL_LAUNCH
            if (not (WM_CPL_LAUNCH == message ? translation.apply("WM_CPL_LAUNCH", "Windows", "Control Panel Launch") : true))
            return "";
          #endif

          #ifdef WM_CPL_LAUNCHED
            if (not (WM_CPL_LAUNCHED == message ? translation.apply("WM_CPL_LAUNCHED", "Windows", "Control Panel Launched") : true))
            return "";
          #endif

          #ifdef WM_CREATE
            if (not (WM_CREATE == message ? translation.apply("WM_CREATE", "Windows", "Create") : true))
            return "";
          #endif

          #ifdef WM_CTLCOLOR
            if (not (WM_CTLCOLOR == message ? translation.apply("WM_CTLCOLOR", "Windows", "Control Color") : true))
            return "";
          #endif

          #ifdef WM_CTLCOLORBTN
            if (not (WM_CTLCOLORBTN == message ? translation.apply("WM_CTLCOLORBTN", "Windows", "Control Color Button") : true))
            return "";
          #endif

          #ifdef WM_CTLCOLORDLG
            if (not (WM_CTLCOLORDLG == message ? translation.apply("WM_CTLCOLORDLG", "Windows", "Control Color Dialog") : true))
            return "";
          #endif

          #ifdef WM_CTLCOLOREDIT
            if (not (WM_CTLCOLOREDIT == message ? translation.apply("WM_CTLCOLOREDIT", "Windows", "Control Color Editor") : true))
            return "";
          #endif

          #ifdef WM_CTLCOLORLISTBOX
            if (not (WM_CTLCOLORLISTBOX == message ? translation.apply("WM_CTLCOLORLISTBOX", "Windows", "Control Color List Box") : true))
            return "";
          #endif

          #ifdef WM_CTLCOLORMSGBOX
            if (not (WM_CTLCOLORMSGBOX == message ? translation.apply("WM_CTLCOLORMSGBOX", "Windows", "Control Color Message Box") : true))
            return "";
          #endif

          #ifdef WM_CTLCOLORSCROLLBAR
            if (not (WM_CTLCOLORSCROLLBAR == message ? translation.apply("WM_CTLCOLORSCROLLBAR", "Windows", "Control Color Scrollbar") : true))
            return "";
          #endif

          #ifdef WM_CTLCOLORSTATIC
            if (not (WM_CTLCOLORSTATIC == message ? translation.apply("WM_CTLCOLORSTATIC", "Windows", "Control Color Static") : true))
            return "";
          #endif

          #ifdef WM_CTLINIT
            if (not (WM_CTLINIT == message ? translation.apply("WM_CTLINIT", "Windows", "Control Initiation") : true))
            return "";
          #endif

          #ifdef WM_CUT
            if (not (WM_CUT == message ? translation.apply("WM_CUT", "Windows", "Cut") : true))
            return "";
          #endif

          #ifdef WM_DEADCHAR
            if (not (WM_DEADCHAR == message ? translation.apply("WM_DEADCHAR", "Windows", "Dead Character") : true))
            return "";
          #endif

          #ifdef WM_DELETEITEM
            if (not (WM_DELETEITEM == message ? translation.apply("WM_DELETEITEM", "Windows", "Delete Item") : true))
            return "";
          #endif

          #ifdef WM_DESTROY
            if (not (WM_DESTROY == message ? translation.apply("WM_DESTROY", "Windows", "Destroy") : true))
            return "";
          #endif

          #ifdef WM_DESTROY
            if (not (WM_DESTROY == message ? translation.apply("WM_DESTROY", "Windows", "Destroy") : true))
            return "";
          #endif

          #ifdef WM_DESTROYCLIPBOARD
            if (not (WM_DESTROYCLIPBOARD == message ? translation.apply("WM_DESTROYCLIPBOARD", "Windows", "Destroy Clipboard") : true))
            return "";
          #endif

          #ifdef WM_DEVICECHANGE
            if (not (WM_DEVICECHANGE == message ? translation.apply("WM_DEVICECHANGE", "Windows", "Device Change") : true))
            return "";
          #endif

          #ifdef WM_DEVMODECHANGE
            if (not (WM_DEVMODECHANGE == message ? translation.apply("WM_DEVMODECHANGE", "Windows", "Device Mode Change") : true))
            return "";
          #endif

          #ifdef WM_DISPLAYCHANGE
            if (not (WM_DISPLAYCHANGE == message ? translation.apply("WM_DISPLAYCHANGE", "Windows", "Display Change") : true))
            return "";
          #endif

          #ifdef WM_DRAWCLIPBOARD
            if (not (WM_DRAWCLIPBOARD == message ? translation.apply("WM_DRAWCLIPBOARD", "Windows", "Draw Clipboard") : true))
            return "";
          #endif

          #ifdef WM_DRAWITEM
            if (not (WM_DRAWITEM == message ? translation.apply("WM_DRAWITEM", "Windows", "Draw Item") : true))
            return "";
          #endif

          #ifdef WM_DROPFILES
            if (not (WM_DROPFILES == message ? translation.apply("WM_DROPFILES", "Windows", "Drop Files") : true))
            return "";
          #endif

          #ifdef WM_ENABLE
            if (not (WM_ENABLE == message ? translation.apply("WM_ENABLE", "Windows", "Enable") : true))
            return "";
          #endif

          #ifdef WM_ENDSESSION
            if (not (WM_ENDSESSION == message ? translation.apply("WM_ENDSESSION", "Windows", "End Session") : true))
            return "";
          #endif

          #ifdef WM_ENTERIDLE
            if (not (WM_ENTERIDLE == message ? translation.apply("WM_ENTERIDLE", "Windows", "Enter Idle") : true))
            return "";
          #endif

          #ifdef WM_ENTERMENULOOP
            if (not (WM_ENTERMENULOOP == message ? translation.apply("WM_ENTERMENULOOP", "Windows", "Enter Menu Loop") : true))
            return "";
          #endif

          #ifdef WM_ENTERSIZEMOVE
            if (not (WM_ENTERSIZEMOVE == message ? translation.apply("WM_ENTERSIZEMOVE", "Windows", "Enter Size Move") : true))
            return "";
          #endif

          #ifdef WM_ERASEBKGND
            if (not (WM_ERASEBKGND == message ? translation.apply("WM_ERASEBKGND", "Windows", "Erase Background") : true))
            return "";
          #endif

          #ifdef WM_EXITMENULOOP
            if (not (WM_EXITMENULOOP == message ? translation.apply("WM_EXITMENULOOP", "Windows", "Exit Menu Loop") : true))
            return "";
          #endif

          #ifdef WM_EXITSIZEMOVE
            if (not (WM_EXITSIZEMOVE == message ? translation.apply("WM_EXITSIZEMOVE", "Windows", "Exit Size Move") : true))
            return "";
          #endif

          #ifdef WM_FONTCHANGE
            if (not (WM_FONTCHANGE == message ? translation.apply("WM_FONTCHANGE", "Windows", "Font Change") : true))
            return "";
          #endif

          #ifdef WM_GETDLGCODE
            if (not (WM_GETDLGCODE == message ? translation.apply("WM_GETDLGCODE", "Windows", "Get Dialog Code") : true))
            return "";
          #endif

          #ifdef WM_GETFONT
            if (not (WM_GETFONT == message ? translation.apply("WM_GETFONT", "Windows", "Get Font") : true))
            return "";
          #endif

          #ifdef WM_GETHOTKEY
            if (not (WM_GETHOTKEY == message ? translation.apply("WM_GETHOTKEY", "Windows", "Get Hotkey") : true))
            return "";
          #endif

          #ifdef WM_GETICON
            if (not (WM_GETICON == message ? translation.apply("WM_GETICON", "Windows", "Get Icon") : true))
            return "";
          #endif

          #ifdef WM_GETMINMAXINFO
            if (not (WM_GETMINMAXINFO == message ? translation.apply("WM_GETMINMAXINFO", "Windows", "Get Min-Maximum Information") : true))
            return "";
          #endif

          #ifdef WM_GETOBJECT
            if (not (WM_GETOBJECT == message ? translation.apply("WM_GETOBJECT", "Windows", "Get Object") : true))
            return "";
          #endif

          #ifdef WM_GETTEXT
            if (not (WM_GETTEXT == message ? translation.apply("WM_GETTEXT", "Windows", "Get Text") : true))
            return "";
          #endif

          #ifdef WM_GETTEXTLENGTH
            if (not (WM_GETTEXTLENGTH == message ? translation.apply("WM_GETTEXTLENGTH", "Windows", "Get Text Length") : true))
            return "";
          #endif

          #ifdef WM_GLOBALRCCHANGE
            if (not (WM_GLOBALRCCHANGE == message ? translation.apply("WM_GLOBALRCCHANGE", "Windows", "Global RC Change") : true))
            return "";
          #endif

          #ifdef WM_HANDHELDFIRST
            if (not (WM_HANDHELDFIRST == message ? translation.apply("WM_HANDHELDFIRST", "Windows", "Hand-Held [FIRST]") : true))
            return "";
          #endif

          #ifdef WM_HANDHELDLAST
            if (not (WM_HANDHELDLAST == message ? translation.apply("WM_HANDHELDLAST", "Windows", "Hand-Held [LAST]") : true))
            return "";
          #endif

          #ifdef WM_HEDITCTL
            if (not (WM_HEDITCTL == message ? translation.apply("WM_HEDITCTL", "Windows", "Hand-Editing Control") : true))
            return "";
          #endif

          #ifdef WM_HELP
            if (not (WM_HELP == message ? translation.apply("WM_HELP", "Windows", "Help") : true))
            return "";
          #endif

          #ifdef WM_HOOKRCRESULT
            if (not (WM_HOOKRCRESULT == message ? translation.apply("WM_HOOKRCRESULT", "Windows", "Hook RC Result") : true))
            return "";
          #endif

          #ifdef WM_HOTKEY
            if (not (WM_HOTKEY == message ? translation.apply("WM_HOTKEY", "Windows", "Hotkey") : true))
            return "";
          #endif

          #ifdef WM_HSCROLL
            if (not (WM_HSCROLL == message ? translation.apply("WM_HSCROLL", "Windows", "Horizontal Scroll") : true))
            return "";
          #endif

          #ifdef WM_HSCROLLCLIPBOARD
            if (not (WM_HSCROLLCLIPBOARD == message ? translation.apply("WM_HSCROLLCLIPBOARD", "Windows", "Horizontal Scroll Clipboard") : true))
            return "";
          #endif

          #ifdef WM_ICONERASEBKGND
            if (not (WM_ICONERASEBKGND == message ? translation.apply("WM_ICONERASEBKGND", "Windows", "Icon Erase Background") : true))
            return "";
          #endif

          #ifdef WM_IME_CHAR
            if (not (WM_IME_CHAR == message ? translation.apply("WM_IME_CHAR", "Windows", "IME (Input Method Encoding) Character") : true))
            return "";
          #endif

          #ifdef WM_IME_COMPOSITION
            if (not (WM_IME_COMPOSITION == message ? translation.apply("WM_IME_COMPOSITION", "Windows", "IME (Input Method Encoding) Composition [(Key) LAST]") : true))
            return "";
          #endif

          #ifdef WM_IME_COMPOSITIONFULL
            if (not (WM_IME_COMPOSITIONFULL == message ? translation.apply("WM_IME_COMPOSITIONFULL", "Windows", "IME (Input Method Encoding) Composition Full") : true))
            return "";
          #endif

          #ifdef WM_IME_CONTROL
            if (not (WM_IME_CONTROL == message ? translation.apply("WM_IME_CONTROL", "Windows", "IME (Input Method Encoding) Control") : true))
            return "";
          #endif

          #ifdef WM_IME_ENDCOMPOSITION
            if (not (WM_IME_ENDCOMPOSITION == message ? translation.apply("WM_IME_ENDCOMPOSITION", "Windows", "IME (Input Method Encoding) End Composition") : true))
            return "";
          #endif

          #ifdef WM_IME_NOTIFY
            if (not (WM_IME_NOTIFY == message ? translation.apply("WM_IME_NOTIFY", "Windows", "IME (Input Method Encoding) Notify") : true))
            return "";
          #endif

          #ifdef WM_IME_REPORT
            if (not (WM_IME_REPORT == message ? translation.apply("WM_IME_REPORT", "Windows", "IME (Input Method Encoding) Report") : true))
            return "";
          #endif

          #ifdef WM_IME_REQUEST
            if (not (WM_IME_REQUEST == message ? translation.apply("WM_IME_REQUEST", "Windows", "IME (Input Method Encoding) Request") : true))
            return "";
          #endif

          #ifdef WM_IME_SELECT
            if (not (WM_IME_SELECT == message ? translation.apply("WM_IME_SELECT", "Windows", "IME (Input Method Encoding) Select") : true))
            return "";
          #endif

          #ifdef WM_IME_SETCONTEXT
            if (not (WM_IME_SETCONTEXT == message ? translation.apply("WM_IME_SETCONTEXT", "Windows", "IME (Input Method Encoding) Set Context") : true))
            return "";
          #endif

          #ifdef WM_IME_STARTCOMPOSITION
            if (not (WM_IME_STARTCOMPOSITION == message ? translation.apply("WM_IME_STARTCOMPOSITION", "Windows", "IME (Input Method Encoding) Start Composition") : true))
            return "";
          #endif

          #ifdef WM_IMEKEYDOWN
            if (not (WM_IMEKEYDOWN == message ? translation.apply("WM_IMEKEYDOWN", "Windows", "IME (Input Method Encoding) Key Down") : true))
            return "";
          #endif

          #ifdef WM_IMEKEYUP
            if (not (WM_IMEKEYUP == message ? translation.apply("WM_IMEKEYUP", "Windows", "IME (Input Method Encoding) Key Up") : true))
            return "";
          #endif

          #ifdef WM_INITDIALOG
            if (not (WM_INITDIALOG == message ? translation.apply("WM_INITDIALOG", "Windows", "Initiate Dialog") : true))
            return "";
          #endif

          #ifdef WM_INITMENU
            if (not (WM_INITMENU == message ? translation.apply("WM_INITMENU", "Windows", "Initiate Menu") : true))
            return "";
          #endif

          #ifdef WM_INITMENUPOPUP
            if (not (WM_INITMENUPOPUP == message ? translation.apply("WM_INITMENUPOPUP", "Windows", "Initiate Menu Pop-Up") : true))
            return "";
          #endif

          #ifdef WM_INPUT
            if (not (WM_INPUT == message ? translation.apply("WM_INPUT", "Windows", "Input") : true))
            return "";
          #endif

          #ifdef WM_INPUTLANGCHANGE
            if (not (WM_INPUTLANGCHANGE == message ? translation.apply("WM_INPUTLANGCHANGE", "Windows", "Input Language Change") : true))
            return "";
          #endif

          #ifdef WM_INPUTLANGCHANGEREQUEST
            if (not (WM_INPUTLANGCHANGEREQUEST == message ? translation.apply("WM_INPUTLANGCHANGEREQUEST", "Windows", "Input Language Change Request") : true))
            return "";
          #endif

          #ifdef WM_INTERIM
            if (not (WM_INTERIM == message ? translation.apply("WM_INTERIM", "Windows", "Interim") : true))
            return "";
          #endif

          #ifdef WM_KEYDOWN
            if (not (WM_KEYDOWN == message ? translation.apply("WM_KEYDOWN", "Windows", "Key Down") : true))
            return "";
          #endif

          #ifdef WM_KEYFIRST
            if (not (WM_KEYFIRST == message ? translation.apply("WM_KEYFIRST", "Windows", "Key 1st") : true))
            return "";
          #endif

          #ifdef WM_KEYLAST
            if (not (WM_KEYLAST == message ? translation.apply("WM_KEYLAST", "Windows", "Key nth") : true))
            return "";
          #endif

          #ifdef WM_KEYUP
            if (not (WM_KEYUP == message ? translation.apply("WM_KEYUP", "Windows", "Key Up") : true))
            return "";
          #endif

          #ifdef WM_KILLFOCUS
            if (not (WM_KILLFOCUS == message ? translation.apply("WM_KILLFOCUS", "Windows", "Kill Focus") : true))
            return "";
          #endif

          #ifdef WM_LBUTTONDBLCLK
            if (not (WM_LBUTTONDBLCLK == message ? translation.apply("WM_LBUTTONDBLCLK", "Windows", "Left (Mouse) Button Double-Click") : true))
            return "";
          #endif

          #ifdef WM_LBUTTONDOWN
            if (not (WM_LBUTTONDOWN == message ? translation.apply("WM_LBUTTONDOWN", "Windows", "Left (Mouse) Button Down") : true))
            return "";
          #endif

          #ifdef WM_LBUTTONUP
            if (not (WM_LBUTTONUP == message ? translation.apply("WM_LBUTTONUP", "Windows", "Left (Mouse) Button Up") : true))
            return "";
          #endif

          #ifdef WM_MBUTTONDBLCLK
            if (not (WM_MBUTTONDBLCLK == message ? translation.apply("WM_MBUTTONDBLCLK", "Windows", "Middle (Mouse) Button Double-Click") : true))
            return "";
          #endif

          #ifdef WM_MBUTTONDOWN
            if (not (WM_MBUTTONDOWN == message ? translation.apply("WM_MBUTTONDOWN", "Windows", "Middle (Mouse) Button Down") : true))
            return "";
          #endif

          #ifdef WM_MBUTTONUP
            if (not (WM_MBUTTONUP == message ? translation.apply("WM_MBUTTONUP", "Windows", "Middle (Mouse) Button Up") : true))
            return "";
          #endif

          #ifdef WM_MDIACTIVATE
            if (not (WM_MDIACTIVATE == message ? translation.apply("WM_MDIACTIVATE", "Windows", "Multiple-Document Interface Activate") : true))
            return "";
          #endif

          #ifdef WM_MDICASCADE
            if (not (WM_MDICASCADE == message ? translation.apply("WM_MDICASCADE", "Windows", "Multiple-Document Interface Cascade") : true))
            return "";
          #endif

          #ifdef WM_MDICREATE
            if (not (WM_MDICREATE == message ? translation.apply("WM_MDICREATE", "Windows", "Multiple-Document Interface Create") : true))
            return "";
          #endif

          #ifdef WM_MDIDESTROY
            if (not (WM_MDIDESTROY == message ? translation.apply("WM_MDIDESTROY", "Windows", "Multiple-Document Interface Destroy") : true))
            return "";
          #endif

          #ifdef WM_MDIGETACTIVE
            if (not (WM_MDIGETACTIVE == message ? translation.apply("WM_MDIGETACTIVE", "Windows", "Multiple-Document Interface Get Active") : true))
            return "";
          #endif

          #ifdef WM_MDIICONARRANGE
            if (not (WM_MDIICONARRANGE == message ? translation.apply("WM_MDIICONARRANGE", "Windows", "Multiple-Document Interface Icon Arrange") : true))
            return "";
          #endif

          #ifdef WM_MDIMAXIMIZE
            if (not (WM_MDIMAXIMIZE == message ? translation.apply("WM_MDIMAXIMIZE", "Windows", "Multiple-Document Interface Maximize") : true))
            return "";
          #endif

          #ifdef WM_MDINEXT
            if (not (WM_MDINEXT == message ? translation.apply("WM_MDINEXT", "Windows", "Multiple-Document Interface Next") : true))
            return "";
          #endif

          #ifdef WM_MDIREFRESHMENU
            if (not (WM_MDIREFRESHMENU == message ? translation.apply("WM_MDIREFRESHMENU", "Windows", "Multiple-Document Interface Refresh Menu") : true))
            return "";
          #endif

          #ifdef WM_MDIRESTORE
            if (not (WM_MDIRESTORE == message ? translation.apply("WM_MDIRESTORE", "Windows", "Multiple-Document Interface Restore") : true))
            return "";
          #endif

          #ifdef WM_MDISETMENU
            if (not (WM_MDISETMENU == message ? translation.apply("WM_MDISETMENU", "Windows", "Multiple-Document Interface Set Menu") : true))
            return "";
          #endif

          #ifdef WM_MDITILE
            if (not (WM_MDITILE == message ? translation.apply("WM_MDITILE", "Windows", "Multiple-Document Interface Tile") : true))
            return "";
          #endif

          #ifdef WM_MEASUREITEM
            if (not (WM_MEASUREITEM == message ? translation.apply("WM_MEASUREITEM", "Windows", "Measure Item") : true))
            return "";
          #endif

          #ifdef WM_MENUCHAR
            if (not (WM_MENUCHAR == message ? translation.apply("WM_MENUCHAR", "Windows", "Menu Character") : true))
            return "";
          #endif

          #ifdef WM_MENUCOMMAND
            if (not (WM_MENUCOMMAND == message ? translation.apply("WM_MENUCOMMAND", "Windows", "Menu Command") : true))
            return "";
          #endif

          #ifdef WM_MENUDRAG
            if (not (WM_MENUDRAG == message ? translation.apply("WM_MENUDRAG", "Windows", "Menu Drag") : true))
            return "";
          #endif

          #ifdef WM_MENUGETOBJECT
            if (not (WM_MENUGETOBJECT == message ? translation.apply("WM_MENUGETOBJECT", "Windows", "Menu Get to Object") : true))
            return "";
          #endif

          #ifdef WM_MENURBUTTONUP
            if (not (WM_MENURBUTTONUP == message ? translation.apply("WM_MENURBUTTONUP", "Windows", "Menu Right (Mouse) Button Up") : true))
            return "";
          #endif

          #ifdef WM_MENUSELECT
            if (not (WM_MENUSELECT == message ? translation.apply("WM_MENUSELECT", "Windows", "Menu Select") : true))
            return "";
          #endif

          #ifdef WM_MOUSEACTIVATE
            if (not (WM_MOUSEACTIVATE == message ? translation.apply("WM_MOUSEACTIVATE", "Windows", "Mouse Activate") : true))
            return "";
          #endif

          #ifdef WM_MOUSEFIRST
            if (not (WM_MOUSEFIRST == message ? translation.apply("WM_MOUSEFIRST", "Windows", "Mouse 1st") : true))
            return "";
          #endif

          #ifdef WM_MOUSEHOVER
            if (not (WM_MOUSEHOVER == message ? translation.apply("WM_MOUSEHOVER", "Windows", "Mouse Hover") : true))
            return "";
          #endif

          #ifdef WM_MOUSELAST
            if (not (WM_MOUSELAST == message ? translation.apply("WM_MOUSELAST", "Windows", "Mouse nth") : true))
            return "";
          #endif

          #ifdef WM_MOUSELEAVE
            if (not (WM_MOUSELEAVE == message ? translation.apply("WM_MOUSELEAVE", "Windows", "Mouse Leave") : true))
            return "";
          #endif

          #ifdef WM_MOUSEWHEEL
            if (not (WM_MOUSEWHEEL == message ? translation.apply("WM_MOUSEWHEEL", "Windows", "Mouse Wheel") : true))
            return "";
          #endif

          #ifdef WM_MOVE
            if (not (WM_MOVE == message ? translation.apply("WM_MOVE", "Windows", "Move") : true))
            return "";
          #endif

          #ifdef WM_MOVING
            if (not (WM_MOVING == message ? translation.apply("WM_MOVING", "Windows", "Moving") : true))
            return "";
          #endif

          #ifdef WM_NCACTIVATE
            if (not (WM_NCACTIVATE == message ? translation.apply("WM_NCACTIVATE", "Windows", "Non-Client Activate") : true))
            return "";
          #endif

          #ifdef WM_NCCALCSIZE
            if (not (WM_NCCALCSIZE == message ? translation.apply("WM_NCCALCSIZE", "Windows", "Non-Client Calculate Size") : true))
            return "";
          #endif

          #ifdef WM_NCCREATE
            if (not (WM_NCCREATE == message ? translation.apply("WM_NCCREATE", "Windows", "Non-Client Create") : true))
            return "";
          #endif

          #ifdef WM_NCDESTROY
            if (not (WM_NCDESTROY == message ? translation.apply("WM_NCDESTROY", "Windows", "Non-Client Destroy") : true))
            return "";
          #endif

          #ifdef WM_NCHITTEST
            if (not (WM_NCHITTEST == message ? translation.apply("WM_NCHITTEST", "Windows", "Non-Client Hit-Test") : true))
            return "";
          #endif

          #ifdef WM_NCLBUTTONDBLCLK
            if (not (WM_NCLBUTTONDBLCLK == message ? translation.apply("WM_NCLBUTTONDBLCLK", "Windows", "Non-Client Left (Mouse) Button Double-Click") : true))
            return "";
          #endif

          #ifdef WM_NCLBUTTONDOWN
            if (not (WM_NCLBUTTONDOWN == message ? translation.apply("WM_NCLBUTTONDOWN", "Windows", "Non-Client Left (Mouse) Button Down") : true))
            return "";
          #endif

          #ifdef WM_NCLBUTTONUP
            if (not (WM_NCLBUTTONUP == message ? translation.apply("WM_NCLBUTTONUP", "Windows", "Non-Client Left (Mouse) Button Up") : true))
            return "";
          #endif

          #ifdef WM_NCMBUTTONDBLCLK
            if (not (WM_NCMBUTTONDBLCLK == message ? translation.apply("WM_NCMBUTTONDBLCLK", "Windows", "Non-Client Middle (Mouse) Button Double-Click") : true))
            return "";
          #endif

          #ifdef WM_NCMBUTTONDOWN
            if (not (WM_NCMBUTTONDOWN == message ? translation.apply("WM_NCMBUTTONDOWN", "Windows", "Non-Client Middle (Mouse) Button Down") : true))
            return "";
          #endif

          #ifdef WM_NCMBUTTONUP
            if (not (WM_NCMBUTTONUP == message ? translation.apply("WM_NCMBUTTONUP", "Windows", "Non-Client Middle (Mouse) Button Up") : true))
            return "";
          #endif

          #ifdef WM_NCMOUSEHOVER
            if (not (WM_NCMOUSEHOVER == message ? translation.apply("WM_NCMOUSEHOVER", "Windows", "Non-Client Mouse Hover") : true))
            return "";
          #endif

          #ifdef WM_NCMOUSELEAVE
            if (not (WM_NCMOUSELEAVE == message ? translation.apply("WM_NCMOUSELEAVE", "Windows", "Non-Client Mouse Leave") : true))
            return "";
          #endif

          #ifdef WM_NCMOUSEMOVE
            if (not (WM_NCMOUSEMOVE == message ? translation.apply("WM_NCMOUSEMOVE", "Windows", "Non-Client Mouse Mouse") : true))
            return "";
          #endif

          #ifdef WM_NCPAINT
            if (not (WM_NCPAINT == message ? translation.apply("WM_NCPAINT", "Windows", "Non-Client Paint") : true))
            return "";
          #endif

          #ifdef WM_NCRBUTTONDBLCLK
            if (not (WM_NCRBUTTONDBLCLK == message ? translation.apply("WM_NCRBUTTONDBLCLK", "Windows", "Non-Client Right (Mouse) Button Double-Click") : true))
            return "";
          #endif

          #ifdef WM_NCRBUTTONDOWN
            if (not (WM_NCRBUTTONDOWN == message ? translation.apply("WM_NCRBUTTONDOWN", "Windows", "Non-Client Right (Mouse) Button Down") : true))
            return "";
          #endif

          #ifdef WM_NCRBUTTONUP
            if (not (WM_NCRBUTTONUP == message ? translation.apply("WM_NCRBUTTONUP", "Windows", "Non-Client Right (Mouse) Button Up") : true))
            return "";
          #endif

          #ifdef WM_NCXBUTTONDBLCLK
            if (not (WM_NCXBUTTONDBLCLK == message ? translation.apply("WM_NCXBUTTONDBLCLK", "Windows", "Non-Client X (Mouse) Button Double-Click") : true))
            return "";
          #endif

          #ifdef WM_NCXBUTTONDOWN
            if (not (WM_NCXBUTTONDOWN == message ? translation.apply("WM_NCXBUTTONDOWN", "Windows", "Non-Client X (Mouse) Button Down") : true))
            return "";
          #endif

          #ifdef WM_NCXBUTTONUP
            if (not (WM_NCXBUTTONUP == message ? translation.apply("WM_NCXBUTTONUP", "Windows", "Non-Client X (Mouse) Button Up") : true))
            return "";
          #endif

          #ifdef WM_NEXTDLGCTL
            if (not (WM_NEXTDLGCTL == message ? translation.apply("WM_NEXTDLGCTL", "Windows", "Next Dialog Control") : true))
            return "";
          #endif

          #ifdef WM_NEXTMENU
            if (not (WM_NEXTMENU == message ? translation.apply("WM_NEXTMENU", "Windows", "Next Menu") : true))
            return "";
          #endif

          #ifdef WM_NOTIFY
            if (not (WM_NOTIFY == message ? translation.apply("WM_NOTIFY", "Windows", "Notify") : true))
            return "";
          #endif

          #ifdef WM_NOTIFYFORMAT
            if (not (WM_NOTIFYFORMAT == message ? translation.apply("WM_NOTIFYFORMAT", "Windows", "Notify Format") : true))
            return "";
          #endif

          #ifdef WM_NULL
            if (not (WM_NULL == message ? translation.apply("WM_NULL", "Windows", "[NULL]") : true))
            return "";
          #endif

          #ifdef WM_PAINT
            if (not (WM_PAINT == message ? translation.apply("WM_PAINT", "Windows", "Paint") : true))
            return "";
          #endif

          #ifdef WM_PAINTCLIPBOARD
            if (not (WM_PAINTCLIPBOARD == message ? translation.apply("WM_PAINTCLIPBOARD", "Windows", "Paint Clipboard") : true))
            return "";
          #endif

          #ifdef WM_PAINTICON
            if (not (WM_PAINTICON == message ? translation.apply("WM_PAINTICON", "Windows", "Paint Icon") : true))
            return "";
          #endif

          #ifdef WM_PALETTECHANGED
            if (not (WM_PALETTECHANGED == message ? translation.apply("WM_PALETTECHANGED", "Windows", "Palette Changed") : true))
            return "";
          #endif

          #ifdef WM_PALETTEISCHANGING
            if (not (WM_PALETTEISCHANGING == message ? translation.apply("WM_PALETTEISCHANGING", "Windows", "Palette is Changing") : true))
            return "";
          #endif

          #ifdef WM_PARENTNOTIFY
            if (not (WM_PARENTNOTIFY == message ? translation.apply("WM_PARENTNOTIFY", "Windows", "Parent Notify") : true))
            return "";
          #endif

          #ifdef WM_PASTE
            if (not (WM_PASTE == message ? translation.apply("WM_PASTE", "Windows", "Paste") : true))
            return "";
          #endif

          #ifdef WM_PENCTL
            if (not (WM_PENCTL == message ? translation.apply("WM_PENCTL", "Windows", "Pen Control") : true))
            return "";
          #endif

          #ifdef WM_PENEVENT
            if (not (WM_PENEVENT == message ? translation.apply("WM_PENEVENT", "Windows", "Pen Event") : true))
            return "";
          #endif

          #ifdef WM_PENMISC
            if (not (WM_PENMISC == message ? translation.apply("WM_PENMISC", "Windows", "Pen Miscellaneous") : true))
            return "";
          #endif

          #ifdef WM_PENMISCINFO
            if (not (WM_PENMISCINFO == message ? translation.apply("WM_PENMISCINFO", "Windows", "Pen Miscellaneous Information") : true))
            return "";
          #endif

          #ifdef WM_PENWINFIRST
            if (not (WM_PENWINFIRST == message ? translation.apply("WM_PENWINFIRST", "Windows", "Pen [FIRST]") : true))
            return "";
          #endif

          #ifdef WM_PENWINLAST
            if (not (WM_PENWINLAST == message ? translation.apply("WM_PENWINLAST", "Windows", "Pen [LAST]") : true))
            return "";
          #endif

          #ifdef WM_POWER
            if (not (WM_POWER == message ? translation.apply("WM_POWER", "Windows", "Power") : true))
            return "";
          #endif

          #ifdef WM_POWERBROADCAST
            if (not (WM_POWERBROADCAST == message ? translation.apply("WM_POWERBROADCAST", "Windows", "Power Broadcast") : true))
            return "";
          #endif

          #ifdef WM_PRINT
            if (not (WM_PRINT == message ? translation.apply("WM_PRINT", "Windows", "Print") : true))
            return "";
          #endif

          #ifdef WM_PRINTCLIENT
            if (not (WM_PRINTCLIENT == message ? translation.apply("WM_PRINTCLIENT", "Windows", "Print Client") : true))
            return "";
          #endif

          #ifdef WM_PSD_ENVSTAMPRECT
            if (not (WM_PSD_ENVSTAMPRECT == message ? translation.apply("WM_PSD_ENVSTAMPRECT", "Windows Page Setup Dialog", "Envelope Stamp Rectangle") : true))
            return "";
          #endif

          #ifdef WM_PSD_FULLPAGERECT
            if (not (WM_PSD_FULLPAGERECT == message ? translation.apply("WM_PSD_FULLPAGERECT", "Windows Page Setup Dialog", "Full Page Rectangle") : true))
            return "";
          #endif

          #ifdef WM_PSD_GREEKTEXTRECT
            if (not (WM_PSD_GREEKTEXTRECT == message ? translation.apply("WM_PSD_GREEKTEXTRECT", "Windows Page Setup Dialog", "Greek Text Rectangle") : true))
            return "";
          #endif

          #ifdef WM_PSD_MARGINRECT
            if (not (WM_PSD_MARGINRECT == message ? translation.apply("WM_PSD_MARGINRECT", "Windows Page Setup Dialog", "Margin Rectangle") : true))
            return "";
          #endif

          #ifdef WM_PSD_MINMARGINRECT
            if (not (WM_PSD_MINMARGINRECT == message ? translation.apply("WM_PSD_MINMARGINRECT", "Windows Page Setup Dialog", "Minimum Margin Rectangle") : true))
            return "";
          #endif

          #ifdef WM_PSD_PAGESETUPDLG
            if (not (WM_PSD_PAGESETUPDLG == message ? translation.apply("WM_PSD_PAGESETUPDLG", "Windows Page Setup Dialog", "Page Setup Dialog") : true))
            return "";
          #endif

          #ifdef WM_PSD_YAFULLPAGERECT
            if (not (WM_PSD_YAFULLPAGERECT == message ? translation.apply("WM_PSD_YAFULLPAGERECT", "Windows Page Setup Dialog", "Full Page Rectangle") : true))
            return "";
          #endif

          #ifdef WM_QUERYDRAGICON
            if (not (WM_QUERYDRAGICON == message ? translation.apply("WM_QUERYDRAGICON", "Windows", "Query Drag Icon") : true))
            return "";
          #endif

          #ifdef WM_QUERYENDSESSION
            if (not (WM_QUERYENDSESSION == message ? translation.apply("WM_QUERYENDSESSION", "Windows", "Query End Session") : true))
            return "";
          #endif

          #ifdef WM_QUERYNEWPALETTE
            if (not (WM_QUERYNEWPALETTE == message ? translation.apply("WM_QUERYNEWPALETTE", "Windows", "Query New Palette") : true))
            return "";
          #endif

          #ifdef WM_QUERYOPEN
            if (not (WM_QUERYOPEN == message ? translation.apply("WM_QUERYOPEN", "Windows", "Query Open") : true))
            return "";
          #endif

          #ifdef WM_QUERYUISTATE
            if (not (WM_QUERYUISTATE == message ? translation.apply("WM_QUERYUISTATE", "Windows", "Query User-Interface State") : true))
            return "";
          #endif

          #ifdef WM_QUEUESYNC
            if (not (WM_QUEUESYNC == message ? translation.apply("WM_QUEUESYNC", "Windows", "Queue Synchronization") : true))
            return "";
          #endif

          #ifdef WM_QUIT
            if (not (WM_QUIT == message ? translation.apply("WM_QUIT", "Windows", "Quit") : true))
            return "";
          #endif

          #ifdef WM_RASDIALEVENT
            if (not (WM_RASDIALEVENT == message ? translation.apply("WM_RASDIALEVENT", "Windows", "Routing & Remote Access Service Dial Event") : true))
            return "";
          #endif

          #ifdef WM_RBUTTONDBLCLK
            if (not (WM_RBUTTONDBLCLK == message ? translation.apply("WM_RBUTTONDBLCLK", "Windows", "Right (Mouse) Button Double-Click") : true))
            return "";
          #endif

          #ifdef WM_RBUTTONDOWN
            if (not (WM_RBUTTONDOWN == message ? translation.apply("WM_RBUTTONDOWN", "Windows", "Right (Mouse) Button Down") : true))
            return "";
          #endif

          #ifdef WM_RBUTTONUP
            if (not (WM_RBUTTONUP == message ? translation.apply("WM_RBUTTONUP", "Windows", "Right (Mouse) Button Up") : true))
            return "";
          #endif

          #ifdef WM_RCRESULT
            if (not (WM_RCRESULT == message ? translation.apply("WM_RCRESULT", "Windows", "RC Result") : true))
            return "";
          #endif

          #ifdef WM_RENDERALLFORMATS
            if (not (WM_RENDERALLFORMATS == message ? translation.apply("WM_RENDERALLFORMATS", "Windows", "Render All Formats") : true))
            return "";
          #endif

          #ifdef WM_RENDERFORMAT
            if (not (WM_RENDERFORMAT == message ? translation.apply("WM_RENDERFORMAT", "Windows", "Render Format") : true))
            return "";
          #endif

          #ifdef WM_SETCURSOR
            if (not (WM_SETCURSOR == message ? translation.apply("WM_SETCURSOR", "Windows", "Set Cursor") : true))
            return "";
          #endif

          #ifdef WM_SETFOCUS
            if (not (WM_SETFOCUS == message ? translation.apply("WM_SETFOCUS", "Windows", "Set Focus") : true))
            return "";
          #endif

          #ifdef WM_SETFONT
            if (not (WM_SETFONT == message ? translation.apply("WM_SETFONT", "Windows", "Set Font") : true))
            return "";
          #endif

          #ifdef WM_SETHOTKEY
            if (not (WM_SETHOTKEY == message ? translation.apply("WM_SETHOTKEY", "Windows", "Set Hotkey") : true))
            return "";
          #endif

          #ifdef WM_SETICON
            if (not (WM_SETICON == message ? translation.apply("WM_SETICON", "Windows", "Set Icon") : true))
            return "";
          #endif

          #ifdef WM_SETREDRAW
            if (not (WM_SETREDRAW == message ? translation.apply("WM_SETREDRAW", "Windows", "Set Redraw") : true))
            return "";
          #endif

          #ifdef WM_SETTEXT
            if (not (WM_SETTEXT == message ? translation.apply("WM_SETTEXT", "Windows", "Set Text") : true))
            return "";
          #endif

          #ifdef WM_SHOWWINDOW
            if (not (WM_SHOWWINDOW == message ? translation.apply("WM_SHOWWINDOW", "Windows", "Show Window") : true))
            return "";
          #endif

          #ifdef WM_SIZE
            if (not (WM_SIZE == message ? translation.apply("WM_SIZE", "Windows", "Size") : true))
            return "";
          #endif

          #ifdef WM_SIZECLIPBOARD
            if (not (WM_SIZECLIPBOARD == message ? translation.apply("WM_SIZECLIPBOARD", "Windows", "Size Clipboard") : true))
            return "";
          #endif

          #ifdef WM_SIZING
            if (not (WM_SIZING == message ? translation.apply("WM_SIZING", "Windows", "Sizing") : true))
            return "";
          #endif

          #ifdef WM_SKB
            if (not (WM_SKB == message ? translation.apply("WM_SKB", "Windows", "SketchUp Backup") : true))
            return "";
          #endif

          #ifdef WM_SPOOLERSTATUS
            if (not (WM_SPOOLERSTATUS == message ? translation.apply("WM_SPOOLERSTATUS", "Windows", "Spooler Status") : true))
            return "";
          #endif

          #ifdef WM_STYLECHANGED
            if (not (WM_STYLECHANGED == message ? translation.apply("WM_STYLECHANGED", "Windows", "Style Changed") : true))
            return "";
          #endif

          #ifdef WM_STYLECHANGING
            if (not (WM_STYLECHANGING == message ? translation.apply("WM_STYLECHANGING", "Windows", "Style Changing") : true))
            return "";
          #endif

          #ifdef WM_SYNCPAINT
            if (not (WM_SYNCPAINT == message ? translation.apply("WM_SYNCPAINT", "Windows", "Synchronized Paint") : true))
            return "";
          #endif

          #ifdef WM_SYSCHAR
            if (not (WM_SYSCHAR == message ? translation.apply("WM_SYSCHAR", "Windows", "System Character") : true))
            return "";
          #endif

          #ifdef WM_SYSCOLORCHANGE
            if (not (WM_SYSCOLORCHANGE == message ? translation.apply("WM_SYSCOLORCHANGE", "Windows", "System Color Change") : true))
            return "";
          #endif

          #ifdef WM_SYSCOMMAND
            if (not (WM_SYSCOMMAND == message ? translation.apply("WM_SYSCOMMAND", "Windows", "System Command") : true))
            return "";
          #endif

          #ifdef WM_SYSDEADCHAR
            if (not (WM_SYSDEADCHAR == message ? translation.apply("WM_SYSDEADCHAR", "Windows", "System Dead Character") : true))
            return "";
          #endif

          #ifdef WM_SYSKEYDOWN
            if (not (WM_SYSKEYDOWN == message ? translation.apply("WM_SYSKEYDOWN", "Windows", "System Key Down") : true))
            return "";
          #endif

          #ifdef WM_SYSKEYUP
            if (not (WM_SYSKEYUP == message ? translation.apply("WM_SYSKEYUP", "Windows", "System Key Up") : true))
            return "";
          #endif

          #ifdef WM_SYSTIMER
            if (not (WM_SYSTIMER == message ? translation.apply("WM_SYSTIMER", "Windows", "System Timer") : true))
            return "";
          #endif

          #ifdef WM_TCARD
            if (not (WM_TCARD == message ? translation.apply("WM_TCARD", "Windows", "Text Card") : true))
            return "";
          #endif

          #ifdef WM_TIMECHANGE
            if (not (WM_TIMECHANGE == message ? translation.apply("WM_TIMECHANGE", "Windows", "Time Change") : true))
            return "";
          #endif

          #ifdef WM_TIMER
            if (not (WM_TIMER == message ? translation.apply("WM_TIMER", "Windows", "Timer") : true))
            return "";
          #endif

          #ifdef WM_UNDO
            if (not (WM_UNDO == message ? translation.apply("WM_UNDO", "Windows", "Undo") : true))
            return "";
          #endif

          #ifdef WM_UNICHAR
            if (not (WM_UNICHAR == message ? translation.apply("WM_UNICHAR", "Windows", "Unicode Character") : true))
            return "";
          #endif

          #ifdef WM_UNINITMENUPOPUP
            if (not (WM_UNINITMENUPOPUP == message ? translation.apply("WM_UNINITMENUPOPUP", "Windows", "Uninitiate Menu Pop-Up") : true))
            return "";
          #endif

          #ifdef WM_UPDATEUISTATE
            if (not (WM_UPDATEUISTATE == message ? translation.apply("WM_UPDATEUISTATE", "Windows", "Update UI State") : true))
            return "";
          #endif

          #ifdef WM_USER
            if (not (WM_USER == message ? translation.apply("WM_USER", "Windows", "User") : true))
            return "";
          #endif

          #ifdef WM_USERCHANGED
            if (not (WM_USERCHANGED == message ? translation.apply("WM_USERCHANGED", "Windows", "User Changed") : true))
            return "";
          #endif

          #ifdef WM_VKEYTOITEM
            if (not (WM_VKEYTOITEM == message ? translation.apply("WM_VKEYTOITEM", "Windows", "Virtual Key to Item") : true))
            return "";
          #endif

          #ifdef WM_VSCROLL
            if (not (WM_VSCROLL == message ? translation.apply("WM_VSCROLL", "Windows", "Vertical Scroll") : true))
            return "";
          #endif

          #ifdef WM_VSCROLLCLIPBOARD
            if (not (WM_VSCROLLCLIPBOARD == message ? translation.apply("WM_VSCROLLCLIPBOARD", "Windows", "Vertical Scroll Clipboard") : true))
            return "";
          #endif

          #ifdef WM_WINDOWPOSCHANGED
            if (not (WM_WINDOWPOSCHANGED == message ? translation.apply("WM_WINDOWPOSCHANGED", "Windows", "Window Position Changed") : true))
            return "";
          #endif

          #ifdef WM_WINDOWPOSCHANGING
            if (not (WM_WINDOWPOSCHANGING == message ? translation.apply("WM_WINDOWPOSCHANGING", "Windows", "Window Position Changing") : true))
            return "";
          #endif

          #ifdef WM_WININICHANGE
            if (not (WM_WININICHANGE == message ? translation.apply("WM_WININICHANGE", "Windows", "Windows INI Change") : true))
            return "";
          #endif

          #ifdef WM_WNT_CONVERTREQUESTEX
            if (not (WM_WNT_CONVERTREQUESTEX == message ? translation.apply("WM_WNT_CONVERTREQUESTEX", "Windows", "Convert Request") : true))
            return "";
          #endif

          #ifdef WM_XBUTTONDOWN
            if (not (WM_XBUTTONDOWN == message ? translation.apply("WM_XBUTTONDOWN", "Windows", "Extended Button Down") : true))
            return "";
          #endif

          #ifdef WM_XBUTTONUP
            if (not (WM_XBUTTONUP == message ? translation.apply("WM_XBUTTONUP", "Windows", "Extended Button Up") : true))
            return "";
          #endif

          if (0u == translation.length or translation.length == sizeof translation.value / sizeof(char))
            return NULL;

          translation.value[++translation.length] = '\0';
          return translation.value;
        }
      };

      std::size_t       messageLength           = 0u;
      std::size_t const messageMaximum          = (((static_cast<std::size_t>(1u) << ((CHAR_BIT * sizeof message) - 1u)) - 1u) << 1u) + 1u;
      std::size_t       parameterLength         = 0u;
      std::size_t       parameterMaximum        = (((static_cast<std::size_t>(1u) << ((CHAR_BIT * sizeof parameter) - 1u)) - 1u) << 1u) + 1u;
      std::size_t       subparameterLength      = 0u;
      std::size_t const subparameterMaximum     = (((static_cast<std::size_t>(1u) << ((CHAR_BIT * sizeof subparameter) - 1u)) - 1u) << 1u) + 1u;
      char const       *translation             = output::translate(message);
      std::size_t       windowHandleLength      = 0u;
      std::size_t const windowHandleMaximum     = (((static_cast<std::size_t>(1u) << ((CHAR_BIT * sizeof windowHandle) - 1u)) - 1u) << 1u) + 1u;
      static LPWSTR     windowText              = NULL; // ->> Ideally `HeapFree(…)`-ed on program termination
      bool              windowTextAcquired      = false;
      static SIZE_T     windowTextCapacity      = 0L;
      static HANDLE     windowTextHeap          = NULL; // ->> Ideally `HeapDestroy(…)`-ed on program termination
      LRESULT           windowTextLength        = 0L;   // --> int
      LRESULT const     windowTextLengthMaximum = (static_cast<std::size_t>(1u) << ((CHAR_BIT * sizeof(LRESULT)) - 1u)) - 1u;
      SIZE_T            windowTextSize          = 0u;

      // ... --> …Length = ::log16(…);
      for (std::size_t value = messageMaximum;      value; value /= 16u) ++messageLength;
      for (std::size_t value = parameterMaximum;    value; value /= 16u) ++parameterLength;
      for (std::size_t value = subparameterMaximum; value; value /= 16u) ++subparameterLength;
      for (std::size_t value = windowHandleMaximum; value; value /= 16u) ++windowHandleLength;

      // ... ->> Prevent recursive `::GetMessageW(…, WM_GETTEXT…, …WM_GETTEXT)`-to-`::SendMessage(…, WM_GETTEXT, …)` chains
      if (WM_GETTEXT != message or (windowText != static_cast<LPWSTR>(reinterpret_cast<void*>(static_cast<uintptr_t>(subparameter))) and windowTextCapacity != static_cast<SIZE_T>(parameter))) {
        // ... --> windowText… = …;
        if (NULL != windowHandle) {
          windowTextHeap = NULL == windowTextHeap ? ::HeapCreate(HEAP_NO_SERIALIZE, 0u, 0u) : windowTextHeap;
          windowTextHeap = NULL == windowTextHeap ? ::GetProcessHeap()                      : windowTextHeap;

          // ...
          if (not windowTextAcquired and NULL != windowTextHeap) {
            windowTextLength = WM_GETTEXTLENGTH != message and procedureWindowHandle != windowHandle ? ::SendMessage(windowHandle, WM_GETTEXTLENGTH, 0x00u, 0x00L) : ::DefWindowProcW(windowHandle, WM_GETTEXTLENGTH, 0x00u, 0x00L); // ->> NUL character omitted

            if (ERROR_ACCESS_DENIED != ::GetLastError())
            if (windowTextLength < windowTextLengthMaximum - 1L) {
              windowTextSize = static_cast<std::size_t>(windowTextLength + 1L);

              if (windowTextCapacity < windowTextSize) {
                LPVOID const allocation = NULL == windowText ? ::HeapAlloc(windowTextHeap, HEAP_ZERO_MEMORY, static_cast<SIZE_T>(windowTextSize) /* ->> Less than `0x7FFF8u`? */) : ::HeapReAlloc(windowTextHeap, HEAP_ZERO_MEMORY, windowText, static_cast<SIZE_T>(windowTextSize));

                // ...
                if (NULL != allocation) {
                  windowText         = static_cast<LPWSTR>(allocation);
                  windowTextCapacity = windowTextSize;
                }
              }

              // ...
              if (windowTextCapacity >= windowTextSize)
              windowTextAcquired = windowTextLength >= (
                WM_GETTEXT != message and procedureWindowHandle != windowHandle
                ? ::SendMessage   (windowHandle, WM_GETTEXT, static_cast<WPARAM>(windowTextCapacity), static_cast<LPARAM>(reinterpret_cast<uintptr_t>(static_cast<void*>(windowText))))
                : ::DefWindowProcW(windowHandle, WM_GETTEXT, static_cast<WPARAM>(windowTextCapacity), static_cast<LPARAM>(reinterpret_cast<uintptr_t>(static_cast<void*>(windowText))))
              ) ? ERROR_ACCESS_DENIED != ::GetLastError() : false;
            }
          }

          // ...
          if (not windowTextAcquired and NULL != windowTextHeap) {
            ::SetLastError(0x0000u /* --> ERROR_SUCCESS */);
            windowTextLength = WM_GETTEXTLENGTH != message and procedureWindowHandle != windowHandle ? ::GetWindowTextLengthW(windowHandle) : 0; // ->> Presumably NUL character omitted

            if (0 != windowTextLength and 0x0000u /* --> ERROR_SUCCESS */ == ::GetLastError())
            if (windowTextLength < windowTextLengthMaximum - 1L) {
              windowTextSize = static_cast<std::size_t>(windowTextLength + 1);

              if (windowTextCapacity < windowTextSize) {
                LPVOID const allocation = NULL == windowText ? ::HeapAlloc(windowTextHeap, HEAP_ZERO_MEMORY, static_cast<SIZE_T>(windowTextSize) /* ->> Less than `0x7FFF8u`? */) : ::HeapReAlloc(windowTextHeap, HEAP_ZERO_MEMORY, windowText, static_cast<SIZE_T>(windowTextSize));

                // ...
                if (NULL != allocation) {
                  windowText         = static_cast<LPWSTR>(allocation);
                  windowTextCapacity = windowTextSize;
                }
              }

              // ...
              if (windowTextCapacity >= windowTextSize)
              windowTextAcquired = WM_GETTEXT != message and procedureWindowHandle != windowHandle ? 0 != ::GetWindowTextW(windowHandle, windowText, static_cast<int>(windowTextCapacity)) : false;
            }
          }
        }

        // ... ->> Log the `message`
        if (NULL == translation)
          (void) std::fprintf(stdout, "%1.2s%0*" PRIXMAX "%1.12s%0*" PRIXMAX "%0.1s%0.1s%0.*ls%0.1s%1.16s%0*" PRIXMAX "%1.4s%0*" PRIXMAX "%1.4s",
            "0x", static_cast<int>(messageLength), static_cast<uintmax_t>(message), " {"
              "window: "
                "0x", static_cast<int>(windowHandleLength), static_cast<uintmax_t>(reinterpret_cast<uintptr_t>(static_cast<void*>(windowHandle))),         windowTextAcquired ? " " : "",
                windowTextAcquired ? "\"" : "", static_cast<int>(windowTextLength), windowTextAcquired ? windowText : L"", windowTextAcquired ? "\"" : "", ", "
              "arguments: ["
                "0x", static_cast<int>(parameterLength),    static_cast<uintmax_t>(parameter), ", "
                "0x", static_cast<int>(subparameterLength), static_cast<uintmax_t>(subparameter),
              "]"
            "}" "\r\n"
          );

        else while ('\0' != *translation) {
          char const *const messageConstantTranslation = translation;
          char const       *messageEventTranslation    = NULL;
          char const       *messageTypeTranslation     = NULL;

          // ...
          for (messageTypeTranslation  = messageConstantTranslation; '\0' != *(messageTypeTranslation++); )  continue;
          for (messageEventTranslation = messageTypeTranslation;     '\0' != *(messageEventTranslation++); ) continue;

          // ...
          if (std::fprintf(stdout, "%1.2s%0*" PRIXMAX "%1.9s%s%1.3s%s%1.2s%s%1.13s%0*" PRIXMAX "%0.1s%0.1s%0.*ls%0.1s%1.13s",
            "0x", static_cast<int>(messageLength), static_cast<uintmax_t>(message), " {"
              "name: `", messageConstantTranslation, "` \"", messageTypeTranslation, ": ", messageEventTranslation, "\"" ", "
              "window: "
                "0x", static_cast<int>(windowHandleLength), static_cast<uintmax_t>(reinterpret_cast<uintptr_t>(static_cast<void*>(windowHandle))),         windowTextAcquired ? " " : "",
                windowTextAcquired ? "\"" : "", static_cast<int>(windowTextLength), windowTextAcquired ? windowText : L"", windowTextAcquired ? "\"" : "", ", "
              "arguments: "
          ) > static_cast<int>(messageLength + windowHandleLength + 42u)) {
            switch (message) {
              case WM_CLOSE:
              case WM_DESTROY:
              case WM_GETTEXTLENGTH:
              case WM_NCDESTROY: {
                (void) std::fputs("[..., ...]", stdout);
              } break;

              case WM_GETTEXT: {
                if (std::fprintf(stdout, "%c%" PRIuMAX "%1.4s%0*" PRIXMAX "%c", '[',
                  static_cast<uintmax_t>(parameter), ", "
                  "0x", static_cast<int>(subparameterLength), static_cast<uintmax_t>(subparameter),
                ']') < static_cast<int>(subparameterLength + 6u))
                (void) std::fputs("...", stdout);
              } break;

              // CITE (Lapys) -> https://learn.microsoft.com/en-us/windows/win32/inputdev/about-keyboard-input
              case WM_KEYDOWN   :
              case WM_KEYUP     :
              case WM_SYSKEYDOWN:
              case WM_SYSKEYUP  : {
                WORD        const  keyFlags        = HIWORD(subparameter);                                                                      //
                BOOL        const  extended        = KF_EXTENDED == (LOBYTE(keyFlags) & KF_EXTENDED);                                           // ->> `TRUE` if `scanCode` has `0xE0` prefix
                BOOL        const  context         = KF_ALTDOWN  == (keyFlags         & KF_ALTDOWN);                                            // ->> `TRUE` on `VK_MENU`, always `FALSE` on `WM_KEYDOWN`
                BOOL        const  previous        = KF_REPEAT   == (keyFlags         & KF_REPEAT);                                             // ->> `TRUE` on auto-repeat
                WORD        const  repeatCount     = LOWORD(subparameter);                                                                      //
                WORD        const  scanCode        = extended ? MAKEWORD(LOBYTE(keyFlags), 0xE0u) : LOBYTE(keyFlags);                           //
                std::size_t        scanCodeLength  = 0u;                                                                                        //
                char        const *scanCodeLog     = NULL;                                                                                      //
                std::size_t const  scanCodeMaximum = (((static_cast<std::size_t>(1u) << ((CHAR_BIT * sizeof scanCode) - 1u)) - 1u) << 1u) + 1u; //
                BOOL        const  transition      = KF_UP == (keyFlags & KF_UP);                                                               // ->> `TRUE` on key release
                WORD        const  virtualKey      = LOWORD(parameter);                                                                         //
                char        const *virtualKeyLog   = NULL;                                                                                      //

                // ...
                for (std::size_t value = scanCodeMaximum; value; value /= 16u)
                  ++scanCodeLength;

                switch (scanCode) {
                  case 0x0001u:               scanCodeLog = "Key"             ": Keyboard Escape";                                     break;
                  case 0x0002u:               scanCodeLog = "Key"             ": Keyboard 1 and Bang";                                 break;
                  case 0x0003u:               scanCodeLog = "Key"             ": Keyboard 2 and At";                                   break;
                  case 0x0004u:               scanCodeLog = "Key"             ": Keyboard 3 And Hash";                                 break;
                  case 0x0005u:               scanCodeLog = "Key"             ": Keyboard 4 and Dollar";                               break;
                  case 0x0006u:               scanCodeLog = "Key"             ": Keyboard 5 and Percent";                              break;
                  case 0x0007u:               scanCodeLog = "Key"             ": Keyboard 6 and Caret";                                break;
                  case 0x0008u:               scanCodeLog = "Key"             ": Keyboard 7 and Ampersand";                            break;
                  case 0x0009u:               scanCodeLog = "Key"             ": Keyboard 8 and Star";                                 break;
                  case 0x000Au:               scanCodeLog = "Key"             ": Keyboard 9 and Left Bracket";                         break;
                  case 0x000Bu:               scanCodeLog = "Key"             ": Keyboard 0 and Right Bracket";                        break;
                  case 0x000Cu:               scanCodeLog = "Key"             ": Keyboard Dash and Underscore";                        break;
                  case 0x000Du:               scanCodeLog = "Key"             ": Keyboard Equals and Plus";                            break;
                  case 0x000Eu:               scanCodeLog = "Key"             ": Keyboard Delete";                                     break;
                  case 0x000Fu:               scanCodeLog = "Key"             ": Keyboard Tab";                                        break;
                  case 0x0010u:               scanCodeLog = "Key"             ": Keyboard Q";                                          break;
                  case 0x0011u:               scanCodeLog = "Key"             ": Keyboard W";                                          break;
                  case 0x0012u:               scanCodeLog = "Key"             ": Keyboard E";                                          break;
                  case 0x0013u:               scanCodeLog = "Key"             ": Keyboard R";                                          break;
                  case 0x0014u:               scanCodeLog = "Key"             ": Keyboard T";                                          break;
                  case 0x0015u:               scanCodeLog = "Key"             ": Keyboard Y";                                          break;
                  case 0x0016u:               scanCodeLog = "Key"             ": Keyboard U";                                          break;
                  case 0x0017u:               scanCodeLog = "Key"             ": Keyboard I";                                          break;
                  case 0x0018u:               scanCodeLog = "Key"             ": Keyboard O";                                          break;
                  case 0x0019u:               scanCodeLog = "Key"             ": Keyboard P";                                          break;
                  case 0x001Au:               scanCodeLog = "Key"             ": Keyboard Left Brace";                                 break;
                  case 0x001Bu:               scanCodeLog = "Key"             ": Keyboard Right Brace";                                break;
                  case 0x001Cu:               scanCodeLog = "Key"             ": Keyboard Return Enter";                               break;
                  case 0x001Du:               scanCodeLog = "Key"             ": Keyboard Left Control";                               break;
                  case 0x001Eu:               scanCodeLog = "Key"             ": Keyboard A";                                          break;
                  case 0x001Fu:               scanCodeLog = "Key"             ": Keyboard S";                                          break;
                  case 0x0020u:               scanCodeLog = "Key"             ": Keyboard D";                                          break;
                  case 0x0021u:               scanCodeLog = "Key"             ": Keyboard F";                                          break;
                  case 0x0022u:               scanCodeLog = "Key"             ": Keyboard G";                                          break;
                  case 0x0023u:               scanCodeLog = "Key"             ": Keyboard H";                                          break;
                  case 0x0024u:               scanCodeLog = "Key"             ": Keyboard J";                                          break;
                  case 0x0025u:               scanCodeLog = "Key"             ": Keyboard K";                                          break;
                  case 0x0026u:               scanCodeLog = "Key"             ": Keyboard L";                                          break;
                  case 0x0027u:               scanCodeLog = "Key"             ": Keyboard SemiColon and Colon";                        break;
                  case 0x0028u:               scanCodeLog = "Key"             ": Keyboard Apostrophe and Double Quotation Mark";       break;
                  case 0x0029u:               scanCodeLog = "Key"             ": Keyboard Grave Accent and Tilde";                     break;
                  case 0x002Au:               scanCodeLog = "Key"             ": Keyboard Left Shift";                                 break;
                  case 0x002Bu:               scanCodeLog = "Key"             ": Keyboard Non-United States, Keyboard Pipe and Slash"; break;
                  case 0x002Cu:               scanCodeLog = "Key"             ": Keyboard Z";                                          break;
                  case 0x002Du:               scanCodeLog = "Key"             ": Keyboard X";                                          break;
                  case 0x002Eu:               scanCodeLog = "Key"             ": Keyboard C";                                          break;
                  case 0x002Fu:               scanCodeLog = "Key"             ": Keyboard V";                                          break;
                  case 0x0030u:               scanCodeLog = "Key"             ": Keyboard B";                                          break;
                  case 0x0031u:               scanCodeLog = "Key"             ": Keyboard N";                                          break;
                  case 0x0032u:               scanCodeLog = "Key"             ": Keyboard M";                                          break;
                  case 0x0033u:               scanCodeLog = "Key"             ": Keyboard Comma";                                      break;
                  case 0x0034u:               scanCodeLog = "Key"             ": Keyboard Period";                                     break;
                  case 0x0035u:               scanCodeLog = "Key"             ": Keyboard QuestionMark";                               break;
                  case 0x0036u:               scanCodeLog = "Key"             ": Keyboard Right Shift";                                break;
                  case 0x0037u:               scanCodeLog = "Key"             ": Keypad Star";                                         break;
                  case 0x0038u:               scanCodeLog = "Key"             ": Keyboard Left Alternative";                           break;
                  case 0x0039u:               scanCodeLog = "Key"             ": Keyboard Spacebar";                                   break;
                  case 0x003Au:               scanCodeLog = "Key"             ": Keyboard Caps Lock";                                  break;
                  case 0x003Bu:               scanCodeLog = "Key"             ": Keyboard Function 1";                                 break;
                  case 0x003Cu:               scanCodeLog = "Key"             ": Keyboard Function 2";                                 break;
                  case 0x003Du:               scanCodeLog = "Key"             ": Keyboard Function 3";                                 break;
                  case 0x003Eu:               scanCodeLog = "Key"             ": Keyboard Function 4";                                 break;
                  case 0x003Fu:               scanCodeLog = "Key"             ": Keyboard Function 5";                                 break;
                  case 0x0040u:               scanCodeLog = "Key"             ": Keyboard Function 6";                                 break;
                  case 0x0041u:               scanCodeLog = "Key"             ": Keyboard Function 7";                                 break;
                  case 0x0042u:               scanCodeLog = "Key"             ": Keyboard Function 8";                                 break;
                  case 0x0043u:               scanCodeLog = "Key"             ": Keyboard Function 9";                                 break;
                  case 0x0044u:               scanCodeLog = "Key"             ": Keyboard Function 10";                                break;
                  case 0x0045u:               scanCodeLog = "Key"             ": Keyboard Pause, Keypad Number Lock and Clear";        break;
                  case 0xE045u:               scanCodeLog = "Key"             ": Keypad Number Lock and Clear";                        break;
                  case 0xE046u:               scanCodeLog = "Key"             ": Keyboard Pause";                                      break; // --> 0xE11D45u
                  case 0x0046u:               scanCodeLog = "Key"             ": Keyboard Scroll Lock";                                break;
                  case 0x0047u:               scanCodeLog = "Key"             ": Keypad 7 and Home";                                   break;
                  case 0x0048u:               scanCodeLog = "Key"             ": Keypad 8 and Up Arrow";                               break;
                  case 0x0049u:               scanCodeLog = "Key"             ": Keypad 9 and Page Up";                                break;
                  case 0x004Au:               scanCodeLog = "Key"             ": Keypad Dash";                                         break;
                  case 0x004Bu:               scanCodeLog = "Key"             ": Keypad 4 and Left Arrow";                             break;
                  case 0x004Cu:               scanCodeLog = "Key"             ": Keypad 5";                                            break;
                  case 0x004Du:               scanCodeLog = "Key"             ": Keypad 6 and Right Arrow";                            break;
                  case 0x004Eu:               scanCodeLog = "Key"             ": Keypad Plus";                                         break;
                  case 0x004Fu:               scanCodeLog = "Key"             ": Keypad 1 and End";                                    break;
                  case 0x0050u:               scanCodeLog = "Key"             ": Keypad 2 and Down Arrow";                             break;
                  case 0x0051u:               scanCodeLog = "Key"             ": Keypad 3 and Page Down";                              break;
                  case 0x0052u:               scanCodeLog = "Key"             ": Keypad 0 and Insert";                                 break;
                  case 0x0053u:               scanCodeLog = "Key"             ": Keypad Period";                                       break;
                  case 0x0054u: case 0xE037u: scanCodeLog = "Key"             ": Keyboard Print Screen";                               break;
                  case 0x0056u:               scanCodeLog = "Key"             ": Keyboard Non-United States Slash Bar";                break;
                  case 0x0057u:               scanCodeLog = "Key"             ": Keyboard Function 11";                                break;
                  case 0x0058u:               scanCodeLog = "Key"             ": Keyboard Function 12";                                break;
                  case 0x0059u:               scanCodeLog = "Key"             ": Keypad Equals";                                       break;
                  case 0x005Cu:               scanCodeLog = "Key"             ": Keyboard International 6";                            break;
                  case 0x0064u:               scanCodeLog = "Key"             ": Keyboard Function 13";                                break;
                  case 0x0065u:               scanCodeLog = "Key"             ": Keyboard Function 14";                                break;
                  case 0x0066u:               scanCodeLog = "Key"             ": Keyboard Function 15";                                break;
                  case 0x0067u:               scanCodeLog = "Key"             ": Keyboard Function 16";                                break;
                  case 0x0068u:               scanCodeLog = "Key"             ": Keyboard Function 17";                                break;
                  case 0x0069u:               scanCodeLog = "Key"             ": Keyboard Function 18";                                break;
                  case 0x006Au:               scanCodeLog = "Key"             ": Keyboard Function 19";                                break;
                  case 0x006Bu:               scanCodeLog = "Key"             ": Keyboard Function 20";                                break;
                  case 0x006Cu:               scanCodeLog = "Key"             ": Keyboard Function 21";                                break;
                  case 0x006Du:               scanCodeLog = "Key"             ": Keyboard Function 22";                                break;
                  case 0x006Eu:               scanCodeLog = "Key"             ": Keyboard Function 23";                                break;
                  case 0x0070u:               scanCodeLog = "Key"             ": Keyboard International 2";                            break;
                  case 0x0071u: case 0x00F1u: scanCodeLog = "Key"             ": Keyboard Language 2";                                 break;
                  case 0x0072u: case 0x00F2u: scanCodeLog = "Key"             ": Keyboard Language 1";                                 break;
                  case 0x0073u:               scanCodeLog = "Key"             ": Keyboard International 1";                            break;
                  case 0x0076u:               scanCodeLog = "Key"             ": Keyboard Function 24, Keyboard Language 5";           break;
                  case 0x0077u:               scanCodeLog = "Key"             ": Keyboard Language 4";                                 break;
                  case 0x0078u:               scanCodeLog = "Key"             ": Keyboard Language 3";                                 break;
                  case 0x0079u:               scanCodeLog = "Key"             ": Keyboard International 4";                            break;
                  case 0x007Bu:               scanCodeLog = "Key"             ": Keyboard International 5";                            break;
                  case 0x007Du:               scanCodeLog = "Key"             ": Keyboard International 3";                            break;
                  case 0x007Eu:               scanCodeLog = "Key"             ": Keypad Comma";                                        break;
                  case 0x00FFu:               scanCodeLog = "Key"             ": Error Roll Over";                                     break;
                  case 0xE010u:               scanCodeLog = "Consumer"        ": Scan Previous Track";                                 break;
                  case 0xE019u:               scanCodeLog = "Consumer"        ": Scan Next Track";                                     break;
                  case 0xE01Cu:               scanCodeLog = "Key"             ": Keypad Enter";                                        break;
                  case 0xE01Du:               scanCodeLog = "Key"             ": Keyboard Right Control";                              break;
                  case 0xE020u:               scanCodeLog = "Consumer"        ": Mute";                                                break;
                  case 0xE021u:               scanCodeLog = "Consumer"        ": AL Calculator";                                       break;
                  case 0xE022u:               scanCodeLog = "Consumer"        ": Play/ Pause";                                         break;
                  case 0xE024u:               scanCodeLog = "Consumer"        ": Stop";                                                break;
                  case 0xE02Eu:               scanCodeLog = "Consumer"        ": Volume Decrement";                                    break;
                  case 0xE030u:               scanCodeLog = "Consumer"        ": Volume Increment";                                    break;
                  case 0xE032u:               scanCodeLog = "Consumer"        ": AC Home";                                             break;
                  case 0xE035u:               scanCodeLog = "Key"             ": Keypad Slash";                                        break;
                  case 0xE038u:               scanCodeLog = "Key"             ": Keyboard Right Alternatives";                         break;
                  case 0xE047u:               scanCodeLog = "Key"             ": Keyboard Home";                                       break;
                  case 0xE048u:               scanCodeLog = "Key"             ": Keyboard Up Arrow";                                   break;
                  case 0xE049u:               scanCodeLog = "Key"             ": Keyboard Page Up";                                    break;
                  case 0xE04Bu:               scanCodeLog = "Key"             ": Keyboard Left Arrow";                                 break;
                  case 0xE04Du:               scanCodeLog = "Key"             ": Keyboard Right Arrow";                                break;
                  case 0xE04Fu:               scanCodeLog = "Key"             ": Keyboard End";                                        break;
                  case 0xE050u:               scanCodeLog = "Key"             ": Keyboard Down Arrow";                                 break;
                  case 0xE051u:               scanCodeLog = "Key"             ": Keyboard Page Down";                                  break;
                  case 0xE052u:               scanCodeLog = "Key"             ": Keyboard Insert";                                     break;
                  case 0xE053u:               scanCodeLog = "Key"             ": Keyboard Delete Forward";                             break;
                  case 0xE05Bu:               scanCodeLog = "Key"             ": Keyboard Left GUI";                                   break;
                  case 0xE05Cu:               scanCodeLog = "Key"             ": Keyboard Right GUI";                                  break;
                  case 0xE05Du:               scanCodeLog = "Key"             ": Keyboard Application";                                break;
                  case 0xE05Eu:               scanCodeLog = "Generic Desktop" ": System Power Down, Key: Keyboard Power";              break;
                  case 0xE05Fu:               scanCodeLog = "Generic Desktop" ": System Sleep";                                        break;
                  case 0xE063u:               scanCodeLog = "Generic Desktop" ": System Wake Up";                                      break;
                  case 0xE065u:               scanCodeLog = "Consumer"        ": AC Search";                                           break;
                  case 0xE066u:               scanCodeLog = "Consumer"        ": AC Bookmarks";                                        break;
                  case 0xE067u:               scanCodeLog = "Consumer"        ": AC Refresh";                                          break;
                  case 0xE068u:               scanCodeLog = "Consumer"        ": AC Stop";                                             break;
                  case 0xE069u:               scanCodeLog = "Consumer"        ": AC Forward";                                          break;
                  case 0xE06Au:               scanCodeLog = "Consumer"        ": AC Back";                                             break;
                  case 0xE06Bu:               scanCodeLog = "Consumer"        ": AL Local Machine Browser";                            break;
                  case 0xE06Cu:               scanCodeLog = "Consumer"        ": AL Email Reader";                                     break;
                  case 0xE06Du:               scanCodeLog = "Consumer"        ": AL Consumer Control Configuration";                   break;
                }

                // ...
                if (
                  virtualKey == 0xE1u or
                  virtualKey == 0xE6u or
                  (virtualKey >= 0x92u and virtualKey <= 0x96u) or
                  (virtualKey >= 0xE3u and virtualKey <= 0xE4u) or
                  (virtualKey >= 0xE9u and virtualKey <= 0xF5u)
                ) virtualKeyLog = "OEM-specific";

                else if (
                  virtualKey == 0xE8u or
                  (virtualKey >= 0x0Eu and virtualKey <= 0x0Fu) or
                  (virtualKey >= 0x97u and virtualKey <= 0x9Fu)
                ) virtualKeyLog = "Unassigned";

                else if (virtualKey >= 0x3Au and virtualKey <= 0x40u)
                  virtualKeyLog = "Undefined";

                else switch (virtualKey) {
                  case 0x30u: virtualKeyLog = "0"; break;
                  case 0x31u: virtualKeyLog = "1"; break;
                  case 0x32u: virtualKeyLog = "2"; break;
                  case 0x33u: virtualKeyLog = "3"; break;
                  case 0x34u: virtualKeyLog = "4"; break;
                  case 0x35u: virtualKeyLog = "5"; break;
                  case 0x36u: virtualKeyLog = "6"; break;
                  case 0x37u: virtualKeyLog = "7"; break;
                  case 0x38u: virtualKeyLog = "8"; break;
                  case 0x39u: virtualKeyLog = "9"; break;
                  case 0x41u: virtualKeyLog = "A"; break;
                  case 0x42u: virtualKeyLog = "B"; break;
                  case 0x43u: virtualKeyLog = "C"; break;
                  case 0x44u: virtualKeyLog = "D"; break;
                  case 0x45u: virtualKeyLog = "E"; break;
                  case 0x46u: virtualKeyLog = "F"; break;
                  case 0x47u: virtualKeyLog = "G"; break;
                  case 0x48u: virtualKeyLog = "H"; break;
                  case 0x49u: virtualKeyLog = "I"; break;
                  case 0x4Au: virtualKeyLog = "J"; break;
                  case 0x4Bu: virtualKeyLog = "K"; break;
                  case 0x4Cu: virtualKeyLog = "L"; break;
                  case 0x4Du: virtualKeyLog = "M"; break;
                  case 0x4Eu: virtualKeyLog = "N"; break;
                  case 0x4Fu: virtualKeyLog = "O"; break;
                  case 0x50u: virtualKeyLog = "P"; break;
                  case 0x51u: virtualKeyLog = "Q"; break;
                  case 0x52u: virtualKeyLog = "R"; break;
                  case 0x53u: virtualKeyLog = "S"; break;
                  case 0x54u: virtualKeyLog = "T"; break;
                  case 0x55u: virtualKeyLog = "U"; break;
                  case 0x56u: virtualKeyLog = "V"; break;
                  case 0x57u: virtualKeyLog = "W"; break;
                  case 0x58u: virtualKeyLog = "X"; break;
                  case 0x59u: virtualKeyLog = "Y"; break;
                  case 0x5Au: virtualKeyLog = "Z"; break;

                  case VK_CONTROL: switch (LOWORD(::MapVirtualKeyW(scanCode, MAPVK_VSC_TO_VK_EX))) {
                    case VK_LCONTROL: virtualKeyLog = "Left"  " Control"; break;
                    case VK_RCONTROL: virtualKeyLog = "Right" " Control"; break;
                    default         : virtualKeyLog =          "Control";
                  } break;

                  case VK_MENU: switch (LOWORD(::MapVirtualKeyW(scanCode, MAPVK_VSC_TO_VK_EX))) {
                    case VK_LMENU: virtualKeyLog = "Left"  " Alternative"; break;
                    case VK_RMENU: virtualKeyLog = "Right" " Alternative"; break;
                    default      : virtualKeyLog =          "Alternative";
                  } break;

                  case VK_SHIFT: switch (LOWORD(::MapVirtualKeyW(scanCode, MAPVK_VSC_TO_VK_EX))) {
                    case VK_LSHIFT: virtualKeyLog = "Left"  " Shift"; break;
                    case VK_RSHIFT: virtualKeyLog = "Right" " Shift"; break;
                    default       : virtualKeyLog =          "Shift";
                  } break;

                  case VK_ACCEPT             : virtualKeyLog = "Input Method Encoding: Accept";              break;
                  case VK_ADD                : virtualKeyLog = "Add";                                        break;
                  case VK_APPS               : virtualKeyLog = "Application";                                break;
                  case VK_ATTN               : virtualKeyLog = "Attention";                                  break;
                  case VK_BACK               : virtualKeyLog = "Backspace";                                  break;
                  case VK_BROWSER_BACK       : virtualKeyLog = "Browser: Back";                              break;
                  case VK_BROWSER_FAVORITES  : virtualKeyLog = "Browser: Favorites";                         break;
                  case VK_BROWSER_FORWARD    : virtualKeyLog = "Browser: Forward";                           break;
                  case VK_BROWSER_HOME       : virtualKeyLog = "Browser: Start and Home";                    break;
                  case VK_BROWSER_REFRESH    : virtualKeyLog = "Browser: Refresh";                           break;
                  case VK_BROWSER_SEARCH     : virtualKeyLog = "Browser: Search";                            break;
                  case VK_BROWSER_STOP       : virtualKeyLog = "Browser: Stop";                              break;
                  case VK_CANCEL             : virtualKeyLog = "Cancel, Control-Break Processing";           break;
                  case VK_CAPITAL            : virtualKeyLog = "Capital Lock";                               break;
                  case VK_CLEAR              : virtualKeyLog = "Clear";                                      break;
                  case VK_CONVERT            : virtualKeyLog = "Input Method Encoding: Convert";             break;
                  case VK_CRSEL              : virtualKeyLog = "Cursor Select";                              break;
                  case VK_DECIMAL            : virtualKeyLog = "Decimal";                                    break;
                  case VK_DELETE             : virtualKeyLog = "Delete";                                     break;
                  case VK_DIVIDE             : virtualKeyLog = "Divide";                                     break;
                  case VK_DOWN               : virtualKeyLog = "Down Arrow";                                 break;
                  case VK_END                : virtualKeyLog = "End";                                        break;
                  case VK_EREOF              : virtualKeyLog = "Erase End-of-File";                          break;
                  case VK_ESCAPE             : virtualKeyLog = "Escape";                                     break;
                  case VK_EXECUTE            : virtualKeyLog = "Execute";                                    break;
                  case VK_EXSEL              : virtualKeyLog = "Extend Selection";                           break;
                  case VK_F1                 : virtualKeyLog = "Function 1";                                 break;
                  case VK_F2                 : virtualKeyLog = "Function 2";                                 break;
                  case VK_F3                 : virtualKeyLog = "Function 3";                                 break;
                  case VK_F4                 : virtualKeyLog = "Function 4";                                 break;
                  case VK_F5                 : virtualKeyLog = "Function 5";                                 break;
                  case VK_F6                 : virtualKeyLog = "Function 6";                                 break;
                  case VK_F7                 : virtualKeyLog = "Function 7";                                 break;
                  case VK_F8                 : virtualKeyLog = "Function 8";                                 break;
                  case VK_F9                 : virtualKeyLog = "Function 9";                                 break;
                  case VK_F10                : virtualKeyLog = "Function 10";                                break;
                  case VK_F11                : virtualKeyLog = "Function 11";                                break;
                  case VK_F12                : virtualKeyLog = "Function 12";                                break;
                  case VK_F13                : virtualKeyLog = "Function 13";                                break;
                  case VK_F14                : virtualKeyLog = "Function 14";                                break;
                  case VK_F15                : virtualKeyLog = "Function 15";                                break;
                  case VK_F16                : virtualKeyLog = "Function 16";                                break;
                  case VK_F17                : virtualKeyLog = "Function 17";                                break;
                  case VK_F18                : virtualKeyLog = "Function 18";                                break;
                  case VK_F19                : virtualKeyLog = "Function 19";                                break;
                  case VK_F20                : virtualKeyLog = "Function 20";                                break;
                  case VK_F21                : virtualKeyLog = "Function 21";                                break;
                  case VK_F22                : virtualKeyLog = "Function 22";                                break;
                  case VK_F23                : virtualKeyLog = "Function 23";                                break;
                  case VK_F24                : virtualKeyLog = "Function 24";                                break;
                  case VK_FINAL              : virtualKeyLog = "Input Method Encoding: Final";               break;
                  case VK_HANGUL | VK_KANA   : virtualKeyLog = "Input Method Encoding: Hangul, Kana";        break;
                  case VK_HANJA  | VK_KANJI  : virtualKeyLog = "Input Method Encoding: Hanja, Kanji";        break;
                  case VK_HELP               : virtualKeyLog = "Help";                                       break;
                  case VK_HOME               : virtualKeyLog = "Home";                                       break;
                  case VK_IME_OFF            : virtualKeyLog = "Input Method Encoding: Off";                 break;
                  case VK_IME_ON             : virtualKeyLog = "Input Method Encoding: On";                  break;
                  case VK_INSERT             : virtualKeyLog = "Insert";                                     break;
                  case VK_JUNJA              : virtualKeyLog = "Input Method Encoding: Junja";               break;
                  case VK_LAUNCH_APP1        : virtualKeyLog = "Start Application 1";                        break;
                  case VK_LAUNCH_APP2        : virtualKeyLog = "Start Application 2";                        break;
                  case VK_LAUNCH_MAIL        : virtualKeyLog = "Start Mail";                                 break;
                  case VK_LAUNCH_MEDIA_SELECT: virtualKeyLog = "Select Media";                               break;
                  case VK_LBUTTON            : virtualKeyLog = "Left Mouse Button";                          break;
                  case VK_LCONTROL           : virtualKeyLog = "Left Control";                               break;
                  case VK_LEFT               : virtualKeyLog = "Left Arrow";                                 break;
                  case VK_LMENU              : virtualKeyLog = "Left Alternative";                           break;
                  case VK_LSHIFT             : virtualKeyLog = "Left Shift";                                 break;
                  case VK_LWIN               : virtualKeyLog = "Left Windows";                               break;
                  case VK_MBUTTON            : virtualKeyLog = "Middle Mouse Button";                        break;
                  case VK_MEDIA_NEXT_TRACK   : virtualKeyLog = "Media: Next";                                break;
                  case VK_MEDIA_PLAY_PAUSE   : virtualKeyLog = "Media: Play/ Pause";                         break;
                  case VK_MEDIA_PREV_TRACK   : virtualKeyLog = "Media: Previous";                            break;
                  case VK_MEDIA_STOP         : virtualKeyLog = "Media: Stop";                                break;
                  case VK_MODECHANGE         : virtualKeyLog = "Input Method Encoding: Mode Change Request"; break;
                  case VK_MULTIPLY           : virtualKeyLog = "Multiply";                                   break;
                  case VK_NEXT               : virtualKeyLog = "Next, Page Down";                            break;
                  case VK_NONAME             : /* Do nothing… */                                            break;
                  case VK_NONCONVERT         : virtualKeyLog = "Input Method Encoding: Non-Convert";         break;
                  case VK_NUMLOCK            : virtualKeyLog = "Number Lock";                                break;
                  case VK_NUMPAD0            : virtualKeyLog = "Number Keypad 0";                            break;
                  case VK_NUMPAD1            : virtualKeyLog = "Number Keypad 1";                            break;
                  case VK_NUMPAD2            : virtualKeyLog = "Number Keypad 2";                            break;
                  case VK_NUMPAD3            : virtualKeyLog = "Number Keypad 3";                            break;
                  case VK_NUMPAD4            : virtualKeyLog = "Number Keypad 4";                            break;
                  case VK_NUMPAD5            : virtualKeyLog = "Number Keypad 5";                            break;
                  case VK_NUMPAD6            : virtualKeyLog = "Number Keypad 6";                            break;
                  case VK_NUMPAD7            : virtualKeyLog = "Number Keypad 7";                            break;
                  case VK_NUMPAD8            : virtualKeyLog = "Number Keypad 8";                            break;
                  case VK_NUMPAD9            : virtualKeyLog = "Number Keypad 9";                            break;
                  case VK_OEM_1              : virtualKeyLog = "OEM-specific 1";                             break;
                  case VK_OEM_2              : virtualKeyLog = "OEM-specific 2";                             break;
                  case VK_OEM_3              : virtualKeyLog = "OEM-specific 3";                             break;
                  case VK_OEM_4              : virtualKeyLog = "OEM-specific 4";                             break;
                  case VK_OEM_5              : virtualKeyLog = "OEM-specific 5";                             break;
                  case VK_OEM_6              : virtualKeyLog = "OEM-specific 6";                             break;
                  case VK_OEM_7              : virtualKeyLog = "OEM-specific 7";                             break;
                  case VK_OEM_8              : virtualKeyLog = "OEM-specific 8";                             break;
                  case VK_OEM_102            : virtualKeyLog = "OEM-specific 102";                           break;
                  case VK_OEM_CLEAR          : virtualKeyLog = "Clear";                                      break;
                  case VK_OEM_COMMA          : virtualKeyLog = "OEM-specific Comma";                         break;
                  case VK_OEM_MINUS          : virtualKeyLog = "OEM-specific Minus";                         break;
                  case VK_OEM_PERIOD         : virtualKeyLog = "OEM-specific Period";                        break;
                  case VK_OEM_PLUS           : virtualKeyLog = "OEM-specific Plus";                          break;
                  case VK_PA1                : virtualKeyLog = "Program Action 1";                           break;
                  case VK_PACKET             : virtualKeyLog = "Unicode Packet";                             break;
                  case VK_PAUSE              : virtualKeyLog = "Pause";                                      break;
                  case VK_PLAY               : virtualKeyLog = "Play";                                       break;
                  case VK_PRINT              : virtualKeyLog = "Print";                                      break;
                  case VK_PRIOR              : virtualKeyLog = "Prior, Page Up";                             break;
                  case VK_PROCESSKEY         : virtualKeyLog = "Input Method Encoding: Process";             break;
                  case VK_RBUTTON            : virtualKeyLog = "Right Mouse Button";                         break;
                  case VK_RCONTROL           : virtualKeyLog = "Right Control";                              break;
                  case VK_RETURN             : virtualKeyLog = "Return";                                     break;
                  case VK_RIGHT              : virtualKeyLog = "Right Arrow";                                break;
                  case VK_RMENU              : virtualKeyLog = "Right Alternative";                          break;
                  case VK_RSHIFT             : virtualKeyLog = "Right Shift";                                break;
                  case VK_RWIN               : virtualKeyLog = "Right Windows";                              break;
                  case VK_SCROLL             : virtualKeyLog = "Scroll Lock";                                break;
                  case VK_SELECT             : virtualKeyLog = "Select";                                     break;
                  case VK_SEPARATOR          : virtualKeyLog = "Separator";                                  break;
                  case VK_SLEEP              : virtualKeyLog = "Sleep";                                      break;
                  case VK_SNAPSHOT           : virtualKeyLog = "Snapshot";                                   break;
                  case VK_SPACE              : virtualKeyLog = "Space";                                      break;
                  case VK_SUBTRACT           : virtualKeyLog = "Subtract";                                   break;
                  case VK_TAB                : virtualKeyLog = "Tab";                                        break;
                  case VK_UP                 : virtualKeyLog = "Up Arrow";                                   break;
                  case VK_VOLUME_DOWN        : virtualKeyLog = "Volume: Down";                               break;
                  case VK_VOLUME_MUTE        : virtualKeyLog = "Volume: Mute";                               break;
                  case VK_VOLUME_UP          : virtualKeyLog = "Volume: Up";                                 break;
                  case VK_XBUTTON1           : virtualKeyLog = "Extended Mouse Button 1";                    break;
                  case VK_XBUTTON2           : virtualKeyLog = "Extended Mouse Button 2";                    break;
                  case VK_ZOOM               : virtualKeyLog = "Zoom";
                }

                // ...
                if (NULL == virtualKeyLog)
                return false;

                if (std::fprintf(stdout, "%1.2s%s%1.13s%4.5s%1.12s%4.5s%1.12s%4.5s%1.10s%" PRIuMAX "%1.10s%0*" PRIXMAX "%0.2s%s%0.1s%1.14s%4.5s%1.2s", "["
                  "`", virtualKeyLog, "`, "
                  "{"
                    "context: ",      context  ? "TRUE" : "FALSE",
                    ", extended: ",   extended ? "TRUE" : "FALSE",
                    ", previous: ",   previous ? "TRUE" : "FALSE",
                    ", repeat: ",     static_cast<uintmax_t>(repeatCount),
                    ", scan: 0x",     static_cast<int>(scanCodeLength), static_cast<uintmax_t>(scanCode), NULL != scanCodeLog ? " `" : "", NULL != scanCodeLog ? scanCodeLog : "", NULL != scanCodeLog ? "`" : "",
                    ", transition: ", transition ? "TRUE" : "FALSE",
                  "}"
                "]") < static_cast<int>(scanCodeLength + 94u))
                (void) std::fputs("...", stdout);
              } break;

              case WM_QUIT: {
                parameterLength  = 0u;
                parameterMaximum = (((static_cast<std::size_t>(1u) << ((CHAR_BIT * sizeof(int)) - 1u)) - 1u) << 1u) + 1u;

                for (std::size_t value = parameterMaximum; value; value /= 16u)
                  ++parameterLength;

                switch (static_cast<int>(parameter)) {
                  case EXIT_FAILURE: if (EOF == std::fputs("[EXIT_FAILURE, ...]", stdout)) (void) std::fputs("...", stdout); break;
                  case EXIT_SUCCESS: if (EOF == std::fputs("[EXIT_SUCCESS, ...]", stdout)) (void) std::fputs("...", stdout); break;
                  default: {
                    if (std::fprintf(stdout, "%c%0.1s%1.2s%0*" PRIXMAX "%1.6s", '[',
                      static_cast<int>(parameter) < 0 ? "-" : "", "0x", static_cast<int>(parameterLength), static_cast<uintmax_t>(static_cast<int>(parameter) < 0 ? -static_cast<int>(parameter) : static_cast<int>(parameter)), ", "
                      "..."
                    "]") < static_cast<int>(parameterLength + 9u))
                    (void) std::fputs("...", stdout);
                  } break;
                }
              } break;

              // TODO (Lapys) -> The other messages
              default: {
                if (std::fprintf(stdout, "%1.3s%0*" PRIXMAX "%1.4s%0*" PRIXMAX "%c", "["
                  "0x", static_cast<int>(parameterLength),    static_cast<uintmax_t>(parameter), ", "
                  "0x", static_cast<int>(subparameterLength), static_cast<uintmax_t>(subparameter),
                ']') < static_cast<int>(parameterLength + subparameterLength + 8u))
                (void) std::fputs("...", stdout);
              } break;
            }

            (void) std::fputs("}" "\r\n", stdout);
          }

          translation = messageEventTranslation;
          while ('\0' != *(translation++)) continue;
        }
      }

      // ...
      switch (message) {
        case WM_CLOSE:
        case WM_DESTROY:
          ::PostQuitMessage(EXIT_SUCCESS);
          break;

        case WM_KEYDOWN:
          if (VK_ESCAPE == parameter)
          ::PostQuitMessage(EXIT_SUCCESS);

          break;

        case WM_QUIT:
          ::DestroyWindow(windowHandle);
          break;
      }

      return ::DefWindowProcW(windowHandle, message, parameter, subparameter);
    }
  } window = {{}, NULL};

  // ...
  if (0x00u == ::GetModuleFileNameW(static_cast<HMODULE>(NULL), moduleFileName, MAX_PATH)) {
    (void) std::fputs("Unable to create window: Failed to retrieve filepath of this process module", stderr);
    return EXIT_FAILURE;
  }

  threadMessage.hwnd    = NULL; // --> window.handle
  threadMessage.lParam  = 0x00L;
  threadMessage.message = 0x00u;
  threadMessage.pt      = POINT();
  threadMessage.pt.x    = 0L;
  threadMessage.pt.y    = 0L;
  threadMessage.time    = 0u;
  threadMessage.wParam  = EXIT_SUCCESS;

  window.classTemplate               = WNDCLASSEXW();
  window.classTemplate.cbClsExtra    = 0;
  window.classTemplate.cbSize        = sizeof(WNDCLASSEX);
  window.classTemplate.cbWndExtra    = 0;
  window.classTemplate.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
  window.classTemplate.hCursor       = ::LoadCursor      (static_cast<HINSTANCE>(NULL), IDC_ARROW); // --> static_cast<HCURSOR>(::LoadImage(NULL, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED));
  window.classTemplate.hIcon         = ::ExtractIconW    (static_cast<HINSTANCE>(::GetCurrentProcess()), moduleFileName, 0u);
  window.classTemplate.hIconSm       = static_cast<HICON>(NULL);
  window.classTemplate.hInstance     =  instanceHandle;
  window.classTemplate.lpfnWndProc   = window.getProcedureByCallback(window.procedureCallback); // ->> Ideally non-null
  window.classTemplate.lpszClassName = L"window";
  window.classTemplate.lpszMenuName  = static_cast<LPCWSTR>(NULL);
  window.classTemplate.style         = CS_HREDRAW | CS_VREDRAW;

  if (0x00u == ::RegisterClassExW(&window.classTemplate)) {
    (void) std::fputs("Unable to create window: Failed to register window class", stderr);
    return EXIT_FAILURE;
  }

  window.handle = ::CreateWindowExW(0x00u, window.classTemplate.lpszClassName, L"Windows Event Messages", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 480, 320, static_cast<HWND>(NULL), static_cast<HMENU>(NULL), window.classTemplate.hInstance, static_cast<LPVOID>(NULL));

  if (NULL == window.handle) {
    (void) std::fputs("Unable to create window", stderr);
    threadMessage.wParam = EXIT_FAILURE;
  }

  else {
    ::ShowWindow  (window.handle, SW_SHOW | (windowAppearance & SW_SHOW));
    ::UpdateWindow(window.handle);

    while (FALSE != ::GetMessageW(&threadMessage, static_cast<HWND>(NULL), 0x0u, 0x0u)) {
      ::TranslateMessage(&threadMessage);
      ::DispatchMessageW(&threadMessage);
    }
  }

  ::UnregisterClassW(window.classTemplate.lpszClassName, window.classTemplate.hInstance);

  // ...
  return threadMessage.wParam;
}
