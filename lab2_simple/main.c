#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_EQUALS 20
#define EPS 0.000000001
#define MAX_ITER 100

typedef double MAT[MAX_EQUALS][MAX_EQUALS+1];
typedef double VEC[MAX_EQUALS];

MAT a; /*Расширенная матрица системы*/
VEC x1; /*Начальное приближение*/
VEC x2; /*Новое приближение*/

unsigned int N; /*Количество уравнений*/

/*Инициализирует расширенную матрицу значениями, введенными пользователем*/
int initMat(unsigned int N, MAT a)
{
    for (int i =0; i<N; i++)
    {
        for (int j=0; j<=N; j++)
        {
            printf("a[%d][%d]=",i,j);
            scanf("%lf", &a[i][j]);
        }
    }
    return 0;
}
/*Выводит расширенную матрицу системы*/
int printMat(unsigned int N, MAT a)
{
    for (int i =0; i<N; i++)
    {
        for (int j=0; j<=N; j++)
        {
            printf("%.3lf ",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int initX(unsigned int N, MAT a, VEC x1 )
{
    for (int i = 0; i<N; i++)
    {
        x1[i]=a[i][N];
    }
    return 0;
}

int printX(unsigned int N, VEC x1 )
{
    for (int i = 0; i<N; i++)
    {
        printf("x[%d]=%lf, ", i, x1[i]);
    }
    printf("\n");
    return 0;
}

double maxX(int N, VEC x)
{
    double m = x[0];
    for (int i = 0; i<N; i++)
    {
        if (x[i]>m)
            m=x[i];
    }
    return m;
}

double testX(unsigned int N, VEC x1, VEC x2)
{
    VEC eps;
    for (int i=0; i<N; i++)
        eps[i]=fabs(x1[i]-x2[i]);
    /*Реализовать поиск максимального значения*/
    return maxX(N, eps);

}

int main()
{
/*Тестовая система
10x1+x2=10.1
x1+10x2=2
x1=1
x2=0.1
*/
    printf("Введите количество уравнений\n");
    scanf("%d", &N);
    /*Решается система из N уравнений*/
    printf("Введите коэфициенты расширенной системы\n");
    initMat(N, a);
    printf("Введена система \n");
    printMat(N,a);

    initX(N,a,x2);

    printf("Начальное приближение\n");
    printX(N,x2);
    int m;
    for(m=0; m<MAX_ITER; m++)
    {
        for(int k=0; k<N; k++)
            x1[k]=x2[k];
        for(int i=0; i<N; i++)
        {
            double delta=a[i][N];
            for (int j=0; j<N; j++)
                delta-=a[i][j]*x1[j];
            delta/=a[i][i];
            x2[i]=delta+x1[i];
        }
        printf("Текущее приближение\n");
        printX(N,x2);
        if (testX(N, x1, x2)<EPS) break;
    }
    if (m==MAX_ITER)
        printf("Ошибка. Достигнуто максимальное количество итераций!");
    else
    {
        printf("Выполнено %d итераций(я). ", m);
        printf("Решение:\n");
        printX(N, x2);
    }
    return 0;
}
