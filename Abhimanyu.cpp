
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool canAbhimanyuSucceed(int p, int a, int b, vector<int>& k) {
    int n = 11;

    
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(a + 1, vector<int>(b + 1, -1)));

    // Initial state
    dp[0][a][b] = p;

    
    for (int i = 0; i < n; ++i) {
        for (int skips_left = 0; skips_left <= a; ++skips_left) {
            for (int recharges_left = 0; recharges_left <= b; ++recharges_left) {
                if (dp[i][skips_left][recharges_left] == -1) {
                    continue;
                }

                int current_power = dp[i][skips_left][recharges_left];

                
                if (current_power >= k[i]) {
                    int next_power = current_power - k[i];
                    if (i == 2 || i == 6) {  
                        int regenerated_power = k[i] / 2;
                        if (next_power >= regenerated_power) {
                            next_power -= regenerated_power;
                        } else {
                            if (skips_left > 0) {
                                dp[i + 1][skips_left - 1][recharges_left] = max(dp[i + 1][skips_left - 1][recharges_left], next_power);
                            }
                            if (recharges_left > 0) {
                                dp[i][skips_left][recharges_left - 1] = max(dp[i][skips_left][recharges_left - 1], next_power + p);
                            }
                            continue;
                        }
                    }
                    if (i + 1 < n) {
                        dp[i + 1][skips_left][recharges_left] = max(dp[i + 1][skips_left][recharges_left], next_power);
                    }
                }

                
                if (skips_left > 0) {
                    if (i + 1 < n) {
                        dp[i + 1][skips_left - 1][recharges_left] = max(dp[i + 1][skips_left - 1][recharges_left], current_power);
                    }
                }

                
                if (recharges_left > 0) {
                    dp[i][skips_left][recharges_left - 1] = max(dp[i][skips_left][recharges_left - 1], current_power + p);
                }
            }
        }
    }

    
    for (int skips_left = 0; skips_left <= a; ++skips_left) {
        for (int recharges_left = 0; recharges_left <= b; ++recharges_left) {
            if (dp[n - 1][skips_left][recharges_left] >= 0) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    int p = 50;
    int a = 6;
    int b = 4;
    vector<int> k = {30, 20, 40, 35, 25, 45, 50, 30, 20, 15, 10};

    if (canAbhimanyuSucceed(p, a, b, k)) {
        cout << "Abhimanyu can succeed." << endl;
    } else {
        cout << "Abhimanyu cannot succeed." << endl;
    }

    return 0;
}
