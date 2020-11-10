#include <iostream>
#include <stdlib.h>
#include <fstream>


const std::string FILES[] = {"easy1.txt", "easy2.txt", "easy3.txt",
                            "medium1.txt", "medium2.txt", "medium3.txt",
                            "hard1.txt", "hard2.txt", "hard3.txt"};



int getVerticalIndex(char letter) {
    return letter - 'A';
}

int getHorizontalIndex(char number) {
    return number - '1';
}

void addNumber(int game_board[9][9]) {
    std::cout << "What number would you like to add (1-9)? ";
    
    int number;
    std::cin >> number;

    std::string user_index;
    std::cout << "Where would you like the " << number << " to go ('A1', 'B2', etc.)? ";
    std::cin >> user_index;
    
    int vert_index = getVerticalIndex(user_index[0]);
    int horiz_index = getHorizontalIndex(user_index[1]);
    
    game_board[vert_index][horiz_index] = number;
}

int getUserMove() {
    std::cout << "What would you like to do?\n";
    std::cout << "1. Add Number\n";
    std::cout << "2. Remove Number\n";
    std::cout << "3. Get Hint\n";
    std::cout << "4. Show Solution\n\n\n";

    int move;
    std::cin >> move;

    return move;
}

void printBoard(int game_board[9][9]) {
    std::cout << "\n\n\n";
    std::cout << "        Current Board\n";
    std::cout << "  -------------------------\n";
    std::cout << "    1 2 3   4 5 6   7 8 \n";
    std::cout << "  - - - - - - - - - - - - -\n";

    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) std::cout << "  - - - - - - - - - - - - -\n";
        char letter = i + 'A';
        std::cout << letter << " ";

        for (int j = 0; j < 9; j++) {
            
            if (j % 3 == 0 || j == 0) std::cout << "| ";

            if (game_board[i][j] != 0) std::cout << game_board[i][j];
            else std::cout << " ";
            std::cout << " ";
        }
        std::cout << "| \n";
    }
    std::cout << "  - - - - - - - - - - - - -\n  ";
    std::cout << "\n\n\n";
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

void readInBoard(int game_board[9][9]) {
    std::string filename = selectFile();
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


void printMenu() {

    std::cout << "\n\n\n";

    std::cout << "Welcome to the Command-Line Sodoku Game!!\n";
    std::cout << "This game was developed by Sean Traynor (Tufts University '23).\n\n";

    std::cout << "This game can be played exclusively on the Command-Line.\n\n";

}

void playGame() {

    printMenu();

    int game_board[9][9];
    readInBoard(game_board);

    int solved_board[9][9];
    readInBoard(solved_board);
    // solveGame(solved_board); 

    bool game_over = false;

    while (!game_over) {
        printBoard(game_board);
        int query = getUserMove();
        
        if (query == 1) addNumber(game_board);
        else if (query == 4) {
            printBoard(solved_board);
            game_over = true;
        }
        

        game_over = true;
    }
    

}

int main() {

    playGame();

    return 0;
}