#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"

#include "../utils/utils.h"
#include "../init/init.h"

#include "game.h"

int cont = 0;
int entrou = 0;
int selectedQuadrant = -1;
int successfulCatch = 0;
float waitingFish = -1;
int waitingFrames = 0;
bool isMiniGaming = false;
bool showError = false;
float errorStartTime = 0.0f;
int waterFrames = 0;
int waterUpdateCounter = 0;
bool caught = false;
bool canThrow = true;

void updateArrow(Arrow *arrow);
void drawElements(Assets assets, Location *location, int arrowFrames);
void fadeHandle(bool *inTransition, int *fadeAlpha);
void updateAnimationFrames(AnimationFrames *animationFrames, Assets assets, Vector2 mousePos);
int cursorHandle(Vector2 mousePos, Texture2D button, Texture2D bucket, Texture2D fishpedia, int gameFrame);

void playSound(bool *isSoundPlayed, Music sound);
int* getSequence(int letters);
void throwRod(AnimationFrames **animationFrames);
void pullRod(AnimationFrames **animationFrames, Assets assets, int successfulCatch);
int catchSequence[5] = {KEY_W, KEY_A, KEY_S, KEY_D, KEY_F};
int currentSequenceIndex = 0;

void UpdateGame(bool *inTransition, GameScreen *currentScreen, Arrow *arrow, Arrow *arrow2, Vector2 mousePos, Assets assets, int *gameFrame, AnimationFrames **animationFrames, Location *location) {
    updateArrow(arrow);
    updateArrow(arrow2);

    Rectangle fishZone = {280, 0, 688, 720};

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        *gameFrame = cursorHandle(mousePos, assets.button, assets.fishBucket, assets.fishPedia, *gameFrame);
    }
    
    if (*gameFrame == PIER) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || successfulCatch != 0) {

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
                    waitingFrames = 0;
                    waitingFish = -1;
                    if (successfulCatch == 1) {
                        caught = true;
                    }
                    successfulCatch = 0;

                } else if (successfulCatch != 2 && CheckCollisionPointRec(mousePos, fishZone) && canThrow){
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
                    Rectangle upperLeftSquare = {210, 0, 367, 360};
                    Rectangle bottomLeftSquare = {210, 360, 367, 360};
                    Rectangle upperRightSquare = {577, 0, 367, 360};
                    Rectangle bottomRightSquare = {577, 360, 367, 360};

                    successfulCatch = 0;
                    caught = false;

                    waitingFish = (rand() % 500) + 200; 

                    if (CheckCollisionPointRec(mousePos, upperLeftSquare)) {
                        selectedQuadrant = 1;
                    } else if (CheckCollisionPointRec(mousePos, bottomLeftSquare)) {
                        selectedQuadrant = 2;
                    } else if (CheckCollisionPointRec(mousePos, upperRightSquare)) {
                        selectedQuadrant = 3;
                    } else if (CheckCollisionPointRec(mousePos, bottomRightSquare)) {
                        selectedQuadrant = 4;
                    }
                }
            } else {
                entrou = 1;
            }
        }
    }
}

