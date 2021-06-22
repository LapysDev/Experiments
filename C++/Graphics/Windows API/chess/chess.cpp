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
#define NOGDI

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
union bit {
    private: uint8_t value : count;
    public:
        bit(uint8_t const value = 0u) : value(value) {}

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

        operator uint8_t(void) const { return this -> value; }
};

// : Piece ->> Pointer-to-implementation structure; Implementation is `Game::MEMORY`
union Piece {
    friend struct Game;

    struct Color { static unsigned char const BLACK = 0u, WHITE = 1u; };
    enum Type { BISHOP, KING, KNIGHT, PAWN, QUEEN, ROOK };

    private:
        bit<8u> *const self;
        Piece(bit<8u>* const address) : self(address) {}

    public:
        // ...
        static unsigned char countTotal(Piece::Type const);

        void capture(Piece const) const;
        void castle (void) const;
        void promote(Type const) const;

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
    enum PiecesEnumerationControl { CONTINUE_ENUMERATING_PIECES, STOP_ENUMERATING_PIECES };
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
    static bit<8u>* addressEnPassantData      (void);
    static bit<8u>* addressPromotedPawnData   (void);
    static bit<8u>* addressTurnData           (void);

    // ... ->> Getter/ Setter
    static Piece       getPiece     (Color const, Piece::Type const, bit<3u> const = 0u);
    static Color       getPlayerTurn(void);

    static void        setPlayerTurn(Color const);
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
bit<8u> Game::MEMORY[sizeof(Game::MEMORY) / sizeof(bit<8u>)] = {0};

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
bit<8u>* Game::addressEnPassantData      (void) { return Game::MEMORY + 32; }
bit<8u>* Game::addressPromotedPawnData   (void) { return Game::MEMORY + 18; }
bit<8u>* Game::addressTurnData           (void) { return Game::MEMORY + 34; }

// : Piece
void Piece::capture(Piece const piece) const {
    this -> setPosition(piece.getColumn(), piece.getRow());
    switch (piece.getType()) {
        // ... ->> Mark the `piece` as captured
        case Piece::KING  : break;
        case Piece::PAWN  : Game::addressCapturedPawnData   ()[Piece::WHITE == piece.getColor() ? 1u : 0u] |= 1u << piece.getIndex(); break;

        case Piece::BISHOP: Game::addressCapturedOfficerData()[0] |= 1u << ((piece.getIndex() + (Piece::WHITE == piece.getColor() ? Piece::countTotal(Piece::BISHOP) : 0u)) << 4u); break;
        case Piece::KNIGHT: Game::addressCapturedOfficerData()[0] |= 1u << ((piece.getIndex() + (Piece::WHITE == piece.getColor() ? Piece::countTotal(Piece::KNIGHT) : 0u)) << 0u); break;
        case Piece::QUEEN : Game::addressCapturedOfficerData()[1] |= 1u << ((piece.getIndex() + (Piece::WHITE == piece.getColor() ? Piece::countTotal(Piece::QUEEN ) : 0u)) << 2u); break;
        case Piece::ROOK  : Game::addressCapturedOfficerData()[1] |= 1u << ((piece.getIndex() + (Piece::WHITE == piece.getColor() ? Piece::countTotal(Piece::ROOK  ) : 0u)) << 4u); break;
    }
}

unsigned char Piece::countTotal(Piece::Type const type) {
    switch (type) {
        case Piece::BISHOP: case Piece::KNIGHT: case Piece::ROOK: return 2u;
        case Piece::KING: case Piece::QUEEN: return 1u;
        case Piece::PAWN: return 8u;
    }

    return 0u;
}

void Rook::castle(void) const {
}

// Color Piece::getColor(void) const {}
// bit<3u> Piece::getColumn(void) const {}
// bit<3u> Piece::getIndex(void) const {}
// bit<6u> Piece::getPosition(void) const {}
// Piece::Type Piece::getPromotionType(void) const {}
// bit<3u> Piece::getRow(void) const {}
// Piece::Type Piece::getType(void) const {}
// bool Piece::isCaptured(void) const {}
// bool Piece::isCastled(void) const {}
// bool Piece::isIncidental(void) const {}
// bool Piece::isPromoted(void) const {}
// void Piece::promote(Piece::Type const type) const {}
// void Piece::setColumn(bit<3u> const column) {}
// void Piece::setPosition(bit<3u> const column, bit<3u> const row) {}
// void Piece::setRow(bit<3u> const row) {}

/* Main */
int main(void) {}
