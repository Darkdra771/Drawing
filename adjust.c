#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "adjust.h"
#include "commandPrompt.h"



void addPos(char ***board,int *numRows,int *numCols){
    //This function is to add rows or column
    //makes a newboard and fill it with the corresponding value
    //and then resizes the board to the new board

    char pos;
    int numPos;
    int i,j,k = 0;
    int argsRead = 0;
    char check = ' ';

    //get input
    argsRead += scanf(" %c", &pos);
    if (pos != 'r' && pos != 'c'){
	printf("Improper add command.\n");
	while (check != '\n'){
		scanf("%c", &check);
	}
	return;
    }
    argsRead += scanf("%d", &numPos);
    if (argsRead != 2){
	printf("Improper add command.\n");
	while (check != '\n'){
		scanf("%c", &check);
	}
	return;
    }

    if (!takes()){
	printf("Improper add command.\n");
	return;
    }

    //for row
    if (pos == 'r'){

	if ((numPos > *numRows) || (numPos < 0)){
		printf("Improper add command.\n");
		return;
        }

        int newRows = *numRows + 1;

        //create temp board
        char newBoard[newRows][*numCols];


        for (i = 0; i < newRows; i++){
            for (j = 0; j < *numCols; j++){
                newBoard[i][j] = '*';
            }
        }

        //modify the temp board to desired
        k = *numRows;
        for (i = newRows - 1; i >= 0; i--){
            for (j = 0; j < *numCols; j++){
                if (numPos == 0){
                    newBoard[i][j] = '*';
                }
                else {
                    newBoard[i][j] = (*board)[k - 1][j];
                }
            }
            if (numPos != 0){
                k--;
            }
            numPos--;
        }

        //reallocates space in the board

        *board = realloc(*board, newRows * sizeof(char*));

        for (i = 0; i < newRows; i++){
            (*board)[i] = realloc((*board)[i], *numCols * sizeof(char));
        }

        for (i = 0; i < newRows; i++){
            for (j = 0; j < *numCols; j++){
                (*board)[i][j] = newBoard[i][j];
            }
        }

        *numRows = newRows;

    }

    //if column
    else if (pos == 'c'){

	if ((numPos > *numCols) || (numPos < 0)){
		printf("Improper add command.\n");
		return;
   	 }

        int newCols = *numCols + 1;

        char newBoard[*numRows][newCols];

        //make temp board
        for (i = 0; i < *numRows; i++){
            for (j = 0; j < newCols; j++){
                newBoard[i][j] = '*';
            }
        }

        //modify the temp board to desired board
        for (i = *numRows - 1; i >= 0; i--){
            k = 0;
            for (j = 0; j < newCols; j++){
                if (j == numPos){
                    newBoard[i][j] = '*';
                    continue;
                }
                else {
                    newBoard[i][j] = (*board)[i][k];
                }
                k++;
            }
        }

        //reallocates space of the board

        for (i = 0; i < *numRows; i++){
            (*board)[i] = realloc((*board)[i], newCols * sizeof(char));
        }

        for (i = 0; i < *numRows; i++){
            for (j = 0; j < newCols; j++){
                (*board)[i][j] = newBoard[i][j];
            }
        }

        *numCols = newCols;

    }

    return;
}

void delPos(char ***board, int *numRows, int *numCols){
    //This function is deletes rows or column
    //makes a newboard and fill it with the corresponding value
    //and then resizes the board to the new board

    char pos;
    int numPos;
    int i,j,k = 0;
    char check = ' ';
    int argsRead = 0;


    argsRead += scanf(" %c", &pos);
    if (pos != 'r' && pos != 'c'){
	printf("Improper delete command.\n");
	while (check != '\n'){
		scanf("%c", &check);
	}
	return;
    }
    argsRead += scanf("%d", &numPos);
    if (argsRead != 2){
	printf("Improper delete command.\n");
	while (check != '\n'){
		scanf("%c", &check);
	}
	return;
    }

    if (!takes()){
	printf("Improper delete command.\n");
	return;
    }

    //if rows
    if (pos == 'r'){

	if ((numPos >= *numRows) || (numPos < 0)){
		printf("Improper delete command.\n");
		return;
  	}

        int newRow = *numRows - 1;

        char newBoard[newRow][*numCols];

        //make temp board
        for (i = 0; i < newRow; i++){
            for (j = 0; j < *numCols; j++){
                newBoard[i][j] = '*';
            }
        }

        //modify the temp board
        k = newRow - 1;
        for (i = *numRows - 1; i >= 0; i--){
            for (j = 0; j < *numCols; j++){
                if (i == (*numRows - numPos - 1)){
                    break;
                }
                newBoard[k][j] = (*board)[i][j];
            }
            if (i != (*numRows - numPos - 1)){
                k--;
            }
        }

        //resizes the board

        (*board) = realloc(*board, newRow * sizeof(char*));

        for (i = 0; i < newRow; i++){
            (*board)[i] = realloc((*board)[i], *numCols * sizeof(char));
        }


        for (i = 0; i < newRow; i++){
            for (j = 0; j < *numCols; j++){
                (*board)[i][j] = newBoard[i][j];
            }
        }


        *numRows = newRow;

    }

    //if columns
    else if (pos == 'c'){

	if ((numPos >= *numCols) || (numPos < 0)){
		printf("Improper delete command.\n");
		return;
   	 }

        int newCol  = *numCols - 1;

        char newBoard[*numRows][newCol];

        //make temp board
        for (i = 0; i < *numRows; i++){
            for (j = 0; j < newCol; j++){
                newBoard[i][j] = '*';
            }
        }

        //modify temp board to desired
        for (i = *numRows - 1; i >= 0; i--){
            for (j = 0; j < *numCols; j++){
                if (j == numPos){
                    continue;
                }
                newBoard[i][k] = (*board)[i][j];
                k++;
            }
            k = 0;
        }

         //resizes the board

        (*board) = realloc(*board, *numRows * sizeof(char*));

        for (i = 0; i < *numRows; i++){
            (*board)[i] = realloc((*board)[i], newCol * sizeof(char));
        }


        for (i = 0; i < *numRows; i++){
            for (j = 0; j < newCol; j++){
                (*board)[i][j] = newBoard[i][j];
            }
        }


        *numCols = newCol;

    }


    return;
}

