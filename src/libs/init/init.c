#include "init.h"
#include "raylib.h"
#include "../game/game.h"

#include <stdio.h>

int frames = 0;

Assets LoadAssets(void) {

    Assets assets;

    assets.anunciacao = LoadMusicStream("assets/sounds/anunciacao.WAV");
    assets.labelledejour = LoadMusicStream("assets/sounds/labelledejour.WAV");
    assets.morenaTropicana = LoadMusicStream("assets/sounds/morena-tropicana.WAV");
    assets.keyPress = LoadSound("assets/sounds/spacePress.wav");
    assets.boowomp = LoadSound("assets/sounds/boowomp.mp3");
    assets.tictac = LoadSound("assets/sounds/tictac.mp3");
    assets.fail = LoadSound("assets/sounds/fail.wav");
    assets.alert = LoadSound("assets/sounds/alert.wav");
    assets.success = LoadSound("assets/sounds/success.mp3");
    assets.sellSound = LoadSound("assets/sounds/sellSound.mp3");

    assets.bucketBackground=LoadTexture("assets/menu/bucketbg.png");
    assets.fishpediaBackground=LoadTexture("assets/menu/fishpediabg.png");
    assets.fishFrame=LoadTexture("assets/menu/fishframing.png");
    assets.MarcoSign=LoadTexture("assets/icons/symbolmarcozero.png");
    assets.PortoSign=LoadTexture("assets/icons/symbolporto.png");
    assets.NoronhaSign=LoadTexture("assets/icons/symbolnoronha.png");

    assets.coin = LoadTexture("assets/icons/coin.png");
    assets.arrow = LoadTexture("assets/icons/arrow.png");
    assets.button = LoadTexture("assets/icons/button.png");
    assets.buttonDark = LoadTexture("assets/icons/darkbuttonTemplate.png");
    assets.logoTexture = LoadTexture("assets/icons/logo.png");
    assets.fishPedia = LoadTexture("assets/icons/fishpedia.png");
    assets.fishPedia2 = LoadTexture("assets/icons/fishpedia2.png");
    assets.fishBucket = LoadTexture("assets/icons/fishbucket.png");
    assets.baseButton = LoadTexture("assets/icons/baseButton.png");
    assets.emptyButton = LoadTexture("assets/icons/emptyButton.png");
    assets.baseButtonPressed = LoadTexture("assets/icons/baseButtonPressed.png");
    assets.baseButtonFail = LoadTexture("assets/icons/baseButtonFail.png");
    assets.baseButtonSpace = LoadTexture("assets/icons/basebuttonspaceBarra.png");
    assets.keyButtonBox = LoadTexture("assets/icons/keyButtonBox.png");
    assets.fishFraming = LoadTexture("assets/icons/fishframing.png");
    assets.fishCounter = LoadTexture("assets/icons/fishcounter.png");
    assets.sellButton = LoadTexture("assets/icons/sellbutton.png");
    assets.sellButtonHover = LoadTexture("assets/icons/sellbuttonHover.png");

    assets.exitButton = LoadTexture("assets/menu/exitButton.png");
    assets.startButton = LoadTexture("assets/menu/startButton.png");
    assets.backgroundMenu = LoadTexture("assets/menu/background.png");
    assets.darkExitButton = LoadTexture("assets/menu/darkExitButton.png");
    assets.darkStartButton = LoadTexture("assets/menu/darkStartButton.png");
    assets.fishShopMenuBG = LoadTexture("assets/menu/fishingshopMenuBG.png");

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

    for (int i = 0; i < 10; i++) {
        char filePath[50];
        sprintf(filePath, "assets/frames/water/water%d.png", i); 
        assets.water[i] = LoadTexture(filePath);
    }

    assets.boat = LoadTexture("assets/marco_zero/boat.png");
    assets.marcoZeroFishes[0] = LoadTexture("assets/marco_zero/fishes/aligator.png");
    assets.marcoZeroFishes[1] = LoadTexture("assets/marco_zero/fishes/cesarfish.png");
    assets.marcoZeroFishes[2] = LoadTexture("assets/marco_zero/fishes/chicofish.png");
    assets.marcoZeroFishes[3] = LoadTexture("assets/marco_zero/fishes/frevofish.png");
    assets.marcoZeroFishes[4] = LoadTexture("assets/marco_zero/fishes/maloka.png");
    assets.marcoZeroFishes[5] = LoadTexture("assets/marco_zero/fishes/nauticofish.png");
    assets.marcoZeroFishes[6] = LoadTexture("assets/marco_zero/fishes/santacruzfish.png");
    assets.marcoZeroFishes[7] = LoadTexture("assets/marco_zero/fishes/sportfish.png");
    assets.marcoZeroFishes[8] = LoadTexture("assets/marco_zero/fishes/bokus.png");
    assets.marcoZeroFishes[9] = LoadTexture("assets/marco_zero/fishes/hairyleg.png");

    assets.portoFishes[0] = LoadTexture("assets/porto_de_galinhas/fishes/chickenfish.png");
    assets.portoFishes[1] = LoadTexture("assets/porto_de_galinhas/fishes/crab.png");
    assets.portoFishes[2] = LoadTexture("assets/porto_de_galinhas/fishes/flounder.png");
    assets.portoFishes[3] = LoadTexture("assets/porto_de_galinhas/fishes/goldfish.png");
    assets.portoFishes[4] = LoadTexture("assets/porto_de_galinhas/fishes/magikarp.png");
    assets.portoFishes[5] = LoadTexture("assets/porto_de_galinhas/fishes/maracatu.png");
    assets.portoFishes[6] = LoadTexture("assets/porto_de_galinhas/fishes/pufferfish.png");
    assets.portoFishes[7] = LoadTexture("assets/porto_de_galinhas/fishes/rossifish.png");
    assets.portoFishes[8] = LoadTexture("assets/porto_de_galinhas/fishes/brokencd.png");
    assets.portoFishes[9] = LoadTexture("assets/porto_de_galinhas/fishes/heinekin.png");

    assets.noronhaFishes[0] = LoadTexture("assets/fernando_de_noronha/fishes/eel.png");
    assets.noronhaFishes[1] = LoadTexture("assets/fernando_de_noronha/fishes/lionfish.png");
    assets.noronhaFishes[2] = LoadTexture("assets/fernando_de_noronha/fishes/octopus.png");
    assets.noronhaFishes[3] = LoadTexture("assets/fernando_de_noronha/fishes/salmon.png");
    assets.noronhaFishes[4] = LoadTexture("assets/fernando_de_noronha/fishes/sardine.png");
    assets.noronhaFishes[5] = LoadTexture("assets/fernando_de_noronha/fishes/shark.png");
    assets.noronhaFishes[6] = LoadTexture("assets/fernando_de_noronha/fishes/stingray.png");
    assets.noronhaFishes[7] = LoadTexture("assets/fernando_de_noronha/fishes/straw.png");
    assets.noronhaFishes[8] = LoadTexture("assets/fernando_de_noronha/fishes/swordfish.png");
    assets.noronhaFishes[9] = LoadTexture("assets/fernando_de_noronha/fishes/tuna.png");
    assets.noronhaFishes[10] = LoadTexture("assets/fernando_de_noronha/fishes/trashbag.png");

    assets.sailor = LoadTexture("assets/marco_zero/sailor.png");
    assets.salesman = LoadTexture("assets/marco_zero/salesman.png");
    assets.fishShop = LoadTexture("assets/marco_zero/fishshop.png");
    assets.fishShopPorto = LoadTexture("assets/porto_de_galinhas/fishshop.png");
    assets.fishShopPortoMenu = LoadTexture("assets/porto_de_galinhas/menuPorto.png");
    assets.fishShopMenu = LoadTexture("assets/marco_zero/fishshopMenu.png");
    assets.portSign = LoadTexture("assets/marco_zero/portoSign.png");
    assets.marcoZeroPier = LoadTexture("assets/marco_zero/pier.png");
    assets.marcoZeroPierRight = LoadTexture("assets/marco_zero/pierRight.png");
    assets.backgroundMarcoZero = LoadTexture("assets/marco_zero/background.png");
    assets.backgroundMarcoZeroBlur = LoadTexture("assets/marco_zero/backgroundBlur.png");

    assets.sailorPorto = LoadTexture("assets/porto_de_galinhas/sailorporto.png");
    assets.salesmanPorto = LoadTexture("assets/porto_de_galinhas/salesmanporto.png");
    assets.coconutLeft = LoadTexture("assets/porto_de_galinhas/coconutL.png");
    assets.coconutRight = LoadTexture("assets/porto_de_galinhas/coconutR.png");
    assets.chicken = LoadTexture("assets/porto_de_galinhas/chicken.png");
    assets.portal = LoadTexture("assets/porto_de_galinhas/portal.png");
    assets.backgroundPorto = LoadTexture("assets/porto_de_galinhas/porto_galinhas_bg.png");
    assets.backgroundPortoBlur = LoadTexture("assets/porto_de_galinhas/portobg.png");

    assets.sailorNoronha = LoadTexture("assets/fernando_de_noronha/sailornoronha.png");
    assets.salesmanNoronha = LoadTexture("assets/fernando_de_noronha/salesmannoronha.png");
    assets.coral = LoadTexture("assets/fernando_de_noronha/coral.png");
    assets.islands = LoadTexture("assets/fernando_de_noronha/islands.png");
    assets.sharkfin = LoadTexture("assets/fernando_de_noronha/sharkfin.png");
    assets.star = LoadTexture("assets/fernando_de_noronha/star.png");
    assets.turtle = LoadTexture("assets/fernando_de_noronha/turtle.png");


    return assets;
}
