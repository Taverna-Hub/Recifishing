#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"

#include "../game/game.h"
#include "../init/init.h"

Fish *hookedFish = NULL;
Fish *marcoZeroFishList = NULL;
Fish *portoDeGalinhasFishList = NULL;
Fish *fernandoDeNoronhaFishList = NULL;

GameFrames calledGameFrame = DEFAULT;

Location *nextLocation = NULL;

Bucket *bucketHead = NULL;

Fishpedia *fishpediaHead = NULL;
FishpediaPage currentFishpediaPage = MARCO_ZERO_PAGE;

bool alert = true;
bool caught = false;
bool canThrow = true;
bool firstGame = true;
bool showError = false;
bool sharkCaught = false;
bool isMiniGaming = false;
bool ranOutOfTime = false;
bool visitedNoronha = false;
bool isTransitioning = false;

int cont = 0;
int entrou = 0;
int bucket = 0;
int balance = 0;
int fadeAlpha = 0;
int fishFrame = 0;
int waterFrames = 0;
int catchSequence[20];
int waitingFrames = 0;
int fishpediaCount = 0;
int successfulCatch = 0;
int selectedQuadrant = -1;
int waterUpdateCounter = 0;
int currentSequenceIndex = 0;
int marcoZeroCapturedCount = 0;
int portoDeGalinhasCapturedCount = 0;
int fernandoDeNoronhaCapturedCount = 0;

float waitingFish = -1;
float errorStartTime = 0.0f;
float gameTime = 1000000.0f;

char bucketStr[20];
char fishpediaCountStr[20];

Fish* pescar(Fish *head);
Fish* getSharkFish();

Location* startLocation(LocationName locationName, Assets assets);

int cursorHandle(Vector2 mousePos, Texture2D button, Texture2D bucket, Texture2D fishpedia, int gameFrame);

void updateWaterFrames();
void sell(Assets assets);
void updateArrow(Arrow *arrow);
void updateSequence(Fish *fish);
void fishingMiniGame(Assets assets);
void spaceKeyMiniGame(Assets assets);
void addFishToFishpedia(Fish *newFish);
void showMiniGameMistake(Assets assets);
void sortFishListByDifficulty(Fish **head);
void insertBucket(Bucket **head, Fish *fish);
void DrawBucket(Assets assets, Vector2 mousePos);
void playSound(bool *isSoundPlayed, Music sound);
void throwRod(AnimationFrames **animationFrames);
void insertFishpedia(Fishpedia **head, Fish *fish);
void fadeHandle(bool *inTransition, int *fadeAlpha);
void DrawFishpedia(Assets assets, Vector2 mousePos);
void resetGameStates(AnimationFrames **animationFrames);
void DrawPort(Assets assets, Location *location, Vector2 mousePos);
void drawElements(Assets assets, Location *location, int arrowFrames);
void DrawFishShop(Assets assets, Location *location, Vector2 mousePos);
void setHookedFish(Assets assets, Location *location, Vector2 mousePos);
void showCatchedFishAlert(Assets assets, AnimationFrames **animationFrames);
void DrawPier(Assets assets, Location *location, Vector2 mousePos, int arrowFrames2);
void updateAnimationFrames(AnimationFrames *animationFrames, Assets assets, Vector2 mousePos);
void updateHover(int frame, Vector2 mousePos, AnimationFrames *animationFrames, Assets assets);
void pullRod(AnimationFrames **animationFrames, Assets assets, int successfulCatch, Fish* hookedFish);
void createFish(Fish **head, char *name, int price, int letters, Texture2D sprite, LocationName locationName);
bool isHoveringOverInteractiveArea(int frame, Vector2 mousePos, AnimationFrames *animationFrames, Assets assets);

