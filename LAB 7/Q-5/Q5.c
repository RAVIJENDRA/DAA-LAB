#include <stdio.h>
#include <stdlib.h>

/* Function to create the sequence of shots */
void createStrategy(int n, int shots[], int *count)
{
    int i;

    *count = 0;

    /* Special case when n = 2 */
    if (n == 2)
    {
        shots[(*count)++] = 1;
        shots[(*count)++] = 1;
        return;
    }

    /* First sweep: 2, 3, ..., n-1 */
    for (i = 2; i <= n - 1; i++)
    {
        shots[(*count)++] = i;
    }

    /*
       Second sweep:
       If n is odd, go from 2 to n-1 again.
       If n is even, go from n-1 down to 2.
    */
    if (n % 2 == 1)
    {
        for (i = 2; i <= n - 1; i++)
        {
            shots[(*count)++] = i;
        }
    }
    else
    {
        for (i = n - 1; i >= 2; i--)
        {
            shots[(*count)++] = i;
        }
    }
}

/* Function to validate whether the strategy guarantees a hit */
int validateStrategy(int n, int shots[], int count)
{
    int i, j;
    int remaining;
    
    /* Arrays to store possible target positions */
    int *possible = (int *)malloc((n + 1) * sizeof(int));
    int *next = (int *)malloc((n + 1) * sizeof(int));

    /* Initially target can be at any position */
    for (i = 1; i <= n; i++)
    {
        possible[i] = 1;
    }

    /* Position 0 is not used */
    possible[0] = 0;

    /* Process every shot */
    for (i = 0; i < count; i++)
    {
        /* The position being shot cannot contain a surviving target */
        possible[shots[i]] = 0;

        /* Initially no positions are possible */
        for (j = 1; j <= n; j++)
        {
            next[j] = 0;
        }

        /*
           Target moves to an adjacent position
           after the shot.
        */
        for (j = 1; j <= n; j++)
        {
            if (possible[j] == 1)
            {
                if (j > 1)
                {
                    next[j - 1] = 1;
                }

                if (j < n)
                {
                    next[j + 1] = 1;
                }
            }
        }

        /* Copy next positions into possible */
        for (j = 1; j <= n; j++)
        {
            possible[j] = next[j];
        }
    }

    /* Count the positions where target can still survive */
    remaining = 0;

    for (i = 1; i <= n; i++)
    {
        if (possible[i] == 1)
        {
            remaining++;
        }
    }

    free(possible);
    free(next);

    /* If no position remains, the target was guaranteed to be hit */
    if (remaining == 0)
    {
        return 1;
    }

    return 0;
}

int main()
{
    int n;
    int i;
    int count;
    int *shots;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n <= 1)
    {
        printf("Number of hiding spots must be greater than 1.\n");
        return 0;
    }

    /*
       Maximum number of shots is 2n - 4 for n >= 3.
       We allocate a little extra space.
    */
    shots = (int *)malloc((2 * n + 1) * sizeof(int));

    /* Create the shooting strategy */
    createStrategy(n, shots, &count);

    printf("\nShooting sequence:\n");

    for (i = 0; i < count; i++)
    {
        printf("%d ", shots[i]);
    }

    printf("\n");

    /* Validate the strategy */
    if (validateStrategy(n, shots, count))
    {
        printf("Result: Guaranteed to hit the target.\n");
    }
    else
    {
        printf("Result: Strategy does not guarantee a hit.\n");
    }

    printf("Number of shots = %d\n", count);

    free(shots);

    return 0;
}