#ifndef GAME_H
#define GAME_H

#include "../init/init.h"
typedef struct Arrow {
    int arrowFrames;
    int direction;
}Arrow;

void UpdateGame(bool *inTransition, GameScreen *currentScreen, Arrow *arrow, Vector2 mousePos);
void DrawGame(bool *inTransition, int *fadeAlpha, Assets assets, bool *isSoundPlayed, int arrowFrames, Vector2 mousePos);


#endif
