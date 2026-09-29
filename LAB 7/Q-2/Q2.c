#include <stdio.h>

#define MAX_EGGS 50
#define MAX_FLOORS 1000

int eggDrop(int eggs, int floors)
{
    int dp[MAX_EGGS + 1][MAX_FLOORS + 1];

    int e, f, x;
    int breakCase, surviveCase;
    int drops;

    /* Base case: 0 floors need 0 drops */
    for (e = 1; e <= eggs; e++)
    {
        dp[e][0] = 0;
    }

    /* Base case: 1 floor needs 1 drop */
    for (e = 1; e <= eggs; e++)
    {
        dp[e][1] = 1;
    }

    /* Base case: 1 egg requires checking every floor */
    for (f = 0; f <= floors; f++)
    {
        dp[1][f] = f;
    }

    /* Fill the DP table */
    for (e = 2; e <= eggs; e++)
    {
        for (f = 2; f <= floors; f++)
        {
            dp[e][f] = floors;   // Initial large value

            /* Try dropping from every possible floor */
            for (x = 1; x <= f; x++)
            {
                /* Egg breaks */
                breakCase = dp[e - 1][x - 1];

                /* Egg does not break */
                surviveCase = dp[e][f - x];

                /* We consider the worst case */
                if (breakCase > surviveCase)
                    drops = breakCase;
                else
                    drops = surviveCase;

                /* Add the current drop */
                drops = drops + 1;

                /* Store the minimum */
                if (drops < dp[e][f])
                {
                    dp[e][f] = drops;
                }
            }
        }
    }

    return dp[eggs][floors];
}

int main()
{
    int eggs, floors;
    int result;

    printf("Enter number of eggs: ");
    scanf("%d", &eggs);

    printf("Enter number of floors: ");
    scanf("%d", &floors);

    if (eggs <= 0 || floors < 0)
    {
        printf("Invalid input.\n");
        return 0;
    }

    if (eggs > MAX_EGGS || floors > MAX_FLOORS)
    {
        printf("Input size is too large.\n");
        return 0;
    }

    result = eggDrop(eggs, floors);

    printf("Minimum number of drops required = %d\n", result);

    return 0;
}