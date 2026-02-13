#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Rat in a Maze
 * Description: Finds all possible paths from (0,0) to (n-1, n-1) using Backtracking.
 * * Time Complexity: O(3^(n^2)) 
 * -- In the worst case, at each cell, we have 3 choices (excluding the cell we came from).
 * * Space Complexity: O(n^2) 
 * -- Due to the recursion stack and the auxiliary 'vis' (visited) matrix.
 */

void solve(int i, int j, vector<vector<int>> &arr, string &path, vector<string> &ans, vector<vector<int>> &vis, int &n) {
    // Base Case: If we reach the bottom-right corner, store the current path
    if (i == n - 1 && j == n - 1) {
        ans.push_back(path);
        return;
    }

    /* We explore 4 directions in lexicographical order (D, L, R, U) 
       to ensure the resulting paths are sorted alphabetically.
    */

    // 1. Move Down: Check boundary, if already visited, and if path is blocked (0)
    if (i + 1 < n && !vis[i + 1][j] && arr[i + 1][j] != 0) {
        vis[i + 1][j] = 1;         // Mark as visited
        path.push_back('D');       // Add direction to path
        solve(i + 1, j, arr, path, ans, vis, n);
        path.pop_back();           // Backtrack: remove direction
        vis[i + 1][j] = 0;         // Backtrack: unmark visited
    }

    // 2. Move Left
    if (j - 1 > -1 && !vis[i][j - 1] && arr[i][j - 1] != 0) {
        vis[i][j - 1] = 1;
        path.push_back('L');
        solve(i, j - 1, arr, path, ans, vis, n);
        path.pop_back();
        vis[i][j - 1] = 0;
    }

    // 3. Move Right
    if (j + 1 < n && !vis[i][j + 1] && arr[i][j + 1] != 0) {
        vis[i][j + 1] = 1;
        path.push_back('R');
        solve(i, j + 1, arr, path, ans, vis, n);
        path.pop_back();
        vis[i][j + 1] = 0;
    }

    // 4. Move Up
    if (i - 1 > -1 && !vis[i - 1][j] && arr[i - 1][j] != 0) {
        vis[i - 1][j] = 1;
        path.push_back('U');
        solve(i - 1, j, arr, path, ans, vis, n);
        path.pop_back();
        vis[i - 1][j] = 0;
    }
}

/**
 * Main wrapper function to initialize structures and start the search.
 * @param arr: The n x n maze
 * @param n: Size of the maze
 * @return: A list of all valid path strings
 */
vector<string> searchMaze(vector<vector<int>> &arr, int n) {
    vector<string> ans;
    // Visited matrix to prevent cycles
    vector<vector<int>> vis(n, vector<int>(n, 0));
    string s = "";

    // Edge case: If starting or ending cell is blocked, no path exists
    if (arr[0][0] == 0 || arr[n-1][n-1] == 0) return ans;

    // Start recursion from (0,0)
    vis[0][0] = 1;
    solve(0, 0, arr, s, ans, vis, n);
    
    return ans;
}