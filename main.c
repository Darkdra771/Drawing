#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "file.h"
#include "drawCommand.h"
#include "adjust.h"
#include "commandPrompt.h"

/*
 *This program is called paint which is a text based version of paint
 */

void getDimension(int* numRows, int* numCols, int argc, char **argv){
    //This function checks for the number of arguments entered by the user
    //prints default board of 10 x 10 if user entered invalid command

    if (argc == 1){
        *numRows = 10;
        *numCols = 10;
        return;
    }

    else if ((argc > 3) || (argc == 2)){
        printf("Wrong number of command line arguements entered.\n");
        printf("Usage: ./paint.out [num_rows num_cols]\n");
        *numRows = 10;
        *numCols = 10;
	printf("Making default board of %d X %d.\n", *numRows, *numCols);

	return;
    }

    else if (argc == 3){
        if (sscanf(argv[1], "%d", &*numRows) == 0){
            printf("The number of rows is not an integer.\n");
       	    *numRows = 10;
            *numCols = 10;
            printf("Making default board of %d X %d.\n", *numRows, *numCols);
            return;
        }
        if (sscanf(argv[2], "%d", &*numCols)== 0){
            printf("The number of columns is not an integer.\n");
            *numRows = 10;
            *numCols = 10;
            printf("Making default board of %d X %d.\n", *numRows, *numCols);
            return;
        }
        else {
            if (*numRows < 1){
                printf("The number of rows is less than 1.\n");
       		*numRows = 10;
        	*numCols = 10;
        	printf("Making default board of %d X %d.\n", *numRows, *numCols);
        	return;
            }
            else if (*numCols < 1){
                printf("The number of columns is less than 1.\n");
                *numRows = 10;
                *numCols = 10;
                printf("Making default board of %d X %d.\n", *numRows, *numCols);
                return;
            }
            else {
                return;
            }
        }

    }

}

char** makeBoard(int numRows, int numCols){
    //This function makes the board based on the user input
    //and fill a 2d array with '*'

    int i,j;

    char** board = (char**)malloc(numRows * sizeof(char*));

    for (i = 0; i < numRows; i++){
        board[i] = (char*)malloc((numCols + 1) * sizeof(char));
    }

    for (i = 0; i < numRows; i++){
        for (j = 0; j < numCols; j++){
            board[i][j] = '*';
        }
    }



    return board;
}

void printBoard(char **board, int rows, int cols){
    //This function prints the board based on the current position

    int i,j,k = 0;

    for (i = 0; i < rows; i++){
        printf("%d ", (rows - (i + 1)));
        for (j = 0; j < cols; j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }

    printf(" ");
    while (k != cols){
    printf(" %d", k);
    k++;
    }
    printf("\n");

    return ;
}


void freeMemory(char **board, int numRows){
    //This function is to free the memory of the 2d array

    int i;

    for (i = 0; i < numRows; i++){
        free(board[i]);
    }

    free(board);

    return;
}

void paint(char **board, int numRows, int numCols){
    //This function reads the command of the user
    //based on the first command of the user, execute the respective function
    //repeats until the user enter 'q' for quit

    char command;
    char checkChar;
    bool check = true;


    do {
	do {
        printBoard(board, numRows, numCols);
        printf("Enter your command: ");
        scanf("%c", &command);
	check = true;
	if (command == '\n'){
		scanf("%c", &command);
	}
        scanf("%c", &checkChar);
	if (checkChar != ' ' && checkChar != '\n'){
		printf("Unrecognized command. Type h for help.\n");
		check = false;
		while (checkChar != '\n'){
			scanf("%c", &checkChar);
		}
	}
	} while(check == false);

        switch(command){

            case 'q' :
		while (checkChar != '\n'){
			scanf("%c", &checkChar);
			if (!isspace(checkChar)){
			check = false;
			}
		}
		if (check == false){
			printf("Unrecognized command. Type h for help.\n");
		}
                break;

            case 'h' :
		while (checkChar != '\n'){
			scanf("%c", &checkChar);
			if (!isspace(checkChar)){
			check = false;
			}
		}
		if (check == false){
			printf("Unrecognized command. Type h for help.\n");
			break;
		}
                print_help();
                break;

            case 'w' :
               	draw(&board, numRows, numCols);
                break;

            case 'e' :
                erase(&board, numRows, numCols);
                break;

            case 'r' :
                board = resize(&board, &numRows, &numCols);
                break;

            case 'a' :
                addPos(&board, &numRows, &numCols);
                break;

            case 'd' :
                delPos(&board, &numRows, &numCols);
                break;

            case 's' :
                saveFile(board, numRows, numCols);
                break;

            case 'l' :
                board = openFile(board, &numRows, &numCols);
                break;

            default :
                printf("Unrecognized command. Type h for help.\n");
        }


    }while (command != 'q' || !check);

	freeMemory(board, numRows);

}

int main(int argc, char *argv[]){
    //get user input
    //makes board
    //execute paint program

    int numRows = 0;
    int numCols = 0;

    getDimension(&numRows, &numCols, argc, argv);
    char** board = makeBoard(numRows, numCols);

    paint(board, numRows, numCols);


    return 0;
}
