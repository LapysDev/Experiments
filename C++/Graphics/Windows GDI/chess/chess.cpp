/* ... --> kernel32.lib, user32.lib
    --- WARN ---
    #Lapys: Requires a byte to be at least 8 bits.
*/

/* Import */
#include <cstdio> // C Standard Input/ Output
#include <cstdlib> // C Standard Library

#undef UNICODE

/* Definition > ... */
static void Initiate(void);
static void Update(void);
static void Terminate(void);

typedef struct Piece /* final */ {
    enum Color /* : bool */ { BLACK = 0u, WHITE = 1u };
    enum Type /* : unsigned char */ { BISHOP = 1u, KING = 2u, KNIGHT = 3u, PAWN = 4u, QUEEN = 5u, ROOK = 6u };

    private: unsigned char *const data;
    public:
        Piece(unsigned char* const data) : data(data) {}

        Color getColor(void) const;
        unsigned char getColumn(void) const;
        unsigned char* getData(void) const;
        signed char getIndex(void) const;
        unsigned char getPosition(void) const;
        unsigned char getRow(void) const;
        Type getType(void) const;

        void setColumn(unsigned char const);
        void setPosition(unsigned char const, unsigned char const);
        void setRow(unsigned char const);
} Bishop, King, Knight, Pawn, Queen, Rook;

/* Global */
/* : Game ...
    --- UPDATE ---
    #Lapys: Could feasibly algorithmically compress the game to a single integer state i.e.: 35 to the 80th possible moves

    --- NOTE ---
    #Lapys: Memory model (with an unimplemented custom 32-turn draw)
       flag               index            flag                             bit
      [CASTLE STATE (4) | EN-PASSANT (4)] [CAPTURED QUEEN & OFFICERS (14) | TURN (1)]
      [0000             | 0000          ] [00000000 000000                | - 0     ]

       position                pos.             position                 pos.              position                pos.             position                 pos.
      [BLACK KING ROOK   (6) | BLACK KING (2) | BLACK QUEEN ROOK   (6) | BLACK QUEEN (2) | WHITE KING ROOK   (6) | WHITE KING (2) | WHITE QUEEN ROOK   (6) | WHITE QUEEN (2)]
      [000000                | 00             | 000000                 | 00              | 000000                | 00             | 000000                 | 00             ]

       position                pos.             position                 pos.              position                pos.             position                 pos.
      [BLACK KING KNIGHT (6) | BLACK KING (2) | BLACK QUEEN KNIGHT (6) | BLACK QUEEN (2) | WHITE KING KNIGHT (6) | WHITE KING (2) | WHITE QUEEN KNIGHT (6) | WHITE QUEEN (2)]
      [000000                | 00             | 000000                 | 00              | 000000                | 00             | 000000                 | 00             ]

       position                pos.             position                 pos.              position                pos.             position                 pos.
      [BLACK KING BISHOP (5) | BLACK KING (2) | BLACK QUEEN BISHOP (5) | BLACK QUEEN (2) | WHITE KING BISHOP (5) | WHITE KING (2) | WHITE QUEEN BISHOP (5) | WHITE QUEEN (2)]
      [00000 -               | 00             | 00000 -                | 00              | 00000 -               | 00             | 00000 -                | 00             ]

       pos.   type      pos.   type      pos.   type      pos.   type      pos.   type      pos.   type      pos.   type      pos.   type
      [BLACK PAWN (8) | BLACK PAWN (8) | BLACK PAWN (8) | BLACK PAWN (8) | BLACK PAWN (8) | BLACK PAWN (8) | BLACK PAWN (8) | BLACK PAWN (8)]
      [000000 00      | 000000 00      | 000000 00      | 000000 00      | 000000 00      | 000000 00      | 000000 00      | 000000 00     ]

       flag                      flag
      [CAPTURED BLACK PAWN (8)] [PROMOTED BLACK PAWN (8)]
      [00000000               ] [00000000               ]

       pos.   type      pos.   type      pos.   type      pos.   type      pos.   type      pos.   type      pos.   type      pos.   type
      [WHITE PAWN (8) | WHITE PAWN (8) | WHITE PAWN (8) | WHITE PAWN (8) | WHITE PAWN (8) | WHITE PAWN (8) | WHITE PAWN (8) | WHITE PAWN (8)]
      [000000 00      | 000000 00      | 000000 00      | 000000 00      | 000000 00      | 000000 00      | 000000 00      | 000000 00     ]

       flag                      flag
      [CAPTURED WHITE PAWN (8)] [PROMOTED WHITE PAWN (8)]
      [00000000               ] [00000000               ]
*/
namespace Game {
    static unsigned char MEMORY[/* 275 / CHAR_BIT */ 35]; // ->> Encoded in terms of recency.

