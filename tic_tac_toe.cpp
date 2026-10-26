// Tic Tac Toe - Console Mini Game in C++
// Demonstrates: loops, arrays, conditional logic, input validation, replay.

#include <iostream>
#include <limits>
using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE];

// Fill the board with the numbers 1-9 so players can pick a cell
void resetBoard() {
    char cell = '1';
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = cell++;
}

// Redraw the board after every move
void displayBoard() {
    cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        cout << "     ";
        for (int j = 0; j < SIZE; j++) {
            cout << " " << board[i][j] << " ";
            if (j < SIZE - 1) cout << "|";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "     ---+---+---\n";
    }
    cout << "\n";
}

// Place a mark if the cell number is valid and free
bool makeMove(int choice, char player) {
    if (choice < 1 || choice > 9) return false;
    int row = (choice - 1) / SIZE;
    int col = (choice - 1) % SIZE;
    if (board[row][col] == 'X' || board[row][col] == 'O') return false;
    board[row][col] = player;
    return true;
}

// Check rows, columns and both diagonals
bool checkWin(char p) {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == p && board[i][1] == p && board[i][2] == p) return true;
        if (board[0][i] == p && board[1][i] == p && board[2][i] == p) return true;
    }
    if (board[0][0] == p && board[1][1] == p && board[2][2] == p) return true;
    if (board[0][2] == p && board[1][1] == p && board[2][0] == p) return true;
    return false;
}

bool isDraw() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O') return false;
    return true;
}

// Read an integer safely (handles letters / bad input)
int readNumber() {
    int n;
    while (!(cin >> n)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a number (1-9): ";
    }
    return n;
}

void playGame(int &winsX, int &winsO, int &draws) {
    resetBoard();
    char player = 'X';
    bool gameOver = false;

    while (!gameOver) {
        displayBoard();
        cout << "Player " << player << ", choose a cell (1-9): ";
        int choice = readNumber();

        if (!makeMove(choice, player)) {
            cout << "Invalid or already taken cell. Try again.\n";
            continue;
        }

        if (checkWin(player)) {
            displayBoard();
            cout << "*** Player " << player << " wins! ***\n";
            if (player == 'X') winsX++; else winsO++;
            gameOver = true;
        } else if (isDraw()) {
            displayBoard();
            cout << "*** It's a draw! ***\n";
            draws++;
            gameOver = true;
        } else {
            player = (player == 'X') ? 'O' : 'X';
        }
    }
}

int main() {
    int winsX = 0, winsO = 0, draws = 0;
    char again;

    cout << "=====================================\n";
    cout << "        TIC TAC TOE  (2 Players)\n";
    cout << "=====================================\n";

    do {
        playGame(winsX, winsO, draws);
        cout << "\nScore -> X: " << winsX << " | O: " << winsO
             << " | Draws: " << draws << "\n";
        cout << "Play again? (y/n): ";
        cin >> again;
    } while (again == 'y' || again == 'Y');

    cout << "\nThanks for playing!\n";
    return 0;
}
