/* ...
    --- WARN ---
    #Lapys: Requires a byte to be at least 8 bits.
*/

/* Import */
#include <climits> // C Limits
#include <csignal> // C Signal
#include <cstdio> // C Standard Input/ Output
#include <cstdlib> // C Standard Library

/* Namespace */
// : Color, Piece
namespace Color { enum Color /* : bool */ { BLACK = 0u, WHITE = 1u }; }
namespace Piece { enum Piece /* : unsigned char */ {
    KING = 0u,
      KING_BISHOP = 1u,
      KING_KNIGHT = 2u,
      KING_ROOK = 3u,
    PAWN = 4u,
    QUEEN = 5u,
      QUEEN_BISHOP = 6u,
      QUEEN_KNIGHT = 7u,
      QUEEN_ROOK = 8u
}; }

/* : Game ...
    --- UPDATE ---
    #Lapys: Could feasibly algorithmically compress the game to a single integer state i.e.: 35 to the 80th possible moves

    --- NOTE ---
    #Lapys: Memory model (with an unimplemented custom 32-turn draw)

     no.                index            flag                             bit
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
    namespace MemorySegment { enum MemorySegment /* : unsigned char */ {
        CAPTURED_BLACK_PAWNS = 0x00u,
        CAPTURED_PIECES = 0x01u,
        CAPTURED_WHITE_PAWNS = 0x02u,
        CASTLE_STATE = 0x03u,
        EN_PASSANT = 0x04u,
        PROMOTED_BLACK_PAWNS = 0x05u,
        PROMOTED_WHITE_PAWNS = 0x06u,
        TURN = 0x07u,

        BLACK_KING = 0x08u,
        BLACK_KING_BISHOP = 0x09u,
        BLACK_KING_KNIGHT = 0x0Au,
        BLACK_KING_ROOK = 0x0Bu,
        BLACK_PAWNS = 0x0Cu,
        BLACK_QUEEN = 0x0Du,
        BLACK_QUEEN_BISHOP = 0x0Eu,
        BLACK_QUEEN_KNIGHT = 0x0Fu,
        BLACK_QUEEN_ROOK = 0x10u,
        WHITE_KING = 0x11u,
        WHITE_KING_BISHOP = 0x12u,
        WHITE_KING_KNIGHT = 0x13u,
        WHITE_KING_ROOK = 0x14u,
        WHITE_PAWNS = 0x15u,
        WHITE_QUEEN = 0x16u,
        WHITE_QUEEN_BISHOP = 0x17u,
        WHITE_QUEEN_KNIGHT = 0x18u,
        WHITE_QUEEN_ROOK = 0x19u
    }; }

    unsigned char MEMORY[35];

    // : Capture
    void capturePiece(Color::Color const, Piece::Piece const);
    bool pieceIsCaptured(Color::Color const, Piece::Piece const);

    // : Castle
    bool canCastleKingSide(Color::Color const);
    bool canCastleQueenSide(Color::Color const);

    void castleKingSide(Color::Color const);
    void castleQueenSide(Color::Color const);

    // : En-Passant
    unsigned char getEnPassantPawnIndex(void);

    // : Turn
    Color::Color getTurn(void);
    void setTurn(Color::Color const);

    // : ...
    void clearMemory(void);
    unsigned char getMemorySegment(MemorySegment::MemorySegment const);
    unsigned char getMemorySegment(Color::Color const, Piece::Piece const);

    MemorySegment::MemorySegment mapToMemorySegment(Color::Color const, Piece::Piece const);

    void setMemorySegment(MemorySegment::MemorySegment const, unsigned char const);
    void setMemorySegment(Color::Color const, Piece::Piece const, unsigned char const);
    void reset(void);
}

