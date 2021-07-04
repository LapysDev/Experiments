/* ... --> advapi32.lib, gdi32.lib, kernel32.lib, shell32.lib, user32.lib
    --- WARN ---
    #Lapys:
*/
/* Definition > ... */
#ifndef MOUSEEVENTF_FROMTOUCH
#   define MOUSEEVENTF_FROMTOUCH 0xFF515700
#endif
#define _MAC
#define INC_OLE1
#define NOCRYPT

#undef NOGDI
#undef UNICODE

/* Import */
// : [C Standard Library]
#include <stdint.h> // Standard Integers

// : [C++ Standard Library]
#include <cstddef> // C Standard Definitions
#include <csignal> // C Signal
#include <cstdio>  // C Standard Input/ Output
#include <cstdlib> // C Standard Library

// : [Windows API]
#include <windef.h>   // Windows Definition
#include <winbase.h>  // Windows Base
#include <wincon.h>   // Windows Console
#include <winerror.h> // Windows Errors
#include <wingdi.h>   // Windows GDI
#include <winnt.h>    // Windows New Technologies
#include <winuser.h>  // Windows User
#   include <basetsd.h>        // Base Types & Definitions
#   include <errhandlingapi.h> // Error Handling API
#   include <libloaderapi.h>   // Library Loader API
#   include <memoryapi.h>      // Memory API
#   include <shellapi.h>       // Shell API

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
    private: uint8_t value : count;
    public:
        bit(uint8_t const value = 0u) : value(value) {}

        // ...
        bit<count>& operator =(bit<count> const bits) { this -> value = bits.value; return *this; }
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

        operator uint8_t(void) const { return this -> value; }
};

// : Piece ->> Pointer-to-implementation structure; Implementation is `Game::MEMORY`
union Piece {
    friend struct Game;

    struct Color {
        private: unsigned char const value;
        public:
            static Color const BLACK, WHITE;

            Color(unsigned char const value) : value(value) {}
            operator unsigned char(void) const { return this -> value; }
    };
    enum Type { BISHOP, KING, KNIGHT, PAWN, QUEEN, ROOK };

    private:
        bit<8u> *const self;
        Piece(bit<8u>* const address) : self(address) {}

    public:
        // ...
        static unsigned char countTotal(Type const);

        void capture(Piece const);
        void castle (void);
        void promote(Type const);

        // ...
        Color   getColor        (void) const;
        bit<3u> getColumn       (void) const;
        bit<3u> getIndex        (void) const;
        bit<6u> getPosition     (void) const;
        Type    getPromotionType(void) const;
        bit<3u> getRow          (void) const;
        Type    getType         (void) const;

        bool    isCaptured      (void) const;
        bool    isCastled       (void) const;
        bool    isIncidental    (void) const; // ->> en passant
        bool    isPromoted      (void) const;

        void    setColumn       (bit<3u> const);
        void    setPosition     (bit<3u> const, bit<3u> const);
        void    setRow          (bit<3u> const);
};

/* Definition > ... */
typedef Piece Bishop, King, Knight, Pawn, Queen, Rook;
typedef Piece::Color Color;

/* Namespace */
/* : Game
    --- WARNING (Lapys) -> Requires a byte to be at least 8 bits
    --- UPDATE (Lapys) -> Could feasibly algorithmically compress the game to a single integer state i.e.: 35 to the 80th possible moves
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
        static HDC     BITMAP_DEVICE_CONTEXT;
        static HBITMAP BITMAP_HANDLE;
        static UINT32 *BITMAP_MEMORY;
    };

    struct Tiles {
        static DWORD               COLORS[2];
        static unsigned char const COLUMN_COUNT;
        static DWORD               HOVER_COLORS[2];
        static unsigned char       MARGIN;
        static unsigned char const ROW_COUNT;
        static DWORD               SELECTION_COLORS[2];
    };

    // ...
    static bit<8u> MEMORY[/* 275 ÷ 8 */ 35];

    // ... ->> Address memory segments
    static bit<8u>* addressBishopData(void);
    static bit<8u>* addressKnightData(void);
    static bit<8u>* addressKingData  (void);
    static bit<8u>* addressPawnData  (void);
    static bit<8u>* addressQueenData (void);
    static bit<8u>* addressRookData  (void);

    static bit<8u>* addressCapturedOfficerData(void);
    static bit<8u>* addressCapturedPawnData   (void);
    static bit<8u>* addressCastleData         (void);
    static bit<8u>* addressIncidentalPawnData (void);
    static bit<8u>* addressPromotedPawnData   (void);
    static bit<8u>* addressTurnData           (void);

    // ...
    static Piece getPiece     (Color const, Piece::Type const, bit<3u> const = 0u);
    static Color getPlayerTurn(void);

    static void  setPlayerTurn(Color const);
};

