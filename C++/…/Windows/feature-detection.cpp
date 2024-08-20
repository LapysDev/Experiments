#ifdef _WIN32_WINNT
# if _WIN32_WINNT+0 >= 0x0501 // --> _WIN32_WINNT_WINXP
  // Also do a runtime version check
  HMODULE module = NULL;

  if (FALSE != ::GetModuleHandleExW(0x00u, L"kernel32" ".dll", &module)) {
    if (NULL != module)
    std::printf("[...]: %p -> %p / %p" "\r\n", (void*) module, (void*) ::GetProcAddress(module, "GetModuleHandleExW"), (void*) &::GetModuleHandleExW);
  }

  else
    std::puts("[...]: nothing" "\r\n");
# endif
#endif
