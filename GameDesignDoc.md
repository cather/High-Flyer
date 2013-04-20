# Game Overview
The National Aeronautic Space Corporation has just received unprecedented funding for its newest space flight project to travel the universe and see the sights. (Oh and collect data on stars too, I guess). The rocket, named High Flyer, has been built and is ready to launch. Don't let all of NASC's hard work go to waste. Help High Flyer travel to the furthest limits of the galaxy... and beyond!

Pilot High Flyer through outer space as long as possible, collecting stars and avoiding obstacles! Use the arrow keys to move High Flyer and mouse to shoot lasers at enemies.

----

## Gameplay

### Objective
The aim of the game is to survive as long as possible. Navigate the rocket to avoid comets, alien ships, missiles, and planets. Collect stars for extra points.

### Objects
| Object        | Role          | In gameplay          | Preliminary Appearance |
|:-------------:|---------------|----------------------|----------------------|
| Rocket Ship   | Player        | The user controls the rocketship with the keyboard arrows in order to safely guide it through space       | ![Rocket](images/rocket.jpg "Rocket Ship") |
| Laser Beam   | Weapon        | Damages enemies. Activated by left-clicking the mouse. The laser shoots (moves) quickly in the direction of the mouse, originating from the rocketship.| ![Laser beams](images/laser.jpg "Two laser beams") |
| Meteor        | Enemy         | Appear randomly on the left of the screen and move in a straight line until going off-screen. They can move directly left to right, or may move to the right of the screen on a diagonal path. If they hit the rocket, the rocket suffers some damage. Meteors can be damaged by the laser. | ![Meteors](images/meteor.jpg "Meteor") |
| Alien ship    | Enemy         | Alien ships appear randomly from any direction off screen, and move randomy on-screen. They drop off missiles in their paths. If the alien ship collides with the rocket, the rocket suffers some damage. Alien ships can be attacked with the laser. | ![Alien Ship](images/alien.jpg "Alien ship") |
| Missile        | Enemy        | Missiles explode after a certain period of time or if they collide with any other object. They travel in a path that follows the rocket ship. If the missile collides with the rocket, the missile explodes and the rocket loses a life. If the missile collides with any other object, including a laser beam, it explodes. If the radius of their explosions hits the rocket, the rocket suffers damage.  | ![Missile](images/missile.jpg "Missile") |
| Planet       | Barrier       | Rocket must avoid colliding with planets or else they lose a life. Planets are stationary, as in they only move with the background and not independently. | ![Planets](images/planets.jpg "Two planets") |
| Star        | Collectable   | The rocket ship collects stars for points. Stars are collected when the rocketship collides with them. Stars are stationary in that they only move with the background and not independently. | ![Star](images/stars.jpg "Two stars") |

### Controls

##### In-game
  * Up, down, left, right arrow keys: controls the rocketship's movement
  * Left click: Shoots a laser from the rocket to the location of the mouse, or if clicking on the pause button, pauses the game
  
##### Menus
  * Left click: selects an option, whether to Start, Continue, Restart, go back to the Main home screen, or Quit, depending on whether the user is in the Main screen or the Pause screen menus.
  * Keyboard: Allows the user to type in his/her name when the name field is on screen

###  Scoring
Scoring corresponds to the number of seconds the player has been alive. Collecting a star adds an equivalent of 5 seconds to the score. Scores can only increase, never decrease.

### Lives
The player starts with four lives, three of which are indicated on screen by small icons. The rocketship has a health bar that depletes when hit by commets or alien bombs. When the health bar is depleted, a life is lost. A life is immediately lost when the rocket collides with a planet. When a life is lost, a life icon on screen disappears and the health bar replenishes to indicate that the player has moved on to his or her next life.
When all three lives are lost, the game ends.

## Layout
The game will be a vertical scroller. The rocket ship will be free to move around the entirety of the screen. The background will appear to scroll down as if the rocketship is moving up in space. The rest of the layout will consist of the following:
  - A pause button in the top right corner. 
  - Score, displayed in the center top of the screen. 
  - Number of lives and health bar, displayed in the center bottom of the screen.

In the pause menu, there will be buttons to continue, restart, or quit the game.

### Preliminary layout

![Layouts](images/layout.jpg "Storyboarding High Flyer")


