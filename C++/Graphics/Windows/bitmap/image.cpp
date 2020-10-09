/* Import */
#include <iostream>
#include <stdlib.h> // Standard Library
#include <windows.h> // Windows

/* Namespace > Image */
namespace Image {
    /* Function */
        // Create Bitmap From Display
        HBITMAP createBitmapFromDisplay() {
            // Initialization > (Bitmap, Display) ...
            HDC bitmapGraphicsDeviceContext;
            HGDIOBJ bitmapDummyObject;
            HBITMAP bitmapHandle;

            HDC displayGraphicsDeviceContext;
            int displayHeight, displayWidth;

            // Update > (Display, Bitmap) ...
            displayGraphicsDeviceContext = ::GetDC(0x0);
            displayHeight = ::GetSystemMetrics(SM_CYVIRTUALSCREEN);
            displayWidth = ::GetSystemMetrics(SM_CXVIRTUALSCREEN);

            bitmapGraphicsDeviceContext = ::CreateCompatibleDC(displayGraphicsDeviceContext);
            bitmapHandle = ::CreateCompatibleBitmap(displayGraphicsDeviceContext, displayWidth, displayHeight);

            // Update > ... Graphics Device Context
            bitmapDummyObject = ::SelectObject(bitmapGraphicsDeviceContext, bitmapHandle);
            ::BitBlt(bitmapGraphicsDeviceContext, 0, 0, displayWidth, displayHeight, displayGraphicsDeviceContext, 0, 0, SRCCOPY);
            bitmapHandle = (HBITMAP) ::SelectObject(bitmapGraphicsDeviceContext, bitmapDummyObject);

            // Deletion
            ::ReleaseDC(0x0, displayGraphicsDeviceContext);
            ::DeleteDC(bitmapGraphicsDeviceContext);

            // Return
            return bitmapHandle;
        }

        // Create Bitmap Mask [From Color]
        HBITMAP createBitmapMask(HBITMAP bitmapHandle, const COLORREF transparencyColor) {
            // Evaluation > Bitmap Mask Handle
            HBITMAP bitmapMaskHandle;

            // Initialization > Bitmap (Mask) ...
            BITMAP bitmap;
            HGDIOBJ bitmapDummyObject;
            HDC bitmapGraphicsDeviceContext = ::CreateCompatibleDC(0x0);

            HGDIOBJ bitmapMaskDummyObject;
            HDC bitmapMaskGraphicsDeviceContext = ::CreateCompatibleDC(0x0);

            // Update > Bitmap (Mask Handle)
            ::GetObject(bitmapHandle, sizeof(BITMAP), &bitmap);
            bitmapMaskHandle = ::CreateBitmap(bitmap.bmWidth, bitmap.bmHeight, 1, 1, 0x0);

            // Update > ... Graphics Device Context
            bitmapDummyObject = ::SelectObject(bitmapGraphicsDeviceContext, (HGDIOBJ) (HBITMAP) bitmapHandle);
            bitmapMaskDummyObject = ::SelectObject(bitmapMaskGraphicsDeviceContext, (HGDIOBJ) (HBITMAP) bitmapMaskHandle);

            // Logic
            #if true
                // Loop > Update > Bitmap Mask Graphics Device Context --- WARN (Lapys) -> Ad-hoc method for creating the image mask.
                for (unsigned bitmapPixelRowIterator = 0u; bitmapPixelRowIterator ^ bitmap.bmWidth; bitmapPixelRowIterator++)
                for (unsigned bitmapPixelColumnIterator = 0u; bitmapPixelColumnIterator ^ bitmap.bmHeight; bitmapPixelColumnIterator++)
                    ::GetPixel(bitmapGraphicsDeviceContext, bitmapPixelRowIterator, bitmapPixelColumnIterator) == transparencyColor ?
                    ::SetPixelV(bitmapMaskGraphicsDeviceContext, bitmapPixelRowIterator, bitmapPixelColumnIterator, 16777215 /* -> RGB(255, 255, 255) */) :
                    ::SetPixelV(bitmapMaskGraphicsDeviceContext, bitmapPixelRowIterator, bitmapPixelColumnIterator, 0);
            #else
                // Update > ... Graphics Device Context --- WARN (Lapys) -> This code doesn`t work for some God-forsaken reason; Weeks have gone into rectifying this, don`t fix it!.
                ::SetBkColor(bitmapMaskGraphicsDeviceContext, transparencyColor);
                ::BitBlt(bitmapMaskGraphicsDeviceContext, 0, 0, bitmap.bmWidth, bitmap.bmHeight, bitmapGraphicsDeviceContext, 0, 0, SRCCOPY);

                ::BitBlt(bitmapGraphicsDeviceContext, 0, 0, bitmap.bmWidth, bitmap.bmHeight, bitmapMaskGraphicsDeviceContext, 0, 0, SRCINVERT);
            #endif

            // Update > Bitmap Mask Handle
            /*bitmapHandle = (HBITMAP) */::SelectObject(bitmapGraphicsDeviceContext, bitmapDummyObject);
            bitmapMaskHandle = (HBITMAP) ::SelectObject(bitmapMaskGraphicsDeviceContext, bitmapMaskDummyObject);

            // Deletion
            ::DeleteDC(bitmapGraphicsDeviceContext);
            ::DeleteDC(bitmapMaskGraphicsDeviceContext);

            // Return
            return bitmapMaskHandle;
        }
        HBITMAP createBitmapMask(HBITMAP bitmapHandle) {
            // Initialization > (Bitmap ..., Transparency Color)
            HGDIOBJ bitmapDummyObject;
            HDC bitmapGraphicsDeviceContext = ::CreateCompatibleDC(0x0);

            COLORREF transparencyColor = 0;

            // ...; Update > Transparency Color; ...
            bitmapDummyObject = ::SelectObject(bitmapGraphicsDeviceContext, bitmapHandle);
            transparencyColor = ::GetPixel(bitmapGraphicsDeviceContext, 0, 0);

            ::SelectObject(bitmapGraphicsDeviceContext, bitmapDummyObject);

            // Deletion
            ::DeleteDC(bitmapGraphicsDeviceContext);

            // Return
            return Image::createBitmapMask(bitmapHandle, transparencyColor);
        }

