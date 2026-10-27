#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long sum;
    int root;
    int version;
} HeapItem;

typedef struct {
    HeapItem *items;
    int size;
    int capacity;
} MaxHeap;

int heapPush(MaxHeap *heap, HeapItem value) {
    if (heap->size == heap->capacity) {
        int newCapacity = (heap->capacity == 0) ? 16 : heap->capacity * 2;
        HeapItem *newItems = realloc(heap->items,
                                     (size_t)newCapacity * sizeof(HeapItem));
        if (newItems == NULL) {
            return 0;
        }
        heap->items = newItems;
        heap->capacity = newCapacity;
    }

    int index = heap->size++;
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (heap->items[parentIndex].sum >= value.sum) {
            break;
        }
        heap->items[index] = heap->items[parentIndex];
        index = parentIndex;
    }
    heap->items[index] = value;
    return 1;
}

void heapPop(MaxHeap *heap) {
    if (heap->size == 0) {
        return;
    }

    HeapItem last = heap->items[--heap->size];
    if (heap->size == 0) {
        return;
    }

    int index = 0;
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        if (left >= heap->size) {
            break;
        }
        int larger = left;
        if (right < heap->size &&
            heap->items[right].sum > heap->items[left].sum) {
            larger = right;
        }
        if (heap->items[larger].sum <= last.sum) {
            break;
        }
        heap->items[index] = heap->items[larger];
        index = larger;
    }
    heap->items[index] = last;
}

int findRoot(int parent[], int x) {
    if (parent[x] != x) {
        parent[x] = findRoot(parent, parent[x]);
    }
    return parent[x];
}

long long getMaximum(MaxHeap *heap, int parent[], int version[],
                     long long compSum[], int *exists) {
    while (heap->size > 0) {
        HeapItem top = heap->items[0];
        int root = top.root;
        if (parent[root] == root && version[root] == top.version &&
            compSum[root] == top.sum) {
            *exists = 1;
            return top.sum;
        }
        heapPop(heap);
    }
    *exists = 0;
    return 0;
}

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2 || N <= 0 || M < 0) {
        printf("Invalid input. Expected N M, with N > 0 and M >= 0.\n");
        return 1;
    }

    long long *weight = malloc((size_t)(N + 1) * sizeof(long long));
    int *head = malloc((size_t)(N + 1) * sizeof(int));
    int *to = malloc((size_t)(2 * M + 1) * sizeof(int));
    int *next = malloc((size_t)(2 * M + 1) * sizeof(int));
    int *order = malloc((size_t)(N + 1) * sizeof(int));
    int *seen = calloc((size_t)(N + 1), sizeof(int));
    int *parent = malloc((size_t)(N + 1) * sizeof(int));
    int *compSize = malloc((size_t)(N + 1) * sizeof(int));
    int *version = calloc((size_t)(N + 1), sizeof(int));
    long long *compSum = malloc((size_t)(N + 1) * sizeof(long long));
    long long *answer = calloc((size_t)(N + 1), sizeof(long long));
    int *hasAnswer = calloc((size_t)(N + 1), sizeof(int));

    if (weight == NULL || head == NULL || to == NULL || next == NULL ||
        order == NULL || seen == NULL || parent == NULL || compSize == NULL ||
        version == NULL || compSum == NULL || answer == NULL || hasAnswer == NULL) {
        printf("Memory allocation failed.\n");
        free(weight); free(head); free(to); free(next); free(order); free(seen);
        free(parent); free(compSize); free(version); free(compSum);
        free(answer); free(hasAnswer);
        return 1;
    }

    for (int v = 1; v <= N; v++) {
        if (scanf("%lld", &weight[v]) != 1) {
            printf("Invalid vertex weight input.\n");
            return 1;
        }
        head[v] = -1;
        parent[v] = -1; /* All vertices are inactive at the start. */
        compSize[v] = 0;
        compSum[v] = 0;
    }

    int edgeCount = 0;
    for (int i = 1; i <= M; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2 ||
            u < 1 || u > N || v < 1 || v > N) {
            printf("Invalid edge at input position %d.\n", i);
            return 1;
        }

        to[edgeCount] = v;
        next[edgeCount] = head[u];
        head[u] = edgeCount++;

        to[edgeCount] = u;
        next[edgeCount] = head[v];
        head[v] = edgeCount++;
    }

    for (int i = 1; i <= N; i++) {
        if (scanf("%d", &order[i]) != 1 ||
            order[i] < 1 || order[i] > N || seen[order[i]]) {
            printf("Deletion order must be a permutation of 1..N.\n");
            return 1;
        }
        seen[order[i]] = 1;
    }

    MaxHeap heap = {NULL, 0, 0};

    /* Reverse deletions: activate p[N], p[N-1], ..., p[1]. */
    for (int i = N; i >= 1; i--) {
        int v = order[i];
        parent[v] = v;
        compSize[v] = 1;
        compSum[v] = weight[v];
        version[v] = 1;

        HeapItem singleton = {compSum[v], v, version[v]};
        if (!heapPush(&heap, singleton)) {
            printf("Memory allocation failed for the heap.\n");
            return 1;
        }

        for (int edge = head[v]; edge != -1; edge = next[edge]) {
            int u = to[edge];
            if (parent[u] == -1) {
                continue; /* Neighbor has not been restored yet. */
            }

            int rootV = findRoot(parent, v);
            int rootU = findRoot(parent, u);
            if (rootV == rootU) {
                continue;
            }

            if (compSize[rootV] < compSize[rootU]) {
                int temp = rootV;
                rootV = rootU;
                rootU = temp;
            }

            parent[rootU] = rootV;
            compSize[rootV] += compSize[rootU];
            compSum[rootV] += compSum[rootU];
            version[rootV]++;

            HeapItem merged = {compSum[rootV], rootV, version[rootV]};
            if (!heapPush(&heap, merged)) {
                printf("Memory allocation failed for the heap.\n");
                return 1;
            }
        }

        /* After restoring p[i], the graph is the state after i-1 deletions. */
        int exists;
        answer[i - 1] = getMaximum(&heap, parent, version, compSum, &exists);
        hasAnswer[i - 1] = exists;
    }

    /* After all N deletions, no vertices remain, so answer[N] is NONE. */
    for (int deletions = 1; deletions <= N; deletions++) {
        if (hasAnswer[deletions]) {
            printf("After %d deletion(s): maximum component sum = %lld\n",
                   deletions, answer[deletions]);
        } else {
            printf("After %d deletion(s): NONE (the graph is empty)\n", deletions);
        }
    }

    free(weight); free(head); free(to); free(next); free(order); free(seen);
    free(parent); free(compSize); free(version); free(compSum);
    free(answer); free(hasAnswer); free(heap.items);
    return 0;
}
