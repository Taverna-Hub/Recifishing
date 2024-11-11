#ifndef GAME_H
#define GAME_H

#include "../init/init.h"
#include "../utils/utils.h"

typedef struct Arrow {
    int arrowFrames;
    int direction;
}Arrow;

typedef enum GameFrames {
    DEFAULT = 0,
    FISHPEDIA = 1,
    BUCKET = 2,
    PORT = 3,
    FISHSHOP = 4,
    PIER = 5,
} GameFrames;

typedef enum LocationName {
    MARCO_ZERO = 0,
    PORTO_DE_GALINHAS = 1,
    FERNANDO_DE_NORONHA = 2,
} LocationName;

typedef struct Frame {
    int frame;
    int isUsing;
    int direction;
    int x;
    int y;
    int finalX;
    int finalY;
    int velX;
    int velY;
}Frame;

typedef struct Fish {

    char name[30];
    int price;
    int letters;
    Texture2D sprite;
    struct Fish *next;
    struct Fish *prev;
    bool isTrash;
    bool wasCaptured;
    LocationName locationName;

}Fish;

typedef struct Fishpedia {
    Fish *fish;
    struct Fishpedia *next;
    struct Fishpedia *prev;
} Fishpedia;

typedef struct Bucket {
    Fish *fish;
    struct Bucket *next;
    struct Bucket *prev;
} Bucket;

typedef struct Location {

    LocationName name;
    Fish *firstFish;
    Texture2D background;
    Texture2D backgroundBlur;
    Texture2D sailor;
    Texture2D salesman;
    Texture2D pier;
    Texture2D pierRight;
    Texture2D boat;
    Texture2D fishShop;
    Texture2D fishShopMenu;
    Color pierFilter;
    Music defaultMusic;
    Music fishingMusic;

}Location;


typedef struct AnimationFrames {
    int throwingRodAnimation;
    int pullingRodAnimation;
    Frame *fishingRod;
    Frame *fishmanIdle;
    Frame *fishmanFishing;
    Frame *fishmanHook;
    Vector2 rodPoints[10000];
    int rodPointCount;
} AnimationFrames;

typedef enum FishpediaPage {
    MARCO_ZERO_PAGE,
    PORTO_DE_GALINHAS_PAGE,
    FERNANDO_DE_NORONHA_PAGE
} FishpediaPage;

Arrow* createArrow();
AnimationFrames* createAnimationFrames();
void updateArrow(Arrow *arrow);

int cursorHandle(Vector2 mousePos, Texture2D button, Texture2D bucket, Texture2D fishpedia, int gameFrame);
void fadeHandle(bool *inTransition, int *fadeAlpha);

void UpdateGame(bool *inTransition, GameScreen *currentScreen, Arrow *arrow, Arrow *arrow2, Vector2 mousePos, Assets assets, int *gameFrame, AnimationFrames **animationFrames, Location *location,int *fadeAlpha);
void DrawGame(bool *inTransition, int *fadeAlpha, Assets assets, bool *isSoundPlayed, int arrowFrames,int arrowFrames2, Vector2 mousePos, int frame, AnimationFrames **animationFrames, Location *location);
Location* startLocation(LocationName locationName, Assets assets);
void insertFish(Fish **head, char *name, int price, int letters, Texture2D sprite, LocationName locationName);
void removeFish(Fish **head);
void initializeFishLists(Assets assets);



#endif
