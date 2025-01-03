#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "../game/game.h"
#include "../cleanup/cleanup.h"

#include "menu.h"

void fadeHandleMenu(int fadeAlpha);
void playSoundMenu(bool *isSoundPlayed, GameScreen *currentScreen, Music sound);
void buttonsHandle(Texture2D startButton, Texture2D exitButton, Texture2D darkStartButton, Texture2D darkExitButton, Vector2 mousePos);

void UpdateMenu(GameScreen *currentScreen, bool *inTransition, int *fadeAlpha, Vector2 mousePos, Assets assets, bool *isSoundPlayed) {
    Rectangle startButtonRect = { 337, 430, assets.startButton.width, assets.startButton.height };
    Rectangle exitButtonRect = { 337, 560, assets.exitButton.width, assets.exitButton.height };

    if (CheckCollisionPointRec(mousePos, startButtonRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {  
        *fadeAlpha = 255;  
        *isSoundPlayed = false;
        *currentScreen = GAME;
        StopMusicStream(assets.anunciacao);
    }

    if (CheckCollisionPointRec(mousePos, exitButtonRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        CloseAudioDevice();
        CloseWindow();
    }
}

void DrawMenu(GameScreen *currentScreen, Vector2 mousePos, bool inTransition, int fadeAlpha, Assets assets, bool *isSoundPlayed) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(assets.backgroundMenu, 0, 0, RAYWHITE);
    DrawTexture(assets.logoTexture, 256, -20, RAYWHITE);

    buttonsHandle(assets.startButton, assets.exitButton, assets.darkStartButton, assets.darkExitButton, mousePos);

    playSoundMenu(isSoundPlayed, currentScreen, assets.anunciacao);
    UpdateMusicStream(assets.anunciacao);

    fadeHandleMenu(fadeAlpha);

    EndDrawing();
}

void buttonsHandle(Texture2D startButton, Texture2D exitButton, Texture2D darkStartButton, Texture2D darkExitButton, Vector2 mousePos) {
    Rectangle startButtonRect = { 337, 430, startButton.width, startButton.height };
    Rectangle exitButtonRect = { 337, 560, exitButton.width, exitButton.height };

    bool isClickingStart = false;
    bool isClickingExit = false;

    if (CheckCollisionPointRec(mousePos, startButtonRect)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        isClickingStart = true;
        DrawTexture(darkStartButton, 337, 430, RAYWHITE);
    } else {
        isClickingStart = false;
        DrawTexture(startButton, 337, 430, RAYWHITE);
    }
    if (CheckCollisionPointRec(mousePos, exitButtonRect)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        isClickingExit = true;
        DrawTexture(darkExitButton, 337, 560, RAYWHITE);
    } else {
        isClickingExit = false;
        DrawTexture(exitButton, 337, 560, RAYWHITE);
    }

    if (!isClickingStart && !isClickingExit) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

void playSoundMenu(bool *isSoundPlayed, GameScreen *currentScreen, Music sound) {
    if (!(*isSoundPlayed) && *currentScreen != GAME) {
        PlayMusicStream(sound);
        sound.looping = true;
        *isSoundPlayed = true;
    }
    UpdateMusicStream(sound);
}

void fadeHandleMenu(int fadeAlpha) {
    if (fadeAlpha > 0) {
        DrawRectangle(0, 0, 1024, 720, (Color){ 0, 0, 0, fadeAlpha });
    }
}