/* Global > ... */
/* Functions */
// : Game
    /* Castle --- NOTE (Lapys) ->
        0 ---               ---
        1 ---               WHITE
        2 ---               WHITE KING_SIDE
        3 ---               WHITE QUEEN_SIDE

        4 BLACK             ---
        5 BLACK             WHITE
        6 BLACK             WHITE KING_SIDE
        7 BLACK             WHITE QUEEN_SIDE

        8 BLACK KING_SIDE   ---
        9 BLACK KING_SIDE   WHITE
        A BLACK KING_SIDE   WHITE KING_SIDE
        B BLACK KING_SIDE   WHITE QUEEN_SIDE

        C BLACK QUEEN_SIDE  ---
        D BLACK QUEEN_SIDE  WHITE
        E BLACK QUEEN_SIDE  WHITE KING_SIDE
        F BLACK QUEEN_SIDE  WHITE QUEEN_SIDE
    */
    bool Game::canCastleKingSide(Color::Color const color) {
        unsigned char const state = Game::getMemorySegment(MemorySegment::CASTLE) >> (CHAR_BIT - 4u);

        if (Color::BLACK == color) return state == 0x4u || state == 0x5u || state == 0x6u || state == 0x7u || state == 0x8u || state == 0x9u || state == 0xAu || state == 0xBu;
        if (Color::WHITE == color) return state == 0x1u || state == 0x2u || state == 0x5u || state == 0x6u || state == 0x9u || state == 0xAu || state == 0xDu || state == 0xEu;
        return false;
    }

    bool Game::canCastleQueenSide(Color::Color const color) {
        unsigned char const state = Game::getMemorySegment(MemorySegment::CASTLE) >> (CHAR_BIT - 4u);

        if (Color::BLACK == color) return state == 0x4u || state == 0x5u || state == 0x6u || state == 0x7u || state == 0xCu || state == 0xDu || state == 0xEu || state == 0xFu;
        if (Color::WHITE == color) return state == 0x1u || state == 0x3u || state == 0x5u || state == 0x7u || state == 0x9u || state == 0xBu || state == 0xDu || state == 0xFu;
        return false;
    }

    void Game::castleKingSide(Color::Color const color) {
        if (Color::BLACK == color)
    }
    void Game::castleQueenSide(Color::Color const);

    // ...
    void Game::clearMemory(void) { for (unsigned char *iterator = Game::MEMORY + (sizeof(Game::MEMORY) / sizeof(unsigned char)); Game::MEMORY != iterator--; ) *iterator = 0u; }

    unsigned char Game::getMemorySegment(Color::Color const color, Piece::Piece const piece) { return Game::getMemorySegment(Game::mapToMemorySegment(color, piece)); }
    unsigned char Game::getMemorySegment(MemorySegment::MemorySegment const segment) {
        Game::MEMORY[35]
        switch (segment) {
            case MemorySegment::CAPTURED_BLACK_PAWNS: return Game::MEMORY[0];
            case MemorySegment::CAPTURED_PIECES: return Game::MEMORY[1] | ;
            case MemorySegment::CAPTURED_WHITE_PAWNS: return ...;
            case MemorySegment::CASTLE_STATE: return ...;
            case MemorySegment::EN_PASSANT: return ...;
            case MemorySegment::PROMOTED_BLACK_PAWNS: return ...;
            case MemorySegment::PROMOTED_WHITE_PAWNS: return ...;
            case MemorySegment::TURN: return ...;

            case MemorySegment::BLACK_KING: return ...;
            case MemorySegment::BLACK_KING_BISHOP: return ...;
            case MemorySegment::BLACK_KING_KNIGHT: return ...;
            case MemorySegment::BLACK_KING_ROOK: return ...;
            case MemorySegment::BLACK_PAWNS: return ...;
            case MemorySegment::BLACK_QUEEN: return ...;
            case MemorySegment::BLACK_QUEEN_BISHOP: return ...;
            case MemorySegment::BLACK_QUEEN_KNIGHT: return ...;
            case MemorySegment::BLACK_QUEEN_ROOK: return ...;
            case MemorySegment::WHITE_KING: return ...;
            case MemorySegment::WHITE_KING_BISHOP: return ...;
            case MemorySegment::WHITE_KING_KNIGHT: return ...;
            case MemorySegment::WHITE_KING_ROOK: return ...;
            case MemorySegment::WHITE_PAWNS: return ...;
            case MemorySegment::WHITE_QUEEN: return ...;
            case MemorySegment::WHITE_QUEEN_BISHOP: return ...;
            case MemorySegment::WHITE_QUEEN_KNIGHT: return ...;
            case MemorySegment::WHITE_QUEEN_ROOK: return ...;
        }

        std::raise(SIGSEGV);
        return 0x0u;
    }

    MemorySegment::MemorySegment Game::mapToMemorySegment(Color::Color const color, Piece::Piece const piece) {
        return static_cast<MemorySegment::MemorySegment>(
            // ->> Memory region for pieces.
            static_cast<unsigned char>(MemorySegment::BLACK_KING) +

            // ->> Shift between regions for black/ white pieces.
            (9u * static_cast<unsigned char>(color)) +

            // ->> Offset from region based on specified piece.
            static_cast<unsigned char>(piece)
        );
    }

    void Game::reset(void) {}

    void Game::setMemorySegment(Color::Color const, Piece::Piece const, unsigned char const, value) { Game::setMemorySegment(Game::mapToMemorySegment(color, piece), value); }
    void Game::setMemorySegment(MemorySegment::MemorySegment const, unsigned char const) {}

/* Phase */
// : Initiate
void Initiate(void) {
    Game::reset();
    Game::setTurn(Color::WHITE);
}

// : Reset
void Reset(void) { Initiate(); }

// : Update
// : Terminate

/* Main */
int main(void) {
    // Return
    return EXIT_SUCCESS;
}
