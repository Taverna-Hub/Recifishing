#include "cleanup.h"
#include "raylib.h"

void UnloadAssets(Assets assets) {
    UnloadTexture(assets.logoTexture);
    UnloadTexture(assets.fishPedia);
    UnloadTexture(assets.fishBucket);
    UnloadTexture(assets.exitButton);
    UnloadTexture(assets.startButton);
    UnloadTexture(assets.backgroundMenu);
    UnloadTexture(assets.darkExitButton);
    UnloadTexture(assets.darkStartButton);
    UnloadTexture(assets.portSign);
    UnloadTexture(assets.fishShop);
    UnloadSound(assets.labelledejour);
    UnloadSound(assets.anunciacao);
    UnloadSound(assets.morenaTropicana);
}