#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 2 // Размер матрицы. Можно изменить.
#define EPS 0.000000001 // Точность вычисления

void print_vector(double *x) {
    for (int i = 0; i < N; i++) {
        printf("%f ", x[i]);
    }
    printf("\n");
}

double norm(double *x, double *y) {
    double max = fabs(x[0] - y[0]);
    for (int i = 1; i < N; i++) {
        if (fabs(x[i] - y[i]) > max) {
            max = fabs(x[i] - y[i]);
        }
    }
    return max;
}

void simple_iteration(double (*A)[N], double *B, double *x) {
    double prev_x[N];
    double Bx[N];
    int iter = 0;

    for (int i = 0; i < N; i++) {
        x[i] = B[i];
    }

    do {
        for (int i = 0; i < N; i++) {
            prev_x[i] = x[i];
        }

        for (int i = 0; i < N; i++) {
            Bx[i] = B[i];
            for (int j = 0; j < N; j++) {
                if (i != j) {
                    Bx[i] -= A[i][j] * prev_x[j] / A[i][i];
                }
            }
        }

        for (int i = 0; i < N; i++) {
            x[i] = Bx[i];
        }

        iter++;

    } while (norm(x, prev_x) >= EPS);

    printf("Iterations: %d\n", iter);
}
/*Тестовая система
10x1+x2=10.1
x1+10x2=2
x1=1
x2=0.1
*/
int main() {
    double A[N][N] = {
        {10, 1},
        {1, 10},
    };
    double B[N] = {10.1, 2};

    double x[N];

    simple_iteration(A, B, x);

    printf("Solution:\n");
    print_vector(x);

    return 0;
}
