#include "cleanup.h"
#include "raylib.h"

void UnloadAssets(Assets* assets) {

    /* Efeitos Sonoros */
    UnloadSound(assets->fail);
    UnloadSound(assets->alert);
    UnloadSound(assets->tictac);
    UnloadSound(assets->boowomp);
    UnloadSound(assets->success);
    UnloadSound(assets->keyPress);
    UnloadSound(assets->sellSound);

    /* Trilha Sonora */
    UnloadMusicStream(assets->sol);
    UnloadMusicStream(assets->trombone);
    UnloadMusicStream(assets->borbulhas);
    UnloadMusicStream(assets->eraDomingo);
    UnloadMusicStream(assets->anunciacao);
    UnloadMusicStream(assets->labelledejour);
    UnloadMusicStream(assets->morenaTropicana);

    /* Menu Sprites */
    UnloadTexture(assets->fishFrame);
    UnloadTexture(assets->exitButton);
    UnloadTexture(assets->startButton);
    UnloadTexture(assets->fishShopMenuBG);
    UnloadTexture(assets->backgroundMenu);
    UnloadTexture(assets->darkExitButton);
    UnloadTexture(assets->darkStartButton);
    UnloadTexture(assets->bucketBackground);
    UnloadTexture(assets->fishpediaBackground);

    /* Icons Sprites */
    UnloadTexture(assets->coin);
    UnloadTexture(assets->arrow);
    UnloadTexture(assets->button);
    UnloadTexture(assets->PortoSign);
    UnloadTexture(assets->fishPedia);
    UnloadTexture(assets->MarcoSign);
    UnloadTexture(assets->buttonDark);
    UnloadTexture(assets->fishPedia2);
    UnloadTexture(assets->fishBucket);
    UnloadTexture(assets->baseButton);
    UnloadTexture(assets->sellButton);
    UnloadTexture(assets->logoTexture);
    UnloadTexture(assets->emptyButton);
    UnloadTexture(assets->fishFraming);
    UnloadTexture(assets->fishCounter);
    UnloadTexture(assets->NoronhaSign);
    UnloadTexture(assets->keyButtonBox);
    UnloadTexture(assets->baseButtonFail);
    UnloadTexture(assets->sellButtonHover);
    UnloadTexture(assets->baseButtonSpace);
    UnloadTexture(assets->baseButtonPressed);

    /* Fisherman Hook Frames */
    for (int i = 0; i < 6; i++) {
        UnloadTexture(assets->fishermanHook[i]);
    }

    /* Fisherman Idle Frames */
    for (int i = 0; i < 4; i++) {
        UnloadTexture(assets->fishermanIdle[i]);
    }

    /* Fisherman Fishing Frames */
    for (int i = 0; i < 4; i++) {
        UnloadTexture(assets->fishermanFishing[i]);
    }

    /* Water Frames */
    for (int i = 0; i < 10; i++) {
        UnloadTexture(assets->water[i]);
    }

    /* Marco Zero Fishes */
    for (int i = 0; i < 10; i++) {
        UnloadTexture(assets->marcoZeroFishes[i]);
    }

    /* Porto de Galinhas Fishes */
    for (int i = 0; i < 10; i++) {
        UnloadTexture(assets->portoFishes[i]);
    }

    /* Fernando de Noronha Fishes */
    for (int i = 0; i < 11; i++) {
        UnloadTexture(assets->noronhaFishes[i]);
    }

    /* Marco Zero Sprites */
    UnloadTexture(assets->boat);
    UnloadTexture(assets->sailor);
    UnloadTexture(assets->salesman);
    UnloadTexture(assets->fishShop);
    UnloadTexture(assets->portSign);
    UnloadTexture(assets->fishShopMenu);
    UnloadTexture(assets->marcoZeroPier);
    UnloadTexture(assets->backgroundMarcoZero);
    UnloadTexture(assets->backgroundMarcoZeroBlur);

    /* Porto de Galinhas Sprites */
    UnloadTexture(assets->portal);
    UnloadTexture(assets->chicken);
    UnloadTexture(assets->sailorPorto);
    UnloadTexture(assets->coconutLeft);
    UnloadTexture(assets->coconutRight);
    UnloadTexture(assets->fishShopPorto);
    UnloadTexture(assets->salesmanPorto);
    UnloadTexture(assets->backgroundPorto);
    UnloadTexture(assets->fishShopPortoMenu);
    UnloadTexture(assets->backgroundPortoBlur);

    /* Fernando de Noronha Sprites */
    UnloadTexture(assets->star);
    UnloadTexture(assets->coral);
    UnloadTexture(assets->turtle);
    UnloadTexture(assets->islands);
    UnloadTexture(assets->sharkfin);
    UnloadTexture(assets->sailorNoronha);
    UnloadTexture(assets->fishShopNoronha);
    UnloadTexture(assets->salesmanNoronha);
    UnloadTexture(assets->backgroundNoronha);

}
