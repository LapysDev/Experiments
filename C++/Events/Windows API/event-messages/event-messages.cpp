/* ... - CITE (Lapys) -> https://github.com/LapysDev/Windows-API-Events */
/* Import > ... */
#include <cstdio>    // C Standard Input/ Output
#include <windows.h> // Windows

/* Function > Window Procedure */
LRESULT CALLBACK windowProcedure(HWND const windowHandle, UINT const message, WPARAM const parameter, LPARAM const subparameter) {
  /* ...
    --- CITE ---
      #Lapys:
      - https://docs.microsoft.com/en-us/windows/win32/winmsg/about-messages-and-message-queues#system-defined-messages
      - https://wiki.winehq.org/List_Of_Windows_Messages
  */
  switch (message) {
    /* [Animation Control] */
    case ACM_OPENA: /* --> BFFM_SETSTATUSTEXTA | CDM_FIRST | CDM_GETSPEC | EM_SETPUNCTUATION | IPM_CLEARADDRESS | WM_CAP_UNICODE_START */ {
      std::fprintf(stdout, "%c%X%4s", '[', ACM_OPENA, "]: {");
        std::fputs("Animation Control: Open"                       "\r\n", stdout);
        std::fputs("Browse for Folder: Set Status Text"            "\r\n", stdout);
        std::fputs("Common Dialog    : Get Specifications [FIRST]" "\r\n", stdout);
        std::fputs("Internet Protocol: Clear Address"              "\r\n", stdout);
        std::fputs("Rich Edit        : Set Punctuation"            "\r\n", stdout);
        std::fputs("Windows Capture  : Unicode Start"              "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case ACM_OPENW: /* --> BFFM_SETSELECTIONW | CDM_GETFOLDERIDLIST | EM_GETWORDWRAPMODE | IPM_SETRANGE | PSM_ADDPAGE | UDM_SETPOS | WM_CAP_SET_CALLBACK_STATUSW */ {
      std::fprintf(stdout, "%c%X%4s", '[', ACM_OPENW, "]: {");
        std::fputs("Animation Control: Open"                "\r\n", stdout);
        std::fputs("Browse for Folder: Set Selection"       "\r\n", stdout);
        std::fputs("Common Dialog    : Get Folder ID List"  "\r\n", stdout);
        std::fputs("Internet Protocol: Set Range"           "\r\n", stdout);
        std::fputs("Prop Sheet       : Add Page"            "\r\n", stdout);
        std::fputs("Rich Edit        : Get Word Wrap Mode"  "\r\n", stdout);
        std::fputs("Up-Down Control  : Set Position"        "\r\n", stdout);
        std::fputs("Windows Capture  : Set Callback Status" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case ACM_PLAY: /* --> BFFM_ENABLEOK | CDM_GETFILEPATH | EM_GETPUNCTUATION | IPM_SETADDRESS | UDM_SETRANGE | WM_CHOOSEFONT_SETLOGFONT */ {
      std::fprintf(stdout, "%c%X%4s", '[', ACM_OPENA, "]: {");
        std::fputs("Animation Control: Play"                       "\r\n", stdout);
        std::fputs("Browse for Folder: Enable OK"                  "\r\n", stdout);
        std::fputs("Common Dialog    : Get File Path"              "\r\n", stdout);
        std::fputs("Internet Protocol: Set Address"                "\r\n", stdout);
        std::fputs("Rich Edit        : Get Punctuation"            "\r\n", stdout);
        std::fputs("Up-Down Control  : Set Range"                  "\r\n", stdout);
        std::fputs("Windows          : Choose Font (Set Log Font)" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case ACM_STOP: /* --> BFFM_SETSELECTIONA | CDM_GETFOLDERPATH | EM_SETWORDWRAPMODE | IPM_GETADDRESS | PSM_REMOVEPAGE | UDM_GETRANGE | WM_CAP_SET_CALLBACK_ERRORW | WM_CHOOSEFONT_SETFLAGS */ {
      std::fprintf(stdout, "%c%X%4s", '[', ACM_OPENA, "]: {");
        std::fputs("Animation Control: Stop"                  "\r\n", stdout);
        std::fputs("Browse for Folder: Set Selection"         "\r\n", stdout);
        std::fputs("Common Dialog    : Get Folder Path"       "\r\n", stdout);
        std::fputs("Internet Protocol: Get Address"           "\r\n", stdout);
        std::fputs("Prop Sheet       : Remove Page"           "\r\n", stdout);
        std::fputs("Rich Edit        : Set Word Wrap Mode"    "\r\n", stdout);
        std::fputs("Up-Down Control  : Get Range"             "\r\n", stdout);
        std::fputs("Windows Capture  : Set Callback Error"    "\r\n", stdout);
        std::fputs("Windows          : Choose Font Set Flags" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;

    /* [Browse for Folder] */
    // case BFFM_ENABLEOK      : break;
    // case BFFM_SETSELECTIONA : break;
    // case BFFM_SETSELECTIONW : break;
    // case BFFM_SETSTATUSTEXTA: break;
    case BFFM_SETSTATUSTEXTW: /* --> CDM_SETCONTROLTEXT | EM_SETIMECOLOR | IPM_SETFOCUS | PSM_CHANGED | UDM_GETPOS */ {
      std::fprintf(stdout, "%c%X%4s", '[', ACM_OPENA, "]: {");
        std::fputs("Browse for Folder: Set Status Text"                     "\r\n", stdout);
        std::fputs("Common Dialog    : Set Control Text"                    "\r\n", stdout);
        std::fputs("Internet Protocol: Set Focus"                           "\r\n", stdout);
        std::fputs("Prop Sheet       : Changed"                             "\r\n", stdout);
        std::fputs("Rich Edit        : Set IME (Input Method Editor) Color" "\r\n", stdout);
        std::fputs("Up-Down Control  : Get Position"                        "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case BM_SETDONTCLICK: std::fprintf(stdout, "%c%X%s", '[', BM_SETDONTCLICK, "]: Button > Set Do Not Click" "\r\n"); break;

    /* [Button] */
    case BM_CLICK   : std::fprintf(stdout, "%c%X%s", '[', BM_CLICK,    "]: Button > Click"     "\r\n"); break;
    case BM_GETCHECK: std::fprintf(stdout, "%c%X%s", '[', BM_GETCHECK, "]: Button > Get Check" "\r\n"); break;
    case BM_GETIMAGE: std::fprintf(stdout, "%c%X%s", '[', BM_GETIMAGE, "]: Button > Get Image" "\r\n"); break;
    case BM_GETSTATE: std::fprintf(stdout, "%c%X%s", '[', BM_GETSTATE, "]: Button > Get State" "\r\n"); break;
    case BM_SETCHECK: std::fprintf(stdout, "%c%X%s", '[', BM_SETCHECK, "]: Button > Set Check" "\r\n"); break;
    case BM_SETIMAGE: std::fprintf(stdout, "%c%X%s", '[', BM_SETIMAGE, "]: Button > Set Image" "\r\n"); break;
    case BM_SETSTATE: std::fprintf(stdout, "%c%X%s", '[', BM_SETSTATE, "]: Button > Set State" "\r\n"); break;
    case BM_SETSTYLE: std::fprintf(stdout, "%c%X%s", '[', BM_SETSTYLE, "]: Button > Set Style" "\r\n"); break;

    /* [Combo Box (Extended)] */
    case CBEM_GETCOMBOCONTROL: /* --> PBM_SETRANGE32 | RB_SETBANDINFOA | SB_GETPARTS | TBM_SETRANGE | TB_MARKBUTTON | TTM_NEWTOOLRECTA | WM_PSD_YAFULLPAGERECT */ {
      std::fprintf(stdout, "%c%X%4s", '[', ACM_OPENA, "]: {");
        std::fputs("Combo Box (Extended): Get Combo Control"           "\r\n", stdout);
        std::fputs("Progress Bar        : Set Range"                   "\r\n", stdout);
        std::fputs("Rebar               : Set Band Information"        "\r\n", stdout);
        std::fputs("Status Bar          : Get Parts"                   "\r\n", stdout);
        std::fputs("Toolbar             : Mark Button"                 "\r\n", stdout);
        std::fputs("Tooltips            : New Tool"                    "\r\n", stdout);
        std::fputs("Trackbar            : Set Range"                   "\r\n", stdout);
        std::fputs("Windows             : Page Setup Dialog Full Page" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case CBEM_GETEDITCONTROL: /* --> IE_GETPAINTDC | PBM_GETRANGE | RB_SETPARENT | SB_GETBORDERS | TBM_SETRANGEMIN | TTM_RELAYEVENT */ {
      std::fprintf(stdout, "%c%X%4s", '[', CBEM_GETEDITCONTROL, "]: {");
        std::fputs("Combo Box (Extended): Get Edit Control"         "\r\n", stdout);
        std::fputs("Ink Edit            : Get Paint Device Context" "\r\n", stdout);
        std::fputs("Progress Bar        : Get Range"                "\r\n", stdout);
        std::fputs("Rebar               : Set Parent"               "\r\n", stdout);
        std::fputs("Status Bar          : Get Borders"              "\r\n", stdout);
        std::fputs("Tooltips            : Relay Event"              "\r\n", stdout);
        std::fputs("Trackbar            : Set Range Minimum"        "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case CBEM_GETEXSTYLE: /* --> CBEM_GETEXTENDEDSTYLE | PBM_SETBARCOLOR | RB_GETRECT | SB_SIMPLE | TBM_CLEARTICS | TB_ISBUTTONENABLED | TTM_SETTOOLINFOA */ {
      std::fprintf(stdout, "%c%X%4s", '[', CBEM_GETEXSTYLE, "]: {");
        std::fputs("Combo Box (Extended): Get Extended Style"   "\r\n", stdout);
        std::fputs("Progress Bar        : Set Bar Color"        "\r\n", stdout);
        std::fputs("Rebar               : Get Rectangle"        "\r\n", stdout);
        std::fputs("Status Bar          : Simple"               "\r\n", stdout);
        std::fputs("Toolbar             : Is Button Enabled"    "\r\n", stdout);
        std::fputs("Tooltip             : Set Tool Information" "\r\n", stdout);
        std::fputs("Trackbar            : Clear Ticks"          "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case CBEM_GETIMAGELIST: /* --> HKM_SETRULES | PBM_DELTAPOS | RB_GETBARINFO | SB_GETTEXTLENGTHA | TBM_GETTIC | TB_PRESSBUTTON | TTM_SETDELAYTIME | WM_PSD_MARGINRECT */ {
      std::fprintf(stdout, "%c%X%4s", '[', CBEM_GETIMAGELIST, "]: {");
        std::fputs("Combo Box (Extended): Get Image List"      "\r\n", stdout);
        std::fputs("Hot Key             : Set Rules"           "\r\n", stdout);
        std::fputs("Page Setup Dialog   : Margin Rectangle"    "\r\n", stdout);
        std::fputs("Progress Bar        : Delta Position"      "\r\n", stdout);
        std::fputs("Rebar               : Get Bar Information" "\r\n", stdout);
        std::fputs("Status Bar          : Get Text Length"     "\r\n", stdout);
        std::fputs("Toolbar             : Press Button"        "\r\n", stdout);
        std::fputs("Tooltip             : Set Delay Time"      "\r\n", stdout);
        std::fputs("Trackbar            : Get Tick"            "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case CBEM_GETITEMA: /* --> DDM_END | PBM_SETSTEP | RB_SETBARINFO | SB_SETPARTS | TBM_SETTIC | TB_HIDEBUTTON | TB_SETBUTTONINFOW | TTM_ADDTOOLA | WM_PSD_GREEKTEXTRECT */ {
      std::fprintf(stdout, "%c%X%4s", '[', CBEM_GETITEMA, "]: {");
        std::fputs("Combo Box (Extended): Get Item"               "\r\n", stdout);
        std::fputs("Direct Draw         : End"                    "\r\n", stdout);
        std::fputs("Page Setup Dialog   : Greek Text Rectangle"   "\r\n", stdout);
        std::fputs("Progress Bar        : Set Step"               "\r\n", stdout);
        std::fputs("Rebar               : Set Bar Information"    "\r\n", stdout);
        std::fputs("Status Bar          : Set Parts"              "\r\n", stdout);
        std::fputs("Toolbar             : Hide Button"            "\r\n", stdout);
        std::fputs("Toolbar             : Set Button Information" "\r\n", stdout);
        std::fputs("Tooltip             : Add Tool"               "\r\n", stdout);
        std::fputs("Trackbar            : Set Tick"               "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case CBEM_GETITEMW: /* --> RB_GETROWCOUNT | SB_GETTEXTW | TB_ISBUTTONINDETERMINATE | TTM_GETTOOLCOUNT */ {
      std::fprintf(stdout, "%c%X%4s", '[', CBEM_GETITEMW, "]: {");
        std::fputs("Combo Box (Extended): Get Item"                "\r\n", stdout);
        std::fputs("Rebar               : Get Row Count"           "\r\n", stdout);
        std::fputs("Status Bar          : Get Text"                "\r\n", stdout);
        std::fputs("Toolbar             : Is Button Indeterminate" "\r\n", stdout);
        std::fputs("Tooltip             : Get Tool Count"          "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case CBEM_HASEDITCHANGED: /* --> RB_INSERTBANDW | SB_GETRECT | TBM_SETSEL | TB_ISBUTTONCHECKED | TTM_HITTESTA | WIZ_QUERYNUMPAGES */ {
      std::fprintf(stdout, "%c%X%4s", '[', CBEM_HASEDITCHANGED, "]: {");
        std::fputs("Combo Box (Extended): Has Edit Changed"      "\r\n", stdout);
        std::fputs("Rebar               : Insert Band"           "\r\n", stdout);
        std::fputs("Status Bar          : Get Rectangle"         "\r\n", stdout);
        std::fputs("Toolbar             : Is Button Checked"     "\r\n", stdout);
        std::fputs("Tooltip             : Hit Test"              "\r\n", stdout);
        std::fputs("Trackbar            : Set Selection"         "\r\n", stdout);
        std::fputs("Wizard              : Query Number of Pages" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case CBEM_INSERTITEMA: /* --> DDM_DRAW | DM_SETDEFID | HKM_SETHOTKEY | PBM_SETRANGE | RB_INSERTBANDA | SB_SETTEXTA | TBM_GETRANGEMIN | TB_ENABLEBUTTON | TTM_ACTIVATE | WM_CHOOSEFONT_GETLOGFONT | WM_PSD_FULLPAGERECT */ {
      std::fprintf(stdout, "%c%X%4s", '[', CBEM_INSERTITEMA, "]: {");
        std::fputs("Combo Box (Extended): Insert Item"                "\r\n", stdout);
        std::fputs("Direct Draw         : Draw"                       "\r\n", stdout);
        std::fputs("Dialog              : Set Default Identity"       "\r\n", stdout);
        std::fputs("Hot Key             : Set Hotkey"                 "\r\n", stdout);
        std::fputs("Page Setup Dialog   : Full Page Rectangle"        "\r\n", stdout);
        std::fputs("Progress Bar        : Set Range"                  "\r\n", stdout);
        std::fputs("Rebar               : Insert Band"                "\r\n", stdout);
        std::fputs("Status Bar          : Set Text"                   "\r\n", stdout);
        std::fputs("Toolbar             : Enable Button"              "\r\n", stdout);
        std::fputs("Tooltip             : Activate"                   "\r\n", stdout);
        std::fputs("Trackbar            : Get Range"                  "\r\n", stdout);
        std::fputs("Windows             : Choose Font / Get Log Font" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case CBEM_INSERTITEMW: /* --> RB_SETBANDINFOW | SB_SETTEXTW | TBM_SETSELSTART | TB_ISBUTTONPRESSED | TTM_GETTEXTA | WIZ_NEXT */ {
      std::fprintf(stdout, "%c%X%4s", '[', CBEM_INSERTITEMW, "]: {");
        std::fputs("Combo Box (Extended): Insert Item"          "\r\n", stdout);
        std::fputs("Rebar               : Set Band Information" "\r\n", stdout);
        std::fputs("Status Bar          : Set Text"             "\r\n", stdout);
        std::fputs("Toolbar             : Is Button Pressed"    "\r\n", stdout);
        std::fputs("Tooltip             : Get Text"             "\r\n", stdout);
        std::fputs("Trackbar            : Set Selection Start"  "\r\n", stdout);
        std::fputs("Wizard              : Next"                 "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case CBEM_SETEXSTYLE: /* --> CBEM_SETEXTENDEDSTYLE | PBM_GETPOS | RB_HITTEST | SB_SETMINHEIGHT | TBM_SETRANGEMAX | TTM_GETTOOLINFOA */ {
      std::fprintf(stdout, "%c%X%4s", '[', CBEM_SETEXSTYLE, "]: {");
        std::fputs("Combo Box (Extended): Set Extended Style"   "\r\n", stdout);
        std::fputs("Progress Bar        : Get Position"         "\r\n", stdout);
        std::fputs("Rebar               : Hit Test"             "\r\n", stdout);
        std::fputs("Status Bar          : Set Minimum Height"   "\r\n", stdout);
        std::fputs("Tooltip             : Get Tool Information" "\r\n", stdout);
        std::fputs("Trackbar            : Set Range Maximum"    "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case CBEM_SETIMAGELIST: /* --> DDM_BEGIN | DDM_CLOSE | DM_REPOSITION | HKM_GETHOTKEY | PBM_SETPOS | RB_DELETEBAND | SB_GETTEXTA | TBM_GETRANGEMAX | TB_CHECKBUTTON | WM_PSD_MINMARGINRECT */ {
      std::fprintf(stdout, "%c%X%4s", '[', CBEM_SETIMAGELIST, "]: {");
        std::fputs("Combo Box (Extended): Set Image List"           "\r\n", stdout);
        std::fputs("Dialog              : Reposition"               "\r\n", stdout);
        std::fputs("Direct Draw         : Begin"                    "\r\n", stdout);
        std::fputs("Direct Draw         : Close"                    "\r\n", stdout);
        std::fputs("Hot Key             : Get Hotkey"               "\r\n", stdout);
        std::fputs("Page Setup Dialog   : Minimum Margin Rectangle" "\r\n", stdout);
        std::fputs("Progress Bar        : Set Position"             "\r\n", stdout);
        std::fputs("Rebar               : Delete Band"              "\r\n", stdout);
        std::fputs("Status Bar          : Get Text"                 "\r\n", stdout);
        std::fputs("Toolbar             : Check Button"             "\r\n", stdout);
        std::fputs("Trackbar            : Get Range Maximum"        "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case CBEM_SETITEMA: /* --> PBM_STEPIT | TBM_SETPOS | TB_INDETERMINATE | TTM_DELTOOLA | WM_PSD_ENVSTAMPRECT */ {
      std::fprintf(stdout, "%c%X%4s", '[', CBEM_SETITEMA, "]: {");
        std::fputs("Combo Box (Extended): Set Item"                 "\r\n", stdout);
        std::fputs("Page Setup Dialog   : Envelope Stamp Rectangle" "\r\n", stdout);
        std::fputs("Progress Bar        : Step It"                  "\r\n", stdout);
        std::fputs("Toolbar             : Indeterminate"            "\r\n", stdout);
        std::fputs("Tooltip             : Delete Tool"              "\r\n", stdout);
        std::fputs("Trackbar            : Set Position"             "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case CBEM_SETITEMW: /* --> RB_GETBANDCOUNT | SB_GETTEXTLENGTHW | TBM_SETSELEND | TB_ISBUTTONHIDDEN | TTM_UPDATETIPTEXTA | WIZ_PREV */ {
      std::fprintf(stdout, "%c%X%4s", '[', CBEM_SETITEMW, "]: {");
        std::fputs("Combo Box (Extended): Set Item"          "\r\n", stdout);
        std::fputs("Rebar               : Get Band Count"    "\r\n", stdout);
        std::fputs("Status Bar          : Get Text Length"   "\r\n", stdout);
        std::fputs("Toolbar             : Is Button Hidden"  "\r\n", stdout);
        std::fputs("Tooltip             : Update Tip Text"   "\r\n", stdout);
        std::fputs("Trackbar            : Set Selection End" "\r\n", stdout);
        std::fputs("Wizard              : Previous"          "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;

    /* [Common Item Dialog] */
    // case CDM_GETFILEPATH    : break;
    // case CDM_GETFOLDERIDLIST: break;
    // case CDM_GETFOLDERPATH  : break;
    case CDM_HIDECONTROL: /* --> EM_GETIMECOLOR | IPM_ISBLANK | PSM_RESTARTWINDOWS | UDM_SETBUDDY */ {
      std::fprintf(stdout, "%c%X%4s", '[', CDM_HIDECONTROL, "]: {");
        std::fputs("Common Dialog    : Hide Control"                        "\r\n", stdout);
        std::fputs("Internet Protocol: Is Blank"                            "\r\n", stdout);
        std::fputs("Prop Sheet       : Restart Windows"                     "\r\n", stdout);
        std::fputs("Rich Edit        : Get IME (Input Method Editor) Color" "\r\n", stdout);
        std::fputs("Up-Down Control  : Set Buddy"                           "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case CDM_FIRST  : break;
    // case CDM_GETSPEC: break;
    case CDM_LAST: /* (Lapys) > EM_SETBIDIOPTIONS | IE_DOCOMMAND | MCIWNDM_NOTIFYMODE */ {
      std::fprintf(stdout, "%c%X%4s", '[', CDM_LAST, "]: {");
        std::fputs("Common Dialog        : [LAST]"                     "\r\n", stdout);
        std::fputs("Ink Edit             : Do Command"                 "\r\n", stdout);
        std::fputs("Multimedia MCI Window: Notify Mode"                "\r\n", stdout);
        std::fputs("Rich Edit            : Set Bi-directional Options" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case CDM_SETCONTROLTEXT: break;
    case CDM_SETDEFEXT: /* --> EM_SETIMEOPTIONS | PSM_REBOOTSYSTEM | UDM_GETBUDDY */ {
      std::fprintf(stdout, "%c%X%4s", '[', CDM_SETDEFEXT, "]: {");
        std::fputs("Common Dialog  : Set Default Text"                      "\r\n", stdout);
        std::fputs("Prop Sheet     : Reboot System"                         "\r\n", stdout);
        std::fputs("Rich Edit      : Set IME (Input Method Editor) Options" "\r\n", stdout);
        std::fputs("Up-Down Control: Get Buddy"                             "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;

    /* [Direct Draw] */
    // case DDM_BEGIN: break;
    // case DDM_CLOSE: break;
    // case DDM_DRAW : break;
    // case DDM_END  : break;
    case DDM_SETFMT: /* --> DM_GETDEFID | NIN_SELECT | TBM_GETPOS | WM_PSD_PAGESETUPDLG | WM_USER */ {
      std::fprintf(stdout, "%c%X%4s", '[', DDM_SETFMT, "]: {");
        std::fputs("Dialog           : Get Default Identity" "\r\n", stdout);
        std::fputs("Direct Draw      : Set Format"           "\r\n", stdout);
        std::fputs("Notify Icon      : Select"               "\r\n", stdout);
        std::fputs("Page Setup Dialog: Page Setup Dialog"    "\r\n", stdout);
        std::fputs("Trackbar         : Get Position"         "\r\n", stdout);
        std::fputs("Windows          : [USER]"               "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;

    /* [Drag List (Box)] */
    case DL_BEGINDRAG: /* --> MCIWNDM_GETINACTIVETIMER | PSM_IDTOINDEX | TB_BUTTONCOUNT | TTM_SETMAXTIPWIDTH */ {
      std::fprintf(stdout, "%c%X%4s", '[', DL_BEGINDRAG, "]: {");
        std::fputs("Drag List Box        : Begin Drag"            "\r\n", stdout);
        std::fputs("Multimedia MCI Window: Get Inactive Timer"    "\r\n", stdout);
        std::fputs("Prop Sheet           : Identity to Index"     "\r\n", stdout);
        std::fputs("Toolbar              : Button Count"          "\r\n", stdout);
        std::fputs("Tooltip              : Set Maximum Tip Width" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case DL_CANCELDRAG: /* --> PSM_RECALCPAGESIZES */ {
      std::fprintf(stdout, "%c%X%4s", '[', DL_CANCELDRAG, "]: {");
        std::fputs("Drag List Box: Cancel Drag"            "\r\n", stdout);
        std::fputs("Prop Sheet   : Recalculate Page Sizes" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case DL_DRAGGING: /* --> PSM_INDEXTOID */ {
      std::fprintf(stdout, "%c%X%4s", '[', DL_DRAGGING, "]: {");
        std::fputs("Drag List Box: Dragging"          "\r\n", stdout);
        std::fputs("Prop Sheet   : Index to Identity" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case DL_DROPPED: /* --> PSM_GETRESULT */ {
      std::fprintf(stdout, "%c%X%4s", '[', DL_DROPPED, "]: {");
        std::fputs("Drag List Box: Dropped"     "\r\n", stdout);
        std::fputs("Prop Sheet   : Get Results" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;

    /* [Dialog] */
    // case DM_GETDEFID  : break;
    // case DM_REPOSITION: break;
    // case DM_SETDEFID  : break;

    /* [Rich Edit] */
    case EM_AUTOURLDETECT: /* --> TB_GETSTRINGW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_AUTOURLDETECT, "]: {");
        std::fputs("Rich Edit: Automatic URL Detect" "\r\n", stdout);
        std::fputs("Toolbar  : Get String"           "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_CANPASTE: /* --> TB_LOADIMAGES */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_CANPASTE, "]: {");
        std::fputs("Rich Edit: Can Paste"   "\r\n", stdout);
        std::fputs("Toolbar  : Load Images" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_CANREDO: /* --> TB_GETEXTENDEDSTYLE */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_CANREDO, "]: {");
        std::fputs("Rich Edit: Can Redo"           "\r\n", stdout);
        std::fputs("Toolbar  : Get Extended Style" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_CANUNDO    : std::fprintf(stdout, "%c%X%s", '[', EM_CANUNDO,     "]: Rich Edit > Can Undo"                "\r\n"); break;
    case EM_CHARFROMPOS: std::fprintf(stdout, "%c%X%s", '[', EM_CHARFROMPOS, "]: Rich Edit > Character from Position" "\r\n"); break;
    case EM_CONVPOSITION: /* --> PSM_QUERYSIBLINGS | UDM_GETACCEL */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_CONVPOSITION, "]: {");
        std::fputs("Prop Sheet     : Query Siblings"  "\r\n", stdout);
        std::fputs("Rich Edit      : Conv... Position" "\r\n", stdout);
        std::fputs("Up-Down Control: Get Acceleration" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_DISPLAYBAND: /* --> TB_GETRECT | TTM_DELTOOLW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_DISPLAYBAND, "]: {");
        std::fputs("Rich Edit: Display Band"  "\r\n", stdout);
        std::fputs("Toolbar  : Get Rectangle" "\r\n", stdout);
        std::fputs("Tooltip  : Delete Tool"   "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_EMPTYUNDOBUFFER: std::fprintf(stdout, "%c%X%s", '[', EM_EMPTYUNDOBUFFER, "]: Rich Edit > Empty Undo Buffer" "\r\n"); break;
    case EM_EXGETSEL: /* --> TB_SETHOTIMAGELIST | TTM_NEWTOOLRECTW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_EXGETSEL, "]: {");
        std::fputs("Rich Edit: Extend Get Selection" "\r\n", stdout);
        std::fputs("Toolbar  : Set Hot Image List"   "\r\n", stdout);
        std::fputs("Tooltip  : New Tool Rectangle"   "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_EXLIMITTEXT: /* --> TB_GETHOTIMAGELIST | TTM_GETTOOLINFOW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_EXLIMITTEXT, "]: {");
        std::fputs("Rich Edit: Extend Limit Text"    "\r\n", stdout);
        std::fputs("Toolbar  : Get Hot Image List"   "\r\n", stdout);
        std::fputs("Tooltip  : Get Tool Information" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_EXLINEFROMCHAR: /* --> TB_SETDISABLEDIMAGELIST | TTM_SETTOOLINFOW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_EXLINEFROMCHAR, "]: {");
        std::fputs("Rich Edit: Extend Line From Character" "\r\n", stdout);
        std::fputs("Toolbar  : Set Disabled Image List"    "\r\n", stdout);
        std::fputs("Tooltip  : Set Tool Information"       "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_EXSETSEL: /* --> TB_GETDISABLEDIMAGELIST | TTM_HITTESTW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_EXSETSEL, "]: {");
        std::fputs("Rich Edit: Extend Set Selection"    "\r\n", stdout);
        std::fputs("Toolbar  : Get Disabled Image List" "\r\n", stdout);
        std::fputs("Tooltip  : Hit Test"                "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_FINDTEXT: /* --> TB_SETSTYLE | TTM_GETTEXTW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_FINDTEXT, "]: {");
        std::fputs("Rich Edit: Find Text" "\r\n", stdout);
        std::fputs("Toolbar  : Set Style" "\r\n", stdout);
        std::fputs("Tooltip  : Get Text"  "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_FINDTEXTEX: /* --> TB_GETINSERTMARK */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_FINDTEXTEX, "]: {");
        std::fputs("Rich Edit: Find Text (Extended)" "\r\n", stdout);
        std::fputs("Toolbar  : Get Insert Mark"      "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_FINDTEXTEXW: /* --> MCIWNDM_GETFILENAMEA */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_FINDTEXTEXW, "]: {");
        std::fputs("Rich Edit              : Find Text (Extended)" "\r\n", stdout);
        std::fputs("Multimedia (MCI) Window: Get File Name"        "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_FINDTEXTW: /* --> MCIWNDM_PLAYTO | WM_CAP_FILE_SAVEASW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_FINDTEXTW, "]: {");
        std::fputs("Rich Edit              : Find Text (Extended)" "\r\n", stdout);
        std::fputs("Multimedia (MCI) Window: Play To"              "\r\n", stdout);
        std::fputs("Windows Capture        : File Save As"         "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_FINDWORDBREAK: /* --> TB_SAVERESTOREW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_FINDWORDBREAK, "]: {");
        std::fputs("Rich Edit: Find Word Break" "\r\n", stdout);
        std::fputs("Toolbar  : Save Restore"    "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_FMTLINES: std::fprintf(stdout, "%c%X%s", '[', EM_FMTLINES, "]: Rich Edit > Format Lines" "\r\n"); break;
    case EM_FORMATRANGE: /* --> TB_GETSTYLE | TTM_UPDATETIPTEXTW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_FORMATRANGE, "]: {");
        std::fputs("Rich Edit: Format Range"    "\r\n", stdout);
        std::fputs("Toolbar  : Get Style"       "\r\n", stdout);
        std::fputs("Tooltip  : Update Tip Text" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETAUTOURLDETECT: /* --> TB_GETSTRINGA */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETAUTOURLDETECT, "]: {");
        std::fputs("Rich Edit: Get Automatic URL Detection" "\r\n", stdout);
        std::fputs("Toolbar  : Get String"                  "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETBIDIOPTIONS: /* --> IE_GETCOMMAND */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETBIDIOPTIONS, "]: {");
        std::fputs("Ink Edit : Get Command"                "\r\n", stdout);
        std::fputs("Rich Edit: Get Bi-directional Options" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETCHARFORMAT: /* --> TB_GETBUTTONSIZE | TTM_ENUMTOOLSW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETCHARFORMAT, "]: {");
        std::fputs("Rich Edit: Get Character Format" "\r\n", stdout);
        std::fputs("Toolbar  : Get Button Size"      "\r\n", stdout);
        std::fputs("Tooltip  : Enumerate Tools"      "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETCTFMODEBIAS  : std::fprintf(stdout, "%c%X%s", '[', EM_GETCTFMODEBIAS,   "]: Rich Edit > Get CTF Mode Bias"   "\r\n"); break;
    case EM_GETCTFOPENSTATUS: std::fprintf(stdout, "%c%X%s", '[', EM_GETCTFOPENSTATUS, "]: Rich Edit > Get CTF Open Status" "\r\n"); break;
    case EM_GETEDITSTYLE: /* --> MCIWNDM_NOTIFYERROR */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETEDITSTYLE, "]: {");
        std::fputs("Rich Edit            : Get Edit Style" "\r\n", stdout);
        std::fputs("Multimedia MCI Window: Notify Error"   "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETEVENTMASK: /* --> TB_SETBUTTONWIDTH | TTM_GETCURRENTTOOLW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETEVENTMASK, "]: {");
        std::fputs("Rich Edit: Get Event Mask"   "\r\n", stdout);
        std::fputs("Toolbar  : Set Button Width" "\r\n", stdout);
        std::fputs("Tooltip  : Get Current Tool" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETFIRSTVISIBLELINE: std::fprintf(stdout, "%c%X%s", '[', EM_GETFIRSTVISIBLELINE, "]: Rich Edit > Get First Visible Line"    "\r\n"); break;
    case EM_GETHANDLE          : std::fprintf(stdout, "%c%X%s", '[', EM_GETHANDLE,           "]: Rich Edit > Get Handle"                "\r\n"); break;
    case EM_GETHYPHENATEINFO   : std::fprintf(stdout, "%c%X%s", '[', EM_GETHYPHENATEINFO,    "]: Rich Edit > Get Hyphenate Information" "\r\n"); break;
    // case EM_GETIMECOLOR: break;
    case EM_GETIMECOMPMODE: std::fprintf(stdout, "%c%X%s", '[', EM_GETIMECOMPMODE, "]: Rich Edit > Get IME (Input Method Editor) Composition Mode" "\r\n"); break;
    case EM_GETIMECOMPTEXT: std::fprintf(stdout, "%c%X%s", '[', EM_GETIMECOMPTEXT, "]: Rich Edit > Get IME (Input Method Editor) Composition Text" "\r\n"); break;
    case EM_GETIMEMODEBIAS: /* --> MCIWNDM_SETPALETTE | PSM_SETHEADERSUBTITLEA */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETIMEMODEBIAS, "]: {");
        std::fputs("Rich Edit            : Get IME (Input Method Editor) Mode Bias" "\r\n", stdout);
        std::fputs("Multimedia MCI Window: Set Palette"                             "\r\n", stdout);
        std::fputs("Prop Sheet           : Set Header Subtitle"                     "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETIMEOPTIONS: /* --> PSM_CANCELTOCLOSE | UDM_SETACCEL */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETIMEOPTIONS, "]: {");
        std::fputs("Rich Edit      : Get IME (Input Method Editor) Options" "\r\n", stdout);
        std::fputs("Prop Sheet     : Cancel to Close"                       "\r\n", stdout);
        std::fputs("Up-Down Control: Set Acceleration"                      "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETIMEPROPERTY: std::fprintf(stdout, "%c%X%s", '[', EM_GETIMECOMPTEXT, "]: Rich Edit > Get IME (Input Method Editor) Property" "\r\n"); break;
    case EM_GETIMESTATUS  : std::fprintf(stdout, "%c%X%s", '[', EM_GETIMESTATUS,   "]: Rich Edit > Get IME (Input Method Editor) Status"   "\r\n"); break;
    case EM_GETLANGOPTIONS: /* --> MCIWNDM_VALIDATEMEDIA | PSM_SETCURSEL | PSM_SETFINISHTEXTA | PSM_SETFINISHTEXTW | WM_CAP_FILE_GET_CAPTURE_FILEW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETLANGOPTIONS, "]: {");
        std::fputs("Rich Edit              : Get Language Options" "\r\n", stdout);
        std::fputs("Multimedia (MCI) Window: Validate Media"       "\r\n", stdout);
        std::fputs("Prop Sheet             : Set Cursor Selection" "\r\n", stdout);
        std::fputs("Prop Sheet             : Set Finish Text"      "\r\n", stdout);
        std::fputs("Windows Capture        : File Get Capture"     "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETLIMITTEXT: std::fprintf(stdout, "%c%X%s", '[', EM_GETLIMITTEXT, "]: Rich Edit > Get Limit Text" "\r\n"); break;
    case EM_GETLINE     : std::fprintf(stdout, "%c%X%s", '[', EM_GETLINE,      "]: Rich Edit > Get Line"       "\r\n"); break;
    case EM_GETLINECOUNT: std::fprintf(stdout, "%c%X%s", '[', EM_GETLINECOUNT, "]: Rich Edit > Get Line Count" "\r\n"); break;
    case EM_GETMARGINS  : std::fprintf(stdout, "%c%X%s", '[', EM_GETMARGINS,   "]: Rich Edit > Get Margins"    "\r\n"); break;
    case EM_GETMODIFY   : std::fprintf(stdout, "%c%X%s", '[', EM_GETMODIFY,    "]: Rich Edit > Get Modify"     "\r\n"); break;
    case EM_GETOLEINTERFACE: /* --> TB_SETMAXTEXTROWS */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETOLEINTERFACE, "]: {");
        std::fputs("Rich Edit: Get Tole Interface"    "\r\n", stdout);
        std::fputs("Toolbar  : Set Maximum Text Rows" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETOPTIONS: /* --> TB_MAPACCELERATORA */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETOPTIONS, "]: {");
        std::fputs("Rich Edit: Get Options"     "\r\n", stdout);
        std::fputs("Toolbar  : Map Accelerator" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETPAGE: {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETPAGE, "]: {");
        std::fputs("Multimedia (MCI) Window: Get Error" "\r\n", stdout);
        std::fputs("Rich Edit              : Get Page"  "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETPAGEROTATE: std::fprintf(stdout, "%c%X%s", '[', EM_GETPAGEROTATE, "]: Rich Edit > Get Page Rotate" "\r\n"); break;
    case EM_GETPARAFORMAT: /* --> TB_GETTEXTROWS */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETPARAFORMAT, "]: {");
        std::fputs("Rich Edit: Get Paragraph Format" "\r\n", stdout);
        std::fputs("Toolbar  : Get Text Rows"        "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETPASSWORDCHAR: std::fprintf(stdout, "%c%X%s", '[', EM_GETPASSWORDCHAR, "]: Rich Edit > Get Password Character" "\r\n"); break;
    // case EM_GETPUNCTUATION: break;
    // case EM_GETQUERYRTFOBJ: break;
    case EM_GETRECT: std::fprintf(stdout, "%c%X%s", '[', EM_GETRECT, "]: Rich Edit > Get Rectangle" "\r\n"); break;
    case EM_GETREDONAME: /* --> TB_SETPADDING */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETREDONAME, "]: {");
        std::fputs("Rich Edit: Get Redo Name" "\r\n", stdout);
        std::fputs("Toolbar  : Set Padding"   "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETSCROLLPOS: std::fprintf(stdout, "%c%X%s", '[', EM_GETSCROLLPOS, "]: Rich Edit > Get Scroll Position" "\r\n"); break;
    case EM_GETSEL      : std::fprintf(stdout, "%c%X%s", '[', EM_GETSEL,       "]: Rich Edit > Get Selection"       "\r\n"); break;
    case EM_GETSELTEXT: /* --> TB_GETOBJECT */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETSELTEXT, "]: {");
        std::fputs("Rich Edit: Get Selection Text" "\r\n", stdout);
        std::fputs("Toolbar  : Get Object"         "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETTEXTEX      : std::fprintf(stdout, "%c%X%s", '[', EM_GETTEXTEX,       "]: Rich Edit > Get Text (Extended)"        "\r\n"); break;
    case EM_GETTEXTLENGTHEX: std::fprintf(stdout, "%c%X%s", '[', EM_GETTEXTLENGTHEX, "]: Rich Edit > Get Text Length (Extended)" "\r\n"); break;
    case EM_GETTEXTMODE: /* --> TB_MAPACCELERATORW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETTEXTMODE, "]: {");
        std::fputs("Rich Edit: Get Text Mode"    "\r\n", stdout);
        std::fputs("Toolbar  : Map Acceleration" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETTEXTRANGE: /* --> TB_GETBUTTONTEXTW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETTEXTRANGE, "]: {");
        std::fputs("Rich Edit: Get Text Range"  "\r\n", stdout);
        std::fputs("Toolbar  : Get Button Text" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETTHUMB: std::fprintf(stdout, "%c%X%s", '[', EM_GETTHUMB, "]: Rich Edit > Get Thumb" "\r\n"); break;
    case EM_GETTYPOGRAPHYOPTIONS: /* --> IE_GETGESTURE | MCIWNDM_NOTIFYMEDIA */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETTYPOGRAPHYOPTIONS, "]: {");
        std::fputs("Ink Edit               : Get Gesture"            "\r\n", stdout);
        std::fputs("Multimedia (MCI) Window: Notify Media"           "\r\n", stdout);
        std::fputs("Rich Edit              : Get Typography Options" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETUNDONAME: /* --> TB_GETPADDING */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETUNDONAME, "]: {");
        std::fputs("Rich Edit: Get Undo Name" "\r\n", stdout);
        std::fputs("Toolbar  : Get Padding"   "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_GETVIEWKIND     : std::fprintf(stdout, "%c%X%s", '[', EM_GETVIEWKIND,      "]: Rich Edit > Get View Kind"            "\r\n"); break;
    case EM_GETWORDBREAKPROC: std::fprintf(stdout, "%c%X%s", '[', EM_GETWORDBREAKPROC, "]: Rich Edit > Get Word Break Procedure" "\r\n"); break;
    case EM_GETWORDBREAKPROCEX: /* --> TB_SETINSERTMARK */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETWORDBREAKPROCEX, "]: {");
        std::fputs("Rich Edit: Get Word Break Procedure (Extended)" "\r\n", stdout);
        std::fputs("Toolbar  : Set Insert Mark"                     "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case EM_GETWORDWRAPMODE: break;
    case EM_GETZOOM: /* --> MCIWNDM_GETFILENAMEW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_GETZOOM, "]: {");
        std::fputs("Multimedia (MCI) Window: Get File Name" "\r\n", stdout);
        std::fputs("Rich Edit              : Get Zoom"      "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_HIDESELECTION: /* --> TB_GETBUTTONINFOW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_HIDESELECTION, "]: {");
        std::fputs("Rich Edit: Hide Selection"         "\r\n", stdout);
        std::fputs("Toolbar  : Get Button Information" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_ISIME: std::fprintf(stdout, "%c%X%s", '[', EM_ISIME, "]: Rich Edit > Is IME (Input Method Editor)" "\r\n"); break;
    case EM_LIMITTEXT: /* --> EM_SETLIMITTEXT */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_LIMITTEXT, "]: {");
        std::fputs("Rich Edit: Limit Text"     "\r\n", stdout);
        std::fputs("Rich Edit: Set Limit Text" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_LINEFROMCHAR: std::fprintf(stdout, "%c%X%s", '[', EM_LINEFROMCHAR, "]: Rich Edit > Line From Character"          "\r\n"); break;
    case EM_LINEINDEX   : std::fprintf(stdout, "%c%X%s", '[', EM_LINEINDEX,    "]: Rich Edit > Line Index"                   "\r\n"); break;
    case EM_LINELENGTH  : std::fprintf(stdout, "%c%X%s", '[', EM_LINELENGTH,   "]: Rich Edit > Line Length"                  "\r\n"); break;
    case EM_LINESCROLL  : std::fprintf(stdout, "%c%X%s", '[', EM_LINESCROLL,   "]: Rich Edit > Line Scroll"                  "\r\n"); break;
    case EM_OUTLINE     : std::fprintf(stdout, "%c%X%s", '[', EM_OUTLINE,      "]: Rich Edit > Line Outline"                 "\r\n"); break;
    case EM_PASTESPECIAL: std::fprintf(stdout, "%c%X%s", '[', EM_PASTESPECIAL, "]: Rich Edit > Line Paste Special"           "\r\n"); break;
    case EM_POSFROMCHAR : std::fprintf(stdout, "%c%X%s", '[', EM_POSFROMCHAR,  "]: Rich Edit > Line Position from Character" "\r\n"); break;
    case EM_RECONVERSION: /* --> MCIWNDM_GETDEVICEA | PSM_SETHEADERTITLEA | WM_CAP_FILE_SAVEDIBW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_RECONVERSION, "]: {");
        std::fputs("Multimedia (MCI) Window: Get Device"       "\r\n", stdout);
        std::fputs("Prop Sheet             : Set Header Title" "\r\n", stdout);
        std::fputs("Rich Edit              : Reconversion"     "\r\n", stdout);
        std::fputs("Windows Capture        : File Save ..."    "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_REDO: /* --> TB_SETEXTENDEDSTYLE */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_REDO, "]: {");
        std::fputs("Rich Edit: Redo"               "\r\n", stdout);
        std::fputs("Toolbar  : Set Extended Style" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_REPLACESEL: std::fprintf(stdout, "%c%X%s", '[', EM_REPLACESEL, "]: Rich Edit > Replace Selection" "\r\n"); break;
    case EM_REQUESTRESIZE: /* --> TB_GETBUTTONINFOA */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_REQUESTRESIZE, "]: {");
        std::fputs("Rich Edit: Request Resize"         "\r\n", stdout);
        std::fputs("Toolbar  : Get Button Information" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_SCROLL     : std::fprintf(stdout, "%c%X%s", '[', EM_SCROLL,      "]: Rich Edit > Scroll"       "\r\n"); break;
    case EM_SCROLLCARET: std::fprintf(stdout, "%c%X%s", '[', EM_SCROLLCARET, "]: Rich Edit > Scroll Caret" "\r\n"); break;
    case EM_SELECTIONTYPE: /* --> TB_SETBUTTONINFOA */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_SELECTIONTYPE, "]: {");
        std::fputs("Rich Edit: Selection Type"         "\r\n", stdout);
        std::fputs("Toolbar  : Set Button Information" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case EM_SETBIDIOPTIONS: break;
    case EM_SETBKGNDCOLOR: /* --> TB_INSERTBUTTONW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_SETBKGNDCOLOR, "]: {");
        std::fputs("Rich Edit: Set Background Color" "\r\n", stdout);
        std::fputs("Toolbar  : Insert Button"        "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_SETCHARFORMAT: /* --> TB_ADDBUTTONSW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_SETCHARFORMAT, "]: {");
        std::fputs("Rich Edit: Set Character Format" "\r\n", stdout);
        std::fputs("Toolbar  : Add Buttons"          "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_SETCTFMODEBIAS  : std::fprintf(stdout, "%c%X%s", '[', EM_SETCTFMODEBIAS,   "]: Rich Edit > Set CTF Mode Bias" "\r\n");   break;
    case EM_SETCTFOPENSTATUS: std::fprintf(stdout, "%c%X%s", '[', EM_SETCTFOPENSTATUS, "]: Rich Edit > Set CTF Open Status" "\r\n"); break;
    case EM_SETEDITSTYLE: /* --> IE_GETMENU */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_SETEDITSTYLE, "]: {");
        std::fputs("Ink Edit : Get Menu"       "\r\n", stdout);
        std::fputs("Rich Edit: Set Edit Style" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_SETEVENTMASK: /* --> TB_HITTEST */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_SETEVENTMASK, "]: {");
        std::fputs("Rich Edit: Set Event Mask" "\r\n", stdout);
        std::fputs("Toolbar  : Hit Test"       "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_SETFONT         : std::fprintf(stdout, "%c%X%s", '[', EM_SETFONT,          "]: Rich Edit > Set Font"                  "\r\n"); break;
    case EM_SETFONTSIZE     : std::fprintf(stdout, "%c%X%s", '[', EM_SETFONTSIZE,      "]: Rich Edit > Set Font Size"             "\r\n"); break;
    case EM_SETHANDLE       : std::fprintf(stdout, "%c%X%s", '[', EM_SETHANDLE,        "]: Rich Edit > Set Handle"                "\r\n"); break;
    case EM_SETHYPHENATEINFO: std::fprintf(stdout, "%c%X%s", '[', EM_SETHYPHENATEINFO, "]: Rich Edit > Set Hyphenate Information" "\r\n");  break;
    // case EM_SETIMECOLOR: break;
    case EM_SETIMEMODEBIAS: /* --> MCIWNDM_GETPALETTE | PSM_SETHEADERTITLEW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_SETIMEMODEBIAS, "]: {");
        std::fputs("Multimedia (MCI) Window: Get Palette"                             "\r\n", stdout);
        std::fputs("Prop Sheet             : Set Header Title"                        "\r\n", stdout);
        std::fputs("Rich Edit              : Set IME (Input Method Editor) Mode Bias" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case EM_SETIMEOPTIONS: break;
    case EM_SETIMESTATUS: std::fprintf(stdout, "%c%X%s", '[', EM_SETIMESTATUS, "]: Rich Edit > Set Time Status" "\r\n"); break;
    case EM_SETLANGOPTIONS: /* --> MCIWNDM_GETTIMEFORMATA | PSM_SETTITLEW | WM_CAP_FILE_SET_CAPTURE_FILEW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_SETLANGOPTIONS, "]: {");
        std::fputs("Multimedia (MCI) Window: Get Time Format"       "\r\n", stdout);
        std::fputs("Prop Sheet             : Set Title"             "\r\n", stdout);
        std::fputs("Rich Edit              : Set Language Options"  "\r\n", stdout);
        std::fputs("Windows Capture        : File Set Capture File" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_SETMARGINS: std::fprintf(stdout, "%c%X%s", '[', EM_SETMARGINS, "]: Rich Edit > Set Margins" "\r\n"); break;
    case EM_SETMODIFY : std::fprintf(stdout, "%c%X%s", '[', EM_SETMODIFY,  "]: Rich Edit > Set Modify"  "\r\n"); break;
    // case EM_SETLIMITTEXT: break;
    case EM_SETOLECALLBACK: /* --> TB_SETDRAWTEXTFLAGS */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_SETOLECALLBACK, "]: {");
        std::fputs("Rich Edit: Set OLE (Object Linking & Embedding) Callback" "\r\n", stdout);
        std::fputs("Toolbar  : Set Draw Text Flags"                           "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_SETOPTIONS: /* --> TB_ADDSTRINGW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_SETOLECALLBACK, "]: {");
        std::fputs("Rich Edit: Set Options" "\r\n", stdout);
        std::fputs("Toolbar  : Add String"  "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_SETPAGE      : std::fprintf(stdout, "%c%X%s", '[', EM_SETPAGE,       "]: Rich Edit > Set Page"        "\r\n"); break;
    case EM_SETPAGEROTATE: std::fprintf(stdout, "%c%X%s", '[', EM_SETPAGEROTATE, "]: Rich Edit > Set Page Rotate" "\r\n"); break;
    case EM_SETPALETTE   : std::fprintf(stdout, "%c%X%s", '[', EM_SETPALETTE,    "]: Rich Edit > Set Palette"     "\r\n"); break;
    case EM_SETPARAFORMAT: /* --> TB_GETHOTITEM */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_SETPARAFORMAT, "]: {");
        std::fputs("Rich Edit: Set Paragraph Format" "\r\n", stdout);
        std::fputs("Toolbar  : Get Hot Item"         "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_SETPASSWORDCHAR: std::fprintf(stdout, "%c%X%s", '[', EM_SETPASSWORDCHAR, "]: Rich Edit > Set Password Character" "\r\n"); break;
    // case EM_SETPUNCTUATION: break;
    case EM_SETQUERYRTFOBJ: std::fprintf(stdout, "%c%X%s", '[', EM_SETQUERYRTFOBJ, "]: Rich Edit > Set Query Rich-Text Format Object" "\r\n"); break;
    case EM_SETREADONLY   : std::fprintf(stdout, "%c%X%s", '[', EM_SETREADONLY,    "]: Rich Edit > Set Read-Only"                     "\r\n"); break;
    case EM_SETRECT       : std::fprintf(stdout, "%c%X%s", '[', EM_SETRECT,        "]: Rich Edit > Set Rectangle"                     "\r\n"); break;
    case EM_SETRECTNP     : std::fprintf(stdout, "%c%X%s", '[', EM_SETRECTNP,      "]: Rich Edit > Set Rectangle New Position"        "\r\n"); break;
    case EM_SETSCROLLPOS  : std::fprintf(stdout, "%c%X%s", '[', EM_SETSCROLLPOS,   "]: Rich Edit > Set Scroll Position"               "\r\n"); break;
    case EM_SETSEL        : std::fprintf(stdout, "%c%X%s", '[', EM_SETSEL,         "]: Rich Edit > Set Selection"                     "\r\n"); break;
    case EM_SETTABSTOPS   : std::fprintf(stdout, "%c%X%s", '[', EM_SETTABSTOPS,    "]: Rich Edit > Set Absolute Stops"                "\r\n"); break;
    case EM_SETTARGETDEVICE: /* --> TB_SETHOTITEM */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_SETTARGETDEVICE, "]: {");
        std::fputs("Rich Edit: Set Target Device" "\r\n", stdout);
        std::fputs("Toolbar  : Set Hot Item"      "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_SETTEXTEX: std::fprintf(stdout, "%c%X%s", '[', EM_SETTEXTEX, "]: Rich Edit > Set Text (Extended)" "\r\n"); break;
    case EM_SETTEXTMODE: /* --> TB_GETINSERTMARKCOLOR */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_SETTEXTMODE, "]: {");
        std::fputs("Rich Edit: Set Text Mode"         "\r\n", stdout);
        std::fputs("Toolbar  : Get Insert Mark Color" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_SETTYPOGRAPHYOPTIONS: /* --> IE_GETCOUNT */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_SETTYPOGRAPHYOPTIONS, "]: {");
        std::fputs("Ink Edit : Get Count"              "\r\n", stdout);
        std::fputs("Rich Edit: Set Typography Options" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_SETUNDOLIMIT: /* --> TB_MOVEBUTTON */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_SETUNDOLIMIT, "]: {");
        std::fputs("Rich Edit: Set Undo Limit" "\r\n", stdout);
        std::fputs("Toolbar  : Move Button"    "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_SETVIEWKIND     : std::fprintf(stdout, "%c%X%s", '[', EM_SETVIEWKIND,      "]: Rich Edit > Set View Kind"            "\r\n"); break;
    case EM_SETWORDBREAK    : std::fprintf(stdout, "%c%X%s", '[', EM_SETWORDBREAK,     "]: Rich Edit > Set Word Break"           "\r\n"); break;
    case EM_SETWORDBREAKPROC: std::fprintf(stdout, "%c%X%s", '[', EM_SETWORDBREAKPROC, "]: Rich Edit > Set Word Break Procedure" "\r\n"); break;
    case EM_SETWORDBREAKPROCEX: /* --> TB_INSERTMARKHITTEST */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_SETWORDBREAKPROCEX, "]: {");
        std::fputs("Rich Edit: Set Word Break Procedure (Extended)" "\r\n", stdout);
        std::fputs("Toolbar  : Insert Mark Hit Test"                "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case EM_SETWORDWRAPMODE: break;
    case EM_SETZOOM: /* --> MCIWNDM_GETDEVICEW */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_SETZOOM, "]: {");
        std::fputs("Multimedia (MCI) Window: Get Device" "\r\n", stdout);
        std::fputs("Rich Edit              : Set Zoom"   "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_SHOWSCROLLBAR: std::fprintf(stdout, "%c%X%s", '[', EM_SHOWSCROLLBAR, "]: Rich Edit > Show Scrollbar" "\r\n"); break;
    case EM_STOPGROUPTYPING: /* --> TB_SETINSERTMARKCOLOR */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_STOPGROUPTYPING, "]: {");
        std::fputs("Rich Edit: Stop Group Typing"     "\r\n", stdout);
        std::fputs("Toolbar  : Set Insert Mark Color" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_STREAMIN: /* --> TB_SETANCHORHIGHLIGHT */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_STREAMIN, "]: {");
        std::fputs("Rich Edit: Stream In"            "\r\n", stdout);
        std::fputs("Toolbar  : Set Anchor Highlight" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_STREAMOUT: /* --> TB_GETANCHORHIGHLIGHT */ {
      std::fprintf(stdout, "%c%X%4s", '[', EM_STREAMOUT, "]: {");
        std::fputs("Rich Edit: Stream Out"           "\r\n", stdout);
        std::fputs("Toolbar  : Get Anchor Highlight" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case EM_UNDO: std::fprintf(stdout, "%c%X%s", '[', EM_UNDO, "]: Rich Edit > Undo" "\r\n"); break;

    /* [File Manager] */
    case FM_GETDRIVEINFOA    : std::fprintf(stdout, "%c%X%s", '[', FM_GETDRIVEINFOA,     "]: File Manager > Get Drive Information"       "\r\n"); break;
    case FM_GETDRIVEINFOW    : std::fprintf(stdout, "%c%X%s", '[', FM_GETDRIVEINFOW,     "]: File Manager > Get Drive Information"       "\r\n"); break;
    case FM_GETFILESELA      : std::fprintf(stdout, "%c%X%s", '[', FM_GETFILESELA,       "]: File Manager > Get File Selection"          "\r\n"); break;
    case FM_GETFILESELLFNA   : std::fprintf(stdout, "%c%X%s", '[', FM_GETFILESELLFNA,    "]: File Manager > Get File Selection Function" "\r\n"); break;
    case FM_GETFILESELLFNW   : std::fprintf(stdout, "%c%X%s", '[', FM_GETFILESELLFNW,    "]: File Manager > Get File Selection Function" "\r\n"); break;
    case FM_GETFILESELW      : std::fprintf(stdout, "%c%X%s", '[', FM_GETFILESELW,       "]: File Manager > Get File Selection"          "\r\n"); break;
    case FM_GETFOCUS         : std::fprintf(stdout, "%c%X%s", '[', FM_GETFOCUS,          "]: File Manager > Get Focus"                   "\r\n"); break;
    case FM_GETSELCOUNT      : std::fprintf(stdout, "%c%X%s", '[', FM_GETSELCOUNT,       "]: File Manager > Selection Count"             "\r\n"); break;
    case FM_GETSELCOUNTLFN   : std::fprintf(stdout, "%c%X%s", '[', FM_GETSELCOUNTLFN,    "]: File Manager > Selection Count ..."         "\r\n"); break;
    case FM_REFRESH_WINDOWS  : std::fprintf(stdout, "%c%X%s", '[', FM_REFRESH_WINDOWS,   "]: File Manager > Refresh Windows"             "\r\n"); break;
    case FM_RELOAD_EXTENSIONS: std::fprintf(stdout, "%c%X%s", '[', FM_RELOAD_EXTENSIONS, "]: File Manager > Reload Extensions"           "\r\n"); break;

    /* [Hot Key] */
    // case HKM_GETHOTKEY: break;
    // case HKM_SETHOTKEY: break;
    // case HKM_SETRULES: break;

    /* [Ink Edit] */
    // case IE_DOCOMMAND: break;
    case IE_GETAPPDATA: std::fprintf(stdout, "%c%X%s", '[', IE_GETAPPDATA, "]: Ink Edit > Get Application Data" "\r\n"); break;
    case IE_GETBKGND  : std::fprintf(stdout, "%c%X%s", '[', IE_GETBKGND,   "]: Ink Edit > Get Background"       "\r\n"); break;
    // case IE_GETCOMMAND: break;
    // case IE_GETCOUNT: break;
    case IE_GETDRAWOPTS : std::fprintf(stdout, "%c%X%s", '[', IE_GETDRAWOPTS,  "]: Ink Edit > Get Draw Options" "\r\n"); break;
    case IE_GETERASERTIP: std::fprintf(stdout, "%c%X%s", '[', IE_GETERASERTIP, "]: Ink Edit > Get Eraser Tip"   "\r\n"); break;
    case IE_GETFORMAT   : std::fprintf(stdout, "%c%X%s", '[', IE_GETFORMAT,    "]: Ink Edit > Get Format"       "\r\n"); break;
    // case IE_GETGESTURE: break;
    case IE_GETGRIDORIGIN: std::fprintf(stdout, "%c%X%s", '[', IE_GETGRIDORIGIN, "]: Ink Edit > Get Grid Origin" "\r\n"); break;
    case IE_GETGRIDPEN   : std::fprintf(stdout, "%c%X%s", '[', IE_GETGRIDPEN,    "]: Ink Edit > Get Grid Pen"    "\r\n"); break;
    case IE_GETGRIDSIZE  : std::fprintf(stdout, "%c%X%s", '[', IE_GETGRIDSIZE,   "]: Ink Edit > Get Grid Size"   "\r\n"); break;
    case IE_GETINK: /* --> IE_MSGFIRST | MCIWNDM_PALETTEKICK */ {
      std::fprintf(stdout, "%c%X%4s", '[', IE_GETINK, "]: {");
        std::fputs("Ink Edit               : Get Ink [FIRST]" "\r\n", stdout);
        std::fputs("Multimedia (MCI) Window: Palette Kick"    "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case IE_GETINKINPUT: std::fprintf(stdout, "%c%X%s", '[', IE_GETAPPDATA, "]: Ink Edit > Get Ink Input" "\r\n"); break;
    case IE_GETINKRECT: /* --> WM_CAP_SET_MCI_DEVICEW */ {
      std::fprintf(stdout, "%c%X%4s", '[', IE_GETINKRECT, "]: {");
        std::fputs("Ink Edit       : Get Ink Rectangle"           "\r\n", stdout);
        std::fputs("Windows Capture: Set Multimedia (MCI) Device" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case IE_GETMENU: break;
    case IE_GETMODE  : std::fprintf(stdout, "%c%X%s", '[', IE_GETAPPDATA, "]: Ink Edit > Get Mode"   "\r\n"); break;
    case IE_GETNOTIFY: std::fprintf(stdout, "%c%X%s", '[', IE_GETNOTIFY,  "]: Ink Edit > Get Notify" "\r\n"); break;
    // case IE_GETPAINTDC: break;
    case IE_GETPDEVENT : std::fprintf(stdout, "%c%X%s", '[', IE_GETPDEVENT,  "]: Ink Edit > Get PD Event"        "\r\n"); break;
    case IE_GETPENTIP  : std::fprintf(stdout, "%c%X%s", '[', IE_GETPENTIP,   "]: Ink Edit > Get Pen Tip"         "\r\n"); break;
    case IE_GETRECOG   : std::fprintf(stdout, "%c%X%s", '[', IE_GETRECOG,    "]: Ink Edit > Get Recognition"     "\r\n"); break;
    case IE_GETSECURITY: std::fprintf(stdout, "%c%X%s", '[', IE_GETSECURITY, "]: Ink Edit > Get Security"        "\r\n"); break;
    case IE_GETSEL     : std::fprintf(stdout, "%c%X%s", '[', IE_GETSEL,      "]: Ink Edit > Get Selection"       "\r\n"); break;
    case IE_GETSELCOUNT: std::fprintf(stdout, "%c%X%s", '[', IE_GETSELCOUNT, "]: Ink Edit > Get Selection Count" "\r\n"); break;
    case IE_GETSELITEMS: std::fprintf(stdout, "%c%X%s", '[', IE_GETSELITEMS, "]: Ink Edit > Get Selection Items" "\r\n"); break;
    case IE_GETSTYLE   : std::fprintf(stdout, "%c%X%s", '[', IE_GETSTYLE,    "]: Ink Edit > Get Style"           "\r\n"); break;
    // case IE_MSGFIRST: break;
    case IE_SETAPPDATA   : std::fprintf(stdout, "%c%X%s", '[', IE_SETAPPDATA,    "]: Ink Edit > Set Application Data" "\r\n"); break;
    case IE_SETBKGND     : std::fprintf(stdout, "%c%X%s", '[', IE_SETBKGND,      "]: Ink Edit > Set Background"       "\r\n"); break;
    case IE_SETDRAWOPTS  : std::fprintf(stdout, "%c%X%s", '[', IE_SETDRAWOPTS,   "]: Ink Edit > Set Draw Options"     "\r\n"); break;
    case IE_SETERASERTIP : std::fprintf(stdout, "%c%X%s", '[', IE_SETERASERTIP,  "]: Ink Edit > Set Eraser Tip"       "\r\n"); break;
    case IE_SETFORMAT    : std::fprintf(stdout, "%c%X%s", '[', IE_SETFORMAT,     "]: Ink Edit > Set Format"           "\r\n"); break;
    case IE_SETGRIDORIGIN: std::fprintf(stdout, "%c%X%s", '[', IE_SETGRIDORIGIN, "]: Ink Edit > Set Grid Origin"      "\r\n"); break;
    case IE_SETGRIDPEN   : std::fprintf(stdout, "%c%X%s", '[', IE_SETGRIDPEN,    "]: Ink Edit > Set Grid Pen"         "\r\n"); break;
    case IE_SETGRIDSIZE  : std::fprintf(stdout, "%c%X%s", '[', IE_SETGRIDSIZE,   "]: Ink Edit > Set Grid Size"        "\r\n"); break;
    case IE_SETINK       : std::fprintf(stdout, "%c%X%s", '[', IE_SETINK,        "]: Ink Edit > Set Ink"              "\r\n"); break;
    case IE_SETINKINPUT  : std::fprintf(stdout, "%c%X%s", '[', IE_SETINKINPUT,   "]: Ink Edit > Set Ink Input"        "\r\n"); break;
    case IE_SETMODE      : std::fprintf(stdout, "%c%X%s", '[', IE_SETMODE,       "]: Ink Edit > Set Mode"             "\r\n"); break;
    case IE_SETNOTIFY    : std::fprintf(stdout, "%c%X%s", '[', IE_SETNOTIFY,     "]: Ink Edit > Set Notify"           "\r\n"); break;
    case IE_SETPENTIP    : std::fprintf(stdout, "%c%X%s", '[', IE_SETPENTIP,     "]: Ink Edit > Set Pen Tip"          "\r\n"); break;
    case IE_SETRECOG     : std::fprintf(stdout, "%c%X%s", '[', IE_SETRECOG,      "]: Ink Edit > Set Recognition"      "\r\n"); break;
    case IE_SETSECURITY  : std::fprintf(stdout, "%c%X%s", '[', IE_SETSECURITY,   "]: Ink Edit > Set Security"         "\r\n"); break;
    case IE_SETSEL       : std::fprintf(stdout, "%c%X%s", '[', IE_SETSEL,        "]: Ink Edit > Set Selection"        "\r\n"); break;

    /* [Internet Protocol] */
    // case IPM_CLEARADDRESS: break;
    // case IPM_GETADDRESS  : break;
    // case IPM_ISBLANK     : break;
    // case IPM_SETADDRESS  : break;
    // case IPM_SETFOCUS    : break;
    // case IPM_SETRANGE    : break;

    /* [List View] */
    // case LVM_APPROXIMATEVIEWRECT: break;
    case LVM_ARRANGE        : std::fprintf(stdout, "%c%X%s", '[', LVM_ARRANGE,         "]: List View > Arrange"                           "\r\n"); break;
    case LVM_CANCELEDITLABEL: std::fprintf(stdout, "%c%X%s", '[', LVM_CANCELEDITLABEL, "]: List View > Cancel Edit Label"                 "\r\n"); break;
    case LVM_CREATEDRAGIMAGE: std::fprintf(stdout, "%c%X%s", '[', LVM_CREATEDRAGIMAGE, "]: List View > Create Drag Image"                 "\r\n"); break;
    case LVM_DELETEALLITEMS : std::fprintf(stdout, "%c%X%s", '[', LVM_DELETEALLITEMS,  "]: List View > Delete All Items"                  "\r\n"); break;
    case LVM_DELETECOLUMN   : std::fprintf(stdout, "%c%X%s", '[', LVM_DELETECOLUMN,    "]: List View > Delete Column"                     "\r\n"); break;
    case LVM_DELETEITEM     : std::fprintf(stdout, "%c%X%s", '[', LVM_DELETEITEM,      "]: List View > Delete Item"                       "\r\n"); break;
    case LVM_EDITLABELA     : std::fprintf(stdout, "%c%X%s", '[', LVM_EDITLABELA,      "]: List View > Edit Label"                        "\r\n"); break;
    case LVM_EDITLABELW     : std::fprintf(stdout, "%c%X%s", '[', LVM_EDITLABELW,      "]: List View > Edit Label"                        "\r\n"); break;
    case LVM_ENABLEGROUPVIEW: std::fprintf(stdout, "%c%X%s", '[', LVM_ENABLEGROUPVIEW, "]: List View > Enable Group View"                 "\r\n"); break;
    case LVM_ENSUREVISIBLE  : std::fprintf(stdout, "%c%X%s", '[', LVM_ENSUREVISIBLE,   "]: List View > Ensure Visible"                    "\r\n"); break;
    case LVM_FINDITEMA      : std::fprintf(stdout, "%c%X%s", '[', LVM_FINDITEMA,       "]: List View > Find Item"                         "\r\n"); break;
    case LVM_FINDITEMW      : std::fprintf(stdout, "%c%X%s", '[', LVM_FINDITEMW,       "]: List View > Find Item"                         "\r\n"); break;
    case LVM_FIRST: /* --> LVM_GETBKCOLOR */ std::fprintf(stdout, "%c%X%s", '[', LVM_FIRST, "]: List View > Get Background Color [FIRST]" "\r\n"); break;
    // case LVM_GETBKCOLOR: break;
    case LVM_GETBKIMAGEA             : std::fprintf(stdout, "%c%X%s", '[', LVM_GETBKIMAGEA,              "]: List View > Get Background Image"          "\r\n"); break;
    case LVM_GETBKIMAGEW             : std::fprintf(stdout, "%c%X%s", '[', LVM_GETBKIMAGEW,              "]: List View > Get Background Image"          "\r\n"); break;
    case LVM_GETCALLBACKMASK         : std::fprintf(stdout, "%c%X%s", '[', LVM_GETCALLBACKMASK,          "]: List View > Get Call Back Mask"            "\r\n"); break;
    case LVM_GETCOLUMNA              : std::fprintf(stdout, "%c%X%s", '[', LVM_GETCOLUMNA,               "]: List View > Get Column"                    "\r\n"); break;
    case LVM_GETCOLUMNORDERARRAY     : std::fprintf(stdout, "%c%X%s", '[', LVM_GETCOLUMNORDERARRAY,      "]: List View > Get Column Order Array"        "\r\n"); break;
    case LVM_GETCOLUMNW              : std::fprintf(stdout, "%c%X%s", '[', LVM_GETCOLUMNW,               "]: List View > Get Column"                    "\r\n"); break;
    case LVM_GETCOLUMNWIDTH          : std::fprintf(stdout, "%c%X%s", '[', LVM_GETCOLUMNWIDTH,           "]: List View > Get Column Width"              "\r\n"); break;
    case LVM_GETCOUNTPERPAGE         : std::fprintf(stdout, "%c%X%s", '[', LVM_GETCOUNTPERPAGE,          "]: List View > Get Count per Page"            "\r\n"); break;
    case LVM_GETEDITCONTROL          : std::fprintf(stdout, "%c%X%s", '[', LVM_GETEDITCONTROL,           "]: List View > Get Edit Control"              "\r\n"); break;
    case LVM_GETEXTENDEDLISTVIEWSTYLE: std::fprintf(stdout, "%c%X%s", '[', LVM_GETEXTENDEDLISTVIEWSTYLE, "]: List View > Get Extended List View Style"  "\r\n"); break;
    case LVM_GETGROUPINFO            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETGROUPINFO,             "]: List View > Get Group Information"         "\r\n"); break;
    case LVM_GETGROUPMETRICS         : std::fprintf(stdout, "%c%X%s", '[', LVM_GETGROUPMETRICS,          "]: List View > Get Group Metrics"             "\r\n"); break;
    case LVM_GETHEADER               : std::fprintf(stdout, "%c%X%s", '[', LVM_GETHEADER,                "]: List View > Get Header"                    "\r\n"); break;
    case LVM_GETHOTCURSOR            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETHOTCURSOR,             "]: List View > Get Hot Cursor"                "\r\n"); break;
    case LVM_GETHOTITEM              : std::fprintf(stdout, "%c%X%s", '[', LVM_GETHOTITEM,               "]: List View > Get Hover Time"                "\r\n"); break;
    case LVM_GETHOVERTIME            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETHOVERTIME,             "]: List View > Get Image List"                "\r\n"); break;
    case LVM_GETIMAGELIST            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETIMAGELIST,             "]: List View > Get Image List"                "\r\n"); break;
    case LVM_GETINSERTMARK           : std::fprintf(stdout, "%c%X%s", '[', LVM_GETINSERTMARK,            "]: List View > Get Insert Mark"               "\r\n"); break;
    case LVM_GETINSERTMARKCOLOR      : std::fprintf(stdout, "%c%X%s", '[', LVM_GETINSERTMARKCOLOR,       "]: List View > Get Insert Mark Color"         "\r\n"); break;
    case LVM_GETINSERTMARKRECT       : std::fprintf(stdout, "%c%X%s", '[', LVM_GETINSERTMARKRECT,        "]: List View > Get Insert Mark Rectangle"     "\r\n"); break;
    case LVM_GETISEARCHSTRINGA       : std::fprintf(stdout, "%c%X%s", '[', LVM_GETISEARCHSTRINGA,        "]: List View > Get Incremental Search String" "\r\n"); break;
    case LVM_GETISEARCHSTRINGW       : std::fprintf(stdout, "%c%X%s", '[', LVM_GETISEARCHSTRINGW,        "]: List View > Get Incremental Search String" "\r\n"); break;
    case LVM_GETITEMA                : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMA,                 "]: List View > Get Item"                      "\r\n"); break;
    case LVM_GETITEMCOUNT            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMCOUNT,             "]: List View > Get Item Count"                "\r\n"); break;
    case LVM_GETITEMPOSITION         : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMPOSITION,          "]: List View > Get Item Position"             "\r\n"); break;
    case LVM_GETITEMRECT             : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMRECT,              "]: List View > Get Item Rectangle"            "\r\n"); break;
    case LVM_GETITEMSPACING          : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMSPACING,           "]: List View > Get Item Spacing"              "\r\n"); break;
    case LVM_GETITEMSTATE            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMSTATE,             "]: List View > Get Item State"                "\r\n"); break;
    case LVM_GETITEMTEXTA            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMTEXTA,             "]: List View > Get Item Text"                 "\r\n"); break;
    case LVM_GETITEMTEXTW            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMTEXTW,             "]: List View > Get Item Text"                 "\r\n"); break;
    case LVM_GETITEMW                : std::fprintf(stdout, "%c%X%s", '[', LVM_GETITEMW,                 "]: List View > Get Item"                      "\r\n"); break;
    case LVM_GETNEXTITEM             : std::fprintf(stdout, "%c%X%s", '[', LVM_GETNEXTITEM,              "]: List View > Get Next Item"                 "\r\n"); break;
    case LVM_GETNUMBEROFWORKAREAS    : std::fprintf(stdout, "%c%X%s", '[', LVM_GETNUMBEROFWORKAREAS,     "]: List View > Get Number of Work Areas"      "\r\n"); break;
    case LVM_GETORIGIN               : std::fprintf(stdout, "%c%X%s", '[', LVM_GETORIGIN,                "]: List View > Get Origin"                    "\r\n"); break;
    case LVM_GETOUTLINECOLOR         : std::fprintf(stdout, "%c%X%s", '[', LVM_GETOUTLINECOLOR,          "]: List View > Get Outline Color"             "\r\n"); break;
    case LVM_GETSELECTEDCOLUMN       : std::fprintf(stdout, "%c%X%s", '[', LVM_GETSELECTEDCOLUMN,        "]: List View > Get Selected Column"           "\r\n"); break;
    case LVM_GETSELECTEDCOUNT        : std::fprintf(stdout, "%c%X%s", '[', LVM_GETSELECTEDCOUNT,         "]: List View > Get Selected Count"            "\r\n"); break;
    case LVM_GETSELECTIONMARK        : std::fprintf(stdout, "%c%X%s", '[', LVM_GETSELECTIONMARK,         "]: List View > Get Selection Mark"            "\r\n"); break;
    case LVM_GETSTRINGWIDTHA         : std::fprintf(stdout, "%c%X%s", '[', LVM_GETSTRINGWIDTHA,          "]: List View > Get String Width"              "\r\n"); break;
    case LVM_GETSTRINGWIDTHW         : std::fprintf(stdout, "%c%X%s", '[', LVM_GETSTRINGWIDTHW,          "]: List View > Get String Width"              "\r\n"); break;
    case LVM_GETSUBITEMRECT          : std::fprintf(stdout, "%c%X%s", '[', LVM_GETSUBITEMRECT,           "]: List View > Get Sub-Item Rectangle"        "\r\n"); break;
    case LVM_GETTEXTBKCOLOR          : std::fprintf(stdout, "%c%X%s", '[', LVM_GETTEXTBKCOLOR,           "]: List View > Get Text Background Color"     "\r\n"); break;
    case LVM_GETTEXTCOLOR            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETTEXTCOLOR,             "]: List View > Get Text Color"                "\r\n"); break;
    case LVM_GETTILEINFO             : std::fprintf(stdout, "%c%X%s", '[', LVM_GETTILEINFO,              "]: List View > Get Tile Information"          "\r\n"); break;
    case LVM_GETTILEVIEWINFO         : std::fprintf(stdout, "%c%X%s", '[', LVM_GETTILEVIEWINFO,          "]: List View > Get Tile View Information"     "\r\n"); break;
    case LVM_GETTOOLTIPS             : std::fprintf(stdout, "%c%X%s", '[', LVM_GETTOOLTIPS,              "]: List View > Get Tooltips"                  "\r\n"); break;
    case LVM_GETTOPINDEX             : std::fprintf(stdout, "%c%X%s", '[', LVM_GETTOPINDEX,              "]: List View > Get Top Index"                 "\r\n"); break;
    case LVM_GETUNICODEFORMAT        : std::fprintf(stdout, "%c%X%s", '[', LVM_GETUNICODEFORMAT,         "]: List View > Get Unicode Format"            "\r\n"); break;
    case LVM_GETVIEW                 : std::fprintf(stdout, "%c%X%s", '[', LVM_GETVIEW,                  "]: List View > Get View"                      "\r\n"); break;
    case LVM_GETVIEWRECT             : std::fprintf(stdout, "%c%X%s", '[', LVM_GETVIEWRECT,              "]: List View > Get View Rectangle"            "\r\n"); break;
    case LVM_GETWORKAREAS            : std::fprintf(stdout, "%c%X%s", '[', LVM_GETWORKAREAS,             "]: List View > Get Work Areas"                "\r\n"); break;
    case LVM_HASGROUP                : std::fprintf(stdout, "%c%X%s", '[', LVM_HASGROUP,                 "]: List View > Has Group"                     "\r\n"); break;
    case LVM_HITTEST                 : std::fprintf(stdout, "%c%X%s", '[', LVM_HITTEST,                  "]: List View > Hit Test"                      "\r\n"); break;
    case LVM_INSERTCOLUMNA           : std::fprintf(stdout, "%c%X%s", '[', LVM_INSERTCOLUMNA,            "]: List View > Insert Column"                 "\r\n"); break;
    case LVM_INSERTCOLUMNW           : std::fprintf(stdout, "%c%X%s", '[', LVM_INSERTCOLUMNW,            "]: List View > Insert Column"                 "\r\n"); break;
    case LVM_INSERTGROUP             : std::fprintf(stdout, "%c%X%s", '[', LVM_INSERTGROUP,              "]: List View > Insert Group"                  "\r\n"); break;
    case LVM_INSERTGROUPSORTED       : std::fprintf(stdout, "%c%X%s", '[', LVM_INSERTGROUPSORTED,        "]: List View > Insert Group Sorted"           "\r\n"); break;
    case LVM_INSERTITEMA             : std::fprintf(stdout, "%c%X%s", '[', LVM_INSERTITEMA,              "]: List View > Insert Item"                   "\r\n"); break;
    case LVM_INSERTITEMW             : std::fprintf(stdout, "%c%X%s", '[', LVM_INSERTITEMW,              "]: List View > Insert Item"                   "\r\n"); break;
    case LVM_INSERTMARKHITTEST       : std::fprintf(stdout, "%c%X%s", '[', LVM_INSERTMARKHITTEST,        "]: List View > Insert Mark Hit Test"          "\r\n"); break;
    case LVM_ISGROUPVIEWENABLED      : std::fprintf(stdout, "%c%X%s", '[', LVM_ISGROUPVIEWENABLED,       "]: List View > Is Group View Enabled"         "\r\n"); break;
    case LVM_ISITEMVISIBLE           : std::fprintf(stdout, "%c%X%s", '[', LVM_ISITEMVISIBLE,            "]: List View > Is Item Visible"               "\r\n"); break;
    case LVM_MAPIDTOINDEX            : std::fprintf(stdout, "%c%X%s", '[', LVM_MAPIDTOINDEX,             "]: List View > Map Identity to Index"         "\r\n"); break;
    case LVM_MAPINDEXTOID            : std::fprintf(stdout, "%c%X%s", '[', LVM_MAPINDEXTOID,             "]: List View > Map Index to Identity"         "\r\n"); break;
    case LVM_MOVEGROUP               : std::fprintf(stdout, "%c%X%s", '[', LVM_MOVEGROUP,                "]: List View > Move Group"                    "\r\n"); break;
    case LVM_MOVEITEMTOGROUP         : std::fprintf(stdout, "%c%X%s", '[', LVM_MOVEITEMTOGROUP,          "]: List View > Move Item to Group"            "\r\n"); break;
    case LVM_REDRAWITEMS             : std::fprintf(stdout, "%c%X%s", '[', LVM_REDRAWITEMS,              "]: List View > Redraw Items"                  "\r\n"); break;
    case LVM_REMOVEALLGROUPS         : std::fprintf(stdout, "%c%X%s", '[', LVM_REMOVEALLGROUPS,          "]: List View > Remove all Groups"             "\r\n"); break;
    case LVM_REMOVEGROUP             : std::fprintf(stdout, "%c%X%s", '[', LVM_REMOVEGROUP,              "]: List View > Remove Group"                  "\r\n"); break;
    case LVM_SCROLL                  : std::fprintf(stdout, "%c%X%s", '[', LVM_SCROLL,                   "]: List View > Scroll"                        "\r\n"); break;
    case LVM_SETBKCOLOR              : std::fprintf(stdout, "%c%X%s", '[', LVM_SETBKCOLOR,               "]: List View > Set Background Color"          "\r\n"); break;
    case LVM_SETBKIMAGEA             : std::fprintf(stdout, "%c%X%s", '[', LVM_SETBKIMAGEA,              "]: List View > Set Background Image"          "\r\n"); break;
    case LVM_SETCALLBACKMASK         : std::fprintf(stdout, "%c%X%s", '[', LVM_SETCALLBACKMASK,          "]: List View > Set Callback Mask"             "\r\n"); break;
    case LVM_SETCOLUMNA              : std::fprintf(stdout, "%c%X%s", '[', LVM_SETCOLUMNA,               "]: List View > Set Column"                    "\r\n"); break;
    case LVM_SETCOLUMNORDERARRAY     : std::fprintf(stdout, "%c%X%s", '[', LVM_SETCOLUMNORDERARRAY,      "]: List View > Set Column Order Array"        "\r\n"); break;
    case LVM_SETCOLUMNW              : std::fprintf(stdout, "%c%X%s", '[', LVM_SETCOLUMNW,               "]: List View > Set Column"                    "\r\n"); break;
    case LVM_SETCOLUMNWIDTH          : std::fprintf(stdout, "%c%X%s", '[', LVM_SETCOLUMNWIDTH,           "]: List View > Set Column Width"              "\r\n"); break;
    case LVM_SETEXTENDEDLISTVIEWSTYLE: std::fprintf(stdout, "%c%X%s", '[', LVM_SETEXTENDEDLISTVIEWSTYLE, "]: List View > Set Extended List View Style"  "\r\n"); break;
    case LVM_SETGROUPINFO            : std::fprintf(stdout, "%c%X%s", '[', LVM_SETGROUPINFO,             "]: List View > Set Group Information"         "\r\n"); break;
    case LVM_SETGROUPMETRICS         : std::fprintf(stdout, "%c%X%s", '[', LVM_SETGROUPMETRICS,          "]: List View > Set Group Metrics"             "\r\n"); break;
    case LVM_SETHOTCURSOR: /* --> LVM_SETHOTITEM */ {
      std::fprintf(stdout, "%c%X%4s", '[', LVM_SETHOTCURSOR, "]: {");
        std::fputs("List View: Set Hot Cursor" "\r\n", stdout);
        std::fputs("List View: Set Hot Item"   "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case LVM_SETHOTITEM: break;
    case LVM_SETHOVERTIME      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETHOVERTIME,       "]: List View > Set Hover Time"             "\r\n"); break;
    case LVM_SETICONSPACING    : std::fprintf(stdout, "%c%X%s", '[', LVM_SETICONSPACING,     "]: List View > Set Icon Spacing"           "\r\n"); break;
    case LVM_SETIMAGELIST      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETIMAGELIST,       "]: List View > Set Image List"             "\r\n"); break;
    case LVM_SETINFOTIP        : std::fprintf(stdout, "%c%X%s", '[', LVM_SETINFOTIP,         "]: List View > Set Information Tip"        "\r\n"); break;
    case LVM_SETINSERTMARK     : std::fprintf(stdout, "%c%X%s", '[', LVM_SETINSERTMARK,      "]: List View > Set Insert Mark"            "\r\n"); break;
    case LVM_SETINSERTMARKCOLOR: std::fprintf(stdout, "%c%X%s", '[', LVM_SETINSERTMARKCOLOR, "]: List View > Set Insert Mark Color"      "\r\n"); break;
    case LVM_SETITEMA          : std::fprintf(stdout, "%c%X%s", '[', LVM_SETITEMA,           "]: List View > Set Item"                   "\r\n"); break;
    case LVM_SETITEMCOUNT      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETITEMCOUNT,       "]: List View > Set Item Count"             "\r\n"); break;
    case LVM_SETITEMPOSITION   : std::fprintf(stdout, "%c%X%s", '[', LVM_SETITEMPOSITION,    "]: List View > Set Item Position"          "\r\n"); break;
    case LVM_SETITEMPOSITION32 : std::fprintf(stdout, "%c%X%s", '[', LVM_SETITEMPOSITION32,  "]: List View > Set Item Position (32-Bit)" "\r\n"); break;
    case LVM_SETITEMSTATE      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETITEMSTATE,       "]: List View > Set Item State"             "\r\n"); break;
    case LVM_SETITEMTEXTA      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETITEMTEXTA,       "]: List View > Set Item Text"              "\r\n"); break;
    case LVM_SETITEMTEXTW      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETITEMTEXTW,       "]: List View > Set Item Text"              "\r\n"); break;
    case LVM_SETITEMW          : std::fprintf(stdout, "%c%X%s", '[', LVM_SETITEMW,           "]: List View > Set Item"                   "\r\n"); break;
    case LVM_SETOUTLINECOLOR   : std::fprintf(stdout, "%c%X%s", '[', LVM_SETOUTLINECOLOR,    "]: List View > Set Outline Color"          "\r\n"); break;
    case LVM_SETSELECTEDCOLUMN : std::fprintf(stdout, "%c%X%s", '[', LVM_SETSELECTEDCOLUMN,  "]: List View > Set Selected Column"        "\r\n"); break;
    case LVM_SETSELECTIONMARK  : std::fprintf(stdout, "%c%X%s", '[', LVM_SETSELECTIONMARK,   "]: List View > Set Selection Mark"         "\r\n"); break;
    case LVM_SETTEXTBKCOLOR    : std::fprintf(stdout, "%c%X%s", '[', LVM_SETTEXTBKCOLOR,     "]: List View > Set Text Background Color"  "\r\n"); break;
    case LVM_SETTEXTCOLOR      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETTEXTCOLOR,       "]: List View > Set Text Color"             "\r\n"); break;
    case LVM_SETTILEINFO       : std::fprintf(stdout, "%c%X%s", '[', LVM_SETTILEINFO,        "]: List View > Set Tile Information"       "\r\n"); break;
    case LVM_SETTILEVIEWINFO   : std::fprintf(stdout, "%c%X%s", '[', LVM_SETTILEVIEWINFO,    "]: List View > Set Tile View Information"  "\r\n"); break;
    case LVM_SETTILEWIDTH      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETTILEWIDTH,       "]: List View > Set Tile Width"             "\r\n"); break;
    case LVM_SETTOOLTIPS       : std::fprintf(stdout, "%c%X%s", '[', LVM_SETTOOLTIPS,        "]: List View > Set Tooltips"               "\r\n"); break;
    case LVM_SETUNICODEFORMAT  : std::fprintf(stdout, "%c%X%s", '[', LVM_SETUNICODEFORMAT,   "]: List View > Set Unicode Format"         "\r\n"); break;
    case LVM_SETVIEW           : std::fprintf(stdout, "%c%X%s", '[', LVM_SETVIEW,            "]: List View > Set View"                   "\r\n"); break;
    case LVM_SETWORKAREAS      : std::fprintf(stdout, "%c%X%s", '[', LVM_SETWORKAREAS,       "]: List View > Set WorkaAreas"             "\r\n"); break;
    case LVM_SORTGROUPS        : std::fprintf(stdout, "%c%X%s", '[', LVM_SORTGROUPS,         "]: List View > Sort Groups"                "\r\n"); break;
    case LVM_SORTITEMS         : std::fprintf(stdout, "%c%X%s", '[', LVM_SORTITEMS,          "]: List View > Sort Items"                 "\r\n"); break;
    case LVM_SUBITEMHITTEST    : std::fprintf(stdout, "%c%X%s", '[', LVM_SUBITEMHITTEST,     "]: List View > Sub-Item Hit Test"          "\r\n"); break;
    case LVM_UPDATE            : std::fprintf(stdout, "%c%X%s", '[', LVM_UPDATE,             "]: List View > Update"                     "\r\n"); break;

    /* [Multimedia MCI Window] */
    case MCIWNDM_CAN_CONFIG: std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_CAN_CONFIG, "]: Multimedia (MCI) Window > Can Configure" "\r\n"); break;
    case MCIWNDM_CAN_EJECT : std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_CAN_EJECT,  "]: Multimedia (MCI) Window > Can Eject"     "\r\n"); break;
    case MCIWNDM_CAN_PLAY  : std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_CAN_PLAY,   "]: Multimedia (MCI) Window > Can Play"      "\r\n"); break;
    case MCIWNDM_CAN_RECORD: std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_CAN_RECORD, "]: Multimedia (MCI) Window > Can Record"    "\r\n"); break;
    case MCIWNDM_CAN_SAVE  : std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_CAN_SAVE,   "]: Multimedia (MCI) Window > Can Save"      "\r\n"); break;
    case MCIWNDM_CAN_WINDOW: std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_CAN_WINDOW, "]: Multimedia (MCI) Window > Can Window"    "\r\n"); break;
    // case MCIWNDM_GETDEVICEA: break;
    // case MCIWNDM_GETDEVICEW: break;
    case MCIWNDM_GETERRORA: /* --> PSM_SETHEADERSUBTITLEW */ {
      std::fprintf(stdout, "%c%X%4s", '[', MCIWNDM_GETERRORA, "]: {");
        std::fputs("Multimedia (MCI) Window: Get Error"           "\r\n", stdout);
        std::fputs("Prop Sheet             : Set Header Subtitle" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case MCIWNDM_GETERRORW       : break;
    // case MCIWNDM_GETFILENAMEA    : break;
    // case MCIWNDM_GETFILENAMEW    : break;
    // case MCIWNDM_GETINACTIVETIMER: break;
    // case MCIWNDM_GETPALETTE      : break;
    // case MCIWNDM_GETTIMEFORMATA  : break;
    // case MCIWNDM_GETTIMEFORMATW  : break;
    case MCIWNDM_GETZOOM: /* --> PSM_UNCHANGED | UDM_SETBASE */ {
      std::fprintf(stdout, "%c%X%4s", '[', MCIWNDM_GETERRORA, "]: {");
        std::fputs("Multimedia (MCI) Window: Get Zoom"  "\r\n", stdout);
        std::fputs("Prop Sheet             : Unchanged" "\r\n", stdout);
        std::fputs("Up-Down Control        : Set Base"  "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case MCIWNDM_GET_DEST  : std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_GET_DEST,   "]: Multimedia (MCI) Window > Get Destination" "\r\n"); break;
    case MCIWNDM_GET_SOURCE: std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_GET_SOURCE, "]: Multimedia (MCI) Window > Get Source"      "\r\n"); break;
    // case MCIWNDM_NOTIFYERROR: break;
    // case MCIWNDM_NOTIFYMEDIA: break;
    // case MCIWNDM_NOTIFYMODE: break;
    // case MCIWNDM_PALETTEKICK: break;
    // case MCIWNDM_PLAYTO: break;
    case MCIWNDM_PUT_DEST  : std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_PUT_DEST,   "]: Multimedia (MCI) Window > Put Destination" "\r\n"); break;
    case MCIWNDM_PUT_SOURCE: std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_PUT_SOURCE, "]: Multimedia (MCI) Window > Put Source"      "\r\n"); break;
    case MCIWNDM_REALIZE: /* --> PSM_GETCURRENTPAGEHWND */ {
      std::fprintf(stdout, "%c%X%4s", '[', MCIWNDM_REALIZE, "]: {");
        std::fputs("Multimedia (MCI) Window: Realize"                        "\r\n", stdout);
        std::fputs("Prop Sheet             : Get Current Page Window Handle" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case MCIWNDM_SETINACTIVETIMER: /* --> PSM_PAGETOINDEX */ {
      std::fprintf(stdout, "%c%X%4s", '[', MCIWNDM_SETINACTIVETIMER, "]: {");
        std::fputs("Multimedia (MCI) Window: Set Inactive Timer" "\r\n", stdout);
        std::fputs("Prop Sheet             : Page to Index"      "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case MCIWNDM_SETPALETTE: break;
    case MCIWNDM_SETTIMEFORMATA: /* --> PSM_INSERTPAGE */ {
      std::fprintf(stdout, "%c%X%4s", '[', MCIWNDM_SETTIMEFORMATA, "]: {");
        std::fputs("Multimedia (MCI) Window: Set Time Format" "\r\n", stdout);
        std::fputs("Prop Sheet             : Insert Page"     "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case MCIWNDM_SETTIMEFORMATW: std::fprintf(stdout, "%c%X%s", '[', MCIWNDM_SETTIMEFORMATW, "]: Multimedia (MCI) Window > Set Time Format" "\r\n"); break;
    // case MCIWNDM_VALIDATEMEDIA: break;

    /* [...] */
    case MSG_FTS_JUMP_QWORD: /* --> RB_SHOWBAND | TB_GETTOOLTIPS */ {
      std::fprintf(stdout, "%c%X%4s", '[', MSG_FTS_JUMP_QWORD, "]: {");
        std::fputs("... Jump ..."          "\r\n", stdout);
        std::fputs("Rebar  : Show Band"    "\r\n", stdout);
        std::fputs("Toolbar: Get Tooltips" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case MSG_FTS_JUMP_VA: /* --> TBM_GETBUDDY | TB_AUTOSIZE | TTM_SETTITLEW */ {
      std::fprintf(stdout, "%c%X%4s", '[', MSG_FTS_JUMP_VA, "]: {");
        std::fputs("... Jump ..."        "\r\n", stdout);
        std::fputs("Toolbar : Auto Size" "\r\n", stdout);
        std::fputs("Tooltip : Set Title" "\r\n", stdout);
        std::fputs("Trackbar: Get Buddy" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case MSG_FTS_WHERE_IS_IT: /* --> RB_SETPALETTE | TB_SETPARENT */ {
      std::fprintf(stdout, "%c%X%4s", '[', MSG_FTS_WHERE_IS_IT, "]: {");
        std::fputs("Rebar  : Set Palette" "\r\n", stdout);
        std::fputs("Toolbar: Set Parent"  "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case MSG_GET_DEFFONT: /* --> TB_GETBUTTONTEXTA */ {
      std::fprintf(stdout, "%c%X%4s", '[', MSG_GET_DEFFONT, "]: {");
        std::fputs("Get Default Font"         "\r\n", stdout);
        std::fputs("Toolbar: Get Button Text" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case MSG_REINDEX_REQUEST: /* --> TB_SETTOOLTIPS */ {
      std::fprintf(stdout, "%c%X%4s", '[', MSG_REINDEX_REQUEST, "]: {");
        std::fputs("Re-Index Request"      "\r\n", stdout);
        std::fputs("Toolbar: Set Tooltips" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;

    /* [Object Linking & Embedding] */
    // case NIN_SELECT: break;
    case OCM_CHARTOITEM       : std::fprintf(stdout, "%c%X%s", '[', OCM_CHARTOITEM,        "]: Object Linking & Embedding Control > Character To Item"         "\r\n"); break;
    case OCM_COMMAND          : std::fprintf(stdout, "%c%X%s", '[', OCM_COMMAND,           "]: Object Linking & Embedding Control > Command"                   "\r\n"); break;
    case OCM_COMPAREITEM      : std::fprintf(stdout, "%c%X%s", '[', OCM_COMPAREITEM,       "]: Object Linking & Embedding Control > Compare Item"              "\r\n"); break;
    case OCM_CTLCOLOR         : std::fprintf(stdout, "%c%X%s", '[', OCM_CTLCOLOR,          "]: Object Linking & Embedding Control > Control Color"             "\r\n"); break;
    case OCM_CTLCOLORBTN      : std::fprintf(stdout, "%c%X%s", '[', OCM_CTLCOLORBTN,       "]: Object Linking & Embedding Control > Control Color Button"      "\r\n"); break;
    case OCM_CTLCOLORDLG      : std::fprintf(stdout, "%c%X%s", '[', OCM_CTLCOLORDLG,       "]: Object Linking & Embedding Control > Control Color Dialog"      "\r\n"); break;
    case OCM_CTLCOLOREDIT     : std::fprintf(stdout, "%c%X%s", '[', OCM_CTLCOLOREDIT,      "]: Object Linking & Embedding Control > Control Color Edit"        "\r\n"); break;
    case OCM_CTLCOLORLISTBOX  : std::fprintf(stdout, "%c%X%s", '[', OCM_CTLCOLORLISTBOX,   "]: Object Linking & Embedding Control > Control Color List Box"    "\r\n"); break;
    case OCM_CTLCOLORMSGBOX   : std::fprintf(stdout, "%c%X%s", '[', OCM_CTLCOLORMSGBOX,    "]: Object Linking & Embedding Control > Control Color Message Box" "\r\n"); break;
    case OCM_CTLCOLORSCROLLBAR: std::fprintf(stdout, "%c%X%s", '[', OCM_CTLCOLORSCROLLBAR, "]: Object Linking & Embedding Control > Control Color Scrollbar"   "\r\n"); break;
    case OCM_CTLCOLORSTATIC   : std::fprintf(stdout, "%c%X%s", '[', OCM_CTLCOLORSTATIC,    "]: Object Linking & Embedding Control > Control Color Static"      "\r\n"); break;
    case OCM_DELETEITEM       : std::fprintf(stdout, "%c%X%s", '[', OCM_DELETEITEM,        "]: Object Linking & Embedding Control > Delete Item"               "\r\n"); break;
    case OCM_DRAWITEM         : std::fprintf(stdout, "%c%X%s", '[', OCM_DRAWITEM,          "]: Object Linking & Embedding Control > Draw Item"                 "\r\n"); break;
    case OCM_HSCROLL          : std::fprintf(stdout, "%c%X%s", '[', OCM_HSCROLL,           "]: Object Linking & Embedding Control > Horizontal Scroll"         "\r\n"); break;
    case OCM_MEASUREITEM      : std::fprintf(stdout, "%c%X%s", '[', OCM_MEASUREITEM,       "]: Object Linking & Embedding Control > Measure Item"              "\r\n"); break;
    case OCM_NOTIFY           : std::fprintf(stdout, "%c%X%s", '[', OCM_NOTIFY,            "]: Object Linking & Embedding Control > Notify"                    "\r\n"); break;
    case OCM_PARENTNOTIFY     : std::fprintf(stdout, "%c%X%s", '[', OCM_PARENTNOTIFY,      "]: Object Linking & Embedding Control > Parent Notify"             "\r\n"); break;
    case OCM_VKEYTOITEM       : std::fprintf(stdout, "%c%X%s", '[', OCM_VKEYTOITEM,        "]: Object Linking & Embedding Control > Virtual Key to Item"       "\r\n"); break;
    case OCM_VSCROLL          : std::fprintf(stdout, "%c%X%s", '[', OCM_VSCROLL,           "]: Object Linking & Embedding Control > Vertical Scroll"           "\r\n"); break;
    case OCM__BASE            : std::fprintf(stdout, "%c%X%s", '[', OCM__BASE,             "]: Object Linking & Embedding Control > Base"                      "\r\n"); break;

    /* [Prop Sheet] */
    // case PBM_DELTAPOS   : break;
    // case PBM_GETPOS     : break;
    // case PBM_GETRANGE   : break;
    // case PBM_SETBARCOLOR: break;
    // case PBM_SETPOS     : break;
    // case PBM_SETRANGE   : break;
    // case PBM_SETRANGE32 : break;
    // case PBM_SETSTEP    : break;
    // case PBM_STEPIT     : break;
    // case PSM_ADDPAGE    : break;
    case PSM_APPLY: /* --> UDM_GETBASE */ {
      std::fprintf(stdout, "%c%X%4s", '[', PSM_APPLY, "]: {");
        std::fputs("Prop Sheet     : Apply"    "\r\n", stdout);
        std::fputs("Up-Down Control: Get Base" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case PSM_CANCELTOCLOSE: break;
    // case PSM_CHANGED: break;
    // case PSM_GETCURRENTPAGEHWND: break;
    // case PSM_GETRESULT: break;
    case PSM_GETTABCONTROL: std::fprintf(stdout, "%c%X%s", '[', PSM_GETTABCONTROL, "]: Prop Sheet > Get Tab Control"        "\r\n"); break;
    case PSM_HWNDTOINDEX  : std::fprintf(stdout, "%c%X%s", '[', PSM_HWNDTOINDEX,   "]: Prop Sheet > Window Handle to Index" "\r\n"); break;
    // case PSM_IDTOINDEX: break;
    case PSM_INDEXTOHWND: std::fprintf(stdout, "%c%X%s", '[', PSM_INDEXTOHWND, "]: Prop Sheet > Index To Window Handle" "\r\n"); break;
    // case PSM_INDEXTOID: break;
    case PSM_INDEXTOPAGE: std::fprintf(stdout, "%c%X%s", '[', PSM_INDEXTOPAGE, "]: Prop Sheet > Index To Page" "\r\n"); break;
    // case PSM_INSERTPAGE: break;
    case PSM_ISDIALOGMESSAGE: std::fprintf(stdout, "%c%X%s", '[', PSM_ISDIALOGMESSAGE, "]: Prop Sheet > Is Dialog Message" "\r\n"); break;
    // case PSM_PAGETOINDEX: break;
    case PSM_PRESSBUTTON: /* --> UDM_SETPOS32 | WM_CAP_DRIVER_GET_VERSIONW */ {
      std::fprintf(stdout, "%c%X%4s", '[', PSM_PRESSBUTTON, "]: {");
        std::fputs("Prop Sheet     : Press Buttons" "\r\n", stdout);
        std::fputs("Up-Down Control: Set Position" "\r\n", stdout);
        std::fputs("Windows Capture: Driver Get Version" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case PSM_QUERYSIBLINGS  : break;
    // case PSM_REBOOTSYSTEM   : break;
    // case PSM_RECALCPAGESIZES: break;
    // case PSM_REMOVEPAGE     : break;
    // case PSM_RESTARTWINDOWS : break;
    // case PSM_SETCURSEL      : break;
    case PSM_SETCURSELID: /* --> UDM_GETPOS32 */ {
      std::fprintf(stdout, "%c%X%4s", '[', PSM_SETCURSELID, "]: {");
        std::fputs("Prop Sheet     : Set Current Selection Identity" "\r\n", stdout);
        std::fputs("Up-Down Control: Get Position" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case PSM_SETFINISHTEXTA: std::fprintf(stdout, "%c%X%s", '[', PSM_SETFINISHTEXTA, "]: Prop Sheet > Set Finish Text" "\r\n"); break;
    // case PSM_SETFINISHTEXTW    : break;
    // case PSM_SETHEADERSUBTITLEA: break;
    // case PSM_SETHEADERSUBTITLEW: break;
    // case PSM_SETHEADERTITLEA   : break;
    // case PSM_SETHEADERTITLEW   : break;
    case PSM_SETTITLEA: /* --> UDM_SETRANGE32 */ {
      std::fprintf(stdout, "%c%X%4s", '[', PSM_SETTITLEA, "]: {");
        std::fputs("Prop Sheet     : Set Title" "\r\n", stdout);
        std::fputs("Up-Down Control: Set Range" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case PSM_SETTITLEW: break;
    case PSM_SETWIZBUTTONS: /* --> UDM_GETRANGE32 | WM_CAP_DRIVER_GET_NAMEW */ {
      std::fprintf(stdout, "%c%X%4s", '[', PSM_SETWIZBUTTONS, "]: {");
        std::fputs("Prop Sheet     : Set Wizard Buttons" "\r\n", stdout);
        std::fputs("Up-Down Control: Get Range"          "\r\n", stdout);
        std::fputs("Windows Capture: Driver Get Name"    "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case PSM_UNCHANGED: break;

    /* [Rebar] */
    case RB_BEGINDRAG: /* --> TBM_GETLINESIZE */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_BEGINDRAG, "]: {");
        std::fputs("Rebar   : Begin Drag"    "\r\n", stdout);
        std::fputs("Trackbar: Get Line Size" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case RB_DELETEBAND: break;
    case RB_DRAGMOVE: /* --> TBM_GETCHANNELRECT | TB_SAVERESTOREA | TTM_SETMARGIN */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_DRAGMOVE, "]: {");
        std::fputs("Rebar   : Drag Move"             "\r\n", stdout);
        std::fputs("Toolbar : Save Restore"          "\r\n", stdout);
        std::fputs("Tooltip : Set Margin"            "\r\n", stdout);
        std::fputs("Trackbar: Get Channel Rectangle" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case RB_ENDDRAG: /* --> TBM_GETTHUMBRECT | TB_COMMANDTOINDEX | TTM_GETMAXTIPWIDTH */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_ENDDRAG, "]: {");
        std::fputs("Rebar   : End Drag"              "\r\n", stdout);
        std::fputs("Toolbar : Command To Index"      "\r\n", stdout);
        std::fputs("Tooltip : Get Maximum Tip Width" "\r\n", stdout);
        std::fputs("Trackbar: Get Thumb Rectangle"   "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case RB_GETBANDBORDERS: std::fprintf(stdout, "%c%X%s", '[', RB_GETBANDBORDERS, "]: Rebar > Get Band Borders" "\r\n"); break;
    // case RB_GETBANDCOUNT: break;
    case RB_GETBANDINFOA: /* --> TBM_SETTOOLTIPS | TB_GETITEMRECT | TTM_UPDATE */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_GETBANDINFOA, "]: {");
        std::fputs("Rebar   : Get Band Information" "\r\n", stdout);
        std::fputs("Toolbar : Get Item Rectangle"   "\r\n", stdout);
        std::fputs("Tooltip : Update"               "\r\n", stdout);
        std::fputs("Trackbar: Set Tooltips"         "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case RB_GETBANDINFOW: /* --> TBM_GETTHUMBLENGTH | TB_ADDSTRINGA | TTM_POP */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_GETBANDINFOW, "]: {");
        std::fputs("Rebar   : Get Band Information" "\r\n", stdout);
        std::fputs("Toolbar : Add String"           "\r\n", stdout);
        std::fputs("Tooltip : Pop"                  "\r\n", stdout);
        std::fputs("Trackbar: Get Thumb Length"     "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case RB_GETBARHEIGHT: /* --> TBM_SETTHUMBLENGTH | TB_CUSTOMIZE | TTM_GETMARGIN */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_GETBARHEIGHT, "]: {");
        std::fputs("Rebar   : Get Bar Height"   "\r\n", stdout);
        std::fputs("Toolbar : Customize"        "\r\n", stdout);
        std::fputs("Tooltip : Get Margin"       "\r\n", stdout);
        std::fputs("Trackbar: Set Thumb Length" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case RB_GETBARINFO: break;
    case RB_GETBKCOLOR: /* --> SB_GETTIPTEXTW | TBM_SETTICFREQ | TB_ADDBUTTONSA | TTM_SETTIPTEXTCOLOR */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_GETBKCOLOR, "]: {");
        std::fputs("Rebar     : Get Background Color" "\r\n", stdout);
        std::fputs("Status Bar: Get Tip Text"         "\r\n", stdout);
        std::fputs("Toolbar   : Add Buttons"          "\r\n", stdout);
        std::fputs("Tooltip   : Set Tip Text Color"   "\r\n", stdout);
        std::fputs("Trackbar  : Set Tick Frequency"   "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case RB_GETPALETTE: std::fprintf(stdout, "%c%X%s", '[', RB_GETPALETTE, "]: Rebar > Get Palette" "\r\n"); break;
    // case RB_GETRECT: break;
    // case RB_GETROWCOUNT: break;
    case RB_GETROWHEIGHT: /* --> SB_ISSIMPLE | TBM_GETPTICS | TB_ISBUTTONHIGHLIGHTED | TTM_ENUMTOOLSA */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_GETROWHEIGHT, "]: {");
        std::fputs("Rebar     : Get Row Height"          "\r\n", stdout);
        std::fputs("Status Bar: Is Simple"               "\r\n", stdout);
        std::fputs("Toolbar   : Is Button Highlighted"   "\r\n", stdout);
        std::fputs("Tooltip   : Enumerate Tools"         "\r\n", stdout);
        std::fputs("Trackbar  : Get Position (of) Ticks" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case RB_GETTEXTCOLOR: /* --> TBM_GETPAGESIZE | TB_DELETEBUTTON | TTM_GETTIPBKCOLOR */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_GETTEXTCOLOR, "]: {");
        std::fputs("Rebar   : Get Text Color"           "\r\n", stdout);
        std::fputs("Toolbar : Delete Button"            "\r\n", stdout);
        std::fputs("Tooltip : Get Tip Background Color" "\r\n", stdout);
        std::fputs("Trackbar: Get Page Size"            "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case RB_GETTOOLTIPS: /* --> SB_SETTIPTEXTW | TBM_GETSELSTART | TB_SETSTATE | TTM_TRACKACTIVATE */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_GETTOOLTIPS, "]: {");
        std::fputs("Rebar     : Get Tooltips"        "\r\n", stdout);
        std::fputs("Status Bar: Set Tip Text"        "\r\n", stdout);
        std::fputs("Toolbar   : Set State"           "\r\n", stdout);
        std::fputs("Tooltip   : Track Activate"      "\r\n", stdout);
        std::fputs("Trackbar  : Get Selection Start" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case RB_HITTEST: break;
    case RB_IDTOINDEX: /* --> SB_SETTIPTEXTA | TBM_GETNUMTICS | TTM_WINDOWFROMPOINT */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_IDTOINDEX, "]: {");
        std::fputs("Rebar     : Identity to Index"     "\r\n", stdout);
        std::fputs("Status Bar: Set Tip Text"          "\r\n", stdout);
        std::fputs("Tooltip   : Window From Point"     "\r\n", stdout);
        std::fputs("Trackbar  : Get Number (of) Ticks" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case RB_INSERTBANDA: break;
    // case RB_INSERTBANDW: break;
    case RB_MAXIMIZEBAND: /* --> TBM_SETTIPSIDE | TB_SETBUTTONSIZE | TTM_ADJUSTRECT */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_MAXIMIZEBAND, "]: {");
        std::fputs("Rebar   : Maximize Band"    "\r\n", stdout);
        std::fputs("Toolbar : Set Button Size"  "\r\n", stdout);
        std::fputs("Tooltip : Adjust Rectangle" "\r\n", stdout);
        std::fputs("Trackbar: Set Tip Side"     "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case RB_MINIMIZEBAND: /* --> TBM_GETTOOLTIPS | TB_BUTTONSTRUCTSIZE | TTM_GETBUBBLESIZE */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_MINIMIZEBAND, "]: {");
        std::fputs("Rebar   : Minimize Band"         "\r\n", stdout);
        std::fputs("Toolbar : Button Structure Size" "\r\n", stdout);
        std::fputs("Tooltip : Get Bubble Size"       "\r\n", stdout);
        std::fputs("Trackbar: Get Tooltips"          "\r\n", stdout);
    ::print('}');
    } break;
    case RB_MOVEBAND: /* --> TB_SETROWS */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_MOVEBAND, "]: {");
        std::fputs("Rebar  : Move Band" "\r\n", stdout);
        std::fputs("Toolbar: Set Rows"  "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case RB_PUSHCHEVRON: /* --> TB_CHANGEBITMAP */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_PUSHCHEVRON, "]: {");
        std::fputs("Rebar  : Push Chevron"  "\r\n", stdout);
        std::fputs("Toolbar: Change Bitmap" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case RB_SETBANDINFOA: break;
    // case RB_SETBANDINFOW: break;
    // case RB_SETBARINFO  : break;
    case RB_SETBKCOLOR: /* --> TBM_CLEARSEL | TB_ADDBITMAP | TTM_SETTIPBKCOLOR */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_SETBKCOLOR, "]: {");
        std::fputs("Rebar   : Set Background Color"     "\r\n", stdout);
        std::fputs("Toolbar : Add Bitmap"               "\r\n", stdout);
        std::fputs("Tooltip : Set Tip Background Color" "\r\n", stdout);
        std::fputs("Trackbar: Clear Selection"          "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case RB_SETPALETTE: break;
    // case RB_SETPARENT : break;
    case RB_SETTEXTCOLOR: /* --> TBM_SETPAGESIZE | TB_INSERTBUTTONA | TTM_GETDELAYTIME */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_SETTEXTCOLOR, "]: {");
        std::fputs("Rebar   : Set Text Color" "\r\n", stdout);
        std::fputs("Toolbar : Insert Button"  "\r\n", stdout);
        std::fputs("Tooltip : Get Delay Time" "\r\n", stdout);
        std::fputs("Trackbar: Set Page Size"  "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case RB_SETTOOLTIPS: /* --> SB_GETTIPTEXTA | TBM_GETSELEND | TB_GETSTATE | TTM_TRACKPOSITION */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_SETTOOLTIPS, "]: {");
        std::fputs("Rebar     : Set Tooltips"      "\r\n", stdout);
        std::fputs("Status Bar: Get Tip Text"      "\r\n", stdout);
        std::fputs("Toolbar   : Get State"         "\r\n", stdout);
        std::fputs("Tooltip   : Track Position"    "\r\n", stdout);
        std::fputs("Trackbar  : Get Selection End" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case RB_SHOWBAND: break;
    case RB_SIZETORECT: /* --> TBM_SETLINESIZE | TB_GETBUTTON | TTM_GETTIPTEXTCOLOR */ {
      std::fprintf(stdout, "%c%X%4s", '[', RB_SIZETORECT, "]: {");
        std::fputs("Rebar   : Size to Rectangle"  "\r\n", stdout);
        std::fputs("Toolbar : Get Button"         "\r\n", stdout);
        std::fputs("Tooltip : Get Tip Text Color" "\r\n", stdout);
        std::fputs("Trackbar: Set Line Size"      "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;

    /* [Scrollbar] */
    case SBM_ENABLE_ARROWS: std::fprintf(stdout, "%c%X%s", '[', SBM_ENABLE_ARROWS, "]: Scrollbar > Enable Arrows" "\r\n"); break;
    case SBM_GETPOS       : std::fprintf(stdout, "%c%X%s", '[', SBM_GETPOS,        "]: Scrollbar > Get Position"  "\r\n"); break;
    case SBM_GETRANGE     : std::fprintf(stdout, "%c%X%s", '[', SBM_GETRANGE,      "]: Scrollbar > Get Range"     "\r\n"); break;
    // case SBM_GETSCROLLBARINFO: break;
    case SBM_GETSCROLLINFO : std::fprintf(stdout, "%c%X%s", '[', SBM_GETSCROLLINFO,  "]: Scrollbar > Get Scroll Information" "\r\n"); break;
    case SBM_SETPOS        : std::fprintf(stdout, "%c%X%s", '[', SBM_SETPOS,         "]: Scrollbar > Set Position"           "\r\n"); break;
    case SBM_SETRANGE      : std::fprintf(stdout, "%c%X%s", '[', SBM_SETRANGE,       "]: Scrollbar > Set Range"              "\r\n"); break;
    case SBM_SETRANGEREDRAW: std::fprintf(stdout, "%c%X%s", '[', SBM_SETRANGEREDRAW, "]: Scrollbar > Set Range Redraw"       "\r\n"); break;
    case SBM_SETSCROLLINFO : std::fprintf(stdout, "%c%X%s", '[', SBM_SETSCROLLINFO,  "]: Scrollbar > Set Scroll Information" "\r\n"); break;

    /* [Status Bar] */
    // case SB_GETBORDERS    : break;
    // case SB_GETICON       : break;
    // case SB_GETPARTS      : break;
    // case SB_GETRECT       : break;
    // case SB_GETTEXTA      : break;
    // case SB_GETTEXTLENGTHA: break;
    // case SB_GETTEXTLENGTHW: break;
    // case SB_GETTEXTW      : break;
    // case SB_GETTIPTEXTA   : break;
    // case SB_GETTIPTEXTW   : break;
    // case SB_ISSIMPLE      : break;
    case SB_SETICON: /* --> TBM_GETTICPOS | TTM_GETCURRENTTOOLA */ {
      std::fprintf(stdout, "%c%X%4s", '[', SB_SETICON, "]: {");
        std::fputs("Status Bar: Set Icon"                 "\r\n", stdout);
        std::fputs("Trackbar  : Get Tick (Mark) Position" "\r\n", stdout);
        std::fputs("Tooltip   : Get Current Tool"         "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case SB_SETMINHEIGHT: break;
    // case SB_SETPARTS    : break;
    // case SB_SETTEXTA    : break;
    // case SB_SETTEXTW    : break;
    // case SB_SETTIPTEXTA : break;
    // case SB_SETTIPTEXTW : break;
    // case SB_SIMPLE      : break;

    /* [Storage Management] */
    case SM_GETCURFOCUSA: /* --> UM_GETGROUPSELA */ {
      std::fprintf(stdout, "%c%X%4s", '[', SM_GETCURFOCUSA, "]: {");
        std::fputs("Storage Management: Get Current Focus"   "\r\n", stdout);
        std::fputs("User Manager      : Get Group Selection" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case SM_GETCURFOCUSW: /* --> UM_GETGROUPSELW */ {
      std::fprintf(stdout, "%c%X%4s", '[', SM_GETCURFOCUSW, "]: {");
        std::fputs("Storage Management: Get Current Focus"   "\r\n", stdout);
        std::fputs("User Manager      : Get Group Selection" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case SM_GETOPTIONS: /* --> UM_GETCURFOCUSA */ {
      std::fprintf(stdout, "%c%X%4s", '[', SM_GETOPTIONS, "]: {");
        std::fputs("Storage Management: Get Options"       "\r\n", stdout);
        std::fputs("User Manager      : Get Current Focus" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case SM_GETSELCOUNT: /* --> UM_GETSELCOUNT | WM_CPL_LAUNCH */ {
      std::fprintf(stdout, "%c%X%4s", '[', SM_GETSELCOUNT, "]: {");
        std::fputs("Storage Management: Get Selection Count"    "\r\n", stdout);
        std::fputs("User Manager      : Get Selection Count"    "\r\n", stdout);
        std::fputs("Windows           : Control Panel Launched" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case SM_GETSERVERSELA: /* --> UM_GETUSERSELA | WM_CPL_LAUNCHED */ {
      std::fprintf(stdout, "%c%X%4s", '[', SM_GETSERVERSELA, "]: {");
        std::fputs("Storage Management: Get Server Selection"   "\r\n", stdout);
        std::fputs("User Manager      : Get User Selection"     "\r\n", stdout);
        std::fputs("Windows           : Control Panel Launched" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case SM_GETSERVERSELW: /* --> UM_GETUSERSELW */ {
      std::fprintf(stdout, "%c%X%4s", '[', SM_GETSERVERSELW, "]: {");
        std::fputs("Storage Management: Get Server Selection" "\r\n", stdout);
        std::fputs("User Manager      : Get User Selection"   "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;

    /* [Telephony API] */
    case TAPI_REPLY: std::fprintf(stdout, "%c%X%s", '[', TAPI_REPLY, "]: Telephony API > Reply" "\r\n"); break;

    /* [Trackbar] */
    // case TBM_CLEARSEL      : break;
    // case TBM_CLEARTICS     : break;
    // case TBM_GETBUDDY      : break;
    // case TBM_GETCHANNELRECT: break;
    // case TBM_GETLINESIZE   : break;
    // case TBM_GETNUMTICS    : break;
    // case TBM_GETPAGESIZE   : break;
    // case TBM_GETPOS        : break;
    // case TBM_GETPTICS      : break;
    // case TBM_GETRANGEMAX   : break;
    // case TBM_GETRANGEMIN   : break;
    // case TBM_GETSELEND     : break;
    // case TBM_GETSELSTART   : break;
    // case TBM_GETTHUMBLENGTH: break;
    // case TBM_GETTHUMBRECT  : break;
    // case TBM_GETTIC        : break;
    // case TBM_GETTICPOS     : break;
    // case TBM_GETTOOLTIPS   : break;
    case TBM_SETBUDDY: /* --> TB_SETBITMAPSIZE | TTM_SETTITLEA */ {
      std::fprintf(stdout, "%c%X%4s", '[', TBM_SETBUDDY, "]: {");
        std::fputs("Toolbar : Set Bitmap Size"    "\r\n", stdout);
        std::fputs("Tooltip : Set Title"          "\r\n", stdout);
        std::fputs("Trackbar: Set Buddy (Window)" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    // case TBM_SETLINESIZE   : break;
    // case TBM_SETPAGESIZE   : break;
    // case TBM_SETPOS        : break;
    // case TBM_SETRANGE      : break;
    // case TBM_SETRANGEMAX   : break;
    // case TBM_SETRANGEMIN   : break;
    // case TBM_SETSEL        : break;
    // case TBM_SETSELEND     : break;
    // case TBM_SETSELSTART   : break;
    // case TBM_SETTHUMBLENGTH: break;
    // case TBM_SETTIC        : break;
    // case TBM_SETTICFREQ    : break;
    // case TBM_SETTIPSIDE    : break;
    // case TBM_SETTOOLTIPS   : break;

    /* [Toolbar] */
    // case TB_ADDBITMAP         : break;
    // case TB_ADDBUTTONSA       : break;
    // case TB_ADDBUTTONSW       : break;
    // case TB_ADDSTRINGA        : break;
    // case TB_ADDSTRINGW        : break;
    // case TB_AUTOSIZE          : break;
    // case TB_BUTTONCOUNT       : break;
    // case TB_BUTTONSTRUCTSIZE  : break;
    // case TB_CHANGEBITMAP      : break;
    // case TB_CHECKBUTTON       : break;
    // case TB_COMMANDTOINDEX    : break;
    // case TB_CUSTOMIZE         : break;
    // case TB_DELETEBUTTON      : break;
    // case TB_ENABLEBUTTON      : break;
    // case TB_GETANCHORHIGHLIGHT: break;
    case TB_GETBITMAP     : std::fprintf(stdout, "%c%X%s", '[', TB_GETBITMAP,      "]: Toolbar > Get Bitmap"       "\r\n"); break;
    case TB_GETBITMAPFLAGS: std::fprintf(stdout, "%c%X%s", '[', TB_GETBITMAPFLAGS, "]: Toolbar > Get Bitmap Flags" "\r\n"); break;
    // case TB_GETBUTTON           : break;
    // case TB_GETBUTTONINFOA      : break;
    // case TB_GETBUTTONINFOW      : break;
    // case TB_GETBUTTONSIZE       : break;
    // case TB_GETBUTTONTEXTA      : break;
    // case TB_GETBUTTONTEXTW      : break;
    // case TB_GETDISABLEDIMAGELIST: break;
    // case TB_GETEXTENDEDSTYLE    : break;
    // case TB_GETHOTIMAGELIST     : break;
    // case TB_GETHOTITEM          : break;
    case TB_GETIMAGELIST: std::fprintf(stdout, "%c%X%s", '[', TB_GETIMAGELIST, "]: Toolbar > Get Image List" "\r\n"); break;
    // case TB_GETINSERTMARK     : break;
    // case TB_GETINSERTMARKCOLOR: break;
    // case TB_GETITEMRECT       : break;
    case TB_GETMAXSIZE: std::fprintf(stdout, "%c%X%s", '[', TB_GETMAXSIZE, "]: Toolbar > Get Maximum Size" "\r\n"); break;
    // case TB_GETOBJECT : break;
    // case TB_GETPADDING: break;
    // case TB_GETRECT   : break;
    case TB_GETROWS: std::fprintf(stdout, "%c%X%s", '[', TB_GETROWS, "]: Toolbar > Get Rows" "\r\n"); break;
    // case TB_GETSTATE             : break;
    // case TB_GETSTRINGA           : break;
    // case TB_GETSTRINGW           : break;
    // case TB_GETSTYLE             : break;
    // case TB_GETTEXTROWS          : break;
    // case TB_GETTOOLTIPS          : break;
    // case TB_HIDEBUTTON           : break;
    // case TB_HITTEST              : break;
    // case TB_INDETERMINATE        : break;
    // case TB_INSERTBUTTONA        : break;
    // case TB_INSERTBUTTONW        : break;
    // case TB_INSERTMARKHITTEST    : break;
    // case TB_ISBUTTONCHECKED      : break;
    // case TB_ISBUTTONENABLED      : break;
    // case TB_ISBUTTONHIDDEN       : break;
    // case TB_ISBUTTONHIGHLIGHTED  : break;
    // case TB_ISBUTTONINDETERMINATE: break;
    // case TB_ISBUTTONPRESSED      : break;
    // case TB_LOADIMAGES           : break;
    // case TB_MAPACCELERATORA      : break;
    // case TB_MAPACCELERATORW      : break;
    // case TB_MARKBUTTON           : break;
    // case TB_MOVEBUTTON           : break;
    // case TB_PRESSBUTTON          : break;
    case TB_REPLACEBITMAP: std::fprintf(stdout, "%c%X%s", '[', TB_REPLACEBITMAP, "]: Toolbar > Replace Bitmap" "\r\n"); break;
    // case TB_SAVERESTOREA      : break;
    // case TB_SAVERESTOREW      : break;
    // case TB_SETANCHORHIGHLIGHT: break;
    // case TB_SETBITMAPSIZE     : break;
    // case TB_SETBUTTONINFOA    : break;
    // case TB_SETBUTTONINFOW    : break;
    // case TB_SETBUTTONSIZE     : break;
    // case TB_SETBUTTONWIDTH    : break;
    case TB_SETCMDID: std::fprintf(stdout, "%c%X%s", '[', TB_SETCMDID, "]: Toolbar > Set Command Identifier" "\r\n"); break;
    // case TB_SETDISABLEDIMAGELIST: break;
    // case TB_SETDRAWTEXTFLAGS    : break;
    // case TB_SETEXTENDEDSTYLE    : break;
    // case TB_SETHOTIMAGELIST     : break;
    // case TB_SETHOTITEM          : break;
    case TB_SETIMAGELIST: std::fprintf(stdout, "%c%X%s", '[', TB_SETIMAGELIST, "]: Toolbar > Set Image List"  "\r\n"); break;
    case TB_SETINDENT   : std::fprintf(stdout, "%c%X%s", '[', TB_SETINDENT,    "]: Toolbar > Set Indentation" "\r\n"); break;
    // case TB_SETINSERTMARK     : break;
    // case TB_SETINSERTMARKCOLOR: break;
    // case TB_SETMAXTEXTROWS    : break;
    // case TB_SETPADDING        : break;
    // case TB_SETPARENT         : break;
    // case TB_SETROWS           : break;
    // case TB_SETSTATE          : break;
    // case TB_SETSTYLE          : break;
    // case TB_SETTOOLTIPS       : break;

    /* [Tooltip] */
    // case TTM_ACTIVATE       : break;
    // case TTM_ADDTOOLA       : break;
    // case TTM_ADDTOOLW       : break;
    // case TTM_ADJUSTRECT     : break;
    // case TTM_DELTOOLA       : break;
    // case TTM_DELTOOLW       : break;
    // case TTM_ENUMTOOLSA     : break;
    // case TTM_ENUMTOOLSW     : break;
    // case TTM_GETBUBBLESIZE  : break;
    // case TTM_GETCURRENTTOOLA: break;
    // case TTM_GETCURRENTTOOLW: break;
    // case TTM_GETDELAYTIME   : break;
    // case TTM_GETMARGIN      : break;
    // case TTM_GETMAXTIPWIDTH : break;
    // case TTM_GETTEXTA       : break;
    // case TTM_GETTEXTW       : break;
    // case TTM_GETTIPBKCOLOR  : break;
    // case TTM_GETTIPTEXTCOLOR: break;
    // case TTM_GETTOOLCOUNT   : break;
    // case TTM_GETTOOLINFOA   : break;
    // case TTM_GETTOOLINFOW   : break;
    // case TTM_HITTESTA       : break;
    // case TTM_HITTESTW       : break;
    // case TTM_NEWTOOLRECTA   : break;
    // case TTM_NEWTOOLRECTW   : break;
    // case TTM_POP            : break;
    // case TTM_RELAYEVENT     : break;
    // case TTM_SETDELAYTIME   : break;
    // case TTM_SETMARGIN      : break;
    // case TTM_SETMAXTIPWIDTH : break;
    // case TTM_SETTIPBKCOLOR  : break;
    // case TTM_SETTIPTEXTCOLOR: break;
    // case TTM_SETTITLEA      : break;
    // case TTM_SETTITLEW      : break;
    // case TTM_SETTOOLINFOA   : break;
    // case TTM_SETTOOLINFOW   : break;
    // case TTM_TRACKACTIVATE  : break;
    // case TTM_TRACKPOSITION  : break;
    // case TTM_UPDATE         : break;
    // case TTM_UPDATETIPTEXTA : break;
    // case TTM_UPDATETIPTEXTW : break;
    // case TTM_WINDOWFROMPOINT: break;

    /* [Up-Down Control] */
    // case UDM_GETACCEL  : break;
    // case UDM_GETBASE   : break;
    // case UDM_GETBUDDY  : break;
    // case UDM_GETPOS    : break;
    // case UDM_GETPOS32  : break;
    // case UDM_GETRANGE  : break;
    // case UDM_GETRANGE32: break;
    // case UDM_SETACCEL  : break;
    // case UDM_SETBASE   : break;
    // case UDM_SETBUDDY  : break;
    // case UDM_SETPOS    : break;
    // case UDM_SETPOS32  : break;
    // case UDM_SETRANGE  : break;
    // case UDM_SETRANGE32: break;

    /* [User Manager] */
    // case UM_GETCURFOCUSA: break;
    case UM_GETCURFOCUSW: std::fprintf(stdout, "%c%X%s", '[', UM_GETCURFOCUSW, "]: User Manager > Get Current Focus" "\r\n"); break;
    // case UM_GETGROUPSELA: break;
    // case UM_GETGROUPSELW: break;
    case UM_GETOPTIONS : std::fprintf(stdout, "%c%X%s", '[', UM_GETOPTIONS,  "]: User Manager > Get Options"             "\r\n"); break;
    case UM_GETOPTIONS2: std::fprintf(stdout, "%c%X%s", '[', UM_GETOPTIONS2, "]: User Manager > Get Options (Structure)" "\r\n"); break;
    // case UM_GETSELCOUNT: break;
    // case UM_GETUSERSELA: break;
    // case UM_GETUSERSELW: break;

    /* [Wizard?] */
    // case WIZ_NEXT         : break;
    // case WIZ_PREV         : break;
    // case WIZ_QUERYNUMPAGES: break;

    /* [Windows Live Sync?] */
    case WLX_WM_SAS: std::fprintf(stdout, "%c%X%s", '[', WLX_WM_SAS, "]: Windows Live Sync > Statistical Analysis Suite Message" "\r\n"); break;

    /* [Windows Capture] */
    // case WM_CAP_DRIVER_GET_NAMEW      : break;
    // case WM_CAP_DRIVER_GET_VERSIONW   : break;
    // case WM_CAP_FILE_GET_CAPTURE_FILEW: break;
    // case WM_CAP_FILE_SAVEASW          : break;
    // case WM_CAP_FILE_SAVEDIBW         : break;
    // case WM_CAP_FILE_SET_CAPTURE_FILEW: break;
    case WM_CAP_GET_MCI_DEVICEW: std::fprintf(stdout, "%c%X%s", '[', WM_CAP_GET_MCI_DEVICEW, "]: Windows Capture > Get Media Control Interface Device" "\r\n"); break;
    case WM_CAP_PAL_OPENW      : std::fprintf(stdout, "%c%X%s", '[', WM_CAP_PAL_OPENW,       "]: Windows Capture > Palette Open"                       "\r\n"); break;
    case WM_CAP_PAL_SAVEW      : std::fprintf(stdout, "%c%X%s", '[', WM_CAP_PAL_SAVEW,       "]: Windows Capture > Palette Save"                       "\r\n"); break;
    // case WM_CAP_SET_CALLBACK_ERRORW : break;
    // case WM_CAP_SET_CALLBACK_STATUSW: break;
    // case WM_CAP_SET_MCI_DEVICEW     : break;
    // case WM_CAP_UNICODE_START       : break;

    /* [Windows] */
    case WM_ACTIVATE       : std::fprintf(stdout, "%c%X%s", '[', WM_ACTIVATE,        "]: Windows > Activate"                                 "\r\n"); break;
    case WM_ACTIVATEAPP    : std::fprintf(stdout, "%c%X%s", '[', WM_ACTIVATEAPP,     "]: Windows > Activate Application"                     "\r\n"); break;
    case WM_AFXFIRST       : std::fprintf(stdout, "%c%X%s", '[', WM_AFXFIRST,        "]: Windows > Application Framework Extensions [FIRST]" "\r\n"); break;
    case WM_AFXLAST        : std::fprintf(stdout, "%c%X%s", '[', WM_AFXLAST,         "]: Windows > Application Framework Extensions [LAST]"  "\r\n"); break;
    case WM_APP            : std::fprintf(stdout, "%c%X%s", '[', WM_APP,             "]: Windows > Application"                              "\r\n"); break;
    case WM_APPCOMMAND     : std::fprintf(stdout, "%c%X%s", '[', WM_APPCOMMAND,      "]: Windows > Application Command"                      "\r\n"); break;
    case WM_ASKCBFORMATNAME: std::fprintf(stdout, "%c%X%s", '[', WM_ASKCBFORMATNAME, "]: Windows > Ask Clipboard Format Name"                "\r\n"); break;
    case WM_CANCELJOURNAL  : std::fprintf(stdout, "%c%X%s", '[', WM_CANCELJOURNAL,   "]: Windows > Cancel Journal"                           "\r\n"); break;
    case WM_CANCELMODE     : std::fprintf(stdout, "%c%X%s", '[', WM_CANCELMODE,      "]: Windows > Cancel Mode"                              "\r\n"); break;
    case WM_CAPTURECHANGED : std::fprintf(stdout, "%c%X%s", '[', WM_CAPTURECHANGED,  "]: Windows Capture > Changed"                          "\r\n"); break;
    case WM_CHANGECBCHAIN  : std::fprintf(stdout, "%c%X%s", '[', WM_CHANGECBCHAIN,   "]: Windows > Change Control Box Chain"                 "\r\n"); break;
    case WM_CHANGEUISTATE  : std::fprintf(stdout, "%c%X%s", '[', WM_CHANGEUISTATE,   "]: Windows > Change User-Interface State"              "\r\n"); break;
    case WM_CHAR           : std::fprintf(stdout, "%c%X%s", '[', WM_CHAR,            "]: Windows > Character"                                "\r\n"); break;
    case WM_CHARTOITEM     : std::fprintf(stdout, "%c%X%s", '[', WM_CHARTOITEM,      "]: Windows > Character to Item"                        "\r\n"); break;
    case WM_CHILDACTIVATE  : std::fprintf(stdout, "%c%X%s", '[', WM_CHILDACTIVATE,   "]: Windows > Child Activate"                           "\r\n"); break;
    // case WM_CHOOSEFONT_GETLOGFONT: break;
    // case WM_CHOOSEFONT_SETFLAGS  : break;
    // case WM_CHOOSEFONT_SETLOGFON T: break;
    case WM_CLEAR         : std::fprintf(stdout, "%c%X%s", '[', WM_CLEAR,          "]: Windows > Clear"            "\r\n"); break;
    case WM_CLOSE         : std::fprintf(stdout, "%c%X%s", '[', WM_CLOSE,          "]: Windows > Close" "\r\n"); { ::DestroyWindow(windowHandle); ::PostQuitMessage(0x0u); } break;
    case WM_COMMAND       : std::fprintf(stdout, "%c%X%s", '[', WM_COMMAND,        "]: Windows > Command"          "\r\n"); break;
    case WM_COMMNOTIFY    : std::fprintf(stdout, "%c%X%s", '[', WM_COMMNOTIFY,     "]: Windows > Command Notify"   "\r\n"); break;
    case WM_COMPACTING    : std::fprintf(stdout, "%c%X%s", '[', WM_COMPACTING,     "]: Windows > Compacting"       "\r\n"); break;
    case WM_COMPAREITEM   : std::fprintf(stdout, "%c%X%s", '[', WM_COMPAREITEM,    "]: Windows > Compare Item"     "\r\n"); break;
    case WM_CONTEXTMENU   : std::fprintf(stdout, "%c%X%s", '[', WM_CONTEXTMENU,    "]: Windows > Context Menu"     "\r\n"); break;
    case WM_CONVERTREQUEST: std::fprintf(stdout, "%c%X%s", '[', WM_CONVERTREQUEST, "]: Windows > Convert Request"  "\r\n"); break;
    case WM_CONVERTRESULT : std::fprintf(stdout, "%c%X%s", '[', WM_CONVERTRESULT,  "]: Windows > Convert Result"   "\r\n"); break;
    case WM_COPY          : std::fprintf(stdout, "%c%X%s", '[', WM_COPY,           "]: Windows > Copy"             "\r\n"); break;
    case WM_COPYDATA      : std::fprintf(stdout, "%c%X%s", '[', WM_COPYDATA,       "]: Windows > Copy Data"        "\r\n"); break;
    case WM_COPYGLOBALDATA: std::fprintf(stdout, "%c%X%s", '[', WM_COPYGLOBALDATA, "]: Windows > Copy Global Data" "\r\n"); break;
    // case WM_CPL_LAUNCH  : break;
    // case WM_CPL_LAUNCHED: break;
    case WM_CREATE           : std::fprintf(stdout, "%c%X%s", '[', WM_CREATE,            "]: Windows > Create"                      "\r\n"); break;
    case WM_CTLCOLOR         : std::fprintf(stdout, "%c%X%s", '[', WM_CTLCOLOR,          "]: Windows > Control Color"               "\r\n"); break;
    case WM_CTLCOLORBTN      : std::fprintf(stdout, "%c%X%s", '[', WM_CTLCOLORBTN,       "]: Windows > Control Color Button"        "\r\n"); break;
    case WM_CTLCOLORDLG      : std::fprintf(stdout, "%c%X%s", '[', WM_CTLCOLORDLG,       "]: Windows > Control Color Dialog"        "\r\n"); break;
    case WM_CTLCOLOREDIT     : std::fprintf(stdout, "%c%X%s", '[', WM_CTLCOLOREDIT,      "]: Windows > Control Color Editor"        "\r\n"); break;
    case WM_CTLCOLORLISTBOX  : std::fprintf(stdout, "%c%X%s", '[', WM_CTLCOLORLISTBOX,   "]: Windows > Control Color List Box"      "\r\n"); break;
    case WM_CTLCOLORMSGBOX   : std::fprintf(stdout, "%c%X%s", '[', WM_CTLCOLORMSGBOX,    "]: Windows > Control Color Message Box"   "\r\n"); break;
    case WM_CTLCOLORSCROLLBAR: std::fprintf(stdout, "%c%X%s", '[', WM_CTLCOLORSCROLLBAR, "]: Windows > Control Color Scrollbar"     "\r\n"); break;
    case WM_CTLCOLORSTATIC   : std::fprintf(stdout, "%c%X%s", '[', WM_CTLCOLORSTATIC,    "]: Windows > Control Color Static"        "\r\n"); break;
    case WM_CTLINIT          : std::fprintf(stdout, "%c%X%s", '[', WM_CTLINIT,           "]: Windows > Control Initiation"          "\r\n"); break;
    case WM_CUT              : std::fprintf(stdout, "%c%X%s", '[', WM_CUT,               "]: Windows > Cut"                         "\r\n"); break;
    case WM_DEADCHAR         : std::fprintf(stdout, "%c%X%s", '[', WM_DEADCHAR,          "]: Windows > Dead Character"              "\r\n"); break;
    case WM_DELETEITEM       : std::fprintf(stdout, "%c%X%s", '[', WM_DELETEITEM,        "]: Windows > Delete Item"                 "\r\n"); break;
    case WM_DESTROY          : std::fprintf(stdout, "%c%X%s", '[', WM_DESTROY,           "]: Windows > Destroy" "\r\n"); { ::PostQuitMessage(0x0u); } break;
    case WM_DESTROYCLIPBOARD : std::fprintf(stdout, "%c%X%s", '[', WM_DESTROYCLIPBOARD,  "]: Windows > Destroy Clipboard"           "\r\n"); break;
    case WM_DEVICECHANGE     : std::fprintf(stdout, "%c%X%s", '[', WM_DEVICECHANGE,      "]: Windows > Device Change"               "\r\n"); break;
    case WM_DEVMODECHANGE    : std::fprintf(stdout, "%c%X%s", '[', WM_DEVMODECHANGE,     "]: Windows > Device Mode Change"          "\r\n"); break;
    case WM_DISPLAYCHANGE    : std::fprintf(stdout, "%c%X%s", '[', WM_DISPLAYCHANGE,     "]: Windows > Display Change"              "\r\n"); break;
    case WM_DRAWCLIPBOARD    : std::fprintf(stdout, "%c%X%s", '[', WM_DRAWCLIPBOARD,     "]: Windows > Draw Clipboard"              "\r\n"); break;
    case WM_DRAWITEM         : std::fprintf(stdout, "%c%X%s", '[', WM_DRAWITEM,          "]: Windows > Draw Item"                   "\r\n"); break;
    case WM_DROPFILES        : std::fprintf(stdout, "%c%X%s", '[', WM_DROPFILES,         "]: Windows > Drop Files"                  "\r\n"); break;
    case WM_ENABLE           : std::fprintf(stdout, "%c%X%s", '[', WM_ENABLE,            "]: Windows > Enable"                      "\r\n"); break;
    case WM_ENDSESSION       : std::fprintf(stdout, "%c%X%s", '[', WM_ENDSESSION,        "]: Windows > End Session"                 "\r\n"); break;
    case WM_ENTERIDLE        : std::fprintf(stdout, "%c%X%s", '[', WM_ENTERIDLE,         "]: Windows > Enter Idle"                  "\r\n"); break;
    case WM_ENTERMENULOOP    : std::fprintf(stdout, "%c%X%s", '[', WM_ENTERMENULOOP,     "]: Windows > Enter Menu Loop"             "\r\n"); break;
    case WM_ENTERSIZEMOVE    : std::fprintf(stdout, "%c%X%s", '[', WM_ENTERSIZEMOVE,     "]: Windows > Enter Size Move"             "\r\n"); break;
    case WM_ERASEBKGND       : std::fprintf(stdout, "%c%X%s", '[', WM_ERASEBKGND,        "]: Windows > Erase Background"            "\r\n"); break;
    case WM_EXITMENULOOP     : std::fprintf(stdout, "%c%X%s", '[', WM_EXITMENULOOP,      "]: Windows > Exit Menu Loop"              "\r\n"); break;
    case WM_EXITSIZEMOVE     : std::fprintf(stdout, "%c%X%s", '[', WM_EXITSIZEMOVE,      "]: Windows > Exit Size Move"              "\r\n"); break;
    case WM_FONTCHANGE       : std::fprintf(stdout, "%c%X%s", '[', WM_FONTCHANGE,        "]: Windows > Font Change"                 "\r\n"); break;
    case WM_GETDLGCODE       : std::fprintf(stdout, "%c%X%s", '[', WM_GETDLGCODE,        "]: Windows > Get Dialog Code"             "\r\n"); break;
    case WM_GETFONT          : std::fprintf(stdout, "%c%X%s", '[', WM_GETFONT,           "]: Windows > Get Font"                    "\r\n"); break;
    case WM_GETHOTKEY        : std::fprintf(stdout, "%c%X%s", '[', WM_GETHOTKEY,         "]: Windows > Get Hotkey"                  "\r\n"); break;
    case WM_GETICON          : std::fprintf(stdout, "%c%X%s", '[', WM_GETICON,           "]: Windows > Get Icon"                    "\r\n"); break;
    case WM_GETMINMAXINFO    : std::fprintf(stdout, "%c%X%s", '[', WM_GETMINMAXINFO,     "]: Windows > Get Min-Maximum Information" "\r\n"); break;
    case WM_GETOBJECT        : std::fprintf(stdout, "%c%X%s", '[', WM_GETOBJECT,         "]: Windows > Get Object"                  "\r\n"); break;
    case WM_GETTEXT          : std::fprintf(stdout, "%c%X%s", '[', WM_GETTEXT,           "]: Windows > Get Text"                    "\r\n"); break;
    case WM_GETTEXTLENGTH    : std::fprintf(stdout, "%c%X%s", '[', WM_GETTEXTLENGTH,     "]: Windows > Get Text Length"             "\r\n"); break;
    case WM_GLOBALRCCHANGE: /* --> WM_PENMISCINFO */ {
    //   std::fprintf(stdout, "%c%X%4s", '[', WM_GLOBALRCCHANGE, "]: {");
    //     std::fputs("Windows: Global RC Change"              "\r\n", stdout);
    //     std::fputs("Windows: Pen Miscellaneous Information" "\r\n", stdout);
    //   std::fputs("}" "\r\n", stdout);
    // } break;
    case WM_HANDHELDFIRST: std::fprintf(stdout, "%c%X%s", '[', WM_HANDHELDFIRST, "]: Windows > Hand-Held [FIRST]" "\r\n"); break;
    case WM_HANDHELDLAST : std::fprintf(stdout, "%c%X%s", '[', WM_HANDHELDLAST,  "]: Windows > Hand-Held [LAST]"  "\r\n"); break;
    case WM_HEDITCTL: /* --> WM_PENCTL */ {
    //   std::fprintf(stdout, "%c%X%4s", '[', WM_HEDITCTL, "]: {");
    //     std::fputs("Windows: Hand-Editing Control" "\r\n", stdout);
    //     std::fputs("Windows: Pen Control"          "\r\n", stdout);
    //   std::fputs("}" "\r\n", stdout);
    // } break;
    case WM_HELP                   : std::fprintf(stdout, "%c%X%s", '[', WM_HELP,                "]: Windows > Help"                                                                    "\r\n"); break;
    case WM_HOOKRCRESULT           : std::fprintf(stdout, "%c%X%s", '[', WM_HOOKRCRESULT,        "]: Windows > Hook RC Result"                                                          "\r\n"); break;
    case WM_HOTKEY                 : std::fprintf(stdout, "%c%X%s", '[', WM_HOTKEY,              "]: Windows > Hotkey"                                                                  "\r\n"); break;
    case WM_HSCROLL                : std::fprintf(stdout, "%c%X%s", '[', WM_HSCROLL,             "]: Windows > Horizontal Scroll"                                                       "\r\n"); break;
    case WM_HSCROLLCLIPBOARD       : std::fprintf(stdout, "%c%X%s", '[', WM_HSCROLLCLIPBOARD,    "]: Windows > Horizontal Scroll Clipboard"                                             "\r\n"); break;
    case WM_ICONERASEBKGND         : std::fprintf(stdout, "%c%X%s", '[', WM_ICONERASEBKGND,      "]: Windows > Icon Erase Background"                                                   "\r\n"); break;
    case WM_IMEKEYDOWN             : /* --> WM_IME_KEYDOWN */ std::fprintf(stdout, "%c%X%s", '[', WM_IMEKEYDOWN,      "]: Windows > IME (Input Method Editor) Key Down"                 "\r\n"); break;
    case WM_IMEKEYUP               : /* --> WM_IME_KEYUP */   std::fprintf(stdout, "%c%X%s", '[', WM_IMEKEYUP,        "]: Windows > IME (Input Method Editor) Key Up"                   "\r\n"); break;
    case WM_IME_CHAR               : std::fprintf(stdout, "%c%X%s", '[', WM_IME_CHAR,            "]: Windows > IME (Input Method Editor) Character"                                     "\r\n"); break;
    case WM_IME_COMPOSITION        : /* --> WM_IME_KEYLAST */ std::fprintf(stdout, "%c%X%s", '[', WM_IME_COMPOSITION, "]: Windows > IME (Input Method Editor) Composition [(Key) LAST]" "\r\n"); break;
    case WM_IME_COMPOSITIONFULL    : std::fprintf(stdout, "%c%X%s", '[', WM_IME_COMPOSITIONFULL, "]: Windows > IME (Input Method Editor) Composition Full"                              "\r\n"); break;
    case WM_IME_CONTROL            : std::fprintf(stdout, "%c%X%s", '[', WM_IME_CONTROL,         "]: Windows > IME (Input Method Editor) Control"                                       "\r\n"); break;
    case WM_IME_ENDCOMPOSITION     : std::fprintf(stdout, "%c%X%s", '[', WM_IME_ENDCOMPOSITION,  "]: Windows > IME (Input Method Editor) End Composition"                               "\r\n"); break;
    // case WM_IME_KEYDOWN: break;
    // case WM_IME_KEYLAST: break;
    // case WM_IME_KEYUP  : break;
    case WM_IME_NOTIFY            : std::fprintf(stdout, "%c%X%s", '[', WM_IME_NOTIFY,             "]: Windows > IME (Input Method Editor) Notify"            "\r\n"); break;
    case WM_IME_REPORT            : std::fprintf(stdout, "%c%X%s", '[', WM_IME_REPORT,             "]: Windows > IME (Input Method Editor) Report"            "\r\n"); break;
    case WM_IME_REQUEST           : std::fprintf(stdout, "%c%X%s", '[', WM_IME_REQUEST,            "]: Windows > IME (Input Method Editor) Request"           "\r\n"); break;
    case WM_IME_SELECT            : std::fprintf(stdout, "%c%X%s", '[', WM_IME_SELECT,             "]: Windows > IME (Input Method Editor) Select"            "\r\n"); break;
    case WM_IME_SETCONTEXT        : std::fprintf(stdout, "%c%X%s", '[', WM_IME_SETCONTEXT,         "]: Windows > IME (Input Method Editor) Set Context"       "\r\n"); break;
    case WM_IME_STARTCOMPOSITION  : std::fprintf(stdout, "%c%X%s", '[', WM_IME_STARTCOMPOSITION,   "]: Windows > IME (Input Method Editor) Start Composition" "\r\n"); break;
    case WM_INITDIALOG            : std::fprintf(stdout, "%c%X%s", '[', WM_INITDIALOG,             "]: Windows > Initiate Dialog"                             "\r\n"); break;
    case WM_INITMENU              : std::fprintf(stdout, "%c%X%s", '[', WM_INITMENU,               "]: Windows > Initiate Menu"                               "\r\n"); break;
    case WM_INITMENUPOPUP         : std::fprintf(stdout, "%c%X%s", '[', WM_INITMENUPOPUP,          "]: Windows > Initiate Menu Pop-Up"                        "\r\n"); break;
    case WM_INPUT                 : std::fprintf(stdout, "%c%X%s", '[', WM_INPUT,                  "]: Windows > Input"                                       "\r\n"); break;
    case WM_INPUTLANGCHANGE       : std::fprintf(stdout, "%c%X%s", '[', WM_INPUTLANGCHANGE,        "]: Windows > Input Language Change"                       "\r\n"); break;
    case WM_INPUTLANGCHANGEREQUEST: std::fprintf(stdout, "%c%X%s", '[', WM_INPUTLANGCHANGEREQUEST, "]: Windows > Input Language Change Request"               "\r\n"); break;
    case WM_INTERIM               : std::fprintf(stdout, "%c%X%s", '[', WM_INTERIM,                "]: Windows > Interim"                                     "\r\n"); break;
    case WM_KEYDOWN: /* --> WM_KEYFIRST */ std::fprintf(stdout, "%c%X%s", '[', WM_KEYDOWN, "]: Windows > Key Down [FIRST]" "\r\n"); { if (VK_ESCAPE == parameter) { ::DestroyWindow(windowHandle); ::PostQuitMessage(0x0u); } } break;
    // case WM_KEYFIRST: break;
    case WM_KEYLAST: /* --> WM_UNICHAR | WM_WNT_CONVERTREQUESTEX */ {
      std::fprintf(stdout, "%c%X%4s", '[', WM_KEYLAST, "]: {");
        std::fputs("Windows: Convert Request"   "\r\n", stdout);
        std::fputs("Windows: Key [LAST]"        "\r\n", stdout);
        std::fputs("Windows: Unicode Character" "\r\n", stdout);
      std::fputs("}" "\r\n", stdout);
    } break;
    case WM_KEYUP         : std::fprintf(stdout, "%c%X%s", '[', WM_KEYUP,          "]: Windows > Key Up"                                                               "\r\n"); break;
    case WM_KILLFOCUS     : std::fprintf(stdout, "%c%X%s", '[', WM_KILLFOCUS,      "]: Windows > Kill Focus"                                                           "\r\n"); break;
    case WM_LBUTTONDBLCLK : std::fprintf(stdout, "%c%X%s", '[', WM_LBUTTONDBLCLK,  "]: Windows > Left (Mouse) Button Double-Click"                                     "\r\n"); break;
    case WM_LBUTTONDOWN   : std::fprintf(stdout, "%c%X%s", '[', WM_LBUTTONDOWN,    "]: Windows > Left (Mouse) Button Down"                                             "\r\n"); break;
    case WM_LBUTTONUP     : std::fprintf(stdout, "%c%X%s", '[', WM_LBUTTONUP,      "]: Windows > Left (Mouse) Button Up"                                               "\r\n"); break;
    case WM_MBUTTONDBLCLK : std::fprintf(stdout, "%c%X%s", '[', WM_MBUTTONDBLCLK,  "]: Windows > Middle (Mouse) Button Double-Click"                                   "\r\n"); break;
    case WM_MBUTTONDOWN   : std::fprintf(stdout, "%c%X%s", '[', WM_MBUTTONDOWN,    "]: Windows > Middle (Mouse) Button Down"                                           "\r\n"); break;
    case WM_MBUTTONUP     : std::fprintf(stdout, "%c%X%s", '[', WM_MBUTTONUP,      "]: Windows > Middle (Mouse) Button Up"                                             "\r\n"); break;
    case WM_MDIACTIVATE   : std::fprintf(stdout, "%c%X%s", '[', WM_MDIACTIVATE,    "]: Windows > Multiple-Document Interface Activate"                                 "\r\n"); break;
    case WM_MDICASCADE    : std::fprintf(stdout, "%c%X%s", '[', WM_MDICASCADE,     "]: Windows > Multiple-Document Interface Cascade"                                  "\r\n"); break;
    case WM_MDICREATE     : std::fprintf(stdout, "%c%X%s", '[', WM_MDICREATE,      "]: Windows > Multiple-Document Interface Create"                                   "\r\n"); break;
    case WM_MDIDESTROY    : std::fprintf(stdout, "%c%X%s", '[', WM_MDIDESTROY,     "]: Windows > Multiple-Document Interface Destroy"                                  "\r\n"); break;
    case WM_MDIGETACTIVE  : std::fprintf(stdout, "%c%X%s", '[', WM_MDIGETACTIVE,   "]: Windows > Multiple-Document Interface Get Active"                               "\r\n"); break;
    case WM_MDIICONARRANGE: std::fprintf(stdout, "%c%X%s", '[', WM_MDIICONARRANGE, "]: Windows > Multiple-Document Interface Icon Arrange"                             "\r\n"); break;
    case WM_MDIMAXIMIZE   : std::fprintf(stdout, "%c%X%s", '[', WM_MDIMAXIMIZE,    "]: Windows > Multiple-Document Interface Maximize"                                 "\r\n"); break;
    case WM_MDINEXT       : std::fprintf(stdout, "%c%X%s", '[', WM_MDINEXT,        "]: Windows > Multiple-Document Interface Next"                                     "\r\n"); break;
    case WM_MDIREFRESHMENU: std::fprintf(stdout, "%c%X%s", '[', WM_MDIREFRESHMENU, "]: Windows > Multiple-Document Interface Refresh Menu"                             "\r\n"); break;
    case WM_MDIRESTORE    : std::fprintf(stdout, "%c%X%s", '[', WM_MDIRESTORE,     "]: Windows > Multiple-Document Interface Restore"                                  "\r\n"); break;
    case WM_MDISETMENU    : std::fprintf(stdout, "%c%X%s", '[', WM_MDISETMENU,     "]: Windows > Multiple-Document Interface Set Menu"                                 "\r\n"); break;
    case WM_MDITILE       : std::fprintf(stdout, "%c%X%s", '[', WM_MDITILE,        "]: Windows > Multiple-Document Interface Tile"                                     "\r\n"); break;
    case WM_MEASUREITEM   : std::fprintf(stdout, "%c%X%s", '[', WM_MEASUREITEM,    "]: Windows > Measure Item"                                                         "\r\n"); break;
    case WM_MENUCHAR      : std::fprintf(stdout, "%c%X%s", '[', WM_MENUCHAR,       "]: Windows > Menu Character"                                                       "\r\n"); break;
    case WM_MENUCOMMAND   : std::fprintf(stdout, "%c%X%s", '[', WM_MENUCOMMAND,    "]: Windows > Menu Command"                                                         "\r\n"); break;
    case WM_MENUDRAG      : std::fprintf(stdout, "%c%X%s", '[', WM_MENUDRAG,       "]: Windows > Menu Drag"                                                            "\r\n"); break;
    case WM_MENUGETOBJECT : std::fprintf(stdout, "%c%X%s", '[', WM_MENUGETOBJECT,  "]: Windows > Menu Get to Object"                                                   "\r\n"); break;
    case WM_MENURBUTTONUP : std::fprintf(stdout, "%c%X%s", '[', WM_MENURBUTTONUP,  "]: Windows > Menu Right (Mouse) Button Up"                                         "\r\n"); break;
    case WM_MENUSELECT    : std::fprintf(stdout, "%c%X%s", '[', WM_MENUSELECT,     "]: Windows > Menu Select"                                                          "\r\n"); break;
    case WM_MOUSEACTIVATE : std::fprintf(stdout, "%c%X%s", '[', WM_MOUSEACTIVATE,  "]: Windows > Mouse Activate"                                                       "\r\n"); break;
    case WM_MOUSEFIRST    : /* --> WM_MOUSEMOVE */     std::fprintf(stdout, "%c%X%s", '[', WM_MOUSEMOVE,     "]: Windows > Mouse Move [FIRST]"                         "\r\n"); break;
    case WM_MOUSEHOVER    : std::fprintf(stdout, "%c%X%s", '[', WM_MOUSEHOVER,     "]: Windows > Mouse Hover"                                                          "\r\n"); break;
    case WM_MOUSELAST     : /* --> WM_XBUTTONDBLCLK */ std::fprintf(stdout, "%c%X%s", '[', WM_XBUTTONDBLCLK, "]: Windows > Mouse X (Mouse) Button Double-Click [LAST]" "\r\n"); break;
    case WM_MOUSELEAVE    : std::fprintf(stdout, "%c%X%s", '[', WM_MOUSELEAVE,     "]: Windows > Mouse Leave"                                                          "\r\n"); break;
    // case WM_MOUSEMOVE: break;
    case WM_MOUSEWHEEL       : std::fprintf(stdout, "%c%X%s", '[', WM_MOUSEWHEEL,        "]: Windows > Mouse Wheel"                                   "\r\n"); break;
    case WM_MOVE             : std::fprintf(stdout, "%c%X%s", '[', WM_MOVE,              "]: Windows > Move"                                          "\r\n"); break;
    case WM_MOVING           : std::fprintf(stdout, "%c%X%s", '[', WM_MOVING,            "]: Windows > Moving"                                        "\r\n"); break;
    case WM_NCACTIVATE       : std::fprintf(stdout, "%c%X%s", '[', WM_NCACTIVATE,        "]: Windows > Non-Client Activate"                           "\r\n"); break;
    case WM_NCCALCSIZE       : std::fprintf(stdout, "%c%X%s", '[', WM_NCCALCSIZE,        "]: Windows > Non-Client Calculate Size"                     "\r\n"); break;
    case WM_NCCREATE         : std::fprintf(stdout, "%c%X%s", '[', WM_NCCREATE,          "]: Windows > Non-Client Create"                             "\r\n"); break;
    case WM_NCDESTROY        : std::fprintf(stdout, "%c%X%s", '[', WM_NCDESTROY,         "]: Windows > Non-Client Destroy"                            "\r\n"); break;
    case WM_NCHITTEST        : std::fprintf(stdout, "%c%X%s", '[', WM_NCHITTEST,         "]: Windows > Non-Client Hit-Test"                           "\r\n"); break;
    case WM_NCLBUTTONDBLCLK  : std::fprintf(stdout, "%c%X%s", '[', WM_NCLBUTTONDBLCLK,   "]: Windows > Non-Client Left (Mouse) Button Double-Click"   "\r\n"); break;
    case WM_NCLBUTTONDOWN    : std::fprintf(stdout, "%c%X%s", '[', WM_NCLBUTTONDOWN,     "]: Windows > Non-Client Left (Mouse) Button Down"           "\r\n"); break;
    case WM_NCLBUTTONUP      : std::fprintf(stdout, "%c%X%s", '[', WM_NCLBUTTONUP,       "]: Windows > Non-Client Left (Mouse) Button Up"             "\r\n"); break;
    case WM_NCMBUTTONDBLCLK  : std::fprintf(stdout, "%c%X%s", '[', WM_NCMBUTTONDBLCLK,   "]: Windows > Non-Client Middle (Mouse) Button Double-Click" "\r\n"); break;
    case WM_NCMBUTTONDOWN    : std::fprintf(stdout, "%c%X%s", '[', WM_NCMBUTTONDOWN,     "]: Windows > Non-Client Middle (Mouse) Button Down"         "\r\n"); break;
    case WM_NCMBUTTONUP      : std::fprintf(stdout, "%c%X%s", '[', WM_NCMBUTTONUP,       "]: Windows > Non-Client Middle (Mouse) Button Up"           "\r\n"); break;
    case WM_NCMOUSEHOVER     : std::fprintf(stdout, "%c%X%s", '[', WM_NCMOUSEHOVER,      "]: Windows > Non-Client Mouse Hover"                        "\r\n"); break;
    case WM_NCMOUSELEAVE     : std::fprintf(stdout, "%c%X%s", '[', WM_NCMOUSELEAVE,      "]: Windows > Non-Client Mouse Leave"                        "\r\n"); break;
    case WM_NCMOUSEMOVE      : std::fprintf(stdout, "%c%X%s", '[', WM_NCMOUSEMOVE,       "]: Windows > Non-Client Mouse Mouse"                        "\r\n"); break;
    case WM_NCPAINT          : std::fprintf(stdout, "%c%X%s", '[', WM_NCPAINT,           "]: Windows > Non-Client Paint"                              "\r\n"); break;
    case WM_NCRBUTTONDBLCLK  : std::fprintf(stdout, "%c%X%s", '[', WM_NCRBUTTONDBLCLK,   "]: Windows > Non-Client Right (Mouse) Button Double-Click"  "\r\n"); break;
    case WM_NCRBUTTONDOWN    : std::fprintf(stdout, "%c%X%s", '[', WM_NCRBUTTONDOWN,     "]: Windows > Non-Client Right (Mouse) Button Down"          "\r\n"); break;
    case WM_NCRBUTTONUP      : std::fprintf(stdout, "%c%X%s", '[', WM_NCRBUTTONUP,       "]: Windows > Non-Client Right (Mouse) Button Up"            "\r\n"); break;
    case WM_NCXBUTTONDBLCLK  : std::fprintf(stdout, "%c%X%s", '[', WM_NCXBUTTONDBLCLK,   "]: Windows > Non-Client X (Mouse) Button Double-Click"      "\r\n"); break;
    case WM_NCXBUTTONDOWN    : std::fprintf(stdout, "%c%X%s", '[', WM_NCXBUTTONDOWN,     "]: Windows > Non-Client X (Mouse) Button Down"              "\r\n"); break;
    case WM_NCXBUTTONUP      : std::fprintf(stdout, "%c%X%s", '[', WM_NCXBUTTONUP,       "]: Windows > Non-Client X (Mouse) Button Up"                "\r\n"); break;
    case WM_NEXTDLGCTL       : std::fprintf(stdout, "%c%X%s", '[', WM_NEXTDLGCTL,        "]: Windows > Next Dialog Control"                           "\r\n"); break;
    case WM_NEXTMENU         : std::fprintf(stdout, "%c%X%s", '[', WM_NEXTMENU,          "]: Windows > Next Menu"                                     "\r\n"); break;
    case WM_NOTIFY           : std::fprintf(stdout, "%c%X%s", '[', WM_NOTIFY,            "]: Windows > Notify"                                        "\r\n"); break;
    case WM_NOTIFYFORMAT     : std::fprintf(stdout, "%c%X%s", '[', WM_NOTIFYFORMAT,      "]: Windows > Notify Format"                                 "\r\n"); break;
    case WM_NULL             : std::fprintf(stdout, "%c%X%s", '[', WM_NULL,              "]: Windows > [NULL]"                                        "\r\n"); break;
    case WM_PAINT            : std::fprintf(stdout, "%c%X%s", '[', WM_PAINT,             "]: Windows > Paint"                                         "\r\n"); break;
    case WM_PAINTCLIPBOARD   : std::fprintf(stdout, "%c%X%s", '[', WM_PAINTCLIPBOARD,    "]: Windows > Paint Clipboard"                               "\r\n"); break;
    case WM_PAINTICON        : std::fprintf(stdout, "%c%X%s", '[', WM_PAINTICON,         "]: Windows > Paint Icon"                                    "\r\n"); break;
    case WM_PALETTECHANGED   : std::fprintf(stdout, "%c%X%s", '[', WM_PALETTECHANGED,    "]: Windows > Palette Changed"                               "\r\n"); break;
    case WM_PALETTEISCHANGING: std::fprintf(stdout, "%c%X%s", '[', WM_PALETTEISCHANGING, "]: Windows > Palette is Changing"                           "\r\n"); break;
    case WM_PARENTNOTIFY     : std::fprintf(stdout, "%c%X%s", '[', WM_PARENTNOTIFY,      "]: Windows > Parent Notify"                                 "\r\n"); break;
    case WM_PASTE            : std::fprintf(stdout, "%c%X%s", '[', WM_PASTE,             "]: Windows > Paste"                                         "\r\n"); break;
    // case WM_PENCTL: break;
    case WM_PENEVENT: std::fprintf(stdout, "%c%X%s", '[', WM_PENEVENT, "]: Windows > Pen Event"         "\r\n"); break;
    case WM_PENMISC : std::fprintf(stdout, "%c%X%s", '[', WM_PENMISC,  "]: Windows > Pen Miscellaneous" "\r\n"); break;
    // case WM_PENMISCINFO: break;
    case WM_PENWINFIRST   : std::fprintf(stdout, "%c%X%s", '[', WM_PENWINFIRST,    "]: Windows > Pen [FIRST]"     "\r\n"); break;
    case WM_PENWINLAST    : std::fprintf(stdout, "%c%X%s", '[', WM_PENWINLAST,     "]: Windows > Pen [LAST]"      "\r\n"); break;
    case WM_POWER         : std::fprintf(stdout, "%c%X%s", '[', WM_POWER,          "]: Windows > Power"           "\r\n"); break;
    case WM_POWERBROADCAST: std::fprintf(stdout, "%c%X%s", '[', WM_POWERBROADCAST, "]: Windows > Power Broadcast" "\r\n"); break;
    case WM_PRINT         : std::fprintf(stdout, "%c%X%s", '[', WM_PRINT,          "]: Windows > Print"           "\r\n"); break;
    case WM_PRINTCLIENT   : std::fprintf(stdout, "%c%X%s", '[', WM_PRINTCLIENT,    "]: Windows > Print Client"    "\r\n"); break;
    // case WM_PSD_ENVSTAMPRECT  : break;
    // case WM_PSD_FULLPAGERECT  : break;
    // case WM_PSD_GREEKTEXTRECT : break;
    // case WM_PSD_MARGINRECT    : break;
    // case WM_PSD_MINMARGINRECT : break;
    // case WM_PSD_PAGESETUPDLG  : break;
    // case WM_PSD_YAFULLPAGERECT: break;
    case WM_QUERYDRAGICON   : std::fprintf(stdout, "%c%X%s", '[', WM_QUERYDRAGICON,    "]: Windows > Query Drag Icon"                            "\r\n"); break;
    case WM_QUERYENDSESSION : std::fprintf(stdout, "%c%X%s", '[', WM_QUERYENDSESSION,  "]: Windows > Query End Session"                          "\r\n"); break;
    case WM_QUERYNEWPALETTE : std::fprintf(stdout, "%c%X%s", '[', WM_QUERYNEWPALETTE,  "]: Windows > Query New Palette"                          "\r\n"); break;
    case WM_QUERYOPEN       : std::fprintf(stdout, "%c%X%s", '[', WM_QUERYOPEN,        "]: Windows > Query Open"                                 "\r\n"); break;
    case WM_QUERYUISTATE    : std::fprintf(stdout, "%c%X%s", '[', WM_QUERYUISTATE,     "]: Windows > Query User-Interface State"                 "\r\n"); break;
    case WM_QUEUESYNC       : std::fprintf(stdout, "%c%X%s", '[', WM_QUEUESYNC,        "]: Windows > Queue Synchronization"                      "\r\n"); break;
    case WM_QUIT            : std::fprintf(stdout, "%c%X%s", '[', WM_QUIT,             "]: Windows > Quit" "\r\n"); { ::PostQuitMessage(0x0u); } break;
    case WM_RASDIALEVENT    : std::fprintf(stdout, "%c%X%s", '[', WM_RASDIALEVENT,     "]: Windows > Routing & Remote Access Service Dial Event" "\r\n"); break;
    case WM_RBUTTONDBLCLK   : std::fprintf(stdout, "%c%X%s", '[', WM_RBUTTONDBLCLK,    "]: Windows > Right (Mouse) Button Double-Click"          "\r\n"); break;
    case WM_RBUTTONDOWN     : std::fprintf(stdout, "%c%X%s", '[', WM_RBUTTONDOWN,      "]: Windows > Right (Mouse) Button Down"                  "\r\n"); break;
    case WM_RBUTTONUP       : std::fprintf(stdout, "%c%X%s", '[', WM_RBUTTONUP,        "]: Windows > Right (Mouse) Button Up"                    "\r\n"); break;
    case WM_RCRESULT        : std::fprintf(stdout, "%c%X%s", '[', WM_RCRESULT,         "]: Windows > RC Result"                                  "\r\n"); break;
    case WM_RENDERALLFORMATS: std::fprintf(stdout, "%c%X%s", '[', WM_RENDERALLFORMATS, "]: Windows > Render All Formats"                         "\r\n"); break;
    case WM_RENDERFORMAT    : std::fprintf(stdout, "%c%X%s", '[', WM_RENDERFORMAT,     "]: Windows > Render Format"                              "\r\n"); break;
    case WM_SETCURSOR       : std::fprintf(stdout, "%c%X%s", '[', WM_SETCURSOR,        "]: Windows > Set Cursor"                                 "\r\n"); break;
    case WM_SETFOCUS        : std::fprintf(stdout, "%c%X%s", '[', WM_SETFOCUS,         "]: Windows > Set Focus"                                  "\r\n"); break;
    case WM_SETFONT         : std::fprintf(stdout, "%c%X%s", '[', WM_SETFONT,          "]: Windows > Set Font"                                   "\r\n"); break;
    case WM_SETHOTKEY       : std::fprintf(stdout, "%c%X%s", '[', WM_SETHOTKEY,        "]: Windows > Set Hotkey"                                 "\r\n"); break;
    case WM_SETICON         : std::fprintf(stdout, "%c%X%s", '[', WM_SETICON,          "]: Windows > Set Icon"                                   "\r\n"); break;
    case WM_SETREDRAW       : std::fprintf(stdout, "%c%X%s", '[', WM_SETREDRAW,        "]: Windows > Set Redraw"                                 "\r\n"); break;
    case WM_SETTEXT         : std::fprintf(stdout, "%c%X%s", '[', WM_SETTEXT,          "]: Windows > Set Text"                                   "\r\n"); break;
    case WM_SHOWWINDOW      : std::fprintf(stdout, "%c%X%s", '[', WM_SHOWWINDOW,       "]: Windows > Show Window"                                "\r\n"); break;
    case WM_SIZE            : std::fprintf(stdout, "%c%X%s", '[', WM_SIZE,             "]: Windows > Size"                                       "\r\n"); break;
    case WM_SIZECLIPBOARD   : std::fprintf(stdout, "%c%X%s", '[', WM_SIZECLIPBOARD,    "]: Windows > Size Clipboard"                             "\r\n"); break;
    case WM_SIZING          : std::fprintf(stdout, "%c%X%s", '[', WM_SIZING,           "]: Windows > Sizing"                                     "\r\n"); break;
    case WM_SKB             : std::fprintf(stdout, "%c%X%s", '[', WM_SKB,              "]: Windows > SketchUp Backup"                            "\r\n"); break;
    case WM_SPOOLERSTATUS   : std::fprintf(stdout, "%c%X%s", '[', WM_SPOOLERSTATUS,    "]: Windows > Spooler Status"                             "\r\n"); break;
    case WM_STYLECHANGED    : std::fprintf(stdout, "%c%X%s", '[', WM_STYLECHANGED,     "]: Windows > Style Changed"                              "\r\n"); break;
    case WM_STYLECHANGING   : std::fprintf(stdout, "%c%X%s", '[', WM_STYLECHANGING,    "]: Windows > Style Changing"                             "\r\n"); break;
    case WM_SYNCPAINT       : std::fprintf(stdout, "%c%X%s", '[', WM_SYNCPAINT,        "]: Windows > Synchronized Paint"                         "\r\n"); break;
    case WM_SYSCHAR         : std::fprintf(stdout, "%c%X%s", '[', WM_SYSCHAR,          "]: Windows > System Character"                           "\r\n"); break;
    case WM_SYSCOLORCHANGE  : std::fprintf(stdout, "%c%X%s", '[', WM_SYSCOLORCHANGE,   "]: Windows > System Color Change"                        "\r\n"); break;
    case WM_SYSCOMMAND      : std::fprintf(stdout, "%c%X%s", '[', WM_SYSCOMMAND,       "]: Windows > System Command"                             "\r\n"); break;
    case WM_SYSDEADCHAR     : std::fprintf(stdout, "%c%X%s", '[', WM_SYSDEADCHAR,      "]: Windows > System Dead Character"                      "\r\n"); break;
    case WM_SYSKEYDOWN      : std::fprintf(stdout, "%c%X%s", '[', WM_SYSKEYDOWN,       "]: Windows > System Key Down"                            "\r\n"); break;
    case WM_SYSKEYUP        : std::fprintf(stdout, "%c%X%s", '[', WM_SYSKEYUP,         "]: Windows > System Key Up"                              "\r\n"); break;
    case WM_SYSTIMER        : std::fprintf(stdout, "%c%X%s", '[', WM_SYSTIMER,         "]: Windows > System Timer"                               "\r\n"); break;
    case WM_TCARD           : std::fprintf(stdout, "%c%X%s", '[', WM_TCARD,            "]: Windows > Text Card"                                  "\r\n"); break;
    case WM_TIMECHANGE      : std::fprintf(stdout, "%c%X%s", '[', WM_TIMECHANGE,       "]: Windows > Time Change"                                "\r\n"); break;
    case WM_TIMER           : std::fprintf(stdout, "%c%X%s", '[', WM_TIMER,            "]: Windows > Timer"                                      "\r\n"); break;
    case WM_UNDO            : std::fprintf(stdout, "%c%X%s", '[', WM_UNDO,             "]: Windows > Undo"                                       "\r\n"); break;
    // case WM_UNICHAR: break;
    case WM_UNINITMENUPOPUP: std::fprintf(stdout, "%c%X%s", '[', WM_UNINITMENUPOPUP, "]: Windows > Uninitiate Menu Pop-Up" "\r\n"); break;
    case WM_UPDATEUISTATE  : std::fprintf(stdout, "%c%X%s", '[', WM_UPDATEUISTATE,   "]: Windows > Update UI State"        "\r\n"); break;
    // case WM_USER: break;
    case WM_USERCHANGED      : std::fprintf(stdout, "%c%X%s", '[', WM_USERCHANGED,       "]: Windows > User Changed"              "\r\n"); break;
    case WM_VKEYTOITEM       : std::fprintf(stdout, "%c%X%s", '[', WM_VKEYTOITEM,        "]: Windows > Virtual Key to Item"       "\r\n"); break;
    case WM_VSCROLL          : std::fprintf(stdout, "%c%X%s", '[', WM_VSCROLL,           "]: Windows > Vertical Scroll"           "\r\n"); break;
    case WM_VSCROLLCLIPBOARD : std::fprintf(stdout, "%c%X%s", '[', WM_VSCROLLCLIPBOARD,  "]: Windows > Vertical Scroll Clipboard" "\r\n"); break;
    case WM_WINDOWPOSCHANGED : std::fprintf(stdout, "%c%X%s", '[', WM_WINDOWPOSCHANGED,  "]: Windows > Window Position Changed"   "\r\n"); break;
    case WM_WINDOWPOSCHANGING: std::fprintf(stdout, "%c%X%s", '[', WM_WINDOWPOSCHANGING, "]: Windows > Window Position Changing"  "\r\n"); break;
    case WM_WININICHANGE     : std::fprintf(stdout, "%c%X%s", '[', WM_WININICHANGE,      "]: Windows > Windows INI Change"        "\r\n"); break;
    // case WM_WNT_CONVERTREQUESTEX: break;
    // case WM_XBUTTONDBLCLK       : break;
    case WM_XBUTTONDOWN: std::fprintf(stdout, "%c%X%s", '[', WM_XBUTTONDOWN, "]: Windows > X Button Down" "\r\n"); break;
    case WM_XBUTTONUP  : std::fprintf(stdout, "%c%X%s", '[', WM_XBUTTONUP,   "]: Windows > X Button Up"   "\r\n"); break;
    default: std::fputs("[...]: ?" "\r\n", stdout); break;
  }

  // ...
  return ::DefWindowProc(windowHandle, message, parameter, subparameter);
}

/* Main */
int WinMain(HINSTANCE const instanceHandle, HINSTANCE const, LPSTR const, int const windowAppearance) {
  CHAR     moduleFileName[MAX_PATH];
  MSG      threadMessage = MSG();
  HWND     windowHandle  = NULL;
  WNDCLASS windowClass   = WNDCLASS();

  // ...
  ::GetModuleFileName(static_cast<HMODULE>(NULL), moduleFileName, MAX_PATH);

  threadMessage.hwnd    = windowHandle;
  threadMessage.message = 0x0u;
  threadMessage.lParam  = 0x0L;
  threadMessage.wParam  = EXIT_SUCCESS;
  threadMessage.time    = 0u;
  threadMessage.pt      = POINT();
  threadMessage.pt.x    = 0L;
  threadMessage.pt.y    = 0L;

  windowClass.cbClsExtra    = 0;
  windowClass.cbWndExtra    = 0;
  windowClass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
  windowClass.hCursor       = ::LoadCursor(static_cast<HINSTANCE>(NULL), IDC_ARROW); // --> static_cast<HCURSOR>(::LoadImage(NULL, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED))
  windowClass.hIcon         = ::ExtractIcon(static_cast<HINSTANCE>(::GetCurrentProcess()), moduleFileName, 0u);
  windowClass.hInstance     = instanceHandle;
  windowClass.lpfnWndProc   = &windowProcedure;
  windowClass.lpszClassName = "window";
  windowClass.lpszMenuName  = static_cast<LPCSTR>(NULL);
  windowClass.style         = CS_HREDRAW | CS_VREDRAW;

  // ...
  if (0x0u == ::RegisterClassA(&windowClass)) {
    std::fputs("Unable to create window (failed to register window class)", stderr);
    return EXIT_FAILURE;
  }

  windowHandle = ::CreateWindowExA(0x0, windowClass.lpszClassName, "Windows API: event messages", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 320, 480, static_cast<HWND>(NULL), static_cast<HMENU>(NULL), windowClass.hInstance, static_cast<LPVOID>(NULL));
  if (NULL == windowHandle) {
    std::fputs("Unable to create window", stderr);
    ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

    return EXIT_FAILURE;
  }

  ::ShowWindow(windowHandle, SW_SHOW | windowAppearance);
  ::UpdateWindow(windowHandle);

  // ...
  while (FALSE != ::GetMessage(&threadMessage, static_cast<HWND>(NULL), 0u, 0u)) {
    ::TranslateMessage(&threadMessage);
    ::DispatchMessage(&threadMessage);
  }

  ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

  // ...
  return threadMessage.wParam;
}
