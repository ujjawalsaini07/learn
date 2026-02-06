#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * ======================================================================================
 * 1. PRINT ALL STRING SUBSEQUENCES
 * ======================================================================================
 * Purpose: Generates all possible subsequences of a given string.
 *
 * Logic:   For every character, we have two choices:
 * 1. TAKE it into the subsequence.
 * 2. NOT TAKE it.
 *
 * Complexity:
 * - Time:  O(2^n) - We make 2 decisions for every index.
 * - Space: O(n)   - Stack space depth is equal to the length of the string.
 */
void printAllSubSequences(int index, string &str, string &currentStr) {
    // Base Case: We have processed all indices
    if (index == str.length()) {
        cout << (currentStr == "" ? "{}" : currentStr) << endl;
        return;
    }

    // --- CHOICE 1: TAKE ---
    currentStr.push_back(str[index]); // Add char to current state
    printAllSubSequences(index + 1, str, currentStr);

    // --- BACKTRACK ---
    currentStr.pop_back(); // Remove char to restore state for the next call

    // --- CHOICE 2: NOT TAKE ---
    printAllSubSequences(index + 1, str, currentStr);
}

/**
 * ======================================================================================
 * 2. PRINT ALL SUBSEQUENCES WITH TARGET SUM
 * ======================================================================================
 * Purpose: Prints every subsequence whose elements add up to 'targetSum'.
 *
 * Parameters:
 * - index: Current index in the original array.
 * - nums: The input vector (passed by ref to save memory).
 * - ds:   The current subsequence being built (Data Structure).
 * - targetSum: The sum we want to achieve.
 * - currentSum: The sum of elements currently in 'ds'.
 *
 * Complexity:
 * - Time:  O(2^n)
 * - Space: O(n)
 */
void printAllSubSequencesWithSum(int index, const vector<int> &nums, vector<int> &ds, int targetSum, int currentSum) {
    // Base Case
    if (index == nums.size()) {
        if (currentSum == targetSum) {
            cout << "[ ";
            for (int val : ds) cout << val << " ";
            cout << "]" << endl;
        }
        return;
    }

    // --- CHOICE 1: TAKE ---
    ds.push_back(nums[index]);
    // Note: We pass (currentSum + nums[index]) directly. 
    // This avoids the need to manually subtract later!
    printAllSubSequencesWithSum(index + 1, nums, ds, targetSum, currentSum + nums[index]);

    // --- BACKTRACK ---
    ds.pop_back(); // We must still remove the element from the vector

    // --- CHOICE 2: NOT TAKE ---
    printAllSubSequencesWithSum(index + 1, nums, ds, targetSum, currentSum);
}

/**
 * ======================================================================================
 * 3. PRINT ONLY ONE SUBSEQUENCE WITH TARGET SUM
 * ======================================================================================
 * Purpose: Finds the FIRST valid subsequence and stops.
 *
 * Logic:   The function returns a boolean (true/false).
 * If the 'Take' call returns true, we return true immediately
 * without making the 'Not Take' call (Pruning).
 *
 * Complexity:
 * - Time:  O(2^n) (Worst case, if answer is at the very end or doesn't exist)
 * - Space: O(n)
 */
bool printOneSubSequenceWithSum(int index, const vector<int> &nums, vector<int> &ds, int targetSum, int currentSum) {
    // Base Case
    if (index == nums.size()) {
        if (currentSum == targetSum) {
            cout << "Found one: [ ";
            for (int val : ds) cout << val << " ";
            cout << "]" << endl;
            return true; // Condition satisfied
        }
        return false; // Condition not satisfied
    }

    // --- CHOICE 1: TAKE ---
    ds.push_back(nums[index]);
    if (printOneSubSequenceWithSum(index + 1, nums, ds, targetSum, currentSum + nums[index]) == true) {
        return true; // If found in the left branch, return immediately
    }

    // --- BACKTRACK ---
    ds.pop_back();

    // --- CHOICE 2: NOT TAKE ---
    if (printOneSubSequenceWithSum(index + 1, nums, ds, targetSum, currentSum) == true) {
        return true;
    }

    return false; // Not found in either branch
}

/**
 * ======================================================================================
 * 4. COUNT SUBSEQUENCES WITH TARGET SUM
 * ======================================================================================
 * Purpose: Returns the integer count of subsequences that match the sum.
 *
 * Logic:   l = count from 'Take' branch
 * r = count from 'Not Take' branch
 * return l + r
 *
 * Complexity:
 * - Time:  O(2^n)
 * - Space: O(n)
 */
int countSubSequencesWithSum(int index, const vector<int> &nums, int targetSum, int currentSum) {
    // Optimization: If currentSum exceeds target (and numbers are positive), we can stop early.
    // Uncomment the line below if array only contains positives:
    // if (currentSum > targetSum) return 0;

    // Base Case
    if (index == nums.size()) {
        return (currentSum == targetSum) ? 1 : 0;
    }

    // --- CHOICE 1: TAKE ---
    int left = countSubSequencesWithSum(index + 1, nums, targetSum, currentSum + nums[index]);

    // --- CHOICE 2: NOT TAKE ---
    // Note: No vector push/pop needed here since we only care about the count.
    int right = countSubSequencesWithSum(index + 1, nums, targetSum, currentSum);

    return left + right;
}

int main() {
    // --- Test Data ---
    const vector<int> nums = {1, 2, 1};
    const int targetSum = 2;
    vector<int> ds;

    cout << "--- 1. All Subsequences with Sum " << targetSum << " ---" << endl;
    printAllSubSequencesWithSum(0, nums, ds, targetSum, 0);

    cout << "\n--- 2. Print Only One Subsequence ---" << endl;
    // Reset ds for next function
    ds.clear(); 
    printOneSubSequenceWithSum(0, nums, ds, targetSum, 0);

    cout << "\n--- 3. Count Subsequences ---" << endl;
    cout << "Count: " << countSubSequencesWithSum(0, nums, targetSum, 0) << endl;

    return 0;
}