#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "libs/init/init.h"
#include "libs/menu/menu.h"
#include "libs/game/game.h"
#include "libs/cleanup/cleanup.h"

int main(void) {

    GameScreen currentScreen = MENU;

    int fadeAlpha = 0;
    bool inTransition = false;
    bool isSoundPlayed = false;  

    const int screenWidth = 1024;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Recifishing");

    InitAudioDevice();

    SetTargetFPS(60);

    Assets assets = LoadAssets();

    Vector2 mousePos = GetMousePosition();

    Arrow *arrow = createArrow();

    while (!WindowShouldClose()) {

        mousePos = GetMousePosition();

        if (currentScreen == MENU) {

            UpdateMenu(&currentScreen, &inTransition,&fadeAlpha, mousePos, assets, &isSoundPlayed);
            DrawMenu(&currentScreen, mousePos, inTransition, fadeAlpha, assets, &isSoundPlayed);

        } else if (currentScreen == GAME) {

            if (!inTransition && fadeAlpha == 255) {
                inTransition = true; 
            }
            UpdateGame(&inTransition, &currentScreen, arrow, mousePos);
            DrawGame(&inTransition, &fadeAlpha, assets, &isSoundPlayed, arrow->arrowFrames, mousePos);

        }
    }

    UnloadAssets(assets);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
