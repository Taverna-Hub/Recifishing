#ifndef INIT_H
#define INIT_H

#include "raylib.h"
#include "../utils/utils.h"

typedef struct {
    Texture2D logoTexture;
    Texture2D fishPedia;
    Texture2D fishPedia2;
    Texture2D fishBucket;
    Texture2D exitButton;
    Texture2D startButton;
    Texture2D backgroundMenu;
    Texture2D backgroundMarcoZero;
    Texture2D darkExitButton;
    Texture2D darkStartButton;
    Texture2D portSign;
    Texture2D fishShop;
    Texture2D arrow;
    Texture2D boat;
    Texture2D button;
    Texture2D coin;
    Sound labelledejour;
    Sound morenaTropicana;
    Sound anunciacao;
} Assets;

Assets LoadAssets(void);

#endif
