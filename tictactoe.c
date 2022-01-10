/* 
	Poner el getline para tomar input, y que tome strings.
	Tambien arreglar el temita de los prints, que muestre currentPlayer para evitar confusiones
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* Function declarations */
void printTable(char table[4][7]);
void getCoordinates(char table[4][7], int currentPlayer);
int checkWinner(char table[4][7], int currentPlayer);
void printFile(FILE *file);

int main(void) {
	/* Table variables */
	char row;
	char col;
	char table[4][7] = {
				{'*', ' ', '1', ' ', '2', ' ', '3'},
				{'1', ' ', ' ', '|', ' ', '|', ' '},
				{'2', ' ', ' ', '|', ' ', '|', ' '},
				{'3', ' ', ' ', '|', ' ', '|', ' '}
				};
	/* Player count */
	int turnCount;
	int currentPlayer = 1;
	char playAgain;
	FILE *file;


	file = fopen("ASCII/intro.txt", "r");
	printFile(file);
	file = fopen("ASCII/authors.txt", "r");
	printFile(file);
	sleep(1);
	system("clear");
	
	while (1) {
		for (turnCount = 0; turnCount < 9; turnCount++) {
			printf("Player %d\n\n", currentPlayer);
			printTable(table);
			getCoordinates(table, currentPlayer);
			system("clear");
			
			if (checkWinner(table, currentPlayer) == 0) {
				if (currentPlayer == 1) {
					file = fopen("ASCII/winnerOne.txt", "r");
				}
				else {
					file = fopen("ASCII/winnerTwo.txt", "r");
				}
				printFile(file);
				break;
			}

			if (currentPlayer == 1) {
				currentPlayer = 2;
			} else {
				currentPlayer = 1;
			}
		}

		if (turnCount == 9) {
			file = fopen("ASCII/draw.txt", "r");
			printFile(file);
		}
		break;
	}
	file = fopen("ASCII/end.txt", "r");
	printFile(file);
	return 0;
}

void printTable(char table[4][7]) {
	int row;
	int col;
		
	for (row = 0; row < 4; row++) {
		for (col = 0; col < 7; col++) {
			printf("%c", table[row][col]);
		}
		printf("\n");
	}
}

void getCoordinates(char table[4][7], int currentPlayer) {
	char *rowString = NULL;
	char *colString = NULL;
	int row = -1;
	int col = -1;
	char playerOne = 'X';
	char playerTwo = 'O';
	size_t bufferSize;

	while (1) {
		/* Get row and reassign to correct value */
		while (row == -1) {
			printf("Please input the row number: ");
			bufferSize = 0;
			getline(&rowString, &bufferSize, stdin);
			rowString[strcspn(rowString, "\n")] = 0;
			if (strcmp(rowString, "1") != 0 && strcmp(rowString, "2") != 0 && strcmp(rowString, "3") != 0) {
				printf("Row numbers must be 1, 2 or 3\n");
				continue;
			}
			row = atoi(rowString);
		}
		
		/* Get column and reassign to correct value */
		while (col == -1) {
			printf("Please input the column number: ");
			bufferSize = 0;
			getline(&colString, &bufferSize, stdin);
			colString[strcspn(colString, "\n")] = 0;
			if (strcmp(colString, "1") != 0 && strcmp(colString, "2") != 0 && strcmp(colString, "3") != 0) {
				printf("\nColumn numbers must be 1, 2 or 3\n");
				continue;
			}
			col = ((atoi(colString) -1) * 2) + 2;
		}
		
		/* Check if the space is empty */
		if (table[row][col] != ' ') {
			printf("\nThat space has been taken. Please enter new coordinates\n");
			continue;
		}
		break;
	}
	if(currentPlayer == 1) {
		table[row][col] = playerOne;
	} else {
		table[row][col] = playerTwo;
	}

}

int checkWinner(char table[4][7], int currentPlayer) {
	/* Retorna 0 cuando encontro, 1 cuando no */
	char row;
	char col;
	char searchChar;

	if (currentPlayer == 1) {
		searchChar = 'X';
	}
	else {
		searchChar = 'O';
	}

	if ((table[1][2] == searchChar && table[1][4] == searchChar && table[1][6] == searchChar) || // row 1
		(table[2][2] == searchChar && table[2][4] == searchChar && table[2][6] == searchChar) || // row 2
		(table[3][2] == searchChar && table[3][4] == searchChar && table[3][6] == searchChar) || // row 3
		(table[1][2] == searchChar && table[2][2] == searchChar && table[3][2] == searchChar) || // col 2
		(table[1][4] == searchChar && table[2][4] == searchChar && table[3][4] == searchChar) || // col 4
		(table[1][6] == searchChar && table[2][6] == searchChar && table[3][6] == searchChar) || // col 6
		(table[1][2] == searchChar && table[2][4] == searchChar && table[3][6] == searchChar) || // diag 1
		(table[1][6] == searchChar && table[2][4] == searchChar && table[3][2] == searchChar)) { // diag 2
		return 0;
	}

	return 1;
}

void printFile(FILE *file) {
	char * line = NULL;
    size_t len = 0;
    ssize_t read;

	system("clear");

	while ((read = getline(&line, &len, file)) != -1) {
        printf("%s", line);
    }

    fclose(file);
    if (line) {
        free(line);
	}
	sleep(1);
}