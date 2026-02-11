/*
 * ======================================================================================
 * PROBLEM: Palindrome Partitioning (LeetCode #131)
 * ======================================================================================
 * * GOAL:
 * Given a string 's', partition it such that every substring of the partition is a
 * palindrome. Return all possible palindrome partitionings.
 * * ALGORITHM: Backtracking
 * -----------------------
 * The solution uses a recursive backtracking approach to explore all potential cuts.
 * * 1. Start at index 0.
 * 2. Loop through the string from 'index' to the end.
 * 3. For every position 'i', check if the substring s[index...i] is a palindrome.
 * 4. IF VALID:
 * a. Choose: Add substring to 'ds' (current path).
 * b. Explore: Recursively call solve() for the next starting position (i + 1).
 * c. Un-choose: Backtrack by popping the substring to try the next cut.
 * * COMPLEXITY ANALYSIS
 * -------------------
 * N = length of string 's'
 * * Time Complexity: O(N * 2^N)
 * - 2^N: In the worst case (e.g., "aaaa"), there are 2^(N-1) possible partitionings.
 * - N:   For each valid partition, generating the substring and storing it takes O(N).
 * Palindrome checking also takes linear time relative to substring length.
 * * Space Complexity: O(N)
 * - We use O(N) stack space for recursion depth.
 * - We use O(N) space for the temporary vector 'ds'.
 * - (This excludes the space needed for the final answer vector).
 * ======================================================================================
 */

#include <bits/stdc++.h>
using namespace std;

class Solution1
{
private:
    /**
     * @brief Helper function to check if a substring is a palindrome.
     * * @param s The source string.
     * @param start The starting index of the substring.
     * @param end The ending index of the substring.
     * @return true if s[start...end] reads the same forwards and backwards.
     */
    bool isValid(string &s, int start, int end)
    {
        while (start <= end)
        {
            if (s[start] != s[end])
                return false;
            start++;
            end--;
        }
        return true;
    }

    /**
     * @brief Core recursive backtracking function.
     * * @param index The current starting index for the cut.
     * @param s The original string.
     * @param ds Temporary list storing the current sequence of palindromes.
     * @param ans The final list of lists to store all valid partition sequences.
     */
    void solve(int index, string &s, vector<string> &ds, vector<vector<string>> &ans)
    {
        // Base Case: If index reaches the end, we found a valid partition sequence.
        if (index == s.size())
        {
            ans.push_back(ds);
            return;
        }

        // Try to cut at every position from 'index' to the end of string
        for (int i = index; i < s.size(); i++)
        {

            // Only proceed if the substring s[index...i] is a palindrome
            if (isValid(s, index, i))
            {

                // 1. CHOOSE: Add this palindrome to our current list
                ds.push_back(s.substr(index, i - index + 1));

                // 2. EXPLORE: Move to the next index (i + 1) and continue
                solve(i + 1, s, ds, ans);

                // 3. UN-CHOOSE (Backtrack): Remove the last added substring
                // so we can try a different cut in the next iteration of the loop.
                ds.pop_back();
            }
        }
    }

public:
    /**
     * @brief Main public interface.
     * * @param s Input string.
     * @return vector<vector<string>> All possible palindrome partitions.
     */
    vector<vector<string>> partition(string s)
    {
        vector<vector<string>> ans;
        vector<string> ds;
        solve(0, s, ds, ans);
        return ans;
    }
};


/*
 * Problem: Palindrome Partitioning II (Optimized Version)
 * * APPROACH: Recursion with Memoization + Pre-computed Palindrome Table
 * * 1. Pre-computation Phase:
 * We build a 2D boolean table `isPal[n][n]`.
 * isPal[i][j] is TRUE if the substring s[i...j] is a palindrome.
 * This allows us to check palindrome status in O(1) later.
 * * 2. Solver Phase:
 * We use standard recursion to find the minimum cuts, but now looking up
 * palindromes is instant.
 * * COMPLEXITY ANALYSIS:
 * --------------------
 * Time Complexity: $$O(N^2)$$
 * - Pre-computation: We fill an N*N table with nested loops = $$O(N^2)$$.
 * - Recursion: There are N states. Inside each state, we loop N times.
 * The check inside the loop is now $$O(1)$$. 
 * Work = $$N \times N \times 1 = O(N^2)$$.
 * - Total Time = $$O(N^2) + O(N^2) \approx O(N^2)$$.
 * * Space Complexity: $$O(N^2)$$
 * - $$O(N^2)$$ for the `isPal` table (Dominant term).
 * - $$O(N)$$ for the `dp` array.
 * - $$O(N)$$ for recursion stack space.
 */


class Solution2 {
private: 
    // Recursive solver
    int solve(int index, const int n, vector<int> &dp, const vector<vector<bool>> &isPal) {
        // Base Case: Reached end of string, 0 segments needed for empty string
        if (index == n) return 0;

        // Memoization: Return pre-calculated result
        if (dp[index] != -1) return dp[index];

        int min_cost = INT_MAX;

        // Try every possible cut from 'index' to 'n-1'
        for (int i = index; i < n; i++) {
            
            // OPTIMIZATION: Check if s[index...i] is palindrome in O(1) time
            if (isPal[index][i]) {
                // 1 cost for this segment + cost for the remaining suffix
                int cost = 1 + solve(i + 1, n, dp, isPal);
                min_cost = min(cost, min_cost);
            }
        }
        
        return dp[index] = min_cost;
    }

public:
    int minCut(string s) {
        int n = s.size();
        if (n == 0) return 0;

        // --- STEP 1: Pre-compute Palindrome Table ---
        // isPal[i][j] will store true if s[i...j] is a palindrome
        vector<vector<bool>> isPal(n, vector<bool>(n, false));

        // We fill the table. 'i' is the start index, 'j' is the end index.
        // We iterate backwards for 'i' so that when we compute isPal[i][j],
        // the inner palindrome isPal[i+1][j-1] is already computed.
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s[i] == s[j]) {
                    // It is a palindrome if:
                    // 1. It is 1 char long (j - i < 2)
                    // 2. OR the inner substring (i+1 to j-1) is a palindrome
                    if (j - i < 2 || isPal[i + 1][j - 1]) {
                        isPal[i][j] = true;
                    }
                }
            }
        }

        // --- STEP 2: Solve with Memoization ---
        vector<int> dp(n, -1);
        
        // We subtract 1 because solve() returns the number of *segments*.
        // Cuts = Segments - 1. (e.g., "a|b" is 2 segments, 1 cut)
        return solve(0, n, dp, isPal) - 1;
    }
};

int main()
{
    return 0;
}