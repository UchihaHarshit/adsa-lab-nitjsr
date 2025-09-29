#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack(int W, int wt[], int val[], int n) {

    int dp[n + 1][W + 1];
    int i, w;

    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {

            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            }

            else if (wt[i - 1] > w) {
                dp[i][w] = dp[i - 1][w];
            }

            else {
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            }
        }
    }


    return dp[n][W];
}


int main() {
    int val[] = {60, 100, 120}; // Values of the items
    int wt[] = {10, 20, 30};    // Weights of the items
    int W = 50;                // Knapsack capacity
    int n = sizeof(val) / sizeof(val[0]); // Number of items

    int maxValue = knapsack(W, wt, val, n);

    printf("The maximum value that can be put in the knapsack is: %d\n", maxValue);

    return 0;
}