    // ...
    enum MemorySegment {
        BISHOPS,
        KNIGHTS,
        KINGS,
        PAWNS,
        QUEENS,
        ROOKS,

        CAPTURED_OFFICERS,
        CAPTURED_PAWNS,
        CASTLE,
        EN_PASSANT,
        PROMOTED_PAWNS,
        TURN
    };

    enum PiecesEnumerationControl {
        CONTINUE_ENUMERATING_PIECES,
        STOP_ENUMERATING_PIECES
    };

    // ...
    static void capturePiece(Piece, Piece const);
    static void castleRook(Rook const);
    static PiecesEnumerationControl enumeratePieces(PiecesEnumerationControl (*const)(Piece));
    static bool hasPiece(unsigned char const, unsigned char const);
    static void movePiece(Piece, unsigned char const, unsigned char const);
    static void promotePawn(Pawn const, Piece::Type const);
    static void removePiece(Piece const);

    // ...
    static unsigned char getColumnCount(void);
    static Pawn getEnPassantPawn(void);
    static unsigned char* getMemorySegment(MemorySegment const);
    static Piece::Type getPawnPromotion(Pawn const);
    static Piece getPiece(Piece::Color const, Piece::Type const, unsigned char const = 0u);
    static unsigned char getPieceCount(Piece::Type const);
    static unsigned char getRowCount(void);
    static unsigned char getTileCount(void);
    static Piece::Color getTurn(void);

    static bool isPawnPromoted(Pawn const);
    static bool isPieceCaptured(Piece const);
    static bool isRookCastled(Rook const);

    static void setEnPassantPawn(Pawn const);
    static void setPawnPromotion(Pawn, Piece::Type const);
    static void setTurn(Piece::Color const);
}

/* Functions > ... */
void Game::capturePiece(Piece capturer, Piece const captured) {
    unsigned char const column = captured.getColumn();
    unsigned char const row = captured.getRow();

    Game::removePiece(captured);
    Game::movePiece(capturer, column, row);
}

void Game::castleRook(Rook const rook) {
    *Game::getMemorySegment(Game::CASTLE) &= 0xFu | ((
        (*Game::getMemorySegment(Game::CASTLE) >> 4u) |
        (1u << (rook.getIndex() + ((Piece::WHITE == rook.getColor()) << 1u)))
    ) << 4u);
}

Game::PiecesEnumerationControl Game::enumeratePieces(PiecesEnumerationControl (*const handler)(Piece)) {
    for (Piece::Type type = Piece::BISHOP; type <= Piece::ROOK; type = static_cast<Piece::Type>(static_cast<int>(type) + 1))
    for (unsigned char iterator = 0u; iterator != Game::getPieceCount(type); ++iterator) {
        if (Game::STOP_ENUMERATING_PIECES == handler(Game::getPiece(Piece::BLACK, type, iterator)))
        return Game::STOP_ENUMERATING_PIECES;
    }

    for (Piece::Type type = Piece::BISHOP; type <= Piece::ROOK; type = static_cast<Piece::Type>(static_cast<int>(type) + 1))
    for (unsigned char iterator = 0u; iterator != Game::getPieceCount(type); ++iterator) {
        if (Game::STOP_ENUMERATING_PIECES == handler(Game::getPiece(Piece::WHITE, type, iterator)))
        return Game::STOP_ENUMERATING_PIECES;
    }

    return Game::CONTINUE_ENUMERATING_PIECES;
}

unsigned char Game::getColumnCount(void) {
    return 8u;
}

Pawn Game::getEnPassantPawn(void) {
    unsigned char const count = Game::getPieceCount(Piece::PAWN);
    unsigned char const index = *Game::getMemorySegment(Game::EN_PASSANT) & 0xF;

    return Game::getPiece(count > index ? Piece::BLACK : Piece::WHITE, Piece::PAWN, index % count);
}

