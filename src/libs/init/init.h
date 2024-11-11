#ifndef INIT_H
#define INIT_H

#include "raylib.h"

typedef struct {

    /* Efeitos Sonoros */
    Sound fail;
    Sound alert;
    Sound tictac;
    Sound boowomp;
    Sound success;
    Sound keyPress;
    Sound sellSound;

    /* Trilha sonora */
    Music sol;
    Music trombone;
    Music borbulhas;
    Music anunciacao;
    Music eraDomingo;
    Music labelledejour;
    Music morenaTropicana;

    /* Menu Sprites */
    Texture2D fishFrame;
    Texture2D exitButton;
    Texture2D startButton;
    Texture2D backgroundMenu;
    Texture2D darkExitButton;
    Texture2D fishShopMenuBG;
    Texture2D darkStartButton;
    Texture2D bucketBackground;
    Texture2D fishpediaBackground;

    /* Icons Sprites */
    Texture2D coin;
    Texture2D arrow;
    Texture2D button;
    Texture2D MarcoSign;
    Texture2D PortoSign;
    Texture2D fishPedia;
    Texture2D fishPedia2;
    Texture2D baseButton;
    Texture2D fishBucket;
    Texture2D sellButton;
    Texture2D buttonDark;
    Texture2D fishFraming;
    Texture2D logoTexture;
    Texture2D emptyButton;
    Texture2D fishCounter;
    Texture2D NoronhaSign;
    Texture2D keyButtonBox;
    Texture2D baseButtonFail;
    Texture2D baseButtonSpace;
    Texture2D sellButtonHover;
    Texture2D baseButtonPressed;

    /* Fisherman Frames*/
    Texture2D fishermanHook[6];
    Texture2D fishermanIdle[4];
    Texture2D fishermanFishing[4];

    /* Water Frames */
    Texture2D water[10];

    /* Marco Zero Fishes */
    Texture2D marcoZeroFishes[10];

    /* Porto de Galinhas Fishes */
    Texture2D portoFishes[10];

    /* Fernando de Noronha Fishes */
    Texture2D noronhaFishes[11];

    /* Marco Zero Sprites */
    Texture2D boat;
    Texture2D sailor;
    Texture2D salesman;
    Texture2D fishShop;
    Texture2D portSign;
    Texture2D fishShopMenu;
    Texture2D marcoZeroPier;
    Texture2D backgroundMarcoZero;
    Texture2D backgroundMarcoZeroBlur;

    /* Porto de Galinhas Sprites */
    Texture2D portal;
    Texture2D chicken;
    Texture2D sailorPorto;
    Texture2D coconutLeft;
    Texture2D coconutRight;
    Texture2D fishShopPorto;
    Texture2D salesmanPorto;
    Texture2D backgroundPorto;
    Texture2D fishShopPortoMenu;
    Texture2D backgroundPortoBlur;

    /* Fernando de Noronha Sprites */
    Texture2D star;
    Texture2D coral;
    Texture2D turtle;
    Texture2D islands;
    Texture2D sharkfin;
    Texture2D sailorNoronha;
    Texture2D salesmanNoronha;
    Texture2D fishShopNoronha;
    Texture2D backgroundNoronha;
    Texture2D fishShopMenuNoronha;

} Assets;

Assets LoadAssets(void);

#endif
