#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "../utils/utils.h"

#include "game.h"

void updateArrow(Arrow *arrow);
void drawElements(Assets assets, int arrowFrames);
void fadeHandle(bool *inTransition, int *fadeAlpha);
void updateAnimationFrames(AnimationFrames *animationFrames, Assets assets);
int cursorHandle(Vector2 mousePos, Texture2D button, Texture2D bucket, Texture2D fishpedia, int gameFrame);

void playSound(bool *isSoundPlayed, Music sound);

void UpdateGame(bool *inTransition, GameScreen *currentScreen, Arrow *arrow, Vector2 mousePos, Assets assets, int *gameFrame, AnimationFrames **animationFrames) {
    updateArrow(arrow);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        *gameFrame = cursorHandle(mousePos, assets.button, assets.fishBucket, assets.fishPedia, *gameFrame);
    }
    
    if (*gameFrame == PIER) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            if ((*animationFrames)->fishmanFishing->isUsing) {
                (*animationFrames)->fishmanFishing->isUsing = 0;
                (*animationFrames)->fishmanFishing->frame = 0;
                (*animationFrames)->fishmanHook->isUsing = 1;
                (*animationFrames)->fishmanHook->frame = 0;
            } else {
                (*animationFrames)->fishmanIdle->isUsing = 0;
                (*animationFrames)->fishmanFishing->isUsing = 1;
                (*animationFrames)->fishmanFishing->frame = 0;
            }
        }
    }
}

void DrawGame(bool *inTransition, int *fadeAlpha, Assets assets, bool *isSoundPlayed, int arrowFrames, Vector2 mousePos, int frame, AnimationFrames **animationFrames) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    printf("GAME\n");
    Rectangle recBackButton = {50, 620, assets.button.width, assets.button.height};

    if (frame!=DEFAULT && CheckCollisionPointRec(mousePos,recBackButton))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

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
            DrawTexture(assets.marcoZeroPier, 0, 0, RAYWHITE);

            updateAnimationFrames(*animationFrames, assets);

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

AnimationFrames* createAnimationFrames() {
    AnimationFrames *animationFrames = (AnimationFrames*)malloc(sizeof(AnimationFrames));

    animationFrames->fishmanHook = (Frames*)malloc(sizeof(Frames));
    animationFrames->fishmanHook->frame = 0;
    animationFrames->fishmanHook->direction = 0;
    animationFrames->fishmanHook->isUsing = 0;

    animationFrames->fishmanIdle = (Frames*)malloc(sizeof(Frames));
    animationFrames->fishmanIdle->frame = 0;
    animationFrames->fishmanIdle->direction = 0;
    animationFrames->fishmanIdle->isUsing = 1;

    animationFrames->fishmanFishing = (Frames*)malloc(sizeof(Frames));
    animationFrames->fishmanFishing->frame = 0;
    animationFrames->fishmanFishing->direction = 0;
    animationFrames->fishmanFishing->isUsing = 1;

    return animationFrames;
}

void updateAnimationFrames(AnimationFrames *animationFrames, Assets assets) {

    if (animationFrames->fishmanIdle->isUsing) {
        DrawTextureEx(assets.fishermanIdle[animationFrames->fishmanIdle->frame / 10], (Vector2){120, 280}, 0.0f, 3.0f, WHITE);
        if (!animationFrames->fishmanIdle->direction) {
            animationFrames->fishmanIdle->frame--;
            if (animationFrames->fishmanIdle->frame <= 0) {
                animationFrames->fishmanIdle->frame = 0;
                animationFrames->fishmanIdle->direction = 1;
            }
        } else {
            animationFrames->fishmanIdle->frame++;
            if (animationFrames->fishmanIdle->frame >= 40) {
                animationFrames->fishmanIdle->frame = 39;
                animationFrames->fishmanIdle->direction = 0;
            }
        }
    } else if (animationFrames->fishmanFishing->isUsing) {
        DrawTextureEx(assets.fishermanFishing[animationFrames->fishmanFishing->frame / 10], (Vector2){120, 280}, 0.0f, 3.0f, WHITE);
        if (!animationFrames->fishmanFishing->direction) {
            animationFrames->fishmanFishing->frame--;
            if (animationFrames->fishmanFishing->frame <= 0) {
                animationFrames->fishmanFishing->frame = 0;
                animationFrames->fishmanFishing->direction = 1;
            }
        } else {
            animationFrames->fishmanFishing->frame++;
            if (animationFrames->fishmanFishing->frame >= 40) {
                animationFrames->fishmanFishing->frame = 39;
                animationFrames->fishmanFishing->direction = 0;
            }
        }
    } else if (animationFrames->fishmanHook->isUsing) {
        DrawTextureEx(assets.fishermanHook[animationFrames->fishmanHook->frame / 10], (Vector2){120, 280}, 0.0f, 3.0f, WHITE);
        animationFrames->fishmanHook->frame++;
        if (animationFrames->fishmanHook->frame >= 60) {
            animationFrames->fishmanHook->isUsing = 0;
            animationFrames->fishmanIdle->isUsing = 1;
        }
    } 
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

    if (CheckCollisionPointRec(mousePos, recBackButton) && gameFrame != DEFAULT) {

        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

        return DEFAULT;
    } 

    if (CheckCollisionPointRec(mousePos, recPort) && gameFrame == DEFAULT) {
        
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawTextureEx(button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
        DrawText("PORTO", 79, 632, 30, WHITE);
        return PORT;
    }

    if (CheckCollisionPointRec(mousePos, recPier) && gameFrame == DEFAULT) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawTextureEx(button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
        DrawText("PIER", 95, 632, 30, WHITE);
        return PIER;
    } 

    if (CheckCollisionPointRec(mousePos, recFishShop) && gameFrame == DEFAULT) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        DrawTextureEx(button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
        DrawText("PEIXARIA", 65, 632, 28, WHITE);

        return FISHSHOP;
    } 

    if (CheckCollisionPointRec(mousePos, recBucket) && gameFrame == DEFAULT) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

        return BUCKET;
    } 

    if (CheckCollisionPointRec(mousePos, recFishpedia) && gameFrame == DEFAULT) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

        return FISHPEDIA;
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
    DrawTextureEx(assets.portSign, (Vector2){30, 350}, 0.0f, 0.8f, WHITE);
    DrawTexture(assets.sailor, 170, 250, RAYWHITE);
    DrawTextureEx(assets.coin, (Vector2){780, 40}, 0.0f, 0.7f, WHITE);
    DrawText("350", 858, 57, 45, BLACK);
    DrawText("350", 860, 55, 45, WHITE);
}
