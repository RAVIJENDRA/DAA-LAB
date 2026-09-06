#include <stdio.h>
#include <math.h>

#define MAX 20

/* Matrix Addition */
void addMatrices(int A[MAX][MAX], int B[MAX][MAX],
                 int C[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

/* Matrix Multiplication */
void multiplyMatrices(int A[MAX][MAX], int B[MAX][MAX],
                      int C[MAX][MAX], int n)
{
    int i, j, k;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for (k = 0; k < n; k++)
            {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
}

/* Check whether matrix is a zero matrix */
int isZeroMatrix(int A[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (A[i][j] != 0)
            {
                return 0;
            }
        }
    }

    return 1;
}

/* Check whether matrix is symmetric */
int isSymmetric(int A[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (A[i][j] != A[j][i])
            {
                return 0;
            }
        }
    }

    return 1;
}

/* Create a smaller matrix by removing one row and one column */
void getCofactor(int A[MAX][MAX], int temp[MAX][MAX],
                 int p, int q, int n)
{
    int i = 0, j = 0;
    int row, col;

    for (row = 0; row < n; row++)
    {
        for (col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j] = A[row][col];

                j++;

                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

/* Recursive determinant */
int determinant(int A[MAX][MAX], int n)
{
    int det = 0;
    int sign = 1;
    int temp[MAX][MAX];
    int col;

    if (n == 1)
    {
        return A[0][0];
    }

    if (n == 2)
    {
        return A[0][0] * A[1][1]
             - A[0][1] * A[1][0];
    }

    for (col = 0; col < n; col++)
    {
        getCofactor(A, temp, 0, col, n);

        det = det + sign * A[0][col]
              * determinant(temp, n - 1);

        sign = -sign;
    }

    return det;
}

/* In-place transpose */
void transpose(int A[MAX][MAX], int n)
{
    int i, j, temp;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

/* Power Method for dominant eigenvalue and eigenvector */
void powerMethod(int A[MAX][MAX], int n)
{
    double x[MAX];
    double y[MAX];
    double eigenvalue;
    double maxValue;
    int i, j, iteration;
    int maxIndex;

    /* Initial vector */
    for (i = 0; i < n; i++)
    {
        x[i] = 1.0;
    }

    for (iteration = 0; iteration < 100; iteration++)
    {
        /* y = A*x */
        for (i = 0; i < n; i++)
        {
            y[i] = 0;

            for (j = 0; j < n; j++)
            {
                y[i] = y[i] + A[i][j] * x[j];
            }
        }

        /* Find largest absolute value */
        maxValue = fabs(y[0]);
        maxIndex = 0;

        for (i = 1; i < n; i++)
        {
            if (fabs(y[i]) > maxValue)
            {
                maxValue = fabs(y[i]);
                maxIndex = i;
            }
        }

        eigenvalue = y[maxIndex];

        /* Normalize vector */
        for (i = 0; i < n; i++)
        {
            x[i] = y[i] / eigenvalue;
        }
    }

    printf("\nDominant Eigenvalue = %.4lf\n", eigenvalue);

    printf("Corresponding Eigenvector:\n");

    for (i = 0; i < n; i++)
    {
        printf("%.4lf ", x[i]);
    }

    printf("\n");
}

/* Display matrix */
void displayMatrix(int A[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", A[i][j]);
        }

        printf("\n");
    }
}

int main()
{
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int n;
    int i, j;
    int det;

    printf("Enter order of square matrix: ");
    scanf("%d", &n);

    printf("\nEnter elements of Matrix A:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    printf("\nEnter elements of Matrix B:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }

    /* Matrix Addition */
    addMatrices(A, B, C, n);

    printf("\nMatrix Addition:\n");
    displayMatrix(C, n);

    /* Matrix Multiplication */
    multiplyMatrices(A, B, C, n);

    printf("\nMatrix Multiplication:\n");
    displayMatrix(C, n);

    /* Zero Matrix */
    if (isZeroMatrix(A, n))
        printf("\nMatrix A is a Zero Matrix.\n");
    else
        printf("\nMatrix A is NOT a Zero Matrix.\n");

    /* Symmetric Matrix */
    if (isSymmetric(A, n))
        printf("Matrix A is Symmetric.\n");
    else
        printf("Matrix A is NOT Symmetric.\n");

    /* Determinant */
    det = determinant(A, n);

    printf("Determinant of Matrix A = %d\n", det);

    /* Transpose */
    transpose(A, n);

    printf("\nTranspose of Matrix A:\n");
    displayMatrix(A, n);

    /* Eigenvalue and Eigenvector */
    printf("\nEigenvalue and Eigenvector:\n");
    powerMethod(B, n);

    return 0;
}