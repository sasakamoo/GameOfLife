#include "pge/olcPixelGameEngine.h"
#include "pge/olcPGEX_TransformedView.h"

struct Cell {
    // Position in World Space
    olc::vf2d position;
    int neighbors;

    Cell(olc::vf2d pos);
};

class GameOfLife : public olc::PixelGameEngine {
public:
    GameOfLife();

private:
    // Pan and zoom variables
    static olc::TransformedView tv;
    olc::vf2d cursor;
    float grid = 1.0f;

    // List of cells existing in the world
    std::list<Cell> cells;

    void handlePanAndZoom();
    void handleCursor();
    void handleCellInput();

    // Draw functions
    void drawWorld();
    void drawCursor();
    void drawCells();

public:
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
};