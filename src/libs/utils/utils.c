#include <raylib.h>
#include "utils.h"

Rectangle imageToRectangle(Texture2D image, int x, int y) {
    Rectangle rec;
    rec.x = x;
    rec.y = y;
    rec.width = image.width;
    rec.height = image.height;
    return rec;
}

int indexOf(int *arr, int c) {
    int cont = 0;
    for (int i = 0; arr[i] != '\0'; i++) {
        cont++;
    }
    return cont;  
}