        // Download Image [As Bitmap]
        void downloadImage(HBITMAP bitmapHandle) {
            // PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp) {
            //     BITMAP bmp;
            //     PBITMAPINFO pbmi;
            //     WORD    cClrBits;

            //     // Retrieve the bitmap color format, width, and height.
            //     if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp))
            //         errhandler("GetObject", hwnd);

            //     // Convert the color format to a count of bits.
            //     cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
            //     if (cClrBits == 1)
            //         cClrBits = 1;
            //     else if (cClrBits <= 4)
            //         cClrBits = 4;
            //     else if (cClrBits <= 8)
            //         cClrBits = 8;
            //     else if (cClrBits <= 16)
            //         cClrBits = 16;
            //     else if (cClrBits <= 24)
            //         cClrBits = 24;
            //     else cClrBits = 32;

            //     // Allocate memory for the BITMAPINFO structure. (This structure
            //     // contains a BITMAPINFOHEADER structure and an array of RGBQUAD
            //     // data structures.)

            //     if (cClrBits < 24)
            //         pbmi = (PBITMAPINFO) LocalAlloc(LPTR,
            //         sizeof(BITMAPINFOHEADER) +
            //         sizeof(RGBQUAD) * (1<< cClrBits));

            //     // There is no RGBQUAD array for these formats: 24-bit-per-pixel or 32-bit-per-pixel

            //     else
            //         pbmi = (PBITMAPINFO) LocalAlloc(LPTR,
            //         sizeof(BITMAPINFOHEADER));

            //     // Initialize the fields in the BITMAPINFO structure.

            //     pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            //     pbmi->bmiHeader.biWidth = bmp.bmWidth;
            //     pbmi->bmiHeader.biHeight = bmp.bmHeight;
            //     pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
            //     pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
            //     if (cClrBits < 24)
            //         pbmi->bmiHeader.biClrUsed = (1<<cClrBits);

            //     // If the bitmap is not compressed, set the BI_RGB flag.
            //     pbmi->bmiHeader.biCompression = BI_RGB;

            //     // Compute the number of bytes in the array of color
            //     // indices and store the result in biSizeImage.
            //     // The width must be DWORD aligned unless the bitmap is RLE
            //     // compressed.
            //     pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8
            //         * pbmi->bmiHeader.biHeight;
            //     // Set biClrImportant to 0, indicating that all of the
            //     // device colors are important.
            //     pbmi->bmiHeader.biClrImportant = 0;
            //     return pbmi;
            // }

            /*
                int CreateBMPFile(HWND hwnd, LPCTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC) {
                    HANDLE hf;                  // file handle
                    BITMAPFILEHEADER hdr;       // bitmap file-header
                    PBITMAPINFOHEADER pbih;     // bitmap info-header
                    //LPBYTE lpBits;            // memory pointer
                    DWORD dwTotal;              // total count of bytes
                    DWORD cb;                   // incremental count of bytes
                    BYTE *hp;                   // byte pointer
                    DWORD dwTmp;
                    int ret = 0;


                    pbi = CreateBitmapInfoStruct(0x0, hBMP);
                    if(pbi == 0x0)
                    {
                        return ret;
                    }
                    pbih = (PBITMAPINFOHEADER) pbi;

                    // lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);
                    // if (!lpBits)
                    // {
                         //errhandler("GlobalAlloc", hwnd);
                     //   return;
                    // }

                    RGBQUAD *rgbq;
                    rgbq = pbi->bmiColors;
                    PALETTEENTRY pe[256];
                    GetSystemPaletteEntries(hDC, 0, pbih->biClrUsed, pe);
                    for(DWORD i = 0; i < pbih->biClrUsed; i++)
                    {
                        rgbq[i].rgbRed = pe[i].peRed;
                        rgbq[i].rgbBlue = pe[i].peBlue;
                        rgbq[i].rgbGreen = pe[i].peGreen;
                        rgbq[i].rgbReserved = 0;
                    }

                    // CE5.0 + CE6.0
                    HDC tHDC;
                    tHDC = CreateCompatibleDC(hDC);
                    HBITMAP h = CreateDIBSection(hDC, pbi, DIB_PAL_COLORS, (void **)&hp, 0x0, 0);
                    if(h == 0x0)
                    {
                        goto close_bmp;
                    }
                    SelectObject(tHDC, h);
                    BitBlt(tHDC, 0, 0, SCREEN_W, SCREEN_H, hDC, 0, 0, SRCCOPY);

                    // Retrieve the color table (RGBQUAD array) and the bits
                    // (array of palette indices) from the DIB.
                    // if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi,
                        // DIB_RGB_COLORS))
                    // {
                        //errhandler("GetDIBits", hwnd);
                        // return;
                    // }

                    // Create the .BMP file.
                    hf = CreateFile(pszFile,
                                   GENERIC_READ | GENERIC_WRITE,
                                   (DWORD) 0,
                                    0x0,
                                   CREATE_ALWAYS,
                                   FILE_ATTRIBUTE_NORMAL,
                                   (HANDLE) 0x0);
                    if (hf == INVALID_HANDLE_VALUE)
                    {
                        //errhandler("CreateFile", hwnd);
                        goto close_bmp;
                    }
                    hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"
                    // Compute the size of the entire file.
                    hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) +
                                 pbih->biSize + pbih->biClrUsed
                                 * sizeof(RGBQUAD) + pbih->biSizeImage);
                    hdr.bfReserved1 = 0;
                    hdr.bfReserved2 = 0;

                    // Compute the offset to the array of color indices.
                    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
                                    pbih->biSize + pbih->biClrUsed
                                    * sizeof (RGBQUAD);

                    // Copy the BITMAPFILEHEADER into the .BMP file.
                    if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER),
                        (LPDWORD) &dwTmp,  0x0))
                    {
                       //errhandler("WriteFile", hwnd);
                        goto close_bmp;
                    }

                    // Copy the BITMAPINFOHEADER and RGBQUAD array into the file.
                    if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER)
                                  + pbih->biClrUsed * sizeof (RGBQUAD),
                                  (LPDWORD) &dwTmp, ( 0x0)))
                    {
                        //errhandler("WriteFile", hwnd);
                    }

                    // Copy the array of color indices into the .BMP file.
                    dwTotal = cb = pbih->biSizeImage;

                    //hp = lpBits;
                    if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,0x0))
                    {
                        //errhandler("WriteFile", hwnd);
                        goto close_bmp;
                    }



                close_bmp:
                    // Close the .BMP file.
                    if(hf != INVALID_HANDLE_VALUE)
                    {
                        if (!CloseHandle(hf))
                        {
                           //errhandler("CloseHandle", hwnd);
                        }
                        else
                        {
                            ret = 1;
                        }
                    }
                    // Free memory.
                    // GlobalFree((HGLOBAL)lpBits);
                    if(tHDC != 0x0)
                        DeleteObject(tHDC);
                    if(h != 0x0)
                        DeleteObject(h);
                    if(pbi != 0x0)
                    {
                        //LocalFree(pbi);
                        free(pbi);
                    }

                    return ret;

                }

                OR

                // void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi,  HBITMAP hBMP, HDC hDC)  {
                //     HANDLE hf;                 // file handle
                //     BITMAPFILEHEADER hdr;       // bitmap file-header
                //     PBITMAPINFOHEADER pbih;     // bitmap info-header
                //     LPBYTE lpBits;              // memory pointer
                //     DWORD dwTotal;              // total count of bytes
                //     DWORD cb;                   // incremental count of bytes
                //     BYTE *hp;                   // byte pointer
                //     DWORD dwTmp;

                //     pbih = (PBITMAPINFOHEADER) pbi;
                //     lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

                //     if (!lpBits)
                //         errhandler("GlobalAlloc", hwnd);

                //     // Retrieve the color table (RGBQUAD array) and the bits
                //     // (array of palette indices) from the DIB.
                //     if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi,
                //         DIB_RGB_COLORS))
                //     {
                //         errhandler("GetDIBits", hwnd);
                //     }

                //     // Create the .BMP file.
                //     hf = CreateFile(pszFile,
                //         GENERIC_READ | GENERIC_WRITE,
                //         (DWORD) 0,
                //         0x0,
                //         CREATE_ALWAYS,
                //         FILE_ATTRIBUTE_NORMAL,
                //         (HANDLE) 0x0);
                //     if (hf == INVALID_HANDLE_VALUE)
                //         errhandler("CreateFile", hwnd);
                //     hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"
                //     // Compute the size of the entire file.
                //     hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) +
                //         pbih->biSize + pbih->biClrUsed
                //         * sizeof(RGBQUAD) + pbih->biSizeImage);
                //     hdr.bfReserved1 = 0;
                //     hdr.bfReserved2 = 0;

                //     // Compute the offset to the array of color indices.
                //     hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
                //         pbih->biSize + pbih->biClrUsed
                //         * sizeof (RGBQUAD);

                //     // Copy the BITMAPFILEHEADER into the .BMP file.
                //     if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER),
                //         (LPDWORD) &dwTmp,  0x0))
                //     {
                //         errhandler("WriteFile", hwnd);
                //     }

                //     // Copy the BITMAPINFOHEADER and RGBQUAD array into the file.
                //     if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER)
                //         + pbih->biClrUsed * sizeof (RGBQUAD),
                //         (LPDWORD) &dwTmp, ( 0x0)))
                //         errhandler("WriteFile", hwnd);

                //     // Copy the array of color indices into the .BMP file.
                //     dwTotal = cb = pbih->biSizeImage;
                //     hp = lpBits;
                //     if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,0x0))
                //         errhandler("WriteFile", hwnd);

                //     // Close the .BMP file.
                //     if (!CloseHandle(hf))
                //         errhandler("CloseHandle", hwnd);

                //     // Free memory.
                //     GlobalFree((HGLOBAL)lpBits);
                // }
            */
        }

