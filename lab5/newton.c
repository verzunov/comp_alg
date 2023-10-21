#include <stdio.h>
#include <math.h>
#define EPSILON 0.00001


void Jacobian(double x, double y, double J[2][2]) {
J[0][0] = 2*x; // df/dx
J[0][1] = 2*y; // df/dy
J[1][0] = y; // dg/dx
J[1][1] = x; // dg/dy
}
void Func(double x, double y, double F[2]) {
F[0] = x*x + y*y - 4;
F[1] = x * y - 1;
}
void Newton(double* x, double* y) {
double J[2][2], F[2], det, dx, dy;
int iter = 0;
do {
Jacobian(*x, *y, J);
Func(*x, *y, F);
det = J[0][0]*J[1][1] - J[0][1]*J[1][0];
printf("det=%.5lf\n", det);
dx = (-F[0]*J[1][1] + F[1]*J[0][1]) / det;
dy = (-J[0][0]*F[1] + J[1][0]*F[0]) / det;
*x += dx;
*y += dy;
printf("x=%.5lf, y=%.5lf\n", *x, *y);

iter++;
} while (fabs(dx) > EPSILON || fabs(dy) > EPSILON);
printf("Iterations: %d\n", iter);
}
int main() {
double x = 1.0;
double y = 2.0;
Newton(&x, &y);
printf("Roots: x = %.5lf, y = %.5lf\n", x, y);
return 0;
}
