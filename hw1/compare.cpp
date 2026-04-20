#include "compare.h"

CompareFiles::CompareFiles(const std::string& _p1, const std::string& _p2): p1(_p1), p2(_p2)
{
    std::ifstream file1(p1), file2(p2);
    std::string s1, s2, line;
    while (std::getline(file1, line)) s1 += line;
    while (std::getline(file2, line)) s2 += line;
    common = longestCommonSubsequence(s1, s2);
}

CompareFiles::CompareFiles(const fs::path& _p1, const fs::path& _p2): p1(_p1), p2(_p2)
{
    std::ifstream file1(p1), file2(p2);
    std::string s1, s2, line;
    while (std::getline(file1, line)) s1 += line;
    while (std::getline(file2, line)) s2 += line;
    common = longestCommonSubsequence(s1, s2);
}

std::string CompareFiles::longestCommonSubsequence(std::string X, std::string Y) {

    std::string cleanX = "", cleanY = "";
    for (char c : X) {
        if (c != ' ' && c != '\n' && c != '\t' && c != '\r'){
            cleanX += c;
        }
    }
    
    for (char c : Y) {
        if (c != ' ' && c != '\n' && c != '\t' && c != '\r'){
            cleanY += c;
        }
    }
    
    X = cleanX;
    Y = cleanY;

    size_t m = X.length();
    size_t n = Y.length();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    std::string result = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            result += X[i - 1];
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    std::reverse(result.begin(), result.end());
    return result;
}

void CompareFiles::show_stats() const{
   
    std::cout << "Pair: " << p1.string() << ", " << p2.string() << "\n";
    std::cout << "Common subsequence length: " << common.length() << "\n";
    std::cout << "Overlap: " << common << "\n"; 

}
