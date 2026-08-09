#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void merge_two(int a[], int l, int m, int r, long long *comp)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    int i, j, k;

    int *left = malloc(n1 * sizeof(int));
    int *right = malloc(n2 * sizeof(int));

    if(left == NULL || right == NULL)
        exit(1);

    for(i = 0; i < n1; i++)
        left[i] = a[l + i];

    for(j = 0; j < n2; j++)
        right[j] = a[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while(i < n1 && j < n2)
    {
        (*comp)++;

        if(left[i] <= right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }

    while(i < n1)
        a[k++] = left[i++];

    while(j < n2)
        a[k++] = right[j++];

    free(left);
    free(right);
}

static void merge_sort_two(int a[], int l, int r, long long *comp)
{
    int m;

    if(l >= r)
        return;

    m = l + (r - l) / 2;

    merge_sort_two(a, l, m, comp);
    merge_sort_two(a, m + 1, r, comp);
    merge_two(a, l, m, r, comp);
}

static void merge_three(int a[], int l, int m1, int m2, int r, long long *comp)
{
    int n1 = m1 - l + 1;
    int n2 = m2 - m1;
    int n3 = r - m2;
    int i = 0, j = 0, k = 0, t = 0;

    int *x = malloc(n1 * sizeof(int));
    int *y = malloc(n2 * sizeof(int));
    int *z = malloc(n3 * sizeof(int));
    int *temp = malloc((r - l + 1) * sizeof(int));

    if(x == NULL || y == NULL || z == NULL || temp == NULL)
        exit(1);

    while(i < n1)
        x[i] = a[l + i], i++;

    i = 0;
    while(i < n2)
        y[i] = a[m1 + 1 + i], i++;

    i = 0;
    while(i < n3)
        z[i] = a[m2 + 1 + i], i++;

    i = 0;

    while(i < n1 || j < n2 || k < n3)
    {
        int from = 0;

        if(i < n1)
        {
            from = 1;
        }

        if(j < n2)
        {
            if(from == 0 || y[j] < x[i])
                from = 2;
            (*comp)++;
        }

        if(k < n3)
        {
            if(from == 0)
                from = 3;
            else if(from == 1)
            {
                (*comp)++;
                if(z[k] < x[i])
                    from = 3;
            }
            else if(from == 2)
            {
                (*comp)++;
                if(z[k] < y[j])
                    from = 3;
            }
        }

        if(from == 1)
            temp[t++] = x[i++];
        else if(from == 2)
            temp[t++] = y[j++];
        else
            temp[t++] = z[k++];
    }

    for(i = 0; i < r - l + 1; i++)
        a[l + i] = temp[i];

    free(x);
    free(y);
    free(z);
    free(temp);
}

static void merge_sort_three(int a[], int l, int r, long long *comp)
{
    int n, n1, n2, m1, m2;

    if(l >= r)
        return;

    n = r - l + 1;

    if(n == 2)
    {
        (*comp)++;

        if(a[l] > a[r])
        {
            int t = a[l];
            a[l] = a[r];
            a[r] = t;
        }

        return;
    }

    n1 = n / 3;
    n2 = n / 3;

    if(n1 == 0)
    {
        merge_sort_two(a, l, r, comp);
        return;
    }

    m1 = l + n1 - 1;
    m2 = m1 + n2;

    merge_sort_three(a, l, m1, comp);
    merge_sort_three(a, m1 + 1, m2, comp);
    merge_sort_three(a, m2 + 1, r, comp);

    merge_three(a, l, m1, m2, r, comp);
}

static int is_sorted(int a[], int n)
{
    int i;

    for(i = 1; i < n; i++)
    {
        if(a[i - 1] > a[i])
            return 0;
    }

    return 1;
}

int main()
{
    int n, i;
    int *a, *b;
    long long c1, c2;
    FILE *fp;

    srand(1);

    fp = fopen("q2_data.csv", "w");

    if(fp == NULL)
    {
        printf("Could not create q2_data.csv\n");
        return 1;
    }

    fprintf(fp, "n,Merge_Sort,Modified_Merge_Sort\n");
    printf("n,Merge Sort,Modified Merge Sort\n");

    for(n = 30; n <= 300; n += 30)
    {
        a = malloc(n * sizeof(int));
        b = malloc(n * sizeof(int));

        if(a == NULL || b == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }

        for(i = 0; i < n; i++)
        {
            a[i] = rand() % 1000;
            b[i] = a[i];
        }

        c1 = 0;
        c2 = 0;

        merge_sort_two(a, 0, n - 1, &c1);
        merge_sort_three(b, 0, n - 1, &c2);

        if(!is_sorted(a, n) || !is_sorted(b, n))
        {
            printf("Sorting verification failed for n = %d\n", n);
            free(a);
            free(b);
            fclose(fp);
            return 1;
        }

        printf("%d,%lld,%lld\n", n, c1, c2);
        fprintf(fp, "%d,%lld,%lld\n", n, c1, c2);

        free(a);
        free(b);
    }

    fclose(fp);

    printf("\nBoth sorting methods were verified.\n");
    printf("Data saved in q2_data.csv\n");

    return 0;
}
