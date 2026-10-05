#include <stdio.h>

typedef unsigned long long ull;

/*
    Returns the next value in the Collatz sequence.
*/
ull nextCollatz(ull n)
{
    if (n % 2 == 0)
        return n / 2;
    else
        return 3 * n + 1;
}

/*
    Prints the trajectory of one starting value.
    Returns the number of steps required to reach 1.
*/
ull analyzeStartingValue(ull n)
{
    ull original = n;
    ull steps = 0;
    ull maxValue = n;

    printf("\nTrajectory for n = %llu:\n", original);
    printf("%llu", n);

    while (n != 1)
    {
        n = nextCollatz(n);
        steps++;

        if (n > maxValue)
            maxValue = n;

        printf(" -> %llu", n);
    }

    printf("\nSteps to reach 1 = %llu\n", steps);
    printf("Maximum value reached = %llu\n", maxValue);

    return steps;
}

/*
    Analyzes every starting value in the interval [a, b].
*/
void analyzeInterval(ull a, ull b)
{
    ull i;
    ull steps;
    ull totalSteps = 0;
    ull maxSteps = 0;
    ull maxStart = a;

    printf("\nCollatz analysis for interval [%llu, %llu]\n",
           a, b);

    printf("\nStarting Value\tSteps to Reach 1\n");
    printf("--------------------------------\n");

    for (i = a; i <= b; i++)
    {
        steps = analyzeStartingValue(i);

        printf("%llu\t\t%llu\n", i, steps);

        totalSteps += steps;

        if (steps > maxSteps)
        {
            maxSteps = steps;
            maxStart = i;
        }

        /*
            Prevent overflow of i when b is the largest
            possible unsigned long long value.
        */
        if (i == b)
            break;
    }

    printf("\nInterval Summary\n");
    printf("----------------\n");
    printf("Total steps over interval = %llu\n", totalSteps);
    printf("Maximum steps = %llu\n", maxSteps);
    printf("Starting value with maximum steps = %llu\n", maxStart);
}

int main()
{
    ull n, a, b;

    printf("Enter starting value n (n >= 1): ");
    scanf("%llu", &n);

    if (n < 1)
    {
        printf("Invalid starting value. n must be at least 1.\n");
        return 0;
    }

    printf("\nEnter interval [a, b]: ");
    scanf("%llu %llu", &a, &b);

    if (a < 1 || b < a)
    {
        printf("Invalid interval. It must satisfy 1 <= a <= b.\n");
        return 0;
    }

    /* Analyze the user-provided starting value */
    analyzeStartingValue(n);

    /* Analyze every value in the interval */
    analyzeInterval(a, b);

    return 0;
}