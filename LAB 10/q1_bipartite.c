#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *parent;
    int *size;
    int *xorToParent;
} ParityDSU;

int findRoot(ParityDSU *dsu, int x) {
    if (dsu->parent[x] != x) {
        int oldParent = dsu->parent[x];
        dsu->parent[x] = findRoot(dsu, oldParent);
        dsu->xorToParent[x] ^= dsu->xorToParent[oldParent];
    }
    return dsu->parent[x];
}

/* Add the constraint that u and v must have opposite colors. */
int addEdge(ParityDSU *dsu, int u, int v) {
    int rootU = findRoot(dsu, u);
    int parityU = dsu->xorToParent[u];
    int rootV = findRoot(dsu, v);
    int parityV = dsu->xorToParent[v];

    if (rootU == rootV) {
        /* The existing path must give u and v opposite colors. */
        return ((parityU ^ parityV) == 1);
    }

    /* color[rootU] XOR color[rootV] = parityU XOR parityV XOR 1 */
    int rootParity = parityU ^ parityV ^ 1;

    if (dsu->size[rootU] < dsu->size[rootV]) {
        dsu->parent[rootU] = rootV;
        dsu->xorToParent[rootU] = rootParity;
        dsu->size[rootV] += dsu->size[rootU];
    } else {
        dsu->parent[rootV] = rootU;
        dsu->xorToParent[rootV] = rootParity;
        dsu->size[rootU] += dsu->size[rootV];
    }
    return 1;
}

int main(void) {
    int V, E;
    if (scanf("%d %d", &V, &E) != 2 || V <= 0 || E < 0) {
        printf("Invalid input. Expected V E, with V > 0 and E >= 0.\n");
        return 1;
    }

    ParityDSU dsu;
    dsu.parent = malloc((size_t)(V + 1) * sizeof(int));
    dsu.size = malloc((size_t)(V + 1) * sizeof(int));
    dsu.xorToParent = malloc((size_t)(V + 1) * sizeof(int));
    if (dsu.parent == NULL || dsu.size == NULL || dsu.xorToParent == NULL) {
        printf("Memory allocation failed.\n");
        free(dsu.parent);
        free(dsu.size);
        free(dsu.xorToParent);
        return 1;
    }

    for (int v = 1; v <= V; v++) {
        dsu.parent[v] = v;
        dsu.size[v] = 1;
        dsu.xorToParent[v] = 0;
    }
    for (int i = 1; i <= E; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2 || u < 1 || u > V || v < 1 || v > V) {
            printf("Invalid edge input at edge %d.\n", i);
            free(dsu.parent);
            free(dsu.size);
            free(dsu.xorToParent);
            return 1;
        }

        if (addEdge(&dsu, u, v)) {
            printf("Edge %d (%d, %d): ACCEPTED\n", i, u, v);
        } else {
            printf("Edge %d (%d, %d): REJECTED - would break bipartiteness\n",
                   i, u, v);
        }
    }
    free(dsu.parent);
    free(dsu.size);
    free(dsu.xorToParent);
    return 0;
}
