#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-9  // Маленькое число для сравнения с плавающей точкой

// Функция для обмена двух строк матрицы
void swap_rows(double **mat, int row1, int row2, int n) {
    for (int i = 0; i <= n; i++) {
        double temp = mat[row1][i];
        mat[row1][i] = mat[row2][i];
        mat[row2][i] = temp;
    }
}

// Функция реализующая метод Гаусса
void gauss_elimination(double **mat, int n, double *x) {
    // Прямой ход
    for (int i = 0; i < n; i++) {
        // Ищем строку с максимальным элементом в текущем столбце
        int max_row = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(mat[k][i]) > fabs(mat[max_row][i])) {
                max_row = k;
            }
        }
        
        // Меняем местами строку с максимальным элементом и текущую строку
        swap_rows(mat, i, max_row, n);
        
        // Зануляем элементы ниже главной диагонали
        for (int k = i + 1; k < n; k++) {
            double factor = mat[k][i] / mat[i][i];
            for (int j = i; j <= n; j++) {
                mat[k][j] -= factor * mat[i][j];
            }
        }
    }
    
    // Обратный ход
    for (int i = n - 1; i >= 0; i--) {
        x[i] = mat[i][n] / mat[i][i];
        for (int k = i - 1; k >= 0; k--) {
            mat[k][n] -= mat[k][i] * x[i];
        }
    }
}

int main() {
    int n;
    printf("Enter the number of equations: ");
    scanf("%d", &n);

    // Выделение памяти для матрицы и вектора решений
    double **mat = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        mat[i] = (double *)malloc((n + 1) * sizeof(double));
    }

    // Ввод элементов матрицы
    printf("Enter the augmented matrix of the system (A|B):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            scanf("%lf", &mat[i][j]);
        }
    }

    double *x = (double *)malloc(n * sizeof(double));

    // Решение системы уравнений методом Гаусса
    gauss_elimination(mat, n, x);

    // Вывод решения
    printf("Solution:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %lf\n", i + 1, x[i]);
    }

    // Освобождение выделенной памяти
    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
    free(x);

    return 0;
}
