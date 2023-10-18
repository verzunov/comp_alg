#define EPS 1e-6
#define MAX_ITER 100
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double x0;
double x1;
double f(double x)
{
    return x*x*x -27 ;
}
double psi(double x)
{
    return -1.0/(3.0*x*x);
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
        delta=f(x0)*psi(x0);
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
