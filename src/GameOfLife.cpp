#include "GameOfLife.h"

olc::TransformedView GameOfLife::tv;

GameOfLife::GameOfLife() {
    sAppName = "Game Of Life";
}

void GameOfLife::handlePanAndZoom() {
    // Get mouse position
    const olc::vi2d mouse = GetMousePos();

    // Handle pan
    if (GetMouse(2).bPressed || GetKey(olc::Key::SPACE).bPressed) tv.StartPan(mouse);
    if (GetMouse(2).bHeld || GetKey(olc::Key::SPACE).bHeld) tv.UpdatePan(mouse);
    if (GetMouse(2).bReleased || GetKey(olc::Key::SPACE).bReleased) tv.EndPan(mouse);
    
    // Handle zoom
    if (GetMouseWheel() > 0) tv.ZoomAtScreenPos(1.1f, mouse);
    if (GetMouseWheel() < 0) tv.ZoomAtScreenPos(0.9f, mouse);
}

void GameOfLife::handleCursor() {
    // Get mouse world position
    olc::vf2d mouseWorldPosition;
    mouseWorldPosition = tv.ScreenToWorld({ (float) GetMouseX(), (float) GetMouseY() });
    
    // snap cursor to grid position
    cursor.x = floorf((mouseWorldPosition.x) * grid);
    cursor.y = floorf((mouseWorldPosition.y) * grid);
}

void GameOfLife::drawWorld() {
     // Get visible world
    olc::vf2d worldTopLeft, worldBottomRight;
    worldTopLeft = tv.ScreenToWorld({ 0, 0 });
    worldBottomRight = tv.ScreenToWorld({ (float) ScreenWidth(), (float) ScreenHeight() });

    // Set values to just beyond screen boundaries
    worldTopLeft.x = floorf(worldTopLeft.x);
    worldTopLeft.y = floorf(worldTopLeft.y);
    worldBottomRight.x = ceilf(worldBottomRight.x);
    worldBottomRight.y = ceilf(worldBottomRight.y);

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
    DrawString(10, 10, "X=" + std::to_string(cursor.x) + ", Y=" + std::to_string(cursor.y), olc::YELLOW, 2);
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
    handlePanAndZoom();
    handleCursor();

    // Start drawing
    Clear(olc::BLACK);
    drawWorld();
    drawCursor();

    return true;
}