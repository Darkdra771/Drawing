#ifndef COMMANDPROMPT_H_INCLUDED
    #define COMMANDPROMPT_H_INCLUDED

    bool takes();
    void print_help();
    bool checkCommand(int x_coor, int y_coor, int numRows, int numCols);
    void draw(char ***board, int numRows, int numCols);
    void erase(char ***board, int numRows, int numCols);
    char** resize(char ***board, int *numRows, int *numCols);



#endif // COMMANDPROMPT_H_INCLUDED
