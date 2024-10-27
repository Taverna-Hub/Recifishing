#ifndef INIT_H
#define INIT_H

#include "raylib.h"
#include "../utils/utils.h"

typedef struct {
    Texture2D logoTexture;
    Texture2D fishPedia;
    Texture2D fishBucket;
    Texture2D exitButton;
    Texture2D startButton;
    Texture2D backgroundMenu;
    Texture2D darkExitButton;
    Texture2D darkStartButton;
    Texture2D portSign;
    Texture2D fishShop;
    Sound labelledejour;
    Sound morenaTropicana;
    Sound anunciacao;
} Assets;

Assets LoadAssets(void);

#endif
