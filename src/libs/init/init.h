#ifndef INIT_H
#define INIT_H

#include "raylib.h"
#include "../utils/utils.h"

typedef struct {

    Texture2D boat;
    Texture2D coin;
    Texture2D arrow;
    Texture2D salesman;
    Texture2D sailor;
    Texture2D button;
    Texture2D fishShop;
    Texture2D portSign;
    Texture2D fishPedia;
    Texture2D fishPedia2;
    Texture2D fishBucket;
    Texture2D exitButton;
    Texture2D startButton;
    Texture2D logoTexture;
    Texture2D backgroundMenu;
    Texture2D darkExitButton;
    Texture2D darkStartButton;
    Texture2D backgroundMarcoZero;
    Texture2D marcoZeroPier;

    Texture2D fish;
    Texture2D baseButton;
    Texture2D baseButtonSpace;
    Texture2D baseButtonFail;
    Texture2D baseButtonPressed;
    Texture2D keyButtonBox;

    Texture2D fishermanHook[6];
    Texture2D fishermanIdle[4];
    Texture2D fishermanFishing[4];

    Texture2D bucketBackground;
    Texture2D fishpediaBackground;
    Texture2D fishFrame;

    Music anunciacao;
    Music labelledejour;
    Music morenaTropicana;
    Sound keyPress;

} Assets;

Assets LoadAssets(void);

#endif