unsigned char* Game::getMemorySegment(MemorySegment const segment) {
    switch (segment) {
        case Game::BISHOPS: return Game::MEMORY + 20;
        case Game::KNIGHTS: return Game::MEMORY + 24;
        case Game::KINGS: return Game::MEMORY - 1;
        case Game::PAWNS: return Game::MEMORY + 0;
        case Game::QUEENS: return Game::MEMORY - 3;
        case Game::ROOKS: return Game::MEMORY + 28;

        case Game::CAPTURED_PAWNS: return Game::MEMORY + 16;
        case Game::CAPTURED_OFFICERS: return Game::MEMORY + 33;
        case Game::CASTLE: return Game::MEMORY + 32;
        case Game::EN_PASSANT: return Game::MEMORY + 32;
        case Game::PROMOTED_PAWNS: return Game::MEMORY + 18;
        case Game::TURN: return Game::MEMORY + 34;
    }

    return NULL;
}

Piece::Type Game::getPawnPromotion(Pawn const pawn) {
    switch (*pawn.getData() >> 6u) {
        case 0x0u: return Piece::BISHOP;
        case 0x1u: return Piece::KNIGHT;
        case 0x2u: return Piece::QUEEN;
        case 0x3u: return Piece::ROOK;
    }

    return Piece::PAWN;
}

Piece Game::getPiece(Piece::Color const color, Piece::Type const type, unsigned char const index) {
    switch (type) {
        case Piece::BISHOP: return Piece(Game::getMemorySegment(Game::BISHOPS) + index + (Game::getPieceCount(Piece::BISHOP) * (Piece::WHITE == color)));
        case Piece::KING: return Piece(Game::getMemorySegment(Game::KINGS) + index - (0L + (1L << (Piece::WHITE == color))));
        case Piece::KNIGHT: return Piece(Game::getMemorySegment(Game::KNIGHTS) + index + (Game::getPieceCount(Piece::KNIGHT) * (Piece::WHITE == color)));
        case Piece::PAWN: return Piece(Game::getMemorySegment(Game::PAWNS) + index + (Game::getPieceCount(Piece::PAWN) * (Piece::WHITE == color)));
        case Piece::QUEEN: return Piece(Game::getMemorySegment(Game::QUEENS) + index - (2L + (1L << (Piece::WHITE == color))));
        case Piece::ROOK: return Piece(Game::getMemorySegment(Game::ROOKS) + index + (Game::getPieceCount(Piece::ROOK) * (Piece::WHITE == color)));
    }

    return Piece(NULL);
}

unsigned char Game::getPieceCount(Piece::Type const type) {
    switch (type) {
        case Piece::BISHOP: case Piece::KNIGHT: case Piece::ROOK: return 2u;
        case Piece::KING: case Piece::QUEEN: return 1u;
        case Piece::PAWN: return 8u;
    }

    return 0u;
}

unsigned char Game::getRowCount(void) {
    return 8u;
}

unsigned char Game::getTileCount(void) {
    return Game::getColumnCount() * Game::getRowCount();
}

Piece::Color Game::getTurn(void) {
    return *Game::getMemorySegment(Game::TURN) & 1u ? Piece::WHITE : Piece::BLACK;
}

bool Game::hasPiece(unsigned char const column, unsigned char const row) {
    for (Piece::Type type = Piece::BISHOP; type <= Piece::ROOK; type = static_cast<Piece::Type>(static_cast<int>(type) + 1))
    for (unsigned char iterator = Game::getPieceCount(type); iterator--; ) {
        Piece const piece = Game::getPiece(Piece::WHITE, type, iterator);
        if (column == piece.getColumn() && row == piece.getRow()) return true;
    }

    return false;
}

bool Game::isPawnPromoted(Pawn const pawn) {
    return (Game::getMemorySegment(Game::PROMOTED_PAWNS)[Piece::WHITE == pawn.getColor()] >> pawn.getIndex()) & 1u;
}

