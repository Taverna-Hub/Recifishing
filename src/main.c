#include "raylib.h"
#include <stdio.h>

#include "libs/init/init.h"
#include "libs/menu/menu.h"
#include "libs/game/game.h"
#include "libs/cleanup/cleanup.h"

int main(void) {

    GameScreen currentScreen = MENU;
    bool inTransition = false;
    int fadeAlpha = 0;
    bool isSoundPlayed = false;  

    const int screenWidth = 1024;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Recifishing");
    InitAudioDevice();
    SetTargetFPS(60);
    Assets assets = LoadAssets();

    Vector2 mousePos = GetMousePosition();

    while (!WindowShouldClose()) {

        mousePos = GetMousePosition();

        if (currentScreen == MENU) {
            UpdateMenu(&currentScreen, &inTransition,&fadeAlpha, mousePos, assets, &isSoundPlayed);
            DrawMenu(&currentScreen, mousePos, inTransition, fadeAlpha, assets, &isSoundPlayed);
        }
        else if (currentScreen == GAME) {
        if (!inTransition && fadeAlpha == 255) {
                inTransition = true; 
            }
            
            UpdateGame(&inTransition, &currentScreen);
            DrawGame(&inTransition, &fadeAlpha, assets, &isSoundPlayed);
            
        }
    }

    UnloadAssets(assets);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
