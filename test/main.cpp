#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"
#include<cstdlib>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <ctime>
using namespace std;
bool checkCollison(SDL_Rect& Rect1, SDL_Rect& Rect2){
if(Rect1.x+Rect1.w<Rect2.x){
    return false;
}
if(Rect1.y+Rect1.h<Rect2.y){
    return false;
}
if(Rect2.x+Rect2.w<Rect1.x){
    return false;
}
if(Rect2.y+Rect2.h<Rect1.y){
    return false;
}
return true;
}
int ship_x=350;
int ship_y=500;
int ship_speed=30;

vector <bullet> bull;

    int main(int argc, char *argv[])
{
    int HighestScore=0;
    int CurrentScore=0;
    string HighestScoreString="Highest Score: "+to_string(HighestScore);
    string CurrentScoreString="Current Score: "+to_string(CurrentScore);
    srand(static_cast<unsigned int>(time(nullptr)));
    int x_enemy = rand()%800;
    double y_enemy = 0;
    int x_enemy2 = rand()%800;
    double y_enemy2 = 0;
    Graphics graphics;
    graphics.init();
    TTF_Font* font = graphics.loadFont("font/times new roman.ttf",30);
    SDL_Color color = {255,255, 255, 0};
    SDL_Texture* highestScore = graphics.renderText(HighestScoreString.c_str(),font, color);
    SDL_Texture* currentScore = graphics.renderText(CurrentScoreString.c_str(),font, color);
    Sprite fuel;
    SDL_Texture* fuel_tex = graphics.loadTexture("image/fuel.png");
    fuel.init(fuel_tex, fuel_frames, fuel_clip);
    Mix_Music *gMusic = graphics.loadMusic("sound/91476_Glorious_morning.mp3");
    Mix_Chunk *laserShot = graphics.loadSound("sound/mixkit-short-laser-gun-shot-1670.wav");
    Mix_Chunk *explosionSound = graphics.loadSound("sound/explosionSound.MP3");
    graphics.play(gMusic);
    bool isStandingStill = true;
    bool turnLeft=false;
    bool turnRight=false;
    ScrollingBackground background;
    background.setTexture(graphics.loadTexture("image/SpaceBackground.jpg"));
    SDL_Texture*ship_tex=graphics.loadTexture("image/shipstraight.png");
    SDL_Texture*ship_right=graphics.loadTexture("image/shipturnright.png");
    SDL_Texture*ship_left=graphics.loadTexture("image/shipturnleft.png");
    SDL_Texture*enemy_tex=graphics.loadTexture("image/enemyShip.png");
    SDL_Texture*bullet_tex=graphics.loadTexture("image/redLaser.png");
    SDL_Texture*explode_tex=graphics.loadTexture("image/explode.png");
    SDL_Texture*enemy_tex2=graphics.loadTexture("image/enemyShip2.png");
    SDL_Texture *title=graphics.loadTexture("image/titleScreen.png");
    SDL_Texture*endScreen=graphics.loadTexture("image/endScreen.png");

    bool quit = false;
bool is_shotting = false;
bool die = false;
bool play = false;
SDL_Event event;
int gameState = 0;  // 0: title, 1: play, 2: die
int enemy_health=2;
while (!quit) {
    if (gameState == 0) {
        graphics.prepareScene(title);
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE) {
                    gameState = 1;  // Chuyển sang trạng thái "play"
                    break;
                } else if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
            }
        }
        graphics.presentScene();
    } else if (gameState == 1&&!die) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        isStandingStill = false;
                        turnRight = true;
                        ship_x += ship_speed;
                        break;
                    case SDLK_LEFT:
                        isStandingStill = false;
                        turnLeft = true;
                        ship_x -= ship_speed;
                        break;
                    case SDLK_UP:
                        ship_y -= ship_speed;
                        break;
                    case SDLK_DOWN:
                        ship_y += ship_speed;
                        break;
                    case SDLK_SPACE:
                        is_shotting = true;
                        graphics.play(laserShot);
                        break;
                }
                    if(ship_x+30>800){
                        ship_x=750;
                    }
                    else if(ship_y+30>600){
                        ship_y=550;
                    }
                    else if(ship_x+30<0){
                        ship_x=50;
                    }
                    else if(ship_y+30<0){
                        ship_y=50;
                    }
                    } else if (event.type == SDL_KEYUP) {
                        if (event.key.keysym.sym == SDLK_SPACE) {
                            is_shotting = false;
                            break;}
                       else if (event.key.keysym.sym == SDLK_LEFT) {
                            isStandingStill=true;
                            turnLeft=false;
                        break;}
                       else if (event.key.keysym.sym == SDLK_RIGHT) {
                            isStandingStill=true;
                            turnRight=false;
                        break;}
                    }
}
                    if (is_shotting) {
                    bullet bullets;
                    bullets.bulletX = ship_x +45 ;
                    bullets.bulletY = ship_y - 10;
                    bullets.bulletSpeed = 10;
                    bull.push_back(bullets);
                    is_shotting = false;
                }
                 int size=bull.size();
                for (int i = 0; i < size; i++) {
                    bull[i].bulletY -= bull[i].bulletSpeed;
                    if (bull[i].bulletX > 800) {
                        bull.erase(bull.begin() + i);
                        i--;
                        size--;
                    }
                }
          if(turnLeft){
            graphics.renderTexture(ship_left, ship_x, ship_y, 100, 80);
          }
          if(turnRight){
            graphics.renderTexture(ship_right, ship_x, ship_y, 100, 80);
          }

