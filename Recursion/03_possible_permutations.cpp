#include <bits/stdc++.h>
using namespace std;
/**
 * @class Solution
 * @brief Provides a method to generate all possible permutations of a sequence of unique integers.
 */
class Solution
{
private:
    /**
     * @brief Helper function that uses backtracking to build permutations.
     * * @param nums   The original input vector of numbers.
     * @param ds     "Data Structure" - A temporary vector representing the current permutation being built.
     * @param mymap  A frequency map (boolean) to track indices used in the current recursive path.
     * @param ans    The result vector containing all complete permutations.
     */
    void permute(vector<int> &nums, vector<int> &ds, unordered_map<int, bool> &mymap, vector<vector<int>> &ans)
    {

        // Base Case: If the current permutation size equals the input size, we've found a valid permutation.
        if (ds.size() == nums.size())
        {
            ans.push_back(ds);
            return;
        }

        // Recursive Step: Iterate through all numbers to find the next element for the permutation.
        for (int i = 0; i < nums.size(); i++)
        {

            // If the element at index 'i' has not been used in the current path:
            if (!mymap[i])
            {

                // 1. Action: Mark index as used and add the number to our current sequence.
                mymap[i] = true;
                ds.push_back(nums[i]);

                // 2. Recurse: Move to the next level of the tree to pick the next number.
                permute(nums, ds, mymap, ans);

                // 3. Backtrack: Remove the number and unmark the index to explore other possibilities.
                mymap[i] = false;
                ds.pop_back();
            }
        }
    }

public:
    /**
     * @brief Entry point for the permutation algorithm.
     * @param nums A vector of distinct integers.
     * @return A 2D vector containing all possible permutations.
     * * Time Complexity: O(N! * N) - Where N is the number of elements.
     * Space Complexity: O(N) - For the recursion stack and the map.
     */
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> ans;
        vector<int> ds;
        unordered_map<int, bool> mymap; // Tracks used indices to handle recursion state.

        permute(nums, ds, mymap, ans);

        return ans;
    }
};

int main()
{
    return 0;
}