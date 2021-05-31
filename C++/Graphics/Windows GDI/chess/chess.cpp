/* Import --> gdi32.dll, kernel32.dll, shell32.dll, user32.dll */
#include <stdint.h> // Standard Integer
#include <csignal> // C Signal
#include <cstdio>
#include <cstdlib> // C Standard Library

#include <windef.h> // Windows Definitions
#include <winbase.h> // Window Base
#include <wincon.h> // Windows Console
#include <wingdi.h> // Windows Graphics Device Interface
#include <winnt.h> // Windows New Technologies
#include <winuser.h> // Windows User
#   include <basetsd.h> // Base Type Definitions
#   include <fileapi.h> // File API
#   include <handleapi.h> // Handle API
#   include <libloaderapi.h> // Library Loader API
#   include <processthreadsapi.h> // Process Threads API
#   include <shellapi.h> // Shell API
#   include <synchapi.h> // Synchronicity API
#   include <windowsx.h> // Windows Extensions API

/* Definitions > ... */
#undef UNICODE
#ifdef _WIN32_WINNT
# if _WIN32_WINNT < 0x0500
#   undef _WIN32_WINNT
#   define _WIN32_WINNT 0x0500
# endif
#endif

static void Initiate(HDC const);
static void Terminate(void);
static bool Update(void);

inline void putPixel(unsigned short const, unsigned short const, DWORD const);

/* Class */
// : Color
// : Piece
union Color { public: enum __CONSTRUCTOR__ { BLACK, WHITE }; };
union Piece { public: enum __CONSTRUCTOR__ { BISHOP = 0x1, KNIGHT = 0x2, KING = 0x3, PAWN = 0x4, QUEEN = 0x5, ROOK = 0x6 }; };

// : Tile
struct Tile /* final */ {
    Piece::__CONSTRUCTOR__ const piece;
    Color::__CONSTRUCTOR__ const pieceColor;

    // ...
    Tile(Piece::__CONSTRUCTOR__ const piece, Color::__CONSTRUCTOR__ const color) : piece(piece), pieceColor(color) {}
    bool isClear(void) const { return static_cast<Piece::__CONSTRUCTOR__>(0x0) == this -> piece; }
};

// : Board
class Board /* final */ {
    private:
        uint64_t attribute, locations[6];

        static bool hasPiece(uint64_t const subboard, unsigned char const index) { return (subboard >> index) & 1u; }
        static void removePiece(uint64_t& subboard, unsigned char const index) { subboard &= ~(1u << index); }
        static void setPiece(uint64_t& subboard, unsigned char const index) { subboard |= 1u << index; }

    public:
        // ...
        Board(void) : attribute(0u), locations() {
            for (unsigned char iterator = 8u; iterator--; ) {
                this -> setTile(Piece::PAWN, Color::BLACK, iterator, 1u);
                this -> setTile(Piece::PAWN, Color::WHITE, iterator, 6u);
            }

            this -> setTile(Piece::ROOK, Color::WHITE, 0u, 0u);
            this -> setTile(Piece::KNIGHT, Color::WHITE, 1u, 0u);
            this -> setTile(Piece::BISHOP, Color::WHITE, 2u, 0u);
            this -> setTile(Piece::KING, Color::WHITE, 3u, 0u);
            this -> setTile(Piece::QUEEN, Color::WHITE, 4u, 0u);
            this -> setTile(Piece::BISHOP, Color::WHITE, 5u, 0u);
            this -> setTile(Piece::KNIGHT, Color::WHITE, 6u, 0u);
            this -> setTile(Piece::ROOK, Color::WHITE, 7u, 0u);
            // this -> locations[0] = 0xFFFFFFFFFFFFFFFFu;
            // ... ->> Faster than manually modifying each tile.
            // this -> locations[0] = 0x24000024u;
            // this -> locations[1] = 0x42000042u;
            // this -> locations[2] = 0x08000008u;
            // this -> locations[3] = 0x00FFFF00u;
            // this -> locations[4] = 0x10000010u;
            // this -> locations[5] = 0x81000081u;
        }

