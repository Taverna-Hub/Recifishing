#include <raylib.h>
#ifndef UTILS_H
#define UTILS_H

Rectangle imageToRectangle(Texture2D image, int x, int y);

typedef enum GameScreen { 
    MENU = 0, 
    GAME = 1
} GameScreen;

#endif 