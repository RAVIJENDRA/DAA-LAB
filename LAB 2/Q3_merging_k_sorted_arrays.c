#include <stdio.h>
#include <stdlib.h>

static void merge_two(int *a, int n1, int *b, int n2, int *out, long long *comp)
{
    int i = 0, j = 0, k = 0;

    while(i < n1 && j < n2)
    {
        (*comp)++;

        if(a[i] <= b[j])
            out[k++] = a[i++];
        else
            out[k++] = b[j++];
    }

    while(i < n1)
        out[k++] = a[i++];

    while(j < n2)
        out[k++] = b[j++];
}

static int *copy_array(const int *src, int n)
{
    int i;
    int *dst = malloc(n * sizeof(int));

    if(dst == NULL)
        return NULL;

    for(i = 0; i < n; i++)
        dst[i] = src[i];

    return dst;
}

static int is_sorted(const int *a, int n)
{
    int i;

    for(i = 1; i < n; i++)
    {
        if(a[i - 1] > a[i])
            return 0;
    }

    return 1;
}

static long long method1(int **arrays, int n, int k)
{
    int i;
    int current_size = n;
    int *current = copy_array(arrays[0], n);
    long long comp = 0;

    if(current == NULL)
        return -1;

    for(i = 1; i < k; i++)
    {
        int new_size = current_size + n;
        int *next = malloc(new_size * sizeof(int));

        if(next == NULL)
        {
            free(current);
            return -1;
        }

        merge_two(current, current_size, arrays[i], n, next, &comp);

        free(current);
        current = next;
        current_size = new_size;
    }

    free(current);
    return comp;
}

static long long method2(int **arrays, int n, int k)
{
    int count = k;
    int i;
    int **list = malloc(k * sizeof(int *));
    int *sizes = malloc(k * sizeof(int));
    long long comp = 0;

    if(list == NULL || sizes == NULL)
        return -1;

    for(i = 0; i < k; i++)
    {
        list[i] = copy_array(arrays[i], n);
        sizes[i] = n;

        if(list[i] == NULL)
            return -1;
    }

    while(count > 1)
    {
        int new_count = (count + 1) / 2;
        int **new_list = malloc(new_count * sizeof(int *));
        int *new_sizes = malloc(new_count * sizeof(int));
        int p, q = 0;

        if(new_list == NULL || new_sizes == NULL)
            return -1;

        for(p = 0; p < count; p += 2)
        {
            if(p + 1 < count)
            {
                int size = sizes[p] + sizes[p + 1];
                int *merged = malloc(size * sizeof(int));

                if(merged == NULL)
                    return -1;

                merge_two(list[p], sizes[p], list[p + 1], sizes[p + 1],
                          merged, &comp);

                free(list[p]);
                free(list[p + 1]);

                new_list[q] = merged;
                new_sizes[q] = size;
                q++;
            }
            else
            {
                new_list[q] = list[p];
                new_sizes[q] = sizes[p];
                q++;
            }
        }

        free(list);
        free(sizes);

        list = new_list;
        sizes = new_sizes;
        count = new_count;
    }

    free(list[0]);
    free(list);
    free(sizes);

    return comp;
}

int main()
{
    int n, max_k, k, i;
    int **arrays;
    FILE *fp;

    printf("Enter number of elements in each sorted array (n): ");
    scanf("%d", &n);

    printf("Enter maximum number of arrays (k): ");
    scanf("%d", &max_k);

    if(n <= 0 || max_k < 2)
    {
        printf("Invalid input.\n");
        return 1;
    }

    arrays = malloc(max_k * sizeof(int *));

    if(arrays == NULL)
        return 1;

    for(i = 0; i < max_k; i++)
    {
        arrays[i] = malloc(n * sizeof(int));

        if(arrays[i] == NULL)
            return 1;

        /* Simple deterministic sorted data */
        for(int j = 0; j < n; j++)
            arrays[i][j] = i * 2 + j * max_k;
    }

    fp = fopen("q3_data.csv", "w");

    if(fp == NULL)
    {
        printf("Could not create q3_data.csv\n");
        return 1;
    }

    fprintf(fp, "k,Method1_Comparisons,Method2_Comparisons\n");
    printf("\nk,Method 1,Method 2\n");

    for(k = 2; k <= max_k; k++)
    {
        long long c1 = method1(arrays, n, k);
        long long c2 = method2(arrays, n, k);

        if(c1 < 0 || c2 < 0)
        {
            printf("Memory allocation failed.\n");
            fclose(fp);
            return 1;
        }

        printf("%d,%lld,%lld\n", k, c1, c2);
        fprintf(fp, "%d,%lld,%lld\n", k, c1, c2);
    }

    fclose(fp);

    for(i = 0; i < max_k; i++)
        free(arrays[i]);

    free(arrays);

    printf("\nData saved in q3_data.csv\n");
    return 0;
}
