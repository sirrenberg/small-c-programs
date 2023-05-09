#include <stdio.h>
#include <stdlib.h>
#include <time.h> // used to get the time.
#include <string.h>

/*
Set a seed for the random number generator.
*/
void saltTheRNG(){
    int numberOfSecondsSinceJan1_1970 = time(NULL);
    srand(numberOfSecondsSinceJan1_1970); // sets the seed for the random number generator.
}

void playGame(){
    int randomNumber = 1 + rand() % 100; // create a random number in the interval [1,100], but destroys the uniformity

    printf("I created a random number between 1 and 100. Try to guess it.\n");
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
}

int main(void){
    saltTheRNG();
    int playerWantsToPlay = 1;
    char answerToPlayWishQuestion[4];

    do {
        playGame();
        printf("Do you want to play again? [Yes, No]: ");
        
        scanf("%s", answerToPlayWishQuestion);
        if (strcmp(answerToPlayWishQuestion,"No") == 0){
            printf("Thank you for playing.\n");
            break;
        }
    } while(playerWantsToPlay);
}
