/* Import */
    // [C Standard Library]
    #include <stdlib.h> // Standard Library

    // [Windows]
    #include <winbase.h> // Windows Base
    #include <winuser.h> // Windows User

    // [...]
    #include "~/polyfills.h" // Polyfills
    #include "~/logger.hpp" // Logger

/* Definition > Trace (End, Start) --- WARN (Lapys) -> Can only trace one message at a time. */
#define trace_end() messageRepeatCount = 0u; recentMessage = message; } else { static char *iterator; static unsigned char length = 0u; static unsigned char recentLength = 0u; static char string[20] {0}; iterator = string; ::memset(string, '\0', sizeof(string)); 0u == messageRepeatCount ? messageRepeatCount = 2u : ++messageRepeatCount; for (unsigned long subiterator = messageRepeatCount; subiterator; subiterator /= 10u) *iterator++ = *("0123456789" + (subiterator % 10u)); if (2u ^ messageRepeatCount) { length = (iterator - string); for (unsigned char subiterator = 0u; subiterator < length - (length != recentLength); ++subiterator) ::print("\b \b"); recentLength = length; } for (char *subiterator = string; --iterator > subiterator; ++subiterator) { *iterator ^= *subiterator; *subiterator ^= *iterator; *iterator ^= *subiterator; } if (2u ^ messageRepeatCount) print("\b \b\b \b\b \b"); print(" (", (char const*) string, ')'); } once = false;
#define trace_start() static unsigned long messageRepeatCount = 0u; static UINT recentMessage = !message; static bool once = true; if (message != recentMessage) { if (false == once) println();

