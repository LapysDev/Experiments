/* Import */
#include <conio.h> // Console Input-Output
#include <cstdio> // C Standard Input-Output
#include <cstdlib> // C Standard Library
#include <unistd.h> // Unix Standard
#include <windows.h> // Windows

/* Definition > ... */
int Reset(); int Initiate(bool); int Update(); int Terminate();

/* Function */
    // Character String
        // Length
        inline const unsigned characterStringLength(char* characterString) { if (NULL == characterString) return 0; else { unsigned length = 0; while (*(characterString + length) ^ '\0') length += 1; return length; } }
        const unsigned characterStringLength(const char* characterString) { return ::characterStringLength((char*) characterString); }

        // Is
        const bool characterStringIs(char* characterStringA, char* characterStringB) {
            // Initialization > Character String (A, B) Length
            const unsigned characterStringALength = ::characterStringLength(characterStringA),
                characterStringBLength = ::characterStringLength(characterStringB);

            // Logic
            if (characterStringALength == characterStringBLength) {
                // Initialization > Iterator
                unsigned iterator = characterStringALength;

                // Loop
                while (iterator) {
                    // Update > Iterator
                    iterator -= 1;

                    // Logic > Return
                    if (*(characterStringA + iterator) ^ *(characterStringB + iterator)) return false;
                }

                // Return
                return true;
            }

            else
                // Return
                return false;
        }
        const bool characterStringIs(char* characterStringA, const char* characterStringB) { return ::characterStringIs(characterStringA, (char*) characterStringB); }
        const bool characterStringIs(const char* characterStringA, char* characterStringB) { return ::characterStringIs((char*) characterStringA, characterStringB); }
        const bool characterStringIs(const char* characterStringA, const char* characterStringB) { return ::characterStringIs((char*) characterStringA, (char*) characterStringB); }

    // Number > (Is Negative, Minimum)
    const bool numberIsNegative(long double arg) { return arg < 0; }
    unsigned numberMin(unsigned numberA, unsigned numberB) { return numberA > numberB ? numberB : numberB; }

    // Print
    void print() { std::fflush(stdout); }
    void print(const bool arg) { arg ? ::write(STDOUT_FILENO, "true", 4) : ::write(STDOUT_FILENO, "false", 5); }
    void print(const char arg) { char characterString[1] {arg}; ::write(STDOUT_FILENO, characterString, 1); }
    void print(char* arg) { ::write(STDOUT_FILENO, arg, ::characterStringLength(arg)); }
    void print(const char* arg) { ::print((char*) arg); }
    void print(unsigned long long arg) { std::printf("%u", arg); }
    void print(long long arg) { if (::numberIsNegative(arg)) ::write(STDOUT_FILENO, "-", 1);  ::print(arg); }
    void print(long arg) { ::print((long long) arg); }
    void print(short arg) { ::print((long long) arg); }
    void print(signed int arg) { ::print((unsigned long long) arg); }
    void print(unsigned int arg) { ::print((unsigned long long) arg); }
    void print(unsigned long arg) { ::print((unsigned long long) arg); }
    void print(unsigned short arg) { ::print((unsigned long long) arg); }
    template <typename type, typename... types> void print(type arg, types... args) { ::print(arg); ::print(args...); }
        // Character
        void printc(const char arg) { ::print(arg); }
        inline void printc(char* arg) { ::write(STDOUT_FILENO, arg, 1); }
        inline void printc(const char* arg) { ::print((char*) arg); }

        // Newline
        void printn(bool FLUSH_BUFFER = true) { ::write(STDOUT_FILENO, "\n", 1); if (FLUSH_BUFFER) std::fflush(stdout); }
        template <typename... types> void printn(types... args) { ::print(args...); ::printn(false); }

        // Long-Line
        void printl(unsigned length = 30, const char* pattern = "=") { while (length) { length -= 1; ::write(STDOUT_FILENO, pattern, 1); } }

        // Long-Line and Newline
        template <typename... types> void println(types... args) { ::printl(args...); ::printn(false); }

        // Tab
        void printt(unsigned length = 4) { while (length) { length -= 1; ::write(STDOUT_FILENO, " ", 1); } }

        // Tab and Newline
        template <typename... types> void printtn(types... args) { ::printt(args...); ::printn(false); }

    // Random
    const unsigned random() { return std::rand(); }
    const unsigned long long randomRange(long double range) { return std::rand() % (unsigned long long) range; }

    // To Character String
    char* toCharacterString(const char arg) { bool isNullTerminationCharacter = arg == '\0'; char* characterString = (char*) std::malloc(1 + isNullTerminationCharacter); *characterString = arg; isNullTerminationCharacter && (*(characterString + 1) = '\0'); return characterString; }

