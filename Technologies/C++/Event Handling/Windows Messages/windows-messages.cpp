/* Import */
#include <stdlib.h> // Standard Library
#include <windows.h> // Windows
#  include <commctrl.h> // Common Controls
#  include "penwin.h" // Pen Windows
#  include <prsht.h> // Prop Sheet
#  include <richedit.h> // Rich Edit
#  include <shellapi.h> // Shell API
#  include "wfext.h" // Windows File Manager Extensions

/* Definition > ... */
#ifndef _INC_COMMCTRL /* `<commctrl.h>` */
#  define _INC_COMMCTRL

#  ifndef CBEM_GETEXTENDEDSTYLE
#     define CBEM_GETEXTENDEDSTYLE CBEM_GETEXSTYLE
#  else
#     ifndef CBEM_GETEXSTYLE
#          define CBEM_GETEXSTYLE CBEM_GETEXTENDEDSTYLE
#     endif
#  endif

#  ifndef CBEM_SETEXTENDEDSTYLE
#     define CBEM_SETEXTENDEDSTYLE CBEM_SETEXSTYLE
#  else
#     ifndef CBEM_SETEXSTYLE
#          define CBEM_SETEXSTYLE CBEM_SETEXTENDEDSTYLE
#     endif
#  endif

#  ifndef RB_BEGINDRAG
#     define RB_BEGINDRAG (WM_USER + 24)
#  endif

#  ifndef RB_DRAGMOVE
#     define RB_DRAGMOVE (WM_USER + 26)
#  endif

#  ifndef RB_ENDDRAG
#     define RB_ENDDRAG (WM_USER + 25)
#  endif

#  ifndef RB_GETBANDBORDERS // NOTE (Lapys) -> Returns as an Additional Message Parameter the amount of edges added to band a Message Parameter as an `LPRECT` pointer.
#     define RB_GETBANDBORDERS (WM_USER + 34)
#  endif

#  ifndef RB_GETBANDINFOA
#     define RB_GETBANDINFOA (WM_USER + 29)
#  endif

#  ifndef RB_GETBANDINFOW
#     define RB_GETBANDINFOW (WM_USER + 28)
#  endif

#  ifndef RB_GETBARHEIGHT
#     define RB_GETBARHEIGHT (WM_USER + 27)
#  endif

#  ifndef RB_GETBKCOLOR // NOTE (Lapys) -> Defaults to `CLR_NONE`.
#     define RB_GETBKCOLOR (WM_USER + 20)
#  endif

#  ifndef RB_GETPALETTE
#     define RB_GETPALETTE (WM_USER + 38)
#  endif

#  ifndef RB_GETRECT
#     define RB_GETRECT (WM_USER + 9)
#  endif

#  ifndef RB_GETTEXTCOLOR // NOTE (Lapys) -> Defaults to `0x00000000`
#     define RB_GETTEXTCOLOR (WM_USER + 22)
#  endif

#  ifndef RB_GETTOOLTIPS
#     define RB_GETTOOLTIPS (WM_USER + 17)
#  endif

#  ifndef RB_HITTEST
#     define RB_HITTEST (WM_USER + 8)
#  endif

#  ifndef RB_IDTOINDEX // NOTE (Lapys) -> The Message Parameter is an ID.
#     define RB_IDTOINDEX (WM_USER + 16)
#  endif

#  ifndef RB_MAXIMIZEBAND
#     define RB_MAXIMIZEBAND (WM_USER + 31)
#  endif

#  ifndef RB_MINIMIZEBAND
#     define RB_MINIMIZEBAND (WM_USER + 30)
#  endif

#  ifndef RB_MOVEBAND
#     define RB_MOVEBAND (WM_USER + 39)
#  endif

#  ifndef RB_PUSHCHEVRON
#     define RB_PUSHCHEVRON (WM_USER + 43)
#  endif

#  ifndef RB_SETBKCOLOR // NOTE (Lapys) -> Sets the default background color.
#     define RB_SETBKCOLOR (WM_USER + 19)
#  endif

#  ifndef RB_SETPALETTE
#     define RB_SETPALETTE (WM_USER + 37)
#  endif

#  ifndef RB_SETTEXTCOLOR
#     define RB_SETTEXTCOLOR (WM_USER + 21)
#  endif

#  ifndef RB_SETTOOLTIPS
#     define RB_SETTOOLTIPS (WM_USER + 18)
#  endif

#  ifndef RB_SHOWBAND // NOTE (Lapys) -> Hide or show band.
#     define RB_SHOWBAND (WM_USER + 35)
#  endif

#  ifndef RB_SIZETORECT // NOTE (Lapys) -> Resize the re-bar (or break bands) and such to this `RECT` structure as an Additional Message Parameter.
#     define RB_SIZETORECT (WM_USER + 23)
#  endif
#endif

#ifndef _INC_PENWIN /* `<penwin.h>` */
#  define _INC_PENWIN

#  ifndef IE_DOCOMMAND // NOTE (Lapys) -> Send command to Interactive Editor (I-Edit).
#     define IE_DOCOMMAND (IE_MSGFIRST + 50)
#  endif

#  ifndef IE_GETAPPDATA // NOTE (Lapys) -> Gets the user-defined datum.
#     define IE_GETAPPDATA (IE_MSGFIRST + 34)
#  endif

#  ifndef IE_GETBKGND // NOTE (Lapys) -> Gets the background options.
#     define IE_GETBKGND (IE_MSGFIRST + 6)
#  endif

#  ifndef IE_GETCOMMAND // NOTE (Lapys) -> Gets user command.
#     define IE_GETCOMMAND (IE_MSGFIRST + 51)
#  endif

#  ifndef IE_GETCOUNT // NOTE (Lapys) -> Gets count of strokes in Interactive Editor (I-Edit).
#     define IE_GETCOUNT (IE_MSGFIRST + 52)
#  endif

#  ifndef IE_GETDRAWOPTS // NOTE (Lapys) -> Gets the ink draw options.
#     define IE_GETDRAWOPTS (IE_MSGFIRST + 36)
#  endif

#  ifndef IE_GETERASERTIP // NOTE (Lapys) -> Gets the current eraser pen tip.
#     define IE_GETERASERTIP (IE_MSGFIRST + 4)
#  endif

#  ifndef IE_GETFORMAT // NOTE (Lapys) -> Gets format of stroke(s).
#     define IE_GETFORMAT (IE_MSGFIRST + 38)
#  endif

#  ifndef IE_GETGESTURE // NOTE (Lapys) -> Gets details on user gesture.
#     define IE_GETGESTURE (IE_MSGFIRST + 53)
#  endif

#  ifndef IE_GETGRIDORIGIN // NOTE (Lapys) -> Gets background grid origin.
#     define IE_GETGRIDORIGIN (IE_MSGFIRST + 8)
#  endif

#  ifndef IE_GETGRIDPEN // NOTE (Lapys) -> Gets background grid pen.
#     define IE_GETGRIDPEN (IE_MSGFIRST + 10)
#  endif

#  ifndef IE_GETGRIDSIZE // NOTE (Lapys) -> Gets background grid size.
#     define IE_GETGRIDSIZE (IE_MSGFIRST + 12)
#  endif

#  ifndef IE_GETINK // NOTE (Lapys) -> Gets ink from the control.
#     define IE_GETINK (IE_MSGFIRST + 0)
#  endif

#  ifndef IE_GETINKINPUT // NOTE (Lapys) -> Gets the ink input option.
#     define IE_GETINKINPUT (IE_MSGFIRST + 40)
#  endif

#  ifndef IE_GETINKRECT // NOTE (Lapys) -> Gets the rectangular boundaries of the ink.
#     define IE_GETINKRECT (IE_MSGFIRST + 16)
#  endif

#  ifndef IE_GETMENU // NOTE (Lapys) -> Gets handle to pop-up menu.
#     define IE_GETMENU (IE_MSGFIRST + 54)
#  endif

#  ifndef IE_GETMODE // NOTE (Lapys) -> Gets the current pen mode.
#     define IE_GETMODE (IE_MSGFIRST + 14)
#  endif

#  ifndef IE_GETNOTIFY // NOTE (Lapys) -> Gets the notification bits.
#     define IE_GETNOTIFY (IE_MSGFIRST + 42)
#  endif

#  ifndef IE_GETPAINTDC // NOTE (Lapys) -> Gets the device context handle for painting.
#     define IE_GETPAINTDC (IE_MSGFIRST + 55)
#  endif

#  ifndef IE_GETPDEVENT // NOTE (Lapys) -> Gets details of last "pd" event.
#     define IE_GETPDEVENT (IE_MSGFIRST + 56)
#  endif

#  ifndef IE_GETPENTIP // NOTE (Lapys) -> Gets the currently defined ink pen tip.
#     define IE_GETPENTIP (IE_MSGFIRST + 2)
#  endif

#  ifndef IE_GETRECOG // NOTE (Lapys) -> Gets recognition options.
#     define IE_GETRECOG (IE_MSGFIRST + 44)
#  endif

#  ifndef IE_GETSECURITY // NOTE (Lapys) -> Gets the security options.
#     define IE_GETSECURITY (IE_MSGFIRST + 46)
#  endif

#  ifndef IE_GETSEL // NOTE (Lapys) -> Gets selection status of a stroke.
#     define IE_GETSEL (IE_MSGFIRST + 48)
#  endif

#  ifndef IE_GETSELCOUNT // NOTE (Lapys) -> Gets count of selected strokes.
#     define IE_GETSELCOUNT (IE_MSGFIRST + 57)
#  endif

#  ifndef IE_GETSELITEMS // NOTE (Lapys) -> Gets indices of all selection strokes.
#     define IE_GETSELITEMS (IE_MSGFIRST + 58)
#  endif

#  ifndef IE_GETSTYLE // NOTE (Lapys) -> Gets Interactive Editor (I-Edit) control styles.
#     define IE_GETSTYLE (IE_MSGFIRST + 59)
#  endif

