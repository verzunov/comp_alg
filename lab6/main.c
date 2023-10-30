#include <stdio.h>
#include <stdlib.h>

void intro(double *x, double *y, double xxs, double *yxs, int q){
    int w,d;
    double k;

    for(d=0; d<q; d++){
        k=1;
        for(w=0; w<q; w++){
            if(w==d) continue;
            k*=(xxs-x[w])/(x[d]-x[w]);
        }
        *yxs+=y[d]*k;
    }
}

int main() {
    int i, m;
    FILE *fifa;
    double *X, *Y, j = 0, Xcsy, Ycsy = 0;
    printf("Input number of knots");
    scanf("%d", &m);

    X = malloc(m * sizeof(double));
    Y = malloc(m * sizeof(double));

    printf("Input Xi:\n");
    for (i = 0; i < m; i++) {
        scanf("%lf", &X[i]);
    }
    printf("Input Yi:\n");
    for (i = 0; i < m; i++) {
        scanf("%lf", &Y[i]);
    }
    printf("Input Xcsy:\n");
    scanf("%lf", &Xcsy);
    intro(X, Y, Xcsy, &Ycsy, m);
    printf("Ycsy = %lf", Ycsy);
    fifa = popen("gnuplot", "w");
    fprintf(fifa, "set grid\n");
    fprintf(fifa, "set xrange [0:2.5]\n");
    fprintf(fifa, "set yrange [0:1]\n");
    fprintf(fifa, "set style line 1 lc rgb 'red' pt 2\n");
    fprintf(fifa, "set style line 2 lc rgb 'blue' pt 7\n");
    fprintf(fifa, "plot '-' w p ls 1 title '', '-' with lines title '', '-' w p ls 2 title ''\n");
    fprintf(fifa, "%lf %lf\n", Xcsy, Ycsy);
    fprintf(fifa, "e\n");

    while (j <= 3) {
        Ycsy = 0;
        intro(X, Y, j, &Ycsy, m);
        fprintf(fifa, "%lf %lf\n", j, Ycsy);
        j += 0.01;
    }
    fprintf(fifa, "e\n");
    for (i = 0; i < m; i++) {
        fprintf(fifa, "%lf %lf\n", X[i], Y[i]);
    }
    fprintf(fifa, "e\n");
    fprintf(fifa, "pause mouse keypress\n");
    fflush(fifa);

    free(X);
    free(Y);
    return 0;
}