#include "game.h"
#include "raylib.h"
#include "../utils/utils.h"
#include <stdio.h>

void UpdateGame(bool *inTransition, GameScreen *currentScreen, Arrow *arrow, Vector2 mousePos) {
    if ((*arrow).direction) {
        ((*arrow).arrowFrames)++;
        if ((*arrow).arrowFrames > 30) {
            (*arrow).direction = 0;
        }
    } else {
        ((*arrow).arrowFrames)--;
        if ((*arrow).arrowFrames < 0) {
            (*arrow).direction = 1;
        }
    }
}

void DrawGame(bool *inTransition, int *fadeAlpha, Assets assets, bool *isSoundPlayed, int arrowFrames, Vector2 mousePos) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    Rectangle recPort = {0, 140, 310, 270};
    Rectangle recPier = {405, 305, 220, 125};
    Rectangle recFishShop = {740, 240, 200, 250};

    if (!(*isSoundPlayed)) {
        PlaySound(assets.morenaTropicana);
        SetSoundVolume(assets.morenaTropicana, 0.5);
        *isSoundPlayed = true;
    }
    DrawTexture(assets.backgroundMarcoZero, 0, 0, RAYWHITE);
    DrawTexture(assets.arrow, 485, 260+(arrowFrames)/5, RAYWHITE);
    DrawTexture(assets.boat, -50, 115, RAYWHITE);
    DrawTexture(assets.fishPedia, 50, 40, RAYWHITE);
    DrawTexture(assets.fishBucket, 140, 40, RAYWHITE);
    DrawTexture(assets.fishShop, 730, 220, RAYWHITE);
    DrawTexture(assets.portSign, 10, 330, RAYWHITE);
    DrawTextureEx(assets.coin, (Vector2){780, 40}, 0.0f, 0.7f, WHITE);
    DrawText("350", 858, 53, 45, BLACK);
    DrawText("350", 860, 55, 45, WHITE);

    bool isClickingPort = false;
    bool isClickingPier = false;
    bool isClickingFishShop = false;

    if (CheckCollisionPointRec(mousePos, recPort)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawTextureEx(assets.button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
        DrawText("PORTO", 79, 632, 30, WHITE);
        isClickingPort = true;
    } else {
        isClickingPort = false;
    }
    if (CheckCollisionPointRec(mousePos, recPier)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawTextureEx(assets.button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
        DrawText("PIER", 95, 632, 30, WHITE);
        isClickingPier = true;
    } else {
        isClickingPier = false;
    }
    if (CheckCollisionPointRec(mousePos, recFishShop)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawTextureEx(assets.button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
        DrawText("PEIXARIA", 65, 632, 28, WHITE);
        isClickingFishShop = true;
    } else {
        isClickingFishShop = false;
    }

    if (!isClickingFishShop && !isClickingPier && !isClickingPort) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (*inTransition) {
        DrawRectangle(0, 0, 1024, 720, Fade(BLACK, *fadeAlpha / 255.0f));
        *fadeAlpha -= 3; 
        if (*fadeAlpha <= 0) {
            *fadeAlpha = 0;
            *inTransition = false;  
        }
    }
    EndDrawing();
}
