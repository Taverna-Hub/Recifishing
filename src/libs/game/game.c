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

Fishpedia *fishpediaHead = NULL;

Bucket *bucketHead = NULL;

int balance = 0;
int marcoZeroCapturedCount = 0;
int portoDeGalinhasCapturedCount = 0;
int fernandoDeNoronhaCapturedCount = 0;

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
bool alert = true;
bool ranOutOfTime = false;
bool firstGame = true;
int bucket = 0;
int fishpediaCount = 0;
FishpediaPage currentFishpediaPage = MARCO_ZERO_PAGE;
char bucketStr[20];
char fishpediaCountStr[20];

GameFrames called = DEFAULT;

int fishFrame = 0;

int catchSequence[20];
int currentSequenceIndex = 0;
Fish *hookedFish = NULL;

float gameTime = 1000000.0f;

void updateArrow(Arrow *arrow);
void drawElements(Assets assets, Location *location, int arrowFrames);
void fadeHandle(bool *inTransition, int *fadeAlpha);
void updateAnimationFrames(AnimationFrames *animationFrames, Assets assets, Vector2 mousePos);
int cursorHandle(Vector2 mousePos, Texture2D button, Texture2D bucket, Texture2D fishpedia, int gameFrame);
void createFish(Fish **head, char *name, int price, int letters, Texture2D sprite, LocationName locationName);
void insertBucket(Bucket **head, Fish *fish);
void DrawBucket(Assets assets, Vector2 mousePos);
void DrawPort(Assets assets, Location *location, Vector2 mousePos);
void DrawFishpedia(Assets assets, Location *MarcoZero, Location *PortoDeGalinhas, Location *FernandoDeNoronha, Vector2 mousePos);
void addFishToFishpedia(Fish *newFish);
void sell(Assets assets);
void insertFishpedia(Fishpedia **head, Fish *fish);
void DrawFishShop(Assets assets, Location *location, Vector2 mousePos);

void playSound(bool *isSoundPlayed, Music sound);
void updateSequence(Fish *fish);
void throwRod(AnimationFrames **animationFrames);
void pullRod(AnimationFrames **animationFrames, Assets assets, int successfulCatch, Fish* hookedFish);
Fish* pescar(Fish *head);

void UpdateGame(bool *inTransition, GameScreen *currentScreen, Arrow *arrow, Arrow *arrow2, Vector2 mousePos, Assets assets, int *gameFrame, AnimationFrames **animationFrames, Location *location) {
    updateArrow(arrow);
    updateArrow(arrow2);

    Rectangle fishZone = {280, 0, 744, 720};

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
                    isMiniGaming = false;
                    showError = false;

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

                    firstGame = false;
                    waitingFish = (rand() % 500) + 200; 

                    hookedFish = NULL;
                    currentSequenceIndex = 0;
                }
            } else {
                entrou = 1;
            }
        }
    }
}


