/* Import */
    // [C Standard Library]
    #include <stdio.h> // Standard Input-Output
    #include <stdlib.h> // Standard Library

    // [Windows]
    #include <winbase.h> // Windows Base
    #include <winuser.h> // Windows User

    #  include "windows/commctrl.h" // Common Controls
    #  include "windows/ftsiface.h" // ...
    #  include "windows/olectl.h" // Object-Linking & Embedding Controls
    #  include "windows/penwin.h" // Pen for Windows
    #  include "windows/prsht.h" // Prop Sheet
    #  include "windows/richedit.h" // Rich Edit
    #  include "windows/smx.h" // Server Manager Extensions
    #  include "windows/shellapi.h" // Shell API
    #  include "windows/shlobj.h" // Shell Object
    #  include "windows/vfw.h" // Video for Windows
    #  include "windows/wfext.h" // Windows File Extensions

/* Definition */
    /* [Common Controls] `<commctrl.h>` */
    #ifndef _INC_COMMCTRL
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

    #  ifndef LVM_GETBKIMAGEA
    #     define LVM_GETBKIMAGEA 0x1045
    #  endif

    #  ifndef LVM_GETBKIMAGEW
    #     define LVM_GETBKIMAGEW 0x108B
    #  endif

    #  ifndef LVM_GETCOLUMNORDERARRAY
    #     define LVM_GETCOLUMNORDERARRAY 0x103B
    #  endif

    #  ifndef LVM_GETEXTENDEDLISTVIEWSTYLE
    #     define LVM_GETEXTENDEDLISTVIEWSTYLE 0x1037
    #  endif

    #  ifndef LVM_GETHEADER
    #     define LVM_GETHEADER 0x101F
    #  endif

    #  ifndef LVM_GETHOTCURSOR
    #     define LVM_GETHOTCURSOR 0x103F
    #  endif

    #  ifndef LVM_GETHOTITEM
    #     define LVM_GETHOTITEM 0x103D
    #  endif

    #  ifndef LVM_GETHOVERTIME
    #     define LVM_GETHOVERTIME 0x1048
    #  endif

    #  ifndef LVM_GETNUMBEROFWORKAREAS
    #     define LVM_GETNUMBEROFWORKAREAS 0x1049
    #  endif

    #  ifndef LVM_GETSELECTIONMARK
    #     define LVM_GETSELECTIONMARK 0x1042
    #  endif

    #  ifndef LVM_GETSUBITEMRECT
    #     define LVM_GETSUBITEMRECT 0x1038
    #  endif

    #  ifndef LVM_GETTOOLTIPS
    #     define LVM_GETTOOLTIPS 0x104E
    #  endif

    #  ifndef LVM_GETUNICODEFORMAT
    #     define LVM_GETUNICODEFORMAT 0x2006
    #  endif

    #  ifndef LVM_GETWORKAREAS
    #     define LVM_GETWORKAREAS 0x1046
    #  endif

    #  ifndef LVM_ISITEMVISIBLE
    #     define LVM_ISITEMVISIBLE 0x10B6
    #  endif

    #  ifndef LVM_MAPINDEXTOID
    #     define LVM_MAPINDEXTOID 0x10B4
    #  endif

    #  ifndef LVM_MOVEITEMTOGROUP
    #     define LVM_MOVEITEMTOGROUP 0x109A
    #  endif

    #  ifndef LVM_SETBKIMAGEA
    #     define LVM_SETBKIMAGEA 0x1044
    #  endif

    #  ifndef LVM_SETCOLUMNORDERARRAY
    #     define LVM_SETCOLUMNORDERARRAY 0x103A
    #  endif

    #  ifndef LVM_SETEXTENDEDLISTVIEWSTYLE
    #     define LVM_SETEXTENDEDLISTVIEWSTYLE 0x1036
    #  endif

    #  ifndef LVM_SETHOTCURSOR
    #     define LVM_SETHOTCURSOR 0x103E
    #  endif

    #  ifndef LVM_SETHOTITEM
    #     define LVM_SETHOTITEM 0x103E
    #  endif

    #  ifndef LVM_SETHOVERTIME
    #     define LVM_SETHOVERTIME 0x1047
    #  endif

    #  ifndef LVM_SETICONSPACING
    #     define LVM_SETICONSPACING 0x1035
    #  endif

    #  ifndef LVM_SETSELECTEDCOLUMN
    #     define LVM_SETSELECTEDCOLUMN 0x108C
    #  endif

    #  ifndef LVM_SETSELECTIONMARK
    #     define LVM_SETSELECTIONMARK 0x1043
    #  endif

    #  ifndef LVM_SETTILEWIDTH
    #     define LVM_SETTILEWIDTH 0x108D
    #  endif

    #  ifndef LVM_SETTOOLTIPS
    #     define LVM_SETTOOLTIPS 0x104A
    #  endif

    #  ifndef LVM_SETUNICODEFORMAT
    #     define LVM_SETUNICODEFORMAT 0x2005
    #  endif

    #  ifndef LVM_SETWORKAREAS
    #     define LVM_SETWORKAREAS 0x1041
    #  endif

    #  ifndef LVM_SUBITEMHITTEST
    #     define LVM_SUBITEMHITTEST 0x1039
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

    #  ifndef SB_GETTIPTEXTA
    #     define SB_GETTIPTEXTA 0x0412
    #  endif

    #  ifndef SB_GETTIPTEXTW
    #     define SB_GETTIPTEXTW 0x0413
    #  endif

    #  ifndef SB_ISSIMPLE
    #     define SB_ISSIMPLE 0x040E
    #  endif

    #  ifndef SB_SETICON
    #     define SB_SETICON 0x040F
    #  endif

    #  ifndef SB_SETTIPTEXTA
    #     define SB_SETTIPTEXTA 0x0410
    #  endif

    #  ifndef SB_SETTIPTEXTW
    #     define SB_SETTIPTEXTW 0x0411
    #  endif

    #  ifndef TB_ADDBUTTONSA
    #     define TB_ADDBUTTONSA 0x0414
    #  endif

    #  ifndef TB_ADDBUTTONSW
    #     define TB_ADDBUTTONSW 0x0444
    #  endif

    #  ifndef TB_GETANCHORHIGHLIGHT
    #     define TB_GETANCHORHIGHLIGHT 0x044A
    #  endif

    #  ifndef TB_GETBUTTONINFOA
    #     define TB_GETBUTTONINFOA 0x0441
    #  endif

    #  ifndef TB_GETBUTTONINFOW
    #     define TB_GETBUTTONINFOW 0x043F
    #  endif

    #  ifndef TB_GETDISABLEDIMAGELIST
    #     define TB_GETDISABLEDIMAGELIST 0x0437
    #  endif

    #  ifndef TB_GETEXTENDEDSTYLE
    #     define TB_GETEXTENDEDSTYLE 0x0455
    #  endif

    #  ifndef TB_GETHOTIMAGELIST
    #     define TB_GETHOTIMAGELIST 0x0435
    #  endif

    #  ifndef TB_GETHOTITEM
    #     define TB_GETHOTITEM 0x0447
    #  endif

    #  ifndef TB_GETIMAGELIST
    #     define TB_GETIMAGELIST 0x0431
    #  endif

    #  ifndef TB_GETINSERTMARK
    #     define TB_GETINSERTMARK 0x044F
    #  endif

    #  ifndef TB_GETINSERTMARKCOLOR
    #     define TB_GETINSERTMARKCOLOR 0x0459
    #  endif

    #  ifndef TB_GETMAXSIZE
    #     define TB_GETMAXSIZE 0x0453
    #  endif

    #  ifndef TB_GETOBJECT
    #     define TB_GETOBJECT 0x043E
    #  endif

    #  ifndef TB_GETPADDING
    #     define TB_GETPADDING 0x0456
    #  endif

    #  ifndef TB_GETRECT
    #     define TB_GETRECT 0x0433
    #  endif

    #  ifndef TB_GETSTRINGA
    #     define TB_GETSTRINGA 0x045C
    #  endif

    #  ifndef TB_GETSTRINGW
    #     define TB_GETSTRINGW 0x045B
    #  endif

    #  ifndef TB_GETSTYLE
    #     define TB_GETSTYLE 0x0439
    #  endif

    #  ifndef TB_GETTEXTROWS
    #     define TB_GETTEXTROWS 0x043D
    #  endif

    #  ifndef TB_HITTEST
    #     define TB_HITTEST 0x0445
    #  endif

    #  ifndef TB_INSERTBUTTONA
    #     define TB_INSERTBUTTONA 0x0415
    #  endif

    #  ifndef TB_INSERTBUTTONW
    #     define TB_INSERTBUTTONW 0x0443
    #  endif

    #  ifndef TB_INSERTMARKHITTEST
    #     define TB_INSERTMARKHITTEST 0x0451
    #  endif

    #  ifndef TB_ISBUTTONHIGHLIGHTED
    #     define TB_ISBUTTONHIGHLIGHTED 0x040E
    #  endif

    #  ifndef TB_LOADIMAGES
    #     define TB_LOADIMAGES 0x0432
    #  endif

    #  ifndef TB_MAPACCELERATORA
    #     define TB_MAPACCELERATORA 0x044E
    #  endif

    #  ifndef TB_MAPACCELERATORW
    #     define TB_MAPACCELERATORW 0x045A
    #  endif

    #  ifndef TB_MARKBUTTON
    #     define TB_MARKBUTTON 0x0406
    #  endif

    #  ifndef TB_MOVEBUTTON
    #     define TB_MOVEBUTTON 0x0452
    #  endif

    #  ifndef TB_SETANCHORHIGHLIGHT
    #     define TB_SETANCHORHIGHLIGHT 0x0449
    #  endif

    #  ifndef TB_SETBUTTONINFOA
    #     define TB_SETBUTTONINFOA 0x0442
    #  endif

    #  ifndef TB_SETBUTTONINFOW
    #     define TB_SETBUTTONINFOW 0x0404
    #  endif

    #  ifndef TB_SETDISABLEDIMAGELIST
    #     define TB_SETDISABLEDIMAGELIST 0x0436
    #  endif

    #  ifndef TB_SETDRAWTEXTFLAGS
    #     define TB_SETDRAWTEXTFLAGS 0x0446
    #  endif

    #  ifndef TB_SETEXTENDEDSTYLE
    #     define TB_SETEXTENDEDSTYLE 0x0454
    #  endif

    #  ifndef TB_SETHOTIMAGELIST
    #     define TB_SETHOTIMAGELIST 0x0434
    #  endif

    #  ifndef TB_SETHOTITEM
    #     define TB_SETHOTITEM 0x0448
    #  endif

    #  ifndef TB_SETIMAGELIST
    #     define TB_SETIMAGELIST 0x0430
    #  endif

    #  ifndef TB_SETINDENT
    #     define TB_SETINDENT 0x042F
    #  endif

    #  ifndef TB_SETINSERTMARK
    #     define TB_SETINSERTMARK 0x0450
    #  endif

    #  ifndef TB_SETINSERTMARKCOLOR
    #     define TB_SETINSERTMARKCOLOR 0x0458
    #  endif

    #  ifndef TB_SETMAXTEXTROWS
    #     define TB_SETMAXTEXTROWS 0x043C
    #  endif

    #  ifndef TB_SETPADDING
    #     define TB_SETPADDING 0x0457
    #  endif

    #  ifndef TB_SETSTYLE
    #     define TB_SETSTYLE 0x0438
    #  endif

    #  ifndef TTM_ADJUSTRECT
    #     define TTM_ADJUSTRECT 0x041F
    #  endif

    #  ifndef TTM_GETBUBBLESIZE
    #     define TTM_GETBUBBLESIZE 0x041E
    #  endif

    #  ifndef TTM_GETDELAYTIME
    #     define TTM_GETDELAYTIME 0x0415
    #  endif

    #  ifndef TTM_GETMARGIN
    #     define TTM_GETMARGIN 0x041B
    #  endif

    #  ifndef TTM_GETMAXTIPWIDTH
    #     define TTM_GETMAXTIPWIDTH 0x0419
    #  endif

    #  ifndef TTM_GETTIPBKCOLOR
    #     define TTM_GETTIPBKCOLOR 0x0416
    #  endif

    #  ifndef TTM_GETTIPTEXTCOLOR
    #     define TTM_GETTIPTEXTCOLOR 0x0417
    #  endif

    #  ifndef TTM_POP
    #     define TTM_POP 0x041C
    #  endif

    #  ifndef TTM_SETMARGIN
    #     define TTM_SETMARGIN 0x041A
    #  endif

    #  ifndef TTM_SETMAXTIPWIDTH
    #     define TTM_SETMAXTIPWIDTH 0x0418
    #  endif

    #  ifndef TTM_SETTIPBKCOLOR
    #     define TTM_SETTIPBKCOLOR 0x0413
    #  endif

    #  ifndef TTM_SETTIPTEXTCOLOR
    #     define TTM_SETTIPTEXTCOLOR 0x0414
    #  endif

    #  ifndef TTM_SETTITLEA
    #     define TTM_SETTITLEA 0x0420
    #  endif

    #  ifndef TTM_SETTITLEW
    #     define TTM_SETTITLEW 0x0421
    #  endif

    #  ifndef TTM_TRACKACTIVATE
    #     define TTM_TRACKACTIVATE 0x0411
    #  endif

    #  ifndef TTM_TRACKPOSITION
    #     define TTM_TRACKPOSITION 0x0412
    #  endif

    #  ifndef TTM_UPDATE
    #     define TTM_UPDATE 0x041D
    #  endif

    #  ifndef UDM_GETPOS32
    #     define UDM_GETPOS32 0x0472
    #  endif

    #  ifndef UDM_GETRANGE32
    #     define UDM_GETRANGE32 0x0470
    #  endif

    #  ifndef UDM_SETPOS32
    #     define UDM_SETPOS32 0x0471
    #  endif

    #  ifndef UDM_SETRANGE32
    #     define UDM_SETRANGE32 0x046F
    #  endif
    #endif

    /* [Display Device-Independent Bitmap] `<dispdib.h>` */
    #ifndef __DISPDIB_H__
    #  ifndef DDM_BEGIN
    #     define DDM_BEGIN 0x0403
    #endif

    #  ifndef DDM_CLOSE
    #     define DDM_CLOSE 0x0402
    #endif

    #  ifndef DDM_DRAW
    #     define DDM_DRAW 0x0401
    #endif

    #  ifndef DDM_END
    #     define DDM_END 0x0404
    #endif

    #  ifndef DDM_SETFMT
    #     define DDM_SETFMT 0x0400
    #endif
    #endif

    /* [Input Method Encoding] `<ime.h>` */
    #ifndef _IME_
    #  ifndef WM_CONVERTREQUEST
    #     define WM_CONVERTREQUEST 0x010A
    #  endif

    #  ifndef WM_CONVERTRESULT
    #     define WM_CONVERTRESULT 0x010B
    #  endif
    #endif

    /* [Object-Linking & Embedding Controls] `<olectl.h>` */
    #if/*ndef _OLECTL_H*/true
    #  ifndef OCM__BASE
    #     define OCM__BASE (WM_USER + 0x1C00)
    #  endif

    #  ifndef OCM_CHARTOITEM
    #     define OCM_CHARTOITEM (OCM__BASE + WM_CHARTOITEM)
    #  endif

    #  ifndef OCM_COMMAND
    #     define OCM_COMMAND (OCM__BASE + WM_COMMAND)
    #  endif

    #  ifndef OCM_COMPAREITEM
    #     define OCM_COMPAREITEM (OCM__BASE + WM_COMPAREITEM)
    #  endif

    #  ifndef OCM_CTLCOLOR
    #     define OCM_CTLCOLOR (OCM__BASE + WM_CTLCOLOR)
    #  endif

    #  ifndef OCM_CTLCOLORBTN
    #     define OCM_CTLCOLORBTN (OCM__BASE + WM_CTLCOLORBTN)
    #  endif

    #  ifndef OCM_CTLCOLORDLG
    #     define OCM_CTLCOLORDLG (OCM__BASE + WM_CTLCOLORDLG)
    #  endif

    #  ifndef OCM_CTLCOLOREDIT
    #     define OCM_CTLCOLOREDIT (OCM__BASE + WM_CTLCOLOREDIT)
    #  endif

    #  ifndef OCM_CTLCOLORLISTBOX
    #     define OCM_CTLCOLORLISTBOX (OCM__BASE + WM_CTLCOLORLISTBOX)
    #  endif

    #  ifndef OCM_CTLCOLORMSGBOX
    #     define OCM_CTLCOLORMSGBOX (OCM__BASE + WM_CTLCOLORMSGBOX)
    #  endif

    #  ifndef OCM_CTLCOLORSCROLLBAR
    #     define OCM_CTLCOLORSCROLLBAR (OCM__BASE + WM_CTLCOLORSCROLLBAR)
    #  endif

    #  ifndef OCM_CTLCOLORSTATIC
    #     define OCM_CTLCOLORSTATIC (OCM__BASE + WM_CTLCOLORSTATIC)
    #  endif

    #  ifndef OCM_DELETEITEM
    #     define OCM_DELETEITEM (OCM__BASE + WM_DELETEITEM)
    #  endif

    #  ifndef OCM_DRAWITEM
    #     define OCM_DRAWITEM (OCM__BASE + WM_DRAWITEM)
    #  endif

    #  ifndef OCM_HSCROLL
    #     define OCM_HSCROLL (OCM__BASE + WM_HSCROLL)
    #  endif

    #  ifndef OCM_MEASUREITEM
    #     define OCM_MEASUREITEM (OCM__BASE + WM_MEASUREITEM)
    #  endif

    #  ifndef OCM_NOTIFY
    #     define OCM_NOTIFY (OCM__BASE + WM_NOTIFY)
    #  endif

    #  ifndef OCM_PARENTNOTIFY
    #     define OCM_PARENTNOTIFY (OCM__BASE + WM_PARENTNOTIFY)
    #  endif

    #  ifndef OCM_VKEYTOITEM
    #     define OCM_VKEYTOITEM (OCM__BASE + WM_VKEYTOITEM)
    #  endif

    #  ifndef OCM_VSCROLL
    #     define OCM_VSCROLL (OCM__BASE + WM_VSCROLL)
    #  endif
    #endif

    /* [Pen for Windows] `<penwin.h>` */
    #ifndef _INC_PENWIN
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

    /* [Prop Sheet] `<prsht.h>` */
    #ifndef _PRSHT_H_
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

    /* [Rich Edit] `<richedit.h>` */
    #if/*ndef _RICHEDIT_H*/true
    #  ifndef EM_CONVPOSITION
    #     define EM_CONVPOSITION 0x046C
    #  endif

    #  ifndef EM_GETCTFMODEBIAS
    #     define EM_GETCTFMODEBIAS 0x04ED
    #  endif

    #  ifndef EM_GETCTFOPENSTATUS
    #     define EM_GETCTFOPENSTATUS 0x04F0
    #  endif

    #  ifndef EM_GETHYPHENATEINFO
    #     define EM_GETHYPHENATEINFO 0x04E6
    #  endif

    #  ifndef EM_GETIMECOMPTEXT
    #     define EM_GETIMECOMPTEXT 0x04F2
    #  endif

    #  ifndef EM_GETIMEMODEBIAS
    #     define EM_GETIMEMODEBIAS 0x047F
    #  endif

    #  ifndef EM_GETIMEPROPERTY
    #     define EM_GETIMEPROPERTY 0x04F4
    #  endif

    #  ifndef EM_GETPAGE
    #     define EM_GETPAGE 0x04EF
    #  endif

    #  ifndef EM_GETPAGEROTATE
    #     define EM_GETPAGEROTATE 0x04EB
    #  endif

    #  ifndef EM_GETVIEWKIND
    #     define EM_GETVIEWKIND 0x04E2
    #  endif

    #  ifndef EM_ISIME
    #     define EM_ISIME 0x04F3
    #  endif

    #  ifndef EM_OUTLINE
    #     define EM_OUTLINE 0x04DC
    #  endif

    #  ifndef EM_SETCTFMODEBIAS
    #     define EM_SETCTFMODEBIAS 0x04EE
    #  endif

    #  ifndef EM_SETCTFOPENSTATUS
    #     define EM_SETCTFOPENSTATUS 0x04F1
    #  endif

    #  ifndef EM_SETFONT
    #     define EM_SETFONT 0x00C3
    #  endif

    #  ifndef EM_SETHYPHENATEINFO
    #     define EM_SETHYPHENATEINFO 0x04E7
    #  endif

    #  ifndef EM_SETIMEMODEBIAS
    #     define EM_SETIMEMODEBIAS 0x047E
    #  endif

    #  ifndef EM_SETPAGE
    #     define EM_SETPAGE 0x04E5
    #  endif

    #  ifndef EM_SETPAGEROTATE
    #     define EM_SETPAGEROTATE 0x04EC
    #  endif

    #  ifndef EM_SETQUERYRTFOBJ
    #     define EM_SETQUERYRTFOBJ 0x050E
    #  endif

    #  ifndef EM_SETVIEWKIND
    #     define EM_SETVIEWKIND 0x04E3
    #  endif

    #  ifndef EM_SETWORDBREAK
    #     define EM_SETWORDBREAK 0x00CA
    #  endif
    #endif

    /* [Shell API] `<shellapi.h>` */
    #ifndef _INC_SHELLAPI
    #  ifndef NIN_SELECT
    #     define NIN_SELECT (WM_USER + 0)
    #  endif
    #endif

    /* [Shell Objects] `<shlobj.h>` */
    #ifndef _SHLOBJ_H
    #  ifndef BFFM_ENABLEOK
    #     define BFFM_ENABLEOK 0x0465
    #  endif

    #  ifndef BFFM_SETSELECTIONA
    #     define BFFM_SETSELECTIONA 0x0466
    #  endif

    #  ifndef BFFM_SETSELECTIONW
    #     define BFFM_SETSELECTIONW 0x0467
    #  endif

    #  ifndef BFFM_SETSTATUSTEXTA
    #     define BFFM_SETSTATUSTEXTA 0x0464
    #  endif

    #  ifndef BFFM_SETSTATUSTEXTW
    #     define BFFM_SETSTATUSTEXTW 0x0468
    #  endif
    #endif

    /* [Unicode Methods] `<umx.h>` */
    #ifndef _UMX_H_
    #  ifndef UM_GETCURFOCUSA
    #     define UM_GETCURFOCUSA WM_USER + 1005
    #  endif

    #  ifndef UM_GETCURFOCUSW
    #     define UM_GETCURFOCUSW WM_USER + 1006
    #  endif

    #  ifndef UM_GETGROUPSELA
    #     define UM_GETGROUPSELA WM_USER + 1003
    #  endif

    #  ifndef UM_GETGROUPSELW
    #     define UM_GETGROUPSELW WM_USER + 1004
    #  endif

    #  ifndef UM_GETOPTIONS
    #     define UM_GETOPTIONS WM_USER + 1007
    #  endif

    #  ifndef UM_GETOPTIONS2
    #     define UM_GETOPTIONS2 WM_USER + 1008
    #  endif

    #  ifndef UM_GETSELCOUNT
    #     define UM_GETSELCOUNT WM_USER + 1000
    #  endif

    #  ifndef UM_GETUSERSELA
    #     define UM_GETUSERSELA WM_USER + 1001
    #  endif

    #  ifndef UM_GETUSERSELW
    #     define UM_GETUSERSELW WM_USER + 1002
    #  endif
    #endif

    /* [Video for Windows] `<vfw.h>` */
    #ifndef _INC_VFW
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

    #  ifndef WM_CAP_SET_CALLBACK_STATUSW
    #     define WM_CAP_SET_CALLBACK_STATUSW 0x0467
    #  endif

    #  ifndef WM_CAP_UNICODE_START
    #     define WM_CAP_UNICODE_START 0x0464
    #  endif
    #endif

    /* [Windows File Extensions] `<wfext.h>` */
    #ifndef _INC_WFEXT
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

    /* [Windows -> User] `<winuser.h>` */
    #if/*ndef _WINUSER_H*/true
    #  ifndef BM_SETDONTCLICK
    #     define BM_SETDONTCLICK 0x00F8
    #  endif

    #  ifndef WM_CTLCOLOR
    #     define WM_CTLCOLOR 0x0019
    #  endif

    #  ifndef WM_COPYGLOBALDATA
    #     define WM_COPYGLOBALDATA 0x0049
    #  endif

    #  ifndef WM_CPL_LAUNCH
    #     define WM_CPL_LAUNCH 0x07E8
    #  endif

    #  ifndef WM_CPL_LAUNCHED
    #     define WM_CPL_LAUNCHED 0x07E9
    #  endif

    #  ifndef WM_HOOKRCRESULT
    #     define WM_HOOKRCRESULT 0x0382
    #  endif

    #  ifndef WM_IMEKEYDOWN
    #     define WM_IMEKEYDOWN 0x0290
    #  endif

    #  ifndef WM_IMEKEYUP
    #     define WM_IMEKEYUP 0x0291
    #  endif

    #  ifndef WM_IME_REPORT
    #     define WM_IME_REPORT 0x0280
    #  endif

    #  ifndef WM_INPUT
    #     define WM_INPUT 0x00FF
    #  endif

    #  ifndef WM_INTERIM
    #     define WM_INTERIM 0x010C
    #  endif

    #  ifndef WM_RASDIALEVENT
    #     define WM_RASDIALEVENT 0xCCCD
    #  endif

    #  ifndef WM_RCRESULT
    #     define WM_RCRESULT 0x0381
    #  endif

    #  ifndef WM_SKB
    #     define WM_SKB 0x0384
    #  endif

    #  ifndef WM_SYSTIMER
    #     define WM_SYSTIMER 0x0118
    #  endif

    #  ifndef WM_UNICHAR
    #     define WM_UNICHAR 0x0109
    #  endif

    #  ifndef WM_WNT_CONVERTREQUESTEX
    #     define WM_WNT_CONVERTREQUESTEX 0x0109
    #  endif
    #endif

    /* ... `<ftsiface.h>` */
    #ifndef __FTSIFACE_H__
    #  ifndef MSG_FTS_JUMP_QWORD
    #     define MSG_FTS_JUMP_QWORD 0x0423
    #  endif

    #  ifndef MSG_FTS_JUMP_VA
    #     define MSG_FTS_JUMP_VA 0x0421
    #  endif

    #  ifndef MSG_FTS_WHERE_IS_IT
    #     define MSG_FTS_WHERE_IS_IT 0x0425
    #  endif

    #  ifndef MSG_GET_DEFFONT
    #     define MSG_GET_DEFFONT 0x042D
    #  endif

    #  ifndef MSG_REINDEX_REQUEST
    #     define MSG_REINDEX_REQUEST 0x0424
    #  endif
    #endif

    /* ... */
    #ifndef TAPI_REPLY
    #  define TAPI_REPLY 0x0463
    #endif

    #ifndef WIZ_NEXT
    #  define WIZ_NEXT 0x040B
    #endif

    #ifndef WIZ_PREV
    #  define WIZ_PREV 0x040C
    #endif

    #ifndef WIZ_QUERYNUMPAGES
    #  define WIZ_QUERYNUMPAGES 0x040A
    #endif

    #ifndef WLX_WM_SAS
    #  define WLX_WM_SAS 0x0659
    #endif