// : Program
namespace Program {
    namespace Lock {
        static HANDLE      FILE       = NULL;
        static char const *FILE_NAME  = NULL;

        static HANDLE      MUTEX      = NULL;
        static char const *MUTEX_NAME = NULL;
    }

    static LPSTR     ARGUMENTS           = NULL;
    static int       EXIT_CODE           = EXIT_SUCCESS;
    static CHAR      FILE_NAME[MAX_PATH] = {0};
    static HINSTANCE HANDLE              = NULL;
    static HINSTANCE PREVIOUS_HANDLE     = NULL;
    static MSG       THREAD_MESSAGE      = MSG();

    // ... ->> Program termination handlers
    static void exit (void);
    static void exit (int const);
    static void raise(int const);

    // ... ->> Program termination listeners
    static void (*onabort       )(void) = NULL;
    static void (*onexit        )(void) = NULL;
    static void (*oninterrupt   )(void) = NULL;
    static void (*oninvalidfault)(void) = NULL;
    static void (*onmathfault   )(void) = NULL;
    static void (*onsegfault    )(void) = NULL;
    static void (*onterminate   )(void) = NULL;
}

// : Window
namespace Window {
    static int     APPEARANCE      = SW_SHOW;
    static HBRUSH  BACKGROUND      = EXIT_SUCCESS;
    static LPCSTR  CLASS_NAME      = "window";
    static UINT    CLASS_STYLE     = CS_GLOBALCLASS | CS_OWNDC;
    static HCURSOR CURSOR          = NULL;
    static HICON   FAVICON         = NULL;
    static HWND    HANDLE          = NULL;
    static int     HEIGHT          = -1;
    static HICON   ICON            = NULL;
    static int     LEFT            = -1;
    static LRESULT CALLBACK (*PROCEDURE)(HWND const, UINT const, WPARAM const, LPARAM const) = &::DefWindowProc;
    static DWORD   STYLE           = WS_OVERLAPPEDWINDOW;
    static DWORD   STYLE_EXTENSION = 0x0u;
    static LPCSTR  TITLE           = "";
    static int     TOP             = -1;
    static int     WIDTH           = -1;

    // ... ->> Renderers
    static HBITMAP DEVICE_CONTEXT_BITMAP_HANDLE        = NULL;
    static HDC     DEVICE_CONTEXT_HANDLE               = NULL;

    static BITMAP  MEMORY_DEVICE_CONTEXT_BITMAP        = BITMAP();
    static HBITMAP MEMORY_DEVICE_CONTEXT_BITMAP_HANDLE = NULL;
    static UINT32 *MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY = NULL;
    static HDC     MEMORY_DEVICE_CONTEXT_HANDLE        = NULL;
}

/* Global > ... */
Color const Color::BLACK = 0u;
Color const Color::WHITE = 1u;

bit<8u>             Game::MEMORY[sizeof(Game::MEMORY) / sizeof(bit<8u>)] = {0};
DWORD               Game::Board::COLOR        = 0x000000u;
unsigned short      Game::Board::HEIGHT       = 0u;
unsigned short      Game::Board::WIDTH        = 0u;
unsigned char const Game::Tiles::COLUMN_COUNT = 8u;
unsigned char const Game::Tiles::ROW_COUNT    = 8u;