if (isStandingStill) {
        graphics.renderTexture(ship_tex, ship_x, ship_y, 100, 80);}

            y_enemy += 2;

                if (y_enemy + 30 >= 600) {

                    y_enemy = 0 ;
                    x_enemy = rand() % 700;
                }
                y_enemy2 += 2;

                if (y_enemy2 + 30 >= 600) {

                    y_enemy2 = 0 ;
                    x_enemy2 = rand() % 700;
                }
        SDL_Rect enemyRect = {x_enemy, y_enemy,90,60};
        SDL_Rect enemyRect2 = {x_enemy2, y_enemy2,90,60};
        SDL_Rect playerRect={ship_x,ship_y,90,60};
        for(int i = 0; i < size; i++){
                SDL_Rect bullet_ = {bull[i].bulletX, bull[i].bulletY, 10 , 10};
                graphics.renderTexture(bullet_tex,bull[i].bulletX,bull[i].bulletY,10,10);
         if(checkCollison(bullet_,enemyRect) == true){
                    CurrentScore++;
            if(HighestScore<CurrentScore){
            HighestScore=CurrentScore;
         }
                    graphics.play(explosionSound);
                    graphics.renderTexture(explode_tex,x_enemy,y_enemy,200,200);
                    //SDL_Delay(100);
                    y_enemy = 600;
                    x_enemy = rand()%800;
                    bull.erase(bull.begin() + i);
                        i--;
                        size--;
                }
                else if(checkCollison(bullet_,enemyRect2) == true){
                        if(enemy_health==0){
                                graphics.play(explosionSound);
                    graphics.renderTexture(explode_tex,x_enemy2,y_enemy2,200,200);
                    //SDL_Delay(100);
                    y_enemy2 = 600;
                    x_enemy2 = rand()%800;
                    CurrentScore+=2;
                    enemy_health=2;}
                    if(HighestScore<CurrentScore){
            HighestScore=CurrentScore;
         }          enemy_health--;
                    bull.erase(bull.begin() + i);
                        i--;
                        size--;
                }}
            if(checkCollison(playerRect,enemyRect2)||checkCollison(playerRect,enemyRect)){
                    y_enemy2 = 600;
                    x_enemy2 = rand()%800;
            y_enemy = 600;
                    x_enemy = rand()%800;
                gameState=2;
                die=true;
            }
        HighestScoreString="Highest Score: "+to_string(HighestScore);
        CurrentScoreString="Current Score: "+to_string(CurrentScore);
        highestScore = graphics.renderText(HighestScoreString.c_str(),font, color);
        currentScore = graphics.renderText(CurrentScoreString.c_str(),font, color);
        graphics.renderTexture(highestScore, 20, 20);
        graphics.renderTexture(currentScore,20,50);
            fuel.tick();
            graphics.renderAni(ship_x+22,ship_y+26, fuel);
                background.scroll(1);
        graphics.renderTexture(enemy_tex2,x_enemy2,y_enemy2,100,80);
        graphics.renderTexture(enemy_tex,x_enemy,y_enemy,100,80);
        graphics.presentScene();

        graphics.render(background);

       // graphics.presentScene();
        //SDL_Delay(0);
    }
else if (gameState == 2) {
        HighestScoreString="Highest Score: "+to_string(HighestScore);
        CurrentScoreString="Current Score: "+to_string(CurrentScore);
        highestScore = graphics.renderText(HighestScoreString.c_str(),font, color);
        currentScore = graphics.renderText(CurrentScoreString.c_str(),font, color);
        graphics.prepareScene(endScreen);
        graphics.renderTexture(highestScore, 280, 400);
        graphics.renderTexture(currentScore,280,430);
        SDL_Event e1;
        while (SDL_PollEvent(&e1) != 0) {
            if (e1.type == SDL_KEYDOWN) {
                if (e1.key.keysym.sym == SDLK_SPACE) {
                    CurrentScore=0;
                    enemy_health=2;
                    gameState = 1;
                    die=false;
                    break;
                } else if (e1.key.keysym.sym == SDLK_ESCAPE) {
                    quit=true;
                }
            }
        }
        graphics.presentScene();
    }
}
SDL_DestroyTexture( highestScore );
    TTF_CloseFont( font );
    highestScore = NULL;
    SDL_DestroyTexture( fuel_tex ); fuel_tex = nullptr;
    SDL_DestroyTexture( background.texture );
    graphics.quit();
    return 0;
}
