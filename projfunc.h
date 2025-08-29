/*
Leonardo Molina
projfunc.h*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "gfx2.h"

//Screen size and one array size 
#define WID 700
#define HEIGHT 500
#define ARR_SZ 20

typedef enum{turnLeft=97, turnRight=100, moveForward=119, shoot=32} movement;
typedef enum{largeAsteroid=35, mediumAsteroid=20, smallAsteroid=10} asteroidSize;
typedef enum{largeScore=20, mediumScore=50, smallScore=100} score;

typedef struct{
    int x; // x coordinate 
    int y; // y coordinate 
} gameObject;

typedef struct{
    int len; // radius of the object
    gameObject coords; //coords x and y 
    int nose_angle; //front of ship angle 
    int base_angle; // back of ship angle 
    int left_wing_angle; // left wing of ship angle 
    int right_wing_angle; // right wing of ship angle 
} starShip;

typedef struct{
    gameObject coords; // coords x and y 
    float dist; //distance the pellet has traveled 
    float old_dist; //if pellet goes out the screen, the distance currently traveled will be placed here 
    int angle; //angle the pellet was shot at 
    int radius; //size of pellet 
    bool active; // flag for if the pellet is on the screen 
} pellet;

typedef struct{
    gameObject coords; // coords x and y 
    float radius; // size of asteroid 
    int angle; // current angle the asteroid is going in 
    int dx; // the change in x 
    int dy; // the change in y 
    bool active; // flag for if asteroid is on screen 
} asteroid;

void init_game(starShip *, pellet [], asteroid [],int *, int);
void init_ship(starShip *, int, int , int );
void render_starship(starShip *);
void move_starship(starShip *, char);
void fill_in_starship(XPoint [], int, int, int, float, float);
void start_screen(bool *, bool *);
void render_pellet(starShip *, pellet []);
void update_game(starShip *, pellet [], asteroid [], int *, int *);
void update_pellets(starShip *, pellet []);
void flip_ship(starShip *);
void flip_pellets(pellet []);
void init_asteroids(asteroid [], starShip *);
void render_asteroids(asteroid []);
void flip_asteroids(asteroid []);
void update_asteroids(asteroid [], pellet [], int *);
bool collision_detection_ap(asteroid , pellet);
void split_asteroid(asteroid [], int, int, int, int);
void update_score(int *, int);
void print_score(int *);
void print_lives(int);
void update_starship(starShip *, asteroid [], int *);
bool collision_detection_as(starShip *, asteroid);
void game_over(int);
void safely_replace_ship(starShip *, asteroid []);
float object_distance(int , int, int ,int);
bool position_is_safe(starShip *, asteroid []);
void reset_asteroids(asteroid [], starShip *);