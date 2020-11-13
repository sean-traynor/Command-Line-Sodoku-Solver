#include <iostream>
#include <stdlib.h>
#include <fstream>

#ifndef SODOKUGAME_H
#define SODOKUGAME_H

const static std::string FILES[] = {"easy1.txt", "easy2.txt", "easy3.txt",
                            "medium1.txt", "medium2.txt", "medium3.txt",
                            "hard1.txt", "hard2.txt", "hard3.txt"};

class SodokuGame {
public:    
    SodokuGame();
    void playGame();

private:
    
    // Setup member functions
    void printMenu();
    void readInBoard();
    void printBoard(int board[9][9]);
    int getUserMove();
    std::string selectFile();
    void copyBoard(int to_copy[9][9], int new_board[9][9]);

    // Possible moves member functions
    void addNumber();
    void removeNumber();
    void giveHint();
    void resetGame();
    bool solveGame();

    // Helper functions
    bool boardSolved(int board[9][9]);
    bool validPosition(int num, int row, int col);
    bool findEmpty(int &row, int &col, int board[9][9]);
    int getVerticalIndex(char letter);
    int getHorizontalIndex(char number);
    void printExitMessage(bool game_won);


    // Member variables
    int game_board[9][9];
    int solved_board[9][9];
    int starter_board[9][9];
    bool game_over;
    bool solution_possible;
    int num_moves;
    int num_hints;
    int steps_to_solve;
};

#endif