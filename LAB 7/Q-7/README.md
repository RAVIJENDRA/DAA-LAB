# Matrix Chain Multiplication (MCM) - DAA Lab

## Aim
Implement the Matrix Chain Multiplication problem using Dynamic Programming in C and find:

1. The minimum number of scalar multiplications.
2. The optimal order (parenthesization) of matrix multiplication.

## Problem
Suppose we have matrices:

A1, A2, ..., An

Matrix multiplication is associative, so the final result is the same for every valid parenthesization. However, the number of scalar multiplications can be very different.

For example:

(A1 A2) A3 and A1 (A2 A3)

give the same final matrix, but may require different numbers of scalar multiplications.

The objective is to choose the order that requires the minimum number of scalar multiplications.

## Dynamic Programming Idea

Let:

m[i][j] = minimum number of scalar multiplications needed to multiply
          matrices Ai through Aj.

If the chain is split between Ak and A(k+1), then:

m[i][j] = m[i][k] + m[k+1][j]
          + p[i-1] * p[k] * p[j]

where p contains the matrix dimensions.

The minimum is taken over every possible k from i to j-1.

A second table, split[i][j], stores the split point that gives the minimum cost. It is used to print the optimal parenthesization.

## Input Format

First enter the number of matrices n.

Then enter n+1 dimensions.

If:
A1 = p0 x p1
A2 = p1 x p2
...
An = p(n-1) x pn

then the input is:

n
p0 p1 p2 ... pn

## Sample Input

4
10 20 30 40 30

This represents:

A1 = 10 x 20
A2 = 20 x 30
A3 = 30 x 40
A4 = 40 x 30

## Sample Output

Minimum number of scalar multiplications = 44000
Optimal parenthesization = ((A1(A2A3))A4)

## Complexity

Time Complexity: O(n^3)

There are O(n^2) subproblems. For each subproblem, we try O(n)
possible split points.

Space Complexity: O(n^2)

The m and split tables each use O(n^2) space.

## Important C Variables

- p[]: stores matrix dimensions.
- m[][]: stores minimum multiplication cost for each matrix chain.
- split[][]: stores the best split point for each chain.
- n: number of matrices.
- length: current chain length.
- i, j: starting and ending matrix indices.
- k: possible split position.
- cost: cost obtained for the current split.
- minimumCost: final minimum multiplication count.

## Functions

### matrixChainMultiplication()
Calculates the minimum number of scalar multiplications using bottom-up
Dynamic Programming.

### printOrder()
Uses the split table recursively to print the optimal parenthesization.

## Algorithm

1. Read n and n+1 dimensions.
2. Set m[i][i] = 0 because one matrix needs no multiplication.
3. Consider chains of length 2, 3, ..., n.
4. For every chain Ai...Aj, try every split k.
5. Calculate:
   m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j]
6. Store the smallest cost in m[i][j].
7. Store the corresponding k in split[i][j].
8. The answer is m[1][n].
9. Use split[][] to print the optimal parenthesization.

## Why Dynamic Programming?

A brute-force approach checks all possible parenthesizations and becomes
very expensive as n increases.

Dynamic Programming avoids calculating the same smaller matrix-chain
problems repeatedly. It stores their answers in m[][] and reuses them.

## Advantages

- Much faster than brute-force enumeration for large n.
- Avoids repeated calculation of the same subproblems.
- Also gives the optimal multiplication order.

## Disadvantages

- Requires O(n^2) memory.
- The implementation is more complex than a simple recursive brute-force
  solution.

## Viva Quick Revision

1. What is MCM?
   It finds the multiplication order that minimizes scalar multiplications.

2. Why does order matter?
   Matrix multiplication is associative, but different orders can have
   different costs.

3. Why Dynamic Programming?
   MCM has overlapping subproblems and optimal substructure.

4. What does m[i][j] store?
   Minimum cost to multiply Ai through Aj.

5. What does split[i][j] store?
   The k at which the optimal chain is split.

6. Why is m[i][i] = 0?
   A single matrix does not need multiplication.

7. Time complexity?
   O(n^3).

8. Space complexity?
   O(n^2).

9. What is p[]?
   It stores the dimensions of all matrices in compact form.

10. How is the optimal order printed?
    printOrder() uses split[][] recursively.
