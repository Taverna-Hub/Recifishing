#ifndef GAME_H
#define GAME_H

#include "../init/init.h"

void UpdateGame(bool *inTransition, GameScreen *currentScreen);
void DrawGame(bool inTransition, int fadeAlpha, Assets assets, bool *isSoundPlayed);

#endif