        // Draw Image [To Window]
        void drawImage(HBITMAP bitmapHandle, const HWND windowHandle, const int xCoordinate = 0, const int yCoordinate = 0) {
            // Initialization  > (Bitmap, Window) ...
            BITMAP bitmap;
            HGDIOBJ bitmapDummyObject;
            HDC bitmapGraphicsDeviceContext;

            HDC windowGraphicsDeviceContext;
            PAINTSTRUCT windowPaintInformation;

            // Update > (Bitmap, ... Graphics Device Context)
            ::GetObject(bitmapHandle, sizeof(BITMAP), &bitmap);

            windowGraphicsDeviceContext = ::BeginPaint(windowHandle, &windowPaintInformation);
            bitmapGraphicsDeviceContext = ::CreateCompatibleDC(windowGraphicsDeviceContext);

            // Update > ... Graphics Device Context
            bitmapDummyObject = ::SelectObject(bitmapGraphicsDeviceContext, bitmapHandle);
            ::BitBlt(windowGraphicsDeviceContext, xCoordinate, yCoordinate, bitmap.bmWidth, bitmap.bmHeight, bitmapGraphicsDeviceContext, 0, 0, SRCCOPY);
            /*bitmapHandle = (HBITMAP) */::SelectObject(bitmapGraphicsDeviceContext, bitmapDummyObject);

            // Deletion
            ::DeleteObject(bitmapDummyObject);
            ::DeleteDC(bitmapGraphicsDeviceContext);
            ::DeleteObject(bitmapHandle);

            ::ReleaseDC(windowHandle, windowGraphicsDeviceContext);
            ::EndPaint(windowHandle, &windowPaintInformation);
        }

