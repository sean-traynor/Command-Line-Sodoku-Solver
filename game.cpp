#include <iostream>
#include <stdlib.h>
#include <fstream>


const std::string FILES[] = {"easy1.txt", "easy2.txt", "easy3.txt",
                            "medium1.txt", "medium2.txt", "medium3.txt",
                            "hard1.txt", "hard2.txt", "hard3.txt"};


void printBoard(int game_board[9][9]) {
    std::cout << "\n\n\n";
    std::cout << "      Current Board\n";
    std::cout << "- - - - - - - - - - - - -\n";

    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) std::cout << "- - - - - - - - - - - - -\n";
        
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 || j == 0) std::cout << "| ";

            if (game_board[i][j] != 0) std::cout << game_board[i][j];
            else std::cout << " ";
            std::cout << " ";
        }
        std::cout << "| \n";
    }
    std::cout << "- - - - - - - - - - - - -\n";
    std::cout << "\n\n\n";
}

void readInBoard(std::string filename, int game_board[9][9]) {
    
    std::ifstream infile;
    infile.open("game_files/" + filename);
    
    if (!infile.is_open()) {
        std::cerr << "Error Opening File. Please Try Again.\n";
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            infile >> game_board[i][j];
        }
    }
    
    infile.close();

}

std::string selectFile() {
    std::cout << "Please select a difficulty.\n";
    std::cout << "1. Easy\n";
    std::cout << "2. Medium\n";
    std::cout << "3. Hard\n\n";

    int difficulty;
    std::cin >> difficulty;
    
    std::cout << "\n";
    std::cout << "Which level would you like to play (1, 2, or 3)? ";
    
    int level;
    std::cin >> level;

    int file_index = (difficulty - 1) * 3 + level - 1;

    std::string filename = FILES[file_index];

    return filename;
}

void printMenu() {

    std::cout << "\n\n\n";

    std::cout << "Welcome to the Command-Line Sodoku Game!!\n";
    std::cout << "This game was developed by Sean Traynor (Tufts University '23).\n\n";

    std::cout << "This game can be played exclusively on the Command-Line.\n\n";

}

void playGame() {

    printMenu();

    std::string filename = selectFile();

    int game_board[9][9];
    
    readInBoard(filename, game_board);

    printBoard(game_board);

}

int main() {

    playGame();

    return 0;
}