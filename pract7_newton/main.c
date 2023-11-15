#include <stdio.h>

#define MAXN 100  // Максимальное количество узлов интерполяции

// Функция для вычисления разделённых разностей
void dividedDifferences(float x[], float y[], int n, float diffTable[MAXN][MAXN]) {
    for (int i = 0; i < n; i++) {
        diffTable[i][0] = y[i];
    }

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            diffTable[i][j] = (diffTable[i + 1][j - 1] - diffTable[i][j - 1]) / (x[i + j] - x[i]);
        }
    }
}

// Функция для вычисления значения интерполяционного полинома Ньютона
float newtonPolynomial(float x[], float diffTable[MAXN][MAXN], int n, float value) {
    float result = diffTable[0][0];
    float product;

    for (int i = 1; i < n; i++) {
        product = diffTable[0][i];
        for (int j = 0; j < i; j++) {
            product *= (value - x[j]);
        }
        result += product;
    }

    return result;
}

int main() {
    float x[MAXN], y[MAXN], value;
    int n;

    printf("Enter the number of points: ");
    scanf("%d", &n);

    printf("Enter the values of x and y:\n");
    for (int i = 0; i < n; i++) {
        scanf("%f %f", &x[i], &y[i]);
    }

    printf("Enter the value of x to find the corresponding y: ");
    scanf("%f", &value);

    float diffTable[MAXN][MAXN]; // Таблица разделенных разностей
    dividedDifferences(x, y, n, diffTable);

    printf("Value of polynomial at %f is %f\n", value, newtonPolynomial(x, diffTable, n, value));

    return 0;
}
