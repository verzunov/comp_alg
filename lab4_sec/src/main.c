#define EPS 1e-6
#define MAX_ITER 100
#define DX 1e-3

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double x0;
double x1;
double f(double x)
{
    return x*x-4;
}
double psi(double x)
{
    
    return -(f(x+DX)-f(x))/DX;
}
int main()
{
    printf("Введите начальное приближение\n");
    scanf("%lf", &x1);
    int i;
    for(i=0; i<MAX_ITER;i++)
    {
        x0=x1;
        double delta;
        delta=f(x0)/psi(x0);
        if (fabs(delta)<EPS) break;
        x1=x0+delta;
        printf("Текущее приближение x=%lf\n",x1);
    }
    if (i==MAX_ITER)
    {
        printf("Достигнута максимальное количество итераций.\n");
        return 1;
    }
    printf("x=%lf\n", x1);
    printf("Понадобилось %d итераций. \n", i);
    return 0;

}
