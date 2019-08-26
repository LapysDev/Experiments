/* Import */
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library
#include <unistd.h> // UNIX Standard

/* Class */
    // ...
    class Entity;
    class DynamicEntity;
    class StaticEntity;

    // Entity
    class Entity {
        // ...
        public:
            // [Constructor]
            inline Entity() : id(0u) {}
            inline Entity(const unsigned id) : id(id) {}

            // Initialization > ID
            unsigned short id;

            // Function > Announce
            virtual void announce() const { if (id) ::printf("[Entity #%i]:\t\t\"Hello, World!\"\n", this -> id); else ::write(1, "[Entity]:\t\t\"Hello, World!\"\n", 27); }
    };
        // Dynamic Entity
        class DynamicEntity : Entity {
            // ...
            public:
                // [Constructor]
                inline DynamicEntity() { this -> id = 0u; }
                inline DynamicEntity(const unsigned id) { this -> id = id; }

                // Function > Announce
                void announce() const { if (id) ::printf("[Dynamic Entity #%i]:\t\"Hello, World!\"\n", this -> id); else ::write(1, "[Dynamic Entity]:\t\"Hello, World!\"\n", 34); }
        };

        // Static Entity
        class StaticEntity : Entity {
            // ...
            public:
                // [Constructor]
                inline StaticEntity() { this -> id = 0u; }
                inline StaticEntity(const unsigned id) { this -> id = id; }

                // Function > Announce
                void announce() const { if (id) ::printf("[Static Entity #%i]:\t\"Hello, World!\"\n", this -> id); else ::write(1, "[Static Entity]:\t\"Hello, World!\"\n", 33); }
        };

