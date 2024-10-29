#include "init.h"
#include "raylib.h"

int frames = 0;

Assets LoadAssets(void) {
    Assets assets;
    assets.logoTexture = LoadTexture("assets/icons/logo.png");
    assets.fishPedia = LoadTexture("assets/icons/fishpedia.png");
    assets.fishPedia2 = LoadTexture("assets/icons/fishpedia2.png");
    assets.arrow = LoadTexture("assets/icons/arrow.png");
    assets.exitButton = LoadTexture("assets/menu/exitButton.png");
    assets.anunciacao = LoadSound("assets/sounds/anunciacao.WAV");
    assets.morenaTropicana = LoadSound("assets/sounds/morena-tropicana.WAV");
    assets.fishBucket = LoadTexture("assets/icons/fishbucket.png");
    assets.startButton = LoadTexture("assets/menu/startButton.png");
    assets.fishShop = LoadTexture("assets/marco_zero/fishshop.png");
    assets.backgroundMarcoZero = LoadTexture("assets/marco_zero/background.png");
    assets.portSign = LoadTexture("assets/marco_zero/portoSign.png");
    assets.backgroundMenu = LoadTexture("assets/menu/background.png");
    assets.labelledejour = LoadSound("assets/sounds/labelledejour.WAV");
    assets.darkExitButton = LoadTexture("assets/menu/darkExitButton.png");
    assets.darkStartButton = LoadTexture("assets/menu/darkStartButton.png");
    assets.boat = LoadTexture("assets/marco_zero/boat.png");
    assets.button = LoadTexture("assets/icons/button.png");
    assets.coin = LoadTexture("assets/icons/coin.png");
    return assets;
}
