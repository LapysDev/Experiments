/* ... */
#define _WIN32_WINNT 0x0501 // --> _WIN32_WINNT_WINXP

/* Import */
#include <windows.h>
# include <wow64apiset.h>

/* Main */
int WinMain(HINSTANCE const, HINSTANCE const, LPSTR const, int const) {
  SYSTEM_INFO systemInformation;

  // ...
  #if _WIN32_WINNT >= 0x0501 /* --> _WIN32_WINNT_WINXP */
    USHORT processArchitecture;
    USHORT systemArchitecture;

    // ...
    if (FALSE != ::IsWow64Process2(::GetCurrentProcess(), &processArchitecture, &systemArchitecture) ? IMAGE_FILE_MACHINE_UNKNOWN != processArchitecture : false)
      ::GetNativeSystemInfo(&systemInformation);
    else
  #endif
  ::GetSystemInfo(&systemInformation);
}