bool Game::isPieceCaptured(Piece const piece) {
    switch (piece.getType()) {
        case Piece::KING: return false;
        case Piece::PAWN: return (Game::getMemorySegment(Game::CAPTURED_PAWNS)[Piece::WHITE == piece.getColor()] >> piece.getIndex()) & 1u;

        case Piece::BISHOP: return ((Game::getMemorySegment(Game::CAPTURED_OFFICERS)[0] >> 4u) >> (piece.getIndex() + (Game::getPieceCount(Piece::BISHOP) * (Piece::WHITE == piece.getColor())))) & 1u;
        case Piece::KNIGHT: return ((Game::getMemorySegment(Game::CAPTURED_OFFICERS)[0] >> 0u) >> (piece.getIndex() + (Game::getPieceCount(Piece::KNIGHT) * (Piece::WHITE == piece.getColor())))) & 1u;
        case Piece::QUEEN : return ((Game::getMemorySegment(Game::CAPTURED_OFFICERS)[1] >> 2u) >> (piece.getIndex() + (Game::getPieceCount(Piece::QUEEN ) * (Piece::WHITE == piece.getColor())))) & 1u;
        case Piece::ROOK  : return ((Game::getMemorySegment(Game::CAPTURED_OFFICERS)[1] >> 4u) >> (piece.getIndex() + (Game::getPieceCount(Piece::ROOK  ) * (Piece::WHITE == piece.getColor())))) & 1u;
    }

    return false;
}

bool Game::isRookCastled(Rook const rook) {
    return ((*Game::getMemorySegment(Game::CASTLE) >> 4u) >> (rook.getIndex() + (Game::getPieceCount(Piece::ROOK) * (Piece::WHITE == rook.getColor())))) & 1u;
}

void Game::movePiece(Piece piece, unsigned char const column, unsigned char const row) {
    piece.setPosition(column, row);
}

void Game::promotePawn(Pawn const pawn, Piece::Type const type) {
    Game::getMemorySegment(Game::PROMOTED_PAWNS)[Piece::WHITE == pawn.getColor()] |= 1u << pawn.getIndex();
    Game::setPawnPromotion(pawn, type);
}

void Game::removePiece(Piece const piece) {
    switch (piece.getType()) {
        case Piece::KING: break;
        case Piece::PAWN: Game::getMemorySegment(Game::CAPTURED_PAWNS)[Piece::WHITE == piece.getColor()] |= 1u << piece.getIndex(); break;

        case Piece::BISHOP: Game::getMemorySegment(Game::CAPTURED_OFFICERS)[0] |= 1u << ((piece.getIndex() + (Game::getPieceCount(Piece::BISHOP) * (Piece::WHITE == piece.getColor()))) << 4u); break;
        case Piece::KNIGHT: Game::getMemorySegment(Game::CAPTURED_OFFICERS)[0] |= 1u << ((piece.getIndex() + (Game::getPieceCount(Piece::KNIGHT) * (Piece::WHITE == piece.getColor()))) << 0u); break;
        case Piece::QUEEN : Game::getMemorySegment(Game::CAPTURED_OFFICERS)[1] |= 1u << ((piece.getIndex() + (Game::getPieceCount(Piece::QUEEN ) * (Piece::WHITE == piece.getColor()))) << 2u); break;
        case Piece::ROOK  : Game::getMemorySegment(Game::CAPTURED_OFFICERS)[1] |= 1u << ((piece.getIndex() + (Game::getPieceCount(Piece::ROOK  ) * (Piece::WHITE == piece.getColor()))) << 4u); break;
    }
}

void Game::setEnPassantPawn(Pawn const pawn) {
    unsigned char *const data = Game::getMemorySegment(Game::EN_PASSANT);

    *data &= 0xF0u;
    *data |= pawn.getIndex() << (Piece::WHITE == pawn.getColor());
}

void Game::setPawnPromotion(Pawn pawn, Piece::Type const type) {
    unsigned char *const data = pawn.getData();

    *data &= 0x3Fu;
    switch (type) {
        case Piece::BISHOP: *data |= 0x0u << 6u; break;
        case Piece::KNIGHT: *data |= 0x1u << 6u; break;
        case Piece::QUEEN : *data |= 0x2u << 6u; break;
        case Piece::ROOK  : *data |= 0x3u << 6u; break;

        case Piece::KING: case Piece::PAWN: break;
    }
}

void Game::setTurn(Piece::Color const color) {
    if (Piece::BLACK == color) *Game::getMemorySegment(Game::TURN) &= 0xFEu;
    if (Piece::WHITE == color) *Game::getMemorySegment(Game::TURN) |= 0x01u;
}

