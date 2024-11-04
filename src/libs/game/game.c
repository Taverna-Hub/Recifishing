#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "raylib.h"
#include "raymath.h"

#include "../utils/utils.h"

#include "game.h"

int cont = 0;
int entrou = 0;

void updateArrow(Arrow *arrow);
void drawElements(Assets assets, Location *location, int arrowFrames);
void fadeHandle(bool *inTransition, int *fadeAlpha);
void updateAnimationFrames(AnimationFrames *animationFrames, Assets assets, Vector2 mousePos);
int cursorHandle(Vector2 mousePos, Texture2D button, Texture2D bucket, Texture2D fishpedia, int gameFrame);

void playSound(bool *isSoundPlayed, Music sound);
void throwRod(AnimationFrames **animationFrames);
void pullRod(AnimationFrames **animationFrames, Assets assets);

void UpdateGame(bool *inTransition, GameScreen *currentScreen, Arrow *arrow, Vector2 mousePos, Assets assets, int *gameFrame, AnimationFrames **animationFrames, Location *location) {
    updateArrow(arrow);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        *gameFrame = cursorHandle(mousePos, assets.button, assets.fishBucket, assets.fishPedia, *gameFrame);
    }
    
    if (*gameFrame == PIER) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            if (entrou) {
                if ((*animationFrames)->fishmanFishing->isUsing) {
                    (*animationFrames)->fishingRod->finalX = 240;
                    (*animationFrames)->fishingRod->finalY = 350;
                    (*animationFrames)->pullingRodAnimation = 1;
                    (*animationFrames)->throwingRodAnimation = 0;
                    (*animationFrames)->fishingRod->isUsing = 1;
                    (*animationFrames)->fishmanFishing->isUsing = 0;
                    (*animationFrames)->fishmanFishing->frame = 0;
                    (*animationFrames)->fishmanHook->isUsing = 1;
                    (*animationFrames)->fishmanHook->frame = 0;
                } else {
                    (*animationFrames)->fishingRod->finalX = mousePos.x;
                    (*animationFrames)->fishingRod->finalY = mousePos.y;
                    (*animationFrames)->fishingRod->x = 240;
                    (*animationFrames)->fishingRod->y = 350;
                    (*animationFrames)->throwingRodAnimation = 1;
                    (*animationFrames)->pullingRodAnimation = 0;
                    (*animationFrames)->fishingRod->isUsing = 1;
                    (*animationFrames)->fishmanIdle->isUsing = 0;
                    (*animationFrames)->fishmanFishing->isUsing = 1;
                    (*animationFrames)->fishmanFishing->frame = 0;
                    (*animationFrames)->rodPointCount = 0; 
                }
            } else {
                entrou = 1;
            }
        }
    }
}