/* Main */
int main(void) {
    // Constant > ...
    const DynamicEntity DYNAMIC_ENTITY;
    const Entity ENTITY;
    const StaticEntity STATIC_ENTITY;

    // Entity > Announce; ...
    ENTITY.announce();
    DYNAMIC_ENTITY.announce();
    STATIC_ENTITY.announce();
    ::write(1, "\n", 1);

    // [Test A] Logic --- WARN (Lapys) -> Referencing the entities causes undefined behavior.
    #if false
        // [Begin] ...
        ::write(1, "[A]\n==================================================\n", 55);

        // Initialization > Entities Collection A
        void *entitiesCollectionA = std::malloc(5u * sizeof(Entity));

        // Update > Entities Collection A
        *(((Entity*) (entitiesCollectionA)) + 0u) = Entity(1u);
        *(((Entity*) (entitiesCollectionA)) + 1u) = DynamicEntity(2u);
        *(((Entity*) (entitiesCollectionA)) + 2u) = Entity(3u);
        *(((Entity*) (entitiesCollectionA)) + 3u) = StaticEntity(4u);
        *(((Entity*) (entitiesCollectionA)) + 4u) = Entity(5u);

        // [Entity] > Announce
        (*(((Entity*) entitiesCollectionA) + 0u)).announce();
        (*(((Entity*) entitiesCollectionA) + 1u)).announce();
        (*(((Entity*) entitiesCollectionA) + 2u)).announce();
        (*(((Entity*) entitiesCollectionA) + 3u)).announce();
        (*(((Entity*) entitiesCollectionA) + 4u)).announce();

        // Deletion
        std::free(entitiesCollectionA);

        // [End] ...
        ::write(1, "\n", 1);
    #endif

    // [Test B] Logic --- WARN (Lapys) -> Causes object splicing.
    #if false
        // [Begin] ...
        ::write(1, "[B]\n==================================================\n", 55);

        // Initialization > Entities Collection A
        void *entitiesCollectionB = new Entity[5u];

        // Update > Entities Collection A
        *(((Entity*) (entitiesCollectionB)) + 0u) = Entity(1u);
        *(((Entity*) (entitiesCollectionB)) + 1u) = DynamicEntity(2u);
        *(((Entity*) (entitiesCollectionB)) + 2u) = Entity(3u);
        *(((Entity*) (entitiesCollectionB)) + 3u) = StaticEntity(4u);
        *(((Entity*) (entitiesCollectionB)) + 4u) = Entity(5u);

        // [Entity] > Announce
        (*(((Entity*) entitiesCollectionB) + 0u)).announce();
        (*(((Entity*) entitiesCollectionB) + 1u)).announce();
        (*(((Entity*) entitiesCollectionB) + 2u)).announce();
        (*(((Entity*) entitiesCollectionB) + 3u)).announce();
        (*(((Entity*) entitiesCollectionB) + 4u)).announce();

        // Deletion --- WARN (Lapys) -> Deleting `void*` types is undefined.
        std::free(entitiesCollectionB);

        // [End] ...
        ::write(1, "\n", 1);
    #endif

    // [Test C] Logic --- WARN (Lapys) -> Referencing the entities causes undefined behavior.
    #if false
        // [Begin] ...
        ::write(1, "[C]\n==================================================\n", 55);

        // Initialization > Entities Collection C
        Entity *entitiesCollectionC = (Entity*) std::malloc(5u * sizeof(Entity));

        // Update > Entities Collection C
        *(entitiesCollectionC + 0u) = Entity(1u);
        *(entitiesCollectionC + 1u) = DynamicEntity(2u);
        *(entitiesCollectionC + 2u) = Entity(3u);
        *(entitiesCollectionC + 3u) = StaticEntity(4u);
        *(entitiesCollectionC + 4u) = Entity(5u);

        // [Entity] > Announce
        (*(((Entity*) entitiesCollectionC) + 0u)).announce();
        (*(((Entity*) entitiesCollectionC) + 1u)).announce();
        (*(((Entity*) entitiesCollectionC) + 2u)).announce();
        (*(((Entity*) entitiesCollectionC) + 3u)).announce();
        (*(((Entity*) entitiesCollectionC) + 4u)).announce();

        // Deletion
        std::free(entitiesCollectionC);

        // [End] ...
        ::write(1, "\n", 1);
    #endif

    // [Test D] Logic --- WARN (Lapys) -> Causes object splicing.
    #if false
        // [Begin] ...
        ::write(1, "[D]\n==================================================\n", 55);

        // Initialization > Entities Collection D
        Entity *entitiesCollectionD = new Entity[5u];

        // Update > Entities Collection D
        *(entitiesCollectionD + 0u) = Entity(1u);
        *(entitiesCollectionD + 1u) = DynamicEntity(2u);
        *(entitiesCollectionD + 2u) = Entity(3u);
        *(entitiesCollectionD + 3u) = StaticEntity(4u);
        *(entitiesCollectionD + 4u) = Entity(5u);

        // [Entity] > Announce
        (*(((Entity*) entitiesCollectionD) + 0u)).announce();
        (*(((Entity*) entitiesCollectionD) + 1u)).announce();
        (*(((Entity*) entitiesCollectionD) + 2u)).announce();
        (*(((Entity*) entitiesCollectionD) + 3u)).announce();
        (*(((Entity*) entitiesCollectionD) + 4u)).announce();

        // Deletion --- WARN (Lapys) -> Deleting objects of polymorphic types with a non-virtual destructor may cause undefined behavior.
        std::free(entitiesCollectionD);

        // [End] ...
        ::write(1, "\n", 1);
    #endif

    // [Test E] Logic --- WARN (Lapys) -> Causes object splicing.
    #if false
        // [Begin] ...
        ::write(1, "[E]\n==================================================\n", 55);

        // Initialization > Entities Collection E
        Entity entitiesCollectionE[5u];

        // Update > Entities Collection E
        entitiesCollectionE[0u] = Entity(1u);
        entitiesCollectionE[1u] = Entity(2u);
        entitiesCollectionE[2u] = Entity(3u);
        entitiesCollectionE[3u] = Entity(4u);
        entitiesCollectionE[4u] = Entity(5u);

        // [Entity] > Announce
        entitiesCollectionE[0u].announce();
        entitiesCollectionE[1u].announce();
        entitiesCollectionE[2u].announce();
        entitiesCollectionE[3u].announce();
        entitiesCollectionE[4u].announce();

        // [End] ...
        ::write(1, "\n", 1);
    #endif

    // [Test F] Logic --- WARN (Lapys) -> Referencing the entities causes undefined behavior.
    #if false
        // [Begin] ...
        ::write(1, "[F]\n==================================================\n", 55);

        // Initialization > Entities Collection F
        void **entitiesCollectionF = (void**) std::malloc(5u * sizeof(Entity*));

        // Update > Entities Collection F
        *(entitiesCollectionF + 0u) = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) *(entitiesCollectionF + 0u)) = Entity(1u);

        *(entitiesCollectionF + 1u) = (Entity*) std::malloc(sizeof(DynamicEntity));
        *((Entity*) *(entitiesCollectionF + 1u)) = DynamicEntity(2u);

        *(entitiesCollectionF + 2u) = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) *(entitiesCollectionF + 2u)) = Entity(3u);

        *(entitiesCollectionF + 3u) = (Entity*) std::malloc(sizeof(StaticEntity));
        *((Entity*) *(entitiesCollectionF + 3u)) = StaticEntity(4u);

        *(entitiesCollectionF + 5u) = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) *(entitiesCollectionF + 5u)) = Entity(5u);

        // [Entity] > Announce
        (*((Entity*) *(entitiesCollectionF + 0u))).announce();
        (*((Entity*) *(entitiesCollectionF + 1u))).announce();
        (*((Entity*) *(entitiesCollectionF + 2u))).announce();
        (*((Entity*) *(entitiesCollectionF + 3u))).announce();
        (*((Entity*) *(entitiesCollectionF + 4u))).announce();

        // Deletion
        { unsigned short iterator = 5u; while (iterator) std::free(*(entitiesCollectionF + (iterator -= 1))); std::free(entitiesCollectionF); }

        // [End] ...
        ::write(1, "\n", 1);
    #endif

    /* [Test G] Logic --- WARN (Lapys) ->
            - Causes object slicing.
            - Referencing farthest entities causes undefined behavior.
    */
    #if false
        // [Begin] ...
        ::write(1, "[G]\n==================================================\n", 55);

        // Initialization > Entities Collection G
        void **entitiesCollectionG = (void**) std::malloc(5u * sizeof(Entity*));

        // Update > Entities Collection G
        *(entitiesCollectionG + 0u) = new Entity(1u);
        *(entitiesCollectionG + 0u) = new Entity(1u);
        *(entitiesCollectionG + 0u) = new Entity(1u);
        *(entitiesCollectionG + 0u) = new Entity(1u);
        *(entitiesCollectionG + 0u) = new Entity(1u);

        // [Entity] > Announce
        (*((Entity*) *(entitiesCollectionG + 0u))).announce();
        (*((Entity*) *(entitiesCollectionG + 1u))).announce();
        (*((Entity*) *(entitiesCollectionG + 2u))).announce();
        (*((Entity*) *(entitiesCollectionG + 3u))).announce();
        (*((Entity*) *(entitiesCollectionG + 4u))).announce();

        // Deletion --- WARN (Lapys) -> Deleting `void*` types is undefined.
        { unsigned short iterator = 5u; while (iterator) std::free(*(entitiesCollectionG + (iterator -= 1))); std::free(entitiesCollectionG); }

        // [End] ...
        ::write(1, "\n", 1);
    #endif

    // [Test H] Logic --- WARN (Lapys) -> Referencing the entities causes undefined behavior.
    #if false
        // [Begin] ...
        ::write(1, "[H]\n==================================================\n", 55);

        // Initialization > Entities Collection H
        void **entitiesCollectionH = (void**) new Entity*[5u];

        // Update > Entities Collection H
        *(entitiesCollectionH + 0u) = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) *(entitiesCollectionH + 0u)) = Entity(1u);

        *(entitiesCollectionH + 1u) = (Entity*) std::malloc(sizeof(DynamicEntity));
        *((Entity*) *(entitiesCollectionH + 1u)) = DynamicEntity(2u);

        *(entitiesCollectionH + 2u) = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) *(entitiesCollectionH + 2u)) = Entity(3u);

        *(entitiesCollectionH + 3u) = (Entity*) std::malloc(sizeof(StaticEntity));
        *((Entity*) *(entitiesCollectionH + 3u)) = StaticEntity(4u);

        *(entitiesCollectionH + 5u) = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) *(entitiesCollectionH + 5u)) = Entity(5u);

        // [Entity] > Announce
        (*((Entity*) *(entitiesCollectionH + 0u))).announce();
        (*((Entity*) *(entitiesCollectionH + 1u))).announce();
        (*((Entity*) *(entitiesCollectionH + 2u))).announce();
        (*((Entity*) *(entitiesCollectionH + 3u))).announce();
        (*((Entity*) *(entitiesCollectionH + 4u))).announce();

        // Deletion
        delete[] entitiesCollectionH;

        // [End] ...
        ::write(1, "\n", 1);
    #endif

    // [Test I] Logic --- CONSIDERATION (Lapys) -> May cause undefined behavior; Reference Test O.
    #if true
        // [Begin] ...
        ::write(1, "[I]\n==================================================\n", 55);

        // Initialization > Entities Collection I
        void **entitiesCollectionI = (void**) new Entity*[5u];

        // Update > Entities Collection I
        *(entitiesCollectionI + 0u) = new Entity(1u);
        *(entitiesCollectionI + 1u) = new DynamicEntity(2u);
        *(entitiesCollectionI + 2u) = new Entity(3u);
        *(entitiesCollectionI + 3u) = new StaticEntity(4u);
        *(entitiesCollectionI + 4u) = new Entity(5u);

        // [Entity] > Announce
        (*((Entity*) *(entitiesCollectionI + 0u))).announce();
        (*((Entity*) *(entitiesCollectionI + 1u))).announce();
        (*((Entity*) *(entitiesCollectionI + 2u))).announce();
        (*((Entity*) *(entitiesCollectionI + 3u))).announce();
        (*((Entity*) *(entitiesCollectionI + 4u))).announce();

        // Deletion
        delete[] entitiesCollectionI;

        // [End] ...
        ::write(1, "\n", 1);
    #endif

    // [Test J] Logic --- WARN (Lapys) -> Referencing the entities causes undefined behavior.
    #if false
        // [Begin] ...
        ::write(1, "[J]\n==================================================\n", 55);

        // Initialization > Entities Collection J
        void *entitiesCollectionJ[5u];

        // Update > Entities Collection J
        entitiesCollectionJ[0u] = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) entitiesCollectionJ[0u]) = Entity(1u);

        entitiesCollectionJ[1u] = (Entity*) std::malloc(sizeof(DynamicEntity));
        *((Entity*) entitiesCollectionJ[1u]) = DynamicEntity(2u);

        entitiesCollectionJ[2u] = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) entitiesCollectionJ[2u]) = Entity(3u);

        entitiesCollectionJ[3u] = (Entity*) std::malloc(sizeof(StaticEntity));
        *((Entity*) entitiesCollectionJ[3u]) = StaticEntity(4u);

        entitiesCollectionJ[4u] = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) entitiesCollectionJ[4u]) = Entity(5u);

        // [Entity] > Announce
        (*((Entity*) entitiesCollectionJ[0u])).announce();
        (*((Entity*) entitiesCollectionJ[1u])).announce();
        (*((Entity*) entitiesCollectionJ[2u])).announce();
        (*((Entity*) entitiesCollectionJ[3u])).announce();
        (*((Entity*) entitiesCollectionJ[4u])).announce();

        // [End] ...
        ::write(1, "\n", 1);
    #endif

    // [Test K] Logic --- CONSIDERATION (Lapys) -> May cause undefined behavior; Reference Test Q.
    #if true
        // [Begin] ...
        ::write(1, "[K]\n==================================================\n", 55);

        // Initialization > Entities Collection K
        void *entitiesCollectionK[5u];

        // Update > Entities Collection K
        *(entitiesCollectionK + 0u) = new Entity(1u);
        *(entitiesCollectionK + 1u) = new DynamicEntity(2u);
        *(entitiesCollectionK + 2u) = new Entity(3u);
        *(entitiesCollectionK + 3u) = new StaticEntity(4u);
        *(entitiesCollectionK + 4u) = new Entity(5u);

        // [Entity] > Announce
        (*((Entity*) *(entitiesCollectionK + 0u))).announce();
        (*((Entity*) *(entitiesCollectionK + 1u))).announce();
        (*((Entity*) *(entitiesCollectionK + 2u))).announce();
        (*((Entity*) *(entitiesCollectionK + 3u))).announce();
        (*((Entity*) *(entitiesCollectionK + 4u))).announce();

        // [End] ...
        ::write(1, "\n", 1);
    #endif

    // [Test L] Logic --- WARN (Lapys) -> Referencing the entities causes undefined behavior.
    #if false
        // [Begin] ...
        ::write(1, "[F]\n==================================================\n", 55);

        // Initialization > Entities Collection L
        Entity **entitiesCollectionL = (Entity**) std::malloc(5u * sizeof(Entity*));

        // Update > Entities Collection L
        *(entitiesCollectionL + 0u) = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) *(entitiesCollectionL + 0u)) = Entity(1u);

        *(entitiesCollectionL + 1u) = (Entity*) std::malloc(sizeof(DynamicEntity));
        *((Entity*) *(entitiesCollectionL + 1u)) = DynamicEntity(2u);

        *(entitiesCollectionL + 2u) = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) *(entitiesCollectionL + 2u)) = Entity(3u);

        *(entitiesCollectionL + 3u) = (Entity*) std::malloc(sizeof(StaticEntity));
        *((Entity*) *(entitiesCollectionL + 3u)) = StaticEntity(4u);

        *(entitiesCollectionL + 5u) = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) *(entitiesCollectionL + 5u)) = Entity(5u);

        // [Entity] > Announce
        (*((Entity*) *(entitiesCollectionL + 0u))).announce();
        (*((Entity*) *(entitiesCollectionL + 1u))).announce();
        (*((Entity*) *(entitiesCollectionL + 2u))).announce();
        (*((Entity*) *(entitiesCollectionL + 3u))).announce();
        (*((Entity*) *(entitiesCollectionL + 4u))).announce();

        // Deletion
        { unsigned short iterator = 5u; while (iterator) std::free(*(entitiesCollectionL + (iterator -= 1))); std::free(entitiesCollectionL); }

        // [End] ...
        ::write(1, "\n", 1);
    #endif

    /* [Test M] Logic --- WARN (Lapys) ->
            - Causes object slicing.
            - Referencing farthest entities causes undefined behavior.
    */
    #if false
        // [Begin] ...
        ::write(1, "[M]\n==================================================\n", 55);

        // Initialization > Entities Collection M
        Entity **entitiesCollectionM = (Entity**) std::malloc(5u * sizeof(Entity*));

        // Update > Entities Collection M
        *(entitiesCollectionM + 0u) = new Entity(1u);
        *(entitiesCollectionM + 0u) = new Entity(1u);
        *(entitiesCollectionM + 0u) = new Entity(1u);
        *(entitiesCollectionM + 0u) = new Entity(1u);
        *(entitiesCollectionM + 0u) = new Entity(1u);

        // [Entity] > Announce
        (*((Entity*) *(entitiesCollectionM + 0u))).announce();
        (*((Entity*) *(entitiesCollectionM + 1u))).announce();
        (*((Entity*) *(entitiesCollectionM + 2u))).announce();
        (*((Entity*) *(entitiesCollectionM + 3u))).announce();
        (*((Entity*) *(entitiesCollectionM + 4u))).announce();

        // Deletion --- WARN (Lapys) -> Deleting objects of polymorphic types with a non-virtual destructor may cause undefined behavior.
        { unsigned short iterator = 5u; while (iterator) std::free(*(entitiesCollectionM + (iterator -= 1))); std::free(entitiesCollectionM); }

        // [End] ...
        ::write(1, "\n", 1);
    #endif

    // [Test N] Logic --- WARN (Lapys) -> Referencing the entities causes undefined behavior.
    #if false
        // [Begin] ...
        ::write(1, "[N]\n==================================================\n", 55);

        // Initialization > Entities Collection N
        Entity **entitiesCollectionN = (Entity**) new Entity*[5u];

        // Update > Entities Collection N
        *(entitiesCollectionN + 0u) = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) *(entitiesCollectionN + 0u)) = Entity(1u);

        *(entitiesCollectionN + 1u) = (Entity*) std::malloc(sizeof(DynamicEntity));
        *((Entity*) *(entitiesCollectionN + 1u)) = DynamicEntity(2u);

        *(entitiesCollectionN + 2u) = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) *(entitiesCollectionN + 2u)) = Entity(3u);

        *(entitiesCollectionN + 3u) = (Entity*) std::malloc(sizeof(StaticEntity));
        *((Entity*) *(entitiesCollectionN + 3u)) = StaticEntity(4u);

        *(entitiesCollectionN + 5u) = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) *(entitiesCollectionN + 5u)) = Entity(5u);

        // [Entity] > Announce
        (*((Entity*) *(entitiesCollectionN + 0u))).announce();
        (*((Entity*) *(entitiesCollectionN + 1u))).announce();
        (*((Entity*) *(entitiesCollectionN + 2u))).announce();
        (*((Entity*) *(entitiesCollectionN + 3u))).announce();
        (*((Entity*) *(entitiesCollectionN + 4u))).announce();

        // Deletion
        delete[] entitiesCollectionN;

        // [End] ...
        ::write(1, "\n", 1);
    #endif

    // [Test O] Logic --- WARN (Lapys) -> On some compilers `Entity` is an inaccessible base class of `DynamicEntity` and `StaticEntity` (if the derived classes do not inherit publicly).
    #if false
        // [Begin] ...
        ::write(1, "[O]\n==================================================\n", 55);

        // Initialization > Entities Collection O
        Entity **entitiesCollectionO = (Entity**) new Entity*[5u];

        // Update > Entities Collection O
        *(entitiesCollectionO + 0u) = new Entity(1u);
        *(entitiesCollectionO + 1u) = new DynamicEntity(2u);
        *(entitiesCollectionO + 2u) = new Entity(3u);
        *(entitiesCollectionO + 3u) = new StaticEntity(4u);
        *(entitiesCollectionO + 4u) = new Entity(5u);

        // [Entity] > Announce
        (*((Entity*) *(entitiesCollectionO + 0u))).announce();
        (*((Entity*) *(entitiesCollectionO + 1u))).announce();
        (*((Entity*) *(entitiesCollectionO + 2u))).announce();
        (*((Entity*) *(entitiesCollectionO + 3u))).announce();
        (*((Entity*) *(entitiesCollectionO + 4u))).announce();

        // Deletion
        delete[] entitiesCollectionO;

        // [End] ...
        ::write(1, "\n", 1);
    #endif

    // [Test P] Logic --- WARN (Lapys) -> Referencing the entities causes undefined behavior.
    #if false
        // [Begin] ...
        ::write(1, "[P]\n==================================================\n", 55);

        // Initialization > Entities Collection P
        Entity *entitiesCollectionP[5u];

        // Update > Entities Collection P
        entitiesCollectionP[0u] = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) entitiesCollectionP[0u]) = Entity(1u);

        entitiesCollectionP[1u] = (Entity*) std::malloc(sizeof(DynamicEntity));
        *((Entity*) entitiesCollectionP[1u]) = DynamicEntity(2u);

        entitiesCollectionP[2u] = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) entitiesCollectionP[2u]) = Entity(3u);

        entitiesCollectionP[3u] = (Entity*) std::malloc(sizeof(StaticEntity));
        *((Entity*) entitiesCollectionP[3u]) = StaticEntity(4u);

        entitiesCollectionP[4u] = (Entity*) std::malloc(sizeof(Entity));
        *((Entity*) entitiesCollectionP[4u]) = Entity(5u);

        // [Entity] > Announce
        (*((Entity*) entitiesCollectionP[0u])).announce();
        (*((Entity*) entitiesCollectionP[1u])).announce();
        (*((Entity*) entitiesCollectionP[2u])).announce();
        (*((Entity*) entitiesCollectionP[3u])).announce();
        (*((Entity*) entitiesCollectionP[4u])).announce();

        // [End] ...
        ::write(1, "\n", 1);
    #endif

    // [Test Q] Logic --- WARN (Lapys) -> On some compilers `Entity` is an inaccessible base class of `DynamicEntity` and `StaticEntity` (if the derived classes do not inherit publicly).
    #if false
        // [Begin] ...
        ::write(1, "[Q]\n==================================================\n", 55);

        // Initialization > Entities Collection Q
        Entity *entitiesCollectionQ[5u];

        // Update > Entities Collection Q
        *(entitiesCollectionQ + 0u) = new Entity(1u);
        *(entitiesCollectionQ + 1u) = new DynamicEntity(2u);
        *(entitiesCollectionQ + 2u) = new Entity(3u);
        *(entitiesCollectionQ + 3u) = new StaticEntity(4u);
        *(entitiesCollectionQ + 4u) = new Entity(5u);

        // [Entity] > Announce
        (*((Entity*) *(entitiesCollectionQ + 0u))).announce();
        (*((Entity*) *(entitiesCollectionQ + 1u))).announce();
        (*((Entity*) *(entitiesCollectionQ + 2u))).announce();
        (*((Entity*) *(entitiesCollectionQ + 3u))).announce();
        (*((Entity*) *(entitiesCollectionQ + 4u))).announce();

        // [End] ...
        ::write(1, "\n", 1);
    #endif

    // Return
    return 0;
}