#  ifndef IE_MSGFIRST // NOTE (Lapys) -> Gets indices of all selection strokes.
#     define IE_MSGFIRST (WM_USER + 150) /* -> 0x496 == 1174 */
#  endif

#  ifndef IE_SETAPPDATA // NOTE (Lapys) -> Sets the user-defined data.
#     define IE_SETAPPDATA (IE_MSGFIRST + 35)
#  endif

#  ifndef IE_SETBKGND // NOTE (Lapys) -> Sets the background options.
#     define IE_SETBKGND (IE_MSGFIRST + 7)
#  endif

#  ifndef IE_SETDRAWOPTS // NOTE (Lapys) -> Sets the ink options.
#     define IE_SETDRAWOPTS (IE_MSGFIRST + 37)
#  endif

#  ifndef IE_SETERASERTIP // NOTE (Lapys) -> Sets the current eraser pen tip.
#     define IE_SETERASERTIP (IE_MSGFIRST + 5)
#  endif

#  ifndef IE_SETFORMAT // NOTE (Lapys) -> Sets format of stroke(s).
#     define IE_SETFORMAT (IE_MSGFIRST + 39)
#  endif

#  ifndef IE_SETGRIDORIGIN // NOTE (Lapys) -> Sets the background grid origin.
#     define IE_SETGRIDORIGIN (IE_MSGFIRST + 9)
#  endif

#  ifndef IE_SETGRIDPEN // NOTE (Lapys) -> Sets the background grid pen.
#     define IE_SETGRIDPEN (IE_MSGFIRST + 11)
#  endif

#  ifndef IE_SETGRIDSIZE // NOTE (Lapys) -> Sets the background grid size.
#     define IE_SETGRIDSIZE (IE_MSGFIRST + 13)
#  endif

#  ifndef IE_SETINK // NOTE (Lapys) -> Sets ink unto the control.
#     define IE_SETINK (IE_MSGFIRST + 1)
#  endif

#  ifndef IE_SETINKINPUT // NOTE (Lapys) -> Sets the ink input option.
#     define IE_SETINKINPUT (IE_MSGFIRST + 41)
#  endif

#  ifndef IE_SETMODE // NOTE (Lapys) -> Sets the current pen mode.
#     define IE_SETMODE (IE_MSGFIRST + 15)
#  endif

#  ifndef IE_SETNOTIFY // NOTE (Lapys) -> Sets the notification bits.
#     define IE_SETNOTIFY (IE_MSGFIRST + 43)
#  endif

#  ifndef IE_SETPENTIP // NOTE (Lapys) -> Sets the currently defined ink pen tip.
#     define IE_SETPENTIP (IE_MSGFIRST + 3)
#  endif

#  ifndef IE_SETRECOG // NOTE (Lapys) -> Sets recognition options.
#     define IE_SETRECOG (IE_MSGFIRST + 45)
#  endif

#  ifndef IE_SETSECURITY // NOTE (Lapys) -> Sets the security options.
#     define IE_SETSECURITY (IE_MSGFIRST + 47)
#  endif

#  ifndef IE_SETSEL // NOTE (Lapys) -> Sets selection status of a stroke.
#     define IE_SETSEL (IE_MSGFIRST + 49)
#  endif
#endif

#ifndef _INC_WFEXT /* `<wfext.h>` */
#  define _INC_WFEXT

#  ifndef FM_GETDRIVEINFOA
#     define FM_GETDRIVEINFOA (WM_USER + 0x0201)
#  endif

#  ifndef FM_GETDRIVEINFOW
#     define FM_GETDRIVEINFOW (WM_USER + 0x0211)
#  endif

#  ifndef FM_GETFILESELA
#     define FM_GETFILESELA (WM_USER + 0x0204)
#  endif

#  ifndef FM_GETFILESELLFNA // NOTE (Lapys) -> LFN (Long-File Names) versions are odd.
#     define FM_GETFILESELLFNA (WM_USER + 0x0205)
#  endif

#  ifndef FM_GETFILESELLFNW // NOTE (Lapys) -> LFN (Long-File Names) versions are odd.
#     define FM_GETFILESELLFNW (WM_USER + 0x0215)
#  endif

#  ifndef FM_GETFILESELW
#     define FM_GETFILESELW (WM_USER + 0x0214)
#  endif

#  ifndef FM_GETFOCUS
#     define FM_GETFOCUS (WM_USER + 0x0200)
#  endif

#  ifndef FM_GETSELCOUNT
#     define FM_GETSELCOUNT (WM_USER + 0x0202)
#  endif

#  ifndef FM_GETSELCOUNTLFN // NOTE (Lapys) -> LFN (Long-File Names) versions are odd.
#     define FM_GETSELCOUNTLFN (WM_USER + 0x0203)
#  endif

#  ifndef FM_REFRESH_WINDOWS
#     define FM_REFRESH_WINDOWS (WM_USER + 0x0206)
#  endif

#  ifndef FM_RELOAD_EXTENSIONS
#     define FM_RELOAD_EXTENSIONS (WM_USER + 0x0207)
#  endif
#endif

#ifndef _INC_VFW
#  define _INC_VFW

#  ifndef MCIWNDM_CAN_CONFIG
#     define MCIWNDM_CAN_CONFIG (WM_USER + 149)
#  endif

#  ifndef MCIWNDM_CAN_EJECT
#     define MCIWNDM_CAN_EJECT (WM_USER + 148)
#  endif

#  ifndef MCIWNDM_CAN_PLAY
#     define MCIWNDM_CAN_PLAY (WM_USER + 144)
#  endif

#  ifndef MCIWNDM_CAN_RECORD
#     define MCIWNDM_CAN_RECORD (WM_USER + 146)
#  endif

#  ifndef MCIWNDM_CAN_SAVE
#     define MCIWNDM_CAN_SAVE (WM_USER + 147)
#  endif

#  ifndef MCIWNDM_CAN_WINDOW
#     define MCIWNDM_CAN_WINDOW (WM_USER + 145)
#  endif

#  ifndef MCIWNDM_GETDEVICEA
#     define MCIWNDM_GETDEVICEA (WM_USER + 125)
#  endif

#  ifndef MCIWNDM_GETDEVICEW
#     define MCIWNDM_GETDEVICEW (WM_USER + 225)
#  endif

#  ifndef MCIWNDM_GETERRORA
#     define MCIWNDM_GETERRORA (WM_USER + 128)
#  endif

#  ifndef MCIWNDM_GETERRORW
#     define MCIWNDM_GETERRORW (WM_USER + 228)
#  endif

#  ifndef MCIWNDM_GETFILENAMEA
#     define MCIWNDM_GETFILENAMEA (WM_USER + 124)
#  endif

#  ifndef MCIWNDM_GETFILENAMEW
#     define MCIWNDM_GETFILENAMEW (WM_USER + 224)
#  endif

#  ifndef MCIWNDM_GETINACTIVETIMER
#     define MCIWNDM_GETINACTIVETIMER (WM_USER + 133)
#  endif

#  ifndef MCIWNDM_GETPALETTE
#     define MCIWNDM_GETPALETTE (WM_USER + 126)
#  endif

#  ifndef MCIWNDM_GETTIMEFORMATA
#     define MCIWNDM_GETTIMEFORMATA (WM_USER + 120)
#  endif

#  ifndef MCIWNDM_GETTIMEFORMATW
#     define MCIWNDM_GETTIMEFORMATW (WM_USER + 220)
#  endif

#  ifndef MCIWNDM_GETZOOM
#     define MCIWNDM_GETZOOM (WM_USER + 109)
#  endif

#  ifndef MCIWNDM_GET_DEST
#     define MCIWNDM_GET_DEST (WM_USER + 142)
#  endif

#  ifndef MCIWNDM_GET_SOURCE
#     define MCIWNDM_GET_SOURCE (WM_USER + 140)
#  endif

#  ifndef MCIWNDM_NOTIFYERROR // NOTE (Lapys) -> Message Parameter must be a `HWND` pointer and the Additional Message Parameter must be an error.
#     define MCIWNDM_NOTIFYERROR (WM_USER + 205)
#  endif

#  ifndef MCIWNDM_NOTIFYMEDIA // NOTE (Lapys) -> Message Parameter must be a `HWND` pointer and the Additional Message Parameter must be a function.
#     define MCIWNDM_NOTIFYMEDIA (WM_USER + 203)
#  endif

#  ifndef MCIWNDM_NOTIFYMODE // NOTE (Lapys) -> Message Parameter must be a `HWND` pointer and the Additional Message Parameter must be a mode.
#     define MCIWNDM_NOTIFYMODE (WM_USER + 200)
#  endif

#  ifndef MCIWNDM_PALETTEKICK
#     define MCIWNDM_PALETTEKICK (WM_USER + 150)
#  endif

#  ifndef MCIWNDM_PLAYTO
#     define MCIWNDM_PLAYTO (WM_USER + 123)
#  endif

#  ifndef MCIWNDM_PUT_DEST
#     define MCIWNDM_PUT_DEST (WM_USER + 143)
#  endif

#  ifndef MCIWNDM_PUT_SOURCE
#     define MCIWNDM_PUT_SOURCE (WM_USER + 141)
#  endif

#  ifndef MCIWNDM_REALIZE
#     define MCIWNDM_REALIZE (WM_USER + 118)
#  endif

#  ifndef MCIWNDM_SETINACTIVETIMER
#     define MCIWNDM_SETINACTIVETIMER (WM_USER + 131)
#  endif

#  ifndef MCIWNDM_SETPALETTE
#     define MCIWNDM_SETPALETTE (WM_USER + 127)
#  endif

#  ifndef MCIWNDM_SETTIMEFORMATA
#     define MCIWNDM_SETTIMEFORMATA (WM_USER + 119)
#  endif

#  ifndef MCIWNDM_SETTIMEFORMATW
#     define MCIWNDM_SETTIMEFORMATW (WM_USER + 219)
#  endif

