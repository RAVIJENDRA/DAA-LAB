#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n, i, j, temp;
    int count1, count2;
    FILE *fp;

    fp = fopen("q3_data.csv", "w");

    if(fp == NULL)
    {
        printf("Could not create q3_data.csv\n");
        return 1;
    }

    fprintf(fp, "n,Early_Termination,Without_Early_Termination\n");

    srand(time(NULL));

    for(n = 10; n <= 100; n += 10)
    {
        int a[n], b[n];

        for(i = 0; i < n; i++)
        {
            a[i] = rand() % 1000;
            b[i] = a[i];
        }

        count1 = 0;
        count2 = 0;

        /* Version 1: stops when no swap occurs in a pass */
        for(i = 0; i < n - 1; i++)
        {
            int swapped = 0;

            for(j = 0; j < n - 1 - i; j++)
            {
                count1++;

                if(a[j] > a[j + 1])
                {
                    temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                    swapped = 1;
                }
            }

            if(swapped == 0)
                break;
        }

        /* Version 2: always completes all passes */
        for(i = 0; i < n - 1; i++)
        {
            for(j = 0; j < n - 1 - i; j++)
            {
                count2++;

                if(b[j] > b[j + 1])
                {
                    temp = b[j];
                    b[j] = b[j + 1];
                    b[j + 1] = temp;
                }
            }
        }

        printf("n = %d : %d , %d\n", n, count1, count2);
        fprintf(fp, "%d,%d,%d\n", n, count1, count2);
    }

    fclose(fp);

    printf("\nData saved in q3_data.csv\n");

    return 0;
}
