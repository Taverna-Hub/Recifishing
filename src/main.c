#include "raylib.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum GameScreen { 
    MENU = 0, 
    GAME = 1
    } GameScreen;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1024;
    const int screenHeight = 720;


    InitWindow(screenWidth, screenHeight, "Recifishing");

    GameScreen currentScreen = MENU;
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        Texture2D startTexture = LoadTexture("../assets/pixel-art-beach-with-coconut-trees-clouds-sky-background-retro-style-8-bit-game-ai_985124-981.png");
        Texture2D logoTexture = LoadTexture("../assets/soumteste.png");
        Texture2D startmenuButton = LoadTexture("../assets/startbuttonMenu.png");
        Texture2D exitmenuButton = LoadTexture("../assets/exitbuttonMenu.png");
        Texture2D backgroundMenu = LoadTexture("../assets/yes.png");

        Rectangle exitbutton = imageToRectangle(exitmenuButton, 337, 580);
        Rectangle startbutton = imageToRectangle(startmenuButton, 337, 450);
        Vector2 mousePos = GetMousePosition();

        if (CheckCollisionPointRec(mousePos, startbutton) == true && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) == true){
            currentScreen = GAME;
        }
        if (CheckCollisionPointRec(mousePos, exitbutton) == true && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) == true && currentScreen == MENU){
            break;
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();


            if (currentScreen == MENU){
                DrawTexture(backgroundMenu, 0, 0, RAYWHITE);
                DrawTexture(logoTexture, 256, 0, RAYWHITE);
                DrawTexture(startmenuButton, 337, 450, RAYWHITE);
                DrawTexture(exitmenuButton, 337, 580, RAYWHITE);
            } else if (currentScreen == GAME){
                ClearBackground(RAYWHITE);
            }
            ClearBackground(RAYWHITE);

        EndDrawing();

        // bool CheckCollisionPointRec(Vector2 point, Rectangle rec);   Check if point is inside rectangle
        // Rectangle exitbutton, startbutton;
        // exitbutton.x = 337;
        // exitbutton.y = 580;
        // exitbutton.height = exitmenuButton.height;
        // exitbutton.width = exitmenuButton.width;
        // startbutton.x = 337;
        // startbutton.y = 450;
        // startbutton.width = 337;

        printf("%f %f", mousePos.x, mousePos.y);


        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}