#include <vector>
#include <iostream>

using namespace std;

class Solution {
private:
    // TRANSLATION OF: private static boolean isSafe(...)
    // Checks if it is safe to assign color 'col' to 'node'
    bool isSafe(int node, vector<vector<int>>& G, vector<int>& color, int n, int col) {
        // "for(int it : G[node])" -> Iterating through neighbors
        for(int it : G[node]) {
            // "if(color[it] == col) return false;"
            if(color[it] == col) {
                return false;
            }
        }
        return true;
    }

    // TRANSLATION OF: private static boolean solve(...)
    // Recursive function to try coloring nodes one by one
    bool solve(int node, vector<vector<int>>& G, vector<int>& color, int n, int m) {
        // "if(node == n) return true;" -> Base case: all nodes colored
        if(node == n) {
            return true;
        }

        // "for(int i = 1; i <= m; i++)" -> Try all colors from 1 to m
        for(int i = 1; i <= m; i++) {
            
            // "if(isSafe(node, G, color, n, i))"
            if(isSafe(node, G, color, n, i)) {
                
                // "color[node] = i;" -> Assign color
                color[node] = i;
                
                // "if(solve(node + 1, G, color, n, m) == true) return true;"
                // Recurse to next node
                if(solve(node + 1, G, color, n, m)) {
                    return true;
                }
                
                // "color[node] = 0;" -> Backtrack (reset color)
                color[node] = 0;
            }
        }
        
        return false;
    }

public:
    // TRANSLATION OF: public static boolean graphColoring(...)
    // Main wrapper function
    bool graphColoring(int n, vector<pair<int, int>>& edges, int m) {
        // Building the Adjacency List (G) from edges
        // Note: The screenshot assumes G is already built. 
        // In C++, we often build it first.
        vector<vector<int>> G(n);
        for(auto& edge : edges) {
            G[edge.first].push_back(edge.second);
            G[edge.second].push_back(edge.first); // Undirected graph
        }

        // "int[] color" -> vector initialized to 0
        vector<int> color(n, 0);

        // "if(solve(0, G, color, n, m) == true)"
        if(solve(0, G, color, n, m)) {
            return true;
        }

        return false;
    }
};

int main(int argc, char const *argv[])
{
    
    return 0;
}