#  ifndef MCIWNDM_VALIDATEMEDIA
#     define MCIWNDM_VALIDATEMEDIA (WM_USER + 121)
#  endif
#endif

#define MSG_FTS_JUMP_QWORD 0x0423
#define MSG_FTS_JUMP_VA 0x0421
#define MSG_FTS_WHERE_IS_IT 0x0425
#define MSG_GET_DEFFONT 0x042D
#define MSG_REINDEX_REQUEST 0x0424

#ifndef _INC_SHELLAPI /* `<shellapi.h>` */
#  define _INC_SHELLAPI

#  ifndef NIN_SELECT
#     define NIN_SELECT (WM_USER + 0)
#  endif
#endif

#define OCM__BASE (WM_USER + 0x1C00)
#define OCM_CHARTOITEM (OCM__BASE + WM_CHARTOITEM)
#define OCM_COMMAND (OCM__BASE + WM_COMMAND)
#define OCM_COMPAREITEM (OCM__BASE + WM_COMPAREITEM)
#define OCM_CTLCOLOR (OCM__BASE + WM_CTLCOLOR)
#define OCM_CTLCOLORBTN (OCM__BASE + WM_CTLCOLORBTN)
#define OCM_CTLCOLORDLG (OCM__BASE + WM_CTLCOLORDLG)
#define OCM_CTLCOLOREDIT (OCM__BASE + WM_CTLCOLOREDIT)
#define OCM_CTLCOLORLISTBOX (OCM__BASE + WM_CTLCOLORLISTBOX)
#define OCM_CTLCOLORMSGBOX (OCM__BASE + WM_CTLCOLORMSGBOX)
#define OCM_CTLCOLORSCROLLBAR (OCM__BASE + WM_CTLCOLORSCROLLBAR)
#define OCM_CTLCOLORSTATIC (OCM__BASE + WM_CTLCOLORSTATIC)
#define OCM_DELETEITEM (OCM__BASE + WM_DELETEITEM)
#define OCM_DRAWITEM (OCM__BASE + WM_DRAWITEM)
#define OCM_HSCROLL (OCM__BASE + WM_HSCROLL)
#define OCM_MEASUREITEM (OCM__BASE + WM_MEASUREITEM)
#define OCM_NOTIFY (OCM__BASE + WM_NOTIFY)
#define OCM_PARENTNOTIFY (OCM__BASE + WM_PARENTNOTIFY)
#define OCM_VKEYTOITEM (OCM__BASE + WM_VKEYTOITEM)
#define OCM_VSCROLL (OCM__BASE + WM_VSCROLL)

#ifndef _PRSHT_H_ /* `<prsht.h>` */
#  define _PRSHT_H_

#  ifndef PSM_GETRESULT
#     define PSM_GETRESULT (WM_USER + 135)
#  endif

#  ifndef PSM_HWNDTOINDEX
#     define PSM_HWNDTOINDEX (WM_USER + 129)
#  endif

#  ifndef PSM_IDTOINDEX
#     define PSM_IDTOINDEX (WM_USER + 133)
#  endif

#  ifndef PSM_INDEXTOHWND
#     define PSM_INDEXTOHWND (WM_USER + 130)
#  endif

#  ifndef PSM_INDEXTOID
#     define PSM_INDEXTOID (WM_USER + 134)
#  endif

#  ifndef PSM_INDEXTOPAGE
#     define PSM_INDEXTOPAGE (WM_USER + 132)
#  endif

#  ifndef PSM_INSERTPAGE
#     define PSM_INSERTPAGE (WM_USER + 119)
#  endif

#  ifndef PSM_PAGETOINDEX
#     define PSM_PAGETOINDEX (WM_USER + 131)
#  endif

#  ifndef PSM_RECALCPAGESIZES
#     define PSM_RECALCPAGESIZES (WM_USER + 136)
#  endif

#  ifndef PSM_SETHEADERSUBTITLEA
#     define PSM_SETHEADERSUBTITLEA (WM_USER + 127)
#  endif

#  ifndef PSM_SETHEADERSUBTITLEW
#     define PSM_SETHEADERSUBTITLEW (WM_USER + 128)
#  endif

#  ifndef PSM_SETHEADERTITLEA
#     define PSM_SETHEADERTITLEA (WM_USER + 125)
#  endif

#  ifndef PSM_SETHEADERTITLEW
#     define PSM_SETHEADERTITLEW (WM_USER + 126)
#  endif
#endif

#define WM_CTLCOLOR 0x0019

