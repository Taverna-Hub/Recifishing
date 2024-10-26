#include <raylib.h>
#define UTILS_H

Rectangle imageToRectangle (Texture2D image, int x, int y){
    Rectangle rec;
    rec.x = x;
    rec.y = y;
    rec.height = image.height;
    rec.width = image.width;

    return rec;
}
