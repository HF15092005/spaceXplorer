#ifndef SPACEXPLORER_H
#define SPACEXPLORER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define MIN_SIZE 18
#define MAX_SIZE 30
#define MAX_JUNK 50
#define MAX_NAME_LENGTH 50

// Game difficulty levels
typedef enum {
    EASY,
    MEDIUM,
    HARD
} Difficulty;

// Game state
typedef enum {
    PLAYING,
    WON,
    LOST
} GameState;

// Structure for the player's spaceship
typedef struct {
    int x;
    int y;
    int fuel;
    int health;
    int junk_collected;
    int score;
} Spaceship;

// Structure for space junk
typedef struct {
    int x;
    int y;
    int value;
    int collected;
} SpaceJunk;

// Structure for the asteroid
typedef struct {
    int x;
    int y;
    int direction; // 0: right, 1: down, 2: left, 3: up
} Asteroid;

// Structure for the game
typedef struct {
    int size;
    Difficulty difficulty;
    GameState state;
    Spaceship player;
    SpaceJunk junk[MAX_JUNK];
    int junk_count;
    Asteroid asteroid;
    int turns;
} Game;

// Function declarations
void initialize_game(Game *game, Difficulty difficulty);
void print_game(Game *game);
void move_player(Game *game, char direction);
void move_asteroid(Game *game);
void collect_junk(Game *game);
void update_game_state(Game *game);
void save_high_score(const char *player_name, int score, Difficulty difficulty);
void load_high_scores();
void display_help();
void clear_screen();

#endif // SPACEXPLORER_H 