        // Request Bitmap File --- NOTE (Lapys) -> Bitmap may be OEM or stand-alone if the instance handle is `0x0`.
        HBITMAP requestBitmapFile(const char* filepath, HINSTANCE instanceHandle = (HMODULE) ::GetWindowLong(::GetActiveWindow(), GWL_HINSTANCE)) {
            // Logic > Update > Instance Handle
            if (::GetLastError()) instanceHandle = 0x0;

            // Evaluation > Bitmap Handle
            HBITMAP bitmapHandle = (HBITMAP) ::LoadImage(instanceHandle, filepath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

            // Logic
            if (0x0 == bitmapHandle) {
                // Initialization > (Error ID (Buffer ...), ... Console Buffer Handle)
                const unsigned short errorID = ::GetLastError();
                char errorIDBuffer[6] {'0', '\0', '\0', '\0', '\0', '\0'};
                char *errorIDBufferPointer = errorIDBuffer;

                HANDLE screenConsoleBufferHandle; // NOTE (Lapys) -> Keep the current active screen buffer active afterwards.
                const HANDLE recentActiveScreenConsoleBufferHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);

                // Update > Screen Console Buffer Handle; ...
                screenConsoleBufferHandle = ::CreateFile("CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, 0x0, OPEN_ALWAYS, 0, 0x0);
                ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);

                // Logic > Update > Error ID Buffer ...
                if (errorID) {
                    for (unsigned short iterator = errorID; iterator; iterator /= 10u) errorIDBufferPointer++;
                    for (unsigned short iterator = errorID; iterator; iterator /= 10u) *(--errorIDBufferPointer) = '0' + (char) (iterator % 10u);
                }

                // ... Print
                ::WriteFile(screenConsoleBufferHandle, "[ERROR (", 8uL, 0x0, 0x0);
                for (; *errorIDBufferPointer; errorIDBufferPointer++) ::WriteFile(screenConsoleBufferHandle, errorIDBufferPointer, 1uL, 0x0, 0x0);
                ::WriteFile(screenConsoleBufferHandle, ")]: Unable to retrieve requested bitmap file\n\r\0", 47uL, 0x0, 0x0);

                // Deletion; ...
                ::CloseHandle(screenConsoleBufferHandle);
                ::SetConsoleActiveScreenBuffer(recentActiveScreenConsoleBufferHandle);

                // Terminate
                ::exit(EXIT_FAILURE);
            }

            // Return
            return bitmapHandle;
        }