BITMAP         Game::Pieces::BITMAP;
LPCSTR         Game::Pieces::BITMAP_FILE_NAME;
HDC            Game::Pieces::BITMAP_DEVICE_CONTEXT;
HBITMAP        Game::Pieces::BITMAP_HANDLE;
UINT32        *Game::Pieces::BITMAP_MEMORY;

DWORD          Game::Tiles::COLORS[2];
DWORD          Game::Tiles::HOVER_COLORS[2];
unsigned char  Game::Tiles::MARGIN;
DWORD          Game::Tiles::SELECTION_COLORS[2];
bit<8u>        Game::MEMORY[/* 275 ÷ 8 */ 35];

/* Function */
// : Game
bit<8u>* Game::addressBishopData(void) { return Game::MEMORY + 20; }
bit<8u>* Game::addressKnightData(void) { return Game::MEMORY + 24; }
bit<8u>* Game::addressKingData  (void) { return Game::MEMORY - 1; }
bit<8u>* Game::addressPawnData  (void) { return Game::MEMORY + 0; }
bit<8u>* Game::addressQueenData (void) { return Game::MEMORY - 3; }
bit<8u>* Game::addressRookData  (void) { return Game::MEMORY + 28; }

bit<8u>* Game::addressCapturedOfficerData(void) { return Game::MEMORY + 16; }
bit<8u>* Game::addressCapturedPawnData   (void) { return Game::MEMORY + 33; }
bit<8u>* Game::addressCastleData         (void) { return Game::MEMORY + 32; }
bit<8u>* Game::addressIncidentalPawnData (void) { return Game::MEMORY + 32; }
bit<8u>* Game::addressPromotedPawnData   (void) { return Game::MEMORY + 18; }
bit<8u>* Game::addressTurnData           (void) { return Game::MEMORY + 34; }

Piece Game::getPiece(Color const color, Piece::Type const type, bit<3u> const index) {
    switch (type) {
        case Piece::BISHOP: return Piece(Game::addressBishopData() + index + (Color::WHITE == color ? Piece::countTotal(Piece::BISHOP) : 0u));
        case Piece::KING: return Piece(Game::addressKingData() + index - (0u + (Color::WHITE == color ? 2u : 1u)));
        case Piece::KNIGHT: return Piece(Game::addressKnightData() + index + (Color::WHITE == color ? Piece::countTotal(Piece::KNIGHT) : 0u));
        case Piece::PAWN: return Piece(Game::addressPawnData() + index + (Color::WHITE == color ? Piece::countTotal(Piece::PAWN) : 0u));
        case Piece::QUEEN: return Piece(Game::addressQueenData() + index - (2u + (Color::WHITE == color ? 2u : 1u)));
        case Piece::ROOK: return Piece(Game::addressRookData() + index + (Color::WHITE == color ? Piece::countTotal(Piece::ROOK) : 0u));
    }

    return Piece(NULL);
}

Color Game::getPlayerTurn(void) {
    return *Game::addressTurnData() & 0x01u ? Color::WHITE : Color::BLACK;
}

void Game::setPlayerTurn(Color const color) {
    if (Color::BLACK == color) *Game::addressTurnData() &= 0xFEu;
    if (Color::WHITE == color) *Game::addressTurnData() |= 0x01u;
}

// : Pawn
Piece::Type Pawn::getPromotionType(void) const {
    switch (*(this -> self) & 0xC0u) {
        case 0x0u: return Piece::BISHOP;
        case 0x1u: return Piece::KNIGHT;
        case 0x2u: return Piece::QUEEN;
        case 0x3u: return Piece::ROOK;
    }

    return Piece::PAWN;
}

bool Pawn::isPromoted(void) const {
    return (Game::addressPromotedPawnData()[Color::WHITE == this -> getColor() ? 1 : 0] >> this -> getIndex()) & 0x1u;
}

