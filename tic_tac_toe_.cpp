
#include <array>
#include <string>

using Board = std::array<char, 9>;

void printBoard(const Board &board) {
    std::cout << "\n";
    for (int i = 0; i < 9; i += 3) {
        std::cout << " " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << " \n";
        if (i < 6) {
            std::cout << "---+---+---\n";
        }
    }
    std::cout << "\n";
}

bool isWinner(const Board &board, char player) {
    const int wins[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };
    for (auto &line : wins) {
        if (board[line[0]] == player && board[line[1]] == player && board[line[2]] == player) {
            return true;
        }
    }
    return false;
}

bool isBoardFull(const Board &board) {
    for (char cell : board) {
        if (cell == ' ') {
            return false;
        }
    }
    return true;
}

int getMove(const Board &board, char player) {
    int move = -1;
    while (true) {
        std::cout << "Player " << player << ", enter a position (1-9): ";
        if (!(std::cin >> move)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 9." << std::endl;
            continue;
        }
        if (move < 1 || move > 9) {
            std::cout << "Choose a position from 1 to 9." << std::endl;
            continue;
        }
        if (board[move - 1] != ' ') {
            std::cout << "That cell is already taken. Choose another." << std::endl;
            continue;
        }
        break;
    }
    return move - 1;
}

void playGame() {
    Board board;
    board.fill(' ');
    char currentPlayer = 'X';
    bool gameOver = false;

    std::cout << "Welcome to Tic Tac Toe!" << std::endl;
    std::cout << "Positions are numbered 1 through 9 like this:" << std::endl;
    std::cout << " 1 | 2 | 3\n";
    std::cout << "---+---+---\n";
    std::cout << " 4 | 5 | 6\n";
    std::cout << "---+---+---\n";
    std::cout << " 7 | 8 | 9\n";

    while (!gameOver) {
        printBoard(board);
        int move = getMove(board, currentPlayer);
        board[move] = currentPlayer;

        if (isWinner(board, currentPlayer)) {
            printBoard(board);
            std::cout << "Player " << currentPlayer << " wins!" << std::endl;
            gameOver = true;
        } else if (isBoardFull(board)) {
            printBoard(board);
            std::cout << "It's a draw!" << std::endl;
            gameOver = true;
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

int main() {
    std::string choice;
    do {
        playGame();
        std::cout << "Play again? (y/n): ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (!choice.empty() && (choice[0] == 'y' || choice[0] == 'Y'));

    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}
