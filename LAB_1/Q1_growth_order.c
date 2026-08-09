#include <stdio.h>

struct Function
{
    char name[50];
    int rank;
};

int main()
{
    struct Function f[] = {
        {"1/n", 1},
        {"log2(n)", 2},
        {"12*sqrt(n)", 3},
        {"50*n^0.5", 3},
        {"n^0.51", 4},
        {"n", 5},
        {"2^32*n", 5},
        {"n*log2(n)", 6},
        {"100*n^2 + 6*n", 7},
        {"n^2 - 324", 7},
        {"2*n^3", 8},
        {"n^(log2(n))", 9},
        {"3^n", 10}
    };

    int count = sizeof(f) / sizeof(f[0]);
    int i, j;
    struct Function temp;

    for(i = 0; i < count - 1; i++)
    {
        for(j = 0; j < count - 1 - i; j++)
        {
            if(f[j].rank > f[j + 1].rank)
            {
                temp = f[j];
                f[j] = f[j + 1];
                f[j + 1] = temp;
            }
        }
    }

    printf("Functions in increasing order of growth:\n\n");

    for(i = 0; i < count; i++)
    {
        printf("%s\n", f[i].name);
    }

    return 0;
}
