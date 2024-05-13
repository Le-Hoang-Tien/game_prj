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
    int bulletRemain=5;
    int HighestScore=0;
    int CurrentScore=0;
    string HighestScoreString="Highest Score: "+to_string(HighestScore);
    string CurrentScoreString="Current Score: "+to_string(CurrentScore);
    string RemainingBullet="Remaining Bullets: "+to_string(bulletRemain);
    srand(static_cast<unsigned int>(time(nullptr)));
    bullet dropBullet1;
    bullet dropBullet2;
        dropBullet1.bulletX=rand()%800;
        dropBullet1.bulletY=-200;
        dropBullet2.bulletX=rand()%800;
        dropBullet2.bulletY=-400;
    int x_enemy = rand()%800;
    double y_enemy = 0;
    int x_enemy2 = rand()%800;
    double y_enemy2 = -150;
    Graphics graphics;
    graphics.init();
    TTF_Font* font = graphics.loadFont("font/times new roman.ttf",30);
    SDL_Color color = {255,255, 255, 0};
    SDL_Texture* highestScore = graphics.renderText(HighestScoreString.c_str(),font, color);
    SDL_Texture* currentScore = graphics.renderText(CurrentScoreString.c_str(),font, color);
    SDL_Texture* remainingBullets = graphics.renderText(CurrentScoreString.c_str(),font, color);
    Sprite fuel;
    SDL_Texture* fuel_tex = graphics.loadTexture("image/fuel.png");
    fuel.init(fuel_tex, fuel_frames, fuel_clip);
    Mix_Music *gMusic = graphics.loadMusic("sound/91476_Glorious_morning.mp3");
    Mix_Chunk *laserShot = graphics.loadSound("sound/mixkit-short-laser-gun-shot-1670.wav");
    Mix_Chunk *explosionSound = graphics.loadSound("sound/explosionSound.MP3");
    Mix_Chunk *bullet_up = graphics.loadSound("sound/bullet_up.mp3");
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
    SDL_Texture*dropBullet1_tex=graphics.loadTexture("image/redLaser.png");
    SDL_Texture*dropBullet2_tex=graphics.loadTexture("image/redLaser.png");
    SDL_Texture*playButton_tex=graphics.loadTexture("image/playbutton.png");
    SDL_Texture*soundButtonOn_tex=graphics.loadTexture("image/soundButtonOn.png");
    SDL_Texture*soundButtonOff_tex=graphics.loadTexture("image/soundButtonOff.png");