// ...
Piece::Color Piece::getColor(void) const {
    unsigned char const *const data = this -> getData();

    for (Type type = Piece::BISHOP; type <= Piece::ROOK; type = static_cast<Type>(static_cast<int>(type) + 1))
    for (unsigned char iterator = Game::getPieceCount(type); iterator--; ) {
        if (data == Game::getPiece(Piece::BLACK, type, iterator).getData()) return Piece::BLACK;
        if (data == Game::getPiece(Piece::WHITE, type, iterator).getData()) return Piece::WHITE;
    }

    return static_cast<Color>(0x0u);
}

unsigned char Piece::getColumn(void) const {
    if (Piece::BISHOP == this -> getType()) return (this -> getPosition() % Game::getColumnCount()) + (this -> getRow() & 1u
        ? 0u == this -> getIndex() || 4u == this -> getIndex()
        : 1u == this -> getIndex() || 2u == this -> getIndex()
    );

    return this -> getPosition() >> 3u;
}

unsigned char* Piece::getData(void) const {
    return this -> data;
}

signed char Piece::getIndex(void) const {
    unsigned char const *const data = this -> getData();

    for (Type type = Piece::BISHOP; type <= Piece::ROOK; type = static_cast<Type>(static_cast<int>(type) + 1))
    for (unsigned char iterator = Game::getPieceCount(type); iterator--; ) {
        if (
            data == Game::getPiece(Piece::BLACK, type, iterator).getData() ||
            data == Game::getPiece(Piece::WHITE, type, iterator).getData()
        ) return iterator;
    }

    return -1;
}

unsigned char Piece::getPosition(void) const {
    Type const type = this -> getType();

    switch (type) {
        case Piece::BISHOP: return *(this -> getData()) & 0x1F;
        case Piece::KNIGHT: case Piece::PAWN: case Piece::ROOK: return *(this -> getData()) & 0x7Fu;
        case Piece::KING: case Piece::QUEEN: {
            Color const color = this -> getColor();
            return (
                ((*Game::getPiece(color, Piece::BISHOP, Piece::QUEEN == type).getData() >> 6u) << 4u) |
                ((*Game::getPiece(color, Piece::KNIGHT, Piece::QUEEN == type).getData() >> 6u) << 2u) |
                ((*Game::getPiece(color, Piece::ROOK  , Piece::QUEEN == type).getData() >> 6u) << 0u)
            );
        } break;
    }

    return 0u;
}

unsigned char Piece::getRow(void) const {
    if (Piece::BISHOP == this -> getType()) return this -> getPosition() >> 3u;
    return this -> getPosition() & 0x7u;
}

Piece::Type Piece::getType(void) const {
    unsigned char const *const data = this -> getData();

    for (Type type = Piece::BISHOP; type <= Piece::ROOK; type = static_cast<Type>(static_cast<int>(type) + 1))
    for (unsigned char iterator = Game::getPieceCount(type); iterator--; ) {
        if (
            data == Game::getPiece(Piece::BLACK, type, iterator).getData() ||
            data == Game::getPiece(Piece::WHITE, type, iterator).getData()
        ) return type;
    }

    return static_cast<Type>(0u);
}

void Piece::setColumn(unsigned char const column) {
    this -> setPosition(column, this -> getRow());
}

void Piece::setPosition(unsigned char const column, unsigned char const row) {
    unsigned char *const data = this -> getData();
    Type const type = this -> getType();

    switch (type) {
        case Piece::BISHOP: {
            unsigned char const index = this -> getIndex();
            unsigned char position = 0u;

            while (position < Game::getTileCount()) {
                unsigned char const positionRow = position >> 3u;
                unsigned char const positionColumn = (position % Game::getColumnCount()) + (positionRow & 1u
                    ? 0u == index || 4u == index
                    : 1u == index || 2u == index
                );

                if (column == positionColumn && row == positionRow) {
                    *data &= 0xE0;
                    *data |= position;

                    break;
                }

                position += 2u;
            }
        } break;

        case Piece::KNIGHT: case Piece::PAWN: case Piece::ROOK: {
            *data &= 0xC0u;
            *data |= row | (column << 3u);
        } break;

        case Piece::KING: case Piece::QUEEN: {
            Color const color = this -> getColor();
            unsigned char *const position[3] = {
                Game::getPiece(color, Piece::BISHOP, Piece::QUEEN == type).getData(),
                Game::getPiece(color, Piece::KNIGHT, Piece::QUEEN == type).getData(),
                Game::getPiece(color, Piece::ROOK  , Piece::QUEEN == type).getData()
            };

            *position[0] &= 0x3Fu;
            *position[1] &= 0x3Fu;
            *position[2] &= 0x3Fu;

            *position[0] |= (column >> 1u)                << 6u;
            *position[1] |= ((column & 1u) | (row >> 2u)) << 6u;
            *position[2] |= (row & 0x3u)                  << 6u;
        } break;
    }
}

