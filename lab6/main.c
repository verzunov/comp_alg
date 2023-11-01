#include <stdio.h>
#define MAX_NODE 10
double X[MAX_NODE], Y[MAX_NODE];
int N;
FILE *fifa;
double l_(int i, double x)
{
    double acc =1.0;
    for(int j=0; j<N; j++)
    {
        if (i == j) continue;
        acc *= x - X[j];
    }
    return acc;
}
double l(int i, double x)
{
    return l_(i, x)/l_(i, X[i]);
}
double P(double x)
{
    double acc=0;
    for(int i=0; i<N; i++)
        acc+=Y[i]*l(i,x);
    return  acc;

}
int main() {
    printf("Введите количество узлов ");
    scanf("%d",&N);
    for(int i=0; i<N; i++)
    {
        printf("Введите x[%d] y[%d] ", i, i);
        scanf("%lf %lf", &X[i], &Y[i]);
    }
    double x;
    printf ("Введите значение x ");
    scanf("%lf", &x);
    double y =P(x);
    printf("P=%lf" , y);
    fifa = popen("gnuplot", "w");
    fprintf(fifa, "set grid\n");
    fprintf(fifa, "set xrange [-5:5]\n");
    fprintf(fifa, "set yrange [0:10]\n");
    fprintf(fifa, "set style line 1 lc rgb 'red' pt 2\n");
    fprintf(fifa, "set style line 2 lc rgb 'blue' pt 7\n");
    fprintf(fifa, "plot '-' w p ls 1 title '', '-' with lines title '', '-' w p ls 2 title ''\n");
    fprintf(fifa, "%lf %lf\n", x, y);
    fprintf(fifa, "e\n");


    double a=-5;
    while (a <= 5) {

        fprintf(fifa, "%lf %lf\n", a, P(a));
       a += 0.01;
    }
    fprintf(fifa, "e\n");
    for (int i = 0; i < N; i++) {
        fprintf(fifa, "%lf %lf\n", X[i], Y[i]);
    }
    fprintf(fifa, "set title \"Polinom Lagranja\", font '20'\n");
    fprintf(fifa, "e\n");
    fprintf(fifa, "pause mouse keypress\n");
    fflush(fifa);
    return 0;
}
