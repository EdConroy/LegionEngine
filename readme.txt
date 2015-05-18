This engine is the version that provides the functionality of the fighting game Mahvel Baybe!, it is not the final version, nor
the most optimized version of the engine.  I appologize for any inconvience or performance issues this version may cause in advance.
The Characters, Stages, and Music are all owned by Capcom and Marvel respectively, the assets are not included due to copyright
issues so the only thing that is made available is the source code.

Controls:
Player 2
WASD - Movement
r - jab
t - medium
y - heavy
g - launcher
f - block

Player 1
Arrows - Movement
j - light
k - medium
l - heavy
m - launcher
n - block

These controls are not final

Launching will unleash a one hit kill move as aerial combos have not yet been implemented

Update 10/21: The game's floor has shifted down to make the players look more like they are walking on the ground.
The game does not currently run on an entity system as that is currently in the works, but for now the game functions
just fine.

Update 10/25: Press O and P to change stages

Update 10/26: Added background music, audio.c, and audio.h. 

Update 12/16: Switch out FIGHT_SENTINEL and FIGHT_DOOM in LoadFighter in game.c to change fighters.  Also change the music path to
any sound file in the sounds folder in order to change the music.  You must not be in fullscreen mode to use the Fighter Editor
since it uses the command line.  Have Fun!

Update 5/18: Fixed Draw call problem where sprite would be deleted every frame.  
