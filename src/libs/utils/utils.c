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