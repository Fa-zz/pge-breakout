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
    float fBatSpeed = 250.0f;               // fBatSpeed: How fast the ball moves
    
    //olc::vf2d vBall = { 200.0f, 200.0f };   // vBall: Ball's x and y pos
    //olc::vf2d vBallVel = {200.0f, -100.0f}; // vBallVel: Velocity vector of ball
    olc::vf2d vBallPos = {0.0f, 0.0f};
    olc::vf2d vBallDir = {0.0f, 0.0f};
    float fBallSpeed = 20.0f;
    float fBallRadius = 5.0f;               // fBallRadius: 

    olc::vi2d vBlockSize = { 16,16 };       // vBlockSize: Represents the size in pixels of one tile
    std::unique_ptr<int[]> blocks;          // blocks: Array of ints, each int will hold a different value, helps us with what to draw
    
    std::unique_ptr<olc::Sprite> sprTile;

public:
    bool OnUserCreate() override {
        srand(time(NULL));
        // Start ball
        float fAngle = float(rand()) / float(RAND_MAX) * 2.0f * 3.14159f;
        fAngle = -0.4f;
        vBallDir = {cos(fAngle), sin(fAngle)};
        vBallPos = { 12.5f, 15.5f };

        blocks = std::make_unique<int[]>(24 * 30);  // Grid is initialized to contain 24x30 tiles

        // Iterates through grid.
        for (int y = 0; y < 30; y++) {
            for (int x = 0; x < 24; x++) {

                if (x == 0 || y == 0 || x == 23)
                    blocks[y * 24 + x] = 10;
                else
                    blocks[y * 24 + x] = 0;

                if (x > 2 && x <= 20 && y > 3 && y <= 5)
                    blocks[y * 24 + x] = 1;
                if (x > 2 && x <= 20 && y > 5 && y <= 7)
                    blocks[y * 24 + x] = 2;
                if (x > 2 && x <= 20 && y > 7 && y <= 9)
                    blocks[y * 24 + x] = 3;            
            }
        }

        // Load sprite
        sprTile = std::make_unique<olc::Sprite>("./Sprites/tut_tiles.png");

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {
        // Erase previous frame
        Clear(olc::DARK_BLUE);
        SetPixelMode(olc::Pixel::MASK);

        // COLLISION TESTING
        // Calculate where ball should be, if no collision
        olc::vf2d vPotentialBallPos = vBallPos + vBallDir * fBallSpeed * fElapsedTime;

        olc::vf2d vTileBallRadialDims = { fBallRadius / vBlockSize.x, fBallRadius / vBlockSize.y};

        auto TestResolveCollisionPoint = [&](const olc::vf2d& point) {
        /*
        Collision testing is as follows:

        For each midpoint of the edge of the ball (rectangle):
            Determine location in tile array
                a) If location == 0, empty space, no collision
                b) If location == 10, collision, but with wall tile
                c) Anything else, decrease array value by 1 (some tiles require more hits than others)
        */

            olc::vi2d vTestPoint = vPotentialBallPos + vTileBallRadialDims * point;
            auto& tile = blocks[vTestPoint.y * 24 + vTestPoint.x];
            if (tile == 0) {
                // Do Nothing, no collision
                return false;
            } else {
                // Ball has collided with a tile
                bool bTileHit = tile < 10;
                if (bTileHit) tile--;
                        
                // Collision response
                if (point.x == 0.0f)	
                    vBallDir.y *= -1.0f;				
                if (point.y == 0.0f)	
                    vBallDir.x *= -1.0f;
                return bTileHit;
            }
        };

        // Check all 4 corners of ball for collision
        bool bHasHitTile = false;
        bHasHitTile |= TestResolveCollisionPoint(olc::vf2d(0, -1));
        bHasHitTile |= TestResolveCollisionPoint(olc::vf2d(0, +1));
        bHasHitTile |= TestResolveCollisionPoint(olc::vf2d(-1, 0));
        bHasHitTile |= TestResolveCollisionPoint(olc::vf2d(+1, 0));

        // Artificial floor, for testing
        if (vBallPos.y > 20.0f) vBallDir.y *= -1.0f;

        // Actually update ball's position
        vBallPos += vBallDir * fBallSpeed * fElapsedTime;

        // DRAW SCREEN
        for (int y = 0; y < 30; y++) {
            for (int x = 0; x < 24; x++) {

                switch(blocks[y * 24 + x]) {

                case 0: // Empty space; nothing is drawn
                    break;
                case 10: // Draw boundary
                    DrawPartialSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get(), olc::vi2d(0, 0) * vBlockSize, vBlockSize);
                    break;
                case 1: // Draw Red block
                    DrawPartialSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get(), olc::vi2d(1, 0) * vBlockSize, vBlockSize);
                    break;
                case 2: // Draw Green block
                    DrawPartialSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get(), olc::vi2d(2, 0) * vBlockSize, vBlockSize);
                    break;
                case 3: // Draw Yellow block
                    DrawPartialSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get(), olc::vi2d(3, 0) * vBlockSize, vBlockSize);
                    break;
                }
            }
        }
        SetPixelMode(olc::Pixel::NORMAL);

        // DRAW BALL
        FillCircle(vBallPos * vBlockSize, fBallRadius, olc::CYAN);
        std::cout << "vBallPos = " << vBallPos.x << " " << vBallPos.y << std::endl;
        // vBallDir * fBallSpeed * fElapsedTime
        std::cout << "vBallDir = " << vBallDir.x << " " << vBallDir.y << std::endl;
        std::cout << "fBallSpeed = " << fBallSpeed << std::endl;
        return true;
    }
};

int main() {
    BreakOut game;
    if (game.Construct(512, 480, 2, 2))
        game.Start();
    return 0;
}