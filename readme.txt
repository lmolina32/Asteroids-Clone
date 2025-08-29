Leonardo Molina 
readme.txt 

The project is a clone of asteroids. The game mechanics are showed in the start game screen. The 
asteroids are green circles and split when they are shoot by a pellet. In addition, due to the 
randomly generating asteroids, their velocities and directions, there is a bug where the asteroid 
just stays still. I couldn't figure out how to fix this issues but if you shoot the asteroid, when 
it splits in most cases the two generated asteroids move around. In addition, I couldn't figure out 
how to do a more complex bounding box for collisions between the asteroids and the ship. Therefore, I just
computed the distance between the object centers. Then, I checked if they collided, this leads to 
weird animation were the asteroid barely graces the ship and you re-spawn. In addition, the bullets 
are infinite but can only be shoot consecutively 20 times. This is because the array for pellet is 
capped at 20, but allows for infinite usage once each pellet goes out of range. A pellet can be 
shoot a distance of 300 before it de-spawns, freeing up space in the array for a new pellet to be 
shoot. Everything is tracked by 3 different structs: starship, asteroid, pellet. For the asteroid 
and pellet, the program determines if they are on the screen by the "active" flag, which determines
what is in usage. 