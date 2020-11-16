#include "SodokuGame.h"


/*
 * SodokuGame Constructor
 * Arguments: None
 * Purpose: Creates an instance of the SodokuGame Class
 */
SodokuGame::SodokuGame() {
    this->game_over = false;
    this->num_moves = 0;
    this->num_hints = 3;
    this->steps_to_solve = 0;
}

/*
 * playGame
 * Arguments: None
 * Purpose: Sets up the game and puts the user into the game loop
 * Return: None (void)
 */
void SodokuGame::playGame() {
    this->printMenu();
    this->readInBoard();
    
    this->copyBoard(this->game_board, this->starter_board);
    this->copyBoard(this->game_board, this->solved_board);
    
    this->solution_possible = this->solveGame();
    if (!this->solution_possible) {
        std::cerr << "\nThis puzzle is invalid, please try again with another puzzle.\n\n";
        exit(EXIT_FAILURE);
    }

    this->game_won = this->gameLoop();

    if (game_won) {
        this->printBoard(this->game_board);
        this->printExitMessage(true);
    } else this->printExitMessage(false);
}

/*
 * gameLoop
 * Arguments: None
 * Purpose: Loops the user through the game and allows the user to query their moves
 * Return: A boolean that holds whether or not the user has won the game
 */
bool SodokuGame::gameLoop() {
    while (!this->game_over) {
        this->printBoard(this->game_board);
        char query = this->getUserMove();

        if (query == '1') this->addNumber();
        else if (query == '2') this->removeNumber();
        else if (query == '3') this->giveHint();
        else if (query == '4') this->resetGame();
        else if (query == '5') {
            this->printBoard(this->solved_board);
            std::cout << "The algorithm solved the board in " << this->steps_to_solve << " steps.\n\n";
            return false;
        } else if (query == 'q') return false;
        else {
            std::cout << "Invalid query, please try again.\n";
            continue;
        }
        this->num_moves++;

        int row, col;
        this->game_over = this->boardSolved(this->game_board);
    }
    return true;
}

/*
 * getUserMove
 * Arguments: None
 * Purpose: Queries the user for their move
 * Return: A char that holds the single-letter query that the user selected
 */
char SodokuGame::getUserMove() {
    std::cout << "What would you like to do?\n";
    std::cout << "1. Add Number\n";
    std::cout << "2. Remove Number\n";
    std::cout << "3. Get Hint\n";
    std::cout << "4. Start Over\n";
    std::cout << "5. Show Solution\n";
    std::cout << "Quit Game ('q')\n\n\n";

    char move;
    std::cin >> move;
    std::cout << "\n";

    return move;
}

/*
 * printBoard
 * Arguments: The board to print
 * Purpose: Prints the current state of the board
 * Return: None (void)
 */
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

/*
 * selectFile
 * Arguments: None
 * Purpose: Queries the user for a file to play from
 * Return: A string with the file name to read in
 */
std::string SodokuGame::selectFile() {
    std::cout << "Please select a difficulty.\n";
    std::cout << "1. Easy\n";
    std::cout << "2. Medium\n";
    std::cout << "3. Hard\n\n";
    std::cout << "... or you can attempt the World's Hardest Sodoku Puzzle (4)\n\n\n\n";

    int difficulty;
    std::cin >> difficulty;

    if (difficulty == 4) return FILES[9];

    std::cout << "\n";
    std::cout << "Which level would you like to play (1, 2, or 3)? ";
    
    int level;
    std::cin >> level;

    if (difficulty > 3 || difficulty < 1 || level > 3 || level < 1) {
        std::cout << "\nThe file you specified is out of range. Please try again.\n\n";
        return this->selectFile();
    }

    int file_index = (difficulty - 1) * 3 + level - 1;

    std::string filename = FILES[file_index];

    return filename;
}

/*
 * printMenu
 * Arguments: None
 * Purpose: Prints the menu at the start of the game
 * Return: None (void)
 */