/* Global > Game */
namespace Game {
    // Namespace
        // Settings
        inline namespace Settings { bool phaseThroughWalls = true, viewStatistics = true; }

        // State
        inline namespace State { bool gameover = false, paused = false; }

        // Data
        inline namespace Data {
            /* Class > Coordinates */
            struct Coordinates {
                // [Public]
                public:
                    // [Constructor]
                    Coordinates() {}
                    Coordinates(signed x, signed y) { this -> initiate(x, y); }

                    // Initialization > (X, Y)
                    signed x = 0, y = 0;

                    // Phase > Initiate
                    void initiate(signed x, signed y) { this -> set(x, y); }

                    // Function
                        // Matches
                        bool matches(signed x, signed y) const { return this -> x == x && this -> y == y; }
                        bool matches(const Coordinates& coordinates) const { return this -> x == coordinates.x && this -> y == coordinates.y; }

                        // Set (Random) [Coordinates]
                        inline void set(signed x, signed y) { this -> x = x; this -> y = y; }
                        inline void set(const Coordinates& coordinates) { this -> x = coordinates.x; this -> y = coordinates.y; }
                        inline void setRandom(signed xRange = 1, signed yRange = 1) { this -> x = ::randomRange(xRange); this -> y = ::randomRange(yRange); }
            };

            // Initialization
                // Direction
                enum Direction {East, North, South, West, null};

                // (Former) Input Key
                int FORMER_INPUT_KEY = -1, INPUT_KEY = -1;

                // Game (Height, Width)
                unsigned GAME_HEIGHT = ::randomRange(22),
                    GAME_WIDTH = ::randomRange(23) + unsigned(GAME_HEIGHT / 2);

                // Frame
                char* FRAME = (char*) std::malloc((GAME_HEIGHT + 2) * (GAME_WIDTH + 2));

                // Input String
                char* INPUT_STRING = NULL;

            /* Class */
                // Bush
                class Bush {
                    // [Public]
                    public:
                        // Initialization > Coordinates
                        Coordinates coordinates;

                        // Function > Draw
                        inline void draw() {
                            // Initialization > Index
                            unsigned index = this -> coordinates.x + (this -> coordinates.y * (GAME_WIDTH + 1));

                            // Update > (Data > Frame)
                            (
                                *(Data::FRAME + index) ^ '_' &&
                                *(Data::FRAME + index) ^ '|' &&
                                *(Data::FRAME + index) ^ '-'
                            ) && (*(Data::FRAME + index) = ',');
                        }
                };

                // Snake
                class Snake;

                // Food
                class Food {
                    // [Public]
                    public:
                        // [Constructor]
                        Food() { this -> initiate(); }

                        // Initialization > (Coordinates, Type)
                        Coordinates coordinates; enum {bonus, fruit, poison} type;

                        // Phase > Initiate
                        void initiate() { this -> respawn(); }

                        // Function
                            // Draw
                            void draw() {
                                // Initialization > Character Sprite
                                char characterSprite;

                                // Logic > Update > Character Sprite
                                switch (this -> type) {
                                    case this -> bonus: characterSprite = 'B'; break;
                                    case this -> poison: characterSprite = 'P'; break;
                                    default: characterSprite = 'F';
                                }

                                // Update > (Data > Frame)
                                *(Data::FRAME + (this -> coordinates.x + (this -> coordinates.y * (GAME_WIDTH + 1)))) = characterSprite;
                            }

                            // On Eaten
                            void oneaten(Snake&);

                            // Respawn
                            void respawn() { this -> coordinates.setRandom(GAME_WIDTH, GAME_HEIGHT); }

                            // To (Bonus, Fruit, Poison)
                            void toBonus() { (this -> type ^ this -> bonus) && (this -> type = this -> bonus); }
                            void toFruit() { (this -> type ^ this -> fruit) && (this -> type = this -> fruit); }
                            void toPoison() { (this -> type ^ this -> poison) && (this -> type = this -> poison); }
                };

                // Snake
                class Snake {
                    // [Public]
                    public:
                        // [Constructor]
                        Snake() { this -> tail.snake = this; }

                        // Initialization
                            // Cause of Death
                            char* causeOfDeath = NULL;

                            // Can Phase Through Wall, Is Dead
                            bool canPhaseThroughWall, isDead = false;

                            // Character Sprites
                            struct SnakeCharacterSprites { public: char body = 's', head = 'S', hidden = '*', pattern = '.', tail = '`'; } characterSprites;

                            // Coordinates, Direction
                            Coordinates coordinates; Direction direction = null;

                            // Score (Increment)
                            unsigned score = 0, scoreIncrement = 5, scoreIncrementBonus = 1;

                            // Tail
                            struct SnakeTail {
                                // [Public]
                                public:
                                    // Initialization > (Coordinates, Length, Snake)
                                    Coordinates coordinates[150]; unsigned length = 0; Snake* snake = NULL;

                                    // Function
                                        // Draw
                                        void draw() {
                                            // Loop
                                            for (unsigned iterator = 0; iterator ^ length; iterator += 1) {
                                                // Initialization > Index
                                                char characterSprite = snake -> characterSprites.tail;
                                                unsigned index = (*(this -> coordinates + iterator)).x + ((*(this -> coordinates + iterator)).y * (GAME_WIDTH + 1));

                                                // Logic > Update > Character Sprite
                                                if (!(iterator % 5)) characterSprite = snake -> characterSprites.pattern;
                                                else if (iterator) characterSprite = snake -> characterSprites.body;

                                                // Update > (Data > Frame)
                                                (*(Data::FRAME + index) ^ '\n') &&
                                                (*(Data::FRAME + index) = snake -> isDead ?
                                                    'x' :
                                                    ((*(Data::FRAME + index) ^ '_' && *(Data::FRAME + index) ^ '|' && *(Data::FRAME + index) ^ '-') ?
                                                        characterSprite :
                                                        snake -> characterSprites.hidden)
                                                );
                                            }
                                        }

                                        // Extend
                                        inline void extend() { this -> length += 1; }

                                        // Retract
                                        inline void retract() { (this -> length - 1) && (this -> length -= 1); }
                            } tail;

                        // Phase > Reset
                        void reset() {
                            // Modification > Target
                                // Cause Of Death
                                this -> causeOfDeath = NULL;

                                // Is Dead
                                this -> isDead = false;

                                // Direction
                                this -> direction = Data::Direction::null;

                                // Score (Increment (Bonus))
                                this -> score = 0; this -> scoreIncrement = 5; this -> scoreIncrementBonus /= 2;
                                this -> tail.length = 0;

                            // Target > Spawn
                            this -> spawn();
                        }

                        // Function
                            // Die, Move
                            void die(); void die(const char*);
                            void move(); void move(bool);

                            // Draw
                            void draw() {
                                // Initialization > Index
                                unsigned index = this -> coordinates.x + (this -> coordinates.y * (GAME_WIDTH + 1));

                                // Update > (Data > Frame)
                                (*(Data::FRAME + index) ^ '\n') &&
                                (*(Data::FRAME + index) = this -> isDead ?
                                    'X' :
                                    ((*(Data::FRAME + index) ^ '_' && *(Data::FRAME + index) ^ '|' && *(Data::FRAME + index) ^ '-') ?
                                        this -> characterSprites.head :
                                        this -> characterSprites.hidden)
                                );

                                // (Target > Tail) > Draw
                                this -> tail.draw();
                            }

                            // Eat
                            void eat(Food& food) {
                                // Modification > Player > Score
                                this -> score += ::randomRange(this -> scoreIncrement) + 1;

                                // Food > On Eaten
                                food.oneaten(*this);
                            }

                            // Set Direction
                            void setDirection(Direction direction) {
                                // Initialization > Has Tails
                                const bool hasTails = this -> tail.length;

                                // Logic > Modification > Target > Direction
                                if (!(
                                    hasTails && (
                                        (this -> direction == Data::East && direction == Data::West) ||
                                        (this -> direction == Data::North && direction == Data::South) ||
                                        (this -> direction == Data::South && direction == Data::North) ||
                                        (this -> direction == Data::West && direction == Data::East)
                                    )
                                )) this -> direction = direction;
                            }

                            // Spawn
                            void spawn() { this -> coordinates.set(GAME_WIDTH / 2, GAME_HEIGHT / 2); }

                            // Stop
                            void stop() { this -> direction = Direction::null; }
                };
        }
            // Utilization
            using Data::GAME_HEIGHT;
            using Data::GAME_WIDTH;