        // Request Joint Photographic Experts Group Image File
        /*
        #include <stdio.h>
    #include <windows.h>

     #include "wtypes.h"
    #pragma comment(lib,"gd132.lib")
    #pragma comment(lib,"user32.lib")
    // Helper function to retrieve current position of file pointer:
    inline int GetFilePointer(HANDLE FileHandle){
        return SetFilePointer(FileHandle, 0, 0, FILE_CURRENT);
        }
    //---------------------------------------------------------------------------

    // Screenshot
    //    -> FileName: Name of file to save screenshot to
    //    -> lpDDS: DirectDraw surface to capture
    //    <- Result: Success
    //
    extern bool SaveBMPFile(char *filename, HBITMAP bitmap, HDC bitmapDC, int width, int height){
        bool Success=false;
        HDC SurfDC=0x0;        // GDI-compatible device context for the surface
        HBITMAP OffscrBmp=0x0; // bitmap that is converted to a DIB
        HDC OffscrDC=0x0;      // offscreen DC that we can select OffscrBmp into
        LPBITMAPINFO lpbi=0x0; // bitmap format info; used by GetDIBits
        LPVOID lpvBits=0x0;    // pointer to bitmap bits array
        HANDLE BmpFile=INVALID_HANDLE_VALUE;    // destination .bmp file
        BITMAPFILEHEADER bmfh;  // .bmp file header

        // We need an HBITMAP to convert it to a DIB:
        if ((OffscrBmp = CreateCompatibleBitmap(bitmapDC, width, height)) == 0x0)
            return false;

        // The bitmap is empty, so let's copy the contents of the surface to it.
        // For that we need to select it into a device context. We create one.
        if ((OffscrDC = CreateCompatibleDC(bitmapDC)) == 0x0)
            return false;

        // Select OffscrBmp into OffscrDC:
        HBITMAP OldBmp = (HBITMAP)SelectObject(OffscrDC, OffscrBmp);

        // Now we can copy the contents of the surface to the offscreen bitmap:
        BitBlt(OffscrDC, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);

        // GetDIBits requires format info about the bitmap. We can have GetDIBits
        // fill a structure with that info if we pass a 0x0 pointer for lpvBits:
        // Reserve memory for bitmap info (BITMAPINFOHEADER + largest possible
        // palette):
        if ((lpbi = (LPBITMAPINFO)(new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)])) == 0x0)
            return false;


        ZeroMemory(&lpbi->bmiHeader, sizeof(BITMAPINFOHEADER));
        lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        // Get info but first de-select OffscrBmp because GetDIBits requires it:
        SelectObject(OffscrDC, OldBmp);
        if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, 0x0, lpbi, DIB_RGB_COLORS))
            return false;

        // Reserve memory for bitmap bits:
        if ((lpvBits = new char[lpbi->bmiHeader.biSizeImage]) == 0x0)
            return false;

        // Have GetDIBits convert OffscrBmp to a DIB (device-independent bitmap):
        if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, lpvBits, lpbi, DIB_RGB_COLORS))
            return false;

        // Create a file to save the DIB to:
        if ((BmpFile = CreateFile(filename,
                                  GENERIC_WRITE,
                                  0, 0x0,
                                  CREATE_ALWAYS,
                                  FILE_ATTRIBUTE_NORMAL,
                                  0x0)) == INVALID_HANDLE_VALUE)

                                  return false;

        DWORD Written;    // number of bytes written by WriteFile

        // Write a file header to the file:
        bmfh.bfType = 19778;        // 'BM'
        // bmfh.bfSize = ???        // we'll write that later
        bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
        // bmfh.bfOffBits = ???     // we'll write that later
        if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, 0x0))
            return false;

        if (Written < sizeof(bmfh))
            return false;

        // Write BITMAPINFOHEADER to the file:
        if (!WriteFile(BmpFile, &lpbi->bmiHeader, sizeof(BITMAPINFOHEADER), &Written, 0x0))
            return false;

        if (Written < sizeof(BITMAPINFOHEADER))
                return false;

        // Calculate size of palette:
        int PalEntries;
        // 16-bit or 32-bit bitmaps require bit masks:
        if (lpbi->bmiHeader.biCompression == BI_BITFIELDS)
            PalEntries = 3;
        else
            // bitmap is palletized?
            PalEntries = (lpbi->bmiHeader.biBitCount <= 8) ?
                // 2^biBitCount palette entries max.:
                (int)(1 << lpbi->bmiHeader.biBitCount)
            // bitmap is TrueColor -> no palette:
            : 0;
        // If biClrUsed use only biClrUsed palette entries:
        if(lpbi->bmiHeader.biClrUsed)
            PalEntries = lpbi->bmiHeader.biClrUsed;

        // Write palette to the file:
        if(PalEntries){
            if (!WriteFile(BmpFile, &lpbi->bmiColors, PalEntries * sizeof(RGBQUAD), &Written, 0x0))
                return false;

            if (Written < PalEntries * sizeof(RGBQUAD))
                return false;
            }

        // The current position in the file (at the beginning of the bitmap bits)
        // will be saved to the BITMAPFILEHEADER:
        bmfh.bfOffBits = GetFilePointer(BmpFile);

        // Write bitmap bits to the file:
        if (!WriteFile(BmpFile, lpvBits, lpbi->bmiHeader.biSizeImage, &Written, 0x0))
            return false;

        if (Written < lpbi->bmiHeader.biSizeImage)
            return false;

        // The current pos. in the file is the final file size and will be saved:
        bmfh.bfSize = GetFilePointer(BmpFile);

        // We have all the info for the file header. Save the updated version:
        SetFilePointer(BmpFile, 0, 0, FILE_BEGIN);
        if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, 0x0))
            return false;

        if (Written < sizeof(bmfh))
            return false;

        return true;
        }



    bool ScreenCapture(int x, int y, int width, int height, char *filename){
    // get a DC compat. w/ the screen
    HDC hDc = CreateCompatibleDC(0);

    // make a bmp in memory to store the capture in
    HBITMAP hBmp = CreateCompatibleBitmap(GetDC(0), width, height);

    // join em up
    SelectObject(hDc, hBmp);

    // copy from the screen to my bitmap
    BitBlt(hDc, 0, 0, width, height, GetDC(0), x, y, SRCCOPY);

    // save my bitmap
    bool ret = SaveBMPFile(filename, hBmp, hDc, width, height);

    // free the bitmap memory
    DeleteObject(hBmp);

    }




    int main()
    {
       int horizontal = 0;
       int vertical = 0;
          RECT desktop;
       const HWND hDesktop = GetDesktopWindow();
       GetWindowRect(hDesktop, &desktop);
       horizontal = desktop.right;
       vertical = desktop.bottom;

       Sleep(10000);

      ScreenCapture(0, 0, horizontal, vertical, "testScreenCap.bmp");
      printf("wrote to testScreenCap.bmp");
    }
            */
}