void SodokuGame::printMenu() {

    std::cout << "\n\n";

    std::cout << "Welcome to the Command-Line Sodoku Game!!\n";
    std::cout << "This game was developed by Sean Traynor (Tufts University '23).\n\n";

    std::cout << "This game can be played exclusively on the Command-Line.\n\n";

}

/*
 * readInBoard
 * Arguments: None
 * Purpose: Reads in the board into the 2-D game board array 
 * Return: None (void)
 */
void SodokuGame::readInBoard() {
    std::string filename = this->selectFile();
    std::ifstream infile;
    infile.open("game_files/" + filename);
    
    if (!infile.is_open()) {
        std::cerr << "Error Opening File. Please Try Again.\n\n";
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            infile >> this->game_board[i][j];
        }
    }
    
    infile.close();
}

/*
 * getHorizontalIndex
 * Arguments: The number of the user-selected column
 * Purpose: Converts the char holding the number of the column (1-9) to an integer (0-8)
 * Return: An integer that will be used to index the game board's column
 */
int SodokuGame::getHorizontalIndex(char number) {
    return number - '1';
}

/*
 * getVerticalIndex
 * Arguments:   The letter of the user-selected row
 * Purpose:     Converts the char holding the letter of the row (A-I) to
 *              an integer (0-8)
 * Return:      An integer that will be used to index the game board's row
 */
int SodokuGame::getVerticalIndex(char letter) {
    return letter - 'A';
}

/*
 * addNumber
 * Arguments:   None
 * Purpose:     Prompts the user to add a number to a certain place in the
 *              board, checks for errors, and then adds the number to the
 *              board
 * Return:      None (void)
 */
void SodokuGame::addNumber() {
    std::cout << "What number would you like to add (1-9)? ";
    
    int number;
    std::cin >> number;

    std::string user_index;
    std::cout << "Where would you like the " << number << " to go ('A1', 'B2', etc.)? ";
    std::cin >> user_index;
    
    int vert_index = getVerticalIndex(user_index[0]);
    int horiz_index = getHorizontalIndex(user_index[1]);

    if (!validAddition(number, vert_index, horiz_index)) {
        addNumber();
        return;
    }
    
    this->game_board[vert_index][horiz_index] = number;
}

/*
 * removeNumber
 * Arguments:   None
 * Purpose:     Prompts the user to remove from a certain place in the
 *              board, checks for errors, and then removes the number
 *              from the specified index on the board
 * Return:      None (void)
 */
void SodokuGame::removeNumber() {
    std::cout << "What index would you like to remove ('A1', 'B2', etc.)? ";

    std::string user_index;
    std::cin >> user_index;

    int vert_index = getVerticalIndex(user_index[0]);
    int horiz_index = getHorizontalIndex(user_index[1]);

    if (!validRemoval(vert_index, horiz_index)) {
        removeNumber();
        return;
    }
    
    this->game_board[vert_index][horiz_index] = 0;
}

/*
 * giveHint
 * Arguments:   None
 * Purpose:     Adds a number (in the first empty index on the board)
 *              to help the user progress
 * Return:      None (void)
 */
void SodokuGame::giveHint() {
    if (this->num_hints <= 0) {
        std::cout << "\nERROR: No more hints. Please try again.\n\n";
        return;
    }

    this->num_hints--;
    int row, col;
    bool empty_found = this->findEmpty(row, col, this->game_board);
    this->game_board[row][col] = this->solved_board[row][col];
}

/*
 * resetGame
 * Arguments:   None
 * Purpose:     Resets the game back to the beginning
 * Return:      None (void)
 */
void SodokuGame::resetGame() {
    this->copyBoard(this->starter_board, this->game_board);
    this->num_moves = 0;
    this->num_hints = 3;
}

/*
 * solveGame
 * Arguments:   None
 * Purpose:     Recursively solves the game using a backtracking algorithm
 *              (O(n^2) time complexity)
 * Return:      A boolean whether or not the game board has been solved
 *              (will return false if there is no solution)
 */
