	#include <raylib.h>
	#include "utils.h"
	#include <stdlib.h>
	/* #include "../game/game.h" */

	Rectangle imageToRectangle(Texture2D image, int x, int y) {
		Rectangle rec;
		rec.x = x;
		rec.y = y;
		rec.width = image.width;
		rec.height = image.height;
		return rec;
	}
	