/* ... --> advapi32.lib, gdi32.lib, kernel32.lib, shell32.lib, user32.lib */
/* Definition > ... */
#ifndef MOUSEEVENTF_FROMTOUCH
# define MOUSEEVENTF_FROMTOUCH 0xFF515700
#endif
#define _MAC
#define INC_OLE1
#define NOCRYPT

#undef NOGDI
#undef UNICODE

/* Import */
// : [C Standard Library]
#include <stdbool.h> // Standard Boolean
#include <stdint.h>  // Standard Integers

// : [C++ Standard Library]
#include <cstddef> // C Standard Definitions
#include <csignal> // C Signal
#include <cstdio>  // C Standard Input/ Output
#include <cstdlib> // C Standard Library

// : [Windows API]
#include <windows.h>  // Windows
#include <windowsx.h> // Windows Extensions

/* Phase */
// : Singular `INITIATE` called by entry point;
// : Definitions for `RESET`, `TERMINATE`, `UPDATE`, more definitions are allowed & callable by programmer
static void INITIATE (...);
       void RESET    (   );
       void TERMINATE(   );
       void UPDATE   (   );

void TERMINATE(char const[]);
LRESULT CALLBACK UPDATE(HWND const, UINT const, WPARAM const, LPARAM const);

/* Class */
// : Bit
template <unsigned char count>
struct bit {
    template <unsigned char> friend struct bit;

    private: uint8_t value : count;
    public:
        bit() : value() {}
        bit(uint8_t const value) : value(value) {}

        // ...
        friend bit<count>& operator += (bit<count>& a, bit<count> const b) { a.value +=  b.value; return a; }
        friend bit<count>& operator -= (bit<count>& a, bit<count> const b) { a.value -=  b.value; return a; }
        friend bit<count>& operator *= (bit<count>& a, bit<count> const b) { a.value *=  b.value; return a; }
        friend bit<count>& operator /= (bit<count>& a, bit<count> const b) { a.value /=  b.value; return a; }
        friend bit<count>& operator %= (bit<count>& a, bit<count> const b) { a.value %=  b.value; return a; }
        friend bit<count>& operator &= (bit<count>& a, bit<count> const b) { a.value &=  b.value; return a; }
        friend bit<count>& operator |= (bit<count>& a, bit<count> const b) { a.value |=  b.value; return a; }
        friend bit<count>& operator ^= (bit<count>& a, bit<count> const b) { a.value ^=  b.value; return a; }
        friend bit<count>& operator <<=(bit<count>& a, bit<count> const b) { a.value <<= b.value; return a; }
        friend bit<count>& operator >>=(bit<count>& a, bit<count> const b) { a.value >>= b.value; return a; }
        friend bit<count>& operator ++ (bit<count>& bits)            { ++bits.value; return bits; }
        friend bit<count>  operator ++ (bit<count>& bits, int const) { return bit<count>(bits.value++); }
        friend bit<count>& operator -- (bit<count>& bits)            { ++bits.value; return bits; }
        friend bit<count>  operator -- (bit<count>& bits, int const) { return bit<count>(bits.value++); }

        operator uint8_t() const { return this -> value; }
};

// : Piece ->> Pointer-to-implementation structure; Implementation is `Game::MEMORY`
union Piece {
    friend struct Game;

    enum Type { BISHOP, KING, KNIGHT, PAWN, QUEEN, ROOK };
    struct Color {
        private: unsigned char const value;
        public:
            static Color const DARK, LIGHT;

            Color(unsigned char const value) : value(value) {}
            operator unsigned char() const { return this -> value; }
    };

    public:
        bit<8u> *self;
        Piece(bit<8u>* const address) : self(address) {}

    public:
        // ...
        static unsigned char count();
        static unsigned char countTotal(Type const);

        void capture(Piece const);
        void castle ();
        void promote(Type const);

        // ...
        Color   getColor        () const;
        bit<3u> getColumn       () const;
        bit<3u> getIndex        () const;
        bit<6u> getPosition     () const;
        Type    getPromotionType() const;
        bit<3u> getRow          () const;
        Type    getType         () const;

        bool    isCaptured      () const;
        bool    isCastled       () const;
        bool    isIncidental    () const; // ->> en passant
        bool    isPromoted      () const;

        void    setColumn       (bit<3u> const);
        void    setPosition     (bit<3u> const, bit<3u> const);
        void    setRow          (bit<3u> const);
};

/* Definition > ... */
typedef Piece::Color Color;
typedef Piece Bishop, King, Knight, Pawn, Queen, Rook;

/* Namespace */
/* : Game
    --- UPDATE (Lapys) -> Could feasibly algorithmically compress the game to a single (big) integer i.e.: 35 to the 80th possible states
    --- NOTE (Lapys) -> Memory model (with an unimplemented custom 32-turn draw)
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
struct Game {
    struct Board {
        static DWORD          COLOR;
        static unsigned short HEIGHT;
        static unsigned short WIDTH;
    };

    struct Pieces {
        static BITMAP  BITMAP;
        static LPCSTR  BITMAP_FILE_NAME;
        static HDC     BITMAP_DEVICE_CONTEXT_HANDLE;
        static HBITMAP BITMAP_HANDLE;
        static UINT32 *BITMAP_MEMORY;
    };

    struct Pointer {
        static bool ACTIVE;
        static int  X, Y;
    };

    struct Tiles {
        static unsigned char       BEVEL;
        static DWORD               COLOR[2];
        static unsigned char const COLUMN_COUNT;
        static HCURSOR             CURSOR;
        static DWORD               HOVER_COLOR[2];
        static signed char         HOVERED_TILE;
        static unsigned char       MARGIN;
        static unsigned char const ROW_COUNT;
        static signed char         SELECTED_TILE;
        static DWORD               SELECTION_COLOR[2];
    };

    // ...
    static bit<8u> MEMORY[/* 275 ÷ 8 */ 35];

    // ... ->> Address memory segments
    static bit<8u>* addressCapturedOfficerData();
    static bit<8u>* addressCapturedPawnData   ();
    static bit<8u>* addressCastleData         ();
    static bit<8u>* addressIncidentalPawnData ();
    static bit<8u>* addressPieceData(Piece::Type const);
    static bit<8u>* addressPromotedPawnData   ();
    static bit<8u>* addressTurnData           ();

    // ...
    static Piece        getPiece(Color const, Piece::Type const, bit<3u> const = 0u);
    static Piece const* getPieces();
    static Color        getPlayerTurn();
    static void         setPlayerTurn(Color const);
};

// : Program
struct Program {
    struct Lock {
        static HANDLE      FILE;
        static char const *FILE_NAME;

        static HANDLE      MUTEX;
        static char const *MUTEX_NAME;
    };

    static LPSTR     ARGUMENTS;
    static int       EXIT_CODE;
    static CHAR      FILE_NAME[MAX_PATH];
    static HINSTANCE HANDLE;
    static HINSTANCE PREVIOUS_HANDLE;
    static MSG       THREAD_MESSAGE;

    // ... ->> Program termination handlers
    static void exit ();
    static void exit (int const);
    static void raise(int const);

    // ... ->> Program termination listeners
    static void (*onabort       )();
    static void (*onexit        )();
    static void (*oninterrupt   )();
    static void (*oninvalidfault)();
    static void (*onmathfault   )();
    static void (*onsegfault    )();
    static void (*onterminate   )();
};

