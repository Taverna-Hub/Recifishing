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
    Texture2D buttonDark;
    Texture2D fishShop;
    Texture2D fishShopMenu;
    Texture2D fishShopPorto;
    Texture2D fishShopPortoMenu;
    Texture2D fishShopMenuBG;
    Texture2D fishCounter;
    Texture2D portSign;
    Texture2D fishPedia;
    Texture2D fishPedia2;
    Texture2D fishBucket;
    Texture2D exitButton;
    Texture2D startButton;
    Texture2D emptyButton;
    Texture2D logoTexture;
    Texture2D backgroundMenu;
    Texture2D darkExitButton;
    Texture2D darkStartButton;
    Texture2D backgroundMarcoZero;
    Texture2D backgroundMarcoZeroBlur;
    Texture2D marcoZeroPier;
    Texture2D marcoZeroPierRight;
    Texture2D sellButton;
    Texture2D sellButtonHover;

    Texture2D sailorPorto;
    Texture2D salesmanPorto;
    Texture2D coconutLeft;
    Texture2D coconutRight;
    Texture2D chicken;
    Texture2D portal;
    Texture2D backgroundPorto;
    Texture2D backgroundPortoBlur;

    Texture2D sailorNoronha;
    Texture2D salesmanNoronha;
    Texture2D coral;
    Texture2D islands;
    Texture2D sharkfin;
    Texture2D star;
    Texture2D turtle;
    Texture2D backgroundNoronha;
    Texture2D fishShopMenuNoronha;
    Texture2D fishShopNoronha;

    Texture2D fish;
    Texture2D fishFraming;
    Texture2D baseButton;
    Texture2D baseButtonSpace;
    Texture2D baseButtonFail;
    Texture2D baseButtonPressed;
    Texture2D keyButtonBox;

    Texture2D fishermanHook[6];
    Texture2D fishermanIdle[4];
    Texture2D fishermanFishing[4];
    Texture2D water[10];
    Texture2D marcoZeroFishes[10];
    Texture2D portoFishes[10];
    Texture2D noronhaFishes[11];

    Texture2D bucketBackground;
    Texture2D fishpediaBackground;
    Texture2D fishFrame;
    Texture2D MarcoSign;
    Texture2D PortoSign;
    Texture2D NoronhaSign;

    Music anunciacao;
    Music labelledejour;
    Music morenaTropicana;
    Music sol;
    Music trombone;
    Music eraDomingo;
    Music borbulhas;

    Sound keyPress;
    Sound boowomp;
    Sound tictac;
    Sound fail;
    Sound success;
    Sound alert;
    Sound sellSound;

} Assets;

Assets LoadAssets(void);

#endif
