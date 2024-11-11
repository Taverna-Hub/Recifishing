#ifndef MENU_H
#define MENU_H

#include "../init/init.h"
#include "../game/game.h"

void DrawMenu(GameScreen *currentScreen, Vector2 mousePos, bool inTransition, int fadeAlpha, Assets assets, bool *isSoundPlayed);
void UpdateMenu(GameScreen *currentScreen, bool *inTransition, int *fadeAlpha, Vector2 mousePos, Assets assets, bool *isSoundPlayed);

#endif