// : Window
struct Window {
    static int     APPEARANCE;
    static HBRUSH  BACKGROUND;
    static LPCSTR  CLASS_NAME;
    static UINT    CLASS_STYLE;
    static HCURSOR CURSOR;
    static HICON   FAVICON;
    static HWND    HANDLE;
    static int     HEIGHT;
    static HICON   ICON;
    static int     LEFT;
    static LRESULT CALLBACK (*PROCEDURE)(HWND const, UINT const, WPARAM const, LPARAM const);
    static DWORD   STYLE;
    static DWORD   STYLE_EXTENSION;
    static LPCSTR  TITLE;
    static int     TOP;
    static int     WIDTH;

    // ... ->> Renderers
    static HBITMAP DEVICE_CONTEXT_BITMAP_HANDLE;
    static HDC     DEVICE_CONTEXT_HANDLE;

    static BITMAP  MEMORY_DEVICE_CONTEXT_BITMAP;
    static HBITMAP MEMORY_DEVICE_CONTEXT_BITMAP_HANDLE;
    static UINT32 *MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY;
    static HDC     MEMORY_DEVICE_CONTEXT_HANDLE;
};

/* Global > ... */
Color const Color::DARK  = 0u;
Color const Color::LIGHT = 1u;

bit<8u>             Game::MEMORY[sizeof(Game::MEMORY) / sizeof(bit<8u>)] = {0};
DWORD               Game::Board::COLOR                         = 0x000000u;
unsigned short      Game::Board::HEIGHT                        = 0u;
unsigned short      Game::Board::WIDTH                         = 0u;
BITMAP              Game::Pieces::BITMAP                       = ::BITMAP();
LPCSTR              Game::Pieces::BITMAP_FILE_NAME             = NULL;
HDC                 Game::Pieces::BITMAP_DEVICE_CONTEXT_HANDLE = NULL;
HBITMAP             Game::Pieces::BITMAP_HANDLE                = NULL;
UINT32             *Game::Pieces::BITMAP_MEMORY                = NULL;
bool                Game::Pointer::ACTIVE                      = false;
int                 Game::Pointer::X                           = 0;
int                 Game::Pointer::Y                           = 0;
unsigned char       Game::Tiles::BEVEL                         = 0u;
DWORD               Game::Tiles::COLOR[2]                      = {0x000000u, 0x000000u};
unsigned char const Game::Tiles::COLUMN_COUNT                  = 8u;
HCURSOR             Game::Tiles::CURSOR                        = NULL;
DWORD               Game::Tiles::HOVER_COLOR[2]                = {0x000000u, 0x000000u};
signed char         Game::Tiles::HOVERED_TILE                  = -1;
unsigned char       Game::Tiles::MARGIN                        = 0u;
unsigned char const Game::Tiles::ROW_COUNT                     = 8u;
signed char         Game::Tiles::SELECTED_TILE                 = -1;
DWORD               Game::Tiles::SELECTION_COLOR[2]            = {0x000000u, 0x000000u};

HANDLE      Program::Lock::FILE          = NULL;
char const *Program::Lock::FILE_NAME     = NULL;
HANDLE      Program::Lock::MUTEX         = NULL;
char const *Program::Lock::MUTEX_NAME    = NULL;
LPSTR       Program::ARGUMENTS           = NULL;
int         Program::EXIT_CODE           = EXIT_SUCCESS;
CHAR        Program::FILE_NAME[MAX_PATH] = {0};
HINSTANCE   Program::HANDLE              = NULL;
HINSTANCE   Program::PREVIOUS_HANDLE     = NULL;
MSG         Program::THREAD_MESSAGE      = MSG();
void        (*Program::onabort       )() = NULL;
void        (*Program::onexit        )() = NULL;
void        (*Program::oninterrupt   )() = NULL;
void        (*Program::oninvalidfault)() = NULL;
void        (*Program::onmathfault   )() = NULL;
void        (*Program::onsegfault    )() = NULL;
void        (*Program::onterminate   )() = NULL;

int     Window::APPEARANCE                          = SW_SHOW;
HBRUSH  Window::BACKGROUND                          = EXIT_SUCCESS;
LPCSTR  Window::CLASS_NAME                          = "window";
UINT    Window::CLASS_STYLE                         = CS_GLOBALCLASS | CS_OWNDC;
HCURSOR Window::CURSOR                              = NULL;
HBITMAP Window::DEVICE_CONTEXT_BITMAP_HANDLE        = NULL;
HDC     Window::DEVICE_CONTEXT_HANDLE               = NULL;
HICON   Window::FAVICON                             = NULL;
HWND    Window::HANDLE                              = NULL;
int     Window::HEIGHT                              = -1;
HICON   Window::ICON                                = NULL;
int     Window::LEFT                                = -1;
BITMAP  Window::MEMORY_DEVICE_CONTEXT_BITMAP        = ::BITMAP();
HBITMAP Window::MEMORY_DEVICE_CONTEXT_BITMAP_HANDLE = NULL;
UINT32 *Window::MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY = NULL;
HDC     Window::MEMORY_DEVICE_CONTEXT_HANDLE        = NULL;
LRESULT CALLBACK (*Window::PROCEDURE)(HWND const, UINT const, WPARAM const, LPARAM const) = &::DefWindowProc;
DWORD   Window::STYLE                               = WS_OVERLAPPEDWINDOW;
DWORD   Window::STYLE_EXTENSION                     = 0x00000000L;
LPCSTR  Window::TITLE                               = "";
int     Window::TOP                                 = -1;
int     Window::WIDTH                               = -1;

/* Function */
// : Game
bit<8u>* Game::addressCapturedOfficerData() { return Game::MEMORY + 16; }
bit<8u>* Game::addressCapturedPawnData   () { return Game::MEMORY + 33; }
bit<8u>* Game::addressCastleData         () { return Game::MEMORY + 32; }
bit<8u>* Game::addressIncidentalPawnData () { return Game::MEMORY + 32; }
bit<8u>* Game::addressPromotedPawnData   () { return Game::MEMORY + 18; }
bit<8u>* Game::addressTurnData           () { return Game::MEMORY + 34; }
bit<8u>* Game::addressPieceData(Piece::Type const type) {
    switch (type) {
        case Piece::BISHOP: return Game::MEMORY + 20;
        case Piece::KING  : return Game::MEMORY - 2;
        case Piece::KNIGHT: return Game::MEMORY + 24;
        case Piece::PAWN  : return Game::MEMORY + 0;
        case Piece::QUEEN : return Game::MEMORY - 4;
        case Piece::ROOK  : return Game::MEMORY + 28;
    } return NULL;
}

Piece Game::getPiece(Color const color, Piece::Type const type, bit<3u> const index) {
    return Piece(Game::addressPieceData(type) + index + (Color::LIGHT == color ? Piece::countTotal(type) : 0u));
}

Piece const* Game::getPieces() {
    static unsigned char pieces[32u * sizeof(Piece)];
    unsigned char *iterator = pieces;

    for (Piece::Type const types[] = {Piece::QUEEN, Piece::KING, Piece::PAWN, Piece::BISHOP, Piece::KNIGHT, Piece::ROOK}, *type = types + (sizeof(types) / sizeof(Piece::Type)); type-- != types; )
    for (unsigned char index = 2u * Piece::countTotal(*type); index--; iterator += sizeof(Piece)) {
        Piece const piece = Piece(Game::addressPieceData(*type) + index);

        for (unsigned char subiterator = sizeof(Piece); subiterator--; )
        iterator[subiterator] = static_cast<unsigned char const*>(static_cast<void const*>(&piece))[subiterator];
    }

    return static_cast<Piece const*>(static_cast<void*>(pieces));
}

Color Game::getPlayerTurn() {
    return *Game::addressTurnData() & 0x01u ? Color::LIGHT : Color::DARK;
}

