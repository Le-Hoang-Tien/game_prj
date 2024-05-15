#ifndef _DEFS__H
#define _DEFS__H

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define WINDOW_TITLE "Space Shooter"

//#define BACKGROUND_IMG "img\\forest.jpg"
#define BACKGROUND_IMG "img\\123456.png"
const int fuel_clip[][4] = {
    { 80, 0, 60, 190},
    { 140, 0,60,190},
    { 205,0,60,190},
    { 265,0,60,190}};
const int fuel_frames = sizeof(fuel_clip)/sizeof(int)/4;
struct bullet{
int bulletX;
int bulletY;
int bulletSpeed;
int bulletWidth=30;
int bulletHeight=10;
};
#endif
