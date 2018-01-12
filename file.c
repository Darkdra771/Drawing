#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "file.h"
#include "commandPrompt.h"

void saveFile(char **board, int numRows, int numCols){
    //this function saves the board into a file named after the user input

    FILE* fp;
    int i = 0, j = 0;
    char nameFile[100];


    scanf("%s", nameFile);


    if (!takes()){
	printf("Improper save command or file could not be created.\n");
	return;
    }


    fp = fopen(nameFile, "w");

    //create and write into the file
    for (i = 0; i < numRows; i++){
        for (j = 0; j < numCols; j++){
            fwrite(&board[i][j], 1, sizeof(char), fp);
        }
        fwrite("\n", sizeof(char), 1, fp);
    }


    fclose(fp);

    return;
}



char** openFile(char **board, int *numRows, int *numCols){
    //This function opens the file based on the user input and then reads the file
    //before saving it in board



    FILE* fp;
    char nameFile[100];
    char checkChar = ' ';

    scanf("%s", nameFile);

    if (!takes()){
	printf("Improper save command or file could not be created.\n");
	return board;
    }

    fp = fopen(nameFile, "r");

    if (fp == NULL){
	printf("Failed to open file: %s\n", nameFile);
	return board;
    }

    int i = 0;
    int j = 0;
    int numLines = 0;


    //find the number of lines in the file
    while(!feof(fp)){
        fscanf(fp, "%c", &checkChar);
        if(checkChar == '\n'){
           numLines++;
        }
    }

	 rewind(fp);
	 numLines--;


	char** newboard = (char**)malloc(numLines * sizeof(char*));

	for ( i = 0; i < numLines; i++){
		newboard[i] = (char*)malloc(1 * sizeof(char));
	}

	i = 0;


    //reads the file and copy the content into an array
	while (!feof(fp) && (i < numLines)){
        	fscanf(fp, "%c", &checkChar);
		if (checkChar != '\n'){
       			newboard[i] = realloc(newboard[i], (j + 1) * sizeof(char));
        		newboard[i][j] = checkChar;
		}
		if (checkChar == '\n'){
			j++;
			newboard[i] = realloc(newboard[i], (j + 1) * sizeof(char));
			newboard[i][j] = '\0';
            		i++;
           		j = 0;
	    		continue;
        	}
		else {
        		j++;
		}
	}

	*numRows = numLines;
	*numCols = strlen(newboard[0]);



    return newboard;

}