bool SodokuGame::solveGame() {
    int row, col;
    bool empty_found = this->findEmpty(row, col, this->solved_board);
    if (!empty_found) return true;

    for (int i = 1; i <= 9; i++) {
        this->steps_to_solve++;
        if (validPosition(i, row, col)) {
            this->solved_board[row][col] = i;

            if (this->solveGame()) return true;

            this->solved_board[row][col] = 0;
        }
    }
    return false;
}

/*
 * validPosition
 * Arguments:   The row, column, and number to check if it is valid
 * Purpose:     Loops through the current number's row, column, and box
 *              to check if the number is a valid entry
 * Return:      A boolean whether or not the position is valid
 */
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

/*
 * findEmpty
 * Arguments:   The address of a row & column and the board to check
 * Purpose:     Sets the row and column variables to that of the first empty
 *              index by passing them by reference
 * Return:      A boolean whether or not there is an empty index in the board
 */
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

/*
 * boardSolved
 * Arguments:   A board to check if the game is successfully solved
 * Purpose:     Checks if a board has been solved
 * Return:      A boolean whether or not the game board has been solved
 */
bool SodokuGame::boardSolved(int board[9][9]) {
    int row, col;
    return !(this->findEmpty(row, col, board));
}

/*
 * copyBoard
 * Arguments:   Two instances of a board - one to copy from and one to copy to
 * Purpose:     Copies the content of one board to another board
 * Return:      None (void)
 */
void SodokuGame::copyBoard(int to_copy[9][9], int new_board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            new_board[i][j] = to_copy[i][j];
        }
    }
}

/*
 * printExitMessage
 * Arguments:   Whether or not the game was won by the user
 * Purpose:     Prints either the success or failure exit message
 * Return:      None (void)
 */
void SodokuGame::printExitMessage(bool game_won) {
    if (game_won) {
        std::cout << "You have won this game!! ";
    } else {
        std::cout << "Unfortunately, you have not completed this game. ";
    }
    std::cout << "Thanks for playing!!\n\n\n";
}

/*
 * validAddition
 * Arguments:   The row and column to check
 * Purpose:     Checks the number and position the user has selected
 *              to add a number to and validates whether or not the
 *              move is possible
 * Return:      A boolean whether or not the addition is valid
 */
bool SodokuGame::validAddition(int num, int row, int col) {
    if (row > 9 || row < 1 || col > 9 || col < 1) {
        std::cout << "\nERROR: The position you have selected is out of range. Please try again.\n\n";
        return false;
    }

    if (num > 9 || num < 1) {
        std::cout << "\nERROR: The number you have selected is invalid. Please try again.\n\n";
        return false;
    }

    if (!validPosition(num, row, col)) {
        std::cout << "\nERROR: The position you have selected is invalid. Please try again.\n\n";
        return false;
    }

    if (this->game_board[row][col] != 0) {
        std::cout << "\nERROR: The position you have selected already has a value. Please try again\n\n";
        return false;
    }
    
    return true;
}

/*
 * validRemoval
 * Arguments:   The row and column to check
 * Purpose:     Checks the position the user has selected to remove from and
 *              validates whether or not the move is possible
 * Return:      A boolean whether or not the removal is valid
 */
bool SodokuGame::validRemoval(int row, int col) {
    if (row > 9 || row < 1 || col > 9 || col < 1) {
        std::cout << "\nERROR: The position you have selected is out of range. Please try again.\n\n";
        return false;
    }

    if (this->starter_board[row][col] != 0) {
        std::cout << "\nERROR: You are trying to remove a number in the starter board. Please try again.\n\n";
        return false;
    }

    if (this->game_board[row][col] != 0) {
        std::cout << "\nERROR: The position you have selected has no value to remove. Please try again\n\n";
        return false;
    }

    return true;
}