void Game::setPlayerTurn(Color const color) {
    if (Color::DARK  == color) *Game::addressTurnData() &= 0xFEu;
    if (Color::LIGHT == color) *Game::addressTurnData() |= 0x01u;
}

// : Pawn
Piece::Type Pawn::getPromotionType() const {
    switch (*(this -> self) & 0xC0u) {
        case 0x0u: return Piece::BISHOP;
        case 0x1u: return Piece::KNIGHT;
        case 0x2u: return Piece::QUEEN;
        case 0x3u: return Piece::ROOK;
    }

    return Piece::PAWN;
}

bool Pawn::isPromoted() const {
    return (Game::addressPromotedPawnData()[Color::LIGHT == this -> getColor() ? 1 : 0] >> this -> getIndex()) & 0x1u;
}

void Pawn::promote(Type const type) {
    Game::addressPromotedPawnData()[Color::LIGHT == this -> getColor() ? 1 : 0] |= 1u << this -> getIndex();

    *(this -> self) &= 0x3Fu;
    switch (type) {
        case Piece::KING  : break;
        case Piece::PAWN  : break;

        case Piece::BISHOP: *(this -> self) |= 0x0u << 6u; break;
        case Piece::KNIGHT: *(this -> self) |= 0x1u << 6u; break;
        case Piece::QUEEN : *(this -> self) |= 0x2u << 6u; break;
        case Piece::ROOK  : *(this -> self) |= 0x3u << 6u; break;
    }
}

// : Piece
void Piece::capture(Piece const piece) {
    this -> setPosition(piece.getColumn(), piece.getRow());
    switch (piece.getType()) {
        // ... ->> Mark the `piece` as "captured"
        case Piece::KING  : break;
        case Piece::PAWN  : Game::addressCapturedPawnData   ()[Color::LIGHT == piece.getColor() ? 1 : 0] |= 1u << piece.getIndex(); break;

        case Piece::BISHOP: Game::addressCapturedOfficerData()[0] |= 1u << ((piece.getIndex() + (Color::LIGHT == piece.getColor() ? Piece::countTotal(Piece::BISHOP) : 0u)) << 4u); break;
        case Piece::KNIGHT: Game::addressCapturedOfficerData()[0] |= 1u << ((piece.getIndex() + (Color::LIGHT == piece.getColor() ? Piece::countTotal(Piece::KNIGHT) : 0u)) << 0u); break;
        case Piece::QUEEN : Game::addressCapturedOfficerData()[1] |= 1u << ((piece.getIndex() + (Color::LIGHT == piece.getColor() ? Piece::countTotal(Piece::QUEEN ) : 0u)) << 2u); break;
        case Piece::ROOK  : Game::addressCapturedOfficerData()[1] |= 1u << ((piece.getIndex() + (Color::LIGHT == piece.getColor() ? Piece::countTotal(Piece::ROOK  ) : 0u)) << 4u); break;
    }
}

unsigned char Piece::countTotal(Type const type) {
    switch (type) {
        case Piece::BISHOP: case Piece::KNIGHT: case Piece::ROOK: return 2u;
        case Piece::KING  : case Piece::QUEEN :                   return 1u;
        case Piece::PAWN  :                                       return 8u;
    }

    return 0u;
}

Color Piece::getColor() const {
    for (Type const types[] = {Piece::QUEEN, Piece::KING, Piece::PAWN, Piece::BISHOP, Piece::KNIGHT, Piece::ROOK}, *type = types + (sizeof(types) / sizeof(Type)); type-- != types; )
    for (unsigned char index = Piece::countTotal(*type); index--; ) {
        if (this -> self == Game::getPiece(Color::DARK , *type, index).self) return Color::DARK;
        if (this -> self == Game::getPiece(Color::LIGHT, *type, index).self) return Color::LIGHT;
    }

    return static_cast<Color>(0x0u);
}

bit<3u> Piece::getColumn() const {
    return Piece::BISHOP != this -> getType() ? (this -> getPosition() & 0x38u) >> 3u : (
        ((this -> getPosition() * 2u) % Game::Tiles::COLUMN_COUNT) + (this -> getRow() % 2u
            ? this -> getIndex() == (Color::LIGHT == this -> getColor() ? 0u : 1u)
            : this -> getIndex() == (Color::LIGHT == this -> getColor() ? 1u : 0u)
        )
    );
}

bit<3u> Piece::getIndex() const {
    for (Type const types[] = {Piece::QUEEN, Piece::KING, Piece::PAWN, Piece::BISHOP, Piece::KNIGHT, Piece::ROOK}, *type = types + (sizeof(types) / sizeof(Type)); type-- != types; ) {
        for (unsigned char index = Piece::countTotal(*type); index--; )
        if (
            this -> self == Game::getPiece(Color::DARK , *type, index).self ||
            this -> self == Game::getPiece(Color::LIGHT, *type, index).self
        ) return index;
    }

    return 0u;
}

bit<6u> Piece::getPosition() const {
    Type const type = this -> getType();

    switch (type) {
        case Piece::BISHOP: return *(this -> self) & 0x1Fu;
        case Piece::KNIGHT: case Piece::PAWN: case Piece::ROOK: return *(this -> self) & 0x3Fu;
        case Piece::KING: case Piece::QUEEN: {
            Color const color = this -> getColor();
            return (
                ((*Game::getPiece(color, Piece::BISHOP, Piece::QUEEN == type ? 1u : 0u).self >> 6u) << 4u) |
                ((*Game::getPiece(color, Piece::KNIGHT, Piece::QUEEN == type ? 1u : 0u).self >> 6u) << 2u) |
                ((*Game::getPiece(color, Piece::ROOK  , Piece::QUEEN == type ? 1u : 0u).self >> 6u) << 0u)
            );
        } break;
    }

    return 0u;
}

bit<3u> Piece::getRow() const {
    return Piece::BISHOP != this -> getType() ? (this -> getPosition() & 0x07u) >> 0u : (
        this -> getPosition() / (Game::Tiles::COLUMN_COUNT / 2u)
    );
}

Piece::Type Piece::getType() const {
    for (Type const types[] = {Piece::QUEEN, Piece::KING, Piece::PAWN, Piece::BISHOP, Piece::KNIGHT, Piece::ROOK}, *type = types + (sizeof(types) / sizeof(Type)); type-- != types; ) {
        for (unsigned char index = Piece::countTotal(*type); index--; )
        if (
            this -> self == Game::getPiece(Color::DARK , *type, index).self ||
            this -> self == Game::getPiece(Color::LIGHT, *type, index).self
        ) return *type;
    }

    return static_cast<Type>(0x0u);
}

bool Piece::isCaptured() const {
    switch (this -> getType()) {
        case Piece::KING  : return false;
        case Piece::PAWN  : return (Game::addressCapturedPawnData()[Color::LIGHT == this -> getColor() ? 1 : 0] >> this -> getIndex()) & 0x01u;

        case Piece::BISHOP: return ((Game::addressCapturedOfficerData()[0] >> 4u) >> (this -> getIndex() + (Color::LIGHT == this -> getColor() ? Piece::countTotal(Piece::BISHOP) : 0u))) & 0x01u;
        case Piece::KNIGHT: return ((Game::addressCapturedOfficerData()[0] >> 0u) >> (this -> getIndex() + (Color::LIGHT == this -> getColor() ? Piece::countTotal(Piece::KNIGHT) : 0u))) & 0x01u;
        case Piece::QUEEN : return ((Game::addressCapturedOfficerData()[1] >> 2u) >> (this -> getIndex() + (Color::LIGHT == this -> getColor() ? Piece::countTotal(Piece::QUEEN ) : 0u))) & 0x01u;
        case Piece::ROOK  : return ((Game::addressCapturedOfficerData()[1] >> 4u) >> (this -> getIndex() + (Color::LIGHT == this -> getColor() ? Piece::countTotal(Piece::ROOK  ) : 0u))) & 0x01u;
    }

    return false;
}

