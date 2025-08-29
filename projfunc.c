/*
Leonardo Molina
projfunc.c
*/
#include "projfunc.h"

/*
start_screen

This function creates the start screen the user first sees when they run the game.

Params:
    *flag: the address of the start game flag, when the user hits the key to start the game 
           this flag does not allow for this screen to be populated again
    *game: the address of the end game flag, if user hits 'esc' the game will terminate */
void start_screen(bool *flag, bool *game){
    int margin = 100;
    int text_mrgn = 100;

    //print out load in screen 
    gfx_color(255, 255, 255);
    gfx_changefont("12x24");
    gfx_text(WID/2 - text_mrgn, HEIGHT/2 - margin, "Asteroids Clone");
    gfx_changefont("9x15");
    gfx_text(WID/2 - 0.9*text_mrgn, HEIGHT/2 - 0.8*margin, "By Leonardo Molina");
    gfx_text(WID/2 - 0.9*text_mrgn, HEIGHT/2 - 0.4*margin, "Controls");
    gfx_text(WID/2 - 0.8*text_mrgn, HEIGHT/2 - 0.2*margin, "w: move ship forward");
    gfx_text(WID/2 - 0.8*text_mrgn, HEIGHT/2 - 0.0*margin, "a: turn ship left");
    gfx_text(WID/2 - 0.8*text_mrgn, HEIGHT/2 + 0.2*margin, "d: turn ship right");
    gfx_text(WID/2 - 0.8*text_mrgn, HEIGHT/2 + 0.4*margin, "spacebar: shoot pellets");
    gfx_text(WID/2 - 0.8*text_mrgn, HEIGHT/2 + 0.6*margin, "esc: quit game");
    gfx_text(WID/2 - 0.8*text_mrgn, HEIGHT/2 + 0.8*margin, "Hit 's' to start game");

    // wait for user input
    while(1){
        char c = gfx_wait();
        if (c == 27){
            *game = false;
            *flag = false; 
            break;
        } if (c == 's'){
            *flag = false;
            break;
        }
    }
    gfx_clear();
}

/*
game_over

This function prints the game over screen 

Params:
    score: int, this is the score the user got when playing the game
return:
    none */
void game_over(int score){
    int margin = 100;
    int text_mrgn = 50;
    char str[30];

    //print game over screen
    gfx_clear();
    sprintf(str, "Score: %d", score);
    gfx_color(255, 255, 255);
    gfx_changefont("12x24");
    gfx_text(WID/2 - text_mrgn, HEIGHT/2 - margin, "Game Over");
    gfx_changefont("9x15");
    gfx_text(WID/2 - 0.9*text_mrgn, HEIGHT/2 - 0.8*margin, str);
    gfx_text(WID/2 - 0.8*text_mrgn, HEIGHT/2 + 0.8*margin, "Hit 'q' to quit game");

    //wait for user input to exit the game 
    while(1){
        char c = gfx_wait();
        if (c == 'q'){
            break;
        }
    }
}

/*
init_game

This function initializes the game. It builds the starship, all the asteroids, initializes all the pellets,
and sets up the lives and score tracker on the left. 

params:
    *ship: starShip, This is the location in memory of the struct starShip. It is used to print the ship on the screen
    pellets[]: array of pellet, this is an array of structs which contains the pellets the user can shoot
    asteroids[]: array of asteroid, this is an array of structs which contains the asteroids information that are placed on the screen.
    *score: int *, the location in memory of the score tracker
    lives: int, the lives the user currently has, starts of with 3
   
return:
    none  */
void init_game(starShip *ship, pellet pellets[], asteroid asteroids[], int *score, int lives){
    init_ship(ship, WID/2, HEIGHT/2, 15);
    render_starship(ship); 

    //turns off all the pellets 
    for(int i = 0; i < ARR_SZ; i++){
        pellets[i].active = false;
    }

    //turns off all the asteroids
    for (int i = 0; i < ARR_SZ * 2; i++){
        asteroids[i].active = false;
    }

    //prints asteroids, score and lives 
    init_asteroids(asteroids, ship);
    render_asteroids(asteroids);
    print_score(score);
    print_lives(lives);
}

/*
init_ship

this function initializes the ships informaiton and location of the ship 

params:
    *ship: starShip, location in memory of ship
    x: int, the starting x location of the ship
    y: int, the starting y location of the ship 
    len: int, the size of the ship, the ship is inscribed in a circle, so len correlates to the radius

return:
    none */
