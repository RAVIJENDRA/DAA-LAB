
#include <stdio.h>
#include <stdlib.h>
#define MAX 256
typedef struct node {
    char ch;
    int freq;
    struct node *left, *right;
} node;
typedef struct {
    char ch;
    int len;
} code;
node *heap[2 * MAX];
int hs = 0;
node *create(char ch, int freq, node *l, node *r) {
    node *p = malloc(sizeof(node));
    p->ch = ch;
    p->freq = freq;
    p->left = l;
    p->right = r;
    return p;
}
void push(node *p) {
    int i = ++hs;
    while (i > 1 && heap[i / 2]->freq > p->freq) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = p;
}
node *pop() {
    node *ans = heap[1];
    node *x = heap[hs--];
    int i = 1, c;
    while (2 * i <= hs) {
        c = 2 * i;
        if (c < hs && heap[c + 1]->freq < heap[c]->freq)
            c++;
        if (x->freq <= heap[c]->freq)
            break;
        heap[i] = heap[c];
        i = c;
    }
    if (hs > 0)
        heap[i] = x;
    return ans;
}
void buildTree(int n) {
    while (hs > 1) {
        node *a = pop();
        node *b = pop();
        node *p = create('\0', a->freq + b->freq, a, b);
        push(p);
    }
}
code codes[MAX];
int count = 0;
void getLengths(node *p, int depth) {
    if (p == NULL)
        return;
    if (p->left == NULL && p->right == NULL) {
        codes[count].ch = p->ch;
        codes[count].len = depth ? depth : 1;
        count++;
        return;
    }
    getLengths(p->left, depth + 1);
    getLengths(p->right, depth + 1);
}
int compare(const void *a, const void *b) {
    code *x = (code *)a;
    code *y = (code *)b;
    if (x->len != y->len)
        return x->len - y->len;
    return (unsigned char)x->ch - (unsigned char)y->ch;
}
void canonicalCodes() {
    char bits[MAX + 1] = {0};
    int prev = codes[0].len;
    for (int i = 0; i < prev; i++)
        bits[i] = '0';
    bits[prev] = '\0';
    for(int i = 0; i < count; i++){
        if (i > 0){
            int j = prev - 1;
            while(j >= 0 && bits[j] == '1'){
                bits[j] = '0';
                j--;
            }
            if(j >= 0)
                bits[j] = '1';
            int len = codes[i].len;
            for (int k = prev; k < len; k++){
                bits[k] = '0';
            }
            bits[len] = '\0';
            prev = len;
        }
        printf("%c : %s\n", codes[i].ch, bits);
    }
}
int main() {
    int n, freq;
    char ch;
    printf("Enter number of symbols: ");
    scanf("%d", &n);
    if (n < 1 || n > MAX)
        return 1;
    for (int i = 0; i < n; i++) {
        printf("Enter symbol and frequency: ");
        scanf(" %c %d", &ch, &freq);
        push(create(ch, freq, NULL, NULL));
    }
    buildTree(n);
    node *root = pop();
    getLengths(root, 0);
    qsort(codes, count, sizeof(code), compare);
    printf("\nCanonical Huffman Codes:\n");
    canonicalCodes();
    return 0;
}