bool Piece::isIncidental() const {
    unsigned char const count = Piece::countTotal(Piece::PAWN);
    unsigned char const index = *Game::addressIncidentalPawnData() & 0x0Fu;

    return this -> self == Game::getPiece(count > index ? Color::DARK : Color::LIGHT, Piece::PAWN, index % count).self;
}

void Piece::setColumn(bit<3u> const column) {
    this -> setPosition(column, this -> getRow());
}

void Piece::setPosition(bit<3u> const column, bit<3u> const row) {
    Type const type = this -> getType();

    switch (type) {
        case Piece::BISHOP: {
            Color const color = this -> getColor();
            unsigned char const index = this -> getIndex();
            unsigned char position = (Game::Tiles::COLUMN_COUNT * Game::Tiles::ROW_COUNT) / 2u;

            while (position--) {
                unsigned char const positionRow = position / (Game::Tiles::COLUMN_COUNT / 2u);
                unsigned char const positionColumn = ((position * 2u) % Game::Tiles::COLUMN_COUNT) + (positionRow % 2u
                    ? index == (Color::LIGHT == color ? 0u : 1u)
                    : index == (Color::LIGHT == color ? 1u : 0u)
                );

                if (column == positionColumn && row == positionRow) {
                    *(this -> self) &= 0xE0u;
                    *(this -> self) |= position;

                    break;
                }
            }
        } break;

        case Piece::KNIGHT: case Piece::PAWN: case Piece::ROOK: {
            *(this -> self) &= 0xC0u;
            *(this -> self) |= (column << 3u) | (row << 0u);
        } break;

        case Piece::KING: case Piece::QUEEN: {
            Color const color = this -> getColor();
            bit<8u> *const position[3] = {
                Game::getPiece(color, Piece::BISHOP, Piece::QUEEN == type ? 1u : 0u).self,
                Game::getPiece(color, Piece::KNIGHT, Piece::QUEEN == type ? 1u : 0u).self,
                Game::getPiece(color, Piece::ROOK  , Piece::QUEEN == type ? 1u : 0u).self
            };

            *position[0] &= 0x3Fu;
            *position[1] &= 0x3Fu;
            *position[2] &= 0x3Fu;

            *position[0] |= ((column & 0x06u) >> 1u) << 6u;
            *position[1] |= ((((column & 0x01u) >> 0u) << 1u) | (((row & 0x04u) >> 2u) << 0u)) << 6u;
            *position[2] |= ((row    & 0x03u) >> 0u) << 6u;
        } break;
    }
}

void Piece::setRow(bit<3u> const row) {
    this -> setPosition(this -> getColumn(), row);
}

// : Program
void Program::exit() { Program::exit(Program::EXIT_CODE); }
void Program::exit(int const code) {
    Program::EXIT_CODE = code;

    if (NULL != Program::onexit) (*Program::onexit)();
    std::exit(Program::EXIT_CODE);
}

void Program::raise(int const signal) {
    switch (signal) {
        case SIGABRT: if (NULL != Program::onabort       ) (*Program::onabort)()       ; break;
        case SIGFPE : if (NULL != Program::onmathfault   ) (*Program::onmathfault)()   ; break;
        case SIGILL : if (NULL != Program::oninvalidfault) (*Program::oninvalidfault)(); break;
        case SIGINT : if (NULL != Program::oninterrupt   ) (*Program::oninterrupt)()   ; break;
        case SIGSEGV: if (NULL != Program::onsegfault    ) (*Program::onsegfault)()    ; break;
        case SIGTERM: if (NULL != Program::onterminate   ) (*Program::onterminate)()   ; break;
    } Program::exit(Program::EXIT_CODE);
}

// : Rook
void Rook::castle() {
    *Game::addressCastleData() |= (1u << (
        this -> getIndex() + (Color::LIGHT == this -> getColor() ? Piece::countTotal(Piece::ROOK) : 0u)
    )) << 4u;
}

bool Rook::isCastled() const {
    return (
        (*Game::addressCastleData() >> 4u) >>
        (this -> getIndex() + (Color::LIGHT == this -> getColor() ? Piece::countTotal(Piece::ROOK) : 0u))
    ) & 0x01u;
}

/* Main */
int WinMain(HINSTANCE const programHandle, HINSTANCE const programPreviousHandle, LPSTR const commandLineArguments, int const appearance) {
    Program::ARGUMENTS       = commandLineArguments;
    Program::HANDLE          = programHandle;
    Program::PREVIOUS_HANDLE = programPreviousHandle;

    Window::APPEARANCE = appearance;

    // ...
    std::atexit(static_cast<void (*)()>(&Program::exit));
    std::signal(SIGABRT, &Program::raise);
    std::signal(SIGFPE , &Program::raise);
    std::signal(SIGILL , &Program::raise);
    std::signal(SIGINT , &Program::raise);
    std::signal(SIGSEGV, &Program::raise);
    std::signal(SIGTERM, &Program::raise);

    // ...
    INITIATE();
    return Program::EXIT_CODE;
}

