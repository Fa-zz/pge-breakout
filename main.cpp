#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class BreakOut : public olc::PixelGameEngine {

public:
    BreakOut() {
        sAppName = "BreakOut Clone";
    }

private:
    float fBatPos = 20.0f;   // fBatPos: X coord of bat, as it only moves horizontally
    float fBatWidth = 40.0f; // fBatWidth: Width of bat

    olc::vf2d vBall = { 200.0f, 200.0f };   // vBall: Ball's x and y pos

    float fBatSpeed = 5.0f;

public:
    bool OnUserCreate() override {
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {
        // Erase previous frame
        Clear(olc::DARK_BLUE);

        // Draw boundary
        DrawLine(10, 10, ScreenWidth()-10, 10, olc::YELLOW);    // top boundary
        DrawLine(10, 10, 10, ScreenHeight()-10, olc::YELLOW);   // LH boundary
        DrawLine(ScreenWidth()-10, 10, ScreenWidth()-10, ScreenHeight()-10, olc::YELLOW);   // RH boundary

        // Draw bat
        FillRect(int(fBatPos), ScreenHeight()-20, int(fBatWidth), 10, olc::GREEN);

        // Draw ball
        FillCircle(vBall, 5, olc::CYAN);

        // Handle user input
        if (GetKey(olc::Key::LEFT).bHeld)   fBatPos -= fBatSpeed;
        if (GetKey(olc::Key::RIGHT).bHeld)  fBatPos += fBatSpeed;

        if (fBatPos < 11.0f)    fBatPos = 11.0f;
        if (fBatPos + fBatWidth > float(ScreenWidth()) - 10.0f) fBatPos = float(ScreenWidth()) - 10.0f - fBatWidth;

        return true;
    }
};

int main() {
    BreakOut game;
    if (game.Construct(512, 480, 2, 2))
        game.Start();
    return 0;
}