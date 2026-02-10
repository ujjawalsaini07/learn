#include <vector>
#include <iostream>

using namespace std;

class Solution
{
private:
    /**
     * @brief Checks if placing character 'c' at board[row][col] is valid.
     * * Validates against three Sudoku rules:
     * 1. The number must not exist in the current row.
     * 2. The number must not exist in the current column.
     * 3. The number must not exist in the specific 3x3 sub-grid.
     * * @param board The current state of the Sudoku board.
     * @param row The row index of the cell.
     * @param col The column index of the cell.
     * @param c The character ('1'-'9') to check.
     * @return true if placement is valid, false otherwise.
     */
    bool isValid(vector<vector<char>> &board, int &row, int &col, char &c)
    {
        for (int i = 0; i < 9; i++)
        {
            // Check Row
            if (board[row][i] == c)
                return false;
                
            // Check Column
            if (board[i][col] == c)
                return false;
                
            // Check 3x3 Sub-grid
            // The formula 3 * (row / 3) finds the starting row of the 3x3 block.
            // i / 3 moves the row offset by 0, 1, or 2.
            if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c)
                return false;
        }
        return true;
    }

    /**
     * @brief Recursive function to solve the Sudoku using Backtracking.
     * * @param board The Sudoku board reference.
     * @return true if the board is completely and correctly filled.
     * @return false if the current path leads to no solution.
     */
    bool solve(vector<vector<char>> &board)
    {
        // Iterate through the entire 9x9 grid
        for(int i = 0 ; i < 9 ; i++)
        {
            for(int j = 0 ; j < 9 ;j++)
            {
                // If we find an empty cell (represented by '.')
                if(board[i][j] == '.')
                {
                    // Try numbers '1' through '9'
                    for(char c = '1' ; c <= '9' ; c++)
                    {
                        if(isValid(board, i, j, c))
                        {
                            // Place the number
                            board[i][j] = c;
                            
                            // Recursively attempt to solve the rest of the board
                            if(solve(board) == true) 
                                return true;
                            else
                            {
                                // BACKTRACK: If the recursive call returned false,
                                // reset this cell to '.' and try the next number.
                                board[i][j] = '.';
                            }
                        }
                    }
                    // If no number from 1-9 fits in this empty cell, return false
                    // to trigger backtracking in the previous stack frame.
                    return false;
                }
            }
        }
        // If loops complete without returning false, no empty cells remain.
        return true;
    }

public:
    /**
     * @brief Entry point to solve the Sudoku puzzle.
     * Modifies the board in-place.
     * * @param board A 9x9 vector of characters representing the Sudoku grid.
     */
    void solveSudoku(vector<vector<char>> &board)
    {
        solve(board);
    }
};