void Pawn::promote(Type const type) {
    Game::addressPromotedPawnData()[Color::WHITE == this -> getColor() ? 1 : 0] |= 1u << this -> getIndex();

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
        case Piece::PAWN  : Game::addressCapturedPawnData   ()[Color::WHITE == piece.getColor() ? 1 : 0] |= 1u << piece.getIndex(); break;

        case Piece::BISHOP: Game::addressCapturedOfficerData()[0] |= 1u << ((piece.getIndex() + (Color::WHITE == piece.getColor() ? Piece::countTotal(Piece::BISHOP) : 0u)) << 4u); break;
        case Piece::KNIGHT: Game::addressCapturedOfficerData()[0] |= 1u << ((piece.getIndex() + (Color::WHITE == piece.getColor() ? Piece::countTotal(Piece::KNIGHT) : 0u)) << 0u); break;
        case Piece::QUEEN : Game::addressCapturedOfficerData()[1] |= 1u << ((piece.getIndex() + (Color::WHITE == piece.getColor() ? Piece::countTotal(Piece::QUEEN ) : 0u)) << 2u); break;
        case Piece::ROOK  : Game::addressCapturedOfficerData()[1] |= 1u << ((piece.getIndex() + (Color::WHITE == piece.getColor() ? Piece::countTotal(Piece::ROOK  ) : 0u)) << 4u); break;
    }
}

unsigned char Piece::countTotal(Type const type) {
    switch (type) {
        case Piece::BISHOP: case Piece::KNIGHT: case Piece::ROOK: return 2u;
        case Piece::KING: case Piece::QUEEN: return 1u;
        case Piece::PAWN: return 8u;
    }

    return 0u;
}

Color Piece::getColor(void) const {
    for (Type const
        types[] = {Piece::BISHOP, Piece::KING, Piece::KNIGHT, Piece::PAWN, Piece::QUEEN, Piece::QUEEN},
        *type   = types + (sizeof(types) / sizeof(Type));
    type-- != types; )
    for (unsigned char iterator = Piece::countTotal(*type); iterator--; ) {
        if (this -> self == Game::getPiece(Color::BLACK, *type, iterator).self) return Color::BLACK;
        if (this -> self == Game::getPiece(Color::WHITE, *type, iterator).self) return Color::WHITE;
    }

    return static_cast<Color>(0x0u);
}

bit<3u> Piece::getColumn(void) const {
    return Piece::BISHOP != this -> getType() ? this -> getPosition() & 0xF8u : (
        ((this -> getPosition() * 2u) % Game::Tiles::COLUMN_COUNT) + (this -> getRow() % 2u
            ? this -> getIndex() == (Color::WHITE == this -> getColor() ? 0u : 1u)
            : this -> getIndex() == (Color::WHITE == this -> getColor() ? 1u : 0u)
        )
    );
}

bit<3u> Piece::getIndex(void) const {
    for (Type const
        types[] = {Piece::BISHOP, Piece::KING, Piece::KNIGHT, Piece::PAWN, Piece::QUEEN, Piece::QUEEN},
        *type   = types + (sizeof(types) / sizeof(Type));
    type-- != types; ) {
        for (unsigned char iterator = Piece::countTotal(*type); iterator--; )
        if (
            this -> self == Game::getPiece(Color::BLACK, *type, iterator).self ||
            this -> self == Game::getPiece(Color::WHITE, *type, iterator).self
        ) return iterator;
    }

    return 0u;
}