void init_ship(starShip *ship, int x, int y, int len){
    ship->coords.x = x;
    ship->coords.y = y;
    ship->nose_angle = 270;
    ship->base_angle = 90;
    ship->left_wing_angle = 120;
    ship->right_wing_angle = 60;
    ship->len = len;
}

/*
print_lives

This function prints the lives on the screen in the top left corner

params:
    lives: int, the number of lives the user has left 
    
return:
    none*/
void print_lives(int lives){
    int x_buffer = 20;
    int y_buffer = 35;
    starShip ship;

    //print the small ship on the top left corner 
    for(int i = 0; i < lives; i++){
        init_ship(&ship, x_buffer + i*10, y_buffer, 7);
        render_starship(&ship);
    }
}

/*
init_asteroids

this initializes the first 4 asteroids on the screen and sets the rest as inactive 

params:
    asteroids: array of asteroid, this array contains all the asteroids that can be placed on the screen 
    *ship: starShip, the place in memory where the ship is held, used to prevent asteroids in spawning on top of the ship*/
void init_asteroids(asteroid asteroids[], starShip *ship){
    srand(time(0));
    int x = ship->coords.x;
    int y = ship->coords.y;
    int start = 4; // debugging purposes;

    //create the first 4 asteroids
    for (int i = 0; i < start; i++){

        //create random x and y 
        asteroids[i].coords.x = rand()%WID;
        asteroids[i].coords.y = rand()%HEIGHT;

        //check asteroid is not placed within 100 pixels of the center of the ship 
        while(1){
            if ((asteroids[i].coords.x >= x-100 && asteroids[i].coords.x <= x+100) && 
                (asteroids[i].coords.y >= y - 100 && asteroids[i].coords.y <= y + 100)){
                asteroids[i].coords.x = rand()%WID;
                asteroids[i].coords.y = rand()%HEIGHT;
                }
            else{
                break;
            }
        } 

        //generate the size, change in x & y, and the angle the asteroid will travel in 
        asteroids[i].active = true;
        asteroids[i].radius = largeAsteroid;
        asteroids[i].dx = 1 + rand()%6;
        asteroids[i].dy = 1 + rand()%6;
        asteroids[i].angle = rand()%360;
        
        // minimize the bug of the asteroid stopping or riding alone one of the walls, it still happens but this lowers the possibility of it happening 
        while(1){
            if (asteroids[i].angle == 0 || asteroids[i].angle == 90 ||
                asteroids[i].angle == 180 || asteroids[i].angle == 360){
                    asteroids[i].angle = rand()%360;
            } else {
                break;
            }
        }

    }

    // ensure all the other asteroids are false 
    for (int i = start; i <ARR_SZ*2; i++){
        asteroids[i].active = false;
    }
}

/*
render_asteroids

this function prints the asteroids on the screen 

Params:
    asteroids: array of asteroid, this contains all the asteroids information 
    
return:
    none*/
void render_asteroids(asteroid asteroids[]){
    // asteroids are green 
    gfx_color(0, 255, 0);

    //iterate through the asteroids 
    for (int i = 0; i < ARR_SZ*2; i++){

        // check if asteroid is on screen 
        if (asteroids[i].active){
            float angle_rad = asteroids[i].angle * M_PI/180;

            //increment x and y coords 
            asteroids[i].coords.x += asteroids[i].dx * cos(angle_rad);
            asteroids[i].coords.y += asteroids[i].dy * sin(angle_rad);

            //print to screen 
            gfx_fill_circle(asteroids[i].coords.x, asteroids[i].coords.y, asteroids[i].radius);
        }
    }
}

/*
render_starship

This function prints the ship to the screen

Params: 
    *ship: starship, memory location of the main ship 
    
returns:
    none */
