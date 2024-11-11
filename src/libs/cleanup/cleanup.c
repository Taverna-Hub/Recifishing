#include "cleanup.h"
#include "raylib.h"

void UnloadAssets(Assets assets) {

    UnloadTexture(assets.boat);
    UnloadTexture(assets.coin);
    UnloadTexture(assets.arrow);
    UnloadTexture(assets.sailor);
    UnloadTexture(assets.salesman);
    UnloadTexture(assets.button);
    UnloadTexture(assets.buttonDark);
    UnloadTexture(assets.portSign);
    UnloadTexture(assets.fishShop);
    UnloadTexture(assets.fishShopMenu);
    UnloadTexture(assets.fishShopMenuBG);
    UnloadTexture(assets.fishCounter);
    UnloadTexture(assets.fishFraming);
    UnloadTexture(assets.fishPedia);
    UnloadTexture(assets.exitButton);
    UnloadTexture(assets.fishBucket);
    UnloadTexture(assets.startButton);
    UnloadTexture(assets.logoTexture);
    UnloadTexture(assets.marcoZeroPier);
    UnloadTexture(assets.marcoZeroPierRight);
    UnloadTexture(assets.backgroundMenu);
    UnloadTexture(assets.darkExitButton);
    UnloadTexture(assets.darkStartButton);
    UnloadTexture(assets.backgroundMarcoZero);
    UnloadTexture(assets.backgroundMarcoZeroBlur);
    UnloadTexture(assets.fish);
    UnloadTexture(assets.sellButton);
    UnloadTexture(assets.sellButtonHover);
    UnloadTexture(assets.baseButton);
    UnloadTexture(assets.emptyButton);
    UnloadTexture(assets.baseButtonPressed);
    UnloadTexture(assets.baseButtonFail);
    UnloadTexture(assets.baseButtonSpace);

    UnloadTexture(assets.sailorPorto);
    UnloadTexture(assets.salesmanPorto);
    UnloadTexture(assets.coconutLeft);
    UnloadTexture(assets.coconutRight);
    UnloadTexture(assets.chicken);
    UnloadTexture(assets.portal);
    UnloadTexture(assets.backgroundPorto);
    UnloadTexture(assets.fishShopPorto);
    UnloadTexture(assets.fishShopPortoMenu);
    UnloadTexture(assets.backgroundPortoBlur);

    UnloadTexture(assets.sailorNoronha);
    UnloadTexture(assets.salesmanNoronha);
    UnloadTexture(assets.coral);
    UnloadTexture(assets.islands);
    UnloadTexture(assets.sharkfin);
    UnloadTexture(assets.star);
    UnloadTexture(assets.turtle);
    UnloadTexture(assets.backgroundNoronha);


    for (int i = 0; i < 5; i++){
        UnloadTexture(assets.fishermanHook[i]);
    }

    for (int i = 0; i < 3; i++) {
        UnloadTexture(assets.fishermanFishing[i]);
        UnloadTexture(assets.fishermanIdle[i]);
    }

    UnloadTexture(assets.keyButtonBox);

    UnloadTexture(assets.fishpediaBackground);
    UnloadTexture(assets.bucketBackground);
    UnloadTexture(assets.fishFrame);

    for (int i = 0; i < 10; i++) {
        UnloadTexture(assets.water[i]);
    }

    for (int i = 0; i < 10; i++){
        UnloadTexture(assets.marcoZeroFishes[i]);
    }
    for (int i = 0; i < 10; i++){
        UnloadTexture(assets.portoFishes[i]);
    }

    for (int i = 0; i < 11; i++){
        UnloadTexture(assets.noronhaFishes[i]);
    }

    UnloadTexture(assets.MarcoSign);
    UnloadTexture(assets.PortoSign);
    UnloadTexture(assets.NoronhaSign);

    UnloadMusicStream(assets.anunciacao);
    UnloadMusicStream(assets.labelledejour);
    UnloadMusicStream(assets.morenaTropicana);
    UnloadSound(assets.keyPress);
    UnloadSound(assets.boowomp);
    UnloadSound(assets.tictac);
    UnloadSound(assets.fail);
    UnloadSound(assets.success);
    UnloadSound(assets.alert);
    UnloadSound(assets.sellSound);
}