void Piece::setRow(unsigned char const row) {
    this -> setPosition(this -> getColumn(), row);
}

/* Phase */
/* : Initiate */
void Initiate(void) {}

/* : Update */
void Update(void) {}

/* : Terminate */
void Terminate(void) {}

/* Main */
int WinMain(HINSTANCE const instanceHandle, HINSTANCE const previousInstanceHandle, LPSTR const /* commandLineArguments */, int const appearance) {
    int exitCode = EXIT_SUCCESS;
    bool instanceAlreadyRunning = false;

    // ...
    if (NULL != previousInstanceHandle) instanceAlreadyRunning = true;
    else {
        static HANDLE lockFile = NULL, lockMutex = NULL;

        struct instanceEventHandler {
            static void onexit(void) {
                if (NULL != lockFile && INVALID_HANDLE_VALUE != lockFile) ::CloseHandle(lockFile);
                if (NULL != lockMutex) ::CloseHandle(lockMutex);
            }

            static void onsignal(int const signal) {
                instanceEventHandler::onexit();
                static_cast<void (*)(int)>(SIG_DFL)(signal);
            }
        };

        // ...
        if (false == instanceAlreadyRunning) {
            lockMutex = ::CreateMutex(NULL, TRUE, "ChessLockMutex");
            if (NULL != lockMutex) instanceAlreadyRunning = ERROR_ALREADY_EXISTS == ::GetLastError();
        }

        if (false == instanceAlreadyRunning)
        if (NULL == lockMutex) {
            CHAR lockFilePath[MAX_PATH + 17u] = {0};
            DWORD lockFilePathLength = ::GetTempPath(MAX_PATH + 1u, lockFilePath);

            if (0u != lockFilePathLength) {
                for (CHAR const *lockFileName = "ChessLockFile.tmp"; '\0' != *lockFileName; )
                lockFilePath[lockFilePathLength++] = *(lockFileName++);

                lockFile = ::CreateFile(lockFilePath, DELETE | GENERIC_READ | GENERIC_WRITE, 0x0u, NULL, CREATE_NEW, FILE_FLAG_DELETE_ON_CLOSE, NULL);
                instanceAlreadyRunning = ERROR_FILE_EXISTS == ::GetLastError();
            }
        }
    }

    // ...
    if (instanceAlreadyRunning) {
        FLASHWINFO previousInstanceWindowFlashInformation;
        HWND const previousInstanceWindowHandle = ...;

        previousInstanceWindowFlashInformation.cbSize = sizeof(FLASHWINFO);
        previousInstanceWindowFlashInformation.dwFlags = FLASHW_CAPTION | FLASHW_TRAY;
        previousInstanceWindowFlashInformation.dwTimeout = 0u;
        previousInstanceWindowFlashInformation.hwnd = previousInstanceWindowHandle;
        previousInstanceWindowFlashInformation.uCount = 2u;

        ::FlashWindowEx(&previousInstanceWindowFlashInformation);
        if (FALSE != ::ShowWindow(previousInstanceWindowHandle, SW_RESTORE)) ::SetForegroundWindow(previousInstanceWindowHandle);
        if (NULL != ::SetActiveWindow(previousInstanceWindowHandle)) ::SetFocus(previousInstanceWindowHandle);
    }

    else {
        CHAR instanceFileName[MAX_PATH] = {0};
        ::GetModuleFileName(NULL, instanceFileName, MAX_PATH);

        // ...
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

            windowHandle = ::CreateWindowEx(0x0, windowClassInformation.lpszClassName, "Tic-Tac-Toe", WS_OVERLAPPEDWINDOW, windowCoordinates.cx, windowCoordinates.cy, windowWidth, windowHeight, HWND_DESKTOP, static_cast<HMENU>(NULL), windowClassInformation.hInstance, reinterpret_cast<LPVOID>(static_cast<LPARAM>(appearance)));

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
