# SpaceXplorer

A text-based space exploration game where you control a spaceship to collect space junk while avoiding asteroids.

## Game Features

- Collect space junk to increase your score
- Manage your spaceship's fuel and health
- Avoid the moving asteroid
- Three difficulty levels
- High score system
- Text-based interface

## Requirements

- Windows operating system
- C compiler (GCC recommended)
- Standard C libraries

## Compilation

To compile the game, use the following command:

```bash
gcc main.c game_logic.c -o spacexplorer
```

## How to Play

1. Run the compiled executable
2. Select your difficulty level
3. Use the following controls:
   - W: Move up
   - S: Move down
   - A: Move left
   - D: Move right
   - H: Show help
   - Q: Quit game

## Game Rules

- Collect all space junk (J) to win
- Each piece of junk gives you fuel and health
- Avoid the asteroid (A)
- Don't run out of fuel
- The asteroid moves in a fixed pattern
- Your score increases with each piece of junk collected

## Game Elements

- P: Player (your spaceship)
- A: Asteroid (avoid this!)
- J: Space junk (collect these)
- .: Empty space

## Difficulty Levels

1. Easy: 18x18 grid
2. Medium: 24x24 grid
3. Hard: 30x30 grid

## High Scores

Your score will be saved to `highscores.txt` when you complete a game. 