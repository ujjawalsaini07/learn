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

class Solution
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

int main()
{
    Solution sol;
    string s = "aab";

    // Execute logic
    vector<vector<string>> result = sol.partition(s);

    // Output results
    cout << "Input: " << s << endl;
    cout << "Output: [" << endl;
    for (size_t i = 0; i < result.size(); i++)
    {
        cout << "  [";
        for (size_t j = 0; j < result[i].size(); j++)
        {
            cout << "\"" << result[i][j] << "\"";
            if (j < result[i].size() - 1)
                cout << ", ";
        }
        cout << "]";
        if (i < result.size() - 1)
            cout << ",";
        cout << endl;
    }
    cout << "]" << endl;

    return 0;
}