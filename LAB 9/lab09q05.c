#include <stdio.h>
#include <stdlib.h>
int candy(int rating[], int n){
    int *c = (int *)malloc(n * sizeof(int));
    int i, total = 0;
    for (i = 0; i < n; i++)
        c[i] = 1;
    for (i = 1; i < n; i++){
        if (rating[i] > rating[i - 1])
            c[i] = c[i - 1] + 1;
    }
    for (i = n - 2; i >= 0; i--){
        if (rating[i] > rating[i + 1] &&c[i] <= c[i + 1])
            c[i] = c[i + 1] + 1;
    }
    for (i = 0; i < n; i++)
        total += c[i];
    free(c);
    return total;
}
int main(){
    int n, i, *rating;
    printf("Enter number of children: ");
    scanf("%d", &n);
    if (n <= 0)
        return 0;
    rating = (int *)malloc(n * sizeof(int));
    printf("Enter ratings: ");
    for (i = 0; i < n; i++)
        scanf("%d", &rating[i]);
    printf("Minimum candies = %d\n", candy(rating, n));
    free(rating);
    return 0;
}