        // ...
        void clearTile(unsigned char const column, unsigned char const row) {
            for (uint64_t *location = this -> locations + (sizeof(this -> locations) / sizeof(uint64_t)); location-- != this -> locations; )
            Board::removePiece(*location, column + (row << 3u));
        }

        Tile getTile(unsigned char const column, unsigned char const row) const {
            for (uint64_t const *location = this -> locations + (sizeof(this -> locations) / sizeof(uint64_t)); location-- != this -> locations; )
            if (Board::hasPiece(*location, column + (row << 3u))) return Tile(static_cast<Piece::__CONSTRUCTOR__>((location - (this -> locations)) + 1), Board::hasPiece(this -> attribute, column + (row << 3u)) ? Color::WHITE : Color::BLACK);

            return Tile(static_cast<Piece::__CONSTRUCTOR__>(0x0), static_cast<Color::__CONSTRUCTOR__>(0x0));
        }

        void setTile(Piece::__CONSTRUCTOR__ const piece, Color::__CONSTRUCTOR__ const color, unsigned char const column, unsigned char const row) {
            Board::setPiece(this -> locations[static_cast<int>(piece) - 1], column + (row << 3u));
            switch (color) {
                case Color::BLACK: Board::removePiece(this -> attribute, column + (row << 3u)); break;
                case Color::WHITE: Board::setPiece(this -> attribute, column + (row << 3u)); break;
            }
        }
};

/* Global */
// : Console
static HWND consoleWindowHandle = NULL;

// : Game
static Board gameBoard = Board();
static DWORD gameBoardColor;
static unsigned short gameBoardSize;

static bool gameHasLoadedPiecesBitmap = false;
static BITMAP gamePiecesBitmap = BITMAP();
static unsigned char gamePieceBitmapHeight = 0u;
static VOID *gamePiecesBitmapBits = NULL;
static HDC gamePiecesBitmapDeviceContextHandle = NULL;
static char const *gamePiecesBitmapFilePath = NULL;
static HBITMAP gamePiecesBitmapHandle = NULL;
static UINT32 gamePiecesBitmapMaskColor = 0x000000u;
static unsigned char gamePieceBitmapWidth = 0u;

static DWORD gameTileColors[2] = {0x000000u, 0x000000u};
static unsigned short gameTileMargin = 0u;

// : Pointer
static POINTS pointerCoordinates = POINTS();
static bool pointerIsPressed = false;

