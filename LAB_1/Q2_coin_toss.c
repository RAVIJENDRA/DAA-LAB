#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n, i;
    int fairHeads = 0;
    int biasedHeads = 0;
    double fairProbability, biasedProbability;

    printf("Enter number of tosses: ");
    scanf("%d", &n);

    srand(time(NULL));

    for(i = 0; i < n; i++)
    {
        if(rand() % 2 == 0)
            fairHeads++;

        if(rand() % 100 < 70)
            biasedHeads++;
    }

    fairProbability = (double)fairHeads / n;
    biasedProbability = (double)biasedHeads / n;

    printf("\nFair coin:\n");
    printf("Heads = %d\n", fairHeads);
    printf("Probability of HEAD = %.4f\n", fairProbability);

    printf("\nBiased coin (70%% HEAD):\n");
    printf("Heads = %d\n", biasedHeads);
    printf("Probability of HEAD = %.4f\n", biasedProbability);

    return 0;
}
