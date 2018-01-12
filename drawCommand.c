#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "drawCommand.h"




bool checkOverlap(int y_coor, int x_coor,char draw, char ***board){
    //This function is to check if there are any overlaps in drawing
    //if there is draw '+';

	if ((*board)[y_coor][x_coor] != '*' && (*board)[y_coor][x_coor] != draw){
	     (*board)[y_coor][x_coor] = '+';
	      return true;
        }
	return false;
}

void drawHorizontal(Coor intPoint, Coor finPoint, char ***board, int numCols, int numRows){
    //This function draws a horizontal line based on the user input

    int i;

    if (intPoint.x_coor == finPoint.x_coor){
        //checks for overlap
        if (checkOverlap(intPoint.y_coor, intPoint.x_coor, '-', board)){

        }

        else {
            (*board)[numRows - intPoint.y_coor - 1][intPoint.x_coor] = '-';
        }
    }


    else if (intPoint.x_coor < finPoint.x_coor){
        for (i = intPoint.x_coor; i <= finPoint.x_coor; i++){
            if(checkOverlap(numRows - intPoint.y_coor - 1, i, '-', board)){
                continue;
                    }
            (*board)[numRows - intPoint.y_coor - 1][i] = '-';
        }
    }

    else if (intPoint.x_coor > finPoint.x_coor){
        for (i = intPoint.x_coor; i >= finPoint.x_coor; i--){
            if(checkOverlap(numRows - intPoint.y_coor - 1, i, '-', board)){
                continue;
                    }
            (*board)[numRows - intPoint.y_coor - 1][i] = '-';
        }
    }

}

void drawVertical(Coor intPoint, Coor finPoint, char ***board, int numRows){
    //this function draws a vertical line based on the user input

     int i;

     if (intPoint.y_coor == finPoint.y_coor){
	if (checkOverlap(intPoint.y_coor, intPoint.x_coor, '|', board)){

	}
        else {
	(*board)[intPoint.y_coor][intPoint.x_coor] = '|';
	}
     }

     else if (intPoint.y_coor < finPoint.y_coor){
	 for (i = numRows - intPoint.y_coor - 1; i >= numRows - finPoint.y_coor - 1; i--){
		if (checkOverlap(i, intPoint.x_coor, '|', board)){
			continue;
		}
		(*board)[i][intPoint.x_coor] = '|';
	 }

      }

      else if (intPoint.y_coor > finPoint.y_coor){
          for (i = numRows - 1 - intPoint.y_coor; i <= numRows - finPoint.y_coor - 1; i++){
		if (checkOverlap(i, intPoint.x_coor, '|', board)){
			continue;
		}
	        (*board)[i][intPoint.x_coor] = '|';
	  }
      }

}

void drawRightDiag(Coor intPoint, Coor finPoint, char ***board, int numRows, int numCols){
    //This function draws a right diagonal based on the user input

    int i = 0,j = 0;


    if (abs(intPoint.x_coor - finPoint.x_coor) != abs(intPoint.y_coor - finPoint.y_coor)){
        printf("Cannot draw the line as it is not straight.\n");
        return;
    }


    if (intPoint.x_coor < finPoint.x_coor){
        j = intPoint.x_coor;
        for (i = numRows - intPoint.y_coor - 1; i >= numRows - finPoint.y_coor - 1; i--){
            if (checkOverlap(i, j, '/', board)){
		j++;
                continue;
            }
	    (*board)[i][j] = '/';
	    j++;
        }
    }

    else if (intPoint.x_coor > finPoint.x_coor){
        i = numRows - 1 - intPoint.y_coor;
        for (j = intPoint.x_coor; j >= finPoint.x_coor; j--){
            if (checkOverlap(i, j, '/', board)){
		i++;
                continue;
            }
	    (*board)[i][j] = '/';
	    i++;
        }
    }

    return;

}


void drawLeftDiag(Coor intPoint, Coor finPoint, char ***board, int numRows, int numCols){
    //This function draws a left diagonal based on the user input

    int i = 0, j = 0;

    if (abs(intPoint.x_coor - finPoint.x_coor) != abs(intPoint.y_coor - finPoint.y_coor)){
        printf("Cannot draw the line as it is not straight.\n");
        return;
    }

    if (intPoint.x_coor < finPoint.x_coor){
        i = numRows - 1 - intPoint.y_coor;
        for (j = intPoint.x_coor; j <= finPoint.x_coor; j++){
            if (checkOverlap(i, j, '\\', board)){
		i++;
                continue;
            }
            (*board)[i][j] = '\\';
            i++;
        }
    }

    else if (intPoint.x_coor > finPoint.x_coor){
        i = numRows - 1 - intPoint.y_coor;
        for (j = intPoint.x_coor; j >= finPoint.x_coor; j--){
            if (checkOverlap(i, j, '\\', board)){
		i--;
                continue;
            }
            (*board)[i][j] = '\\';
            i--;
        }
    }

	return;

}
