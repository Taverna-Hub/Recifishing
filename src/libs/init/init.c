#include "init.h"
#include "raylib.h"

Assets LoadAssets(void) {
    Assets assets;
    assets.logoTexture = LoadTexture("assets/icons/logo.png");
    assets.fishPedia = LoadTexture("assets/icons/fishpedia.png");
    assets.exitButton = LoadTexture("assets/menu/exitButton.png");
    assets.anunciacao = LoadSound("assets/sounds/anunciacao.WAV");
    assets.morenaTropicana = LoadSound("assets/sounds/morena-tropicana.WAV");
    assets.fishBucket = LoadTexture("assets/icons/fishbucket.png");
    assets.startButton = LoadTexture("assets/menu/startButton.png");
    assets.fishShop = LoadTexture("assets/marco_zero/fishshop.png");
    assets.portSign = LoadTexture("assets/marco_zero/portosign.png");
    assets.backgroundMenu = LoadTexture("assets/menu/background.png");
    assets.labelledejour = LoadSound("assets/sounds/labelledejour.WAV");
    assets.darkExitButton = LoadTexture("assets/menu/darkExitButton.png");
    assets.darkStartButton = LoadTexture("assets/menu/darkStartButton.png");
    return assets;
}
