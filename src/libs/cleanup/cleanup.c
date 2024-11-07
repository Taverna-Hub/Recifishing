#include "cleanup.h"
#include "raylib.h"

void UnloadAssets(Assets assets) {

    UnloadTexture(assets.boat);
    UnloadTexture(assets.coin);
    UnloadTexture(assets.arrow);
    UnloadTexture(assets.sailor);
    UnloadTexture(assets.salesman);
    UnloadTexture(assets.button);
    UnloadTexture(assets.portSign);
    UnloadTexture(assets.fishShop);
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
    UnloadTexture(assets.fish);
    UnloadTexture(assets.baseButton);
    UnloadTexture(assets.emptyButton);
    UnloadTexture(assets.baseButtonPressed);
    UnloadTexture(assets.baseButtonFail);
    UnloadTexture(assets.baseButtonSpace);

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

    UnloadMusicStream(assets.anunciacao);
    UnloadMusicStream(assets.labelledejour);
    UnloadMusicStream(assets.morenaTropicana);
    UnloadSound(assets.keyPress);
    UnloadSound(assets.boowomp);
    UnloadSound(assets.tictac);
    UnloadSound(assets.fail);
    UnloadSound(assets.success);
}
