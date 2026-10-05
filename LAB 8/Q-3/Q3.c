#include <stdio.h>
#include <string.h>

#define MAX 100

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

/* Builds the DP table and returns the LCS length */
int findLCS(char X[], char Y[], int m, int n,
            int dp[MAX + 1][MAX + 1])
{
    int i, j;

    /* First row and first column are zero */
    for (i = 0; i <= m; i++)
        dp[i][0] = 0;

    for (j = 0; j <= n; j++)
        dp[0][j] = 0;

    /* Fill the DP table */
    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[m][n];
}

/* Reconstructs the actual LCS */
void printLCS(char X[], char Y[], int m, int n,
              int dp[MAX + 1][MAX + 1])
{
    char lcs[MAX + 1];

    int i = m;
    int j = n;
    int k = dp[m][n];

    lcs[k] = '\0';

    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs[k - 1] = X[i - 1];

            i--;
            j--;
            k--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    printf("LCS: %s\n", lcs);
}

int main()
{
    char X[MAX + 1];
    char Y[MAX + 1];

    int m, n;
    int dp[MAX + 1][MAX + 1];
    int length;

    printf("Enter first string: ");
    scanf("%100s", X);

    printf("Enter second string: ");
    scanf("%100s", Y);

    m = strlen(X);
    n = strlen(Y);

    length = findLCS(X, Y, m, n, dp);

    printf("Length of LCS: %d\n", length);

    printLCS(X, Y, m, n, dp);

    return 0;
}