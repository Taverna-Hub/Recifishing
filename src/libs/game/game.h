#ifndef GAME_H
#define GAME_H

#include "../init/init.h"
typedef struct Arrow {
    int arrowFrames;
    int direction;
}Arrow;

typedef enum Frames {
    DEFAULT = 0,
    FISHPEDIA = 1,
    BUCKET = 2,
    PORT = 3,
    FISHSHOP = 4,
    PIER = 5,
} Frames;

Arrow* createArrow();
void updateArrow(Arrow *arrow);

int cursorHandle(Vector2 mousePos, Texture2D button, Texture2D bucket, Texture2D fishpedia, int gameFrame);
void fadeHandle(bool *inTransition, int *fadeAlpha);

void UpdateGame(bool *inTransition, GameScreen *currentScreen, Arrow *arrow, Vector2 mousePos, Assets assets, int *gameFrame);
void DrawGame(bool *inTransition, int *fadeAlpha, Assets assets, bool *isSoundPlayed, int arrowFrames, Vector2 mousePos, int frame);


#endif
