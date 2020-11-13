#include "SodokuGame.h"

SodokuGame::SodokuGame() {
    this->game_over = false;
    this->num_moves = 0;
    this->num_hints = 3;
    this->steps_to_solve = 0;
    this->printMenu();
    this->readInBoard();
    this->copyBoard(this->game_board, this->starter_board);
    this->copyBoard(this->game_board, this->solved_board);
    this->solution_possible = this->solveGame();
}

void SodokuGame::playGame() {

    while (!this->game_over) {
        this->printBoard(this->game_board);
        int query = this->getUserMove();
        
        this->num_moves++;

        if (query == 1) this->addNumber();
        else if (query == 2) this->removeNumber();
        else if (query == 3) this->giveHint();
        else if (query == 4) this->resetGame();
        else if (query == 5) {
            this->printBoard(this->solved_board);
            this->printExitMessage(false);
            return;
        } else if (query == 6) {
            this->printExitMessage(false);
            return;
        }

        int row, col;
        this->game_over = this->boardSolved(this->game_board);
        
        if (this->game_over) {
            this->printBoard(this->game_board);
            this->printExitMessage(true);
        }
    }
}

int SodokuGame::getUserMove() {
    std::cout << "What would you like to do?\n";
    std::cout << "1. Add Number\n";
    std::cout << "2. Remove Number\n";
    std::cout << "3. Get Hint\n";
    std::cout << "4. Start Over\n";
    std::cout << "5. Show Solution\n";
    std::cout << "6. Exit\n\n\n";

    int move;
    std::cin >> move;
    std::cout << "\n";

    return move;
}

void SodokuGame::printBoard(int board[9][9]) {
    std::cout << "\n\n\n";
    std::cout << "        Current Board\n";
    std::cout << "  -------------------------\n";
    std::cout << "    1 2 3   4 5 6   7 8 9\n";
    std::cout << "  - - - - - - - - - - - - -\n";

    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) std::cout << "  - - - - - - - - - - - - -\n";
        char letter = i + 'A';
        std::cout << letter << " ";

        for (int j = 0; j < 9; j++) {
            
            if (j % 3 == 0 || j == 0) std::cout << "| ";

            if (board[i][j] != 0) std::cout << board[i][j];
            else std::cout << " ";
            std::cout << " ";
        }
        std::cout << "| \n";
    }
    std::cout << "  - - - - - - - - - - - - -\n\n";
    std::cout << "Hints Remaining: " << this->num_hints << "\n";
    std::cout << "Total Moves: " << this->num_moves << "\n";
    std::cout << "\n\n\n";
}


std::string SodokuGame::selectFile() {
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

void SodokuGame::printMenu() {

    std::cout << "\n\n\n";

    std::cout << "Welcome to the Command-Line Sodoku Game!!\n";
    std::cout << "This game was developed by Sean Traynor (Tufts University '23).\n\n";

    std::cout << "This game can be played exclusively on the Command-Line.\n\n";

}

void SodokuGame::readInBoard() {
    std::string filename = this->selectFile();
    std::ifstream infile;
    infile.open("game_files/" + filename);
    
    if (!infile.is_open()) {
        std::cerr << "Error Opening File. Please Try Again.\n";
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            infile >> this->game_board[i][j];
        }
    }
    
    infile.close();
}

int SodokuGame::getHorizontalIndex(char number) {
    return number - '1';
}

int SodokuGame::getVerticalIndex(char letter) {
    return letter - 'A';
}

void SodokuGame::addNumber() {
    std::cout << "What number would you like to add (1-9)? ";
    
    int number;
    std::cin >> number;

    std::string user_index;
    std::cout << "Where would you like the " << number << " to go ('A1', 'B2', etc.)? ";
    std::cin >> user_index;
    
    int vert_index = getVerticalIndex(user_index[0]);
    int horiz_index = getHorizontalIndex(user_index[1]);
    
    this->game_board[vert_index][horiz_index] = number;
}

void SodokuGame::removeNumber() {
    std::cout << "What index would you like to remove ('A1', 'B2', etc.)? ";

    std::string user_index;
    std::cin >> user_index;

    int vert_index = getVerticalIndex(user_index[0]);
    int horiz_index = getHorizontalIndex(user_index[1]);
    
    this->game_board[vert_index][horiz_index] = 0;
}

void SodokuGame::giveHint() {
    this->num_hints--;
    int row, col;
    bool empty_found = this->findEmpty(row, col, this->game_board);
    this->game_board[row][col] = this->solved_board[row][col];
}

void SodokuGame::resetGame() {
    this->copyBoard(this->starter_board, this->game_board);
    this->num_moves = 0;
}

bool SodokuGame::solveGame() {
    int row, col;
    bool empty_found = this->findEmpty(row, col, this->solved_board);
    if (!empty_found) return true;

    for (int i = 1; i <= 9; i++) {
        if (validPosition(i, row, col)) {
            this->solved_board[row][col] = i;

            if (this->solveGame()) return true;

            this->solved_board[row][col] = 0;
        }
    }
    return false;
}

bool SodokuGame::validPosition(int num, int row, int col) {
    
    // Check the row
    for (int i = 0; i < 9; i++) {
        if (this->solved_board[row][i] == num && col != i) return false;
    }

    // Check the column
    for (int i = 0; i < 9; i++) {
        if (this->solved_board[i][col] == num && row != i) return false;
    }

    // Check the box
    int x = col / 3;
    int y = row / 3;

    for (int i = y * 3; i < (y * 3) + 3; i++) {
        for (int j = x * 3; j < (x * 3) + 3; j++) {
            if (this->solved_board[i][j] == num && (i != row && j != col)) return false;
        }
    }

    return true;
}

bool SodokuGame::findEmpty(int &row, int &col, int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                row = i;
                col = j;
                return true;
            }
        }
    }
    return false;
}

bool SodokuGame::boardSolved(int board[9][9]) {
    int row, col;
    return !(this->findEmpty(row, col, board));
}

void SodokuGame::copyBoard(int to_copy[9][9], int new_board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            new_board[i][j] = to_copy[i][j];
        }
    }
}

void SodokuGame::printExitMessage(bool game_won) {
    if (game_won) {
        std::cout << "You have won this game!! ";
    } else {
        std::cout << "Unfortunately, you have not completed this game. ";
    }
    std::cout << "Thanks for playing!!\n\n\n";
}