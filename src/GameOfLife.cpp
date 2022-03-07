#include "GameOfLife.h"

// If you make these static figure this out
//olc::TransformedView GameOfLife::tv;
//olc::vf2d GameOfLife::cursor;

GameOfLife::GameOfLife() {
    sAppName = "Game Of Life";
}

void GameOfLife::drawWorld() {
    olc::vf2d sp, ep;
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
            sp = tv.WorldToScreen({ x, y });
            Draw(sp.x, sp.y, olc::BLUE);
        }
    }

    // Draw world axis
    sp = tv.WorldToScreen({ 0, worldTopLeft.y });
    ep = tv.WorldToScreen({ 0, worldBottomRight.y });
    DrawLine(sp.x, sp.y, ep.x, ep.y, olc::GREY, 0xF0F0F0F0);
    sp = tv.WorldToScreen({ worldTopLeft.x, 0 });
    ep = tv.WorldToScreen({ worldBottomRight.x, 0 });
    DrawLine(sp.x, sp.y, ep.x, ep.y, olc::GREY, 0xF0F0F0F0);
}

void GameOfLife::drawCursor() {
    // Draw temp cell placement
    olc::vf2d sp;
    sp = tv.WorldToScreen(cursor);
    FillRect(sp, tv.GetWorldScale(), { 255, 51, 255 });

    // Draw cursor string position
    DrawString(10, 10, "X=" + std::to_string(cursor.x) + ", Y=" + std::to_string(cursor.y), olc::YELLOW, 2);
}

bool GameOfLife::OnUserCreate() {
    tv.Initialise({ ScreenWidth(), ScreenHeight() }, { 10.0f, 10.0f });
    tv.SetWorldOffset({ (float) -ScreenWidth() / 2, (float) -ScreenHeight() / 2 });
    return true;
}

bool GameOfLife::OnUserUpdate(float fElapsedTime) {
    // Handle pan and zoom
    tv.HandlePanAndZoom();

    // Start drawing
    Clear(olc::BLACK);

    // Draw world
    drawWorld();

    // Draw cursor
    drawCursor();

    return true;
}