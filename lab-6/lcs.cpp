#include <bits/stdc++.h>
using namespace std;

// Function to find LCS length and LCS string
pair<int, string> longestCommonSubsequence(const string& X, const string& Y) {
    int m = X.size();
    int n = Y.size();
    
    // DP table to store LCS lengths
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    // Fill DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    // Backtracking to find the LCS string
    int lcsLength = dp[m][n];
    string lcs = "";
    
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs += X[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    
    reverse(lcs.begin(), lcs.end());
    
    return {lcsLength, lcs};
}

int main() {
    string X = "diksha";
    string Y = "shivam";

    auto result = longestCommonSubsequence(X, Y);
    cout << "Length of LCS: " << result.first << endl;
    cout << "LCS: " << result.second << endl;

    return 0;
}