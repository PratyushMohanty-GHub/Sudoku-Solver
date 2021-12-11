#include <bits/stdc++.h>
using namespace std;

#define RED printf("\033[0;31m");
#define CYAN printf("\033[0;36m");
#define BLUE printf("\033[0;34m");
#define GREEN printf("\033[0;32m");
#define WHITE printf("\033[0;37m");
#define YELLOW printf("\033[0;33m");
#define MAGENTA printf("\033[0;35m");
#define RESET printf("\033[0m");

#define N 9
int grid[N][N];

bool solveSudoku(int row, int col);
bool isValidPlace(int num, int row, int col);
bool isPresentInCol(int num, int row, int col);
bool isPresentInRow(int num, int row, int col);
bool isPresentInBox(int num, int row, int col);
bool findUnassignedLocation(int &row, int &col);

bool isPresentInCol(int num, int row, int col)
{
    for (int i = 0; i < N; i++)
        if (grid[i][col] == num)
            return true;
    return false;
}
bool isPresentInRow(int num, int row, int col)
{
    for (int i = 0; i < N; i++)
        if (grid[row][i] == num)
            return true;
    return false;
}
bool isPresentInBox(int num, int row, int col)
{
    int r = row - (row % 3);
    int c = col - (col % 3);
    for (int i = r; i < r + 3; i++)
        for (int j = c; j < c + 3; j++)
            if (grid[i][j] == num)
                return true;
    return false;
}
bool isValidPlace(int num, int row, int col)
{
    bool isColSafe = !isPresentInCol(num, row, col);
    bool isRowSafe = !isPresentInRow(num, row, col);
    bool isBoxSafe = !isPresentInBox(num, row, col);

    return isColSafe && isRowSafe && isBoxSafe;
}
bool findUnassignedLocation(int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return true;
    return false;
}
bool solveSudoku()
{
    int row = 0, col = 0;
    if (!findUnassignedLocation(row, col))
        return true;
    for (int num = 1; num <= 9; num++)
    {
        if (isValidPlace(num, row, col))
        {
            grid[row][col] = num;
            if (solveSudoku() == true)
                return true;
            grid[row][col] = 0;
        }
    }
    return false;
}
int main(int argc, char const *argv[])
{
    RED
    cout << "Enter the sudoku grid: " << endl;
    RESET

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> grid[i][j];
        }
    }
    if (solveSudoku() == true)
    {
        GREEN
        cout << endl
             << "______Solved Sudoku_____" << endl
             << endl;
        RESET

        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < N; col++)
            {
                if (col == 3 || col == 6)
                {
                    YELLOW
                            cout
                        << " | ";
                    RESET
                }
                CYAN
                        cout
                    << grid[row][col] << " ";
                RESET
            }
            if (row == 2 || row == 5)
            {
                cout << endl;
                for (int i = 0; i < N - 1; i++)
                {
                    YELLOW
                            cout
                        << "---";
                    RESET
                }
            }
            cout << endl;
        }
        MAGENTA
        cout << endl
             << "______Thank You!!!_____" << endl
             << endl;
        RESET
    }
    else
    {
        RED
                cout
            << "Unable to solve sudoku" << endl;
        RESET
    }
    cout << endl;
    return 0;
}
