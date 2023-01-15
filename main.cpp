#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class BreakOut : public olc::PixelGameEngine {

public:
    BreakOut() {
        sAppName = "BreakOut Clone";
    }

private:
    float fBatPos = 20.0f;                  // fBatPos: X coord of bat. Only moves horizontally so only x coord is necessary
    float fBatWidth = 40.0f;                // fBatWidth: Width of bat
    olc::vf2d vBall = { 200.0f, 200.0f };   // vBall: Ball's x and y pos
    olc::vf2d vBallVel = {200.0f, -100.0f}; // vBallVel: Velocity vector of ball 
    float fBatSpeed = 250.0f;               // fBatSpeed: How fast the ball moves
    float fBallRadius = 5.0f;               // fBallRadius: 

    olc::vi2d vBlockSize = { 16,16 };       // vBlockSize: Represents the size in pixels of one tile
    std::unique_ptr<int[]> blocks;          // blocks: Array of ints, each int will hold a different value, helps us with what to draw
    
    std::unique_ptr<olc::Sprite> sprTile;

public:
    bool OnUserCreate() override {
        blocks = std::make_unique<int[]>(24 * 30);  // Grid is initialized to contain 24x30 tiles

        // Iterates through grid. Unless tile is on the left, top, or right hand boundary, tile is set to 0.
        for (int y = 0; y < 30; y++) {
            for (int x = 0; x < 24; x++) {
                if (x == 0 || y == 0 || x == 23)
                    blocks[y * 24 + x] = 10;
                else
                    blocks[y * 24 + x] = 0;
            }
        }

        // Load sprite
        sprTile = std::make_unique<olc::Sprite>("./Sprites/tut_tile.png");

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {
        // Erase previous frame
        Clear(olc::DARK_BLUE);

        // Draw screen
        for (int y = 0; y < 30; y++) {
            for (int x = 0; x < 24; x++) {

                switch(blocks[y * 24 + x]) {
                    
                case 0: // Do nothing
                    break;
                case 10: // Draw boundary
                    DrawSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get());
                    break;
                case 1:

                }
            }
        }

        // // Draw boundary
        // DrawLine(10, 10, ScreenWidth()-10, 10, olc::YELLOW);    // top boundary
        // DrawLine(10, 10, 10, ScreenHeight()-10, olc::YELLOW);   // LH boundary
        // DrawLine(ScreenWidth()-10, 10, ScreenWidth()-10, ScreenHeight()-10, olc::YELLOW);   // RH boundary

        // // Draw bat
        // FillRect(int(fBatPos), ScreenHeight()-20, int(fBatWidth), 10, olc::GREEN);

        // // Draw ball
        // FillCircle(vBall, 5, olc::CYAN);

        // // Handle user input
        // if (GetKey(olc::Key::LEFT).bHeld)   fBatPos -= fBatSpeed * fElapsedTime;
        // if (GetKey(olc::Key::RIGHT).bHeld)  fBatPos += fBatSpeed * fElapsedTime;

        // if (fBatPos < 11.0f)    fBatPos = 11.0f;
        // if (fBatPos + fBatWidth > float(ScreenWidth()) - 10.0f) fBatPos = float(ScreenWidth()) - 10.0f - fBatWidth;

        return true;
    }
};

int main() {
    BreakOut game;
    if (game.Construct(512, 480, 2, 2))
        game.Start();
    return 0;
}