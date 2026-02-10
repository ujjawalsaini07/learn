#include <bits/stdc++.h>
using namespace std;

// Solution class to generate all subsequences using bit manipulation
class Solution {
public:
    // Function to return all subsequences of string s
    vector<string> getSubsequences(string s) {
        // Length of input string
        int n = s.size();

        // Total subsequences = 2^n
        int total = 1 << n;

        // Vector to store all subsequences
        vector<string> subsequences;

        // Iterate over all bit masks from 0 to 2^n - 1
        for (int mask = 0; mask < total; mask++) {
            // Temporary subsequence string
            string subseq = "";

            // Check each bit position in mask
            for (int i = 0; i < n; i++) {
                // If i-th bit of mask is set, include s[i]
                if (mask & (1 << i)) {
                    subseq += s[i];
                }
            }

            // Store the formed subsequence
            subsequences.push_back(subseq);
        }

        // Return all generated subsequences
        return subsequences;
    }
};

int main() {
    // Input string
    string s = "abc";

    // Create Solution object
    Solution sol;

    // Get all subsequences
    vector<string> subsequences = sol.getSubsequences(s);

    // Print all subsequences
    for (auto &subseq : subsequences) {
        cout << "\"" << subseq << "\"" << endl;
    }

    return 0;
}