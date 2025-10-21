# Fearful Stars
shut em up cosmic horor inspired game

## Lore
Earth sent Norman as an explorer of the final frontier. With new wormhole manipulation technology, it became possible to reach the limits of the observable universe. A journey with no return, yet Norman accepts it to pay off his enormous hospital debts that were accumulated by his daughter with cancer. Now Norman Pearson is the lucky pilot who will take humanity forward, but something appeared in the middle of the wormhole journey, the ship was damaged, but he sees the final frontier, he cannot return, so he moves forward into the unknown, not knowing what awaits him on his journey.

## Compilation

1. Make sure you have cmake or a toolchain like visual studio that are compitible;
2. Create and enter a build folder;
3. Inside the build folder use the command:
```bash
cmake -S . -B build/
```

4. Compile with your chosen toolchain, if it is gnu make just use the command:
```bash
cmake --build build/
```

## Gameplay

The player controls a spaceship doging and shooting asteroids and various grotesque mosntrosities in their way;

- Power ups are available troughout the levels that can power up the ship 
- The player has a total of 5 lives per stage, if they end the player returns to the beginning of the stage
- A wide range of stage hazards and enemies will apear in the stages
- The stages are arranged in a tree like manner having different routes, there are 4 stages from beginning to end, but the path will be up to the player visiting a differnt set of stages each run
- Gripping bossfigths at the end of each stage 
- Unique enddings deppending on the routes

## Visuals

The visuals are drawn in a 320 by 180 canvas in pixel art inspired by the nes era of video games

## Player

### Capabilities

This is what the player is capable of:

- Free 2D movement
- Slowdown for precise doging
- Shooting a array o different projectiles
- Using a special ability when the special bar is full

### Modules system

At the beginning of a new playthrough the player can choose what their primary shot, secundary shot, auxiliary ability and special will be freely. This decision is final for the entire playthrough.

### Power ups

During the stages special enemies will spawn that can drop power ups, those power ups evolve each individual module, adding more damage, more shots deppending of what the module is.

### Primary shot

This is the main projectile that the player shoots, dealing the most damage.

#### Types

### Secundary shot

This is an extra shot that deals less damage, but has a different behaviour from your primary, complementing your build

#### Types

### Auxiliary

This is a passive ability that will help you in your playthrough, its very open so it can be from a shield to a minion that helps you deal damage.

#### Types

### Special

This is a specal ability that can be triggered deppending on the charge of a special meter.

The special meter can be charged from defeating enemies or grazing enemies and projectiles.

#### Types

### Movement

The player has octodirectional movement in a 2D Space.
The player can slow down their movement to make it more precise to dodge in certain situations.

### Grazing

Grazing refers to the action of nearly doging something, be it a enemy or a projectile, this action will raise the special meter a certain ammount deppending on what the player is grazing.

### Controls

## Enemies

## Bosses

### Chroma: Eater of light

It will be the first boss the player fights.

It will have a assortment of lazer attacks and ilusions/distorsions do devour the players light.

## Levels

The first level will be the target for the demo;

### Level 1: Lights out

