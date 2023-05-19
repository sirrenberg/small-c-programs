#include <stdio.h>
#include <stdlib.h>
#include <time.h> // used to get the time.
#include <string.h>
#define SCOREBOARD_MAX_SIZE 10
#define RANDOM_NUMBER_UPPER_BOUND 100

struct player {
    char name[20];
    int score;
};

/*
 * Read the scoreboard from the csv file. Save the entries of the scoreboard in the array entries and 
 */
void read_scoreboard_from_file(struct player * entries, int *size_of_scoreboard){
    FILE *scoreboard_file;
    scoreboard_file = fopen("./scoreboard.csv", "r");
    char current_line[256]; // string saved on the stack in which the line is saved that was read from the file.
    int number_of_lines = 0;
    char name[20];
    int score;

    while ((fgets(current_line, 256, scoreboard_file) != NULL) && (number_of_lines <= *size_of_scoreboard)) { //the name current_line decays to a pointer to the array.
        sscanf(current_line, "%[^,], %d", name, &score);
        strcpy(entries[number_of_lines].name, name);
        entries[number_of_lines].score = score;
        number_of_lines++;
    }
    
    *size_of_scoreboard = number_of_lines;
    fclose(scoreboard_file);
}

/*
Set a seed for the random number generator.
*/
void saltTheRNG(){
    int numberOfSecondsSinceJan1_1970 = time(NULL);
    srand(numberOfSecondsSinceJan1_1970); // sets the seed for the random number generator.
}

/*
 * Start a game of Guess A Number, create a random number between 1 and upper_bound and return the number of guesses until the correct answer was found.
 */
int playGame(int upper_bound){
    int randomNumber = 1 + rand() % upper_bound; // create a random number in the interval [1,upper_bound), but destroys the uniformity

    printf("%s %i %s\n", "I created a random number between 1 and", upper_bound, "Try to guess it.");
    int guess;

    //printf("My number is %i and yours is %i", randomNumber, guess);

    int numberOfGuesses = 0;

    do{
        numberOfGuesses++;
        printf("Try number %i: ", numberOfGuesses);
        scanf("%i", &guess);
        if (guess > randomNumber) {
            printf("My number is smaller.\n");
        }
        else if (guess < randomNumber) {
            printf("My number is larger.\n");
        }
    } while(guess != randomNumber);

    printf("Yes, my number was %i. You needed %i tries to guess it right.\n", randomNumber, numberOfGuesses);

    return numberOfGuesses;
}

void print_scoreboard(struct player * scoreboard, int size){
    for(int i = 0; i < size; i++){
        printf("%i\t", scoreboard[i].score);
        printf("%s\n", scoreboard[i].name);
    }
}

/*
 * Return the position of the current_score in the scoreboard. If the current_score is worse than every score on the scoreboard, return -1.
 */
int position_in_scoreboard(struct player * scoreboard, int size, int current_score){
    for(int i = 0; i < size; i++){
        if(scoreboard[i].score > current_score){
            return i;
        }
    }
    return -1;
}

/*
 * Update the scoreboard.
 */
void update_scoreboard(struct player * scoreboard, int size, int new_high_score, char * name, int position){
    for(int i = size - 1; i > position; i--){
        strcpy(scoreboard[i].name, scoreboard[i-1].name);
        scoreboard[i].score = scoreboard[i-1].score;
    }
    strcpy(scoreboard[position].name, name);
    scoreboard[position].score = new_high_score;
}

void write_scoreboard_to_file(struct player * scoreboard, int size){
    FILE *scoreboard_file;
    scoreboard_file = fopen("./scoreboard.csv", "w");
    for(int i = 0; i < size; i++){
        fprintf(scoreboard_file, "%s,%i\n", scoreboard[i].name, scoreboard[i].score);
    }
    fclose(scoreboard_file);
}

int main(void){
    saltTheRNG();
    int playerWantsToPlay = 1;
    char choice_of_action;

    struct player *scoreboard;
    scoreboard = malloc(10 * sizeof(struct player));
    int size_of_scoreboard = SCOREBOARD_MAX_SIZE;

    int upper_bound = RANDOM_NUMBER_UPPER_BOUND;

    read_scoreboard_from_file(scoreboard, &size_of_scoreboard);

    printf("%s\n", "Welcome to Guess A Number.");
    print_scoreboard(scoreboard, size_of_scoreboard);

    do {
        printf("%s\n", "Choose an action.:");
        printf("%s\n", "[p]lay the game.");
        printf("%s\n", "[s]how the scoreboard.");
        printf("%s\n", "[q]uit");
        
        choice_of_action = (char) fgetc(stdin);
        if (choice_of_action == '\n' || choice_of_action == EOF){
            choice_of_action = (char) fgetc(stdin);
        }

        switch (choice_of_action){
            case 'q':
                printf("Thank you for playing.\n");
                playerWantsToPlay = 0;
                break;
            case 's':
                print_scoreboard(scoreboard, size_of_scoreboard);
                break;
            case 'p':
                int current_score = playGame(upper_bound);
                int position = position_in_scoreboard(scoreboard, size_of_scoreboard, current_score);

                if (position > -1){
                    printf("%s %i %s\n", "Congratulations, you are position", position + 1, "on the scoreboard.");
                    printf("%s", "Please enter your name: ");
                    char name[20]; 
                    fscanf(stdin, "%s", name);
                    update_scoreboard(scoreboard, size_of_scoreboard, current_score, name, position);
                    write_scoreboard_to_file(scoreboard, size_of_scoreboard);
                }
                break;
            default:
                printf("%s\n", "Input unknown.");
        }
    } while(playerWantsToPlay);
    free(scoreboard);

    return 0;
}
