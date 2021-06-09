/* ...
    --- WARN ---
    #Lapys: Requires a byte to be at least 8 bits.
*/

/* Import */
#include <cstdio> // C Standard Input/ Output
#include <cstdlib> // C Standard Library

/* Definition > ... */
static void Initiate(void);
static void Update(void);
static void Terminate(void);

typedef struct Piece /* final */ {
    enum Color /* : bool */ { BLACK = 0u, WHITE = 1u };
    enum Type /* : unsigned char */ { BISHOP = 1u, KING = 2u, KNIGHT = 3u, PAWN = 4u, QUEEN = 5u, ROOK = 6u };

    private:
        unsigned char const *const data;
        unsigned char getPosition(void) const;

    public:
        Piece(unsigned char* const data) : data(const_cast<unsigned char const*>(data)) {}

        Color getColor(void) const;
        unsigned char getColumn(void) const;
        unsigned char const* getData(void) const;
        signed char getIndex(void) const;
        unsigned char getRow(void) const;
        Type getType(void) const;
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
    static void capturePiece(Piece const, Piece const);
    static void castleRook(Rook const);
    static void movePiece(Piece const, unsigned char const, unsigned char const);
    static void promotePawn(Piece const, Piece const);

    static bool isPawnPromoted(Pawn const);
    static bool isPieceCaptured(Piece const);
    static bool isRookCastled(Rook const);

    // ...
    static Pawn getEnPassantPawn(void);
    static unsigned char* getMemorySegment(MemorySegment const);
    static Piece::Type getPawnPromotion(Pawn const);
    static Piece getPiece(Piece::Color const, Piece::Type const, unsigned char const = 0u);
    static unsigned char getPieceCount(Piece::Type const);
    static Piece::Color getTurn(void);

    static void setEnPassantPawn(Pawn const);
    static void setTurn(Piece::Color const);
}

/* Functions > ... */
void Game::castleRook(Rook const rook) {
    *Game::getMemorySegment(Game::CASTLE) &= 0xFu | ((
        (*Game::getMemorySegment(Game::CASTLE) >> 4u) |
        (1u << (rook.getIndex() + ((Piece::WHITE == rook.getColor()) << 1u)))
    ) << 4u);
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

Piece::Color Game::getTurn(void) {
    return *Game::getMemorySegment(Game::TURN) & 1u ? Piece::WHITE : Piece::BLACK;
}

bool Game::isPawnPromoted(Pawn const pawn) {
    return (*Game::getMemorySegment(Game::PROMOTED_PAWNS) >> pawn.getIndex()) & 1u;
}

bool Game::isPieceCaptured(Piece const piece) {
    switch (piece.getType()) {
        case Piece::KING: return false;
        case Piece::PAWN: return (*Game::getMemorySegment(Game::CAPTURED_PAWNS) >> (piece.getIndex() + (Game::getPieceCount(Piece::PAWN) * (Piece::WHITE == piece.getColor())))) & 1u;

        case Piece::BISHOP: return ((*(Game::getMemorySegment(Game::CAPTURED_OFFICERS) + 0L) >> 4u) >> (piece.getIndex() + (Game::getPieceCount(Piece::BISHOP) * (Piece::WHITE == piece.getColor())))) & 1u;
        case Piece::KNIGHT: return ((*(Game::getMemorySegment(Game::CAPTURED_OFFICERS) + 0L) >> 0u) >> (piece.getIndex() + (Game::getPieceCount(Piece::KNIGHT) * (Piece::WHITE == piece.getColor())))) & 1u;
        case Piece::QUEEN : return ((*(Game::getMemorySegment(Game::CAPTURED_OFFICERS) + 1L) >> 2u) >> (piece.getIndex() + (Game::getPieceCount(Piece::QUEEN ) * (Piece::WHITE == piece.getColor())))) & 1u;
        case Piece::ROOK  : return ((*(Game::getMemorySegment(Game::CAPTURED_OFFICERS) + 1L) >> 4u) >> (piece.getIndex() + (Game::getPieceCount(Piece::ROOK  ) * (Piece::WHITE == piece.getColor())))) & 1u;
    }

    return false;
}

bool Game::isRookCastled(Rook const rook) {
    return ((*Game::getMemorySegment(Game::CASTLE) >> 4u) >> (rook.getIndex() + (Game::getPieceCount(Piece::ROOK) * (Piece::WHITE == rook.getColor())))) & 1u;
}

void Game::setEnPassantPawn(Pawn const pawn) {
    unsigned char *const data = Game::getMemorySegment(Game::EN_PASSANT);

    *data &= 0xF0u;
    *data |= pawn.getIndex() << (Piece::WHITE == pawn.getColor());
}

void Game::setTurn(Piece::Color const color) {
    if (Piece::BLACK == color) *Game::getMemorySegment(Game::TURN) &= 0xFEu;
    if (Piece::WHITE == color) *Game::getMemorySegment(Game::TURN) |= 0x01u;
}

// ...
Piece::Color Piece::getColor(void) const {
    unsigned char const *const data = this -> data;

    for (Type type = Piece::BISHOP; type <= Piece::ROOK; type = static_cast<Type>(static_cast<int>(type) + 1))
    for (unsigned char iterator = Game::getPieceCount(type); iterator--; ) {
        if (data == Game::getPiece(Piece::BLACK, type, iterator).getData()) return Piece::BLACK;
        if (data == Game::getPiece(Piece::WHITE, type, iterator).getData()) return Piece::WHITE;
    }

    return static_cast<Color>(0x0u);
}

unsigned char Piece::getColumn(void) const {
    if (Piece::BISHOP == this -> getType()) return (this -> getPosition() % 8u) + (this -> getRow() & 1u
        ? 0u == this -> getIndex() || 4u == this -> getIndex()
        : 1u == this -> getIndex() || 2u == this -> getIndex()
    );

    return this -> getPosition() >> 3u;
}

unsigned char const* Piece::getData(void) const {
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
        case Piece::BISHOP: return *(this -> data) & 0x1F;
        case Piece::KNIGHT: case Piece::PAWN: case Piece::ROOK: return *(this -> data) & 0x7F;
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
