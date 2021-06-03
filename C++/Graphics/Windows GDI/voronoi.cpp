#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

struct Point {
    olc::vi2d position;
    olc::vf2d velocity;

    void Logic(const olc::vu2d& ref_point, float k, float dt) {
        olc::vf2d offset = olc::vf2d(position - ref_point);
        velocity += -k * offset * dt;
        position += velocity * dt;
    }

    void Constrain(const olc::vi2d& size) {
        if (position.x < 0) position.x = 0;
        else if (position.x > size.x) position.x = size.x;

        if (position.y < 0) position.y = 0;
        else if (position.y > size.y) position.y = size.y;
    }

    Point() {}
    Point(const olc::vi2d& p)
        : position(p) {}

    void SetVelocity(float vx, float vy) {
        velocity = { vx, vy };
    }
};

class Simulation : public olc::PixelGameEngine {
private:
    uint8_t* buffer = nullptr;
    olc::vu2d n_tiles;
    uint32_t size;

    std::vector<Point> points;

    void SetTile(int x, int y, uint8_t a) {
        buffer[y * n_tiles.x + x] = a;
    }

    void GeneratePattern() {
        for (int i = 0; i < n_tiles.y; i++) {
            for (int j = 0; j < n_tiles.x; j++) {
                float min_distance = INFINITY;
                Point* min_point = nullptr;

                olc::vi2d unit(j, i);

                for (auto& p : points) {
                    float new_distance = (float)(unit - p.position).mag2();
                    if (new_distance < min_distance) {
                        min_distance = new_distance;
                        min_point = &p;
                    }
                }

                if (min_point != nullptr) {
                    olc::vi2d offset = unit - min_point->position;
                    int n = std::max(abs(offset.x), abs(offset.y));

                    SetTile(j, i, std::min(n * 2, 255));
                }
            }
        }
    }
public:
    Simulation() {
        sAppName = "Title";
    }

    bool OnUserCreate() override {

        size = 2;
        n_tiles = { ScreenWidth() / size, ScreenHeight() / size };
        buffer = new uint8_t[n_tiles.x * n_tiles.y * sizeof(uint8_t)];
        std::generate(buffer, buffer + (n_tiles.x * n_tiles.y), []() { return rand() % 256; });

        for (int i = 0; i < 10; i++) {
            points.push_back(Point(olc::vi2d((rand() % n_tiles.x), (rand() % n_tiles.y))));
            points[i].SetVelocity((rand() / RAND_MAX), (rand() / RAND_MAX));
        }

        return true;
    }

    bool OnUserUpdate(float dt) override {

        auto GetTile = [&](int x, int y) -> uint8_t {
            if (x < 0 || y < 0 || x > n_tiles.x-1 || y > n_tiles.y-1) return '\0';
            return buffer[y * n_tiles.x + x];
        };

        // Input
        if (GetKey(olc::SPACE).bHeld) GeneratePattern();

        // Logic
        for (auto& p : points) {
            p.Logic({ n_tiles.x / 2, n_tiles.y / 2 }, 10.0f, dt);
            p.Constrain(n_tiles);
        }

        // Render
        for (int i = 0; i < n_tiles.y; i++) {
            for (int j = 0; j < n_tiles.x; j++) {
                uint8_t a = GetTile(j, i);
                FillRect(j * size, i * size, size, size, olc::Pixel(0, 0, a));
            }
        }

        return true;
    }

    bool OnUserDestroy() override {

        delete[] buffer;
        return true;
    }
};

int main() {

    srand((unsigned)time(0));

    Simulation app;
    if (app.Construct(256, 256, 1, 1)) {
        app.Start();
    }

    return 0;
}
