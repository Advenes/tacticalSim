#include "core/game.h"
#include "raylib.h"

int main(){
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(InitalWidth, InitalHeight, "tacticalSim");
    SetTargetFPS(60);
    srand(time(NULL));
    Game game;
    return 0;
}
