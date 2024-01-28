#include <cstdio>
#include <windows.h>

/* ... */
enum WindowsVersion {
  WindowsXP,
  WindowsXP_ServicePack1,
  WindowsXP_ServicePack2,
  WindowsXP_ServicePack3,
  WindowsVista,
  WindowsVista_ServicePack1,
  WindowsVista_ServicePack2,
  Windows7,
  Windows7_ServicePack1,
  Windows8,
  Windows8_Point1,
  Windows10_Threshold,
  Windows10,
  WindowsServer
};

// ...
bool featuresWindowsVersion(WORD const majorVersion, WORD const minorVersion, WORD const servicePackVersion);
bool featuresWindowsVersion(WindowsVersion const version) {
  OSVERSIONINFOEXW information = {};

  // ...
  information.dwBuildNumber       = 0uL;
  information.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
  information.dwPlatformId        = 0uL;
  *information.szCSDVersion       = L'\0';
  information.wServicePackMinor   = 0u;
  information.wSuiteMask          = 0x00u;

  if (version == ::WindowsServer) {
    information.dwMajorVersion    = 0uL;
    information.dwMinorVersion    = 0uL;
    information.wProductType      = VER_NT_WORKSTATION;
    information.wServicePackMajor = 0u;

    return FALSE == VerifyVersionInfoW(&information, VER_PRODUCT_TYPE, ::VerSetConditionMask(0x00uL, VER_PRODUCT_TYPE, VER_EQUAL));
  }

  else {
    ULONGLONG conditionMask = 0x00u;

    // ...
    conditionMask            = ::VerSetConditionMask(conditionMask, VER_MAJORVERSION,     VER_GREATER_EQUAL);
    conditionMask            = ::VerSetConditionMask(conditionMask, VER_MINORVERSION,     VER_GREATER_EQUAL);
    conditionMask            = ::VerSetConditionMask(conditionMask, VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);
    information.wProductType = 0x00u;

    switch (version) {
      case WindowsXP:                 information.dwMajorVersion = HIBYTE(_WIN32_WINNT_WINXP);        information.dwMinorVersion = LOBYTE(_WIN32_WINNT_WINXP);        information.wServicePackMajor = 0u; break;
      case WindowsXP_ServicePack1:    information.dwMajorVersion = HIBYTE(_WIN32_WINNT_WINXP);        information.dwMinorVersion = LOBYTE(_WIN32_WINNT_WINXP);        information.wServicePackMajor = 1u; break;
      case WindowsXP_ServicePack2:    information.dwMajorVersion = HIBYTE(_WIN32_WINNT_WINXP);        information.dwMinorVersion = LOBYTE(_WIN32_WINNT_WINXP);        information.wServicePackMajor = 2u; break;
      case WindowsXP_ServicePack3:    information.dwMajorVersion = HIBYTE(_WIN32_WINNT_WINXP);        information.dwMinorVersion = LOBYTE(_WIN32_WINNT_WINXP);        information.wServicePackMajor = 3u; break;
      case WindowsVista:              information.dwMajorVersion = HIBYTE(_WIN32_WINNT_VISTA);        information.dwMinorVersion = LOBYTE(_WIN32_WINNT_VISTA);        information.wServicePackMajor = 0u; break;
      case WindowsVista_ServicePack1: information.dwMajorVersion = HIBYTE(_WIN32_WINNT_VISTA);        information.dwMinorVersion = LOBYTE(_WIN32_WINNT_VISTA);        information.wServicePackMajor = 1u; break;
      case WindowsVista_ServicePack2: information.dwMajorVersion = HIBYTE(_WIN32_WINNT_VISTA);        information.dwMinorVersion = LOBYTE(_WIN32_WINNT_VISTA);        information.wServicePackMajor = 2u; break;
      case Windows7:                  information.dwMajorVersion = HIBYTE(_WIN32_WINNT_WIN7);         information.dwMinorVersion = LOBYTE(_WIN32_WINNT_WIN7);         information.wServicePackMajor = 0u; break;
      case Windows7_ServicePack1:     information.dwMajorVersion = HIBYTE(_WIN32_WINNT_WIN7);         information.dwMinorVersion = LOBYTE(_WIN32_WINNT_WIN7);         information.wServicePackMajor = 1u; break;
      case Windows8:                  information.dwMajorVersion = HIBYTE(_WIN32_WINNT_WIN8);         information.dwMinorVersion = LOBYTE(_WIN32_WINNT_WIN8);         information.wServicePackMajor = 0u; break;
      case Windows8_Point1:           information.dwMajorVersion = HIBYTE(_WIN32_WINNT_WINBLUE);      information.dwMinorVersion = LOBYTE(_WIN32_WINNT_WINBLUE);      information.wServicePackMajor = 0u; break;
      case Windows10:
      case Windows10_Threshold:       information.dwMajorVersion = HIBYTE(_WIN32_WINNT_WINTHRESHOLD); information.dwMinorVersion = LOBYTE(_WIN32_WINNT_WINTHRESHOLD); information.wServicePackMajor = 0u; break;
      default: break;
    }

    return FALSE != ::VerifyVersionInfoW(&information, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, conditionMask);
  }

  return false;
}

/* Main */
int main(int, char*[]) /* noexcept */ {}
