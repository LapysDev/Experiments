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
        Color         getColor   (void) const;
        bit<3u>       getColumn  (void) const;
        bit<3u>       getIndex   (void) const;
        bit<6u>       getPosition(void) const;
        bit<3u>       getRow     (void) const;
        Type          getType    (void) const;

        void          setColumn  (bit<3u> const);
        void          setPosition(bit<3u> const, bit<3u> const);
        void          setRow     (bit<3u> const);
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

    // ... ->> Getter
    static Pawn        getEnPassantPawn    (void);
    static Piece       getPiece            (Color const, Piece::Type const, bit<3u> const = 0u);
    static Piece::Type getPawnPromotionType(Pawn const);
};

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

/* Main */
int main(void) {}
