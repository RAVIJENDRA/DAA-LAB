#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int root;
    int key;
} ComponentKey;

int findRoot(int parent[], int x) {
    if (parent[x] != x) {
        parent[x] = findRoot(parent, parent[x]);
    }
    return parent[x];
}

void unite(int parent[], int size[], int a, int b) {
    int rootA = findRoot(parent, a);
    int rootB = findRoot(parent, b);
    if (rootA == rootB) {
        return;
    }

    if (size[rootA] < size[rootB]) {
        int temp = rootA;
        rootA = rootB;
        rootB = temp;
    }

    parent[rootB] = rootA;
    size[rootA] += size[rootB];
}

int compareComponentKey(const void *left, const void *right) {
    const ComponentKey *a = left;
    const ComponentKey *b = right;

    if (a->root < b->root) return -1;
    if (a->root > b->root) return 1;
    if (a->key < b->key) return -1;
    if (a->key > b->key) return 1;
    return 0;
}

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2 || N <= 0 || M < 0) {
        printf("Invalid input. Expected N M, with N > 0 and M >= 0.\n");
        return 1;
    }

    int *A = malloc((size_t)(N + 1) * sizeof(int));
    int *parent = malloc((size_t)(N + 1) * sizeof(int));
    int *size = malloc((size_t)(N + 1) * sizeof(int));
    int *answer = malloc((size_t)(N + 1) * sizeof(int));
    ComponentKey *positions = malloc((size_t)N * sizeof(ComponentKey));
    ComponentKey *values = malloc((size_t)N * sizeof(ComponentKey));
    if (A == NULL || parent == NULL || size == NULL || answer == NULL ||
        positions == NULL || values == NULL) {
        printf("Memory allocation failed.\n");
        free(A); free(parent); free(size); free(answer);
        free(positions); free(values);
        return 1;
    }

    for (int i = 1; i <= N; i++) {
        if (scanf("%d", &A[i]) != 1 || A[i] < 1 || A[i] > N) {
            printf("Invalid permutation value. Values must be in 1..N.\n");
            return 1;
        }
        parent[i] = i;
        size[i] = 1;
    }

    for (int i = 1; i <= M; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2 ||
            u < 1 || u > N || v < 1 || v > N) {
            printf("Invalid allowed-swap edge at position %d.\n", i);
            return 1;
        }
        unite(parent, size, u, v);
    }

    /* Positions are sorted by (component, index); values by (component, value). */
    for (int i = 1; i <= N; i++) {
        int root = findRoot(parent, i);
        positions[i - 1].root = root;
        positions[i - 1].key = i;
        values[i - 1].root = root;
        values[i - 1].key = A[i];
    }

    qsort(positions, (size_t)N, sizeof(ComponentKey), compareComponentKey);
    qsort(values, (size_t)N, sizeof(ComponentKey), compareComponentKey);

    for (int i = 0; i < N; i++) {
        /* Matching component order guarantees each value stays in its component. */
        answer[positions[i].key] = values[i].key;
    }

    printf("Lexicographically smallest achievable permutation:\n");
    for (int i = 1; i <= N; i++) {
        printf("%d%s", answer[i], (i == N) ? "\n" : " ");
    }

    free(A); free(parent); free(size); free(answer);
    free(positions); free(values);
    return 0;
}
