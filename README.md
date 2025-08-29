# Asteroids Clone

Author: Leonardo Molina  

This project is a simple clone of the classic **Asteroids** game, written in C.  

---

## How to Build and Run
1. Compile the project using `make`:
```bash
make
```
This produces an executable called runproject.

###Run the game:
```bash
./runproject
```

###To clean up object files and the executable:
```bash
make clean
```

## Game Mechanics
- Asteroids

    - Represented as green circles.
    - When hit by a pellet, they split into smaller asteroids.
    - Because asteroids are randomly generated with different velocities and directions, sometimes one may stay still (known bug). Shooting a stationary asteroid usually resolves this, since the split asteroids will move.

- Collisions

    - Collision detection is based on the distance between object centers (not complex bounding boxes).
    - This can cause cases where an asteroid barely grazes the ship but still counts as a collision.
    - On collision, the ship respawns.

- Bullets (Pellets)
    - Infinite firing is allowed, but only 20 bullets can be active at once.
    - Each pellet travels a distance of 300 units before despawning.
    - When a pellet despawns, it frees space in the array for a new shot.

## Implementation Details
The game logic is organized around three main structs:
- starship
- asteroid
- pellet

Both asteroids and pellets are managed using an active flag, which determines whether they are currently in use on screen.

## Known Issues
1. Occasionally, asteroids spawn without moving (they remain stationary until destroyed).
2. Collision detection is simplified, which can lead to slightly inaccurate collision responses.

## Future Improvements
1. Implement more accurate bounding-box or polygon-based collision detection.
2. Fix stationary asteroid bug.
3. Add more game features (levels, scoring, etc.).