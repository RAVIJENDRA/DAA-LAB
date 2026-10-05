#include <stdio.h>

#define MAX 100

int maximumSumIncreasingSubsequence(int a[], int n)
{
    int dp[MAX];
    int i, j;
    int maxSum;

    /* Initially, each element forms an increasing subsequence by itself. */
    for (i = 0; i < n; i++)
    {
        dp[i] = a[i];
    }

    /* Find the best increasing subsequence ending at each position. */
    for (i = 1; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (a[j] < a[i] && dp[i] < dp[j] + a[i])
            {
                dp[i] = dp[j] + a[i];
            }
        }
    }

    /* Find the largest value in dp[]. */
    maxSum = dp[0];

    for (i = 1; i < n; i++)
    {
        if (dp[i] > maxSum)
        {
            maxSum = dp[i];
        }
    }

    return maxSum;
}

int main()
{
    int a[MAX];
    int n, i;
    int result;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter %d positive integers:\n", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    result = maximumSumIncreasingSubsequence(a, n);

    printf("Maximum sum of increasing subsequence = %d\n", result);

    return 0;
}