/* Phase --- WARN (Lapys) -> Phases (except `INITIATE`) can be invoked by the user. */
/* : Initiate */
void INITIATE(...) {
    bool programAlreadyRunning = false;

    // ... ->> Configuration
    for (bit<8u> *data = Game::MEMORY + (sizeof(Game::MEMORY) / sizeof(bit<8u>)); data-- != Game::MEMORY; ) *data = 0x00u;
    Game::Board::COLOR              = 0x300F00u;
    Game::Board::HEIGHT             = 512u;
    Game::Board::WIDTH              = 512u;
    Game::Pieces::BITMAP_FILE_NAME  = "pieces.bmp";
    Game::Tiles::BEVEL              = 5u;
    Game::Tiles::COLOR[0]           = 0xF9F9F9u;
    Game::Tiles::COLOR[1]           = 0x006900u;
    Game::Tiles::HOVER_COLOR[0]     = 0xCFCFCFu;
    Game::Tiles::HOVER_COLOR[1]     = 0x006000u;
    Game::Tiles::MARGIN             = 2u;
    Game::Tiles::SELECTION_COLOR[0] = 0xFAFA00u;
    Game::Tiles::SELECTION_COLOR[1] = 0x006FFFu;

    ::GetModuleFileName(static_cast<HMODULE>(NULL), Program::FILE_NAME, MAX_PATH);
    Program::onexit           = static_cast<void (*)()>(&TERMINATE);
    Program::Lock::FILE_NAME  = "ChessLockFile.tmp";
    Program::Lock::MUTEX_NAME = "ChessLockMutex";

    Window::BACKGROUND = ::GetSysColorBrush(COLOR_WINDOW);
    Window::CURSOR     = ::LoadCursor(NULL, IDC_ARROW); // --> static_cast<HCURSOR>(::LoadImage(NULL, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED))
    Window::ICON       = ::ExtractIcon(static_cast<HINSTANCE>(::GetCurrentProcess()), Program::FILE_NAME, 0u);
    Window::PROCEDURE  = static_cast<LRESULT CALLBACK (*)(HWND const, UINT const, WPARAM const, LPARAM const)>(&UPDATE);
    Window::STYLE      = WS_POPUP;
    Window::TITLE      = "Chess";

    // ... ->> Setup
    Game::getPiece(Color::DARK , Piece::ROOK  , 0u).setPosition(0u, 7u);
    Game::getPiece(Color::DARK , Piece::KNIGHT, 0u).setPosition(1u, 7u);
    Game::getPiece(Color::DARK , Piece::BISHOP, 0u).setPosition(2u, 7u);
    Game::getPiece(Color::DARK , Piece::KING      ).setPosition(3u, 7u);
    Game::getPiece(Color::DARK , Piece::QUEEN     ).setPosition(4u, 7u);
    Game::getPiece(Color::DARK , Piece::BISHOP, 1u).setPosition(5u, 7u);
    Game::getPiece(Color::DARK , Piece::KNIGHT, 1u).setPosition(6u, 7u);
    Game::getPiece(Color::DARK , Piece::ROOK  , 1u).setPosition(7u, 7u);
    Game::getPiece(Color::LIGHT, Piece::ROOK  , 0u).setPosition(0u, 0u);
    Game::getPiece(Color::LIGHT, Piece::KNIGHT, 0u).setPosition(1u, 0u);
    Game::getPiece(Color::LIGHT, Piece::BISHOP, 0u).setPosition(2u, 0u);
    Game::getPiece(Color::LIGHT, Piece::KING      ).setPosition(3u, 0u);
    Game::getPiece(Color::LIGHT, Piece::QUEEN     ).setPosition(4u, 0u);
    Game::getPiece(Color::LIGHT, Piece::BISHOP, 1u).setPosition(5u, 0u);
    Game::getPiece(Color::LIGHT, Piece::KNIGHT, 1u).setPosition(6u, 0u);
    Game::getPiece(Color::LIGHT, Piece::ROOK  , 1u).setPosition(7u, 0u);
    for (unsigned char iterator = Game::Tiles::COLUMN_COUNT; iterator--; ) Game::getPiece(Color::LIGHT, Piece::PAWN, iterator).setPosition(iterator, 1u);
    for (unsigned char iterator = Game::Tiles::COLUMN_COUNT; iterator--; ) Game::getPiece(Color::DARK , Piece::PAWN, iterator).setPosition(iterator, 6u);

    Game::setPlayerTurn(Color::LIGHT);

    // Logic ->> Assert previous program instance
    if (NULL != Program::PREVIOUS_HANDLE) programAlreadyRunning = true;
    else do {
        // ... ->> Mutex lock
        if (false == programAlreadyRunning)
        if (NULL != Program::Lock::MUTEX_NAME) {
            Program::Lock::MUTEX = ::CreateMutex(NULL, TRUE, Program::Lock::MUTEX_NAME);

            if (NULL != Program::Lock::MUTEX) {
                programAlreadyRunning = ERROR_ALREADY_EXISTS == ::GetLastError();
                break;
            }
        }

        // ... ->> File lock
        if (false == programAlreadyRunning)
        if (NULL != Program::Lock::FILE_NAME) {
            DWORD length;
            CHAR  path[MAX_PATH + 17] = {0};

            length = ::GetTempPath(MAX_PATH + 1u, path);
            if (0u != length) {
                for (CHAR const *name = Program::Lock::FILE_NAME; '\0' != *name; ++name) path[length++] = *name;
                Program::Lock::FILE = ::CreateFile(path, DELETE | GENERIC_READ | GENERIC_WRITE, 0x00000000u, NULL, CREATE_NEW, FILE_FLAG_DELETE_ON_CLOSE, NULL);

                if (INVALID_HANDLE_VALUE != Program::Lock::FILE) {
                    programAlreadyRunning = ERROR_FILE_EXISTS == ::GetLastError();
                    break;
                }
            }
        }
    } while (false);

    // Logic ... ->> Create or focus the program window
    if (programAlreadyRunning) {
        HWND const programPreviousWindowHandle = ::FindWindowEx(NULL /* --> HWND_DESKTOP */, NULL, Window::CLASS_NAME, Window::TITLE);

        if (NULL != programPreviousWindowHandle) {
            FLASHWINFO flashInformation;

            flashInformation.cbSize = sizeof(FLASHWINFO);
            flashInformation.dwFlags = FLASHW_CAPTION | FLASHW_TRAY;
            flashInformation.dwTimeout = 0u;
            flashInformation.hwnd = programPreviousWindowHandle;
            flashInformation.uCount = 2u;

            ::FlashWindowEx(&flashInformation);
            if (FALSE != ::ShowWindow(programPreviousWindowHandle, SW_RESTORE)) ::SetForegroundWindow(programPreviousWindowHandle);
            if (NULL != ::SetActiveWindow(programPreviousWindowHandle)) ::SetFocus(programPreviousWindowHandle);
        }
    }

    else {
        WNDCLASSEX classInformation;

        classInformation.cbClsExtra    = 0;
        classInformation.cbSize        = sizeof(WNDCLASSEX);
        classInformation.cbWndExtra    = 0;
        classInformation.hbrBackground = Window::BACKGROUND;
        classInformation.hCursor       = Window::CURSOR;
        classInformation.hIcon         = Window::ICON;
        classInformation.hIconSm       = Window::FAVICON;
        classInformation.hInstance     = Program::HANDLE;
        classInformation.lpfnWndProc   = Window::PROCEDURE;
        classInformation.lpszClassName = Window::CLASS_NAME;
        classInformation.lpszMenuName  = static_cast<LPCSTR>(NULL);
        classInformation.style         = Window::CLASS_STYLE;

        // ...
        if (0x0 == ::RegisterClassEx(const_cast<WNDCLASSEX const*>(&classInformation))) TERMINATE("Unable to setup game window");
        else {
            if (Window::HEIGHT == -1 || Window::LEFT == -1 || Window::TOP == -1 || Window::WIDTH == -1) {
                RECT workareaBounds;
                ::SystemParametersInfo(SPI_GETWORKAREA, 0x0000u, static_cast<PVOID>(&workareaBounds), 0x0u);

                // ...
                if (Window::HEIGHT == -1) Window::HEIGHT = ((workareaBounds.bottom - workareaBounds.top) * 3) / 4;
                if (Window::WIDTH  == -1) Window::WIDTH  = ((workareaBounds.right - workareaBounds.left) * 3) / 4;

                if (Window::LEFT   == -1) Window::LEFT   = (((workareaBounds.right - workareaBounds.left) - Window::WIDTH ) * 1) / 2;
                if (Window::TOP    == -1) Window::TOP    = (((workareaBounds.bottom - workareaBounds.top) - Window::HEIGHT) * 1) / 2;
            }

            Window::HANDLE = ::CreateWindowEx(
                Window::STYLE_EXTENSION, Window::CLASS_NAME, Window::TITLE, Window::STYLE,
                Window::LEFT, Window::TOP, Window::WIDTH, Window::HEIGHT,
                NULL /* --> HWND_DESKTOP */, static_cast<HMENU>(NULL), Program::HANDLE,
                reinterpret_cast<LPVOID>(static_cast<LPARAM>(Window::APPEARANCE))
            );

            // ...
            if (NULL == Window::HANDLE) TERMINATE("Unable to create game window");
            else for (bool available = false; WM_QUIT != Program::THREAD_MESSAGE.message; ) {
                available = ::PeekMessage(&Program::THREAD_MESSAGE, NULL, 0x0u, 0x0u, PM_REMOVE);
                if (FALSE != available) ::DispatchMessage(&Program::THREAD_MESSAGE);

                Program::EXIT_CODE = Program::THREAD_MESSAGE.wParam;
            }
        }
    }
}

