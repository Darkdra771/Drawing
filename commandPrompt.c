#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "drawCommand.h"
#include "commandPrompt.h"

bool takes(){
    //This function is to consume all of the white spaces after input


    char checkChar = ' ';
    bool check = true;

    scanf("%c",&checkChar);
    while (checkChar != '\n'){
        if ((checkChar != ' ') && (checkChar != '\n')){
            check = false;
        }
        scanf("%c", &checkChar);
    }

    return check;
}


void print_help(){
    //This function prints the available command


	printf("Commands:\n");
	printf("Help: h\n");
	printf("Quit: q\n");
	printf("Draw line: w row_start col_start row_end col_end\n");
	printf("Resize: r num_rows num_cols\n");
	printf("Add row or column: a [r | c] pos\n");
	printf("Delete row or column: d [r | c] pos\n");
	printf("Erase: e row col\n");
	printf("Save: s file_name\n");
	printf("Load: l file_name\n");
}

bool checkCommand(int x_coor, int y_coor, int numRows, int numCols){
    //This function check whether the command entered by the user
    //is less than 0 or more than the size of the current board
    //if it is, then it is invalid command

    if ((x_coor >= numCols) || (x_coor < 0)){
        return false;
    }

    if ((y_coor >= numRows) || (y_coor < 0)){
        return false;
    }

    else {
        return true;
    }
}

void draw(char ***board, int numRows, int numCols){
    //This function scans for the coordinates of the line the user wants to draw
    //then checks whether it is horizontal, vertical or diagonal line
    //execute the following function

    Coor intPoint;
    Coor finPoint;
    int argsRead = 0;
    char newLine;





      argsRead += scanf("%d", &intPoint.y_coor);
      argsRead += scanf("%d", &intPoint.x_coor);
      if ((argsRead != 2) || !checkCommand(intPoint.x_coor, intPoint.y_coor, numRows, numCols)){
        do{
            scanf("%c", &newLine);
        }while (newLine != '\n');
        printf("Improper draw command.\n");
        return;
      }



      argsRead -=scanf("%d", &finPoint.y_coor);
      argsRead -= scanf("%d", &finPoint.x_coor);
      if((argsRead != 0) || !checkCommand(finPoint.x_coor, finPoint.y_coor, numRows, numCols)){
        do{
            scanf("%c", &newLine);
        }while (newLine != '\n');
        printf("Improper draw command.\n");
        return;
      }

      if (!takes()){
	printf("Improper draw command.\n");
	return;
      }

    if ((intPoint.x_coor == finPoint.x_coor) && (intPoint.y_coor == finPoint.y_coor)){
        (*board)[numRows - 1 -intPoint.y_coor][finPoint.x_coor] = '-';
    }

    else if (intPoint.y_coor == finPoint.y_coor){
        drawHorizontal(intPoint, finPoint, board, numCols, numRows);
    }

    else if (intPoint.x_coor == finPoint.x_coor){
        drawVertical(intPoint, finPoint, board, numRows);
    }

    else if ((intPoint.y_coor < finPoint.y_coor) && (intPoint.x_coor < finPoint.x_coor)){
        drawRightDiag(intPoint, finPoint, board, numRows, numCols);
    }

    else if ((intPoint.y_coor > finPoint.y_coor) && (intPoint.x_coor > finPoint.x_coor)){
        drawRightDiag(intPoint, finPoint, board, numRows, numCols);
    }

    else if ((intPoint.x_coor < finPoint.x_coor) && (intPoint.y_coor > finPoint.y_coor)){
        drawLeftDiag(intPoint, finPoint, board, numRows, numCols);
    }

    else if ((intPoint.x_coor > finPoint.x_coor) && (intPoint.y_coor < finPoint.y_coor)){
        drawLeftDiag(intPoint, finPoint, board, numRows, numCols);
    }

return;

}

void erase(char ***board, int numRows, int numCols){
    //This function scans the user input for the coordinate to delete

    int row,col;
    int argsRead = 0;
    char newLine;

    argsRead += scanf("%d", &row);
    argsRead += scanf("%d", &col);
    if ((argsRead != 2) || !checkCommand(col, row, numRows, numCols) ){
        do{
            scanf("%c", &newLine);
        }while (newLine != '\n');
        printf("Improper erase command.\n");
        return;
    }

    if (!takes()){
	printf("Improper erase command.\n");
    }


    (*board)[numRows - 1 - row][col] = '*';


    return;
}

char** resize(char*** board, int *numRows, int *numCols){
    //This function is to resize the board
    //scans for new row and new column
    //delete the old board and return the new board;

    int newRows, newCols;
    int i,j, k = 0;
    int argsRead = 0;
    char newLine;


    //get input
    argsRead += scanf("%d", &newRows);
    argsRead += scanf("%d", &newCols);
    if((argsRead != 2)){
        do{
            scanf("%c", &newLine);
        }while (newLine != '\n');
        printf("Improper resize command.\n");
        return *board;
    }

    if (!takes()){
	printf("Improper resize command.\n");
	return *board;
    }

    if ((newRows < 1) || (newCols < 1)){
	printf("Improper resize command.\n");
	return *board;
    }

    char** newBoard;

    //make temp board
	newBoard = (char**)malloc(newRows * sizeof(char*));

	for ( i = 0; i < newRows; i++){
		newBoard[i] = (char*)malloc(newCols * sizeof(char));
	}


        for (i = newRows - 1; i >= 0; i--){
            for (j = 0; j < newCols; j++){
                newBoard[i][j] = '*';
            }
        }

    //this resize to smaller board
    if ((newRows < *numRows) && (newCols < *numCols)){


        for (i = *numRows - 1; i >= *numRows - newRows; i--){
            for (j = 0; j < newCols; j++){
                newBoard[newRows - 1 - k][j] = (*board)[i][j];
            }
            k++;
        }

    }

    //this resize to larger board
    else if ((newRows > *numRows) && (newCols > *numCols)){


        for (i = newRows - 1; i > 0; i--){
            for (j = 0; j < *numCols; j++){
                newBoard[i][j] = (*board)[*numRows - 1 - k][j];
            }
	    if (*numRows - 1 - k == 0){
		break;
	    }
            k++;
     }
    }

    //this elongates the board
    else if ((newRows > *numRows) && (newCols < *numCols)){

        for (i = newRows - 1; i >= newRows - *numRows; i--){
            for (j = 0; j < newCols; j++){
                newBoard[i][j] = (*board)[*numRows - 1 - k][j];
            }
            if (*numRows - 1 - k == 0){
                break;
            }
            k++;
        }
    }

    //this flatten the board
    else if ((newRows < *numRows) && (newCols > *numCols)){

        for (i = newRows - 1; i >= 0; i--){
            for (j = 0; j < *numCols;j++){
                newBoard[i][j] = (*board)[*numRows - 1 - k][j];
            }
            if (*numRows - 1 - k == 0){
                break;
            }
            k++;

        }
    }



    //frees the board
   for (i = 0; i < *numRows; i++){
	free((*board)[i]);
    }
    free(*board);

    *numRows = newRows;
    *numCols = newCols;

    return newBoard;
}


