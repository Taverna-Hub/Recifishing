#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "../utils/utils.h"

#include "game.h"

void updateArrow(Arrow *arrow);
void fadeHandle(bool *inTransition, int *fadeAlpha);
int cursorHandle(Vector2 mousePos, Texture2D button, Texture2D bucket, Texture2D fishpedia, int gameFrame);
void drawElements(Assets assets, int arrowFrames);

void playSound(bool *isSoundPlayed, Music sound);

void UpdateGame(bool *inTransition, GameScreen *currentScreen, Arrow *arrow, Vector2 mousePos, Assets assets, int *gameFrame) {
    updateArrow(arrow);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        *gameFrame = cursorHandle(mousePos, assets.button, assets.fishBucket, assets.fishPedia, *gameFrame);
    }
    
    
}

void DrawGame(bool *inTransition, int *fadeAlpha, Assets assets, bool *isSoundPlayed, int arrowFrames, Vector2 mousePos, int frame) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    switch (frame) {
        case BUCKET:
            DrawText("Balde de peixes", 300, 300, 28, BLACK);
            DrawTextureEx(assets.button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
            DrawText("VOLTAR", 65, 632, 28, WHITE);
            break;
        
        case FISHPEDIA:
            DrawText("Fishpedia", 300, 300, 28, BLACK);
            DrawTextureEx(assets.button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
            DrawText("VOLTAR", 65, 632, 28, WHITE);
            break;

        case PORT:
            DrawText("Porto", 300, 300, 28, BLACK);
            DrawTextureEx(assets.button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
            DrawText("VOLTAR", 65, 632, 28, WHITE);
            break;

        case PIER:
            DrawText("Pier", 300, 300, 28, BLACK);
            DrawTextureEx(assets.button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
            DrawText("VOLTAR", 65, 632, 28, WHITE);
            break;

        case FISHSHOP:
            DrawText("Peixaria", 300, 300, 28, BLACK);
            DrawTextureEx(assets.button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
            DrawText("VOLTAR", 65, 632, 28, WHITE);
            break;
        
        case DEFAULT:
            
            drawElements(assets, arrowFrames);

            cursorHandle(mousePos, assets.button, assets.fishBucket, assets.fishPedia, frame);

            playSound(isSoundPlayed, assets.morenaTropicana);
            UpdateMusicStream(assets.morenaTropicana);

            fadeHandle(inTransition, fadeAlpha);
            break;
    }
    

    EndDrawing();
}

Arrow* createArrow() {
    Arrow *arrow = (Arrow*)malloc(sizeof(Arrow));
    arrow->direction = 0;
    arrow->arrowFrames = 0;
    return arrow;
}

void updateArrow(Arrow *arrow) {
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

int cursorHandle(Vector2 mousePos, Texture2D button, Texture2D bucket, Texture2D fishpedia, int gameFrame) {

    Rectangle recPort = {0, 140, 310, 270};
    Rectangle recPier = {405, 305, 220, 125};
    Rectangle recFishShop = {740, 240, 200, 250};
    Rectangle recBucket = {140, 40, bucket.width, bucket.height};
    Rectangle recFishpedia = {50, 40, fishpedia.width, fishpedia.height};
    Rectangle recBackButton = {50, 620, button.width, button.height};

    bool isClickingPort = false;
    bool isClickingPier = false;
    bool isClickingBackButton = false;
    bool isClickingBucket = false;
    bool isClickingFishpedia = false;
    bool isClickingFishShop = false;

    if (CheckCollisionPointRec(mousePos, recBackButton) && gameFrame != DEFAULT) {
        
        printf("\n");
        printf("chegou");
        printf("\n");
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        isClickingBackButton = true;
        return DEFAULT;
    } else {
        isClickingBackButton = false;
    }
    if (CheckCollisionPointRec(mousePos, recPort)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawTextureEx(button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
        DrawText("PORTO", 79, 632, 30, WHITE);
        isClickingPort = true;
        return PORT;
    } else {
        isClickingPort = false;
    }
    if (CheckCollisionPointRec(mousePos, recPier)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawTextureEx(button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
        DrawText("PIER", 95, 632, 30, WHITE);
        isClickingPier = true;
        return PIER;
    } else {
        isClickingPier = false;
    }
    if (CheckCollisionPointRec(mousePos, recFishShop)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawTextureEx(button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
        DrawText("PEIXARIA", 65, 632, 28, WHITE);
        isClickingFishShop = true;
        return FISHSHOP;
    } else {
        isClickingFishShop = false;
    }
    if (CheckCollisionPointRec(mousePos, recBucket)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        isClickingBucket = true;
        return BUCKET;
    } else {
        isClickingBucket = false;
    }
    if (CheckCollisionPointRec(mousePos, recFishpedia)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        isClickingFishpedia = true;
        return FISHPEDIA;
    } else {
        isClickingFishpedia = false;
    }

    if (!isClickingFishShop && !isClickingPier && !isClickingPort && !isClickingBucket && !isClickingFishpedia && !isClickingBackButton) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        
    }
    if (CheckCollisionPointRec(mousePos,recBackButton) && gameFrame==PORT)
    {
       SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    
    return gameFrame;

}

void fadeHandle(bool *inTransition, int *fadeAlpha) {
    if (*inTransition) {
        DrawRectangle(0, 0, 1024, 720, Fade(BLACK, *fadeAlpha / 255.0f));
        *fadeAlpha -= 3; 
        if (*fadeAlpha <= 0) {
            *fadeAlpha = 0;
            *inTransition = false;  
        }
    }
}

void playSound(bool *isSoundPlayed, Music sound) {
    if (!(*isSoundPlayed)) {
        PlayMusicStream(sound);
        sound.looping = true;
        *isSoundPlayed = true;
    }
    UpdateMusicStream(sound);
}

void drawElements(Assets assets, int arrowFrames) {
    DrawTexture(assets.backgroundMarcoZero, 0, 0, RAYWHITE);
    DrawTexture(assets.arrow, 485, 260+(arrowFrames)/5, RAYWHITE);
    DrawTexture(assets.boat, -50, 115, RAYWHITE);
    DrawTexture(assets.fishPedia, 50, 40, RAYWHITE);
    DrawTexture(assets.fishBucket, 140, 40, RAYWHITE);
    DrawTexture(assets.fishShop, 730, 220, RAYWHITE);
    DrawTexture(assets.portSign, 10, 330, RAYWHITE);
    DrawTextureEx(assets.coin, (Vector2){780, 40}, 0.0f, 0.7f, WHITE);
    DrawText("350", 858, 57, 45, BLACK);
    DrawText("350", 860, 55, 45, WHITE);
}