// : Window
static WNDCLASSEX windowClassInformation = WNDCLASSEX();
static HBITMAP windowDeviceContextBitmapHandle = NULL;
static HDC windowDeviceContextHandle = NULL;
static HWND windowHandle = NULL;
static int windowHeight = 0, windowWidth = 0;
static BITMAP windowMemoryDeviceContextBitmap = BITMAP();
static VOID *windowMemoryDeviceContextBitmapBits = NULL;
static HBITMAP windowMemoryDeviceContextBitmapHandle = NULL;
static HDC windowMemoryDeviceContextHandle = NULL;
static LRESULT CALLBACK windowProcedure(HWND const windowHandle, UINT const message, WPARAM const messageParameter, LPARAM const messageSubparameter) {
    switch (message) {
        /* ... */
        case WM_CLOSE: ::DestroyWindow(windowHandle); break;
        case WM_KEYDOWN: if (VK_ESCAPE == messageParameter) ::DestroyWindow(windowHandle); break;
        case WM_SYSCOMMAND: if (SC_CLOSE == messageParameter) ::DestroyWindow(windowHandle); break;
        case WM_SYSKEYDOWN: if (VK_F4 == messageParameter) ::DestroyWindow(windowHandle); break;

        /* ... */
        case WM_LBUTTONDOWN: {
            if (false == pointerIsPressed) pointerIsPressed = true;
            ::RedrawWindow(windowHandle, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE);
        } return EXIT_SUCCESS;

        case WM_LBUTTONUP: {
            pointerIsPressed = false;
            ::RedrawWindow(windowHandle, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE);
        } return EXIT_SUCCESS;

        case WM_MOUSEMOVE: {
            if (false == pointerIsPressed) {
                pointerCoordinates.x = GET_X_LPARAM(messageSubparameter);
                pointerCoordinates.y = GET_Y_LPARAM(messageSubparameter);
            }

            ::RedrawWindow(windowHandle, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE);
        } return EXIT_SUCCESS;

        #ifdef WM_TOUCH
        case WM_TOUCH: {
            POINT touchCoordinates = POINT();
            TOUCHINPUT touchInput = TOUCHINPUT();

            ::GetTouchInputInfo(reinterpret_cast<HTOUCHINPUT>(messageSubparameter), 1u, &touchInput, sizeof(TOUCHINPUT));
            ::CloseTouchInputHandle(reinterpret_cast<HTOUCHINPUT>(messageSubparameter));

            if (false == pointerIsPressed) {
                touchCoordinates.x = TOUCH_COORD_TO_PIXEL(touchInput.x);
                touchCoordinates.y = TOUCH_COORD_TO_PIXEL(touchInput.y);
                ::ScreenToClient(windowHandle, &touchCoordinates);

                pointerIsPressed = true;
                pointerCoordinates.x = touchCoordinates.x;
                pointerCoordinates.y = touchCoordinates.y;

                ::RedrawWindow(windowHandle, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE);
            }
        } return EXIT_SUCCESS;
        #endif

        /* ... */
        case WM_CREATE: {
            LPVOID const creationParameter = reinterpret_cast<CREATESTRUCTA const*>(messageSubparameter) -> lpCreateParams;

            int const windowAppearance = static_cast<int>(reinterpret_cast<intptr_t>(creationParameter));
            BITMAPINFO windowMemoryDeviceContextBitmapInformation = BITMAPINFO();

            // ...
            consoleWindowHandle = ::GetConsoleWindow();

            windowDeviceContextHandle = ::GetDCEx(windowHandle, NULL, CS_OWNDC | DCX_NORESETATTRS);
            windowDeviceContextBitmapHandle = ::CreateCompatibleBitmap(windowDeviceContextHandle, windowWidth, windowHeight);

            windowMemoryDeviceContextBitmapInformation.bmiColors -> rgbBlue = 0u;
            windowMemoryDeviceContextBitmapInformation.bmiColors -> rgbGreen = 0u;
            windowMemoryDeviceContextBitmapInformation.bmiColors -> rgbRed = 0u;
            windowMemoryDeviceContextBitmapInformation.bmiColors -> rgbReserved = 0x0u;
            windowMemoryDeviceContextBitmapInformation.bmiHeader.biBitCount = 32u;
            windowMemoryDeviceContextBitmapInformation.bmiHeader.biClrUsed = 0u;
            windowMemoryDeviceContextBitmapInformation.bmiHeader.biClrImportant = 0u;
            windowMemoryDeviceContextBitmapInformation.bmiHeader.biCompression = BI_RGB;
            windowMemoryDeviceContextBitmapInformation.bmiHeader.biHeight = windowHeight;
            windowMemoryDeviceContextBitmapInformation.bmiHeader.biPlanes = 1u;
            windowMemoryDeviceContextBitmapInformation.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            windowMemoryDeviceContextBitmapInformation.bmiHeader.biWidth = windowWidth;
            windowMemoryDeviceContextBitmapInformation.bmiHeader.biXPelsPerMeter = ::GetDeviceCaps(windowDeviceContextHandle, HORZRES) / ::GetDeviceCaps(windowDeviceContextHandle, HORZSIZE);
            windowMemoryDeviceContextBitmapInformation.bmiHeader.biYPelsPerMeter = ::GetDeviceCaps(windowDeviceContextHandle, VERTRES) / ::GetDeviceCaps(windowDeviceContextHandle, VERTSIZE);
            windowMemoryDeviceContextBitmapInformation.bmiHeader.biSizeImage = windowMemoryDeviceContextBitmapInformation.bmiHeader.biHeight * windowMemoryDeviceContextBitmapInformation.bmiHeader.biWidth * sizeof(UINT32);

            windowMemoryDeviceContextHandle = ::CreateCompatibleDC(windowDeviceContextHandle);
            windowMemoryDeviceContextBitmapHandle = ::CreateDIBSection(windowMemoryDeviceContextHandle, &windowMemoryDeviceContextBitmapInformation, DIB_RGB_COLORS, &windowMemoryDeviceContextBitmapBits, NULL, 0u);

            // ...
            ::GetObject(windowMemoryDeviceContextBitmapHandle, sizeof(BITMAP), &windowMemoryDeviceContextBitmap);
            ::SelectObject(windowDeviceContextHandle, windowDeviceContextBitmapHandle);
            ::SelectObject(windowMemoryDeviceContextHandle, windowMemoryDeviceContextBitmapHandle);

            // ...
            #ifdef WM_TOUCH
                if (0 != ::GetSystemMetrics(0x5E /*SM_DIGITIZER*/))
                ::RegisterTouchWindow(windowHandle, 0x0);
            #endif

            // if (NULL != consoleWindowHandle) ::ShowWindow(consoleWindowHandle, SW_HIDE);
            ::ShowWindow(windowHandle, static_cast<long>(windowAppearance));

            /* ... */
            Initiate(windowDeviceContextHandle);
        } break;

        // ...
        case WM_DESTROY: {
            ::DeleteDC(windowMemoryDeviceContextHandle), ::DeleteObject(windowMemoryDeviceContextBitmapHandle);
            ::ReleaseDC(windowHandle, windowDeviceContextHandle);

            ::PostQuitMessage(EXIT_SUCCESS);

            /* ... */
            Terminate();
        } break;

        // ...
        case WM_PAINT: {
            if (false == Update()) ::DestroyWindow(windowHandle);
            else {
                ::BitBlt(windowDeviceContextHandle, 0, 0, windowWidth, windowHeight, windowMemoryDeviceContextHandle, 0, 0, SRCCOPY);
                ::ValidateRect(windowHandle, NULL);
            }
        } return EXIT_SUCCESS;
    }

    // ...
    return ::DefWindowProc(windowHandle, message, messageParameter, messageSubparameter);
}

