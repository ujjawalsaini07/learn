#include <bits/stdc++.h>
using namespace std;

/**
 * ======================================================================================
 * ALGORITHM 1: COMBINATION SUM I (Unlimited Picks)
 * ======================================================================================
 * Purpose: 
 * Finds all combinations where elements can be reused unlimited times 
 * to reach the targetSum.
 * * Parameters:
 * - index: Current index in the nums array.
 * - nums: The input array of candidates.
 * - subsequence_vec: The 2D vector to store all valid combinations.
 * - ds: The current combination (data structure) being built.
 * - targetSum: The remaining sum we need to achieve.
 * * Complexity:
 * - Time:  O(2^t * k) -> Exponential. 't' is the target value. 
 * In the worst case (all 1s), the tree height is 'target'.
 * - Space: O(t) -> Maximum stack depth depends on the target value.
 */
void returnAllSubSequencesWithSum(int index, const vector<int> &nums, vector<vector<int>> &subsequence_vec, vector<int> &ds, int targetSum)
{
    // --- BASE CASE 1: Boundary & Failure Check ---
    // If we reached the end of the array OR the sum became negative/zero
    if (index == nums.size() || targetSum <= 0)
    {
        if (targetSum == 0)
        {
            subsequence_vec.push_back(ds); // Success: Add valid combination
        }
        return;
    }

    // --- CHOICE 1: TAKE (Stay at SAME index) ---
    // We implicitly prune here by ensuring we don't pick if targetSum becomes negative 
    // (though the Base Case catches it, this check saves a recursion step).
    if (nums[index] <= targetSum) 
    {
        ds.push_back(nums[index]);
        // CRITICAL LOGIC: We pass 'index' (not index+1) because we can reuse this number.
        returnAllSubSequencesWithSum(index, nums, subsequence_vec, ds, targetSum - nums[index]);
        
        // --- BACKTRACK ---
        ds.pop_back(); // Remove element to restore state for the "Not Take" branch
    }

    // --- CHOICE 2: NOT TAKE (Move to NEXT index) ---
    returnAllSubSequencesWithSum(index + 1, nums, subsequence_vec, ds, targetSum);
}

/**
 * ======================================================================================
 * ALGORITHM 2: COMBINATION SUM II (No Reuse + Handle Duplicates)
 * ======================================================================================
 * Purpose: 
 * Finds all unique combinations where each number is used at most once.
 * Must handle duplicate numbers in the input (e.g., [1, 2, 2, 2, 5]).
 * * Complexity:
 * - Time:  O(2^n * k) -> Exponential. 'n' is the number of elements.
 * - Space: O(n) -> Maximum stack depth is the size of the array.
 */
class Solution
{
private:
    void returnAllSubSequencesWithSum(int index, const vector<int> &nums,
                                      vector<vector<int>> &subsequence_vec,
                                      vector<int> &st, int targetSum)
    {
        // 1. BASE CASE: Success
        if (targetSum == 0)
        {
            subsequence_vec.push_back(st);
            return;
        }

        // 2. BASE CASE: End of Array
        if (index == nums.size())
        {
            return;
        }

        // 3. PRUNING (Optimization)
        // Since array is sorted, if nums[index] is greater than remaining target,
        // no subsequent number can fit either. We stop immediately.
        if (nums[index] > targetSum)
            return;

        // --- CHOICE 1: TAKE ---
        st.push_back(nums[index]);
        // CRITICAL LOGIC: We pass 'index + 1' because we CANNOT reuse the same element.
        returnAllSubSequencesWithSum(index + 1, nums, subsequence_vec, st, targetSum - nums[index]);
        
        // --- BACKTRACK ---
        st.pop_back();

        // --- CHOICE 2: NOT TAKE (with Duplicate Skipping) ---
        // We want to skip this number, but if the next number is identical, 
        // taking that one instead would result in the exact same combination 
        // we just generated in the "Take" branch. So we skip ALL duplicates.
        
        // Check bounds (index+1 < size) to prevent crash
        while (index + 1 < nums.size() && nums[index] == nums[index + 1])
        {
            index++;
        }

        // Move to the next distinct number
        returnAllSubSequencesWithSum(index + 1, nums, subsequence_vec, st, targetSum);
    }

public:
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        vector<int> st;
        vector<vector<int>> ans;
        
        // Sorting is MANDATORY for duplicate handling and pruning to work
        sort(candidates.begin(), candidates.end());
        
        returnAllSubSequencesWithSum(0, candidates, ans, st, target);
        return ans;
    }
};

/**
 * ======================================================================================
 * MAIN DRIVER CODE
 * ======================================================================================
 */
int main()
{
    // --- Test Data for Algorithm 1 (Unlimited Picks) ---
    // Note: This logic assumes input is distinct for pure Combination Sum I logic,
    // though the code works regardless.
    vector<int> original_vec = {1, 2, 3, 4, 5, 6, 7};
    vector<vector<int>> subsequence_vec;
    vector<int> ds;
    int targetSum = 13;

    cout << "--- Running Combination Sum I (Unlimited Picks) ---" << endl;
    
    // Call the global function
    returnAllSubSequencesWithSum(0, original_vec, subsequence_vec, ds, targetSum);

    // Print Results
    for (auto &vec : subsequence_vec)
    {
        cout << "{ ";
        for (auto &i : vec)
            cout << i << " ";
        cout << "}" << endl;
    }
    
    // --- Note: To test Algorithm 2, you would create a Solution object here ---
    // Solution sol;
    // vector<int> candidates = {10,1,2,7,6,1,5};
    // vector<vector<int>> res = sol.combinationSum2(candidates, 8);

    return 0;
}