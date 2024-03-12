/* ... */
#define  UNICODE // ->> Windows API
#define _UNICODE //

/* Import */
#include <ciso646>    // ->> C ISO 646
#include <climits>    // ->> C Limits
#include <cstddef>    // ->> C Standard Definition
#include <cstdio>     // ->> C Standard Input/ Output
#include <inttypes.h> // ->> Integer Types
#include <stdint.h>   // ->> Standard Integers
#include <windows.h>  // ->> Windows
# include <commctrl.h> // ->> Common Control    --> ACM_OPENA, ACM_OPENW, ACM_PLAY, ACM_STOP
# include <ddraw.h>    // ->> Direct Draw       --> DDM_BEGIN, DDM_CLOSE, DDM_DRAW, DDM_END, DDM_SETFMT
// # include <inked.h>    // ->> Ink Edit          --> IE_DOCOMMAND, IE_GETAPPDATA, IE_GETBKGND, IE_GETCOMMAND, IE_GETCOUNT, IE_GETDRAWOPTS, IE_GETERASERTIP, IE_GETFORMAT, IE_GETGESTURE, IE_GETGRIDORIGIN, IE_GETGRIDPEN, IE_GETGRIDSIZE, IE_GETINK, IE_GETINKINPUT, IE_GETINKRECT, IE_GETMENU, IE_GETMODE, IE_GETNOTIFY, IE_GETPDEVENT, IE_GETPENTIP, IE_GETRECOG, IE_GETSECURITY, IE_GETSEL, IE_GETSELCOUNT, IE_GETSELITEMS, IE_GETSTYLE, IE_MSGFIRST, IE_SETAPPDATA, IE_SETBKGND, IE_SETDRAWOPTS, IE_SETERASERTIP, IE_SETFORMAT, IE_SETGRIDORIGIN, IE_SETGRIDPEN, IE_SETGRIDSIZE, IE_SETINK, IE_SETINKINPUT, IE_SETMODE, IE_SETNOTIFY, IE_SETPENTIP, IE_SETRECOG, IE_SETSECURITY, IE_SETSEL
# include <richedit.h> // ->> Rich Edit         --> EM_AUTOURLDETECT, EM_CANPASTE, EM_CANREDO, EM_CANUNDO, EM_CHARFROMPOS, EM_CONVPOSITION, EM_DISPLAYBAND, EM_EMPTYUNDOBUFFER, EM_EXGETSEL, EM_EXLIMITTEXT, EM_EXLINEFROMCHAR, EM_EXSETSEL, EM_FINDTEXT, EM_FINDTEXTEX, EM_FINDTEXTEXW, EM_FINDTEXTW, EM_FINDWORDBREAK, EM_FMTLINES, EM_FORMATRANGE, EM_GETAUTOURLDETECT, EM_GETBIDIOPTIONS, EM_GETCHARFORMAT, EM_GETCTFMODEBIAS, EM_GETCTFOPENSTATUS, EM_GETEDITSTYLE, EM_GETEVENTMASK, EM_GETFIRSTVISIBLELINE, EM_GETHANDLE, EM_GETHYPHENATEINFO, EM_GETIMECOLOR, EM_GETIMECOMPMODE, EM_GETIMECOMPTEXT, EM_GETIMECOMPTEXT, EM_GETIMEMODEBIAS, EM_GETIMEOPTIONS, EM_GETIMEPROPERTY, EM_GETIMESTATUS, EM_GETLANGOPTIONS, EM_GETLIMITTEXT, EM_GETLINE, EM_GETLINECOUNT, EM_GETMARGINS, EM_GETMODIFY, EM_GETOLEINTERFACE, EM_GETOPTIONS, EM_GETPAGE, EM_GETPAGEROTATE, EM_GETPARAFORMAT, EM_GETPASSWORDCHAR, EM_GETPUNCTUATION, EM_GETQUERYRTFOBJ, EM_GETRECT, EM_GETREDONAME, EM_GETSCROLLPOS, EM_GETSEL, EM_GETSELTEXT, EM_GETTEXTEX, EM_GETTEXTLENGTHEX, EM_GETTEXTMODE, EM_GETTEXTRANGE, EM_GETTHUMB, EM_GETTYPOGRAPHYOPTIONS, EM_GETUNDONAME, EM_GETVIEWKIND, EM_GETWORDBREAKPROC, EM_GETWORDBREAKPROCEX, EM_GETWORDWRAPMODE, EM_GETZOOM, EM_HIDESELECTION, EM_ISIME, EM_LIMITTEXT, EM_LINEFROMCHAR, EM_LINEINDEX, EM_LINELENGTH, EM_LINESCROLL, EM_OUTLINE, EM_PASTESPECIAL, EM_POSFROMCHAR, EM_RECONVERSION, EM_REDO, EM_REPLACESEL, EM_REQUESTRESIZE, EM_SCROLL, EM_SCROLLCARET, EM_SELECTIONTYPE, EM_SETBIDIOPTIONS, EM_SETBKGNDCOLOR, EM_SETCHARFORMAT, EM_SETCTFMODEBIAS, EM_SETCTFOPENSTATUS, EM_SETEDITSTYLE, EM_SETEVENTMASK, EM_SETFONT, EM_SETFONTSIZE, EM_SETHANDLE, EM_SETHYPHENATEINFO, EM_SETIMECOLOR, EM_SETIMEMODEBIAS, EM_SETIMEOPTIONS, EM_SETIMESTATUS, EM_SETLANGOPTIONS, EM_SETLIMITTEXT, EM_SETMARGINS, EM_SETMODIFY, EM_SETOLECALLBACK, EM_SETOPTIONS, EM_SETPAGE, EM_SETPAGEROTATE, EM_SETPALETTE, EM_SETPARAFORMAT, EM_SETPASSWORDCHARR, EM_SETPUNCTUATION, EM_SETQUERYRTFOBJ, EM_SETREADONLY, EM_SETRECT, EM_SETRECTNP, EM_SETSCROLLPOS, EM_SETSEL, EM_SETTABSTOPS, EM_SETTARGETDEVICE, EM_SETTEXTEX, EM_SETTEXTMODE, EM_SETTYPOGRAPHYOPTIONS, EM_SETUNDOLIMIT, EM_SETVIEWKIND, EM_SETWORDBREAK, EM_SETWORDBREAKPROC, EM_SETWORDBREAKPROCEX, EM_SETWORDWRAPMODE, EM_SETZOOM, EM_SHOWSCROLLBAR, EM_STOPGROUPTYPING, EM_STREAMIN, EM_STREAMOUT, EM_UNDO
# include <shlobj.h>   // ->> Shell Objects     --> BFFM_SETSTATUSTEXTA, BFFM_SETSELECTIONW, BFFM_ENABLEOK, BFFM_SETSELECTIONA, BFFM_SETSTATUSTEXTW
# include <vfw.h>      // ->> Video for Windows --> WM_CAP_DRIVER_GET_NAMEW, WM_CAP_DRIVER_GET_VERSIONW, WM_CAP_FILE_GET_CAPTURE_FILEW, WM_CAP_FILE_SAVEASW, WM_CAP_FILE_SAVEDIBW, WM_CAP_FILE_SET_CAPTURE_FILEW, WM_CAP_GET_MCI_DEVICEW, WM_CAP_PAL_OPENW, WM_CAP_PAL_SAVEW, WM_CAP_SET_CALLBACK_ERRORW, WM_CAP_SET_CALLBACK_STATUSW, WM_CAP_SET_MCI_DEVICEW, WM_CAP_UNICODE_START
# include <winuser.h>  // ->> Windows User      --> VK_ACCEPT, VK_ADD, VK_APPS, VK_ATTN, VK_BACK, VK_BROWSER_BACK, VK_BROWSER_FAVORITES, VK_BROWSER_FORWARD, VK_BROWSER_HOME, VK_BROWSER_REFRESH, VK_BROWSER_SEARCH, VK_BROWSER_STOP, VK_CANCEL, VK_CAPITAL, VK_CLEAR, VK_CONTROL, VK_CONVERT, VK_CRSEL, VK_DECIMAL, VK_DELETE, VK_DIVIDE, VK_DOWN, VK_END, VK_EREOF, VK_ESCAPE, VK_EXECUTE, VK_EXSEL, VK_F1, VK_F10, VK_F11, VK_F12, VK_F13, VK_F14, VK_F15, VK_F16, VK_F17, VK_F18, VK_F19, VK_F2, VK_F20, VK_F21, VK_F22, VK_F23, VK_F24, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_FINAL, VK_HANGUL, VK_HANJA, VK_HELP, VK_HOME, VK_IME_OFF, VK_IME_ON, VK_INSERT, VK_JUNJA, VK_KANA, VK_KANJI, VK_LAUNCH_APP1, VK_LAUNCH_APP2, VK_LAUNCH_MAIL, VK_LAUNCH_MEDIA_SELECT, VK_LBUTTON, VK_LCONTROL, VK_LEFT, VK_LMENU, VK_LSHIFT, VK_LWIN, VK_MBUTTON, VK_MEDIA_NEXT_TRACK, VK_MEDIA_PLAY_PAUSE, VK_MEDIA_PREV_TRACK, VK_MEDIA_STOP, VK_MENU, VK_MODECHANGE, VK_MULTIPLY, VK_NEXT, VK_NONAME, VK_NONCONVERT, VK_NUMLOCK, VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9, VK_OEM_1, VK_OEM_102, VK_OEM_2, VK_OEM_3, VK_OEM_4, VK_OEM_5, VK_OEM_6, VK_OEM_7, VK_OEM_8, VK_OEM_CLEAR, VK_OEM_COMMA, VK_OEM_MINUS, VK_OEM_PERIOD, VK_OEM_PLUS, VK_PA1, VK_PACKET, VK_PAUSE, VK_PLAY, VK_PRINT, VK_PRIOR, VK_PROCESSKEY, VK_RBUTTON, VK_RCONTROL, VK_RETURN, VK_RIGHT, VK_RMENU, VK_RSHIFT, VK_RWIN, VK_SCROLL, VK_SELECT, VK_SEPARATOR, VK_SHIFT, VK_SLEEP, VK_SNAPSHOT, VK_SPACE, VK_SUBTRACT, VK_TAB, VK_UP, VK_VOLUME_DOWN, VK_VOLUME_MUTE, VK_VOLUME_UP, VK_XBUTTON1, VK_XBUTTON2, VK_ZOOM