/* Function > Window Procedure */
LRESULT CALLBACK windowProcedure(HWND windowHandle, UINT message, WPARAM messageParameter, LPARAM additionalMessageParameter) {
    // Logic --- WARN (Lapys) -> These, of course are not all window messages.
    switch (message) {
        // [Window Manager ...]
        case ACM_OPENA /* -> CDM_FIRST || CDM_GETSPEC || EM_SETPUNCTUATION || IPM_CLEARADDRESS */: break;
        case ACM_OPENW /* -> CDM_GETFOLDERIDLIST || EM_GETWORDWRAPMODE || IPM_SETRANGE || PSM_ADDPAGE */: break;
        case ACM_PLAY /* -> CDM_GETFILEPATH || EM_GETPUNCTUATION || IPM_SETADDRESS */: break;
        case ACM_STOP /* -> CDM_GETFOLDERPATH || EM_SETWORDWRAPMODE || IPM_GETADDRESS || PSM_REMOVEPAGE */: break;
        case BM_CLICK: break;
        case BM_GETCHECK: break;
        case BM_GETIMAGE: break;
        case BM_GETSTATE: break;
        case BM_SETCHECK: break;
        case BM_SETIMAGE: break;
        case BM_SETSTATE: break;
        case BM_SETSTYLE: break;
        case CBEM_GETCOMBOCONTROL /* -> PBM_SETRANGE32 || RB_SETBANDINFOA */: break;
        case CBEM_GETEDITCONTROL /* -> IE_GETPAINTDC || PBM_GETRANGE || RB_SETPARENT */: break;
        case CBEM_GETEXSTYLE /* -> CBEM_GETEXTENDEDSTYLE || PBM_SETBARCOLOR || RB_GETRECT */: break;
        /*case CDM_GETFILEPATH: break;*/
        /*case CDM_GETFOLDERPATH: break;*/
        case CBEM_GETIMAGELIST /* -> HKM_SETRULES || PBM_DELTAPOS || RB_GETBARINFO */: break;
        case CBEM_GETITEMA /* -> PBM_SETSTEP || RB_SETBARINFO */: break;
        case CBEM_GETITEMW /* -> RB_GETROWCOUNT */: break;
        case CBEM_HASEDITCHANGED /* -> RB_INSERTBANDW */: break;
        case CBEM_INSERTITEMA /* -> DM_SETDEFID || HKM_SETHOTKEY || PBM_SETRANGE || RB_INSERTBANDA */: break;
        case CBEM_INSERTITEMW /* -> RB_SETBANDINFOW */: break;
        case CBEM_SETEXSTYLE /* -> CBEM_SETEXTENDEDSTYLE || PBM_GETPOS || RB_HITTEST */: break;
        case CBEM_SETIMAGELIST /* -> DM_REPOSITION || HKM_GETHOTKEY || PBM_SETPOS || RB_DELETEBAND */: break;
        case CBEM_SETITEMA /* -> PBM_STEPIT */: break;
        case CBEM_SETITEMW /* -> RB_GETBANDCOUNT */: break;
        /*case CDM_GETFOLDERIDLIST: break;*/
        case CDM_HIDECONTROL /* -> EM_GETIMECOLOR || IPM_ISBLANK || PSM_RESTARTWINDOWS */: break;
        /*case CDM_FIRST: break;*/
        /*case CDM_GETSPEC: break;*/
        case CDM_LAST /* -> EM_SETBIDIOPTIONS || IE_DOCOMMAND || MCIWNDM_NOTIFYMODE */: break;
        case CDM_SETCONTROLTEXT /* -> EM_SETIMECOLOR || IPM_SETFOCUS || PSM_CHANGED */: break;
        case CDM_SETDEFEXT /* -> EM_SETIMEOPTIONS || PSM_REBOOTSYSTEM */: break;
        case DL_BEGINDRAG /* -> MCIWNDM_GETINACTIVETIMER || PSM_IDTOINDEX */: break;
        case DL_CANCELDRAG /* -> PSM_RECALCPAGESIZES */: break;
        case DL_DRAGGING /* -> PSM_INDEXTOID */: break;
        case DL_DROPPED /* -> PSM_GETRESULT */: break;
        case DM_GETDEFID /* -> NIN_SELECT */: break;
        /*case DM_REPOSITION: break;*/
        /*case DM_SETDEFID: break;*/
        case EM_AUTOURLDETECT: break;
        case EM_CANPASTE: break;
        case EM_CANREDO: break;
        case EM_CANUNDO: break;
        case EM_CHARFROMPOS: break;
        case EM_DISPLAYBAND: break;
        case EM_EMPTYUNDOBUFFER: break;
        case EM_EXGETSEL: break;
        case EM_EXLIMITTEXT: break;
        case EM_EXLINEFROMCHAR: break;
        case EM_EXSETSEL: break;
        case EM_FINDTEXT: break;
        case EM_FINDTEXTEX: break;
        case EM_FINDTEXTEXW /* -> MCIWNDM_GETFILENAMEA */: break;
        case EM_FINDTEXTW /* -> MCIWNDM_PLAYTO */: break;
        case EM_FINDWORDBREAK: break;
        case EM_FMTLINES: break;
        case EM_FORMATRANGE: break;
        case EM_GETAUTOURLDETECT: break;
        case EM_GETBIDIOPTIONS /* -> IE_GETCOMMAND */: break;
        case EM_GETCHARFORMAT: break;
        case EM_GETEDITSTYLE /* -> MCIWNDM_NOTIFYERROR */: break;
        case EM_GETEVENTMASK: break;
        case EM_GETFIRSTVISIBLELINE: break;
        case EM_GETHANDLE: break;
        /*case EM_GETIMECOLOR: break;*/
        case EM_GETIMECOMPMODE: break;
        case EM_GETIMEOPTIONS /* -> PSM_CANCELTOCLOSE */: break;
        case EM_GETIMESTATUS: break;
        case EM_GETLANGOPTIONS /* -> MCIWNDM_VALIDATEMEDIA || PSM_SETCURSEL || PSM_SETFINISHTEXTA || PSM_SETFINISHTEXTW */: break;
        case EM_GETLIMITTEXT: break;
        case EM_GETLINE: break;
        case EM_GETLINECOUNT: break;
        case EM_GETMARGINS: break;
        case EM_GETMODIFY: break;
        case EM_GETOLEINTERFACE: break;
        case EM_GETOPTIONS: break;
        /*case EM_GETPAGE: break;*/
        /*case EM_GETPAGEROTATE: break;*/
        case EM_GETPARAFORMAT: break;
        case EM_GETPASSWORDCHAR: break;
        /*case EM_GETPUNCTUATION: break;*/
        /*case EM_GETQUERYRTFOBJ: break;*/
        case EM_GETRECT: break;
        case EM_GETREDONAME: break;
        case EM_GETSCROLLPOS: break;
        case EM_GETSEL: break;
        case EM_GETSELTEXT: break;
        case EM_GETTEXTEX: break;
        case EM_GETTEXTLENGTHEX: break;
        case EM_GETTEXTMODE: break;
        case EM_GETTEXTRANGE: break;
        case EM_GETTHUMB: break;
        case EM_GETTYPOGRAPHYOPTIONS /* -> IE_GETGESTURE || MCIWNDM_NOTIFYMEDIA */: break;
        case EM_GETUNDONAME: break;
        /*case EM_GETVIEWKIND: break;*/
        case EM_GETWORDBREAKPROC: break;
        case EM_GETWORDBREAKPROCEX: break;
        /*case EM_GETWORDWRAPMODE: break;*/
        case EM_GETZOOM /* -> MCIWNDM_GETFILENAMEW */: break;
        case EM_HIDESELECTION: break;
        /*case EM_ISIME: break;*/
        case EM_LIMITTEXT /* -> EM_SETLIMITTEXT */: break;
        case EM_LINEFROMCHAR: break;
        case EM_LINEINDEX: break;
        case EM_LINELENGTH: break;
        case EM_LINESCROLL: break;
        /*case EM_OUTLINE: break;*/
        case EM_PASTESPECIAL: break;
        case EM_POSFROMCHAR: break;
        case EM_RECONVERSION /* -> MCIWNDM_GETDEVICEA || PSM_SETHEADERTITLEA */: break;
        case EM_REDO: break;
        case EM_REPLACESEL: break;
        case EM_REQUESTRESIZE: break;
        case EM_SCROLL: break;
        case EM_SCROLLCARET: break;
        case EM_SELECTIONTYPE: break;
        /*case EM_SETBIDIOPTIONS: break;*/
        case EM_SETBKGNDCOLOR: break;
        case EM_SETCHARFORMAT: break;
        /*case EM_SETCTFMODEBIAS: break;*/
        /*case EM_SETCTFOPENSTATUS: break;*/
        case EM_SETEDITSTYLE /* -> IE_GETMENU */: break;
        case EM_SETEVENTMASK: break;
        /*case EM_SETFONT: break;*/
        case EM_SETFONTSIZE: break;
        case EM_SETHANDLE: break;
        /*case EM_SETHYPHENATEINFO: break;*/
        /*case EM_SETIMECOLOR: break;*/
        /*case EM_SETIMEMODEBIAS: break;*/
        /*case EM_SETIMEOPTIONS: break;*/
        case EM_SETIMESTATUS: break;
        case EM_SETLANGOPTIONS /* -> MCIWNDM_GETTIMEFORMATA || PSM_SETTITLEW */: break;
        case EM_SETMARGINS: break;
        case EM_SETMODIFY: break;
        /*case EM_SETLIMITTEXT: break;*/
        case EM_SETOLECALLBACK: break;
        case EM_SETOPTIONS: break;
        /*case EM_SETPAGE: break;*/
        /*case EM_SETPAGEROTATE: break;*/
        case EM_SETPALETTE: break;
        case EM_SETPARAFORMAT: break;
        case EM_SETPASSWORDCHAR: break;
        /*case EM_SETPUNCTUATION: break*/
        /*case EM_SETQUERYRTFOBJ: break;*/
        case EM_SETREADONLY: break;
        case EM_SETRECT: break;
        case EM_SETRECTNP: break;
        case EM_SETSCROLLPOS: break;
        case EM_SETSEL: break;
        case EM_SETTABSTOPS: break;
        case EM_SETTARGETDEVICE: break;
        case EM_SETTEXTEX: break;
        case EM_SETTEXTMODE: break;
        case EM_SETTYPOGRAPHYOPTIONS /* -> IE_GETCOUNT */: break;
        case EM_SETUNDOLIMIT: break;
        /*case EM_SETVIEWKIND: break;*/
        /*case EM_SETWORDBREAK: break;*/
        case EM_SETWORDBREAKPROC: break;
        case EM_SETWORDBREAKPROCEX: break;
        /*case EM_SETWORDWRAPMODE: break;*/
        case EM_SETZOOM /* -> MCIWNDM_GETDEVICEW */: break;
        case EM_SHOWSCROLLBAR: break;
        case EM_STOPGROUPTYPING: break;
        case EM_STREAMIN: break;
        case EM_STREAMOUT: break;
        case EM_UNDO: break;
        case FM_GETDRIVEINFOA: break;
        case FM_GETDRIVEINFOW: break;
        case FM_GETFILESELA: break;
        case FM_GETFILESELLFNA: break;
        case FM_GETFILESELLFNW: break;
        case FM_GETFILESELW: break;
        case FM_GETFOCUS: break;
        case FM_GETSELCOUNT: break;
        case FM_GETSELCOUNTLFN: break;
        case FM_REFRESH_WINDOWS: break;
        case FM_RELOAD_EXTENSIONS: break;
        /*case HKM_GETHOTKEY: break;*/
        /*case HKM_SETHOTKEY: break;*/
        /*case HKM_SETRULES: break;*/
        /*case IE_DOCOMMAND: break;*/
        case IE_GETAPPDATA: break;
        case IE_GETBKGND: break;
        /*case IE_GETCOMMAND: break;*/
        /*case IE_GETCOUNT: break;*/
        case IE_GETDRAWOPTS: break;
        case IE_GETERASERTIP: break;
        case IE_GETFORMAT: break;
        /*case IE_GETGESTURE: break;*/
        case IE_GETGRIDORIGIN: break;
        case IE_GETGRIDPEN: break;
        case IE_GETGRIDSIZE: break;
        case IE_GETINK /* -> IE_MSGFIRST || MCIWNDM_PALETTEKICK */: break;
        case IE_GETINKINPUT: break;
        case IE_GETINKRECT: break;
        /*case IE_GETMENU: break;*/
        case IE_GETMODE: break;
        case IE_GETNOTIFY: break;
        /*case IE_GETPAINTDC: break;*/
        case IE_GETPDEVENT: break;
        case IE_GETPENTIP: break;
        case IE_GETRECOG: break;
        case IE_GETSECURITY: break;
        case IE_GETSEL: break;
        case IE_GETSELCOUNT: break;
        case IE_GETSELITEMS: break;
        case IE_GETSTYLE: break;
        /*case IE_MSGFIRST: break;*/
        case IE_SETAPPDATA: break;
        case IE_SETBKGND: break;
        case IE_SETDRAWOPTS: break;
        case IE_SETERASERTIP: break;
        case IE_SETFORMAT: break;
        case IE_SETGRIDORIGIN: break;
        case IE_SETGRIDPEN: break;
        case IE_SETGRIDSIZE: break;
        case IE_SETINK: break;
        case IE_SETINKINPUT: break;
        case IE_SETMODE: break;
        case IE_SETNOTIFY: break;
        case IE_SETPENTIP: break;
        case IE_SETRECOG: break;
        case IE_SETSECURITY: break;
        case IE_SETSEL: break;
        /*case IPM_CLEARADDRESS: break;*/
        /*case IPM_GETADDRESS: break;*/
        /*case IPM_ISBLANK: break;*/
        /*case IPM_SETADDRESS: break;*/
        /*case IPM_SETFOCUS: break;*/
        /*case IPM_SETRANGE: break;*/
        /*case LVM_APPROXIMATEVIEWRECT: break;*/
        case LVM_ARRANGE: break;
        case LVM_CANCELEDITLABEL: break;
        case LVM_CREATEDRAGIMAGE: break;
        case LVM_DELETEALLITEMS: break;
        case LVM_DELETECOLUMN: break;
        case LVM_DELETEITEM: break;
        case LVM_EDITLABELA: break;
        case LVM_EDITLABELW: break;
        case LVM_ENABLEGROUPVIEW: break;
        case LVM_ENSUREVISIBLE: break;
        case LVM_FINDITEMA: break;
        case LVM_FINDITEMW: break;
        case LVM_FIRST /* -> LVM_GETBKCOLOR */: break;
        /*case LVM_GETBKCOLOR: break;*/
        /*case LVM_GETBKIMAGEA: break;*/
        /*case LVM_GETBKIMAGEW: break;*/
        case LVM_GETCALLBACKMASK: break;
        case LVM_GETCOLUMNA: break;
        /*case LVM_GETCOLUMNORDERARRAY: break;*/
        case LVM_GETCOLUMNW: break;
        case LVM_GETCOLUMNWIDTH: break;
        case LVM_GETCOUNTPERPAGE: break;
        case LVM_GETEDITCONTROL: break;
        /*case LVM_GETEXTENDEDLISTVIEWSTYLE: break;*/
        case LVM_GETGROUPINFO: break;
        case LVM_GETGROUPMETRICS: break;
        /*case LVM_GETHEADER: break;*/
        /*case LVM_GETHOTCURSOR: break;*/
        /*case LVM_GETHOTITEM: break;*/
        /*case LVM_GETHOVERTIME: break;*/
        case LVM_GETIMAGELIST: break;
        case LVM_GETINSERTMARK: break;
        case LVM_GETINSERTMARKCOLOR: break;
        case LVM_GETINSERTMARKRECT: break;
        case LVM_GETISEARCHSTRINGA: break;
        case LVM_GETISEARCHSTRINGW: break;
        case LVM_GETITEMA: break;
        case LVM_GETITEMCOUNT: break;
        case LVM_GETITEMPOSITION: break;
        case LVM_GETITEMRECT: break;
        case LVM_GETITEMSPACING: break;
        case LVM_GETITEMSTATE: break;
        case LVM_GETITEMTEXTA: break;
        case LVM_GETITEMTEXTW: break;
        case LVM_GETITEMW: break;
        case LVM_GETNEXTITEM: break;
        /*case LVM_GETNUMBEROFWORKAREAS: break;*/
        case LVM_GETORIGIN: break;
        case LVM_GETOUTLINECOLOR: break;
        case LVM_GETSELECTEDCOLUMN: break;
        case LVM_GETSELECTEDCOUNT: break;
        /*case LVM_GETSELECTIONMARK: break;*/
        case LVM_GETSTRINGWIDTHA: break;
        case LVM_GETSTRINGWIDTHW: break;
        /*case LVM_GETSUBITEMRECT: break;*/
        case LVM_GETTEXTBKCOLOR: break;
        case LVM_GETTEXTCOLOR: break;
        case LVM_GETTILEINFO: break;
        case LVM_GETTILEVIEWINFO: break;
        /*case LVM_GETTOOLTIPS: break;*/
        case LVM_GETTOPINDEX: break;
        /*case LVM_GETUNICODEFORMAT: break;*/
        case LVM_GETVIEW: break;
        case LVM_GETVIEWRECT: break;
        /*case LVM_GETWORKAREAS: break;*/
        case LVM_HASGROUP: break;
        case LVM_HITTEST: break;
        case LVM_INSERTCOLUMNA: break;
        case LVM_INSERTCOLUMNW: break;
        case LVM_INSERTGROUP: break;
        case LVM_INSERTGROUPSORTED: break;
        case LVM_INSERTITEMA: break;
        case LVM_INSERTITEMW: break;
        case LVM_INSERTMARKHITTEST: break;
        case LVM_ISGROUPVIEWENABLED: break;
        /*case LVM_ISITEMVISIBLE: break;*/
        case LVM_MAPIDTOINDEX: break;
        /*case LVM_MAPINDEXTOID: break;*/
        case LVM_MOVEGROUP: break;
        /*case LVM_MOVEITEMTOGROUP: break;*/
        case LVM_REDRAWITEMS: break;
        case LVM_REMOVEALLGROUPS: break;
        case LVM_REMOVEGROUP: break;
        case LVM_SCROLL: break;
        case LVM_SETBKCOLOR: break;
        /*case LVM_SETBKIMAGEA: break;*/
        case LVM_SETCALLBACKMASK: break;
        case LVM_SETCOLUMNA: break;
        /*case LVM_SETCOLUMNORDERARRAY: break;*/
        case LVM_SETCOLUMNW: break;
        case LVM_SETCOLUMNWIDTH: break;
        /*case LVM_SETEXTENDEDLISTVIEWSTYLE: break;*/
        case LVM_SETGROUPINFO: break;
        case LVM_SETGROUPMETRICS: break;
        /*case LVM_SETHOTCURSOR: break;*/
        /*case LVM_SETHOTITEM: break;*/
        /*case LVM_SETHOVERTIME: break;*/
        /*case LVM_SETICONSPACING: break;*/
        case LVM_SETIMAGELIST: break;
        case LVM_SETINFOTIP: break;
        case LVM_SETINSERTMARK: break;
        case LVM_SETINSERTMARKCOLOR: break;
        case LVM_SETITEMA: break;
        case LVM_SETITEMCOUNT: break;
        case LVM_SETITEMPOSITION: break;
        case LVM_SETITEMPOSITION32: break;
        case LVM_SETITEMSTATE: break;
        case LVM_SETITEMTEXTA: break;
        case LVM_SETITEMTEXTW: break;
        case LVM_SETITEMW: break;
        case LVM_SETOUTLINECOLOR: break;
        /*case LVM_SETSELECTEDCOLUMN: break;*/
        /*case LVM_SETSELECTIONMARK: break;*/
        case LVM_SETTEXTBKCOLOR: break;
        case LVM_SETTEXTCOLOR: break;
        case LVM_SETTILEINFO: break;
        case LVM_SETTILEVIEWINFO: break;
        /*case LVM_SETTILEWIDTH: break;*/
        /*case LVM_SETTOOLTIPS: break;*/
        /*case LVM_SETUNICODEFORMAT: break;*/
        case LVM_SETVIEW: break;
        /*case LVM_SETWORKAREAS: break;*/
        case LVM_SORTGROUPS: break;
        case LVM_SORTITEMS: break;
        /*case LVM_SUBITEMHITTEST: break;*/
        case LVM_UPDATE: break;
        case MCIWNDM_CAN_CONFIG: break;
        case MCIWNDM_CAN_EJECT: break;
        case MCIWNDM_CAN_PLAY: break;
        case MCIWNDM_CAN_RECORD: break;
        case MCIWNDM_CAN_SAVE: break;
        case MCIWNDM_CAN_WINDOW: break;
        /*case MCIWNDM_GETDEVICEA: break;*/
        /*case MCIWNDM_GETDEVICEW: break;*/
        case MCIWNDM_GETERRORA /* -> PSM_SETHEADERSUBTITLEW */: break;
        case MCIWNDM_GETERRORW: break;
        /*case MCIWNDM_GETFILENAMEA: break;*/
        /*case MCIWNDM_GETFILENAMEW: break;*/
        /*case MCIWNDM_GETINACTIVETIMER: break;*/
        case MCIWNDM_GETPALETTE /* -> PSM_SETHEADERTITLEW */: break;
        /*case MCIWNDM_GETTIMEFORMATA: break;*/
        case MCIWNDM_GETTIMEFORMATW: break;
        case MCIWNDM_GETZOOM /* -> PSM_UNCHANGED */: break;
        case MCIWNDM_GET_DEST: break;
        case MCIWNDM_GET_SOURCE: break;
        /*case MCIWNDM_NOTIFYERROR: break;*/
        /*case MCIWNDM_NOTIFYMEDIA: break;*/
        /*case MCIWNDM_NOTIFYMODE: break;*/
        /*case MCIWNDM_PALETTEKICK: break;*/
        /*case MCIWNDM_PLAYTO: break;*/
        case MCIWNDM_PUT_DEST: break;
        case MCIWNDM_PUT_SOURCE: break;
        case MCIWNDM_REALIZE /* -> PSM_GETCURRENTPAGEHWND */: break;
        case MCIWNDM_SETINACTIVETIMER /* -> PSM_PAGETOINDEX */: break;
        case MCIWNDM_SETPALETTE /* -> PSM_SETHEADERSUBTITLEA */: break;
        case MCIWNDM_SETTIMEFORMATA /* -> PSM_INSERTPAGE */: break;
        case MCIWNDM_SETTIMEFORMATW: break;
        /*case MCIWNDM_VALIDATEMEDIA: break;*/
        case MSG_FTS_JUMP_QWORD /* -> RB_SHOWBAND */: break;
        case MSG_FTS_JUMP_VA: break;
        case MSG_FTS_WHERE_IS_IT /* -> RB_SETPALETTE */: break;
        case MSG_GET_DEFFONT: break;
        case MSG_REINDEX_REQUEST: break;
        /*case NIN_SELECT: break;*/
        case OCM_CHARTOITEM: break;
        case OCM_COMMAND: break;
        case OCM_COMPAREITEM: break;
        case OCM_CTLCOLOR: break;
        case OCM_CTLCOLORBTN: break;
        case OCM_CTLCOLORDLG: break;
        case OCM_CTLCOLOREDIT: break;
        case OCM_CTLCOLORLISTBOX: break;
        case OCM_CTLCOLORMSGBOX: break;
        case OCM_CTLCOLORSCROLLBAR: break;
        case OCM_CTLCOLORSTATIC: break;
        case OCM_DELETEITEM: break;
        case OCM_DRAWITEM: break;
        case OCM_HSCROLL: break;
        case OCM_MEASUREITEM: break;
        case OCM_NOTIFY: break;
        case OCM_PARENTNOTIFY: break;
        case OCM_VKEYTOITEM: break;
        case OCM_VSCROLL: break;
        case OCM__BASE: break;
        /*case PBM_DELTAPOS: break;*/
        /*case PBM_GETPOS: break;*/
        /*case PBM_GETRANGE: break;*/
        /*case PBM_SETBARCOLOR: break;*/
        /*case PBM_SETPOS: break;*/
        /*case PBM_SETRANGE: break;*/
        /*case PBM_SETRANGE32: break;*/
        /*case PBM_SETSTEP: break;*/
        /*case PBM_STEPIT: break;*/
        /*case PSM_ADDPAGE: break;*/
        case PSM_APPLY: break;
        /*case PSM_CANCELTOCLOSE: break;*/
        /*case PSM_CHANGED: break;*/
        /*case PSM_GETCURRENTPAGEHWND: break;*/
        /*case PSM_GETRESULT: break;*/
        case PSM_GETTABCONTROL: break;
        case PSM_HWNDTOINDEX: break;
        /*case PSM_IDTOINDEX: break;*/
        case PSM_INDEXTOHWND: break;
        /*case PSM_INDEXTOID: break;*/
        case PSM_INDEXTOPAGE: break;
        /*case PSM_INSERTPAGE: break;*/
        case PSM_ISDIALOGMESSAGE: break;
        /*case PSM_PAGETOINDEX: break;*/
        case PSM_PRESSBUTTON: break;
        case PSM_QUERYSIBLINGS: break;
        /*case PSM_REBOOTSYSTEM: break;*/
        /*case PSM_RECALCPAGESIZES: break;*/
        /*case PSM_REMOVEPAGE: break;*/
        /*case PSM_RESTARTWINDOWS: break;*/
        /*case PSM_SETCURSEL: break;*/
        case PSM_SETCURSELID: break;
        /*case PSM_SETFINISHTEXTA: break;*/
        /*case PSM_SETFINISHTEXTW: break;*/
        /*case PSM_SETHEADERSUBTITLEA: break;*/
        /*case PSM_SETHEADERSUBTITLEW: break;*/
        /*case PSM_SETHEADERTITLEA: break;*/
        /*case PSM_SETHEADERTITLEW: break;*/
        case PSM_SETTITLEA: break;
        /*case PSM_SETTITLEW: break;*/
        case PSM_SETWIZBUTTONS: break;
        /*case PSM_UNCHANGED: break;*/
        case RB_BEGINDRAG: break;
        /*case RB_DELETEBAND: break;*/
        case RB_DRAGMOVE: break;
        case RB_ENDDRAG: break;
        case RB_GETBANDBORDERS: break;
        /*case RB_GETBANDCOUNT: break;*/
        case RB_GETBANDINFOA: break;
        case RB_GETBANDINFOW: break;
        case RB_GETBARHEIGHT: break;
        /*case RB_GETBARINFO: break;*/
        case RB_GETBKCOLOR: break;
        case RB_GETPALETTE: break;
        /*case RB_GETRECT: break;*/
        /*case RB_GETROWCOUNT: break;*/
        case RB_GETROWHEIGHT: break;
        case RB_GETTEXTCOLOR: break;
        case RB_GETTOOLTIPS: break;
        /*case RB_HITTEST: break;*/
        case RB_IDTOINDEX: break;
        /*case RB_INSERTBANDA: break;*/
        /*case RB_INSERTBANDW: break;*/
        case RB_MAXIMIZEBAND: break;
        case RB_MINIMIZEBAND: break;
        case RB_MOVEBAND: break;
        case RB_PUSHCHEVRON: break;
        /*case RB_SETBANDINFOA: break;*/
        /*case RB_SETBANDINFOW: break;*/
        /*case RB_SETBARINFO: break;*/
        case RB_SETBKCOLOR: break;
        /*case RB_SETPALETTE: break;*/
        /*case RB_SETPARENT: break;*/
        case RB_SETTEXTCOLOR: break;
        case RB_SETTOOLTIPS: break;
        /*case RB_SHOWBAND: break;*/
        case RB_SIZETORECT: break;
        // case SBM_ENABLE_ARROWS: break;
        // case SBM_GETPOS: break;
        // case SBM_GETRANGE: break;
        // case SBM_GETSCROLLBARINFO: break;
        // case SBM_GETSCROLLINFO: break;
        // case SBM_SETPOS: break;
        // case SBM_SETRANGE: break;
        // case SBM_SETRANGEREDRAW: break;
        // case SBM_SETSCROLLINFO: break;
        // case SB_GETBORDERS: break;
        // case SB_GETICON: break;
        // case SB_GETPARTS: break;
        // case SB_GETRECT: break;
        // case SB_GETTEXTA: break;
        // case SB_GETTEXTLENGTHA: break;
        // case SB_GETTEXTLENGTHW: break;
        // case SB_GETTEXTW: break;
        // case SB_GETTIPTEXTA: break;
        // case SB_GETTIPTEXTW: break;
        // case SB_ISSIMPLE: break;
        // case SB_SETICON: break;
        // case SB_SETMINHEIGHT: break;
        // case SB_SETPARTS: break;
        // case SB_SETTEXTA: break;
        // case SB_SETTEXTW: break;
        // case SB_SETTIPTEXTA: break;
        // case SB_SETTIPTEXTW: break;
        // case SB_SIMPLE: break;
        // case SM_GETCURFOCUSA: break;
        // case SM_GETCURFOCUSW: break;
        // case SM_GETOPTIONS: break;
        // case SM_GETSELCOUNT: break;
        // case SM_GETSERVERSELA: break;
        // case SM_GETSERVERSELW: break;
        // case TAPI_REPLY: break;
        // case TBM_CLEARSEL: break;
        // case TBM_CLEARTICS: break;
        // case TBM_GETBUDDY: break;
        // case TBM_GETCHANNELRECT: break;
        // case TBM_GETLINESIZE: break;
        // case TBM_GETNUMTICS: break;
        // case TBM_GETPAGESIZE: break;
        // case TBM_GETPOS: break;
        // case TBM_GETPTICS: break;
        // case TBM_GETRANGEMAX: break;
        // case TBM_GETRANGEMIN: break;
        // case TBM_GETSELEND: break;
        // case TBM_GETSELSTART: break;
        // case TBM_GETTHUMBLENGTH: break;
        // case TBM_GETTHUMBRECT: break;
        // case TBM_GETTIC: break;
        // case TBM_GETTICPOS: break;
        // case TBM_GETTOOLTIPS: break;
        // case TBM_SETBUDDY: break;
        // case TBM_SETLINESIZE: break;
        // case TBM_SETPAGESIZE: break;
        // case TBM_SETPOS: break;
        // case TBM_SETRANGE: break;
        // case TBM_SETRANGEMAX: break;
        // case TBM_SETRANGEMIN: break;
        // case TBM_SETSEL: break;
        // case TBM_SETSELEND: break;
        // case TBM_SETSELSTART: break;
        // case TBM_SETTHUMBLENGTH: break;
        // case TBM_SETTIC: break;
        // case TBM_SETTICFREQ: break;
        // case TBM_SETTIPSIDE: break;
        // case TBM_SETTOOLTIPS: break;
        // case TB_ADDBITMAP: break;
        // case TB_ADDBUTTONSA: break;
        // case TB_ADDBUTTONSW: break;
        // case TB_ADDSTRINGA: break;
        // case TB_ADDSTRINGW: break;
        // case TB_AUTOSIZE: break;
        // case TB_BUTTONCOUNT: break;
        // case TB_BUTTONSTRUCTSIZE: break;
        // case TB_CHANGEBITMAP: break;
        // case TB_CHECKBUTTON: break;
        // case TB_COMMANDTOINDEX: break;
        // case TB_CUSTOMIZE: break;
        // case TB_DELETEBUTTON: break;
        // case TB_ENABLEBUTTON: break;
        // case TB_GETANCHORHIGHLIGHT: break;
        // case TB_GETBITMAP: break;
        // case TB_GETBITMAPFLAGS: break;
        // case TB_GETBUTTON: break;
        // case TB_GETBUTTONINFOA: break;
        // case TB_GETBUTTONINFOW: break;
        // case TB_GETBUTTONSIZE: break;
        // case TB_GETBUTTONTEXTA: break;
        // case TB_GETBUTTONTEXTW: break;
        // case TB_GETDISABLEDIMAGELIST: break;
        // case TB_GETEXTENDEDSTYLE: break;
        // case TB_GETHOTIMAGELIST: break;
        // case TB_GETHOTITEM: break;
        // case TB_GETIMAGELIST: break;
        // case TB_GETINSERTMARK: break;
        // case TB_GETINSERTMARKCOLOR: break;
        // case TB_GETITEMRECT: break;
        // case TB_GETMAXSIZE: break;
        // case TB_GETOBJECT: break;
        // case TB_GETPADDING: break;
        // case TB_GETRECT: break;
        // case TB_GETROWS: break;
        // case TB_GETSTATE: break;
        // case TB_GETSTRINGA: break;
        // case TB_GETSTRINGW: break;
        // case TB_GETSTYLE: break;
        // case TB_GETTEXTROWS: break;
        // case TB_GETTOOLTIPS: break;
        // case TB_HIDEBUTTON: break;
        // case TB_HITTEST: break;
        // case TB_INDETERMINATE: break;
        // case TB_INSERTBUTTONA: break;
        // case TB_INSERTBUTTONW: break;
        // case TB_INSERTMARKHITTEST: break;
        // case TB_ISBUTTONCHECKED: break;
        // case TB_ISBUTTONENABLED: break;
        // case TB_ISBUTTONHIDDEN: break;
        // case TB_ISBUTTONHIGHLIGHTED: break;
        // case TB_ISBUTTONINDETERMINATE: break;
        // case TB_ISBUTTONPRESSED: break;
        // case TB_LOADIMAGES: break;
        // case TB_MAPACCELERATORA: break;
        // case TB_MAPACCELERATORW: break;
        // case TB_MARKBUTTON: break;
        // case TB_MOVEBUTTON: break;
        // case TB_PRESSBUTTON: break;
        // case TB_REPLACEBITMAP: break;
        // case TB_SAVERESTOREA: break;
        // case TB_SAVERESTOREW: break;
        // case TB_SETANCHORHIGHLIGHT: break;
        // case TB_SETBITMAPSIZE: break;
        // case TB_SETBUTTONINFOA: break;
        // case TB_SETBUTTONINFOW: break;
        // case TB_SETBUTTONSIZE: break;
        // case TB_SETBUTTONWIDTH: break;
        // case TB_SETCMDID: break;
        // case TB_SETDISABLEDIMAGELIST: break;
        // case TB_SETDRAWTEXTFLAGS: break;
        // case TB_SETEXTENDEDSTYLE: break;
        // case TB_SETHOTIMAGELIST: break;
        // case TB_SETHOTITEM: break;
        // case TB_SETIMAGELIST: break;
        // case TB_SETINDENT: break;
        // case TB_SETINSERTMARK: break;
        // case TB_SETINSERTMARKCOLOR: break;
        // case TB_SETMAXTEXTROWS: break;
        // case TB_SETPADDING: break;
        // case TB_SETPARENT: break;
        // case TB_SETROWS: break;
        // case TB_SETSTATE: break;
        // case TB_SETSTYLE: break;
        // case TB_SETTOOLTIPS: break;
        // case TTM_ACTIVATE: break;
        // case TTM_ADDTOOLA: break;
        // case TTM_ADDTOOLW: break;
        // case TTM_ADJUSTRECT: break;
        // case TTM_DELTOOLA: break;
        // case TTM_DELTOOLW: break;
        // case TTM_ENUMTOOLSA: break;
        // case TTM_ENUMTOOLSW: break;
        // case TTM_GETBUBBLESIZE: break;
        // case TTM_GETCURRENTTOOLA: break;
        // case TTM_GETCURRENTTOOLW: break;
        // case TTM_GETDELAYTIME: break;
        // case TTM_GETMARGIN: break;
        // case TTM_GETMAXTIPWIDTH: break;
        // case TTM_GETTEXTA: break;
        // case TTM_GETTEXTW: break;
        // case TTM_GETTIPBKCOLOR: break;
        // case TTM_GETTIPTEXTCOLOR: break;
        // case TTM_GETTOOLCOUNT: break;
        // case TTM_GETTOOLINFOA: break;
        // case TTM_GETTOOLINFOW: break;
        // case TTM_HITTESTA: break;
        // case TTM_HITTESTW: break;
        // case TTM_NEWTOOLRECTA: break;
        // case TTM_NEWTOOLRECTW: break;
        // case TTM_POP: break;
        // case TTM_RELAYEVENT: break;
        // case TTM_SETDELAYTIME: break;
        // case TTM_SETMARGIN: break;
        // case TTM_SETMAXTIPWIDTH: break;
        // case TTM_SETTIPBKCOLOR: break;
        // case TTM_SETTIPTEXTCOLOR: break;
        // case TTM_SETTITLEA: break;
        // case TTM_SETTITLEW: break;
        // case TTM_SETTOOLINFOA: break;
        // case TTM_SETTOOLINFOW: break;
        // case TTM_TRACKACTIVATE: break;
        // case TTM_TRACKPOSITION: break;
        // case TTM_UPDATE: break;
        // case TTM_UPDATETIPTEXTA: break;
        // case TTM_UPDATETIPTEXTW: break;
        // case TTM_WINDOWFROMPOINT: break;
        // case UDM_GETACCEL: break;
        // case UDM_GETBASE: break;
        // case UDM_GETBUDDY: break;
        // case UDM_GETPOS: break;
        // case UDM_GETPOS32: break;
        // case UDM_GETRANGE: break;
        // case UDM_GETRANGE32: break;
        // case UDM_SETACCEL: break;
        // case UDM_SETBASE: break;
        // case UDM_SETBUDDY: break;
        // case UDM_SETPOS: break;
        // case UDM_SETPOS32: break;
        // case UDM_SETRANGE: break;
        // case UDM_SETRANGE32: break;
        // case UM_GETCURFOCUSA: break;
        // case UM_GETCURFOCUSW: break;
        // case UM_GETGROUPSELA: break;
        // case UM_GETGROUPSELW: break;
        // case UM_GETOPTIONS: break;
        // case UM_GETOPTIONS2: break;
        // case UM_GETSELCOUNT: break;
        // case UM_GETUSERSELA: break;
        // case UM_GETUSERSELW: break;
        // case WIZ_NEXT: break;
        // case WIZ_PREV: break;
        // case WIZ_QUERYNUMPAGES: break;
        // case WLX_WM_SAS: break;
        // case WM_ACTIVATE: break;
        // case WM_ACTIVATEAPP: break;
        // case WM_AFXFIRST: break;
        // case WM_AFXLAST: break;
        // case WM_APP: break;
        // case WM_APPCOMMAND: break;
        // case WM_ASKCBFORMATNAME: break;
        // case WM_CANCELJOURNAL: break;
        // case WM_CANCELMODE: break;
        // case WM_CAPTURECHANGED: break;
        // case WM_CAP_DRIVER_GET_NAMEW: break;
        // case WM_CAP_DRIVER_GET_VERSIONW: break;
        // case WM_CAP_FILE_GET_CAPTURE_FILEW: break;
        // case WM_CAP_FILE_SAVEASW: break;
        // case WM_CAP_FILE_SAVEDIBW: break;
        // case WM_CAP_FILE_SET_CAPTURE_FILEW: break;
        // case WM_CAP_GET_MCI_DEVICEW: break;
        // case WM_CAP_PAL_OPENW: break;
        // case WM_CAP_PAL_SAVEW: break;
        // case WM_CAP_SET_CALLBACK_ERRORW: break;
        // case WM_CAP_SET_CALLBACK_STATUSW: break;
        // case WM_CAP_SET_MCI_DEVICEW: break;
        // case WM_CAP_UNICODE_START: break;
        // case WM_CHANGECBCHAIN: break;
        // case WM_CHANGEUISTATE: break;
        // case WM_CHAR: break;
        // case WM_CHARTOITEM: break;
        // case WM_CHILDACTIVATE: break;
        // case WM_CHOOSEFONT_GETLOGFONT: break;
        // case WM_CHOOSEFONT_SETFLAGS: break;
        // case WM_CHOOSEFONT_SETLOGFONT: break;
        // case WM_CLEAR: break;
        case WM_CLOSE: ::DestroyWindow(windowHandle); break;
        // case WM_COMMAND: break;
        // case WM_COMMNOTIFY: break;
        // case WM_COMPACTING: break;
        // case WM_COMPAREITEM: break;
        // case WM_CONTEXTMENU: break;
        // case WM_CONVERTREQUEST: break;
        // case WM_CONVERTRESULT: break;
        // case WM_COPY: break;
        // case WM_COPYDATA: break;
        // case WM_COPYGLOBALDATA: break;
        // case WM_CPL_LAUNCH: break;
        // case WM_CPL_LAUNCHED: break;
        // case WM_CREATE: break;
        // case WM_CTLCOLOR: break;
        // case WM_CTLCOLORBTN: break;
        // case WM_CTLCOLORDLG: break;
        // case WM_CTLCOLOREDIT: break;
        // case WM_CTLCOLORLISTBOX: break;
        // case WM_CTLCOLORMSGBOX: break;
        // case WM_CTLCOLORSCROLLBAR: break;
        // case WM_CTLCOLORSTATIC: break;
        // case WM_CTLINIT: break;
        // case WM_CUT: break;
        // case WM_DEADCHAR: break;
        // case WM_DELETEITEM: break;
        case WM_DESTROY: ::PostQuitMessage(0); break;
        // case WM_DESTROYCLIPBOARD: break;
        // case WM_DEVICECHANGE: break;
        // case WM_DEVMODECHANGE: break;
        // case WM_DISPLAYCHANGE: break;
        // case WM_DRAWCLIPBOARD: break;
        // case WM_DRAWITEM: break;
        // case WM_DROPFILES: break;
        // case WM_ENABLE: break;
        // case WM_ENDSESSION: break;
        // case WM_ENTERIDLE: break;
        // case WM_ENTERMENULOOP: break;
        // case WM_ENTERSIZEMOVE: break;
        // case WM_ERASEBKGND: break;
        // case WM_EXITMENULOOP: break;
        // case WM_EXITSIZEMOVE: break;
        // case WM_FONTCHANGE: break;
        // case WM_GETDLGCODE: break;
        // case WM_GETFONT: break;
        // case WM_GETHOTKEY: break;
        // case WM_GETICON: break;
        // case WM_GETMINMAXINFO: break;
        // case WM_GETOBJECT: break;
        // case WM_GETTEXT: break;
        // case WM_GETTEXTLENGTH: break;
        // case WM_GLOBALRCCHANGE: break;
        // case WM_HANDHELDFIRST: break;
        // case WM_HANDHELDLAST: break;
        // case WM_HEDITCTL: break;
        // case WM_HELP: break;
        // case WM_HOOKRCRESULT: break;
        // case WM_HOTKEY: break;
        // case WM_HSCROLL: break;
        // case WM_HSCROLLCLIPBOARD: break;
        // case WM_ICONERASEBKGND: break;
        // case WM_IMEKEYDOWN: break;
        // case WM_IMEKEYUP: break;
        // case WM_IME_CHAR: break;
        // case WM_IME_COMPOSITION: break;
        // case WM_IME_COMPOSITIONFULL: break;
        // case WM_IME_CONTROL: break;
        // case WM_IME_ENDCOMPOSITION: break;
        // case WM_IME_KEYDOWN: break;
        // case WM_IME_KEYLAST: break;
        // case WM_IME_KEYUP: break;
        // case WM_IME_NOTIFY: break;
        // case WM_IME_REPORT: break;
        // case WM_IME_REQUEST: break;
        // case WM_IME_SELECT: break;
        // case WM_IME_SETCONTEXT: break;
        // case WM_IME_STARTCOMPOSITION: break;
        // case WM_INITDIALOG: break;
        // case WM_INITMENU: break;
        // case WM_INITMENUPOPUP: break;
        // case WM_INPUT: break;
        // case WM_INPUTLANGCHANGE: break;
        // case WM_INPUTLANGCHANGEREQUEST: break;
        // case WM_INTERIM: break;
        // case WM_KEYDOWN: break;
        // case WM_KEYFIRST: break;
        // case WM_KEYLAST: break;
        // case WM_KEYUP: break;
        // case WM_KILLFOCUS: break;
        // case WM_LBUTTONDBLCLK: break;
        // case WM_LBUTTONDOWN: break;
        // case WM_LBUTTONUP: break;
        // case WM_MBUTTONDBLCLK: break;
        // case WM_MBUTTONDOWN: break;
        // case WM_MBUTTONUP: break;
        // case WM_MDIACTIVATE: break;
        // case WM_MDICASCADE: break;
        // case WM_MDICREATE: break;
        // case WM_MDIDESTROY: break;
        // case WM_MDIGETACTIVE: break;
        // case WM_MDIICONARRANGE: break;
        // case WM_MDIMAXIMIZE: break;
        // case WM_MDINEXT: break;
        // case WM_MDIREFRESHMENU: break;
        // case WM_MDIRESTORE: break;
        // case WM_MDISETMENU: break;
        // case WM_MDITILE: break;
        // case WM_MEASUREITEM: break;
        // case WM_MENUCHAR: break;
        // case WM_MENUCOMMAND: break;
        // case WM_MENUDRAG: break;
        // case WM_MENUGETOBJECT: break;
        // case WM_MENURBUTTONUP: break;
        // case WM_MENUSELECT: break;
        // case WM_MOUSEACTIVATE: break;
        // case WM_MOUSEFIRST: break;
        // case WM_MOUSEHOVER: break;
        // case WM_MOUSELAST: break;
        // case WM_MOUSELEAVE: break;
        // case WM_MOUSEMOVE: break;
        // case WM_MOUSEWHEEL: break;
        // case WM_MOVE: break;
        // case WM_MOVING: break;
        // case WM_NCACTIVATE: break;
        // case WM_NCCALCSIZE: break;
        // case WM_NCCREATE: break;
        // case WM_NCDESTROY: break;
        // case WM_NCHITTEST: break;
        // case WM_NCLBUTTONDBLCLK: break;
        // case WM_NCLBUTTONDOWN: break;
        // case WM_NCLBUTTONUP: break;
        // case WM_NCMBUTTONDBLCLK: break;
        // case WM_NCMBUTTONDOWN: break;
        // case WM_NCMBUTTONUP: break;
        // case WM_NCMOUSEHOVER: break;
        // case WM_NCMOUSELEAVE: break;
        // case WM_NCMOUSEMOVE: break;
        // case WM_NCPAINT: break;
        // case WM_NCRBUTTONDBLCLK: break;
        // case WM_NCRBUTTONDOWN: break;
        // case WM_NCRBUTTONUP: break;
        // case WM_NCXBUTTONDBLCLK: break;
        // case WM_NCXBUTTONDOWN: break;
        // case WM_NCXBUTTONUP: break;
        // case WM_NEXTDLGCTL: break;
        // case WM_NEXTMENU: break;
        // case WM_NOTIFY: break;
        // case WM_NOTIFYFORMAT: break;
        // case WM_0x0: break;
        // case WM_PAINT: break;
        // case WM_PAINTCLIPBOARD: break;
        // case WM_PAINTICON: break;
        // case WM_PALETTECHANGED: break;
        // case WM_PALETTEISCHANGING: break;
        // case WM_PARENTNOTIFY: break;
        // case WM_PASTE: break;
        // case WM_PENCTL: break;
        // case WM_PENEVENT: break;
        // case WM_PENMISC: break;
        // case WM_PENMISCINFO: break;
        // case WM_PENWINFIRST: break;
        // case WM_PENWINLAST: break;
        // case WM_POWER: break;
        // case WM_POWERBROADCAST: break;
        // case WM_PRINT: break;
        // case WM_PRINTCLIENT: break;
        // case WM_PSD_ENVSTAMPRECT: break;
        // case WM_PSD_FULLPAGERECT: break;
        // case WM_PSD_GREEKTEXTRECT: break;
        // case WM_PSD_MARGINRECT: break;
        // case WM_PSD_MINMARGINRECT: break;
        // case WM_PSD_PAGESETUPDLG: break;
        // case WM_PSD_YAFULLPAGERECT: break;
        // case WM_QUERYDRAGICON: break;
        // case WM_QUERYENDSESSION: break;
        // case WM_QUERYNEWPALETTE: break;
        // case WM_QUERYOPEN: break;
        // case WM_QUERYUISTATE: break;
        // case WM_QUEUESYNC: break;
        case WM_QUIT: ::PostQuitMessage(0); break;
        // case WM_RASDIALEVENT: break;
        // case WM_RBUTTONDBLCLK: break;
        // case WM_RBUTTONDOWN: break;
        // case WM_RBUTTONUP: break;
        // case WM_RCRESULT: break;
        // case WM_RENDERALLFORMATS: break;
        // case WM_RENDERFORMAT: break;
        // case WM_SETCURSOR: break;
        // case WM_SETFOCUS: break;
        // case WM_SETFONT: break;
        // case WM_SETHOTKEY: break;
        // case WM_SETICON: break;
        // case WM_SETREDRAW: break;
        // case WM_SETTEXT: break;
        // case WM_SHOWWINDOW: break;
        // case WM_SIZE: break;
        // case WM_SIZECLIPBOARD: break;
        // case WM_SIZING: break;
        // case WM_SKB: break;
        // case WM_SPOOLERSTATUS: break;
        // case WM_STYLECHANGED: break;
        // case WM_STYLECHANGING: break;
        // case WM_SYNCPAINT: break;
        // case WM_SYSCHAR: break;
        // case WM_SYSCOLORCHANGE: break;
        // case WM_SYSCOMMAND: break;
        // case WM_SYSDEADCHAR: break;
        // case WM_SYSKEYDOWN: break;
        // case WM_SYSKEYUP: break;
        // case WM_SYSTIMER: break;
        // case WM_TCARD: break;
        // case WM_TIMECHANGE: break;
        // case WM_TIMER: break;
        // case WM_UNDO: break;
        // case WM_UNICHAR: break;
        // case WM_UNINITMENUPOPUP: break;
        // case WM_UPDATEUISTATE: break;
        // case WM_USER: break;
        // case WM_USERCHANGED: break;
        // case WM_VKEYTOITEM: break;
        // case WM_VSCROLL: break;
        // case WM_VSCROLLCLIPBOARD: break;
        // case WM_WINDOWPOSCHANGED: break;
        // case WM_WINDOWPOSCHANGING: break;
        // case WM_WININICHANGE: break;
        // case WM_WNT_CONVERTREQUESTEX: break;
        // case WM_XBUTTONDBLCLK: break;
        // case WM_XBUTTONDOWN: break;
        // case WM_XBUTTONUP: break;
    }

    // Return
    return ::DefWindowProc(windowHandle, message, messageParameter, additionalMessageParameter);
}

