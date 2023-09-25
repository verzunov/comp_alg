#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 3
#define EPS 1e-6
#define MAX_ITER 1000

/*Тестовая система
10x1+x2=10.1
x1+10x2=2
x1=1
x2=0.1
*/
double A[N][N] = {
    {10, 1},
    {1, 10},
};

double b[N] = {10.1, 2};
double x[N];
double prev_x[N];

void print_solution() {
    for (int i = 0; i < N; i++) {
        printf("x%d = %lf\n", i+1, x[i]);
    }
}

int main() {
    for (int i = 0; i < N; i++) {
        x[i] = 0; // начальное приближение
    }

    int iter;
    for (iter = 0; iter < MAX_ITER; iter++) {
        for (int i = 0; i < N; i++) {
            prev_x[i] = x[i];
            double sum = b[i];

            for (int j = 0; j < N; j++) {
                if (i != j) {
                    sum -= A[i][j] * prev_x[j];
                }
            }

            x[i] = sum / A[i][i];
        }

        double norm = 0;
        for (int i = 0; i < N; i++) {
            if (fabs(prev_x[i] - x[i]) > norm) {
                norm = fabs(prev_x[i] - x[i]);
            }
        }

        if (norm < EPS) {
            break;
        }
    }

    if (iter == MAX_ITER) {
        printf("Метод не сошелся за %d итераций.\n", MAX_ITER);
    } else {
        printf("Решение после %d итераций:\n", iter + 1);
        print_solution();
    }

    return 0;
}
