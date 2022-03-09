#include "GameOfLife.h"

Cell::Cell(olc::vf2d pos) {
    position = pos;
}

olc::TransformedView GameOfLife::tv;

GameOfLife::GameOfLife() {
    sAppName = "Game Of Life";
}

void GameOfLife::handlePan() {
    // Get mouse position
    const olc::vi2d mouse = GetMousePos();

    // Handle pan
    if (GetMouse(2).bPressed || GetKey(olc::Key::SPACE).bPressed) tv.StartPan(mouse);
    if (GetMouse(2).bHeld || GetKey(olc::Key::SPACE).bHeld) tv.UpdatePan(mouse);
    if (GetMouse(2).bReleased || GetKey(olc::Key::SPACE).bReleased) tv.EndPan(mouse);
    
    // // Handle zoom
    // if (GetMouseWheel() > 0) tv.ZoomAtScreenPos(1.1f, mouse);
    // if (GetMouseWheel() < 0) tv.ZoomAtScreenPos(0.9f, mouse);
}

void GameOfLife::handleCursor() {
    // Get mouse world position
    const olc::vf2d mouseWorldPosition = tv.ScreenToWorld({ (float) GetMouseX(), (float) GetMouseY() });
    
    // snap cursor to grid position
    cursor = mouseWorldPosition.floor() * grid;
}

void GameOfLife::handleCellInput() {
    if (GetKey(olc::Key::A).bPressed || GetKey(olc::Key::A).bHeld) {
        // Create temporary cell at mouse position
        // and assume the cell doesn't already exist
        bool exists = false;
        Cell temp(cursor);

        // Check if cell already exists at cursor position
        for (Cell cell : cells) {
            if ((cell.position - temp.position).mag() < 0.1) {
                // Cell already exists
                exists = true;
                break;
            }
        }

        if (!exists) {
            cells.push_back(temp);
        }
    }
}

void GameOfLife::drawWorld() {
    // Get visible world to just beyond screen boundaries
    const olc::vf2d worldTopLeft = tv.ScreenToWorld({ 0, 0 }).floor();
    const olc::vf2d worldBottomRight = tv.ScreenToWorld({ (float) ScreenWidth(), (float) ScreenHeight() }).ceil();

    // Draw grid dots of world
    for (float x = worldTopLeft.x; x < worldBottomRight.x; x += grid) {
        for (float y = worldTopLeft.y; y < worldBottomRight.y; y += grid) {
            tv.Draw({ x, y }, olc::BLUE);
        }
    }

    // Draw world axis
    tv.DrawLine({ 0, worldTopLeft.y }, { 0, worldBottomRight.y }, olc::GREY, 0xF0F0F0F0);
    tv.DrawLine({ worldTopLeft.x, 0 }, { worldBottomRight.x, 0 }, olc::GREY, 0xF0F0F0F0);
}

void GameOfLife::drawCursor() {
    // Draw temp cell placement
    tv.FillRect(cursor, { grid, grid }, { 255, 51, 255 });

    // Draw cursor string position
    DrawString(10, 10, "X=" + std::to_string(cursor.x) + ", Y=" + std::to_string(-cursor.y), olc::YELLOW, 2);
}

void GameOfLife::drawCells() {
    // Draw cells
    for (Cell cell : cells) {
        tv.FillRect(cell.position, { grid, grid });
    }
}

bool GameOfLife::OnUserCreate() {
    tv.Initialise({ ScreenWidth(), ScreenHeight() });
    tv.SetZoom(10.0f, { 0, 0 });
    olc::vf2d screenWorldSize = tv.ScreenToWorld({ (float) ScreenWidth(), (float) ScreenHeight() });
    tv.SetWorldOffset(-screenWorldSize/2);
    return true;
}

bool GameOfLife::OnUserUpdate(float fElapsedTime) {
    // Handle pan and zoom
    handlePan();
    handleCursor();
    handleCellInput();

    // Start drawing
    Clear(olc::BLACK);
    drawWorld();
    drawCells();
    drawCursor();

    return true;
}