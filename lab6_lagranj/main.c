#include <stdio.h>
#define MAX_NODE 100
double X[MAX_NODE], Y[MAX_NODE];
int N;
FILE *fi;
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
    fi = popen("gnuplot", "w");
    fprintf(fi, "set grid\n");
    fprintf(fi, "set xrange [-5:5]\n");
    fprintf(fi, "set yrange [0:30]\n");
    fprintf(fi, "set style line 1 lc rgb 'red' pt 2\n");
    fprintf(fi, "set style line 2 lc rgb 'blue' pt 7\n");
    fprintf(fi, "plot '-' w p ls 1 title '', '-' with lines title '', '-' w p ls 2 title ''\n");
    fprintf(fi, "%lf %lf\n", x, y);
    fprintf(fi, "e\n");

    double a=-5;
    while (a <= 5) {

        fprintf(fi, "%lf %lf\n", a, P(a));
       a += 0.01;
    }
    fprintf(fi, "e\n");
    for (int i = 0; i < N; i++) {
        fprintf(fi, "%lf %lf\n", X[i], Y[i]);
    }
    fprintf(fi, "e\n");

    fprintf(fi, "set title \"Polinom Lagranja\", font '20'\n");
    fprintf(fi, "pause mouse keypress\n");
    fflush(fi);
    return 0;
}