            // Initialization
                // (Number Of) Bushes
                const unsigned NUMBER_OF_BUSHES = 15;
                Data::Bush BUSHES[NUMBER_OF_BUSHES];

                // (Number Of) Foods
                unsigned NUMBER_OF_FOODS = 1;
                Data::Food FOODS[100];

                // Player
                Data::Snake PLAYER;

        // Actions
        inline namespace Actions {
            // Function
                // Request Input
                const char* requestInput() {
                    // Modification > Data > (Former) Input Key
                    Data::FORMER_INPUT_KEY = Data::INPUT_KEY;
                    Data::INPUT_KEY = ::_getch();

                    // Logic > Deletion
                    if (~Data::FORMER_INPUT_KEY) std::free(Data::INPUT_STRING);

                    // Logic
                    if (Data::FORMER_INPUT_KEY == 224)
                        // Logic > Modification > Player > Direction
                        switch (Data::INPUT_KEY) { case 80: return "ArrowDown"; case 75: return "ArrowLeft"; case 77: return "ArrowRight"; case 72: return "ArrowUp"; }

                    // Return
                    return Data::INPUT_STRING = ::toCharacterString(Data::INPUT_KEY);
                }

                // Draw On Frame By Index
                void drawOnFrameByIndex(const char character, unsigned& index) { *(Data::FRAME + index) = character; index += 1; }

                // Render Controls Menu --- MINIFY
                void renderControlsMenu() { ::printn("\n\nCONTROLS\n========================================\nMove/ Strafe:\n    Down: 'Key S' or 'Down Arrow'\n    Left: 'Key A' or 'Left Arrow'\n    Right: 'Key D' or 'Right Arrow'\n    Up: 'Key W' or 'Up Arrow'\nDie: 'Key X'\nPause: 'Key P'\nSolid Walls: 'Key N'\nToggle Phasing: 'Key T'\n"); ::print(); }

                // Render Frame
                void renderFrame() { ::printn(FRAME); }

                // Render Game Over Menu
                void renderGameOverMenu() {
                    // [Head] Print
                    ::printn("\n\n", "GAME OVER");
                    ::println(40);

                    // [Body] Print
                    ::printn("Cause of Death: ", PLAYER.causeOfDeath);
                    ::print("Continue Game [Y / N]: ");
                        // Initialization > Input
                        const char* input = Actions::requestInput();

                        // Loop > Update > Input
                        while ((*input ^ 'n' && *input ^ 'N') && (*input ^ 'y' && *input ^ 'Y')) input = Actions::requestInput();

                        // Logic > (Reset; Print)
                        if (*input == 'y' || *input == 'Y') Reset();
                        else ::printc("N");
                }

                // Render Statistics
                void renderStatistics() {
                    // [Head] Print
                    ::printn("\n\n", "STATISTICS");
                    ::println(40);

                    // [Body] Print
                    ::printn("Coordinates: [x: ", PLAYER.coordinates.x, ", y: ", PLAYER.coordinates.y, ']');
                    ::printn("Dimensions: [H: ", GAME_HEIGHT, ", W: ", GAME_WIDTH, ']');
                    ::print("Direction: ");
                        switch (PLAYER.direction) {
                            case Data::Direction::East: ::print("East"); break;
                            case Data::Direction::North: ::print("North"); break;
                            case Data::Direction::South: ::print("South"); break;
                            case Data::Direction::West: ::print("West");
                        }
                    ::printn();
                    ::printn("Phase Through Walls: ", Settings::phaseThroughWalls);
                    ::printn("Score: ", PLAYER.score);
                    ::printn("Tail Length: ", PLAYER.tail.length);
                    ::print();
                }

                // Draw Frame
                void drawFrame() {
                    // Initialization > Index
                    unsigned index = 0;

                    // [Ceiling] Loop > Actions > Draw On Frame By Index
                    for (unsigned iterator = GAME_WIDTH; iterator; iterator -= 1)
                        Actions::drawOnFrameByIndex('_', index);

                    // Actions > Draw On Frame By Index
                    Actions::drawOnFrameByIndex('\n', index);

                    // Loop
                    for (unsigned rowiterator = GAME_HEIGHT; rowiterator; rowiterator -= 1) {
                        // Loop
                        for (unsigned columniterator = 0; columniterator ^ GAME_WIDTH; columniterator += 1)
                            // [Wall | Empty Field] Actions > Draw On Frame By Index
                            Actions::drawOnFrameByIndex(!columniterator || columniterator == GAME_WIDTH - 1 ? '|' : ' ', index);

                        // Actions > Draw On Frame By Index
                        Actions::drawOnFrameByIndex('\n', index);
                    }

                    // [Floor] Loop > Actions > Draw On Frame By Index
                    for (unsigned iterator = GAME_WIDTH; iterator; iterator -= 1)
                        Actions::drawOnFrameByIndex('-', index);

                    // Loop > ([Bush], [Food]) > Draw
                    for (unsigned iterator = 0; iterator ^ NUMBER_OF_BUSHES; iterator += 1) (*(BUSHES + iterator)).draw();
                    for (unsigned iterator = 0; iterator ^ NUMBER_OF_FOODS; iterator += 1) (*(FOODS + iterator)).draw();

                    // Player > Draw
                    PLAYER.draw();

                    // System
                    ::system("cls");

                    // Actions > Render (Controls, Frame, Statistics)
                    Actions::renderFrame();
                    Actions::renderControlsMenu();
                    if (Settings::viewStatistics) Actions::renderStatistics();
                }

                // Has Received Input
                const bool hasRecievedInput() { return ::_kbhit(); }

                // Pause
                inline void pause() { State::paused = !State::paused; }
        }

