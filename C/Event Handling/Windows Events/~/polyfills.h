/* Import */
    // [Windows]
    #include "../windows/commctrl.h" // Common Controls
    #include "../windows/ftsiface.h" // ...
    #include "../windows/olectl.h" // Object-Linking & Embedding Controls
    #include "../windows/penwin.h" // Pen for Windows
    #include "../windows/prsht.h" // Prop Sheet
    #include "../windows/richedit.h" // Rich Edit
    #include "../windows/smx.h" // Server Manager Extensions
    #include "../windows/shellapi.h" // Shell API
    #include "../windows/shlobj.h" // Shell Object
    #include "../windows/vfw.h" // Video for Windows
    #include "../windows/wfext.h" // Windows File Extensions

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
