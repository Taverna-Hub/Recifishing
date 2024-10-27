#include "game.h"
#include "raylib.h"
#include "../utils/utils.h"

void UpdateGame(bool *inTransition, GameScreen *currentScreen) {
    if (*inTransition) {
        *inTransition = false;
    }
}

void DrawGame(bool inTransition, int fadeAlpha, Assets assets, bool *isSoundPlayed) {
    BeginDrawing();

    if (!(*isSoundPlayed)) {
        PlaySound(assets.morenaTropicana);
        *isSoundPlayed = true;
    }

    ClearBackground(RAYWHITE);
    DrawTexture(assets.fishPedia, 50, 40, RAYWHITE);
    DrawTexture(assets.fishBucket, 140, 40, RAYWHITE);
    DrawTexture(assets.fishShop, 650, 200, RAYWHITE);
    DrawTexture(assets.portSign, 50, 300, RAYWHITE);
    
    if (inTransition) {
        DrawRectangle(0, 0, 1024, 720, Fade(BLACK, fadeAlpha / 255.0f));
    }

    EndDrawing();
}
