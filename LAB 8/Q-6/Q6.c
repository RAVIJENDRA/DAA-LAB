#include <stdio.h>
#include <string.h>

#define MAX 100

/* Print the operations in forward order using the traceback table. */
void printTrace(char A[], char B[], char trace[MAX + 1][MAX + 1],
                int i, int j)
{
    char steps[MAX + MAX][120];
    int count = 0;

    while (i > 0 || j > 0)
    {
        if (i > 0 && j > 0 && trace[i][j] == 'M')
        {
            sprintf(steps[count],
                    "Match: '%c' -> '%c' (no operation)",
                    A[i - 1], B[j - 1]);
            count++;
            i--;
            j--;
        }
        else if (i > 0 && j > 0 && trace[i][j] == 'S')
        {
            sprintf(steps[count],
                    "Substitute: '%c' -> '%c'",
                    A[i - 1], B[j - 1]);
            count++;
            i--;
            j--;
        }
        else if (i > 0 && trace[i][j] == 'D')
        {
            sprintf(steps[count],
                    "Delete: '%c'",
                    A[i - 1]);
            count++;
            i--;
        }
        else if (j > 0 && trace[i][j] == 'I')
        {
            sprintf(steps[count],
                    "Insert: '%c'",
                    B[j - 1]);
            count++;
            j--;
        }
    }

    /* Traceback is collected backwards, so print it in reverse. */
    for (i = count - 1; i >= 0; i--)
    {
        printf("%d. %s\n", count - i, steps[i]);
    }
}

int min3(int a, int b, int c)
{
    int min = a;

    if (b < min)
        min = b;

    if (c < min)
        min = c;

    return min;
}

int main()
{
    char A[MAX + 1], B[MAX + 1];
    int dp[MAX + 1][MAX + 1];
    char trace[MAX + 1][MAX + 1];

    int m, n;
    int i, j;

    printf("Enter first string: ");
    scanf("%100s", A);

    printf("Enter second string: ");
    scanf("%100s", B);

    m = strlen(A);
    n = strlen(B);

    /* Initialize first column */
    for (i = 0; i <= m; i++)
    {
        dp[i][0] = i;

        if (i > 0)
            trace[i][0] = 'D';
    }

    /* Initialize first row */
    for (j = 0; j <= n; j++)
    {
        dp[0][j] = j;

        if (j > 0)
            trace[0][j] = 'I';
    }

    /* Fill the DP table */
    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (A[i - 1] == B[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
                trace[i][j] = 'M';
            }
            else
            {
                int insertCost;
                int deleteCost;
                int substituteCost;

                insertCost = dp[i][j - 1] + 1;
                deleteCost = dp[i - 1][j] + 1;
                substituteCost = dp[i - 1][j - 1] + 1;

                dp[i][j] = min3(insertCost,
                                deleteCost,
                                substituteCost);

                if (dp[i][j] == substituteCost)
                    trace[i][j] = 'S';
                else if (dp[i][j] == deleteCost)
                    trace[i][j] = 'D';
                else
                    trace[i][j] = 'I';
            }
        }
    }

    printf("\nMinimum edit distance = %d\n", dp[m][n]);

    printf("\nTraceback operations:\n");
    printTrace(A, B, trace, m, n);

    return 0;
}