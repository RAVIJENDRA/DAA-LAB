#include <stdio.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159265358979323846

// Recursive FFT function
void fft(complex double a[], int n, int inverse)
{
    int i;

    // Base case
    if (n == 1)
        return;

    // Arrays for even and odd elements
    complex double even[n / 2];
    complex double odd[n / 2];

    // Divide the array
    for (i = 0; i < n / 2; i++)
    {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }

    // Recursive calls
    fft(even, n / 2, inverse);
    fft(odd, n / 2, inverse);

    // Combine
    for (i = 0; i < n / 2; i++)
    {
        double angle = 2 * PI * i / n;

        if (!inverse)
            angle = -angle;

        complex double w = cos(angle) + I * sin(angle);

        complex double t = w * odd[i];

        a[i] = even[i] + t;
        a[i + n / 2] = even[i] - t;
    }
}

// Find the smallest power of 2 >= required size
int nextPowerOfTwo(int size)
{
    int n = 1;

    while (n < size)
        n = n * 2;

    return n;
}

int main()
{
    int m, n;
    int i;
    int size;

    printf("Enter size of vector A: ");
    scanf("%d", &m);

    printf("Enter size of vector B: ");
    scanf("%d", &n);

    // Check condition n >= m
    if (n < m)
    {
        printf("Condition n >= m is not satisfied.\n");
        return 0;
    }

    complex double A[1024];
    complex double B[1024];

    printf("Enter elements of vector A:\n");
    for (i = 0; i < m; i++)
    {
        double x;
        scanf("%lf", &x);
        A[i] = x;
    }

    printf("Enter elements of vector B:\n");
    for (i = 0; i < n; i++)
    {
        double x;
        scanf("%lf", &x);
        B[i] = x;
    }

    // Required convolution size
    size = nextPowerOfTwo(m + n - 1);

    // Fill remaining positions with zero
    for (i = m; i < size; i++)
        A[i] = 0;

    for (i = n; i < size; i++)
        B[i] = 0;

    // FFT of A and B
    fft(A, size, 0);
    fft(B, size, 0);

    // Point-wise multiplication
    for (i = 0; i < size; i++)
        A[i] = A[i] * B[i];

    // Inverse FFT
    fft(A, size, 1);

    // Divide by size after inverse FFT
    for (i = 0; i < size; i++)
        A[i] = A[i] / size;

    // Print convolution
    printf("\nConvolution of A and B:\n");

    for (i = 0; i < m + n - 1; i++)
    {
        printf("%.2f ", creal(A[i]));
    }

    printf("\n");

    return 0;
}