void DrawGame(bool *inTransition, int *fadeAlpha, Assets assets, bool *isSoundPlayed, int arrowFrames, int arrowFrames2, Vector2 mousePos, int frame, AnimationFrames **animationFrames, Location *location) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    Rectangle recBackButton = {50, 620, assets.button.width / 2, assets.button.height / 2};
    Rectangle recArrow = {0, 340, 70, 120};
    Rectangle fishZone = {280, 0, 688, 720};

    if (canThrow) {
        printf("JOGA AI\n");
    } else {
        printf(" \n");
    }

    if ((frame != DEFAULT && frame != PIER && CheckCollisionPointRec(mousePos, recBackButton)) || 
    (frame == PIER && (CheckCollisionPointRec(mousePos, recArrow) || CheckCollisionPointRec(mousePos, fishZone) && (*animationFrames)->fishmanIdle->isUsing || (*animationFrames)->fishmanHook->isUsing))) {
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

        case PIER:
            DrawTextureEx(assets.water[waterFrames], (Vector2){0, 0}, 0.0f, 1.0f, RAYWHITE);
            DrawRectangle(0, 0, 1024, 720, (Color){0, 255, 51, 120});
            DrawTexture(location->pier, 0, 100, RAYWHITE);
            DrawTexture(location->pierRight, 0, 0, RAYWHITE);

            DrawTextureEx(assets.arrow, (Vector2){65 + arrowFrames2 / 5, 370}, 90.0f, 1.0f, RAYWHITE);

            if (waterUpdateCounter >= 13) {  
                waterFrames = (waterFrames + 1) % 10;  
                waterUpdateCounter = 0;
            } else {
                waterUpdateCounter++;
            }

            /* DrawRectangle(280, 0, 344, 360, (Color){255, 0, 0, 50});
            DrawRectangle(280, 360, 344, 360, (Color){0, 255, 0, 50});
            DrawRectangle(624, 0, 344, 360, (Color){0, 0, 255, 50});
            DrawRectangle(624, 360, 344, 360, (Color){0, 155, 155, 50}); */

            /* DrawRectangle(280, 0, 688, 720, (Color){255, 0, 0, 50}); */

            if (!(*animationFrames)->pullingRodAnimation) {
                canThrow = true;
            }

            if ((*animationFrames)->throwingRodAnimation || (*animationFrames)->fishmanFishing->isUsing) {

                throwRod(animationFrames);

                if (waitingFrames >= waitingFish) {
                    if (!isMiniGaming && !showError) {
                        DrawTexture(assets.baseButtonSpace, 200, 150, RAYWHITE);

                        if (IsKeyPressed(KEY_SPACE)) {
                            isMiniGaming = true;
                            currentSequenceIndex = 0;
                            PlaySound(assets.keyPress);
                        }
                    } else if (isMiniGaming) {
                        DrawTextureEx(assets.keyButtonBox, (Vector2){200, 150}, 0.0f, 0.8f, RAYWHITE);

                        for (int i = 0; i < sizeof(catchSequence) / sizeof(int); i++) {
                            if (i < currentSequenceIndex) {
                                DrawTextureEx(assets.baseButtonPressed, (Vector2){223 + (100 * i), 172}, 0.0f, 1.0f, WHITE);
                            } else {
                                DrawTextureEx(assets.baseButton, (Vector2){223 + (100 * i), 172}, 0.0f, 1.0f, WHITE);
                            }
                            DrawTextCodepoint(GetFontDefault(), catchSequence[i], (Vector2){251 + (100 * i), 185}, 50, WHITE);
                        }

                        int key = GetKeyPressed();
                        if (key != 0) {
                            if (key == catchSequence[currentSequenceIndex]) {
                                PlaySound(assets.keyPress);
                                currentSequenceIndex++;
                                if (currentSequenceIndex == 5) {
                                    successfulCatch = 1;
                                    currentSequenceIndex = 0;
                                    waitingFrames = 0;
                                    waitingFish = (rand() % 500) + 200;
                                    isMiniGaming = false;
                                }
                            } else {
                                PlaySound(assets.boowomp);
                                showError = true;
                                errorStartTime = GetTime();
                                isMiniGaming = false;
                            }
                        }
                    } else if (showError) {
                        DrawTextureEx(assets.keyButtonBox, (Vector2){200, 150}, 0.0f, 0.8f, RAYWHITE);

                        for (int i = 0; i < sizeof(catchSequence) / sizeof(int); i++) {
                            if (i < currentSequenceIndex) {
                                DrawTextureEx(assets.baseButtonPressed, (Vector2){223 + (100 * i), 172}, 0.0f, 1.0f, WHITE);
                                DrawTextCodepoint(GetFontDefault(), catchSequence[i], (Vector2){251 + (100 * i), 185}, 50, WHITE);
                            } else if (i == currentSequenceIndex) {
                                DrawTextureEx(assets.baseButtonFail, (Vector2){223 + (100 * i), 172}, 0.0f, 1.0f, WHITE);
                                DrawTextCodepoint(GetFontDefault(), catchSequence[i], (Vector2){251 + (100 * i), 185}, 50, WHITE);
                            } else {
                                DrawTextureEx(assets.baseButton, (Vector2){223 + (100 * i), 172}, 0.0f, 1.0f, WHITE);
                                DrawTextCodepoint(GetFontDefault(), catchSequence[i], (Vector2){251 + (100 * i), 185}, 50, WHITE);
                            }
                        }

                        if (GetTime() - errorStartTime >= 1.0f) {
                            showError = false;
                            currentSequenceIndex = 0;
                            successfulCatch = 2;
                            isMiniGaming = false;
                        }
                    }
                } else {
                    waitingFrames++;
                }
            } else if ((*animationFrames)->pullingRodAnimation || (*animationFrames)->fishmanHook->isUsing || successfulCatch != 2) {
                pullRod(animationFrames, assets, successfulCatch);
            }

            updateAnimationFrames(*animationFrames, assets, mousePos);
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

        case FISHSHOP:
            DrawText("Peixaria", 300, 300, 28, BLACK);
            DrawTextureEx(assets.button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
            DrawText("VOLTAR", 65, 632, 28, WHITE);
            break;

        case DEFAULT:
            drawElements(assets, location, arrowFrames);

            free(*animationFrames);
            *animationFrames = createAnimationFrames();

            waitingFrames = 0;
            waitingFish = -1;
            successfulCatch = 0;
            caught = false;

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
        
        float speed = 15.0f;
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
        float speed = 15.0f;

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
    Rectangle recArrow = {0, 340, 70, 120};

    if ((CheckCollisionPointRec(mousePos, recBackButton) && gameFrame != DEFAULT && gameFrame != PIER) || (gameFrame == PIER && CheckCollisionPointRec(mousePos, recArrow))) {
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
    DrawTexture(location->fishShop, 680, 228, RAYWHITE);
    DrawTextureEx(assets.portSign, (Vector2){30, 350}, 0.0f, 0.8f, WHITE);
    DrawTexture(location->sailor, 170, 250, RAYWHITE);
    DrawTexture(location->salesman, 830, 350, RAYWHITE);
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
            location->pierRight = assets.marcoZeroPierRight;

            Fish *first = NULL;

            /* insertFish(&first, "Jacaré", 75, 8, assets.marcoZeroFishes[0], MARCO_ZERO);
            insertFish(&first, "Peixe-CESAR", 50, 6, assets.marcoZeroFishes[1], MARCO_ZERO);
            insertFish(&first, "Peixe-Chico", 50, 6, assets.marcoZeroFishes[2], MARCO_ZERO);
            insertFish(&first, "Peixe-Frevo", 25, 4, assets.marcoZeroFishes[3], MARCO_ZERO);
            insertFish(&first, "Peixe-Maloka", 20, 4, assets.marcoZeroFishes[4], MARCO_ZERO);
            insertFish(&first, "Peixe-Náutico", 30, 5, assets.marcoZeroFishes[5], MARCO_ZERO);
            insertFish(&first, "Peixe-Santa", 30, 5, assets.marcoZeroFishes[6], MARCO_ZERO);
            insertFish(&first, "Peixe-Sport", 30, 5, assets.marcoZeroFishes[7], MARCO_ZERO); */

            location->firstFish = first;

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

void pullRod(AnimationFrames **animationFrames, Assets assets, int successfulCatch) {

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

        if (caught) {
            DrawTextureEx(assets.marcoZeroFishes[2], (Vector2){tipPosition.x - assets.marcoZeroFishes[2].width * 0.25f, tipPosition.y - assets.marcoZeroFishes[2].height * 0.25f}, angle, 0.4f, WHITE);
            canThrow = false;
        }
    } else if (rodPointCount == 1) {
        Vector2 tipPosition = (*animationFrames)->rodPoints[rodPointCount - 1];

        DrawCircleV(tipPosition, 7.0f, BLACK);
        DrawCircleV(tipPosition, 5.0f, GRAY);

        if (caught) {
            DrawTextureEx(assets.marcoZeroFishes[2], (Vector2){tipPosition.x - assets.marcoZeroFishes[2].width * 0.25f, tipPosition.y - assets.marcoZeroFishes[2].height * 0.25f}, 0.0f, 0.4f, WHITE);
            canThrow = false;
        }
    }
}

/* int* getSequence(marcoZeroFishes[0] marcoZeroFishes[0]) {
    int sequence[marcoZeroFishes[0].letters];

    for (int i = 0; i < marcoZeroFishes[0].letters; i++) {
        sequence[i] = (rand() % 26) + 65;
    }

    return sequence;
} */

Fish pescar(Vector2 mousePos) {

    Rectangle zone1 = {280, 0, 344, 360};
    Rectangle zone2 = {280, 360, 344, 360};
    Rectangle zone3 = {624, 0, 344, 360};
    Rectangle zone4 = {624, 360, 344, 360};

    if (CheckCollisionPointRec(mousePos, zone1)) {

    } else if ((CheckCollisionPointRec(mousePos, zone2))) {

    } else if ((CheckCollisionPointRec(mousePos, zone3))) {

    } else if ((CheckCollisionPointRec(mousePos, zone4))) {

    }

    

}

void insertFish(Fish **head, char *name, int price, int letters, Texture2D sprite, LocationName locationName) {
		
		Fish *new = (Fish *)malloc(sizeof(Fish));
		
		if (new != NULL) {
			strcpy(new->name, name);
			new->price = price;
			new->sprite = sprite;
			new->locationName = locationName;
			new->next = *head;
			new->letters = letters;
			new->prev = NULL;
			
			if (*head != NULL) {
				(*head)->prev = new;
			} 
			
			*head = new;
		}
		
	}

	void removeFish(Fish **head) {

		if (*head != NULL) {
			Fish *aux = *head;
			
			*head = (*head)->next;
			
			free(aux);
			
			if (*head != NULL) {
				(*head)->prev = NULL;
			}
		}
	}
