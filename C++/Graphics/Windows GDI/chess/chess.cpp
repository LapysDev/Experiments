/* ...
    --- WARN ---
    #Lapys: Requires a byte to be at least 8 bits.
*/

/* Import */
#include <cstdio> // C Standard Input/ Output
#include <cstdlib> // C Standard Library

/* Definition > ... */
struct Piece;

static void Initiate(void);
static void Update(void);
static void Terminate(void);

/* Class > Piece ->> May well just be a pointer, eh? */
struct Piece /* final */ {
    enum Color /* : bool */ { BLACK = 0u, WHITE = 1u };
    enum Type /* : unsigned char */ { BISHOP = 0u, KING = 1u, KNIGHT = 2u, PAWN = 3u, QUEEN = 4u, ROOK = 5u };

    private: unsigned char const *const data;
    public:
        Piece(unsigned char* const data) : data(const_cast<unsigned char const*>(data)) {}

        Color getColor(void) const;
        unsigned char getColumn(void) const;
        signed char getIndex(void) const;
        unsigned char getRow(void) const;
        Type getType(void) const;
};

/* Global */
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
    static unsigned char MEMORY[/* 275 / CHAR_BIT */ 35]; // ->> Encoded in terms of recency.

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

    // ...
    bool canRookCastle(Piece const, unsigned char const = 0u);

    static unsigned char* getMemorySegment(MemorySegment const);
    unsigned char getPawnEnPassantIndex(void);
    Type getPawnPromotionType(Piece const);
    static Piece getPiece(Piece::Color const, Piece::Type const, unsigned char const = 0u);
    Color getTurn(void);

    bool isPawnPromoted(Piece const, unsigned char const);
    bool isPieceCaptured(Piece const, unsigned char const = 0u);
}

