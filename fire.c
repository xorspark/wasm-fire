#include "engine.h"

const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;

unsigned int display[SCREEN_WIDTH * SCREEN_HEIGHT] = {36};

unsigned int* getDisplay() {
    return display;
}

const unsigned int getScreenWidth() {
    return SCREEN_WIDTH;
}

const unsigned int getScreenHeight() {
    return SCREEN_HEIGHT;
}

void setup() {
    initBuffer();
}

void update() {
    blitFire(display);
}
