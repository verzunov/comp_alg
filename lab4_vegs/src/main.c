#define EPS 1e-6
#define MAX_ITER 100
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double x0;
double x1;
double x2;
double f(double x)
{
    return x*x +4 ;
}
double psi(double x0, double x1)
{
    return -1.0/(
        (f(x1)-f(x0))/(x1-x0)
    ); /*(3)*/
}
int main()
{
    printf("Введите 1 начальное приближение\n");
    scanf("%lf", &x1);
    printf("Введите 2 начальное приближение\n");
    scanf("%lf", &x2);
    int i;
    for(i=0; i<MAX_ITER;i++)
    {
        x0=x1;
        x1=x2;
        double delta;
        delta=f(x1)*psi(x0, x1);
        if (fabs(delta)<EPS) break;
        x2=x1+delta;
        printf("Текущее приближение x2=%lf\n",x2);
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