void render_starship(starShip *ship){
    int len = ship->len;
    float nose_rad = ship->nose_angle * M_PI/180;
    float base_rad = ship->base_angle * M_PI/180;
    float left_wing_rad = ship->left_wing_angle * M_PI/180;
    float right_wing_rad = ship->right_wing_angle * M_PI/180;
    int x = ship->coords.x;
    int y = ship->coords.y;
    
    XPoint ship_points[5]; 
    
    /*The ship is inscribed in a circle of radius "len", what these 4 points do is draw 3 points of a circle of radius
    "len" and one point of radius 0.5*len. The purpose of this is being able to use trig to rotate the points on the circle
    using the different angles. This explains why I have 4 different angles for the ship, as each angle corresponds to the current 
    angle that each point is located at with respect to the circle */
    ship_points[0] = (XPoint){x + len*cos(nose_rad), y + len*sin(nose_rad)};
    ship_points[1] = (XPoint){x + len*cos(left_wing_rad), y + len*sin(left_wing_rad)};
    ship_points[2] = (XPoint){x + 0.5*len*cos(base_rad), y + 0.5*len*sin(base_rad)};
    ship_points[3] = (XPoint){x + len*cos(right_wing_rad), y + len*sin(right_wing_rad)};
    ship_points[4] = (XPoint){x + len*cos(nose_rad), y + len*sin(nose_rad)};
    
    // print ship 
    gfx_color(255, 0, 0);
    gfx_fill_polygon(ship_points, 5);
}

/*
move_starship

this function takes in user input and ship and determines were to move the ship

params:
    *ship: starShip, memory location of the main ship 
    c: char, the key the user inputted

returns:
    none*/
void move_starship(starShip *ship, char c){
    int angle_incrm = 10; // angle increment 
    int xy_incrm = 10; // x and y increment 

    //move ship based on user input
    if (c == turnRight){
        ship->nose_angle += angle_incrm;
        ship->base_angle += angle_incrm;
        ship->left_wing_angle += angle_incrm;
        ship->right_wing_angle += angle_incrm;
    } else if (c == turnLeft){
        ship->nose_angle -= angle_incrm;
        ship->base_angle -= angle_incrm;
        ship->left_wing_angle -= angle_incrm;
        ship->right_wing_angle -= angle_incrm;
    } else if (c == moveForward){
        int curr_angle = ship->nose_angle % 360;

        //depending on the angle depends on increment added
        if (curr_angle == 270){
            ship->coords.y -= xy_incrm;
        } else if (curr_angle % 360 == 0){
            ship->coords.x += xy_incrm;
        } else if (curr_angle % 360 == 90){
            ship->coords.y += xy_incrm;
        } else if (curr_angle % 360 == 180){
            ship->coords.x -= xy_incrm;
        } else {
            ship->coords.x += xy_incrm*cos(M_PI/180 * ship->nose_angle);
            ship->coords.y += xy_incrm*sin(M_PI/180 * ship->nose_angle);
        } 
    }

    //print ship 
    render_starship(ship);
}

/*
render_pellet 

this function actives a pellet to be printed on the screen

params:
    *ship, starShip, memory location of the main ship 
    pellets, array of pellet, array containing each pellets information*/
void render_pellet(starShip *ship, pellet pellets[]){
    float nose_rad = ship->nose_angle * M_PI/180;
    int x = ship->coords.x + ship->len * cos(nose_rad); // x location pellet will shoot from 
    int y = ship->coords.y + ship->len * sin(nose_rad); // y location pellet will shoot from 
    
    // iterate through pellets until one pellet is inactive to turn it active 
    for (int i = 0; i < ARR_SZ; i++){

        // if pellet is inactive make it active and update information 
        if (!pellets[i].active){
            pellets[i].active = true;
            pellets[i].coords.x = x;
            pellets[i].coords.y = y;
            pellets[i].angle = ship->nose_angle;
            pellets[i].dist = 0;
            pellets[i].old_dist = 0;
            pellets[i].radius = 2;

            //draw pellet 
            gfx_color(255,255,255);
            gfx_fill_circle(pellets[i].coords.x, pellets[i].coords.y, pellets[i].radius);
            break;
        }
    }
}

/*
update game

this function updates all the movements of the game, it is the main driver ensuring everything is running 
correctly 

Params:
    *ship, starShip, memory location of the main ship 
    pellets, array of pellet, the information of each pellet 
    asteroids, array of asteroid, the information of each asteroid 
    *score, int, the memory location of the current score 
    *lives, int, the memory location of the current lives
    
return:
    none*/
void update_game(starShip *ship, pellet pellets[], asteroid asteroids[], int *score, int *lives){
    gfx_clear();

    //conditions if object goes out of the screen 
    flip_ship(ship);
    flip_pellets(pellets);
    flip_asteroids(asteroids);
    
    // checks collisions between asteroids, pellets, starShips and terminating conditions for pellets 
    update_asteroids(asteroids, pellets, score);
    update_pellets(ship, pellets);
    update_starship(ship, asteroids, lives);

    //prints out asteroids and ship  
    render_asteroids(asteroids);
    render_starship(ship); 

    //updates score and lives 
    print_score(score);
    print_lives(*lives);

    //resets asteroids if all of them are destroyed to play infinitely or until the game crashes lol 
    reset_asteroids(asteroids, ship);
    gfx_flush();
}