/* : Update */
void UPDATE() {}
LRESULT CALLBACK UPDATE(HWND const windowHandle, UINT const message, WPARAM const parameter, LPARAM const subparameter) {
    int const            boardLeft  = (Window::WIDTH  - (Game::Board::WIDTH  + (Game::Tiles::MARGIN * (Game::Tiles::COLUMN_COUNT - 1)))) / 2;
    int const            boardTop   = (Window::HEIGHT - (Game::Board::HEIGHT + (Game::Tiles::MARGIN * (Game::Tiles::ROW_COUNT    - 1)))) / 2;
    unsigned short const tileHeight = Game::Board::HEIGHT / Game::Tiles::ROW_COUNT;
    unsigned short const tileWidth  = Game::Board::WIDTH  / Game::Tiles::COLUMN_COUNT;
    int x, y;

    // ...
    switch (message) {
        /* ... */
        case WM_CLOSE     :                             ::DestroyWindow(windowHandle); break;
        case WM_SYSCOMMAND: if (SC_CLOSE  == parameter) ::DestroyWindow(windowHandle); break;
        case WM_SYSKEYDOWN: if (VK_F4     == parameter) ::DestroyWindow(windowHandle); break;

        /* ... */
        case WM_KEYDOWN: {
            if (VK_ESCAPE == parameter) ::DestroyWindow(windowHandle);
            else switch (parameter) {
                case VK_DOWN : Game::Tiles::HOVERED_TILE = (Game::Tiles::HOVERED_TILE != -1) * (
                    0u
                ); break;

                case VK_LEFT : Game::Tiles::HOVERED_TILE = (Game::Tiles::HOVERED_TILE != -1) * (
                    0u == Game::Tiles::HOVERED_TILE % Game::Tiles::COLUMN_COUNT ? (
                        0u != Game::Tiles::HOVERED_TILE / Game::Tiles::COLUMN_COUNT
                        ? (
                            (Game::Tiles::COLUMN_COUNT - 1u) +
                            (((Game::Tiles::HOVERED_TILE / Game::Tiles::COLUMN_COUNT) - 1u) * Game::Tiles::COLUMN_COUNT)
                        ) : (Game::Tiles::COLUMN_COUNT * Game::Tiles::ROW_COUNT) - 1u
                    ) : Game::Tiles::HOVERED_TILE - 1u
                ); break;

                case VK_RIGHT: Game::Tiles::HOVERED_TILE = (Game::Tiles::HOVERED_TILE != -1) * (
                    Game::Tiles::COLUMN_COUNT - 1u == Game::Tiles::HOVERED_TILE % Game::Tiles::COLUMN_COUNT ? (
                        (((Game::Tiles::HOVERED_TILE / Game::Tiles::COLUMN_COUNT) + 1u) != Game::Tiles::ROW_COUNT   ) *
                        (((Game::Tiles::HOVERED_TILE / Game::Tiles::COLUMN_COUNT) + 1u) *  Game::Tiles::COLUMN_COUNT)
                    ) : Game::Tiles::HOVERED_TILE + 1u
                ); break;

                case VK_UP   : Game::Tiles::HOVERED_TILE = (Game::Tiles::HOVERED_TILE != -1) * (
                    0u
                ); break;
            }
        } break;

        case WM_LBUTTONDOWN: {
            if (MOUSEEVENTF_FROMTOUCH != (::GetMessageExtraInfo() & MOUSEEVENTF_FROMTOUCH)) {
                Game::Pointer::ACTIVE = true;
                Game::Pointer::X = GET_X_LPARAM(subparameter);
                Game::Pointer::Y = GET_Y_LPARAM(subparameter);
            }
        } break;

        case WM_MOUSEMOVE: {
            signed char const hoveredTile = Game::Tiles::HOVERED_TILE;

            // ...
            Game::Tiles::HOVERED_TILE = -1;
            Game::Pointer::X = GET_X_LPARAM(subparameter);
            Game::Pointer::Y = GET_Y_LPARAM(subparameter);

            for (unsigned char row    = Game::Tiles::ROW_COUNT   ; row--    && !~Game::Tiles::HOVERED_TILE; )
            for (unsigned char column = Game::Tiles::COLUMN_COUNT; column-- && !~Game::Tiles::HOVERED_TILE; ) {
                x = boardLeft + (column * (tileWidth  + Game::Tiles::MARGIN));
                y = boardTop  + (row    * (tileHeight + Game::Tiles::MARGIN));

                if (
                    (Game::Pointer::X >= x + Game::Tiles::MARGIN && Game::Pointer::X < x + tileWidth ) &&
                    (Game::Pointer::Y >= y + Game::Tiles::MARGIN && Game::Pointer::Y < y + tileHeight)
                ) Game::Tiles::HOVERED_TILE = column + (row * Game::Tiles::COLUMN_COUNT);
            }

            // ...
            if (hoveredTile != Game::Tiles::HOVERED_TILE)
            ::RedrawWindow(windowHandle, NULL, NULL, RDW_INTERNALPAINT);
        } break;

        case WM_LBUTTONUP  : /* ->> Called by `WM_TOUCH` afterward */ Game::Pointer::ACTIVE = false; break;
        case WM_SETCURSOR  : return TRUE;

        #ifdef WM_TOUCH
          case WM_TOUCH    : {
            HTOUCHINPUT const touchInputHandle = reinterpret_cast<HTOUCHINPUT>(Program::THREAD_MESSAGE.lParam);
            TOUCHINPUT touchInputs[10];
            UINT const touchInputsCount = static_cast<UINT>(LOWORD(Program::THREAD_MESSAGE.wParam));

            // ...
            if (FALSE != ::GetTouchInputInfo(touchInputHandle, touchInputsCount < 10u ? touchInputsCount : 10u, static_cast<PTOUCHINPUT>(touchInputs), sizeof(TOUCHINPUT)))
            ::CloseTouchInputHandle(touchInputHandle);

            Game::Pointer::ACTIVE = true;
            Game::Pointer::X = TOUCH_COORD_TO_PIXEL(touchInputs -> x) - Window::LEFT;
            Game::Pointer::Y = TOUCH_COORD_TO_PIXEL(touchInputs -> y) - Window::TOP;
          } return 0x0L;
        #endif

        /* ... */
        case WM_CREATE: {
            BITMAPINFO bitmapInformation;
            LPVOID const creationParameter = reinterpret_cast<CREATESTRUCTA const*>(subparameter) -> lpCreateParams;

            // ...
            bitmapInformation.bmiColors -> rgbBlue     = 0u;
            bitmapInformation.bmiColors -> rgbGreen    = 0u;
            bitmapInformation.bmiColors -> rgbRed      = 0u;
            bitmapInformation.bmiColors -> rgbReserved = 0x0u;
            bitmapInformation.bmiHeader.biBitCount     = 32u;
            bitmapInformation.bmiHeader.biClrUsed      = 0u;
            bitmapInformation.bmiHeader.biClrImportant = 0u;
            bitmapInformation.bmiHeader.biCompression  = BI_RGB;
            bitmapInformation.bmiHeader.biSize         = sizeof(BITMAPINFOHEADER);

            /* ... ->> Window bitmap and graphics context */ {
                Window::DEVICE_CONTEXT_HANDLE = ::GetDCEx(windowHandle, static_cast<HRGN>(NULL), DCX_LOCKWINDOWUPDATE | DCX_NORESETATTRS | DCX_WINDOW);
                if (NULL == Window::DEVICE_CONTEXT_HANDLE) TERMINATE("Unable to paint game window");

                Window::DEVICE_CONTEXT_BITMAP_HANDLE = ::CreateCompatibleBitmap(Window::DEVICE_CONTEXT_HANDLE, Window::WIDTH, Window::HEIGHT);
                if (NULL == Window::DEVICE_CONTEXT_BITMAP_HANDLE) TERMINATE("Unable to draw on game window");

                // ...
                bitmapInformation.bmiHeader.biHeight        = -Window::HEIGHT;
                bitmapInformation.bmiHeader.biPlanes        = 1u;
                bitmapInformation.bmiHeader.biSizeImage     = Window::HEIGHT * Window::WIDTH * sizeof(UINT32);
                bitmapInformation.bmiHeader.biWidth         = Window::WIDTH;
                bitmapInformation.bmiHeader.biXPelsPerMeter = ::GetDeviceCaps(Window::DEVICE_CONTEXT_HANDLE, HORZRES) / ::GetDeviceCaps(Window::DEVICE_CONTEXT_HANDLE, HORZSIZE);
                bitmapInformation.bmiHeader.biYPelsPerMeter = ::GetDeviceCaps(Window::DEVICE_CONTEXT_HANDLE, VERTRES) / ::GetDeviceCaps(Window::DEVICE_CONTEXT_HANDLE, VERTSIZE);

                // ...
                Window::MEMORY_DEVICE_CONTEXT_HANDLE = ::CreateCompatibleDC(Window::DEVICE_CONTEXT_HANDLE);
                if (NULL == Window::MEMORY_DEVICE_CONTEXT_HANDLE) TERMINATE("Unable to render on game window");

                Window::MEMORY_DEVICE_CONTEXT_BITMAP_HANDLE = ::CreateDIBSection(Window::MEMORY_DEVICE_CONTEXT_HANDLE, &bitmapInformation, DIB_RGB_COLORS, static_cast<VOID**>(static_cast<void*>(&Window::MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY)), NULL, 0u);
                if (NULL == Window::MEMORY_DEVICE_CONTEXT_BITMAP_HANDLE && NULL == Window::MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY) TERMINATE("Unable to render on game window");
            }

            /* ... ->> Game pieces bitmap and graphics context */ {
                Game::Pieces::BITMAP_HANDLE = static_cast<HBITMAP>(::LoadImage(static_cast<HINSTANCE>(NULL), Game::Pieces::BITMAP_FILE_NAME, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTCOLOR | LR_LOADFROMFILE));

                if (NULL != Game::Pieces::BITMAP_HANDLE) Game::Pieces::BITMAP_DEVICE_CONTEXT_HANDLE = ::CreateCompatibleDC(Window::DEVICE_CONTEXT_HANDLE);
                if (NULL != Game::Pieces::BITMAP_DEVICE_CONTEXT_HANDLE) {
                    ::GetObject(Game::Pieces::BITMAP_HANDLE, sizeof(BITMAP), &Game::Pieces::BITMAP);
                    Game::Pieces::BITMAP_MEMORY = static_cast<UINT32*>(std::malloc(Game::Pieces::BITMAP.bmHeight * Game::Pieces::BITMAP.bmWidth * sizeof(UINT32)));

                    if (NULL != Game::Pieces::BITMAP_MEMORY) {
                        bitmapInformation.bmiHeader.biHeight        = -Game::Pieces::BITMAP.bmHeight;
                        bitmapInformation.bmiHeader.biPlanes        = Game::Pieces::BITMAP.bmPlanes;
                        bitmapInformation.bmiHeader.biSizeImage     = Game::Pieces::BITMAP.bmHeight * Game::Pieces::BITMAP.bmWidth * sizeof(UINT32);
                        bitmapInformation.bmiHeader.biWidth         = Game::Pieces::BITMAP.bmWidth;
                        bitmapInformation.bmiHeader.biXPelsPerMeter = ::GetDeviceCaps(Game::Pieces::BITMAP_DEVICE_CONTEXT_HANDLE, HORZRES) / ::GetDeviceCaps(Game::Pieces::BITMAP_DEVICE_CONTEXT_HANDLE, HORZSIZE);
                        bitmapInformation.bmiHeader.biYPelsPerMeter = ::GetDeviceCaps(Game::Pieces::BITMAP_DEVICE_CONTEXT_HANDLE, VERTRES) / ::GetDeviceCaps(Game::Pieces::BITMAP_DEVICE_CONTEXT_HANDLE, VERTSIZE);

                        // ...
                        ::GetDIBits(Game::Pieces::BITMAP_DEVICE_CONTEXT_HANDLE, Game::Pieces::BITMAP_HANDLE, 0u, Game::Pieces::BITMAP.bmHeight, Game::Pieces::BITMAP_MEMORY, &bitmapInformation, DIB_RGB_COLORS);
                        ::SelectObject(Game::Pieces::BITMAP_DEVICE_CONTEXT_HANDLE, Game::Pieces::BITMAP_HANDLE);
                    }
                }
            }

            // ... ->> Setup
            Game::Board::HEIGHT = ((Window::HEIGHT < Window::WIDTH ? Window::HEIGHT : Window::WIDTH) * 9) / 10;
            Game::Board::WIDTH  = ((Window::HEIGHT < Window::WIDTH ? Window::HEIGHT : Window::WIDTH) * 9) / 10;

            ::GetObject(Window::MEMORY_DEVICE_CONTEXT_BITMAP_HANDLE, sizeof(BITMAP), &Window::MEMORY_DEVICE_CONTEXT_BITMAP);
            // ::FreeConsole();

            ::SelectObject(Window::DEVICE_CONTEXT_HANDLE, Window::DEVICE_CONTEXT_BITMAP_HANDLE);
            ::SelectObject(Window::MEMORY_DEVICE_CONTEXT_HANDLE, Window::MEMORY_DEVICE_CONTEXT_BITMAP_HANDLE);
            ::SetCursor(Window::CURSOR);
            ::ShowWindow(windowHandle, /* --> SW_SHOWDEFAULT */ static_cast<long>(static_cast<int>(reinterpret_cast<intptr_t>(creationParameter))));
            #ifdef WM_TOUCH
              if (0 != ::GetSystemMetrics(0x5E /* --> SM_DIGITIZER */))
              ::RegisterTouchWindow(windowHandle, 0x0);
            #endif
        } break;

        // ...
        case WM_DESTROY: {
            ::DeleteDC(Window::MEMORY_DEVICE_CONTEXT_HANDLE); ::DeleteObject(Window::MEMORY_DEVICE_CONTEXT_BITMAP_HANDLE);
            ::ReleaseDC(windowHandle, Window::DEVICE_CONTEXT_HANDLE);
            Window::HANDLE = NULL;

            ::PostQuitMessage(EXIT_SUCCESS);
        } break;

        /* ... */
        case WM_PAINT: {
            Piece const *const pieces = Game::getPieces();
            unsigned short const tileContentHeight = tileHeight - Game::Tiles::MARGIN;
            unsigned short const tileContentWidth  = tileWidth  - Game::Tiles::MARGIN;

            // ... ->> Board & Tiles
            for (unsigned short boardY = (tileHeight + Game::Tiles::MARGIN) * Game::Tiles::ROW_COUNT   ; boardY--; )
            for (unsigned short boardX = (tileWidth  + Game::Tiles::MARGIN) * Game::Tiles::COLUMN_COUNT; boardX--; ) {
                DWORD                tileColor;
                unsigned char const  tileColumn = boardX / (tileWidth  + Game::Tiles::MARGIN);
                unsigned char const  tileRow    = boardY / (tileHeight + Game::Tiles::MARGIN);
                unsigned short const tileX      = boardX - (tileColumn * (tileWidth + Game::Tiles::MARGIN));
                unsigned short const tileY      = boardY - (tileRow    * (tileWidth + Game::Tiles::MARGIN));

                // ... ->> Board
                x = boardLeft + boardX;
                y = boardTop  + boardY;

                if ((x > -1 && x < Window::WIDTH) && (y > -1 && y < Window::HEIGHT))
                Window::MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY[x + (y * Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmWidth)] = 0xFF000000u | Game::Board::COLOR;

                // ... ->> Tiles
                tileColor = Game::Tiles::COLOR[(tileColumn + tileRow) % 2u];
                x = boardLeft + tileX + (tileColumn * (tileWidth  + Game::Tiles::MARGIN));
                y = boardTop  + tileY + (tileRow    * (tileHeight + Game::Tiles::MARGIN));

                if (
                    (tileX >= Game::Tiles::MARGIN && tileX < tileWidth ) &&
                    (tileY >= Game::Tiles::MARGIN && tileY < tileHeight)
                ) {
                    unsigned short const tileContentX = tileX - Game::Tiles::MARGIN;
                    unsigned short const tileContentY = tileY - Game::Tiles::MARGIN;

                    // ... ->> Hovered
                    if (
                        tileColumn == Game::Tiles::HOVERED_TILE % Game::Tiles::COLUMN_COUNT &&
                        tileRow    == Game::Tiles::HOVERED_TILE / Game::Tiles::COLUMN_COUNT
                    ) tileColor = 0x000FFFu;//Game::Tiles::HOVER_COLOR[(tileColumn + tileRow) % 2u];

                    // ... ->> Beveled
                    if (
                        (tileContentX > tileContentWidth  - Game::Tiles::BEVEL || tileContentX < 0u + Game::Tiles::BEVEL) ||
                        (tileContentY > tileContentHeight - Game::Tiles::BEVEL || tileContentY < 0u + Game::Tiles::BEVEL)
                    ) tileColor = (
                        (((((tileColor >> 0x10u) & 0xFFu) * 2u) / 3u) << 0x10u) |
                        (((((tileColor >> 0x08u) & 0xFFu) * 2u) / 3u) << 0x08u) |
                        (((((tileColor >> 0x00u) & 0xFFu) * 2u) / 3u) << 0x00u)
                    );

                    // ...
                    if ((x > -1 && x < Window::WIDTH) && (y > -1 && y < Window::HEIGHT))
                    Window::MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY[x + (y * Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmWidth)] = 0xFF000000u | tileColor;
                }
            }

            // ... ->> Pieces
            for (Piece const *piece = pieces + (2u * (Piece::countTotal(Piece::BISHOP) + Piece::countTotal(Piece::KING) + Piece::countTotal(Piece::KNIGHT) + Piece::countTotal(Piece::PAWN) + Piece::countTotal(Piece::QUEEN) + Piece::countTotal(Piece::ROOK))); piece-- != pieces; ) {
                unsigned short const pieceBitmapHeight = Game::Pieces::BITMAP.bmHeight / 2u;
                unsigned short const pieceBitmapWidth  = Game::Pieces::BITMAP.bmWidth  / 6u;
                DWORD const          pieceColor  = piece -> getColor();
                unsigned char const  pieceColumn = piece -> getColumn();
                unsigned short const pieceHeight = (tileHeight * 2u) / 3u;
                unsigned char const  pieceRow    = piece -> getRow();
                Piece::Type const    pieceType   = piece -> getType();
                unsigned short const pieceWidth  = (tileWidth  * 2u) / 3u;

                // ...
                for (unsigned short pieceY = tileHeight; pieceY--; )
                for (unsigned short pieceX = tileWidth ; pieceX--; ) {
                    x = pieceX + (boardLeft + (pieceColumn * (tileWidth  + Game::Tiles::MARGIN)) - ((tileWidth  - pieceWidth ) / 2u));
                    y = pieceY + (boardTop  + (pieceRow    * (tileHeight + Game::Tiles::MARGIN)) - ((tileHeight - pieceHeight) / 2u));

                    if (
                        (x > -1 && x < Window::WIDTH) && (y > -1 && y < Window::HEIGHT) &&
                        (pieceWidth > tileWidth - pieceX) && (pieceHeight > tileHeight - pieceY)
                    ) {
                        // ... ->> Bitmap/ computed
                        if (NULL == Game::Pieces::BITMAP_HANDLE) {}
                        else {
                            DWORD          pieceBitmapColor;
                            DWORD const    pieceBitmapMaskColor = *Game::Pieces::BITMAP_MEMORY;
                            unsigned short pieceBitmapX = pieceBitmapWidth;
                            unsigned short pieceBitmapY = Color::LIGHT == pieceColor ? pieceBitmapHeight : 0u;

                            // ...
                            switch (pieceType) {
                                case Piece::BISHOP: pieceBitmapX *= 0u; break;
                                case Piece::KING  : pieceBitmapX *= 1u; break;
                                case Piece::KNIGHT: pieceBitmapX *= 2u; break;
                                case Piece::PAWN  : pieceBitmapX *= 3u; break;
                                case Piece::QUEEN : pieceBitmapX *= 4u; break;
                                case Piece::ROOK  : pieceBitmapX *= 5u; break;
                            }

                            pieceBitmapX += ((pieceX - (((tileWidth  - pieceWidth ) / 2u) + ((tileWidth  - pieceWidth ) / 2u))) * pieceBitmapWidth ) / pieceWidth;
                            pieceBitmapY += ((pieceY - (((tileHeight - pieceHeight) / 2u) + ((tileHeight - pieceHeight) / 2u))) * pieceBitmapHeight) / pieceHeight;

                            // ...
                            if (pieceBitmapX < Game::Pieces::BITMAP.bmWidth && pieceBitmapY < Game::Pieces::BITMAP.bmHeight) {
                                pieceBitmapColor = Game::Pieces::BITMAP_MEMORY[pieceBitmapX + (pieceBitmapY * Game::Pieces::BITMAP.bmWidth)];

                                if (pieceBitmapColor != pieceBitmapMaskColor)
                                Window::MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY[x + (y * Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmWidth)] = 0xFF000000u | pieceBitmapColor;
                            }
                        }
                    }
                }
            }

            /* ... */
            ::BitBlt(Window::DEVICE_CONTEXT_HANDLE, 0, 0, Window::WIDTH, Window::HEIGHT, Window::MEMORY_DEVICE_CONTEXT_HANDLE, 0, 0, SRCCOPY);
            // if (FALSE != ::GetUpdateRect(windowHandle, NULL, FALSE)) ::RedrawWindow(windowHandle, NULL, NULL, RDW_INTERNALPAINT);
        } return 0x0L;
    }

    // ...
    return ::DefWindowProc(windowHandle, message, parameter, subparameter);
}