/* Main */
int WinMain(HINSTANCE instanceHandle, HINSTANCE /*previousInstanceHandle*/, LPSTR /*programInitiationCommandLine*/, int windowAppearance) {
    /* Global > Program Status */
    int PROGRAM_STATUS = EXIT_SUCCESS;

    /* Initialization */
        // Screen Console Buffer (Bytes Written, Handle, Information)
        DWORD screenConsoleBufferBytesWritten;
        HANDLE screenConsoleBufferHandle = ::CreateFile("CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, 0x0, OPEN_ALWAYS, 0, 0x0);
        CONSOLE_SCREEN_BUFFER_INFO screenConsoleBufferInformation;

        // Window (Class, Handle, Procedure Message)
        WNDCLASS windowClass {
            CS_HREDRAW | CS_VREDRAW, /* -> `style` --- NOTE (Lapys) -> Pre-defined look of window instances of the class. */
            &windowProcedure, /* -> `lpfnWndProc`  --- NOTE (Lapys) -> Event loop or Message queue.*/
            0, /* -> `cbClsExtra` --- NOTE (Lapys) -> Extra bytes to allocate following the window class structure. */
            0, /* -> `cbWndExtra` --- NOTE (Lapys) -> Extra bytes to allocate following the window instance. */
            0x0, /* -> `hInstance` */
            0x0, /* -> `hIcon` --- NOTE (Lapys) -> Window favorite icon. */
            (HCURSOR) ::LoadCursor(0x0, IDC_ARROW), /* -> `hCursor` --- NOTE (Lapys) -> Window cursor. */
            (HBRUSH) COLOR_WINDOW, /* -> `hbrBackground` --- NOTE (Lapys) -> Window background color. */
            0x0, /* -> `lpszMenuName` --- NOTE (Lapys) -> Resource name of the window class menu. */
            "Windows Messages" /* -> `lpszClassName` */
        };
        HWND windowHandle = 0x0;
        MSG windowProcedureMessage {};

    // ...
    ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);

    ::FillConsoleOutputCharacter(screenConsoleBufferHandle, ' ', screenConsoleBufferInformation.dwSize.X * screenConsoleBufferInformation.dwSize.Y, {0L, 0L}, &screenConsoleBufferBytesWritten);
    ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
    ::SetConsoleCursorPosition(screenConsoleBufferHandle, {0L, 1L});
    ::SetConsoleTitle("Windows Messages");
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
    ::WriteConsoleOutputCharacter(screenConsoleBufferHandle, "[PROGRAM INITIATED]", 19, {0, 0}, &screenConsoleBufferBytesWritten);

    // Logic
    if (::RegisterClass(&windowClass)) {
        // Update > Window Handle
        windowHandle = ::CreateWindowEx(0, windowClass.lpszClassName, "Windows Messages", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0x0, 0x0, instanceHandle, 0x0);

        // Logic > ...
        if (windowHandle) {
            // Update > Window Handle
            ::ShowWindow(windowHandle, windowAppearance);
            ::UpdateWindow(windowHandle);

            // Loop
            while (::GetMessage(&windowProcedureMessage, 0x0, 0, 0)) {
                // Update > Window Procedure Message
                ::TranslateMessage(&windowProcedureMessage);
                ::DispatchMessage(&windowProcedureMessage);
            }

            // Update > Program Status
            PROGRAM_STATUS = windowProcedureMessage.wParam;
        } else ::exit(PROGRAM_STATUS = EXIT_FAILURE);

        // Deletion
        ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
    }

    else
        // Terminate
        ::exit(PROGRAM_STATUS = EXIT_FAILURE);

    // ...
    ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);

    ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
    ::WriteConsoleOutputCharacter(screenConsoleBufferHandle, "[PROGRAM TERMINATED]", 20, {0, (short) (screenConsoleBufferInformation.dwCursorPosition.Y + 1)}, &screenConsoleBufferBytesWritten);

    // Return
    return PROGRAM_STATUS;
}
