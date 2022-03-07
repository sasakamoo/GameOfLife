#include "pge/olcPixelGameEngine.h"
#include "pge/olcPGEX_TransformedView.h"

struct Cell {
    // Position in World Space
    olc::vf2d pos;
};

class GameOfLife : public olc::PixelGameEngine {
public:
    GameOfLife();

private:
    // Pan and zoom variables
    olc::TransformedView tv;
    olc::vf2d cursor;

    // Grid square every 1.0f in world space
    float grid = 1.0f;

    // List of cells existing in the world
    std::list<Cell*> cells;

    // Draw functions
    void drawWorld();
    void drawCursor();

public:
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
};