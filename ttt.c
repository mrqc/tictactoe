#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define AI 1
#define PLAYER 2
#define EMPTY 0
#define MAX 9
#define TRUE 1
#define FALSE 0

int field[MAX]; //indexes from 0-8
// indexes in the field are as follows:
// 0 1 2
// 3 4 5
// 6 7 8

int wonPlayer = 0;
int wonAi = 0;
int gamesCount = 0;

//declaration of all functions
void printField();
int again();
void printStats();
void playGame();
int nextFieldToPlace();
int checkDraw();
int checkWon();
int getBeginner();
void clearField();
int checkIfPlayerCouldWin();

// implementation of all functions
void clearField() {
	for (int i = 0; i < MAX; i++) {
		field[i] = EMPTY;
	}
}

int getBeginner() {
	rand(); rand(); rand(); //to force a random number
	double random = (double) rand() / (double) RAND_MAX; //get random number between 0 and 1
	if (random > 0.5) { //50% chance to be above 0.5 and 50% to below 0.5
		return PLAYER;
	}
	return AI;
}

int checkWon() {
	//horizontal winning
	if (field[0] == field[1] && field[1] == field[2] && field[0] != EMPTY) {
		return field[0];
	} else if (field[3] == field[4] && field[4] == field[5] && field[3] != EMPTY) {
		return field[3];
	} else if (field[6] == field[7] && field[7] == field[8] && field[6] != EMPTY) {
		return field[6];
	}
	//vertical winning
	if (field[0] == field[3] && field[3] == field[6] && field[0] != EMPTY) {
		return field[0];
	} else if (field[1] == field[4] && field[4] == field[7] && field[1] != EMPTY) {
		return field[1];
	} else if (field[2] == field[5] && field[5] == field[8] && field[2] != EMPTY) {
		return field[2];
	}
	//diagonal winning
	if (field[0] == field[4] && field[4] == field[8] && field[0] != EMPTY) {
		return field[0];
	} else if (field[2] == field[4] && field[4] == field[6] && field[2] != EMPTY) {
		return field[2];
	}
	return EMPTY;
}

int checkDraw() {
	if (!checkWon()) {
		for (int i = 0; i < MAX; i++) {
			if (field[i] == EMPTY) { //if one field is empty it is possible to set a field
				return FALSE;
			}
		}
		return TRUE;
	}
	return FALSE;
}

int nextFieldToPlace() {
	int choice = checkIfPlayerCouldWin(); //if player is on to win, take the winning field as next
	if (choice == -1) {
		//in prioritized order which cell is preferred to place next by the AI
		if (field[4] == EMPTY) {
			choice = 4;
		} else if (field[0] == EMPTY) {
			choice = 0;
		} else if (field[8] == EMPTY) {
			choice = 8;
		} else if (field[2] == EMPTY) {
			choice = 2;
		} else if (field[6] == EMPTY) {
			choice = 6;
		} else if (field[1] == EMPTY) {
			choice = 1;
		} else if (field[7] == EMPTY) {
			choice = 7;
		} else if (field[3] == EMPTY) {
			choice = 3;
		} else if (field[5] == EMPTY) {
			choice = 5;
		}
	}
	return choice;
}

int checkIfPlayerCouldWin() {
	for (int index = 0; index < MAX; index++) {
		if (field[index] == EMPTY) {
			field[index] = PLAYER;
			if (checkWon() == PLAYER) {
				field[index] = EMPTY;
				return index;
			}
			field[index] = EMPTY;
		}
	}
	return -1;
}

void playGame() {
	int currentTurn = getBeginner();
	int won = EMPTY;
	while (!checkDraw() && won == EMPTY) { //check if draw or one has still won the game
		int fieldChoice = -1;
		printField();
		if (currentTurn == PLAYER) { //if player is on turn get input from player
			while(fieldChoice < 1 || fieldChoice > MAX) {
				printf("your turn, next field to place [1-9]: ");
				scanf("%d", &fieldChoice);
			}
			fieldChoice--; //since player has to input between 1-9 our indexex are between 0-8
		} else if (currentTurn == AI) { //if AI is on turn get the most proper index of the field to be set
			fieldChoice = nextFieldToPlace();
			printf("computers turn on field: %d\n", fieldChoice);
		}
		if (fieldChoice < MAX && fieldChoice >= 0) {
			//check the index which should be set in the field
			//the AI algorithm should return correct one
			//but the user can type in anything		
			field[fieldChoice] = currentTurn; //set the field to the players symbol which is on turn
			if (currentTurn == AI) {
				currentTurn = PLAYER; //AI was on turn now player
			} else if (currentTurn == PLAYER) {
				currentTurn = AI; //player was on turn now AI
			}
		}
		won = checkWon();
	}
	printField();
	if (won == PLAYER) {
		printf("you won\n");
		wonPlayer++; //count on games for player
	} else if (won == AI) {
		printf("you lost\n");
		wonAi++; //count on games for AI
	} else {
		printf("draw\n");
	}
	gamesCount++;
}

void printStats() {
	float percentPlayer = ((float) wonPlayer) / ((float) gamesCount) * 100;
	float percentAi = ((float) wonAi) / ((float) gamesCount) * 100;
	int countDraw = gamesCount - wonPlayer - wonAi;
	printf("stats\n");
	printf("====================\n");
	printf("games count %d\n", gamesCount);
	printf("player won: %f percent\n", percentPlayer);
	printf("AI won: %f percent\n", percentAi);
	printf("====================\n");
}

int again() {
	printf("again? (y/n) ");
	char choice;
	scanf(" %c", &choice);
	if (choice == 'n') {
		return FALSE;
	}
	return TRUE;
}

void printField() {
	printf("\n\n---\n");
	for (int i = 0; i < MAX; i++) {
		if (i % 3 == 0 && i > 0) {
			printf("\n");
		}
		if (field[i] == AI) {
			printf("O");
		} else if (field[i] == PLAYER) {
			printf("X");
		} else if (field[i] == EMPTY) {
			printf(" ");
		}
	}
	printf("\n---\n\n\n");
}

int main() {
	srand((unsigned)time(NULL));
	while (TRUE) {
		clearField();
		playGame();
		printStats();
		if (!again()) {
			break;
		}
	}
}