/*
reset_asteroids

This function resets the asteroids if all of them are destroyed

Params:
    asteroids: array of asteroids, the array contains all the information of all the asteroids on the screen
    *ship: starShip, memory location of the main ship  */
void reset_asteroids(asteroid asteroids[], starShip *ship){
    bool active_flag = false; // flag to see if asteroids are still active 

    //iterate through asteroids and check if all of them are inactive 
    for(int i = 0; i < ARR_SZ*2; i++){
        if (asteroids[i].active){
            active_flag = true;
            break;
        }
    }

    //if all asteroids are inactive reinitialize them 
    if (!active_flag){
        init_asteroids(asteroids, ship);
    }
}

/*
update_starship

this function checks between asteroid and ship collisions 

Params:
    *ship, starShip, the memory location of the main ship 
    asteroids: array of asteroid, the informaiton of each asteroid
    *lives, int, memory location of the number of lives the user has
    
returns:
    none  */
void update_starship(starShip *ship, asteroid asteroids[], int *lives){

    //check each asteroid for collision if active 
    for (int i = 0; i < ARR_SZ*2; i++){
        if (!asteroids[i].active) continue; // skip if inactive 

        //check for collision 
        bool collision = collision_detection_as(ship, asteroids[i]);

        //if collision, take away a life and re-spawn 
        if (collision && *lives >= 0){
           *lives = *lives - 1;
            safely_replace_ship(ship, asteroids);
        }
    }
}

/*
Safely_replace_ship

this function safely placed the ship on the screen after death

params:
    *ship: starShip, memory location of the main ship 
    asteroids: array of asteroids, array containing all the information of each asteroid */
void safely_replace_ship(starShip *ship, asteroid asteroids[]){
    int mrg = 30;
    int grid_size = 3;
    int x =  WID/2;
    int y = HEIGHT/2;
    int placed = false;

    // try to place ship at the center, by ensuring there are no asteroids in the area  
    init_ship(ship, WID/2, HEIGHT/2, ship->len);
    bool can_place = position_is_safe(ship, asteroids); 
    if (can_place){
        render_starship(ship);
    } else {
        // if cannot place iterate through a grid to try to place 
        while(!placed){
            /*
            This double for loop iterates in a grid structure, initially it is set as a 3x3 grid.
            it iterates through each point on the grid checking if it can be placed. If it cannot it
            will it will increment grid size until it reaches 7x7, then it will go down back 3x3 grid with
            smaller margin */
            for(int i = -grid_size; i <= grid_size && !placed; i++){
                for(int j = -grid_size; j<= grid_size && !placed; i++){
                    int cur_x = x + i*mrg;
                    int cur_y = y + j*mrg;

                    // check the x and y are inside the frame 
                    if ( cur_x > 0 && cur_x < WID &&
                         cur_y > 0 && cur_y < HEIGHT){
                            init_ship(ship, cur_x, cur_y, ship->len);

                            //check if the ship can be placed safely 
                            can_place = position_is_safe(ship, asteroids);
                            if (can_place){
                                render_starship(ship);
                                placed = true;
                            }
                        }
                }
            }
            //increment grid size if couldn't placed 
            if (!placed){
                grid_size++;
            }
            if (grid_size >= 7){
                grid_size = 3;
                mrg -= 5;
            }
        }
    }
}

/*
position is safe

This function checks if the ship can be placed safely 

params:
    *ship, starShip, memory location of the main ship 
    asteroids, array of asteroid, array containing all the asteroids information
    
returns
    collision: bool, false if unsafe to place, true if safe to place */
bool position_is_safe(starShip *ship, asteroid asteroids[]){
    bool collision = false;

    //check for collision between ship and asteroid if asteroid is active 
    for (int i = 0; i < ARR_SZ; i++){
        if (asteroids[i].active){

            //check for collision 
            collision = collision_detection_as(ship, asteroids[i]); 
            if (collision){
                break;
            }
        }
    }

    return (!collision);
}

/*
collision_detection_as

this function checks for collision between 'as', meaning asteroid and ship 

params:
    *ship: starShip, memory location of main ship 
    a: asteroid, struct containing information of asteroid
    
returns:
    bool: false if no collision, true if collision  */