/* Function > Put Pixel */
void putPixel(unsigned short const x, unsigned short const y, DWORD const color) { static_cast<UINT32*>(windowMemoryDeviceContextBitmapBits)[x + (windowMemoryDeviceContextBitmap.bmWidth * (windowMemoryDeviceContextBitmap.bmHeight - y - 1L))] = color | (0xFFu << 0x18u); }

/* Phase */
// : Initiate
void Initiate(HDC const windowDeviceContextHandle) {
    gameBoardColor = 0x006600u;
    gameBoardSize = ((windowHeight < windowWidth ? windowHeight : windowWidth) * 4u) / 5u;

    gamePieceBitmapHeight = 80u;
    gamePiecesBitmapFilePath = "pieces.bmp";
    gamePiecesBitmapHandle = static_cast<HBITMAP>(::LoadImage(NULL, gamePiecesBitmapFilePath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTCOLOR | LR_LOADFROMFILE));
    gamePieceBitmapWidth = 83u;

    gameTileColors[0] = 0xFFFFFFu;
    gameTileColors[1] = 0x00AA00u;
    gameTileMargin = 3u;

    // ...
    if (NULL != gamePiecesBitmapHandle) {
        BITMAPINFO gamePiecesBitmapInformation;

        // ...
        gamePiecesBitmapDeviceContextHandle = ::CreateCompatibleDC(windowDeviceContextHandle);

        ::SelectObject(gamePiecesBitmapDeviceContextHandle, gamePiecesBitmapHandle);
        ::GetObject(gamePiecesBitmapHandle, sizeof(BITMAP), &gamePiecesBitmap);

        // ...
        gamePiecesBitmapInformation.bmiColors -> rgbBlue = 0u;
        gamePiecesBitmapInformation.bmiColors -> rgbGreen = 0u;
        gamePiecesBitmapInformation.bmiColors -> rgbRed = 0u;
        gamePiecesBitmapInformation.bmiColors -> rgbReserved = 0x0u;
        gamePiecesBitmapInformation.bmiHeader.biBitCount = 32u;
        gamePiecesBitmapInformation.bmiHeader.biClrUsed = 0u;
        gamePiecesBitmapInformation.bmiHeader.biClrImportant = 0u;
        gamePiecesBitmapInformation.bmiHeader.biCompression = BI_RGB;
        gamePiecesBitmapInformation.bmiHeader.biHeight = gamePiecesBitmap.bmHeight;
        gamePiecesBitmapInformation.bmiHeader.biPlanes = gamePiecesBitmap.bmPlanes;
        gamePiecesBitmapInformation.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        gamePiecesBitmapInformation.bmiHeader.biWidth = gamePiecesBitmap.bmWidth;
        gamePiecesBitmapInformation.bmiHeader.biXPelsPerMeter = ::GetDeviceCaps(windowDeviceContextHandle, HORZRES) / ::GetDeviceCaps(windowDeviceContextHandle, HORZSIZE);
        gamePiecesBitmapInformation.bmiHeader.biYPelsPerMeter = ::GetDeviceCaps(windowDeviceContextHandle, VERTRES) / ::GetDeviceCaps(windowDeviceContextHandle, VERTSIZE);
        gamePiecesBitmapInformation.bmiHeader.biSizeImage = gamePiecesBitmapInformation.bmiHeader.biHeight * gamePiecesBitmapInformation.bmiHeader.biWidth * sizeof(UINT32);

        gamePiecesBitmapBits = static_cast<VOID*>(std::malloc(gamePiecesBitmapInformation.bmiHeader.biSizeImage * sizeof(BYTE)));

        if (NULL != gamePiecesBitmapBits)
        if (0 != ::GetDIBits(gamePiecesBitmapDeviceContextHandle, gamePiecesBitmapHandle, 0u, gamePiecesBitmap.bmHeight, gamePiecesBitmapBits, &gamePiecesBitmapInformation, DIB_RGB_COLORS)) {
            gameHasLoadedPiecesBitmap = true;
            gamePiecesBitmapMaskColor = *static_cast<UINT32*>(gamePiecesBitmapBits);
        }
    }
}

