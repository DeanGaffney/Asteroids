## Asteroids
### __*A C++ implementation of Asteroids using opengl*__

### Author - __*Dean Gaffney (20067423)*__
### Subject - __*Console Game Development 2*__
---


#### Features
- Basic Collision Detection __*(working)*__
    - Used circles for collision detection
- Asteroid Destruction/Spawning __*(working)*__
    - Asteroids can be destroyed by being shot at with bullets.
    - If an asteroid is destroyed several more asteroids are spawned, this is up to a random number of asteroids that are spawned and they spawn in random velocites and rotations.
    - The asteroids keep breaking into smaller pieces until there is no smaller type left.
    - Once an asteroid that is the size of the smallest asteroid is destroyed it is completley destroyed.
- Powerups __*(working)*__
    - The powerups are implemented using a new sublcass of BaseGameObject of  A random chance calculator determines if a power up will be spawned and what type of power up it is, and where it's located. I have included several types of power ups they are as follows:
        -  Health powerup __*(working)*__
        -  Ammo powerup __*(working)*__
        -  Repel asteroids powerup __*(working)*__
        -  Shield powerup __*(working)*__

- AI (Auto-Navigation) __*(working)*__
    - The AI navigation system is triggered by pressing 'A' key.
    - This triggers a bool to be set which toggles auto navigation on/off.
    - If on the AI ship has several states to choose from.
    - States are controlled by state machine which switches on these states at appropriate times.
    - The states are [FIGHT,FLIGHT,AMMO,HEALTH,WAIT]
        - FIGHT: In this state the ship rotates and fires at all asteroids to destroy them.
        - FLIGHT: In this state the ship calculates if an asteroid is moving owards it and if so it moves out of the way.
        - AMMO: This state is triggered when the ship is low on bullets and needs to shoot at an ammo pickup.
        - HEALTH: This state is triggered when the player is low on health and has enough ammo left to shoot a health pickup.
        - WAIT: This state is triggered when all asteroids are destroyed, which makes the ship sit and wait for the next appropriate action such as fighting newly spawned asteroids.
---
#### Overview 
- Ship has 100% health.
- Game starts with large asteroid and a random powerup.
- Shooting an asteroid makes it explode into smaller pieces which must also be destroyed.
- The player can use powerups to aid them in the game (see powerups section above for specification).
- An auto navigation mode can be triggered by pressing the 'A' key.
- The game has timers which will spawn asteroids and powerups if there are none on the screen this will allow for the game not to end prematurely and allow the player to keep playing.
