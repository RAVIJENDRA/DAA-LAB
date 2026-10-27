#include <stdio.h>
#include <stdlib.h>

int findRoot(int parent[], int x) {
    if (parent[x] != x) {
        parent[x] = findRoot(parent, parent[x]);
    }
    return parent[x];
}

/* Return 1 only when two different components were merged. */
int unite(int parent[], int size[], int a, int b) {
    int rootA = findRoot(parent, a);
    int rootB = findRoot(parent, b);

    if (rootA == rootB) {
        return 0;
    }

    if (size[rootA] < size[rootB]) {
        int temp = rootA;
        rootA = rootB;
        rootB = temp;
    }

    parent[rootB] = rootA;
    size[rootA] += size[rootB];
    return 1;
}

int main(void) {
    int R, C, K;
    if (scanf("%d %d %d", &R, &C, &K) != 3 ||
        R <= 0 || C <= 0 || K < 0 || (long long)R * C > 2000000000LL) {
        printf("Invalid input. Expected positive R, C and non-negative K.\n");
        return 1;
    }

    int cells = R * C;
    int *parent = malloc((size_t)cells * sizeof(int));
    int *size = malloc((size_t)cells * sizeof(int));
    if (parent == NULL || size == NULL) {
        printf("Memory allocation failed.\n");
        free(parent);
        free(size);
        return 1;
    }

    /* parent[id] == -1 means that cell is still water. */
    for (int i = 0; i < cells; i++) {
        parent[i] = -1;
        size[i] = 0;
    }

    int islands = 0;
    for (int operation = 1; operation <= K; operation++) {
        int row, col;
        if (scanf("%d %d", &row, &col) != 2 ||
            row < 1 || row > R || col < 1 || col > C) {
            printf("Invalid coordinate at operation %d.\n", operation);
            free(parent);
            free(size);
            return 1;
        }

        int r = row - 1;
        int c = col - 1;
        int id = r * C + c;

        /* Re-adding an existing land cell changes nothing. */
        if (parent[id] == -1) {
            parent[id] = id;
            size[id] = 1;
            islands++;

            /* Only orthogonal neighbors count: up, down, left, right. */
            if (r > 0) {
                int neighbor = id - C;
                if (parent[neighbor] != -1 &&
                    unite(parent, size, id, neighbor)) {
                    islands--;
                }
            }
            if (r + 1 < R) {
                int neighbor = id + C;
                if (parent[neighbor] != -1 &&
                    unite(parent, size, id, neighbor)) {
                    islands--;
                }
            }
            if (c > 0) {
                int neighbor = id - 1;
                if (parent[neighbor] != -1 &&
                    unite(parent, size, id, neighbor)) {
                    islands--;
                }
            }
            if (c + 1 < C) {
                int neighbor = id + 1;
                if (parent[neighbor] != -1 &&
                    unite(parent, size, id, neighbor)) {
                    islands--;
                }
            }
        }

        printf("After adding (%d, %d): islands = %d\n", row, col, islands);
    }

    free(parent);
    free(size);
    return 0;
}