// : Terminate
static void Terminate(void) {
    if (NULL != gamePiecesBitmapBits) std::free(gamePiecesBitmapBits);
    if (NULL != gamePiecesBitmapDeviceContextHandle) ::DeleteObject(gamePiecesBitmapDeviceContextHandle);
    if (NULL != gamePiecesBitmapHandle) ::DeleteObject(gamePiecesBitmapHandle);
}

// : Update
bool Update(void) {
    if (false == gameHasLoadedPiecesBitmap) return false;

    unsigned short const boardLeftBound = ((windowWidth - gameBoardSize) >> 1u) - ((gameTileMargin * 7u) >> 1u);
    unsigned short const boardTopBound = ((windowHeight - gameBoardSize) >> 1u) - ((gameTileMargin * 7u) >> 1u);
    unsigned short const boardRightBound = boardLeftBound + (gameBoardSize + ((gameTileMargin * 7u) >> 1u));
    unsigned short const boardBottomBound = boardTopBound + (gameBoardSize + ((gameTileMargin * 7u) >> 1u));

    // ...
    for (unsigned short x = boardRightBound; boardLeftBound != x--; )
    for (unsigned short y = boardBottomBound; boardTopBound != y--; ) {
        putPixel(x, y, gameBoardColor);
    }

    for (unsigned char column = 8u; column--; )
    for (unsigned char row = 8u; row--; ) {
        Tile const tile = gameBoard.getTile(column, row);

        unsigned short const tileSize = gameBoardSize >> 3u;
        unsigned short const tileTopBound = boardTopBound + (tileSize * row) + (row ? gameTileMargin * row : 0u);
        unsigned short const tileLeftBound = boardLeftBound + (tileSize * column) + (column ? gameTileMargin * column : 0u);

        // ...
        for (unsigned short x = tileSize; x--; )
        for (unsigned short y = tileSize; y--; ) {
            putPixel(tileLeftBound + x, tileTopBound + y, gameTileColors[(column + row) & 1u]);
        }

        // ...
        if (false == tile.isClear()) {
            unsigned short pieceLeftBound = gamePieceBitmapWidth;
            unsigned short const pieceTopBound = 0u;//gamePieceBitmapHeight * (Color::BLACK == tile.pieceColor);

            switch (tile.piece) { // ->> based on the `gamePiecesBitmap` file.
                case Piece::BISHOP: pieceLeftBound *= 2u; break;
                case Piece::KNIGHT: pieceLeftBound *= 1u; break;
                case Piece::KING: pieceLeftBound *= 3u; break;
                case Piece::PAWN: pieceLeftBound *= 5u; break;
                case Piece::QUEEN: pieceLeftBound *= 4u; break;
                case Piece::ROOK: pieceLeftBound *= 0u; break;
            }

            /*if (0u == row || 1u == row) */{
                float const pieceHeightRatio = static_cast<float>(gamePieceBitmapHeight) / static_cast<float>(tileSize);
                float const pieceWidthRatio = static_cast<float>(gamePieceBitmapWidth) / static_cast<float>(tileSize);

                for (float x = gamePieceBitmapWidth; x > 0; x -= pieceWidthRatio)
                for (float y = gamePieceBitmapHeight; y > 0; y -= pieceHeightRatio) {
                    UINT32 const pieceColor = static_cast<UINT32*>(gamePiecesBitmapBits)[
                        (pieceLeftBound + static_cast<unsigned short>(x)) +
                        (gamePiecesBitmap.bmWidth * (gamePiecesBitmap.bmHeight - (pieceTopBound + static_cast<unsigned short>(y)) - 1u))
                    ];

                    if (gamePiecesBitmapMaskColor != pieceColor)
                    putPixel(
                        tileLeftBound + static_cast<unsigned short>(x / pieceWidthRatio),
                        tileTopBound + static_cast<unsigned short>(y / pieceHeightRatio),
                        pieceColor
                    );
                }
            }
        }
    }

    // ...
    return true;
}

