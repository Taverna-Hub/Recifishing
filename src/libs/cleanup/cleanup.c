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
    UnloadTexture(assets.fishPedia);
    UnloadTexture(assets.exitButton);
    UnloadTexture(assets.fishBucket);
    UnloadTexture(assets.startButton);
    UnloadTexture(assets.logoTexture);
    UnloadTexture(assets.marcoZeroPier);
    UnloadTexture(assets.backgroundMenu);
    UnloadTexture(assets.darkExitButton);
    UnloadTexture(assets.darkStartButton);
    UnloadTexture(assets.backgroundMarcoZero);
    UnloadTexture(assets.fish);
    UnloadTexture(assets.baseButton);
    UnloadTexture(assets.baseButtonSpace);

    UnloadTexture(assets.fishermanHook[0]);
    UnloadTexture(assets.fishermanHook[1]);
    UnloadTexture(assets.fishermanHook[2]);
    UnloadTexture(assets.fishermanHook[3]);
    UnloadTexture(assets.fishermanHook[4]);
    UnloadTexture(assets.fishermanHook[5]);

    UnloadTexture(assets.fishermanIdle[0]);
    UnloadTexture(assets.fishermanIdle[1]);
    UnloadTexture(assets.fishermanIdle[2]);
    UnloadTexture(assets.fishermanIdle[3]);

    UnloadTexture(assets.fishermanFishing[0]);
    UnloadTexture(assets.fishermanFishing[1]);
    UnloadTexture(assets.fishermanFishing[2]);
    UnloadTexture(assets.fishermanFishing[3]);

    UnloadMusicStream(assets.anunciacao);
    UnloadMusicStream(assets.labelledejour);
    UnloadMusicStream(assets.morenaTropicana);
    UnloadSound(assets.spacePress);
}