        // Data
        inline namespace Data {
            /* Modification */
                /* Food */
                    // On Eaten
                    void Food::oneaten(Snake& snake) {
                        // Initialization > Is Valid Spawn Coordinates
                        bool isValidSpawnCoordinates = true;

                        // Loop
                        do {
                            // Target > Respawn
                            this -> respawn();

                            // (Loop >)Update > Is Valid Spawn Coordinates
                            isValidSpawnCoordinates = true;
                            snake.coordinates.matches(this -> coordinates) && (isValidSpawnCoordinates = false);
                            for (unsigned iterator = snake.tail.length; isValidSpawnCoordinates && iterator; iterator -= 1)
                                snake.tail.coordinates[iterator].matches(this -> coordinates) && (isValidSpawnCoordinates = false);
                        } while (!isValidSpawnCoordinates);

                        // Logic > ...
                        switch (this -> type) {
                            case Data::Food::bonus: snake.tail.retract(); break;
                            case Data::Food::fruit: snake.tail.extend(); break;
                            case Data::Food::poison: snake.die("Eaten Poison");
                        }
                    }

                /* Snake */
                    // Die
                    void Snake::die() { this -> die((char*) "Program Request"); }
                    void Snake::die(const char* cause) { this -> causeOfDeath = (char*) cause; this -> isDead = true; }

                    // Move
                    void Snake::move() { this -> move(true); }
                    void Snake::move(bool UPDATE_COORDINATES) {
                        // Logic
                        if (!(this -> isDead)) {
                            // Logic
                            if (UPDATE_COORDINATES) {
                                // Initialization > Coordinates
                                Coordinates formerCoordinates(this -> tail.coordinates[0].x, this -> tail.coordinates[0].y);

                                // Modification > (Target > Tail) > (X, Y)
                                this -> tail.coordinates[0].x = this -> coordinates.x;
                                this -> tail.coordinates[0].y = this -> coordinates.y;

                                // Loop
                                for (unsigned iterator = 0; iterator < this -> tail.length; iterator += 1) {
                                    // Initialization > Temporary Coordinates
                                    Coordinates temporaryCoordinates(this -> tail.coordinates[iterator].x, this -> tail.coordinates[iterator].y);

                                    // Modification
                                        // (Target > Tail) > (X, Y)
                                        this -> tail.coordinates[iterator].x = formerCoordinates.x;
                                        this -> tail.coordinates[iterator].y = formerCoordinates.y;

                                        // Former Coordinates > (X, Y)
                                        formerCoordinates.x = temporaryCoordinates.x;
                                        formerCoordinates.y = temporaryCoordinates.y;
                                }

                                // Logic > Modification > (Target > Coordinates) > (X, Y)
                                switch (this -> direction) {
                                    case Data::Direction::East: (this -> coordinates.x == GAME_WIDTH) || (this -> coordinates.x += 1); break;
                                    case Data::Direction::North: this -> coordinates.y && (this -> coordinates.y -= 1); break;
                                    case Data::Direction::South: (this -> coordinates.y == GAME_HEIGHT) || (this -> coordinates.y += 1); break;
                                    case Data::Direction::West: this -> coordinates.x && (this -> coordinates.x -= 1);
                                }

                                // Loop
                                for (unsigned iterator = 0; iterator ^ NUMBER_OF_FOODS; iterator += 1) {
                                    // Logic
                                    if (this -> coordinates.matches(FOODS[iterator].coordinates)) {
                                        // Target > Eat
                                        this -> eat(FOODS[iterator]);

                                        // Logic
                                        if (::randomRange(1e3) == 1) {
                                            // Initialization > Food
                                            Food food = (*(FOODS + (NUMBER_OF_FOODS - 1)));

                                            // Update > Number Of Foods
                                            NUMBER_OF_FOODS += 1;

                                            // Food > Respawn
                                            food.respawn();

                                            // Logic > Food > To Poison
                                            if (::randomRange(10) == 1) food.toPoison();
                                            else if (::randomRange(100) == 1) food.toBonus();
                                            else food.toFruit();
                                        }
                                    }
                                }
                            }

                            // Logic
                            if (!(this -> canPhaseThroughWall))
                                // Loop
                                for (unsigned iterator = this -> tail.length; iterator; iterator -= 1)
                                    // Logic > (Target > Die)
                                    if (this -> coordinates.matches(this -> tail.coordinates[iterator]))
                                        this -> die("Eaten Tail");

                            // Logic
                            if (Settings::phaseThroughWalls) {
                                // Initialization > Snake Is On Wall
                                bool snakeIsOnWall = false;

                                // Logic
                                if (this -> coordinates.x == GAME_WIDTH) {
                                    // Update > Snake Is On Wall
                                    snakeIsOnWall = true;

                                    // Logic
                                    if (this -> canPhaseThroughWall && this -> direction == Data::Direction::East) {
                                        // Modification > Target > (Can Phase Through Wall, Coordinates > X)
                                        this -> canPhaseThroughWall = false;
                                        this -> coordinates.x = 0;

                                        // Target > Move
                                        this -> move(false);
                                    }
                                }

                                else if (!(this -> coordinates.x)) {
                                    // Update > Snake Is On Wall
                                    snakeIsOnWall = true;

                                    // Logic
                                    if (this -> canPhaseThroughWall && this -> direction == Data::Direction::West) {
                                        // Modification > Target > (Can Phase Through Wall, Coordinates > X)
                                        this -> canPhaseThroughWall = false;
                                        this -> coordinates.x = GAME_WIDTH - 1;

                                        // Target > Move
                                        this -> move(false);
                                    }
                                }

                                if (this -> coordinates.y == GAME_HEIGHT) {
                                    // Update > Snake Is On Wall
                                    snakeIsOnWall = true;

                                    // Logic
                                    if (this -> canPhaseThroughWall && this -> direction == Data::Direction::South) {
                                        // Modification > Target > (Can Phase Through Wall, Coordinates > Y)
                                        this -> canPhaseThroughWall = false;
                                        this -> coordinates.y = 0;

                                        // Target > Move
                                        this -> move(false);
                                    }
                                }

                                else if (!(this -> coordinates.y)) {
                                    // Update > Snake Is On Wall
                                    snakeIsOnWall = true;

                                    // Logic
                                    if (this -> canPhaseThroughWall && this -> direction == Data::Direction::North) {
                                        // Modification > Target > (Can Phase Through Wall, Coordinates > Y)
                                        this -> canPhaseThroughWall = false;
                                        this -> coordinates.y = GAME_HEIGHT - 1;

                                        // Target > Move
                                        this -> move(false);
                                    }
                                }

                                // Modification > Target > Can Phase Through Wall
                                this -> canPhaseThroughWall = snakeIsOnWall;
                            }

                            else if (
                                (!(this -> coordinates.x) || this -> coordinates.x == GAME_WIDTH - 1) ||
                                (!(this -> coordinates.y) || this -> coordinates.y == GAME_HEIGHT)
                            )
                                // Target > Die
                                this -> die("Crashed on Wall");
                        }
                    }
        }
}