/* Functions > ... */
bool Game::canRookCastle(Piece const rook, unsigned char const index) {
    unsigned char const castles = *Game::getMemorySegment(Game::CASTLE) >> 4u;

    if (0u != castles)
    switch (rook.getColor()) {
        case Piece::BLACK: return (castles == 0x1u || castles == 0x4u || castles == 0x7u || castles == 0xAu) || (
            0u == index
            ? castles == 0x2u || castles == 0x5u || castles == 0x8u || castles == 0xBu
            : castles == 0x3u || castles == 0x6u || castles == 0x9u || castles == 0xCu
        );

        case Piece::WHITE: return (castles == 0x4u || castles == 0x5u || castles == 0x6u || castles == 0xDu) || (
            0u == index
            ? castles == 0x7u || castles == 0x8u || castles == 0x9u || castles == 0xEu
            : castles == 0xAu || castles == 0xBu || castles == 0xCu || castles == 0xFu
        );
    }

    return false;
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

unsigned char Game::getPawnEnPassantIndex(void) { return *Game::getMemorySegment(Game::EN_PASSANT) & ~(~0u << 4u); }
Piece::Type Game::getPawnPromotionType(Piece const pawn) {
    switch (*pawn.data >> 6u) {
        case 0x0u: return Piece::BISHOP;
        case 0x1u: return Piece::KNIGHT;
        case 0x2u: return Piece::QUEEN;
        case 0x3u: return Piece::ROOK;
    }
}

Piece Game::getPiece(Piece::Color const color, Piece::Type const type, unsigned char const index) {
    switch (type) {
        case Piece::BISHOP: return Piece(Game::getMemorySegment(Game::BISHOPS) + (2L * (Piece::WHITE == color)) + index);
        case Piece::KING: return Piece(Game::getMemorySegment(Game::KINGS) - (0L + (1L << index)));
        case Piece::KNIGHT: return Piece(Game::getMemorySegment(Game::KNIGHTS) + (2L * (Piece::WHITE == color)) + index);
        case Piece::PAWN: return Piece(Game::getMemorySegment(Game::PAWNS) + (8L * (Piece::WHITE == color)) + index);
        case Piece::QUEEN: return Piece(Game::getMemorySegment(Game::QUEENS) - (2L + (1L << index)));
        case Piece::ROOK: return Piece(Game::getMemorySegment(Game::ROOKS) + (2L * (Piece::WHITE == color)) + index);
    }

    return Piece(NULL);
}

Piece::Color Game::getTurn(void) { return static_cast<Piece::Color>(*Game::getMemorySegment(Game::TURN) & 1u); }
bool Game::isPawnPromoted(Piece const pawn, unsigned char const index) { return (*Game::getMemorySegment(Game::PROMOTED_PAWNS) >> index) & 1u; }
bool Game::isPieceCaptured(Piece const piece, unsigned char const index) {
    if (Piece::PAWN == piece.getType()) return (*Game::getMemorySegment(Game::CAPTURED_PAWNS) >> index) & 1u;

    switch (piece.getType()) {
        case Piece::BISHOP: return ((*(Game::getMemorySegment(Game::CAPTURED_OFFICERS) + 0) >> 4u) >> index) & 1u;
        case Piece::KNIGHT: return ((*(Game::getMemorySegment(Game::CAPTURED_OFFICERS) + 0) >> 0u) >> index) & 1u;
        case Piece::QUEEN : return ((*(Game::getMemorySegment(Game::CAPTURED_OFFICERS) + 1) >> 2u) >> index) & 1u;
        case Piece::ROOK  : return ((*(Game::getMemorySegment(Game::CAPTURED_OFFICERS) + 1) >> 4u) >> index) & 1u;
    }

    return false;
}

// ...
Piece::Color Piece::getColor(void) const {
    unsigned char const *const data = this -> data;
    unsigned char iterator;

    for (Color color = Piece::BLACK; ; color = static_cast<Color>(static_cast<int>(color) + 1)) {
        for (iterator = 1u; iterator--; )
        if (
            data == Game::getPiece(color, Piece::KING, iterator).data ||
            data == Game::getPiece(color, Piece::QUEEN, iterator).data
        ) return color;

        for (iterator = 2u; iterator--; )
        if (
            data == Game::getPiece(color, Piece::BISHOP, iterator).data ||
            data == Game::getPiece(color, Piece::KNIGHT, iterator).data ||
            data == Game::getPiece(color, Piece::ROOK, iterator).data
        ) return color;

        for (iterator = 8u; iterator--; )
        if (
            data == Game::getPiece(color, Piece::PAWN, iterator).data
        ) return color;

        // ...
        if (Piece::WHITE == color) break;
    }

    return static_cast<Color>(0x0u);
}

unsigned char Piece::getColumn(void) const {
    Type const type = this -> getType();

    if (Piece::BISHOP == type) {
        unsigned char const position = *(this -> data) & ~(~0u << 5u);
        return (position % 8u) + ((position >> 3u) & 1u
            ? 0u == this -> getIndex() || 4u == this -> getIndex()
            : 1u == this -> getIndex() || 2u == this -> getIndex()
        );
    }

    if (Piece::KING == type || Piece::QUEEN == type) {
        return (
            ((*Game::getPiece(this -> getColor(), Piece::BISHOP, Piece::QUEEN == type).data >> 7u) << 2u) |
            ((*Game::getPiece(this -> getColor(), Piece::KNIGHT, Piece::QUEEN == type).data >> 6u) << 0u)
        );
    }

    return (*(this -> data) >> 3u) & ~(~0u << 3u);
}

signed char Piece::getIndex(void) const {
    unsigned char const *const data = this -> data;
    unsigned char iterator;

    for (Type type = Piece::BISHOP; ; type = static_cast<Color>(static_cast<int>(type) + 1)) {
        switch (type) {
            case Piece::BISHOP: case Piece::KNIGHT: case Piece::ROOK: iterator = 2u; break;
            case Piece::KING: case Piece::QUEEN: iterator = 1u; break;
            case Piece::PAWN: iterator = 8u; break;
        }

        while (iterator--)
        if (
            data == Game::getPiece(Piece::BLACK, type, iterator).data ||
            data == Game::getPiece(Piece::WHITE, type, iterator).data
        ) return iterator;

        // ...
        if (Piece::ROOK == type) break;
    }

    return -1;
}

unsigned char Piece::getRow(void) const {
    Type const type = this -> getType();

    if (Piece::BISHOP == type) {
        unsigned char const position = *(this -> data) & ~(~0u << 5u);
        return position >> 3u;
    }

    if (Piece::KING == type || Piece::QUEEN == type)
    return (
        ((*Game::getPiece(this -> getColor(), Piece::KNIGHT, Piece::QUEEN == type).data >> 7u) << 2u) |
        ((*Game::getPiece(this -> getColor(), Piece::ROOK  , Piece::QUEEN == type).data >> 6u) << 0u)
    );

    return (*(this -> data) >> 0u) & ~(~0u << 3u);
}

Piece::Type Piece::getType(void) const {
    unsigned char const *const data = this -> data;
    unsigned char iterator;

    for (Type type = Piece::BISHOP; ; type = static_cast<Color>(static_cast<int>(type) + 1)) {
        switch (type) {
            case Piece::BISHOP: case Piece::KNIGHT: case Piece::ROOK: iterator = 2u; break;
            case Piece::KING: case Piece::QUEEN: iterator = 1u; break;
            case Piece::PAWN: iterator = 8u; break;
        }

        while (iterator--)
        if (
            data == Game::getPiece(Piece::BLACK, type, iterator).data ||
            data == Game::getPiece(Piece::WHITE, type, iterator).data
        ) return type;

        // ...
        if (Piece::ROOK == type) break;
    }

    return static_cast<Type>(0x0u);
}

/* Phase */
/* : Initiate */
void Initiate(void) {}

/* : Update */
void Update(void) {}

/* : Terminate */
void Terminate(void) {}

/* Main */
int main(void) {
    Initiate();
    Update();
    Terminate();

    // ...
    return EXIT_SUCCESS;
}
