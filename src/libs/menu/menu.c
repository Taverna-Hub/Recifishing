#include "menu.h"
#include "raylib.h"
#include "../cleanup/cleanup.h"

void UpdateMenu(GameScreen *currentScreen, bool *inTransition, int *fadeAlpha, Vector2 mousePos, Assets assets, bool *isSoundPlayed) {
    Rectangle startButtonRect = { 337, 430, assets.startButton.width, assets.startButton.height };
    Rectangle exitButtonRect = { 337, 560, assets.exitButton.width, assets.exitButton.height };

    
    if (CheckCollisionPointRec(mousePos, startButtonRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {  
        *fadeAlpha = 255;  
        *isSoundPlayed = false;
        *currentScreen = GAME;
        StopSound(assets.anunciacao);
    }

    if (CheckCollisionPointRec(mousePos, exitButtonRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        UnloadAssets(assets);
        CloseAudioDevice();
        CloseWindow();
    }
}

void DrawMenu(GameScreen *currentScreen, Vector2 mousePos, bool inTransition, int fadeAlpha, Assets assets, bool *isSoundPlayed) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(assets.backgroundMenu, 0, 0, RAYWHITE);
    DrawTexture(assets.logoTexture, 256, -20, RAYWHITE);
    
    Rectangle startButtonRect = { 337, 430, assets.startButton.width, assets.startButton.height };
    Rectangle exitButtonRect = { 337, 560, assets.exitButton.width, assets.exitButton.height };

    if (CheckCollisionPointRec(mousePos, startButtonRect)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawTexture(assets.darkStartButton, 337, 430, RAYWHITE);
    } else {
        DrawTexture(assets.startButton, 337, 430, RAYWHITE);
    }
    if (CheckCollisionPointRec(mousePos, exitButtonRect)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawTexture(assets.darkExitButton, 337, 560, RAYWHITE);
    } else {
        DrawTexture(assets.exitButton, 337, 560, RAYWHITE);
    }

    if (!(*isSoundPlayed) && *currentScreen != GAME) {
        PlaySound(assets.anunciacao);
        *isSoundPlayed = true;
    }

    if (fadeAlpha > 0) {
        DrawRectangle(0, 0, 1024, 720, (Color){ 0, 0, 0, fadeAlpha });
    }

    EndDrawing();
}