void DrawGame(bool *inTransition, int *fadeAlpha, Assets assets, bool *isSoundPlayed, int arrowFrames, Vector2 mousePos, int frame, AnimationFrames **animationFrames, Location *location) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    Rectangle recBackButton = {50, 620, assets.button.width, assets.button.height};

    if (frame != DEFAULT && CheckCollisionPointRec(mousePos, recBackButton)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    } else {
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
            DrawTexture(location->pier, 0, 0, RAYWHITE);

            DrawRectangle(210, 0, 367, 360, (Color){255, 0, 0, 128});
            DrawRectangle(210, 360, 367, 360, (Color){0, 255, 0, 128});
            DrawRectangle(577, 0, 367, 360, (Color){0, 0, 255, 128});
            DrawRectangle(577, 360, 367, 360, (Color){0, 155, 155, 128});

            if ((*animationFrames)->throwingRodAnimation || (*animationFrames)->fishmanFishing->isUsing) {
                throwRod(animationFrames);
            } else if ((*animationFrames)->pullingRodAnimation || (*animationFrames)->fishmanHook->isUsing) {
                pullRod(animationFrames, assets); 
            }

            updateAnimationFrames(*animationFrames, assets, mousePos);

            DrawTextureEx(assets.button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
            DrawText("VOLTAR", 65, 632, 28, WHITE);
            break;

        case FISHSHOP:
            DrawText("Peixaria", 300, 300, 28, BLACK);
            DrawTextureEx(assets.button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
            DrawText("VOLTAR", 65, 632, 28, WHITE);
            break;
        
        case DEFAULT:
            drawElements(assets, location, arrowFrames);

            free(*animationFrames);
            *animationFrames = createAnimationFrames();

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

    animationFrames->rodPointCount = 0;
    animationFrames->throwingRodAnimation = 0;
    animationFrames->pullingRodAnimation = 0;

    animationFrames->fishingRod = (Frame*)malloc(sizeof(Frame));
    animationFrames->fishingRod->frame = 0;
    animationFrames->fishingRod->direction = 0;
    animationFrames->fishingRod->isUsing = 0;
    animationFrames->fishingRod->x = 240;
    animationFrames->fishingRod->y = 350;
    animationFrames->fishingRod->finalX = 0;
    animationFrames->fishingRod->finalY = 0;
    animationFrames->fishingRod->velX = 0;
    animationFrames->fishingRod->velY = 0;

    animationFrames->fishmanHook = (Frame*)malloc(sizeof(Frame));
    animationFrames->fishmanHook->frame = 0;
    animationFrames->fishmanHook->direction = 0;
    animationFrames->fishmanHook->isUsing = 0;

    animationFrames->fishmanIdle = (Frame*)malloc(sizeof(Frame));
    animationFrames->fishmanIdle->frame = 0;
    animationFrames->fishmanIdle->direction = 0;
    animationFrames->fishmanIdle->isUsing = 1;

    animationFrames->fishmanFishing = (Frame*)malloc(sizeof(Frame));
    animationFrames->fishmanFishing->frame = 0;
    animationFrames->fishmanFishing->direction = 0;
    animationFrames->fishmanFishing->isUsing = 0;

    return animationFrames;
}

void updateAnimationFrames(AnimationFrames *animationFrames, Assets assets, Vector2 mousePos) {

    if (animationFrames->fishmanIdle->isUsing) {
        DrawTextureEx(assets.fishermanIdle[animationFrames->fishmanIdle->frame / 10], (Vector2){120, 280}, 0.0f, 3.0f, WHITE);
        animationFrames->fishmanIdle->frame = (animationFrames->fishmanIdle->frame + 1) % 40;
    } else if (animationFrames->fishmanFishing->isUsing) {
        DrawTextureEx(assets.fishermanFishing[animationFrames->fishmanFishing->frame / 10], (Vector2){120, 280}, 0.0f, 3.0f, WHITE);
        animationFrames->fishmanFishing->frame = (animationFrames->fishmanFishing->frame + 1) % 40;
    } else if (animationFrames->fishmanHook->isUsing) {
        DrawTextureEx(assets.fishermanHook[animationFrames->fishmanHook->frame / 10], (Vector2){120, 280}, 0.0f, 3.0f, WHITE);
        animationFrames->fishmanHook->frame++;
        if (animationFrames->fishmanHook->frame >= 60) {
            animationFrames->fishmanHook->isUsing = 0;
            animationFrames->fishmanIdle->isUsing = 1;
        }
    }

    if (animationFrames->fishingRod->isUsing && animationFrames->throwingRodAnimation) {
        Vector2 rodPos = {animationFrames->fishingRod->x, animationFrames->fishingRod->y};
        Vector2 targetPos = {animationFrames->fishingRod->finalX, animationFrames->fishingRod->finalY};
        
        float speed = 20.0f;
        float distance = Vector2Distance(rodPos, targetPos);

        if (distance < 10.0f) {
            animationFrames->throwingRodAnimation = 0;
        } else {
            Vector2 direction = Vector2Normalize(Vector2Subtract(targetPos, rodPos));
            Vector2 velocity = Vector2Scale(direction, speed);
            
            animationFrames->fishingRod->x += velocity.x;
            animationFrames->fishingRod->y += velocity.y;

            if (animationFrames->rodPointCount < 10000) {
                animationFrames->rodPoints[animationFrames->rodPointCount++] = rodPos;
            }
        }
    }

    if (animationFrames->fishingRod->isUsing && animationFrames->pullingRodAnimation) {
        Vector2 targetPos = {240, 350}; 
        float speed = 20.0f;

        Vector2 rodPos = {animationFrames->fishingRod->x, animationFrames->fishingRod->y};
        float distance = Vector2Distance(rodPos, targetPos);

        if (distance < 10.0f) {
            animationFrames->fishingRod->x = targetPos.x;
            animationFrames->fishingRod->y = targetPos.y;
            animationFrames->fishingRod->isUsing = 0;
            animationFrames->pullingRodAnimation = 0;
            animationFrames->rodPointCount = 0; 
        } else {
            Vector2 direction = Vector2Normalize(Vector2Subtract(targetPos, rodPos));
            Vector2 velocity = Vector2Scale(direction, speed);

            animationFrames->fishingRod->x += velocity.x;
            animationFrames->fishingRod->y += velocity.y;

            for (int i = 0; i < animationFrames->rodPointCount; i++) {
                Vector2 pointDirection = Vector2Normalize(Vector2Subtract(targetPos, animationFrames->rodPoints[i]));
                Vector2 pointVelocity = Vector2Scale(pointDirection, speed);
                animationFrames->rodPoints[i].x += pointVelocity.x;
                animationFrames->rodPoints[i].y += pointVelocity.y;
            }
        }
    }
}

void updateArrow(Arrow *arrow) {
    if (arrow->direction) {
        arrow->arrowFrames++;
        if (arrow->arrowFrames > 30) {
            arrow->direction = 0;
        }
    } else {
        arrow->arrowFrames--;
        if (arrow->arrowFrames < 0) {
            arrow->direction = 1;
        }
    }
}

int cursorHandle(Vector2 mousePos, Texture2D button, Texture2D bucket, Texture2D fishpedia, int gameFrame) {

    Rectangle recPort = {0, 140, 310, 270};
    Rectangle recPier = {405, 305, 220, 125};
    Rectangle recFishShop = {760, 240, 250, 250};
    Rectangle recBucket = {140, 40, bucket.width, bucket.height};
    Rectangle recFishpedia = {50, 40, fishpedia.width, fishpedia.height};
    Rectangle recBackButton = {50, 620, button.width / 2, button.height / 2};

    if (CheckCollisionPointRec(mousePos, recBackButton) && gameFrame != DEFAULT) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        entrou = 0;
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

void drawElements(Assets assets, Location *location, int arrowFrames) {
    DrawTexture(location->background, 0, 0, RAYWHITE);
    DrawTexture(assets.arrow, 485, 260 + arrowFrames / 5, RAYWHITE);
    DrawTexture(location->boat, -50, 115, RAYWHITE);
    DrawTexture(assets.fishPedia, 50, 40, RAYWHITE);
    DrawTexture(assets.fishBucket, 140, 40, RAYWHITE);
    DrawTexture(location->fishShop, 730, 220, RAYWHITE);
    DrawTextureEx(assets.portSign, (Vector2){30, 350}, 0.0f, 0.8f, WHITE);
    DrawTexture(location->sailor, 170, 250, RAYWHITE);
    DrawTexture(location->salesman, 860, 350, RAYWHITE);
    DrawTextureEx(assets.coin, (Vector2){780, 40}, 0.0f, 0.7f, WHITE);
    DrawText("350", 858, 57, 45, BLACK);
    DrawText("350", 860, 55, 45, WHITE);
}

Location* startLocation(LocationName locationName, Assets assets) {

    Location *location = (Location*)malloc(sizeof(Location));
    location->name = locationName;

    switch (locationName) {

        case MARCO_ZERO:

            location->background = assets.backgroundMarcoZero;
            location->boat = assets.boat;
            location->sailor = assets.sailor;
            location->salesman = assets.salesman;
            location->fishShop = assets.fishShop;
            location->pier = assets.marcoZeroPier;

            break;

        case PORTO_DE_GALINHAS:
            break;

        case FERNANDO_DE_NORONHA:
            break;

        default:
            break;
    }
    return location;
}

void throwRod(AnimationFrames **animationFrames) {

    Vector2 start;
    Vector2 end;
    for (int i = 0; i < (*animationFrames)->rodPointCount - 1; i++) {
        
        start = (*animationFrames)->rodPoints[i];
        end = (*animationFrames)->rodPoints[i + 1];

        DrawLineEx(start, end, 9.0f, BLACK);
        DrawLineEx(start, end, 5.0f, GRAY);
    }

    if ((*animationFrames)->rodPointCount > 0) {
        DrawCircleV((*animationFrames)->rodPoints[(*animationFrames)->rodPointCount - 1], 7.0f, BLACK);
        DrawCircleV((*animationFrames)->rodPoints[(*animationFrames)->rodPointCount - 1], 5.0f, ((*animationFrames)->rodPointCount > 2) ? RED : GRAY); 
    }
}

void pullRod(AnimationFrames **animationFrames, Assets assets) {

    Vector2 start;
    Vector2 end;
    int rodPointCount = (*animationFrames)->rodPointCount;

    for (int i = 0; i < rodPointCount - 1; i++) {
        
        start = (*animationFrames)->rodPoints[i];
        end = (*animationFrames)->rodPoints[i + 1];

        DrawLineEx(start, end, 9.0f, BLACK);
        DrawLineEx(start, end, 5.0f, GRAY);
    }

    if (rodPointCount > 1) {
        Vector2 tipPosition = (*animationFrames)->rodPoints[rodPointCount - 1];
        Vector2 prevPosition = (*animationFrames)->rodPoints[rodPointCount - 2];

        DrawCircleV(tipPosition, 7.0f, BLACK);
        DrawCircleV(tipPosition, 5.0f, (rodPointCount > 2) ? RED : GRAY); 

        float angle = atan2f(tipPosition.y - prevPosition.y, tipPosition.x - prevPosition.x) * (180.0f / PI);

        DrawTextureEx(assets.fish, (Vector2){tipPosition.x - assets.fish.width * 0.25f, tipPosition.y - assets.fish.height * 0.25f}, angle, 3.0f, WHITE);
    } else if (rodPointCount == 1) {
        Vector2 tipPosition = (*animationFrames)->rodPoints[rodPointCount - 1];

        DrawCircleV(tipPosition, 7.0f, BLACK);
        DrawCircleV(tipPosition, 5.0f, GRAY);

        DrawTextureEx(assets.fish, (Vector2){tipPosition.x - assets.fish.width * 0.25f, tipPosition.y - assets.fish.height * 0.25f}, 0.0f, 3.0f, WHITE);
    }
}