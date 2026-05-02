//Author: Cameron Van Fleet
//Purpose: Wordle Game
//Date: 5/1/26

#include <stdio.h>
#define capacity 100
#define passwordFile "mystery.txt"
/*
ALGORITHM:

- The user is asked to enter a guess
- The program takes that guess and displays back to user if it is the correct word, otherwise, it shows which characters are correct and in the correct position and correct character in the wrong position
- Repeat until the user has either guess correctly or the have made 6 incorrect guesses.
*/

//Pulls the correct word from the file and places it in a character array
int getPassword(char string[]);


//DisplayPrompt
void promptUser (char guess[], char game[][6], int* guesses, _Bool* win, _Bool *outOfGuesses);


//Returns true if the guess matches the password, otherwise returns false
_Bool winConditionComparator (char game[][6], char password[], int* guesses, _Bool *outOfGuesses);


//Prints the contents of the game
void showGame (char game[][6]);


//Returns which letters are correct characters and in the correct position
void getCorrectPositions(char password[], char game[][6], int* guesses);


//Returns which letters are correct characters, but in the wrong postion
void getCorrectCharacters(char password[], char game[][6], int guesses);


int main(){

	int guesses = 1;
	_Bool outOfGuesses = 0;
	_Bool win = 0;

	char password[capacity];
	getPassword(password);
	

	//Game board (6 guesses, 5 letters per guess + 1 null character)
	char game[6][6] = {{'-','-','-','-','-','-'},{'-','-','-','-','-','-'},{'-','-','-','-','-','-'},{'-','-','-','-','-','-'},{'-','-','-','-','-','-'},{'-','-','-','-','-','-'}};
	
	do {
		
		promptUser(password, game, &guesses, &win, &outOfGuesses);
		guesses++;
		
	} while (winConditionComparator(game, password, &guesses, &outOfGuesses));
	guesses--;
	
	if (outOfGuesses){
		printf("You lost, better luck next time!\n");
	} else {
		printf("		%s", game[guesses - 1]);
		printf("	You won in %d guesses!\n", guesses);
		if (guesses == 1){
			printf("		GOATED!\n");
		} else if (guesses > 1 && guesses < 4){
			printf("		Amazing!\n");
		} else if (guesses > 3 && guesses < 6){
			printf("		Nice!\n");
		} else {
			return 0;
		}
	}
	

	return 0;
}

int getPassword(char string[]){
	//Open the passwordFile
	FILE* fileptr;
	fileptr = fopen(passwordFile, "r");
	if (fileptr == NULL){
		printf("Can't Open File\n");
		return 0;
	}
	
	//Insert the word that the passwordFile contains into the character array
	char letter;
	int count = 0;
	while (fscanf(fileptr, " %c", &letter) == 1){
		string[count] = letter;
		count++;
	}
	//Close the passwordFile
	fclose(fileptr);
	return 0;
}


void promptUser (char password[], char game[][6], int* guesses, _Bool* win, _Bool *outOfGuesses){
	//Ask the user for a guess and store it in the next item in the game array
	
	
	
	//Prompt for a guess
	if (*guesses <= 5){
		printf("GUESS %d! Enter your guess: ", *guesses);
	} else if (*guesses == 6){
		printf("Final Guess: ");
	} else {
		return;
	}
	
	fgets(game[*guesses - 1], capacity, stdin);
	
	//Change to Lowercase
	for (int i = 0; i < 5; i++){
		if (game[*guesses - 1][i] < 97){
			game[*guesses - 1][i] += 32;
		}
	}
	
	
	
	printf("================================\n");
	
	int g = *guesses + 1;
	_Bool o = *outOfGuesses;
	
	getCorrectPositions(password, game, *&guesses);
	
	if (!winConditionComparator(game, password, &g, &o)){
		
		return;
	}
	
	
	
	//Display a list of all the previous guesses
	for (int i = 0; i < *guesses; i++){
		for (int j = 0; j < 5; j++){
			printf("%c", game[i][j]);
		}
		printf("\n");
		getCorrectCharacters(password, game, i);
		printf("\n");
		
	}
	
	
	
}


_Bool winConditionComparator (char game[][6], char password[], int* guesses, _Bool *outOfGuesses){
	
	//Compare the last entered guess to the password, if all the characters match, then they are the same otherwise they are not.
	if (*guesses >= 8){
		*outOfGuesses = 1;
		
	}
	_Bool areTheSame = 0;
	for (int i = 0; i < 5; i++){
		//printf("\nGAME: %c, PASS: %c\n", (game[*guesses - 2][i] + 32), password[i]);
		if ((game[*guesses - 2][i] + 32) == password[i]){
			areTheSame = 1;	
		} else {
			areTheSame = 0;
			
			break;
		}
	}
	
	if (*outOfGuesses || areTheSame){
		//printf("\nSame or Out\n");
		return 0;
	} else {
		return 1;
	}
	
}


void showGame (char game[][6]){
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 5; j++){
			printf("%c", game[i][j]);
		}
		printf("\n");
		
	}
}


void getCorrectPositions(char password[], char game[][6], int* guesses){
	
	for (int j = 0; j < 5; j++){
		//printf("game: %c password: %c \n", game[*guesses - 1][j], password[j]);
		if (game[*guesses - 1][j] == password[j]){
			game[*guesses - 1][j] = password[j] - 32;		
		}
	}
}


void getCorrectCharacters(char password[], char game[][6], int guesses){
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++){
			if(game[guesses][i] == password[j]){
				printf("^");
				break;
			} else if (j == 4) {
				printf(" ");
			}
					
		
		}
		
	}
}

