#include <stdio.h>
#include <limits.h>
#define MAX 100
int min(int a, int b){
    return a < b ? a : b;
}
int optimalCost(int w[], int n){
    int dp[MAX][MAX] = {0};
    int sum[MAX] = {0};
    int i, j, k, len, cost;
    for (i = 0; i < n; i++)
        sum[i + 1] = sum[i] + w[i];
    for (len = 2; len <= n; len++){
        for (i = 0; i + len <= n; i++){
            j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (k = i; k < j; k++){
                cost = dp[i][k] + dp[k + 1][j] + sum[j + 1] - sum[i];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    return n > 0 ? dp[0][n - 1] : 0;
}
int main(){
    int n, i, w[MAX];
    printf("Enter number of weights: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX)
        return 0;
    printf("Enter weights in order: ");
    for (i = 0; i < n; i++)
        scanf("%d", &w[i]);
    printf("Minimum weighted path cost = %d\n",
           optimalCost(w, n));
    return 0;
}