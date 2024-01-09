#include <iostream>
using namespace std;

const int N = 9;

bool isSafe(int board[N][N], int row, int col, int num) {
    // Check if 'num' is not present in the current row and column
    for (int i = 0; i < N; ++i) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    // Check if 'num' is not present in the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

bool findEmptyPosition(int board[N][N], int &row, int &col) {
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (board[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool solveSudoku(int board[N][N]) {
    int row, col;

    if (!findEmptyPosition(board, row, col)) {
        return true; // Puzzle solved
    }

    for (int num = 1; num <= 9; ++num) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;

            if (solveSudoku(board)) {
                return true; // Recur to solve the remaining puzzle
            }

            board[row][col] = 0; // Backtrack if no solution found
        }
    }

    return false; // No solution found
}

void printSudoku(int board[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int sudoku[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(sudoku)) {
        cout << "Sudoku Solved:" << endl;
        printSudoku(sudoku);
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}
