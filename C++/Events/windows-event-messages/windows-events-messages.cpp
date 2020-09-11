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
                ::println(printt, "Rich Edit -> Set Punctuation");
                ::println(printt, "Windows Capture -> Unicode Start");
            ::print('}');
        } break;
        case ACM_OPENW /* -> BFFM_SETSELECTIONW || CDM_GETFOLDERIDLIST || EM_GETWORDWRAPMODE || IPM_SETRANGE || PSM_ADDPAGE || UDM_SETPOS || WM_CAP_SET_CALLBACK_STATUSW */: {
            ::println('[', ACM_OPENW, "]: {");
                ::println(printt, "Animation Control -> Open");
                ::println(printt, "Browse for Folder -> Set Selection");
                ::println(printt, "Common Dialog -> Get Folder ID List");
                ::println(printt, "Internet Protocol -> Set Range");
                ::println(printt, "Prop Sheet -> Add Page");
                ::println(printt, "Rich Edit -> Get Word Wrap Mode");
                ::println(printt, "Up-Down Control -> Set Position");
                ::println(printt, "Windows Capture -> Set Callback Status");
            ::print('}');
        } break;
        case ACM_PLAY /* -> BFFM_ENABLEOK || CDM_GETFILEPATH || EM_GETPUNCTUATION || IPM_SETADDRESS || UDM_SETRANGE || WM_CHOOSEFONT_SETLOGFONT */: {
            ::println('[', ACM_OPENA, "]: {");
                ::println(printt, "Animation Control -> Play");
                ::println(printt, "Browse for Folder -> Enable OK");
                ::println(printt, "Common Dialog -> Get File Path");
                ::println(printt, "Internet Protocol -> Set Address");
                ::println(printt, "Rich Edit -> Get Punctuation");
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
                ::println(printt, "Rich Edit -> Set Word Wrap Mode");
                ::println(printt, "Up-Down Control -> Get Range");
                ::println(printt, "Windows Capture -> Set Callback Error");
                ::println(printt, "Windows -> Choose Font Set Flags");
            ::print('}');
        } break;

        // [Browse for Folder]
        /* case BFFM_ENABLEOK: break; */
        /* case BFFM_SETSELECTIONA: break; */
        /* case BFFM_SETSELECTIONW: break; */
        /* case BFFM_SETSTATUSTEXTA: break; */
        case BFFM_SETSTATUSTEXTW /* -> CDM_SETCONTROLTEXT || EM_SETIMECOLOR || IPM_SETFOCUS || PSM_CHANGED || UDM_GETPOS */: {
            ::println('[', ACM_OPENA, "]: {");
                ::println(printt, "Browse for Folder -> Set Status Text");
                ::println(printt, "Common Dialog -> Set Control Text");
                ::println(printt, "Internet Protocol -> Set Focus");
                ::println(printt, "Prop Sheet -> Changed");
                ::println(printt, "Rich Edit -> Set IME (Input Method Editor) Color");
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
                ::println(printt, "Status Bar -> Get Parts");
                ::println(printt, "Toolbar -> Mark Button");
                ::println(printt, "Tooltips -> New Tool");
                ::println(printt, "Trackbar -> Set Range");
                ::println(printt, "Windows -> Page Setup Dialog Full Page");
            ::print('}');
        } break;
        case CBEM_GETEDITCONTROL /* -> IE_GETPAINTDC || PBM_GETRANGE || RB_SETPARENT || SB_GETBORDERS || TBM_SETRANGEMIN || TTM_RELAYEVENT */: {
            ::println('[', CBEM_GETEDITCONTROL, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Edit Control");
                ::println(printt, "Ink Edit -> Get Paint Device Context");
                ::println(printt, "Progress Bar -> Get Range");
                ::println(printt, "Rebar -> Set Parent");
                ::println(printt, "Status Bar -> Get Borders");
                ::println(printt, "Tooltips -> Relay Event");
                ::println(printt, "Trackbar -> Set Range Minimum");
            ::print('}');
        } break;
        case CBEM_GETEXSTYLE /* -> CBEM_GETEXTENDEDSTYLE || PBM_SETBARCOLOR || RB_GETRECT || SB_SIMPLE || TBM_CLEARTICS || TB_ISBUTTONENABLED || TTM_SETTOOLINFOA */: {
            ::println('[', CBEM_GETEXSTYLE, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Extended Style");
                ::println(printt, "Progress Bar -> Set Bar Color");
                ::println(printt, "Rebar -> Get Rectangle");
                ::println(printt, "Status Bar -> Simple");
                ::println(printt, "Toolbar -> Is Button Enabled");
                ::println(printt, "Tooltip -> Set Tool Information");
                ::println(printt, "Trackbar -> Clear Ticks");
            ::print('}');
        } break;
        case CBEM_GETIMAGELIST /* -> HKM_SETRULES || PBM_DELTAPOS || RB_GETBARINFO || SB_GETTEXTLENGTHA || TBM_GETTIC || TB_PRESSBUTTON || TTM_SETDELAYTIME || WM_PSD_MARGINRECT */: {
            ::println('[', CBEM_GETIMAGELIST, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Image List");
                ::println(printt, "Hot Key -> Set Rules");
                ::println(printt, "Page Setup Dialog -> Margin Rectangle");
                ::println(printt, "Progress Bar -> Delta Position");
                ::println(printt, "Rebar -> Get Bar Information");
                ::println(printt, "Status Bar -> Get Text Length");
                ::println(printt, "Toolbar -> Press Button");
                ::println(printt, "Tooltip -> Set Delay Time");
                ::println(printt, "Trackbar -> Get Tick");
            ::print('}');
        } break;
        case CBEM_GETITEMA /* -> DDM_END || PBM_SETSTEP || RB_SETBARINFO || SB_SETPARTS || TBM_SETTIC || TB_HIDEBUTTON || TB_SETBUTTONINFOW || TTM_ADDTOOLA || WM_PSD_GREEKTEXTRECT */: {
            ::println('[', CBEM_GETITEMA, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Item");
                ::println(printt, "Direct Draw -> End");
                ::println(printt, "Page Setup Dialog -> Greek Text Rectangle");
                ::println(printt, "Progress Bar -> Set Step");
                ::println(printt, "Rebar -> Set Bar Information");
                ::println(printt, "Status Bar -> Set Parts");
                ::println(printt, "Toolbar -> Hide Button");
                ::println(printt, "Toolbar -> Set Button Information");
                ::println(printt, "Tooltip -> Add Tool");
                ::println(printt, "Trackbar -> Set Tick");
            ::print('}');
        } break;
        case CBEM_GETITEMW /* -> RB_GETROWCOUNT || SB_GETTEXTW || TB_ISBUTTONINDETERMINATE || TTM_GETTOOLCOUNT */: {
            ::println('[', CBEM_GETITEMW, "]: {");
                ::println(printt, "Combo Box (Extended) -> Get Item");
                ::println(printt, "Rebar -> Get Row Count");
                ::println(printt, "Status Bar -> Get Text");
                ::println(printt, "Toolbar -> Is Button Indeterminate");
                ::println(printt, "Tooltip -> Get Tool Count");
            ::print('}');
        } break;
        case CBEM_HASEDITCHANGED /* -> RB_INSERTBANDW || SB_GETRECT || TBM_SETSEL || TB_ISBUTTONCHECKED || TTM_HITTESTA || WIZ_QUERYNUMPAGES */: {
            ::println('[', CBEM_HASEDITCHANGED, "]: {");
                ::println(printt, "Combo Box (Extended) -> Has Edit Changed");
                ::println(printt, "Rebar -> Insert Band");
                ::println(printt, "Status Bar -> Get Rectangle");
                ::println(printt, "Toolbar -> Is Button Checked");
                ::println(printt, "Tooltip -> Hit Test");
                ::println(printt, "Trackbar -> Set Selection");
                ::println(printt, "Wizard -> Query Number of Pages");
            ::print('}');
        } break;
        case CBEM_INSERTITEMA /* -> DDM_DRAW || DM_SETDEFID || HKM_SETHOTKEY || PBM_SETRANGE || RB_INSERTBANDA || SB_SETTEXTA || TBM_GETRANGEMIN || TB_ENABLEBUTTON || TTM_ACTIVATE || WM_CHOOSEFONT_GETLOGFONT || WM_PSD_FULLPAGERECT */: {
            ::println('[', CBEM_INSERTITEMA, "]: {");
                ::println(printt, "Combo Box (Extended) -> Insert Item");
                ::println(printt, "Direct Draw -> Draw");
                ::println(printt, "Dialog -> Set Default Identity");
                ::println(printt, "Hot Key -> Set Hotkey");
                ::println(printt, "Page Setup Dialog -> Full Page Rectangle");
                ::println(printt, "Progress Bar -> Set Range");
                ::println(printt, "Rebar -> Insert Band");
                ::println(printt, "Status Bar -> Set Text");
                ::println(printt, "Toolbar -> Enable Button");
                ::println(printt, "Tooltip -> Activate");
                ::println(printt, "Trackbar -> Get Range");
                ::println(printt, "Windows -> Choose Font / Get Log Font");
            ::print('}');
        } break;
        case CBEM_INSERTITEMW /* -> RB_SETBANDINFOW || SB_SETTEXTW || TBM_SETSELSTART || TB_ISBUTTONPRESSED || TTM_GETTEXTA || WIZ_NEXT */: {
            ::println('[', CBEM_INSERTITEMW, "]: {");
                ::println(printt, "Combo Box (Extended) -> Insert Item");
                ::println(printt, "Rebar -> Set Band Information");
                ::println(printt, "Status Bar -> Set Text");
                ::println(printt, "Toolbar -> Is Button Pressed");
                ::println(printt, "Tooltip -> Get Text");
                ::println(printt, "Trackbar -> Set Selection Start");
                ::println(printt, "Wizard -> Next");
            ::print('}');
        } break;
        case CBEM_SETEXSTYLE /* -> CBEM_SETEXTENDEDSTYLE || PBM_GETPOS || RB_HITTEST || SB_SETMINHEIGHT || TBM_SETRANGEMAX || TTM_GETTOOLINFOA */: {
            ::println('[', CBEM_SETEXSTYLE, "]: {");
                ::println(printt, "Combo Box (Extended) -> Set Extended Style");
                ::println(printt, "Progress Bar -> Get Position");
                ::println(printt, "Rebar -> Hit Test");
                ::println(printt, "Status Bar -> Set Minimum Height");
                ::println(printt, "Tooltip -> Get Tool Information");
                ::println(printt, "Trackbar -> Set Range Maximum");
            ::print('}');
        } break;
        case CBEM_SETIMAGELIST /* -> DDM_BEGIN || DDM_CLOSE || DM_REPOSITION || HKM_GETHOTKEY || PBM_SETPOS || RB_DELETEBAND || SB_GETTEXTA || TBM_GETRANGEMAX || TB_CHECKBUTTON || WM_PSD_MINMARGINRECT */: {
            ::println('[', CBEM_SETIMAGELIST, "]: {");
                ::println(printt, "Combo Box (Extended) -> Set Image List");
                ::println(printt, "Dialog -> Reposition");
                ::println(printt, "Direct Draw -> Begin");
                ::println(printt, "Direct Draw -> Close");
                ::println(printt, "Hot Key -> Get Hotkey");
                ::println(printt, "Page Setup Dialog -> Minimum Margin Rectangle");
                ::println(printt, "Progress Bar -> Set Position");
                ::println(printt, "Rebar -> Delete Band");
                ::println(printt, "Status Bar -> Get Text");
                ::println(printt, "Toolbar -> Check Button");
                ::println(printt, "Trackbar -> Get Range Maximum");
            ::print('}');
        } break;
        case CBEM_SETITEMA /* -> PBM_STEPIT || TBM_SETPOS || TB_INDETERMINATE || TTM_DELTOOLA || WM_PSD_ENVSTAMPRECT */: {
            ::println('[', CBEM_SETITEMA, "]: {");
                ::println(printt, "Combo Box (Extended) -> Set Item");
                ::println(printt, "Page Setup Dialog -> Envelope Stamp Rectangle");
                ::println(printt, "Progress Bar -> Step It");
                ::println(printt, "Toolbar -> Indeterminate");
                ::println(printt, "Tooltip -> Delete Tool");
                ::println(printt, "Trackbar -> Set Position");
            ::print('}');
        } break;
        case CBEM_SETITEMW /* -> RB_GETBANDCOUNT || SB_GETTEXTLENGTHW || TBM_SETSELEND || TB_ISBUTTONHIDDEN || TTM_UPDATETIPTEXTA || WIZ_PREV */: {
            ::println('[', CBEM_SETITEMW, "]: {");
                ::println(printt, "Combo Box (Extended) -> Set Item");
                ::println(printt, "Rebar -> Get Band Count");
                ::println(printt, "Status Bar -> Get Text Length");
                ::println(printt, "Toolbar -> Is Button Hidden");
                ::println(printt, "Tooltip -> Update Tip Text");
                ::println(printt, "Trackbar -> Set Selection End");
                ::println(printt, "Wizard -> Previous");
            ::print('}');
        } break;

        // [Common Item Dialog]
        /* case CDM_GETFILEPATH: break; */
        /* case CDM_GETFOLDERIDLIST: break; */
        /* case CDM_GETFOLDERPATH: break; */
        case CDM_HIDECONTROL /* -> EM_GETIMECOLOR || IPM_ISBLANK || PSM_RESTARTWINDOWS || UDM_SETBUDDY */: {
            ::println('[', CDM_HIDECONTROL, "]: {");
                ::println(printt, "Common Dialog -> Hide Control");
                ::println(printt, "Internet Protocol -> Is Blank");
                ::println(printt, "Prop Sheet -> Restart Windows");
                ::println(printt, "Rich Edit -> Get IME (Input Method Editor) Color");
                ::println(printt, "Up-Down Control -> Set Buddy");
            ::print('}');
        } break;
        /* case CDM_FIRST: break; */
        /* case CDM_GETSPEC: break; */
        case CDM_LAST /* (Lapys) -> EM_SETBIDIOPTIONS || IE_DOCOMMAND || MCIWNDM_NOTIFYMODE */: {
            ::println('[', CDM_LAST, "]: {");
                ::println(printt, "Common Dialog [LAST]");
                ::println(printt, "Ink Edit -> Do Command");
                ::println(printt, "Multimedia MCI Window -> Notify Mode");
                ::println(printt, "Rich Edit -> Set Bi-directional Options");
            ::print('}');
        } break;
        /* case CDM_SETCONTROLTEXT: break; */
        case CDM_SETDEFEXT /* -> EM_SETIMEOPTIONS || PSM_REBOOTSYSTEM || UDM_GETBUDDY */: {
            ::println('[', CDM_SETDEFEXT, "]: {");
                ::println(printt, "Common Dialog -> Set Default Text");
                ::println(printt, "Prop Sheet -> Reboot System");
                ::println(printt, "Rich Edit -> Set IME (Input Method Editor) Options");
                ::println(printt, "Up-Down Control -> Get Buddy");
            ::print('}');
        } break;

        // [Direct Draw]
        /* case DDM_BEGIN: break; */
        /* case DDM_CLOSE: break; */
        /* case DDM_DRAW: break; */
        /* case DDM_END: break; */
        case DDM_SETFMT /* -> DM_GETDEFID || NIN_SELECT || TBM_GETPOS || WM_PSD_PAGESETUPDLG || WM_USER */: {
            ::println('[', DDM_SETFMT, "]: {");
                ::println(printt, "Dialog -> Get Default Identity");
                ::println(printt, "Direct Draw -> Set Format");
                ::println(printt, "Notify Icon -> Select");
                ::println(printt, "Page Setup Dialog -> Page Setup Dialog");
                ::println(printt, "Trackbar -> Get Position");
                ::println(printt, "Windows [USER]");
            ::print('}');
        } break;

        // [Drag List (Box)]
        case DL_BEGINDRAG /* -> MCIWNDM_GETINACTIVETIMER || PSM_IDTOINDEX || TB_BUTTONCOUNT || TTM_SETMAXTIPWIDTH */: {
            ::println('[', DL_BEGINDRAG, "]: {");
                ::println(printt, "Drag List Box -> Begin Drag");
                ::println(printt, "Multimedia MCI Window -> Get Inactive Timer");
                ::println(printt, "Prop Sheet -> Identity to Index");
                ::println(printt, "Toolbar -> Button Count");
                ::println(printt, "Tooltip -> Set Maximum Tip Width");
            ::print('}');
        } break;
        case DL_CANCELDRAG /* -> PSM_RECALCPAGESIZES */: {
            ::println('[', DL_CANCELDRAG, "]: {");
                ::println(printt, "Drag List Box -> Cancel Drag");
                ::println(printt, "Prop Sheet -> Recalculate Page Sizes");
            ::print('}');
        } break;
        case DL_DRAGGING /* -> PSM_INDEXTOID */: {
            ::println('[', DL_DRAGGING, "]: {");
                ::println(printt, "Drag List Box -> Dragging");
                ::println(printt, "Prop Sheet -> Index to Identity");
            ::print('}');
        } break;
        case DL_DROPPED /* -> PSM_GETRESULT */: {
            ::println('[', DL_DROPPED, "]: {");
                ::println(printt, "Drag List Box -> Dropped");
                ::println(printt, "Prop Sheet -> Get Results");
            ::print('}');
        } break;

        // [Dialog]
        /* case DM_GETDEFID: break; */
        /* case DM_REPOSITION: break; */
        /* case DM_SETDEFID: break; */

        // [Rich Edit]
        case EM_AUTOURLDETECT /* -> TB_GETSTRINGW */: {
            ::println('[', EM_AUTOURLDETECT, "]: {");
                ::println(printt, "Rich Edit -> Automatic URL Detect");
                ::println(printt, "Toolbar -> Get String");
            ::print('}');
        } break;
        case EM_CANPASTE /* -> TB_LOADIMAGES */: {
            ::println('[', EM_CANPASTE, "]: {");
                ::println(printt, "Rich Edit -> Can Paste");
                ::println(printt, "Toolbar -> Load Images");
            ::print('}');
        } break;
        case EM_CANREDO /* -> TB_GETEXTENDEDSTYLE */: {
            ::println('[', EM_CANREDO, "]: {");
                ::println(printt, "Rich Edit -> Can Redo");
                ::println(printt, "Toolbar -> Get Extended Style");
            ::print('}');
        } break;
        case EM_CANUNDO: ::print('[', EM_CANUNDO, "]: Rich Edit -> Can Undo"); break;
        case EM_CHARFROMPOS: ::print('[', EM_CHARFROMPOS, "]: Rich Edit -> Character from Position"); break;
        case EM_CONVPOSITION /* -> PSM_QUERYSIBLINGS || UDM_GETACCEL */: {
            ::println('[', EM_CONVPOSITION, "]: {");
                ::println(printt, "Prop Sheet -> Query Siblings");
                ::println(printt, "Rich Edit -> Conv... Position");
                ::println(printt, "Up-Down Control -> Get Acceleration");
            ::print('}');
        } break;
        case EM_DISPLAYBAND /* -> TB_GETRECT || TTM_DELTOOLW */: {
            ::println('[', EM_DISPLAYBAND, "]: {");
                ::println(printt, "Rich Edit -> Display Band");
                ::println(printt, "Toolbar -> Get Rectangle");
                ::println(printt, "Tooltip -> Delete Tool");
            ::print('}');
        } break;
        case EM_EMPTYUNDOBUFFER: ::print('[', EM_EMPTYUNDOBUFFER, "]: Rich Edit -> Empty Undo Buffer"); break;
        case EM_EXGETSEL /* -> TB_SETHOTIMAGELIST || TTM_NEWTOOLRECTW */: {
            ::println('[', EM_EXGETSEL, "]: {");
                ::println(printt, "Rich Edit -> Extend Get Selection");
                ::println(printt, "Toolbar -> Set Hot Image List");
                ::println(printt, "Tooltip -> New Tool Rectangle");
            ::print('}');
        } break;
        case EM_EXLIMITTEXT /* -> TB_GETHOTIMAGELIST || TTM_GETTOOLINFOW */: {
            ::println('[', EM_EXLIMITTEXT, "]: {");
                ::println(printt, "Rich Edit -> Extend Limit Text");
                ::println(printt, "Toolbar -> Get Hot Image List");
                ::println(printt, "Tooltip -> Get Tool Information");
            ::print('}');
        } break;
        case EM_EXLINEFROMCHAR /* -> TB_SETDISABLEDIMAGELIST || TTM_SETTOOLINFOW */: {
            ::println('[', EM_EXLINEFROMCHAR, "]: {");
                ::println(printt, "Rich Edit -> Extend Line From Character");
                ::println(printt, "Toolbar -> Set Disabled Image List");
                ::println(printt, "Tooltip -> Set Tool Information");
            ::print('}');
        } break;
        case EM_EXSETSEL /* -> TB_GETDISABLEDIMAGELIST || TTM_HITTESTW */: {
            ::println('[', EM_EXSETSEL, "]: {");
                ::println(printt, "Rich Edit -> Extend Set Selection");
                ::println(printt, "Toolbar -> Get Disabled Image List");
                ::println(printt, "Tooltip -> Hit Test");
            ::print('}');
        } break;
        case EM_FINDTEXT /* -> TB_SETSTYLE || TTM_GETTEXTW */: {
            ::println('[', EM_FINDTEXT, "]: {");
                ::println(printt, "Rich Edit -> Find Text");
                ::println(printt, "Toolbar -> Set Style");
                ::println(printt, "Tooltip -> Get Text");
            ::print('}');
        } break;
        case EM_FINDTEXTEX /* -> TB_GETINSERTMARK */: {
            ::println('[', EM_FINDTEXTEX, "]: {");
                ::println(printt, "Rich Edit -> Find Text (Extended)");
                ::println(printt, "Toolbar -> Get Insert Mark");
            ::print('}');
        } break;
        case EM_FINDTEXTEXW /* -> MCIWNDM_GETFILENAMEA */: {
            ::println('[', EM_FINDTEXTEXW, "]: {");
                ::println(printt, "Rich Edit -> Find Text (Extended)");
                ::println(printt, "Multimedia (MCI) Window -> Get File Name");
            ::print('}');
        } break;
        case EM_FINDTEXTW /* -> MCIWNDM_PLAYTO || WM_CAP_FILE_SAVEASW */: {
            ::println('[', EM_FINDTEXTW, "]: {");
                ::println(printt, "Rich Edit -> Find Text (Extended)");
                ::println(printt, "Multimedia (MCI) Window -> Play To");
                ::println(printt, "Windows Capture -> File Save As");
            ::print('}');
        } break;
        case EM_FINDWORDBREAK /* -> TB_SAVERESTOREW */: {
            ::println('[', EM_FINDWORDBREAK, "]: {");
                ::println(printt, "Rich Edit -> Find Word Break");
                ::println(printt, "Toolbar -> Save Restore");
            ::print('}');
        } break;
        case EM_FMTLINES: ::print('[', EM_FMTLINES, "]: Rich Edit -> Format Lines"); break;
        case EM_FORMATRANGE /* -> TB_GETSTYLE || TTM_UPDATETIPTEXTW */: {
            ::println('[', EM_FORMATRANGE, "]: {");
                ::println(printt, "Rich Edit -> Format Range");
                ::println(printt, "Toolbar -> Get Style");
                ::println(printt, "Tooltip -> Update Tip Text");
            ::print('}');
        } break;
        case EM_GETAUTOURLDETECT /* -> TB_GETSTRINGA */: {
            ::println('[', EM_GETAUTOURLDETECT, "]: {");
                ::println(printt, "Rich Edit -> Get Automatic URL Detection");
                ::println(printt, "Toolbar -> Get String");
            ::print('}');
        } break;
        case EM_GETBIDIOPTIONS /* -> IE_GETCOMMAND */: {
            ::println('[', EM_GETBIDIOPTIONS, "]: {");
                ::println(printt, "Ink Edit - Get Command");
                ::println(printt, "Rich Edit -> Get Bi-directional Options");
            ::print('}');
        } break;
        case EM_GETCHARFORMAT /* -> TB_GETBUTTONSIZE || TTM_ENUMTOOLSW */: {
            ::println('[', EM_GETCHARFORMAT, "]: {");
                ::println(printt, "Rich Edit -> Get Character Format");
                ::println(printt, "Toolbar -> Get Button Size");
                ::println(printt, "Tooltip -> Enumerate Tools");
            ::print('}');
        } break;
        case EM_GETCTFMODEBIAS: ::print('[', EM_GETCTFMODEBIAS, "]: Rich Edit -> Get CTF Mode Bias"); break;
        case EM_GETCTFOPENSTATUS: ::print('[', EM_GETCTFOPENSTATUS, "]: Rich Edit -> Get CTF Open Status"); break;
        case EM_GETEDITSTYLE /* -> MCIWNDM_NOTIFYERROR */: {
            ::println('[', EM_GETEDITSTYLE, "]: {");
                ::println(printt, "Rich Edit -> Get Edit Style");
                ::println(printt, "Multimedia MCI Window -> Notify Error");
            ::print('}');
        } break;
        case EM_GETEVENTMASK /* -> TB_SETBUTTONWIDTH || TTM_GETCURRENTTOOLW */: {
            ::println('[', EM_GETEVENTMASK, "]: {");
                ::println(printt, "Rich Edit -> Get Event Mask");
                ::println(printt, "Toolbar -> Set Button Width");
                ::println(printt, "Tooltip -> Get Current Tool");
            ::print('}');
        } break;
        case EM_GETFIRSTVISIBLELINE: ::print('[', EM_GETFIRSTVISIBLELINE, "]: Rich Edit -> Get First Visible Line"); break;
        case EM_GETHANDLE: ::print('[', EM_GETHANDLE, "]: Rich Edit -> Get Handle"); break;
        case EM_GETHYPHENATEINFO: ::print('[', EM_GETHYPHENATEINFO, "]: Rich Edit -> Get Hyphenate Information"); break;
        /* case EM_GETIMECOLOR: break; */
        case EM_GETIMECOMPMODE: ::print('[', EM_GETIMECOMPMODE, "]: Rich Edit -> Get IME (Input Method Editor) Composition Mode"); break;
        case EM_GETIMECOMPTEXT: ::print('[', EM_GETIMECOMPTEXT, "]: Rich Edit -> Get IME (Input Method Editor) Composition Text"); break;
        case EM_GETIMEMODEBIAS /* -> MCIWNDM_SETPALETTE || PSM_SETHEADERSUBTITLEA */: {
            ::println('[', EM_GETIMEMODEBIAS, "]: {");
                ::println(printt, "Rich Edit -> Get IME (Input Method Editor) Mode Bias");
                ::println(printt, "Multimedia MCI Window -> Set Palette");
                ::println(printt, "Prop Sheet -> Set Header Subtitle");
            ::print('}');
        } break;
        case EM_GETIMEOPTIONS /* -> PSM_CANCELTOCLOSE || UDM_SETACCEL */: {
            ::println('[', EM_GETIMEOPTIONS, "]: {");
                ::println(printt, "Rich Edit -> Get IME (Input Method Editor) Options");
                ::println(printt, "Prop Sheet -> Cancel to Close");
                ::println(printt, "Up-Down Control -> Set Acceleration");
            ::print('}');
        } break;
        case EM_GETIMEPROPERTY: ::print('[', EM_GETIMECOMPTEXT, "]: Rich Edit -> Get IME (Input Method Editor) Property"); break;
        case EM_GETIMESTATUS: ::print('[', EM_GETIMESTATUS, "]: Rich Edit -> Get IME (Input Method Editor) Status"); break;
        case EM_GETLANGOPTIONS /* -> MCIWNDM_VALIDATEMEDIA || PSM_SETCURSEL || PSM_SETFINISHTEXTA || PSM_SETFINISHTEXTW || WM_CAP_FILE_GET_CAPTURE_FILEW */: {
            ::println('[', EM_GETLANGOPTIONS, "]: {");
                ::println(printt, "Rich Edit -> Get Language Options");
                ::println(printt, "Multimedia (MCI) Window -> Validate Media");
                ::println(printt, "Prop Sheet -> Set Cursor Selection");
                ::println(printt, "Prop Sheet -> Set Finish Text");
                ::println(printt, "Windows Capture -> File Get Capture");
            ::print('}');
        } break;
        case EM_GETLIMITTEXT: ::print('[', EM_GETLIMITTEXT, "]: Rich Edit -> Get Limit Text"); break;
        case EM_GETLINE: ::print('[', EM_GETLINE, "]: Rich Edit -> Get Line"); break;
        case EM_GETLINECOUNT: ::print('[', EM_GETLINECOUNT, "]: Rich Edit -> Get Line Count"); break;
        case EM_GETMARGINS: ::print('[', EM_GETMARGINS, "]: Rich Edit -> Get Margins"); break;
        case EM_GETMODIFY: ::print('[', EM_GETMODIFY, "]: Rich Edit -> Get Modify"); break;
        case EM_GETOLEINTERFACE /* -> TB_SETMAXTEXTROWS */: {
            ::println('[', EM_GETOLEINTERFACE, "]: {");
                ::println(printt, "Rich Edit -> Get Tole Interface");
                ::println(printt, "Toolbar -> Set Maximum Text Rows");
            ::print('}');
        } break;
        case EM_GETOPTIONS /* -> TB_MAPACCELERATORA */: {
            ::println('[', EM_GETOPTIONS, "]: {");
                ::println(printt, "Rich Edit -> Get Options");
                ::println(printt, "Toolbar -> Map Accelerator");
            ::print('}');
        } break;
        case EM_GETPAGE: ::print('[', EM_GETPAGE, "]: Rich Edit -> Get Page"); break;
        case EM_GETPAGEROTATE: ::print('[', EM_GETPAGEROTATE, "]: Rich Edit -> Get Page Rotate"); break;
        case EM_GETPARAFORMAT /* -> TB_GETTEXTROWS */: {
            ::println('[', EM_GETPARAFORMAT, "]: {");
                ::println(printt, "Rich Edit -> Get Paragraph Format");
                ::println(printt, "Toolbar -> Get Text Rows");
            ::print('}');
        } break;
        case EM_GETPASSWORDCHAR: ::print('[', EM_GETPASSWORDCHAR, "]: Rich Edit -> Get Password Character"); break;
        /* case EM_GETPUNCTUATION: break; */
        /* case EM_GETQUERYRTFOBJ: break; */
        case EM_GETRECT: ::print('[', EM_GETRECT, "]: Rich Edit -> Get Rectangle"); break;
        case EM_GETREDONAME /* -> TB_SETPADDING */: {
            ::println('[', EM_GETREDONAME, "]: {");
                ::println(printt, "Rich Edit -> Get Redo Name");
                ::println(printt, "Toolbar -> Set Padding");
            ::print('}');
        } break;
        case EM_GETSCROLLPOS: ::print('[', EM_GETSCROLLPOS, "]: Rich Edit -> Get Scroll Position"); break;
        case EM_GETSEL: ::print('[', EM_GETSEL, "]: Rich Edit -> Get Selection"); break;
        case EM_GETSELTEXT /* -> TB_GETOBJECT */: {
            ::println('[', EM_GETSELTEXT, "]: {");
                ::println(printt, "Rich Edit -> Get Selection Text");
                ::println(printt, "Toolbar -> Get Object");
            ::print('}');
        } break;
        case EM_GETTEXTEX: ::print('[', EM_GETTEXTEX, "]: Rich Edit -> Get Text (Extended)"); break;
        case EM_GETTEXTLENGTHEX: ::print('[', EM_GETTEXTLENGTHEX, "]: Rich Edit -> Get Text Length (Extended)"); break;
        case EM_GETTEXTMODE /* -> TB_MAPACCELERATORW */: {
            ::println('[', EM_GETTEXTMODE, "]: {");
                ::println(printt, "Rich Edit -> Get Text Mode");
                ::println(printt, "Toolbar -> Map Acceleration");
            ::print('}');
        } break;
        case EM_GETTEXTRANGE /* -> TB_GETBUTTONTEXTW */: {
            ::println('[', EM_GETTEXTRANGE, "]: {");
                ::println(printt, "Rich Edit -> Get Text Range");
                ::println(printt, "Toolbar -> Get Button Text");
            ::print('}');
        } break;
        case EM_GETTHUMB: ::print('[', EM_GETTHUMB, "]: Rich Edit -> Get Thumb"); break;
        case EM_GETTYPOGRAPHYOPTIONS /* -> IE_GETGESTURE || MCIWNDM_NOTIFYMEDIA */: {
            ::println('[', EM_GETTYPOGRAPHYOPTIONS, "]: {");
                ::println(printt, "Ink Edit -> Get Gesture");
                ::println(printt, "Multimedia (MCI) Window -> Notify Media");
                ::println(printt, "Rich Edit -> Get Typography Options");
            ::print('}');
        } break;
        case EM_GETUNDONAME /* -> TB_GETPADDING */: {
            ::println('[', EM_GETUNDONAME, "]: {");
                ::println(printt, "Rich Edit -> Get Undo Name");
                ::println(printt, "Toolbar -> Get Padding");
            ::print('}');
        } break;
        case EM_GETVIEWKIND: ::print('[', EM_GETVIEWKIND, "]: Rich Edit -> Get View Kind"); break;
        case EM_GETWORDBREAKPROC: ::print('[', EM_GETVIEWKIND, "]: Rich Edit -> Get Word Break Procedure"); break;
        case EM_GETWORDBREAKPROCEX /* -> TB_SETINSERTMARK */: {
            ::println('[', EM_GETWORDBREAKPROCEX, "]: {");
                ::println(printt, "Rich Edit -> Get Word Break Procedure (Extended)");
                ::println(printt, "Toolbar -> Set Insert Mark");
            ::print('}');
        } break;
        /* case EM_GETWORDWRAPMODE: break; */
        case EM_GETZOOM /* -> MCIWNDM_GETFILENAMEW */: {
            ::println('[', EM_GETZOOM, "]: {");
                ::println(printt, "Multimedia (MCI) Window -> Get File Name");
                ::println(printt, "Rich Edit -> Get Zoom");
            ::print('}');
        } break;
        case EM_HIDESELECTION /* -> TB_GETBUTTONINFOW */: {
            ::println('[', EM_HIDESELECTION, "]: {");
                ::println(printt, "Rich Edit -> Hide Selection");
                ::println(printt, "Toolbar -> Get Button Information");
            ::print('}');
        } break;
        case EM_ISIME: ::print('[', EM_ISIME, "]: Rich Edit -> Is IME (Input Method Editor)"); break;
        case EM_LIMITTEXT /* -> EM_SETLIMITTEXT */: {
            ::println('[', EM_LIMITTEXT, "]: {");
                ::println(printt, "Rich Edit -> Limit Text");
                ::println(printt, "Rich Edit -> Set Limit Text");
            ::print('}');
        } break;
        case EM_LINEFROMCHAR: ::print('[', EM_LINEFROMCHAR, "]: Rich Edit -> Line From Character"); break;
        case EM_LINEINDEX: ::print('[', EM_LINEINDEX, "]: Rich Edit -> Line Index"); break;
        case EM_LINELENGTH: ::print('[', EM_LINELENGTH, "]: Rich Edit -> Line Length"); break;
        case EM_LINESCROLL: ::print('[', EM_LINESCROLL, "]: Rich Edit -> Line Scroll"); break;
        case EM_OUTLINE: ::print('[', EM_OUTLINE, "]: Rich Edit -> Line Outline"); break;
        case EM_PASTESPECIAL: ::print('[', EM_PASTESPECIAL, "]: Rich Edit -> Line Paste Special"); break;
        case EM_POSFROMCHAR: ::print('[', EM_POSFROMCHAR, "]: Rich Edit -> Line Position from Character"); break;
        case EM_RECONVERSION /* -> MCIWNDM_GETDEVICEA || PSM_SETHEADERTITLEA || WM_CAP_FILE_SAVEDIBW */: {
            ::println('[', EM_RECONVERSION, "]: {");
                ::println(printt, "Multimedia (MCI) Window -> Get Device");
                ::println(printt, "Prop Sheet -> Set Header Title");
                ::println(printt, "Rich Edit -> Reconversion");
                ::println(printt, "Windows Capture -> File Save ...");
            ::print('}');
        } break;
        case EM_REDO /* -> TB_SETEXTENDEDSTYLE */: {
            ::println('[', EM_REDO, "]: {");
                ::println(printt, "Rich Edit -> Redo");
                ::println(printt, "Toolbar -> Set Extended Style");
            ::print('}');
        } break;
        case EM_REPLACESEL: ::print('[', EM_REPLACESEL, "]: Rich Edit -> Replace Selection"); break;
        case EM_REQUESTRESIZE /* -> TB_GETBUTTONINFOA */: {
            ::println('[', EM_REQUESTRESIZE, "]: {");
                ::println(printt, "Rich Edit -> Request Resize");
                ::println(printt, "Toolbar -> Get Button Information");
            ::print('}');
        } break;
        case EM_SCROLL: ::print('[', EM_SCROLL, "]: Rich Edit -> Scroll"); break;
        case EM_SCROLLCARET: ::print('[', EM_SCROLLCARET, "]: Rich Edit -> Scroll Caret"); break;
        case EM_SELECTIONTYPE /* -> TB_SETBUTTONINFOA */: {
            ::println('[', EM_SELECTIONTYPE, "]: {");
                ::println(printt, "Rich Edit -> Selection Type");
                ::println(printt, "Toolbar -> Set Button Information");
            ::print('}');
        } break;
        /* case EM_SETBIDIOPTIONS: break; */
        case EM_SETBKGNDCOLOR /* -> TB_INSERTBUTTONW */: {
            ::println('[', EM_SETBKGNDCOLOR, "]: {");
                ::println(printt, "Rich Edit -> Set Background Color");
                ::println(printt, "Toolbar -> Insert Button");
            ::print('}');
        } break;
        case EM_SETCHARFORMAT /* -> TB_ADDBUTTONSW */: {
            ::println('[', EM_SETCHARFORMAT, "]: {");
                ::println(printt, "Rich Edit -> Set Character Format");
                ::println(printt, "Toolbar -> Add Buttons");
            ::print('}');
        } break;
        case EM_SETCTFMODEBIAS: ::print('[', EM_SETCTFMODEBIAS, "]: Rich Edit -> Set CTF Mode Bias"); break;
        case EM_SETCTFOPENSTATUS: ::print('[', EM_SETCTFOPENSTATUS, "]: Rich Edit -> Set CTF Open Status"); break;
        case EM_SETEDITSTYLE /* -> IE_GETMENU */: {
            ::println('[', EM_SETEDITSTYLE, "]: {");
                ::println(printt, "Ink Edit -> Get Menu");
                ::println(printt, "Rich Edit -> Set Edit Style");
            ::print('}');
        } break;
        case EM_SETEVENTMASK /* -> TB_HITTEST */: {
            ::println('[', EM_SETEVENTMASK, "]: {");
                ::println(printt, "Rich Edit -> Set Event Mask");
                ::println(printt, "Toolbar -> Hit Test");
            ::print('}');
        } break;
        case EM_SETFONT: ::print('[', EM_SETFONT, "]: Rich Edit -> Set Font"); break;
        case EM_SETFONTSIZE: ::print('[', EM_SETFONTSIZE, "]: Rich Edit -> Set Font Size"); break;
        case EM_SETHANDLE: ::print('[', EM_SETHANDLE, "]: Rich Edit -> Set Handle"); break;
        case EM_SETHYPHENATEINFO: ::print('[', EM_SETHYPHENATEINFO, "]: Rich Edit -> Set Hyphenate Information"); break;
        /* case EM_SETIMECOLOR: break; */
        case EM_SETIMEMODEBIAS /* -> MCIWNDM_GETPALETTE || PSM_SETHEADERTITLEW */: {
            ::println('[', EM_SETIMEMODEBIAS, "]: {");
                ::println(printt, "Multimedia (MCI) Window -> Get Palette");
                ::println(printt, "Prop Sheet -> Set Header Title");
                ::println(printt, "Rich Edit -> Set IME (Input Method Editor) Mode Bias");
            ::print('}');
        } break;
        /* case EM_SETIMEOPTIONS: break; */
        case EM_SETIMESTATUS: ::print('[', EM_SETIMESTATUS, "]: Rich Edit -> Set Time Status"); break;
        case EM_SETLANGOPTIONS /* -> MCIWNDM_GETTIMEFORMATA || PSM_SETTITLEW || WM_CAP_FILE_SET_CAPTURE_FILEW */: {
            ::println('[', EM_SETLANGOPTIONS, "]: {");
                ::println(printt, "Multimedia (MCI) Window -> Get Time Format");
                ::println(printt, "Prop Sheet -> Set Title");
                ::println(printt, "Rich Edit -> Set Language Options");
                ::println(printt, "Windows Capture -> File Set Capture File");
            ::print('}');
        } break;
        case EM_SETMARGINS: ::print('[', EM_SETMARGINS, "]: Rich Edit -> Set Margins"); break;
        case EM_SETMODIFY: ::print('[', EM_SETMODIFY, "]: Rich Edit -> Set Modify"); break;
        /* case EM_SETLIMITTEXT: break; */
        case EM_SETOLECALLBACK /* -> TB_SETDRAWTEXTFLAGS */: {
            ::println('[', EM_SETOLECALLBACK, "]: {");
                ::println(printt, "Rich Edit -> Set OLE (Object Linking & Embedding) Callback");
                ::println(printt, "Toolbar -> Set Draw Text Flags");
            ::print('}');
        } break;
        case EM_SETOPTIONS /* -> TB_ADDSTRINGW */: {
            ::println('[', EM_SETOLECALLBACK, "]: {");
                ::println(printt, "Rich Edit -> Set Options");
                ::println(printt, "Toolbar -> Add String");
            ::print('}');
        } break;
        case EM_SETPAGE: ::print('[', EM_SETPAGE, "]: Rich Edit -> Set Page"); break;
        case EM_SETPAGEROTATE: ::print('[', EM_SETPAGEROTATE, "]: Rich Edit -> Set Page Rotate"); break;
        case EM_SETPALETTE: ::print('[', EM_SETPALETTE, "]: Rich Edit -> Set Palette"); break;
        case EM_SETPARAFORMAT /* -> TB_GETHOTITEM */: {
            ::println('[', EM_SETPARAFORMAT, "]: {");
                ::println(printt, "Rich Edit -> Set Paragraph Format");
                ::println(printt, "Toolbar -> Get Hot Item");
            ::print('}');
        } break;
        case EM_SETPASSWORDCHAR: ::print('[', EM_SETPASSWORDCHAR, "]: Rich Edit -> Set Password Character"); break;
        /*case EM_SETPUNCTUATION: break*/
        case EM_SETQUERYRTFOBJ: ::print('[', EM_SETQUERYRTFOBJ, "]: Rich Edit -> Set Query Rich-Text Format Object"); break;
        case EM_SETREADONLY: ::print('[', EM_SETREADONLY, "]: Rich Edit -> Set Read-Only"); break;
        case EM_SETRECT: ::print('[', EM_SETRECT, "]: Rich Edit -> Set Rectangle"); break;
        case EM_SETRECTNP: ::print('[', EM_SETRECTNP, "]: Rich Edit -> Set Rectangle New Position"); break;
        case EM_SETSCROLLPOS: ::print('[', EM_SETSCROLLPOS, "]: Rich Edit -> Set Scroll Position"); break;
        case EM_SETSEL: ::print('[', EM_SETSEL, "]: Rich Edit -> Set Selection"); break;
        case EM_SETTABSTOPS: ::print('[', EM_SETTABSTOPS, "]: Rich Edit -> Set Absolute Stops"); break;
        case EM_SETTARGETDEVICE /* -> TB_SETHOTITEM */: {
            ::println('[', EM_SETTARGETDEVICE, "]: {");
                ::println(printt, "Rich Edit -> Set Target Device");
                ::println(printt, "Toolbar -> Set Hot Item");
            ::print('}');
        } break;
        case EM_SETTEXTEX: ::print('[', EM_SETTEXTEX, "]: Rich Edit -> Set Text (Extended)"); break;
        case EM_SETTEXTMODE /* -> TB_GETINSERTMARKCOLOR */: {
            ::println('[', EM_SETTEXTMODE, "]: {");
                ::println(printt, "Rich Edit -> Set Text Mode");
                ::println(printt, "Toolbar -> Get Insert Mark Color");
            ::print('}');
        } break;
        case EM_SETTYPOGRAPHYOPTIONS /* -> IE_GETCOUNT */: {
            ::println('[', EM_SETTYPOGRAPHYOPTIONS, "]: {");
                ::println(printt, "Ink Edit -> Get Count");
                ::println(printt, "Rich Edit -> Set Typography Options");
            ::print('}');
        } break;
        case EM_SETUNDOLIMIT /* -> TB_MOVEBUTTON */: {
            ::println('[', EM_SETUNDOLIMIT, "]: {");
                ::println(printt, "Rich Edit -> Set Undo Limit");
                ::println(printt, "Toolbar -> Move Button");
            ::print('}');
        } break;
        case EM_SETVIEWKIND: ::print('[', EM_SETVIEWKIND, "]: Rich Edit -> Set View Kind"); break;
        case EM_SETWORDBREAK: ::print('[', EM_SETWORDBREAK, "]: Rich Edit -> Set Word Break"); break;
        case EM_SETWORDBREAKPROC: ::print('[', EM_SETWORDBREAKPROC, "]: Rich Edit -> Set Word Break Procedure"); break;
        case EM_SETWORDBREAKPROCEX /* -> TB_INSERTMARKHITTEST */: {
            ::println('[', EM_SETWORDBREAKPROCEX, "]: {");
                ::println(printt, "Rich Edit -> Set Word Break Procedure (Extended)");
                ::println(printt, "Toolbar -> Insert Mark Hit Test");
            ::print('}');
        } break;
        /* case EM_SETWORDWRAPMODE: break; */
        case EM_SETZOOM /* -> MCIWNDM_GETDEVICEW */: {
            ::println('[', EM_SETZOOM, "]: {");
                ::println(printt, "Multimedia (MCI) Window -> Get Device");
                ::println(printt, "Rich Edit -> Set Zoom");
            ::print('}');
        } break;
        case EM_SHOWSCROLLBAR: ::print('[', EM_SHOWSCROLLBAR, "]: Rich Edit -> Show Scrollbar"); break;
        case EM_STOPGROUPTYPING /* -> TB_SETINSERTMARKCOLOR */: {
            ::println('[', EM_STOPGROUPTYPING, "]: {");
                ::println(printt, "Rich Edit -> Stop Group Typing");
                ::println(printt, "Toolbar -> Set Insert Mark Color");
            ::print('}');
        } break;
        case EM_STREAMIN /* -> TB_SETANCHORHIGHLIGHT */: {
            ::println('[', EM_STREAMIN, "]: {");
                ::println(printt, "Rich Edit -> Stream In");
                ::println(printt, "Toolbar -> Set Anchor Highlight");
            ::print('}');
        } break;
        case EM_STREAMOUT /* -> TB_GETANCHORHIGHLIGHT */: {
            ::println('[', EM_STREAMOUT, "]: {");
                ::println(printt, "Rich Edit -> Stream Out");
                ::println(printt, "Toolbar -> Get Anchor Highlight");
            ::print('}');
        } break;
        case EM_UNDO: ::print('[', EM_UNDO, "]: Rich Edit -> Undo"); break;

        // [File Manager]
        case FM_GETDRIVEINFOA: ::print('[', FM_GETDRIVEINFOA, "]: File Manager -> Get Drive Information"); break;
        case FM_GETDRIVEINFOW: ::print('[', FM_GETDRIVEINFOW, "]: File Manager -> Get Drive Information"); break;
        case FM_GETFILESELA: ::print('[', FM_GETFILESELA, "]: File Manager -> Get File Selection"); break;
        case FM_GETFILESELLFNA: ::print('[', FM_GETFILESELLFNA, "]: File Manager -> Get File Selection Function"); break;
        case FM_GETFILESELLFNW: ::print('[', FM_GETFILESELLFNW, "]: File Manager -> Get File Selection Function"); break;
        case FM_GETFILESELW: ::print('[', FM_GETFILESELW, "]: File Manager -> Get File Selection"); break;
        case FM_GETFOCUS: ::print('[', FM_GETFOCUS, "]: File Manager -> Get Focus"); break;
        case FM_GETSELCOUNT: ::print('[', FM_GETSELCOUNT, "]: File Manager -> Selection Count"); break;
        case FM_GETSELCOUNTLFN: ::print('[', FM_GETSELCOUNTLFN, "]: File Manager -> Selection Count ..."); break;
        case FM_REFRESH_WINDOWS: ::print('[', FM_REFRESH_WINDOWS, "]: File Manager -> Refresh Windows"); break;
        case FM_RELOAD_EXTENSIONS: ::print('[', FM_RELOAD_EXTENSIONS, "]: File Manager -> Reload Extensions"); break;

        // [Hot Key]
        /* case HKM_GETHOTKEY: break; */
        /* case HKM_SETHOTKEY: break; */
        /* case HKM_SETRULES: break; */

        // [Ink Edit]
        /* case IE_DOCOMMAND: break; */
        case IE_GETAPPDATA: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Application Data"); break;
        case IE_GETBKGND: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Background"); break;
        /* case IE_GETCOMMAND: break; */
        /* case IE_GETCOUNT: break; */
        case IE_GETDRAWOPTS: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Draw Options"); break;
        case IE_GETERASERTIP: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Eraser Tip"); break;
        case IE_GETFORMAT: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Format"); break;
        /* case IE_GETGESTURE: break; */
        case IE_GETGRIDORIGIN: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Grid Origin"); break;
        case IE_GETGRIDPEN: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Grid Pen"); break;
        case IE_GETGRIDSIZE: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Grid Size"); break;
        case IE_GETINK /* -> IE_MSGFIRST || MCIWNDM_PALETTEKICK */: {
            ::println('[', IE_GETINK, "]: {");
                ::println(printt, "Ink Edit -> Get Ink [FIRST]");
                ::println(printt, "Multimedia (MCI) Window -> Palette Kick");
            ::print('}');
        } break;
        case IE_GETINKINPUT: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Ink Input"); break;
        case IE_GETINKRECT /* -> WM_CAP_SET_MCI_DEVICEW */: {
            ::println('[', IE_GETINKRECT, "]: {");
                ::println(printt, "Ink Edit -> Get Ink Rectangle");
                ::println(printt, "Windows Capture -> Set Multimedia (MCI) Device");
            ::print('}');
        } break;
        /* case IE_GETMENU: break; */
        case IE_GETMODE: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Mode"); break;
        case IE_GETNOTIFY: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Notify"); break;
        /* case IE_GETPAINTDC: break; */
        case IE_GETPDEVENT: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get PD Event"); break;
        case IE_GETPENTIP: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Pen Tip"); break;
        case IE_GETRECOG: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Recognition"); break;
        case IE_GETSECURITY: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Security"); break;
        case IE_GETSEL: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Selection"); break;
        case IE_GETSELCOUNT: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Selection Count"); break;
        case IE_GETSELITEMS: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Selection Items"); break;
        case IE_GETSTYLE: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Get Style"); break;
        /* case IE_MSGFIRST: break; */
        case IE_SETAPPDATA: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Set Application Data"); break;
        case IE_SETBKGND: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Set Background"); break;
        case IE_SETDRAWOPTS: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Set Draw Options"); break;
        case IE_SETERASERTIP: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Set Eraser Tip"); break;
        case IE_SETFORMAT: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Set Format"); break;
        case IE_SETGRIDORIGIN: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Set Grid Origin"); break;
        case IE_SETGRIDPEN: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Set Grid Pen"); break;
        case IE_SETGRIDSIZE: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Set Grid Size"); break;
        case IE_SETINK: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Set Ink"); break;
        case IE_SETINKINPUT: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Set Ink Input"); break;
        case IE_SETMODE: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Set Mode"); break;
        case IE_SETNOTIFY: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Set Notify"); break;
        case IE_SETPENTIP: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Set Pen Tip"); break;
        case IE_SETRECOG: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Set Recognition"); break;
        case IE_SETSECURITY: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Set Security"); break;
        case IE_SETSEL: ::print('[', IE_GETAPPDATA, "]: Ink Edit -> Set Selection"); break;

        // [Internet Protocol]
        /* case IPM_CLEARADDRESS: break; */
        /* case IPM_GETADDRESS: break; */
        /* case IPM_ISBLANK: break; */
        /* case IPM_SETADDRESS: break; */
        /* case IPM_SETFOCUS: break; */
        /* case IPM_SETRANGE: break; */

        // [List View]
        /* case LVM_APPROXIMATEVIEWRECT: break; */
        case LVM_ARRANGE: ::print('[', LVM_ARRANGE, "]: List View -> Arrange"); break;
        case LVM_CANCELEDITLABEL: ::print('[', LVM_CANCELEDITLABEL, "]: List View -> Cancel Edit Label"); break;
        case LVM_CREATEDRAGIMAGE: ::print('[', LVM_CREATEDRAGIMAGE, "]: List View -> Create Drag Image"); break;
        case LVM_DELETEALLITEMS: ::print('[', LVM_DELETEALLITEMS, "]: List View -> Delete All Items"); break;
        case LVM_DELETECOLUMN: ::print('[', LVM_DELETECOLUMN, "]: List View -> Delete Column"); break;
        case LVM_DELETEITEM: ::print('[', LVM_DELETEITEM, "]: List View -> Delete Item"); break;
        case LVM_EDITLABELA: ::print('[', LVM_EDITLABELA, "]: List View -> Edit Label"); break;
        case LVM_EDITLABELW: ::print('[', LVM_EDITLABELW, "]: List View -> Edit Label"); break;
        case LVM_ENABLEGROUPVIEW: ::print('[', LVM_ENABLEGROUPVIEW, "]: List View -> Enable Group View"); break;
        case LVM_ENSUREVISIBLE: ::print('[', LVM_ENSUREVISIBLE, "]: List View -> Ensure Visible"); break;
        case LVM_FINDITEMA: ::print('[', LVM_FINDITEMA, "]: List View -> Find Item"); break;
        case LVM_FINDITEMW: ::print('[', LVM_FINDITEMW, "]: List View -> Find Item"); break;
        case LVM_FIRST /* -> LVM_GETBKCOLOR */: ::print('[', LVM_FIRST, "]: List View -> Get Background Color [FIRST]"); break;
        /* case LVM_GETBKCOLOR: break; */
        case LVM_GETBKIMAGEA: ::print('[', LVM_GETBKIMAGEA, "]: List View -> Get Background Image"); break;
        case LVM_GETBKIMAGEW: ::print('[', LVM_GETBKIMAGEW, "]: List View -> Get Background Image"); break;
        case LVM_GETCALLBACKMASK: ::print('[', LVM_GETCALLBACKMASK, "]: List View -> Get Call Back Mask"); break;
        case LVM_GETCOLUMNA: ::print('[', LVM_GETCOLUMNA, "]: List View -> Get Column"); break;
        case LVM_GETCOLUMNORDERARRAY: ::print('[', LVM_GETCOLUMNORDERARRAY, "]: List View -> Get Column Order Array"); break;
        case LVM_GETCOLUMNW: ::print('[', LVM_GETCOLUMNW, "]: List View -> Get Column"); break;
        case LVM_GETCOLUMNWIDTH: ::print('[', LVM_GETCOLUMNWIDTH, "]: List View -> Get Column Width"); break;
        case LVM_GETCOUNTPERPAGE: ::print('[', LVM_GETCOUNTPERPAGE, "]: List View -> Get Count per Page"); break;
        case LVM_GETEDITCONTROL: ::print('[', LVM_GETEDITCONTROL, "]: List View -> Get Edit Control"); break;
        case LVM_GETEXTENDEDLISTVIEWSTYLE: ::print('[', LVM_GETEXTENDEDLISTVIEWSTYLE, "]: List View -> Get Extended List View Style"); break;
        case LVM_GETGROUPINFO: ::print('[', LVM_GETGROUPINFO, "]: List View -> Get Group Information"); break;
        case LVM_GETGROUPMETRICS: ::print('[', LVM_GETGROUPMETRICS, "]: List View -> Get Group Metrics"); break;
        case LVM_GETHEADER: ::print('[', LVM_GETHEADER, "]: List View -> Get Header"); break;
        case LVM_GETHOTCURSOR: ::print('[', LVM_GETHOTCURSOR, "]: List View -> Get Hot Cursor"); break;
        case LVM_GETHOTITEM: ::print('[', LVM_GETHOTITEM, "]: List View -> Get Hover Time"); break;
        case LVM_GETHOVERTIME: ::print('[', LVM_GETHOVERTIME, "]: List View -> Get Image List"); break;
        case LVM_GETIMAGELIST: ::print('[', LVM_GETIMAGELIST, "]: List View -> Get Image List"); break;
        case LVM_GETINSERTMARK: ::print('[', LVM_GETINSERTMARK, "]: List View -> Get Insert Mark"); break;
        case LVM_GETINSERTMARKCOLOR: ::print('[', LVM_GETINSERTMARKCOLOR, "]: List View -> Get Insert Mark Color"); break;
        case LVM_GETINSERTMARKRECT: ::print('[', LVM_GETINSERTMARKRECT, "]: List View -> Get Insert Mark Rectangle"); break;
        case LVM_GETISEARCHSTRINGA: ::print('[', LVM_GETISEARCHSTRINGA, "]: List View -> Get Incremental Search String"); break;
        case LVM_GETISEARCHSTRINGW: ::print('[', LVM_GETISEARCHSTRINGW, "]: List View -> Get Incremental Search String"); break;
        case LVM_GETITEMA: ::print('[', LVM_GETITEMA, "]: List View -> Get Item"); break;
        case LVM_GETITEMCOUNT: ::print('[', LVM_GETITEMCOUNT, "]: List View -> Get Item Count"); break;
        case LVM_GETITEMPOSITION: ::print('[', LVM_GETITEMPOSITION, "]: List View -> Get Item Position"); break;
        case LVM_GETITEMRECT: ::print('[', LVM_GETITEMRECT, "]: List View -> Get Item Rectangle"); break;
        case LVM_GETITEMSPACING: ::print('[', LVM_GETITEMSPACING, "]: List View -> Get Item Spacing"); break;
        case LVM_GETITEMSTATE: ::print('[', LVM_GETITEMSTATE, "]: List View -> Get Item State"); break;
        case LVM_GETITEMTEXTA: ::print('[', LVM_GETITEMTEXTA, "]: List View -> Get Item Text"); break;
        case LVM_GETITEMTEXTW: ::print('[', LVM_GETITEMTEXTW, "]: List View -> Get Item Text"); break;
        case LVM_GETITEMW: ::print('[', LVM_GETITEMW, "]: List View -> Get Item"); break;
        case LVM_GETNEXTITEM: ::print('[', LVM_GETNEXTITEM, "]: List View -> Get Next Item"); break;
        case LVM_GETNUMBEROFWORKAREAS: ::print('[', LVM_GETNUMBEROFWORKAREAS, "]: List View -> Get Number of Work Areas"); break;
        case LVM_GETORIGIN: ::print('[', LVM_GETORIGIN, "]: List View -> Get Origin"); break;
        case LVM_GETOUTLINECOLOR: ::print('[', LVM_GETOUTLINECOLOR, "]: List View -> Get Outline Color"); break;
        case LVM_GETSELECTEDCOLUMN: ::print('[', LVM_GETSELECTEDCOLUMN, "]: List View -> Get Selected Column"); break;
        case LVM_GETSELECTEDCOUNT: ::print('[', LVM_GETSELECTEDCOUNT, "]: List View -> Get Selected Count"); break;
        case LVM_GETSELECTIONMARK: ::print('[', LVM_GETSELECTIONMARK, "]: List View -> Get Selection Mark"); break;
        case LVM_GETSTRINGWIDTHA: ::print('[', LVM_GETSTRINGWIDTHA, "]: List View -> Get String Width"); break;
        case LVM_GETSTRINGWIDTHW: ::print('[', LVM_GETSTRINGWIDTHW, "]: List View -> Get String Width"); break;
        case LVM_GETSUBITEMRECT: ::print('[', LVM_GETSUBITEMRECT, "]: List View -> Get Sub-Item Rectangle"); break;
        case LVM_GETTEXTBKCOLOR: ::print('[', LVM_GETTEXTBKCOLOR, "]: List View -> Get Text Background Color"); break;
        case LVM_GETTEXTCOLOR: ::print('[', LVM_GETTEXTCOLOR, "]: List View -> Get Text Color"); break;
        case LVM_GETTILEINFO: ::print('[', LVM_GETTILEINFO, "]: List View -> Get Tile Information"); break;
        case LVM_GETTILEVIEWINFO: ::print('[', LVM_GETTILEVIEWINFO, "]: List View -> Get Tile View Information"); break;
        case LVM_GETTOOLTIPS: ::print('[', LVM_GETTOOLTIPS, "]: List View -> Get Tooltips"); break;
        case LVM_GETTOPINDEX: ::print('[', LVM_GETTOPINDEX, "]: List View -> Get Top Index"); break;
        case LVM_GETUNICODEFORMAT: ::print('[', LVM_GETUNICODEFORMAT, "]: List View -> Get Unicode Format"); break;
        case LVM_GETVIEW: ::print('[', LVM_GETVIEW, "]: List View -> Get View"); break;
        case LVM_GETVIEWRECT: ::print('[', LVM_GETVIEWRECT, "]: List View -> Get View Rect"); break;
        case LVM_GETWORKAREAS: ::print('[', LVM_GETWORKAREAS, "]: List View -> Get Work Areas"); break;
        case LVM_HASGROUP: ::print('[', LVM_HASGROUP, "]: List View -> Has Group"); break;
        case LVM_HITTEST: ::print('[', LVM_HITTEST, "]: List View -> Hit Test"); break;
        case LVM_INSERTCOLUMNA: ::print('[', LVM_INSERTCOLUMNA, "]: List View -> Insert Column"); break;
        case LVM_INSERTCOLUMNW: ::print('[', LVM_INSERTCOLUMNW, "]: List View -> Insert Column"); break;
        case LVM_INSERTGROUP: ::print('[', LVM_INSERTGROUP, "]: List View -> Insert Group"); break;
        case LVM_INSERTGROUPSORTED: ::print('[', LVM_INSERTGROUPSORTED, "]: List View -> Insert Group Sorted"); break;
        case LVM_INSERTITEMA: ::print('[', LVM_INSERTITEMA, "]: List View -> Insert Item"); break;
        case LVM_INSERTITEMW: ::print('[', LVM_INSERTITEMW, "]: List View -> Insert Item"); break;
        case LVM_INSERTMARKHITTEST: ::print('[', LVM_INSERTMARKHITTEST, "]: List View -> Insert Mark Hit Test"); break;
        case LVM_ISGROUPVIEWENABLED: ::print('[', LVM_ISGROUPVIEWENABLED, "]: List View -> Is Group View Enabled"); break;
        case LVM_ISITEMVISIBLE: ::print('[', LVM_ISITEMVISIBLE, "]: List View -> Is Item Visible"); break;
        case LVM_MAPIDTOINDEX: ::print('[', LVM_MAPIDTOINDEX, "]: List View -> Map Identity to Index"); break;
        case LVM_MAPINDEXTOID: ::print('[', LVM_MAPINDEXTOID, "]: List View -> Map Index to Identity"); break;
        case LVM_MOVEGROUP: ::print('[', LVM_MOVEGROUP, "]: List View -> Move Group"); break;
        case LVM_MOVEITEMTOGROUP: ::print('[', LVM_MOVEITEMTOGROUP, "]: List View -> Move Item to Group"); break;
        case LVM_REDRAWITEMS: ::print('[', LVM_REDRAWITEMS, "]: List View -> Redraw Items"); break;
        case LVM_REMOVEALLGROUPS: ::print('[', LVM_REMOVEALLGROUPS, "]: List View -> Remove all Groups"); break;
        case LVM_REMOVEGROUP: ::print('[', LVM_REMOVEGROUP, "]: List View -> Remove Group"); break;
        case LVM_SCROLL: ::print('[', LVM_SCROLL, "]: List View -> Scroll"); break;
        case LVM_SETBKCOLOR: ::print('[', LVM_SETBKCOLOR, "]: List View -> Set Background Color"); break;
        case LVM_SETBKIMAGEA: ::print('[', LVM_SETBKIMAGEA, "]: List View -> Set Background Image"); break;
        case LVM_SETCALLBACKMASK: ::print('[', LVM_SETCALLBACKMASK, "]: List View -> Set Callback Mask"); break;
        case LVM_SETCOLUMNA: ::print('[', LVM_SETCOLUMNA, "]: List View -> Set Column"); break;
        case LVM_SETCOLUMNORDERARRAY: ::print('[', LVM_SETCOLUMNORDERARRAY, "]: List View -> Set Column Order Array"); break;
        case LVM_SETCOLUMNW: ::print('[', LVM_SETCOLUMNW, "]: List View -> Set Column"); break;
        case LVM_SETCOLUMNWIDTH: ::print('[', LVM_SETCOLUMNWIDTH, "]: List View -> Set Column Width"); break;
        case LVM_SETEXTENDEDLISTVIEWSTYLE: ::print('[', LVM_SETEXTENDEDLISTVIEWSTYLE, "]: List View -> Set Extended List View Style"); break;
        case LVM_SETGROUPINFO: ::print('[', LVM_SETGROUPINFO, "]: List View -> Set Group Information"); break;
        case LVM_SETGROUPMETRICS: ::print('[', LVM_SETGROUPMETRICS, "]: List View -> Set Group Metrics"); break;
        case LVM_SETHOTCURSOR /* -> LVM_SETHOTITEM */: {
            ::println('[', LVM_SETHOTCURSOR, "]: {");
                ::println(printt, "List View -> Set Hot Cursor");
                ::println(printt, "List View -> Set Hot Item");
            ::print('}');
        } break;
        /* case LVM_SETHOTITEM: break; */
        case LVM_SETHOVERTIME: ::print('[', LVM_SETHOVERTIME, "]: List View -> Set Hover Time"); break;
        case LVM_SETICONSPACING: ::print('[', LVM_SETICONSPACING, "]: List View -> Set Icon Spacing"); break;
        case LVM_SETIMAGELIST: ::print('[', LVM_SETIMAGELIST, "]: List View -> Set Image List"); break;
        case LVM_SETINFOTIP: ::print('[', LVM_SETINFOTIP, "]: List View -> Set Information Tip"); break;
        case LVM_SETINSERTMARK: ::print('[', LVM_SETINSERTMARK, "]: List View -> Set Insert Mark"); break;
        case LVM_SETINSERTMARKCOLOR: ::print('[', LVM_SETINSERTMARKCOLOR, "]: List View -> Set Insert Mark Color"); break;
        case LVM_SETITEMA: ::print('[', LVM_SETITEMA, "]: List View -> Set Item"); break;
        case LVM_SETITEMCOUNT: ::print('[', LVM_SETITEMCOUNT, "]: List View -> Set Item Count"); break;
        case LVM_SETITEMPOSITION: ::print('[', LVM_SETITEMPOSITION, "]: List View -> Set Item Position"); break;
        case LVM_SETITEMPOSITION32: ::print('[', LVM_SETITEMPOSITION32, "]: List View -> Set Item Position (32-Bit)"); break;
        case LVM_SETITEMSTATE: ::print('[', LVM_SETITEMSTATE, "]: List View -> Set Item State"); break;
        case LVM_SETITEMTEXTA: ::print('[', LVM_SETITEMTEXTA, "]: List View -> Set Item Text"); break;
        case LVM_SETITEMTEXTW: ::print('[', LVM_SETITEMTEXTW, "]: List View -> Set Item Text"); break;
        case LVM_SETITEMW: ::print('[', LVM_SETITEMW, "]: List View -> Set Item"); break;
        case LVM_SETOUTLINECOLOR: ::print('[', LVM_SETOUTLINECOLOR, "]: List View -> Set Outline Color"); break;
        case LVM_SETSELECTEDCOLUMN: ::print('[', LVM_SETSELECTEDCOLUMN, "]: List View -> Set Selected Column"); break;
        case LVM_SETSELECTIONMARK: ::print('[', LVM_SETSELECTIONMARK, "]: List View -> Set Selection Mark"); break;
        case LVM_SETTEXTBKCOLOR: ::print('[', LVM_SETTEXTBKCOLOR, "]: List View -> Set Text Background Color"); break;
        case LVM_SETTEXTCOLOR: ::print('[', LVM_SETTEXTCOLOR, "]: List View -> Set Text Color"); break;
        case LVM_SETTILEINFO: ::print('[', LVM_SETTILEINFO, "]: List View -> Set Tile Information"); break;
        case LVM_SETTILEVIEWINFO: ::print('[', LVM_SETTILEVIEWINFO, "]: List View -> Set Tile View Information"); break;
        case LVM_SETTILEWIDTH: ::print('[', LVM_SETTILEWIDTH, "]: List View -> Set Tile Width"); break;
        case LVM_SETTOOLTIPS: ::print('[', LVM_SETTOOLTIPS, "]: List View -> Set Tooltips"); break;
        case LVM_SETUNICODEFORMAT: ::print('[', LVM_SETUNICODEFORMAT, "]: List View -> Set Unicode Format"); break;
        case LVM_SETVIEW: ::print('[', LVM_SETVIEW, "]: List View -> Set View"); break;
        case LVM_SETWORKAREAS: ::print('[', LVM_SETWORKAREAS, "]: List View -> Set WorkaAreas"); break;
        case LVM_SORTGROUPS: ::print('[', LVM_SORTGROUPS, "]: List View -> Sort Groups"); break;
        case LVM_SORTITEMS: ::print('[', LVM_SORTITEMS, "]: List View -> Sort Items"); break;
        case LVM_SUBITEMHITTEST: ::print('[', LVM_SUBITEMHITTEST, "]: List View -> Sub-Item Hit Test"); break;
        case LVM_UPDATE: ::print('[', LVM_UPDATE, "]: List View -> Update"); break;

        // [Multimedia MCI Window]
        case MCIWNDM_CAN_CONFIG: ::print('[', MCIWNDM_CAN_CONFIG, "]: Multimedia (MCI) Window -> Can Configure"); break;
        case MCIWNDM_CAN_EJECT: ::print('[', MCIWNDM_CAN_EJECT, "]: Multimedia (MCI) Window -> Can Eject"); break;
        case MCIWNDM_CAN_PLAY: ::print('[', MCIWNDM_CAN_PLAY, "]: Multimedia (MCI) Window -> Can Play"); break;
        case MCIWNDM_CAN_RECORD: ::print('[', MCIWNDM_CAN_RECORD, "]: Multimedia (MCI) Window -> Can Record"); break;
        case MCIWNDM_CAN_SAVE: ::print('[', MCIWNDM_CAN_SAVE, "]: Multimedia (MCI) Window -> Can Save"); break;
        case MCIWNDM_CAN_WINDOW: ::print('[', MCIWNDM_CAN_WINDOW, "]: Multimedia (MCI) Window -> Can Window"); break;
        /* case MCIWNDM_GETDEVICEA: break; */
        /* case MCIWNDM_GETDEVICEW: break; */
        case MCIWNDM_GETERRORA /* -> PSM_SETHEADERSUBTITLEW */: {
            ::println('[', MCIWNDM_GETERRORA, "]: {");
                ::println(printt, "Multimedia (MCI) Window -> Get Error");
                ::println(printt, "Prop Sheet -> Set Header Subtitle");
            ::print('}');
        } break;
        case MCIWNDM_GETERRORW: ::print('[', MCIWNDM_GETERRORW, "]: Multimedia (MCI) Window -> Get Error"); break;
        /* case MCIWNDM_GETFILENAMEA: break; */
        /* case MCIWNDM_GETFILENAMEW: break; */
        /* case MCIWNDM_GETINACTIVETIMER: break; */
        /* case MCIWNDM_GETPALETTE: break; */
        /* case MCIWNDM_GETTIMEFORMATA: break; */
        /* case MCIWNDM_GETTIMEFORMATW: break; */
        case MCIWNDM_GETZOOM /* -> PSM_UNCHANGED || UDM_SETBASE */: {
            ::println('[', MCIWNDM_GETERRORA, "]: {");
                ::println(printt, "Multimedia (MCI) Window -> Get Zoom");
                ::println(printt, "Prop Sheet -> Unchanged");
                ::println(printt, "Up-Down Control -> Set Base");
            ::print('}');
        } break;
        case MCIWNDM_GET_DEST: ::print('[', MCIWNDM_GET_DEST, "]: Multimedia (MCI) Window -> Get Destination"); break;
        case MCIWNDM_GET_SOURCE: ::print('[', MCIWNDM_GET_SOURCE, "]: Multimedia (MCI) Window -> Get Source"); break;
        /* case MCIWNDM_NOTIFYERROR: break; */
        /* case MCIWNDM_NOTIFYMEDIA: break; */
        /* case MCIWNDM_NOTIFYMODE: break; */
        /* case MCIWNDM_PALETTEKICK: break; */
        /* case MCIWNDM_PLAYTO: break; */
        case MCIWNDM_PUT_DEST: ::print('[', MCIWNDM_PUT_DEST, "]: Multimedia (MCI) Window -> Put Destination"); break;
        case MCIWNDM_PUT_SOURCE: ::print('[', MCIWNDM_PUT_SOURCE, "]: Multimedia (MCI) Window -> Put Source"); break;
        case MCIWNDM_REALIZE /* -> PSM_GETCURRENTPAGEHWND */: {
            ::println('[', MCIWNDM_REALIZE, "]: {");
                ::println(printt, "Multimedia (MCI) Window -> Realize");
                ::println(printt, "Prop Sheet -> Get Current Page Window Handle");
            ::print('}');
        } break;
        case MCIWNDM_SETINACTIVETIMER /* -> PSM_PAGETOINDEX */: {
            ::println('[', MCIWNDM_SETINACTIVETIMER, "]: {");
                ::println(printt, "Multimedia (MCI) Window -> Set Inactive Timer");
                ::println(printt, "Prop Sheet -> Page to Index");
            ::print('}');
        } break;
        /* case MCIWNDM_SETPALETTE: break; */
        case MCIWNDM_SETTIMEFORMATA /* -> PSM_INSERTPAGE */: {
            ::println('[', MCIWNDM_SETTIMEFORMATA, "]: {");
                ::println(printt, "Multimedia (MCI) Window -> Set Time Format");
                ::println(printt, "Prop Sheet -> Insert Page");
            ::print('}');
        } break;
        case MCIWNDM_SETTIMEFORMATW: ::print('[', MCIWNDM_SETTIMEFORMATW, "]: Multimedia (MCI) Window -> Set Time Format"); break;
        /* case MCIWNDM_VALIDATEMEDIA: break; */

        // [...]
        case MSG_FTS_JUMP_QWORD /* -> RB_SHOWBAND || TB_GETTOOLTIPS */: {
            ::println('[', MSG_FTS_JUMP_QWORD, "]: {");
                ::println(printt, "... Jump ...");
                ::println(printt, "Rebar -> Show Band");
                ::println(printt, "Toolbar -> Get Tooltips");
            ::print('}');
        } break;
        case MSG_FTS_JUMP_VA /* -> TBM_GETBUDDY || TB_AUTOSIZE || TTM_SETTITLEW */: {
            ::println('[', MSG_FTS_JUMP_VA, "]: {");
                ::println(printt, "... Jump ...");
                ::println(printt, "Toolbar -> Auto Size");
                ::println(printt, "Tooltip -> Set Title");
                ::println(printt, "Trackbar -> Get Buddy");
            ::print('}');
        } break;
        case MSG_FTS_WHERE_IS_IT /* -> RB_SETPALETTE || TB_SETPARENT */: {
            ::println('[', MSG_FTS_WHERE_IS_IT, "]: {");
                ::println(printt, "... Where is It");
                ::println(printt, "Rebar -> Set Palette");
                ::println(printt, "Toolbar -> Set Parent");
            ::print('}');
        } break;
        case MSG_GET_DEFFONT /* -> TB_GETBUTTONTEXTA */: {
            ::println('[', MSG_GET_DEFFONT, "]: {");
                ::println(printt, "Get Default Font");
                ::println(printt, "Toolbar -> Get Button Text");
            ::print('}');
        } break;
        case MSG_REINDEX_REQUEST /* -> TB_SETTOOLTIPS */: {
            ::println('[', MSG_REINDEX_REQUEST, "]: {");
                ::println(printt, "Re-Index Request");
                ::println(printt, "Toolbar -> Set Tooltips");
            ::print('}');
        } break;

        // [Object Linking & Embedding]
        /* case NIN_SELECT: break; */
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

        // [Prop Sheet]
        /* case PBM_DELTAPOS: break; */
        /* case PBM_GETPOS: break; */
        /* case PBM_GETRANGE: break; */
        /* case PBM_SETBARCOLOR: break; */
        /* case PBM_SETPOS: break; */
        /* case PBM_SETRANGE: break; */
        /* case PBM_SETRANGE32: break; */
        /* case PBM_SETSTEP: break; */
        /* case PBM_STEPIT: break; */
        /* case PSM_ADDPAGE: break; */
        case PSM_APPLY /* -> UDM_GETBASE */: {
            ::println('[', PSM_APPLY, "]: {");
                ::println(printt, "Prop Sheet -> Apply");
                ::println(printt, "Up-Down Control -> Get Base");
            ::print('}');
        } break;
        /* case PSM_CANCELTOCLOSE: break; */
        /* case PSM_CHANGED: break; */
        /* case PSM_GETCURRENTPAGEHWND: break; */
        /* case PSM_GETRESULT: break; */
        case PSM_GETTABCONTROL: ::print('[', PSM_GETTABCONTROL, "]: Prop Sheet -> Get Tab Control"); break;
        case PSM_HWNDTOINDEX: ::print('[', PSM_HWNDTOINDEX, "]: Prop Sheet -> Window Handle to Index"); break;
        /* case PSM_IDTOINDEX: break; */
        case PSM_INDEXTOHWND: ::print('[', PSM_INDEXTOHWND, "]: Prop Sheet -> Index To Window Handle"); break;
        /* case PSM_INDEXTOID: break; */
        case PSM_INDEXTOPAGE: ::print('[', PSM_INDEXTOPAGE, "]: Prop Sheet -> Index To Page"); break;
        /* case PSM_INSERTPAGE: break; */
        case PSM_ISDIALOGMESSAGE: ::print('[', PSM_ISDIALOGMESSAGE, "]: Prop Sheet -> Is Dialog Message"); break;
        /* case PSM_PAGETOINDEX: break; */
        case PSM_PRESSBUTTON /* -> UDM_SETPOS32 || WM_CAP_DRIVER_GET_VERSIONW */: {
            ::println('[', PSM_PRESSBUTTON, "]: {");
                ::println(printt, "Prop Sheet -> Press Buttons");
                ::println(printt, "Up-Down Control -> Set Position");
                ::println(printt, "Windows Capture -> Driver Get Version");
            ::print('}');
        } break;
        /* case PSM_QUERYSIBLINGS: break; */
        /* case PSM_REBOOTSYSTEM: break; */
        /* case PSM_RECALCPAGESIZES: break; */
        /* case PSM_REMOVEPAGE: break; */
        /* case PSM_RESTARTWINDOWS: break; */
        /* case PSM_SETCURSEL: break; */
        case PSM_SETCURSELID /* -> UDM_GETPOS32 */: {
            ::println('[', PSM_SETCURSELID, "]: {");
                ::println(printt, "Prop Sheet -> Set Current Selection Identity");
                ::println(printt, "Up-Down Control -> Get Position");
            ::print('}');
        } break;
        case PSM_SETFINISHTEXTA: ::print('[', PSM_SETFINISHTEXTA, "]: Prop Sheet -> Set Finish Text"); break;
        /* case PSM_SETFINISHTEXTW: break; */
        /* case PSM_SETHEADERSUBTITLEA: break; */
        /* case PSM_SETHEADERSUBTITLEW: break; */
        /* case PSM_SETHEADERTITLEA: break; */
        /* case PSM_SETHEADERTITLEW: break; */
        case PSM_SETTITLEA /* -> UDM_SETRANGE32 */: {
            ::println('[', PSM_SETTITLEA, "]: {");
                ::println(printt, "Prop Sheet -> Set Title");
                ::println(printt, "Up-Down Control -> Set Range");
            ::print('}');
        } break;
        /* case PSM_SETTITLEW: break; */
        case PSM_SETWIZBUTTONS /* -> UDM_GETRANGE32 || WM_CAP_DRIVER_GET_NAMEW */: {
            ::println('[', PSM_SETWIZBUTTONS, "]: {");
                ::println(printt, "Prop Sheet -> Set Wizard Buttons");
                ::println(printt, "Up-Down Control -> Get Range");
                ::println(printt, "Windows Capture -> Driver Get Name");
            ::print('}');
        } break;
        /* case PSM_UNCHANGED: break; */

        // [Rebar]
        case RB_BEGINDRAG /* -> TBM_GETLINESIZE */: {
            ::println('[', RB_BEGINDRAG, "]: {");
                ::println(printt, "Rebar -> Begin Drag");
                ::println(printt, "Trackbar -> Get Line Size");
            ::print('}');
        } break;
        /* case RB_DELETEBAND: break; */
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
        /* case RB_GETBANDCOUNT: break; */
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
        /* case RB_GETBARINFO: break; */
        case RB_GETBKCOLOR /* -> SB_GETTIPTEXTW || TBM_SETTICFREQ || TB_ADDBUTTONSA || TTM_SETTIPTEXTCOLOR */: {
            ::println('[', RB_GETBKCOLOR, "]: {");
                ::println(printt, "Rebar -> Get Background Color");
                ::println(printt, "Status Bar -> Get Tip Text");
                ::println(printt, "Toolbar -> Add Buttons");
                ::println(printt, "Tooltip -> Set Tip Text Color");
                ::println(printt, "Trackbar -> Set Tick Frequency");
            ::print('}');
        } break;
        case RB_GETPALETTE: ::print('[', RB_GETPALETTE, "]: Rebar -> Get Palette"); break;
        /* case RB_GETRECT: break; */
        /* case RB_GETROWCOUNT: break; */
        case RB_GETROWHEIGHT /* -> SB_ISSIMPLE || TBM_GETPTICS || TB_ISBUTTONHIGHLIGHTED || TTM_ENUMTOOLSA */: {
            ::println('[', RB_GETROWHEIGHT, "]: {");
                ::println(printt, "Rebar -> Get Row Height");
                ::println(printt, "Status Bar -> Is Simple");
                ::println(printt, "Toolbar -> Is Button Highlighted");
                ::println(printt, "Tooltip -> Enumerate Tools");
                ::println(printt, "Trackbar -> Get Position (of) Ticks");
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
                ::println(printt, "Toolbar -> Set State");
                ::println(printt, "Tooltip -> Track Activate");
                ::println(printt, "Trackbar -> Get Selection Start");
            ::print('}');
        } break;
        /* case RB_HITTEST: break; */
        case RB_IDTOINDEX /* -> SB_SETTIPTEXTA || TBM_GETNUMTICS || TTM_WINDOWFROMPOINT */: {
            ::println('[', RB_IDTOINDEX, "]: {");
                ::println(printt, "Rebar -> Identity to Index");
                ::println(printt, "Status Bar -> Set Tip Text");
                ::println(printt, "Tooltip -> Window From Point");
                ::println(printt, "Trackbar -> Get Number (of) Ticks");
            ::print('}');
        } break;
        /* case RB_INSERTBANDA: break; */
        /* case RB_INSERTBANDW: break; */
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
        case RB_MOVEBAND /* -> TB_SETROWS */: {
            ::println('[', RB_MOVEBAND, "]: {");
                ::println(printt, "Rebar -> Move Band");
                ::println(printt, "Toolbar -> Set Rows");
            ::print('}');
        } break;
        case RB_PUSHCHEVRON /* -> TB_CHANGEBITMAP */: {
            ::println('[', RB_PUSHCHEVRON, "]: {");
                ::println(printt, "Rebar -> Push Chevron");
                ::println(printt, "Toolbar -> Change Bitmap");
            ::print('}');
        } break;
        /* case RB_SETBANDINFOA: break; */
        /* case RB_SETBANDINFOW: break; */
        /* case RB_SETBARINFO: break; */
        case RB_SETBKCOLOR /* -> TBM_CLEARSEL || TB_ADDBITMAP || TTM_SETTIPBKCOLOR */: {
            ::println('[', RB_SETBKCOLOR, "]: {");
                ::println(printt, "Rebar -> Set Background Color");
                ::println(printt, "Toolbar -> Add Bitmap");
                ::println(printt, "Tooltip -> Set Tip Background Color");
                ::println(printt, "Trackbar -> Clear Selection");
            ::print('}');
        } break;
        /* case RB_SETPALETTE: break; */
        /* case RB_SETPARENT: break; */
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
        /* case RB_SHOWBAND: break; */
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
        /* case SBM_GETSCROLLBARINFO: break; */
        case SBM_GETSCROLLINFO: ::print('[', SBM_GETSCROLLINFO, "]: Scrollbar -> Get Scroll Information"); break;
        case SBM_SETPOS: ::print('[', SBM_SETPOS, "]: Scrollbar -> Set Position"); break;
        case SBM_SETRANGE: ::print('[', SBM_SETRANGE, "]: Scrollbar -> Set Range"); break;
        case SBM_SETRANGEREDRAW: ::print('[', SBM_SETRANGEREDRAW, "]: Scrollbar -> Set Range Redraw"); break;
        case SBM_SETSCROLLINFO: ::print('[', SBM_SETSCROLLINFO, "]: Scrollbar -> Set Scroll Information"); break;

        // [Status Bar]
        /* case SB_GETBORDERS: break; */
        /* case SB_GETICON: break; */
        /* case SB_GETPARTS: break; */
        /* case SB_GETRECT: break; */
        /* case SB_GETTEXTA: break; */
        /* case SB_GETTEXTLENGTHA: break; */
        /* case SB_GETTEXTLENGTHW: break; */
        /* case SB_GETTEXTW: break; */
        /* case SB_GETTIPTEXTA: break; */
        /* case SB_GETTIPTEXTW: break; */
        /* case SB_ISSIMPLE: break; */
        case SB_SETICON /* -> TBM_GETTICPOS || TTM_GETCURRENTTOOLA */: {
            ::println('[', SB_SETICON, "]: {");
                ::println(printt, "Status Bar -> Set Icon");
                ::println(printt, "Trackbar -> Get Tick (Mark) Position");
                ::println(printt, "Tooltip -> Get Current Tool");
            ::print('}');
        } break;
        /* case SB_SETMINHEIGHT: break; */
        /* case SB_SETPARTS: break; */
        /* case SB_SETTEXTA: break; */
        /* case SB_SETTEXTW: break; */
        /* case SB_SETTIPTEXTA: break; */
        /* case SB_SETTIPTEXTW: break; */
        /* case SB_SIMPLE: break; */

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
        /* case TBM_CLEARSEL: break; */
        /* case TBM_CLEARTICS: break; */
        /* case TBM_GETBUDDY: break; */
        /* case TBM_GETCHANNELRECT: break; */
        /* case TBM_GETLINESIZE: break; */
        /* case TBM_GETNUMTICS: break; */
        /* case TBM_GETPAGESIZE: break; */
        /* case TBM_GETPOS: break; */
        /* case TBM_GETPTICS: break; */
        /* case TBM_GETRANGEMAX: break; */
        /* case TBM_GETRANGEMIN: break; */
        /* case TBM_GETSELEND: break; */
        /* case TBM_GETSELSTART: break; */
        /* case TBM_GETTHUMBLENGTH: break; */
        /* case TBM_GETTHUMBRECT: break; */
        /* case TBM_GETTIC: break; */
        /* case TBM_GETTICPOS: break; */
        /* case TBM_GETTOOLTIPS: break; */
        case TBM_SETBUDDY /* -> TB_SETBITMAPSIZE || TTM_SETTITLEA */: {
            ::println('[', TBM_SETBUDDY, "]: {");
                ::println(printt, "Toolbar -> Set Bitmap Size");
                ::println(printt, "Tooltip -> Set Title");
                ::println(printt, "Trackbar -> Set Buddy (Window)");
            ::print('}');
        } break;
        /* case TBM_SETLINESIZE: break; */
        /* case TBM_SETPAGESIZE: break; */
        /* case TBM_SETPOS: break; */
        /* case TBM_SETRANGE: break; */
        /* case TBM_SETRANGEMAX: break; */
        /* case TBM_SETRANGEMIN: break; */
        /* case TBM_SETSEL: break; */
        /* case TBM_SETSELEND: break; */
        /* case TBM_SETSELSTART: break; */
        /* case TBM_SETTHUMBLENGTH: break; */
        /* case TBM_SETTIC: break; */
        /* case TBM_SETTICFREQ: break; */
        /* case TBM_SETTIPSIDE: break; */
        /* case TBM_SETTOOLTIPS: break; */

        // [Toolbar]
        /* case TB_ADDBITMAP: break; */
        /* case TB_ADDBUTTONSA: break; */
        /* case TB_ADDBUTTONSW: break; */
        /* case TB_ADDSTRINGA: break; */
        /* case TB_ADDSTRINGW: break; */
        /* case TB_AUTOSIZE: break; */
        /* case TB_BUTTONCOUNT: break; */
        /* case TB_BUTTONSTRUCTSIZE: break; */
        /* case TB_CHANGEBITMAP: break; */
        /* case TB_CHECKBUTTON: break; */
        /* case TB_COMMANDTOINDEX: break; */
        /* case TB_CUSTOMIZE: break; */
        /* case TB_DELETEBUTTON: break; */
        /* case TB_ENABLEBUTTON: break; */
        /* case TB_GETANCHORHIGHLIGHT: break; */
        case TB_GETBITMAP: ::print('[', TB_GETBITMAP, "]: Toolbar -> Get Bitmap"); break;
        case TB_GETBITMAPFLAGS: ::print('[', TB_GETBITMAPFLAGS, "]: Toolbar -> Get Bitmap Flags"); break;
        /* case TB_GETBUTTON: break; */
        /* case TB_GETBUTTONINFOA: break; */
        /* case TB_GETBUTTONINFOW: break; */
        /* case TB_GETBUTTONSIZE: break; */
        /* case TB_GETBUTTONTEXTA: break; */
        /* case TB_GETBUTTONTEXTW: break; */
        /* case TB_GETDISABLEDIMAGELIST: break; */
        /* case TB_GETEXTENDEDSTYLE: break; */
        /* case TB_GETHOTIMAGELIST: break; */
        /* case TB_GETHOTITEM: break; */
        case TB_GETIMAGELIST: ::print('[', TB_GETIMAGELIST, "]: Toolbar -> Get Image List"); break;
        /* case TB_GETINSERTMARK: break; */
        /* case TB_GETINSERTMARKCOLOR: break; */
        /* case TB_GETITEMRECT: break; */
        case TB_GETMAXSIZE: ::print('[', TB_GETMAXSIZE, "]: Toolbar -> Get Maximum Size"); break;
        /* case TB_GETOBJECT: break; */
        /* case TB_GETPADDING: break; */
        /* case TB_GETRECT: break; */
        case TB_GETROWS: ::print('[', TB_GETROWS, "]: Toolbar -> Get Rows"); break;
        /* case TB_GETSTATE: break; */
        /* case TB_GETSTRINGA: break; */
        /* case TB_GETSTRINGW: break; */
        /* case TB_GETSTYLE: break; */
        /* case TB_GETTEXTROWS: break; */
        /* case TB_GETTOOLTIPS: break; */
        /* case TB_HIDEBUTTON: break; */
        /* case TB_HITTEST: break; */
        /* case TB_INDETERMINATE: break; */
        /* case TB_INSERTBUTTONA: break; */
        /* case TB_INSERTBUTTONW: break; */
        /* case TB_INSERTMARKHITTEST: break; */
        /* case TB_ISBUTTONCHECKED: break; */
        /* case TB_ISBUTTONENABLED: break; */
        /* case TB_ISBUTTONHIDDEN: break; */
        /* case TB_ISBUTTONHIGHLIGHTED: break; */
        /* case TB_ISBUTTONINDETERMINATE: break; */
        /* case TB_ISBUTTONPRESSED: break; */
        /* case TB_LOADIMAGES: break; */
        /* case TB_MAPACCELERATORA: break; */
        /* case TB_MAPACCELERATORW: break; */
        /* case TB_MARKBUTTON: break; */
        /* case TB_MOVEBUTTON: break; */
        /* case TB_PRESSBUTTON: break; */
        case TB_REPLACEBITMAP: ::print('[', TB_REPLACEBITMAP, "]: Toolbar -> Replace Bitmap"); break;
        /* case TB_SAVERESTOREA: break; */
        /* case TB_SAVERESTOREW: break; */
        /* case TB_SETANCHORHIGHLIGHT: break; */
        /* case TB_SETBITMAPSIZE: break; */
        /* case TB_SETBUTTONINFOA: break; */
        /* case TB_SETBUTTONINFOW: break; */
        /* case TB_SETBUTTONSIZE: break; */
        /* case TB_SETBUTTONWIDTH: break; */
        case TB_SETCMDID: ::print('[', TB_SETCMDID, "]: Toolbar -> Set Command Identifier"); break;
        /* case TB_SETDISABLEDIMAGELIST: break; */
        /* case TB_SETDRAWTEXTFLAGS: break; */
        /* case TB_SETEXTENDEDSTYLE: break; */
        /* case TB_SETHOTIMAGELIST: break; */
        /* case TB_SETHOTITEM: break; */
        case TB_SETIMAGELIST: ::print('[', TB_SETIMAGELIST, "]: Toolbar -> Set Image List"); break;
        case TB_SETINDENT: ::print('[', TB_SETINDENT, "]: Toolbar -> Set Indentation"); break;
        /* case TB_SETINSERTMARK: break; */
        /* case TB_SETINSERTMARKCOLOR: break; */
        /* case TB_SETMAXTEXTROWS: break; */
        /* case TB_SETPADDING: break; */
        /* case TB_SETPARENT: break; */
        /* case TB_SETROWS: break; */
        /* case TB_SETSTATE: break; */
        /* case TB_SETSTYLE: break; */
        /* case TB_SETTOOLTIPS: break; */

        // [Tooltip]
        /* case TTM_ACTIVATE: break; */
        /* case TTM_ADDTOOLA: break; */
        /* case TTM_ADDTOOLW: break; */
        /* case TTM_ADJUSTRECT: break; */
        /* case TTM_DELTOOLA: break; */
        /* case TTM_DELTOOLW: break; */
        /* case TTM_ENUMTOOLSA: break; */
        /* case TTM_ENUMTOOLSW: break; */
        /* case TTM_GETBUBBLESIZE: break; */
        /* case TTM_GETCURRENTTOOLA: break; */
        /* case TTM_GETCURRENTTOOLW: break; */
        /* case TTM_GETDELAYTIME: break; */
        /* case TTM_GETMARGIN: break; */
        /* case TTM_GETMAXTIPWIDTH: break; */
        /* case TTM_GETTEXTA: break; */
        /* case TTM_GETTEXTW: break; */
        /* case TTM_GETTIPBKCOLOR: break; */
        /* case TTM_GETTIPTEXTCOLOR: break; */
        /* case TTM_GETTOOLCOUNT: break; */
        /* case TTM_GETTOOLINFOA: break; */
        /* case TTM_GETTOOLINFOW: break; */
        /* case TTM_HITTESTA: break; */
        /* case TTM_HITTESTW: break; */
        /* case TTM_NEWTOOLRECTA: break; */
        /* case TTM_NEWTOOLRECTW: break; */
        /* case TTM_POP: break; */
        /* case TTM_RELAYEVENT: break; */
        /* case TTM_SETDELAYTIME: break; */
        /* case TTM_SETMARGIN: break; */
        /* case TTM_SETMAXTIPWIDTH: break; */
        /* case TTM_SETTIPBKCOLOR: break; */
        /* case TTM_SETTIPTEXTCOLOR: break; */
        /* case TTM_SETTITLEA: break; */
        /* case TTM_SETTITLEW: break; */
        /* case TTM_SETTOOLINFOA: break; */
        /* case TTM_SETTOOLINFOW: break; */
        /* case TTM_TRACKACTIVATE: break; */
        /* case TTM_TRACKPOSITION: break; */
        /* case TTM_UPDATE: break; */
        /* case TTM_UPDATETIPTEXTA: break; */
        /* case TTM_UPDATETIPTEXTW: break; */
        /* case TTM_WINDOWFROMPOINT: break; */

        // [Up-Down Control]
        /* case UDM_GETACCEL: break; */
        /* case UDM_GETBASE: break; */
        /* case UDM_GETBUDDY: break; */
        /* case UDM_GETPOS: break; */
        /* case UDM_GETPOS32: break; */
        /* case UDM_GETRANGE: break; */
        /* case UDM_GETRANGE32: break; */
        /* case UDM_SETACCEL: break; */
        /* case UDM_SETBASE: break; */
        /* case UDM_SETBUDDY: break; */
        /* case UDM_SETPOS: break; */
        /* case UDM_SETPOS32: break; */
        /* case UDM_SETRANGE: break; */
        /* case UDM_SETRANGE32: break; */

        // [User Manager]
        /* case UM_GETCURFOCUSA: break; */
        case UM_GETCURFOCUSW: ::print('[', UM_GETCURFOCUSW, "]: User Manager -> Get Current Focus"); break;
        /* case UM_GETGROUPSELA: break; */
        /* case UM_GETGROUPSELW: break; */
        case UM_GETOPTIONS: ::print('[', UM_GETOPTIONS, "]: User Manager -> Get Options"); break;
        case UM_GETOPTIONS2: ::print('[', UM_GETOPTIONS2, "]: User Manager -> Get Options (Structure)"); break;
        /* case UM_GETSELCOUNT: break; */
        /* case UM_GETUSERSELA: break; */
        /* case UM_GETUSERSELW: break; */

        // [Wizard?]
        /* case WIZ_NEXT: break; */
        /* case WIZ_PREV: break; */
        /* case WIZ_QUERYNUMPAGES: break; */

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
        case WM_CAPTURECHANGED: ::print('[', WM_CAPTURECHANGED, "]: Windows Capture -> Changed"); break;
        /* case WM_CAP_DRIVER_GET_NAMEW: break; */
        /* case WM_CAP_DRIVER_GET_VERSIONW: break; */
        /* case WM_CAP_FILE_GET_CAPTURE_FILEW: break; */
        /* case WM_CAP_FILE_SAVEASW: break; */
        /* case WM_CAP_FILE_SAVEDIBW: break; */
        /* case WM_CAP_FILE_SET_CAPTURE_FILEW: break; */
        case WM_CAP_GET_MCI_DEVICEW: ::print('[', WM_CAP_GET_MCI_DEVICEW, "]: Windows Capture -> Get Media Control Interface Device"); break;
        case WM_CAP_PAL_OPENW: ::print('[', WM_CAP_PAL_OPENW, "]: Windows Capture -> Palette Open"); break;
        case WM_CAP_PAL_SAVEW: ::print('[', WM_CAP_PAL_SAVEW, "]: Windows Capture -> Palette Save"); break;
        /* case WM_CAP_SET_CALLBACK_ERRORW: break; */
        /* case WM_CAP_SET_CALLBACK_STATUSW: break; */
        /* case WM_CAP_SET_MCI_DEVICEW: break; */
        /* case WM_CAP_UNICODE_START: break; */
        case WM_CHANGECBCHAIN: ::print('[', WM_CHANGECBCHAIN, "]: Windows -> Change Control Box Chain"); break;
        case WM_CHANGEUISTATE: ::print('[', WM_CHANGEUISTATE, "]: Windows -> Change User-Interface State"); break;
        case WM_CHAR: ::print('[', WM_CHAR, "]: Windows -> Character"); break;
        case WM_CHARTOITEM: ::print('[', WM_CHARTOITEM, "]: Windows -> Character to Item"); break;
        case WM_CHILDACTIVATE: ::print('[', WM_CHILDACTIVATE, "]: Windows -> Child Activate"); break;
        /* case WM_CHOOSEFONT_GETLOGFONT: break; */
        /* case WM_CHOOSEFONT_SETFLAGS: break; */
        /* case WM_CHOOSEFONT_SETLOGFONT: break; */
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
        /* case WM_CPL_LAUNCH: break; */
        /* case WM_CPL_LAUNCHED: break; */
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
        case WM_IMEKEYDOWN /* -> WM_IME_KEYDOWN */: ::print('[', WM_IMEKEYDOWN, "]: Windows -> IME (Input Method Editor) Key Down"); break;
        case WM_IMEKEYUP /* -> WM_IME_KEYUP */: ::print('[', WM_IMEKEYUP, "]: Windows -> IME (Input Method Editor) Key Up"); break;
        case WM_IME_CHAR: ::print('[', WM_IME_CHAR, "]: Windows -> IME (Input Method Editor) Character"); break;
        case WM_IME_COMPOSITION /* -> WM_IME_KEYLAST */: ::print('[', WM_IME_COMPOSITION, "]: Windows -> IME (Input Method Editor) Composition [(Key) LAST]"); break;
        case WM_IME_COMPOSITIONFULL: ::print('[', WM_IME_COMPOSITIONFULL, "]: Windows -> IME (Input Method Editor) Composition Full"); break;
        case WM_IME_CONTROL: ::print('[', WM_IME_CONTROL, "]: Windows -> IME (Input Method Editor) Control"); break;
        case WM_IME_ENDCOMPOSITION: ::print('[', WM_IME_ENDCOMPOSITION, "]: Windows -> IME (Input Method Editor) End Composition"); break;
        /* case WM_IME_KEYDOWN: break; */
        /* case WM_IME_KEYLAST: break; */
        /* case WM_IME_KEYUP: break; */
        case WM_IME_NOTIFY: ::print('[', WM_IME_NOTIFY, "]: Windows -> IME (Input Method Editor) Notify"); break;
        case WM_IME_REPORT: ::print('[', WM_IME_REPORT, "]: Windows -> IME (Input Method Editor) Report"); break;
        case WM_IME_REQUEST: ::print('[', WM_IME_REQUEST, "]: Windows -> IME (Input Method Editor) Request"); break;
        case WM_IME_SELECT: ::print('[', WM_IME_SELECT, "]: Windows -> IME (Input Method Editor) Select"); break;
        case WM_IME_SETCONTEXT: ::print('[', WM_IME_SETCONTEXT, "]: Windows -> IME (Input Method Editor) Set Context"); break;
        case WM_IME_STARTCOMPOSITION: ::print('[', WM_IME_STARTCOMPOSITION, "]: Windows -> IME (Input Method Editor) Start Composition"); break;
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
        /* case WM_KEYFIRST: break; */
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
        /* case WM_MOUSEMOVE: break; */
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
        /* case WM_PENCTL: break; */
        case WM_PENEVENT: ::print('[', WM_PENEVENT, "]: Windows -> Pen Event"); break;
        case WM_PENMISC: ::print('[', WM_PENMISC, "]: Windows -> Pen Miscellaneous"); break;
        /* case WM_PENMISCINFO: break; */
        case WM_PENWINFIRST: ::print('[', WM_PENWINFIRST, "]: Windows -> Pen First"); break;
        case WM_PENWINLAST: ::print('[', WM_PENWINLAST, "]: Windows -> Pen Last"); break;
        case WM_POWER: ::print('[', WM_POWER, "]: Windows -> Power"); break;
        case WM_POWERBROADCAST: ::print('[', WM_POWERBROADCAST, "]: Windows -> Power Broadcast"); break;
        case WM_PRINT: ::print('[', WM_PRINT, "]: Windows -> Print"); break;
        case WM_PRINTCLIENT: ::print('[', WM_PRINTCLIENT, "]: Windows -> Print Client"); break;
        /* case WM_PSD_ENVSTAMPRECT: break; */
        /* case WM_PSD_FULLPAGERECT: break; */
        /* case WM_PSD_GREEKTEXTRECT: break; */
        /* case WM_PSD_MARGINRECT: break; */
        /* case WM_PSD_MINMARGINRECT: break; */
        /* case WM_PSD_PAGESETUPDLG: break; */
        /* case WM_PSD_YAFULLPAGERECT: break; */
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
        /* case WM_USER: break; */
        case WM_USERCHANGED: ::print('[', WM_USERCHANGED, "]: Windows -> User Changed"); break;
        case WM_VKEYTOITEM: ::print('[', WM_VKEYTOITEM, "]: Windows -> Virtual Key to Item"); break;
        case WM_VSCROLL: ::print('[', WM_VSCROLL, "]: Windows -> Vertical Scroll"); break;
        case WM_VSCROLLCLIPBOARD: ::print('[', WM_VSCROLLCLIPBOARD, "]: Windows -> Vertical Scroll Clipboard"); break;
        case WM_WINDOWPOSCHANGED: ::print('[', WM_WINDOWPOSCHANGED, "]: Windows -> Window Position Changed"); break;
        case WM_WINDOWPOSCHANGING: ::print('[', WM_WINDOWPOSCHANGING, "]: Windows -> Window Position Changing"); break;
        case WM_WININICHANGE: ::print('[', WM_WININICHANGE, "]: Windows -> Windows INI Change"); break;
        /* case WM_WNT_CONVERTREQUESTEX: break; */
        /* case WM_XBUTTONDBLCLK: break; */
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
        } else ::abort();

        // Deletion
        ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
    } else ::abort();

    // Return
    return windowProcedureMessage.wParam;
}
