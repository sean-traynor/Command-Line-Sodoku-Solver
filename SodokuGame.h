/*
 * Written By: Sean Traynor (https://github.com/sean-traynor)
 * Last Updated: 11/16/20
 *
 * Description: This class creates an instance of a Sodoku Game that can be played completely on the Command-Line.
 *              The user can choose to play the game or see the solution of the game (which the program solves using
 *              a backtracking algorithm). This algorithm solves the Sodoku Puzzle in O(n^2) time.
 */

#include <iostream>
#include <stdlib.h>
#include <fstream>

#ifndef SODOKUGAME_H
#define SODOKUGAME_H

const static std::string FILES[] = {"easy1.txt", "easy2.txt", "easy3.txt",
                            "medium1.txt", "medium2.txt", "medium3.txt",
                            "hard1.txt", "hard2.txt", "hard3.txt", "impossible.txt"};

class SodokuGame {
public:    
    
    SodokuGame();
    void playGame();

private:
    
    // Setup member functions
    bool gameLoop();
    void printMenu();
    void readInBoard();
    void printBoard(int board[9][9]);
    char getUserMove();
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
    bool validAddition(int num, int row, int col);
    bool validRemoval(int row, int col);

    // Member variables
    int game_board[9][9];
    int solved_board[9][9];
    int starter_board[9][9];
    bool game_over;
    bool game_won;
    bool solution_possible;
    int num_moves;
    int num_hints;
    int steps_to_solve;

};

#endif