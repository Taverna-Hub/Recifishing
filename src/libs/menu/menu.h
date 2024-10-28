#ifndef MENU_H
#define MENU_H

#include "../init/init.h"

void UpdateMenu(GameScreen *currentScreen, bool *inTransition, int *fadeAlpha, Vector2 mousePos, Assets assets, bool *isSoundPlayed);
void DrawMenu(GameScreen *currentScreen, Vector2 mousePos, bool inTransition, int fadeAlpha, Assets assets, bool *isSoundPlayed);

#endif
