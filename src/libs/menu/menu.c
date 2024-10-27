#include "menu.h"
#include "raylib.h"

void UpdateMenu(GameScreen *currentScreen, bool *inTransition, Vector2 mousePos, Assets assets, bool *isSoundPlayed) {
    Rectangle startButtonRect = { 337, 430, assets.startButton.width, assets.startButton.height };
    Rectangle exitButtonRect = { 337, 560, assets.exitButton.width, assets.exitButton.height };

    if (CheckCollisionPointRec(mousePos, startButtonRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        *inTransition = true;
        *currentScreen = GAME;
        StopSound(assets.anunciacao);
        *isSoundPlayed = false;

    }
    if (CheckCollisionPointRec(mousePos, exitButtonRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        *currentScreen = -1;
    }
}

void DrawMenu(Vector2 mousePos, bool inTransition, int fadeAlpha, Assets assets, bool *isSoundPlayed) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(assets.backgroundMenu, 0, 0, RAYWHITE);
    DrawTexture(assets.logoTexture, 256, -20, RAYWHITE);
    
    Rectangle startButtonRect = { 337, 430, assets.startButton.width, assets.startButton.height };
    Rectangle exitButtonRect = { 337, 560, assets.exitButton.width, assets.exitButton.height };

    if (CheckCollisionPointRec(mousePos, startButtonRect)) {
        DrawTexture(assets.darkStartButton, 337, 430, RAYWHITE);
    } else {
        DrawTexture(assets.startButton, 337, 430, RAYWHITE);
    }
    if (CheckCollisionPointRec(mousePos, exitButtonRect)) {
        DrawTexture(assets.darkExitButton, 337, 560, RAYWHITE);
    } else {
        DrawTexture(assets.exitButton, 337, 560, RAYWHITE);
    }

    if (!(*isSoundPlayed)) {
        PlaySound(assets.anunciacao);
        *isSoundPlayed = true;
    }

    EndDrawing();
}