/* Main */
int WinMain(HINSTANCE const instanceHandle, HINSTANCE const previousInstanceHandle, LPSTR const /* commandLineArguments */, int const appearance) {
    int exitCode = EXIT_SUCCESS;
    bool instanceAlreadyRunning = false;
    static HANDLE instanceLockFile = NULL, instanceLockMutex = NULL;
    struct instance {
        static void signalHandler(int const signal) { instance::exitHandler(); static_cast<void (*)(int const)>(SIG_DFL)(signal); }
        static void exitHandler(void) {
            if (NULL != instanceLockFile && INVALID_HANDLE_VALUE != instanceLockFile) ::CloseHandle(instanceLockFile);
            if (NULL != instanceLockMutex) ::CloseHandle(instanceLockMutex);
        }
    };

    // ... ->> Prevent multiple program instances.
    if (false == instanceAlreadyRunning)
    instanceAlreadyRunning = NULL != previousInstanceHandle;

    if (false == instanceAlreadyRunning) {
        instanceLockMutex = ::CreateMutex(NULL, TRUE, "ChessLockMutex");
        if (NULL != instanceLockMutex) instanceAlreadyRunning = ERROR_ALREADY_EXISTS == ::GetLastError();
    }

    if (false == instanceAlreadyRunning)
    if (NULL == instanceLockMutex) {
        CHAR instanceLockFilePath[MAX_PATH + 17];
        DWORD instanceLockFilePathLength = ::GetTempPath(MAX_PATH + 1u, instanceLockFilePath);

        if (0u != instanceLockFilePathLength) {
            instanceLockFilePath[instanceLockFilePathLength + 17] = '\0';
            for (CHAR const *instanceLockFileName = "ChessLockFile.tmp"; '\0' != *instanceLockFileName; ) instanceLockFilePath[instanceLockFilePathLength++] = *(instanceLockFileName++);

            instanceLockFile = ::CreateFile(instanceLockFilePath, DELETE | GENERIC_READ | GENERIC_WRITE, 0x0u, NULL, CREATE_NEW, FILE_FLAG_DELETE_ON_CLOSE, NULL);
            instanceAlreadyRunning = ERROR_FILE_EXISTS == ::GetLastError();
        }
    }

    // ... ->> Capture program termination events.
    std::atexit(&instance::exitHandler);
    std::signal(SIGABRT, &instance::signalHandler);
    std::signal(SIGFPE, &instance::signalHandler);
    std::signal(SIGILL, &instance::signalHandler);
    std::signal(SIGINT, &instance::signalHandler);
    std::signal(SIGSEGV, &instance::signalHandler);
    std::signal(SIGTERM, &instance::signalHandler);

    // ... ->> Initiate main program loop.
    if (instanceAlreadyRunning) exitCode = EXIT_FAILURE;
    else {
        CHAR instanceFileName[MAX_PATH] = {0};

        // ...
        ::GetModuleFileName(NULL, instanceFileName, MAX_PATH);

        windowClassInformation.cbClsExtra = 0;
        windowClassInformation.cbSize = sizeof(WNDCLASSEX);
        windowClassInformation.cbWndExtra = 0;
        windowClassInformation.hbrBackground = ::GetSysColorBrush(COLOR_WINDOWTEXT) /* --> ::GetSysColorBrush(COLOR_WINDOW) */;
        windowClassInformation.hCursor = static_cast<HCURSOR>(::LoadCursor(instanceHandle, IDC_ARROW)) /* --> static_cast<HCURSOR>(::LoadImage(instanceHandle, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)) */;
        windowClassInformation.hIcon = static_cast<HICON>(::ExtractIcon(instanceHandle, instanceFileName, 0u));
        windowClassInformation.hIconSm = static_cast<HICON>(NULL);
        windowClassInformation.hInstance = instanceHandle;
        windowClassInformation.lpfnWndProc = &windowProcedure;
        windowClassInformation.lpszClassName = "window";
        windowClassInformation.lpszMenuName = static_cast<LPCSTR>(NULL);
        windowClassInformation.style = CS_GLOBALCLASS | CS_OWNDC;

        // ...
        if (0x0 == ::RegisterClassEx(static_cast<WNDCLASSEX const*>(&windowClassInformation))) exitCode = EXIT_FAILURE;
        else {
            SIZE windowCoordinates = SIZE();
            RECT workareaRectangle = RECT();

            ::SystemParametersInfo(SPI_GETWORKAREA, 0u, static_cast<PVOID>(&workareaRectangle), 0x0);

            // ...
            windowWidth = ((workareaRectangle.right - workareaRectangle.left) * 3) / 4;
            windowHeight = ((workareaRectangle.bottom - workareaRectangle.top) * 3) / 4;

            windowCoordinates.cx = ((workareaRectangle.right - workareaRectangle.left) - windowWidth) / 2L;
            windowCoordinates.cy = ((workareaRectangle.bottom - workareaRectangle.top) - windowHeight) / 2L;

            windowHandle = ::CreateWindowEx(0x0, windowClassInformation.lpszClassName, "Chess", WS_POPUP, windowCoordinates.cx, windowCoordinates.cy, windowWidth, windowHeight, HWND_DESKTOP, static_cast<HMENU>(NULL), windowClassInformation.hInstance, reinterpret_cast<LPVOID>(static_cast<LPARAM>(appearance)));

            // ...
            if (NULL == windowHandle) exitCode = EXIT_FAILURE;
            else {
                MSG threadMessage = MSG();
                BOOL threadMessageAvailable = TRUE;

                while (FALSE == threadMessageAvailable || WM_QUIT != threadMessage.message) {
                    ::DispatchMessage(&threadMessage);
                    threadMessageAvailable = ::PeekMessage(&threadMessage, NULL, 0x0, 0x0, PM_REMOVE);
                }

                exitCode = threadMessage.wParam;
            }

            ::UnregisterClass(windowClassInformation.lpszClassName, windowClassInformation.hInstance);
        }

        ::DestroyCursor(windowClassInformation.hCursor);
    }

    // ...
    return exitCode;
}