void UpdateGame(bool *inTransition, GameScreen *currentScreen, Arrow *arrow, Arrow *arrow2, Vector2 mousePos, Assets assets, int *gameFrame, AnimationFrames **animationFrames, Location *location, int *fadeAlpha) {
    updateArrow(arrow);
    updateArrow(arrow2);
    Rectangle fishZone = {280, 0, 744, 720};

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        *gameFrame = cursorHandle(mousePos, assets.button, assets.fishBucket, assets.fishPedia, *gameFrame);
    }

    if (*gameFrame == PORT && !isTransitioning) {
        Rectangle firstButtonRec = {400, 380, assets.button.width * 0.8f, assets.button.height * 0.8f};
        Rectangle secondButtonRec = {725, 380, assets.button.width * 0.8f, assets.button.height * 0.8f};

        if (location->name == MARCO_ZERO) {
            if (visitedNoronha) {
                if (CheckCollisionPointRec(mousePos, firstButtonRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    nextLocation = startLocation(PORTO_DE_GALINHAS, assets);
                    isTransitioning = true;
                } else if (CheckCollisionPointRec(mousePos, secondButtonRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    nextLocation = startLocation(FERNANDO_DE_NORONHA, assets);
                    isTransitioning = true;
                }
            } else {
                if (CheckCollisionPointRec(mousePos, firstButtonRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && balance >= 350) {
                    balance -= 350;
                    nextLocation = startLocation(PORTO_DE_GALINHAS, assets);
                    isTransitioning = true;
                }
            }
        } else if (location->name == PORTO_DE_GALINHAS) {
            if (visitedNoronha) {
                if (CheckCollisionPointRec(mousePos, firstButtonRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    nextLocation = startLocation(MARCO_ZERO, assets);
                    isTransitioning = true;
                } else if (CheckCollisionPointRec(mousePos, secondButtonRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    nextLocation = startLocation(FERNANDO_DE_NORONHA, assets);
                    isTransitioning = true;
                }
            } else {
                if (CheckCollisionPointRec(mousePos, firstButtonRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && balance >= 800) {
                    balance -= 800;
                    visitedNoronha = true;
                    nextLocation = startLocation(FERNANDO_DE_NORONHA, assets);
                    isTransitioning = true;
                }
            }
        } else if (location->name == FERNANDO_DE_NORONHA) {
            if (CheckCollisionPointRec(mousePos, firstButtonRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                nextLocation = startLocation(MARCO_ZERO, assets);
                isTransitioning = true;
            } else if (CheckCollisionPointRec(mousePos, secondButtonRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                nextLocation = startLocation(PORTO_DE_GALINHAS, assets);
                isTransitioning = true;
            }
        }

        if (isTransitioning) {
            *fadeAlpha = 255;
            *inTransition = true;
            *gameFrame = DEFAULT;
            if (nextLocation != NULL) {
                *location = *nextLocation;
                nextLocation = NULL;
            }
        }
    }

    if (isTransitioning) {
        *fadeAlpha -= 3;
        if (*fadeAlpha <= 0) {
            *fadeAlpha = 0;
            isTransitioning = false;
            *inTransition = false;
        }
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
                } else if (successfulCatch != 2 && CheckCollisionPointRec(mousePos, fishZone) && canThrow) {
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

void DrawGame(bool *inTransition, int *fadeAlpha, Assets assets, bool *isSoundPlayed, int arrowFrames, int arrowFrames2, Vector2 mousePos, int frame, AnimationFrames **animationFrames, Location *location) {

    BeginDrawing();
    ClearBackground(RAYWHITE);

    updateHover(frame, mousePos, *animationFrames, assets);

    switch (frame) {
        case BUCKET:

            if (calledGameFrame == DEFAULT) {
                playSound(isSoundPlayed,location->defaultMusic);
            } else if (calledGameFrame == PIER) {
                playSound(isSoundPlayed,location->fishingMusic);
            }  

            DrawBucket(assets, mousePos);

            break;

        case PIER:

            playSound(isSoundPlayed, location->fishingMusic);

            DrawPier(assets, location, mousePos, arrowFrames2);

            updateWaterFrames();

            if (!(*animationFrames)->pullingRodAnimation) {
                successfulCatch = 0;
                canThrow = true;
            }

            if ((*animationFrames)->throwingRodAnimation || (*animationFrames)->fishmanFishing->isUsing) {

                throwRod(animationFrames);

                setHookedFish(assets, location, mousePos);

                if (waitingFrames >= waitingFish) {

                    if (!isMiniGaming && !showError) {
                        
                        spaceKeyMiniGame(assets);

                    } else if (isMiniGaming) {

                        fishingMiniGame(assets);

                    } else if (showError) {
                        
                        showMiniGameMistake(assets);

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

            updateAnimationFrames(*animationFrames, assets, mousePos);

            showCatchedFishAlert(assets, animationFrames);

            break;

        case FISHPEDIA:

            if (calledGameFrame == DEFAULT) {
                playSound(isSoundPlayed,location->defaultMusic);
            } else if (calledGameFrame == PIER) {
                playSound(isSoundPlayed,location->fishingMusic);
            }

            DrawFishpedia(assets, mousePos);

            break;

        case PORT:

            playSound(isSoundPlayed, location->defaultMusic);
            DrawPort(assets, location, mousePos);

            break;

        case FISHSHOP:

            playSound(isSoundPlayed, location->defaultMusic);
            DrawFishShop(assets, location, mousePos);

            break;

        case DEFAULT:

            drawElements(assets, location, arrowFrames);

            resetGameStates(animationFrames);

            cursorHandle(mousePos, assets.button, assets.fishBucket, assets.fishPedia, frame);

            playSound(isSoundPlayed, location->defaultMusic);

            fadeHandle(inTransition, fadeAlpha);

            break;
    }

    if (*inTransition || isTransitioning) {
        DrawRectangle(0, 0, 1024, 720, Fade(BLACK, (*fadeAlpha) / 255.0f));
    }

    EndDrawing();
}

bool isHoveringOverInteractiveArea(int frame, Vector2 mousePos, AnimationFrames *animationFrames, Assets assets) {
    Rectangle recBackButton = {50, 620, assets.button.width / 2, assets.button.height / 2};
    Rectangle recArrow = {0, 340, 70, 120};
    Rectangle fishZone = {280, 0, 744, 720};
    Rectangle recBucket = {140, 40, assets.fishBucket.width, assets.fishBucket.height};
    Rectangle recFishpedia = {50, 40, assets.fishPedia.width, assets.fishPedia.height};
    Rectangle recSellButton = {525, 575, assets.sellButton.width * 1.3, assets.sellButton.height * 1.3};
    Rectangle yesButton = {400, 380, assets.button.width * 0.8, assets.button.height * 0.8};
    Rectangle noButton = {725, 380, assets.button.width * 0.8, assets.button.height * 0.8};
    Rectangle leftArrow = {810, 600, 60, 50};
    Rectangle rightArrow = {900, 600, 60, 50};

    return 
        (frame != DEFAULT && frame != PIER && CheckCollisionPointRec(mousePos, recBackButton)) ||
        (frame == PIER && 
            (CheckCollisionPointRec(mousePos, recArrow) || 
            (CheckCollisionPointRec(mousePos, fishZone) && animationFrames->fishmanIdle->isUsing) || 
            animationFrames->fishmanHook->isUsing)) ||
        (frame == PIER && 
            (CheckCollisionPointRec(mousePos, recBucket) || 
            CheckCollisionPointRec(mousePos, recFishpedia))) ||
        (frame == FISHSHOP && CheckCollisionPointRec(mousePos, recSellButton)) ||
        (frame == PORT && 
            (CheckCollisionPointRec(mousePos, yesButton) || 
            CheckCollisionPointRec(mousePos, noButton))) ||
        (frame == FISHPEDIA && 
            (CheckCollisionPointRec(mousePos, leftArrow) || 
            CheckCollisionPointRec(mousePos, rightArrow)));
}

void updateHover(int frame, Vector2 mousePos, AnimationFrames *animationFrames, Assets assets) {
    if (isHoveringOverInteractiveArea(frame, mousePos, animationFrames, assets)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

Fish* getSharkFish() {
    Fish *temp = fernandoDeNoronhaFishList; // Percorre a lista de peixes de Fernando de Noronha
    while (temp != NULL) {
        if (strcmp(temp->name, "Tubarão") == 0) { // Verifica se o peixe é um "Tubarão"
            return temp;
        }
        temp = temp->next; // Avança para o próximo peixe na lista
    }
    return NULL; // Retorna NULL se não encontrar o "Tubarão"
}

Arrow* createArrow() {
    Arrow *arrow = (Arrow*)malloc(sizeof(Arrow));
    arrow->direction = 0;
    arrow->arrowFrames = 0;
    return arrow;
}

// Inicializa as listas de peixes para cada localidade com diferentes características e dificuldades
void initializeFishLists(Assets assets) {
    
    // Cria peixes para o local "Marco Zero"
    createFish(&marcoZeroFishList, "Jacaré", 75, 10, assets.marcoZeroFishes[0], MARCO_ZERO);
    createFish(&marcoZeroFishList, "Peixe-CESAR", 60, 8, assets.marcoZeroFishes[1], MARCO_ZERO);
    createFish(&marcoZeroFishList, "Saco de Pipoca", 0, 5, assets.marcoZeroFishes[8], MARCO_ZERO);
    createFish(&marcoZeroFishList, "Peixe-Chico", 50, 7, assets.marcoZeroFishes[2], MARCO_ZERO);
    createFish(&marcoZeroFishList, "Peixe-Frevo", 25, 4, assets.marcoZeroFishes[3], MARCO_ZERO);
    createFish(&marcoZeroFishList, "Peixe-Maloka", 25, 4, assets.marcoZeroFishes[4], MARCO_ZERO);
    createFish(&marcoZeroFishList, "Peixe-Náutico", 30, 5, assets.marcoZeroFishes[5], MARCO_ZERO);
    createFish(&marcoZeroFishList, "Perna Cabeluda", 0, 5, assets.marcoZeroFishes[9], MARCO_ZERO);
    createFish(&marcoZeroFishList, "Peixe-Santa", 30, 5, assets.marcoZeroFishes[6], MARCO_ZERO);
    createFish(&marcoZeroFishList, "Peixe-Sport", 30, 5, assets.marcoZeroFishes[7], MARCO_ZERO);
    sortFishListByDifficulty(&marcoZeroFishList);

    // Cria peixes para o local "Porto de Galinhas"
    createFish(&portoDeGalinhasFishList, "Peixe-Galinha", 120, 10, assets.portoFishes[0], PORTO_DE_GALINHAS);
    createFish(&portoDeGalinhasFishList, "Caranguejo", 75, 4, assets.portoFishes[1], PORTO_DE_GALINHAS);
    createFish(&portoDeGalinhasFishList, "Heineken", 0, 6, assets.portoFishes[9], PORTO_DE_GALINHAS);
    createFish(&portoDeGalinhasFishList, "Linguado", 80, 5, assets.portoFishes[2], PORTO_DE_GALINHAS);
    createFish(&portoDeGalinhasFishList, "Peixe-Dourado", 80, 5, assets.portoFishes[3], PORTO_DE_GALINHAS);
    createFish(&portoDeGalinhasFishList, "Magikarp", 90, 6, assets.portoFishes[4], PORTO_DE_GALINHAS);
    createFish(&portoDeGalinhasFishList, "Maracatu", 100, 8, assets.portoFishes[5], PORTO_DE_GALINHAS);
    createFish(&portoDeGalinhasFishList, "CD Quebrado", 0, 5, assets.portoFishes[8], PORTO_DE_GALINHAS);
    createFish(&portoDeGalinhasFishList, "Peixe-Balão", 90, 6, assets.portoFishes[6], PORTO_DE_GALINHAS);
    createFish(&portoDeGalinhasFishList, "Peixe-Rossi", 100, 8, assets.portoFishes[7], PORTO_DE_GALINHAS);
    sortFishListByDifficulty(&portoDeGalinhasFishList);

    // Cria peixes para o local "Fernando de Noronha"
    createFish(&fernandoDeNoronhaFishList, "Enguia", 200, 6, assets.noronhaFishes[0], FERNANDO_DE_NORONHA);
    createFish(&fernandoDeNoronhaFishList, "Peixe-Leão", 250, 8, assets.noronhaFishes[1], FERNANDO_DE_NORONHA);
    createFish(&fernandoDeNoronhaFishList, "Canudo", 0, 6, assets.noronhaFishes[7], FERNANDO_DE_NORONHA);
    createFish(&fernandoDeNoronhaFishList, "Polvo", 200, 6, assets.noronhaFishes[2], FERNANDO_DE_NORONHA);
    createFish(&fernandoDeNoronhaFishList, "Salmão", 150, 5, assets.noronhaFishes[3], FERNANDO_DE_NORONHA);
    createFish(&fernandoDeNoronhaFishList, "Sardinha", 120, 4, assets.noronhaFishes[4], FERNANDO_DE_NORONHA);
    createFish(&fernandoDeNoronhaFishList, "Tubarão", 999, 15, assets.noronhaFishes[5], FERNANDO_DE_NORONHA);
    createFish(&fernandoDeNoronhaFishList, "Arraia", 250, 8, assets.noronhaFishes[6], FERNANDO_DE_NORONHA);
    createFish(&fernandoDeNoronhaFishList, "Saco de Lixo", 0, 5, assets.noronhaFishes[10], FERNANDO_DE_NORONHA);
    createFish(&fernandoDeNoronhaFishList, "Peixe-Espada", 300, 10, assets.noronhaFishes[8], FERNANDO_DE_NORONHA);
    createFish(&fernandoDeNoronhaFishList, "Atum", 150, 5, assets.noronhaFishes[9], FERNANDO_DE_NORONHA);
    sortFishListByDifficulty(&fernandoDeNoronhaFishList);
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
        Vector2 rodPos = {animationFrames->fishingRod->x-20, animationFrames->fishingRod->y+10};
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
        Vector2 targetPos = {220, 360};
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
    Rectangle recNoButton = {725, 380, button.width*0.8, button.height*0.8};

    if ((CheckCollisionPointRec(mousePos, recBackButton) && gameFrame != DEFAULT && gameFrame != PIER) || (gameFrame == PIER && CheckCollisionPointRec(mousePos, recArrow)) || (gameFrame == PORT && CheckCollisionPointRec(mousePos, recNoButton) && !visitedNoronha)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        entrou = 0;
        if (CheckCollisionPointRec(mousePos, recArrow)) {
            calledGameFrame = DEFAULT;
        }
        return calledGameFrame;
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
        calledGameFrame = gameFrame;
        return BUCKET;
    }

    if (CheckCollisionPointRec(mousePos, recFishpedia) && (gameFrame == DEFAULT || gameFrame == PIER)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        calledGameFrame = gameFrame;
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
    DrawTextureEx(assets.portSign, (Vector2){30, 350}, 0.0f, 0.8f, WHITE);

    DrawTexture(location->sailor, 170, 250, RAYWHITE);

    if (location->name == PORTO_DE_GALINHAS) {
        DrawTexture(assets.portal, 325, 170, RAYWHITE);
        DrawTextureEx(assets.chicken, (Vector2){300, 350}, 0.0f, 0.5f, RAYWHITE);
        DrawTextureEx(assets.chicken, (Vector2){635, 350}, 0.0f, 0.5f, RAYWHITE);
        DrawTextureEx(assets.coconutRight, (Vector2){835, 170}, 0.0f, 0.8f, RAYWHITE);
        DrawTextureEx(assets.chicken, (Vector2){-10, 420}, 0.0f, 2.0f, RAYWHITE);
        DrawTextureEx(assets.PortoSign, (Vector2){635, 550}, 0.0f, 1.0f, RAYWHITE);
    }

    if (location->name == FERNANDO_DE_NORONHA) {
        DrawTexture(assets.coral,300,380,RAYWHITE);
        DrawTextureEx(assets.islands,(Vector2){610, 90}, 0.0f, 0.7f,RAYWHITE);
        DrawTexture(assets.star,870,630,RAYWHITE);
        DrawTexture(assets.turtle,400,420,RAYWHITE);
        if (!sharkCaught)
        {
            DrawTextureEx(assets.sharkfin,(Vector2){910, 210}, 0.0f, 0.5f,RAYWHITE);
        }
        
        DrawTextureEx(assets.coconutLeft, (Vector2){930, 190}, 0.0f, 1.0f, RAYWHITE);
        DrawTextureEx(assets.coconutLeft, (Vector2){-255, 390}, 0.0f, 2.4f, RAYWHITE);
        DrawTextureEx(assets.coconutRight, (Vector2){310, 370}, 0.0f, 2.2f, RAYWHITE);
    }

    DrawTexture(location->fishShop, 680, 228, RAYWHITE);
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
            location->firstFish = marcoZeroFishList;
            location->defaultMusic = assets.morenaTropicana;
            location->fishingMusic = assets.labelledejour;
            location->pierFilter = (Color){0, 255, 51, 120};

            break;

        case PORTO_DE_GALINHAS:
            location->background = assets.backgroundPorto;
            location->backgroundBlur = assets.backgroundPorto;
            location->boat = assets.boat;
            location->sailor = assets.sailorPorto;
            location->salesman = assets.salesmanPorto;
            location->fishShop = assets.fishShopPorto;
            location->fishShopMenu = assets.fishShopPortoMenu;
            location->pier = assets.marcoZeroPier;
            location->firstFish = portoDeGalinhasFishList;
            location->defaultMusic = assets.vidaDeViajante;
            location->fishingMusic = assets.borbulhas;
            location->pierFilter = (Color){0, 0, 0, 0};
            break;

        case FERNANDO_DE_NORONHA:
            location->background = assets.backgroundNoronha;
            location->backgroundBlur = assets.backgroundNoronha;
            location->boat = assets.boat;
            location->sailor = assets.sailorNoronha;
            location->salesman = assets.salesmanNoronha;
            location->fishShop = assets.fishShopNoronha;
            location->fishShopMenu = assets.fishShopMenuNoronha;
            location->pier = assets.marcoZeroPier;
            location->firstFish = fernandoDeNoronhaFishList;
            location->defaultMusic = assets.sol;
            location->fishingMusic = assets.asaBranca;
            location->pierFilter = (Color){42, 0, 255, 120};
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

// Atualiza a sequência de teclas para o minigame de pesca de acordo com o tipo de peixe capturado
void updateSequence(Fish *fish) {
    if (strcmp(fish->name, "Tubarão") == 0) { // Verifica se o peixe é um "Tubarão"
        char sequence[] = "EUAMOPERNAMBUCO";
        for (int i = 0; i < fish->letters; i++) {
            catchSequence[i] = sequence[i]; // Define a sequência específica para "Tubarão"
        }
    } else { // Para outros peixes, gera uma sequência aleatória de letras
        for (int i = 0; i < 20; i++) {
            if (i < fish->letters) { // Define o número de letras correspondente ao peixe
                catchSequence[i] = (rand() % 26) + 65; // Gera uma letra aleatória (A-Z)
            } else {
                catchSequence[i] = -1; // Marca o final da sequência
            }
        }
    }
}

// Função que simula a captura de um peixe, escolhendo aleatoriamente um peixe que não seja o "Tubarão"
Fish* pescar(Fish *head) {
    if (head == NULL) { // Verifica se a lista está vazia
        return NULL;
    }

    int listSize = 0; // Inicializa o tamanho da lista
    Fish *temp = head;

    while (temp != NULL) { // Conta apenas peixes que não são "Tubarão"
        if (temp->price != 999) {
            listSize++;
        }
        temp = temp->next;
    }

    if (listSize == 0) { // Se não houver peixes válidos, retorna NULL
        return NULL;
    }

    int randomIndex = rand() % listSize; // Seleciona um índice aleatório
    temp = head;
    int index = 0;

    while (temp != NULL) { // Percorre a lista para encontrar o peixe no índice aleatório
        if (temp->price != 999) {
            if (index == randomIndex) { // Retorna o peixe correspondente
                return temp;
            }
            index++;
        }
        temp = temp->next;
    }

    return NULL; // Retorna NULL se o peixe não for encontrado
}

// Cria um novo peixe com as características especificadas e insere-o na lista de peixes do local apropriado
void createFish(Fish **head, char *name, int price, int letters, Texture2D sprite, LocationName locationName) {
    Fish *new = (Fish *)malloc(sizeof(Fish)); // Aloca memória para o novo peixe

    if (new != NULL) {
        strcpy(new->name, name); // Define o nome do peixe
        new->wasCaptured = false; // Marca o peixe como ainda não capturado
        new->price = price; // Define o preço do peixe
        new->sprite = sprite; // Define o sprite do peixe
        new->locationName = locationName; // Define a localização do peixe
        new->next = *head;
        new->letters = letters; // Define o número de letras do minigame associado ao peixe
        new->prev = NULL;

        if (!price) { // Se o preço é zero, marca o peixe como "lixo"
            new->isTrash = true;
        } else {
            new->isTrash = false;
        }

        if (*head != NULL) { // Insere o peixe no início da lista
            (*head)->prev = new;
        }

        *head = new; // Atualiza a cabeça da lista
    }
}

// Insere um peixe no balde (bucket) caso haja espaço disponível e o peixe não seja um lixo
void insertBucket(Bucket **head, Fish *fish) {
    // Verifica se o peixe é nulo, é lixo ou se o balde já está cheio
    if (fish == NULL || fish->isTrash || bucket >= 8) {
        return;
    }

    // Cria uma nova entrada para o peixe no balde
    Bucket *newBucket = (Bucket *)malloc(sizeof(Bucket));
    if (newBucket == NULL) { // Verifica falha de alocação
        return;
    }

    newBucket->fish = fish; // Associa o peixe à nova entrada
    newBucket->next = NULL;

    if (*head == NULL) { // Se o balde está vazio, insere o peixe no início
        newBucket->prev = NULL;
        *head = newBucket;
    } else { // Caso contrário, insere o peixe ao final da lista
        Bucket *last = *head;
        while (last->next != NULL) { // Percorre até o último elemento
            last = last->next;
        }
        last->next = newBucket;
        newBucket->prev = last;
    }

    bucket++; // Incrementa o contador de peixes no balde
}

// Insere um novo peixe na Fishpedia
void insertFishpedia(Fishpedia **head, Fish *fish) {
    // Verifica se o peixe é nulo, é lixo ou se a Fishpedia já atingiu seu limite
    if (fish == NULL || fish->isTrash || fishpediaCount >= 24) {
        return;
    }

    // Cria uma nova entrada para o peixe na Fishpedia
    Fishpedia *newFishpedia = (Fishpedia *)malloc(sizeof(Fishpedia));
    if (newFishpedia == NULL) { // Verifica falha de alocação
        return;
    }

    newFishpedia->fish = fish; // Associa o peixe à nova entrada
    newFishpedia->next = NULL;

    if (*head == NULL) { // Se a Fishpedia está vazia, insere o peixe no início
        newFishpedia->prev = NULL;
        *head = newFishpedia;
    } else { // Caso contrário, insere o peixe ao final da lista
        Fishpedia *last = *head;
        while (last->next != NULL) { // Percorre até o último elemento
            last = last->next;
        }
        last->next = newFishpedia;
        newFishpedia->prev = last;
    }
}
// Atualiza o contador de capturas para cada local específico
void updateLocationCaptureCount(Fish *capturedFish) {
    if (capturedFish == NULL) { // Se o peixe capturado for nulo, termina a função
        return;
    }

    // Determina qual localidade o peixe pertence e incrementa o contador correspondente
    switch (capturedFish->locationName) {
        case MARCO_ZERO:
            if (!capturedFish->isTrash) // Ignora peixes classificados como "lixo"
            {
                marcoZeroCapturedCount++; // Incrementa o contador de Marco Zero
            }
            break;
        case PORTO_DE_GALINHAS:
            if (!capturedFish->isTrash) // Ignora peixes classificados como "lixo"
            {
                portoDeGalinhasCapturedCount++; // Incrementa o contador de Porto de Galinhas
            }
            break;
        case FERNANDO_DE_NORONHA:
            if (!capturedFish->isTrash) // Ignora peixes classificados como "lixo"
            {
                fernandoDeNoronhaCapturedCount++; // Incrementa o contador de Fernando de Noronha
            }
            break;
        default:
            break;
    }
}

// Adiciona um peixe à Fishpedia caso ele ainda não tenha sido capturado
void addFishToFishpedia(Fish *fish) {
    if (fish == NULL) { // Se o peixe for nulo, termina a função
        return;
    }

    if (!fish->wasCaptured) { // Adiciona o peixe apenas se ele ainda não foi capturado
        fish->wasCaptured = true; // Marca o peixe como capturado
        if (!fish->isTrash) // Ignora peixes classificados como "lixo"
        {
            fishpediaCount++; // Incrementa o contador da Fishpedia
        }
        updateLocationCaptureCount(fish); // Atualiza o contador do local de captura
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

void DrawFishpedia(Assets assets, Vector2 mousePos) {
    DrawTexture(assets.fishpediaBackground, 0, 0, RAYWHITE);
    DrawTexture(assets.fishCounter, 792, 48, WHITE);
    sprintf(fishpediaCountStr, "%d", fishpediaCount);
    DrawText(fishpediaCountStr, 870, 68, 28, BLACK);
    DrawText("/25", 905, 68, 28, BLACK);
    DrawText(fishpediaCountStr, 872, 66, 28, WHITE);
    DrawText("/25", 907, 66, 28, WHITE);

    DrawText("Fishpedia", 448, 72, 28, BLACK);
    DrawText("Fishpedia", 450, 70, 28, WHITE);

    LocationName locationName;
    int capturedCount = 0;

    switch (currentFishpediaPage) {
        case MARCO_ZERO_PAGE:
            locationName = MARCO_ZERO;
            capturedCount = marcoZeroCapturedCount;
            DrawTextureEx(assets.MarcoSign, (Vector2){50, 56}, 0.0f, 0.5f, RAYWHITE);
            break;
        case PORTO_DE_GALINHAS_PAGE:
            locationName = PORTO_DE_GALINHAS;
            capturedCount = portoDeGalinhasCapturedCount;
            DrawTextureEx(assets.PortoSign, (Vector2){50, 56}, 0.0f, 0.5f, RAYWHITE);
            break;
        case FERNANDO_DE_NORONHA_PAGE:
            locationName = FERNANDO_DE_NORONHA;
            capturedCount = fernandoDeNoronhaCapturedCount;
            DrawTextureEx(assets.NoronhaSign, (Vector2){50, 56}, 0.0f, 0.5f, RAYWHITE);
            break;
        default:
            return;
    }

    sprintf(fishpediaCountStr, "%d", capturedCount);
    DrawText(fishpediaCountStr, 100, 72, 28, BLACK);
    DrawText(fishpediaCountStr, 102, 70, 28, WHITE);
    if (currentFishpediaPage==FERNANDO_DE_NORONHA_PAGE)
    {
        DrawText("/9", 120, 68, 28, BLACK);
        DrawText("/9", 118, 70, 28, WHITE);
    }else
    {
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

    Fish *fish = NULL;
    switch (locationName) {
        case MARCO_ZERO:
            fish = marcoZeroFishList;
            break;
        case PORTO_DE_GALINHAS:
            fish = portoDeGalinhasFishList;
            break;
        case FERNANDO_DE_NORONHA:
            fish = fernandoDeNoronhaFishList;
            break;
        default:
            break;
    }

    int index = 0;
    while (fish != NULL && index < 8) {
        if (!fish->isTrash && fish->price!=999) {
            DrawTextureEx(assets.fishFrame, framePositions[index], 0.0f, 1.1f, RAYWHITE);
            if (fish->wasCaptured) {
                DrawTextureEx(fish->sprite, (Vector2){framePositions[index].x + 40, framePositions[index].y}, 0.0f, 1.0f, WHITE);
                DrawText(fish->name, textPositions[index].x - (strlen(fish->name) * 4), textPositions[index].y, 24, BLACK);
            } else {
                DrawTextureEx(fish->sprite, (Vector2){framePositions[index].x + 40, framePositions[index].y}, 0.0f, 1.0f, BLACK);
                DrawText("?????", textPositions[index].x - 15, textPositions[index].y, 24, BLACK);
            }
            index++;
        }
        fish = fish->next;
    }

    DrawTextureEx(assets.arrow, (Vector2){870, 600}, 90.0f, 1.0f, RAYWHITE);
    DrawTextureEx(assets.arrow, (Vector2){900, 650}, 270.0f, 1.0f, RAYWHITE);

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

    if (CheckCollisionPointRec(mousePos, (Rectangle){50, 620, assets.button.width / 2, assets.button.height / 2})) {
        DrawTextureEx(assets.buttonDark, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
    } else {
        DrawTextureEx(assets.button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
    }
    DrawText("VOLTAR", 75, 632, 28, WHITE);
}

void DrawFishShop(Assets assets, Location *location, Vector2 mousePos) {
    DrawTextureEx(location->backgroundBlur, (Vector2){-1620, -400}, 0.0f, 2.6f, WHITE);
    DrawTextureEx(location->salesman, (Vector2){10, 260}, 0.0f, 2.1f, WHITE);
    DrawTextureEx(location->fishShopMenu, (Vector2){0, -30}, 0.0f, 1.1f, WHITE);
    DrawTextureEx(assets.fishShopMenuBG, (Vector2){475, 7}, 0.0f, 1.0f, WHITE);

    DrawTextureEx(assets.fishFrame, (Vector2){555, 40}, 0.0f, 0.8f, WHITE);
    DrawTextureEx(assets.fishFrame, (Vector2){735, 40}, 0.0f, 0.8f, WHITE);

    DrawTextureEx(assets.fishFrame, (Vector2){555, 40 + 131}, 0.0f, 0.8f, WHITE);
    DrawTextureEx(assets.fishFrame, (Vector2){735, 40 + 131}, 0.0f, 0.8f, WHITE);

    DrawTextureEx(assets.fishFrame, (Vector2){555, 40 + 131 * 2}, 0.0f, 0.8f, WHITE);
    DrawTextureEx(assets.fishFrame, (Vector2){735, 40 + 131 * 2}, 0.0f, 0.8f, WHITE);

    DrawTextureEx(assets.fishFrame, (Vector2){555, 40 + 131 * 3}, 0.0f, 0.8f, WHITE);
    DrawTextureEx(assets.fishFrame, (Vector2){735, 40 + 131 * 3}, 0.0f, 0.8f, WHITE);

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

    if (CheckCollisionPointRec(mousePos, (Rectangle){525, 575, assets.sellButton.width * 1.3, assets.sellButton.height * 1.3})) {
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

    if (CheckCollisionPointRec(mousePos, (Rectangle){50, 620, assets.button.width / 2, assets.button.height / 2})) {
        DrawTextureEx(assets.buttonDark, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
    } else {
        DrawTextureEx(assets.button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
    }
    DrawText("VOLTAR", 75, 632, 28, WHITE);
}

void DrawPier(Assets assets, Location *location, Vector2 mousePos, int arrowFrames2) {

    DrawTextureEx(assets.water[waterFrames], (Vector2){0, 0}, 0.0f, 1.0f, RAYWHITE);
    DrawRectangle(0, 0, 1024, 720, location->pierFilter);
    DrawTexture(location->pier, 0, 100, RAYWHITE);
    DrawTexture(location->pierRight, 0, 0, RAYWHITE);
    DrawTexture(assets.fishPedia, 50, 40, RAYWHITE);
    DrawTexture(assets.fishBucket, 140, 40, RAYWHITE);

    if (location->name==FERNANDO_DE_NORONHA) {
        if (!sharkCaught)
        {
            DrawTexture(assets.sharkfin,900,360,RAYWHITE);
        }
        
    }

    if (firstGame) {
        DrawRectangle(280, 0, 744, 720, (Color){0, 255, 0, 130});
        DrawTextureEx(assets.button, (Vector2){268.25, 530}, 0.0f, 1.5f, WHITE);
        DrawText("Clique em qualquer lugar", 325, 560, 30, WHITE);
        DrawText("da", 365, 600, 30, WHITE);
        DrawText("área verde", 408, 600, 30, GREEN);
        DrawText("para", 590, 600, 30, WHITE);
        DrawText("lançar a vara", 400, 640, 30, YELLOW);
    }

    DrawTextureEx(assets.arrow, (Vector2){65 + arrowFrames2 / 5, 370}, 90.0f, 1.0f, RAYWHITE);

}

void DrawPort(Assets assets, Location *location, Vector2 mousePos) {
    DrawTextureEx(location->backgroundBlur, (Vector2){0, -400}, 0.0f, 2.55f, WHITE);
    DrawTextureEx(location->boat, (Vector2){-130, 40}, 0.0f, 1.7f, WHITE);
    DrawTextureEx(location->sailor, (Vector2){100, 230}, 0.0f, 2.2f, WHITE);
    DrawTextureEx(assets.button, (Vector2){400, 160}, 0.0f, 1.8f, WHITE);

    Rectangle firstButtonRec = {400, 380, assets.button.width * 0.8f, assets.button.height * 0.8f};
    Rectangle secondButtonRec = {725, 380, assets.button.width * 0.8f, assets.button.height * 0.8f};

    Rectangle voltarButtonRec = {50, 620, assets.button.width / 2, assets.button.height / 2};

    if (CheckCollisionPointRec(mousePos, voltarButtonRec)) {
        DrawTextureEx(assets.buttonDark, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
    } else {
        DrawTextureEx(assets.button, (Vector2){50, 620}, 0.0f, 0.5f, WHITE);
    }
    DrawText("VOLTAR", 75, 632, 28, WHITE);

    DrawTextureEx(assets.coin, (Vector2){810, 40}, 0.0f, 0.7f, WHITE);
    char balanceText[10];
    sprintf(balanceText, "%03d", balance);
    DrawText(balanceText, 888, 57, 45, BLACK);
    DrawText(balanceText, 890, 55, 45, WHITE);

    if (location->name == MARCO_ZERO) {
        if (visitedNoronha) {
            DrawText("ESCOLHA O DESTINO PARA VIAJAR", 445, 210, 28, WHITE);
            DrawText("GRÁTIS", 610, 265, 40, YELLOW);

            if (CheckCollisionPointRec(mousePos, firstButtonRec)) {
                DrawTextureEx(assets.buttonDark, (Vector2){400, 380}, 0.0f, 0.8f, WHITE);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    *location = *startLocation(PORTO_DE_GALINHAS, assets);
                }
            } else {
                DrawTextureEx(assets.button, (Vector2){400, 380}, 0.0f, 0.8f, WHITE);
            }
            DrawText("PORTO DE", 455, 395, 28, WHITE);
            DrawText("GALINHAS", 458, 430, 28, WHITE);

            if (CheckCollisionPointRec(mousePos, secondButtonRec)) {
                DrawTextureEx(assets.buttonDark, (Vector2){725, 380}, 0.0f, 0.8f, WHITE);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    *location = *startLocation(FERNANDO_DE_NORONHA, assets);
                }
            } else {
                DrawTextureEx(assets.button, (Vector2){725, 380}, 0.0f, 0.8f, WHITE);
            }
            DrawText("FERNANDO", 780, 395, 28, WHITE);
            DrawText("DE NORONHA", 765, 430, 28, WHITE);

        } else {
            DrawText("VIAJAR PARA", 435, 210, 28, WHITE);
            DrawText("PORTO DE GALINHAS?", 637, 210, 28, YELLOW);
            DrawTextureEx(assets.coin, (Vector2){610, 260}, 0.0f, 0.6f, WHITE);
            DrawText("350", 680, 270, 45, WHITE);

            if (CheckCollisionPointRec(mousePos, firstButtonRec)) {
                DrawTextureEx(assets.buttonDark, (Vector2){400, 380}, 0.0f, 0.8f, WHITE);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && balance >= 350) {
                    if (!visitedNoronha)
                    {
                        balance -= 350;
                    }
                    
                    *location = *startLocation(PORTO_DE_GALINHAS, assets);
                }
            } else {
                DrawTextureEx(assets.button, (Vector2){400, 380}, 0.0f, 0.8f, WHITE);
            }
            DrawText("SIM", 488, 400, 45, WHITE);

            if (CheckCollisionPointRec(mousePos, secondButtonRec)) {
                DrawTextureEx(assets.buttonDark, (Vector2){725, 380}, 0.0f, 0.8f, WHITE);
            } else {
                DrawTextureEx(assets.button, (Vector2){725, 380}, 0.0f, 0.8f, WHITE);
            }
            DrawText("NÃO", 810, 400, 45, WHITE);
        }
    } else if (location->name == PORTO_DE_GALINHAS) {
        if (visitedNoronha) {
            DrawText("ESCOLHA O DESTINO PARA VIAJAR", 445, 210, 28, WHITE);
            DrawText("GRÁTIS", 610, 265, 40, YELLOW);

            if (CheckCollisionPointRec(mousePos, firstButtonRec)) {
                DrawTextureEx(assets.buttonDark, (Vector2){400, 380}, 0.0f, 0.8f, WHITE);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    *location = *startLocation(MARCO_ZERO, assets);
                }
            } else {
                DrawTextureEx(assets.button, (Vector2){400, 380}, 0.0f, 0.8f, WHITE);
            }
            DrawText("MARCO ZERO", 440, 410, 28, WHITE);

            if (CheckCollisionPointRec(mousePos, secondButtonRec)) {
                DrawTextureEx(assets.buttonDark, (Vector2){725, 380}, 0.0f, 0.8f, WHITE);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    *location = *startLocation(FERNANDO_DE_NORONHA, assets);
                }
            } else {
                DrawTextureEx(assets.button, (Vector2){725, 380}, 0.0f, 0.8f, WHITE);
            }
            DrawText("FERNANDO", 780, 395, 28, WHITE);
            DrawText("DE NORONHA", 765, 430, 28, WHITE);

        } else {
            DrawText("VIAJAR PARA", 415, 210, 28, WHITE);
            DrawText("FERNANDO DE NORONHA?", 617, 210, 28, YELLOW);
            DrawTextureEx(assets.coin, (Vector2){610, 260}, 0.0f, 0.6f, WHITE);
            DrawText("800", 680, 270, 45, WHITE);

            if (CheckCollisionPointRec(mousePos, firstButtonRec)) {
                DrawTextureEx(assets.buttonDark, (Vector2){400, 380}, 0.0f, 0.8f, WHITE);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && balance >= 800) {
                    if (!visitedNoronha)
                    {
                        balance -= 800;
                    }
                    
                    *location = *startLocation(FERNANDO_DE_NORONHA, assets);
                    visitedNoronha = true;
                }
            } else {
                DrawTextureEx(assets.button, (Vector2){400, 380}, 0.0f, 0.8f, WHITE);
            }
            DrawText("SIM", 488, 400, 45, WHITE);

            if (CheckCollisionPointRec(mousePos, secondButtonRec)) {
                DrawTextureEx(assets.buttonDark, (Vector2){725, 380}, 0.0f, 0.8f, WHITE);
            } else {
                DrawTextureEx(assets.button, (Vector2){725, 380}, 0.0f, 0.8f, WHITE);
            }
            DrawText("NÃO", 810, 400, 45, WHITE);
        }
    } else if (location->name == FERNANDO_DE_NORONHA) {
        DrawText("ESCOLHA O DESTINO PARA VIAJAR", 445, 210, 28, WHITE);
        DrawText("GRÁTIS", 610, 265, 40, YELLOW);

        if (CheckCollisionPointRec(mousePos, firstButtonRec)) {
            DrawTextureEx(assets.buttonDark, (Vector2){400, 380}, 0.0f, 0.8f, WHITE);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                *location = *startLocation(MARCO_ZERO, assets);
            }
        } else {
            DrawTextureEx(assets.button, (Vector2){400, 380}, 0.0f, 0.8f, WHITE);
        }
        DrawText("MARCO ZERO", 440, 410, 28, WHITE);

        if (CheckCollisionPointRec(mousePos, secondButtonRec)) {
            DrawTextureEx(assets.buttonDark, (Vector2){725, 380}, 0.0f, 0.8f, WHITE);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                *location = *startLocation(PORTO_DE_GALINHAS, assets);
            }
        } else {
            DrawTextureEx(assets.button, (Vector2){725, 380}, 0.0f, 0.8f, WHITE);
        }
        DrawText("PORTO DE", 785, 395, 28, WHITE);
        DrawText("GALINHAS", 788, 430, 28, WHITE);
    }
}

// Vende todos os peixes atualmente no balde e atualiza o saldo
void sell(Assets assets) {
    bool vendeu = false; // Variável de controle para verificar se algum peixe foi vendido
    while (bucketHead != NULL) { // Continua enquanto houver peixes no balde
        Bucket *current = bucketHead;
        balance += current->fish->price; // Adiciona o preço do peixe ao saldo
        if (balance > 999) { // Limita o saldo máximo a 999
            balance = 999;
        }
        bucketHead = bucketHead->next; // Move para o próximo peixe no balde
        if (bucketHead != NULL) { // Se ainda houver peixes, ajusta o ponteiro do anterior
            bucketHead->prev = NULL;
        }
        free(current); // Libera a memória do peixe vendido
        vendeu = true;
    }
    if (vendeu) { // Reproduz o som de venda se houve alguma venda
        PlaySound(assets.sellSound);
    }
    bucket = 0; // Zera o contador de peixes no balde
}

void sortFishListByDifficulty(Fish **head) {
    if (*head == NULL) return;

    bool swapped = true;
    Fish *current;
    Fish *last = NULL;

    while (swapped) {
        swapped = false;
        current = *head;

        while (current->next != last) {
            if (current->letters > current->next->letters) {
                char tempName[30];
                int tempPrice = current->price;
                int tempLetters = current->letters;
                Texture2D tempSprite = current->sprite;
                bool tempIsTrash = current->isTrash;
                bool tempWasCaptured = current->wasCaptured;
                LocationName tempLocationName = current->locationName;

                strcpy(tempName, current->name);
                strcpy(current->name, current->next->name);
                strcpy(current->next->name, tempName);

                current->price = current->next->price;
                current->next->price = tempPrice;

                current->letters = current->next->letters;
                current->next->letters = tempLetters;

                current->sprite = current->next->sprite;
                current->next->sprite = tempSprite;

                current->isTrash = current->next->isTrash;
                current->next->isTrash = tempIsTrash;

                current->wasCaptured = current->next->wasCaptured;
                current->next->wasCaptured = tempWasCaptured;

                current->locationName = current->next->locationName;
                current->next->locationName = tempLocationName;

                swapped = true;
            }
            current = current->next;
        }
        last = current;
    }
}

void updateWaterFrames() {
    if (waterUpdateCounter >= 13) {
        waterFrames = (waterFrames + 1) % 10;
        waterUpdateCounter = 0;
    } else {
        waterUpdateCounter++;
    }
}

void setHookedFish(Assets assets, Location *location, Vector2 mousePos) {
    if (!hookedFish) {

        Rectangle sharkFinArea = {900, 360, assets.sharkfin.width, assets.sharkfin.height};

        if (CheckCollisionPointRec(mousePos,sharkFinArea) && !sharkCaught && fishpediaCount==24) {
            hookedFish = getSharkFish(); 
        } else {
            hookedFish = pescar(location->firstFish);   
        }
        
        updateSequence(hookedFish);
        gameTime = 1000000.0f;
        ranOutOfTime = false;
        StopSound(assets.tictac);
        
    }
}

void spaceKeyMiniGame(Assets assets) {

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

    gameTime -= 10000;

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

}

void fishingMiniGame(Assets assets) {

    int maxButtons;

    if (hookedFish->letters > 10) {
        maxButtons = 15;
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 75}, 0.0f, 0.4f, RAYWHITE);
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 150}, 0.0f, 0.4f, RAYWHITE);
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 225}, 0.0f, 0.4f, RAYWHITE);
    } else if (hookedFish->letters > 5) {
        maxButtons = 10;
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 75}, 0.0f, 0.4f, RAYWHITE);
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 150}, 0.0f, 0.4f, RAYWHITE);
    } else {
        maxButtons = 5;
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 75}, 0.0f, 0.4f, RAYWHITE);
    }

    float timeRatio = gameTime / 1500000.0f;

    if (timeRatio > 0.75f) {
        DrawRectangle(350, 63, 267 * timeRatio, 10, GREEN);
    } else if (timeRatio >= 0.5f) {
        DrawRectangle(350, 63, 267 * timeRatio, 10, YELLOW);
    } else if (timeRatio > 0.35f) {
        DrawRectangle(350, 63, 267 * timeRatio, 10, ORANGE);
    } else {
        DrawRectangle(350, 63, 267 * timeRatio, 10, RED);
    }

    gameTime -= 5000;

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

    for (int i = 0; i < maxButtons; i++) {
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
            DrawTextureEx(assets.emptyButton, (Vector2){startX, startY}, 0.0f, 0.5f, WHITE);
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
                if (strcmp(hookedFish->name, "Tubarão") == 0) {
                    sharkCaught = true;
                }
            }
        } else {
            PlaySound(assets.boowomp);
            showError = true;
            errorStartTime = GetTime();
            isMiniGaming = false;
        }
    }

}

void showMiniGameMistake(Assets assets) {

    if (hookedFish->letters > 10 && hookedFish->letters < 15) {
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 75}, 0.0f, 0.4f, RAYWHITE);
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 150}, 0.0f, 0.4f, RAYWHITE);
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 225}, 0.0f, 0.4f, RAYWHITE);
    } else if (hookedFish->letters > 5 && hookedFish->letters < 11) {
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 75}, 0.0f, 0.4f, RAYWHITE);
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 150}, 0.0f, 0.4f, RAYWHITE);
    } else if (hookedFish->letters < 6) {
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 75}, 0.0f, 0.4f, RAYWHITE);
    }

    int maxButtons;

    if (hookedFish->letters > 10) {
        maxButtons = 15;
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 75}, 0.0f, 0.4f, RAYWHITE);
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 150}, 0.0f, 0.4f, RAYWHITE);
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 225}, 0.0f, 0.4f, RAYWHITE);
    } else if (hookedFish->letters > 5) {
        maxButtons = 10;
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 75}, 0.0f, 0.4f, RAYWHITE);
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 150}, 0.0f, 0.4f, RAYWHITE);
    } else {
        maxButtons = 5;
        DrawTextureEx(assets.keyButtonBox, (Vector2){350, 75}, 0.0f, 0.4f, RAYWHITE);
    }

    for (int i = 0; i < maxButtons; i++) {
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
            DrawTextureEx(assets.emptyButton, (Vector2){startX, startY}, 0.0f, 0.5f, WHITE);
        }
    }

    if (GetTime() - errorStartTime >= 1.0f) {
        showError = false;
        currentSequenceIndex = 0;
        successfulCatch = 2;
        isMiniGaming = false;
    }

}

void showCatchedFishAlert(Assets assets, AnimationFrames **animationFrames) {

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

}

void resetGameStates(AnimationFrames **animationFrames) {

    free(*animationFrames);
    *animationFrames = createAnimationFrames();

    caught = false;
    firstGame = true;

    fishFrame = 0;
    waitingFish = -1;
    waitingFrames = 0;
    successfulCatch = 0;

}
