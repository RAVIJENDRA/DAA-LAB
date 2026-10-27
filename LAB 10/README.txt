GRAPH + DISJOINT SET UNION (DSU) SOLUTIONS

Files
-----
q1_bipartite.c                Online bipartiteness, parity DSU
q2_grid_islands.c             Dynamic 4-neighbor islands in a grid
q3_max_weight_size_limit.c    Max component vertex-weight sum with size <= K
q4_reverse_deletions.c        Reverse-time DSU for vertex deletions
q5_lexicographic_permutation.c Lexicographically smallest achievable permutation

Compile any program with a C11 compiler, for example:
  gcc -std=c11 -Wall -Wextra -Wpedantic -O2 q1_bipartite.c -o q1
Then run it and enter the input format shown in the PDF.

Input summary
-------------
1) Q1: V E, followed by E edge pairs u v.
2) Q2: R C K, followed by K grid coordinates row col (1-based).
3) Q3: N M K, N vertex weights, then M edge lines. An edge line can be
   `u v` or `u v edgeWeight`; any optional edgeWeight is ignored because the
   stated objective sums vertex weights.
4) Q4: N M, N vertex weights, M edge pairs u v, then the deletion permutation
   p1 ... pN.
5) Q5: N M, permutation A[1..N], then M allowed-swap edge pairs u v.

All vertices and coordinates in the input are 1-based. Sample runs and the
full explanations are in Graph_DSU_Five_Problems_Solved.pdf.
