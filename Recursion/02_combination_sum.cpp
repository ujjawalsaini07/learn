#include <bits/stdc++.h>
using namespace std;

void returnAllSubSequencesWithSum(int index, const vector<int> &nums, vector<vector<int>> &subsequence_vec, vector<int> &ds, int targetSum)
{
    // BASE CASE
    if (index == nums.size() || targetSum <= 0)
    {
        if (targetSum == 0)
        {
            subsequence_vec.push_back(ds);
        }
        return;
    }

    // --- CHOICE 1: TAKE ---
    ds.push_back(nums[index]);

    // IMPROVEMENT: Pass the subtraction directly here
    // We stay at 'index' for unlimited pick
    returnAllSubSequencesWithSum(index, nums, subsequence_vec, ds, targetSum - nums[index]);

    // --- BACKTRACK ---
    ds.pop_back();
    // No need to do targetSum += nums[index] because we never changed it!

    // --- CHOICE 2: NOT TAKE ---
    returnAllSubSequencesWithSum(index + 1, nums, subsequence_vec, ds, targetSum);
};

int main()
{
    vector<int> original_vec = {1, 2, 3, 4, 5, 6, 7};
    vector<vector<int>> subsequence_vec;
    vector<int> ds;
    int targetSum = 13;
    returnAllSubSequencesWithSum(0, original_vec, subsequence_vec, ds, targetSum);
    for (auto &vec : subsequence_vec)
    {
        cout << "{ ";
        for (auto &i : vec)
            cout << i << " ";
        cout << "}" << endl;
    }
    return 0;
}