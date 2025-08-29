/*
Leonardo Molina
project.c*/
#include "projfunc.h"

int main(){
    char c;
    bool game = true; 
    starShip ship; //starship 
    bool load_screen = true;
    pellet pellets[ARR_SZ]; // pellet array 
    asteroid asteroids[ARR_SZ*2]; // asteroid array 
    int score = 0;
    int lives = 3;
    bool gameover = false;

    gfx_open(WID, HEIGHT, "Asteroids");
    while(game){

        //the start screen and initializing the game
        if(load_screen){
            start_screen(&load_screen, &game);
            init_game(&ship, pellets, asteroids, &score, lives);
        }
        
        //get user input for on screen movement
        if (!gameover){ 
            gfx_flush();
            if(gfx_event_waiting()){
                c = gfx_wait();
                switch(c){
                    case turnLeft:
                        move_starship(&ship, c);
                        break;
                    case turnRight:
                        move_starship(&ship, c);
                        break;
                    case moveForward:
                        move_starship(&ship, c);
                        break;
                    case shoot:
                        render_pellet(&ship, pellets);
                        break;
                    case 27:
                        game = false;
                        break;
                }
            }
        }

        // update the screen with asteroids and pellets
        update_game(&ship, pellets, asteroids, &score, &lives);
        usleep(25000);

        //load game over screen if users loses all their lives
        if (lives <= 0){
            gameover = false;
            game_over(score);
            break;
        }
    }

    return 0;

}