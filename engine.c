#include "util.h"

const unsigned int FIRE_WIDTH = 640;
const unsigned int FIRE_HEIGHT = 480; 

// Palette based framebuffer. Coordinate system origin upper-left.
unsigned int firePixels[FIRE_WIDTH * FIRE_HEIGHT];

// packed in reverse
#define rgba(r, g, b, a) (unsigned int)((a<<24) + (b<<16) + (g<<8) + r)

const unsigned int palette[37] = {
    rgba(0x07, 0x07, 0x07, 0xFF),
    rgba(0x1F, 0x07, 0x07, 0xFF),
    rgba(0x2F, 0x0F, 0x07, 0xFF),
    rgba(0x47, 0x0F, 0x07, 0xFF),
    rgba(0x57, 0x17, 0x07, 0xFF),
    rgba(0x67, 0x1F, 0x07, 0xFF),
    rgba(0x77, 0x1F, 0x07, 0xFF),
    rgba(0x8F, 0x27, 0x07, 0xFF),
    rgba(0x9F, 0x2F, 0x07, 0xFF),
    rgba(0xAF, 0x3F, 0x07, 0xFF),
    rgba(0xBF, 0x47, 0x07, 0xFF),
    rgba(0xC7, 0x47, 0x07, 0xFF),
    rgba(0xDF, 0x4F, 0x07, 0xFF),
    rgba(0xDF, 0x57, 0x07, 0xFF),
    rgba(0xDF, 0x57, 0x07, 0xFF),
    rgba(0xD7, 0x5F, 0x07, 0xFF),
    rgba(0xD7, 0x5F, 0x07, 0xFF),
    rgba(0xD7, 0x67, 0x0F, 0xFF),
    rgba(0xCF, 0x6F, 0x0F, 0xFF),
    rgba(0xCF, 0x77, 0x0F, 0xFF),
    rgba(0xCF, 0x7F, 0x0F, 0xFF),
    rgba(0xCF, 0x87, 0x17, 0xFF),
    rgba(0xC7, 0x87, 0x17, 0xFF),
    rgba(0xC7, 0x8F, 0x17, 0xFF),
    rgba(0xC7, 0x97, 0x1F, 0xFF),
    rgba(0xBF, 0x9F, 0x1F, 0xFF),
    rgba(0xBF, 0x9F, 0x1F, 0xFF),
    rgba(0xBF, 0xA7, 0x27, 0xFF),
    rgba(0xBF, 0xA7, 0x27, 0xFF),
    rgba(0xBF, 0xAF, 0x2F, 0xFF),
    rgba(0xB7, 0xAF, 0x2F, 0xFF),
    rgba(0xB7, 0xB7, 0x2F, 0xFF),
    rgba(0xB7, 0xB7, 0x37, 0xFF),
    rgba(0xCF, 0xCF, 0x6F, 0xFF),
    rgba(0xDF, 0xDF, 0x9F, 0xFF),
    rgba(0xEF, 0xEF, 0xC7, 0xFF),
    rgba(0xFF, 0xFF, 0xFF, 0xFF)
};

void initBuffer() {
    int i;
    // Set whole screen to 0 (color: 0x07,0x07,0x07)
    for(i = 0; i < FIRE_WIDTH*FIRE_HEIGHT; i++) {
        firePixels[i] = 0;
    }

    // Set bottom line to 36 (color white: 0xFF,0xFF,0xFF)
    for(i = 0; i < FIRE_WIDTH; i++) {
        firePixels[(FIRE_HEIGHT-1)*FIRE_WIDTH + i] = 36;
    }
}

unsigned int spreadFire(unsigned int src) {
    unsigned int pixel = firePixels[src];
    if(pixel == 0) {
        return (firePixels[src - FIRE_WIDTH] = 0);
    } else {
        // the original rounds the index but not rounding it makes it look like somewhat windy.
        unsigned int randIdx = (unsigned int)((genrand() * 3.0));
        unsigned int dst = src - randIdx + 1;
        return (firePixels[dst - FIRE_WIDTH ] = pixel - (randIdx & 1));
    }
}

void blitFire(unsigned int *display) {
    int x;
    int y;
    for(x = 0; x < FIRE_WIDTH; x++) {
        for (y = 1; y < FIRE_HEIGHT; y++) {
            // The original sets opacity based on color in order to overlay the Doom logo,
            // but I didn't bother with that in the palette declaration.
            display[y * FIRE_WIDTH + x] = palette[spreadFire(y * FIRE_WIDTH + x)];
        }
    }
}
