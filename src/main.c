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
    SetTargetFPS(60);
    int fadeAlpha = 255;
    bool inTransition = false; 
    float time=0.0f;              // Set our game to run at 60 frames-per-second
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
        Texture2D darkstartmenuButton = LoadTexture("../assets/darkstartbuttonMenu.png");
        Texture2D exitmenuButton = LoadTexture("../assets/exitbuttonMenu.png");
        Texture2D darkexitmenuButton = LoadTexture("../assets/darkexitbuttonMenu.png");
        Texture2D backgroundMenu = LoadTexture("../assets/yes.png");
        Texture2D portSign=LoadTexture("../assets/portosign.png");
        Texture2D fishBucket = LoadTexture("../assets/fishbucket.png");
        Texture2D fishPedia = LoadTexture("../assets/fishpedia.png");
        Texture2D fishShop= LoadTexture("../assets/fishshop.png");

        Rectangle exitbutton = imageToRectangle(exitmenuButton, 337, 580);
        Rectangle startbutton = imageToRectangle(startmenuButton, 337, 450);
        Vector2 mousePos = GetMousePosition();

        if (CheckCollisionPointRec(mousePos, startbutton) == true && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) == true){
            inTransition = true;
            currentScreen = GAME;

        }
        if (CheckCollisionPointRec(mousePos, exitbutton) == true && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) == true && currentScreen == MENU){
            break;
        }
        if (inTransition) {
            fadeAlpha -= 3;  // Diminui a opacidade gradualmente

            if (fadeAlpha <= 0) {
                fadeAlpha = 0;
                inTransition = false; // Termina a transição
                currentScreen = GAME; // Troca para a tela de jogo
                fadeAlpha = 255;      // Reseta a opacidade para futuros usos
            }
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();


            if (currentScreen == MENU){
                DrawTexture(backgroundMenu, 0, 0, RAYWHITE);
                DrawTexture(logoTexture, 256, 0, RAYWHITE);
                if (CheckCollisionPointRec(mousePos, startbutton) == true){
                    DrawTexture(darkstartmenuButton, 337, 450, RAYWHITE);
                } else {
                    DrawTexture(startmenuButton, 337, 450, RAYWHITE);
                }
                if (CheckCollisionPointRec(mousePos, exitbutton) == true){
                    DrawTexture(darkexitmenuButton, 337, 580, RAYWHITE);
                } else {
                    DrawTexture(exitmenuButton, 337, 580, RAYWHITE);
                }
            } else if (currentScreen == GAME){
                ClearBackground(RAYWHITE);
                if(!inTransition){
                    time+=GetFrameTime();
                    
                    DrawTexture(fishPedia,50,40,RAYWHITE);
                    
                    if (time>=0.2f)
                    {
                        DrawTexture(fishBucket,140,40,RAYWHITE);
                    }
                    
                }
                DrawTexture(fishShop,650,200,RAYWHITE);
                DrawTexture(portSign,50,300,RAYWHITE);
            }
            ClearBackground(RAYWHITE);
             if (inTransition) {
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, fadeAlpha / 255.0f));
            }

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