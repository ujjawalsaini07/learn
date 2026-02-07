#include<bits/stdc++.h>
using namespace std;
 


/**
 * @class Solution
 * @brief Solves the N-Queens problem using Backtracking.
 * * The N-Queens puzzle is the problem of placing n queens on an n x n chessboard 
 * such that no two queens attack each other. This class provides functionality 
 * to find all distinct solutions.
 */
class Solution {
private:
    /**
     * @brief Checks if it is safe to place a Queen at board[row][col].
     * * Since we fill columns from left to right (0 to n-1), we only need to check 
     * for attacking Queens to the LEFT of the current column. We check three directions:
     * 1. Upper-Left Diagonal
     * 2. Left Row (Horizontal)
     * 3. Lower-Left Diagonal
     * * @param row The row index where we want to place the Queen.
     * @param col The column index where we want to place the Queen.
     * @param board The current state of the chessboard.
     * @param n The size of the board (N x N).
     * @return true if the position is safe (no attacking Queens), false otherwise.
     */
    bool check(int row, int col, vector<string>& board, int n) {
        int duprow = row;
        int dupcol = col;

        // 1. Check Upper-Left Diagonal
        // Move diagonally up-left until we hit the board boundary
        while (row > -1 && col > -1) {
            if (board[row][col] == 'Q')
                return false;
            row--;
            col--;
        }

        // Reset position for next check
        row = duprow;
        col = dupcol;

        // 2. Check Left Row (Horizontal)
        // Move strictly left until we hit the board boundary
        while (col > -1) {
            if (board[row][col] == 'Q')
                return false;
            col--;
        }

        // Reset column only (row is already at duprow because the previous loop didn't change it)
        col = dupcol;

        // 3. Check Lower-Left Diagonal
        // Move diagonally down-left until we hit the board boundary
        while (row < n && col > -1) {
            if (board[row][col] == 'Q')
                return false;
            row++;
            col--;
        }

        // If no queens are found in any of the 3 directions, the position is safe.
        return true;
    }

    /**
     * @brief Recursive helper function to solve the N-Queens problem.
     * * This function uses backtracking. It tries to place a Queen in every row 
     * of the current 'col'. If successful, it moves to 'col + 1'. If it reaches 
     * a dead end, it backtracks by removing the Queen and trying the next row.
     * * @param col The current column index we are trying to fill.
     * @param board The current state of the chessboard.
     * @param n The size of the board.
     * @param ans A reference to the vector of vectors where valid solutions are stored.
     */
    void solve(int col, vector<string>& board, int& n,
               vector<vector<string>>& ans) {
        // Base Case: If we have successfully filled all columns (0 to n-1),
        // we have found a valid solution.
        if (col == n) {
            ans.push_back(board);
            return;
        }

        // Iterate through every row in the current column
        for(int row = 0; row < n ; row++)
        {
            // Check if placing a Queen at (row, col) is valid
            if(check(row, col, board, n))
            {
                // Action: Place the Queen
                board[row][col] = 'Q';
                
                // Recurse: Move to the next column
                solve(col + 1, board, n, ans);
                
                // Backtrack: Remove the Queen to explore other possibilities for this row
                board[row][col] = '.';
            }
        }
    }

public:
    /**
     * @brief Main function to solve the N-Queens problem.
     * * Initializes the board and starts the recursive backtracking process.
     * * @param n The number of queens (and the size of the n x n board).
     * @return A vector of vectors, where each inner vector represents a valid board configuration.
     * * @note Time Complexity: O(N! * N) - We have N choices for the first col, N-1 for the second, etc.
     * @note Space Complexity: O(N^2) for the board storage + O(N) for recursion stack depth.
     */
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        
        // Initialize board with empty strings of size 'n' filled with '.'
        // Example for n=4: board = ["....", "....", "....", "...."]
        vector<string> board(n);
        string s(n, '.');
        for (int i = 0; i < n; i++)
            board[i] = s;
            
        // Start solving from the first column (index 0)
        solve(0, board, n, ans);
        
        return ans;
    }
};


int main(int argc, char const *argv[])
{
    
    return 0;
}