bool collision_detection_as(starShip *ship, asteroid a){
    //get distance between ship and asteroid 
    float dist = object_distance(ship->coords.x, ship->coords.y, a.coords.x, a.coords.y);

    //check if distance is smaller than bounding boxes 
    return (dist <= ship->len + a.radius);
}

/*
object_distance

this function computes distances between two points 

Params:
    x1: int, x location of object 1
    y1: int, y location of object 1
    x2: int, x location of object 2
    y2: int, y location of oject 2

returns:
    dist, float, the distance between the two objects*/
float object_distance(int x1, int y1, int x2, int y2){
    int dx = x1 - x2;
    int dy = y1 - y2;
    float dist = sqrt(dx*dx + dy*dy);

    return dist;
}

/*
update_asteroids

checks for collision between asteroids and pellets, then updates the score 

Params:
    asteroids: array of asteroid, contains all the information of all the asteroids
    pellets: array of pellets, contains all the information of all the pellets
    *score: int, memory location of the score */
void update_asteroids(asteroid asteroids[], pellet pellets[], int *score){

    // iterate through all asteroids checking if they are active 
    for (int i = 0; i < ARR_SZ*2; i++){
        if (!asteroids[i].active) continue;

        //if active iterate through pellets  checking if they are active 
        for (int j = 0; j < ARR_SZ; j++){
            if (!pellets[j].active) continue;

            // check if collision 
            bool collision = collision_detection_ap(asteroids[i], pellets[j]);
            
            //if collision occurred, update score, delete asteroid/pellet from screen, and if asteroid is large enough split it 
            if (collision){
                update_score(score, asteroids[i].radius);
                asteroids[i].active = false;
                pellets[j].active = false;

                //split asteroid if it has large or medium radius 
                if (asteroids[i].radius == largeAsteroid || asteroids[i].radius == mediumAsteroid){
                    split_asteroid(asteroids, asteroids[i].radius, asteroids[i].angle,
                                    asteroids[i].coords.x, asteroids[i].coords.y);
                }
                break;
            }
        }
    }
}

/*
update_score

This function updates the score of the game whenever an asteroid is destroyed

params:
    *score: int, memory location of the score
    sz: int, size of the asteroid*/
void update_score(int *score, int sz){
    // update score based on asteroid size
    if (sz == largeAsteroid){
        *score = *score + largeScore;
    } else if (sz == mediumAsteroid){
        *score =  *score + mediumScore;
    } else if (sz == smallAsteroid){
        *score = *score + smallScore;
    }
}

/*
print_score

This function prints the score to the screen 

Params:
    *score: int, memory location of the score*/
void print_score(int *score){
    char str[20];
    gfx_changefont("9x15");
    gfx_color(255,255,255);
    sprintf(str, "%d", *score);
    gfx_text(20, 20, str);
}

/*
split_asteroid

This function split an asteroid into two smaller asteroids 

Params:
    asteroids: an array of asteroid, information of all the asteroids 
    radius: int, the radius of the asteroid you want to split 
    angle: int, angle the asteroid you want to split has 
    x: int, x coord of asteroid you want to split 
    y: int, y coord of the asteroid you want to split
    */
void split_asteroid(asteroid asteroids[], int radius, int angle, int x, int y){
    float angle_rad = angle *M_PI / 180;
    // give radius depending on size of asteroid 
    int a_radius = (radius == largeAsteroid) ? mediumAsteroid : smallAsteroid;

    int count = 0, flip = 1;
    // check for inactive slot to create asteroid 
    for (int i = 0; i < ARR_SZ*2; i++){
        if (count == 1) flip = -1;
        if (asteroids[i].active == false){
            asteroids[i].coords.x = x;
            asteroids[i].coords.y = y;
            asteroids[i].active = true;
            asteroids[i].dx = 1 + rand()%6;
            asteroids[i].dy = 1 + rand()%6;
            asteroids[i].angle = (angle + 30 * flip) % 360;
            asteroids[i].radius = a_radius;
            count++;
        }
        if (count == 2){
            break;
        }
    }
}

/*
collision_detection_ap

This function checks for collision between asteroids and pellets 

params:
    a: asteroid, a struct containing an asteroids information 
    p: pellet, a struct containing a pellets information 
    
returns:
    bool: true if collision detected, false if not collision is detected*/