bool quit = false;
bool is_shotting = false;
bool die = false;
bool play = false;
bool delay=false;
bool music=true;
bool musicStopped=false;
int MouseX,MouseY;
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
                    gameState = 1;
                    break;
                } else if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
            }
        }
        graphics.presentScene();
    } else if (gameState == 1&&!die) {
        while(delay){
                SDL_Event ev;
        SDL_GetMouseState(&MouseX, &MouseY);
        SDL_PollEvent(&ev);
        switch (ev.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONDOWN:
                if (MouseX < 770 && MouseX > 720 && MouseY > 0 && MouseY < 70) {
                    delay=false;
                }
                 break;
        }}
        while (SDL_PollEvent(&event) != 0) {
            SDL_GetMouseState(&MouseX, &MouseY);
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
                      else if (event.type == SDL_MOUSEBUTTONDOWN) {
                            cout << MouseX << " " << MouseY<<endl;
                        if (MouseX < 770 && MouseX > 720 && MouseY > 0 && MouseY < 70) {
                            if (!delay) {
                                delay = true;
                            }
                            }
                        else if(MouseX<700&&MouseX>650&&MouseY>0&&MouseY<70){
                            if(music){
                                music=false;
                                musicStopped=true;
                            }
                        }
                        }
                    }
                    if(music&&!musicStopped){
                graphics.play(gMusic);}
                    if (is_shotting&&bulletRemain>0){
                    bullet bullets;
                    bulletRemain--;
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
        y_enemy2 += 2;
        dropBullet1.bulletY+=2;
        dropBullet2.bulletY+=2;
                if (y_enemy + 30 >= 600) {

                    y_enemy = 0 ;
                    x_enemy = rand() % 700;
                }

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
                    graphics.renderTexture(explode_tex,x_enemy-30,y_enemy-30,200,200);
                    //SDL_Delay(100);
                    y_enemy = 0;
                    x_enemy = rand()%800;
                    bull.erase(bull.begin() + i);
                        i--;
                        size--;
                }
                else if(checkCollison(bullet_,enemyRect2) == true){
                        if(enemy_health==0){
                                graphics.play(explosionSound);
                    graphics.renderTexture(explode_tex,x_enemy2-30,y_enemy2-30,200,200);
                    //SDL_Delay(100);
                    y_enemy2 = -150;
                    x_enemy2 = rand()%800;
                    CurrentScore+=2;
                    enemy_health=2;}
                    if(HighestScore<CurrentScore){
                    HighestScore=CurrentScore;}
                    enemy_health--;
                    bull.erase(bull.begin() + i);
                        i--;
                        size--;
                }}
            if(checkCollison(playerRect,enemyRect2)||checkCollison(playerRect,enemyRect)){
                    y_enemy2 = -150;
                    x_enemy2 = rand()%800;
                y_enemy = 0;
                    x_enemy = rand()%800;
                    dropBullet2.bulletX=rand()%800;
                    dropBullet2.bulletY=-400;
                    dropBullet1.bulletX=rand()%800;
                    dropBullet1.bulletY=-200;
                gameState=2;
                die=true;
            }
        if(bulletRemain>=12){
            bulletRemain=12;
        }
        HighestScoreString="Highest Score: "+to_string(HighestScore);
        CurrentScoreString="Current Score: "+to_string(CurrentScore);
        RemainingBullet="Remaining Bullets: "+to_string(bulletRemain);
        highestScore = graphics.renderText(HighestScoreString.c_str(),font, color);
        currentScore = graphics.renderText(CurrentScoreString.c_str(),font, color);
        remainingBullets = graphics.renderText(RemainingBullet.c_str(),font, color);
        graphics.renderTexture(remainingBullets, 20,80);
        graphics.renderTexture(highestScore, 20, 20);
        graphics.renderTexture(currentScore,20,50);
            fuel.tick();
            graphics.renderAni(ship_x+22,ship_y+26, fuel);
                background.scroll(1);
        SDL_Rect dropBulletRect1={dropBullet1.bulletX,dropBullet1.bulletY,30,10};
        SDL_Rect dropBulletRect2={dropBullet2.bulletX,dropBullet2.bulletY,30,10};
        if(checkCollison(dropBulletRect1,playerRect)){
        dropBullet1.bulletX=rand()%800;
        dropBullet1.bulletY=-200;
        bulletRemain+=rand()%3+1;
        graphics.play(bullet_up);
        }
        else if(dropBullet1.bulletY>600){
        dropBullet1.bulletX=rand()%800;
        dropBullet1.bulletY=-200;
        }
        else if(dropBullet2.bulletY>600){
        dropBullet2.bulletX=rand()%800;
        dropBullet2.bulletY=-200;
        }
        else if(checkCollison(dropBulletRect2,playerRect)){
        dropBullet2.bulletX=rand()%800;
        dropBullet2.bulletY=-400;
        bulletRemain+=rand()%3+1;
        graphics.play(bullet_up);
        }
        graphics.renderTexture(dropBullet1_tex,dropBullet1.bulletX,dropBullet1.bulletY,30,10);
        graphics.renderTexture(dropBullet2_tex,dropBullet2.bulletX,dropBullet2.bulletY,30,10);
        graphics.renderTexture(enemy_tex2,x_enemy2,y_enemy2,100,80);
        graphics.renderTexture(enemy_tex,x_enemy,y_enemy,100,80);
        graphics.renderTexture(playButton_tex,700,0,100,100);
        graphics.renderTexture(soundButtonOn_tex,640,4,100,100);
        graphics.presentScene();
        graphics.render(background);

       // graphics.presentScene();
        //SDL_Delay(0);
    }
else if (gameState == 2) {
        if(music){
            graphics.play(gMusic);
        }
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
                    bulletRemain=5;
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