/* : Terminate */
void TERMINATE() { TERMINATE(NULL); }
void TERMINATE(char const message[]) {
    std::free(Game::Pieces::BITMAP_MEMORY);
    if (NULL != Game::Pieces::BITMAP_DEVICE_CONTEXT_HANDLE) ::DeleteObject(Game::Pieces::BITMAP_DEVICE_CONTEXT_HANDLE);
    if (NULL != Game::Pieces::BITMAP_HANDLE) ::DeleteObject(Game::Pieces::BITMAP_HANDLE);

    if (NULL != Program::Lock::FILE && INVALID_HANDLE_VALUE != Program::Lock::FILE) ::CloseHandle(Program::Lock::FILE);
    if (NULL != Program::Lock::MUTEX) ::CloseHandle(Program::Lock::MUTEX);

    if (NULL != Window::HANDLE) ::DestroyWindow(Window::HANDLE);
    ::UnregisterClass(Window::CLASS_NAME, Program::HANDLE);

    // Logic ->> `TERMINATE(...)` called by the user.
    if (NULL != message) {
        Program::EXIT_CODE = EXIT_FAILURE;

        ::MessageBox(NULL, message, NULL /* --> "Error" */, MB_APPLMODAL | MB_DEFBUTTON1 | MB_ICONERROR | MB_OK | MB_SETFOREGROUND);
        Program::exit();
    }
}
