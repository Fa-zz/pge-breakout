#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class BreakOut : public olc::PixelGameEngine {
    public:
        BreakOut() {
            sAppName = "BreakOut Clone";
        }
    public:
        bool OnUserCreate() override {
            return true;
        }

        bool OnUserUpdate(float fElapsedTime) override {
            return true;
        }
};

int main() {
    BreakOut game;
    if (game.Construct(412, 480, 2, 2))
        game.Start();
    return 0;
}