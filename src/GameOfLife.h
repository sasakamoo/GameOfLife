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
    static olc::vf2d offset;
    static olc::vf2d cursor;
    float scale = 10.0f;
    float grid = 1.0f;

    // List of cells existing in the world
    std::list<Cell*> cells;

    // Convert coordinates from World Space ---> Screen Space
    void worldToScreen(const olc::vf2d& v, int& screenX, int& screenY);

    // Convert coordinates from Screen Space ---> World Space
    void screenToWorld(int screenX, int screenY, olc::vf2d& v);

    // Handle pan and zoom
    void handlePanZoom();

    // Draw functions
    void drawWorld();
    void drawCursor();

public:
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
};