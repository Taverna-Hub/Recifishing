#include "init.h"
#include "raylib.h"
#include "../game/game.h"

int frames = 0;

Assets LoadAssets(void) {

    Assets assets;

    assets.anunciacao = LoadMusicStream("assets/sounds/anunciacao.WAV");
    assets.labelledejour = LoadMusicStream("assets/sounds/labelledejour.WAV");
    assets.morenaTropicana = LoadMusicStream("assets/sounds/morena-tropicana.WAV");

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

    assets.fishermanHook[0] = LoadTexture("assets/frames/fisherman/hook/Fisherman_hook_01.png");
    assets.fishermanHook[1] = LoadTexture("assets/frames/fisherman/hook/Fisherman_hook_02.png");
    assets.fishermanHook[2] = LoadTexture("assets/frames/fisherman/hook/Fisherman_hook_03.png");
    assets.fishermanHook[3] = LoadTexture("assets/frames/fisherman/hook/Fisherman_hook_04.png");
    assets.fishermanHook[4] = LoadTexture("assets/frames/fisherman/hook/Fisherman_hook_05.png");
    assets.fishermanHook[5] = LoadTexture("assets/frames/fisherman/hook/Fisherman_hook_06.png");

    assets.fishermanIdle[0] = LoadTexture("assets/frames/fisherman/idle/Fisherman_idle_01.png");
    assets.fishermanIdle[1] = LoadTexture("assets/frames/fisherman/idle/Fisherman_idle_02.png");
    assets.fishermanIdle[2] = LoadTexture("assets/frames/fisherman/idle/Fisherman_idle_03.png");
    assets.fishermanIdle[3] = LoadTexture("assets/frames/fisherman/idle/Fisherman_idle_04.png");

    assets.fishermanFishing[0] = LoadTexture("assets/frames/fisherman/fishing/Fisherman_fish_01.png");
    assets.fishermanFishing[1] = LoadTexture("assets/frames/fisherman/fishing/Fisherman_fish_02.png");
    assets.fishermanFishing[2] = LoadTexture("assets/frames/fisherman/fishing/Fisherman_fish_03.png");
    assets.fishermanFishing[3] = LoadTexture("assets/frames/fisherman/fishing/Fisherman_fish_04.png");

    assets.boat = LoadTexture("assets/marco_zero/boat.png");
    assets.fish = LoadTexture("assets/marco_zero/fish.png");
    assets.sailor = LoadTexture("assets/marco_zero/sailor.png");
    assets.salesman = LoadTexture("assets/marco_zero/salesman.png");
    assets.fishShop = LoadTexture("assets/marco_zero/fishshop.png");
    assets.portSign = LoadTexture("assets/marco_zero/portoSign.png");
    assets.marcoZeroPier = LoadTexture("assets/marco_zero/pier.png");
    assets.backgroundMarcoZero = LoadTexture("assets/marco_zero/background.png");

    return assets;
}
