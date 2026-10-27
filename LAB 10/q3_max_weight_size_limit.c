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

/* Discard old heap records until the maximum is a current eligible component. */
long long getMaximum(MaxHeap *heap, int parent[], int compSize[],
                     long long compSum[], int version[], int K, int *exists) {
    while (heap->size > 0) {
        HeapItem top = heap->items[0];
        int root = top.root;
        int isCurrent = (parent[root] == root &&
                         version[root] == top.version &&
                         compSize[root] <= K &&
                         compSum[root] == top.sum);
        if (isCurrent) {
            *exists = 1;
            return top.sum;
        }
        heapPop(heap);
    }

    *exists = 0;
    return 0;
}

int main(void) {
    int N, M, K;
    if (scanf("%d %d %d", &N, &M, &K) != 3 ||
        N <= 0 || M < 0 || K < 0) {
        printf("Invalid input. Expected N M K, with N > 0 and M, K >= 0.\n");
        return 1;
    }

    int *parent = malloc((size_t)(N + 1) * sizeof(int));
    int *compSize = malloc((size_t)(N + 1) * sizeof(int));
    int *version = malloc((size_t)(N + 1) * sizeof(int));
    long long *compSum = malloc((size_t)(N + 1) * sizeof(long long));
    if (parent == NULL || compSize == NULL || version == NULL || compSum == NULL) {
        printf("Memory allocation failed.\n");
        free(parent);
        free(compSize);
        free(version);
        free(compSum);
        return 1;
    }

    for (int v = 1; v <= N; v++) {
        long long weight;
        if (scanf("%lld", &weight) != 1) {
            printf("Invalid vertex weight input.\n");
            free(parent);
            free(compSize);
            free(version);
            free(compSum);
            return 1;
        }
        parent[v] = v;
        compSize[v] = 1;
        compSum[v] = weight;
        version[v] = 1;
    }

    /* Move to the next line so each edge can be read as its own record. */
    int character;
    while ((character = getchar()) != '\n' && character != EOF) {
        /* Discard any remaining characters on the vertex-weight line. */
    }

    MaxHeap heap = {NULL, 0, 0};
    if (K >= 1) {
        for (int v = 1; v <= N; v++) {
            HeapItem item = {compSum[v], v, version[v]};
            if (!heapPush(&heap, item)) {
                printf("Memory allocation failed for the heap.\n");
                free(parent);
                free(compSize);
                free(version);
                free(compSum);
                free(heap.items);
                return 1;
            }
        }
    }

    for (int i = 1; i <= M; i++) {
        char edgeLine[256];
        int u, v;
        long long ignoredEdgeWeight = 0;
        int fields;

        if (fgets(edgeLine, sizeof(edgeLine), stdin) == NULL) {
            printf("Missing edge at operation %d.\n", i);
            free(parent);
            free(compSize);
            free(version);
            free(compSum);
            free(heap.items);
            return 1;
        }
        fields = sscanf(edgeLine, "%d %d %lld", &u, &v, &ignoredEdgeWeight);
        if (fields < 2 || u < 1 || u > N || v < 1 || v > N) {
            printf("Invalid edge at operation %d.\n", i);
            free(parent);
            free(compSize);
            free(version);
            free(compSum);
            free(heap.items);
            return 1;
        }
        /* An optional edge weight is parsed but is not part of this objective. */
        (void)ignoredEdgeWeight;

        int rootU = findRoot(parent, u);
        int rootV = findRoot(parent, v);

        if (rootU != rootV) {
            if (compSize[rootU] < compSize[rootV]) {
                int temp = rootU;
                rootU = rootV;
                rootV = temp;
            }

            parent[rootV] = rootU;
            compSize[rootU] += compSize[rootV];
            compSum[rootU] += compSum[rootV];
            version[rootU]++;

            if (compSize[rootU] <= K) {
                HeapItem item = {compSum[rootU], rootU, version[rootU]};
                if (!heapPush(&heap, item)) {
                    printf("Memory allocation failed for the heap.\n");
                    free(parent);
                    free(compSize);
                    free(version);
                    free(compSum);
                    free(heap.items);
                    return 1;
                }
            }
        }

        int exists;
        long long best = getMaximum(&heap, parent, compSize, compSum,
                                    version, K, &exists);
        if (exists) {
            printf("After edge (%d, %d): maximum eligible component weight = %lld\n",
                   u, v, best);
        } else {
            printf("After edge (%d, %d): NONE (no component has size <= K)\n",
                   u, v);
        }
    }

    free(parent);
    free(compSize);
    free(version);
    free(compSum);
    free(heap.items);
    return 0;
}
