void CenterWindowOnScreen(HWND hwnd)
{
    RECT wnd_rect;
    GetWindowRect(hwnd, &wnd_rect);

    RECT screen_rect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, reinterpret_cast<PVOID>(&screen_rect), 0);

    int scr_wd = screen_rect.right - screen_rect.left;
    int scr_hgt = screen_rect.bottom - screen_rect.top;
    int wnd_wd = wnd_rect.right - wnd_rect.left;
    int wnd_hgt = wnd_rect.bottom - wnd_rect.top;

    int x = (scr_wd - wnd_wd) / 2;
    int y = (scr_hgt - wnd_hgt) / 2;

    SetWindowPos(hwnd, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}
