#ifndef DRAWCOMMAND_H_INCLUDED
    #define DRAWCOMMAND_H_INCLUDED

    typedef struct Coor_struct{
    	int x_coor;
    	int y_coor;
    }Coor;
    bool checkOverlap(int y_coor, int x_coor,char draw, char ***board);
    void drawHorizontal(Coor intPoint, Coor finPoint, char ***board, int numCols, int numRows);
    void drawVertical(Coor intPoint, Coor finPoint, char ***board, int numRows);
    void drawRightDiag(Coor intPoint,Coor finPoint, char ***board, int numRows, int numCols);
    void drawLeftDiag(Coor intPoint,Coor finPoint, char ***board, int numRows, int numCols);




#endif // DRAWCOMMAND_H_INCLUDED
