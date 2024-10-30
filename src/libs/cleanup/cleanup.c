#include "cleanup.h"
#include "raylib.h"

void UnloadAssets(Assets assets) {

    UnloadTexture(assets.boat);
    UnloadTexture(assets.coin);
    UnloadTexture(assets.arrow);
    UnloadTexture(assets.button);
    UnloadTexture(assets.portSign);
    UnloadTexture(assets.fishShop);
    UnloadTexture(assets.fishPedia);
    UnloadTexture(assets.exitButton);
    UnloadTexture(assets.fishBucket);
    UnloadTexture(assets.startButton);
    UnloadTexture(assets.logoTexture);
    UnloadTexture(assets.backgroundMenu);
    UnloadTexture(assets.darkExitButton);
    UnloadTexture(assets.darkStartButton);
    UnloadTexture(assets.backgroundMarcoZero);

    UnloadMusicStream(assets.anunciacao);
    UnloadMusicStream(assets.labelledejour);
    UnloadMusicStream(assets.morenaTropicana);
}
