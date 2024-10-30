#include "init.h"
#include "raylib.h"

int frames = 0;

Assets LoadAssets(void) {

    Assets assets;

    assets.coin = LoadTexture("assets/icons/coin.png");
    assets.arrow = LoadTexture("assets/icons/arrow.png");
    assets.button = LoadTexture("assets/icons/button.png");
    assets.logoTexture = LoadTexture("assets/icons/logo.png");
    assets.fishPedia = LoadTexture("assets/icons/fishpedia.png");
    assets.fishPedia2 = LoadTexture("assets/icons/fishpedia2.png");
    assets.fishBucket = LoadTexture("assets/icons/fishbucket.png");

    assets.exitButton = LoadTexture("assets/menu/exitButton.png");
    assets.startButton = LoadTexture("assets/menu/startButton.png");
    assets.backgroundMenu = LoadTexture("assets/menu/background.png");
    assets.darkExitButton = LoadTexture("assets/menu/darkExitButton.png");
    assets.darkStartButton = LoadTexture("assets/menu/darkStartButton.png");

    assets.boat = LoadTexture("assets/marco_zero/boat.png");
    assets.fishShop = LoadTexture("assets/marco_zero/fishshop.png");
    assets.portSign = LoadTexture("assets/marco_zero/portoSign.png");
    assets.backgroundMarcoZero = LoadTexture("assets/marco_zero/background.png");

    assets.anunciacao = LoadMusicStream("assets/sounds/anunciacao.WAV");
    assets.labelledejour = LoadMusicStream("assets/sounds/labelledejour.WAV");
    assets.morenaTropicana = LoadMusicStream("assets/sounds/morena-tropicana.WAV");

    return assets;
}