/* Function */
    // Print ...
    void print(const HANDLE screenConsoleBufferHandle, const char argument[]) noexcept {
        // Logic
        if (argument) {
            // Initialization > Screen Console Buffer (Bytes Written, Information)
            DWORD screenConsoleBufferBytesWritten;
            CONSOLE_SCREEN_BUFFER_INFO screenConsoleBufferInformation;

            // Update > Screen Console Buffer Information
            ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);

            // Loop > Print
            for (char *message = (char*) argument; *message; ++message)
            ::WriteConsoleOutputCharacter(screenConsoleBufferHandle, message, 1, {screenConsoleBufferInformation.dwCursorPosition.X++, screenConsoleBufferInformation.dwCursorPosition.Y}, &screenConsoleBufferBytesWritten);

            // Update > Screen Console Buffer Handle
            ::SetConsoleCursorPosition(screenConsoleBufferHandle, {screenConsoleBufferInformation.dwCursorPosition.X, screenConsoleBufferInformation.dwCursorPosition.Y});
        }
    }
    void printe(const HANDLE screenConsoleBufferHandle) noexcept {
        // Initialization > Screen Console Buffer (Bytes Written, Information)
        DWORD screenConsoleBufferBytesWritten;
        CONSOLE_SCREEN_BUFFER_INFO screenConsoleBufferInformation;

        // Update > Screen Console Buffer Information
        ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);
        ::WriteConsoleOutputCharacter(screenConsoleBufferHandle, "[ERROR CODE]: ", 14, {screenConsoleBufferInformation.dwCursorPosition.X, screenConsoleBufferInformation.dwCursorPosition.Y}, &screenConsoleBufferBytesWritten);

        // Loop
        for (int index = 5; index; ) {
            // Loop > ...
            for (int errorCode = ::GetLastError(); errorCode; errorCode /= 10) { const char digit = (errorCode % 10) + 48; ::WriteConsoleOutputCharacter(screenConsoleBufferHandle, &digit, 1, {(short) (screenConsoleBufferInformation.dwCursorPosition.X + index-- + 13), screenConsoleBufferInformation.dwCursorPosition.Y}, &screenConsoleBufferBytesWritten); }
            while (index) ::WriteConsoleOutputCharacter(screenConsoleBufferHandle, "0", 1, {(short) (screenConsoleBufferInformation.dwCursorPosition.X + index-- + 13), screenConsoleBufferInformation.dwCursorPosition.Y}, &screenConsoleBufferBytesWritten);
        }

        // Update > Screen Console Buffer Handle
        ::SetConsoleCursorPosition(screenConsoleBufferHandle, {0, (short) (screenConsoleBufferInformation.dwCursorPosition.Y + 1)});
    }
    inline void println(const HANDLE screenConsoleBufferHandle, const char argument[] = 0x0) noexcept {
        /* ... */
        ::print(screenConsoleBufferHandle, argument);

        // Initialization > Screen Console Buffer Information
        CONSOLE_SCREEN_BUFFER_INFO screenConsoleBufferInformation;

        // Update > Screen Console Buffer (Handle, Information)
        ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);
        ::SetConsoleCursorPosition(screenConsoleBufferHandle, {0, (short) (screenConsoleBufferInformation.dwCursorPosition.Y + 1)});
    }
    inline void printg(const HANDLE screenConsoleBufferHandle, const char argument[]) noexcept { ::println(screenConsoleBufferHandle, argument); }
    inline void printge(const HANDLE screenConsoleBufferHandle, const char argument[]) noexcept { ::println(screenConsoleBufferHandle, argument); }
    inline void printh(const HANDLE screenConsoleBufferHandle, const int argument) noexcept {
        // Logic ...
        if (argument) {
            // Initialization > (Argument String, ...)
            char buffer[7] {'0', 'x', '0', '0', '0', '0', '\0'};
            char *argumentString = (char*) (buffer + 6);

            // Loop > Update > Argument String
            for (int iterator = argument; ('x' ^ *argumentString) && iterator; iterator /= 16)
            switch (iterator % 16) { case 0: *--argumentString = '0'; break; case 1: *--argumentString = '1'; break; case 2: *--argumentString = '2'; break; case 3: *--argumentString = '3'; break; case 4: *--argumentString = '4'; break; case 5: *--argumentString = '5'; break; case 6: *--argumentString = '6'; break; case 7: *--argumentString = '7'; break; case 8: *--argumentString = '8'; break; case 9: *--argumentString = '9'; break; case 10: *--argumentString = 'A'; break; case 11: *--argumentString = 'B'; break; case 12: *--argumentString = 'C'; break; case 13: *--argumentString = 'D'; break; case 14: *--argumentString = 'E'; break; case 15: *--argumentString = 'F'; break; }

            // Print
            ::print(screenConsoleBufferHandle, argumentString = buffer);
        } else ::print(screenConsoleBufferHandle, "0x0000");
    }
    inline void printmln(const HANDLE screenConsoleBufferHandle, const char argument[]) noexcept { ::println(screenConsoleBufferHandle, argument); }

    /* Window Procedure */
    LRESULT CALLBACK windowProcedure(HWND windowHandle, UINT message, WPARAM messageParameter, LPARAM additionalMessageParameter) noexcept {
        // Constant > Screen Console Buffer Handle
        const HANDLE screenConsoleBufferHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);

        // Update > Screen Console Buffer Handle
        ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);

        // Logic --- WARN (Lapys) -> These, of course are not all window messages.
        switch (message) {
            // [Window Manager ...]
            case ACM_OPENA /* -> BFFM_SETSTATUSTEXTA || CDM_FIRST || CDM_GETSPEC || EM_SETPUNCTUATION || IPM_CLEARADDRESS || WM_CAP_UNICODE_START */:
                ::printh(screenConsoleBufferHandle, ACM_OPENA); ::printg(screenConsoleBufferHandle, ": [");
                    ::printmln(screenConsoleBufferHandle, "    Animation Control -> Open");
                    ::printmln(screenConsoleBufferHandle, "    Browse for Folder -> Set Status Text");
                    ::printmln(screenConsoleBufferHandle, "    Common Dialog -> [FIRST]");
                    ::printmln(screenConsoleBufferHandle, "    Common Dialog -> Get Specifications");
                    ::printmln(screenConsoleBufferHandle, "    Internet Protocol -> Clear Address");
                    ::printmln(screenConsoleBufferHandle, "    Rich Editor -> Set Punctuation");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Cap Unicode Start");
                 ::printge(screenConsoleBufferHandle, "]");
            break;
            case ACM_OPENW /* -> BFFM_SETSELECTIONW || CDM_GETFOLDERIDLIST || EM_GETWORDWRAPMODE || IPM_SETRANGE || PSM_ADDPAGE || UDM_SETPOS || WM_CAP_SET_CALLBACK_STATUSW */:
                ::printh(screenConsoleBufferHandle, ACM_OPENW); ::printg(screenConsoleBufferHandle, ": [");
                    ::printmln(screenConsoleBufferHandle, "    Animation Control -> Open");
                    ::printmln(screenConsoleBufferHandle, "    Browse for Folder -> Set Selection");
                    ::printmln(screenConsoleBufferHandle, "    Common Dialog -> Get Folder ID List");
                    ::printmln(screenConsoleBufferHandle, "    Internet Protocol -> Set Range");
                    ::printmln(screenConsoleBufferHandle, "    Prop Sheet -> Add Page");
                    ::printmln(screenConsoleBufferHandle, "    Rich Editor -> Get Word Wrap Mode");
                    ::printmln(screenConsoleBufferHandle, "    Up-Down Control -> Set Position");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Cap Set Callback Status");
                 ::printge(screenConsoleBufferHandle, "]");
            break;
            case ACM_PLAY /* -> BFFM_ENABLEOK || CDM_GETFILEPATH || EM_GETPUNCTUATION || IPM_SETADDRESS || UDM_SETRANGE || WM_CHOOSEFONT_SETLOGFONT */:
                ::printh(screenConsoleBufferHandle, ACM_OPENA); ::printg(screenConsoleBufferHandle, ": [");
                    ::printmln(screenConsoleBufferHandle, "    Animation Control -> Play");
                    ::printmln(screenConsoleBufferHandle, "    Browse for Folder -> Enable OK");
                    ::printmln(screenConsoleBufferHandle, "    Common Dialog -> Get File Path");
                    ::printmln(screenConsoleBufferHandle, "    Internet Protocol -> Set Address");
                    ::printmln(screenConsoleBufferHandle, "    Rich Editor -> Get Punctuation");
                    ::printmln(screenConsoleBufferHandle, "    Internet Protocol -> Set Address");
                    ::printmln(screenConsoleBufferHandle, "    Up-Down Control -> Set Range");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Choose Font (Set Log Font)");
                 ::printge(screenConsoleBufferHandle, "]");
            break;
            case ACM_STOP /* -> BFFM_SETSELECTIONA || CDM_GETFOLDERPATH || EM_SETWORDWRAPMODE || IPM_GETADDRESS || PSM_REMOVEPAGE || UDM_GETRANGE || WM_CAP_SET_CALLBACK_ERRORW || WM_CHOOSEFONT_SETFLAGS */:
                ::printh(screenConsoleBufferHandle, ACM_OPENA); ::printg(screenConsoleBufferHandle, ": [");
                    ::printmln(screenConsoleBufferHandle, "    Animation Control -> Stop");
                    ::printmln(screenConsoleBufferHandle, "    Browse for Folder -> Set Selection");
                    ::printmln(screenConsoleBufferHandle, "    Common Dialog -> Get Folder Path");
                    ::printmln(screenConsoleBufferHandle, "    Internet Protocol -> Get Address");
                    ::printmln(screenConsoleBufferHandle, "    Prop Sheet -> Remove Page");
                    ::printmln(screenConsoleBufferHandle, "    Rich Editor -> Set Word Wrap Mode");
                    ::printmln(screenConsoleBufferHandle, "    Up-Down Control -> Get Range");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Cap Set Callback Error");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Choose Font Set Flags");
                 ::printge(screenConsoleBufferHandle, "]");
            break;
            /*case BFFM_ENABLEOK: break;*/
            /*case BFFM_SETSELECTIONA: break;*/
            /*case BFFM_SETSELECTIONW: break;*/
            /*case BFFM_SETSTATUSTEXTA: break;*/
            case BFFM_SETSTATUSTEXTW /* -> CDM_SETCONTROLTEXT || EM_SETIMECOLOR || IPM_SETFOCUS || PSM_CHANGED || UDM_GETPOS */:
                ::printh(screenConsoleBufferHandle, ACM_OPENA); ::printg(screenConsoleBufferHandle, ": [");
                    ::printmln(screenConsoleBufferHandle, "    Browse for Folder -> Set Status Text");
                    ::printmln(screenConsoleBufferHandle, "    Common Dialog -> Set Control Text");
                    ::printmln(screenConsoleBufferHandle, "    Internet Protocol -> Set Focus");
                    ::printmln(screenConsoleBufferHandle, "    Prop Sheet -> Changed");
                    ::printmln(screenConsoleBufferHandle, "    Rich Edit -> Set IME Color");
                    ::printmln(screenConsoleBufferHandle, "    Up-Down Control -> Get Position");
                 ::printge(screenConsoleBufferHandle, "]");
            break;
            case BM_SETDONTCLICK: ::printmln(screenConsoleBufferHandle, "Button -> Set Do Not Click"); break;
            case BM_CLICK: ::printmln(screenConsoleBufferHandle, "Button -> Click"); break;
            case BM_GETCHECK: ::printmln(screenConsoleBufferHandle, "Button -> Get Check"); break;
            case BM_GETIMAGE: ::printmln(screenConsoleBufferHandle, "Button -> Get Image"); break;
            case BM_GETSTATE: ::printmln(screenConsoleBufferHandle, "Button -> Get State"); break;
            case BM_SETCHECK: ::printmln(screenConsoleBufferHandle, "Button -> Set Check"); break;
            case BM_SETIMAGE: ::printmln(screenConsoleBufferHandle, "Button -> Set Image"); break;
            case BM_SETSTATE: ::printmln(screenConsoleBufferHandle, "Button -> Set State"); break;
            case BM_SETSTYLE: ::printmln(screenConsoleBufferHandle, "Button -> Set Style"); break;
            case CBEM_GETCOMBOCONTROL /* -> PBM_SETRANGE32 || RB_SETBANDINFOA || SB_GETPARTS || TBM_SETRANGE || TB_MARKBUTTON || TTM_NEWTOOLRECTA || WM_PSD_YAFULLPAGERECT */:
                ::printh(screenConsoleBufferHandle, ACM_OPENA); ::printg(screenConsoleBufferHandle, ": [");
                    ::printmln(screenConsoleBufferHandle, "    Combo Box (Extended) -> Get Combo Control");
                    ::printmln(screenConsoleBufferHandle, "    Progress Bar -> Set Range");
                    ::printmln(screenConsoleBufferHandle, "    Rebar -> Set Band Information");
                    ::printmln(screenConsoleBufferHandle, "    Scrollbar -> Get Parts");
                    ::printmln(screenConsoleBufferHandle, "    Trackbar -> Set Range");
                    ::printmln(screenConsoleBufferHandle, "    Toolbar -> Mark Button");
                    ::printmln(screenConsoleBufferHandle, "    Tooltips -> New Tool");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Page Setup Dialog Full Page");
                 ::printge(screenConsoleBufferHandle, "]");
            break;
            case CBEM_GETEDITCONTROL /* -> IE_GETPAINTDC || PBM_GETRANGE || RB_SETPARENT || SB_GETBORDERS || TBM_SETRANGEMIN || TTM_RELAYEVENT */:
                ::printh(screenConsoleBufferHandle, CBEM_GETEDITCONTROL); ::printg(screenConsoleBufferHandle, ": [");
                    ::printmln(screenConsoleBufferHandle, "    Rich Editor -> Get Paint Device Context");
                    ::printmln(screenConsoleBufferHandle, "    Progress Bar -> Get Range");
                    ::printmln(screenConsoleBufferHandle, "    Rebar -> Set Parent");
                    ::printmln(screenConsoleBufferHandle, "    Scrollbar -> Get Borders");
                    ::printmln(screenConsoleBufferHandle, "    Trackbar -> Set Range Minimum");
                    ::printmln(screenConsoleBufferHandle, "    Tooltips -> Relay Event");
                 ::printge(screenConsoleBufferHandle, "]");
            break;
            case CBEM_GETEXSTYLE /* -> CBEM_GETEXTENDEDSTYLE || PBM_SETBARCOLOR || RB_GETRECT || SB_SIMPLE || TBM_CLEARTICS || TB_ISBUTTONENABLED || TTM_SETTOOLINFOA */: break;
            /*case CDM_GETFILEPATH: break;*/
            /*case CDM_GETFOLDERPATH: break;*/
            case CBEM_GETIMAGELIST /* -> HKM_SETRULES || PBM_DELTAPOS || RB_GETBARINFO || SB_GETTEXTLENGTHA || TBM_GETTIC || TB_PRESSBUTTON || TTM_SETDELAYTIME || WM_PSD_MARGINRECT */: break;
            case CBEM_GETITEMA /* -> PBM_SETSTEP || RB_SETBARINFO || SB_SETPARTS || TBM_SETTIC || TB_HIDEBUTTON || TB_SETBUTTONINFOW || TTM_ADDTOOLA || WM_PSD_GREEKTEXTRECT || DDM_END */: break;
            case CBEM_GETITEMW /* -> RB_GETROWCOUNT || SB_GETTEXTW || TB_ISBUTTONINDETERMINATE || TTM_GETTOOLCOUNT */: break;
            case CBEM_HASEDITCHANGED /* -> RB_INSERTBANDW || SB_GETRECT || TBM_SETSEL || TB_ISBUTTONCHECKED || TTM_HITTESTA || WIZ_QUERYNUMPAGES */: break;
            case CBEM_INSERTITEMA /* -> DM_SETDEFID || HKM_SETHOTKEY || PBM_SETRANGE || RB_INSERTBANDA || SB_SETTEXTA || TBM_GETRANGEMIN || TB_ENABLEBUTTON || TTM_ACTIVATE || WM_CHOOSEFONT_GETLOGFONT || WM_PSD_FULLPAGERECT || DDM_DRAW */: break;
            case CBEM_INSERTITEMW /* -> RB_SETBANDINFOW || SB_SETTEXTW || TBM_SETSELSTART || TB_ISBUTTONPRESSED || TTM_GETTEXTA || WIZ_NEXT */: break;
            case CBEM_SETEXSTYLE /* -> CBEM_SETEXTENDEDSTYLE || PBM_GETPOS || RB_HITTEST || SB_SETMINHEIGHT || TBM_SETRANGEMAX || TTM_GETTOOLINFOA */: break;
            case CBEM_SETIMAGELIST /* -> DM_REPOSITION || HKM_GETHOTKEY || PBM_SETPOS || RB_DELETEBAND || SB_GETTEXTA || TBM_GETRANGEMAX || TB_CHECKBUTTON || WM_PSD_MINMARGINRECT || DDM_BEGIN || DDM_CLOSE */: break;
            case CBEM_SETITEMA /* -> PBM_STEPIT || TBM_SETPOS || TB_INDETERMINATE || TTM_DELTOOLA || WM_PSD_ENVSTAMPRECT */: break;
            case CBEM_SETITEMW /* -> RB_GETBANDCOUNT || SB_GETTEXTLENGTHW || TBM_SETSELEND || TB_ISBUTTONHIDDEN || TTM_UPDATETIPTEXTA || WIZ_PREV */: break;
            /*case CDM_GETFOLDERIDLIST: break;*/
            case CDM_HIDECONTROL /* -> EM_GETIMECOLOR || IPM_ISBLANK || PSM_RESTARTWINDOWS || UDM_SETBUDDY */: break;
            /*case CDM_FIRST: break;*/
            /*case CDM_GETSPEC: break;*/
            case CDM_LAST /* -> EM_SETBIDIOPTIONS || IE_DOCOMMAND || MCIWNDM_NOTIFYMODE */: break;
            /*case CDM_SETCONTROLTEXT: break;*/
            case CDM_SETDEFEXT /* -> EM_SETIMEOPTIONS || PSM_REBOOTSYSTEM || UDM_GETBUDDY */: break;
            /*case DDM_BEGIN: break;*/
            /*case DDM_CLOSE: break;*/
            /*case DDM_DRAW: break;*/
            /*case DDM_END: break;*/
            case DDM_SETFMT /* -> DM_GETDEFID || NIN_SELECT || TBM_GETPOS || WM_PSD_PAGESETUPDLG || WM_USER */: break;
            case DL_BEGINDRAG /* -> MCIWNDM_GETINACTIVETIMER || PSM_IDTOINDEX || TB_BUTTONCOUNT || TTM_SETMAXTIPWIDTH */: break;
            case DL_CANCELDRAG /* -> PSM_RECALCPAGESIZES */: break;
            case DL_DRAGGING /* -> PSM_INDEXTOID */: break;
            case DL_DROPPED /* -> PSM_GETRESULT */: break;
            /*case DM_GETDEFID: break;*/
            /*case DM_REPOSITION: break;*/
            /*case DM_SETDEFID: break;*/
            case EM_AUTOURLDETECT /* -> TB_GETSTRINGW */: break;
            case EM_CANPASTE /* -> ADDTOOLW || TB_LOADIMAGES */: break;
            case EM_CANREDO /* -> TB_GETEXTENDEDSTYLE */: break;
            case EM_CANUNDO: break;
            case EM_CHARFROMPOS: break;
            case EM_CONVPOSITION /* -> PSM_QUERYSIBLINGS || UDM_GETACCEL */: break;
            case EM_DISPLAYBAND /* -> TB_GETRECT || TTM_DELTOOLW */: break;
            case EM_EMPTYUNDOBUFFER: break;
            case EM_EXGETSEL /* -> TB_SETHOTIMAGELIST || TTM_NEWTOOLRECTW */: break;
            case EM_EXLIMITTEXT /* -> TB_GETHOTIMAGELIST || TTM_GETTOOLINFOW */: break;
            case EM_EXLINEFROMCHAR /* -> TB_SETDISABLEDIMAGELIST || TTM_SETTOOLINFOW */: break;
            case EM_EXSETSEL /* -> TB_GETDISABLEDIMAGELIST || TTM_HITTESTW */: break;
            case EM_FINDTEXT /* -> TB_SETSTYLE || TTM_GETTEXTW */: break;
            case EM_FINDTEXTEX /* -> TB_GETINSERTMARK */: break;
            case EM_FINDTEXTEXW /* -> MCIWNDM_GETFILENAMEA */: break;
            case EM_FINDTEXTW /* -> MCIWNDM_PLAYTO || WM_CAP_FILE_SAVEASW */: break;
            case EM_FINDWORDBREAK /* -> TB_SAVERESTOREW */: break;
            case EM_FMTLINES: break;
            case EM_FORMATRANGE /* -> TB_GETSTYLE || TTM_UPDATETIPTEXTW */: break;
            case EM_GETAUTOURLDETECT /* -> TB_GETSTRINGA */: break;
            case EM_GETBIDIOPTIONS /* -> IE_GETCOMMAND */: break;
            case EM_GETCHARFORMAT /* -> TB_GETBUTTONSIZE || TTM_ENUMTOOLSW */: break;
            case EM_GETCTFMODEBIAS: break;
            case EM_GETCTFOPENSTATUS: break;
            case EM_GETEDITSTYLE /* -> MCIWNDM_NOTIFYERROR */: break;
            case EM_GETEVENTMASK /* -> TB_SETBUTTONWIDTH || TTM_GETCURRENTTOOLW */: break;
            case EM_GETFIRSTVISIBLELINE: break;
            case EM_GETHANDLE: break;
            case EM_GETHYPHENATEINFO: break;
            /*case EM_GETIMECOLOR: break;*/
            case EM_GETIMECOMPMODE: break;
            case EM_GETIMECOMPTEXT: break;
            case EM_GETIMEMODEBIAS /* -> MCIWNDM_SETPALETTE || PSM_SETHEADERSUBTITLEA */: break;
            case EM_GETIMEOPTIONS /* -> PSM_CANCELTOCLOSE || UDM_SETACCEL */: break;
            case EM_GETIMEPROPERTY: break;
            case EM_GETIMESTATUS: break;
            case EM_GETLANGOPTIONS /* -> MCIWNDM_VALIDATEMEDIA || PSM_SETCURSEL || PSM_SETFINISHTEXTA || PSM_SETFINISHTEXTW || WM_CAP_FILE_GET_CAPTURE_FILEW || MCIWNDM_VALIDATEMEDIA */: break;
            case EM_GETLIMITTEXT: break;
            case EM_GETLINE: break;
            case EM_GETLINECOUNT: break;
            case EM_GETMARGINS: break;
            case EM_GETMODIFY: break;
            case EM_GETOLEINTERFACE /* -> TB_SETMAXTEXTROWS */: break;
            case EM_GETOPTIONS /* -> TB_MAPACCELERATORA */: break;
            case EM_GETPAGE: break;
            case EM_GETPAGEROTATE: break;
            case EM_GETPARAFORMAT /* -> TB_GETTEXTROWS */: break;
            case EM_GETPASSWORDCHAR: break;
            /*case EM_GETPUNCTUATION: break;*/
            /*case EM_GETQUERYRTFOBJ: break;*/
            case EM_GETRECT: break;
            case EM_GETREDONAME /* -> TB_SETPADDING */: break;
            case EM_GETSCROLLPOS: break;
            case EM_GETSEL: break;
            case EM_GETSELTEXT /* -> TB_GETOBJECT */: break;
            case EM_GETTEXTEX: break;
            case EM_GETTEXTLENGTHEX: break;
            case EM_GETTEXTMODE /* -> TB_MAPACCELERATORW */: break;
            case EM_GETTEXTRANGE /* -> TB_GETBUTTONTEXTW */: break;
            case EM_GETTHUMB: break;
            case EM_GETTYPOGRAPHYOPTIONS /* -> IE_GETGESTURE || MCIWNDM_NOTIFYMEDIA */: break;
            case EM_GETUNDONAME /* -> TB_GETPADDING */: break;
            case EM_GETVIEWKIND: break;
            case EM_GETWORDBREAKPROC: break;
            case EM_GETWORDBREAKPROCEX /* -> TB_SETINSERTMARK */: break;
            /*case EM_GETWORDWRAPMODE: break;*/
            case EM_GETZOOM /* -> MCIWNDM_GETFILENAMEW */: break;
            case EM_HIDESELECTION /* -> TB_GETBUTTONINFOW */: break;
            case EM_ISIME: break;
            case EM_LIMITTEXT /* -> EM_SETLIMITTEXT */: break;
            case EM_LINEFROMCHAR: break;
            case EM_LINEINDEX: break;
            case EM_LINELENGTH: break;
            case EM_LINESCROLL: break;
            case EM_OUTLINE: break;
            case EM_PASTESPECIAL: break;
            case EM_POSFROMCHAR: break;
            case EM_RECONVERSION /* -> MCIWNDM_GETDEVICEA || PSM_SETHEADERTITLEA || WM_CAP_FILE_SAVEDIBW */: break;
            case EM_REDO /* -> TB_SETEXTENDEDSTYLE */: break;
            case EM_REPLACESEL: break;
            case EM_REQUESTRESIZE /* -> TB_GETBUTTONINFOA */: break;
            case EM_SCROLL: break;
            case EM_SCROLLCARET: break;
            case EM_SELECTIONTYPE /* -> TB_SETBUTTONINFOA */: break;
            /*case EM_SETBIDIOPTIONS: break;*/
            case EM_SETBKGNDCOLOR /* -> TB_INSERTBUTTONW */: break;
            case EM_SETCHARFORMAT /* -> TB_ADDBUTTONSW */: break;
            case EM_SETCTFMODEBIAS: break;
            case EM_SETCTFOPENSTATUS: break;
            case EM_SETEDITSTYLE /* -> IE_GETMENU */: break;
            case EM_SETEVENTMASK /* -> TB_HITTEST */: break;
            case EM_SETFONT: break;
            case EM_SETFONTSIZE: break;
            case EM_SETHANDLE: break;
            case EM_SETHYPHENATEINFO: break;
            /*case EM_SETIMECOLOR: break;*/
            case EM_SETIMEMODEBIAS /* -> MCIWNDM_GETPALETTE || PSM_SETHEADERTITLEW */: break;
            /*case EM_SETIMEOPTIONS: break;*/
            case EM_SETIMESTATUS: break;
            case EM_SETLANGOPTIONS /* -> MCIWNDM_GETTIMEFORMATA || PSM_SETTITLEW || WM_CAP_FILE_SET_CAPTURE_FILEW */: break;
            case EM_SETMARGINS: break;
            case EM_SETMODIFY: break;
            /*case EM_SETLIMITTEXT: break;*/
            case EM_SETOLECALLBACK /* -> TB_SETDRAWTEXTFLAGS */: break;
            case EM_SETOPTIONS /* -> TB_ADDSTRINGW */: break;
            case EM_SETPAGE: break;
            case EM_SETPAGEROTATE: break;
            case EM_SETPALETTE: break;
            case EM_SETPARAFORMAT /* -> TB_GETHOTITEM */: break;
            case EM_SETPASSWORDCHAR: break;
            /*case EM_SETPUNCTUATION: break*/
            case EM_SETQUERYRTFOBJ: break;
            case EM_SETREADONLY: break;
            case EM_SETRECT: break;
            case EM_SETRECTNP: break;
            case EM_SETSCROLLPOS: break;
            case EM_SETSEL: break;
            case EM_SETTABSTOPS: break;
            case EM_SETTARGETDEVICE /* -> TB_SETHOTITEM */: break;
            case EM_SETTEXTEX: break;
            case EM_SETTEXTMODE /* -> TB_GETINSERTMARKCOLOR */: break;
            case EM_SETTYPOGRAPHYOPTIONS /* -> IE_GETCOUNT */: break;
            case EM_SETUNDOLIMIT /* -> TB_MOVEBUTTON */: break;
            case EM_SETVIEWKIND: break;
            case EM_SETWORDBREAK: break;
            case EM_SETWORDBREAKPROC: break;
            case EM_SETWORDBREAKPROCEX /* -> TB_INSERTMARKHITTEST */: break;
            /*case EM_SETWORDWRAPMODE: break;*/
            case EM_SETZOOM /* -> MCIWNDM_GETDEVICEW */: break;
            case EM_SHOWSCROLLBAR: break;
            case EM_STOPGROUPTYPING /* -> TB_SETINSERTMARKCOLOR */: break;
            case EM_STREAMIN /* -> TB_SETANCHORHIGHLIGHT */: break;
            case EM_STREAMOUT /* -> TB_GETANCHORHIGHLIGHT */: break;
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
            case IE_GETINKRECT /* -> WM_CAP_SET_MCI_DEVICEW */: break;
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
            case LVM_GETBKIMAGEA: break;
            case LVM_GETBKIMAGEW: break;
            case LVM_GETCALLBACKMASK: break;
            case LVM_GETCOLUMNA: break;
            case LVM_GETCOLUMNORDERARRAY: break;
            case LVM_GETCOLUMNW: break;
            case LVM_GETCOLUMNWIDTH: break;
            case LVM_GETCOUNTPERPAGE: break;
            case LVM_GETEDITCONTROL: break;
            case LVM_GETEXTENDEDLISTVIEWSTYLE: break;
            case LVM_GETGROUPINFO: break;
            case LVM_GETGROUPMETRICS: break;
            case LVM_GETHEADER: break;
            case LVM_GETHOTCURSOR: break;
            case LVM_GETHOTITEM: break;
            case LVM_GETHOVERTIME: break;
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
            case LVM_GETNUMBEROFWORKAREAS: break;
            case LVM_GETORIGIN: break;
            case LVM_GETOUTLINECOLOR: break;
            case LVM_GETSELECTEDCOLUMN: break;
            case LVM_GETSELECTEDCOUNT: break;
            case LVM_GETSELECTIONMARK: break;
            case LVM_GETSTRINGWIDTHA: break;
            case LVM_GETSTRINGWIDTHW: break;
            case LVM_GETSUBITEMRECT: break;
            case LVM_GETTEXTBKCOLOR: break;
            case LVM_GETTEXTCOLOR: break;
            case LVM_GETTILEINFO: break;
            case LVM_GETTILEVIEWINFO: break;
            case LVM_GETTOOLTIPS: break;
            case LVM_GETTOPINDEX: break;
            case LVM_GETUNICODEFORMAT: break;
            case LVM_GETVIEW: break;
            case LVM_GETVIEWRECT: break;
            case LVM_GETWORKAREAS: break;
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
            case LVM_ISITEMVISIBLE: break;
            case LVM_MAPIDTOINDEX: break;
            case LVM_MAPINDEXTOID: break;
            case LVM_MOVEGROUP: break;
            case LVM_MOVEITEMTOGROUP: break;
            case LVM_REDRAWITEMS: break;
            case LVM_REMOVEALLGROUPS: break;
            case LVM_REMOVEGROUP: break;
            case LVM_SCROLL: break;
            case LVM_SETBKCOLOR: break;
            case LVM_SETBKIMAGEA: break;
            case LVM_SETCALLBACKMASK: break;
            case LVM_SETCOLUMNA: break;
            case LVM_SETCOLUMNORDERARRAY: break;
            case LVM_SETCOLUMNW: break;
            case LVM_SETCOLUMNWIDTH: break;
            case LVM_SETEXTENDEDLISTVIEWSTYLE: break;
            case LVM_SETGROUPINFO: break;
            case LVM_SETGROUPMETRICS: break;
            case LVM_SETHOTCURSOR /* -> LVM_SETHOTITEM */: break;
            /*case LVM_SETHOTITEM: break;*/
            case LVM_SETHOVERTIME: break;
            case LVM_SETICONSPACING: break;
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
            case LVM_SETSELECTEDCOLUMN: break;
            case LVM_SETSELECTIONMARK: break;
            case LVM_SETTEXTBKCOLOR: break;
            case LVM_SETTEXTCOLOR: break;
            case LVM_SETTILEINFO: break;
            case LVM_SETTILEVIEWINFO: break;
            case LVM_SETTILEWIDTH: break;
            case LVM_SETTOOLTIPS: break;
            case LVM_SETUNICODEFORMAT: break;
            case LVM_SETVIEW: break;
            case LVM_SETWORKAREAS: break;
            case LVM_SORTGROUPS: break;
            case LVM_SORTITEMS: break;
            case LVM_SUBITEMHITTEST: break;
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
            /*case MCIWNDM_GETPALETTE: break;*/
            /*case MCIWNDM_GETTIMEFORMATA: break;*/
            /*case MCIWNDM_GETTIMEFORMATW: break;*/
            case MCIWNDM_GETZOOM /* -> PSM_UNCHANGED || UDM_SETBASE */: break;
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
            /*case MCIWNDM_SETPALETTE: break;*/
            case MCIWNDM_SETTIMEFORMATA /* -> PSM_INSERTPAGE */: break;
            case MCIWNDM_SETTIMEFORMATW: break;
            /*case MCIWNDM_VALIDATEMEDIA: break;*/
            case MSG_FTS_JUMP_QWORD /* -> RB_SHOWBAND || TB_GETTOOLTIPS */: break;
            case MSG_FTS_JUMP_VA /* -> TBM_GETBUDDY || TB_AUTOSIZE || TTM_SETTITLEW */: break;
            case MSG_FTS_WHERE_IS_IT /* -> RB_SETPALETTE || TB_SETPARENT */: break;
            case MSG_GET_DEFFONT /* -> TB_GETBUTTONTEXTA */: break;
            case MSG_REINDEX_REQUEST /* -> TB_SETTOOLTIPS */: break;
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
            case PSM_APPLY /* -> UDM_GETBASE */: break;
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
            case PSM_PRESSBUTTON /* -> UDM_SETPOS32 || WM_CAP_DRIVER_GET_VERSIONW */: break;
            /*case PSM_QUERYSIBLINGS: break;*/
            /*case PSM_REBOOTSYSTEM: break;*/
            /*case PSM_RECALCPAGESIZES: break;*/
            /*case PSM_REMOVEPAGE: break;*/
            /*case PSM_RESTARTWINDOWS: break;*/
            /*case PSM_SETCURSEL: break;*/
            case PSM_SETCURSELID /* -> UDM_GETPOS32 */: break;
            case PSM_SETFINISHTEXTA: break;
            /*case PSM_SETFINISHTEXTW: break;*/
            /*case PSM_SETHEADERSUBTITLEA: break;*/
            /*case PSM_SETHEADERSUBTITLEW: break;*/
            /*case PSM_SETHEADERTITLEA: break;*/
            /*case PSM_SETHEADERTITLEW: break;*/
            case PSM_SETTITLEA /* -> UDM_SETRANGE32 */: break;
            /*case PSM_SETTITLEW: break;*/
            case PSM_SETWIZBUTTONS /* -> UDM_GETRANGE32 || WM_CAP_DRIVER_GET_NAMEW */: break;
            /*case PSM_UNCHANGED: break;*/
            case RB_BEGINDRAG /* -> TBM_GETLINESIZE */: break;
            /*case RB_DELETEBAND: break;*/
            case RB_DRAGMOVE /* -> TBM_GETCHANNELRECT || TB_SAVERESTOREA || TTM_SETMARGIN */: break;
            case RB_ENDDRAG /* -> TBM_GETTHUMBRECT || TB_COMMANDTOINDEX || TTM_GETMAXTIPWIDTH */: break;
            case RB_GETBANDBORDERS: break;
            /*case RB_GETBANDCOUNT: break;*/
            case RB_GETBANDINFOA /* -> TBM_SETTOOLTIPS || TB_GETITEMRECT || TTM_UPDATE */: break;
            case RB_GETBANDINFOW /* -> TBM_GETTHUMBLENGTH || TB_ADDSTRINGA || TTM_POP */: break;
            case RB_GETBARHEIGHT /* -> TBM_SETTHUMBLENGTH || TB_CUSTOMIZE || TTM_GETMARGIN */: break;
            /*case RB_GETBARINFO: break;*/
            case RB_GETBKCOLOR /* -> SB_GETTIPTEXTW || TBM_SETTICFREQ || TB_ADDBUTTONSA || TTM_SETTIPTEXTCOLOR */: break;
            case RB_GETPALETTE: break;
            /*case RB_GETRECT: break;*/
            /*case RB_GETROWCOUNT: break;*/
            case RB_GETROWHEIGHT /* -> SB_ISSIMPLE || TBM_GETPTICS || TB_ISBUTTONHIGHLIGHTED || TTM_ENUMTOOLSA */: break;
            case RB_GETTEXTCOLOR /* -> TBM_GETPAGESIZE || TB_DELETEBUTTON || TTM_GETTIPBKCOLOR */: break;
            case RB_GETTOOLTIPS /* -> SB_SETTIPTEXTW || TBM_GETSELSTART || TB_SETSTATE || TTM_TRACKACTIVATE */: break;
            /*case RB_HITTEST: break;*/
            case RB_IDTOINDEX /* -> SB_SETTIPTEXTA || TBM_GETNUMTICS || TTM_WINDOWFROMPOINT */: break;
            /*case RB_INSERTBANDA: break;*/
            /*case RB_INSERTBANDW: break;*/
            case RB_MAXIMIZEBAND /* -> TBM_SETTIPSIDE || TB_SETBUTTONSIZE || TTM_ADJUSTRECT */: break;
            case RB_MINIMIZEBAND /* -> TBM_GETTOOLTIPS || TB_BUTTONSTRUCTSIZE || TTM_GETBUBBLESIZE */: break;
            case RB_MOVEBAND /* -> TB_SETROWS */: break;
            case RB_PUSHCHEVRON /* -> TB_CHANGEBITMAP */: break;
            /*case RB_SETBANDINFOA: break;*/
            /*case RB_SETBANDINFOW: break;*/
            /*case RB_SETBARINFO: break;*/
            case RB_SETBKCOLOR /* -> TBM_CLEARSEL || TB_ADDBITMAP || TTM_SETTIPBKCOLOR */: break;
            /*case RB_SETPALETTE: break;*/
            /*case RB_SETPARENT: break;*/
            case RB_SETTEXTCOLOR /* -> TBM_SETPAGESIZE || TB_INSERTBUTTONA || TTM_GETDELAYTIME */: break;
            case RB_SETTOOLTIPS /* -> SB_GETTIPTEXTA || TBM_GETSELEND || TB_GETSTATE || TTM_TRACKPOSITION */: break;
            /*case RB_SHOWBAND: break;*/
            case RB_SIZETORECT /* -> TBM_SETLINESIZE || TB_GETBUTTON || TTM_GETTIPTEXTCOLOR */: break;
            case SBM_ENABLE_ARROWS: break;
            case SBM_GETPOS: break;
            case SBM_GETRANGE: break;
            /*case SBM_GETSCROLLBARINFO: break;*/
            case SBM_GETSCROLLINFO: break;
            case SBM_SETPOS: break;
            case SBM_SETRANGE: break;
            case SBM_SETRANGEREDRAW: break;
            case SBM_SETSCROLLINFO: break;
            /*case SB_GETBORDERS: break;*/
            /*case SB_GETICON: break;*/
            /*case SB_GETPARTS: break;*/
            /*case SB_GETRECT: break;*/
            /*case SB_GETTEXTA: break;*/
            /*case SB_GETTEXTLENGTHA: break;*/
            /*case SB_GETTEXTLENGTHW: break;*/
            /*case SB_GETTEXTW: break;*/
            /*case SB_GETTIPTEXTA: break;*/
            /*case SB_GETTIPTEXTW: break;*/
            /*case SB_ISSIMPLE: break;*/
            case SB_SETICON /* -> TBM_GETTICPOS || TTM_GETCURRENTTOOLA */: break;
            /*case SB_SETMINHEIGHT: break;*/
            /*case SB_SETPARTS: break;*/
            /*case SB_SETTEXTA: break;*/
            /*case SB_SETTEXTW: break;*/
            /*case SB_SETTIPTEXTA: break;*/
            /*case SB_SETTIPTEXTW: break;*/
            /*case SB_SIMPLE: break;*/
            case SM_GETCURFOCUSA /* -> UM_GETGROUPSELA */: break;
            case SM_GETCURFOCUSW /* -> UM_GETGROUPSELW */: break;
            case SM_GETOPTIONS /* -> UM_GETCURFOCUSA */: break;
            case SM_GETSELCOUNT /* -> UM_GETSELCOUNT || WM_CPL_LAUNCH */: break;
            case SM_GETSERVERSELA /* -> UM_GETUSERSELA || WM_CPL_LAUNCHED */: break;
            case SM_GETSERVERSELW /* -> UM_GETUSERSELW */: break;
            case TAPI_REPLY: ::printmln(screenConsoleBufferHandle, "Telephony API -> Reply"); break;
            /*case TBM_CLEARSEL: break;*/
            /*case TBM_CLEARTICS: break;*/
            /*case TBM_GETBUDDY: break;*/
            /*case TBM_GETCHANNELRECT: break;*/
            /*case TBM_GETLINESIZE: break;*/
            /*case TBM_GETNUMTICS: break;*/
            /*case TBM_GETPAGESIZE: break;*/
            /*case TBM_GETPOS: break;*/
            /*case TBM_GETPTICS: break;*/
            /*case TBM_GETRANGEMAX: break;*/
            /*case TBM_GETRANGEMIN: break;*/
            /*case TBM_GETSELEND: break;*/
            /*case TBM_GETSELSTART: break;*/
            /*case TBM_GETTHUMBLENGTH: break;*/
            /*case TBM_GETTHUMBRECT: break;*/
            /*case TBM_GETTIC: break;*/
            /*case TBM_GETTICPOS: break;*/
            /*case TBM_GETTOOLTIPS: break;*/
            case TBM_SETBUDDY /* -> TB_SETBITMAPSIZE || TTM_SETTITLEA */: break;
            /*case TBM_SETLINESIZE: break;*/
            /*case TBM_SETPAGESIZE: break;*/
            /*case TBM_SETPOS: break;*/
            /*case TBM_SETRANGE: break;*/
            /*case TBM_SETRANGEMAX: break;*/
            /*case TBM_SETRANGEMIN: break;*/
            /*case TBM_SETSEL: break;*/
            /*case TBM_SETSELEND: break;*/
            /*case TBM_SETSELSTART: break;*/
            /*case TBM_SETTHUMBLENGTH: break;*/
            /*case TBM_SETTIC: break;*/
            /*case TBM_SETTICFREQ: break;*/
            /*case TBM_SETTIPSIDE: break;*/
            /*case TBM_SETTOOLTIPS: break;*/
            /*case TB_ADDBITMAP: break;*/
            /*case TB_ADDBUTTONSA: break;*/
            /*case TB_ADDBUTTONSW: break;*/
            /*case TB_ADDSTRINGA: break;*/
            /*case TB_ADDSTRINGW: break;*/
            /*case TB_AUTOSIZE: break;*/
            /*case TB_BUTTONCOUNT: break;*/
            /*case TB_BUTTONSTRUCTSIZE: break;*/
            /*case TB_CHANGEBITMAP: break;*/
            /*case TB_CHECKBUTTON: break;*/
            /*case TB_COMMANDTOINDEX: break;*/
            /*case TB_CUSTOMIZE: break;*/
            /*case TB_DELETEBUTTON: break;*/
            /*case TB_ENABLEBUTTON: break;*/
            /*case TB_GETANCHORHIGHLIGHT: break;*/
            case TB_GETBITMAP: break;
            case TB_GETBITMAPFLAGS: break;
            /*case TB_GETBUTTON: break;*/
            /*case TB_GETBUTTONINFOA: break;*/
            /*case TB_GETBUTTONINFOW: break;*/
            /*case TB_GETBUTTONSIZE: break;*/
            /*case TB_GETBUTTONTEXTA: break;*/
            /*case TB_GETBUTTONTEXTW: break;*/
            /*case TB_GETDISABLEDIMAGELIST: break;*/
            /*case TB_GETEXTENDEDSTYLE: break;*/
            /*case TB_GETHOTIMAGELIST: break;*/
            /*case TB_GETHOTITEM: break;*/
            case TB_GETIMAGELIST: break;
            /*case TB_GETINSERTMARK: break;*/
            /*case TB_GETINSERTMARKCOLOR: break;*/
            /*case TB_GETITEMRECT: break;*/
            case TB_GETMAXSIZE: break;
            /*case TB_GETOBJECT: break;*/
            /*case TB_GETPADDING: break;*/
            /*case TB_GETRECT: break;*/
            case TB_GETROWS: break;
            /*case TB_GETSTATE: break;*/
            /*case TB_GETSTRINGA: break;*/
            /*case TB_GETSTRINGW: break;*/
            /*case TB_GETSTYLE: break;*/
            /*case TB_GETTEXTROWS: break;*/
            /*case TB_GETTOOLTIPS: break;*/
            /*case TB_HIDEBUTTON: break;*/
            /*case TB_HITTEST: break;*/
            /*case TB_INDETERMINATE: break;*/
            /*case TB_INSERTBUTTONA: break;*/
            /*case TB_INSERTBUTTONW: break;*/
            /*case TB_INSERTMARKHITTEST: break;*/
            /*case TB_ISBUTTONCHECKED: break;*/
            /*case TB_ISBUTTONENABLED: break;*/
            /*case TB_ISBUTTONHIDDEN: break;*/
            /*case TB_ISBUTTONHIGHLIGHTED: break;*/
            /*case TB_ISBUTTONINDETERMINATE: break;*/
            /*case TB_ISBUTTONPRESSED: break;*/
            /*case TB_LOADIMAGES: break;*/
            /*case TB_MAPACCELERATORA: break;*/
            /*case TB_MAPACCELERATORW: break;*/
            /*case TB_MARKBUTTON: break;*/
            /*case TB_MOVEBUTTON: break;*/
            /*case TB_PRESSBUTTON: break;*/
            case TB_REPLACEBITMAP: break;
            /*case TB_SAVERESTOREA: break;*/
            /*case TB_SAVERESTOREW: break;*/
            /*case TB_SETANCHORHIGHLIGHT: break;*/
            /*case TB_SETBITMAPSIZE: break;*/
            /*case TB_SETBUTTONINFOA: break;*/
            /*case TB_SETBUTTONINFOW: break;*/
            /*case TB_SETBUTTONSIZE: break;*/
            /*case TB_SETBUTTONWIDTH: break;*/
            case TB_SETCMDID: break;
            /*case TB_SETDISABLEDIMAGELIST: break;*/
            /*case TB_SETDRAWTEXTFLAGS: break;*/
            /*case TB_SETEXTENDEDSTYLE: break;*/
            /*case TB_SETHOTIMAGELIST: break;*/
            /*case TB_SETHOTITEM: break;*/
            case TB_SETIMAGELIST: break;
            case TB_SETINDENT: break;
            /*case TB_SETINSERTMARK: break;*/
            /*case TB_SETINSERTMARKCOLOR: break;*/
            /*case TB_SETMAXTEXTROWS: break;*/
            /*case TB_SETPADDING: break;*/
            /*case TB_SETPARENT: break;*/
            /*case TB_SETROWS: break;*/
            /*case TB_SETSTATE: break;*/
            /*case TB_SETSTYLE: break;*/
            /*case TB_SETTOOLTIPS: break;*/
            /*case TTM_ACTIVATE: break;*/
            /*case TTM_ADDTOOLA: break;*/
            /*case TTM_ADDTOOLW: break;*/
            /*case TTM_ADJUSTRECT: break;*/
            /*case TTM_DELTOOLA: break;*/
            /*case TTM_DELTOOLW: break;*/
            /*case TTM_ENUMTOOLSA: break;*/
            /*case TTM_ENUMTOOLSW: break;*/
            /*case TTM_GETBUBBLESIZE: break;*/
            /*case TTM_GETCURRENTTOOLA: break;*/
            /*case TTM_GETCURRENTTOOLW: break;*/
            /*case TTM_GETDELAYTIME: break;*/
            /*case TTM_GETMARGIN: break;*/
            /*case TTM_GETMAXTIPWIDTH: break;*/
            /*case TTM_GETTEXTA: break;*/
            /*case TTM_GETTEXTW: break;*/
            /*case TTM_GETTIPBKCOLOR: break;*/
            /*case TTM_GETTIPTEXTCOLOR: break;*/
            /*case TTM_GETTOOLCOUNT: break;*/
            /*case TTM_GETTOOLINFOA: break;*/
            /*case TTM_GETTOOLINFOW: break;*/
            /*case TTM_HITTESTA: break;*/
            /*case TTM_HITTESTW: break;*/
            /*case TTM_NEWTOOLRECTA: break;*/
            /*case TTM_NEWTOOLRECTW: break;*/
            /*case TTM_POP: break;*/
            /*case TTM_RELAYEVENT: break;*/
            /*case TTM_SETDELAYTIME: break;*/
            /*case TTM_SETMARGIN: break;*/
            /*case TTM_SETMAXTIPWIDTH: break;*/
            /*case TTM_SETTIPBKCOLOR: break;*/
            /*case TTM_SETTIPTEXTCOLOR: break;*/
            /*case TTM_SETTITLEA: break;*/
            /*case TTM_SETTITLEW: break;*/
            /*case TTM_SETTOOLINFOA: break;*/
            /*case TTM_SETTOOLINFOW: break;*/
            /*case TTM_TRACKACTIVATE: break;*/
            /*case TTM_TRACKPOSITION: break;*/
            /*case TTM_UPDATE: break;*/
            /*case TTM_UPDATETIPTEXTA: break;*/
            /*case TTM_UPDATETIPTEXTW: break;*/
            /*case TTM_WINDOWFROMPOINT: break;*/
            /*case UDM_GETACCEL: break;*/
            /*case UDM_GETBASE: break;*/
            /*case UDM_GETBUDDY: break;*/
            /*case UDM_GETPOS: break;*/
            /*case UDM_GETPOS32: break;*/
            /*case UDM_GETRANGE: break;*/
            /*case UDM_GETRANGE32: break;*/
            /*case UDM_SETACCEL: break;*/
            /*case UDM_SETBASE: break;*/
            /*case UDM_SETBUDDY: break;*/
            /*case UDM_SETPOS: break;*/
            /*case UDM_SETPOS32: break;*/
            /*case UDM_SETRANGE: break;*/
            /*case UDM_SETRANGE32: break;*/
            /*case UM_GETCURFOCUSA: break;*/
            case UM_GETCURFOCUSW: break;
            /*case UM_GETGROUPSELA: break;*/
            /*case UM_GETGROUPSELW: break;*/
            case UM_GETOPTIONS: break;
            case UM_GETOPTIONS2: break;
            /*case UM_GETSELCOUNT: break;*/
            /*case UM_GETUSERSELA: break;*/
            /*case UM_GETUSERSELW: break;*/
            /*case WIZ_NEXT: break;*/
            /*case WIZ_PREV: break;*/
            /*case WIZ_QUERYNUMPAGES: break;*/
            case WLX_WM_SAS: ::printmln(screenConsoleBufferHandle, "..."); break;
            case WM_ACTIVATE: ::printmln(screenConsoleBufferHandle, "Windows -> Activate"); break;
            case WM_ACTIVATEAPP: ::printmln(screenConsoleBufferHandle, "Windows -> Activate Application"); break;
            case WM_AFXFIRST: ::printmln(screenConsoleBufferHandle, "..."); break;
            case WM_AFXLAST: ::printmln(screenConsoleBufferHandle, "..."); break;
            case WM_APP: ::printmln(screenConsoleBufferHandle, "Windows -> Application"); break;
            case WM_APPCOMMAND: ::printmln(screenConsoleBufferHandle, "Windows -> Application Command"); break;
            case WM_ASKCBFORMATNAME: ::printmln(screenConsoleBufferHandle, "..."); break;
            case WM_CANCELJOURNAL: ::printmln(screenConsoleBufferHandle, "Windows -> Cancel Journal"); break;
            case WM_CANCELMODE: ::printmln(screenConsoleBufferHandle, "Windows -> Cancel Mode"); break;
            case WM_CAPTURECHANGED: ::printmln(screenConsoleBufferHandle, "Windows -> Capture Changed"); break;
            /*case WM_CAP_DRIVER_GET_NAMEW: break;*/
            /*case WM_CAP_DRIVER_GET_VERSIONW: break;*/
            /*case WM_CAP_FILE_GET_CAPTURE_FILEW: break;*/
            /*case WM_CAP_FILE_SAVEASW: break;*/
            /*case WM_CAP_FILE_SAVEDIBW: break;*/
            /*case WM_CAP_FILE_SET_CAPTURE_FILEW: break;*/
            case WM_CAP_GET_MCI_DEVICEW: ::printmln(screenConsoleBufferHandle, "..."); break;
            case WM_CAP_PAL_OPENW: ::printmln(screenConsoleBufferHandle, "..."); break;
            case WM_CAP_PAL_SAVEW: ::printmln(screenConsoleBufferHandle, "..."); break;
            /*case WM_CAP_SET_CALLBACK_ERRORW: break;*/
            /*case WM_CAP_SET_CALLBACK_STATUSW: break;*/
            /*case WM_CAP_SET_MCI_DEVICEW: break;*/
            /*case WM_CAP_UNICODE_START: break;*/
            case WM_CHANGECBCHAIN: ::printmln(screenConsoleBufferHandle, "Windows -> Change Control Box Chain"); break;
            case WM_CHANGEUISTATE: ::printmln(screenConsoleBufferHandle, "Windows -> Change User-Interface State"); break;
            case WM_CHAR: ::printmln(screenConsoleBufferHandle, "Windows -> Character"); break;
            case WM_CHARTOITEM: ::printmln(screenConsoleBufferHandle, "Windows -> Character to Item"); break;
            case WM_CHILDACTIVATE: ::printmln(screenConsoleBufferHandle, "Windows -> Child Activate"); break;
            /*case WM_CHOOSEFONT_GETLOGFONT: break;*/
            /*case WM_CHOOSEFONT_SETFLAGS: break;*/
            /*case WM_CHOOSEFONT_SETLOGFONT: break;*/
            case WM_CLEAR: ::printmln(screenConsoleBufferHandle, "Windows -> Clear"); break;
            case WM_CLOSE: ::printmln(screenConsoleBufferHandle, "Windows -> Close"); {
                ::DestroyWindow(windowHandle);
                ::PostQuitMessage(0);
            } break;
            case WM_COMMAND: ::printmln(screenConsoleBufferHandle, "Windows -> Command"); break;
            case WM_COMMNOTIFY: ::printmln(screenConsoleBufferHandle, "Windows -> Command Notify"); break;
            case WM_COMPACTING: ::printmln(screenConsoleBufferHandle, "Windows -> Compacting"); break;
            case WM_COMPAREITEM: ::printmln(screenConsoleBufferHandle, "Windows -> Compare Item"); break;
            case WM_CONTEXTMENU: ::printmln(screenConsoleBufferHandle, "Windows -> Context Menu"); break;
            case WM_CONVERTREQUEST: ::printmln(screenConsoleBufferHandle, "Windows -> Convert Request"); break;
            case WM_CONVERTRESULT: ::printmln(screenConsoleBufferHandle, "Windows -> Convert Result"); break;
            case WM_COPY: ::printmln(screenConsoleBufferHandle, "Windows -> Copy"); break;
            case WM_COPYDATA: ::printmln(screenConsoleBufferHandle, "Windows -> Copy Data"); break;
            case WM_COPYGLOBALDATA: ::printmln(screenConsoleBufferHandle, "Windows -> Copy Global Data"); break;
            /*case WM_CPL_LAUNCH: break;*/
            /*case WM_CPL_LAUNCHED: break;*/
            case WM_CREATE: ::printmln(screenConsoleBufferHandle, "Windows -> Create"); break;
            case WM_CTLCOLOR: ::printmln(screenConsoleBufferHandle, "Windows -> Control Color"); break;
            case WM_CTLCOLORBTN: ::printmln(screenConsoleBufferHandle, "Windows -> Control Color Button"); break;
            case WM_CTLCOLORDLG: ::printmln(screenConsoleBufferHandle, "Windows -> Control Color Dialog"); break;
            case WM_CTLCOLOREDIT: ::printmln(screenConsoleBufferHandle, "Windows -> Control Color Editor"); break;
            case WM_CTLCOLORLISTBOX: ::printmln(screenConsoleBufferHandle, "Windows -> Control Color List Box"); break;
            case WM_CTLCOLORMSGBOX: ::printmln(screenConsoleBufferHandle, "Windows -> Control Color Message Box"); break;
            case WM_CTLCOLORSCROLLBAR: ::printmln(screenConsoleBufferHandle, "Windows -> Control Color Scrollbar"); break;
            case WM_CTLCOLORSTATIC: ::printmln(screenConsoleBufferHandle, "Windows -> Control Color Static"); break;
            case WM_CTLINIT: ::printmln(screenConsoleBufferHandle, "Windows -> Control Initiation"); break;
            case WM_CUT: ::printmln(screenConsoleBufferHandle, "Windows -> Cut"); break;
            case WM_DEADCHAR: ::printmln(screenConsoleBufferHandle, "Windows -> Dead Character"); break;
            case WM_DELETEITEM: ::printmln(screenConsoleBufferHandle, "Windows -> Delete Item"); break;
            case WM_DESTROY: ::printmln(screenConsoleBufferHandle, "Windows -> Destroy"); { ::PostQuitMessage(0); } break;
            case WM_DESTROYCLIPBOARD: ::printmln(screenConsoleBufferHandle, "Windows -> Destroy Clipboard"); break;
            case WM_DEVICECHANGE: ::printmln(screenConsoleBufferHandle, "Windows -> Device Change"); break;
            case WM_DEVMODECHANGE: ::printmln(screenConsoleBufferHandle, "Windows -> Device Mode Change"); break;
            case WM_DISPLAYCHANGE: ::printmln(screenConsoleBufferHandle, "Windows -> Display Change"); break;
            case WM_DRAWCLIPBOARD: ::printmln(screenConsoleBufferHandle, "Windows -> Draw Clipboard"); break;
            case WM_DRAWITEM: ::printmln(screenConsoleBufferHandle, "Windows -> Draw Item"); break;
            case WM_DROPFILES: ::printmln(screenConsoleBufferHandle, "Windows -> Drop Files"); break;
            case WM_ENABLE: ::printmln(screenConsoleBufferHandle, "Windows -> Enable"); break;
            case WM_ENDSESSION: ::printmln(screenConsoleBufferHandle, "Windows -> End Session"); break;
            case WM_ENTERIDLE: ::printmln(screenConsoleBufferHandle, "Windows -> Enter Idle"); break;
            case WM_ENTERMENULOOP: ::printmln(screenConsoleBufferHandle, "Windows -> Enter Menu Loop"); break;
            case WM_ENTERSIZEMOVE: ::printmln(screenConsoleBufferHandle, "Windows -> Enter Size Move"); break;
            case WM_ERASEBKGND: ::printmln(screenConsoleBufferHandle, "Windows -> Erase Background"); break;
            case WM_EXITMENULOOP: ::printmln(screenConsoleBufferHandle, "Windows -> Exit Menu Loop"); break;
            case WM_EXITSIZEMOVE: ::printmln(screenConsoleBufferHandle, "Windows -> Exit Size Move"); break;
            case WM_FONTCHANGE: ::printmln(screenConsoleBufferHandle, "Windows -> Font Change"); break;
            case WM_GETDLGCODE: ::printmln(screenConsoleBufferHandle, "Windows -> Get Dialog Code"); break;
            case WM_GETFONT: ::printmln(screenConsoleBufferHandle, "Windows -> Get Font"); break;
            case WM_GETHOTKEY: ::printmln(screenConsoleBufferHandle, "Windows -> Get Hotkey"); break;
            case WM_GETICON: ::printmln(screenConsoleBufferHandle, "Windows -> Get Icon"); break;
            case WM_GETMINMAXINFO: ::printmln(screenConsoleBufferHandle, "Windows -> Get Min-Maximum Information"); break;
            case WM_GETOBJECT: ::printmln(screenConsoleBufferHandle, "Windows -> Get Object"); break;
            case WM_GETTEXT: ::printmln(screenConsoleBufferHandle, "Windows -> Get Text"); break;
            case WM_GETTEXTLENGTH: ::printmln(screenConsoleBufferHandle, "Windows -> Get Text Length"); break;
            case WM_GLOBALRCCHANGE /* -> WM_PENMISCINFO */:
                ::printh(screenConsoleBufferHandle, ACM_OPENA); ::printg(screenConsoleBufferHandle, ": [");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Global RC Change");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Pen Miscellaneous Information");
                 ::printge(screenConsoleBufferHandle, "]");
            break;
            case WM_HANDHELDFIRST: ::printmln(screenConsoleBufferHandle, "Windows -> Hand-Held [FIRST]"); break;
            case WM_HANDHELDLAST: ::printmln(screenConsoleBufferHandle, "Windows -> Hand-Held [LAST]"); break;
            case WM_HEDITCTL /* -> WM_PENCTL */:
                ::printh(screenConsoleBufferHandle, ACM_OPENA); ::printg(screenConsoleBufferHandle, ": [");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Hand-Editing Control");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Pen Control");
                 ::printge(screenConsoleBufferHandle, "]");
            break;
            case WM_HELP: ::printmln(screenConsoleBufferHandle, "Windows -> Help"); break;
            case WM_HOOKRCRESULT: ::printmln(screenConsoleBufferHandle, "Windows -> Hook RC Result"); break;
            case WM_HOTKEY: ::printmln(screenConsoleBufferHandle, "Windows -> Hotkey"); break;
            case WM_HSCROLL: ::printmln(screenConsoleBufferHandle, "Windows -> Horizontal Scroll"); break;
            case WM_HSCROLLCLIPBOARD: ::printmln(screenConsoleBufferHandle, "Windows -> Horizontal Scroll Clipboard"); break;
            case WM_ICONERASEBKGND: ::printmln(screenConsoleBufferHandle, "Windows -> Icon Erase Background"); break;
            case WM_IMEKEYDOWN /* -> WM_IME_KEYDOWN */: ::printmln(screenConsoleBufferHandle, "Windows -> IME Key Down"); break;
            case WM_IMEKEYUP /* -> WM_IME_KEYUP */: ::printmln(screenConsoleBufferHandle, "Windows -> IME Key Up"); break;
            case WM_IME_CHAR: ::printmln(screenConsoleBufferHandle, "Windows -> IME Character"); break;
            case WM_IME_COMPOSITION /* -> WM_IME_KEYLAST */:
                ::printh(screenConsoleBufferHandle, ACM_OPENA); ::printg(screenConsoleBufferHandle, ": [");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> IME Composition");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> IME Key [LAST]");
                 ::printge(screenConsoleBufferHandle, "]");
            break;
            case WM_IME_COMPOSITIONFULL: ::printmln(screenConsoleBufferHandle, "Windows -> IME Composition Full"); break;
            case WM_IME_CONTROL: ::printmln(screenConsoleBufferHandle, "Windows -> IME Control"); break;
            case WM_IME_ENDCOMPOSITION: ::printmln(screenConsoleBufferHandle, "Windows -> IME End Composition"); break;
            /*case WM_IME_KEYDOWN: break;*/
            /*case WM_IME_KEYLAST: break;*/
            /*case WM_IME_KEYUP: break;*/
            case WM_IME_NOTIFY: ::printmln(screenConsoleBufferHandle, "Windows -> IME Notify"); break;
            case WM_IME_REPORT: ::printmln(screenConsoleBufferHandle, "Windows -> IME Report"); break;
            case WM_IME_REQUEST: ::printmln(screenConsoleBufferHandle, "Windows -> IME Request"); break;
            case WM_IME_SELECT: ::printmln(screenConsoleBufferHandle, "Windows -> IME Select"); break;
            case WM_IME_SETCONTEXT: ::printmln(screenConsoleBufferHandle, "Windows -> IME Set Context"); break;
            case WM_IME_STARTCOMPOSITION: ::printmln(screenConsoleBufferHandle, "Windows -> IME Start Composition"); break;
            case WM_INITDIALOG: ::printmln(screenConsoleBufferHandle, "Windows -> Initiate Dialog"); break;
            case WM_INITMENU: ::printmln(screenConsoleBufferHandle, "Windows -> Initiate Menu"); break;
            case WM_INITMENUPOPUP: ::printmln(screenConsoleBufferHandle, "Windows -> Initiate Menu Pop-Up"); break;
            case WM_INPUT: ::printmln(screenConsoleBufferHandle, "Windows -> Input"); break;
            case WM_INPUTLANGCHANGE: ::printmln(screenConsoleBufferHandle, "Windows -> Input Language Change"); break;
            case WM_INPUTLANGCHANGEREQUEST: ::printmln(screenConsoleBufferHandle, "Windows -> Input Language Change Request"); break;
            case WM_INTERIM: ::printmln(screenConsoleBufferHandle, "Windows -> Interim"); break;
            case WM_KEYDOWN /* -> WM_KEYFIRST */:
                ::printh(screenConsoleBufferHandle, ACM_OPENA); ::printg(screenConsoleBufferHandle, ": [");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Key Down");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Key [FIRST]");
                ::printge(screenConsoleBufferHandle, "]");

                if (messageParameter == VK_ESCAPE) {
                    ::DestroyWindow(windowHandle);
                    ::PostQuitMessage(0);
                }
            break;
            /*case WM_KEYFIRST: break;*/
            case WM_KEYLAST: ::printmln(screenConsoleBufferHandle, "Windows -> Key [LAST]"); break;
            case WM_KEYUP: ::printmln(screenConsoleBufferHandle, "Windows -> Key Up"); break;
            case WM_KILLFOCUS: ::printmln(screenConsoleBufferHandle, "Windows -> Kill Focus"); break;
            case WM_LBUTTONDBLCLK: ::printmln(screenConsoleBufferHandle, "Windows -> Left (Mouse) Button Double-Click"); break;
            case WM_LBUTTONDOWN: ::printmln(screenConsoleBufferHandle, "Windows -> Left (Mouse) Button Down"); break;
            case WM_LBUTTONUP: ::printmln(screenConsoleBufferHandle, "Windows -> Left (Mouse) Button Up"); break;
            case WM_MBUTTONDBLCLK: ::printmln(screenConsoleBufferHandle, "Windows -> Middle (Mouse) Button Double-Click"); break;
            case WM_MBUTTONDOWN: ::printmln(screenConsoleBufferHandle, "Windows -> Middle (Mouse) Button Down"); break;
            case WM_MBUTTONUP: ::printmln(screenConsoleBufferHandle, "Windows -> Middle (Mouse) Button Up"); break;
            case WM_MDIACTIVATE: ::printmln(screenConsoleBufferHandle, "Windows -> Multiple-Document Interface Activate"); break;
            case WM_MDICASCADE: ::printmln(screenConsoleBufferHandle, "Windows -> Multiple-Document Interface Cascade"); break;
            case WM_MDICREATE: ::printmln(screenConsoleBufferHandle, "Windows -> Multiple-Document Interface Create"); break;
            case WM_MDIDESTROY: ::printmln(screenConsoleBufferHandle, "Windows -> Multiple-Document Interface Destroy"); break;
            case WM_MDIGETACTIVE: ::printmln(screenConsoleBufferHandle, "Windows -> Multiple-Document Interface Get Active"); break;
            case WM_MDIICONARRANGE: ::printmln(screenConsoleBufferHandle, "Windows -> Multiple-Document Interface Icon Arrange"); break;
            case WM_MDIMAXIMIZE: ::printmln(screenConsoleBufferHandle, "Windows -> Multiple-Document Interface Maximize"); break;
            case WM_MDINEXT: ::printmln(screenConsoleBufferHandle, "Windows -> Multiple-Document Interface Next"); break;
            case WM_MDIREFRESHMENU: ::printmln(screenConsoleBufferHandle, "Windows -> Multiple-Document Interface Refresh Menu"); break;
            case WM_MDIRESTORE: ::printmln(screenConsoleBufferHandle, "Windows -> Multiple-Document Interface Restore"); break;
            case WM_MDISETMENU: ::printmln(screenConsoleBufferHandle, "Windows -> Multiple-Document Interface Set Menu"); break;
            case WM_MDITILE: ::printmln(screenConsoleBufferHandle, "Windows -> Multiple-Document Interface Tile"); break;
            case WM_MEASUREITEM: ::printmln(screenConsoleBufferHandle, "Windows -> Measure Item"); break;
            case WM_MENUCHAR: ::printmln(screenConsoleBufferHandle, "Windows -> Menu Character"); break;
            case WM_MENUCOMMAND: ::printmln(screenConsoleBufferHandle, "Windows -> Menu Command"); break;
            case WM_MENUDRAG: ::printmln(screenConsoleBufferHandle, "Windows -> Menu Drag"); break;
            case WM_MENUGETOBJECT: ::printmln(screenConsoleBufferHandle, "Windows -> Menu Get to Object"); break;
            case WM_MENURBUTTONUP: ::printmln(screenConsoleBufferHandle, "Windows -> Menu Right (Mouse) Button Up"); break;
            case WM_MENUSELECT: ::printmln(screenConsoleBufferHandle, "Windows -> Menu Select"); break;
            case WM_MOUSEACTIVATE: ::printmln(screenConsoleBufferHandle, "Windows -> Mouse Activate"); break;
            case WM_MOUSEFIRST /* -> WM_MOUSEMOVE */:
                ::printh(screenConsoleBufferHandle, ACM_OPENA); ::printg(screenConsoleBufferHandle, ": [");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Mouse [FIRST]");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Mouse Move");
                 ::printge(screenConsoleBufferHandle, "]");
            break;
            case WM_MOUSEHOVER: ::printmln(screenConsoleBufferHandle, "Windows -> Mouse Hover"); break;
            case WM_MOUSELAST /* -> WM_XBUTTONDBLCLK */:
                ::printh(screenConsoleBufferHandle, ACM_OPENA); ::printg(screenConsoleBufferHandle, ": [");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Mouse [LAST]");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Mouse X (Mouse) Button Double-Click");
                 ::printge(screenConsoleBufferHandle, "]");
            break;
            case WM_MOUSELEAVE: ::printmln(screenConsoleBufferHandle, "Windows -> Mouse Leave"); break;
            /*case WM_MOUSEMOVE: break;*/
            case WM_MOUSEWHEEL: ::printmln(screenConsoleBufferHandle, "Windows -> Mouse Wheel"); break;
            case WM_MOVE: ::printmln(screenConsoleBufferHandle, "Windows -> Move"); break;
            case WM_MOVING: ::printmln(screenConsoleBufferHandle, "Windows -> Moving"); break;
            case WM_NCACTIVATE: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Activate"); break;
            case WM_NCCALCSIZE: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Calculate Size"); break;
            case WM_NCCREATE: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Create"); break;
            case WM_NCDESTROY: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Destroy"); break;
            case WM_NCHITTEST: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Hit-Test"); break;
            case WM_NCLBUTTONDBLCLK: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Left (Mouse) Button Double-Click"); break;
            case WM_NCLBUTTONDOWN: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Left (Mouse) Button Down"); break;
            case WM_NCLBUTTONUP: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Left (Mouse) Button Up"); break;
            case WM_NCMBUTTONDBLCLK: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Middle (Mouse) Button Double-Click"); break;
            case WM_NCMBUTTONDOWN: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Middle (Mouse) Button Down"); break;
            case WM_NCMBUTTONUP: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Middle (Mouse) Button Up"); break;
            case WM_NCMOUSEHOVER: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Mouse Hover"); break;
            case WM_NCMOUSELEAVE: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Mouse Leave"); break;
            case WM_NCMOUSEMOVE: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Mouse Mouse"); break;
            case WM_NCPAINT: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Paint"); break;
            case WM_NCRBUTTONDBLCLK: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Right (Mouse) Button Double-Click"); break;
            case WM_NCRBUTTONDOWN: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Right (Mouse) Button Down"); break;
            case WM_NCRBUTTONUP: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client Right (Mouse) Button Up"); break;
            case WM_NCXBUTTONDBLCLK: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client X (Mouse) Button Double-Click"); break;
            case WM_NCXBUTTONDOWN: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client X (Mouse) Button Down"); break;
            case WM_NCXBUTTONUP: ::printmln(screenConsoleBufferHandle, "Windows -> Non-Client X (Mouse) Button Up"); break;
            case WM_NEXTDLGCTL: ::printmln(screenConsoleBufferHandle, "Windows -> Next Dialog Control"); break;
            case WM_NEXTMENU: ::printmln(screenConsoleBufferHandle, "Windows -> Next Menu"); break;
            case WM_NOTIFY: ::printmln(screenConsoleBufferHandle, "Windows -> Notify"); break;
            case WM_NOTIFYFORMAT: ::printmln(screenConsoleBufferHandle, "Windows -> Notify Format"); break;
            case WM_NULL: ::printmln(screenConsoleBufferHandle, "Windows -> [NULL]"); break;
            case WM_PAINT: ::printmln(screenConsoleBufferHandle, "Windows -> Paint"); break;
            case WM_PAINTCLIPBOARD: ::printmln(screenConsoleBufferHandle, "Windows -> Paint Clipboard"); break;
            case WM_PAINTICON: ::printmln(screenConsoleBufferHandle, "Windows -> Paint Icon"); break;
            case WM_PALETTECHANGED: ::printmln(screenConsoleBufferHandle, "Windows -> Palette Changed"); break;
            case WM_PALETTEISCHANGING: ::printmln(screenConsoleBufferHandle, "Windows -> Palette is Changing"); break;
            case WM_PARENTNOTIFY: ::printmln(screenConsoleBufferHandle, "Windows -> Parent Notify"); break;
            case WM_PASTE: ::printmln(screenConsoleBufferHandle, "Windows -> Paste"); break;
            /*case WM_PENCTL: break;*/
            case WM_PENEVENT: ::printmln(screenConsoleBufferHandle, "Windows -> Pen Event"); break;
            case WM_PENMISC: ::printmln(screenConsoleBufferHandle, "Windows -> Pen Miscellaneous"); break;
            /*case WM_PENMISCINFO: break;*/
            case WM_PENWINFIRST: ::printmln(screenConsoleBufferHandle, "Windows -> Pen First"); break;
            case WM_PENWINLAST: ::printmln(screenConsoleBufferHandle, "Windows -> Pen Last"); break;
            case WM_POWER: ::printmln(screenConsoleBufferHandle, "Windows -> Power"); break;
            case WM_POWERBROADCAST: ::printmln(screenConsoleBufferHandle, "Windows -> Power Broadcast"); break;
            case WM_PRINT: ::printmln(screenConsoleBufferHandle, "Windows -> Print"); break;
            case WM_PRINTCLIENT: ::printmln(screenConsoleBufferHandle, "Windows -> Print Client"); break;
            /*case WM_PSD_ENVSTAMPRECT: break;*/
            /*case WM_PSD_FULLPAGERECT: break;*/
            /*case WM_PSD_GREEKTEXTRECT: break;*/
            /*case WM_PSD_MARGINRECT: break;*/
            /*case WM_PSD_MINMARGINRECT: break;*/
            /*case WM_PSD_PAGESETUPDLG: break;*/
            /*case WM_PSD_YAFULLPAGERECT: break;*/
            case WM_QUERYDRAGICON: ::printmln(screenConsoleBufferHandle, "Windows -> Query Drag Icon"); break;
            case WM_QUERYENDSESSION: ::printmln(screenConsoleBufferHandle, "Windows -> Query End Session"); break;
            case WM_QUERYNEWPALETTE: ::printmln(screenConsoleBufferHandle, "Windows -> Query New Palette"); break;
            case WM_QUERYOPEN: ::printmln(screenConsoleBufferHandle, "Windows -> Query Open"); break;
            case WM_QUERYUISTATE: ::printmln(screenConsoleBufferHandle, "Windows -> Query User-Interface State"); break;
            case WM_QUEUESYNC: ::printmln(screenConsoleBufferHandle, "Windows -> Queue Synchronization"); break;
            case WM_QUIT: ::printmln(screenConsoleBufferHandle, "Windows -> Quit"); { ::PostQuitMessage(0); } break;
            case WM_RASDIALEVENT: ::printmln(screenConsoleBufferHandle, "Windows -> Routing & Remote Access Service Dial Event"); break;
            case WM_RBUTTONDBLCLK: ::printmln(screenConsoleBufferHandle, "Windows -> Right (Mouse) Button Double-Click"); break;
            case WM_RBUTTONDOWN: ::printmln(screenConsoleBufferHandle, "Windows -> Right (Mouse) Button Down"); break;
            case WM_RBUTTONUP: ::printmln(screenConsoleBufferHandle, "Windows -> Right (Mouse) Button Up"); break;
            case WM_RCRESULT: ::printmln(screenConsoleBufferHandle, "Windows -> RC Result"); break;
            case WM_RENDERALLFORMATS: ::printmln(screenConsoleBufferHandle, "Windows -> Render All Formats"); break;
            case WM_RENDERFORMAT: ::printmln(screenConsoleBufferHandle, "Windows -> Render Format"); break;
            case WM_SETCURSOR: ::printmln(screenConsoleBufferHandle, "Windows -> Set Cursor"); break;
            case WM_SETFOCUS: ::printmln(screenConsoleBufferHandle, "Windows -> Set Focus"); break;
            case WM_SETFONT: ::printmln(screenConsoleBufferHandle, "Windows -> Set Font"); break;
            case WM_SETHOTKEY: ::printmln(screenConsoleBufferHandle, "Windows -> Set Hotkey"); break;
            case WM_SETICON: ::printmln(screenConsoleBufferHandle, "Windows -> Set Icon"); break;
            case WM_SETREDRAW: ::printmln(screenConsoleBufferHandle, "Windows -> Set Redraw"); break;
            case WM_SETTEXT: ::printmln(screenConsoleBufferHandle, "Windows -> Set Text"); break;
            case WM_SHOWWINDOW: ::printmln(screenConsoleBufferHandle, "Windows -> Show Window"); break;
            case WM_SIZE: ::printmln(screenConsoleBufferHandle, "Windows -> Size"); break;
            case WM_SIZECLIPBOARD: ::printmln(screenConsoleBufferHandle, "Windows -> Size Clipboard"); break;
            case WM_SIZING: ::printmln(screenConsoleBufferHandle, "Windows -> Sizing"); break;
            case WM_SKB: ::printmln(screenConsoleBufferHandle, "Windows -> SketchUp Backup"); break;
            case WM_SPOOLERSTATUS: ::printmln(screenConsoleBufferHandle, "Windows -> Spooler Status"); break;
            case WM_STYLECHANGED: ::printmln(screenConsoleBufferHandle, "Windows -> Style Changed"); break;
            case WM_STYLECHANGING: ::printmln(screenConsoleBufferHandle, "Windows -> Style Changing"); break;
            case WM_SYNCPAINT: ::printmln(screenConsoleBufferHandle, "Windows -> Synchronized Paint"); break;
            case WM_SYSCHAR: ::printmln(screenConsoleBufferHandle, "Windows -> System Character"); break;
            case WM_SYSCOLORCHANGE: ::printmln(screenConsoleBufferHandle, "Windows -> System Color Change"); break;
            case WM_SYSCOMMAND: ::printmln(screenConsoleBufferHandle, "Windows -> System Command"); break;
            case WM_SYSDEADCHAR: ::printmln(screenConsoleBufferHandle, "Windows -> System Dead Character"); break;
            case WM_SYSKEYDOWN: ::printmln(screenConsoleBufferHandle, "Windows -> System Key Down"); break;
            case WM_SYSKEYUP: ::printmln(screenConsoleBufferHandle, "Windows -> System Key Up"); break;
            case WM_SYSTIMER: ::printmln(screenConsoleBufferHandle, "Windows -> System Timer"); break;
            case WM_TCARD: ::printmln(screenConsoleBufferHandle, "Windows -> Text Card"); break;
            case WM_TIMECHANGE: ::printmln(screenConsoleBufferHandle, "Windows -> Time Change"); break;
            case WM_TIMER: ::printmln(screenConsoleBufferHandle, "Windows -> Timer"); break;
            case WM_UNDO: ::printmln(screenConsoleBufferHandle, "Windows -> Undo"); break;
            case WM_UNICHAR /* -> WM_WNT_CONVERTREQUESTEX */:
                ::printh(screenConsoleBufferHandle, ACM_OPENA); ::printg(screenConsoleBufferHandle, ": [");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Convert Request");
                    ::printmln(screenConsoleBufferHandle, "    Windows -> Unicode Character");
                 ::printge(screenConsoleBufferHandle, "]");
            break;
            case WM_UNINITMENUPOPUP: ::printmln(screenConsoleBufferHandle, "Windows -> Uninitiate Menu Pop-Up"); break;
            case WM_UPDATEUISTATE: ::printmln(screenConsoleBufferHandle, "Windows -> Update UI State"); break;
            /*case WM_USER: break;*/
            case WM_USERCHANGED: ::printmln(screenConsoleBufferHandle, "Windows -> User Changed"); break;
            case WM_VKEYTOITEM: ::printmln(screenConsoleBufferHandle, "Windows -> Virtual Key to Item"); break;
            case WM_VSCROLL: ::printmln(screenConsoleBufferHandle, "Windows -> Vertical Scroll"); break;
            case WM_VSCROLLCLIPBOARD: ::printmln(screenConsoleBufferHandle, "Windows -> Vertical Scroll Clipboard"); break;
            case WM_WINDOWPOSCHANGED: ::printmln(screenConsoleBufferHandle, "Windows -> Window Position Changed"); break;
            case WM_WINDOWPOSCHANGING: ::printmln(screenConsoleBufferHandle, "Windows -> Window Position Changing"); break;
            case WM_WININICHANGE: ::printmln(screenConsoleBufferHandle, "Windows -> Windows INI Change"); break;
            /*case WM_WNT_CONVERTREQUESTEX: break;*/
            /*case WM_XBUTTONDBLCLK: break;*/
            case WM_XBUTTONDOWN: ::printmln(screenConsoleBufferHandle, "Windows -> X Button Down"); break;
            case WM_XBUTTONUP: ::printmln(screenConsoleBufferHandle, "Windows -> X Button Up"); break;
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
        HANDLE screenConsoleBufferHandle = ::CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0x0, OPEN_ALWAYS, 0, 0x0);
        CONSOLE_SCREEN_BUFFER_INFO screenConsoleBufferInformation;

        // Window (Class, Handle, Procedure Message)
        WNDCLASS windowClass {
            CS_HREDRAW | CS_VREDRAW, /* -> `style` --- NOTE (Lapys) -> Pre-defined look of window instances of the class. */
            &windowProcedure, /* -> `lpfnWndProc`  --- NOTE (Lapys) -> Event loop or Message queue.*/
            0, /* -> `cbClsExtra` --- NOTE (Lapys) -> Extra bytes to allocate following the window class structure. */
            0, /* -> `cbWndExtra` --- NOTE (Lapys) -> Extra bytes to allocate following the window instance. */
            instanceHandle, /* -> `hInstance` */
            0x0, /* -> `hIcon` --- NOTE (Lapys) -> Window favorite icon. */
            (HCURSOR) ::LoadCursor(0x0, IDC_ARROW), /* -> `hCursor` --- NOTE (Lapys) -> Window cursor. */
            (HBRUSH) COLOR_WINDOW + 1, /* -> `hbrBackground` --- NOTE (Lapys) -> Window background color. */
            0x0, /* -> `lpszMenuName` --- NOTE (Lapys) -> Resource name of the window class menu. */
            "Windows Messages" /* -> `lpszClassName` */
        };
        HWND windowHandle = 0x0;
        MSG windowProcedureMessage {windowHandle, 0, EXIT_SUCCESS, 0, 0, {0L, 0L}};

    // ...
    ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);
    ::FillConsoleOutputCharacter(screenConsoleBufferHandle, ' ', screenConsoleBufferInformation.dwSize.X * screenConsoleBufferInformation.dwSize.Y, {0L, 0L}, &screenConsoleBufferBytesWritten);
    ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
    ::SetConsoleCursorPosition(screenConsoleBufferHandle, {0, 1});
    ::SetConsoleTitle("Windows Messages");
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);

    ::WriteConsoleOutputCharacter(screenConsoleBufferHandle, "[PROGRAM INITIATED]", 19, {0, 0}, &screenConsoleBufferBytesWritten);

    // Logic
    if (::RegisterClass(&windowClass)) {
        // Update > Window Handle
        windowHandle = ::CreateWindowEx(0, windowClass.lpszClassName, "Windows Messages", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, (int) ((float) ::GetSystemMetrics(SM_CXSCREEN) * (75.0f / 100.0f)), (int) ((float) ::GetSystemMetrics(SM_CYSCREEN) * (75.0f / 100.0f)), 0x0, 0x0, instanceHandle, 0x0);

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
        }

        else
            // Terminate
            ::exit(PROGRAM_STATUS = EXIT_FAILURE);

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
    ::SetConsoleCursorPosition(screenConsoleBufferHandle, {0, (short) (screenConsoleBufferInformation.dwCursorPosition.Y + 1)});

    // Return
    return PROGRAM_STATUS;
}