// Utilization > ...
using namespace Game;

/* Phase */
    // Initiate
    int Initiate(bool RESPONSIVE_DRAW = true) {
        // System
        ::system("cls && color 1F && title Snake Game [Loading]");

        // Player > Reset
        PLAYER.reset();

        // Modification > State > Game Over
        State::gameover = false;

        // Logic
        if (RESPONSIVE_DRAW && Settings::viewStatistics) {
            // Initialization > Statistics Display Height
            const unsigned statisicsDisplayHeight = 6;

            // Update > Game (Height, Width)
            GAME_HEIGHT = ::numberIsNegative(signed(GAME_HEIGHT) - (statisicsDisplayHeight + 4)) ? GAME_HEIGHT : GAME_HEIGHT - statisicsDisplayHeight;
            GAME_WIDTH = ::numberIsNegative(signed(GAME_WIDTH) - ((statisicsDisplayHeight / 2) + 4)) ? GAME_WIDTH : GAME_WIDTH - (statisicsDisplayHeight / 2);
        }

        // [Food] > (To Fruit, Respawn); Player > Spawn
        (*FOODS).toFruit(); (*FOODS).respawn();
        PLAYER.spawn();

        // Loop > [Bush] > Coordinates > Set Random
        for (unsigned iterator = 0; iterator ^ NUMBER_OF_BUSHES; iterator += 1)
            (*(BUSHES + iterator)).coordinates.setRandom(GAME_HEIGHT, GAME_WIDTH);

        // Actions > Draw Frame
        Actions::drawFrame();

        // System
        ::system("title Snake Game");

        // Return
        return 0;
    }

    // Reset
    int Reset() {
        // Initiate
        Initiate(false);

        // Loop > Update
        while (!State::gameover) Update();

        // Terminate
        Terminate();

        // Return
        return 0;
    }

    // Terminate
    int Terminate() {
        // System
        ::system("cls && title Snake Game [Gameover]");

        // Actions > Render (Frame, Game Over Menu)
        Actions::renderFrame();
        Actions::renderControlsMenu();
        if (Settings::viewStatistics) Actions::renderStatistics();
        Actions::renderGameOverMenu();

        // Return
        return 0;
    }

    // Update
    int Update() {
        // Logic
        if (!State::gameover) {
            // Logic
            if (Actions::hasRecievedInput()) {
                // Actions > Request Input
                const char* input = Actions::requestInput();

                // Logic
                if (*input == 'p' || *input == 'P') Actions::pause();
                else if (*input == 'n' || *input == 'N') PLAYER.stop();
                else if (*input == 't' || *input == 'T') Settings::phaseThroughWalls = !Settings::phaseThroughWalls;
                else if (*input == 'x' || *input == 'X') PLAYER.die("User Request");
                else if ((*input == 'd' || *input == 'D') || (Data::FORMER_INPUT_KEY == 224 && Data::INPUT_KEY == 77)) PLAYER.setDirection(Data::East);
                else if ((*input == 'w' || *input == 'W') || (Data::FORMER_INPUT_KEY == 224 && Data::INPUT_KEY == 72)) PLAYER.setDirection(Data::North);
                else if ((*input == 's' || *input == 'S') || (Data::FORMER_INPUT_KEY == 224 && Data::INPUT_KEY == 80)) PLAYER.setDirection(Data::South);
                else if ((*input == 'a' || *input == 'A') || (Data::FORMER_INPUT_KEY == 224 && Data::INPUT_KEY == 75)) PLAYER.setDirection(Data::West);
            }

            // Logic
            if (!State::paused) {
                // Actions > Draw Frame
                Actions::drawFrame();

                // Player > Move
                PLAYER.move();

                // Modification > State > Game Over
                PLAYER.isDead && (State::gameover = true);
            }
        }

        // Return
        return 0;
    }

/* Main */
int main(int argc, char* argv[]) {
    // Initiate
    Initiate();

    // Loop > Update
    while (!State::gameover) Update();

    // Terminate
    Terminate();

    // Return
    return 0;
}