bit<6u> Piece::getPosition(void) const {
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

bit<3u> Piece::getRow(void) const {
    return Piece::BISHOP != this -> getType() ? this -> getPosition() & 0x07u : (
        this -> getPosition() / (Game::Tiles::COLUMN_COUNT / 2u)
    );
}

Piece::Type Piece::getType(void) const {
    for (Type const
        types[] = {Piece::BISHOP, Piece::KING, Piece::KNIGHT, Piece::PAWN, Piece::QUEEN, Piece::QUEEN},
        *type   = types + (sizeof(types) / sizeof(Type));
    type-- != types; ) {
        for (unsigned char iterator = Piece::countTotal(*type); iterator--; )
        if (
            this -> self == Game::getPiece(Color::BLACK, *type, iterator).self ||
            this -> self == Game::getPiece(Color::WHITE, *type, iterator).self
        ) return *type;
    }

    return static_cast<Type>(0x0u);
}

bool Piece::isCaptured(void) const {
    switch (this -> getType()) {
        case Piece::KING  : return false;
        case Piece::PAWN  : return (Game::addressCapturedPawnData()[Color::WHITE == this -> getColor() ? 1 : 0] >> this -> getIndex()) & 0x01u;

        case Piece::BISHOP: return ((Game::addressCapturedOfficerData()[0] >> 4u) >> (this -> getIndex() + (Color::WHITE == this -> getColor() ? Piece::countTotal(Piece::BISHOP) : 0u))) & 0x01u;
        case Piece::KNIGHT: return ((Game::addressCapturedOfficerData()[0] >> 0u) >> (this -> getIndex() + (Color::WHITE == this -> getColor() ? Piece::countTotal(Piece::KNIGHT) : 0u))) & 0x01u;
        case Piece::QUEEN : return ((Game::addressCapturedOfficerData()[1] >> 2u) >> (this -> getIndex() + (Color::WHITE == this -> getColor() ? Piece::countTotal(Piece::QUEEN ) : 0u))) & 0x01u;
        case Piece::ROOK  : return ((Game::addressCapturedOfficerData()[1] >> 4u) >> (this -> getIndex() + (Color::WHITE == this -> getColor() ? Piece::countTotal(Piece::ROOK  ) : 0u))) & 0x01u;
    }

    return false;
}

bool Piece::isIncidental(void) const {
    unsigned char const count = Piece::countTotal(Piece::PAWN);
    unsigned char const index = *Game::addressIncidentalPawnData() & 0x0Fu;

    return this -> self == Game::getPiece(count > index ? Color::BLACK : Color::WHITE, Piece::PAWN, index % count).self;
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
                    ? index == (Color::WHITE == color ? 0u : 1u)
                    : index == (Color::WHITE == color ? 1u : 0u)
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
            *(this -> self) |= row | (column << 3u);
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

            *position[0] |= (column & 0x06u) << 6u;
            *position[1] |= (((column & 0x01u) << 1u) | ((row & 0x04u) << 0u)) << 6u;
            *position[2] |= (row    & 0x03u) << 6u;
        } break;
    }
}

void Piece::setRow(bit<3u> const row) {
    this -> setPosition(this -> getColumn(), row);
}

// : Rook
void Rook::castle(void) {
    *Game::addressCastleData() |= (1u << (
        this -> getIndex() + (Color::WHITE == this -> getColor() ? Piece::countTotal(Piece::ROOK) : 0u)
    )) << 4u;
}

bool Rook::isCastled(void) const {
    return (
        (*Game::addressCastleData() >> 4u) >>
        (this -> getIndex() + (Color::WHITE == this -> getColor() ? Piece::countTotal(Piece::ROOK) : 0u))
    ) & 0x01u;
}

/* Main */
int WinMain(HINSTANCE const programHandle, HINSTANCE const programPreviousHandle, LPSTR const commandLineArguments, int const appearance) {
    // ...
    Program::ARGUMENTS = commandLineArguments;
    Program::HANDLE = programHandle;
    Program::PREVIOUS_HANDLE = programPreviousHandle;
    Window::APPEARANCE = appearance;

    std::atexit(static_cast<void (*)(void)>(&Program::exit));
    std::signal(SIGABRT, &Program::raise);
    std::signal(SIGFPE, &Program::raise);
    std::signal(SIGILL, &Program::raise);
    std::signal(SIGINT, &Program::raise);
    std::signal(SIGSEGV, &Program::raise);
    std::signal(SIGTERM, &Program::raise);

    // ...
    INITIATE();
    return Program::EXIT_CODE;
}

