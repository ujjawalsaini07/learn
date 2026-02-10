#include <bits/stdc++.h>
using namespace std;

class Solution {
    void generate(int n, vector<string>& ans, string& s) {
        if (s.size() == n) {
            ans.push_back(s);
            return;
        }

        // Always allowed
        s.push_back('0');
        generate(n, ans, s);
        s.pop_back();

        // Allowed only if last is not '1'
        if (s.empty() || s.back() == '0') {
            s.push_back('1');
            generate(n, ans, s);
            s.pop_back();
        }
    }

public:
    vector<string> generateBinaryStrings(int n) {
        vector<string> ans;
        string s;
        generate(n, ans, s);

        for (auto& str : ans) {
            cout << str << endl;
        }
        return ans;
    }
};

int main() {
    Solution obj;
    obj.generateBinaryStrings(3);
    return 0;
}
