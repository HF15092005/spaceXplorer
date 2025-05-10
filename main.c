#include "spacexplorer.h"

void display_intro() {
    clear_screen();
    printf("Welcome to SpaceXplorer!\n");
    printf("=======================\n\n");
    printf("You are an astronaut exploring deep space.\n");
    printf("Your mission is to collect space junk while avoiding asteroids.\n");
    printf("Each piece of junk you collect will give you fuel and health.\n");
    printf("Be careful not to run out of fuel or get hit by the asteroid!\n\n");
    printf("Press any key to continue...");
    getch();
}

Difficulty select_difficulty() {
    clear_screen();
    printf("Select Difficulty:\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    printf("Enter your choice (1-3): ");
    
    int choice;
    scanf("%d", &choice);
    getchar(); // Clear the newline character
    
    switch (choice) {
        case 1: return EASY;
        case 2: return MEDIUM;
        case 3: return HARD;
        default: return EASY;
    }
}

void game_over(Game *game) {
    clear_screen();
    if (game->state == WON) {
        printf("Congratulations! You've won!\n");
        printf("Final Score: %d\n", game->player.score);
        printf("Turns taken: %d\n", game->turns);
    } else {
        printf("Game Over!\n");
        if (game->player.fuel <= 0) {
            printf("You ran out of fuel!\n");
        } else if (game->player.health <= 0) {
            printf("Your spaceship was destroyed by the asteroid!\n");
        }
        printf("Final Score: %d\n", game->player.score);
    }
    
    char name[MAX_NAME_LENGTH];
    printf("\nEnter your name for the high score board: ");
    scanf("%s", name);
    save_high_score(name, game->player.score, game->difficulty);
    
    printf("\nPress any key to continue...");
    getch();
}

int main() {
    Game game;
    char input;
    
    display_intro();
    Difficulty difficulty = select_difficulty();
    initialize_game(&game, difficulty);
    
    while (1) {  // Changed to infinite loop with break conditions
        print_game(&game);
        
        // Check game state before getting input
        if (game.state != PLAYING) {
            game_over(&game);
            return 0;
        }
        
        input = getch();
        switch (input) {
            case 'w':
            case 'W':
            case 's':
            case 'S':
            case 'a':
            case 'A':
            case 'd':
            case 'D':
                move_player(&game, input);
                break;
            case 'h':
            case 'H':
                display_help();
                break;
            case 'q':
            case 'Q':
                return 0;
        }
    }
    
    return 0;
} 