/* Phase --- WARN (Lapys) -> All phases except `INITIATE()` can be invoked by the user. */
/* : Initiate */
void INITIATE(...) {
    bool programAlreadyRunning = false;

    // ... ->> Configuration
    DWORD          Game::Board::COLOR;
    unsigned short Game::Board::HEIGHT;
    unsigned short Game::Board::WIDTH;
    BITMAP         Game::Pieces::BITMAP;
    LPCSTR         Game::Pieces::BITMAP_FILE_NAME;
    HDC            Game::Pieces::BITMAP_DEVICE_CONTEXT;
    HBITMAP        Game::Pieces::BITMAP_HANDLE;
    UINT32        *Game::Pieces::BITMAP_MEMORY;

    DWORD          Game::Tiles::COLORS[2];
    DWORD          Game::Tiles::HOVER_COLORS[2];
    unsigned char  Game::Tiles::MARGIN;
    DWORD          Game::Tiles::SELECTION_COLORS[2];
    bit<8u>        Game::MEMORY[/* 275 ÷ 8 */ 35];

    // ... ->> Configuration
    Game::Board::COLOR = 0xC0C0C0u;
    Game::Board::HEIGHT = 512u;
    Game::Board::WIDTH = 512u;
    Game::Pieces::BITMAP_FILE_NAME = "pieces.bmp";
    Game::Tiles::BEVEL_COLORS[0] = 0xCFCFCFu;
    Game::Tiles::BEVEL_COLORS[1] = 0x006600u;
    Game::Tiles::BEVEL_ACTIVATION_COLOR = 0x006FFFu;
    Game::Tiles::BEVEL_SELECTION_COLOR = 0x333333u;
    Game::Tiles::BEVEL_SIZE = 4u;
    Game::Tiles::COLORS[0] = 0xF0F0F0u;
    Game::Tiles::COLORS[1] = 0x009900u;
    Game::Tiles::COLUMN_COUNT = 8u;
    Game::Tiles::MARGIN = 2u;
    Game::Tiles::ROW_COUNT = 8u;

    ::GetModuleFileName(static_cast<HMODULE>(NULL), Program::FILE_NAME, MAX_PATH);
    Program::onexit = static_cast<void (*)(void)>(&TERMINATE);
    Program::Lock::FILE_NAME = "ChessLockFile.tmp";
    Program::Lock::MUTEX_NAME = "ChessLockMutex";

    Window::BACKGROUND = ::GetSysColorBrush(COLOR_WINDOW);
    Window::CURSOR = ::LoadCursor(NULL, IDC_ARROW); // --> static_cast<HCURSOR>(::LoadImage(NULL, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED))
    Window::ICON = ::ExtractIcon(static_cast<HINSTANCE>(::GetCurrentProcess()), Program::FILE_NAME, 0u);
    Window::PROCEDURE = static_cast<LRESULT CALLBACK (*)(HWND const, UINT const, WPARAM const, LPARAM const)>(&UPDATE);
    Window::STYLE = WS_POPUP;
    Window::TITLE = "Chess";

    // ... ->> Setup
    Game::clearData();

    for (unsigned char iterator = Game::Tiles::COLUMN_COUNT; iterator--; ) Game::movePiece(Game::getPiece(Piece::WHITE, Piece::PAWN, iterator), iterator, 1u);
    Game::movePiece(Game::getPiece(Piece::WHITE, Piece::ROOK  , 0u), 0u, 0u);
    Game::movePiece(Game::getPiece(Piece::WHITE, Piece::KNIGHT, 0u), 1u, 0u);
    Game::movePiece(Game::getPiece(Piece::WHITE, Piece::BISHOP, 0u), 2u, 0u);
    Game::movePiece(Game::getPiece(Piece::WHITE, Piece::KING      ), 3u, 0u);
    Game::movePiece(Game::getPiece(Piece::WHITE, Piece::QUEEN     ), 4u, 0u);
    Game::movePiece(Game::getPiece(Piece::WHITE, Piece::BISHOP, 1u), 5u, 0u);
    Game::movePiece(Game::getPiece(Piece::WHITE, Piece::KNIGHT, 1u), 6u, 0u);
    Game::movePiece(Game::getPiece(Piece::WHITE, Piece::ROOK  , 1u), 7u, 0u);

    for (unsigned char iterator = Game::Tiles::COLUMN_COUNT; iterator--; ) Game::movePiece(Game::getPiece(Piece::BLACK, Piece::PAWN, iterator), iterator, 6u);
    Game::movePiece(Game::getPiece(Piece::BLACK, Piece::ROOK  , 0u), 0u, 7u);
    Game::movePiece(Game::getPiece(Piece::BLACK, Piece::KNIGHT, 0u), 1u, 7u);
    Game::movePiece(Game::getPiece(Piece::BLACK, Piece::BISHOP, 0u), 2u, 7u);
    Game::movePiece(Game::getPiece(Piece::BLACK, Piece::KING      ), 3u, 7u);
    Game::movePiece(Game::getPiece(Piece::BLACK, Piece::QUEEN     ), 4u, 7u);
    Game::movePiece(Game::getPiece(Piece::BLACK, Piece::BISHOP, 1u), 5u, 7u);
    Game::movePiece(Game::getPiece(Piece::BLACK, Piece::KNIGHT, 1u), 6u, 7u);
    Game::movePiece(Game::getPiece(Piece::BLACK, Piece::ROOK  , 1u), 7u, 7u);

    Game::setTurn(Piece::WHITE);

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
            CHAR path[MAX_PATH + 17u] = {0};

            length = ::GetTempPath(MAX_PATH + 1u, path);
            if (0u != length) {
                for (CHAR const *name = Program::Lock::FILE_NAME; '\0' != *name; ++name) path[length++] = *name;
                Program::Lock::FILE = ::CreateFile(path, DELETE | GENERIC_READ | GENERIC_WRITE, 0x0u, NULL, CREATE_NEW, FILE_FLAG_DELETE_ON_CLOSE, NULL);

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

        classInformation.cbClsExtra = 0;
        classInformation.cbSize = sizeof(WNDCLASSEX);
        classInformation.cbWndExtra = 0;
        classInformation.hbrBackground = Window::BACKGROUND;
        classInformation.hCursor = Window::CURSOR;
        classInformation.hIcon = Window::ICON;
        classInformation.hIconSm = Window::FAVICON;
        classInformation.hInstance = Program::HANDLE;
        classInformation.lpfnWndProc = Window::PROCEDURE;
        classInformation.lpszClassName = Window::CLASS_NAME;
        classInformation.lpszMenuName = static_cast<LPCSTR>(NULL);
        classInformation.style = Window::CLASS_STYLE;

        // ...
        if (0x0 == ::RegisterClassEx(const_cast<WNDCLASSEX const*>(&classInformation)))
            TERMINATE("Unable to setup game window");

        else {
            if (Window::HEIGHT == -1 || Window::LEFT == -1 || Window::TOP == -1 || Window::WIDTH == -1) {
                RECT workareaBounds; ::SystemParametersInfo(SPI_GETWORKAREA, 0u, static_cast<PVOID>(&workareaBounds), 0x0);

                // ...
                Window::WIDTH = ((workareaBounds.right - workareaBounds.left) * 3) / 4;
                Window::HEIGHT = ((workareaBounds.bottom - workareaBounds.top) * 3) / 4;

                Window::LEFT = (((workareaBounds.right - workareaBounds.left) - Window::WIDTH) * 1) / 2;
                Window::TOP = (((workareaBounds.bottom - workareaBounds.top) - Window::HEIGHT) * 1) / 2;
            }

            Window::HANDLE = ::CreateWindowEx(
                Window::STYLE_EXTENSION, Window::CLASS_NAME, Window::TITLE, Window::STYLE,
                Window::LEFT, Window::TOP, Window::WIDTH, Window::HEIGHT,
                NULL /* --> HWND_DESKTOP */, static_cast<HMENU>(NULL), Program::HANDLE,
                reinterpret_cast<LPVOID>(static_cast<LPARAM>(Window::APPEARANCE))
            );

            // ...
            if (NULL == Window::HANDLE)
                TERMINATE("Unable to create game window");

            else while (WM_QUIT != Program::THREAD_MESSAGE.message) {
                Program::THREAD_MESSAGE_AVAILABLE = ::PeekMessage(&Program::THREAD_MESSAGE, NULL, 0x0u, 0x0u, PM_REMOVE);
                if (FALSE != Program::THREAD_MESSAGE_AVAILABLE) { ::DispatchMessage(&Program::THREAD_MESSAGE); UPDATE(); }

                Program::EXIT_CODE = Program::THREAD_MESSAGE.wParam;
            }
        }
    }
}