/* Declaration > Generic Window Class Procedure */
LRESULT CALLBACK genericWindowClassProcedure(HWND, UINT, WPARAM, LPARAM);

/* Global */
    // Image File Path
    char *imageFilepath = (char*) "assets/image.bmp";

    // Generic Window Class
    const WNDCLASS genericWindowClass {
        CS_HREDRAW | CS_VREDRAW, /* -> `style` --- NOTE (Lapys) -> Pre-defined look of window instances of the class. */
        &genericWindowClassProcedure, /* -> `lpfnWndProc`  --- NOTE (Lapys) -> Event loop or Message queue.*/
        0, /* -> `cbClsExtra` --- NOTE (Lapys) -> Extra bytes to allocate following the window class structure. */
        0, /* -> `cbWndExtra` --- NOTE (Lapys) -> Extra bytes to allocate following the window instance. */
        0x0, /* -> `hInstance` */
        0x0, /* -> `hIcon` --- NOTE (Lapys) -> Window favorite icon. */
        (HCURSOR) ::LoadCursor(0x0, IDC_ARROW), /* -> `hCursor` --- NOTE (Lapys) -> Window cursor. */
        (HBRUSH) COLOR_WINDOW, /* -> `hbrBackground` --- NOTE (Lapys) -> Window background color. */
        0x0, /* -> `lpszMenuName` --- NOTE (Lapys) -> Resource name of the window class menu. */
        "Image" /* -> `lpszClassName` */
    };

