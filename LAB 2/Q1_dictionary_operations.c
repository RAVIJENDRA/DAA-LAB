#include <stdio.h>

typedef struct
{
    const char *structure;
    const char *search;
    const char *insert;
    const char *delete_op;
    const char *maximum;
    const char *minimum;
    const char *predecessor;
    const char *successor;
} Row;

int main()
{
    Row table[] = {
        {"Unsorted array",             "O(n)",     "O(1)", "O(1)", "O(n)", "O(n)", "O(1)", "O(1)"},
        {"Sorted array",               "O(log n)", "O(n)", "O(n)", "O(1)", "O(1)", "O(1)", "O(1)"},
        {"Singly linked unsorted list","O(n)",     "O(1)", "O(n)", "O(n)", "O(n)", "O(n)", "O(n)"},
        {"Singly linked sorted list",  "O(n)",     "O(n)", "O(n)", "O(1)", "O(1)", "O(n)", "O(1)"},
        {"Doubly linked unsorted list","O(n)",     "O(1)", "O(1)", "O(n)", "O(n)", "O(1)", "O(1)"},
        {"Doubly linked sorted list",  "O(n)",     "O(n)", "O(1)", "O(1)", "O(1)", "O(1)", "O(1)"}
    };

    int i;
    int count = sizeof(table) / sizeof(table[0]);
    FILE *fp;

    printf("Dictionary operations - worst case\n\n");

    printf("%-29s %-10s %-10s %-10s %-10s %-10s %-13s %-10s\n",
           "Structure", "Search", "Insert", "Delete",
           "Max", "Min", "Predecessor", "Successor");

    printf("------------------------------------------------------------------------------------------------\n");

    for(i = 0; i < count; i++)
    {
        printf("%-29s %-10s %-10s %-10s %-10s %-10s %-13s %-10s\n",
               table[i].structure, table[i].search, table[i].insert,
               table[i].delete_op, table[i].maximum, table[i].minimum,
               table[i].predecessor, table[i].successor);
    }

    /*
       The next part gives representative values for the main
       growth functions. These values can be plotted against n.
    */
    fp = fopen("q1_growth_data.csv", "w");

    if(fp == NULL)
    {
        printf("\nCould not create q1_growth_data.csv\n");
        return 1;
    }

    fprintf(fp, "n,O(1),O(log2n),O(n),O(nlog2n),O(n^2)\n");

    for(i = 10; i <= 1000; i += 10)
    {
        int logn = 0;
        int x = i;

        while(x > 1)
        {
            x = x / 2;
            logn++;
        }

        fprintf(fp, "%d,1,%d,%d,%d,%d\n",
                i, logn, i, i * logn, i * i);
    }

    fclose(fp);

    printf("\nGrowth data saved in q1_growth_data.csv\n");

    return 0;
}
