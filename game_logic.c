#include "spacexplorer.h"

void clear_screen() {
    system("cls");
}

void initialize_game(Game *game, Difficulty difficulty) {
    srand(time(NULL));
    
    game->difficulty = difficulty;
    game->state = PLAYING;
    game->turns = 0;
    
    // Set game size based on difficulty
    switch (difficulty) {
        case EASY:
            game->size = MIN_SIZE;
            break;
        case MEDIUM:
            game->size = MIN_SIZE + 6;
            break;
        case HARD:
            game->size = MIN_SIZE + 12;
            break;
    }
    
    // Initialize player
    game->player.x = game->size / 2;
    game->player.y = game->size / 2;
    game->player.fuel = 100;
    game->player.health = 100;
    game->player.junk_collected = 0;
    game->player.score = 0;
    
    // Initialize asteroid
    game->asteroid.x = 0;
    game->asteroid.y = 0;
    game->asteroid.direction = 0;
    
    // Initialize space junk
    game->junk_count = (game->size * game->size) / 10;
    for (int i = 0; i < game->junk_count; i++) {
        game->junk[i].x = rand() % game->size;
        game->junk[i].y = rand() % game->size;
        game->junk[i].value = rand() % 10 + 1;
        game->junk[i].collected = 0;
    }
}

void print_game(Game *game) {
    clear_screen();
    printf("SpaceXplorer - Score: %d | Fuel: %d | Health: %d | Junk Collected: %d\n", 
           game->player.score, game->player.fuel, game->player.health, game->player.junk_collected);
    printf("Use WASD to move, H for help, Q to quit\n\n");
    
    for (int y = 0; y < game->size; y++) {
        for (int x = 0; x < game->size; x++) {
            if (x == game->player.x && y == game->player.y) {
                printf("P ");
            } else if (x == game->asteroid.x && y == game->asteroid.y) {
                printf("A ");
            } else {
                int junk_here = 0;
                for (int i = 0; i < game->junk_count; i++) {
                    if (game->junk[i].x == x && game->junk[i].y == y && !game->junk[i].collected) {
                        printf("J ");
                        junk_here = 1;
                        break;
                    }
                }
                if (!junk_here) {
                    printf(". ");
                }
            }
        }
        printf("\n");
    }
}

void move_player(Game *game, char direction) {
    int new_x = game->player.x;
    int new_y = game->player.y;
    
    switch (direction) {
        case 'w':
        case 'W':
            new_y--;
            break;
        case 's':
        case 'S':
            new_y++;
            break;
        case 'a':
        case 'A':
            new_x--;
            break;
        case 'd':
        case 'D':
            new_x++;
            break;
    }
    
    // Check boundaries
    if (new_x >= 0 && new_x < game->size && new_y >= 0 && new_y < game->size) {
        // Check for collision with asteroid before moving
        if (new_x == game->asteroid.x && new_y == game->asteroid.y) {
            game->state = LOST;
            return;
        }
        
        game->player.x = new_x;
        game->player.y = new_y;
        game->player.fuel--;
        game->turns++;
        
        collect_junk(game);
        move_asteroid(game);
        
        // Check for collision after asteroid moves
        if (game->player.x == game->asteroid.x && game->player.y == game->asteroid.y) {
            game->state = LOST;
            return;
        }
        
        update_game_state(game);
    }
}

void move_asteroid(Game *game) {
    switch (game->asteroid.direction) {
        case 0: // Right
            if (game->asteroid.x < game->size - 1) {
                game->asteroid.x++;
            } else {
                game->asteroid.direction = 1;
                game->asteroid.y++;
            }
            break;
        case 1: // Down
            if (game->asteroid.y < game->size - 1) {
                game->asteroid.y++;
            } else {
                game->asteroid.direction = 2;
                game->asteroid.x--;
            }
            break;
        case 2: // Left
            if (game->asteroid.x > 0) {
                game->asteroid.x--;
            } else {
                game->asteroid.direction = 3;
                game->asteroid.y--;
            }
            break;
        case 3: // Up
            if (game->asteroid.y > 0) {
                game->asteroid.y--;
            } else {
                game->asteroid.direction = 0;
                game->asteroid.x++;
            }
            break;
    }
}

void collect_junk(Game *game) {
    for (int i = 0; i < game->junk_count; i++) {
        if (!game->junk[i].collected && 
            game->junk[i].x == game->player.x && 
            game->junk[i].y == game->player.y) {
            game->junk[i].collected = 1;
            game->player.junk_collected++;
            game->player.score += game->junk[i].value;
            game->player.fuel += game->junk[i].value * 2;
            if (game->player.fuel > 100) game->player.fuel = 100;
            game->player.health += game->junk[i].value;
            if (game->player.health > 100) game->player.health = 100;
        }
    }
}

void update_game_state(Game *game) {
    if (game->player.fuel <= 0 || game->player.health <= 0) {
        game->state = LOST;
    } else if (game->player.junk_collected >= game->junk_count) {
        game->state = WON;
    }
}

void save_high_score(const char *player_name, int score, Difficulty difficulty) {
    FILE *file = fopen("highscores.txt", "a");
    if (file) {
        const char *diff_str;
        switch (difficulty) {
            case EASY: diff_str = "Easy"; break;
            case MEDIUM: diff_str = "Medium"; break;
            case HARD: diff_str = "Hard"; break;
            default: diff_str = "Unknown"; break;
        }
        fprintf(file, "%s %d %s\n", player_name, score, diff_str);
        fclose(file);
    }
}

void load_high_scores() {
    FILE *file = fopen("highscores.txt", "r");
    if (file) {
        char name[MAX_NAME_LENGTH];
        int score;
        char difficulty[10];
        printf("\nHigh Scores:\n");
        printf("Name\t\tScore\tDifficulty\n");
        printf("--------------------------------\n");
        while (fscanf(file, "%s %d %s", name, &score, difficulty) == 3) {
            printf("%-15s %-8d %s\n", name, score, difficulty);
        }
        fclose(file);
    }
}

void display_help() {
    clear_screen();
    printf("SpaceXplorer Help\n");
    printf("----------------\n");
    printf("W - Move Up\n");
    printf("S - Move Down\n");
    printf("A - Move Left\n");
    printf("D - Move Right\n");
    printf("H - Show Help\n");
    printf("Q - Quit Game\n\n");
    printf("Game Rules:\n");
    printf("- Collect space junk (J) to increase your score\n");
    printf("- Each piece of junk gives you fuel and health\n");
    printf("- Avoid the asteroid (A)\n");
    printf("- Don't run out of fuel\n");
    printf("- Collect all junk to win\n");
    printf("\nPress any key to continue...");
    getch();
} 