#include <stdio.h>
#include <string.h>
#define MAX 256
typedef struct{
    char ch;
    int freq;
} Node;
Node heap[MAX];
int hs = 0;
void push(Node x){
    int i = hs++;
    while (i > 0 && heap[(i - 1) / 2].freq < x.freq){
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap[i] = x;
}
Node pop(){
    Node max = heap[0];
    Node x = heap[--hs];
    int i = 0, child;
    while (2 * i + 1 < hs){
        child = 2 * i + 1;
        if (child + 1 < hs && heap[child + 1].freq > heap[child].freq)
            child++;
        if (heap[child].freq <= x.freq)
            break;
        heap[i] = heap[child];
        i = child;
    }
    if (hs > 0)
        heap[i] = x;
    return max;
}
int reorganize(char str[], int k, char result[]){
    int freq[256] = {0};
    int i, n = strlen(str), pos = 0;
    Node x, used[MAX];
    int count = 0;
    hs = 0;
    for (i = 0; i < n; i++)
        freq[(unsigned char)str[i]]++;
    for (i = 0; i < 256; i++){
        if (freq[i] > 0){
            x.ch = (char)i;
            x.freq = freq[i];
            push(x);
        }
    }
    while (hs > 0){
        x = pop();
        result[pos++] = x.ch;
        x.freq--;
        if (x.freq > 0)
            used[count++] = x;
        if (count == k){
            for(i = 0; i < count; i++)
                push(used[i]);
            count = 0;
        }
    }
    if (pos != n)
        return 0;
    result[pos] = '\0';
    return 1;
}
int main(){
    char str[MAX], result[MAX];
    int k;
    printf("Enter string: ");
    scanf("%255s", str);
    printf("Enter k: ");
    scanf("%d", &k);
    if(k <= 1)
        printf("Result = %s\n", str);
    else if (reorganize(str, k, result))
        printf("Result = %s\n", result);
    else
        printf("-1\n");
    return 0;
}