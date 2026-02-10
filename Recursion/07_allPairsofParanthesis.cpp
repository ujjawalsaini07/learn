#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Helper function to check if a generated string is balanced
    bool valid(string &s) {
        int depth = 0;
        for (char &c : s) {
            // Rule 1: A ')' can never exist without a preceding '('
            if (c == '(') depth++;
            else depth--;
            
            // If depth goes negative, we have more ')' than '(', which is invalid
            if (depth < 0) return false;
        }
        // Rule 2: Total '(' must equal total ')'
        return depth == 0;
    }

    void solve(int n, string &s, vector<string> &ans) {
        // Base Case: String has reached the required length (n pairs = 2*n characters)
        if (s.size() == 2 * n) {
            if (valid(s)) ans.push_back(s);
            return;
        }

        // Recursive Step 1: Try adding an opening bracket
        s.push_back('(');
        solve(n, s, ans);
        s.pop_back(); // Backtrack: remove it to try the other possibility

        // Recursive Step 2: Try adding a closing bracket
        s.push_back(')');
        solve(n, s, ans);
        s.pop_back(); // Backtrack
    }

public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string s = "";
        solve(n, s, ans);
        return ans;
    }
};





class Solution {
private:
    /**
     * @param n Total pairs of parentheses
     * @param s The current string being built
     * @param ans The list of all valid combinations
     * @param open Current count of '(' in the string
     * @param close Current count of ')' in the string
     */
    void solve(int n, string &s, vector<string> &ans, int &open, int &close) {
        // Base Case: The string is full and guaranteed valid by our logic below
        if (s.size() == 2 * n) {
            ans.push_back(s);
            return;
        }

        // Rule 1: We can add an '(' if we haven't reached the limit 'n'
        if (open < n) {
            open++;
            s.push_back('(');
            solve(n, s, ans, open, close);
            // Backtrack: Reset state for the next recursive branch
            s.pop_back();
            open--;
        }

        // Rule 2: We can add a ')' ONLY if there is an unmatched '(' to close
        if (close < open) {
            close++;
            s.push_back(')');
            solve(n, s, ans, open, close);
            // Backtrack: Reset state for the next recursive branch
            close--;
            s.pop_back();
        }
    }

public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string s = "";
        int open = 0;
        int close = 0;
        solve(n, s, ans, open, close);
        return ans;
    }
};

int main()
{

    return 0;
}