/* Main */
int WinMain(HINSTANCE const instanceHandle, HINSTANCE const, LPSTR const, int const windowAppearance) {
  WCHAR moduleFileName[MAX_PATH] = L"\0";
  MSG   threadMessage            = {};
  struct /* final */ {
    WNDCLASSEXW classTemplate;
    HWND        handle;

    static LRESULT CALLBACK procedure(HWND const handle, UINT const message, WPARAM const parameter, LPARAM const subparameter) {
      struct output /* final */ {
        inline static bool info(UINT const message, WPARAM const parameter, LPARAM const subparameter) /* noexcept */ {
          struct radix /* final */ { enum /* : std::size_t */ { destination = 16u, source = 2u }; };
          switch (message) {
            // CITE (Lapys) -> https://learn.microsoft.com/en-us/windows/win32/inputdev/about-keyboard-input
            case WM_KEYDOWN   :
            case WM_KEYUP     :
            case WM_SYSKEYDOWN:
            case WM_SYSKEYUP  : {
              WORD        const  keyFlags       = HIWORD(subparameter);                                                      //
              BOOL        const  extended       = KF_EXTENDED == (LOBYTE(keyFlags) & KF_EXTENDED);                           // ->> `TRUE` if `scanCode` has `0xE0` prefix
              BOOL        const  context        = KF_ALTDOWN  == (keyFlags         & KF_ALTDOWN);                            // ->> `TRUE` on `VK_MENU`, always `FALSE` on `WM_KEYDOWN`
              BOOL        const  previous       = KF_REPEAT   == (keyFlags         & KF_REPEAT);                             // ->> `TRUE` on auto-repeat
              WORD        const  repeatCount    = LOWORD(subparameter);                                                      //
              WORD        const  scanCode       = extended ? MAKEWORD(LOBYTE(keyFlags), 0xE0u) : LOBYTE(keyFlags);           //
              std::size_t const  scanCodeLength = (CHAR_BIT * sizeof scanCode) >> (radix::destination / radix::source / 2u); //
              char        const *scanCodeLog    = NULL;                                                                      //
              BOOL        const  transition     = KF_UP == (keyFlags & KF_UP);                                               // ->> `TRUE` on key release
              WORD        const  virtualKey     = LOWORD(parameter);                                                         //
              char        const *virtualKeyLog  = NULL;                                                                      //

              // ...
              switch (scanCode) {
                case 0x0001u:               scanCodeLog = "Key:"             " Keyboard Escape";                                     break;
                case 0x0002u:               scanCodeLog = "Key:"             " Keyboard 1 and Bang";                                 break;
                case 0x0003u:               scanCodeLog = "Key:"             " Keyboard 2 and At";                                   break;
                case 0x0004u:               scanCodeLog = "Key:"             " Keyboard 3 And Hash";                                 break;
                case 0x0005u:               scanCodeLog = "Key:"             " Keyboard 4 and Dollar";                               break;
                case 0x0006u:               scanCodeLog = "Key:"             " Keyboard 5 and Percent";                              break;
                case 0x0007u:               scanCodeLog = "Key:"             " Keyboard 6 and Caret";                                break;
                case 0x0008u:               scanCodeLog = "Key:"             " Keyboard 7 and Ampersand";                            break;
                case 0x0009u:               scanCodeLog = "Key:"             " Keyboard 8 and Star";                                 break;
                case 0x000Au:               scanCodeLog = "Key:"             " Keyboard 9 and Left Bracket";                         break;
                case 0x000Bu:               scanCodeLog = "Key:"             " Keyboard 0 and Right Bracket";                        break;
                case 0x000Cu:               scanCodeLog = "Key:"             " Keyboard Dash and Underscore";                        break;
                case 0x000Du:               scanCodeLog = "Key:"             " Keyboard Equals and Plus";                            break;
                case 0x000Eu:               scanCodeLog = "Key:"             " Keyboard Delete";                                     break;
                case 0x000Fu:               scanCodeLog = "Key:"             " Keyboard Tab";                                        break;
                case 0x0010u:               scanCodeLog = "Key:"             " Keyboard Q";                                          break;
                case 0x0011u:               scanCodeLog = "Key:"             " Keyboard W";                                          break;
                case 0x0012u:               scanCodeLog = "Key:"             " Keyboard E";                                          break;
                case 0x0013u:               scanCodeLog = "Key:"             " Keyboard R";                                          break;
                case 0x0014u:               scanCodeLog = "Key:"             " Keyboard T";                                          break;
                case 0x0015u:               scanCodeLog = "Key:"             " Keyboard Y";                                          break;
                case 0x0016u:               scanCodeLog = "Key:"             " Keyboard U";                                          break;
                case 0x0017u:               scanCodeLog = "Key:"             " Keyboard I";                                          break;
                case 0x0018u:               scanCodeLog = "Key:"             " Keyboard O";                                          break;
                case 0x0019u:               scanCodeLog = "Key:"             " Keyboard P";                                          break;
                case 0x001Au:               scanCodeLog = "Key:"             " Keyboard Left Brace";                                 break;
                case 0x001Bu:               scanCodeLog = "Key:"             " Keyboard Right Brace";                                break;
                case 0x001Cu:               scanCodeLog = "Key:"             " Keyboard Return Enter";                               break;
                case 0x001Du:               scanCodeLog = "Key:"             " Keyboard Left Control";                               break;
                case 0x001Eu:               scanCodeLog = "Key:"             " Keyboard A";                                          break;
                case 0x001Fu:               scanCodeLog = "Key:"             " Keyboard S";                                          break;
                case 0x0020u:               scanCodeLog = "Key:"             " Keyboard D";                                          break;
                case 0x0021u:               scanCodeLog = "Key:"             " Keyboard F";                                          break;
                case 0x0022u:               scanCodeLog = "Key:"             " Keyboard G";                                          break;
                case 0x0023u:               scanCodeLog = "Key:"             " Keyboard H";                                          break;
                case 0x0024u:               scanCodeLog = "Key:"             " Keyboard J";                                          break;
                case 0x0025u:               scanCodeLog = "Key:"             " Keyboard K";                                          break;
                case 0x0026u:               scanCodeLog = "Key:"             " Keyboard L";                                          break;
                case 0x0027u:               scanCodeLog = "Key:"             " Keyboard SemiColon and Colon";                        break;
                case 0x0028u:               scanCodeLog = "Key:"             " Keyboard Apostrophe and Double Quotation Mark";       break;
                case 0x0029u:               scanCodeLog = "Key:"             " Keyboard Grave Accent and Tilde";                     break;
                case 0x002Au:               scanCodeLog = "Key:"             " Keyboard Left Shift";                                 break;
                case 0x002Bu:               scanCodeLog = "Key:"             " Keyboard Non-United States, Keyboard Pipe and Slash"; break;
                case 0x002Cu:               scanCodeLog = "Key:"             " Keyboard Z";                                          break;
                case 0x002Du:               scanCodeLog = "Key:"             " Keyboard X";                                          break;
                case 0x002Eu:               scanCodeLog = "Key:"             " Keyboard C";                                          break;
                case 0x002Fu:               scanCodeLog = "Key:"             " Keyboard V";                                          break;
                case 0x0030u:               scanCodeLog = "Key:"             " Keyboard B";                                          break;
                case 0x0031u:               scanCodeLog = "Key:"             " Keyboard N";                                          break;
                case 0x0032u:               scanCodeLog = "Key:"             " Keyboard M";                                          break;
                case 0x0033u:               scanCodeLog = "Key:"             " Keyboard Comma";                                      break;
                case 0x0034u:               scanCodeLog = "Key:"             " Keyboard Period";                                     break;
                case 0x0035u:               scanCodeLog = "Key:"             " Keyboard QuestionMark";                               break;
                case 0x0036u:               scanCodeLog = "Key:"             " Keyboard Right Shift";                                break;
                case 0x0037u:               scanCodeLog = "Key:"             " Keypad Star";                                         break;
                case 0x0038u:               scanCodeLog = "Key:"             " Keyboard Left Alternative";                           break;
                case 0x0039u:               scanCodeLog = "Key:"             " Keyboard Spacebar";                                   break;
                case 0x003Au:               scanCodeLog = "Key:"             " Keyboard Caps Lock";                                  break;
                case 0x003Bu:               scanCodeLog = "Key:"             " Keyboard Function 1";                                 break;
                case 0x003Cu:               scanCodeLog = "Key:"             " Keyboard Function 2";                                 break;
                case 0x003Du:               scanCodeLog = "Key:"             " Keyboard Function 3";                                 break;
                case 0x003Eu:               scanCodeLog = "Key:"             " Keyboard Function 4";                                 break;
                case 0x003Fu:               scanCodeLog = "Key:"             " Keyboard Function 5";                                 break;
                case 0x0040u:               scanCodeLog = "Key:"             " Keyboard Function 6";                                 break;
                case 0x0041u:               scanCodeLog = "Key:"             " Keyboard Function 7";                                 break;
                case 0x0042u:               scanCodeLog = "Key:"             " Keyboard Function 8";                                 break;
                case 0x0043u:               scanCodeLog = "Key:"             " Keyboard Function 9";                                 break;
                case 0x0044u:               scanCodeLog = "Key:"             " Keyboard Function 10";                                break;
                case 0x0045u:               scanCodeLog = "Key:"             " Keyboard Pause, Keypad Number Lock and Clear";        break;
                case 0xE045u:               scanCodeLog = "Key:"             " Keypad Number Lock and Clear";                        break;
                case 0xE046u:               scanCodeLog = "Key:"             " Keyboard Pause";                                      break; // --> 0xE11D45u
                case 0x0046u:               scanCodeLog = "Key:"             " Keyboard Scroll Lock";                                break;
                case 0x0047u:               scanCodeLog = "Key:"             " Keypad 7 and Home";                                   break;
                case 0x0048u:               scanCodeLog = "Key:"             " Keypad 8 and Up Arrow";                               break;
                case 0x0049u:               scanCodeLog = "Key:"             " Keypad 9 and Page Up";                                break;
                case 0x004Au:               scanCodeLog = "Key:"             " Keypad Dash";                                         break;
                case 0x004Bu:               scanCodeLog = "Key:"             " Keypad 4 and Left Arrow";                             break;
                case 0x004Cu:               scanCodeLog = "Key:"             " Keypad 5";                                            break;
                case 0x004Du:               scanCodeLog = "Key:"             " Keypad 6 and Right Arrow";                            break;
                case 0x004Eu:               scanCodeLog = "Key:"             " Keypad Plus";                                         break;
                case 0x004Fu:               scanCodeLog = "Key:"             " Keypad 1 and End";                                    break;
                case 0x0050u:               scanCodeLog = "Key:"             " Keypad 2 and Down Arrow";                             break;
                case 0x0051u:               scanCodeLog = "Key:"             " Keypad 3 and Page Down";                              break;
                case 0x0052u:               scanCodeLog = "Key:"             " Keypad 0 and Insert";                                 break;
                case 0x0053u:               scanCodeLog = "Key:"             " Keypad Period";                                       break;
                case 0x0054u: case 0xE037u: scanCodeLog = "Key:"             " Keyboard Print Screen";                               break;
                case 0x0056u:               scanCodeLog = "Key:"             " Keyboard Non-United States Slash Bar";                break;
                case 0x0057u:               scanCodeLog = "Key:"             " Keyboard Function 11";                                break;
                case 0x0058u:               scanCodeLog = "Key:"             " Keyboard Function 12";                                break;
                case 0x0059u:               scanCodeLog = "Key:"             " Keypad Equals";                                       break;
                case 0x005Cu:               scanCodeLog = "Key:"             " Keyboard International 6";                            break;
                case 0x0064u:               scanCodeLog = "Key:"             " Keyboard Function 13";                                break;
                case 0x0065u:               scanCodeLog = "Key:"             " Keyboard Function 14";                                break;
                case 0x0066u:               scanCodeLog = "Key:"             " Keyboard Function 15";                                break;
                case 0x0067u:               scanCodeLog = "Key:"             " Keyboard Function 16";                                break;
                case 0x0068u:               scanCodeLog = "Key:"             " Keyboard Function 17";                                break;
                case 0x0069u:               scanCodeLog = "Key:"             " Keyboard Function 18";                                break;
                case 0x006Au:               scanCodeLog = "Key:"             " Keyboard Function 19";                                break;
                case 0x006Bu:               scanCodeLog = "Key:"             " Keyboard Function 20";                                break;
                case 0x006Cu:               scanCodeLog = "Key:"             " Keyboard Function 21";                                break;
                case 0x006Du:               scanCodeLog = "Key:"             " Keyboard Function 22";                                break;
                case 0x006Eu:               scanCodeLog = "Key:"             " Keyboard Function 23";                                break;
                case 0x0070u:               scanCodeLog = "Key:"             " Keyboard International 2";                            break;
                case 0x0071u: case 0x00F1u: scanCodeLog = "Key:"             " Keyboard Language 2";                                 break;
                case 0x0072u: case 0x00F2u: scanCodeLog = "Key:"             " Keyboard Language 1";                                 break;
                case 0x0073u:               scanCodeLog = "Key:"             " Keyboard International 1";                            break;
                case 0x0076u:               scanCodeLog = "Key:"             " Keyboard Function 24, Keyboard Language 5";           break;
                case 0x0077u:               scanCodeLog = "Key:"             " Keyboard Language 4";                                 break;
                case 0x0078u:               scanCodeLog = "Key:"             " Keyboard Language 3";                                 break;
                case 0x0079u:               scanCodeLog = "Key:"             " Keyboard International 4";                            break;
                case 0x007Bu:               scanCodeLog = "Key:"             " Keyboard International 5";                            break;
                case 0x007Du:               scanCodeLog = "Key:"             " Keyboard International 3";                            break;
                case 0x007Eu:               scanCodeLog = "Key:"             " Keypad Comma";                                        break;
                case 0x00FFu:               scanCodeLog = "Key:"             " Error Roll Over";                                     break;
                case 0xE010u:               scanCodeLog = "Consumer:"        " Scan Previous Track";                                 break;
                case 0xE019u:               scanCodeLog = "Consumer:"        " Scan Next Track";                                     break;
                case 0xE01Cu:               scanCodeLog = "Key:"             " Keypad Enter";                                        break;
                case 0xE01Du:               scanCodeLog = "Key:"             " Keyboard Right Control";                              break;
                case 0xE020u:               scanCodeLog = "Consumer:"        " Mute";                                                break;
                case 0xE021u:               scanCodeLog = "Consumer:"        " AL Calculator";                                       break;
                case 0xE022u:               scanCodeLog = "Consumer:"        " Play/ Pause";                                         break;
                case 0xE024u:               scanCodeLog = "Consumer:"        " Stop";                                                break;
                case 0xE02Eu:               scanCodeLog = "Consumer:"        " Volume Decrement";                                    break;
                case 0xE030u:               scanCodeLog = "Consumer:"        " Volume Increment";                                    break;
                case 0xE032u:               scanCodeLog = "Consumer:"        " AC Home";                                             break;
                case 0xE035u:               scanCodeLog = "Key:"             " Keypad Slash";                                        break;
                case 0xE038u:               scanCodeLog = "Key:"             " Keyboard Right Alternatives";                         break;
                case 0xE047u:               scanCodeLog = "Key:"             " Keyboard Home";                                       break;
                case 0xE048u:               scanCodeLog = "Key:"             " Keyboard Up Arrow";                                   break;
                case 0xE049u:               scanCodeLog = "Key:"             " Keyboard Page Up";                                    break;
                case 0xE04Bu:               scanCodeLog = "Key:"             " Keyboard Left Arrow";                                 break;
                case 0xE04Du:               scanCodeLog = "Key:"             " Keyboard Right Arrow";                                break;
                case 0xE04Fu:               scanCodeLog = "Key:"             " Keyboard End";                                        break;
                case 0xE050u:               scanCodeLog = "Key:"             " Keyboard Down Arrow";                                 break;
                case 0xE051u:               scanCodeLog = "Key:"             " Keyboard Page Down";                                  break;
                case 0xE052u:               scanCodeLog = "Key:"             " Keyboard Insert";                                     break;
                case 0xE053u:               scanCodeLog = "Key:"             " Keyboard Delete Forward";                             break;
                case 0xE05Bu:               scanCodeLog = "Key:"             " Keyboard Left GUI";                                   break;
                case 0xE05Cu:               scanCodeLog = "Key:"             " Keyboard Right GUI";                                  break;
                case 0xE05Du:               scanCodeLog = "Key:"             " Keyboard Application";                                break;
                case 0xE05Eu:               scanCodeLog = "Generic Desktop:" " System Power Down, Key: Keyboard Power";              break;
                case 0xE05Fu:               scanCodeLog = "Generic Desktop:" " System Sleep";                                        break;
                case 0xE063u:               scanCodeLog = "Generic Desktop:" " System Wake Up";                                      break;
                case 0xE065u:               scanCodeLog = "Consumer:"        " AC Search";                                           break;
                case 0xE066u:               scanCodeLog = "Consumer:"        " AC Bookmarks";                                        break;
                case 0xE067u:               scanCodeLog = "Consumer:"        " AC Refresh";                                          break;
                case 0xE068u:               scanCodeLog = "Consumer:"        " AC Stop";                                             break;
                case 0xE069u:               scanCodeLog = "Consumer:"        " AC Forward";                                          break;
                case 0xE06Au:               scanCodeLog = "Consumer:"        " AC Back";                                             break;
                case 0xE06Bu:               scanCodeLog = "Consumer:"        " AL Local Machine Browser";                            break;
                case 0xE06Cu:               scanCodeLog = "Consumer:"        " AL Email Reader";                                     break;
                case 0xE06Du:               scanCodeLog = "Consumer:"        " AL Consumer Control Configuration";                   break;
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
                case VK_NONAME             : /* Do nothing... */                                           break;
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

              return std::fprintf(stdout, "%1.5s%s%1.13s%4.5s%1.12s%4.5s%1.12s%4.5s%1.10s%" PRIuMAX "%1.10s%0*" PRIXMAX "%s%s%s%1.14s%4.5s%1.3s", "["
                "Key{", virtualKeyLog, "}, "
                "{"
                  "context: ",      context  ? "true" : "false",
                  ", extended: ",   extended ? "true" : "false",
                  ", previous: ",   previous ? "true" : "false",
                  ", repeat: ",     static_cast<uintmax_t>(repeatCount),
                  ", scan: 0x",     static_cast<int>(scanCodeLength), static_cast<uintmax_t>(scanCode), NULL != scanCodeLog ? " KeyScan{" : "", NULL != scanCodeLog ? scanCodeLog : "", NULL != scanCodeLog ? "}" : "",
                  ", transition: ", transition ? "true" : "false",
                "}"
              "] ") > static_cast<int>(scanCodeLength + 79);
            }
          }

          // ...
          return true;
        }

        inline static bool log(UINT const message, WPARAM const parameter, LPARAM const subparameter, char const* const messageNameA, char const* const messageNameB = NULL, char const* const messageNameC = NULL, char const* const messageNameD = NULL, char const* const messageNameE = NULL, char const* const messageNameF = NULL, char const* const messageNameG = NULL, char const* const messageNameH = NULL, char const* const messageNameI = NULL, char const* const messageNameJ = NULL, char const* const messageNameK = NULL, char const* const messageNameL = NULL) /* noexcept */ {
          struct radix /* final */ { enum /* : std::size_t */ { destination = 16u, source = 2u }; };
          std::size_t const subparameterLength         = (CHAR_BIT * sizeof subparameter) >> (radix::destination / radix::source / 2u);
          std::size_t const parameterLength            = (CHAR_BIT * sizeof parameter)    >> (radix::destination / radix::source / 2u);
          std::size_t const messageLength              = (CHAR_BIT * sizeof message)      >> (radix::destination / radix::source / 2u);
          char const *const messageNames[]             = {messageNameA, messageNameB, messageNameC, messageNameD, messageNameE, messageNameF, messageNameG, messageNameH, messageNameI, messageNameJ, messageNameK, messageNameL};
          bool        const messageHasMultipleNames    = NULL != messageNameB;
          std::size_t const logHeaderLength            = 14u /* --> "[0x" " (0x" ", 0x" ")] " */ + messageLength + parameterLength + subparameterLength;
          char              logHeader[logHeaderLength] = "";

          // ...
          if (NULL == messageNameA or static_cast<int>(logHeaderLength) > std::sprintf(logHeader, "%1.3s%0*" PRIXMAX "%1.4s%0*" PRIXMAX "%1.4s%0*" PRIXMAX "%1.3s",
            "[0x",  static_cast<int>(messageLength),      static_cast<uintmax_t>(message),
            " (0x", static_cast<int>(parameterLength),    static_cast<uintmax_t>(parameter),
            ", 0x", static_cast<int>(subparameterLength), static_cast<uintmax_t>(subparameter), ")] "
          )) return false;

          // ...
          if (EOF == std::fputs(logHeader, stdout))
          return false;

          if (not output::info(message, parameter, subparameter))
          return false;

          if (std::fprintf(stdout, "%s%1.2s", messageHasMultipleNames ? "" : messageNameA, "\r\n") < 2)
          return false;

          if (messageHasMultipleNames) {
            for (char const *const *iterator = messageNames; NULL != *iterator and iterator != messageNames + (sizeof messageNames / sizeof(char const*)); ++iterator) {
              if (std::fprintf(stdout, "%1.2s%s%1.2s", "  ", *iterator, "\r\n") < 4)
              return false;
            }

            (void) std::fputs("\r\n", stdout);
          }

          // ...
          return true;
        }
      };

      /* ...
        --- CITE ---
          #Lapys:
          - https://docs.microsoft.com/en-us/windows/win32/winmsg/about-messages-and-message-queues#system-defined-messages
          - https://github.com/LapysDev/Windows-API-Events
          - https://wiki.winehq.org/List_Of_Windows_Messages
      */
      switch (message) {
        #if defined ACM_OPENA
          case ACM_OPENA:
        #elif defined BFFM_SETSTATUSTEXTA
          case BFFM_SETSTATUSTEXTA:
        #elif defined CDM_FIRST
          case CDM_FIRST:
        #elif defined CDM_GETSPEC
          case CDM_GETSPEC:
        #elif defined EM_SETPUNCTUATION
          case EM_SETPUNCTUATION:
        #elif defined IPM_CLEARADDRESS
          case IPM_CLEARADDRESS:
        #elif defined WM_CAP_UNICODE_START
          case WM_CAP_UNICODE_START:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Animation Control: Open              " " `ACM_OPENA`",
          "Browse for Folder: Set Status Text   " " `BFFM_SETSTATUSTEXTA`",
          "Common Dialog    : 1st               " " `CDM_FIRST`",
          "Common Dialog    : Get Specifications" " `CDM_GETSPEC`",
          "Internet Protocol: Clear Address     " " `IPM_CLEARADDRESS`",
          "Rich Edit        : Set Punctuation   " " `EM_SETPUNCTUATION`",
          "Windows Capture  : Unicode Start     " " `WM_CAP_UNICODE_START`"
        ); break;

        #if defined ACM_OPENW
          case ACM_OPENW:
        #elif defined BFFM_SETSELECTIONW
          case BFFM_SETSELECTIONW:
        #elif defined CDM_GETFOLDERIDLIST
          case CDM_GETFOLDERIDLIST:
        #elif defined EM_GETWORDWRAPMODE
          case EM_GETWORDWRAPMODE:
        #elif defined IPM_SETRANGE
          case IPM_SETRANGE:
        #elif defined PSM_ADDPAGE
          case PSM_ADDPAGE:
        #elif defined UDM_SETPOS
          case UDM_SETPOS:
        #elif defined WM_CAP_SET_CALLBACK_STATUSW
          case WM_CAP_SET_CALLBACK_STATUSW:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Animation Control: Open               " " `ACM_OPENW`",
          "Browse for Folder: Set Selection      " " `BFFM_SETSELECTIONW`",
          "Common Dialog    : Get Folder ID List " " `CDM_GETFOLDERIDLIST`",
          "Internet Protocol: Set Range          " " `IPM_SETRANGE`",
          "Prop Sheet       : Add Page           " " `PSM_ADDPAGE`",
          "Rich Edit        : Get Word Wrap Mode " " `EM_GETWORDWRAPMODE`",
          "Windows Capture  : Set Callback Status" " `WM_CAP_SET_CALLBACK_STATUSW`"
        ); break;

        #if defined ACM_PLAY
          case ACM_PLAY:
        #elif defined BFFM_ENABLEOK
          case BFFM_ENABLEOK:
        #elif defined CDM_GETFILEPATH
          case CDM_GETFILEPATH:
        #elif defined EM_GETPUNCTUATION
          case EM_GETPUNCTUATION:
        #elif defined IPM_SETADDRESS
          case IPM_SETADDRESS:
        #elif defined UDM_SETRANGE
          case UDM_SETRANGE:
        #elif defined WM_CHOOSEFONT_SETLOGFONT
          case WM_CHOOSEFONT_SETLOGFONT:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Animation Control: Play                      " " `ACM_PLAY`",
          "Browse for Folder: Enable OK                 " " `BFFM_ENABLEOK`",
          "Common Dialog    : Get File Path             " " `CDM_GETFILEPATH`",
          "Internet Protocol: Set Address               " " `IPM_SETADDRESS`",
          "Rich Edit        : Get Punctuation           " " `EM_GETPUNCTUATION`",
          "Up-Down Control  : Set Range                 " " `UDM_SETRANGE`",
          "Windows          : Choose Font (Set Log Font)" " `WM_CHOOSEFONT_SETLOGFONT`"
        ); break;

        #if defined ACM_STOP
          case ACM_STOP:
        #elif defined BFFM_SETSELECTIONA
          case BFFM_SETSELECTIONA:
        #elif defined CDM_GETFOLDERPATH
          case CDM_GETFOLDERPATH:
        #elif defined EM_SETWORDWRAPMODE
          case EM_SETWORDWRAPMODE:
        #elif defined IPM_GETADDRESS
          case IPM_GETADDRESS:
        #elif defined PSM_REMOVEPAGE
          case PSM_REMOVEPAGE:
        #elif defined UDM_GETRANGE
          case UDM_GETRANGE:
        #elif defined WM_CAP_SET_CALLBACK_ERRORW
          case WM_CAP_SET_CALLBACK_ERRORW:
        #elif defined WM_CHOOSEFONT_SETFLAGS
          case WM_CHOOSEFONT_SETFLAGS:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Animation Control: Stop                   " " `ACM_STOP`",
          "Browse for Folder: Set Selection          " " `BFFM_SETSELECTIONA`",
          "Common Dialog    : Get Folder Path        " " `CDM_GETFOLDERPATH`",
          "Internet Protocol: Get Address            " " `IPM_GETADDRESS`",
          "Prop Sheet       : Remove Page            " " `PSM_REMOVEPAGE`",
          "Rich Edit        : Set Word Wrap Mode     " " `EM_SETWORDWRAPMODE`",
          "Up-Down Control  : Get Range              " " `UDM_GETRANGE`",
          "Windows          : Choose Font (Set Flags)" " `WM_CHOOSEFONT_SETFLAGS`",
          "Windows Capture  : Set Callback Error     " " `WM_CAP_SET_CALLBACK_ERRORW`"
        ); break;

        #if defined BFFM_SETSTATUSTEXTW
          case BFFM_SETSTATUSTEXTW:
        #elif defined CDM_SETCONTROLTEXT
          case CDM_SETCONTROLTEXT:
        #elif defined EM_SETIMECOLOR
          case EM_SETIMECOLOR:
        #elif defined IPM_SETFOCUS
          case IPM_SETFOCUS:
        #elif defined PSM_CHANGED
          case PSM_CHANGED:
        #elif defined UDM_GETPOS
          case UDM_GETPOS:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Browse for Folder: Set Status Text                      " " `BFFM_SETSTATUSTEXTW`",
          "Common Dialog    : Set Control Text                     " " `CDM_SETCONTROLTEXT`",
          "Internet Protocol: Set Focus                            " " `IPM_SETFOCUS`",
          "Prop Sheet       : Changed                              " " `PSM_CHANGED`",
          "Rich Edit        : Set IME (Input Method Encoding) Color" " `EM_SETIMECOLOR`",
          "Up-Down Control  : Get Position                         " " `UDM_GETPOS`"
        ); break;

        #if defined BM_CLICK
          case BM_CLICK:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter, "Button: Click" " `BM_CLICK`"); break;

        #if defined BM_GETCHECK
          case BM_GETCHECK:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter, "Button: Get Check" " `BM_GETCHECK`"); break;

        #if defined BM_GETIMAGE
          case BM_GETIMAGE:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter, "Button: Get Image" " `BM_GETIMAGE`"); break;

        #if defined BM_GETSTATE
          case BM_GETSTATE:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter, "Button: Get State" " `BM_GETSTATE`"); break;

        #if defined BM_SETCHECK
          case BM_SETCHECK:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter, "Button: Set Check" " `BM_SETCHECK`"); break;

        #if defined BM_SETDONTCLICK
          case BM_SETDONTCLICK:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter, "Button: Set Don't Click" " `BM_SETDONTCLICK`"); break;

        #if defined BM_SETIMAGE
          case BM_SETIMAGE:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter, "Button: Set Image" " `BM_SETIMAGE`"); break;

        #if defined BM_SETSTATE
          case BM_SETSTATE:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter, "Button: Set State" " `BM_SETSTATE`"); break;

        #if defined BM_SETSTYLE
          case BM_SETSTYLE:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter, "Button: Set Style" " `BM_SETSTYLE`"); break;

        #if defined CBEM_GETCOMBOCONTROL
          case CBEM_GETCOMBOCONTROL:
        #elif defined PBM_SETRANGE32
          case PBM_SETRANGE32:
        #elif defined RB_SETBANDINFOA
          case RB_SETBANDINFOA:
        #elif defined SB_GETPARTS
          case SB_GETPARTS:
        #elif defined TBM_SETRANGE
          case TBM_SETRANGE:
        #elif defined TB_MARKBUTTON
          case TB_MARKBUTTON:
        #elif defined TTM_NEWTOOLRECTA
          case TTM_NEWTOOLRECTA:
        #elif defined WM_PSD_YAFULLPAGERECT
          case WM_PSD_YAFULLPAGERECT:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Combo Box (Extended): Get Combo Control          " " `CBEM_GETCOMBOCONTROL`",
          "Progress Bar        : Set Range                  " " `PBM_SETRANGE32`",
          "Rebar               : Set Band Information       " " `RB_SETBANDINFOA`",
          "Status Bar          : Get Parts                  " " `SB_GETPARTS`",
          "Toolbar             : Mark Button                " " `TB_MARKBUTTON`",
          "Tooltip             : New Tool Rectangle         " " `TTM_NEWTOOLRECTA`",
          "Trackbar            : Set Range                  " " `TBM_SETRANGE`",
          "Windows             : Page Setup Dialog Full Page" " `WM_PSD_YAFULLPAGERECT`"
        ); break;

        #if defined CBEM_GETEDITCONTROL
          case CBEM_GETEDITCONTROL:
        #elif defined IE_GETPAINTDC
          case IE_GETPAINTDC:
        #elif defined PBM_GETRANGE
          case PBM_GETRANGE:
        #elif defined RB_SETPARENT
          case RB_SETPARENT:
        #elif defined SB_GETBORDERS
          case SB_GETBORDERS:
        #elif defined TBM_SETRANGEMIN
          case TBM_SETRANGEMIN:
        #elif defined TTM_RELAYEVENT
          case TTM_RELAYEVENT:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Combo Box (Extended): Get Edit Control        " " `CBEM_GETEDITCONTROL`",
          "Ink Edit            : Get Paint Device Context" " `IE_GETPAINTDC`",
          "Progress Bar        : Get Range               " " `PBM_GETRANGE`",
          "Rebar               : Set Parent              " " `RB_SETPARENT`",
          "Status Bar          : Get Borders             " " `SB_GETBORDERS`",
          "Tooltip             : Relay Event             " " `TTM_RELAYEVENT`",
          "Trackbar            : Set Range Minimum       " " `TBM_SETRANGEMIN`"
        ); break;

        #if defined CBEM_GETEXSTYLE
          case CBEM_GETEXSTYLE:
        #elif defined CBEM_GETEXTENDEDSTYLE
          case CBEM_GETEXTENDEDSTYLE:
        #elif defined PBM_SETBARCOLOR
          case PBM_SETBARCOLOR:
        #elif defined RB_GETRECT
          case RB_GETRECT:
        #elif defined SB_SIMPLE
          case SB_SIMPLE:
        #elif defined TBM_CLEARTICS
          case TBM_CLEARTICS:
        #elif defined TB_ISBUTTONENABLED
          case TB_ISBUTTONENABLED:
        #elif defined TTM_SETTOOLINFOA
          case TTM_SETTOOLINFOA:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Combo Box (Extended): Get Extended Style  " " `CBEM_GETEXSTYLE | CBEM_GETEXTENDEDSTYLE`",
          "Progress Bar        : Set Bar Color       " " `PBM_SETBARCOLOR`",
          "Rebar               : Get Rectangle       " " `RB_GETRECT`",
          "Status Bar          : Simple              " " `SB_SIMPLE`",
          "Toolbar             : Is Button Enabled   " " `TB_ISBUTTONENABLED`",
          "Tooltip             : Set Tool Information" " `TTM_SETTOOLINFOA`",
          "Trackbar            : Clear Ticks         " " `TBM_CLEARTICS`"
        ); break;

        #if defined CBEM_GETIMAGELIST
          case CBEM_GETIMAGELIST:
        #elif defined HKM_SETRULES
          case HKM_SETRULES:
        #elif defined PBM_DELTAPOS
          case PBM_DELTAPOS:
        #elif defined RB_GETBARINFO
          case RB_GETBARINFO:
        #elif defined SB_GETTEXTLENGTHA
          case SB_GETTEXTLENGTHA:
        #elif defined TBM_GETTIC
          case TBM_GETTIC:
        #elif defined TB_PRESSBUTTON
          case TB_PRESSBUTTON:
        #elif defined TTM_SETDELAYTIME
          case TTM_SETDELAYTIME:
        #elif defined WM_PSD_MARGINRECT
          case WM_PSD_MARGINRECT:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Combo Box (Extended): Get Image List     " " `CBEM_GETIMAGELIST`",
          "Hotkey              : Set Rules          " " `HKM_SETRULES`",
          "Page Setup Dialog   : Margin Rectangle   " " `WM_PSD_MARGINRECT`",
          "Progress Bar        : Delta Position     " " `PBM_SETBARCOLOR`",
          "Rebar               : Get Bar Information" " `RB_GETBARINFO`",
          "Status Bar          : Get Text Length    " " `SB_GETTEXTLENGTHA`",
          "Toolbar             : Press Button       " " `TB_PRESSBUTTON`",
          "Tooltip             : Set Delay Time     " " `TTM_SETDELAYTIME`",
          "Trackbar            : Get Tick           " " `TBM_GETTIC`"
        ); break;

        #if defined CBEM_GETITEMA
          case CBEM_GETITEMA:
        #elif defined DDM_END
          case DDM_END:
        #elif defined PBM_SETSTEP
          case PBM_SETSTEP:
        #elif defined RB_SETBARINFO
          case RB_SETBARINFO:
        #elif defined SB_SETPARTS
          case SB_SETPARTS:
        #elif defined TBM_SETTIC
          case TBM_SETTIC:
        #elif defined TB_HIDEBUTTON
          case TB_HIDEBUTTON:
        #elif defined TB_SETBUTTONINFOW
          case TB_SETBUTTONINFOW:
        #elif defined TTM_ADDTOOLA
          case TTM_ADDTOOLA:
        #elif defined WM_PSD_GREEKTEXTRECT
          case WM_PSD_GREEKTEXTRECT:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Combo Box (Extended): Get Item              " " `CBEM_GETITEMA`",
          "Direct Draw         : End                   " " `DDM_END`",
          "Page Setup Dialog   : Greek Text Rectangle  " " `WM_PSD_GREEKTEXTRECT`",
          "Progress Bar        : Set Step              " " `PBM_SETSTEP`",
          "Rebar               : Set Bar Information   " " `RB_SETBARINFO`",
          "Status Bar          : Set Parts             " " `SB_SETPARTS`",
          "Toolbar             : Hide Button           " " `TB_HIDEBUTTON`",
          "Toolbar             : Set Button Information" " `TB_SETBUTTONINFOW`",
          "Tooltip             : Add Tool              " " `TTM_ADDTOOLA`",
          "Trackbar            : Set Tick              " " `TBM_SETTIC`"
        ); break;

        #if defined CBEM_GETITEMW
          case CBEM_GETITEMW:
        #elif defined RB_GETROWCOUNT
          case RB_GETROWCOUNT:
        #elif defined SB_GETTEXTW
          case SB_GETTEXTW:
        #elif defined TB_ISBUTTONINDETERMINATE
          case TB_ISBUTTONINDETERMINATE:
        #elif defined TTM_GETTOOLCOUNT
          case TTM_GETTOOLCOUNT:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Combo Box (Extended): Get Item               " " `CBEM_GETITEMW`",
          "Rebar               : Get Row Count          " " `RB_GETROWCOUNT`",
          "Status Bar          : Get Text               " " `SB_GETTEXTW`",
          "Toolbar             : Is Button Indeterminate" " `TB_ISBUTTONINDETERMINATE`",
          "Tooltip             : Get Tool Count         " " `TTM_GETTOOLCOUNT`"
        ); break;

        #if defined CBEM_HASEDITCHANGED
          case CBEM_HASEDITCHANGED:
        #elif defined RB_INSERTBANDW
          case RB_INSERTBANDW:
        #elif defined SB_GETRECT
          case SB_GETRECT:
        #elif defined TBM_SETSEL
          case TBM_SETSEL:
        #elif defined TB_ISBUTTONCHECKED
          case TB_ISBUTTONCHECKED:
        #elif defined TTM_HITTESTA
          case TTM_HITTESTA:
        #elif defined WIZ_QUERYNUMPAGES
          case WIZ_QUERYNUMPAGES:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Combo Box (Extended): Has Edit Changed     " " `CBEM_HASEDITCHANGED`",
          "Rebar               : Insert Band          " " `RB_INSERTBANDW`",
          "Status Bar          : Get Rectangle        " " `SB_GETRECT`",
          "Toolbar             : Is Button Checked    " " `TB_ISBUTTONCHECKED`",
          "Tooltip             : Hit Test             " " `TTM_HITTESTA`",
          "Trackbar            : Set Selection        " " `TBM_SETSEL`",
          "Wizard              : Query Number of Pages" " `WIZ_QUERYNUMPAGES`"
        ); break;

        #if defined CBEM_INSERTITEMA
          case CBEM_INSERTITEMA:
        #elif defined DDM_DRAW
          case DDM_DRAW:
        #elif defined DM_SETDEFID
          case DM_SETDEFID:
        #elif defined HKM_SETHOTKEY
          case HKM_SETHOTKEY:
        #elif defined PBM_SETRANGE
          case PBM_SETRANGE:
        #elif defined RB_INSERTBANDA
          case RB_INSERTBANDA:
        #elif defined SB_SETTEXTA
          case SB_SETTEXTA:
        #elif defined TBM_GETRANGEMIN
          case TBM_GETRANGEMIN:
        #elif defined TB_ENABLEBUTTON
          case TB_ENABLEBUTTON:
        #elif defined TTM_ACTIVATE
          case TTM_ACTIVATE:
        #elif defined WM_CHOOSEFONT_GETLOGFONT
          case WM_CHOOSEFONT_GETLOGFONT:
        #elif defined WM_PSD_FULLPAGERECT
          case WM_PSD_FULLPAGERECT:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Combo Box (Extended): Insert Item               " " `CBEM_INSERTITEMA`",
          "Dialog              : Set Default Identity      " " `DM_SETDEFID`",
          "Direct Draw         : Draw                      " " `DDM_DRAW`",
          "Hotkey              : Set Hotkey                " " `HKM_SETHOTKEY`",
          "Page Setup Dialog   : Full Page Rectangle       " " `WM_PSD_FULLPAGERECT`",
          "Progress Bar        : Set Range                 " " `PBM_SETRANGE`",
          "Rebar               : Insert Band               " " `RB_INSERTBANDA`",
          "Toolbar             : Enable Button             " " `TB_ENABLEBUTTON`",
          "Tooltip             : Activate                  " " `TTM_ACTIVATE`",
          "Trackbar            : Get Range                 " " `TBM_GETRANGEMIN`",
          "Windows             : Choose Font (Get Log Font)" " `WM_CHOOSEFONT_GETLOGFONT`"
        ); break;

        #if defined CBEM_INSERTITEMW
          case CBEM_INSERTITEMW:
        #elif defined RB_SETBANDINFOW
          case RB_SETBANDINFOW:
        #elif defined SB_SETTEXTW
          case SB_SETTEXTW:
        #elif defined TBM_SETSELSTART
          case TBM_SETSELSTART:
        #elif defined TB_ISBUTTONPRESSED
          case TB_ISBUTTONPRESSED:
        #elif defined TTM_GETTEXTA
          case TTM_GETTEXTA:
        #elif defined WIZ_NEXT
          case WIZ_NEXT:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Combo Box (Extended): Insert Item         " " `CBEM_INSERTITEMW`",
          "Rebar               : Set Band Information" " `RB_SETBANDINFOW`",
          "Status Bar          : Set Text            " " `SB_SETTEXTW`",
          "Toolbar             : Is Button Pressed   " " `TB_ISBUTTONPRESSED`",
          "Tooltip             : Get Text            " " `TTM_GETTEXTA`",
          "Trackbar            : Set Selection Start " " `TBM_SETSELSTART`",
          "Wizard              : Next                " " `WIZ_NEXT`"
        ); break;

        #if defined CBEM_SETEXSTYLE
          case CBEM_SETEXSTYLE:
        #elif defined CBEM_SETEXTENDEDSTYLE
          case CBEM_SETEXTENDEDSTYLE:
        #elif defined PBM_GETPOS
          case PBM_GETPOS:
        #elif defined RB_HITTEST
          case RB_HITTEST:
        #elif defined SB_SETMINHEIGHT
          case SB_SETMINHEIGHT:
        #elif defined TBM_SETRANGEMAX
          case TBM_SETRANGEMAX:
        #elif defined TTM_GETTOOLINFOA
          case TTM_GETTOOLINFOA:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Combo Box (Extended): Set Extended Style  " " `CBEM_SETEXSTYLE`, `CBEM_SETEXTENDEDSTYLE`",
          "Progress Bar        : Get Position        " " `PBM_GETPOS`",
          "Rebar               : Hit Test            " " `RB_HITTEST`",
          "Status Bar          : Set Minimum Height  " " `SB_SETMINHEIGHT`",
          "Tooltip             : Get Tool Information" " `TTM_GETTOOLINFOA`",
          "Trackbar            : Set Range Maximum   " " `TBM_SETRANGEMAX`"
        ); break;

        #if defined CBEM_SETIMAGELIST
          case CBEM_SETIMAGELIST:
        #elif defined DDM_BEGIN
          case DDM_BEGIN:
        #elif defined DDM_CLOSE
          case DDM_CLOSE:
        #elif defined DM_REPOSITION
          case DM_REPOSITION:
        #elif defined HKM_GETHOTKEY
          case HKM_GETHOTKEY:
        #elif defined PBM_SETPOS
          case PBM_SETPOS:
        #elif defined RB_DELETEBAND
          case RB_DELETEBAND:
        #elif defined SB_GETTEXTA
          case SB_GETTEXTA:
        #elif defined TBM_GETRANGEMAX
          case TBM_GETRANGEMAX:
        #elif defined TB_CHECKBUTTON
          case TB_CHECKBUTTON:
        #elif defined WM_PSD_MINMARGINRECT
          case WM_PSD_MINMARGINRECT:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Combo Box (Extended): Set Image List          " " `CBEM_SETIMAGELIST`",
          "Dialog              : Reposition              " " `DM_REPOSITION`",
          "Direct Draw         : Begin                   " " `DDM_BEGIN`",
          "Direct Draw         : Close                   " " `DDM_CLOSE`",
          "Hotkey              : Get Hotkey              " " `HKM_GETHOTKEY`",
          "Page Setup Dialog   : Minimum Margin Rectangle" " `WM_PSD_MINMARGINRECT`",
          "Progress Bar        : Set Position            " " `PBM_SETPOS`",
          "Rebar               : Delete Band             " " `RB_DELETEBAND`",
          "Status Bar          : Get Text                " " `SB_GETTEXTA`",
          "Toolbar             : Check Button            " " `TB_CHECKBUTTON`",
          "Trackbar            : Get Range Maximum       " " `TBM_GETRANGEMAX`"
        ); break;

        #if defined CBEM_SETITEMA
          case CBEM_SETITEMA:
        #elif defined PBM_STEPIT
          case PBM_STEPIT:
        #elif defined TBM_SETPOS
          case TBM_SETPOS:
        #elif defined TB_INDETERMINATE
          case TB_INDETERMINATE:
        #elif defined TTM_DELTOOLA
          case TTM_DELTOOLA:
        #elif defined WM_PSD_ENVSTAMPRECT
          case WM_PSD_ENVSTAMPRECT:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Combo Box (Extended): Set Item                " " `CBEM_SETITEMA`",
          "Page Setup Dialog   : Envelope Stamp Rectangle" " `WM_PSD_ENVSTAMPRECT`",
          "Progress Bar        : Step It                 " " `PBM_STEPIT`",
          "Toolbar             : Indeterminate           " " `TB_INDETERMINATE`",
          "Tooltip             : Delete Tool             " " `TTM_DELTOOLA`",
          "Trackbar            : Set Position            " " `TBM_SETPOS`"
        ); break;

        #if defined CBEM_SETITEMW
          case CBEM_SETITEMW:
        #elif defined RB_GETBANDCOUNT
          case RB_GETBANDCOUNT:
        #elif defined SB_GETTEXTLENGTHW
          case SB_GETTEXTLENGTHW:
        #elif defined TBM_SETSELEND
          case TBM_SETSELEND:
        #elif defined TB_ISBUTTONHIDDEN
          case TB_ISBUTTONHIDDEN:
        #elif defined TTM_UPDATETIPTEXTA
          case TTM_UPDATETIPTEXTA:
        #elif defined WIZ_PREV
          case WIZ_PREV:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Combo Box (Extended): Set Item         " " `CBEM_SETITEMW`",
          "Rebar               : Get Band Count   " " `RB_GETBANDCOUNT`",
          "Status Bar          : Get Text Length  " " `SB_GETTEXTLENGTHW`",
          "Toolbar             : Is Button Hidden " " `TB_ISBUTTONHIDDEN`",
          "Tooltip             : Update Tip Text  " " `TTM_UPDATETIPTEXTA`",
          "Trackbar            : Set Selection End" " `TBM_SETSELEND`",
          "Wizard              : Previous         " " `WIZ_PREV`"
        ); break;

        #if defined DDM_SETFMT
          case DDM_SETFMT:
        #elif defined DM_GETDEFID
          case DM_GETDEFID:
        #elif defined NIN_SELECT
          case NIN_SELECT:
        #elif defined TBM_GETPOS
          case TBM_GETPOS:
        #elif defined WM_PSD_PAGESETUPDLG
          case WM_PSD_PAGESETUPDLG:
        #elif defined WM_USER
          case WM_USER:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Dialog           : Get Default Identity" " `DM_GETDEFID`",
          "Direct Draw      : Set Format          " " `DDM_SETFMT`",
          "Notify Icon      : Select              " " `NIN_SELECT`",
          "Page Setup Dialog: Page Setup Dialog   " " `WM_PSD_PAGESETUPDLG`",
          "Trackbar         : Get Position        " " `TBM_GETPOS`",
          "Windows          : User                " " `WM_USER`"
        ); break;

        #if defined WM_CLOSE
          case WM_CLOSE:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter, "Windows: Close" " `WM_CLOSE`"); ::PostQuitMessage(EXIT_SUCCESS); break;

        #if defined WM_DESTROY
          case WM_DESTROY:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter, "Windows: Destroy" " `WM_DESTROY`"); ::PostQuitMessage(EXIT_SUCCESS); break;

        #if defined WM_KEYDOWN
          case WM_KEYDOWN:
        #elif defined WM_KEYFIRST
          case WM_KEYFIRST:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter,
          "Windows: Key 1st " " `WM_KEYFIRST`",
          "Windows: Key Down" " `WM_KEYDOWN`"
        ); if (VK_ESCAPE == parameter) ::PostQuitMessage(EXIT_SUCCESS); break;

        #if defined WM_QUIT
          case WM_QUIT:
        #else
          case __LINE__: if (false)
        #endif
        (void) output::log(message, parameter, subparameter, "Windows: Quit" " `WM_QUIT`"); ::DestroyWindow(handle); break;
      }
      // switch (message) {
      //   /* [Common Item Dialog] */
      //   // case CDM_GETFILEPATH    : break;
      //   // case CDM_GETFOLDERIDLIST: break;
      //   // case CDM_GETFOLDERPATH  : break;
      //   case CDM_HIDECONTROL: /* --> EM_GETIMECOLOR | IPM_ISBLANK | PSM_RESTARTWINDOWS | UDM_SETBUDDY */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', CDM_HIDECONTROL, "]: {");
      //       std::fputs("Common Dialog    : Hide Control"                        "\r\n", stdout);
      //       std::fputs("Internet Protocol: Is Blank"                            "\r\n", stdout);
      //       std::fputs("Prop Sheet       : Restart Windows"                     "\r\n", stdout);
      //       std::fputs("Rich Edit        : Get IME (Input Method Editor) Color" "\r\n", stdout);
      //       std::fputs("Up-Down Control  : Set Buddy"                           "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case CDM_FIRST  : break;
      //   // case CDM_GETSPEC: break;
      //   case CDM_LAST: /* (Lapys) > EM_SETBIDIOPTIONS | IE_DOCOMMAND | MCIWNDM_NOTIFYMODE */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', CDM_LAST, "]: {");
      //       std::fputs("Common Dialog        : [LAST]"                     "\r\n", stdout);
      //       std::fputs("Ink Edit             : Do Command"                 "\r\n", stdout);
      //       std::fputs("Multimedia MCI Window: Notify Mode"                "\r\n", stdout);
      //       std::fputs("Rich Edit            : Set Bi-directional Options" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case CDM_SETCONTROLTEXT: break;
      //   case CDM_SETDEFEXT: /* --> EM_SETIMEOPTIONS | PSM_REBOOTSYSTEM | UDM_GETBUDDY */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', CDM_SETDEFEXT, "]: {");
      //       std::fputs("Common Dialog  : Set Default Text"                      "\r\n", stdout);
      //       std::fputs("Prop Sheet     : Reboot System"                         "\r\n", stdout);
      //       std::fputs("Rich Edit      : Set IME (Input Method Editor) Options" "\r\n", stdout);
      //       std::fputs("Up-Down Control: Get Buddy"                             "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;

      //   /* [Drag List (Box)] */
      //   case DL_BEGINDRAG: /* --> MCIWNDM_GETINACTIVETIMER | PSM_IDTOINDEX | TB_BUTTONCOUNT | TTM_SETMAXTIPWIDTH */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', DL_BEGINDRAG, "]: {");
      //       std::fputs("Drag List Box        : Begin Drag"            "\r\n", stdout);
      //       std::fputs("Multimedia MCI Window: Get Inactive Timer"    "\r\n", stdout);
      //       std::fputs("Prop Sheet           : Identity to Index"     "\r\n", stdout);
      //       std::fputs("Toolbar              : Button Count"          "\r\n", stdout);
      //       std::fputs("Tooltip              : Set Maximum Tip Width" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case DL_CANCELDRAG: /* --> PSM_RECALCPAGESIZES */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', DL_CANCELDRAG, "]: {");
      //       std::fputs("Drag List Box: Cancel Drag"            "\r\n", stdout);
      //       std::fputs("Prop Sheet   : Recalculate Page Sizes" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case DL_DRAGGING: /* --> PSM_INDEXTOID */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', DL_DRAGGING, "]: {");
      //       std::fputs("Drag List Box: Dragging"          "\r\n", stdout);
      //       std::fputs("Prop Sheet   : Index to Identity" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case DL_DROPPED: /* --> PSM_GETRESULT */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', DL_DROPPED, "]: {");
      //       std::fputs("Drag List Box: Dropped"     "\r\n", stdout);
      //       std::fputs("Prop Sheet   : Get Results" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;

      //   /* [Dialog] */
      //   // case DM_GETDEFID  : break;
      //   // case DM_REPOSITION: break;
      //   // case DM_SETDEFID  : break;

      //   /* [Rich Edit] */
      //   case EM_AUTOURLDETECT: /* --> TB_GETSTRINGW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_AUTOURLDETECT, "]: {");
      //       std::fputs("Rich Edit: Automatic URL Detect" "\r\n", stdout);
      //       std::fputs("Toolbar  : Get String"           "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_CANPASTE: /* --> TB_LOADIMAGES */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_CANPASTE, "]: {");
      //       std::fputs("Rich Edit: Can Paste"   "\r\n", stdout);
      //       std::fputs("Toolbar  : Load Images" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_CANREDO: /* --> TB_GETEXTENDEDSTYLE */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_CANREDO, "]: {");
      //       std::fputs("Rich Edit: Can Redo"           "\r\n", stdout);
      //       std::fputs("Toolbar  : Get Extended Style" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_CANUNDO    : std::fprintf(stdout, "%c%X%s", '[', EM_CANUNDO,     "]: Rich Edit > Can Undo"                "\r\n"); break;
      //   case EM_CHARFROMPOS: std::fprintf(stdout, "%c%X%s", '[', EM_CHARFROMPOS, "]: Rich Edit > Character from Position" "\r\n"); break;
      //   case EM_CONVPOSITION: /* --> PSM_QUERYSIBLINGS | UDM_GETACCEL */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_CONVPOSITION, "]: {");
      //       std::fputs("Prop Sheet     : Query Siblings"  "\r\n", stdout);
      //       std::fputs("Rich Edit      : Conv... Position" "\r\n", stdout);
      //       std::fputs("Up-Down Control: Get Acceleration" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_DISPLAYBAND: /* --> TB_GETRECT | TTM_DELTOOLW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_DISPLAYBAND, "]: {");
      //       std::fputs("Rich Edit: Display Band"  "\r\n", stdout);
      //       std::fputs("Toolbar  : Get Rectangle" "\r\n", stdout);
      //       std::fputs("Tooltip  : Delete Tool"   "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_EMPTYUNDOBUFFER: std::fprintf(stdout, "%c%X%s", '[', EM_EMPTYUNDOBUFFER, "]: Rich Edit > Empty Undo Buffer" "\r\n"); break;
      //   case EM_EXGETSEL: /* --> TB_SETHOTIMAGELIST | TTM_NEWTOOLRECTW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_EXGETSEL, "]: {");
      //       std::fputs("Rich Edit: Extend Get Selection" "\r\n", stdout);
      //       std::fputs("Toolbar  : Set Hot Image List"   "\r\n", stdout);
      //       std::fputs("Tooltip  : New Tool Rectangle"   "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_EXLIMITTEXT: /* --> TB_GETHOTIMAGELIST | TTM_GETTOOLINFOW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_EXLIMITTEXT, "]: {");
      //       std::fputs("Rich Edit: Extend Limit Text"    "\r\n", stdout);
      //       std::fputs("Toolbar  : Get Hot Image List"   "\r\n", stdout);
      //       std::fputs("Tooltip  : Get Tool Information" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_EXLINEFROMCHAR: /* --> TB_SETDISABLEDIMAGELIST | TTM_SETTOOLINFOW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_EXLINEFROMCHAR, "]: {");
      //       std::fputs("Rich Edit: Extend Line From Character" "\r\n", stdout);
      //       std::fputs("Toolbar  : Set Disabled Image List"    "\r\n", stdout);
      //       std::fputs("Tooltip  : Set Tool Information"       "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_EXSETSEL: /* --> TB_GETDISABLEDIMAGELIST | TTM_HITTESTW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_EXSETSEL, "]: {");
      //       std::fputs("Rich Edit: Extend Set Selection"    "\r\n", stdout);
      //       std::fputs("Toolbar  : Get Disabled Image List" "\r\n", stdout);
      //       std::fputs("Tooltip  : Hit Test"                "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_FINDTEXT: /* --> TB_SETSTYLE | TTM_GETTEXTW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_FINDTEXT, "]: {");
      //       std::fputs("Rich Edit: Find Text" "\r\n", stdout);
      //       std::fputs("Toolbar  : Set Style" "\r\n", stdout);
      //       std::fputs("Tooltip  : Get Text"  "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_FINDTEXTEX: /* --> TB_GETINSERTMARK */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_FINDTEXTEX, "]: {");
      //       std::fputs("Rich Edit: Find Text (Extended)" "\r\n", stdout);
      //       std::fputs("Toolbar  : Get Insert Mark"      "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_FINDTEXTEXW: /* --> MCIWNDM_GETFILENAMEA */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_FINDTEXTEXW, "]: {");
      //       std::fputs("Rich Edit              : Find Text (Extended)" "\r\n", stdout);
      //       std::fputs("Multimedia (MCI) Window: Get File Name"        "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_FINDTEXTW: /* --> MCIWNDM_PLAYTO | WM_CAP_FILE_SAVEASW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_FINDTEXTW, "]: {");
      //       std::fputs("Rich Edit              : Find Text (Extended)" "\r\n", stdout);
      //       std::fputs("Multimedia (MCI) Window: Play To"              "\r\n", stdout);
      //       std::fputs("Windows Capture        : File Save As"         "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_FINDWORDBREAK: /* --> TB_SAVERESTOREW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_FINDWORDBREAK, "]: {");
      //       std::fputs("Rich Edit: Find Word Break" "\r\n", stdout);
      //       std::fputs("Toolbar  : Save Restore"    "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_FMTLINES: std::fprintf(stdout, "%c%X%s", '[', EM_FMTLINES, "]: Rich Edit > Format Lines" "\r\n"); break;
      //   case EM_FORMATRANGE: /* --> TB_GETSTYLE | TTM_UPDATETIPTEXTW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_FORMATRANGE, "]: {");
      //       std::fputs("Rich Edit: Format Range"    "\r\n", stdout);
      //       std::fputs("Toolbar  : Get Style"       "\r\n", stdout);
      //       std::fputs("Tooltip  : Update Tip Text" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETAUTOURLDETECT: /* --> TB_GETSTRINGA */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETAUTOURLDETECT, "]: {");
      //       std::fputs("Rich Edit: Get Automatic URL Detection" "\r\n", stdout);
      //       std::fputs("Toolbar  : Get String"                  "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETBIDIOPTIONS: /* --> IE_GETCOMMAND */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETBIDIOPTIONS, "]: {");
      //       std::fputs("Ink Edit : Get Command"                "\r\n", stdout);
      //       std::fputs("Rich Edit: Get Bi-directional Options" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETCHARFORMAT: /* --> TB_GETBUTTONSIZE | TTM_ENUMTOOLSW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETCHARFORMAT, "]: {");
      //       std::fputs("Rich Edit: Get Character Format" "\r\n", stdout);
      //       std::fputs("Toolbar  : Get Button Size"      "\r\n", stdout);
      //       std::fputs("Tooltip  : Enumerate Tools"      "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETCTFMODEBIAS  : std::fprintf(stdout, "%c%X%s", '[', EM_GETCTFMODEBIAS,   "]: Rich Edit > Get CTF Mode Bias"   "\r\n"); break;
      //   case EM_GETCTFOPENSTATUS: std::fprintf(stdout, "%c%X%s", '[', EM_GETCTFOPENSTATUS, "]: Rich Edit > Get CTF Open Status" "\r\n"); break;
      //   case EM_GETEDITSTYLE: /* --> MCIWNDM_NOTIFYERROR */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETEDITSTYLE, "]: {");
      //       std::fputs("Rich Edit            : Get Edit Style" "\r\n", stdout);
      //       std::fputs("Multimedia MCI Window: Notify Error"   "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETEVENTMASK: /* --> TB_SETBUTTONWIDTH | TTM_GETCURRENTTOOLW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETEVENTMASK, "]: {");
      //       std::fputs("Rich Edit: Get Event Mask"   "\r\n", stdout);
      //       std::fputs("Toolbar  : Set Button Width" "\r\n", stdout);
      //       std::fputs("Tooltip  : Get Current Tool" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETFIRSTVISIBLELINE: std::fprintf(stdout, "%c%X%s", '[', EM_GETFIRSTVISIBLELINE, "]: Rich Edit > Get First Visible Line"    "\r\n"); break;
      //   case EM_GETHANDLE          : std::fprintf(stdout, "%c%X%s", '[', EM_GETHANDLE,           "]: Rich Edit > Get Handle"                "\r\n"); break;
      //   case EM_GETHYPHENATEINFO   : std::fprintf(stdout, "%c%X%s", '[', EM_GETHYPHENATEINFO,    "]: Rich Edit > Get Hyphenate Information" "\r\n"); break;
      //   // case EM_GETIMECOLOR: break;
      //   case EM_GETIMECOMPMODE: std::fprintf(stdout, "%c%X%s", '[', EM_GETIMECOMPMODE, "]: Rich Edit > Get IME (Input Method Editor) Composition Mode" "\r\n"); break;
      //   case EM_GETIMECOMPTEXT: std::fprintf(stdout, "%c%X%s", '[', EM_GETIMECOMPTEXT, "]: Rich Edit > Get IME (Input Method Editor) Composition Text" "\r\n"); break;
      //   case EM_GETIMEMODEBIAS: /* --> MCIWNDM_SETPALETTE | PSM_SETHEADERSUBTITLEA */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETIMEMODEBIAS, "]: {");
      //       std::fputs("Rich Edit            : Get IME (Input Method Editor) Mode Bias" "\r\n", stdout);
      //       std::fputs("Multimedia MCI Window: Set Palette"                             "\r\n", stdout);
      //       std::fputs("Prop Sheet           : Set Header Subtitle"                     "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETIMEOPTIONS: /* --> PSM_CANCELTOCLOSE | UDM_SETACCEL */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETIMEOPTIONS, "]: {");
      //       std::fputs("Rich Edit      : Get IME (Input Method Editor) Options" "\r\n", stdout);
      //       std::fputs("Prop Sheet     : Cancel to Close"                       "\r\n", stdout);
      //       std::fputs("Up-Down Control: Set Acceleration"                      "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETIMEPROPERTY: std::fprintf(stdout, "%c%X%s", '[', EM_GETIMECOMPTEXT, "]: Rich Edit > Get IME (Input Method Editor) Property" "\r\n"); break;
      //   case EM_GETIMESTATUS  : std::fprintf(stdout, "%c%X%s", '[', EM_GETIMESTATUS,   "]: Rich Edit > Get IME (Input Method Editor) Status"   "\r\n"); break;
      //   case EM_GETLANGOPTIONS: /* --> MCIWNDM_VALIDATEMEDIA | PSM_SETCURSEL | PSM_SETFINISHTEXTA | PSM_SETFINISHTEXTW | WM_CAP_FILE_GET_CAPTURE_FILEW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETLANGOPTIONS, "]: {");
      //       std::fputs("Rich Edit              : Get Language Options" "\r\n", stdout);
      //       std::fputs("Multimedia (MCI) Window: Validate Media"       "\r\n", stdout);
      //       std::fputs("Prop Sheet             : Set Cursor Selection" "\r\n", stdout);
      //       std::fputs("Prop Sheet             : Set Finish Text"      "\r\n", stdout);
      //       std::fputs("Windows Capture        : File Get Capture"     "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETLIMITTEXT: std::fprintf(stdout, "%c%X%s", '[', EM_GETLIMITTEXT, "]: Rich Edit > Get Limit Text" "\r\n"); break;
      //   case EM_GETLINE     : std::fprintf(stdout, "%c%X%s", '[', EM_GETLINE,      "]: Rich Edit > Get Line"       "\r\n"); break;
      //   case EM_GETLINECOUNT: std::fprintf(stdout, "%c%X%s", '[', EM_GETLINECOUNT, "]: Rich Edit > Get Line Count" "\r\n"); break;
      //   case EM_GETMARGINS  : std::fprintf(stdout, "%c%X%s", '[', EM_GETMARGINS,   "]: Rich Edit > Get Margins"    "\r\n"); break;
      //   case EM_GETMODIFY   : std::fprintf(stdout, "%c%X%s", '[', EM_GETMODIFY,    "]: Rich Edit > Get Modify"     "\r\n"); break;
      //   case EM_GETOLEINTERFACE: /* --> TB_SETMAXTEXTROWS */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETOLEINTERFACE, "]: {");
      //       std::fputs("Rich Edit: Get Tole Interface"    "\r\n", stdout);
      //       std::fputs("Toolbar  : Set Maximum Text Rows" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETOPTIONS: /* --> TB_MAPACCELERATORA */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETOPTIONS, "]: {");
      //       std::fputs("Rich Edit: Get Options"     "\r\n", stdout);
      //       std::fputs("Toolbar  : Map Accelerator" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETPAGE: {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETPAGE, "]: {");
      //       std::fputs("Multimedia (MCI) Window: Get Error" "\r\n", stdout);
      //       std::fputs("Rich Edit              : Get Page"  "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETPAGEROTATE: std::fprintf(stdout, "%c%X%s", '[', EM_GETPAGEROTATE, "]: Rich Edit > Get Page Rotate" "\r\n"); break;
      //   case EM_GETPARAFORMAT: /* --> TB_GETTEXTROWS */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETPARAFORMAT, "]: {");
      //       std::fputs("Rich Edit: Get Paragraph Format" "\r\n", stdout);
      //       std::fputs("Toolbar  : Get Text Rows"        "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETPASSWORDCHAR: std::fprintf(stdout, "%c%X%s", '[', EM_GETPASSWORDCHAR, "]: Rich Edit > Get Password Character" "\r\n"); break;
      //   // case EM_GETPUNCTUATION: break;
      //   // case EM_GETQUERYRTFOBJ: break;
      //   case EM_GETRECT: std::fprintf(stdout, "%c%X%s", '[', EM_GETRECT, "]: Rich Edit > Get Rectangle" "\r\n"); break;
      //   case EM_GETREDONAME: /* --> TB_SETPADDING */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETREDONAME, "]: {");
      //       std::fputs("Rich Edit: Get Redo Name" "\r\n", stdout);
      //       std::fputs("Toolbar  : Set Padding"   "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETSCROLLPOS: std::fprintf(stdout, "%c%X%s", '[', EM_GETSCROLLPOS, "]: Rich Edit > Get Scroll Position" "\r\n"); break;
      //   case EM_GETSEL      : std::fprintf(stdout, "%c%X%s", '[', EM_GETSEL,       "]: Rich Edit > Get Selection"       "\r\n"); break;
      //   case EM_GETSELTEXT: /* --> TB_GETOBJECT */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETSELTEXT, "]: {");
      //       std::fputs("Rich Edit: Get Selection Text" "\r\n", stdout);
      //       std::fputs("Toolbar  : Get Object"         "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETTEXTEX      : std::fprintf(stdout, "%c%X%s", '[', EM_GETTEXTEX,       "]: Rich Edit > Get Text (Extended)"        "\r\n"); break;
      //   case EM_GETTEXTLENGTHEX: std::fprintf(stdout, "%c%X%s", '[', EM_GETTEXTLENGTHEX, "]: Rich Edit > Get Text Length (Extended)" "\r\n"); break;
      //   case EM_GETTEXTMODE: /* --> TB_MAPACCELERATORW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETTEXTMODE, "]: {");
      //       std::fputs("Rich Edit: Get Text Mode"    "\r\n", stdout);
      //       std::fputs("Toolbar  : Map Acceleration" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETTEXTRANGE: /* --> TB_GETBUTTONTEXTW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETTEXTRANGE, "]: {");
      //       std::fputs("Rich Edit: Get Text Range"  "\r\n", stdout);
      //       std::fputs("Toolbar  : Get Button Text" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETTHUMB: std::fprintf(stdout, "%c%X%s", '[', EM_GETTHUMB, "]: Rich Edit > Get Thumb" "\r\n"); break;
      //   case EM_GETTYPOGRAPHYOPTIONS: /* --> IE_GETGESTURE | MCIWNDM_NOTIFYMEDIA */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETTYPOGRAPHYOPTIONS, "]: {");
      //       std::fputs("Ink Edit               : Get Gesture"            "\r\n", stdout);
      //       std::fputs("Multimedia (MCI) Window: Notify Media"           "\r\n", stdout);
      //       std::fputs("Rich Edit              : Get Typography Options" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETUNDONAME: /* --> TB_GETPADDING */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETUNDONAME, "]: {");
      //       std::fputs("Rich Edit: Get Undo Name" "\r\n", stdout);
      //       std::fputs("Toolbar  : Get Padding"   "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_GETVIEWKIND     : std::fprintf(stdout, "%c%X%s", '[', EM_GETVIEWKIND,      "]: Rich Edit > Get View Kind"            "\r\n"); break;
      //   case EM_GETWORDBREAKPROC: std::fprintf(stdout, "%c%X%s", '[', EM_GETWORDBREAKPROC, "]: Rich Edit > Get Word Break Procedure" "\r\n"); break;
      //   case EM_GETWORDBREAKPROCEX: /* --> TB_SETINSERTMARK */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETWORDBREAKPROCEX, "]: {");
      //       std::fputs("Rich Edit: Get Word Break Procedure (Extended)" "\r\n", stdout);
      //       std::fputs("Toolbar  : Set Insert Mark"                     "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case EM_GETWORDWRAPMODE: break;
      //   case EM_GETZOOM: /* --> MCIWNDM_GETFILENAMEW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_GETZOOM, "]: {");
      //       std::fputs("Multimedia (MCI) Window: Get File Name" "\r\n", stdout);
      //       std::fputs("Rich Edit              : Get Zoom"      "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_HIDESELECTION: /* --> TB_GETBUTTONINFOW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_HIDESELECTION, "]: {");
      //       std::fputs("Rich Edit: Hide Selection"         "\r\n", stdout);
      //       std::fputs("Toolbar  : Get Button Information" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_ISIME: std::fprintf(stdout, "%c%X%s", '[', EM_ISIME, "]: Rich Edit > Is IME (Input Method Editor)" "\r\n"); break;
      //   case EM_LIMITTEXT: /* --> EM_SETLIMITTEXT */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_LIMITTEXT, "]: {");
      //       std::fputs("Rich Edit: Limit Text"     "\r\n", stdout);
      //       std::fputs("Rich Edit: Set Limit Text" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_LINEFROMCHAR: std::fprintf(stdout, "%c%X%s", '[', EM_LINEFROMCHAR, "]: Rich Edit > Line From Character"          "\r\n"); break;
      //   case EM_LINEINDEX   : std::fprintf(stdout, "%c%X%s", '[', EM_LINEINDEX,    "]: Rich Edit > Line Index"                   "\r\n"); break;
      //   case EM_LINELENGTH  : std::fprintf(stdout, "%c%X%s", '[', EM_LINELENGTH,   "]: Rich Edit > Line Length"                  "\r\n"); break;
      //   case EM_LINESCROLL  : std::fprintf(stdout, "%c%X%s", '[', EM_LINESCROLL,   "]: Rich Edit > Line Scroll"                  "\r\n"); break;
      //   case EM_OUTLINE     : std::fprintf(stdout, "%c%X%s", '[', EM_OUTLINE,      "]: Rich Edit > Line Outline"                 "\r\n"); break;
      //   case EM_PASTESPECIAL: std::fprintf(stdout, "%c%X%s", '[', EM_PASTESPECIAL, "]: Rich Edit > Line Paste Special"           "\r\n"); break;
      //   case EM_POSFROMCHAR : std::fprintf(stdout, "%c%X%s", '[', EM_POSFROMCHAR,  "]: Rich Edit > Line Position from Character" "\r\n"); break;
      //   case EM_RECONVERSION: /* --> MCIWNDM_GETDEVICEA | PSM_SETHEADERTITLEA | WM_CAP_FILE_SAVEDIBW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_RECONVERSION, "]: {");
      //       std::fputs("Multimedia (MCI) Window: Get Device"       "\r\n", stdout);
      //       std::fputs("Prop Sheet             : Set Header Title" "\r\n", stdout);
      //       std::fputs("Rich Edit              : Reconversion"     "\r\n", stdout);
      //       std::fputs("Windows Capture        : File Save ..."    "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_REDO: /* --> TB_SETEXTENDEDSTYLE */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_REDO, "]: {");
      //       std::fputs("Rich Edit: Redo"               "\r\n", stdout);
      //       std::fputs("Toolbar  : Set Extended Style" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_REPLACESEL: std::fprintf(stdout, "%c%X%s", '[', EM_REPLACESEL, "]: Rich Edit > Replace Selection" "\r\n"); break;
      //   case EM_REQUESTRESIZE: /* --> TB_GETBUTTONINFOA */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_REQUESTRESIZE, "]: {");
      //       std::fputs("Rich Edit: Request Resize"         "\r\n", stdout);
      //       std::fputs("Toolbar  : Get Button Information" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_SCROLL     : std::fprintf(stdout, "%c%X%s", '[', EM_SCROLL,      "]: Rich Edit > Scroll"       "\r\n"); break;
      //   case EM_SCROLLCARET: std::fprintf(stdout, "%c%X%s", '[', EM_SCROLLCARET, "]: Rich Edit > Scroll Caret" "\r\n"); break;
      //   case EM_SELECTIONTYPE: /* --> TB_SETBUTTONINFOA */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_SELECTIONTYPE, "]: {");
      //       std::fputs("Rich Edit: Selection Type"         "\r\n", stdout);
      //       std::fputs("Toolbar  : Set Button Information" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case EM_SETBIDIOPTIONS: break;
      //   case EM_SETBKGNDCOLOR: /* --> TB_INSERTBUTTONW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_SETBKGNDCOLOR, "]: {");
      //       std::fputs("Rich Edit: Set Background Color" "\r\n", stdout);
      //       std::fputs("Toolbar  : Insert Button"        "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_SETCHARFORMAT: /* --> TB_ADDBUTTONSW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_SETCHARFORMAT, "]: {");
      //       std::fputs("Rich Edit: Set Character Format" "\r\n", stdout);
      //       std::fputs("Toolbar  : Add Buttons"          "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_SETCTFMODEBIAS  : std::fprintf(stdout, "%c%X%s", '[', EM_SETCTFMODEBIAS,   "]: Rich Edit > Set CTF Mode Bias" "\r\n");   break;
      //   case EM_SETCTFOPENSTATUS: std::fprintf(stdout, "%c%X%s", '[', EM_SETCTFOPENSTATUS, "]: Rich Edit > Set CTF Open Status" "\r\n"); break;
      //   case EM_SETEDITSTYLE: /* --> IE_GETMENU */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_SETEDITSTYLE, "]: {");
      //       std::fputs("Ink Edit : Get Menu"       "\r\n", stdout);
      //       std::fputs("Rich Edit: Set Edit Style" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_SETEVENTMASK: /* --> TB_HITTEST */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_SETEVENTMASK, "]: {");
      //       std::fputs("Rich Edit: Set Event Mask" "\r\n", stdout);
      //       std::fputs("Toolbar  : Hit Test"       "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_SETFONT         : std::fprintf(stdout, "%c%X%s", '[', EM_SETFONT,          "]: Rich Edit > Set Font"                  "\r\n"); break;
      //   case EM_SETFONTSIZE     : std::fprintf(stdout, "%c%X%s", '[', EM_SETFONTSIZE,      "]: Rich Edit > Set Font Size"             "\r\n"); break;
      //   case EM_SETHANDLE       : std::fprintf(stdout, "%c%X%s", '[', EM_SETHANDLE,        "]: Rich Edit > Set Handle"                "\r\n"); break;
      //   case EM_SETHYPHENATEINFO: std::fprintf(stdout, "%c%X%s", '[', EM_SETHYPHENATEINFO, "]: Rich Edit > Set Hyphenate Information" "\r\n");  break;
      //   // case EM_SETIMECOLOR: break;
      //   case EM_SETIMEMODEBIAS: /* --> MCIWNDM_GETPALETTE | PSM_SETHEADERTITLEW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_SETIMEMODEBIAS, "]: {");
      //       std::fputs("Multimedia (MCI) Window: Get Palette"                             "\r\n", stdout);
      //       std::fputs("Prop Sheet             : Set Header Title"                        "\r\n", stdout);
      //       std::fputs("Rich Edit              : Set IME (Input Method Editor) Mode Bias" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case EM_SETIMEOPTIONS: break;
      //   case EM_SETIMESTATUS: std::fprintf(stdout, "%c%X%s", '[', EM_SETIMESTATUS, "]: Rich Edit > Set Time Status" "\r\n"); break;
      //   case EM_SETLANGOPTIONS: /* --> MCIWNDM_GETTIMEFORMATA | PSM_SETTITLEW | WM_CAP_FILE_SET_CAPTURE_FILEW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_SETLANGOPTIONS, "]: {");
      //       std::fputs("Multimedia (MCI) Window: Get Time Format"       "\r\n", stdout);
      //       std::fputs("Prop Sheet             : Set Title"             "\r\n", stdout);
      //       std::fputs("Rich Edit              : Set Language Options"  "\r\n", stdout);
      //       std::fputs("Windows Capture        : File Set Capture File" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_SETMARGINS: std::fprintf(stdout, "%c%X%s", '[', EM_SETMARGINS, "]: Rich Edit > Set Margins" "\r\n"); break;
      //   case EM_SETMODIFY : std::fprintf(stdout, "%c%X%s", '[', EM_SETMODIFY,  "]: Rich Edit > Set Modify"  "\r\n"); break;
      //   // case EM_SETLIMITTEXT: break;
      //   case EM_SETOLECALLBACK: /* --> TB_SETDRAWTEXTFLAGS */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_SETOLECALLBACK, "]: {");
      //       std::fputs("Rich Edit: Set OLE (Object Linking & Embedding) Callback" "\r\n", stdout);
      //       std::fputs("Toolbar  : Set Draw Text Flags"                           "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_SETOPTIONS: /* --> TB_ADDSTRINGW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_SETOLECALLBACK, "]: {");
      //       std::fputs("Rich Edit: Set Options" "\r\n", stdout);
      //       std::fputs("Toolbar  : Add String"  "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_SETPAGE      : std::fprintf(stdout, "%c%X%s", '[', EM_SETPAGE,       "]: Rich Edit > Set Page"        "\r\n"); break;
      //   case EM_SETPAGEROTATE: std::fprintf(stdout, "%c%X%s", '[', EM_SETPAGEROTATE, "]: Rich Edit > Set Page Rotate" "\r\n"); break;
      //   case EM_SETPALETTE   : std::fprintf(stdout, "%c%X%s", '[', EM_SETPALETTE,    "]: Rich Edit > Set Palette"     "\r\n"); break;
      //   case EM_SETPARAFORMAT: /* --> TB_GETHOTITEM */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_SETPARAFORMAT, "]: {");
      //       std::fputs("Rich Edit: Set Paragraph Format" "\r\n", stdout);
      //       std::fputs("Toolbar  : Get Hot Item"         "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_SETPASSWORDCHAR: std::fprintf(stdout, "%c%X%s", '[', EM_SETPASSWORDCHAR, "]: Rich Edit > Set Password Character" "\r\n"); break;
      //   // case EM_SETPUNCTUATION: break;
      //   case EM_SETQUERYRTFOBJ: std::fprintf(stdout, "%c%X%s", '[', EM_SETQUERYRTFOBJ, "]: Rich Edit > Set Query Rich-Text Format Object" "\r\n"); break;
      //   case EM_SETREADONLY   : std::fprintf(stdout, "%c%X%s", '[', EM_SETREADONLY,    "]: Rich Edit > Set Read-Only"                     "\r\n"); break;
      //   case EM_SETRECT       : std::fprintf(stdout, "%c%X%s", '[', EM_SETRECT,        "]: Rich Edit > Set Rectangle"                     "\r\n"); break;
      //   case EM_SETRECTNP     : std::fprintf(stdout, "%c%X%s", '[', EM_SETRECTNP,      "]: Rich Edit > Set Rectangle New Position"        "\r\n"); break;
      //   case EM_SETSCROLLPOS  : std::fprintf(stdout, "%c%X%s", '[', EM_SETSCROLLPOS,   "]: Rich Edit > Set Scroll Position"               "\r\n"); break;
      //   case EM_SETSEL        : std::fprintf(stdout, "%c%X%s", '[', EM_SETSEL,         "]: Rich Edit > Set Selection"                     "\r\n"); break;
      //   case EM_SETTABSTOPS   : std::fprintf(stdout, "%c%X%s", '[', EM_SETTABSTOPS,    "]: Rich Edit > Set Absolute Stops"                "\r\n"); break;
      //   case EM_SETTARGETDEVICE: /* --> TB_SETHOTITEM */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_SETTARGETDEVICE, "]: {");
      //       std::fputs("Rich Edit: Set Target Device" "\r\n", stdout);
      //       std::fputs("Toolbar  : Set Hot Item"      "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_SETTEXTEX: std::fprintf(stdout, "%c%X%s", '[', EM_SETTEXTEX, "]: Rich Edit > Set Text (Extended)" "\r\n"); break;
      //   case EM_SETTEXTMODE: /* --> TB_GETINSERTMARKCOLOR */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_SETTEXTMODE, "]: {");
      //       std::fputs("Rich Edit: Set Text Mode"         "\r\n", stdout);
      //       std::fputs("Toolbar  : Get Insert Mark Color" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_SETTYPOGRAPHYOPTIONS: /* --> IE_GETCOUNT */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_SETTYPOGRAPHYOPTIONS, "]: {");
      //       std::fputs("Ink Edit : Get Count"              "\r\n", stdout);
      //       std::fputs("Rich Edit: Set Typography Options" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_SETUNDOLIMIT: /* --> TB_MOVEBUTTON */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_SETUNDOLIMIT, "]: {");
      //       std::fputs("Rich Edit: Set Undo Limit" "\r\n", stdout);
      //       std::fputs("Toolbar  : Move Button"    "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_SETVIEWKIND     : std::fprintf(stdout, "%c%X%s", '[', EM_SETVIEWKIND,      "]: Rich Edit > Set View Kind"            "\r\n"); break;
      //   case EM_SETWORDBREAK    : std::fprintf(stdout, "%c%X%s", '[', EM_SETWORDBREAK,     "]: Rich Edit > Set Word Break"           "\r\n"); break;
      //   case EM_SETWORDBREAKPROC: std::fprintf(stdout, "%c%X%s", '[', EM_SETWORDBREAKPROC, "]: Rich Edit > Set Word Break Procedure" "\r\n"); break;
      //   case EM_SETWORDBREAKPROCEX: /* --> TB_INSERTMARKHITTEST */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_SETWORDBREAKPROCEX, "]: {");
      //       std::fputs("Rich Edit: Set Word Break Procedure (Extended)" "\r\n", stdout);
      //       std::fputs("Toolbar  : Insert Mark Hit Test"                "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case EM_SETWORDWRAPMODE: break;
      //   case EM_SETZOOM: /* --> MCIWNDM_GETDEVICEW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_SETZOOM, "]: {");
      //       std::fputs("Multimedia (MCI) Window: Get Device" "\r\n", stdout);
      //       std::fputs("Rich Edit              : Set Zoom"   "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_SHOWSCROLLBAR: std::fprintf(stdout, "%c%X%s", '[', EM_SHOWSCROLLBAR, "]: Rich Edit > Show Scrollbar" "\r\n"); break;
      //   case EM_STOPGROUPTYPING: /* --> TB_SETINSERTMARKCOLOR */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_STOPGROUPTYPING, "]: {");
      //       std::fputs("Rich Edit: Stop Group Typing"     "\r\n", stdout);
      //       std::fputs("Toolbar  : Set Insert Mark Color" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_STREAMIN: /* --> TB_SETANCHORHIGHLIGHT */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_STREAMIN, "]: {");
      //       std::fputs("Rich Edit: Stream In"            "\r\n", stdout);
      //       std::fputs("Toolbar  : Set Anchor Highlight" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_STREAMOUT: /* --> TB_GETANCHORHIGHLIGHT */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', EM_STREAMOUT, "]: {");
      //       std::fputs("Rich Edit: Stream Out"           "\r\n", stdout);
      //       std::fputs("Toolbar  : Get Anchor Highlight" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case EM_UNDO: std::fprintf(stdout, "%c%X%s", '[', EM_UNDO, "]: Rich Edit > Undo" "\r\n"); break;

      //   /* [File Manager] */
      //   case FM_GETDRIVEINFOA    : std::fprintf(stdout, "%c%X%s", '[', FM_GETDRIVEINFOA,     "]: File Manager > Get Drive Information"       "\r\n"); break;
      //   case FM_GETDRIVEINFOW    : std::fprintf(stdout, "%c%X%s", '[', FM_GETDRIVEINFOW,     "]: File Manager > Get Drive Information"       "\r\n"); break;
      //   case FM_GETFILESELA      : std::fprintf(stdout, "%c%X%s", '[', FM_GETFILESELA,       "]: File Manager > Get File Selection"          "\r\n"); break;
      //   case FM_GETFILESELLFNA   : std::fprintf(stdout, "%c%X%s", '[', FM_GETFILESELLFNA,    "]: File Manager > Get File Selection Function" "\r\n"); break;
      //   case FM_GETFILESELLFNW   : std::fprintf(stdout, "%c%X%s", '[', FM_GETFILESELLFNW,    "]: File Manager > Get File Selection Function" "\r\n"); break;
      //   case FM_GETFILESELW      : std::fprintf(stdout, "%c%X%s", '[', FM_GETFILESELW,       "]: File Manager > Get File Selection"          "\r\n"); break;
      //   case FM_GETFOCUS         : std::fprintf(stdout, "%c%X%s", '[', FM_GETFOCUS,          "]: File Manager > Get Focus"                   "\r\n"); break;
      //   case FM_GETSELCOUNT      : std::fprintf(stdout, "%c%X%s", '[', FM_GETSELCOUNT,       "]: File Manager > Selection Count"             "\r\n"); break;
      //   case FM_GETSELCOUNTLFN   : std::fprintf(stdout, "%c%X%s", '[', FM_GETSELCOUNTLFN,    "]: File Manager > Selection Count ..."         "\r\n"); break;
      //   case FM_REFRESH_WINDOWS  : std::fprintf(stdout, "%c%X%s", '[', FM_REFRESH_WINDOWS,   "]: File Manager > Refresh Windows"             "\r\n"); break;
      //   case FM_RELOAD_EXTENSIONS: std::fprintf(stdout, "%c%X%s", '[', FM_RELOAD_EXTENSIONS, "]: File Manager > Reload Extensions"           "\r\n"); break;

      //   /* [Hotkey] */
      //   // case HKM_GETHOTKEY: break;
      //   // case HKM_SETHOTKEY: break;
      //   // case HKM_SETRULES: break;

      //   /* [Ink Edit] */
      //   // case IE_DOCOMMAND: break;
      //   case IE_GETAPPDATA: std::fprintf(stdout, "%c%X%s", '[', IE_GETAPPDATA, "]: Ink Edit > Get Application Data" "\r\n"); break;
      //   case IE_GETBKGND  : std::fprintf(stdout, "%c%X%s", '[', IE_GETBKGND,   "]: Ink Edit > Get Background"       "\r\n"); break;
      //   // case IE_GETCOMMAND: break;
      //   // case IE_GETCOUNT: break;
      //   case IE_GETDRAWOPTS : std::fprintf(stdout, "%c%X%s", '[', IE_GETDRAWOPTS,  "]: Ink Edit > Get Draw Options" "\r\n"); break;
      //   case IE_GETERASERTIP: std::fprintf(stdout, "%c%X%s", '[', IE_GETERASERTIP, "]: Ink Edit > Get Eraser Tip"   "\r\n"); break;
      //   case IE_GETFORMAT   : std::fprintf(stdout, "%c%X%s", '[', IE_GETFORMAT,    "]: Ink Edit > Get Format"       "\r\n"); break;
      //   // case IE_GETGESTURE: break;
      //   case IE_GETGRIDORIGIN: std::fprintf(stdout, "%c%X%s", '[', IE_GETGRIDORIGIN, "]: Ink Edit > Get Grid Origin" "\r\n"); break;
      //   case IE_GETGRIDPEN   : std::fprintf(stdout, "%c%X%s", '[', IE_GETGRIDPEN,    "]: Ink Edit > Get Grid Pen"    "\r\n"); break;
      //   case IE_GETGRIDSIZE  : std::fprintf(stdout, "%c%X%s", '[', IE_GETGRIDSIZE,   "]: Ink Edit > Get Grid Size"   "\r\n"); break;
      //   case IE_GETINK: /* --> IE_MSGFIRST | MCIWNDM_PALETTEKICK */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', IE_GETINK, "]: {");
      //       std::fputs("Ink Edit               : Get Ink [FIRST]" "\r\n", stdout);
      //       std::fputs("Multimedia (MCI) Window: Palette Kick"    "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case IE_GETINKINPUT: std::fprintf(stdout, "%c%X%s", '[', IE_GETAPPDATA, "]: Ink Edit > Get Ink Input" "\r\n"); break;
      //   case IE_GETINKRECT: /* --> WM_CAP_SET_MCI_DEVICEW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', IE_GETINKRECT, "]: {");
      //       std::fputs("Ink Edit       : Get Ink Rectangle"           "\r\n", stdout);
      //       std::fputs("Windows Capture: Set Multimedia (MCI) Device" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case IE_GETMENU: break;
      //   case IE_GETMODE  : std::fprintf(stdout, "%c%X%s", '[', IE_GETAPPDATA, "]: Ink Edit > Get Mode"   "\r\n"); break;
      //   case IE_GETNOTIFY: std::fprintf(stdout, "%c%X%s", '[', IE_GETNOTIFY,  "]: Ink Edit > Get Notify" "\r\n"); break;
      //   // case IE_GETPAINTDC: break;
      //   case IE_GETPDEVENT : std::fprintf(stdout, "%c%X%s", '[', IE_GETPDEVENT,  "]: Ink Edit > Get PD Event"        "\r\n"); break;
      //   case IE_GETPENTIP  : std::fprintf(stdout, "%c%X%s", '[', IE_GETPENTIP,   "]: Ink Edit > Get Pen Tip"         "\r\n"); break;
      //   case IE_GETRECOG   : std::fprintf(stdout, "%c%X%s", '[', IE_GETRECOG,    "]: Ink Edit > Get Recognition"     "\r\n"); break;
      //   case IE_GETSECURITY: std::fprintf(stdout, "%c%X%s", '[', IE_GETSECURITY, "]: Ink Edit > Get Security"        "\r\n"); break;
      //   case IE_GETSEL     : std::fprintf(stdout, "%c%X%s", '[', IE_GETSEL,      "]: Ink Edit > Get Selection"       "\r\n"); break;
      //   case IE_GETSELCOUNT: std::fprintf(stdout, "%c%X%s", '[', IE_GETSELCOUNT, "]: Ink Edit > Get Selection Count" "\r\n"); break;
      //   case IE_GETSELITEMS: std::fprintf(stdout, "%c%X%s", '[', IE_GETSELITEMS, "]: Ink Edit > Get Selection Items" "\r\n"); break;
      //   case IE_GETSTYLE   : std::fprintf(stdout, "%c%X%s", '[', IE_GETSTYLE,    "]: Ink Edit > Get Style"           "\r\n"); break;
      //   // case IE_MSGFIRST: break;
      //   case IE_SETAPPDATA   : std::fprintf(stdout, "%c%X%s", '[', IE_SETAPPDATA,    "]: Ink Edit > Set Application Data" "\r\n"); break;
      //   case IE_SETBKGND     : std::fprintf(stdout, "%c%X%s", '[', IE_SETBKGND,      "]: Ink Edit > Set Background"       "\r\n"); break;
      //   case IE_SETDRAWOPTS  : std::fprintf(stdout, "%c%X%s", '[', IE_SETDRAWOPTS,   "]: Ink Edit > Set Draw Options"     "\r\n"); break;
      //   case IE_SETERASERTIP : std::fprintf(stdout, "%c%X%s", '[', IE_SETERASERTIP,  "]: Ink Edit > Set Eraser Tip"       "\r\n"); break;
      //   case IE_SETFORMAT    : std::fprintf(stdout, "%c%X%s", '[', IE_SETFORMAT,     "]: Ink Edit > Set Format"           "\r\n"); break;
      //   case IE_SETGRIDORIGIN: std::fprintf(stdout, "%c%X%s", '[', IE_SETGRIDORIGIN, "]: Ink Edit > Set Grid Origin"      "\r\n"); break;
      //   case IE_SETGRIDPEN   : std::fprintf(stdout, "%c%X%s", '[', IE_SETGRIDPEN,    "]: Ink Edit > Set Grid Pen"         "\r\n"); break;
      //   case IE_SETGRIDSIZE  : std::fprintf(stdout, "%c%X%s", '[', IE_SETGRIDSIZE,   "]: Ink Edit > Set Grid Size"        "\r\n"); break;
      //   case IE_SETINK       : std::fprintf(stdout, "%c%X%s", '[', IE_SETINK,        "]: Ink Edit > Set Ink"              "\r\n"); break;
      //   case IE_SETINKINPUT  : std::fprintf(stdout, "%c%X%s", '[', IE_SETINKINPUT,   "]: Ink Edit > Set Ink Input"        "\r\n"); break;
      //   case IE_SETMODE      : std::fprintf(stdout, "%c%X%s", '[', IE_SETMODE,       "]: Ink Edit > Set Mode"             "\r\n"); break;
      //   case IE_SETNOTIFY    : std::fprintf(stdout, "%c%X%s", '[', IE_SETNOTIFY,     "]: Ink Edit > Set Notify"           "\r\n"); break;
      //   case IE_SETPENTIP    : std::fprintf(stdout, "%c%X%s", '[', IE_SETPENTIP,     "]: Ink Edit > Set Pen Tip"          "\r\n"); break;
      //   case IE_SETRECOG     : std::fprintf(stdout, "%c%X%s", '[', IE_SETRECOG,      "]: Ink Edit > Set Recognition"      "\r\n"); break;
      //   case IE_SETSECURITY  : std::fprintf(stdout, "%c%X%s", '[', IE_SETSECURITY,   "]: Ink Edit > Set Security"         "\r\n"); break;
      //   case IE_SETSEL       : std::fprintf(stdout, "%c%X%s", '[', IE_SETSEL,        "]: Ink Edit > Set Selection"        "\r\n"); break;

      //   /* [Internet Protocol] */
      //   // case IPM_CLEARADDRESS: break;
      //   // case IPM_GETADDRESS  : break;
      //   // case IPM_ISBLANK     : break;
      //   // case IPM_SETADDRESS  : break;
      //   // case IPM_SETFOCUS    : break;
      //   // case IPM_SETRANGE    : break;

      //   /* [List View] */
      //   // case LVM_APPROXIMATEVIEWRECT: break;
      //   case LVM_ARRANGE        : std::fprintf(stdout, "%c%X%s", '[', LVM_ARRANGE,         "]: List View > Arrange"                           "\r\n"); break;
      //   case LVM_CANCELEDITLABEL: std::fprintf(stdout, "%c%X%s", '[', LVM_CANCELEDITLABEL, "]: List View > Cancel Edit Label"                 "\r\n"); break;
      //   case LVM_CREATEDRAGIMAGE: std::fprintf(stdout, "%c%X%s", '[', LVM_CREATEDRAGIMAGE, "]: List View > Create Drag Image"                 "\r\n"); break;
      //   case LVM_DELETEALLITEMS : std::fprintf(stdout, "%c%X%s", '[', LVM_DELETEALLITEMS,  "]: List View > Delete All Items"                  "\r\n"); break;
      //   case LVM_DELETECOLUMN   : std::fprintf(stdout, "%c%X%s", '[', LVM_DELETECOLUMN,    "]: List View > Delete Column"                     "\r\n"); break;
      //   case LVM_DELETEITEM     : std::fprintf(stdout, "%c%X%s", '[', LVM_DELETEITEM,      "]: List View > Delete Item"                       "\r\n"); break;
      //   case LVM_EDITLABELA     : std::fprintf(stdout, "%c%X%s", '[', LVM_EDITLABELA,      "]: List View > Edit Label"                        "\r\n"); break;
      //   case LVM_EDITLABELW     : std::fprintf(stdout, "%c%X%s", '[', LVM_EDITLABELW,      "]: List View > Edit Label"                        "\r\n"); break;
      //   case LVM_ENABLEGROUPVIEW: std::fprintf(stdout, "%c%X%s", '[', LVM_ENABLEGROUPVIEW, "]: List View > Enable Group View"                 "\r\n"); break;
      //   case LVM_ENSUREVISIBLE  : std::fprintf(stdout, "%c%X%s", '[', LVM_ENSUREVISIBLE,   "]: List View > Ensure Visible"                    "\r\n"); break;
      //   case LVM_FINDITEMA      : std::fprintf(stdout, "%c%X%s", '[', LVM_FINDITEMA,       "]: List View > Find Item"                         "\r\n"); break;
      //   case LVM_FINDITEMW      : std::fprintf(stdout, "%c%X%s", '[', LVM_FINDITEMW,       "]: List View > Find Item"                         "\r\n"); break;
      //   case LVM_FIRST: /* --> LVM_GETBKCOLOR */ std::fprintf(stdout, "%c%X%s", '[', LVM_FIRST, "]: List View > Get Background Color [FIRST]" "\r\n"); break;
      //   // case LVM_GETBKCOLOR: break;
      //   case LVM_GETBKIMAGEA             : std::fprintf(stdout, "%c%X%s", '[', LVM_GETBKIMAGEA,              "]: List View > Get Background Image"          "\r\n"); break;
      //   case LVM_GETBKIMAGEW             : std::fprintf(stdout, "%c%X%s", '[', LVM_GETBKIMAGEW,              "]: List View > Get Background Image"          "\r\n"); break;
      //   case LVM_GETCALLBACKMASK         : std::fprintf(stdout, "%c%X%s", '[', LVM_GETCALLBACKMASK,          "]: List View > Get Call Back Mask"            "\r\n"); break;
      //   case LVM_GETCOLUMNA              : std::fprintf(stdout, "%c%X%s", '[', LVM_GETCOLUMNA,               "]: List View > Get Column"                    "\r\n"); break;
      //   case LVM_GETCOLUMNORDERARRAY     : std::fprintf(stdout, "%c%X%s", '[', LVM_GETCOLUMNORDERARRAY,      "]: List View > Get Column Order Array"        "\r\n"); break;
      //   case LVM_GETCOLUMNW              : std::fprintf(stdout, "%c%X%s", '[', LVM_GETCOLUMNW,               "]: List View > Get Column"                    "\r\n"); break;
      //   case LVM_GETCOLUMNWIDTH          : std::fprintf(stdout, "%c%X%s", '[', LVM_GETCOLUMNWIDTH,           "]: List View > Get Column Width"              "\r\n"); break;
      //   case LVM_GETCOUNTPERPAGE         : std::fprintf(stdout, "%c%X%s", '[', LVM_GETCOUNTPERPAGE,          "]: List View > Get Count per Page"            "\r\n"); break;
      //   case LVM_GETEDITCONTROL          : std::fprintf(stdout, "%c%X%s", '[', LVM_GETEDITCONTROL,           "]: List View > Get Edit Control"              "\r\n"); break;
      //   case LVM_GETEXTENDEDLISTVIEWSTYLE: std::fprintf(stdout, "%c%X%s", '[', LVM_GETEXTENDEDLISTVIEWSTYLE, "]: List View > Get Extended List View Style"  "\r\n"); break;
      //   case LVM_GETGROUPINFO            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETGROUPINFO,             "]: List View > Get Group Information"         "\r\n"); break;
      //   case LVM_GETGROUPMETRICS         : std::fprintf(stdout, "%c%X%s", '[', LVM_GETGROUPMETRICS,          "]: List View > Get Group Metrics"             "\r\n"); break;
      //   case LVM_GETHEADER               : std::fprintf(stdout, "%c%X%s", '[', LVM_GETHEADER,                "]: List View > Get Header"                    "\r\n"); break;
      //   case LVM_GETHOTCURSOR            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETHOTCURSOR,             "]: List View > Get Hot Cursor"                "\r\n"); break;
      //   case LVM_GETHOTITEM              : std::fprintf(stdout, "%c%X%s", '[', LVM_GETHOTITEM,               "]: List View > Get Hover Time"                "\r\n"); break;
      //   case LVM_GETHOVERTIME            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETHOVERTIME,             "]: List View > Get Image List"                "\r\n"); break;
      //   case LVM_GETIMAGELIST            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETIMAGELIST,             "]: List View > Get Image List"                "\r\n"); break;
      //   case LVM_GETINSERTMARK           : std::fprintf(stdout, "%c%X%s", '[', LVM_GETINSERTMARK,            "]: List View > Get Insert Mark"               "\r\n"); break;
      //   case LVM_GETINSERTMARKCOLOR      : std::fprintf(stdout, "%c%X%s", '[', LVM_GETINSERTMARKCOLOR,       "]: List View > Get Insert Mark Color"         "\r\n"); break;
      //   case LVM_GETINSERTMARKRECT       : std::fprintf(stdout, "%c%X%s", '[', LVM_GETINSERTMARKRECT,        "]: List View > Get Insert Mark Rectangle"     "\r\n"); break;
      //   case LVM_GETISEARCHSTRINGA       : std::fprintf(stdout, "%c%X%s", '[', LVM_GETISEARCHSTRINGA,        "]: List View > Get Incremental Search String" "\r\n"); break;
      //   case LVM_GETISEARCHSTRINGW       : std::fprintf(stdout, "%c%X%s", '[', LVM_GETISEARCHSTRINGW,        "]: List View > Get Incremental Search String" "\r\n"); break;
      //   case LVM_GETITEMA                : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMA,                 "]: List View > Get Item"                      "\r\n"); break;
      //   case LVM_GETITEMCOUNT            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMCOUNT,             "]: List View > Get Item Count"                "\r\n"); break;
      //   case LVM_GETITEMPOSITION         : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMPOSITION,          "]: List View > Get Item Position"             "\r\n"); break;
      //   case LVM_GETITEMRECT             : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMRECT,              "]: List View > Get Item Rectangle"            "\r\n"); break;
      //   case LVM_GETITEMSPACING          : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMSPACING,           "]: List View > Get Item Spacing"              "\r\n"); break;
      //   case LVM_GETITEMSTATE            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMSTATE,             "]: List View > Get Item State"                "\r\n"); break;
      //   case LVM_GETITEMTEXTA            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMTEXTA,             "]: List View > Get Item Text"                 "\r\n"); break;
      //   case LVM_GETITEMTEXTW            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMTEXTW,             "]: List View > Get Item Text"                 "\r\n"); break;
      //   case LVM_GETITEMW                : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMW,                 "]: List View > Get Item"                      "\r\n"); break;
      //   case LVM_GETNEXTITEM             : std::fprintf(stdout, "%c%X%s", '[', LVM_GETNEXTITEM,              "]: List View > Get Next Item"                 "\r\n"); break;
      //   case LVM_GETNUMBEROFWORKAREAS    : std::fprintf(stdout, "%c%X%s", '[', LVM_GETNUMBEROFWORKAREAS,     "]: List View > Get Number of Work Areas"      "\r\n"); break;
      //   case LVM_GETORIGIN               : std::fprintf(stdout, "%c%X%s", '[', LVM_GETORIGIN,                "]: List View > Get Origin"                    "\r\n"); break;
      //   case LVM_GETOUTLINECOLOR         : std::fprintf(stdout, "%c%X%s", '[', LVM_GETOUTLINECOLOR,          "]: List View > Get Outline Color"             "\r\n"); break;
      //   case LVM_GETSELECTEDCOLUMN       : std::fprintf(stdout, "%c%X%s", '[', LVM_GETSELECTEDCOLUMN,        "]: List View > Get Selected Column"           "\r\n"); break;
      //   case LVM_GETSELECTEDCOUNT        : std::fprintf(stdout, "%c%X%s", '[', LVM_GETSELECTEDCOUNT,         "]: List View > Get Selected Count"            "\r\n"); break;
      //   case LVM_GETSELECTIONMARK        : std::fprintf(stdout, "%c%X%s", '[', LVM_GETSELECTIONMARK,         "]: List View > Get Selection Mark"            "\r\n"); break;
      //   case LVM_GETSTRINGWIDTHA         : std::fprintf(stdout, "%c%X%s", '[', LVM_GETSTRINGWIDTHA,          "]: List View > Get String Width"              "\r\n"); break;
      //   case LVM_GETSTRINGWIDTHW         : std::fprintf(stdout, "%c%X%s", '[', LVM_GETSTRINGWIDTHW,          "]: List View > Get String Width"              "\r\n"); break;
      //   case LVM_GETSUBITEMRECT          : std::fprintf(stdout, "%c%X%s", '[', LVM_GETSUBITEMRECT,           "]: List View > Get Sub-Item Rectangle"        "\r\n"); break;
      //   case LVM_GETTEXTBKCOLOR          : std::fprintf(stdout, "%c%X%s", '[', LVM_GETTEXTBKCOLOR,           "]: List View > Get Text Background Color"     "\r\n"); break;
      //   case LVM_GETTEXTCOLOR            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETTEXTCOLOR,             "]: List View > Get Text Color"                "\r\n"); break;
      //   case LVM_GETTILEINFO             : std::fprintf(stdout, "%c%X%s", '[', LVM_GETTILEINFO,              "]: List View > Get Tile Information"          "\r\n"); break;
      //   case LVM_GETTILEVIEWINFO         : std::fprintf(stdout, "%c%X%s", '[', LVM_GETTILEVIEWINFO,          "]: List View > Get Tile View Information"     "\r\n"); break;
      //   case LVM_GETTOOLTIPS             : std::fprintf(stdout, "%c%X%s", '[', LVM_GETTOOLTIPS,              "]: List View > Get Tooltips"                  "\r\n"); break;
      //   case LVM_GETTOPINDEX             : std::fprintf(stdout, "%c%X%s", '[', LVM_GETTOPINDEX,              "]: List View > Get Top Index"                 "\r\n"); break;
      //   case LVM_GETUNICODEFORMAT        : std::fprintf(stdout, "%c%X%s", '[', LVM_GETUNICODEFORMAT,         "]: List View > Get Unicode Format"            "\r\n"); break;
      //   case LVM_GETVIEW                 : std::fprintf(stdout, "%c%X%s", '[', LVM_GETVIEW,                  "]: List View > Get View"                      "\r\n"); break;
      //   case LVM_GETVIEWRECT             : std::fprintf(stdout, "%c%X%s", '[', LVM_GETVIEWRECT,              "]: List View > Get View Rectangle"            "\r\n"); break;
      //   case LVM_GETWORKAREAS            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETWORKAREAS,             "]: List View > Get Work Areas"                "\r\n"); break;
      //   case LVM_HASGROUP                : std::fprintf(stdout, "%c%X%s", '[', LVM_HASGROUP,                 "]: List View > Has Group"                     "\r\n"); break;
      //   case LVM_HITTEST                 : std::fprintf(stdout, "%c%X%s", '[', LVM_HITTEST,                  "]: List View > Hit Test"                      "\r\n"); break;
      //   case LVM_INSERTCOLUMNA           : std::fprintf(stdout, "%c%X%s", '[', LVM_INSERTCOLUMNA,            "]: List View > Insert Column"                 "\r\n"); break;
      //   case LVM_INSERTCOLUMNW           : std::fprintf(stdout, "%c%X%s", '[', LVM_INSERTCOLUMNW,            "]: List View > Insert Column"                 "\r\n"); break;
      //   case LVM_INSERTGROUP             : std::fprintf(stdout, "%c%X%s", '[', LVM_INSERTGROUP,              "]: List View > Insert Group"                  "\r\n"); break;
      //   case LVM_INSERTGROUPSORTED       : std::fprintf(stdout, "%c%X%s", '[', LVM_INSERTGROUPSORTED,        "]: List View > Insert Group Sorted"           "\r\n"); break;
      //   case LVM_INSERTITEMA             : std::fprintf(stdout, "%c%X%s", '[', LVM_INSERTITEMA,              "]: List View > Insert Item"                   "\r\n"); break;
      //   case LVM_INSERTITEMW             : std::fprintf(stdout, "%c%X%s", '[', LVM_INSERTITEMW,              "]: List View > Insert Item"                   "\r\n"); break;
      //   case LVM_INSERTMARKHITTEST       : std::fprintf(stdout, "%c%X%s", '[', LVM_INSERTMARKHITTEST,        "]: List View > Insert Mark Hit Test"          "\r\n"); break;
      //   case LVM_ISGROUPVIEWENABLED      : std::fprintf(stdout, "%c%X%s", '[', LVM_ISGROUPVIEWENABLED,       "]: List View > Is Group View Enabled"         "\r\n"); break;
      //   case LVM_ISITEMVISIBLE           : std::fprintf(stdout, "%c%X%s", '[', LVM_ISITEMVISIBLE,            "]: List View > Is Item Visible"               "\r\n"); break;
      //   case LVM_MAPIDTOINDEX            : std::fprintf(stdout, "%c%X%s", '[', LVM_MAPIDTOINDEX,             "]: List View > Map Identity to Index"         "\r\n"); break;
      //   case LVM_MAPINDEXTOID            : std::fprintf(stdout, "%c%X%s", '[', LVM_MAPINDEXTOID,             "]: List View > Map Index to Identity"         "\r\n"); break;
      //   case LVM_MOVEGROUP               : std::fprintf(stdout, "%c%X%s", '[', LVM_MOVEGROUP,                "]: List View > Move Group"                    "\r\n"); break;
      //   case LVM_MOVEITEMTOGROUP         : std::fprintf(stdout, "%c%X%s", '[', LVM_MOVEITEMTOGROUP,          "]: List View > Move Item to Group"            "\r\n"); break;
      //   case LVM_REDRAWITEMS             : std::fprintf(stdout, "%c%X%s", '[', LVM_REDRAWITEMS,              "]: List View > Redraw Items"                  "\r\n"); break;
      //   case LVM_REMOVEALLGROUPS         : std::fprintf(stdout, "%c%X%s", '[', LVM_REMOVEALLGROUPS,          "]: List View > Remove all Groups"             "\r\n"); break;
      //   case LVM_REMOVEGROUP             : std::fprintf(stdout, "%c%X%s", '[', LVM_REMOVEGROUP,              "]: List View > Remove Group"                  "\r\n"); break;
      //   case LVM_SCROLL                  : std::fprintf(stdout, "%c%X%s", '[', LVM_SCROLL,                   "]: List View > Scroll"                        "\r\n"); break;
      //   case LVM_SETBKCOLOR              : std::fprintf(stdout, "%c%X%s", '[', LVM_SETBKCOLOR,               "]: List View > Set Background Color"          "\r\n"); break;
      //   case LVM_SETBKIMAGEA             : std::fprintf(stdout, "%c%X%s", '[', LVM_SETBKIMAGEA,              "]: List View > Set Background Image"          "\r\n"); break;
      //   case LVM_SETCALLBACKMASK         : std::fprintf(stdout, "%c%X%s", '[', LVM_SETCALLBACKMASK,          "]: List View > Set Callback Mask"             "\r\n"); break;
      //   case LVM_SETCOLUMNA              : std::fprintf(stdout, "%c%X%s", '[', LVM_SETCOLUMNA,               "]: List View > Set Column"                    "\r\n"); break;
      //   case LVM_SETCOLUMNORDERARRAY     : std::fprintf(stdout, "%c%X%s", '[', LVM_SETCOLUMNORDERARRAY,      "]: List View > Set Column Order Array"        "\r\n"); break;
      //   case LVM_SETCOLUMNW              : std::fprintf(stdout, "%c%X%s", '[', LVM_SETCOLUMNW,               "]: List View > Set Column"                    "\r\n"); break;
      //   case LVM_SETCOLUMNWIDTH          : std::fprintf(stdout, "%c%X%s", '[', LVM_SETCOLUMNWIDTH,           "]: List View > Set Column Width"              "\r\n"); break;
      //   case LVM_SETEXTENDEDLISTVIEWSTYLE: std::fprintf(stdout, "%c%X%s", '[', LVM_SETEXTENDEDLISTVIEWSTYLE, "]: List View > Set Extended List View Style"  "\r\n"); break;
      //   case LVM_SETGROUPINFO            : std::fprintf(stdout, "%c%X%s", '[', LVM_SETGROUPINFO,             "]: List View > Set Group Information"         "\r\n"); break;
      //   case LVM_SETGROUPMETRICS         : std::fprintf(stdout, "%c%X%s", '[', LVM_SETGROUPMETRICS,          "]: List View > Set Group Metrics"             "\r\n"); break;
      //   case LVM_SETHOTCURSOR: /* --> LVM_SETHOTITEM */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', LVM_SETHOTCURSOR, "]: {");
      //       std::fputs("List View: Set Hot Cursor" "\r\n", stdout);
      //       std::fputs("List View: Set Hot Item"   "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case LVM_SETHOTITEM: break;
      //   case LVM_SETHOVERTIME      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETHOVERTIME,       "]: List View > Set Hover Time"             "\r\n"); break;
      //   case LVM_SETICONSPACING    : std::fprintf(stdout, "%c%X%s", '[', LVM_SETICONSPACING,     "]: List View > Set Icon Spacing"           "\r\n"); break;
      //   case LVM_SETIMAGELIST      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETIMAGELIST,       "]: List View > Set Image List"             "\r\n"); break;
      //   case LVM_SETINFOTIP        : std::fprintf(stdout, "%c%X%s", '[', LVM_SETINFOTIP,         "]: List View > Set Information Tip"        "\r\n"); break;
      //   case LVM_SETINSERTMARK     : std::fprintf(stdout, "%c%X%s", '[', LVM_SETINSERTMARK,      "]: List View > Set Insert Mark"            "\r\n"); break;
      //   case LVM_SETINSERTMARKCOLOR: std::fprintf(stdout, "%c%X%s", '[', LVM_SETINSERTMARKCOLOR, "]: List View > Set Insert Mark Color"      "\r\n"); break;
      //   case LVM_SETITEMA          : std::fprintf(stdout, "%c%X%s", '[', LVM_SETITEMA,           "]: List View > Set Item"                   "\r\n"); break;
      //   case LVM_SETITEMCOUNT      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETITEMCOUNT,       "]: List View > Set Item Count"             "\r\n"); break;
      //   case LVM_SETITEMPOSITION   : std::fprintf(stdout, "%c%X%s", '[', LVM_SETITEMPOSITION,    "]: List View > Set Item Position"          "\r\n"); break;
      //   case LVM_SETITEMPOSITION32 : std::fprintf(stdout, "%c%X%s", '[', LVM_SETITEMPOSITION32,  "]: List View > Set Item Position (32-Bit)" "\r\n"); break;
      //   case LVM_SETITEMSTATE      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETITEMSTATE,       "]: List View > Set Item State"             "\r\n"); break;
      //   case LVM_SETITEMTEXTA      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETITEMTEXTA,       "]: List View > Set Item Text"              "\r\n"); break;
      //   case LVM_SETITEMTEXTW      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETITEMTEXTW,       "]: List View > Set Item Text"              "\r\n"); break;
      //   case LVM_SETITEMW          : std::fprintf(stdout, "%c%X%s", '[', LVM_SETITEMW,           "]: List View > Set Item"                   "\r\n"); break;
      //   case LVM_SETOUTLINECOLOR   : std::fprintf(stdout, "%c%X%s", '[', LVM_SETOUTLINECOLOR,    "]: List View > Set Outline Color"          "\r\n"); break;
      //   case LVM_SETSELECTEDCOLUMN : std::fprintf(stdout, "%c%X%s", '[', LVM_SETSELECTEDCOLUMN,  "]: List View > Set Selected Column"        "\r\n"); break;
      //   case LVM_SETSELECTIONMARK  : std::fprintf(stdout, "%c%X%s", '[', LVM_SETSELECTIONMARK,   "]: List View > Set Selection Mark"         "\r\n"); break;
      //   case LVM_SETTEXTBKCOLOR    : std::fprintf(stdout, "%c%X%s", '[', LVM_SETTEXTBKCOLOR,     "]: List View > Set Text Background Color"  "\r\n"); break;
      //   case LVM_SETTEXTCOLOR      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETTEXTCOLOR,       "]: List View > Set Text Color"             "\r\n"); break;
      //   case LVM_SETTILEINFO       : std::fprintf(stdout, "%c%X%s", '[', LVM_SETTILEINFO,        "]: List View > Set Tile Information"       "\r\n"); break;
      //   case LVM_SETTILEVIEWINFO   : std::fprintf(stdout, "%c%X%s", '[', LVM_SETTILEVIEWINFO,    "]: List View > Set Tile View Information"  "\r\n"); break;
      //   case LVM_SETTILEWIDTH      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETTILEWIDTH,       "]: List View > Set Tile Width"             "\r\n"); break;
      //   case LVM_SETTOOLTIPS       : std::fprintf(stdout, "%c%X%s", '[', LVM_SETTOOLTIPS,        "]: List View > Set Tooltips"               "\r\n"); break;
      //   case LVM_SETUNICODEFORMAT  : std::fprintf(stdout, "%c%X%s", '[', LVM_SETUNICODEFORMAT,   "]: List View > Set Unicode Format"         "\r\n"); break;
      //   case LVM_SETVIEW           : std::fprintf(stdout, "%c%X%s", '[', LVM_SETVIEW,            "]: List View > Set View"                   "\r\n"); break;
      //   case LVM_SETWORKAREAS      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETWORKAREAS,       "]: List View > Set WorkaAreas"             "\r\n"); break;
      //   case LVM_SORTGROUPS        : std::fprintf(stdout, "%c%X%s", '[', LVM_SORTGROUPS,         "]: List View > Sort Groups"                "\r\n"); break;
      //   case LVM_SORTITEMS         : std::fprintf(stdout, "%c%X%s", '[', LVM_SORTITEMS,          "]: List View > Sort Items"                 "\r\n"); break;
      //   case LVM_SUBITEMHITTEST    : std::fprintf(stdout, "%c%X%s", '[', LVM_SUBITEMHITTEST,     "]: List View > Sub-Item Hit Test"          "\r\n"); break;
      //   case LVM_UPDATE            : std::fprintf(stdout, "%c%X%s", '[', LVM_UPDATE,             "]: List View > Update"                     "\r\n"); break;

      //   /* [Multimedia MCI Window] */
      //   case MCIWNDM_CAN_CONFIG: std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_CAN_CONFIG, "]: Multimedia (MCI) Window > Can Configure" "\r\n"); break;
      //   case MCIWNDM_CAN_EJECT : std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_CAN_EJECT,  "]: Multimedia (MCI) Window > Can Eject"     "\r\n"); break;
      //   case MCIWNDM_CAN_PLAY  : std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_CAN_PLAY,   "]: Multimedia (MCI) Window > Can Play"      "\r\n"); break;
      //   case MCIWNDM_CAN_RECORD: std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_CAN_RECORD, "]: Multimedia (MCI) Window > Can Record"    "\r\n"); break;
      //   case MCIWNDM_CAN_SAVE  : std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_CAN_SAVE,   "]: Multimedia (MCI) Window > Can Save"      "\r\n"); break;
      //   case MCIWNDM_CAN_WINDOW: std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_CAN_WINDOW, "]: Multimedia (MCI) Window > Can Window"    "\r\n"); break;
      //   // case MCIWNDM_GETDEVICEA: break;
      //   // case MCIWNDM_GETDEVICEW: break;
      //   case MCIWNDM_GETERRORA: /* --> PSM_SETHEADERSUBTITLEW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', MCIWNDM_GETERRORA, "]: {");
      //       std::fputs("Multimedia (MCI) Window: Get Error"           "\r\n", stdout);
      //       std::fputs("Prop Sheet             : Set Header Subtitle" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case MCIWNDM_GETERRORW       : break;
      //   // case MCIWNDM_GETFILENAMEA    : break;
      //   // case MCIWNDM_GETFILENAMEW    : break;
      //   // case MCIWNDM_GETINACTIVETIMER: break;
      //   // case MCIWNDM_GETPALETTE      : break;
      //   // case MCIWNDM_GETTIMEFORMATA  : break;
      //   // case MCIWNDM_GETTIMEFORMATW  : break;
      //   case MCIWNDM_GETZOOM: /* --> PSM_UNCHANGED | UDM_SETBASE */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', MCIWNDM_GETERRORA, "]: {");
      //       std::fputs("Multimedia (MCI) Window: Get Zoom"  "\r\n", stdout);
      //       std::fputs("Prop Sheet             : Unchanged" "\r\n", stdout);
      //       std::fputs("Up-Down Control        : Set Base"  "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case MCIWNDM_GET_DEST  : std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_GET_DEST,   "]: Multimedia (MCI) Window > Get Destination" "\r\n"); break;
      //   case MCIWNDM_GET_SOURCE: std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_GET_SOURCE, "]: Multimedia (MCI) Window > Get Source"      "\r\n"); break;
      //   // case MCIWNDM_NOTIFYERROR: break;
      //   // case MCIWNDM_NOTIFYMEDIA: break;
      //   // case MCIWNDM_NOTIFYMODE: break;
      //   // case MCIWNDM_PALETTEKICK: break;
      //   // case MCIWNDM_PLAYTO: break;
      //   case MCIWNDM_PUT_DEST  : std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_PUT_DEST,   "]: Multimedia (MCI) Window > Put Destination" "\r\n"); break;
      //   case MCIWNDM_PUT_SOURCE: std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_PUT_SOURCE, "]: Multimedia (MCI) Window > Put Source"      "\r\n"); break;
      //   case MCIWNDM_REALIZE: /* --> PSM_GETCURRENTPAGEHWND */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', MCIWNDM_REALIZE, "]: {");
      //       std::fputs("Multimedia (MCI) Window: Realize"                        "\r\n", stdout);
      //       std::fputs("Prop Sheet             : Get Current Page Window Handle" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case MCIWNDM_SETINACTIVETIMER: /* --> PSM_PAGETOINDEX */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', MCIWNDM_SETINACTIVETIMER, "]: {");
      //       std::fputs("Multimedia (MCI) Window: Set Inactive Timer" "\r\n", stdout);
      //       std::fputs("Prop Sheet             : Page to Index"      "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case MCIWNDM_SETPALETTE: break;
      //   case MCIWNDM_SETTIMEFORMATA: /* --> PSM_INSERTPAGE */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', MCIWNDM_SETTIMEFORMATA, "]: {");
      //       std::fputs("Multimedia (MCI) Window: Set Time Format" "\r\n", stdout);
      //       std::fputs("Prop Sheet             : Insert Page"     "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case MCIWNDM_SETTIMEFORMATW: std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_SETTIMEFORMATW, "]: Multimedia (MCI) Window > Set Time Format" "\r\n"); break;
      //   // case MCIWNDM_VALIDATEMEDIA: break;

      //   /* [...] */
      //   case MSG_FTS_JUMP_QWORD: /* --> RB_SHOWBAND | TB_GETTOOLTIPS */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', MSG_FTS_JUMP_QWORD, "]: {");
      //       std::fputs("... Jump ..."          "\r\n", stdout);
      //       std::fputs("Rebar  : Show Band"    "\r\n", stdout);
      //       std::fputs("Toolbar: Get Tooltips" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case MSG_FTS_JUMP_VA: /* --> TBM_GETBUDDY | TB_AUTOSIZE | TTM_SETTITLEW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', MSG_FTS_JUMP_VA, "]: {");
      //       std::fputs("... Jump ..."        "\r\n", stdout);
      //       std::fputs("Toolbar : Auto Size" "\r\n", stdout);
      //       std::fputs("Tooltip : Set Title" "\r\n", stdout);
      //       std::fputs("Trackbar: Get Buddy" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case MSG_FTS_WHERE_IS_IT: /* --> RB_SETPALETTE | TB_SETPARENT */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', MSG_FTS_WHERE_IS_IT, "]: {");
      //       std::fputs("Rebar  : Set Palette" "\r\n", stdout);
      //       std::fputs("Toolbar: Set Parent"  "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case MSG_GET_DEFFONT: /* --> TB_GETBUTTONTEXTA */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', MSG_GET_DEFFONT, "]: {");
      //       std::fputs("Get Default Font"         "\r\n", stdout);
      //       std::fputs("Toolbar: Get Button Text" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case MSG_REINDEX_REQUEST: /* --> TB_SETTOOLTIPS */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', MSG_REINDEX_REQUEST, "]: {");
      //       std::fputs("Re-Index Request"      "\r\n", stdout);
      //       std::fputs("Toolbar: Set Tooltips" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;

      //   /* [Object Linking & Embedding] */
      //   // case NIN_SELECT: break;
      //   case OCM_CHARTOITEM       : std::fprintf(stdout, "%c%X%s", '[', OCM_CHARTOITEM,        "]: Object Linking & Embedding Control > Character To Item"         "\r\n"); break;
      //   case OCM_COMMAND          : std::fprintf(stdout, "%c%X%s", '[', OCM_COMMAND,           "]: Object Linking & Embedding Control > Command"                   "\r\n"); break;
      //   case OCM_COMPAREITEM      : std::fprintf(stdout, "%c%X%s", '[', OCM_COMPAREITEM,       "]: Object Linking & Embedding Control > Compare Item"              "\r\n"); break;
      //   case OCM_CTLCOLOR         : std::fprintf(stdout, "%c%X%s", '[', OCM_CTLCOLOR,          "]: Object Linking & Embedding Control > Control Color"             "\r\n"); break;
      //   case OCM_CTLCOLORBTN      : std::fprintf(stdout, "%c%X%s", '[', OCM_CTLCOLORBTN,       "]: Object Linking & Embedding Control > Control Color Button"      "\r\n"); break;
      //   case OCM_CTLCOLORDLG      : std::fprintf(stdout, "%c%X%s", '[', OCM_CTLCOLORDLG,       "]: Object Linking & Embedding Control > Control Color Dialog"      "\r\n"); break;
      //   case OCM_CTLCOLOREDIT     : std::fprintf(stdout, "%c%X%s", '[', OCM_CTLCOLOREDIT,      "]: Object Linking & Embedding Control > Control Color Edit"        "\r\n"); break;
      //   case OCM_CTLCOLORLISTBOX  : std::fprintf(stdout, "%c%X%s", '[', OCM_CTLCOLORLISTBOX,   "]: Object Linking & Embedding Control > Control Color List Box"    "\r\n"); break;
      //   case OCM_CTLCOLORMSGBOX   : std::fprintf(stdout, "%c%X%s", '[', OCM_CTLCOLORMSGBOX,    "]: Object Linking & Embedding Control > Control Color Message Box" "\r\n"); break;
      //   case OCM_CTLCOLORSCROLLBAR: std::fprintf(stdout, "%c%X%s", '[', OCM_CTLCOLORSCROLLBAR, "]: Object Linking & Embedding Control > Control Color Scrollbar"   "\r\n"); break;
      //   case OCM_CTLCOLORSTATIC   : std::fprintf(stdout, "%c%X%s", '[', OCM_CTLCOLORSTATIC,    "]: Object Linking & Embedding Control > Control Color Static"      "\r\n"); break;
      //   case OCM_DELETEITEM       : std::fprintf(stdout, "%c%X%s", '[', OCM_DELETEITEM,        "]: Object Linking & Embedding Control > Delete Item"               "\r\n"); break;
      //   case OCM_DRAWITEM         : std::fprintf(stdout, "%c%X%s", '[', OCM_DRAWITEM,          "]: Object Linking & Embedding Control > Draw Item"                 "\r\n"); break;
      //   case OCM_HSCROLL          : std::fprintf(stdout, "%c%X%s", '[', OCM_HSCROLL,           "]: Object Linking & Embedding Control > Horizontal Scroll"         "\r\n"); break;
      //   case OCM_MEASUREITEM      : std::fprintf(stdout, "%c%X%s", '[', OCM_MEASUREITEM,       "]: Object Linking & Embedding Control > Measure Item"              "\r\n"); break;
      //   case OCM_NOTIFY           : std::fprintf(stdout, "%c%X%s", '[', OCM_NOTIFY,            "]: Object Linking & Embedding Control > Notify"                    "\r\n"); break;
      //   case OCM_PARENTNOTIFY     : std::fprintf(stdout, "%c%X%s", '[', OCM_PARENTNOTIFY,      "]: Object Linking & Embedding Control > Parent Notify"             "\r\n"); break;
      //   case OCM_VKEYTOITEM       : std::fprintf(stdout, "%c%X%s", '[', OCM_VKEYTOITEM,        "]: Object Linking & Embedding Control > Virtual Key to Item"       "\r\n"); break;
      //   case OCM_VSCROLL          : std::fprintf(stdout, "%c%X%s", '[', OCM_VSCROLL,           "]: Object Linking & Embedding Control > Vertical Scroll"           "\r\n"); break;
      //   case OCM__BASE            : std::fprintf(stdout, "%c%X%s", '[', OCM__BASE,             "]: Object Linking & Embedding Control > Base"                      "\r\n"); break;

      //   /* [Prop Sheet] */
      //   // case PBM_DELTAPOS   : break;
      //   // case PBM_GETPOS     : break;
      //   // case PBM_GETRANGE   : break;
      //   // case PBM_SETBARCOLOR: break;
      //   // case PBM_SETPOS     : break;
      //   // case PBM_SETRANGE   : break;
      //   // case PBM_SETRANGE32 : break;
      //   // case PBM_SETSTEP    : break;
      //   // case PBM_STEPIT     : break;
      //   // case PSM_ADDPAGE    : break;
      //   case PSM_APPLY: /* --> UDM_GETBASE */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', PSM_APPLY, "]: {");
      //       std::fputs("Prop Sheet     : Apply"    "\r\n", stdout);
      //       std::fputs("Up-Down Control: Get Base" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case PSM_CANCELTOCLOSE: break;
      //   // case PSM_CHANGED: break;
      //   // case PSM_GETCURRENTPAGEHWND: break;
      //   // case PSM_GETRESULT: break;
      //   case PSM_GETTABCONTROL: std::fprintf(stdout, "%c%X%s", '[', PSM_GETTABCONTROL, "]: Prop Sheet > Get Tab Control"        "\r\n"); break;
      //   case PSM_HWNDTOINDEX  : std::fprintf(stdout, "%c%X%s", '[', PSM_HWNDTOINDEX,   "]: Prop Sheet > Window Handle to Index" "\r\n"); break;
      //   // case PSM_IDTOINDEX: break;
      //   case PSM_INDEXTOHWND: std::fprintf(stdout, "%c%X%s", '[', PSM_INDEXTOHWND, "]: Prop Sheet > Index To Window Handle" "\r\n"); break;
      //   // case PSM_INDEXTOID: break;
      //   case PSM_INDEXTOPAGE: std::fprintf(stdout, "%c%X%s", '[', PSM_INDEXTOPAGE, "]: Prop Sheet > Index To Page" "\r\n"); break;
      //   // case PSM_INSERTPAGE: break;
      //   case PSM_ISDIALOGMESSAGE: std::fprintf(stdout, "%c%X%s", '[', PSM_ISDIALOGMESSAGE, "]: Prop Sheet > Is Dialog Message" "\r\n"); break;
      //   // case PSM_PAGETOINDEX: break;
      //   case PSM_PRESSBUTTON: /* --> UDM_SETPOS32 | WM_CAP_DRIVER_GET_VERSIONW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', PSM_PRESSBUTTON, "]: {");
      //       std::fputs("Prop Sheet     : Press Buttons" "\r\n", stdout);
      //       std::fputs("Up-Down Control: Set Position" "\r\n", stdout);
      //       std::fputs("Windows Capture: Driver Get Version" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case PSM_QUERYSIBLINGS  : break;
      //   // case PSM_REBOOTSYSTEM   : break;
      //   // case PSM_RECALCPAGESIZES: break;
      //   // case PSM_REMOVEPAGE     : break;
      //   // case PSM_RESTARTWINDOWS : break;
      //   // case PSM_SETCURSEL      : break;
      //   case PSM_SETCURSELID: /* --> UDM_GETPOS32 */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', PSM_SETCURSELID, "]: {");
      //       std::fputs("Prop Sheet     : Set Current Selection Identity" "\r\n", stdout);
      //       std::fputs("Up-Down Control: Get Position" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case PSM_SETFINISHTEXTA: std::fprintf(stdout, "%c%X%s", '[', PSM_SETFINISHTEXTA, "]: Prop Sheet > Set Finish Text" "\r\n"); break;
      //   // case PSM_SETFINISHTEXTW    : break;
      //   // case PSM_SETHEADERSUBTITLEA: break;
      //   // case PSM_SETHEADERSUBTITLEW: break;
      //   // case PSM_SETHEADERTITLEA   : break;
      //   // case PSM_SETHEADERTITLEW   : break;
      //   case PSM_SETTITLEA: /* --> UDM_SETRANGE32 */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', PSM_SETTITLEA, "]: {");
      //       std::fputs("Prop Sheet     : Set Title" "\r\n", stdout);
      //       std::fputs("Up-Down Control: Set Range" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case PSM_SETTITLEW: break;
      //   case PSM_SETWIZBUTTONS: /* --> UDM_GETRANGE32 | WM_CAP_DRIVER_GET_NAMEW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', PSM_SETWIZBUTTONS, "]: {");
      //       std::fputs("Prop Sheet     : Set Wizard Buttons" "\r\n", stdout);
      //       std::fputs("Up-Down Control: Get Range"          "\r\n", stdout);
      //       std::fputs("Windows Capture: Driver Get Name"    "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case PSM_UNCHANGED: break;

      //   /* [Rebar] */
      //   case RB_BEGINDRAG: /* --> TBM_GETLINESIZE */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_BEGINDRAG, "]: {");
      //       std::fputs("Rebar   : Begin Drag"    "\r\n", stdout);
      //       std::fputs("Trackbar: Get Line Size" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case RB_DELETEBAND: break;
      //   case RB_DRAGMOVE: /* --> TBM_GETCHANNELRECT | TB_SAVERESTOREA | TTM_SETMARGIN */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_DRAGMOVE, "]: {");
      //       std::fputs("Rebar   : Drag Move"             "\r\n", stdout);
      //       std::fputs("Toolbar : Save Restore"          "\r\n", stdout);
      //       std::fputs("Tooltip : Set Margin"            "\r\n", stdout);
      //       std::fputs("Trackbar: Get Channel Rectangle" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case RB_ENDDRAG: /* --> TBM_GETTHUMBRECT | TB_COMMANDTOINDEX | TTM_GETMAXTIPWIDTH */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_ENDDRAG, "]: {");
      //       std::fputs("Rebar   : End Drag"              "\r\n", stdout);
      //       std::fputs("Toolbar : Command To Index"      "\r\n", stdout);
      //       std::fputs("Tooltip : Get Maximum Tip Width" "\r\n", stdout);
      //       std::fputs("Trackbar: Get Thumb Rectangle"   "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case RB_GETBANDBORDERS: std::fprintf(stdout, "%c%X%s", '[', RB_GETBANDBORDERS, "]: Rebar > Get Band Borders" "\r\n"); break;
      //   // case RB_GETBANDCOUNT: break;
      //   case RB_GETBANDINFOA: /* --> TBM_SETTOOLTIPS | TB_GETITEMRECT | TTM_UPDATE */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_GETBANDINFOA, "]: {");
      //       std::fputs("Rebar   : Get Band Information" "\r\n", stdout);
      //       std::fputs("Toolbar : Get Item Rectangle"   "\r\n", stdout);
      //       std::fputs("Tooltip : Update"               "\r\n", stdout);
      //       std::fputs("Trackbar: Set Tooltips"         "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case RB_GETBANDINFOW: /* --> TBM_GETTHUMBLENGTH | TB_ADDSTRINGA | TTM_POP */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_GETBANDINFOW, "]: {");
      //       std::fputs("Rebar   : Get Band Information" "\r\n", stdout);
      //       std::fputs("Toolbar : Add String"           "\r\n", stdout);
      //       std::fputs("Tooltip : Pop"                  "\r\n", stdout);
      //       std::fputs("Trackbar: Get Thumb Length"     "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case RB_GETBARHEIGHT: /* --> TBM_SETTHUMBLENGTH | TB_CUSTOMIZE | TTM_GETMARGIN */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_GETBARHEIGHT, "]: {");
      //       std::fputs("Rebar   : Get Bar Height"   "\r\n", stdout);
      //       std::fputs("Toolbar : Customize"        "\r\n", stdout);
      //       std::fputs("Tooltip : Get Margin"       "\r\n", stdout);
      //       std::fputs("Trackbar: Set Thumb Length" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case RB_GETBARINFO: break;
      //   case RB_GETBKCOLOR: /* --> SB_GETTIPTEXTW | TBM_SETTICFREQ | TB_ADDBUTTONSA | TTM_SETTIPTEXTCOLOR */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_GETBKCOLOR, "]: {");
      //       std::fputs("Rebar     : Get Background Color" "\r\n", stdout);
      //       std::fputs("Status Bar: Get Tip Text"         "\r\n", stdout);
      //       std::fputs("Toolbar   : Add Buttons"          "\r\n", stdout);
      //       std::fputs("Tooltip   : Set Tip Text Color"   "\r\n", stdout);
      //       std::fputs("Trackbar  : Set Tick Frequency"   "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case RB_GETPALETTE: std::fprintf(stdout, "%c%X%s", '[', RB_GETPALETTE, "]: Rebar > Get Palette" "\r\n"); break;
      //   // case RB_GETRECT: break;
      //   // case RB_GETROWCOUNT: break;
      //   case RB_GETROWHEIGHT: /* --> SB_ISSIMPLE | TBM_GETPTICS | TB_ISBUTTONHIGHLIGHTED | TTM_ENUMTOOLSA */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_GETROWHEIGHT, "]: {");
      //       std::fputs("Rebar     : Get Row Height"          "\r\n", stdout);
      //       std::fputs("Status Bar: Is Simple"               "\r\n", stdout);
      //       std::fputs("Toolbar   : Is Button Highlighted"   "\r\n", stdout);
      //       std::fputs("Tooltip   : Enumerate Tools"         "\r\n", stdout);
      //       std::fputs("Trackbar  : Get Position (of) Ticks" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case RB_GETTEXTCOLOR: /* --> TBM_GETPAGESIZE | TB_DELETEBUTTON | TTM_GETTIPBKCOLOR */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_GETTEXTCOLOR, "]: {");
      //       std::fputs("Rebar   : Get Text Color"           "\r\n", stdout);
      //       std::fputs("Toolbar : Delete Button"            "\r\n", stdout);
      //       std::fputs("Tooltip : Get Tip Background Color" "\r\n", stdout);
      //       std::fputs("Trackbar: Get Page Size"            "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case RB_GETTOOLTIPS: /* --> SB_SETTIPTEXTW | TBM_GETSELSTART | TB_SETSTATE | TTM_TRACKACTIVATE */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_GETTOOLTIPS, "]: {");
      //       std::fputs("Rebar     : Get Tooltips"        "\r\n", stdout);
      //       std::fputs("Status Bar: Set Tip Text"        "\r\n", stdout);
      //       std::fputs("Toolbar   : Set State"           "\r\n", stdout);
      //       std::fputs("Tooltip   : Track Activate"      "\r\n", stdout);
      //       std::fputs("Trackbar  : Get Selection Start" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case RB_HITTEST: break;
      //   case RB_IDTOINDEX: /* --> SB_SETTIPTEXTA | TBM_GETNUMTICS | TTM_WINDOWFROMPOINT */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_IDTOINDEX, "]: {");
      //       std::fputs("Rebar     : Identity to Index"     "\r\n", stdout);
      //       std::fputs("Status Bar: Set Tip Text"          "\r\n", stdout);
      //       std::fputs("Tooltip   : Window From Point"     "\r\n", stdout);
      //       std::fputs("Trackbar  : Get Number (of) Ticks" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case RB_INSERTBANDA: break;
      //   // case RB_INSERTBANDW: break;
      //   case RB_MAXIMIZEBAND: /* --> TBM_SETTIPSIDE | TB_SETBUTTONSIZE | TTM_ADJUSTRECT */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_MAXIMIZEBAND, "]: {");
      //       std::fputs("Rebar   : Maximize Band"    "\r\n", stdout);
      //       std::fputs("Toolbar : Set Button Size"  "\r\n", stdout);
      //       std::fputs("Tooltip : Adjust Rectangle" "\r\n", stdout);
      //       std::fputs("Trackbar: Set Tip Side"     "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case RB_MINIMIZEBAND: /* --> TBM_GETTOOLTIPS | TB_BUTTONSTRUCTSIZE | TTM_GETBUBBLESIZE */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_MINIMIZEBAND, "]: {");
      //       std::fputs("Rebar   : Minimize Band"         "\r\n", stdout);
      //       std::fputs("Toolbar : Button Structure Size" "\r\n", stdout);
      //       std::fputs("Tooltip : Get Bubble Size"       "\r\n", stdout);
      //       std::fputs("Trackbar: Get Tooltips"          "\r\n", stdout);
      //   ::print('}');
      //   } break;
      //   case RB_MOVEBAND: /* --> TB_SETROWS */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_MOVEBAND, "]: {");
      //       std::fputs("Rebar  : Move Band" "\r\n", stdout);
      //       std::fputs("Toolbar: Set Rows"  "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case RB_PUSHCHEVRON: /* --> TB_CHANGEBITMAP */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_PUSHCHEVRON, "]: {");
      //       std::fputs("Rebar  : Push Chevron"  "\r\n", stdout);
      //       std::fputs("Toolbar: Change Bitmap" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case RB_SETBANDINFOA: break;
      //   // case RB_SETBANDINFOW: break;
      //   // case RB_SETBARINFO  : break;
      //   case RB_SETBKCOLOR: /* --> TBM_CLEARSEL | TB_ADDBITMAP | TTM_SETTIPBKCOLOR */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_SETBKCOLOR, "]: {");
      //       std::fputs("Rebar   : Set Background Color"     "\r\n", stdout);
      //       std::fputs("Toolbar : Add Bitmap"               "\r\n", stdout);
      //       std::fputs("Tooltip : Set Tip Background Color" "\r\n", stdout);
      //       std::fputs("Trackbar: Clear Selection"          "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case RB_SETPALETTE: break;
      //   // case RB_SETPARENT : break;
      //   case RB_SETTEXTCOLOR: /* --> TBM_SETPAGESIZE | TB_INSERTBUTTONA | TTM_GETDELAYTIME */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_SETTEXTCOLOR, "]: {");
      //       std::fputs("Rebar   : Set Text Color" "\r\n", stdout);
      //       std::fputs("Toolbar : Insert Button"  "\r\n", stdout);
      //       std::fputs("Tooltip : Get Delay Time" "\r\n", stdout);
      //       std::fputs("Trackbar: Set Page Size"  "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case RB_SETTOOLTIPS: /* --> SB_GETTIPTEXTA | TBM_GETSELEND | TB_GETSTATE | TTM_TRACKPOSITION */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_SETTOOLTIPS, "]: {");
      //       std::fputs("Rebar     : Set Tooltips"      "\r\n", stdout);
      //       std::fputs("Status Bar: Get Tip Text"      "\r\n", stdout);
      //       std::fputs("Toolbar   : Get State"         "\r\n", stdout);
      //       std::fputs("Tooltip   : Track Position"    "\r\n", stdout);
      //       std::fputs("Trackbar  : Get Selection End" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case RB_SHOWBAND: break;
      //   case RB_SIZETORECT: /* --> TBM_SETLINESIZE | TB_GETBUTTON | TTM_GETTIPTEXTCOLOR */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', RB_SIZETORECT, "]: {");
      //       std::fputs("Rebar   : Size to Rectangle"  "\r\n", stdout);
      //       std::fputs("Toolbar : Get Button"         "\r\n", stdout);
      //       std::fputs("Tooltip : Get Tip Text Color" "\r\n", stdout);
      //       std::fputs("Trackbar: Set Line Size"      "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;

      //   /* [Scrollbar] */
      //   case SBM_ENABLE_ARROWS: std::fprintf(stdout, "%c%X%s", '[', SBM_ENABLE_ARROWS, "]: Scrollbar > Enable Arrows" "\r\n"); break;
      //   case SBM_GETPOS       : std::fprintf(stdout, "%c%X%s", '[', SBM_GETPOS,        "]: Scrollbar > Get Position"  "\r\n"); break;
      //   case SBM_GETRANGE     : std::fprintf(stdout, "%c%X%s", '[', SBM_GETRANGE,      "]: Scrollbar > Get Range"     "\r\n"); break;
      //   // case SBM_GETSCROLLBARINFO: break;
      //   case SBM_GETSCROLLINFO : std::fprintf(stdout, "%c%X%s", '[', SBM_GETSCROLLINFO,  "]: Scrollbar > Get Scroll Information" "\r\n"); break;
      //   case SBM_SETPOS        : std::fprintf(stdout, "%c%X%s", '[', SBM_SETPOS,         "]: Scrollbar > Set Position"           "\r\n"); break;
      //   case SBM_SETRANGE      : std::fprintf(stdout, "%c%X%s", '[', SBM_SETRANGE,       "]: Scrollbar > Set Range"              "\r\n"); break;
      //   case SBM_SETRANGEREDRAW: std::fprintf(stdout, "%c%X%s", '[', SBM_SETRANGEREDRAW, "]: Scrollbar > Set Range Redraw"       "\r\n"); break;
      //   case SBM_SETSCROLLINFO : std::fprintf(stdout, "%c%X%s", '[', SBM_SETSCROLLINFO,  "]: Scrollbar > Set Scroll Information" "\r\n"); break;

      //   /* [Status Bar] */
      //   // case SB_GETBORDERS    : break;
      //   // case SB_GETICON       : break;
      //   // case SB_GETPARTS      : break;
      //   // case SB_GETRECT       : break;
      //   // case SB_GETTEXTA      : break;
      //   // case SB_GETTEXTLENGTHA: break;
      //   // case SB_GETTEXTLENGTHW: break;
      //   // case SB_GETTEXTW      : break;
      //   // case SB_GETTIPTEXTA   : break;
      //   // case SB_GETTIPTEXTW   : break;
      //   // case SB_ISSIMPLE      : break;
      //   case SB_SETICON: /* --> TBM_GETTICPOS | TTM_GETCURRENTTOOLA */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', SB_SETICON, "]: {");
      //       std::fputs("Status Bar: Set Icon"                 "\r\n", stdout);
      //       std::fputs("Trackbar  : Get Tick (Mark) Position" "\r\n", stdout);
      //       std::fputs("Tooltip   : Get Current Tool"         "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case SB_SETMINHEIGHT: break;
      //   // case SB_SETPARTS    : break;
      //   // case SB_SETTEXTA    : break;
      //   // case SB_SETTEXTW    : break;
      //   // case SB_SETTIPTEXTA : break;
      //   // case SB_SETTIPTEXTW : break;
      //   // case SB_SIMPLE      : break;

      //   /* [Storage Management] */
      //   case SM_GETCURFOCUSA: /* --> UM_GETGROUPSELA */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', SM_GETCURFOCUSA, "]: {");
      //       std::fputs("Storage Management: Get Current Focus"   "\r\n", stdout);
      //       std::fputs("User Manager      : Get Group Selection" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case SM_GETCURFOCUSW: /* --> UM_GETGROUPSELW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', SM_GETCURFOCUSW, "]: {");
      //       std::fputs("Storage Management: Get Current Focus"   "\r\n", stdout);
      //       std::fputs("User Manager      : Get Group Selection" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case SM_GETOPTIONS: /* --> UM_GETCURFOCUSA */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', SM_GETOPTIONS, "]: {");
      //       std::fputs("Storage Management: Get Options"       "\r\n", stdout);
      //       std::fputs("User Manager      : Get Current Focus" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case SM_GETSELCOUNT: /* --> UM_GETSELCOUNT | WM_CPL_LAUNCH */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', SM_GETSELCOUNT, "]: {");
      //       std::fputs("Storage Management: Get Selection Count"    "\r\n", stdout);
      //       std::fputs("User Manager      : Get Selection Count"    "\r\n", stdout);
      //       std::fputs("Windows           : Control Panel Launched" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case SM_GETSERVERSELA: /* --> UM_GETUSERSELA | WM_CPL_LAUNCHED */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', SM_GETSERVERSELA, "]: {");
      //       std::fputs("Storage Management: Get Server Selection"   "\r\n", stdout);
      //       std::fputs("User Manager      : Get User Selection"     "\r\n", stdout);
      //       std::fputs("Windows           : Control Panel Launched" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case SM_GETSERVERSELW: /* --> UM_GETUSERSELW */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', SM_GETSERVERSELW, "]: {");
      //       std::fputs("Storage Management: Get Server Selection" "\r\n", stdout);
      //       std::fputs("User Manager      : Get User Selection"   "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;

      //   /* [Telephony API] */
      //   case TAPI_REPLY: std::fprintf(stdout, "%c%X%s", '[', TAPI_REPLY, "]: Telephony API > Reply" "\r\n"); break;

      //   /* [Trackbar] */
      //   // case TBM_CLEARSEL      : break;
      //   // case TBM_CLEARTICS     : break;
      //   // case TBM_GETBUDDY      : break;
      //   // case TBM_GETCHANNELRECT: break;
      //   // case TBM_GETLINESIZE   : break;
      //   // case TBM_GETNUMTICS    : break;
      //   // case TBM_GETPAGESIZE   : break;
      //   // case TBM_GETPOS        : break;
      //   // case TBM_GETPTICS      : break;
      //   // case TBM_GETRANGEMAX   : break;
      //   // case TBM_GETRANGEMIN   : break;
      //   // case TBM_GETSELEND     : break;
      //   // case TBM_GETSELSTART   : break;
      //   // case TBM_GETTHUMBLENGTH: break;
      //   // case TBM_GETTHUMBRECT  : break;
      //   // case TBM_GETTIC        : break;
      //   // case TBM_GETTICPOS     : break;
      //   // case TBM_GETTOOLTIPS   : break;
      //   case TBM_SETBUDDY: /* --> TB_SETBITMAPSIZE | TTM_SETTITLEA */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', TBM_SETBUDDY, "]: {");
      //       std::fputs("Toolbar : Set Bitmap Size"    "\r\n", stdout);
      //       std::fputs("Tooltip : Set Title"          "\r\n", stdout);
      //       std::fputs("Trackbar: Set Buddy (Window)" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   // case TBM_SETLINESIZE   : break;
      //   // case TBM_SETPAGESIZE   : break;
      //   // case TBM_SETPOS        : break;
      //   // case TBM_SETRANGE      : break;
      //   // case TBM_SETRANGEMAX   : break;
      //   // case TBM_SETRANGEMIN   : break;
      //   // case TBM_SETSEL        : break;
      //   // case TBM_SETSELEND     : break;
      //   // case TBM_SETSELSTART   : break;
      //   // case TBM_SETTHUMBLENGTH: break;
      //   // case TBM_SETTIC        : break;
      //   // case TBM_SETTICFREQ    : break;
      //   // case TBM_SETTIPSIDE    : break;
      //   // case TBM_SETTOOLTIPS   : break;

      //   /* [Toolbar] */
      //   // case TB_ADDBITMAP         : break;
      //   // case TB_ADDBUTTONSA       : break;
      //   // case TB_ADDBUTTONSW       : break;
      //   // case TB_ADDSTRINGA        : break;
      //   // case TB_ADDSTRINGW        : break;
      //   // case TB_AUTOSIZE          : break;
      //   // case TB_BUTTONCOUNT       : break;
      //   // case TB_BUTTONSTRUCTSIZE  : break;
      //   // case TB_CHANGEBITMAP      : break;
      //   // case TB_CHECKBUTTON       : break;
      //   // case TB_COMMANDTOINDEX    : break;
      //   // case TB_CUSTOMIZE         : break;
      //   // case TB_DELETEBUTTON      : break;
      //   // case TB_ENABLEBUTTON      : break;
      //   // case TB_GETANCHORHIGHLIGHT: break;
      //   case TB_GETBITMAP     : std::fprintf(stdout, "%c%X%s", '[', TB_GETBITMAP,      "]: Toolbar > Get Bitmap"       "\r\n"); break;
      //   case TB_GETBITMAPFLAGS: std::fprintf(stdout, "%c%X%s", '[', TB_GETBITMAPFLAGS, "]: Toolbar > Get Bitmap Flags" "\r\n"); break;
      //   // case TB_GETBUTTON           : break;
      //   // case TB_GETBUTTONINFOA      : break;
      //   // case TB_GETBUTTONINFOW      : break;
      //   // case TB_GETBUTTONSIZE       : break;
      //   // case TB_GETBUTTONTEXTA      : break;
      //   // case TB_GETBUTTONTEXTW      : break;
      //   // case TB_GETDISABLEDIMAGELIST: break;
      //   // case TB_GETEXTENDEDSTYLE    : break;
      //   // case TB_GETHOTIMAGELIST     : break;
      //   // case TB_GETHOTITEM          : break;
      //   case TB_GETIMAGELIST: std::fprintf(stdout, "%c%X%s", '[', TB_GETIMAGELIST, "]: Toolbar > Get Image List" "\r\n"); break;
      //   // case TB_GETINSERTMARK     : break;
      //   // case TB_GETINSERTMARKCOLOR: break;
      //   // case TB_GETITEMRECT       : break;
      //   case TB_GETMAXSIZE: std::fprintf(stdout, "%c%X%s", '[', TB_GETMAXSIZE, "]: Toolbar > Get Maximum Size" "\r\n"); break;
      //   // case TB_GETOBJECT : break;
      //   // case TB_GETPADDING: break;
      //   // case TB_GETRECT   : break;
      //   case TB_GETROWS: std::fprintf(stdout, "%c%X%s", '[', TB_GETROWS, "]: Toolbar > Get Rows" "\r\n"); break;
      //   // case TB_GETSTATE             : break;
      //   // case TB_GETSTRINGA           : break;
      //   // case TB_GETSTRINGW           : break;
      //   // case TB_GETSTYLE             : break;
      //   // case TB_GETTEXTROWS          : break;
      //   // case TB_GETTOOLTIPS          : break;
      //   // case TB_HIDEBUTTON           : break;
      //   // case TB_HITTEST              : break;
      //   // case TB_INDETERMINATE        : break;
      //   // case TB_INSERTBUTTONA        : break;
      //   // case TB_INSERTBUTTONW        : break;
      //   // case TB_INSERTMARKHITTEST    : break;
      //   // case TB_ISBUTTONCHECKED      : break;
      //   // case TB_ISBUTTONENABLED      : break;
      //   // case TB_ISBUTTONHIDDEN       : break;
      //   // case TB_ISBUTTONHIGHLIGHTED  : break;
      //   // case TB_ISBUTTONINDETERMINATE: break;
      //   // case TB_ISBUTTONPRESSED      : break;
      //   // case TB_LOADIMAGES           : break;
      //   // case TB_MAPACCELERATORA      : break;
      //   // case TB_MAPACCELERATORW      : break;
      //   // case TB_MARKBUTTON           : break;
      //   // case TB_MOVEBUTTON           : break;
      //   // case TB_PRESSBUTTON          : break;
      //   case TB_REPLACEBITMAP: std::fprintf(stdout, "%c%X%s", '[', TB_REPLACEBITMAP, "]: Toolbar > Replace Bitmap" "\r\n"); break;
      //   // case TB_SAVERESTOREA      : break;
      //   // case TB_SAVERESTOREW      : break;
      //   // case TB_SETANCHORHIGHLIGHT: break;
      //   // case TB_SETBITMAPSIZE     : break;
      //   // case TB_SETBUTTONINFOA    : break;
      //   // case TB_SETBUTTONINFOW    : break;
      //   // case TB_SETBUTTONSIZE     : break;
      //   // case TB_SETBUTTONWIDTH    : break;
      //   case TB_SETCMDID: std::fprintf(stdout, "%c%X%s", '[', TB_SETCMDID, "]: Toolbar > Set Command Identifier" "\r\n"); break;
      //   // case TB_SETDISABLEDIMAGELIST: break;
      //   // case TB_SETDRAWTEXTFLAGS    : break;
      //   // case TB_SETEXTENDEDSTYLE    : break;
      //   // case TB_SETHOTIMAGELIST     : break;
      //   // case TB_SETHOTITEM          : break;
      //   case TB_SETIMAGELIST: std::fprintf(stdout, "%c%X%s", '[', TB_SETIMAGELIST, "]: Toolbar > Set Image List"  "\r\n"); break;
      //   case TB_SETINDENT   : std::fprintf(stdout, "%c%X%s", '[', TB_SETINDENT,    "]: Toolbar > Set Indentation" "\r\n"); break;
      //   // case TB_SETINSERTMARK     : break;
      //   // case TB_SETINSERTMARKCOLOR: break;
      //   // case TB_SETMAXTEXTROWS    : break;
      //   // case TB_SETPADDING        : break;
      //   // case TB_SETPARENT         : break;
      //   // case TB_SETROWS           : break;
      //   // case TB_SETSTATE          : break;
      //   // case TB_SETSTYLE          : break;
      //   // case TB_SETTOOLTIPS       : break;

      //   /* [Tooltip] */
      //   // case TTM_ACTIVATE       : break;
      //   // case TTM_ADDTOOLA       : break;
      //   // case TTM_ADDTOOLW       : break;
      //   // case TTM_ADJUSTRECT     : break;
      //   // case TTM_DELTOOLA       : break;
      //   // case TTM_DELTOOLW       : break;
      //   // case TTM_ENUMTOOLSA     : break;
      //   // case TTM_ENUMTOOLSW     : break;
      //   // case TTM_GETBUBBLESIZE  : break;
      //   // case TTM_GETCURRENTTOOLA: break;
      //   // case TTM_GETCURRENTTOOLW: break;
      //   // case TTM_GETDELAYTIME   : break;
      //   // case TTM_GETMARGIN      : break;
      //   // case TTM_GETMAXTIPWIDTH : break;
      //   // case TTM_GETTEXTA       : break;
      //   // case TTM_GETTEXTW       : break;
      //   // case TTM_GETTIPBKCOLOR  : break;
      //   // case TTM_GETTIPTEXTCOLOR: break;
      //   // case TTM_GETTOOLCOUNT   : break;
      //   // case TTM_GETTOOLINFOA   : break;
      //   // case TTM_GETTOOLINFOW   : break;
      //   // case TTM_HITTESTA       : break;
      //   // case TTM_HITTESTW       : break;
      //   // case TTM_NEWTOOLRECTA   : break;
      //   // case TTM_NEWTOOLRECTW   : break;
      //   // case TTM_POP            : break;
      //   // case TTM_RELAYEVENT     : break;
      //   // case TTM_SETDELAYTIME   : break;
      //   // case TTM_SETMARGIN      : break;
      //   // case TTM_SETMAXTIPWIDTH : break;
      //   // case TTM_SETTIPBKCOLOR  : break;
      //   // case TTM_SETTIPTEXTCOLOR: break;
      //   // case TTM_SETTITLEA      : break;
      //   // case TTM_SETTITLEW      : break;
      //   // case TTM_SETTOOLINFOA   : break;
      //   // case TTM_SETTOOLINFOW   : break;
      //   // case TTM_TRACKACTIVATE  : break;
      //   // case TTM_TRACKPOSITION  : break;
      //   // case TTM_UPDATE         : break;
      //   // case TTM_UPDATETIPTEXTA : break;
      //   // case TTM_UPDATETIPTEXTW : break;
      //   // case TTM_WINDOWFROMPOINT: break;

      //   /* [Up-Down Control] */
      //   // case UDM_GETACCEL  : break;
      //   // case UDM_GETBASE   : break;
      //   // case UDM_GETBUDDY  : break;
      //   // case UDM_GETPOS    : break;
      //   // case UDM_GETPOS32  : break;
      //   // case UDM_GETRANGE  : break;
      //   // case UDM_GETRANGE32: break;
      //   // case UDM_SETACCEL  : break;
      //   // case UDM_SETBASE   : break;
      //   // case UDM_SETBUDDY  : break;
      //   // case UDM_SETPOS    : break;
      //   // case UDM_SETPOS32  : break;
      //   // case UDM_SETRANGE  : break;
      //   // case UDM_SETRANGE32: break;

      //   /* [User Manager] */
      //   // case UM_GETCURFOCUSA: break;
      //   case UM_GETCURFOCUSW: std::fprintf(stdout, "%c%X%s", '[', UM_GETCURFOCUSW, "]: User Manager > Get Current Focus" "\r\n"); break;
      //   // case UM_GETGROUPSELA: break;
      //   // case UM_GETGROUPSELW: break;
      //   case UM_GETOPTIONS : std::fprintf(stdout, "%c%X%s", '[', UM_GETOPTIONS,  "]: User Manager > Get Options"             "\r\n"); break;
      //   case UM_GETOPTIONS2: std::fprintf(stdout, "%c%X%s", '[', UM_GETOPTIONS2, "]: User Manager > Get Options (Structure)" "\r\n"); break;
      //   // case UM_GETSELCOUNT: break;
      //   // case UM_GETUSERSELA: break;
      //   // case UM_GETUSERSELW: break;

      //   /* [Windows Live Sync?] */
      //   case WLX_WM_SAS: std::fprintf(stdout, "%c%X%s", '[', WLX_WM_SAS, "]: Windows Live Sync > Statistical Analysis Suite Message" "\r\n"); break;

      //   /* [Windows Capture] */
      //   // case WM_CAP_DRIVER_GET_NAMEW      : break;
      //   // case WM_CAP_DRIVER_GET_VERSIONW   : break;
      //   // case WM_CAP_FILE_GET_CAPTURE_FILEW: break;
      //   // case WM_CAP_FILE_SAVEASW          : break;
      //   // case WM_CAP_FILE_SAVEDIBW         : break;
      //   // case WM_CAP_FILE_SET_CAPTURE_FILEW: break;
      //   case WM_CAP_GET_MCI_DEVICEW: std::fprintf(stdout, "%c%X%s", '[', WM_CAP_GET_MCI_DEVICEW, "]: Windows Capture > Get Media Control Interface Device" "\r\n"); break;
      //   case WM_CAP_PAL_OPENW      : std::fprintf(stdout, "%c%X%s", '[', WM_CAP_PAL_OPENW,       "]: Windows Capture > Palette Open"                       "\r\n"); break;
      //   case WM_CAP_PAL_SAVEW      : std::fprintf(stdout, "%c%X%s", '[', WM_CAP_PAL_SAVEW,       "]: Windows Capture > Palette Save"                       "\r\n"); break;
      //   // case WM_CAP_SET_CALLBACK_ERRORW : break;
      //   // case WM_CAP_SET_CALLBACK_STATUSW: break;
      //   // case WM_CAP_SET_MCI_DEVICEW     : break;
      //   // case WM_CAP_UNICODE_START       : break;

      //   /* [Windows] */
      //   case WM_ACTIVATE       : std::fprintf(stdout, "%c%X%s", '[', WM_ACTIVATE,        "]: Windows > Activate"                                 "\r\n"); break;
      //   case WM_ACTIVATEAPP    : std::fprintf(stdout, "%c%X%s", '[', WM_ACTIVATEAPP,     "]: Windows > Activate Application"                     "\r\n"); break;
      //   case WM_AFXFIRST       : std::fprintf(stdout, "%c%X%s", '[', WM_AFXFIRST,        "]: Windows > Application Framework Extensions [FIRST]" "\r\n"); break;
      //   case WM_AFXLAST        : std::fprintf(stdout, "%c%X%s", '[', WM_AFXLAST,         "]: Windows > Application Framework Extensions [LAST]"  "\r\n"); break;
      //   case WM_APP            : std::fprintf(stdout, "%c%X%s", '[', WM_APP,             "]: Windows > Application"                              "\r\n"); break;
      //   case WM_APPCOMMAND     : std::fprintf(stdout, "%c%X%s", '[', WM_APPCOMMAND,      "]: Windows > Application Command"                      "\r\n"); break;
      //   case WM_ASKCBFORMATNAME: std::fprintf(stdout, "%c%X%s", '[', WM_ASKCBFORMATNAME, "]: Windows > Ask Clipboard Format Name"                "\r\n"); break;
      //   case WM_CANCELJOURNAL  : std::fprintf(stdout, "%c%X%s", '[', WM_CANCELJOURNAL,   "]: Windows > Cancel Journal"                           "\r\n"); break;
      //   case WM_CANCELMODE     : std::fprintf(stdout, "%c%X%s", '[', WM_CANCELMODE,      "]: Windows > Cancel Mode"                              "\r\n"); break;
      //   case WM_CAPTURECHANGED : std::fprintf(stdout, "%c%X%s", '[', WM_CAPTURECHANGED,  "]: Windows Capture > Changed"                          "\r\n"); break;
      //   case WM_CHANGECBCHAIN  : std::fprintf(stdout, "%c%X%s", '[', WM_CHANGECBCHAIN,   "]: Windows > Change Control Box Chain"                 "\r\n"); break;
      //   case WM_CHANGEUISTATE  : std::fprintf(stdout, "%c%X%s", '[', WM_CHANGEUISTATE,   "]: Windows > Change User-Interface State"              "\r\n"); break;
      //   case WM_CHAR           : std::fprintf(stdout, "%c%X%s", '[', WM_CHAR,            "]: Windows > Character"                                "\r\n"); break;
      //   case WM_CHARTOITEM     : std::fprintf(stdout, "%c%X%s", '[', WM_CHARTOITEM,      "]: Windows > Character to Item"                        "\r\n"); break;
      //   case WM_CHILDACTIVATE  : std::fprintf(stdout, "%c%X%s", '[', WM_CHILDACTIVATE,   "]: Windows > Child Activate"                           "\r\n"); break;
      //   // case WM_CHOOSEFONT_GETLOGFONT: break;
      //   // case WM_CHOOSEFONT_SETFLAGS  : break;
      //   // case WM_CHOOSEFONT_SETLOGFON T: break;
      //   case WM_CLEAR         : std::fprintf(stdout, "%c%X%s", '[', WM_CLEAR,          "]: Windows > Clear"            "\r\n"); break;
      //   case WM_CLOSE         : std::fprintf(stdout, "%c%X%s", '[', WM_CLOSE,          "]: Windows > Close" "\r\n"); { ::DestroyWindow(windowHandle); ::PostQuitMessage(0x0u); } break;
      //   case WM_COMMAND       : std::fprintf(stdout, "%c%X%s", '[', WM_COMMAND,        "]: Windows > Command"          "\r\n"); break;
      //   case WM_COMMNOTIFY    : std::fprintf(stdout, "%c%X%s", '[', WM_COMMNOTIFY,     "]: Windows > Command Notify"   "\r\n"); break;
      //   case WM_COMPACTING    : std::fprintf(stdout, "%c%X%s", '[', WM_COMPACTING,     "]: Windows > Compacting"       "\r\n"); break;
      //   case WM_COMPAREITEM   : std::fprintf(stdout, "%c%X%s", '[', WM_COMPAREITEM,    "]: Windows > Compare Item"     "\r\n"); break;
      //   case WM_CONTEXTMENU   : std::fprintf(stdout, "%c%X%s", '[', WM_CONTEXTMENU,    "]: Windows > Context Menu"     "\r\n"); break;
      //   case WM_CONVERTREQUEST: std::fprintf(stdout, "%c%X%s", '[', WM_CONVERTREQUEST, "]: Windows > Convert Request"  "\r\n"); break;
      //   case WM_CONVERTRESULT : std::fprintf(stdout, "%c%X%s", '[', WM_CONVERTRESULT,  "]: Windows > Convert Result"   "\r\n"); break;
      //   case WM_COPY          : std::fprintf(stdout, "%c%X%s", '[', WM_COPY,           "]: Windows > Copy"             "\r\n"); break;
      //   case WM_COPYDATA      : std::fprintf(stdout, "%c%X%s", '[', WM_COPYDATA,       "]: Windows > Copy Data"        "\r\n"); break;
      //   case WM_COPYGLOBALDATA: std::fprintf(stdout, "%c%X%s", '[', WM_COPYGLOBALDATA, "]: Windows > Copy Global Data" "\r\n"); break;
      //   // case WM_CPL_LAUNCH  : break;
      //   // case WM_CPL_LAUNCHED: break;
      //   case WM_CREATE           : std::fprintf(stdout, "%c%X%s", '[', WM_CREATE,            "]: Windows > Create"                      "\r\n"); break;
      //   case WM_CTLCOLOR         : std::fprintf(stdout, "%c%X%s", '[', WM_CTLCOLOR,          "]: Windows > Control Color"               "\r\n"); break;
      //   case WM_CTLCOLORBTN      : std::fprintf(stdout, "%c%X%s", '[', WM_CTLCOLORBTN,       "]: Windows > Control Color Button"        "\r\n"); break;
      //   case WM_CTLCOLORDLG      : std::fprintf(stdout, "%c%X%s", '[', WM_CTLCOLORDLG,       "]: Windows > Control Color Dialog"        "\r\n"); break;
      //   case WM_CTLCOLOREDIT     : std::fprintf(stdout, "%c%X%s", '[', WM_CTLCOLOREDIT,      "]: Windows > Control Color Editor"        "\r\n"); break;
      //   case WM_CTLCOLORLISTBOX  : std::fprintf(stdout, "%c%X%s", '[', WM_CTLCOLORLISTBOX,   "]: Windows > Control Color List Box"      "\r\n"); break;
      //   case WM_CTLCOLORMSGBOX   : std::fprintf(stdout, "%c%X%s", '[', WM_CTLCOLORMSGBOX,    "]: Windows > Control Color Message Box"   "\r\n"); break;
      //   case WM_CTLCOLORSCROLLBAR: std::fprintf(stdout, "%c%X%s", '[', WM_CTLCOLORSCROLLBAR, "]: Windows > Control Color Scrollbar"     "\r\n"); break;
      //   case WM_CTLCOLORSTATIC   : std::fprintf(stdout, "%c%X%s", '[', WM_CTLCOLORSTATIC,    "]: Windows > Control Color Static"        "\r\n"); break;
      //   case WM_CTLINIT          : std::fprintf(stdout, "%c%X%s", '[', WM_CTLINIT,           "]: Windows > Control Initiation"          "\r\n"); break;
      //   case WM_CUT              : std::fprintf(stdout, "%c%X%s", '[', WM_CUT,               "]: Windows > Cut"                         "\r\n"); break;
      //   case WM_DEADCHAR         : std::fprintf(stdout, "%c%X%s", '[', WM_DEADCHAR,          "]: Windows > Dead Character"              "\r\n"); break;
      //   case WM_DELETEITEM       : std::fprintf(stdout, "%c%X%s", '[', WM_DELETEITEM,        "]: Windows > Delete Item"                 "\r\n"); break;
      //   case WM_DESTROY          : std::fprintf(stdout, "%c%X%s", '[', WM_DESTROY,           "]: Windows > Destroy" "\r\n"); { ::PostQuitMessage(0x0u); } break;
      //   case WM_DESTROYCLIPBOARD : std::fprintf(stdout, "%c%X%s", '[', WM_DESTROYCLIPBOARD,  "]: Windows > Destroy Clipboard"           "\r\n"); break;
      //   case WM_DEVICECHANGE     : std::fprintf(stdout, "%c%X%s", '[', WM_DEVICECHANGE,      "]: Windows > Device Change"               "\r\n"); break;
      //   case WM_DEVMODECHANGE    : std::fprintf(stdout, "%c%X%s", '[', WM_DEVMODECHANGE,     "]: Windows > Device Mode Change"          "\r\n"); break;
      //   case WM_DISPLAYCHANGE    : std::fprintf(stdout, "%c%X%s", '[', WM_DISPLAYCHANGE,     "]: Windows > Display Change"              "\r\n"); break;
      //   case WM_DRAWCLIPBOARD    : std::fprintf(stdout, "%c%X%s", '[', WM_DRAWCLIPBOARD,     "]: Windows > Draw Clipboard"              "\r\n"); break;
      //   case WM_DRAWITEM         : std::fprintf(stdout, "%c%X%s", '[', WM_DRAWITEM,          "]: Windows > Draw Item"                   "\r\n"); break;
      //   case WM_DROPFILES        : std::fprintf(stdout, "%c%X%s", '[', WM_DROPFILES,         "]: Windows > Drop Files"                  "\r\n"); break;
      //   case WM_ENABLE           : std::fprintf(stdout, "%c%X%s", '[', WM_ENABLE,            "]: Windows > Enable"                      "\r\n"); break;
      //   case WM_ENDSESSION       : std::fprintf(stdout, "%c%X%s", '[', WM_ENDSESSION,        "]: Windows > End Session"                 "\r\n"); break;
      //   case WM_ENTERIDLE        : std::fprintf(stdout, "%c%X%s", '[', WM_ENTERIDLE,         "]: Windows > Enter Idle"                  "\r\n"); break;
      //   case WM_ENTERMENULOOP    : std::fprintf(stdout, "%c%X%s", '[', WM_ENTERMENULOOP,     "]: Windows > Enter Menu Loop"             "\r\n"); break;
      //   case WM_ENTERSIZEMOVE    : std::fprintf(stdout, "%c%X%s", '[', WM_ENTERSIZEMOVE,     "]: Windows > Enter Size Move"             "\r\n"); break;
      //   case WM_ERASEBKGND       : std::fprintf(stdout, "%c%X%s", '[', WM_ERASEBKGND,        "]: Windows > Erase Background"            "\r\n"); break;
      //   case WM_EXITMENULOOP     : std::fprintf(stdout, "%c%X%s", '[', WM_EXITMENULOOP,      "]: Windows > Exit Menu Loop"              "\r\n"); break;
      //   case WM_EXITSIZEMOVE     : std::fprintf(stdout, "%c%X%s", '[', WM_EXITSIZEMOVE,      "]: Windows > Exit Size Move"              "\r\n"); break;
      //   case WM_FONTCHANGE       : std::fprintf(stdout, "%c%X%s", '[', WM_FONTCHANGE,        "]: Windows > Font Change"                 "\r\n"); break;
      //   case WM_GETDLGCODE       : std::fprintf(stdout, "%c%X%s", '[', WM_GETDLGCODE,        "]: Windows > Get Dialog Code"             "\r\n"); break;
      //   case WM_GETFONT          : std::fprintf(stdout, "%c%X%s", '[', WM_GETFONT,           "]: Windows > Get Font"                    "\r\n"); break;
      //   case WM_GETHOTKEY        : std::fprintf(stdout, "%c%X%s", '[', WM_GETHOTKEY,         "]: Windows > Get Hotkey"                  "\r\n"); break;
      //   case WM_GETICON          : std::fprintf(stdout, "%c%X%s", '[', WM_GETICON,           "]: Windows > Get Icon"                    "\r\n"); break;
      //   case WM_GETMINMAXINFO    : std::fprintf(stdout, "%c%X%s", '[', WM_GETMINMAXINFO,     "]: Windows > Get Min-Maximum Information" "\r\n"); break;
      //   case WM_GETOBJECT        : std::fprintf(stdout, "%c%X%s", '[', WM_GETOBJECT,         "]: Windows > Get Object"                  "\r\n"); break;
      //   case WM_GETTEXT          : std::fprintf(stdout, "%c%X%s", '[', WM_GETTEXT,           "]: Windows > Get Text"                    "\r\n"); break;
      //   case WM_GETTEXTLENGTH    : std::fprintf(stdout, "%c%X%s", '[', WM_GETTEXTLENGTH,     "]: Windows > Get Text Length"             "\r\n"); break;
      //   case WM_GLOBALRCCHANGE: /* --> WM_PENMISCINFO */ {
      //   //   std::fprintf(stdout, "%c%X%4s", '[', WM_GLOBALRCCHANGE, "]: {");
      //   //     std::fputs("Windows: Global RC Change"              "\r\n", stdout);
      //   //     std::fputs("Windows: Pen Miscellaneous Information" "\r\n", stdout);
      //   //   std::fputs("}" "\r\n", stdout);
      //   // } break;
      //   case WM_HANDHELDFIRST: std::fprintf(stdout, "%c%X%s", '[', WM_HANDHELDFIRST, "]: Windows > Hand-Held [FIRST]" "\r\n"); break;
      //   case WM_HANDHELDLAST : std::fprintf(stdout, "%c%X%s", '[', WM_HANDHELDLAST,  "]: Windows > Hand-Held [LAST]"  "\r\n"); break;
      //   case WM_HEDITCTL: /* --> WM_PENCTL */ {
      //   //   std::fprintf(stdout, "%c%X%4s", '[', WM_HEDITCTL, "]: {");
      //   //     std::fputs("Windows: Hand-Editing Control" "\r\n", stdout);
      //   //     std::fputs("Windows: Pen Control"          "\r\n", stdout);
      //   //   std::fputs("}" "\r\n", stdout);
      //   // } break;
      //   case WM_HELP                   : std::fprintf(stdout, "%c%X%s", '[', WM_HELP,                "]: Windows > Help"                                                                    "\r\n"); break;
      //   case WM_HOOKRCRESULT           : std::fprintf(stdout, "%c%X%s", '[', WM_HOOKRCRESULT,        "]: Windows > Hook RC Result"                                                          "\r\n"); break;
      //   case WM_HOTKEY                 : std::fprintf(stdout, "%c%X%s", '[', WM_HOTKEY,              "]: Windows > Hotkey"                                                                  "\r\n"); break;
      //   case WM_HSCROLL                : std::fprintf(stdout, "%c%X%s", '[', WM_HSCROLL,             "]: Windows > Horizontal Scroll"                                                       "\r\n"); break;
      //   case WM_HSCROLLCLIPBOARD       : std::fprintf(stdout, "%c%X%s", '[', WM_HSCROLLCLIPBOARD,    "]: Windows > Horizontal Scroll Clipboard"                                             "\r\n"); break;
      //   case WM_ICONERASEBKGND         : std::fprintf(stdout, "%c%X%s", '[', WM_ICONERASEBKGND,      "]: Windows > Icon Erase Background"                                                   "\r\n"); break;
      //   case WM_IMEKEYDOWN             : /* --> WM_IME_KEYDOWN */ std::fprintf(stdout, "%c%X%s", '[', WM_IMEKEYDOWN,      "]: Windows > IME (Input Method Editor) Key Down"                 "\r\n"); break;
      //   case WM_IMEKEYUP               : /* --> WM_IME_KEYUP */   std::fprintf(stdout, "%c%X%s", '[', WM_IMEKEYUP,        "]: Windows > IME (Input Method Editor) Key Up"                   "\r\n"); break;
      //   case WM_IME_CHAR               : std::fprintf(stdout, "%c%X%s", '[', WM_IME_CHAR,            "]: Windows > IME (Input Method Editor) Character"                                     "\r\n"); break;
      //   case WM_IME_COMPOSITION        : /* --> WM_IME_KEYLAST */ std::fprintf(stdout, "%c%X%s", '[', WM_IME_COMPOSITION, "]: Windows > IME (Input Method Editor) Composition [(Key) LAST]" "\r\n"); break;
      //   case WM_IME_COMPOSITIONFULL    : std::fprintf(stdout, "%c%X%s", '[', WM_IME_COMPOSITIONFULL, "]: Windows > IME (Input Method Editor) Composition Full"                              "\r\n"); break;
      //   case WM_IME_CONTROL            : std::fprintf(stdout, "%c%X%s", '[', WM_IME_CONTROL,         "]: Windows > IME (Input Method Editor) Control"                                       "\r\n"); break;
      //   case WM_IME_ENDCOMPOSITION     : std::fprintf(stdout, "%c%X%s", '[', WM_IME_ENDCOMPOSITION,  "]: Windows > IME (Input Method Editor) End Composition"                               "\r\n"); break;
      //   // case WM_IME_KEYDOWN: break;
      //   // case WM_IME_KEYLAST: break;
      //   // case WM_IME_KEYUP  : break;
      //   case WM_IME_NOTIFY            : std::fprintf(stdout, "%c%X%s", '[', WM_IME_NOTIFY,             "]: Windows > IME (Input Method Editor) Notify"            "\r\n"); break;
      //   case WM_IME_REPORT            : std::fprintf(stdout, "%c%X%s", '[', WM_IME_REPORT,             "]: Windows > IME (Input Method Editor) Report"            "\r\n"); break;
      //   case WM_IME_REQUEST           : std::fprintf(stdout, "%c%X%s", '[', WM_IME_REQUEST,            "]: Windows > IME (Input Method Editor) Request"           "\r\n"); break;
      //   case WM_IME_SELECT            : std::fprintf(stdout, "%c%X%s", '[', WM_IME_SELECT,             "]: Windows > IME (Input Method Editor) Select"            "\r\n"); break;
      //   case WM_IME_SETCONTEXT        : std::fprintf(stdout, "%c%X%s", '[', WM_IME_SETCONTEXT,         "]: Windows > IME (Input Method Editor) Set Context"       "\r\n"); break;
      //   case WM_IME_STARTCOMPOSITION  : std::fprintf(stdout, "%c%X%s", '[', WM_IME_STARTCOMPOSITION,   "]: Windows > IME (Input Method Editor) Start Composition" "\r\n"); break;
      //   case WM_INITDIALOG            : std::fprintf(stdout, "%c%X%s", '[', WM_INITDIALOG,             "]: Windows > Initiate Dialog"                             "\r\n"); break;
      //   case WM_INITMENU              : std::fprintf(stdout, "%c%X%s", '[', WM_INITMENU,               "]: Windows > Initiate Menu"                               "\r\n"); break;
      //   case WM_INITMENUPOPUP         : std::fprintf(stdout, "%c%X%s", '[', WM_INITMENUPOPUP,          "]: Windows > Initiate Menu Pop-Up"                        "\r\n"); break;
      //   case WM_INPUT                 : std::fprintf(stdout, "%c%X%s", '[', WM_INPUT,                  "]: Windows > Input"                                       "\r\n"); break;
      //   case WM_INPUTLANGCHANGE       : std::fprintf(stdout, "%c%X%s", '[', WM_INPUTLANGCHANGE,        "]: Windows > Input Language Change"                       "\r\n"); break;
      //   case WM_INPUTLANGCHANGEREQUEST: std::fprintf(stdout, "%c%X%s", '[', WM_INPUTLANGCHANGEREQUEST, "]: Windows > Input Language Change Request"               "\r\n"); break;
      //   case WM_INTERIM               : std::fprintf(stdout, "%c%X%s", '[', WM_INTERIM,                "]: Windows > Interim"                                     "\r\n"); break;
      //   case WM_KEYDOWN: /* --> WM_KEYFIRST */ std::fprintf(stdout, "%c%X%s", '[', WM_KEYDOWN, "]: Windows > Key Down [FIRST]" "\r\n"); { if (VK_ESCAPE == parameter) { ::DestroyWindow(windowHandle); ::PostQuitMessage(0x0u); } } break;
      //   // case WM_KEYFIRST: break;
      //   case WM_KEYLAST: /* --> WM_UNICHAR | WM_WNT_CONVERTREQUESTEX */ {
      //     std::fprintf(stdout, "%c%X%4s", '[', WM_KEYLAST, "]: {");
      //       std::fputs("Windows: Convert Request"   "\r\n", stdout);
      //       std::fputs("Windows: Key [LAST]"        "\r\n", stdout);
      //       std::fputs("Windows: Unicode Character" "\r\n", stdout);
      //     std::fputs("}" "\r\n", stdout);
      //   } break;
      //   case WM_KEYUP         : std::fprintf(stdout, "%c%X%s", '[', WM_KEYUP,          "]: Windows > Key Up"                                                               "\r\n"); break;
      //   case WM_KILLFOCUS     : std::fprintf(stdout, "%c%X%s", '[', WM_KILLFOCUS,      "]: Windows > Kill Focus"                                                           "\r\n"); break;
      //   case WM_LBUTTONDBLCLK : std::fprintf(stdout, "%c%X%s", '[', WM_LBUTTONDBLCLK,  "]: Windows > Left (Mouse) Button Double-Click"                                     "\r\n"); break;
      //   case WM_LBUTTONDOWN   : std::fprintf(stdout, "%c%X%s", '[', WM_LBUTTONDOWN,    "]: Windows > Left (Mouse) Button Down"                                             "\r\n"); break;
      //   case WM_LBUTTONUP     : std::fprintf(stdout, "%c%X%s", '[', WM_LBUTTONUP,      "]: Windows > Left (Mouse) Button Up"                                               "\r\n"); break;
      //   case WM_MBUTTONDBLCLK : std::fprintf(stdout, "%c%X%s", '[', WM_MBUTTONDBLCLK,  "]: Windows > Middle (Mouse) Button Double-Click"                                   "\r\n"); break;
      //   case WM_MBUTTONDOWN   : std::fprintf(stdout, "%c%X%s", '[', WM_MBUTTONDOWN,    "]: Windows > Middle (Mouse) Button Down"                                           "\r\n"); break;
      //   case WM_MBUTTONUP     : std::fprintf(stdout, "%c%X%s", '[', WM_MBUTTONUP,      "]: Windows > Middle (Mouse) Button Up"                                             "\r\n"); break;
      //   case WM_MDIACTIVATE   : std::fprintf(stdout, "%c%X%s", '[', WM_MDIACTIVATE,    "]: Windows > Multiple-Document Interface Activate"                                 "\r\n"); break;
      //   case WM_MDICASCADE    : std::fprintf(stdout, "%c%X%s", '[', WM_MDICASCADE,     "]: Windows > Multiple-Document Interface Cascade"                                  "\r\n"); break;
      //   case WM_MDICREATE     : std::fprintf(stdout, "%c%X%s", '[', WM_MDICREATE,      "]: Windows > Multiple-Document Interface Create"                                   "\r\n"); break;
      //   case WM_MDIDESTROY    : std::fprintf(stdout, "%c%X%s", '[', WM_MDIDESTROY,     "]: Windows > Multiple-Document Interface Destroy"                                  "\r\n"); break;
      //   case WM_MDIGETACTIVE  : std::fprintf(stdout, "%c%X%s", '[', WM_MDIGETACTIVE,   "]: Windows > Multiple-Document Interface Get Active"                               "\r\n"); break;
      //   case WM_MDIICONARRANGE: std::fprintf(stdout, "%c%X%s", '[', WM_MDIICONARRANGE, "]: Windows > Multiple-Document Interface Icon Arrange"                             "\r\n"); break;
      //   case WM_MDIMAXIMIZE   : std::fprintf(stdout, "%c%X%s", '[', WM_MDIMAXIMIZE,    "]: Windows > Multiple-Document Interface Maximize"                                 "\r\n"); break;
      //   case WM_MDINEXT       : std::fprintf(stdout, "%c%X%s", '[', WM_MDINEXT,        "]: Windows > Multiple-Document Interface Next"                                     "\r\n"); break;
      //   case WM_MDIREFRESHMENU: std::fprintf(stdout, "%c%X%s", '[', WM_MDIREFRESHMENU, "]: Windows > Multiple-Document Interface Refresh Menu"                             "\r\n"); break;
      //   case WM_MDIRESTORE    : std::fprintf(stdout, "%c%X%s", '[', WM_MDIRESTORE,     "]: Windows > Multiple-Document Interface Restore"                                  "\r\n"); break;
      //   case WM_MDISETMENU    : std::fprintf(stdout, "%c%X%s", '[', WM_MDISETMENU,     "]: Windows > Multiple-Document Interface Set Menu"                                 "\r\n"); break;
      //   case WM_MDITILE       : std::fprintf(stdout, "%c%X%s", '[', WM_MDITILE,        "]: Windows > Multiple-Document Interface Tile"                                     "\r\n"); break;
      //   case WM_MEASUREITEM   : std::fprintf(stdout, "%c%X%s", '[', WM_MEASUREITEM,    "]: Windows > Measure Item"                                                         "\r\n"); break;
      //   case WM_MENUCHAR      : std::fprintf(stdout, "%c%X%s", '[', WM_MENUCHAR,       "]: Windows > Menu Character"                                                       "\r\n"); break;
      //   case WM_MENUCOMMAND   : std::fprintf(stdout, "%c%X%s", '[', WM_MENUCOMMAND,    "]: Windows > Menu Command"                                                         "\r\n"); break;
      //   case WM_MENUDRAG      : std::fprintf(stdout, "%c%X%s", '[', WM_MENUDRAG,       "]: Windows > Menu Drag"                                                            "\r\n"); break;
      //   case WM_MENUGETOBJECT : std::fprintf(stdout, "%c%X%s", '[', WM_MENUGETOBJECT,  "]: Windows > Menu Get to Object"                                                   "\r\n"); break;
      //   case WM_MENURBUTTONUP : std::fprintf(stdout, "%c%X%s", '[', WM_MENURBUTTONUP,  "]: Windows > Menu Right (Mouse) Button Up"                                         "\r\n"); break;
      //   case WM_MENUSELECT    : std::fprintf(stdout, "%c%X%s", '[', WM_MENUSELECT,     "]: Windows > Menu Select"                                                          "\r\n"); break;
      //   case WM_MOUSEACTIVATE : std::fprintf(stdout, "%c%X%s", '[', WM_MOUSEACTIVATE,  "]: Windows > Mouse Activate"                                                       "\r\n"); break;
      //   case WM_MOUSEFIRST    : /* --> WM_MOUSEMOVE */     std::fprintf(stdout, "%c%X%s", '[', WM_MOUSEMOVE,     "]: Windows > Mouse Move [FIRST]"                         "\r\n"); break;
      //   case WM_MOUSEHOVER    : std::fprintf(stdout, "%c%X%s", '[', WM_MOUSEHOVER,     "]: Windows > Mouse Hover"                                                          "\r\n"); break;
      //   case WM_MOUSELAST     : /* --> WM_XBUTTONDBLCLK */ std::fprintf(stdout, "%c%X%s", '[', WM_XBUTTONDBLCLK, "]: Windows > Mouse X (Mouse) Button Double-Click [LAST]" "\r\n"); break;
      //   case WM_MOUSELEAVE    : std::fprintf(stdout, "%c%X%s", '[', WM_MOUSELEAVE,     "]: Windows > Mouse Leave"                                                          "\r\n"); break;
      //   // case WM_MOUSEMOVE: break;
      //   case WM_MOUSEWHEEL       : std::fprintf(stdout, "%c%X%s", '[', WM_MOUSEWHEEL,        "]: Windows > Mouse Wheel"                                   "\r\n"); break;
      //   case WM_MOVE             : std::fprintf(stdout, "%c%X%s", '[', WM_MOVE,              "]: Windows > Move"                                          "\r\n"); break;
      //   case WM_MOVING           : std::fprintf(stdout, "%c%X%s", '[', WM_MOVING,            "]: Windows > Moving"                                        "\r\n"); break;
      //   case WM_NCACTIVATE       : std::fprintf(stdout, "%c%X%s", '[', WM_NCACTIVATE,        "]: Windows > Non-Client Activate"                           "\r\n"); break;
      //   case WM_NCCALCSIZE       : std::fprintf(stdout, "%c%X%s", '[', WM_NCCALCSIZE,        "]: Windows > Non-Client Calculate Size"                     "\r\n"); break;
      //   case WM_NCCREATE         : std::fprintf(stdout, "%c%X%s", '[', WM_NCCREATE,          "]: Windows > Non-Client Create"                             "\r\n"); break;
      //   case WM_NCDESTROY        : std::fprintf(stdout, "%c%X%s", '[', WM_NCDESTROY,         "]: Windows > Non-Client Destroy"                            "\r\n"); break;
      //   case WM_NCHITTEST        : std::fprintf(stdout, "%c%X%s", '[', WM_NCHITTEST,         "]: Windows > Non-Client Hit-Test"                           "\r\n"); break;
      //   case WM_NCLBUTTONDBLCLK  : std::fprintf(stdout, "%c%X%s", '[', WM_NCLBUTTONDBLCLK,   "]: Windows > Non-Client Left (Mouse) Button Double-Click"   "\r\n"); break;
      //   case WM_NCLBUTTONDOWN    : std::fprintf(stdout, "%c%X%s", '[', WM_NCLBUTTONDOWN,     "]: Windows > Non-Client Left (Mouse) Button Down"           "\r\n"); break;
      //   case WM_NCLBUTTONUP      : std::fprintf(stdout, "%c%X%s", '[', WM_NCLBUTTONUP,       "]: Windows > Non-Client Left (Mouse) Button Up"             "\r\n"); break;
      //   case WM_NCMBUTTONDBLCLK  : std::fprintf(stdout, "%c%X%s", '[', WM_NCMBUTTONDBLCLK,   "]: Windows > Non-Client Middle (Mouse) Button Double-Click" "\r\n"); break;
      //   case WM_NCMBUTTONDOWN    : std::fprintf(stdout, "%c%X%s", '[', WM_NCMBUTTONDOWN,     "]: Windows > Non-Client Middle (Mouse) Button Down"         "\r\n"); break;
      //   case WM_NCMBUTTONUP      : std::fprintf(stdout, "%c%X%s", '[', WM_NCMBUTTONUP,       "]: Windows > Non-Client Middle (Mouse) Button Up"           "\r\n"); break;
      //   case WM_NCMOUSEHOVER     : std::fprintf(stdout, "%c%X%s", '[', WM_NCMOUSEHOVER,      "]: Windows > Non-Client Mouse Hover"                        "\r\n"); break;
      //   case WM_NCMOUSELEAVE     : std::fprintf(stdout, "%c%X%s", '[', WM_NCMOUSELEAVE,      "]: Windows > Non-Client Mouse Leave"                        "\r\n"); break;
      //   case WM_NCMOUSEMOVE      : std::fprintf(stdout, "%c%X%s", '[', WM_NCMOUSEMOVE,       "]: Windows > Non-Client Mouse Mouse"                        "\r\n"); break;
      //   case WM_NCPAINT          : std::fprintf(stdout, "%c%X%s", '[', WM_NCPAINT,           "]: Windows > Non-Client Paint"                              "\r\n"); break;
      //   case WM_NCRBUTTONDBLCLK  : std::fprintf(stdout, "%c%X%s", '[', WM_NCRBUTTONDBLCLK,   "]: Windows > Non-Client Right (Mouse) Button Double-Click"  "\r\n"); break;
      //   case WM_NCRBUTTONDOWN    : std::fprintf(stdout, "%c%X%s", '[', WM_NCRBUTTONDOWN,     "]: Windows > Non-Client Right (Mouse) Button Down"          "\r\n"); break;
      //   case WM_NCRBUTTONUP      : std::fprintf(stdout, "%c%X%s", '[', WM_NCRBUTTONUP,       "]: Windows > Non-Client Right (Mouse) Button Up"            "\r\n"); break;
      //   case WM_NCXBUTTONDBLCLK  : std::fprintf(stdout, "%c%X%s", '[', WM_NCXBUTTONDBLCLK,   "]: Windows > Non-Client X (Mouse) Button Double-Click"      "\r\n"); break;
      //   case WM_NCXBUTTONDOWN    : std::fprintf(stdout, "%c%X%s", '[', WM_NCXBUTTONDOWN,     "]: Windows > Non-Client X (Mouse) Button Down"              "\r\n"); break;
      //   case WM_NCXBUTTONUP      : std::fprintf(stdout, "%c%X%s", '[', WM_NCXBUTTONUP,       "]: Windows > Non-Client X (Mouse) Button Up"                "\r\n"); break;
      //   case WM_NEXTDLGCTL       : std::fprintf(stdout, "%c%X%s", '[', WM_NEXTDLGCTL,        "]: Windows > Next Dialog Control"                           "\r\n"); break;
      //   case WM_NEXTMENU         : std::fprintf(stdout, "%c%X%s", '[', WM_NEXTMENU,          "]: Windows > Next Menu"                                     "\r\n"); break;
      //   case WM_NOTIFY           : std::fprintf(stdout, "%c%X%s", '[', WM_NOTIFY,            "]: Windows > Notify"                                        "\r\n"); break;
      //   case WM_NOTIFYFORMAT     : std::fprintf(stdout, "%c%X%s", '[', WM_NOTIFYFORMAT,      "]: Windows > Notify Format"                                 "\r\n"); break;
      //   case WM_NULL             : std::fprintf(stdout, "%c%X%s", '[', WM_NULL,              "]: Windows > [NULL]"                                        "\r\n"); break;
      //   case WM_PAINT            : std::fprintf(stdout, "%c%X%s", '[', WM_PAINT,             "]: Windows > Paint"                                         "\r\n"); break;
      //   case WM_PAINTCLIPBOARD   : std::fprintf(stdout, "%c%X%s", '[', WM_PAINTCLIPBOARD,    "]: Windows > Paint Clipboard"                               "\r\n"); break;
      //   case WM_PAINTICON        : std::fprintf(stdout, "%c%X%s", '[', WM_PAINTICON,         "]: Windows > Paint Icon"                                    "\r\n"); break;
      //   case WM_PALETTECHANGED   : std::fprintf(stdout, "%c%X%s", '[', WM_PALETTECHANGED,    "]: Windows > Palette Changed"                               "\r\n"); break;
      //   case WM_PALETTEISCHANGING: std::fprintf(stdout, "%c%X%s", '[', WM_PALETTEISCHANGING, "]: Windows > Palette is Changing"                           "\r\n"); break;
      //   case WM_PARENTNOTIFY     : std::fprintf(stdout, "%c%X%s", '[', WM_PARENTNOTIFY,      "]: Windows > Parent Notify"                                 "\r\n"); break;
      //   case WM_PASTE            : std::fprintf(stdout, "%c%X%s", '[', WM_PASTE,             "]: Windows > Paste"                                         "\r\n"); break;
      //   // case WM_PENCTL: break;
      //   case WM_PENEVENT: std::fprintf(stdout, "%c%X%s", '[', WM_PENEVENT, "]: Windows > Pen Event"         "\r\n"); break;
      //   case WM_PENMISC : std::fprintf(stdout, "%c%X%s", '[', WM_PENMISC,  "]: Windows > Pen Miscellaneous" "\r\n"); break;
      //   // case WM_PENMISCINFO: break;
      //   case WM_PENWINFIRST   : std::fprintf(stdout, "%c%X%s", '[', WM_PENWINFIRST,    "]: Windows > Pen [FIRST]"     "\r\n"); break;
      //   case WM_PENWINLAST    : std::fprintf(stdout, "%c%X%s", '[', WM_PENWINLAST,     "]: Windows > Pen [LAST]"      "\r\n"); break;
      //   case WM_POWER         : std::fprintf(stdout, "%c%X%s", '[', WM_POWER,          "]: Windows > Power"           "\r\n"); break;
      //   case WM_POWERBROADCAST: std::fprintf(stdout, "%c%X%s", '[', WM_POWERBROADCAST, "]: Windows > Power Broadcast" "\r\n"); break;
      //   case WM_PRINT         : std::fprintf(stdout, "%c%X%s", '[', WM_PRINT,          "]: Windows > Print"           "\r\n"); break;
      //   case WM_PRINTCLIENT   : std::fprintf(stdout, "%c%X%s", '[', WM_PRINTCLIENT,    "]: Windows > Print Client"    "\r\n"); break;
      //   // case WM_PSD_ENVSTAMPRECT  : break;
      //   // case WM_PSD_FULLPAGERECT  : break;
      //   // case WM_PSD_GREEKTEXTRECT : break;
      //   // case WM_PSD_MARGINRECT    : break;
      //   // case WM_PSD_MINMARGINRECT : break;
      //   // case WM_PSD_PAGESETUPDLG  : break;
      //   // case WM_PSD_YAFULLPAGERECT: break;
      //   case WM_QUERYDRAGICON   : std::fprintf(stdout, "%c%X%s", '[', WM_QUERYDRAGICON,    "]: Windows > Query Drag Icon"                            "\r\n"); break;
      //   case WM_QUERYENDSESSION : std::fprintf(stdout, "%c%X%s", '[', WM_QUERYENDSESSION,  "]: Windows > Query End Session"                          "\r\n"); break;
      //   case WM_QUERYNEWPALETTE : std::fprintf(stdout, "%c%X%s", '[', WM_QUERYNEWPALETTE,  "]: Windows > Query New Palette"                          "\r\n"); break;
      //   case WM_QUERYOPEN       : std::fprintf(stdout, "%c%X%s", '[', WM_QUERYOPEN,        "]: Windows > Query Open"                                 "\r\n"); break;
      //   case WM_QUERYUISTATE    : std::fprintf(stdout, "%c%X%s", '[', WM_QUERYUISTATE,     "]: Windows > Query User-Interface State"                 "\r\n"); break;
      //   case WM_QUEUESYNC       : std::fprintf(stdout, "%c%X%s", '[', WM_QUEUESYNC,        "]: Windows > Queue Synchronization"                      "\r\n"); break;
      //   case WM_QUIT            : std::fprintf(stdout, "%c%X%s", '[', WM_QUIT,             "]: Windows > Quit" "\r\n"); { ::PostQuitMessage(0x0u); } break;
      //   case WM_RASDIALEVENT    : std::fprintf(stdout, "%c%X%s", '[', WM_RASDIALEVENT,     "]: Windows > Routing & Remote Access Service Dial Event" "\r\n"); break;
      //   case WM_RBUTTONDBLCLK   : std::fprintf(stdout, "%c%X%s", '[', WM_RBUTTONDBLCLK,    "]: Windows > Right (Mouse) Button Double-Click"          "\r\n"); break;
      //   case WM_RBUTTONDOWN     : std::fprintf(stdout, "%c%X%s", '[', WM_RBUTTONDOWN,      "]: Windows > Right (Mouse) Button Down"                  "\r\n"); break;
      //   case WM_RBUTTONUP       : std::fprintf(stdout, "%c%X%s", '[', WM_RBUTTONUP,        "]: Windows > Right (Mouse) Button Up"                    "\r\n"); break;
      //   case WM_RCRESULT        : std::fprintf(stdout, "%c%X%s", '[', WM_RCRESULT,         "]: Windows > RC Result"                                  "\r\n"); break;
      //   case WM_RENDERALLFORMATS: std::fprintf(stdout, "%c%X%s", '[', WM_RENDERALLFORMATS, "]: Windows > Render All Formats"                         "\r\n"); break;
      //   case WM_RENDERFORMAT    : std::fprintf(stdout, "%c%X%s", '[', WM_RENDERFORMAT,     "]: Windows > Render Format"                              "\r\n"); break;
      //   case WM_SETCURSOR       : std::fprintf(stdout, "%c%X%s", '[', WM_SETCURSOR,        "]: Windows > Set Cursor"                                 "\r\n"); break;
      //   case WM_SETFOCUS        : std::fprintf(stdout, "%c%X%s", '[', WM_SETFOCUS,         "]: Windows > Set Focus"                                  "\r\n"); break;
      //   case WM_SETFONT         : std::fprintf(stdout, "%c%X%s", '[', WM_SETFONT,          "]: Windows > Set Font"                                   "\r\n"); break;
      //   case WM_SETHOTKEY       : std::fprintf(stdout, "%c%X%s", '[', WM_SETHOTKEY,        "]: Windows > Set Hotkey"                                 "\r\n"); break;
      //   case WM_SETICON         : std::fprintf(stdout, "%c%X%s", '[', WM_SETICON,          "]: Windows > Set Icon"                                   "\r\n"); break;
      //   case WM_SETREDRAW       : std::fprintf(stdout, "%c%X%s", '[', WM_SETREDRAW,        "]: Windows > Set Redraw"                                 "\r\n"); break;
      //   case WM_SETTEXT         : std::fprintf(stdout, "%c%X%s", '[', WM_SETTEXT,          "]: Windows > Set Text"                                   "\r\n"); break;
      //   case WM_SHOWWINDOW      : std::fprintf(stdout, "%c%X%s", '[', WM_SHOWWINDOW,       "]: Windows > Show Window"                                "\r\n"); break;
      //   case WM_SIZE            : std::fprintf(stdout, "%c%X%s", '[', WM_SIZE,             "]: Windows > Size"                                       "\r\n"); break;
      //   case WM_SIZECLIPBOARD   : std::fprintf(stdout, "%c%X%s", '[', WM_SIZECLIPBOARD,    "]: Windows > Size Clipboard"                             "\r\n"); break;
      //   case WM_SIZING          : std::fprintf(stdout, "%c%X%s", '[', WM_SIZING,           "]: Windows > Sizing"                                     "\r\n"); break;
      //   case WM_SKB             : std::fprintf(stdout, "%c%X%s", '[', WM_SKB,              "]: Windows > SketchUp Backup"                            "\r\n"); break;
      //   case WM_SPOOLERSTATUS   : std::fprintf(stdout, "%c%X%s", '[', WM_SPOOLERSTATUS,    "]: Windows > Spooler Status"                             "\r\n"); break;
      //   case WM_STYLECHANGED    : std::fprintf(stdout, "%c%X%s", '[', WM_STYLECHANGED,     "]: Windows > Style Changed"                              "\r\n"); break;
      //   case WM_STYLECHANGING   : std::fprintf(stdout, "%c%X%s", '[', WM_STYLECHANGING,    "]: Windows > Style Changing"                             "\r\n"); break;
      //   case WM_SYNCPAINT       : std::fprintf(stdout, "%c%X%s", '[', WM_SYNCPAINT,        "]: Windows > Synchronized Paint"                         "\r\n"); break;
      //   case WM_SYSCHAR         : std::fprintf(stdout, "%c%X%s", '[', WM_SYSCHAR,          "]: Windows > System Character"                           "\r\n"); break;
      //   case WM_SYSCOLORCHANGE  : std::fprintf(stdout, "%c%X%s", '[', WM_SYSCOLORCHANGE,   "]: Windows > System Color Change"                        "\r\n"); break;
      //   case WM_SYSCOMMAND      : std::fprintf(stdout, "%c%X%s", '[', WM_SYSCOMMAND,       "]: Windows > System Command"                             "\r\n"); break;
      //   case WM_SYSDEADCHAR     : std::fprintf(stdout, "%c%X%s", '[', WM_SYSDEADCHAR,      "]: Windows > System Dead Character"                      "\r\n"); break;
      //   case WM_SYSKEYDOWN      : std::fprintf(stdout, "%c%X%s", '[', WM_SYSKEYDOWN,       "]: Windows > System Key Down"                            "\r\n"); break;
      //   case WM_SYSKEYUP        : std::fprintf(stdout, "%c%X%s", '[', WM_SYSKEYUP,         "]: Windows > System Key Up"                              "\r\n"); break;
      //   case WM_SYSTIMER        : std::fprintf(stdout, "%c%X%s", '[', WM_SYSTIMER,         "]: Windows > System Timer"                               "\r\n"); break;
      //   case WM_TCARD           : std::fprintf(stdout, "%c%X%s", '[', WM_TCARD,            "]: Windows > Text Card"                                  "\r\n"); break;
      //   case WM_TIMECHANGE      : std::fprintf(stdout, "%c%X%s", '[', WM_TIMECHANGE,       "]: Windows > Time Change"                                "\r\n"); break;
      //   case WM_TIMER           : std::fprintf(stdout, "%c%X%s", '[', WM_TIMER,            "]: Windows > Timer"                                      "\r\n"); break;
      //   case WM_UNDO            : std::fprintf(stdout, "%c%X%s", '[', WM_UNDO,             "]: Windows > Undo"                                       "\r\n"); break;
      //   // case WM_UNICHAR: break;
      //   case WM_UNINITMENUPOPUP: std::fprintf(stdout, "%c%X%s", '[', WM_UNINITMENUPOPUP, "]: Windows > Uninitiate Menu Pop-Up" "\r\n"); break;
      //   case WM_UPDATEUISTATE  : std::fprintf(stdout, "%c%X%s", '[', WM_UPDATEUISTATE,   "]: Windows > Update UI State"        "\r\n"); break;
      //   // case WM_USER: break;
      //   case WM_USERCHANGED      : std::fprintf(stdout, "%c%X%s", '[', WM_USERCHANGED,       "]: Windows > User Changed"              "\r\n"); break;
      //   case WM_VKEYTOITEM       : std::fprintf(stdout, "%c%X%s", '[', WM_VKEYTOITEM,        "]: Windows > Virtual Key to Item"       "\r\n"); break;
      //   case WM_VSCROLL          : std::fprintf(stdout, "%c%X%s", '[', WM_VSCROLL,           "]: Windows > Vertical Scroll"           "\r\n"); break;
      //   case WM_VSCROLLCLIPBOARD : std::fprintf(stdout, "%c%X%s", '[', WM_VSCROLLCLIPBOARD,  "]: Windows > Vertical Scroll Clipboard" "\r\n"); break;
      //   case WM_WINDOWPOSCHANGED : std::fprintf(stdout, "%c%X%s", '[', WM_WINDOWPOSCHANGED,  "]: Windows > Window Position Changed"   "\r\n"); break;
      //   case WM_WINDOWPOSCHANGING: std::fprintf(stdout, "%c%X%s", '[', WM_WINDOWPOSCHANGING, "]: Windows > Window Position Changing"  "\r\n"); break;
      //   case WM_WININICHANGE     : std::fprintf(stdout, "%c%X%s", '[', WM_WININICHANGE,      "]: Windows > Windows INI Change"        "\r\n"); break;
      //   // case WM_WNT_CONVERTREQUESTEX: break;
      //   // case WM_XBUTTONDBLCLK       : break;
      //   case WM_XBUTTONDOWN: std::fprintf(stdout, "%c%X%s", '[', WM_XBUTTONDOWN, "]: Windows > X Button Down" "\r\n"); break;
      //   case WM_XBUTTONUP  : std::fprintf(stdout, "%c%X%s", '[', WM_XBUTTONUP,   "]: Windows > X Button Up"   "\r\n"); break;
      //   default: std::fputs("[...]: ?" "\r\n", stdout); break;
      // }

      // ...
      return ::DefWindowProcW(handle, message, parameter, subparameter);
    }
  } window = {};

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
  window.classTemplate.lpfnWndProc   = &window.procedure;
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