void DrawGame(bool *inTransition, int *fadeAlpha, Assets assets, bool *isSoundPlayed, int arrowFrames, int arrowFrames2, Vector2 mousePos, int frame, AnimationFrames **animationFrames, Location *location,Location *MarcoZero, Location *PortoDeGalinhas, Location *FernandoDeNoronha) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    Rectangle recBackButton = {50, 620, assets.button.width / 2, assets.button.height / 2};
    Rectangle recArrow = {0, 340, 70, 120};
    Rectangle fishZone = {280, 0, 744, 720};
    Rectangle recBucket = {140, 40, assets.fishBucket.width, assets.fishBucket.height};
    Rectangle recFishpedia = {50, 40, assets.fishPedia.width, assets.fishPedia.height};
    Rectangle recSellButton = {525, 575, assets.sellButton.width*1.3, assets.sellButton.height*1.3};
    Rectangle yesButton = {400, 380, assets.button.width * 0.8, assets.button.height * 0.8};
    Rectangle noButton = {725, 380, assets.button.width * 0.8, assets.button.height * 0.8};

    if ((frame != DEFAULT && frame != PIER && CheckCollisionPointRec(mousePos, recBackButton)) || 
    (frame == PIER && (CheckCollisionPointRec(mousePos, recArrow) || CheckCollisionPointRec(mousePos, fishZone) && (*animationFrames)->fishmanIdle->isUsing || (*animationFrames)->fishmanHook->isUsing)) || (frame == PIER && CheckCollisionPointRec(mousePos, recBucket) || CheckCollisionPointRec(mousePos, recFishpedia)) || frame == FISHSHOP && CheckCollisionPointRec(mousePos, recSellButton) || (frame == PORT && (CheckCollisionPointRec(mousePos, yesButton) || CheckCollisionPointRec(mousePos, noButton)))) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    switch (frame) {
        case BUCKET:
            DrawBucket(assets, mousePos);
            break;

        case PIER:
            playSound(isSoundPlayed, assets.labelledejour);
            SetMusicVolume(assets.labelledejour, 0.5f);
            DrawTextureEx(assets.water[waterFrames], (Vector2){0, 0}, 0.0f, 1.0f, RAYWHITE);
            DrawRectangle(0, 0, 1024, 720, (Color){0, 255, 51, 120});
            DrawTexture(location->pier, 0, 100, RAYWHITE);
            DrawTexture(location->pierRight, 0, 0, RAYWHITE);
            DrawTexture(assets.fishPedia, 50, 40, RAYWHITE);
            DrawTexture(assets.fishBucket, 140, 40, RAYWHITE);

            if (firstGame) {
                DrawRectangle(280, 0, 744, 720, (Color){0, 255, 0, 90});
                DrawTextureEx(assets.button, (Vector2){268.25, 530}, 0.0f, 1.5f, WHITE);
                DrawText("Clique em qualquer lugar", 325, 560, 30, WHITE);
                DrawText("da", 365, 600, 30, WHITE);
                DrawText("área verde", 408, 600, 30, GREEN);  
                DrawText("para", 590, 600, 30, WHITE);
                DrawText("lançar a vara", 400, 640, 30, YELLOW);
            }

            DrawTextureEx(assets.arrow, (Vector2){65 + arrowFrames2 / 5, 370}, 90.0f, 1.0f, RAYWHITE);
            updateAnimationFrames(*animationFrames, assets, mousePos);

            if (waterUpdateCounter >= 13) {  
                waterFrames = (waterFrames + 1) % 10;  
                waterUpdateCounter = 0;
            } else {
                waterUpdateCounter++;
            } 

            if (!(*animationFrames)->pullingRodAnimation) {
                successfulCatch = 0;
                canThrow = true;
            } 

            if ((*animationFrames)->throwingRodAnimation || (*animationFrames)->fishmanFishing->isUsing) {

                throwRod(animationFrames);

                if (!hookedFish) {
                    hookedFish = pescar(location->firstFish);
                    updateSequence(hookedFish);
                    gameTime = 1000000.0f;
                    ranOutOfTime = false;
                    StopSound(assets.tictac);
                }

                if (waitingFrames >= waitingFish) {
                    if (!isMiniGaming && !showError) {
                        DrawTextureEx(assets.baseButtonSpace, (Vector2){100, 250}, 0.0f, 0.5f, RAYWHITE);

                        if (alert) {
                            PlaySound(assets.alert);
                            alert = false;
                        }

                        float timeRatio = gameTime / 1000000.0f;

                        if (timeRatio > 0.75f) {
                            DrawRectangle(100, 240, 160 * timeRatio, 10, GREEN);
                        } else if (timeRatio >= 0.5f) {
                            DrawRectangle(100, 240, 160 * timeRatio, 10, YELLOW);
                        } else if (timeRatio > 0.35f) {
                            DrawRectangle(100, 240, 160 * timeRatio, 10, ORANGE);
                        } else {
                            DrawRectangle(100, 240, 160 * timeRatio, 10, RED);
                        }

                        gameTime-= 10000;

                        if (!IsSoundPlaying(assets.tictac)) {
                            PlaySound(assets.tictac);
                            SetSoundVolume(assets.tictac, 1.0f);
                        }

                        if (gameTime <= 0) {
                            waitingFish = (rand() % 500) + 200;
                            waitingFrames = 0;
                            gameTime = 1000000.0f;
                            hookedFish = NULL;
                            alert = true;
                            StopSound(assets.tictac);
                        }

                        if (IsKeyPressed(KEY_SPACE)) {
                            isMiniGaming = true;
                            currentSequenceIndex = 0;
                            PlaySound(assets.keyPress);
                            gameTime = 1000000.0f;
                            alert = true;
                            StopSound(assets.tictac);
                        }
                    } else if (isMiniGaming) {
                        if (hookedFish->letters > 5 && hookedFish->letters < 15) {
                            DrawTextureEx(assets.keyButtonBox, (Vector2){350, 75}, 0.0f, 0.4f, RAYWHITE);
                            DrawTextureEx(assets.keyButtonBox, (Vector2){350, 150}, 0.0f, 0.4f, RAYWHITE);
                        } else {
                            DrawTextureEx(assets.keyButtonBox, (Vector2){350, 75}, 0.0f, 0.4f, RAYWHITE);
                        }

                        float timeRatio = gameTime / 1000000.0f;

                        if (timeRatio > 0.75f) {
                            DrawRectangle(350, 63, 267 * timeRatio, 10, GREEN);
                        } else if (timeRatio >= 0.5f) {
                            DrawRectangle(350, 63, 267 * timeRatio, 10, YELLOW);
                        } else if (timeRatio > 0.35f) {
                            DrawRectangle(350, 63, 267 * timeRatio, 10, ORANGE);
                        } else {
                            DrawRectangle(350, 63, 267 * timeRatio, 10, RED);
                        }

                        gameTime-= 5000;

                        if (!IsSoundPlaying(assets.tictac)) {
                            PlaySound(assets.tictac);
                            SetSoundVolume(assets.tictac, 1.0f);
                        }

                        if (gameTime <= 0) {
                            showError = true;
                            errorStartTime = GetTime();
                            isMiniGaming = false;
                            ranOutOfTime = true;
                            StopSound(assets.tictac);
                            PlaySound(assets.fail);
                        }

                        for (int i = 0; i < 10; i++) { 
                            int row = i / 5;            
                            int col = i % 5;           

                            float startX = 361.5f + (50 * col); 
                            float startY = 86 + (75 * row); 

                            if (i < hookedFish->letters) {
                                if (i < currentSequenceIndex) {
                                    DrawTextureEx(assets.baseButtonPressed, (Vector2){startX, startY}, 0.0f, 0.5f, WHITE);
                                } else {
                                    DrawTextureEx(assets.baseButton, (Vector2){startX, startY}, 0.0f, 0.5f, WHITE);
                                }
                                DrawTextCodepoint(GetFontDefault(), catchSequence[i], (Vector2){startX + 14.0f, startY + 6.5f}, 25, WHITE);
                            } else {
                                if (hookedFish->letters < 6) {
                                    if (i <= 4){
                                        DrawTextureEx(assets.emptyButton, (Vector2){startX, startY}, 0.0f, 0.5f, WHITE);
                                    }
                                } else {
                                        DrawTextureEx(assets.emptyButton, (Vector2){startX, startY}, 0.0f, 0.5f, WHITE);
                                }
                            }
                        }

                        int key = GetKeyPressed();
                        if (key != 0) {
                            if (key == catchSequence[currentSequenceIndex]) {
                                PlaySound(assets.keyPress);
                                currentSequenceIndex++;
                                if (currentSequenceIndex == hookedFish->letters) {
                                    successfulCatch = 1;
                                    addFishToFishpedia(hookedFish);
                                    insertBucket(&bucketHead, hookedFish);
                                    PlaySound(assets.success);
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
                        if (hookedFish->letters > 5 && hookedFish->letters < 15) {
                            DrawTextureEx(assets.keyButtonBox, (Vector2){350, 75}, 0.0f, 0.4f, RAYWHITE);
                            DrawTextureEx(assets.keyButtonBox, (Vector2){350, 150}, 0.0f, 0.4f, RAYWHITE);
                        } else {
                            DrawTextureEx(assets.keyButtonBox, (Vector2){350, 75}, 0.0f, 0.4f, RAYWHITE);
                        }

                        for (int i = 0; i < 10; i++) { 
                            int row = i / 5;            
                            int col = i % 5;            

                            float startX = 361.5f + (50 * col); 
                            float startY = 86 + (75 * row); 

                            if (i < hookedFish->letters) {
                                
                                if (!ranOutOfTime) {
                                    if (i < currentSequenceIndex) {
                                        DrawTextureEx(assets.baseButtonPressed, (Vector2){startX, startY}, 0.0f, 0.5f, WHITE);
                                    } else if (i == currentSequenceIndex) {
                                        DrawTextureEx(assets.baseButtonFail, (Vector2){startX, startY}, 0.0f, 0.5f, WHITE);
                                    } else {
                                        DrawTextureEx(assets.baseButton, (Vector2){startX, startY}, 0.0f, 0.5f, WHITE);
                                    }
                                } else {
                                    DrawTextureEx(assets.baseButtonFail, (Vector2){startX, startY}, 0.0f, 0.5f, WHITE);
                                }
                                
                                DrawTextCodepoint(GetFontDefault(), catchSequence[i], (Vector2){startX + 14.0f, startY + 6.5f}, 25, WHITE);
                            } else {
                                if (hookedFish->letters < 6) {
                                    if (i <= 4){
                                        DrawTextureEx(assets.emptyButton, (Vector2){startX, startY}, 0.0f, 0.5f, WHITE);
                                    }
                                } else {
                                        DrawTextureEx(assets.emptyButton, (Vector2){startX, startY}, 0.0f, 0.5f, WHITE);
                                }
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
                if (successfulCatch == 1) {
                    fishFrame++;
                }
                pullRod(animationFrames, assets, successfulCatch, hookedFish);
                StopSound(assets.tictac);
            }

            if (fishFrame <= 250 && fishFrame > 0 && !(*animationFrames)->throwingRodAnimation) {
                DrawTextureEx(assets.button, (Vector2){268.25, 530}, 0.0f, 1.5f, WHITE);
                DrawTextureEx(assets.fishFraming, (Vector2){298.25, 560}, 0.0f, 0.8f, WHITE);
                DrawTextureEx(hookedFish->sprite, (Vector2){318.25, 560}, 0.0f, 0.8f, WHITE);
                DrawText("Você pescou um", 474.25, 580, 30, WHITE);
                DrawText(hookedFish->name, 568.25 - (strlen(hookedFish->name) * 6), 620, 30, YELLOW);
                fishFrame++;
            } else {
                fishFrame = 0;
            }

            break;

        case FISHPEDIA:
            DrawFishpedia(assets,location,PortoDeGalinhas,FernandoDeNoronha, mousePos);
            break;

        case PORT:
            playSound(isSoundPlayed, assets.morenaTropicana);
            DrawPort(assets, location, mousePos);
            break;

        case FISHSHOP:
            playSound(isSoundPlayed, assets.morenaTropicana);
            DrawFishShop(assets, location, mousePos);
            break;

        case DEFAULT:
            drawElements(assets, location, arrowFrames);

            free(*animationFrames);
            *animationFrames = createAnimationFrames();

            waitingFrames = 0;
            waitingFish = -1;
            successfulCatch = 0;
            fishFrame = 0;
            caught = false;
            firstGame = true;

            cursorHandle(mousePos, assets.button, assets.fishBucket, assets.fishPedia, frame);

            playSound(isSoundPlayed, assets.morenaTropicana);

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
        if (CheckCollisionPointRec(mousePos, recArrow)) {
            called = DEFAULT;
        }
        return called;
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

    if (CheckCollisionPointRec(mousePos, recBucket) && (gameFrame == DEFAULT || gameFrame == PIER)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        called = gameFrame;
        return BUCKET;
    } 

    if (CheckCollisionPointRec(mousePos, recFishpedia) && (gameFrame == DEFAULT || gameFrame == PIER)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        called = gameFrame;
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
    if (!IsMusicStreamPlaying(sound)) {
        PlayMusicStream(sound);
        sound.looping = true;
        *isSoundPlayed = true;
        SetMusicVolume(sound, 0.8f);
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
    DrawTextureEx(assets.coin, (Vector2){810, 40}, 0.0f, 0.7f, WHITE);
    char balanceText[10];
    sprintf(balanceText, "%03d", balance);
    DrawText(balanceText, 888, 57, 45, BLACK);
    DrawText(balanceText, 890, 55, 45, WHITE);
}

Location* startLocation(LocationName locationName, Assets assets) {

    Location *location = (Location*)malloc(sizeof(Location));
    location->name = locationName;

    switch (locationName) {

        case MARCO_ZERO:

            location->background = assets.backgroundMarcoZero;
            location->backgroundBlur = assets.backgroundMarcoZeroBlur;
            location->boat = assets.boat;
            location->sailor = assets.sailor;
            location->salesman = assets.salesman;
            location->fishShop = assets.fishShop;
            location->fishShopMenu = assets.fishShopMenu;
            location->pier = assets.marcoZeroPier;

            Fish *first = NULL;

            createFish(&first, "Jacaré", 75, 10, assets.marcoZeroFishes[0], MARCO_ZERO);
            createFish(&first, "Peixe-CESAR", 60, 8, assets.marcoZeroFishes[1], MARCO_ZERO);
            createFish(&first, "Peixe-Chico", 50, 7, assets.marcoZeroFishes[2], MARCO_ZERO);
            createFish(&first, "Peixe-Frevo", 25, 4, assets.marcoZeroFishes[3], MARCO_ZERO);
            createFish(&first, "Peixe-Maloka", 25, 4, assets.marcoZeroFishes[4], MARCO_ZERO);
            createFish(&first, "Peixe-Náutico", 30, 5, assets.marcoZeroFishes[5], MARCO_ZERO);
            createFish(&first, "Peixe-Santa", 30, 5, assets.marcoZeroFishes[6], MARCO_ZERO);
            createFish(&first, "Peixe-Sport", 30, 5, assets.marcoZeroFishes[7], MARCO_ZERO);
            createFish(&first, "Saco de Pipoca", 0, 5, assets.marcoZeroFishes[8], MARCO_ZERO);
            createFish(&first, "Perna Cabeluda", 0, 5, assets.marcoZeroFishes[9], MARCO_ZERO);

            location->firstFish = first;

            break;

        case PORTO_DE_GALINHAS:
            Fish *firstPorto = NULL;

            createFish(&firstPorto, "Peixe-Chico", 50, 7, assets.portoFishes[0], PORTO_DE_GALINHAS);
            createFish(&firstPorto, "Caranguejo", 60, 6, assets.portoFishes[1], PORTO_DE_GALINHAS);
            createFish(&firstPorto, "Linguado", 40, 5, assets.portoFishes[2], PORTO_DE_GALINHAS);
            createFish(&firstPorto, "Peixe-Dourado", 55, 6, assets.portoFishes[3], PORTO_DE_GALINHAS);
            createFish(&firstPorto, "Magikarp", 30, 4, assets.portoFishes[4], PORTO_DE_GALINHAS);
            createFish(&firstPorto, "Maracatu", 25, 4, assets.portoFishes[5], PORTO_DE_GALINHAS);
            createFish(&firstPorto, "Peixe-Balão", 35, 5, assets.portoFishes[6], PORTO_DE_GALINHAS);
            createFish(&firstPorto, "Peixe-Rossi", 70, 8, assets.portoFishes[7], PORTO_DE_GALINHAS);

            location->firstFish = firstPorto;
            break;

       
        case FERNANDO_DE_NORONHA:
            Fish *firstNoronha = NULL;

            createFish(&firstNoronha, "Enguia", 100, 10, assets.noronhaFishes[0], FERNANDO_DE_NORONHA);
            createFish(&firstNoronha, "Peixe-Leão", 80, 9, assets.noronhaFishes[1], FERNANDO_DE_NORONHA);
            createFish(&firstNoronha, "Polvo", 90, 8, assets.noronhaFishes[2], FERNANDO_DE_NORONHA);
            createFish(&firstNoronha, "Salmão", 95, 9, assets.noronhaFishes[3], FERNANDO_DE_NORONHA);
            createFish(&firstNoronha, "Sardinha", 20, 3, assets.noronhaFishes[4], FERNANDO_DE_NORONHA);
            createFish(&firstNoronha, "Tubarão", 150, 12, assets.noronhaFishes[5], FERNANDO_DE_NORONHA);
            createFish(&firstNoronha, "Arraia", 120, 11, assets.noronhaFishes[6], FERNANDO_DE_NORONHA);
            createFish(&firstNoronha, "Canudo", 0, 6, assets.noronhaFishes[7], FERNANDO_DE_NORONHA);
            createFish(&firstNoronha, "Peixe-Espada", 130, 11, assets.noronhaFishes[8], FERNANDO_DE_NORONHA);
            createFish(&firstNoronha, "Atum", 110, 10, assets.noronhaFishes[9], FERNANDO_DE_NORONHA);

            location->firstFish = firstNoronha;
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

void pullRod(AnimationFrames **animationFrames, Assets assets, int successfulCatch, Fish *fish) {
    Vector2 start;
    Vector2 end;
    int rodPointCount = (*animationFrames)->rodPointCount;

    for (int i = 0; i < rodPointCount - 1; i++) {
        start = (*animationFrames)->rodPoints[i];
        end = (*animationFrames)->rodPoints[i + 1];

        DrawLineEx(start, end, 9.0f, BLACK);
        DrawLineEx(start, end, 5.0f, GRAY);
    }

    if (rodPointCount > 0) {
        Vector2 tipPosition = (*animationFrames)->rodPoints[rodPointCount - 1];

        DrawCircleV(tipPosition, 7.0f, BLACK);
        DrawCircleV(tipPosition, 5.0f, (rodPointCount > 2) ? RED : GRAY); 

        if (caught) {
            
            float fishScale = 0.5f;
            
            Vector2 previousPoint = (*animationFrames)->rodPoints[rodPointCount - 2];
            float fishAngle = atan2f(tipPosition.y - previousPoint.y, tipPosition.x - previousPoint.x) * (180.0f / PI);

            Rectangle sourceRec = (Rectangle){0, 0, fish->sprite.width, fish->sprite.height};
            Rectangle destRec = (Rectangle){tipPosition.x, tipPosition.y, fish->sprite.width * fishScale, fish->sprite.height * fishScale};
            Vector2 origin = (Vector2){0, (fish->sprite.height * fishScale) / 2};

            DrawTexturePro(fish->sprite, sourceRec, destRec, origin, fishAngle, WHITE);
            canThrow = false;
        }
    }
}

void updateSequence(Fish *fish) {

    for (int i = 0; i < 20; i++) {
        if (i <= fish->letters) {
            catchSequence[i] = (rand() % 26) + 65;
        } else {
            catchSequence[i] = -1;
        }
    } 

}

Fish* pescar(Fish *head) {

    int random = (rand() % 10) + 1;

    Fish *aux = head;
    int index = 1;

    while (aux != NULL) {
        if (index == random) {
            return aux;
        }
        aux = aux->next;
        index++;
    }

    return NULL;
}

void createFish(Fish **head, char *name, int price, int letters, Texture2D sprite, LocationName locationName) {
		
		Fish *new = (Fish *)malloc(sizeof(Fish));
		
		if (new != NULL) {
			strcpy(new->name, name);
            new->wasCaptured = false;
			new->price = price;
			new->sprite = sprite;
			new->locationName = locationName;
			new->next = *head;
			new->letters = letters;
			new->prev = NULL;

            if (!price) {
                new->isTrash = true;
            } else {
                new->isTrash = false;
            }
			
			if (*head != NULL) {
				(*head)->prev = new;
			} 

			*head = new;

		}
		
	}

void insertBucket(Bucket **head, Fish *fish) {
    if (fish == NULL || fish->isTrash || bucket >= 8) {
        return;
    }

    Bucket *newBucket = (Bucket *)malloc(sizeof(Bucket));
    if (newBucket == NULL) {
        return;
    }

    newBucket->fish = fish;
    newBucket->next = NULL;

    if (*head == NULL) {
        newBucket->prev = NULL;
        *head = newBucket;
    } else {
        Bucket *last = *head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newBucket;
        newBucket->prev = last;
    }

    bucket++;
}

void insertFishpedia(Fishpedia **head, Fish *fish) {
    if (fish == NULL || fish->isTrash || fishpediaCount >= 24) {
        return;
    }

    Fishpedia *newFishpedia = (Fishpedia *)malloc(sizeof(Fishpedia));
    if (newFishpedia == NULL) {
        return;
    }

    newFishpedia->fish = fish;
    newFishpedia->next = NULL;

    if (*head == NULL) {
        newFishpedia->prev = NULL;
        *head = newFishpedia;
    } else {
        Fishpedia *last = *head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newFishpedia;
        newFishpedia->prev = last;
    }

}

void updateLocationCaptureCount(Fish *capturedFish) {
    if (capturedFish == NULL) {
        return;
    }

    switch (capturedFish->locationName) {
        case MARCO_ZERO:
            marcoZeroCapturedCount++;
            break;
        case PORTO_DE_GALINHAS:
            portoDeGalinhasCapturedCount++;
            break;
        case FERNANDO_DE_NORONHA:
            fernandoDeNoronhaCapturedCount++;
            break;
        default:
            break;
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

void addFishToFishpedia(Fish *fish) {
    if (fish == NULL) {
        return;
    }

    Fishpedia *current = fishpediaHead;
    while (current != NULL) {
        if (strcmp(current->fish->name, fish->name) == 0) {
            fish->wasCaptured = true;
            fishpediaCount++;
            updateLocationCaptureCount(fish);
            return;
        }
        current = current->next;
    }
}

void DrawBucket(Assets assets, Vector2 mousePos) {
    DrawTexture(assets.bucketBackground, 0, 0, WHITE);
    DrawTexture(assets.fishCounter, 832, 22, WHITE);
    sprintf(bucketStr, "%d", bucket);
    DrawText(bucketStr, 910, 43, 28, BLACK);
    DrawText("/8", 925, 43, 28, BLACK);
    DrawText(bucketStr, 912, 41, 28, WHITE);
    DrawText("/8", 927, 41, 28, WHITE);
    DrawText("Balde de Pesca", 413, 42, 28, BLACK);
    DrawText("Balde de Pesca", 415, 40, 28, WHITE);

    Bucket *current = bucketHead; 
    int maxSlots = 8;

    Vector2 framePositions[8] = {
        {55, 130}, {285, 130}, {525, 130}, {765, 130},  
        {55, 380}, {285, 380}, {525, 380}, {765, 380}  
    };

    Vector2 textPositions[8] = {
        {130, 290}, {360, 290}, {605, 290}, {840, 290}, 
        {130, 540}, {360, 540}, {605, 540}, {840, 540}  
    };

    for (int i = 0; i < maxSlots; i++) {
        Vector2 framePos = framePositions[i];
        Vector2 textPos = textPositions[i];
        DrawTextureEx(assets.fishFrame, framePos, 0.0f, 1.1f, RAYWHITE);
        if (current != NULL) {
            DrawTextureEx(current->fish->sprite, (Vector2){framePos.x + 35, framePos.y}, 0.0f, 1.0f, WHITE);
            DrawText(current->fish->name, textPos.x - (strlen(current->fish->name) * 6), textPos.y, 30, WHITE);
            current = current->next;
        } 
    }

    if (CheckCollisionPointRec(mousePos, (Rectangle){50, 620, assets.button.width / 2, assets.button.height / 2})) {
        DrawTextureEx(assets.buttonDark, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
    } else {
        DrawTextureEx(assets.button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
    }
    DrawText("VOLTAR", 75, 632, 28, WHITE);
}

void DrawFishpedia(Assets assets, Location *MarcoZero, Location *PortoDeGalinhas, Location *FernandoDeNoronha, Vector2 mousePos) {
    DrawTexture(assets.fishpediaBackground, 0, 0, RAYWHITE);
    DrawTexture(assets.fishCounter, 792, 48, WHITE);
    sprintf(fishpediaCountStr, "%d", fishpediaCount);
    DrawText(fishpediaCountStr, 870, 68, 28, BLACK);
    DrawText("/24", 885, 68, 28, BLACK);
    DrawText(fishpediaCountStr, 872, 66, 28, WHITE);
    DrawText("/24", 887, 66, 28, WHITE);

    DrawText("Fishpedia", 448, 72, 28, BLACK);
    DrawText("Fishpedia", 450, 70, 28, WHITE);

     if (currentFishpediaPage == MARCO_ZERO_PAGE) {
        DrawTexture(assets.MarcoSign, 50, 56, RAYWHITE);
        sprintf(fishpediaCountStr, "%d", marcoZeroCapturedCount);
        DrawText(fishpediaCountStr, 100, 68, 28, BLACK);
        DrawText(fishpediaCountStr, 102, 66, 28, WHITE);
        DrawText("/8", 120, 68, 28, BLACK);
        DrawText("/8", 118, 70, 28, WHITE);

    } else if (currentFishpediaPage == PORTO_DE_GALINHAS_PAGE) {
        DrawTexture(assets.PortoSign, 50, 56, RAYWHITE);
        sprintf(fishpediaCountStr, "%d", portoDeGalinhasCapturedCount);
        DrawText(fishpediaCountStr, 100, 68, 28, BLACK);
        DrawText(fishpediaCountStr, 102, 66, 28, WHITE);
        DrawText("/8", 120, 68, 28, BLACK);
        DrawText("/8", 118, 70, 28, WHITE);

    } else if (currentFishpediaPage == FERNANDO_DE_NORONHA_PAGE) {
        DrawTexture(assets.NoronhaSign, 50, 56, RAYWHITE);
        sprintf(fishpediaCountStr, "%d", fernandoDeNoronhaCapturedCount);
        DrawText(fishpediaCountStr, 100, 68, 28, BLACK);
        DrawText(fishpediaCountStr, 102, 66, 28, WHITE);
        DrawText("/8", 120, 68, 28, BLACK);
        DrawText("/8", 118, 70, 28, WHITE);
    }

    Vector2 framePositions[8] = {
        {55, 130}, {275, 130}, {545, 130}, {765, 130},
        {55, 380}, {275, 380}, {545, 380}, {765, 380}
    };
    Vector2 textPositions[8] = {
        {130, 290}, {350, 290}, {620, 290}, {840, 290},
        {130, 540}, {350, 540}, {620, 540}, {840, 540}
    };

    int index = 0;
    Fish *fish = NULL;

    if (currentFishpediaPage == MARCO_ZERO_PAGE) {
        fish = MarcoZero->firstFish;
    } else if (currentFishpediaPage == PORTO_DE_GALINHAS_PAGE) {
        fish = PortoDeGalinhas->firstFish;
    } else if (currentFishpediaPage == FERNANDO_DE_NORONHA_PAGE) {
        fish = FernandoDeNoronha->firstFish;
    }

    while (fish != NULL && index < 8) {
        while (fish->isTrash)
        {
            fish=fish->next;
        }
        
        DrawTextureEx(assets.fishFrame, framePositions[index], 0.0f, 1.1f, RAYWHITE);
        if (fish->wasCaptured && !fish->isTrash) {
            DrawTextureEx(fish->sprite, (Vector2){framePositions[index].x + 40, framePositions[index].y}, 0.0f, 1.0f, WHITE);
            DrawText(fish->name, textPositions[index].x - (strlen(fish->name) * 4), textPositions[index].y, 24, BLACK);
        } else {
            if (!fish->isTrash)
            {
                DrawTextureEx(fish->sprite, (Vector2){framePositions[index].x + 40, framePositions[index].y}, 0.0f, 1.0f, BLACK);
                DrawText("?????", textPositions[index].x - 15, textPositions[index].y, 24, BLACK);
                
            }
        }
        index++;
        fish = fish->next;
    }

    
    DrawTextureEx(assets.arrow, (Vector2){870, 600}, 90.0f, 1.0f, RAYWHITE); 
    DrawTextureEx(assets.arrow, (Vector2){900, 650}, 270.0f, 1.0f, RAYWHITE); 
    DrawRectangle(810, 600, 60, 50, (Color){0, 255, 0, 100});
    DrawRectangle(900, 600, 60, 50, (Color){255, 0, 0, 100});

    if (currentFishpediaPage == MARCO_ZERO_PAGE) {
        if (CheckCollisionPointRec(mousePos, (Rectangle){810, 600, 60, 50}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentFishpediaPage = FERNANDO_DE_NORONHA_PAGE;
        } else if (CheckCollisionPointRec(mousePos, (Rectangle){900, 600, 60, 50}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentFishpediaPage = PORTO_DE_GALINHAS_PAGE;
        }

    } else if (currentFishpediaPage == PORTO_DE_GALINHAS_PAGE) {
        if (CheckCollisionPointRec(mousePos, (Rectangle){810, 600, 60, 50}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentFishpediaPage = MARCO_ZERO_PAGE;
        } else if (CheckCollisionPointRec(mousePos, (Rectangle){900, 600, 60, 50}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentFishpediaPage = FERNANDO_DE_NORONHA_PAGE;
        }

    } else if (currentFishpediaPage == FERNANDO_DE_NORONHA_PAGE) {
        if (CheckCollisionPointRec(mousePos, (Rectangle){810, 600, 60, 50}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentFishpediaPage = PORTO_DE_GALINHAS_PAGE;
        } else if (CheckCollisionPointRec(mousePos, (Rectangle){900, 600, 60, 50}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentFishpediaPage = MARCO_ZERO_PAGE;
        }
    }
    
    
    

    DrawText("VOLTAR", 75, 632, 28, WHITE);
}


void LoadFishpedia(Location MarcoZero, Location PortoDeGalinhas, Location FernandoDeNoronha) {
    Fish *currentFish;

    currentFish = MarcoZero.firstFish;
    while (currentFish != NULL) {
        insertFishpedia(&fishpediaHead, currentFish);
        currentFish = currentFish->next;
    }

    currentFish = PortoDeGalinhas.firstFish;
    while (currentFish != NULL) {
        insertFishpedia(&fishpediaHead, currentFish);
        currentFish = currentFish->next;
    }

    currentFish = FernandoDeNoronha.firstFish;
    while (currentFish != NULL) {
        insertFishpedia(&fishpediaHead, currentFish);
        currentFish = currentFish->next;
    }
}

void DrawFishShop(Assets assets, Location *location, Vector2 mousePos) {
    DrawTextureEx(location->backgroundBlur, (Vector2){-1620, -400}, 0.0f, 2.6f, WHITE);
    DrawTextureEx(location->salesman, (Vector2){10, 260}, 0.0f, 2.1f,WHITE);
    DrawTextureEx(location->fishShopMenu, (Vector2){0, -30}, 0.0f, 1.1f,WHITE);
    DrawTextureEx(assets.fishShopMenuBG, (Vector2){475, 7}, 0.0f, 1.0f, WHITE);

    DrawTextureEx(assets.fishFrame, (Vector2){555, 40}, 0.0f, 0.8f, WHITE);
    DrawTextureEx(assets.fishFrame, (Vector2){735, 40}, 0.0f, 0.8f, WHITE);

    DrawTextureEx(assets.fishFrame, (Vector2){555, 40 + 131}, 0.0f, 0.8f, WHITE);
    DrawTextureEx(assets.fishFrame, (Vector2){735, 40 + 131}, 0.0f, 0.8f, WHITE);

    DrawTextureEx(assets.fishFrame, (Vector2){555, 40 + 131*2}, 0.0f, 0.8f, WHITE);
    DrawTextureEx(assets.fishFrame, (Vector2){735, 40 + 131*2}, 0.0f, 0.8f, WHITE);

    DrawTextureEx(assets.fishFrame, (Vector2){555, 40 + 131*3}, 0.0f, 0.8f, WHITE);
    DrawTextureEx(assets.fishFrame, (Vector2){735, 40 + 131*3}, 0.0f, 0.8f, WHITE);

    DrawTextureEx(assets.coin, (Vector2){20, 20}, 0.0f, 0.7f, WHITE);
    char balanceText[10];
    sprintf(balanceText, "%03d", balance);
    DrawText(balanceText, 98, 37, 45, BLACK);
    DrawText(balanceText, 100, 35, 45, WHITE);

    int total = 0;

    Bucket *current = bucketHead;

    Vector2 framePositions[8] = {
        {545, 35}, {725, 35}, {545, 166}, {725, 166},
        {545, 297}, {725, 297}, {545, 428}, {725, 428}
    };
    Vector2 textPositions[8] = {
        {630, 148}, {810, 148}, {630, 279}, {810, 279},
        {630, 410}, {810, 410}, {630, 541}, {810, 541}
    };

    for (int i = 0; i < 8; i++) {
        Vector2 framePos = framePositions[i];
        Vector2 textPos = textPositions[i];
        if (current != NULL) {
            DrawTextureEx(current->fish->sprite, (Vector2){framePos.x + 35, framePos.y}, 0.0f, 0.8f, WHITE);
            DrawTextureEx(assets.coin, (Vector2){framePos.x + 15, framePos.y + 13}, 0.0f, 0.18f, WHITE);
            char priceText[10];
            sprintf(priceText, "%03d", current->fish->price);
            total += current->fish->price;
            DrawText(priceText, framePos.x + 40, framePos.y + 13, 19, WHITE);
            DrawText(current->fish->name, textPos.x - (strlen(current->fish->name) * 6), textPos.y, 20, WHITE);
            current = current->next;
        } 
    }

    if (CheckCollisionPointRec(mousePos, (Rectangle){525, 575, assets.sellButton.width*1.3, assets.sellButton.height*1.3})){
        DrawTextureEx(assets.sellButtonHover, (Vector2){525, 575}, 0.0f, 1.3f, WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            sell(assets);
        }
    } else {
        DrawTextureEx(assets.sellButton, (Vector2){525, 575}, 0.0f, 1.3f, WHITE);
    }
    DrawText("VENDER TUDO", 550, 605, 30, WHITE);
    DrawTextureEx(assets.coin, (Vector2){800, 50 + 555}, 0.0f, 0.3f, WHITE);
    char totalText[10];
    sprintf(totalText, "%03d", total);
    DrawText(totalText, 835, 605, 30, WHITE);
    
    if (CheckCollisionPointRec(mousePos, (Rectangle){50, 620, assets.button.width / 2, assets.button.height / 2})){
        DrawTextureEx(assets.buttonDark, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
    } else {
        DrawTextureEx(assets.button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
    }
    DrawText("VOLTAR", 75, 632, 28, WHITE);
}

void DrawPort(Assets assets, Location *location, Vector2 mousePos) {
    DrawTextureEx(location->backgroundBlur, (Vector2){0, -400}, 0.0f, 2.55f, WHITE);
    DrawTextureEx(location->boat, (Vector2){-130, 40}, 0.0f, 1.7f, WHITE);
    DrawTextureEx(location->sailor, (Vector2){100, 230}, 0.0f, 2.2f, WHITE);
    DrawTextureEx(assets.button, (Vector2){400, 160}, 0.0f, 1.8f, WHITE);

    if (CheckCollisionPointRec(mousePos, (Rectangle){400, 380, assets.button.width * 0.8, assets.button.height * 0.8})) {
        DrawTextureEx(assets.buttonDark, (Vector2){400, 380}, 0.0f, 0.8f, WHITE);
    } else {
        DrawTextureEx(assets.button, (Vector2){400, 380}, 0.0f, 0.8f, WHITE);
    }

    if (CheckCollisionPointRec(mousePos, (Rectangle){725, 380, assets.button.width * 0.8, assets.button.height * 0.8})) {
        DrawTextureEx(assets.buttonDark, (Vector2){725, 380}, 0.0f, 0.8f, WHITE);
    } else {
        DrawTextureEx(assets.button, (Vector2){725, 380}, 0.0f, 0.8f, WHITE);
    }

    DrawText("SIM", 488, 400, 45, WHITE);
    DrawText("NÃO", 810, 400, 45, WHITE);

    DrawText("VIAJAR PARA", 435, 210, 28, WHITE);
    DrawText("PORTO DE GALINHAS?", 637, 210, 28, YELLOW);
    DrawTextureEx(assets.coin, (Vector2){610, 260}, 0.0f, 0.6f, WHITE);
    DrawText("500", 680, 270, 45, WHITE);

    DrawTextureEx(assets.coin, (Vector2){810, 40}, 0.0f, 0.7f, WHITE);
    char balanceText[10];
    sprintf(balanceText, "%03d", balance);
    DrawText(balanceText, 888, 57, 45, BLACK);
    DrawText(balanceText, 890, 55, 45, WHITE);

    if (CheckCollisionPointRec(mousePos, (Rectangle){50, 620, assets.button.width / 2, assets.button.height / 2})){
        DrawTextureEx(assets.buttonDark, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
    } else {
        DrawTextureEx(assets.button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
    }
    DrawText("VOLTAR", 75, 632, 28, WHITE);
}

void sell(Assets assets) {
    bool vendeu = false;
    while (bucketHead != NULL) {
        Bucket *current = bucketHead;
        balance += current->fish->price;
        if (balance > 999) {
            balance = 999;
        }
        bucketHead = bucketHead->next;
        if (bucketHead != NULL) {
            bucketHead->prev = NULL;
        }
        free(current);
        vendeu = true;
    }
    if (vendeu) {
        PlaySound(assets.sellSound);
    }
    bucket = 0;
}