/* Function > Generic Window Class Procedure */
LRESULT CALLBACK genericWindowClassProcedure(HWND windowHandle, UINT message, WPARAM messageParameter, LPARAM additionalMessageParameter) {
    // Logic
    switch (message) {
        // [Window Manager ...]
        case WM_CLOSE: ::DestroyWindow(windowHandle); break;
        case WM_DESTROY: ::PostQuitMessage(0); break;
        case WM_PAINT: {
            // Initialization > ...
            HBITMAP image = Image::requestBitmapFile(imageFilepath);
            HBITMAP displayImage = Image::createBitmapFromDisplay();
            HBITMAP maskedImage = Image::createBitmapMask(image, RGB(0, 0, 255));

            Image::drawImage(displayImage, windowHandle);
        } break;
    }

    // Return
    return ::DefWindowProc(windowHandle, message, messageParameter, additionalMessageParameter);
}

/* Main */
int WinMain(HINSTANCE instanceHandle, HINSTANCE /*previousInstanceHandle*/, LPSTR programInitiationCommandLine, int windowAppearance) {
    // Global > (Program Status, Screen Console Buffer Handle)
    int programStatus = EXIT_SUCCESS;
    HANDLE screenConsoleBufferHandle = ::CreateFile("CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, 0x0, OPEN_ALWAYS, 0, 0x0);

    // [Begin] Print
    ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
    ::WriteFile(screenConsoleBufferHandle, "[PROGRAM INITIATED]\n\r", 21uL, 0x0, 0x0);

    // ...
    ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
    ::SetConsoleTitle("Image");
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);

    // Logic Update > Image File Path
    if (0x0 != programInitiationCommandLine && *programInitiationCommandLine ^ '\0') imageFilepath = programInitiationCommandLine;

    // Logic
    if (::RegisterClass(&genericWindowClass)) {
        // Constant > Window Handle
        const HWND windowHandle = ::CreateWindowEx(0, genericWindowClass.lpszClassName, "Image", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0x0, 0x0, instanceHandle, 0x0);

        // Logic
        if (windowHandle) {
            // Initialization > Window Procedure Message
            MSG windowProcedureMessage {};

            // Update > Window Handle
            ::ShowWindow(windowHandle, windowAppearance);
            ::UpdateWindow(windowHandle);

            // Loop > Logic
            while (::GetMessage(&windowProcedureMessage, 0x0, 0, 0))
                if (windowProcedureMessage.message == WM_QUIT) break;
                else {
                    // Update > Window Procedure Message
                    ::TranslateMessage(&windowProcedureMessage);
                    ::DispatchMessage(&windowProcedureMessage);
                }

            // Update > Program Status
            programStatus = windowProcedureMessage.wParam;
        }

        else {
            const unsigned short errorID = ::GetLastError();
            char errorMessageBoxCaption[14] {'E', 'R', 'R', 'O', 'R', ' ', '(', '0', '\0', '\0', '\0', '\0', ')', '\0'};
            char *errorIDBuffer = errorMessageBoxCaption + 7;

            if (errorID) {
                char *errorMessageBoxCaptionPointer = errorMessageBoxCaption + 7;
                for (unsigned short iterator = errorID; iterator; iterator /= 10u) errorMessageBoxCaptionPointer++;
                *errorMessageBoxCaptionPointer = ')';
                *(errorMessageBoxCaptionPointer + 1) = '\0';
                for (unsigned short iterator = errorID; iterator; iterator /= 10u) *(--errorMessageBoxCaptionPointer) = '0' + (char) (iterator % 10u);
            }

            else {
                *(errorMessageBoxCaption + 8) = ')';
                *(errorMessageBoxCaption + 9) = '\0';
            }

            ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
            ::WriteFile(screenConsoleBufferHandle, "[ERROR (", 8uL, 0x0, 0x0);
            for (; *errorIDBuffer ^ ')'; errorIDBuffer++) ::WriteFile(screenConsoleBufferHandle, errorIDBuffer, 1uL, 0x0, 0x0);
            ::WriteFile(screenConsoleBufferHandle, ")]: Unable to create window\n\r\0", 30uL, 0x0, 0x0);
            ::MessageBox(0x0, "Unable to create window", errorMessageBoxCaption, MB_ICONERROR | MB_OK | MB_SETFOREGROUND);

            ::exit(programStatus = EXIT_FAILURE);
        }

        // Deletion
        ::UnregisterClass(genericWindowClass.lpszClassName, genericWindowClass.hInstance);
    }

    else {
        const unsigned short errorID = ::GetLastError();
        char errorMessageBoxCaption[14] {'E', 'R', 'R', 'O', 'R', ' ', '(', '0', '\0', '\0', '\0', '\0', ')', '\0'};
        char *errorIDBuffer = errorMessageBoxCaption + 7;

        if (errorID) {
            char *errorMessageBoxCaptionPointer = errorMessageBoxCaption + 7;
            for (unsigned short iterator = errorID; iterator; iterator /= 10u) errorMessageBoxCaptionPointer++;
            *(errorMessageBoxCaptionPointer + 1) = ')';
            *(errorMessageBoxCaptionPointer + 2) = '\0';
            for (unsigned short iterator = errorID; iterator; iterator /= 10u) *(--errorMessageBoxCaptionPointer) = '0' + (char) (iterator % 10u);
        }

        else {
            *(errorMessageBoxCaption + 8) = ')';
            *(errorMessageBoxCaption + 9) = '\0';
        }

        ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
        ::WriteFile(screenConsoleBufferHandle, "[ERROR (", 8uL, 0x0, 0x0);
        for (; *errorIDBuffer ^ ')'; errorIDBuffer++) ::WriteFile(screenConsoleBufferHandle, errorIDBuffer, 1uL, 0x0, 0x0);
        ::WriteFile(screenConsoleBufferHandle, ")]: Unable to create window (due to failing window class)\n\r\0", 60uL, 0x0, 0x0);
        ::MessageBox(0x0, "Unable to create window (due to failing window class)", errorMessageBoxCaption, MB_ICONERROR | MB_OK | MB_SETFOREGROUND);

        ::exit(programStatus = EXIT_FAILURE);
    }

    // [End] Print
    ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
    ::WriteFile(screenConsoleBufferHandle, "[PROGRAM TERMINATED]\0", 21uL, 0x0, 0x0);

    // Return
    return programStatus;
}
