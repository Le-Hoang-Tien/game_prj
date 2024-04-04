#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"

using namespace std;

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture("SpaceBackground.jpg"));
    SDL_Texture*ship_tex=graphics.loadTexture("playerShip1_blue.png");
    bool quit = false;
    SDL_Event e;
    while( !quit ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) quit = true;
        }
        graphics.renderTexture(ship_tex,200,200);

        graphics.presentScene();
        background.scroll(1);

        graphics.render(background);

       // graphics.presentScene();
        SDL_Delay(100);
    }

    SDL_DestroyTexture( background.texture );
    graphics.quit();
    return 0;
}