bool collision_detection_ap(asteroid a, pellet p){
    float angle_rad = p.angle * M_PI/180;
    float dist = object_distance(a.coords.x, a.coords.y,
                          p.coords.x + p.dist * cos(angle_rad),
                          p.coords.y + p.dist * sin(angle_rad));

    return (dist <= a.radius + p.radius); 
}

/*
udate_pellets

This function updates the pellets movement 

Params:
    *ship: starShip, memory location of the main ship 
    pellets: array of pellet, an array containing the information of each pellet
*/
void update_pellets(starShip *ship, pellet pellets[]){
    gfx_color(255, 255, 255);

    //iterate through each pellet  check if it is true 
    for (int i = 0; i <ARR_SZ; i++){
        //if pellet is active increase the distance traveled 
        if (pellets[i].active){
            pellets[i].dist += 10;
            float angle_rad = pellets[i].angle * M_PI/180;
            int x = pellets[i].coords.x + pellets[i].dist * cos(angle_rad);
            int y = pellets[i].coords.y + pellets[i].dist * sin(angle_rad);
            gfx_fill_circle(x, y, pellets[i].radius);

        }
        //if pellet as reached max range destroy pellet 
        if (pellets[i].dist + pellets[i].old_dist > 300){
            pellets[i].active = false;
        }
    }
}

/*
flip_ship

This function flips the ship if it goes out of the screen

Params:
    *ship: starShip, memory location of the main ship */
void flip_ship(starShip *ship){
    // conditions if the ship goes out of the screen 
    if (ship->coords.y <= -(ship->len)){
        ship->coords.y = HEIGHT + ship->len;
    } else if (ship->coords.y >= (ship->len + HEIGHT)){
        ship->coords.y = 0 - ship->len;
    } else if (ship->coords.x <= -(ship->len)){
        ship->coords.x = WID + ship->len;
    } else if (ship->coords.x >= (ship->len + WID)){
        ship->coords.x = 0 - ship->len;
    }
}

/*
flip_pellets

This function is used to flip the pellets that go out of the screen 

Params:
    pellets: array of Pellet, a struct containing the array of pellets*/
void flip_pellets(pellet pellets[]){

    //iterate through each pellet that is active checking if they move out the screen
    for (int i = 0; i < ARR_SZ; i++){
        if (pellets[i].active){
            float angle_rad = pellets[i].angle * M_PI/180;
            int x = pellets[i].coords.x + pellets[i].dist * cos(angle_rad);
            int y = pellets[i].coords.y + pellets[i].dist * sin(angle_rad);
            bool flag = false;

            //check if pellet is out of the screen 
            if (y <= -(pellets[i].radius)){
                pellets[i].coords.y = HEIGHT + pellets[i].radius;
                flag = true;
            } else if (y >= HEIGHT + pellets[i].radius){
                pellets[i].coords.y = 0 - pellets[i].radius;
                flag = true;
            } else if (x <= -pellets[i].radius){
                pellets[i].coords.x = WID + pellets[i].radius;
                flag = true;
            } else if (x >= WID + pellets[i].radius){
                pellets[i].coords.x = 0 - pellets[i].radius;
                flag = true;
            }

            // if pellet is out of screen update old_dist with the distance traveled thus far, and reset dist to be 0
            if (flag){
                pellets[i].old_dist = pellets[i].dist;
                pellets[i].dist = 0;
            }
        }
    }
}

/*
flip_asteroids

This function flips the asteroids that go out the screen

params:
    asteroids: array of asteroid, this array contains all the information of each asteroid */
void flip_asteroids(asteroid asteroids[]){

    //iterate through all active asteroids 
    for (int i = 0; i < ARR_SZ*2; i++){
        if (asteroids[i].active){
            //check if asteroid is out of screen 
            if (asteroids[i].coords.y <= -(asteroids[i].radius)){
                asteroids[i].coords.y = HEIGHT + asteroids[i].radius;
            } else if (asteroids[i].coords.y >= (asteroids[i].radius + HEIGHT)){
                asteroids[i].coords.y = 0 - asteroids[i].radius;
            } else if (asteroids[i].coords.x <= -(asteroids[i].radius)){
                asteroids[i].coords.x = WID + asteroids[i].radius;
            } else if (asteroids[i].coords.x >= (asteroids[i].radius + WID)){
                asteroids[i].coords.x = 0 - asteroids[i].radius;
            }
        }
    }
}