/* Function > Window Procedure */
LRESULT CALLBACK windowProcedure(HWND windowHandle, UINT message, WPARAM argument, LPARAM subargument) noexcept {
    /* [Start] ... --- NOTE (Lapys) -> Both `trace...` invocations may be revoked. */
    trace_start();

    /* Logic --- WARN (Lapys) -> These are not all system-defined Windows messages.
            --- CITE ---
                #Lapys:
                    - https://docs.microsoft.com/en-us/windows/win32/winmsg/about-messages-and-message-queues#system-defined-messages
                    - https://wiki.winehq.org/List_Of_Windows_Messages
    */
    switch (message) {
        // [Animation Control]
        case ACM_OPENA /* -> BFFM_SETSTATUSTEXTA || CDM_FIRST || CDM_GETSPEC || EM_SETPUNCTUATION || IPM_CLEARADDRESS || WM_CAP_UNICODE_START */: {
            ::println('[', ACM_OPENA, "]: {");
                ::println(printt, "Animation Control -> Open");
                ::println(printt, "Browse for Folder -> Set Status Text");
                ::println(printt, "Common Dialog -> Get Specifications [FIRST]");
                ::println(printt, "Internet Protocol -> Clear Address");
                ::println(printt, "Rich Editor -> Set Punctuation");
                ::println(printt, "Windows -> Cap Unicode Start");
            ::print('}');
        } break;
        case ACM_OPENW /* -> BFFM_SETSELECTIONW || CDM_GETFOLDERIDLIST || EM_GETWORDWRAPMODE || IPM_SETRANGE || PSM_ADDPAGE || UDM_SETPOS || WM_CAP_SET_CALLBACK_STATUSW */: {
            ::println('[', ACM_OPENW, "]: {");
                ::println(printt, "Animation Control -> Open");
                ::println(printt, "Browse for Folder -> Set Selection");
                ::println(printt, "Common Dialog -> Get Folder ID List");
                ::println(printt, "Internet Protocol -> Set Range");
                ::println(printt, "Prop Sheet -> Add Page");
                ::println(printt, "Rich Editor -> Get Word Wrap Mode");
                ::println(printt, "Up-Down Control -> Set Position");
                ::println(printt, "Windows -> Cap Set Callback Status");
            ::print('}');
        } break;
        case ACM_PLAY /* -> BFFM_ENABLEOK || CDM_GETFILEPATH || EM_GETPUNCTUATION || IPM_SETADDRESS || UDM_SETRANGE || WM_CHOOSEFONT_SETLOGFONT */: {
            ::println('[', ACM_OPENA, "]: {");
                ::println(printt, "Animation Control -> Play");
                ::println(printt, "Browse for Folder -> Enable OK");
                ::println(printt, "Common Dialog -> Get File Path");
                ::println(printt, "Internet Protocol -> Set Address");
                ::println(printt, "Rich Editor -> Get Punctuation");
                ::println(printt, "Internet Protocol -> Set Address");
                ::println(printt, "Up-Down Control -> Set Range");
                ::println(printt, "Windows -> Choose Font (Set Log Font)");
            ::print('}');
        } break;
        case ACM_STOP /* -> BFFM_SETSELECTIONA || CDM_GETFOLDERPATH || EM_SETWORDWRAPMODE || IPM_GETADDRESS || PSM_REMOVEPAGE || UDM_GETRANGE || WM_CAP_SET_CALLBACK_ERRORW || WM_CHOOSEFONT_SETFLAGS */: {
            ::println('[', ACM_OPENA, "]: {");
                ::println(printt, "Animation Control -> Stop");
                ::println(printt, "Browse for Folder -> Set Selection");
                ::println(printt, "Common Dialog -> Get Folder Path");
                ::println(printt, "Internet Protocol -> Get Address");
                ::println(printt, "Prop Sheet -> Remove Page");
                ::println(printt, "Rich Editor -> Set Word Wrap Mode");
                ::println(printt, "Up-Down Control -> Get Range");
                ::println(printt, "Windows -> Cap Set Callback Error");
                ::println(printt, "Windows -> Choose Font Set Flags");
            ::print('}');
        } break;

        // [Browse for Folder]
        /*case BFFM_ENABLEOK: break;*/
        /*case BFFM_SETSELECTIONA: break;*/
        /*case BFFM_SETSELECTIONW: break;*/
        /*case BFFM_SETSTATUSTEXTA: break;*/
        case BFFM_SETSTATUSTEXTW /* -> CDM_SETCONTROLTEXT || EM_SETIMECOLOR || IPM_SETFOCUS || PSM_CHANGED || UDM_GETPOS */: {
            ::println('[', ACM_OPENA, "]: {");
                ::println(printt, "Browse for Folder -> Set Status Text");
                ::println(printt, "Common Dialog -> Set Control Text");
                ::println(printt, "Internet Protocol -> Set Focus");
                ::println(printt, "Prop Sheet -> Changed");
                ::println(printt, "Rich Edit -> Set IME Color");
                ::println(printt, "Up-Down Control -> Get Position");
            ::print('}');
        } break;
        case BM_SETDONTCLICK: ::print('[', BM_SETDONTCLICK, "]: Button -> Set Do Not Click"); break;

        // [Button]
        case BM_CLICK: ::print('[', BM_CLICK, "]: Button -> Click"); break;
        case BM_GETCHECK: ::print('[', BM_GETCHECK, "]: Button -> Get Check"); break;
        case BM_GETIMAGE: ::print('[', BM_GETIMAGE, "]: Button -> Get Image"); break;
        case BM_GETSTATE: ::print('[', BM_GETSTATE, "]: Button -> Get State"); break;
        case BM_SETCHECK: ::print('[', BM_SETCHECK, "]: Button -> Set Check"); break;
        case BM_SETIMAGE: ::print('[', BM_SETIMAGE, "]: Button -> Set Image"); break;
        case BM_SETSTATE: ::print('[', BM_SETSTATE, "]: Button -> Set State"); break;
        case BM_SETSTYLE: ::print('[', BM_SETSTYLE, "]: Button -> Set Style"); break;

        // [Combo Box (Extended)]
        case CBEM_GETCOMBOCONTROL /* -> PBM_SETRANGE32 || RB_SETBANDINFOA || SB_GETPARTS || TBM_SETRANGE || TB_MARKBUTTON || TTM_NEWTOOLRECTA || WM_PSD_YAFULLPAGERECT */: {
            ::println('[', ACM_OPENA, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Combo Control");
                ::println(printt, "Progress Bar -> Set Range");
                ::println(printt, "Rebar -> Set Band Information");
                ::println(printt, "Scrollbar -> Get Parts");
                ::println(printt, "Toolbar -> Mark Button");
                ::println(printt, "Tooltips -> New Tool");
                ::println(printt, "Trackbar -> Set Range");
                ::println(printt, "Windows -> Page Setup Dialog Full Page");
            ::print('}');
        } break;
        case CBEM_GETEDITCONTROL /* -> IE_GETPAINTDC || PBM_GETRANGE || RB_SETPARENT || SB_GETBORDERS || TBM_SETRANGEMIN || TTM_RELAYEVENT */: {
            ::println('[', CBEM_GETEDITCONTROL, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Edit Control");
                ::println(printt, "Progress Bar -> Get Range");
                ::println(printt, "Rebar -> Set Parent");
                ::println(printt, "Rich Editor -> Get Paint Device Context");
                ::println(printt, "Scrollbar -> Get Borders");
                ::println(printt, "Tooltips -> Relay Event");
                ::println(printt, "Trackbar -> Set Range Minimum");
            ::print('}');
        } break;
        case CBEM_GETEXSTYLE /* -> CBEM_GETEXTENDEDSTYLE || PBM_SETBARCOLOR || RB_GETRECT || SB_SIMPLE || TBM_CLEARTICS || TB_ISBUTTONENABLED || TTM_SETTOOLINFOA */: {
            ::println('[', CBEM_GETEXSTYLE, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Extended Style");
                ::println(printt, "Progress Bar -> Set Bar Color");
                ::println(printt, "Rebar -> Get Rectangle");
                ::println(printt, "Scrollbar -> Simple");
                ::println(printt, "Toolbar -> Is Button Enabled");
                ::println(printt, "Tooltip -> Set Tool Information");
                ::println(printt, "Track Bar -> Clear Ticks");
            ::print('}');
        } break;
        case CBEM_GETIMAGELIST /* -> HKM_SETRULES || PBM_DELTAPOS || RB_GETBARINFO || SB_GETTEXTLENGTHA || TBM_GETTIC || TB_PRESSBUTTON || TTM_SETDELAYTIME || WM_PSD_MARGINRECT */ {
            ::println('[', CBEM_GETIMAGELIST, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Extended Style");
            ::print('}');
        } break;
        case CBEM_GETITEMA /* -> PBM_SETSTEP || RB_SETBARINFO || SB_SETPARTS || TBM_SETTIC || TB_HIDEBUTTON || TB_SETBUTTONINFOW || TTM_ADDTOOLA || WM_PSD_GREEKTEXTRECT || DDM_END */ {
            ::println('[', CBEM_GETITEMA, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Extended Style");
            ::print('}');
        } break;
        case CBEM_GETITEMW /* -> RB_GETROWCOUNT || SB_GETTEXTW || TB_ISBUTTONINDETERMINATE || TTM_GETTOOLCOUNT */ {
            ::println('[', CBEM_GETITEMW, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Extended Style");
            ::print('}');
        } break;
        case CBEM_HASEDITCHANGED /* -> RB_INSERTBANDW || SB_GETRECT || TBM_SETSEL || TB_ISBUTTONCHECKED || TTM_HITTESTA || WIZ_QUERYNUMPAGES */ {
            ::println('[', CBEM_HASEDITCHANGED, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Extended Style");
            ::print('}');
        } break;
        case CBEM_INSERTITEMA /* -> DM_SETDEFID || HKM_SETHOTKEY || PBM_SETRANGE || RB_INSERTBANDA || SB_SETTEXTA || TBM_GETRANGEMIN || TB_ENABLEBUTTON || TTM_ACTIVATE || WM_CHOOSEFONT_GETLOGFONT || WM_PSD_FULLPAGERECT || DDM_DRAW */ {
            ::println('[', CBEM_INSERTITEMA, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Extended Style");
            ::print('}');
        } break;
        case CBEM_INSERTITEMW /* -> RB_SETBANDINFOW || SB_SETTEXTW || TBM_SETSELSTART || TB_ISBUTTONPRESSED || TTM_GETTEXTA || WIZ_NEXT */ {
            ::println('[', CBEM_INSERTITEMW, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Extended Style");
            ::print('}');
        } break;
        case CBEM_SETEXSTYLE /* -> CBEM_SETEXTENDEDSTYLE || PBM_GETPOS || RB_HITTEST || SB_SETMINHEIGHT || TBM_SETRANGEMAX || TTM_GETTOOLINFOA */ {
            ::println('[', CBEM_SETEXSTYLE, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Extended Style");
            ::print('}');
        } break;
        case CBEM_SETIMAGELIST /* -> DM_REPOSITION || HKM_GETHOTKEY || PBM_SETPOS || RB_DELETEBAND || SB_GETTEXTA || TBM_GETRANGEMAX || TB_CHECKBUTTON || WM_PSD_MINMARGINRECT || DDM_BEGIN || DDM_CLOSE */ {
            ::println('[', CBEM_SETIMAGELIST, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Extended Style");
            ::print('}');
        } break;
        case CBEM_SETITEMA /* -> PBM_STEPIT || TBM_SETPOS || TB_INDETERMINATE || TTM_DELTOOLA || WM_PSD_ENVSTAMPRECT */ {
            ::println('[', CBEM_SETITEMA, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Extended Style");
            ::print('}');
        } break;
        case CBEM_SETITEMW /* -> RB_GETBANDCOUNT || SB_GETTEXTLENGTHW || TBM_SETSELEND || TB_ISBUTTONHIDDEN || TTM_UPDATETIPTEXTA || WIZ_PREV */ {
            ::println('[', CBEM_SETITEMW, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Extended Style");
            ::print('}');
        } break;

        // [...]
        /*case CDM_GETFILEPATH: break;*/
        /*case CDM_GETFOLDERIDLIST: break;*/
        /*case CDM_GETFOLDERPATH: break;*/
        case CDM_HIDECONTROL /* -> EM_GETIMECOLOR || IPM_ISBLANK || PSM_RESTARTWINDOWS || UDM_SETBUDDY */: break;
        /*case CDM_FIRST: break;*/
        /*case CDM_GETSPEC: break;*/
        case CDM_LAST /* -> EM_SETBIDIOPTIONS || IE_DOCOMMAND || MCIWNDM_NOTIFYMODE */: break;
        /*case CDM_SETCONTROLTEXT: break;*/
        case CDM_SETDEFEXT /* -> EM_SETIMEOPTIONS || PSM_REBOOTSYSTEM || UDM_GETBUDDY */: break;

        // [...]
        /*case DDM_BEGIN: break;*/
        /*case DDM_CLOSE: break;*/
        /*case DDM_DRAW: break;*/
        /*case DDM_END: break;*/
        case DDM_SETFMT /* -> DM_GETDEFID || NIN_SELECT || TBM_GETPOS || WM_PSD_PAGESETUPDLG || WM_USER */: break;

        // [...]
        case DL_BEGINDRAG /* -> MCIWNDM_GETINACTIVETIMER || PSM_IDTOINDEX || TB_BUTTONCOUNT || TTM_SETMAXTIPWIDTH */: break;
        case DL_CANCELDRAG /* -> PSM_RECALCPAGESIZES */: break;
        case DL_DRAGGING /* -> PSM_INDEXTOID */: break;
        case DL_DROPPED /* -> PSM_GETRESULT */: break;

        // [...]
        /*case DM_GETDEFID: break;*/
        /*case DM_REPOSITION: break;*/
        /*case DM_SETDEFID: break;*/

        // [...]
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

        // [...]
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

        // [...]
        /*case HKM_GETHOTKEY: break;*/
        /*case HKM_SETHOTKEY: break;*/
        /*case HKM_SETRULES: break;*/

        // [...]
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

        // [...]
        /*case IPM_CLEARADDRESS: break;*/
        /*case IPM_GETADDRESS: break;*/
        /*case IPM_ISBLANK: break;*/
        /*case IPM_SETADDRESS: break;*/
        /*case IPM_SETFOCUS: break;*/
        /*case IPM_SETRANGE: break;*/

        // [...]
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

        // [...]
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

        // [...]
        case MSG_FTS_JUMP_QWORD /* -> RB_SHOWBAND || TB_GETTOOLTIPS */: break;
        case MSG_FTS_JUMP_VA /* -> TBM_GETBUDDY || TB_AUTOSIZE || TTM_SETTITLEW */: break;
        case MSG_FTS_WHERE_IS_IT /* -> RB_SETPALETTE || TB_SETPARENT */: ::print('[', MSG_FTS_WHERE_IS_IT, "]: ..."); break;
        case MSG_GET_DEFFONT /* -> TB_GETBUTTONTEXTA */: ::print('[', MSG_GET_DEFFONT, "]: Get Default Font"); break;
        case MSG_REINDEX_REQUEST /* -> TB_SETTOOLTIPS */: ::print('[', MSG_REINDEX_REQUEST, "]: Re-Index Request"); break;

        // [...]
        /*case NIN_SELECT: break;*/
        case OCM_CHARTOITEM: ::print('[', OCM_CHARTOITEM, "]: Object Linking & Embedding Control -> Character To Item"); break;
        case OCM_COMMAND: ::print('[', OCM_COMMAND, "]: Object Linking & Embedding Control -> Command"); break;
        case OCM_COMPAREITEM: ::print('[', OCM_COMPAREITEM, "]: Object Linking & Embedding Control -> Compare Item"); break;
        case OCM_CTLCOLOR: ::print('[', OCM_CTLCOLOR, "]: Object Linking & Embedding Control -> Control Color"); break;
        case OCM_CTLCOLORBTN: ::print('[', OCM_CTLCOLORBTN, "]: Object Linking & Embedding Control -> Control Color Button"); break;
        case OCM_CTLCOLORDLG: ::print('[', OCM_CTLCOLORDLG, "]: Object Linking & Embedding Control -> Control Color Dialog"); break;
        case OCM_CTLCOLOREDIT: ::print('[', OCM_CTLCOLOREDIT, "]: Object Linking & Embedding Control -> Control Color Edit"); break;
        case OCM_CTLCOLORLISTBOX: ::print('[', OCM_CTLCOLORLISTBOX, "]: Object Linking & Embedding Control -> Control Color List Box"); break;
        case OCM_CTLCOLORMSGBOX: ::print('[', OCM_CTLCOLORMSGBOX, "]: Object Linking & Embedding Control -> Control Color Message Box"); break;
        case OCM_CTLCOLORSCROLLBAR: ::print('[', OCM_CTLCOLORSCROLLBAR, "]: Object Linking & Embedding Control -> Control Color Scrollbar"); break;
        case OCM_CTLCOLORSTATIC: ::print('[', OCM_CTLCOLORSTATIC, "]: Object Linking & Embedding Control -> Control Color Static"); break;
        case OCM_DELETEITEM: ::print('[', OCM_DELETEITEM, "]: Object Linking & Embedding Control -> Delete Item"); break;
        case OCM_DRAWITEM: ::print('[', OCM_DRAWITEM, "]: Object Linking & Embedding Control -> Draw Item"); break;
        case OCM_HSCROLL: ::print('[', OCM_HSCROLL, "]: Object Linking & Embedding Control -> Horizontal Scroll"); break;
        case OCM_MEASUREITEM: ::print('[', OCM_MEASUREITEM, "]: Object Linking & Embedding Control -> Measure Item"); break;
        case OCM_NOTIFY: ::print('[', OCM_NOTIFY, "]: Object Linking & Embedding Control -> Notify"); break;
        case OCM_PARENTNOTIFY: ::print('[', OCM_PARENTNOTIFY, "]: Object Linking & Embedding Control -> Parent Notify"); break;
        case OCM_VKEYTOITEM: ::print('[', OCM_VKEYTOITEM, "]: Object Linking & Embedding Control -> Virtual Key to Item"); break;
        case OCM_VSCROLL: ::print('[', OCM_VSCROLL, "]: Object Linking & Embedding Control -> Vertical Scroll"); break;
        case OCM__BASE: ::print('[', OCM__BASE, "]: Object Linking & Embedding Control -> Base"); break;

        // [...]
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
        case PSM_APPLY /* -> UDM_GETBASE */: ::print('[', PSM_APPLY, "]: Prop Sheet -> Apply"); break;
        /*case PSM_CANCELTOCLOSE: break;*/
        /*case PSM_CHANGED: break;*/
        /*case PSM_GETCURRENTPAGEHWND: break;*/
        /*case PSM_GETRESULT: break;*/
        case PSM_GETTABCONTROL: ::print('[', PSM_GETTABCONTROL, "]: Prop Sheet -> Get Tab Control"); break;
        case PSM_HWNDTOINDEX: ::print('[', PSM_HWNDTOINDEX, "]: Prop Sheet -> Window Handle to Index"); break;
        /*case PSM_IDTOINDEX: break;*/
        case PSM_INDEXTOHWND: ::print('[', PSM_INDEXTOHWND, "]: Prop Sheet -> Index To Window Handle"); break;
        /*case PSM_INDEXTOID: break;*/
        case PSM_INDEXTOPAGE: ::print('[', PSM_INDEXTOPAGE, "]: Prop Sheet -> Index To Page"); break;
        /*case PSM_INSERTPAGE: break;*/
        case PSM_ISDIALOGMESSAGE: ::print('[', PSM_ISDIALOGMESSAGE, "]: Prop Sheet -> Is Dialog Message"); break;
        /*case PSM_PAGETOINDEX: break;*/
        case PSM_PRESSBUTTON /* -> UDM_SETPOS32 || WM_CAP_DRIVER_GET_VERSIONW */: ::print('[', PSM_PRESSBUTTON, "]: Prop Sheet -> Press Button"); break;
        /*case PSM_QUERYSIBLINGS: break;*/
        /*case PSM_REBOOTSYSTEM: break;*/
        /*case PSM_RECALCPAGESIZES: break;*/
        /*case PSM_REMOVEPAGE: break;*/
        /*case PSM_RESTARTWINDOWS: break;*/
        /*case PSM_SETCURSEL: break;*/
        case PSM_SETCURSELID /* -> UDM_GETPOS32 */: ::print('[', PSM_SETCURSELID, "]: Prop Sheet -> Set Current Selection Identity"); break;
        case PSM_SETFINISHTEXTA: ::print('[', PSM_SETFINISHTEXTA, "]: Prop Sheet -> Set Finish Text"); break;
        /*case PSM_SETFINISHTEXTW: break;*/
        /*case PSM_SETHEADERSUBTITLEA: break;*/
        /*case PSM_SETHEADERSUBTITLEW: break;*/
        /*case PSM_SETHEADERTITLEA: break;*/
        /*case PSM_SETHEADERTITLEW: break;*/
        case PSM_SETTITLEA /* -> UDM_SETRANGE32 */: ::print('[', PSM_SETTITLEA, "]: Prop Sheet -> Set Title"); break;
        /*case PSM_SETTITLEW: break;*/
        case PSM_SETWIZBUTTONS /* -> UDM_GETRANGE32 || WM_CAP_DRIVER_GET_NAMEW */: ::print('[', PSM_SETWIZBUTTONS, "]: Prop Sheet -> Set Wizard Buttons"); break;
        /*case PSM_UNCHANGED: break;*/

        // [Rebar]
        case RB_BEGINDRAG /* -> TBM_GETLINESIZE */: {
            ::println('[', RB_BEGINDRAG, "]: {");
                ::println(printt, "Rebar -> Begin Drag");
                ::println(printt, "Trackbar -> Get Line Size");
            ::print('}');
        } break;
        /*case RB_DELETEBAND: break;*/
        case RB_DRAGMOVE /* -> TBM_GETCHANNELRECT || TB_SAVERESTOREA || TTM_SETMARGIN */: {
            ::println('[', RB_DRAGMOVE, "]: {");
                ::println(printt, "Rebar -> Drag Move");
                ::println(printt, "Toolbar -> Save Restore");
                ::println(printt, "Tooltip -> Set Margin");
                ::println(printt, "Trackbar -> Get Channel Rectangle");
            ::print('}');
        } break;
        case RB_ENDDRAG /* -> TBM_GETTHUMBRECT || TB_COMMANDTOINDEX || TTM_GETMAXTIPWIDTH */: {
            ::println('[', RB_ENDDRAG, "]: {");
                ::println(printt, "Rebar -> End Drag");
                ::println(printt, "Toolbar -> Command To Index");
                ::println(printt, "Tooltip -> Get Maximum Tip Width");
                ::println(printt, "Trackbar -> Get Thumb Rect");
            ::print('}');
        } break;
        case RB_GETBANDBORDERS: ::print('[', RB_GETBANDBORDERS, "]: Rebar -> Get Band Borders"); break;
        /*case RB_GETBANDCOUNT: break;*/
        case RB_GETBANDINFOA /* -> TBM_SETTOOLTIPS || TB_GETITEMRECT || TTM_UPDATE */: {
            ::println('[', RB_GETBANDINFOA, "]: {");
                ::println(printt, "Rebar -> Get Band Information");
                ::println(printt, "Toolbar -> Get Item Rectangle");
                ::println(printt, "Tooltip -> Update");
                ::println(printt, "Trackbar -> Set Tooltips");
            ::print('}');
        } break;
        case RB_GETBANDINFOW /* -> TBM_GETTHUMBLENGTH || TB_ADDSTRINGA || TTM_POP */: {
            ::println('[', RB_GETBANDINFOW, "]: {");
                ::println(printt, "Rebar -> Get Band Information");
                ::println(printt, "Toolbar -> Add String");
                ::println(printt, "Tooltip -> Pop");
                ::println(printt, "Trackbar -> Get Thumb Length");
            ::print('}');
        } break;
        case RB_GETBARHEIGHT /* -> TBM_SETTHUMBLENGTH || TB_CUSTOMIZE || TTM_GETMARGIN */: {
            ::println('[', RB_GETBARHEIGHT, "]: {");
                ::println(printt, "Rebar -> Get Bar Height");
                ::println(printt, "Toolbar -> Customize");
                ::println(printt, "Tooltip -> Get Margin");
                ::println(printt, "Trackbar -> Set Thumb Length");
            ::print('}');
        } break;
        /*case RB_GETBARINFO: break;*/
        case RB_GETBKCOLOR /* -> SB_GETTIPTEXTW || TBM_SETTICFREQ || TB_ADDBUTTONSA || TTM_SETTIPTEXTCOLOR */: {
            ::println('[', RB_GETROWHEIGHT, "]: {");
                ::println(printt, "Rebar -> Get Background Color");
                ::println(printt, "Status Bar -> Get Tip Text");
                ::println(printt, "Toolbar -> Add Buttons");
                ::println(printt, "Tooltip -> Set Tip Text Color");
                ::println(printt, "Trackbar -> Set Tick Frequency");
            ::print('}');
        } break
        case RB_GETPALETTE: ::print('[', RB_GETPALETTE, "]: Rebar -> Get Palette"); break;
        /*case RB_GETRECT: break;*/
        /*case RB_GETROWCOUNT: break;*/
        case RB_GETROWHEIGHT /* -> SB_ISSIMPLE || TBM_GETPTICS || TB_ISBUTTONHIGHLIGHTED || TTM_ENUMTOOLSA */: {
            ::println('[', RB_GETROWHEIGHT, "]: {");
                ::println(printt, "Rebar -> Get Row Height");
                ::println(printt, "Status Bar -> Is Simple");
                ::println(printt, "Toolbar -> Is Button Highlighted");
                ::println(printt, "Tooltip -> Enumerate Tools");
                ::println(printt, "Trackbar -> Get Position [of] Ticks");
            ::print('}');
        } break;
        case RB_GETTEXTCOLOR /* -> TBM_GETPAGESIZE || TB_DELETEBUTTON || TTM_GETTIPBKCOLOR */: {
            ::println('[', RB_GETTEXTCOLOR, "]: {");
                ::println(printt, "Rebar -> Get Text Color");
                ::println(printt, "Toolbar -> Delete Button");
                ::println(printt, "Tooltip -> Get Tip Background Color");
                ::println(printt, "Trackbar -> Get Page Size");
            ::print('}');
        } break;
        case RB_GETTOOLTIPS /* -> SB_SETTIPTEXTW || TBM_GETSELSTART || TB_SETSTATE || TTM_TRACKACTIVATE */: {
            ::println('[', RB_GETTOOLTIPS, "]: {");
                ::println(printt, "Rebar -> Get Tooltips");
                ::println(printt, "Status Bar -> Set Tip Text");
                ::println(printt, "Tooltip -> Track Activate");
                ::println(printt, "Trackbar -> Set State");
            ::print('}');
        } break;
        /*case RB_HITTEST: break;*/
        case RB_IDTOINDEX /* -> SB_SETTIPTEXTA || TBM_GETNUMTICS || TTM_WINDOWFROMPOINT */: {
            ::println('[', RB_IDTOINDEX, "]: {");
                ::println(printt, "Rebar -> Identity to Index");
                ::println(printt, "Status Bar -> Set Tip Text");
                ::println(printt, "Tooltip -> Window From Point");
                ::println(printt, "Trackbar -> Get Number [of] Ticks");
            ::print('}');
        } break;
        /*case RB_INSERTBANDA: break;*/
        /*case RB_INSERTBANDW: break;*/
        case RB_MAXIMIZEBAND /* -> TBM_SETTIPSIDE || TB_SETBUTTONSIZE || TTM_ADJUSTRECT */: {
            ::println('[', RB_MAXIMIZEBAND, "]: {");
                ::println(printt, "Rebar -> Maximize Band");
                ::println(printt, "Toolbar -> Set Button Size");
                ::println(printt, "Tooltip -> Adjust Rectangle");
                ::println(printt, "Trackbar -> Set Tip Side");
            ::print('}');
        } break;
        case RB_MINIMIZEBAND /* -> TBM_GETTOOLTIPS || TB_BUTTONSTRUCTSIZE || TTM_GETBUBBLESIZE */: {
            ::println('[', RB_MINIMIZEBAND, "]: {");
            ::println(printt, "Rebar -> Minimize Band");
            ::println(printt, "Toolbar -> Button Structure Size");
            ::println(printt, "Tooltip -> Get Bubble Size");
            ::println(printt, "Trackbar -> Get Tooltips");
        ::print('}');
        } break;
        case RB_MOVEBAND /* -> TB_SETROWS */: ::print('[', RB_MOVEBAND, "]: Rebar -> Move Band"); break;
        case RB_PUSHCHEVRON /* -> TB_CHANGEBITMAP */: {
            ::println('[', RB_PUSHCHEVRON, "]: {");
                ::println(printt, "Rebar -> Push Chevron");
                ::println(printt, "Toolbar -> Change Bitmap");
            ::print('}');
        } break;
        /*case RB_SETBANDINFOA: break;*/
        /*case RB_SETBANDINFOW: break;*/
        /*case RB_SETBARINFO: break;*/
        case RB_SETBKCOLOR /* -> TBM_CLEARSEL || TB_ADDBITMAP || TTM_SETTIPBKCOLOR */: {
            ::println('[', RB_SETBKCOLOR, "]: {");
                ::println(printt, "Rebar -> Set Background Color");
                ::println(printt, "Toolbar -> Add Bitmap");
                ::println(printt, "Tooltip -> Set Tip Background Color");
                ::println(printt, "Trackbar -> Clear Selection");
            ::print('}');
        } break;
        /*case RB_SETPALETTE: break;*/
        /*case RB_SETPARENT: break;*/
        case RB_SETTEXTCOLOR /* -> TBM_SETPAGESIZE || TB_INSERTBUTTONA || TTM_GETDELAYTIME */: {
            ::println('[', RB_SETTEXTCOLOR, "]: {");
                ::println(printt, "Rebar -> Set Text Color");
                ::println(printt, "Toolbar -> Insert Button");
                ::println(printt, "Tooltip -> Get Delay Time");
                ::println(printt, "Trackbar -> Set Page Size");
            ::print('}');
        } break;
        case RB_SETTOOLTIPS /* -> SB_GETTIPTEXTA || TBM_GETSELEND || TB_GETSTATE || TTM_TRACKPOSITION */: {
            ::println('[', RB_SETTOOLTIPS, "]: {");
                ::println(printt, "Rebar -> Set Tooltips");
                ::println(printt, "Status Bar -> Get Tip Text");
                ::println(printt, "Toolbar -> Get State");
                ::println(printt, "Tooltip -> Track Position");
                ::println(printt, "Trackbar -> Get Selection End");
            ::print('}');
        } break;
        /*case RB_SHOWBAND: break;*/
        case RB_SIZETORECT /* -> TBM_SETLINESIZE || TB_GETBUTTON || TTM_GETTIPTEXTCOLOR */: {
            ::println('[', RB_SIZETORECT, "]: {");
                ::println(printt, "Rebar -> Size to Rectangle");
                ::println(printt, "Toolbar -> Get Button");
                ::println(printt, "Tooltip -> Get Tip Text Color");
                ::println(printt, "Trackbar -> Set Line Size");
            ::print('}');
        } break;

        // [Scrollbar]
        case SBM_ENABLE_ARROWS: ::print('[', SBM_ENABLE_ARROWS, "]: Scrollbar -> Enable Arrows"); break;
        case SBM_GETPOS: ::print('[', SBM_GETPOS, "]: Scrollbar -> Get Position"); break;
        case SBM_GETRANGE: ::print('[', SBM_GETRANGE, "]: Scrollbar -> Get Range"); break;
        /*case SBM_GETSCROLLBARINFO: break;*/
        case SBM_GETSCROLLINFO: ::print('[', SBM_GETSCROLLINFO, "]: Scrollbar -> Get Scroll Information"); break;
        case SBM_SETPOS: ::print('[', SBM_SETPOS, "]: Scrollbar -> Set Position"); break;
        case SBM_SETRANGE: ::print('[', SBM_SETRANGE, "]: Scrollbar -> Set Range"); break;
        case SBM_SETRANGEREDRAW: ::print('[', SBM_SETRANGEREDRAW, "]: Scrollbar -> Set Range Redraw"); break;
        case SBM_SETSCROLLINFO: ::print('[', SBM_SETSCROLLINFO, "]: Scrollbar -> Set Scroll Information"); break;

        // [Status Bar]
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
        case SB_SETICON /* -> TBM_GETTICPOS || TTM_GETCURRENTTOOLA */: {
            ::println('[', SB_SETICON, "]: {");
                ::println(printt, "Status Bar -> Set Icon");
                ::println(printt, "Trackbar -> Get Tick (Mark) Position");
                ::println(printt, "Tooltip -> Get Current Tool");
            ::print('}');
        } break;
        /*case SB_SETMINHEIGHT: break;*/
        /*case SB_SETPARTS: break;*/
        /*case SB_SETTEXTA: break;*/
        /*case SB_SETTEXTW: break;*/
        /*case SB_SETTIPTEXTA: break;*/
        /*case SB_SETTIPTEXTW: break;*/
        /*case SB_SIMPLE: break;*/

        // [Storage Management]
        case SM_GETCURFOCUSA /* -> UM_GETGROUPSELA */: {
            ::println('[', SM_GETCURFOCUSA, "]: {");
                ::println(printt, "Storage Management -> Get Current Focus");
                ::println(printt, "User Manager -> Get Group Selection");
            ::print('}');
        } break;
        case SM_GETCURFOCUSW /* -> UM_GETGROUPSELW */: {
            ::println('[', SM_GETCURFOCUSW, "]: {");
                ::println(printt, "Storage Management -> Get Current Focus");
                ::println(printt, "User Manager -> Get Group Selection");
            ::print('}');
        } break;
        case SM_GETOPTIONS /* -> UM_GETCURFOCUSA */: {
            ::println('[', SM_GETOPTIONS, "]: {");
                ::println(printt, "Storage Management -> Get Options");
                ::println(printt, "User Manager -> Get Current Focus");
            ::print('}');
        } break;
        case SM_GETSELCOUNT /* -> UM_GETSELCOUNT || WM_CPL_LAUNCH */: {
            ::println('[', SM_GETSELCOUNT, "]: {");
                ::println(printt, "Storage Management -> Get Selection Count");
                ::println(printt, "User Manager -> Get Selection Count");
                ::println(printt, "Windows -> Control Panel Launched");
            ::print('}');
        } break;
        case SM_GETSERVERSELA /* -> UM_GETUSERSELA || WM_CPL_LAUNCHED */: {
            ::println('[', SM_GETSERVERSELA, "]: {");
                ::println(printt, "Storage Management -> Get Server Selection");
                ::println(printt, "User Manager -> Get User Selection");
                ::println(printt, "Windows -> Control Panel Launched");
            ::print('}');
        } break;
        case SM_GETSERVERSELW /* -> UM_GETUSERSELW */: {
            ::println('[', SM_GETSERVERSELW, "]: {");
                ::println(printt, "Storage Management -> Get Server Selection");
                ::println(printt, "User Manager -> Get User Selection");
            ::print('}');
        } break;

        // [Telephony API]
        case TAPI_REPLY: ::print('[', TAPI_REPLY, "]: Telephony API -> Reply"); break;

        // [Trackbar]
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
        case TBM_SETBUDDY /* -> TB_SETBITMAPSIZE || TTM_SETTITLEA */: {
            ::println('[', TBM_SETBUDDY, "]: {");
                ::println(printt, "Trackbar -> Set Buddy (Window)");
                ::println(printt, "Toolbar -> Set Bitmap Size");
                ::println(printt, "Tooltip -> Set Title");
            ::print('}');
        } break;
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

        // [Toolbar]
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
        case TB_GETBITMAP: ::print('[', TB_GETBITMAP, "]: Toolbar -> Get Bitmap"); break;
        case TB_GETBITMAPFLAGS: ::print('[', TB_GETBITMAPFLAGS, "]: Toolbar -> Get Bitmap Flags"); break;
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
        case TB_GETIMAGELIST: ::print('[', TB_GETIMAGELIST, "]: Toolbar -> Get Image List"); break;
        /*case TB_GETINSERTMARK: break;*/
        /*case TB_GETINSERTMARKCOLOR: break;*/
        /*case TB_GETITEMRECT: break;*/
        case TB_GETMAXSIZE: ::print('[', TB_GETMAXSIZE, "]: Toolbar -> Get Maximum Size"); break;
        /*case TB_GETOBJECT: break;*/
        /*case TB_GETPADDING: break;*/
        /*case TB_GETRECT: break;*/
        case TB_GETROWS: ::print('[', TB_GETROWS, "]: Toolbar -> Get Rows"); break;
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
        case TB_REPLACEBITMAP: ::print('[', TB_REPLACEBITMAP, "]: Toolbar -> Replace Bitmap"); break;
        /*case TB_SAVERESTOREA: break;*/
        /*case TB_SAVERESTOREW: break;*/
        /*case TB_SETANCHORHIGHLIGHT: break;*/
        /*case TB_SETBITMAPSIZE: break;*/
        /*case TB_SETBUTTONINFOA: break;*/
        /*case TB_SETBUTTONINFOW: break;*/
        /*case TB_SETBUTTONSIZE: break;*/
        /*case TB_SETBUTTONWIDTH: break;*/
        case TB_SETCMDID: ::print('[', TB_SETCMDID, "]: Toolbar -> Set Command Identifier"); break;
        /*case TB_SETDISABLEDIMAGELIST: break;*/
        /*case TB_SETDRAWTEXTFLAGS: break;*/
        /*case TB_SETEXTENDEDSTYLE: break;*/
        /*case TB_SETHOTIMAGELIST: break;*/
        /*case TB_SETHOTITEM: break;*/
        case TB_SETIMAGELIST: ::print('[', TB_SETIMAGELIST, "]: Toolbar -> Set Image List"); break;
        case TB_SETINDENT: ::print('[', TB_SETINDENT, "]: Toolbar -> Set Indentation"); break;
        /*case TB_SETINSERTMARK: break;*/
        /*case TB_SETINSERTMARKCOLOR: break;*/
        /*case TB_SETMAXTEXTROWS: break;*/
        /*case TB_SETPADDING: break;*/
        /*case TB_SETPARENT: break;*/
        /*case TB_SETROWS: break;*/
        /*case TB_SETSTATE: break;*/
        /*case TB_SETSTYLE: break;*/
        /*case TB_SETTOOLTIPS: break;*/

        // [Tooltip]
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

        // [Up-Down Control]
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

        // [User Manager]
        /*case UM_GETCURFOCUSA: break;*/
        case UM_GETCURFOCUSW: ::print('[', UM_GETCURFOCUSW, "]: User Manager -> Get Current Focus"); break;
        /*case UM_GETGROUPSELA: break;*/
        /*case UM_GETGROUPSELW: break;*/
        case UM_GETOPTIONS: ::print('[', UM_GETOPTIONS, "]: User Manager -> Get Options"); break;
        case UM_GETOPTIONS2: ::print('[', UM_GETOPTIONS2, "]: User Manager -> Get Options (Structure)"); break;
        /*case UM_GETSELCOUNT: break;*/
        /*case UM_GETUSERSELA: break;*/
        /*case UM_GETUSERSELW: break;*/

        // [Wizard?]
        /*case WIZ_NEXT: break;*/
        /*case WIZ_PREV: break;*/
        /*case WIZ_QUERYNUMPAGES: break;*/

        // [Windows Live Sync?]
        case WLX_WM_SAS: ::print('[', WLX_WM_SAS, "]: Windows Live Sync -> Statistical Analysis Suite Message"); break;

        // [Windows]
        case WM_ACTIVATE: ::print('[', WM_ACTIVATE, "]: Windows -> Activate"); break;
        case WM_ACTIVATEAPP: ::print('[', WM_ACTIVATEAPP, "]: Windows -> Activate Application"); break;
        case WM_AFXFIRST: ::print('[', WM_AFXFIRST, "]: Windows -> Application Framework Extensions FIRST[]"); break;
        case WM_AFXLAST: ::print('[', WM_AFXLAST, "]: Windows -> Application Framework Extensions [LAST]"); break;
        case WM_APP: ::print('[', WM_APP, "]: Windows -> Application"); break;
        case WM_APPCOMMAND: ::print('[', WM_APPCOMMAND, "]: Windows -> Application Command"); break;
        case WM_ASKCBFORMATNAME: ::print('[', WM_ASKCBFORMATNAME, "]: Windows -> Ask Clipboard Format Name"); break;
        case WM_CANCELJOURNAL: ::print('[', WM_CANCELJOURNAL, "]: Windows -> Cancel Journal"); break;
        case WM_CANCELMODE: ::print('[', WM_CANCELMODE, "]: Windows -> Cancel Mode"); break;
        case WM_CAPTURECHANGED: ::print('[', WM_CAPTURECHANGED, "]: Windows -> Capture Changed"); break;
        /*case WM_CAP_DRIVER_GET_NAMEW: break;*/
        /*case WM_CAP_DRIVER_GET_VERSIONW: break;*/
        /*case WM_CAP_FILE_GET_CAPTURE_FILEW: break;*/
        /*case WM_CAP_FILE_SAVEASW: break;*/
        /*case WM_CAP_FILE_SAVEDIBW: break;*/
        /*case WM_CAP_FILE_SET_CAPTURE_FILEW: break;*/
        case WM_CAP_GET_MCI_DEVICEW: ::print('[', WM_CAP_GET_MCI_DEVICEW, "]: Windows -> Capture Get Media Control Interface Device"); break;
        case WM_CAP_PAL_OPENW: ::print('[', WM_CAP_PAL_OPENW, "]: Windows -> Capture Palette Open"); break;
        case WM_CAP_PAL_SAVEW: ::print('[', WM_CAP_PAL_SAVEW, "]: Windows -> Capture Palette Save"); break;
        /*case WM_CAP_SET_CALLBACK_ERRORW: break;*/
        /*case WM_CAP_SET_CALLBACK_STATUSW: break;*/
        /*case WM_CAP_SET_MCI_DEVICEW: break;*/
        /*case WM_CAP_UNICODE_START: break;*/
        case WM_CHANGECBCHAIN: ::print('[', WM_CHANGECBCHAIN, "]: Windows -> Change Control Box Chain"); break;
        case WM_CHANGEUISTATE: ::print('[', WM_CHANGEUISTATE, "]: Windows -> Change User-Interface State"); break;
        case WM_CHAR: ::print('[', WM_CHAR, "]: Windows -> Character"); break;
        case WM_CHARTOITEM: ::print('[', WM_CHARTOITEM, "]: Windows -> Character to Item"); break;
        case WM_CHILDACTIVATE: ::print('[', WM_CHILDACTIVATE, "]: Windows -> Child Activate"); break;
        /*case WM_CHOOSEFONT_GETLOGFONT: break;*/
        /*case WM_CHOOSEFONT_SETFLAGS: break;*/
        /*case WM_CHOOSEFONT_SETLOGFONT: break;*/
        case WM_CLEAR: ::print('[', WM_CLEAR, "]: Windows -> Clear"); break;
        case WM_CLOSE: ::print('[', WM_CLOSE, "]: Windows -> Close"); {
            ::DestroyWindow(windowHandle);
            ::PostQuitMessage(0);
        } break;
        case WM_COMMAND: ::print('[', WM_COMMAND, "]: Windows -> Command"); break;
        case WM_COMMNOTIFY: ::print('[', WM_COMMNOTIFY, "]: Windows -> Command Notify"); break;
        case WM_COMPACTING: ::print('[', WM_COMPACTING, "]: Windows -> Compacting"); break;
        case WM_COMPAREITEM: ::print('[', WM_COMPAREITEM, "]: Windows -> Compare Item"); break;
        case WM_CONTEXTMENU: ::print('[', WM_CONTEXTMENU, "]: Windows -> Context Menu"); break;
        case WM_CONVERTREQUEST: ::print('[', WM_CONVERTREQUEST, "]: Windows -> Convert Request"); break;
        case WM_CONVERTRESULT: ::print('[', WM_CONVERTRESULT, "]: Windows -> Convert Result"); break;
        case WM_COPY: ::print('[', WM_COPY, "]: Windows -> Copy"); break;
        case WM_COPYDATA: ::print('[', WM_COPYDATA, "]: Windows -> Copy Data"); break;
        case WM_COPYGLOBALDATA: ::print('[', WM_COPYGLOBALDATA, "]: Windows -> Copy Global Data"); break;
        /*case WM_CPL_LAUNCH: break;*/
        /*case WM_CPL_LAUNCHED: break;*/
        case WM_CREATE: ::print('[', WM_CREATE, "]: Windows -> Create"); break;
        case WM_CTLCOLOR: ::print('[', WM_CTLCOLOR, "]: Windows -> Control Color"); break;
        case WM_CTLCOLORBTN: ::print('[', WM_CTLCOLORBTN, "]: Windows -> Control Color Button"); break;
        case WM_CTLCOLORDLG: ::print('[', WM_CTLCOLORDLG, "]: Windows -> Control Color Dialog"); break;
        case WM_CTLCOLOREDIT: ::print('[', WM_CTLCOLOREDIT, "]: Windows -> Control Color Editor"); break;
        case WM_CTLCOLORLISTBOX: ::print('[', WM_CTLCOLORLISTBOX, "]: Windows -> Control Color List Box"); break;
        case WM_CTLCOLORMSGBOX: ::print('[', WM_CTLCOLORMSGBOX, "]: Windows -> Control Color Message Box"); break;
        case WM_CTLCOLORSCROLLBAR: ::print('[', WM_CTLCOLORSCROLLBAR, "]: Windows -> Control Color Scrollbar"); break;
        case WM_CTLCOLORSTATIC: ::print('[', WM_CTLCOLORSTATIC, "]: Windows -> Control Color Static"); break;
        case WM_CTLINIT: ::print('[', WM_CTLINIT, "]: Windows -> Control Initiation"); break;
        case WM_CUT: ::print('[', WM_CUT, "]: Windows -> Cut"); break;
        case WM_DEADCHAR: ::print('[', WM_DEADCHAR, "]: Windows -> Dead Character"); break;
        case WM_DELETEITEM: ::print('[', WM_DELETEITEM, "]: Windows -> Delete Item"); break;
        case WM_DESTROY: ::print('[', WM_DESTROY, "]: Windows -> Destroy"); { ::PostQuitMessage(0); } break;
        case WM_DESTROYCLIPBOARD: ::print('[', WM_DESTROYCLIPBOARD, "]: Windows -> Destroy Clipboard"); break;
        case WM_DEVICECHANGE: ::print('[', WM_DEVICECHANGE, "]: Windows -> Device Change"); break;
        case WM_DEVMODECHANGE: ::print('[', WM_DEVMODECHANGE, "]: Windows -> Device Mode Change"); break;
        case WM_DISPLAYCHANGE: ::print('[', WM_DISPLAYCHANGE, "]: Windows -> Display Change"); break;
        case WM_DRAWCLIPBOARD: ::print('[', WM_DRAWCLIPBOARD, "]: Windows -> Draw Clipboard"); break;
        case WM_DRAWITEM: ::print('[', WM_DRAWITEM, "]: Windows -> Draw Item"); break;
        case WM_DROPFILES: ::print('[', WM_DROPFILES, "]: Windows -> Drop Files"); break;
        case WM_ENABLE: ::print('[', WM_ENABLE, "]: Windows -> Enable"); break;
        case WM_ENDSESSION: ::print('[', WM_ENDSESSION, "]: Windows -> End Session"); break;
        case WM_ENTERIDLE: ::print('[', WM_ENTERIDLE, "]: Windows -> Enter Idle"); break;
        case WM_ENTERMENULOOP: ::print('[', WM_ENTERMENULOOP, "]: Windows -> Enter Menu Loop"); break;
        case WM_ENTERSIZEMOVE: ::print('[', WM_ENTERSIZEMOVE, "]: Windows -> Enter Size Move"); break;
        case WM_ERASEBKGND: ::print('[', WM_ERASEBKGND, "]: Windows -> Erase Background"); break;
        case WM_EXITMENULOOP: ::print('[', WM_EXITMENULOOP, "]: Windows -> Exit Menu Loop"); break;
        case WM_EXITSIZEMOVE: ::print('[', WM_EXITSIZEMOVE, "]: Windows -> Exit Size Move"); break;
        case WM_FONTCHANGE: ::print('[', WM_FONTCHANGE, "]: Windows -> Font Change"); break;
        case WM_GETDLGCODE: ::print('[', WM_GETDLGCODE, "]: Windows -> Get Dialog Code"); break;
        case WM_GETFONT: ::print('[', WM_GETFONT, "]: Windows -> Get Font"); break;
        case WM_GETHOTKEY: ::print('[', WM_GETHOTKEY, "]: Windows -> Get Hotkey"); break;
        case WM_GETICON: ::print('[', WM_GETICON, "]: Windows -> Get Icon"); break;
        case WM_GETMINMAXINFO: ::print('[', WM_GETMINMAXINFO, "]: Windows -> Get Min-Maximum Information"); break;
        case WM_GETOBJECT: ::print('[', WM_GETOBJECT, "]: Windows -> Get Object"); break;
        case WM_GETTEXT: ::print('[', WM_GETTEXT, "]: Windows -> Get Text"); break;
        case WM_GETTEXTLENGTH: ::print('[', WM_GETTEXTLENGTH, "]: Windows -> Get Text Length"); break;
        case WM_GLOBALRCCHANGE /* -> WM_PENMISCINFO */: {
            ::println('[', WM_GLOBALRCCHANGE, "]: {");
                ::println(printt, "Windows -> Global RC Change");
                ::println(printt, "Windows -> Pen Miscellaneous Information");
            ::print('}');
        } break;
        case WM_HANDHELDFIRST: ::print('[', WM_HANDHELDFIRST, "]: Windows -> Hand-Held [FIRST]"); break;
        case WM_HANDHELDLAST: ::print('[', WM_HANDHELDLAST, "]: Windows -> Hand-Held [LAST]"); break;
        case WM_HEDITCTL /* -> WM_PENCTL */: {
            ::println('[', WM_HEDITCTL, "]: {");
                ::println(printt, "Windows -> Hand-Editing Control");
                ::println(printt, "Windows -> Pen Control");
            ::print('}');
        } break;
        case WM_HELP: ::print('[', WM_HELP, "]: Windows -> Help"); break;
        case WM_HOOKRCRESULT: ::print('[', WM_HOOKRCRESULT, "]: Windows -> Hook RC Result"); break;
        case WM_HOTKEY: ::print('[', WM_HOTKEY, "]: Windows -> Hotkey"); break;
        case WM_HSCROLL: ::print('[', WM_HSCROLL, "]: Windows -> Horizontal Scroll"); break;
        case WM_HSCROLLCLIPBOARD: ::print('[', WM_HSCROLLCLIPBOARD, "]: Windows -> Horizontal Scroll Clipboard"); break;
        case WM_ICONERASEBKGND: ::print('[', WM_ICONERASEBKGND, "]: Windows -> Icon Erase Background"); break;
        case WM_IMEKEYDOWN /* -> WM_IME_KEYDOWN */: ::print('[', WM_IMEKEYDOWN, "]: Windows -> IME Key Down"); break;
        case WM_IMEKEYUP /* -> WM_IME_KEYUP */: ::print('[', WM_IMEKEYUP, "]: Windows -> IME Key Up"); break;
        case WM_IME_CHAR: ::print('[', WM_IME_CHAR, "]: Windows -> IME Character"); break;
        case WM_IME_COMPOSITION /* -> WM_IME_KEYLAST */: ::print('[', WM_IME_COMPOSITION, "]: Windows -> IME Composition [(Key) LAST]"); break;
        case WM_IME_COMPOSITIONFULL: ::print('[', WM_IME_COMPOSITIONFULL, "]: Windows -> IME Composition Full"); break;
        case WM_IME_CONTROL: ::print('[', WM_IME_CONTROL, "]: Windows -> IME Control"); break;
        case WM_IME_ENDCOMPOSITION: ::print('[', WM_IME_ENDCOMPOSITION, "]: Windows -> IME End Composition"); break;
        /*case WM_IME_KEYDOWN: break;*/
        /*case WM_IME_KEYLAST: break;*/
        /*case WM_IME_KEYUP: break;*/
        case WM_IME_NOTIFY: ::print('[', WM_IME_NOTIFY, "]: Windows -> IME Notify"); break;
        case WM_IME_REPORT: ::print('[', WM_IME_REPORT, "]: Windows -> IME Report"); break;
        case WM_IME_REQUEST: ::print('[', WM_IME_REQUEST, "]: Windows -> IME Request"); break;
        case WM_IME_SELECT: ::print('[', WM_IME_SELECT, "]: Windows -> IME Select"); break;
        case WM_IME_SETCONTEXT: ::print('[', WM_IME_SETCONTEXT, "]: Windows -> IME Set Context"); break;
        case WM_IME_STARTCOMPOSITION: ::print('[', WM_IME_STARTCOMPOSITION, "]: Windows -> IME Start Composition"); break;
        case WM_INITDIALOG: ::print('[', WM_INITDIALOG, "]: Windows -> Initiate Dialog"); break;
        case WM_INITMENU: ::print('[', WM_INITMENU, "]: Windows -> Initiate Menu"); break;
        case WM_INITMENUPOPUP: ::print('[', WM_INITMENUPOPUP, "]: Windows -> Initiate Menu Pop-Up"); break;
        case WM_INPUT: ::print('[', WM_INPUT, "]: Windows -> Input"); break;
        case WM_INPUTLANGCHANGE: ::print('[', WM_INPUTLANGCHANGE, "]: Windows -> Input Language Change"); break;
        case WM_INPUTLANGCHANGEREQUEST: ::print('[', WM_INPUTLANGCHANGEREQUEST, "]: Windows -> Input Language Change Request"); break;
        case WM_INTERIM: ::print('[', WM_INTERIM, "]: Windows -> Interim"); break;
        case WM_KEYDOWN /* -> WM_KEYFIRST */: ::print('[', WM_KEYDOWN, "]: Windows -> Key Down [FIRST]"); {
            if (VK_ESCAPE == argument) {
                ::DestroyWindow(windowHandle);
                ::PostQuitMessage(0);
            }
        } break;
        /*case WM_KEYFIRST: break;*/
        case WM_KEYLAST: ::print('[', WM_KEYLAST, "]: Windows -> Key [LAST]"); break;
        case WM_KEYUP: ::print('[', WM_KEYUP, "]: Windows -> Key Up"); break;
        case WM_KILLFOCUS: ::print('[', WM_KILLFOCUS, "]: Windows -> Kill Focus"); break;
        case WM_LBUTTONDBLCLK: ::print('[', WM_LBUTTONDBLCLK, "]: Windows -> Left (Mouse) Button Double-Click"); break;
        case WM_LBUTTONDOWN: ::print('[', WM_LBUTTONDOWN, "]: Windows -> Left (Mouse) Button Down"); break;
        case WM_LBUTTONUP: ::print('[', WM_LBUTTONUP, "]: Windows -> Left (Mouse) Button Up"); break;
        case WM_MBUTTONDBLCLK: ::print('[', WM_MBUTTONDBLCLK, "]: Windows -> Middle (Mouse) Button Double-Click"); break;
        case WM_MBUTTONDOWN: ::print('[', WM_MBUTTONDOWN, "]: Windows -> Middle (Mouse) Button Down"); break;
        case WM_MBUTTONUP: ::print('[', WM_MBUTTONUP, "]: Windows -> Middle (Mouse) Button Up"); break;
        case WM_MDIACTIVATE: ::print('[', WM_MDIACTIVATE, "]: Windows -> Multiple-Document Interface Activate"); break;
        case WM_MDICASCADE: ::print('[', WM_MDICASCADE, "]: Windows -> Multiple-Document Interface Cascade"); break;
        case WM_MDICREATE: ::print('[', WM_MDICREATE, "]: Windows -> Multiple-Document Interface Create"); break;
        case WM_MDIDESTROY: ::print('[', WM_MDIDESTROY, "]: Windows -> Multiple-Document Interface Destroy"); break;
        case WM_MDIGETACTIVE: ::print('[', WM_MDIGETACTIVE, "]: Windows -> Multiple-Document Interface Get Active"); break;
        case WM_MDIICONARRANGE: ::print('[', WM_MDIICONARRANGE, "]: Windows -> Multiple-Document Interface Icon Arrange"); break;
        case WM_MDIMAXIMIZE: ::print('[', WM_MDIMAXIMIZE, "]: Windows -> Multiple-Document Interface Maximize"); break;
        case WM_MDINEXT: ::print('[', WM_MDINEXT, "]: Windows -> Multiple-Document Interface Next"); break;
        case WM_MDIREFRESHMENU: ::print('[', WM_MDIREFRESHMENU, "]: Windows -> Multiple-Document Interface Refresh Menu"); break;
        case WM_MDIRESTORE: ::print('[', WM_MDIRESTORE, "]: Windows -> Multiple-Document Interface Restore"); break;
        case WM_MDISETMENU: ::print('[', WM_MDISETMENU, "]: Windows -> Multiple-Document Interface Set Menu"); break;
        case WM_MDITILE: ::print('[', WM_MDITILE, "]: Windows -> Multiple-Document Interface Tile"); break;
        case WM_MEASUREITEM: ::print('[', WM_MEASUREITEM, "]: Windows -> Measure Item"); break;
        case WM_MENUCHAR: ::print('[', WM_MENUCHAR, "]: Windows -> Menu Character"); break;
        case WM_MENUCOMMAND: ::print('[', WM_MENUCOMMAND, "]: Windows -> Menu Command"); break;
        case WM_MENUDRAG: ::print('[', WM_MENUDRAG, "]: Windows -> Menu Drag"); break;
        case WM_MENUGETOBJECT: ::print('[', WM_MENUGETOBJECT, "]: Windows -> Menu Get to Object"); break;
        case WM_MENURBUTTONUP: ::print('[', WM_MENURBUTTONUP, "]: Windows -> Menu Right (Mouse) Button Up"); break;
        case WM_MENUSELECT: ::print('[', WM_MENUSELECT, "]: Windows -> Menu Select"); break;
        case WM_MOUSEACTIVATE: ::print('[', WM_MOUSEACTIVATE, "]: Windows -> Mouse Activate"); break;
        case WM_MOUSEFIRST /* -> WM_MOUSEMOVE */: ::print('[', WM_MOUSEMOVE, "]: Windows -> Mouse Move [FIRST]"); break;
        case WM_MOUSEHOVER: ::print('[', WM_MOUSEHOVER, "]: Windows -> Mouse Hover"); break;
        case WM_MOUSELAST /* -> WM_XBUTTONDBLCLK */: ::print('[', WM_XBUTTONDBLCLK, "]: Windows -> Mouse X (Mouse) Button Double-Click [LAST]"); break;
        case WM_MOUSELEAVE: ::print('[', WM_MOUSELEAVE, "]: Windows -> Mouse Leave"); break;
        /*case WM_MOUSEMOVE: break;*/
        case WM_MOUSEWHEEL: ::print('[', WM_MOUSEWHEEL, "]: Windows -> Mouse Wheel"); break;
        case WM_MOVE: ::print('[', WM_MOVE, "]: Windows -> Move"); break;
        case WM_MOVING: ::print('[', WM_MOVING, "]: Windows -> Moving"); break;
        case WM_NCACTIVATE: ::print('[', WM_NCACTIVATE, "]: Windows -> Non-Client Activate"); break;
        case WM_NCCALCSIZE: ::print('[', WM_NCCALCSIZE, "]: Windows -> Non-Client Calculate Size"); break;
        case WM_NCCREATE: ::print('[', WM_NCCREATE, "]: Windows -> Non-Client Create"); break;
        case WM_NCDESTROY: ::print('[', WM_NCDESTROY, "]: Windows -> Non-Client Destroy"); break;
        case WM_NCHITTEST: ::print('[', WM_NCHITTEST, "]: Windows -> Non-Client Hit-Test"); break;
        case WM_NCLBUTTONDBLCLK: ::print('[', WM_NCLBUTTONDBLCLK, "]: Windows -> Non-Client Left (Mouse) Button Double-Click"); break;
        case WM_NCLBUTTONDOWN: ::print('[', WM_NCLBUTTONDOWN, "]: Windows -> Non-Client Left (Mouse) Button Down"); break;
        case WM_NCLBUTTONUP: ::print('[', WM_NCLBUTTONUP, "]: Windows -> Non-Client Left (Mouse) Button Up"); break;
        case WM_NCMBUTTONDBLCLK: ::print('[', WM_NCMBUTTONDBLCLK, "]: Windows -> Non-Client Middle (Mouse) Button Double-Click"); break;
        case WM_NCMBUTTONDOWN: ::print('[', WM_NCMBUTTONDOWN, "]: Windows -> Non-Client Middle (Mouse) Button Down"); break;
        case WM_NCMBUTTONUP: ::print('[', WM_NCMBUTTONUP, "]: Windows -> Non-Client Middle (Mouse) Button Up"); break;
        case WM_NCMOUSEHOVER: ::print('[', WM_NCMOUSEHOVER, "]: Windows -> Non-Client Mouse Hover"); break;
        case WM_NCMOUSELEAVE: ::print('[', WM_NCMOUSELEAVE, "]: Windows -> Non-Client Mouse Leave"); break;
        case WM_NCMOUSEMOVE: ::print('[', WM_NCMOUSEMOVE, "]: Windows -> Non-Client Mouse Mouse"); break;
        case WM_NCPAINT: ::print('[', WM_NCPAINT, "]: Windows -> Non-Client Paint"); break;
        case WM_NCRBUTTONDBLCLK: ::print('[', WM_NCRBUTTONDBLCLK, "]: Windows -> Non-Client Right (Mouse) Button Double-Click"); break;
        case WM_NCRBUTTONDOWN: ::print('[', WM_NCRBUTTONDOWN, "]: Windows -> Non-Client Right (Mouse) Button Down"); break;
        case WM_NCRBUTTONUP: ::print('[', WM_NCRBUTTONUP, "]: Windows -> Non-Client Right (Mouse) Button Up"); break;
        case WM_NCXBUTTONDBLCLK: ::print('[', WM_NCXBUTTONDBLCLK, "]: Windows -> Non-Client X (Mouse) Button Double-Click"); break;
        case WM_NCXBUTTONDOWN: ::print('[', WM_NCXBUTTONDOWN, "]: Windows -> Non-Client X (Mouse) Button Down"); break;
        case WM_NCXBUTTONUP: ::print('[', WM_NCXBUTTONUP, "]: Windows -> Non-Client X (Mouse) Button Up"); break;
        case WM_NEXTDLGCTL: ::print('[', WM_NEXTDLGCTL, "]: Windows -> Next Dialog Control"); break;
        case WM_NEXTMENU: ::print('[', WM_NEXTMENU, "]: Windows -> Next Menu"); break;
        case WM_NOTIFY: ::print('[', WM_NOTIFY, "]: Windows -> Notify"); break;
        case WM_NOTIFYFORMAT: ::print('[', WM_NOTIFYFORMAT, "]: Windows -> Notify Format"); break;
        case WM_NULL: ::print('[', WM_NULL, "]: Windows -> [NULL]"); break;
        case WM_PAINT: ::print('[', WM_PAINT, "]: Windows -> Paint"); break;
        case WM_PAINTCLIPBOARD: ::print('[', WM_PAINTCLIPBOARD, "]: Windows -> Paint Clipboard"); break;
        case WM_PAINTICON: ::print('[', WM_PAINTICON, "]: Windows -> Paint Icon"); break;
        case WM_PALETTECHANGED: ::print('[', WM_PALETTECHANGED, "]: Windows -> Palette Changed"); break;
        case WM_PALETTEISCHANGING: ::print('[', WM_PALETTEISCHANGING, "]: Windows -> Palette is Changing"); break;
        case WM_PARENTNOTIFY: ::print('[', WM_PARENTNOTIFY, "]: Windows -> Parent Notify"); break;
        case WM_PASTE: ::print('[', WM_PASTE, "]: Windows -> Paste"); break;
        /*case WM_PENCTL: break;*/
        case WM_PENEVENT: ::print('[', WM_PENEVENT, "]: Windows -> Pen Event"); break;
        case WM_PENMISC: ::print('[', WM_PENMISC, "]: Windows -> Pen Miscellaneous"); break;
        /*case WM_PENMISCINFO: break;*/
        case WM_PENWINFIRST: ::print('[', WM_PENWINFIRST, "]: Windows -> Pen First"); break;
        case WM_PENWINLAST: ::print('[', WM_PENWINLAST, "]: Windows -> Pen Last"); break;
        case WM_POWER: ::print('[', WM_POWER, "]: Windows -> Power"); break;
        case WM_POWERBROADCAST: ::print('[', WM_POWERBROADCAST, "]: Windows -> Power Broadcast"); break;
        case WM_PRINT: ::print('[', WM_PRINT, "]: Windows -> Print"); break;
        case WM_PRINTCLIENT: ::print('[', WM_PRINTCLIENT, "]: Windows -> Print Client"); break;
        /*case WM_PSD_ENVSTAMPRECT: break;*/
        /*case WM_PSD_FULLPAGERECT: break;*/
        /*case WM_PSD_GREEKTEXTRECT: break;*/
        /*case WM_PSD_MARGINRECT: break;*/
        /*case WM_PSD_MINMARGINRECT: break;*/
        /*case WM_PSD_PAGESETUPDLG: break;*/
        /*case WM_PSD_YAFULLPAGERECT: break;*/
        case WM_QUERYDRAGICON: ::print('[', WM_QUERYDRAGICON, "]: Windows -> Query Drag Icon"); break;
        case WM_QUERYENDSESSION: ::print('[', WM_QUERYENDSESSION, "]: Windows -> Query End Session"); break;
        case WM_QUERYNEWPALETTE: ::print('[', WM_QUERYNEWPALETTE, "]: Windows -> Query New Palette"); break;
        case WM_QUERYOPEN: ::print('[', WM_QUERYOPEN, "]: Windows -> Query Open"); break;
        case WM_QUERYUISTATE: ::print('[', WM_QUERYUISTATE, "]: Windows -> Query User-Interface State"); break;
        case WM_QUEUESYNC: ::print('[', WM_QUEUESYNC, "]: Windows -> Queue Synchronization"); break;
        case WM_QUIT: ::print('[', WM_QUIT, "]: Windows -> Quit"); { ::PostQuitMessage(0); } break;
        case WM_RASDIALEVENT: ::print('[', WM_RASDIALEVENT, "]: Windows -> Routing & Remote Access Service Dial Event"); break;
        case WM_RBUTTONDBLCLK: ::print('[', WM_RBUTTONDBLCLK, "]: Windows -> Right (Mouse) Button Double-Click"); break;
        case WM_RBUTTONDOWN: ::print('[', WM_RBUTTONDOWN, "]: Windows -> Right (Mouse) Button Down"); break;
        case WM_RBUTTONUP: ::print('[', WM_RBUTTONUP, "]: Windows -> Right (Mouse) Button Up"); break;
        case WM_RCRESULT: ::print('[', WM_RCRESULT, "]: Windows -> RC Result"); break;
        case WM_RENDERALLFORMATS: ::print('[', WM_RENDERALLFORMATS, "]: Windows -> Render All Formats"); break;
        case WM_RENDERFORMAT: ::print('[', WM_RENDERFORMAT, "]: Windows -> Render Format"); break;
        case WM_SETCURSOR: ::print('[', WM_SETCURSOR, "]: Windows -> Set Cursor"); break;
        case WM_SETFOCUS: ::print('[', WM_SETFOCUS, "]: Windows -> Set Focus"); break;
        case WM_SETFONT: ::print('[', WM_SETFONT, "]: Windows -> Set Font"); break;
        case WM_SETHOTKEY: ::print('[', WM_SETHOTKEY, "]: Windows -> Set Hotkey"); break;
        case WM_SETICON: ::print('[', WM_SETICON, "]: Windows -> Set Icon"); break;
        case WM_SETREDRAW: ::print('[', WM_SETREDRAW, "]: Windows -> Set Redraw"); break;
        case WM_SETTEXT: ::print('[', WM_SETTEXT, "]: Windows -> Set Text"); break;
        case WM_SHOWWINDOW: ::print('[', WM_SHOWWINDOW, "]: Windows -> Show Window"); break;
        case WM_SIZE: ::print('[', WM_SIZE, "]: Windows -> Size"); break;
        case WM_SIZECLIPBOARD: ::print('[', WM_SIZECLIPBOARD, "]: Windows -> Size Clipboard"); break;
        case WM_SIZING: ::print('[', WM_SIZING, "]: Windows -> Sizing"); break;
        case WM_SKB: ::print('[', WM_SKB, "]: Windows -> SketchUp Backup"); break;
        case WM_SPOOLERSTATUS: ::print('[', WM_SPOOLERSTATUS, "]: Windows -> Spooler Status"); break;
        case WM_STYLECHANGED: ::print('[', WM_STYLECHANGED, "]: Windows -> Style Changed"); break;
        case WM_STYLECHANGING: ::print('[', WM_STYLECHANGING, "]: Windows -> Style Changing"); break;
        case WM_SYNCPAINT: ::print('[', WM_SYNCPAINT, "]: Windows -> Synchronized Paint"); break;
        case WM_SYSCHAR: ::print('[', WM_SYSCHAR, "]: Windows -> System Character"); break;
        case WM_SYSCOLORCHANGE: ::print('[', WM_SYSCOLORCHANGE, "]: Windows -> System Color Change"); break;
        case WM_SYSCOMMAND: ::print('[', WM_SYSCOMMAND, "]: Windows -> System Command"); break;
        case WM_SYSDEADCHAR: ::print('[', WM_SYSDEADCHAR, "]: Windows -> System Dead Character"); break;
        case WM_SYSKEYDOWN: ::print('[', WM_SYSKEYDOWN, "]: Windows -> System Key Down"); break;
        case WM_SYSKEYUP: ::print('[', WM_SYSKEYUP, "]: Windows -> System Key Up"); break;
        case WM_SYSTIMER: ::print('[', WM_SYSTIMER, "]: Windows -> System Timer"); break;
        case WM_TCARD: ::print('[', WM_TCARD, "]: Windows -> Text Card"); break;
        case WM_TIMECHANGE: ::print('[', WM_TIMECHANGE, "]: Windows -> Time Change"); break;
        case WM_TIMER: ::print('[', WM_TIMER, "]: Windows -> Timer"); break;
        case WM_UNDO: ::print('[', WM_UNDO, "]: Windows -> Undo"); break;
        case WM_UNICHAR /* -> WM_WNT_CONVERTREQUESTEX */: {
            ::println('[', WM_UNICHAR, "]: {");
                ::println(printt, "Windows -> Convert Request");
                ::println(printt, "Windows -> Unicode Character");
            ::print('}');
        } break;
        case WM_UNINITMENUPOPUP: ::print('[', WM_UNINITMENUPOPUP, "]: Windows -> Uninitiate Menu Pop-Up"); break;
        case WM_UPDATEUISTATE: ::print('[', WM_UPDATEUISTATE, "]: Windows -> Update UI State"); break;
        /*case WM_USER: break;*/
        case WM_USERCHANGED: ::print('[', WM_USERCHANGED, "]: Windows -> User Changed"); break;
        case WM_VKEYTOITEM: ::print('[', WM_VKEYTOITEM, "]: Windows -> Virtual Key to Item"); break;
        case WM_VSCROLL: ::print('[', WM_VSCROLL, "]: Windows -> Vertical Scroll"); break;
        case WM_VSCROLLCLIPBOARD: ::print('[', WM_VSCROLLCLIPBOARD, "]: Windows -> Vertical Scroll Clipboard"); break;
        case WM_WINDOWPOSCHANGED: ::print('[', WM_WINDOWPOSCHANGED, "]: Windows -> Window Position Changed"); break;
        case WM_WINDOWPOSCHANGING: ::print('[', WM_WINDOWPOSCHANGING, "]: Windows -> Window Position Changing"); break;
        case WM_WININICHANGE: ::print('[', WM_WININICHANGE, "]: Windows -> Windows INI Change"); break;
        /*case WM_WNT_CONVERTREQUESTEX: break;*/
        /*case WM_XBUTTONDBLCLK: break;*/
        case WM_XBUTTONDOWN: ::print('[', WM_XBUTTONDOWN, "]: Windows -> X Button Down"); break;
        case WM_XBUTTONUP: ::print('[', WM_XBUTTONUP, "]: Windows -> X Button Up"); break;
        default: ::print("[...]: ?"); break;
    }

    /* [End] ... --- NOTE (Lapys) -> When revoked, replace code with `println` invocation. */
    trace_end();

    // Return
    return ::DefWindowProc(windowHandle, message, argument, subargument);
}

/* Main */
int WinMain(HINSTANCE instanceHandle, HINSTANCE, LPSTR, int const windowAppearance) {
    // Initialization > Window ...
    WNDCLASS windowClass = {CS_HREDRAW | CS_VREDRAW, &windowProcedure, 0x0, 0x0, instanceHandle, 0x0, (HCURSOR) ::LoadCursor(0x0, IDC_ARROW), (HBRUSH) COLOR_WINDOW + 1, 0x0, "Window Default Class Name"};
    HWND windowHandle = NULL;
    MSG windowProcedureMessage = {windowHandle, 0x0, EXIT_SUCCESS, 0x0, 0x0, {0L, 0L}};

    // Logic > ...
    if (RegisterClass(&windowClass)) {
        // Logic > ...
        if ((windowHandle = ::CreateWindowEx(0x0, windowClass.lpszClassName, "Windows Messages", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, (int) ((float) ::GetSystemMetrics(SM_CXSCREEN) * (75.0f / 100.0f)), (int) ((float) ::GetSystemMetrics(SM_CYSCREEN) * (75.0f / 100.0f)), NULL, NULL, instanceHandle, NULL))) {
            // ...
            ::ShowWindow(windowHandle, windowAppearance); // NOTE (Lapys) ? -> ::PostMessage(windowHandle, WM_SHOWWINDOW, 0x0, 0x0);
            ::UpdateWindow(windowHandle);

            // Loop
            while (::GetMessage(&windowProcedureMessage, NULL, 0, 0)) {
                // Update > Window Procedure Message
                ::TranslateMessage(&windowProcedureMessage);
                ::DispatchMessage(&windowProcedureMessage);
            }

            // Logic > Terminate
            if (EXIT_SUCCESS != windowProcedureMessage.wParam) ::abort();
        } else ::abort();

        // Deletion
        ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
    } else ::abort();

    // Return
    return EXIT_SUCCESS;
}
